#include "xe_all.h"
#include <iostream>
#include <fstream>
#include <memory>

bool verbose = false;

template <bool TerminateOnFailure, typename ResulT>
inline void validate(ResulT result, const char *message) {
    if (result == 0) { // assumption 0 is success
        if (verbose) {
            std::cerr << "SUCCESS : " << message << std::endl;
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

int main(int argc, char *argv[]) {

    size_t allocSize = 4096;
    xe_device_handle_t device0;
    xe_device_properties_t device0Properties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;
    xe_mem_allocator_handle_t allocator;
    void *srcBuffer = nullptr;
    void *dstBuffer = nullptr;

    if (argc >= 2)
        allocSize = atoi(argv[1]);

    if ((argc >= 3) && ((0 == strcmp(argv[2], "-v")) || (0 == strcmp(argv[2], "--verbose"))))
        verbose = true;

    SUCCESS_OR_TERMINATE(xeDriverInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDriverGetDevice(0, &device0));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device0, &device0Properties));
    std::cout << device0Properties.device_name << std::endl;

    xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
    cmdQueueDesc.ordinal = 0;
    cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
    SUCCESS_OR_TERMINATE(xeDeviceCreateCommandQueue(device0, &cmdQueueDesc, &cmdQueue));

    xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeDeviceCreateCommandList(device0, &cmdListDesc, &cmdList));

    /* Allocate and initialize memory */
    SUCCESS_OR_TERMINATE(xeCreateMemAllocator(&allocator));

    SUCCESS_OR_TERMINATE(xeSharedMemAlloc(allocator, device0,
                                          XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT,
                                          allocSize, 1, &srcBuffer));
    SUCCESS_OR_TERMINATE(xeSharedMemAlloc(allocator, device0,
                                          XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT,
                                          allocSize, 1, &dstBuffer));

    unsigned char *srcBufferChar = (unsigned char *)srcBuffer;
    unsigned char *dstBufferChar = (unsigned char *)dstBuffer;
    for (int i = 0; i < allocSize; ++i) {
        srcBufferChar[i] = i + 1;
        dstBufferChar[i] = 0;
    }

    /* Perform the copy and sync */
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, dstBuffer, srcBuffer, allocSize));

    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueExecuteCommandLists(cmdQueue, 1, &cmdList, nullptr));
    auto synchronizationResult = xeCommandQueueSynchronize(cmdQueue, 1000 * 1000 /*1s*/);
    SUCCESS_OR_WARNING(synchronizationResult);

    /* Validate */
    bool outputValidationSuccessful = true;
    for (int i = 0; i < allocSize; ++i) {
        if (verbose)
            std::cout << "srcBuffer[" << i << "] = " << (unsigned int)srcBufferChar[i] << ","
                      << "dstBuffer[" << i << "] = " << (unsigned int)dstBufferChar[i] << "\n";

        outputValidationSuccessful &= (srcBufferChar[i] == dstBufferChar[i]);
    }
    SUCCESS_OR_WARNING_BOOL(outputValidationSuccessful);

    /* Cleanup */
    SUCCESS_OR_TERMINATE(xeMemFree(allocator, dstBuffer));
    SUCCESS_OR_TERMINATE(xeMemFree(allocator, srcBuffer));
    SUCCESS_OR_TERMINATE(xeMemAllocatorDestroy(allocator));

    SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList));

    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue));

    bool aubMode = (XE_RESULT_NOT_READY == synchronizationResult);
    if (aubMode == false)
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED") << std::endl;

    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}
