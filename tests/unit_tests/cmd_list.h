#pragma once
#include "xe_cmdlist.h"

namespace xe {

struct Device;

struct CommandList {
    template <typename Type>
    struct Allocator {
        static CommandList *allocate(Device *device) {
            return new Type(device);
        }
    };

    virtual xe_result_t close() = 0;
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t encodeWaitOnEvent(xe_event_handle_t hEvent) = 0;

    static CommandList *create(uint32_t productFamily, Device *device);

    static CommandList *fromHandle(xe_command_list_handle_t handle) {
        return static_cast<CommandList *>(handle.pDriverData);
    }

    inline xe_command_list_handle_t toHandle() const {
        xe_command_list_handle_t handle;
        handle.pDriverData = const_cast<CommandList *>(this);
        return handle;
    }

  protected:
    virtual ~CommandList() = default;
};

using CommandListAllocatorFn = CommandList *(*)(Device *);
extern CommandListAllocatorFn commandListFactory[];

template <uint32_t productFamily, typename CommandListType>
struct CommandListPopulateFactory {
    CommandListPopulateFactory() {
        commandListFactory[productFamily] = CommandList::Allocator<CommandListType>::allocate;
    }
};

xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList ///< [in] handle of command list object to close
);

xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList ///< [in] handle of command list object to destroy
);

xe_result_t __xecall
xeCommandListEncodeWaitOnEvent(
    xe_command_list_handle_t hCommandList, ///< [in] handle of the command list
    xe_event_handle_t hEvent               ///< [in] handle of the event
);
} // namespace xe
