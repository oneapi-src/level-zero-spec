#include "xe_all.h"

#include <iostream>
#include <fstream>
#include <memory>

template <typename SizeT>
inline std::unique_ptr<char[]> readBinaryFile(const std::string &name, SizeT &outSize) {
    std::ifstream file(name, std::ios_base::binary);
    if (false == file.good()) {
        outSize = 0;
        return nullptr;
    }

    size_t length;
    file.seekg(0, file.end);
    length = static_cast<size_t>(file.tellg());
    file.seekg(0, file.beg);

    auto storage = std::make_unique<char[]>(length);
    file.read(storage.get(), length);

    outSize = static_cast<SizeT>(length);
    return storage;
}

bool verbose = false;

template <bool TerminateOnFailure, typename ResulT>
inline void validate(ResulT result, const char *message) {
    if (result == 0) { // assumption 0 is success
        if (verbose) {
            std::cerr << " SUCCESS : " << message << std::endl;
        }
        return;
    }

    std::cerr << (TerminateOnFailure ? "ERROR : " : "WARNING : ") << message << " : " << result << std::endl;
    if (TerminateOnFailure) {
        std::terminate();
    }
}

#define SUCCESS_OR_TERMINATE(CALL) validate<true>(CALL, #CALL)
#define SUCCESS_OR_TERMINATE_BOOL(FLAG) validate<true>(!(FLAG), #FLAG)
#define SUCCESS_OR_WARNING(CALL) validate<false>(CALL, #CALL)
#define SUCCESS_OR_WARNING_BOOL(FLAG) validate<false>(!(FLAG), #FLAG)

void printDeviceProperties(const xe_device_properties_t &props);

int main(int argc, char *argv[]) {
    if ((argc >= 2) && ((0 == strcmp(argv[1], "-v")) || (0 == strcmp(argv[1], "--verbose")))) {
        verbose = true;
    }

    if (verbose) {
        std::cout << "VERBOSE MODE ENABLED" << std::endl;
    }
    // 0. Load the driver
    // Using icd loader linked statically into this executable

    // 1. Set-up
    constexpr size_t allocSize = 4096;
    xe_device_handle_t device0;
    xe_device_properties_t device0Properties = {XE_DEVICE_PROPERTIES_VERSION};
    xe_module_handle_t module;
    xe_function_handle_t function;
    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;
    xe_mem_allocator_handle_t allocator;
    void *srcBuffer = nullptr;
    void *dstBuffer = nullptr;

    SUCCESS_OR_TERMINATE(xeDriverInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDriverGetDevice(0, &device0));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device0, &device0Properties));
    if (verbose) {
        printDeviceProperties(device0Properties);
    } else {
        std::cout << device0Properties.device_name << std::endl;
    }

    {
        uint32_t spirvSize = 0;
        auto spirvModule = readBinaryFile("test_files/spv_modules/cstring_module.spv", spirvSize);
        SUCCESS_OR_TERMINATE_BOOL(spirvSize != 0);

        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION};
        moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
        moduleDesc.pInputModule = spirvModule.get();
        moduleDesc.inputSize = spirvSize;
        SUCCESS_OR_TERMINATE(xeDeviceCreateModule(device0, &moduleDesc, &module, nullptr));
    }

    {
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION};
        functionDesc.pFunctionName = "memcpy_bytes";
        SUCCESS_OR_TERMINATE(xeModuleCreateFunction(module, &functionDesc, &function));
    }

    uint32_t groupSizeX = 32u;
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;
    SUCCESS_OR_TERMINATE(xeFunctionSetGroupSize(function, groupSizeX, groupSizeY, groupSizeZ));

    {
        xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION};
        cmdQueueDesc.ordinal = 0;
        cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
        SUCCESS_OR_TERMINATE(xeDeviceCreateCommandQueue(device0, &cmdQueueDesc, &cmdQueue));
    }

    {
        xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION};
        SUCCESS_OR_TERMINATE(xeDeviceCreateCommandList(device0, &cmdListDesc, &cmdList));
    }

    SUCCESS_OR_TERMINATE(xeCreateMemAllocator(&allocator));
#if SUPPORT_MEM_ALLOC
    SUCCESS_OR_TERMINATE(xeMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &srcBuffer));
    SUCCESS_OR_TERMINATE(xeMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBuffer));
#else
    SUCCESS_OR_TERMINATE(xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &srcBuffer));
    SUCCESS_OR_TERMINATE(xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBuffer));
#endif

    // 2. Encode initialize memory
    uint8_t initDataSrc[allocSize];
    memset(initDataSrc, 7, sizeof(initDataSrc));
    uint8_t initDataDst[allocSize];
    memset(initDataDst, 3, sizeof(initDataDst));
