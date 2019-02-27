#pragma once
#include "xe_common.h"
#include "device.h"

struct _xe_command_graph_handle_t {
};

namespace L0 {

struct CommandGraph : public _xe_command_graph_handle_t {

    virtual xe_result_t close() = 0;
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t encodeDispatchFunction(xe_function_handle_t hFunction,
                                               xe_function_args_handle_t hFunctionArgs,
                                               const xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                               xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeDispatchFunctionIndirect(xe_function_handle_t hFunction,
                                                       xe_function_args_handle_t hFunctionArgs,
                                                       const xe_dispatch_function_indirect_arguments_t *pDispatchArgumentsBuffer,
                                                       xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeDispatchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                   void *pUserData) = 0;

    virtual xe_result_t reset() = 0;

    static CommandGraph *fromHandle(xe_command_graph_handle_t handle) {
        return static_cast<CommandGraph *>(handle);
    }

    inline xe_command_graph_handle_t toHandle() {
        return this;
    }
};

} // namespace L0