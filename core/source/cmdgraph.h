#pragma once
#include "xe_common.h"
#include "device.h"

struct _xe_command_graph_handle_t {
};

namespace L0 {

struct CommandGraph : public _xe_command_graph_handle_t {

    virtual xe_result_t close() = 0;
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t appendLaunchFunction(xe_function_handle_t hFunction,
                                               const xe_thread_group_dimensions_t *pDispatchFuncArgs,
                                               xe_event_handle_t hEvent) = 0;
    virtual xe_result_t appendLaunchFunctionIndirect(xe_function_handle_t hFunction,
                                                       const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                                       xe_event_handle_t hEvent) = 0;
    virtual xe_result_t appendLaunchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                   void *pUserData) = 0;

    virtual xe_result_t reset() = 0;

    //static CommandGraph *fromHandle(xe_command_graph_handle_t handle) {
    //    return static_cast<CommandGraph *>(handle);
    //}

    //inline xe_command_graph_handle_t toHandle() {
    //    return this;
    //}
};

} // namespace L0
