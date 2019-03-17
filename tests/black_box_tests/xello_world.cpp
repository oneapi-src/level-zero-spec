#include "icd_loader/icd_loader.h"

#include "xe_all.h"

#if defined(__linux__)
#include <dlfcn.h>
#define LOAD_DRIVER_LIBRARY() dlopen("liblevel_zero.so", RTLD_LAZY | RTLD_LOCAL)
#define CLOSE_LIBRARY(LIB) dlclose(LIB)
#define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#include <Windows.h>
#define LOAD_DRIVER_LIBRARY() LoadLibraryA("level_zero.dll")
#define CLOSE_LIBRARY(LIB) FreeLibrary(LIB)
#define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#error "Unsupported OS"
#endif

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
void printVerboseValidationError(const void *expected, const void *tested, size_t len);

int main(int argc, char *argv[]) {
    if ((argc >= 2) && ((0 == strcmp(argv[1], "-v")) || (0 == strcmp(argv[1], "--verbose")))) {
        verbose = true;
    }

    if (verbose) {
        std::cerr << "VERBOSE MODE ENABLED" << std::endl;
    }
    // 0. Load the driver
    auto driverLibrary = LOAD_DRIVER_LIBRARY();
    if (NULL == driverLibrary) {
        std::cerr << "Failed to load driver library\n";
        return 1;
    }
    xe_dispatch_table_t xeApi = {};
    load_xe(
        driverLibrary,
        [](void *library, const char *funcName) -> void * { return LOAD_FUNCTION_PTR(library, funcName); },
        &xeApi);

    // 1. Set-up
    constexpr size_t allocSize = 4096;
    constexpr size_t bytesPerThread = sizeof(char);
    constexpr size_t numThreads = allocSize / bytesPerThread;
    xe_device_handle_t device0;
    xe_device_properties_t device0Properties = {XE_DEVICE_PROPERTIES_VERSION};
    xe_module_handle_t module;
    xe_function_handle_t function;
    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;
    xe_mem_allocator_handle_t allocator;
    void *srcBuffer = nullptr;
    void *dstBuffer = nullptr;

    SUCCESS_OR_TERMINATE(xeApi.xeDriverInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeApi.xeDriverGetDevice(0, &device0));
    SUCCESS_OR_TERMINATE(xeApi.xeDeviceGetProperties(device0, &device0Properties));
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
        SUCCESS_OR_TERMINATE(xeApi.xeDeviceCreateModule(device0, &moduleDesc, &module, nullptr));
    }

    {
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION};
        functionDesc.pFunctionName = "memcpy_bytes";
        SUCCESS_OR_TERMINATE(xeApi.xeModuleCreateFunction(module, &functionDesc, &function));
    }

    uint32_t groupSizeX = 32u;
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;
    SUCCESS_OR_TERMINATE(xeApi.xeFunctionSuggestGroupSize(function, numThreads, 1U, 1U, &groupSizeX, &groupSizeY, &groupSizeZ));
    SUCCESS_OR_TERMINATE_BOOL(numThreads % groupSizeX == 0);
    if (verbose) {
        std::cout << "Group size : (" << groupSizeX << ", " << groupSizeY << ", " << groupSizeZ << ")" << std::endl;
    }
    SUCCESS_OR_TERMINATE(xeApi.xeFunctionSetGroupSize(function, groupSizeX, groupSizeY, groupSizeZ));

    {
        xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION};
        cmdQueueDesc.ordinal = 0;
        cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
        SUCCESS_OR_TERMINATE(xeApi.xeDeviceCreateCommandQueue(device0, &cmdQueueDesc, &cmdQueue));
    }

    {
        xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION};
        SUCCESS_OR_TERMINATE(xeApi.xeDeviceCreateCommandList(device0, &cmdListDesc, &cmdList));
    }

    SUCCESS_OR_TERMINATE(xeApi.xeCreateMemAllocator(&allocator));
#if SUPPORT_MEM_ALLOC
    SUCCESS_OR_TERMINATE(xeApi.xeMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &srcBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBuffer));
#else
    SUCCESS_OR_TERMINATE(xeApi.xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &srcBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBuffer));
#endif

    // 2. Encode initialize memory
    uint8_t initDataSrc[allocSize];
    memset(initDataSrc, 7, sizeof(initDataSrc));
    uint8_t initDataDst[allocSize];
    memset(initDataDst, 3, sizeof(initDataDst));
