#include "xello_worlds.h"

#define ENABLE_OCLOC_WRAPPER
#include "core/source/ocloc_shared.h"

#include "xe_all.h"

#include <iostream>
#include <fstream>
#include <memory>

extern bool verbose;
bool verbose = false;

const char *clProgram = R"==(
__kernel void increment_by_one(__global uchar *dst, __global uchar *src) {
    unsigned int gid = get_global_id(0);
    dst[gid] = (uchar)(src[gid] + 1);
}
)==";

int main(int argc, char *argv[]) {
    verbose = isVerbose(argc, argv);

    // Prepare spirV
    auto spirVCompilerOutput = ocloc::OclocWrapper::compileCl12ToSpirV(clProgram);
    if (spirVCompilerOutput.getBuildLogSize() > 0) {
        std::cerr << "CL->spirV comilation log : " << spirVCompilerOutput.getBuildLog() << std::endl;
    }

    SUCCESS_OR_TERMINATE_BOOL(spirVCompilerOutput.success());

    // Set-up
    constexpr size_t allocSize = 4096;
    constexpr size_t bytesPerThread = sizeof(char);
    constexpr size_t numThreads = allocSize / bytesPerThread;
    std::vector <xe_module_handle_t> module;
    std::vector<xe_device_handle_t> device;
    std::vector <xe_function_handle_t> function;
    std::vector <xe_command_queue_handle_t> cmdQueue;
    std::vector <xe_command_list_handle_t> cmdList;
    void *srcBuffer;
    void *dstBuffer;
    uint32_t deviceCount;
    bool outputValidationSuccessful;

    SUCCESS_OR_TERMINATE(xeDriverInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDriverGetDeviceCount(&deviceCount));

    // Resize arrays based on returned device count
    device.resize(deviceCount);

    // Get Device and command queue
    for (uint32_t i = 0; i < deviceCount; i++) {
        xe_device_properties_t deviceProperties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
        SUCCESS_OR_TERMINATE(xeDriverGetDevice(i, &device[i]));

        SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device[i], &deviceProperties));

        printDeviceProperties(deviceProperties);
    }

    module.resize(deviceCount);
    cmdQueue.resize(deviceCount);
    cmdList.resize(deviceCount);
    function.resize(deviceCount);


    // Command Queues
    for (uint32_t i = 0; i < deviceCount; i++) {
        xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
        cmdQueueDesc.ordinal = 0;
        cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
        SUCCESS_OR_TERMINATE(xeDeviceCreateCommandQueue(device[i],
                             &cmdQueueDesc, &cmdQueue[i]));
    }

    // Create Module
    uint32_t spirvSize = spirVCompilerOutput.getOutputSize();
    auto spirvModule = spirVCompilerOutput.getOutput();
    SUCCESS_OR_TERMINATE_BOOL(spirvSize != 0);

    xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
    moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
    moduleDesc.pInputModule = reinterpret_cast<const uint8_t *>(spirvModule);
    moduleDesc.inputSize = spirvSize;
    for (uint32_t i = 0; i < deviceCount; i++) {
        SUCCESS_OR_TERMINATE(xeDeviceCreateModule(device[i], &moduleDesc,
                             &module[i], nullptr));
    }

    // ITERATE OVER DEVICES and CREATE FUNCTIONS, Group Size and Launch the
    // function
    for (uint32_t i = 0; i < deviceCount; i++) {

        // Command Lists
        xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
        SUCCESS_OR_TERMINATE(xeDeviceCreateCommandList(device[i], &cmdListDesc,
                             &cmdList[i]));

        // Create Function
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
        functionDesc.pFunctionName = "increment_by_one";
        SUCCESS_OR_TERMINATE(xeModuleCreateFunction(module[i],
                             &functionDesc, &function[i]));
        uint32_t groupSizeX = 32u;
        uint32_t groupSizeY = 1u;
        uint32_t groupSizeZ = 1u;
        SUCCESS_OR_TERMINATE(xeFunctionSuggestGroupSize(function[i], numThreads, 1U, 1U, &groupSizeX, &groupSizeY, &groupSizeZ));
        SUCCESS_OR_TERMINATE_BOOL(numThreads % groupSizeX == 0);
        if (verbose) {
            std::cout << "Group size : (" << groupSizeX << ", " << groupSizeY << ", " << groupSizeZ << ")" << std::endl;
        }
        SUCCESS_OR_TERMINATE(xeFunctionSetGroupSize(function[i], groupSizeX, groupSizeY, groupSizeZ));

        // Alloc buffers
        srcBuffer = nullptr;
        dstBuffer = nullptr;
        SUCCESS_OR_TERMINATE(xeSharedMemAlloc(device[i], XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &srcBuffer));
        SUCCESS_OR_TERMINATE(xeSharedMemAlloc(device[i], XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBuffer));

        // Init data and copy to device
        uint8_t initDataSrc[allocSize];
        memset(initDataSrc, 7, sizeof(initDataSrc));
        uint8_t initDataDst[allocSize];
        memset(initDataDst, 3, sizeof(initDataDst));
        SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList[i], srcBuffer, initDataSrc, sizeof(initDataSrc), nullptr));
        SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList[i], dstBuffer, initDataDst, sizeof(initDataDst), nullptr));

        SUCCESS_OR_TERMINATE(xeCommandListAppendExecutionBarrier(cmdList[i])); // copying of data must finish before running the user function

        // Set function args and get ready to dispatch
        SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(function[i], 0, sizeof(dstBuffer), &dstBuffer));
        SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(function[i], 1, sizeof(srcBuffer), &srcBuffer));
        {
            xe_thread_group_dimensions_t dispatchTraits;
            dispatchTraits.groupCountX = numThreads / groupSizeX;
            dispatchTraits.groupCountY = 1u;
            dispatchTraits.groupCountZ = 1u;
            if (verbose) {
                std::cerr << "Number of groups : (" << dispatchTraits.groupCountX << ", " << dispatchTraits.groupCountY << ", " << dispatchTraits.groupCountZ << ")" << std::endl;
            }
            SUCCESS_OR_TERMINATE_BOOL(dispatchTraits.groupCountX * groupSizeX == allocSize);
            SUCCESS_OR_TERMINATE(xeCommandListAppendLaunchFunction(cmdList[i],
                                 function[i], &dispatchTraits, nullptr));
        }

        // Barrier to complete function
        uint8_t readBackData[allocSize];
        memset(readBackData, 2, sizeof(readBackData));
        SUCCESS_OR_TERMINATE(xeCommandListAppendExecutionBarrier(cmdList[i]));
        SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList[i], readBackData, dstBuffer, sizeof(readBackData), nullptr));

        // Dispatch and wait
        SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList[i]));
        SUCCESS_OR_TERMINATE(xeCommandQueueExecuteCommandLists(cmdQueue[i], 1, &cmdList[i], nullptr));
        auto synchronizationResult = xeCommandQueueSynchronize(cmdQueue[i], 1000 * 1000 /*1s*/);
        SUCCESS_OR_WARNING(synchronizationResult);


        // Validate
        outputValidationSuccessful = true;
        for (size_t i = 0; i < allocSize; ++i) {
            outputValidationSuccessful &= ((unsigned char)(initDataSrc[i] + 1) == (unsigned char)readBackData[i]);
        }

        // Release Mem
        SUCCESS_OR_TERMINATE(xeMemFree(dstBuffer));
        SUCCESS_OR_TERMINATE(xeMemFree(srcBuffer));

        SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList[i]));

        // Break immediately if output validation is false
        if(!outputValidationSuccessful) {
            break;
        }
    }

    for (uint32_t i = 0; i < deviceCount; i++) {
        SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue[i]));
        SUCCESS_OR_TERMINATE(xeFunctionDestroy(function[i]));
        SUCCESS_OR_TERMINATE(xeModuleDestroy(module[i]));
    }

    bool aubMode = isAubMode(argc, argv);
    if (aubMode == false) {
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED") << std::endl;
    }
    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}
