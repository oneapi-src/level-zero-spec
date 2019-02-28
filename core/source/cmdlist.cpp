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
xeCommandListEncodeDispatchFunction(
    xe_command_list_handle_t hCommandList,
    xe_function_handle_t hFunction,
    xe_dispatch_function_arguments_t *pDispatchFuncArgs,
    xe_event_handle_t hEvent) {
    return CommandList::fromHandle(hCommandList)->encodeDispatchFunction(hFunction, pDispatchFuncArgs, hEvent);
}

xe_result_t __xecall
xeCommandListDispatchFunction(xe_command_list_handle_t hCommandList) {
    return CommandList::fromHandle(hCommandList)->destroy();
}

xe_result_t __xecall
xeCommandListEncodeSignalEvent(xe_command_list_handle_t hCommandList,
                               xe_event_handle_t hEvent) {
    return CommandList::fromHandle(hCommandList)->encodeSignalEvent(hEvent);
}

xe_result_t __xecall
xeCommandListEncodeWaitOnEvent(xe_command_list_handle_t hCommandList,
                               xe_event_handle_t hEvent) {
    return CommandList::fromHandle(hCommandList)->encodeWaitOnEvent(hEvent);
}
} // namespace L0
