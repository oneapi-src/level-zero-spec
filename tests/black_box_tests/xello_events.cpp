#include "xello_worlds.h"

#define ENABLE_OCLOC_WRAPPER
#include "source/core/ocloc_shared.h"

#include "xe_api.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

extern bool verbose;
bool verbose = false;

const char *clProgram = R"==(
__kernel void increment_by_one(__global uchar *dst, __global uchar *src) {
    unsigned int gid = get_global_id(0);
    dst[gid] = (uchar)(src[gid] + 1);
}
)==";

void createModule(xe_module_handle_t &module, xe_device_handle_t &device) {
    // Prepare spirV
    auto spirVCompilerOutput = ocloc::OclocWrapper::compileCl12ToSpirV(clProgram);
    if (spirVCompilerOutput.getBuildLogSize() > 0) {
        std::cerr << "CL->spirV comilation log : " << spirVCompilerOutput.getBuildLog()
                  << std::endl;
    }
    SUCCESS_OR_TERMINATE_BOOL(spirVCompilerOutput.success());
    uint32_t spirvSize = spirVCompilerOutput.getOutputSize();
    auto spirvModule = spirVCompilerOutput.getOutput();
    SUCCESS_OR_TERMINATE_BOOL(spirvSize != 0);

    xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
    moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
    moduleDesc.pInputModule = reinterpret_cast<const uint8_t *>(spirvModule);
    moduleDesc.inputSize = spirvSize;
    SUCCESS_OR_TERMINATE(xeModuleCreate(device, &moduleDesc, &module, nullptr));
}

void createFunction(xe_module_handle_t &module, xe_function_handle_t &function,
                    size_t numThreads, uint32_t sizex, uint32_t sizey,
                    uint32_t sizez) {
    xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
    functionDesc.pFunctionName = "increment_by_one";
    SUCCESS_OR_TERMINATE(xeFunctionCreate(module, &functionDesc, &function));

    // Set group sizes
    uint32_t groupSizeX = sizex;
    uint32_t groupSizeY = sizey;
    uint32_t groupSizeZ = sizez;
    SUCCESS_OR_TERMINATE(xeFunctionSuggestGroupSize(function, numThreads, 1U, 1U, &groupSizeX,
                                                    &groupSizeY, &groupSizeZ));
    SUCCESS_OR_TERMINATE_BOOL(numThreads % groupSizeX == 0);
    if (verbose) {
        std::cout << "Group size : (" << groupSizeX << ", " << groupSizeY << ", " << groupSizeZ
                  << ")" << std::endl;
    }
    SUCCESS_OR_TERMINATE(xeFunctionSetGroupSize(function, groupSizeX, groupSizeY, groupSizeZ));
}

void createCmdQueueAndCmdList(xe_device_handle_t &device,
                              xe_command_queue_handle_t &cmdqueue,
                              xe_command_list_handle_t &cmdList) {
    xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
    cmdQueueDesc.ordinal = 0;
    cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
    SUCCESS_OR_TERMINATE(xeCommandQueueCreate(device, &cmdQueueDesc, &cmdqueue));

    xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeCommandListCreate(device, &cmdListDesc, &cmdList));
}

