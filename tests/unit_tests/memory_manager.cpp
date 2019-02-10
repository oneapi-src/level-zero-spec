#include "graphics_allocation.h"
#include "memory_manager.h"
#include "runtime/memory_manager/memory_manager.h"

namespace xe {

struct MemoryManagerImp : public MemoryManager {
    GraphicsAllocation *allocateDeviceMemory(size_t size) override {
        OCLRT::AllocationProperties properties(size, OCLRT::GraphicsAllocation::AllocationType::COMMAND_BUFFER);

        auto allocation = new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemory(properties, nullptr));

        return allocation;
    }

    void freeMemory(GraphicsAllocation *allocation) {
        memoryManagerRT->freeGraphicsMemory(static_cast<OCLRT::GraphicsAllocation *>(allocation->allocationRT));
        delete allocation;
    }

    MemoryManagerImp(void *memoryManagerRT)
        : memoryManagerRT(static_cast<OCLRT::MemoryManager *>(memoryManagerRT)) {
    }

    OCLRT::MemoryManager *memoryManagerRT;
};

MemoryManager *MemoryManager::create(void *memoryManagerRT) {
    return new MemoryManagerImp(memoryManagerRT);
}

} // namespace xe
