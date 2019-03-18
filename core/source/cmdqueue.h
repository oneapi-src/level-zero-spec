#pragma once
#include "xe_common.h"
#include "xe_fence.h"
#include "device.h"

struct _xe_command_queue_handle_t {
};

namespace L0 {

struct CommandQueue : public _xe_command_queue_handle_t {
    template <typename Type>
    struct Allocator {
        static CommandQueue *allocate(Device *device, void *csrRT) {
            return new Type(device, csrRT);
        }
    };

    virtual xe_result_t createFence(const xe_fence_desc_t *desc,
                                    xe_fence_handle_t *phFence) = 0;
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t executeCommandLists(uint32_t numCommandLists,
                                            xe_command_list_handle_t *phCommandLists,
                                            xe_fence_handle_t hFence) = 0;
    virtual xe_result_t synchronize(uint32_t timeout) = 0;

    static CommandQueue *create(uint32_t productFamily, Device *device, void *csrRT);

    static CommandQueue *fromHandle(xe_command_queue_handle_t handle) {
        return static_cast<CommandQueue *>(handle);
    }

    inline xe_command_queue_handle_t toHandle() {
        return this;
    }
};

using CommandQueueAllocatorFn = CommandQueue *(*)(Device *device, void *csrRT);
extern CommandQueueAllocatorFn commandQueueFactory[];

template <uint32_t productFamily, typename CommandQueueType>
struct CommandQueuePopulateFactory {
    CommandQueuePopulateFactory() {
        commandQueueFactory[productFamily] = CommandQueue::Allocator<CommandQueueType>::allocate;
    }
};

xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
    xe_command_queue_handle_t hCommandQueue,
    uint32_t numCommandLists,
    xe_command_list_handle_t *phCommandLists,
    xe_fence_handle_t hFence);

xe_result_t __xecall
xeCommandQueueSynchronize(xe_command_queue_handle_t hCommandQueue,
                          uint32_t timeout);

} // namespace L0