#if SUPPORT_MEMORY_COPY
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeMemoryCopy(cmdList, srcBuffer, initDataSrc, sizeof(initDataSrc)));
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeMemoryCopy(cmdList, dstBuffer, initDataDst, sizeof(initDataDst)));
#else
    memcpy(srcBuffer, initDataSrc, sizeof(initDataSrc));
    memcpy(dstBuffer, initDataDst, sizeof(initDataDst));
#endif
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeExecutionBarrier(cmdList)); // copying of data must finish before running the user function

    // 3. Encode run user function
    SUCCESS_OR_TERMINATE(xeApi.xeFunctionSetArgumentValue(function, 0, sizeof(dstBuffer), &dstBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeFunctionSetArgumentValue(function, 1, sizeof(srcBuffer), &srcBuffer));
    {
        xe_dispatch_function_arguments_t dispatchTraits{XE_DISPATCH_FUNCTION_ARGS_VERSION};
        dispatchTraits.groupCountX = numThreads / groupSizeX;
        dispatchTraits.groupCountY = 1u;
        dispatchTraits.groupCountZ = 1u;
        if (verbose) {
            std::cerr << "Number of groups : (" << dispatchTraits.groupCountX << ", " << dispatchTraits.groupCountY << ", " << dispatchTraits.groupCountZ << ")" << std::endl;
        }
        SUCCESS_OR_TERMINATE_BOOL(dispatchTraits.groupCountX * groupSizeX == allocSize);
        SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeDispatchFunction(cmdList, function, &dispatchTraits, nullptr));
    }

    // 4. Encode read back memory
    uint8_t readBackData[allocSize];
    memset(readBackData, 2, sizeof(readBackData));
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeExecutionBarrier(cmdList)); // user function must finish before we start copying data
#if SUPPORT_MEMORY_COPY
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeMemoryCopy(cmdList, readBackData, dstBuffer, sizeof(readBackData)));
#endif

    // 5. Dispatch and wait
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeApi.xeCommandQueueEnqueueCommandLists(cmdQueue, 1, &cmdList, nullptr));
    auto synchronizationResult = xeApi.xeCommandQueueSynchronize(cmdQueue, XE_SYNCHRONIZATION_MODE_POLL, 0, 0, 1000 * 1000 /*1s*/);
    SUCCESS_OR_WARNING(synchronizationResult);

// 6. Validate
#if SUPPORT_MEMORY_COPY
#else
    memcpy(readBackData, dstBuffer, sizeof(readBackData));
#endif
    bool outputValidationSuccessful = (0 == memcmp(initDataSrc, readBackData, sizeof(readBackData)));
    if (verbose && (false == outputValidationSuccessful)) {
        printVerboseValidationError(initDataSrc, readBackData, sizeof(readBackData));
    }
    SUCCESS_OR_WARNING_BOOL(outputValidationSuccessful);

    // X. Cleanup
    SUCCESS_OR_TERMINATE(xeApi.xeMemFree(allocator, dstBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeMemFree(allocator, srcBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeMemAllocatorDestroy(allocator));

    SUCCESS_OR_TERMINATE(xeApi.xeCommandListDestroy(cmdList));

    SUCCESS_OR_TERMINATE(xeApi.xeCommandQueueDestroy(cmdQueue));

    SUCCESS_OR_TERMINATE(xeApi.xeFunctionDestroy(function));
    SUCCESS_OR_TERMINATE(xeApi.xeModuleDestroy(module));

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

void printVerboseValidationError(const void *expected, const void *tested, size_t len) {
    size_t offset = 0;

    const uint8_t *expectedU8 = reinterpret_cast<const uint8_t *>(expected);
    const uint8_t *testedU8 = reinterpret_cast<const uint8_t *>(tested);
    uint32_t errorsCount = 0;
    constexpr uint32_t errorsMax = 20;
    while (offset < len) {
        if (expectedU8[offset] != testedU8[offset]) {
            std::cerr << "Data mismatch expectedU8[" << offset << "] != testedU8[" << offset << "]   ->    "
                      << +expectedU8[offset] << " != " << +testedU8[offset] << std::endl;
            ++errorsCount;
            if (errorsCount >= errorsMax) {
                std::cerr << "Found " << errorsCount << " data mismatches - skipping further comparison " << std::endl;
                break;
            }
        }
        ++offset;
    }
}