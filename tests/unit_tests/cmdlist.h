#pragma once
#include "xe_cmdlist.h"
#include "xe_module.h"

struct _xe_command_list_handle_t {
};

namespace xe {

struct Device;
struct GraphicsAllocation;

struct CommandList : public _xe_command_list_handle_t {
    template <typename Type>
    struct Allocator {
        static CommandList *allocate(Device *device) {
            return new Type(device);
        }
    };

    virtual xe_result_t close() = 0;
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t encodeDispatchFunction(xe_function_handle_t hFunction,
                                               xe_function_args_handle_t hFunctionArgs,
                                               xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                               xe_event_handle_t hEvent) = 0;

    virtual xe_result_t encodeSignalEvent(xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeWaitOnEvent(xe_event_handle_t hEvent) = 0;

    static CommandList *create(uint32_t productFamily, Device *device);

    static CommandList *fromHandle(xe_command_list_handle_t handle) {
        return static_cast<CommandList *>(handle);
    }

    inline xe_command_list_handle_t toHandle() {
        return this;
    }

    GraphicsAllocation &getAllocation() {
        return *allocation;
    }

  protected:
    virtual ~CommandList() = default;

    GraphicsAllocation *allocation = nullptr;
    GraphicsAllocation *allocationIndirectHeaps[5];
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
xeCommandListEncodeDispatchFunction(
    xe_command_list_handle_t hCommandList,               ///< [in] handle of the command list
    xe_function_handle_t hFunction,                      ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,             ///< [in] handle to function arguments buffer.
    xe_dispatch_function_arguments_t *pDispatchFuncArgs, ///< [in] dispatch function arguments.
    xe_event_handle_t hEvent                             ///< [in][optional] handle of the event to signal on completion
);

xe_result_t __xecall
xeCommandListEncodeSignalEvent(
    xe_command_list_handle_t hCommandList, ///< [in] handle of the command list
    xe_event_handle_t hEvent               ///< [in] handle of the event
);

xe_result_t __xecall
xeCommandListEncodeWaitOnEvent(
    xe_command_list_handle_t hCommandList, ///< [in] handle of the command list
    xe_event_handle_t hEvent               ///< [in] handle of the event
);
} // namespace xe
