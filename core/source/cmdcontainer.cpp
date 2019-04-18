#include "xe_common.h"
#include "cmdcontainer.h"
#include "device.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include <cassert>

namespace L0 {

CommandContainer::~CommandContainer() {
    destroy();
}

bool CommandContainer::initialize(Device *device) {
    assert(device);
    this->device = device;

    // Allocate memory for our batch buffer
    assert(globalMemoryManager);
    allocation = globalMemoryManager->allocateDeviceMemory(65536u, 4096u);
    assert(allocation);

    // Add our allocation to the residency container
    residencyContainer.push_back(allocation->allocationRT);

    // Allocate memory for each of our indirect state heaps
    for (auto &allocationIndirectHeap : allocationIndirectHeaps) {
        allocationIndirectHeap = globalMemoryManager->allocateDeviceMemory(16384u, 4096u);
        residencyContainer.push_back(allocationIndirectHeap->allocationRT);
    }

    uint32_t index = 0;
    for (auto &indirectHeap : indirectHeaps) {
        auto allocationRT = allocationIndirectHeaps[index++]->allocationRT;
        indirectHeap = new NEO::IndirectHeap(allocationRT);
    }

    commandStream = new NEO::LinearStream(allocation->allocationRT);

    instructionHeapBaseAddress = globalMemoryManager->getIsaHeapGpuAddress();

    return true;
}

xe_result_t CommandContainer::destroy() {
    auto memoryManager = device
                             ? globalMemoryManager
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

    for (auto deallocation : deallocationContainer) {
        assert(deallocation);
        assert(memoryManager);
        memoryManager->freeMemory(deallocation);
    }

    for (auto &indirectHeap : indirectHeaps) {
        delete indirectHeap;
    }

    //For reset, all variables need to be put back to initial state
    dirtyHeaps = static_cast<uint32_t>(-1);
    slmSize = static_cast<uint32_t>(-1);

    delete commandStream;
    residencyContainer.clear();
    deallocationContainer.clear();
    printfFunctionContainer.clear();
    return XE_RESULT_SUCCESS;
}

void CommandContainer::addToResidencyContainer(GraphicsAllocation *alloc) {
    if (alloc == nullptr) {
        return;
    }
    assert(alloc->allocationRT != nullptr);
    auto end = this->residencyContainer.end();
    bool isUnique = (end == std::find(this->residencyContainer.begin(), end, alloc->allocationRT));
    if (isUnique == false) {
        return;
    }

    this->residencyContainer.push_back(alloc->allocationRT);
}

void CommandContainer::storePrintfFunction(Function *function) {
    auto it = std::find(this->printfFunctionContainer.begin(), this->printfFunctionContainer.end(), function);

    if (it == this->printfFunctionContainer.end()) {
        this->printfFunctionContainer.push_back(function);
    }
}

} // namespace L0
