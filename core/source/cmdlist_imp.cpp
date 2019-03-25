#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "device.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"

#include <algorithm>
#include <cassert>

namespace L0 {

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

    CommandListImp *commandList = nullptr;
    if (allocator) {
        commandList = static_cast<CommandListImp *>((*allocator)());

        commandList->initialize(device);
    }
    return commandList;
}

} // namespace L0
