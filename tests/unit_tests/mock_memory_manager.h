#pragma once

#include "memory_manager.h"

#include "graphics_allocation.h"

#include "mock.h"
#include "white_box.h"

#include "runtime/memory_manager/svm_memory_manager.h"

#include <unordered_map>

namespace L0 {
namespace ult {

template <>
struct WhiteBox<::L0::MemoryManager> : public ::L0::MemoryManager {
    using BaseClass = ::L0::MemoryManager;
};

using MemoryManager = WhiteBox<::L0::MemoryManager>;

template <>
struct Mock<MemoryManager> : public MemoryManager {
    Mock();
    virtual ~Mock();

    MOCK_METHOD2(allocateHostMemory, void *(size_t size, size_t alignment));
    MOCK_METHOD3(allocateDeviceMemory, L0::GraphicsAllocation *(L0::Device *device, size_t size, size_t alignment));
    MOCK_METHOD3(allocateManagedMemory, L0::GraphicsAllocation *(L0::Device *device, size_t size, size_t alignment));
    MOCK_METHOD3(allocateManagedMemoryFromFault, L0::GraphicsAllocation *(L0::Device *device, void *buffer, size_t size));
    MOCK_METHOD2(allocateGraphicsMemoryForIsa, PtrOwn<L0::GraphicsAllocation>(PtrRef<const void> isaHostMem, size_t size));
    MOCK_METHOD1(allocateGraphicsMemoryForPrivateMemory, PtrOwn<L0::GraphicsAllocation>(size_t size));
    MOCK_CONST_METHOD0(getIsaHeapGpuAddress, uint64_t());
    MOCK_METHOD2(checkMemoryAccessFromDevice, bool(L0::Device *device, const void *ptr));
    MOCK_METHOD1(findGraphicsAllocation, L0::GraphicsAllocation *(const void *ptr));
    MOCK_METHOD1(findMemAllocation, L0::MemAllocation *(const void *ptr));
    MOCK_METHOD1(freeMemory, void(L0::GraphicsAllocation *allocation));
    MOCK_METHOD1(freeMemory, void(const void *ptr));

    // default mock implementation
    void *doAllocateHostMemory(size_t size, size_t alignment);
    L0::GraphicsAllocation *doCreateGraphicsAllocation(L0::Device *device, size_t size, size_t alignment);
    PtrOwn<L0::GraphicsAllocation> doCreateGraphicsAllocationForIsa(PtrRef<const void> isaHostMem, size_t size);
    PtrOwn<L0::GraphicsAllocation> doCreateGraphicsAllocationForPrivateMemory(size_t size);
    void doFreeGraphicsAllocation(L0::GraphicsAllocation *allocation);
    void doFreePtr(const void *ptr);
    L0::GraphicsAllocation *doFindGraphicsAllocation(const void *ptr);
    L0::MemAllocation *doFindMemAllocation(const void *ptr);

    void track(L0::GraphicsAllocation *alloc);
    void drop(L0::GraphicsAllocation *alloc);
    NEO::SVMAllocsManager::MapBasedAllocationTracker knownAllocations;
    std::unordered_map<NEO::GraphicsAllocation *, L0::GraphicsAllocation *> allocMap;
};

} // namespace ult
} // namespace L0
