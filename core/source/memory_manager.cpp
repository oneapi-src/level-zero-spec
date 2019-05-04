#include "device.h"
#include "memory_manager.h"

#include "graphics_allocation.h"

#include "runtime/helpers/string.h"
#include "runtime/memory_manager/deferred_deleter.h"
#include "runtime/memory_manager/deferrable_allocation_deletion.h"
#include "runtime/memory_manager/memory_manager.h"
#include "runtime/memory_manager/svm_memory_manager.h"
#include "runtime/platform/platform.h"
#include "runtime/execution_environment/execution_environment.h"

#include <cassert>
#include <unordered_map> // temporary

namespace L0 {

MemoryManager *globalMemoryManager = nullptr;

struct MemoryManagerImp : public MemoryManager {

    void *allocateHostMemory(size_t size, size_t alignment) override {
        void *buffer = this->memoryManagerRT->allocateSystemMemory(size, alignment);
        HostAllocation *allocation = new HostAllocation(buffer, size);
        allocationTracker[allocation->getHostAddress()] = allocation;

        return buffer;
    }

    GraphicsAllocation *allocateDeviceMemory(Device *device, size_t size, size_t alignment) override {
        NEO::AllocationProperties properties(size, NEO::GraphicsAllocation::AllocationType::UNDECIDED);
        properties.alignment = alignment;

        auto allocation = new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemoryWithProperties(properties));
        knownAllocations.insert(*allocation->allocationRT); // temporary
        allocMap[allocation->allocationRT] = allocation;    // temporary
        allocationTracker[allocation->getHostAddress()] = allocation;
        allocation->setDevice(device);

        return allocation;
    }

    GraphicsAllocation *allocateManagedMemory(Device *device, size_t size, size_t alignment) override {
        NEO::AllocationProperties properties(size, NEO::GraphicsAllocation::AllocationType::UNDECIDED);
        properties.alignment = alignment;

        auto allocation = new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemoryWithProperties(properties));
        knownAllocations.insert(*allocation->allocationRT); // temporary
        allocMap[allocation->allocationRT] = allocation;    // temporary
        allocationTracker[allocation->getHostAddress()] = allocation;
        allocation->setDevice(device);

        return allocation;
    }

    GraphicsAllocation *allocateManagedMemoryFromFault(Device *device, void *buffer, size_t size) override {
        // TODO :
        //        * How are allocations removed from this list?
        //        * What if we encouter the same allocation multiple times but with different sizes (note : it's a valid and very probable scenario)
        //        * How are handle fragmented allocations handled (aka tripple allocations) ?
        auto allocation = new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemoryWithProperties({false, size, NEO::GraphicsAllocation::AllocationType::UNDECIDED}, buffer));
        allocation->setAllocatedFromFault(true);
        knownAllocations.insert(*allocation->allocationRT); // temporary
        allocMap[allocation->allocationRT] = allocation;    // temporary
        allocationTracker[allocation->getHostAddress()] = allocation;
        allocation->setDevice(device);

        return allocation;
    }

    PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForIsa(PtrRef<const void> isaHostMem, size_t size) override {
        assert(size > 0);
        auto alloc = this->memoryManagerRT->allocateGraphicsMemoryWithProperties({size, NEO::GraphicsAllocation::AllocationType::KERNEL_ISA});
        if (isaHostMem != nullptr) {
            this->memoryManagerRT->copyMemoryToAllocation(alloc, isaHostMem.get(), static_cast<uint32_t>(size));
        }
        return PtrOwn<GraphicsAllocation>{new GraphicsAllocation(alloc)};
    }

    uint64_t getIsaHeapGpuAddress() const override {
        return this->memoryManagerRT->getInternalHeapBaseAddress();
    }

    PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForPrivateMemory(size_t size) override {
        assert(size > 0);
        auto alloc = this->memoryManagerRT->allocateGraphicsMemoryWithProperties({size, NEO::GraphicsAllocation::AllocationType::PRIVATE_SURFACE});
        return PtrOwn<GraphicsAllocation>{new GraphicsAllocation(alloc)};
    }

    GraphicsAllocation *findGraphicsAllocation(const void *ptr) override {
        return static_cast<GraphicsAllocation *>(allocMap[knownAllocations.get(ptr)]); // temporary
    }

    MemAllocation *findMemAllocation(const void *ptr) override {
        return allocMap[knownAllocations.get(ptr)]; // temporary
    }

    bool checkMemoryAccessFromDevice(Device *device, const void *ptr) override {
        MemAllocation *allocation = findMemAllocation(ptr);
        assert(allocation);

        if (allocation->allocType == AllocationType::HOST ||
            allocation->allocType == AllocationType::SHARED)
            return true;

        if (static_cast<GraphicsAllocation *>(allocation)->getDevice() == device)
            return true;

        xe_bool_t p2pCapable = true;
        device->canAccessPeer(static_cast<GraphicsAllocation *>(allocation)->getDevice(), &p2pCapable);

        return p2pCapable;
    }

    void freeMemory(GraphicsAllocation *allocation) {
        allocMap.erase(allocation->allocationRT);           // temporary
        knownAllocations.remove(*allocation->allocationRT); // temporary

        memoryManagerRT->freeGraphicsMemory(static_cast<NEO::GraphicsAllocation *>(allocation->allocationRT));

        delete allocation;
    }

    void freeMemory(const void *ptr) override {
        void *bufferAddress = const_cast<void *>(ptr);
        MemAllocation *allocation = allocationTracker[bufferAddress];
        assert(allocation);
        if (allocation->allocType == AllocationType::DEVICE ||
                allocation->allocType == AllocationType::SHARED) {
            freeMemory(static_cast<GraphicsAllocation *>(allocation));
        } else {
            alignedFree(bufferAddress);
        }
    }

    MemoryManagerImp(void *memoryManagerRT)
        : memoryManagerRT(static_cast<NEO::MemoryManager *>(memoryManagerRT)) {
    }

    NEO::MemoryManager *memoryManagerRT;
    NEO::SVMAllocsManager::MapBasedAllocationTracker knownAllocations;
    std::unordered_map<NEO::GraphicsAllocation *, L0::MemAllocation *> allocMap; // temporary
    std::unordered_map<void *, L0::MemAllocation *> allocationTracker;
};

void MemoryManager::createGlobalMemoryManager() {

    struct MemoryManagerWrapper {
        MemoryManagerWrapper(MemoryManager *&globalMemoryManager) {
            auto platform = NEO::platform();
            globalMemoryManager = new MemoryManagerImp(platform->peekExecutionEnvironment()->memoryManager.get());
        }

        ~MemoryManagerWrapper() {
            if (globalMemoryManager) {
                delete globalMemoryManager;
            }
        }
    };

    static MemoryManagerWrapper memoryManagerWrapper(globalMemoryManager);
    return;
}

} // namespace L0
