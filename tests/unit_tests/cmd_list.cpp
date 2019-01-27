#include "cmd_list.h"

namespace xe {

xe_result_t __xecall
xeCommandListClose(xe_command_list_handle_t hCommandList) {
    return CommandList::fromHandle(hCommandList)->close();
}

xe_result_t __xecall
xeCommandListDestroy(xe_command_list_handle_t hCommandList) {
    return CommandList::fromHandle(hCommandList)->destroy();
}

xe_result_t __xecall
xeCommandListEncodeWaitOnEvent(xe_command_list_handle_t hCommandList,
                               xe_event_handle_t hEvent) {
    return CommandList::fromHandle(hCommandList)->encodeWaitOnEvent(hEvent);
}
} // namespace xe
