#include "cmd_list_product_family.inl"
#include "igfxfmid.h"

namespace xe {

using CommandListAllocatorFn = CommandList *(*)();

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

CommandList *CommandList::create(uint32_t productFamily) {
    commandListFactory[IGFX_SKYLAKE] = CommandListProductFamilyAllocator<IGFX_SKYLAKE>::allocate;

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
