#pragma once
#include "xe_common.h"

struct _xe_command_queue_handle_t {
};

namespace xe {

struct CommandQueue : public _xe_command_queue_handle_t {
    virtual xe_result_t enqueueCommandLists(uint32_t numCommandLists,
                                            xe_command_list_handle_t *phCommandLists,
                                            xe_fence_handle_t hFence) = 0;

    static CommandQueue *create(void *);

    static CommandQueue *fromHandle(xe_command_queue_handle_t handle) {
        return static_cast<CommandQueue *>(handle);
    }

    inline xe_command_queue_handle_t toHandle() {
        return this;
    }
};

xe_result_t __xecall
xeCommandQueueEnqueueCommandLists(
    xe_command_queue_handle_t hCommandQueue,
    uint32_t numCommandLists,
    xe_command_list_handle_t *phCommandLists,
    xe_fence_handle_t hFence);

} // namespace xe
