#define CMD_LIST_INTERNAL
#include "cmd_list_imp.h"
#undef CMD_LIST_INTERNAL
#include "igfxfmid.h"

namespace xe {

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

xe_result_t CommandListImp::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

CommandList *CommandList::create(uint32_t productFamily, Device *device) {
    CommandListAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = commandListFactory[productFamily];
    }

    CommandList *commandList = nullptr;
    if (allocator) {
        commandList = (*allocator)(device);
    }
    return commandList;
}

} // namespace xe
