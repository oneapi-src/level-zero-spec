#include "cmdlist.h"

namespace L0 {

xe_result_t __xecall
xeCommandListClose(xe_command_list_handle_t hCommandList) {
    return CommandList::fromHandle(hCommandList)->close();
}

xe_result_t __xecall
xeCommandListDestroy(xe_command_list_handle_t hCommandList) {
    return CommandList::fromHandle(hCommandList)->destroy();
}

xe_result_t __xecall
xeCommandListAppendExecutionBarrier(xe_command_list_handle_t hCommandList) {
    return CommandList::fromHandle(hCommandList)->appendExecutionBarrier();
}

xe_result_t __xecall
xeCommandListAppendLaunchFunction(
    xe_command_list_handle_t hCommandList,
    xe_function_handle_t hFunction,
    xe_thread_group_dimensions_t *pDispatchFuncArgs,
    xe_event_handle_t hEvent) {
    return CommandList::fromHandle(hCommandList)->appendLaunchFunction(hFunction, pDispatchFuncArgs, hEvent);
}

xe_result_t __xecall
xeCommandListDispatchFunction(xe_command_list_handle_t hCommandList) {
    return CommandList::fromHandle(hCommandList)->destroy();
}

xe_result_t __xecall
xeCommandListAppendSignalEvent(xe_command_list_handle_t hCommandList,
                               xe_event_handle_t hEvent) {
    return CommandList::fromHandle(hCommandList)->appendSignalEvent(hEvent);
}

xe_result_t __xecall
xeCommandListAppendWaitOnEvent(xe_command_list_handle_t hCommandList,
                               xe_event_handle_t hEvent) {
    return CommandList::fromHandle(hCommandList)->appendWaitOnEvent(hEvent);
}
} // namespace L0