bool testEvents(xe_device_handle_t &device) {
    constexpr size_t allocSize = 4096;
    constexpr size_t bytesPerThread = sizeof(char);
    constexpr size_t numThreads = allocSize / bytesPerThread;
    xe_module_handle_t module;
    xe_function_handle_t function;
    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;

    void *srcBuffer;
    void *dstBuffer;
    uint32_t groupSizeX = 32u;
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;

    xe_event_pool_desc_t event_pool_desc;
    xe_event_desc_t event_desc;
    event_pool_desc.count = 1;
    event_pool_desc.flags = XE_EVENT_POOL_FLAG_HOST_VISIBLE;
    event_pool_desc.version = XE_EVENT_POOL_DESC_VERSION_CURRENT;
    event_desc.index = 0;
    event_desc.signal = XE_EVENT_SCOPE_FLAG_NONE;
    event_desc.wait = XE_EVENT_SCOPE_FLAG_NONE;
    event_desc.version = XE_EVENT_DESC_VERSION_CURRENT;
    xe_event_pool_handle_t kernel_launch_event_pool;
    xe_event_handle_t kernel_launch_event;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Create commandQueue and cmdList
    createCmdQueueAndCmdList(device, cmdQueue, cmdList);

    // Create module and function
    createModule(module, device);
    createFunction(module, function, numThreads, groupSizeX, groupSizeY,
                   groupSizeZ);

    // Alloc buffers
    srcBuffer = nullptr;
    dstBuffer = nullptr;
    SUCCESS_OR_TERMINATE(xeDeviceMemAlloc(device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                                          allocSize, 1,
                                          &srcBuffer));
    SUCCESS_OR_TERMINATE(xeDeviceMemAlloc(device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                                          allocSize, 1,
                                          &dstBuffer));

    // Init data and copy to device
    uint8_t initDataSrc[allocSize];
    memset(initDataSrc, 7, sizeof(initDataSrc));
    uint8_t initDataDst[allocSize];
    memset(initDataDst, 3, sizeof(initDataDst));
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(
        cmdList, srcBuffer, initDataSrc, sizeof(initDataSrc), nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(
        cmdList, dstBuffer, initDataDst, sizeof(initDataDst), nullptr, 0, nullptr));

    SUCCESS_OR_TERMINATE(xeCommandListAppendBarrier(
        cmdList, nullptr, 0,
        nullptr)); // copying of data must finish before running the user function

    // Set function args and get ready to dispatch
    SUCCESS_OR_TERMINATE(
        xeFunctionSetArgumentValue(function, 0, sizeof(dstBuffer), &dstBuffer));
    SUCCESS_OR_TERMINATE(
        xeFunctionSetArgumentValue(function, 1, sizeof(srcBuffer), &srcBuffer));
    xe_thread_group_dimensions_t dispatchTraits;
    dispatchTraits.groupCountX = numThreads / groupSizeX;
    dispatchTraits.groupCountY = 1u;
    dispatchTraits.groupCountZ = 1u;
    if (verbose) {
        std::cerr << "Number of groups : (" << dispatchTraits.groupCountX << ", "
                  << dispatchTraits.groupCountY << ", " << dispatchTraits.groupCountZ << ")"
                  << std::endl;
    }

    SUCCESS_OR_TERMINATE_BOOL(dispatchTraits.groupCountX * groupSizeX == allocSize);
    SUCCESS_OR_TERMINATE(xeCommandListAppendLaunchFunction(
        cmdList, function, &dispatchTraits, nullptr, 0, nullptr));

    // Create Event Pool and kernel launch event
    result = xeEventPoolCreate(device, &event_pool_desc,
                         &kernel_launch_event_pool);
    if (result) {
        if (verbose) {
            std::cerr << "Event Pool create failed." << std::endl;
        }
        return false;
    }
    result = xeEventCreate(kernel_launch_event_pool, &event_desc,
                         &kernel_launch_event);
    if (result) {
        if (verbose) {
            std::cerr << "Event create failed." << std::endl;
        }
        return false;
    }

    if (verbose) {
        std::cerr << "Event Pool and Event created." << std::endl;
    }

    // Append a signal event into cmdList and execute
    SUCCESS_OR_TERMINATE(xeCommandListAppendSignalEvent(cmdList,
                         kernel_launch_event));
    if (verbose) {
        std::cerr << "Completed xeCommandListAppendSignalEvent." << std::endl;
    }
    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));

    if (verbose) {
        std::cerr << "Executing CommandList." << std::endl;
    }
    result = xeCommandQueueExecuteCommandLists(cmdQueue, 1,
                         &cmdList, nullptr);
    if (result) {
        if (verbose) {
            std::cerr << "CommandList execution failed." << std::endl;
        }
        return false;
    }

    if (verbose) {
        std::cerr << "Completed xeCommandQueueExecuteCommandLists." << std::endl;
    }
    SUCCESS_OR_TERMINATE(xeEventHostSynchronize(kernel_launch_event,
                         2000));
    if (verbose) {
        std::cerr << "Completed xeEventHostSynchronize." << std::endl;
    }

    SUCCESS_OR_TERMINATE(xeCommandQueueSynchronize(cmdQueue,
                         UINT32_MAX));
    if (verbose) {
        std::cerr << "Completed xeCommandQueueSynchronize." << std::endl;
    }

    SUCCESS_OR_TERMINATE(xeEventReset(kernel_launch_event));

    //Tear down
    xeCommandListReset(cmdList);

    SUCCESS_OR_TERMINATE(xeMemFree(dstBuffer));
    SUCCESS_OR_TERMINATE(xeMemFree(srcBuffer));

    SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList));

    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue));

    SUCCESS_OR_TERMINATE(xeFunctionDestroy(function));
    SUCCESS_OR_TERMINATE(xeModuleDestroy(module));

    return true;
}

int main(int argc, char *argv[]) {
    xe_device_handle_t device0;
    bool outputValidationSuccessful;
    xe_device_properties_t device0Properties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};

    verbose = isVerbose(argc, argv);

    SUCCESS_OR_TERMINATE(xeInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDeviceGet(0, &device0));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device0, &device0Properties));
    std::cout << device0Properties.name << std::endl;

    outputValidationSuccessful = testEvents(device0);

    bool aubMode = isAubMode(argc, argv);
    if (aubMode == false)
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED")
                  << std::endl;

    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}
