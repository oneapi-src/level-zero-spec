#include "cmdqueue_imp.h"
#include "cmdlist_hw.h"
#include "device.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/command_stream/command_stream_receiver.h"
#include <cassert>

namespace L0 {

CommandQueueAllocatorFn commandQueueFactory[IGFX_MAX_PRODUCT] = {};

xe_result_t CommandQueueImp::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

void CommandQueueImp::initialize() {
    assert(globalMemoryManager);
    allocation =
        globalMemoryManager->allocateDeviceMemory(device, defaultQueueCmdBufferSize, 4096u);
    assert(allocation);

    commandStream = new NEO::LinearStream(allocation->allocationRT);
}

Substream CommandQueueImp::getCmdSubstream(size_t size) {
    assert(commandStream);
    if (commandStream->getAvailableSpace() < size) {
        assert(globalMemoryManager);

        // TODO: Add reusable allocations pool instead of deferred deletion
        globalMemoryManager->freeGraphicsAllocation(this->allocation);

        this->allocation =
            globalMemoryManager->allocateDeviceMemory(device, defaultQueueCmdBufferSize, 4096u);
        assert(this->allocation);

        commandStream->replaceGraphicsAllocation(this->allocation->allocationRT);
        commandStream->replaceBuffer(this->allocation->allocationRT->getUnderlyingBuffer(),
                                     this->allocation->allocationRT->getUnderlyingBufferSize());
    }
    return Substream(*commandStream, commandStream->getSpace(size), size);
}

void CommandQueueImp::processCoherency(CommandList *c) {
    auto commandList = static_cast<CommandListImp *>(c);
    auto commandStreamReceiver = static_cast<NEO::CommandStreamReceiver *>(csrRT);
    auto &residencyContainer = commandList->getResidencyContainer();
    for (auto allocation : residencyContainer) {
        this->makeCoherent(*allocation);
    }
}

// FIXME: Remove direct access to taskCount.
// Needed below
struct CommandStreamReceiver : public NEO::CommandStreamReceiver {
    using NEO::CommandStreamReceiver::latestFlushedTaskCount;
    using NEO::CommandStreamReceiver::taskCount;
};

void CommandQueueImp::submitBatchBuffer(size_t offset) {
    auto commandStreamReceiver = static_cast<CommandStreamReceiver *>(csrRT);
    assert(commandStreamReceiver);

    NEO::BatchBuffer batchBuffer(allocation->allocationRT, offset, 0u, nullptr, false, false,
                                 NEO::QueueThrottle::HIGH, commandStream->getUsed(), commandStream);
    NEO::ResidencyContainer residencyContainer;
    if(!this->flush(batchBuffer, residencyContainer)) {
        commandStreamReceiver->flush(batchBuffer, residencyContainer);
        // FIXME: Remove direct access to taskCount.
        this->taskCount = ++commandStreamReceiver->taskCount;
    }
}

xe_result_t CommandQueueImp::synchronize(uint32_t timeout) {
    return synchronizeByPollingForTaskCount(timeout);
}

xe_result_t CommandQueueImp::synchronizeByPollingForTaskCount(uint32_t timeout) {
    auto commandStreamReceiver = static_cast<CommandStreamReceiver *>(csrRT);
    assert(commandStreamReceiver);

    auto taskCountToWait = this->taskCount;
    if (commandStreamReceiver->peekLatestSentTaskCount() < taskCountToWait) {
        dispatchTaskCountWrite(true);
    }

    bool enableTimeout = (timeout != std::numeric_limits<uint32_t>::max());
    commandStreamReceiver->waitForCompletionWithTimeout(enableTimeout, timeout, this->taskCount);

    if (*commandStreamReceiver->getTagAddress() < taskCountToWait) {
        return XE_RESULT_NOT_READY;
    }

    printFunctionsPrintfOutput();

    return XE_RESULT_SUCCESS;
}

void CommandQueueImp::printFunctionsPrintfOutput() {
    size_t size = this->printfFunctionContainer.size();
    if (size) {
        for (size_t i = 0; i < size; i++) {
            this->printfFunctionContainer[i]->printPrintfOutput();
        }
        this->printfFunctionContainer.clear();
    }
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

xe_result_t fenceCreate(xe_command_queue_handle_t hCommandQueue, const xe_fence_desc_t *desc,
                        xe_fence_handle_t *phFence) {
    auto commandQueue = static_cast<CommandQueueImp *>(CommandQueue::fromHandle(hCommandQueue));
    return commandQueue->createFence(desc, phFence);
}

} // namespace L0
