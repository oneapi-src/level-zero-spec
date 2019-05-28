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
        allocationTracker.insert(
            std::pair<void *, MemAllocation *>(allocation->getHostAddress(), allocation));
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
                                             NEO::GraphicsAllocation::AllocationType::INTERNAL_HOST_MEMORY);
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
                                             NEO::GraphicsAllocation::AllocationType::INTERNAL_HOST_MEMORY);
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
        //        * How are handle fragmented allocations handled (aka tripple allocations) ?
        GraphicsAllocation *allocation = findGraphicsAllocation(buffer);
        if (allocation)
            return allocation;

        allocation = new GraphicsAllocation(memoryManagerRT->allocateGraphicsMemoryWithProperties(
                {false, size, NEO::GraphicsAllocation::AllocationType::INTERNAL_HOST_MEMORY},
                        buffer));
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
        // Check if there are any elements
        if (allocationTracker.size() == 0) {
            return nullptr;
        }

        auto allocLower = allocationTracker.lower_bound(const_cast<void *>(ptr));

        // Check if ptr is alloc's base address
        if (ptr == allocLower->first)
            return allocLower->second;

        // Check now for ranges
        if (allocLower != allocationTracker.begin())
            allocLower--;

        uint64_t arithPtr = reinterpret_cast<uint64_t>(ptr);
        uint64_t allocBase = reinterpret_cast<uint64_t>(allocLower->first);

        if ((arithPtr >= allocBase) && (arithPtr < (allocBase + allocLower->second->getSize())))
            return allocLower->second;

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

    void freeHostMemory(MemAllocation *allocation) {
        void *ptr = allocation->getHostAddress();
        allocationTracker.erase(ptr);

        delete allocation;

        alignedFree(ptr);
    }

    void freeMemory(const void *ptr) override {
        void *bufferAddress = const_cast<void *>(ptr);
        auto it = allocationTracker.find(bufferAddress);
        if (it != allocationTracker.end()) {
            MemAllocation *allocation = it->second;
            if (allocation->allocType == AllocationType::DEVICE ||
                allocation->allocType == AllocationType::SHARED) {
                GraphicsAllocation *graphicAllocation =
                    static_cast<GraphicsAllocation *>(allocation);
                // Extra step to clean /dev/shm for DEVICE type of allocation
                if (allocation->allocType == AllocationType::DEVICE) {
                    auto l0mms = L0MemoryManagerSepecifics::create();
                    l0mms->freeShMemory(graphicAllocation);
                }
                freeGraphicsAllocation(graphicAllocation);
            } else {
                freeHostMemory(allocation);
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
