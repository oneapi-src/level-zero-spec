#include "xello_worlds.h"

#include "xe_all.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <memory>

extern bool verbose;
bool verbose = false;

void testAppendMemoryCopy(xe_device_handle_t &device, bool &validRet) {
    const size_t allocSize = 4096 + 7; // +7 to brake alignment and make it harder
    char *heapBuffer = new char[allocSize];
    void *xeBuffer = nullptr;
    char stackBuffer[allocSize];

    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;

    xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
    cmdQueueDesc.ordinal = 0;
    cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
    SUCCESS_OR_TERMINATE(xeCommandQueueCreate(device, &cmdQueueDesc, &cmdQueue));

    xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeCommandListCreate(device, &cmdListDesc, &cmdList));

    SUCCESS_OR_TERMINATE(
        xeMemAlloc(device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize, allocSize, &xeBuffer));

    for (size_t i = 0; i < allocSize; ++i) {
        heapBuffer[i] = static_cast<char>(i + 1);
    }
    memset(stackBuffer, 0, allocSize);

    // Copy from heap to device-allocated memory
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, xeBuffer, heapBuffer, allocSize,
                                                       nullptr, 0, nullptr));

    SUCCESS_OR_TERMINATE(xeCommandListAppendBarrier(cmdList, nullptr, 0, nullptr));

    // Copy from device-allocated memory to stack
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, stackBuffer, xeBuffer, allocSize,
                                                       nullptr, 0, nullptr));

    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueExecuteCommandLists(cmdQueue, 1, &cmdList, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandQueueSynchronize(cmdQueue, std::numeric_limits<uint32_t>::max()));

    // Validate stack and xe buffers have the original data from heapBuffer
    validRet = (0 == memcmp(heapBuffer, stackBuffer, allocSize));

    delete[] heapBuffer;
    SUCCESS_OR_TERMINATE(xeMemFree(xeBuffer));
    SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue));
}

int main(int argc, char *argv[]) {
    xe_device_handle_t device0;
    xe_device_properties_t device0Properties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};

    verbose = isVerbose(argc, argv);

    SUCCESS_OR_TERMINATE(xeInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDeviceGet(0, &device0));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device0, &device0Properties));
    std::cout << device0Properties.name << std::endl;

    bool outputValidationSuccessful;
    testAppendMemoryCopy(device0, outputValidationSuccessful);

    bool aubMode = isAubMode(argc, argv);
    if (aubMode == false)
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED")
                  << std::endl;

    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}
