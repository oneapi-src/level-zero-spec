#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "device.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include <cassert>

namespace xe {

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

CommandListImp::~CommandListImp() {
    if (allocation) {
        assert(device);
        device->getMemoryManager()->freeMemory(allocation);
    }

    delete commandStream;
}

xe_result_t CommandListImp::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

bool CommandListImp::initialize() {
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);
    allocation = memoryManager->allocateDeviceMemory();
    assert(allocation);

    commandStream = new OCLRT::LinearStream(allocation->allocationRT);

    return true;
}

CommandList *CommandList::create(uint32_t productFamily, Device *device) {
    CommandListAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = commandListFactory[productFamily];
    }

    CommandListImp *commandList = nullptr;
    if (allocator) {
        commandList = static_cast<CommandListImp *>((*allocator)(device));

        commandList->initialize();
    }
    return commandList;
}

} // namespace xe
