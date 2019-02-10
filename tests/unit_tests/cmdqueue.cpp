#include "cmdqueue_imp.h"
#include "cmdlist_hw.h"
#include "device.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/command_stream/command_stream_receiver.h"
#include <cassert>

namespace xe {

CommandQueueAllocatorFn commandQueueFactory[IGFX_MAX_PRODUCT] = {};

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

void CommandQueueImp::processResidency(CommandList *c) {
    auto commandList = static_cast<CommandListImp *>(c);
    auto commandStreamReceiver = static_cast<OCLRT::CommandStreamReceiver *>(csrRT);
    auto &residencyContainer = commandList->getResidencyContainer();
    commandStreamReceiver->processResidency(residencyContainer);
}

void CommandQueueImp::submitBatchBuffer() {
    auto commandStreamReceiver = static_cast<OCLRT::CommandStreamReceiver *>(csrRT);
    assert(commandStreamReceiver);

    OCLRT::BatchBuffer batchBuffer(
        allocation->allocationRT,
        0u,
        0u,
        nullptr,
        false,
        false,
        OCLRT::QueueThrottle::HIGH,
        commandStream->getUsed(),
        commandStream);
    OCLRT::ResidencyContainer residencyContainer;
    commandStreamReceiver->flush(batchBuffer, residencyContainer);
}

CommandQueue *CommandQueue::create(uint32_t productFamily, Device *device, void *csrRT) {
    CommandQueueAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = commandQueueFactory[productFamily];
    }

    CommandQueueImp *commandQueue = nullptr;
    if (allocator) {
        commandQueue = static_cast<CommandQueueImp *>((*allocator)(device, csrRT));

        commandQueue->initialize();
    }
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
