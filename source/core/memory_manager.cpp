#include "device.h"
#include "memory_manager.h"

#include "graphics_allocation.h"

#include "runtime/helpers/string.h"
#include "runtime/memory_manager/deferred_deleter.h"
#include "runtime/memory_manager/deferrable_allocation_deletion.h"
#include "runtime/memory_manager/memory_manager.h"
#include "runtime/platform/platform.h"
#include "runtime/execution_environment/execution_environment.h"

#include <cassert>
#include <map>

namespace L0 {

MemoryManager *globalMemoryManager = nullptr;

struct MemoryManagerImp : public MemoryManager {

    void insertAllocation(void *ptr, MemAllocation *allocation) {
        allocationTracker.insert(std::pair<void *,
                MemAllocation *>(allocation->getHostAddress(), allocation));
    }

    void *allocateHostMemory(size_t size, size_t alignment) override {
        void *buffer = this->memoryManagerRT->allocateSystemMemory(size, alignment);
        HostAllocation *allocation = new HostAllocation(buffer, size);
        insertAllocation(allocation->getHostAddress(), allocation);

        return buffer;
    }

    GraphicsAllocation *allocateDeviceMemory(Device *device, size_t size,
                                             size_t alignment) override {
        NEO::AllocationProperties properties(size,
                                             NEO::GraphicsAllocation::AllocationType::UNDECIDED);
        properties.alignment = alignment;

        auto allocation = new GraphicsAllocation(
            memoryManagerRT->allocateGraphicsMemoryWithProperties(properties));
        insertAllocation(allocation->getHostAddress(), allocation);
        allocation->setDevice(device);

        return allocation;
    }

    GraphicsAllocation *allocateManagedMemory(Device *device, size_t size,
                                              size_t alignment) override {
        NEO::AllocationProperties properties(size,
                                             NEO::GraphicsAllocation::AllocationType::UNDECIDED);
        properties.alignment = alignment;

        auto allocation = new GraphicsAllocation(
            memoryManagerRT->allocateGraphicsMemoryWithProperties(properties));
        insertAllocation(allocation->getHostAddress(), allocation);
        allocation->setDevice(device);

        return allocation;
    }

    GraphicsAllocation *allocateManagedMemoryFromFault(Device *device, void *buffer,
                                                       size_t size) override {
        // TODO :
        //        * How are allocations removed from this list?
        //        * What if we encouter the same allocation multiple times but with different sizes
        //        (note : it's a valid and very probable scenario)
        //        * How are handle fragmented allocations handled (aka tripple allocations) ?
        auto allocation =
            new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemoryWithProperties(
                {false, size, NEO::GraphicsAllocation::AllocationType::UNDECIDED}, buffer));
        allocation->setAllocatedFromFault(true);
        insertAllocation(buffer, allocation);
        allocation->setDevice(device);

        return allocation;
    }

    PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForIsa(PtrRef<const void> isaHostMem,
                                                            size_t size) override {
        assert(size > 0);
        auto alloc = this->memoryManagerRT->allocateGraphicsMemoryWithProperties(
            {size, NEO::GraphicsAllocation::AllocationType::KERNEL_ISA});
        if (isaHostMem != nullptr) {
            this->memoryManagerRT->copyMemoryToAllocation(alloc, isaHostMem.get(),
                                                          static_cast<uint32_t>(size));
        }
        return PtrOwn<GraphicsAllocation>{new GraphicsAllocation(alloc)};
    }

    uint64_t getIsaHeapGpuAddress() const override {
        return this->memoryManagerRT->getInternalHeapBaseAddress();
    }

    PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForPrivateMemory(size_t size) override {
        assert(size > 0);
        auto alloc = this->memoryManagerRT->allocateGraphicsMemoryWithProperties(
            {size, NEO::GraphicsAllocation::AllocationType::PRIVATE_SURFACE});
        return PtrOwn<GraphicsAllocation>{new GraphicsAllocation(alloc)};
    }

    MemAllocation *findMemAllocation(const void *ptr) override {
        auto allocIt = allocationTracker.find(const_cast<void *>(ptr));
        if (allocIt != allocationTracker.end()) {
            return allocIt->second;
        }

        uint64_t allocPtr = reinterpret_cast<uint64_t>(ptr);
        for (auto allocation : allocationTracker) {
            uint64_t base = reinterpret_cast<uint64_t>(allocation.second->getHostAddress());
            size_t size = allocation.second->getSize();
            if (allocPtr >= base && allocPtr < base + size) {
                return allocation.second;
            }
        }
        return nullptr;
    }

    xe_result_t getAddressRange(const void *ptr, void **pBase, size_t *pSize) override {
        MemAllocation *alloc = findMemAllocation(ptr);
        if (alloc) {
            uint64_t *allocBase = reinterpret_cast<uint64_t *>(pBase);
            uint64_t base = reinterpret_cast<uint64_t>(alloc->getHostAddress());
            *allocBase = base;

            *pSize = alloc->getSize();

            return XE_RESULT_SUCCESS;
        }

        return XE_RESULT_ERROR_UNKNOWN;
    }

    GraphicsAllocation *findGraphicsAllocation(const void *ptr) override {
        return static_cast<GraphicsAllocation *>(findMemAllocation(ptr));
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
        device->canAccessPeer(static_cast<GraphicsAllocation *>(allocation)->getDevice(),
                              &p2pCapable);

        return p2pCapable;
    }

    void freeGraphicsAllocation(GraphicsAllocation *allocation) {
        memoryManagerRT->freeGraphicsMemory(
            static_cast<NEO::GraphicsAllocation *>(allocation->allocationRT));

        void *ptr = allocation->getHostAddress();
        allocationTracker.erase(ptr);

        delete allocation;
    }

    void freeMemory(const void *ptr) override {
        void *bufferAddress = const_cast<void *>(ptr);
        auto it = allocationTracker.find(bufferAddress);
        if (it != allocationTracker.end()) {
            MemAllocation *allocation = it->second;
            if (allocation->allocType == AllocationType::DEVICE ||
                allocation->allocType == AllocationType::SHARED) {
                freeGraphicsAllocation(static_cast<GraphicsAllocation *>(allocation));
            } else {
                allocationTracker.erase(bufferAddress);
                delete allocation;
                alignedFree(bufferAddress);
            }
        }
    }

    MemoryManagerImp(void *memoryManagerRT)
        : memoryManagerRT(static_cast<NEO::MemoryManager *>(memoryManagerRT)) {}

    NEO::MemoryManager *memoryManagerRT;
protected:
    std::map<void *, L0::MemAllocation *> allocationTracker;
};

void MemoryManager::createGlobalMemoryManager() {

    struct MemoryManagerWrapper {
        MemoryManagerWrapper(MemoryManager *&globalMemoryManager) {
            auto platform = NEO::platform();
            globalMemoryManager =
                new MemoryManagerImp(platform->peekExecutionEnvironment()->memoryManager.get());
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
