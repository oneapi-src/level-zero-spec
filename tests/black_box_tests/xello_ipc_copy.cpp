#include "xello_worlds.h"

#include "xe_api.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <memory>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>

extern bool verbose;
bool verbose = false;

// Temporary: needed for for sizeof()
struct _xe_ipc_mem_handle_t {
    size_t alignment;
    size_t size;
    char shmFileName[255];
};

void run_client(int comm_socket) {

    xe_device_handle_t device;
    xe_device_properties_t deviceProperties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDeviceGet(0, &device));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device, &deviceProperties));
    std::cout << "Client process: " << deviceProperties.name << "\n";

    const size_t allocSize = 4096 + 7; // +7 to brake alignment and make it harder
    char *heapBuffer = new char[allocSize];
    void *xeIpcBuffer;

    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;

    xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
    cmdQueueDesc.ordinal = 0;
    cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
    SUCCESS_OR_TERMINATE(xeCommandQueueCreate(device, &cmdQueueDesc, &cmdQueue));

    xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeCommandListCreate(device, &cmdListDesc, &cmdList));

    for (size_t i = 0; i < allocSize; ++i) {
        heapBuffer[i] = static_cast<char>(i + 1);
    }

    xe_ipc_mem_handle_t pIpcHandle = static_cast<xe_ipc_mem_handle_t>(malloc(sizeof(*pIpcHandle)));

    sleep(1); // give time to the server to write
    if (read(comm_socket, pIpcHandle, sizeof(*pIpcHandle)) < 0) {
        perror("Clent: reading stream message");
        assert(0);
    }

    SUCCESS_OR_TERMINATE(
        xeIpcOpenMemHandle(device, pIpcHandle, XE_IPC_MEMORY_FLAG_NONE, &xeIpcBuffer));
    // Copy from heap to device-allocated shared buffer memory
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, xeIpcBuffer, heapBuffer, allocSize,
                                                       nullptr, 0, nullptr));

    SUCCESS_OR_TERMINATE(xeCommandListAppendBarrier(cmdList, nullptr, 0, nullptr));

    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueExecuteCommandLists(cmdQueue, 1, &cmdList, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandQueueSynchronize(cmdQueue, std::numeric_limits<uint32_t>::max()));

    SUCCESS_OR_TERMINATE(xeIpcCloseMemHandle(xeIpcBuffer));
    SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue));
    delete[] heapBuffer;
    free(pIpcHandle);
}

void run_server(int comm_socket, bool &validRet) {

    xe_device_handle_t device;
    xe_device_properties_t deviceProperties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDeviceGet(0, &device));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device, &deviceProperties));
    std::cout << "Server process: " << deviceProperties.name << "\n";

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

    SUCCESS_OR_TERMINATE(xeDeviceMemAlloc(device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize,
                                          allocSize, &xeBuffer));

    xe_ipc_mem_handle_t pIpcHandle;
    SUCCESS_OR_TERMINATE(xeIpcGetMemHandle(xeBuffer, &pIpcHandle));

    if (write(comm_socket, pIpcHandle, sizeof(*pIpcHandle)) < 0) {
        perror("server: writing on stream socket");
        assert(0);
    }

    memset(stackBuffer, 0, allocSize);
    for (size_t i = 0; i < allocSize; ++i) {
        heapBuffer[i] = static_cast<char>(i + 1);
    }

    sleep(2); // give time to client to copy to the xeBuffer
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
    int child;
    int sv[2];

    verbose = isVerbose(argc, argv);

    bool outputValidationSuccessful;

    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sv) < 0) {
        perror("socketpair");
        exit(1);
    }

    child = fork();
    if (child < 0) {
        perror("fork");
        exit(1);
    } else if (0 == child) {
        close(sv[0]);
        run_client(sv[1]);
        close(sv[1]);
        exit(0);
    } else {
        close(sv[1]);
        run_server(sv[0], outputValidationSuccessful);
        close(sv[0]);
    }

    bool aubMode = isAubMode(argc, argv);
    if (aubMode == false)
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED")
                  << std::endl;

    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}
