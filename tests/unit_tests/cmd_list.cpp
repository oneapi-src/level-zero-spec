#include "cmd_list.h"
#include "igfxfmid.h"

namespace xe {

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

xe_result_t CommandList::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

CommandList *CommandList::create(uint32_t productFamily) {
    CommandListAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = commandListFactory[productFamily];
    }

    CommandList *commandList = nullptr;
    if (allocator) {
        commandList = (*allocator)();
    }
    return commandList;
}

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