#if SUPPORT_MEMORY_COPY
    SUCCESS_OR_TERMINATE(xeCommandListEncodeMemoryCopy(cmdList, srcBuffer, initDataSrc, sizeof(initDataSrc)));
    SUCCESS_OR_TERMINATE(xeCommandListEncodeMemoryCopy(cmdList, dstBuffer, initDataDst, sizeof(initDataDst)));
    SUCCESS_OR_TERMINATE(xeCommandListEncodeExecutionBarrier(cmdList)); // copying of data must finish before running the user function
#else
    memcpy(srcBuffer, initDataSrc, sizeof(initDataSrc));
    memcpy(dstBuffer, initDataDst, sizeof(initDataDst));
#endif

    // 3. Encode run user function
    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(function, 0, sizeof(dstBuffer), &dstBuffer));
    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(function, 1, sizeof(srcBuffer), &srcBuffer));
    {
        xe_dispatch_function_arguments_t dispatchTraits{XE_DISPATCH_FUNCTION_ARGS_VERSION};
        dispatchTraits.groupCountX = allocSize / groupSizeX;
        dispatchTraits.groupCountY = 1;
        dispatchTraits.groupCountZ = 1;
        SUCCESS_OR_TERMINATE_BOOL(dispatchTraits.groupCountX * groupSizeX == allocSize);
        SUCCESS_OR_TERMINATE(xeCommandListEncodeDispatchFunction(cmdList, function, &dispatchTraits, nullptr));
    }

    // 4. Encode read back memory
    uint8_t readBackData[allocSize];
    memset(readBackData, 2, sizeof(readBackData));
#if SUPPORT_MEMORY_COPY
    SUCCESS_OR_TERMINATE(xeCommandListEncodeExecutionBarrier(cmdList)); // user function must finish before we start copying data
    SUCCESS_OR_TERMINATE(xeCommandListEncodeMemoryCopy(cmdList, readBackData, dstBuffer, sizeof(readBackData)));
#endif

    // 5. Dispatch and wait
    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueEnqueueCommandLists(cmdQueue, 1, &cmdList, nullptr));
    auto synchronizationResult = xeCommandQueueSynchronize(cmdQueue, XE_SYNCHRONIZATION_MODE_POLL, 0, 0, 1000 * 1000 /*1s*/);
    SUCCESS_OR_WARNING(synchronizationResult);

// 6. Validate
#if SUPPORT_MEMORY_COPY
#else
    memcpy(readBackData, dstBuffer, sizeof(readBackData));
#endif
    bool outputValidationSuccessful = (0 == memcmp(initDataSrc, readBackData, sizeof(readBackData)));
    SUCCESS_OR_WARNING_BOOL(outputValidationSuccessful);

    // X. Cleanup
    SUCCESS_OR_TERMINATE(xeMemFree(allocator, dstBuffer));
    SUCCESS_OR_TERMINATE(xeMemFree(allocator, srcBuffer));
    SUCCESS_OR_TERMINATE(xeMemAllocatorDestroy(allocator));

    SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList));

    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue));

    SUCCESS_OR_TERMINATE(xeFunctionDestroy(function));
    SUCCESS_OR_TERMINATE(xeModuleDestroy(module));

    bool aubMode = (XE_RESULT_NOT_READY == synchronizationResult);
    if (aubMode == false) {
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED") << std::endl;
    }
    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}

void printDeviceProperties(const xe_device_properties_t &props) {
    std::cout << "Device : "
              << "\n"
              << " * name : " << props.device_name << "\n"
              << " * vendorId : " << props.vendorId << "\n"
              << " * deviceId : " << props.deviceId << "\n"
              << " * subdeviceId : " << props.subdeviceId << "\n"
              << " * isSubdevice : " << (props.isSubdevice ? "TRUE" : "FALSE") << "\n"
              << " * numSubDevices : " << props.numSubDevices << "\n"
              << " * coreClockRate : " << props.coreClockRate << "\n"
              << " * memClockRate : " << props.memClockRate << "\n"
              << " * memGlobalBusWidth : " << props.memGlobalBusWidth << "\n"
              << " * totalLocalMemSize : " << props.totalLocalMemSize << "\n"
              << " * numAsyncComputeEngines : " << props.numAsyncComputeEngines << "\n"
              << " * numAsyncCopyEngines  : " << props.numAsyncCopyEngines << "\n"
              << " * numComputeCores : " << props.numComputeCores << "\n"
              << " * maxCommandQueuePriority : " << props.maxCommandQueuePriority << std::endl;
}
