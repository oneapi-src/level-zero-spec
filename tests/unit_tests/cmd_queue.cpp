#include "cmd_queue_imp.h"
#include "cmd_list_hw.h"
#include "device.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include <cassert>

namespace xe {

xe_result_t CommandQueueImp::enqueueCommandLists(uint32_t numCommandLists,
                                                 xe_command_list_handle_t *phCommandLists,
                                                 xe_fence_handle_t hFence) {
    return XE_RESULT_SUCCESS;
}

xe_result_t CommandQueueImp::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

void CommandQueueImp::initialize() {
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);
    allocation = memoryManager->allocateDeviceMemory();
    assert(allocation);

    commandStream = new OCLRT::LinearStream(allocation->allocationRT);
}

CommandQueue *CommandQueue::create(Device *device) {    
    auto commandQueue = new CommandQueueImp(device);

    commandQueue->initialize();

    return commandQueue;
}

xe_result_t __xecall
xeCommandQueueEnqueueCommandLists(xe_command_queue_handle_t hCommandQueue,
                                  uint32_t numCommandLists,
                                  xe_command_list_handle_t *phCommandLists,
                                  xe_fence_handle_t hFence) {
    return CommandQueue::fromHandle(hCommandQueue)->enqueueCommandLists(numCommandLists, phCommandLists, hFence);
}

} // namespace xe
