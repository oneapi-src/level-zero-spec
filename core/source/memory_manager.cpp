#include "graphics_allocation.h"
#include "memory_manager.h"
#include "runtime/memory_manager/memory_manager.h"
#include "runtime/memory_manager/svm_memory_manager.h"

#include <unordered_map> // temporary

namespace L0 {

struct MemoryManagerImp : public MemoryManager {
    GraphicsAllocation *allocateDeviceMemory(size_t size, size_t alignment) override {
        OCLRT::AllocationProperties properties(size, OCLRT::GraphicsAllocation::AllocationType::UNDECIDED);
        properties.alignment = alignment;

        auto allocation = new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemory(properties, nullptr));
        knownAllocations.insert(*allocation->allocationRT); // temporary
        allocMap[allocation->allocationRT] = allocation; // temporary

        return allocation;
    }

    GraphicsAllocation *allocateManagedMemory(size_t size, size_t alignment) override {
        OCLRT::AllocationProperties properties(size, OCLRT::GraphicsAllocation::AllocationType::UNDECIDED);
        properties.alignment = alignment;

        auto allocation = new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemory(properties, nullptr));
        knownAllocations.insert(*allocation->allocationRT); // temporary
        allocMap[allocation->allocationRT] = allocation; // temporary

        return allocation;
    }

    GraphicsAllocation *findAllocation(const void *ptr) override {
        return allocMap[knownAllocations.get(ptr)]; // temporary
    }

    void freeMemory(GraphicsAllocation *allocation) {
        allocMap.erase(allocation->allocationRT); // temporary
        knownAllocations.remove(*allocation->allocationRT); // temporary
        memoryManagerRT->freeGraphicsMemory(static_cast<OCLRT::GraphicsAllocation *>(allocation->allocationRT));
        delete allocation;
    }

    MemoryManagerImp(void *memoryManagerRT)
        : memoryManagerRT(static_cast<OCLRT::MemoryManager *>(memoryManagerRT)) {
    }

    OCLRT::MemoryManager *memoryManagerRT;
    OCLRT::SVMAllocsManager::MapBasedAllocationTracker knownAllocations;
    std::unordered_map<OCLRT::GraphicsAllocation*, L0::GraphicsAllocation*> allocMap; // temporary
};

MemoryManager *MemoryManager::create(void *memoryManagerRT) {
    return new MemoryManagerImp(memoryManagerRT);
}

} // namespace L0
