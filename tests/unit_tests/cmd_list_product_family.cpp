#include "cmd_list_product_family.h"
#include "igfxfmid.h"

namespace xe {

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

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

} // namespace xe
