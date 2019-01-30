#pragma once
#include "cmd_queue.h"
#include "xe_common.h"

namespace xe {

struct CommandQueueImp : public CommandQueue {
    CommandQueueImp(void *commandQueueRT)
        : commandQueueRT(commandQueueRT) {
    }

    xe_result_t enqueueCommandLists(uint32_t numCommandLists,
                                    xe_command_list_handle_t *phCommandLists,
                                    xe_fence_handle_t hFence) override {
        return XE_RESULT_SUCCESS;
    }

    void *commandQueueRT;
};

CommandQueue *CommandQueue::create(void *commandQueueRT) {
    return new CommandQueueImp(commandQueueRT);
}

xe_result_t __xecall
xeCommandQueueEnqueueCommandLists(
    xe_command_queue_handle_t hCommandQueue,
    uint32_t numCommandLists,
    xe_command_list_handle_t *phCommandLists,
    xe_fence_handle_t hFence) {
    return CommandQueue::fromHandle(hCommandQueue)->enqueueCommandLists(numCommandLists, phCommandLists, hFence);
}

} // namespace xe
