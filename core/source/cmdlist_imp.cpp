#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "device.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include <cassert>

namespace L0 {

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

CommandListImp::~CommandListImp() {
    auto memoryManager = device
                             ? device->getMemoryManager()
                             : nullptr;

    if (allocation) {
        assert(memoryManager);
        memoryManager->freeMemory(allocation);
    }

    for (auto allocationIndirectHeap : allocationIndirectHeaps) {
        if (allocationIndirectHeap) {
            assert(memoryManager);
            memoryManager->freeMemory(allocationIndirectHeap);
        }
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

    // Allocate memory for our batch buffer
    {
        allocation = memoryManager->allocateDeviceMemory(65536u, 4096u);
        assert(allocation);

        // Add our allocation to the residency container
        residencyContainer.push_back(allocation->allocationRT);
    }

    // Allocate memory for each of our indirect state heaps
    for (auto &allocationIndirectHeap : allocationIndirectHeaps) {
        allocationIndirectHeap = memoryManager->allocateDeviceMemory(16384u, 4096u);
        residencyContainer.push_back(allocationIndirectHeap->allocationRT);
    }

    uint32_t index = 0;
    for (auto &indirectHeap : indirectHeaps) {
        auto allocationRT = allocationIndirectHeaps[index++]->allocationRT;
        indirectHeap = new OCLRT::IndirectHeap(allocationRT);
    }

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

} // namespace L0
