#pragma once
#include "xe_common.h"

struct _xe_command_queue_handle_t {
};

namespace xe {
struct Device;

struct CommandQueue : public _xe_command_queue_handle_t {
    template <typename Type>
    struct Allocator {
        static CommandQueue *allocate(Device *device) {
            return new Type(device);
        }
    };

    virtual xe_result_t destroy() = 0;
    virtual xe_result_t enqueueCommandLists(uint32_t numCommandLists,
                                            xe_command_list_handle_t *phCommandLists,
                                            xe_fence_handle_t hFence) = 0;

    static CommandQueue *create(uint32_t productFamily, Device *device);

    static CommandQueue *fromHandle(xe_command_queue_handle_t handle) {
        return static_cast<CommandQueue *>(handle);
    }

    inline xe_command_queue_handle_t toHandle() {
        return this;
    }
};

using CommandQueueAllocatorFn = CommandQueue *(*)(Device *);
extern CommandQueueAllocatorFn commandQueueFactory[];

template <uint32_t productFamily, typename CommandQueueType>
struct CommandQueuePopulateFactory {
    CommandQueuePopulateFactory() {
        commandQueueFactory[productFamily] = CommandQueue::Allocator<CommandQueueType>::allocate;
    }
};

xe_result_t __xecall
xeCommandQueueEnqueueCommandLists(
    xe_command_queue_handle_t hCommandQueue,
    uint32_t numCommandLists,
    xe_command_list_handle_t *phCommandLists,
    xe_fence_handle_t hFence);

} // namespace xe
