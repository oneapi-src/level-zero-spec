#include "mock_memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/helpers/aligned_memory.h"

namespace L0 {
namespace ult {

using namespace testing;

using MockMemoryManager = Mock<L0::ult::MemoryManager>;

MockMemoryManager::Mock() {
    EXPECT_CALL(*this, allocateHostMemory)
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doAllocateHostMemory));

    EXPECT_CALL(*this, allocateDeviceMemory)
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doCreateGraphicsAllocation));

    EXPECT_CALL(*this, allocateGraphicsMemoryForIsa)
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doCreateGraphicsAllocationForIsa));

    EXPECT_CALL(*this, allocateGraphicsMemoryForPrivateMemory)
        .WillRepeatedly(
            Invoke(this, &MockMemoryManager::doCreateGraphicsAllocationForPrivateMemory));

    EXPECT_CALL(*this, allocateManagedMemory)
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doCreateGraphicsAllocation));

    EXPECT_CALL(*this, freeGraphicsAllocation)
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doFreeGraphicsAllocation));

    EXPECT_CALL(*this, freeHostMemory)
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doFreeHostMemory));

    EXPECT_CALL(*this, freeMemory).WillRepeatedly(Invoke(this, &MockMemoryManager::doFreePtr));

    EXPECT_CALL(*this, getIsaHeapGpuAddress).Times(AnyNumber());

    EXPECT_CALL(*this, getAddressRange(_, _, _))
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doGetAddressRange));

    EXPECT_CALL(*this, findGraphicsAllocation(_))
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doFindGraphicsAllocation));

    EXPECT_CALL(*this, findMemAllocation(_))
        .WillRepeatedly(Invoke(this, &MockMemoryManager::doFindMemAllocation));
}

void *MockMemoryManager::doAllocateHostMemory(size_t size, size_t alignment) {
    L0::GraphicsAllocation *alloc = doCreateGraphicsAllocation(nullptr, size, alignment);
    assert(alloc);
    return alloc->getHostAddress();
}

xe_result_t MockMemoryManager::doGetAddressRange(const void *ptr, void **pBase, size_t *pSize) {
    uint64_t allocPtr = reinterpret_cast<uint64_t>(ptr);
    uint64_t *allocBase = reinterpret_cast<uint64_t *>(pBase);

    for (auto &alloc : allocationTracker) {
        uint64_t base = reinterpret_cast<uint64_t>(alloc.second->getHostAddress());
        size_t size = alloc.second->getSize();
        if (allocPtr >= base && allocPtr < base + size) {
            *allocBase = base;
            *pSize = size;

            return XE_RESULT_SUCCESS;
        }
    }
    return XE_RESULT_ERROR_UNKNOWN;
}

GraphicsAllocation *MockMemoryManager::doCreateGraphicsAllocation(Device *device, size_t size,
                                                                  size_t alignment) {
    auto buffer = alignedMalloc(size, alignment);
    auto allocation = new GraphicsAllocation(buffer, size);
    insertAllocation(allocation);
    return allocation;
}

PtrOwn<L0::GraphicsAllocation>
MockMemoryManager::doCreateGraphicsAllocationForIsa(PtrRef<const void> isaHostMem, size_t size) {
    auto buffer = alignedMalloc(size, 64);
    auto allocation = new GraphicsAllocation(buffer, size);
    return PtrOwn<L0::GraphicsAllocation>(allocation);
}

PtrOwn<GraphicsAllocation>
MockMemoryManager::doCreateGraphicsAllocationForPrivateMemory(size_t size) {
    auto buffer = alignedMalloc(size, 64);
    auto allocation = new GraphicsAllocation(buffer, size);
    insertAllocation(allocation);
    return PtrOwn<L0::GraphicsAllocation>(allocation);
}

void MockMemoryManager::doFreeGraphicsAllocation(L0::GraphicsAllocation *allocation) {
    assert(allocation);
    auto buffer = reinterpret_cast<uint8_t *>(allocation->getGpuAddress());
    alignedFree(buffer);
    eraseAllocation(allocation);
}

void MockMemoryManager::doFreeHostMemory(L0::MemAllocation *allocation) {
    doFreeGraphicsAllocation(static_cast<L0::GraphicsAllocation *>(allocation));
}

void MockMemoryManager::doFreePtr(const void *ptr) {
    auto it = allocationTracker.find(const_cast<void *>(ptr));
    assert(it != allocationTracker.end());
    doFreeGraphicsAllocation(static_cast<GraphicsAllocation *>(it->second));
}

L0::MemAllocation *MockMemoryManager::doFindMemAllocation(const void *ptr) {
    // Check if there are any elements
    if (allocationTracker.size() == 0) {
        return nullptr;
    }

    auto allocLower = allocationTracker.lower_bound(const_cast<void *>(ptr));

    // Check if ptr is alloc's base address
    if (allocLower != allocationTracker.end() && ptr == allocLower->first)
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

L0::GraphicsAllocation *MockMemoryManager::doFindGraphicsAllocation(const void *ptr) {
    MemAllocation *alloc = doFindMemAllocation(ptr);
    if (alloc)
        return static_cast<L0::GraphicsAllocation *>(alloc);
    return nullptr;
}

void MockMemoryManager::insertAllocation(MemAllocation *allocation) {
    allocationTracker.insert(
        std::pair<void *, MemAllocation *>(allocation->getHostAddress(), allocation));
}

void MockMemoryManager::eraseAllocation(void *ptr) { allocationTracker.erase(ptr); }

Mock<MemoryManager>::~Mock() {}

} // namespace ult
} // namespace L0
