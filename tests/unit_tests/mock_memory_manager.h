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
    MOCK_METHOD2(allocateDeviceMemory, GraphicsAllocation *(size_t size, size_t alignment));
    MOCK_METHOD2(allocateManagedMemory, GraphicsAllocation *(size_t size, size_t alignment));
    MOCK_METHOD2(allocateManagedMemoryFromFault, GraphicsAllocation *(void *buffer, size_t size));
    MOCK_METHOD2(allocateGraphicsMemoryForIsa, PtrOwn<GraphicsAllocation>(PtrRef<const void> isaHostMem, size_t size));
    MOCK_METHOD1(allocateGraphicsMemoryForPrivateMemory, PtrOwn<GraphicsAllocation>(size_t));
    MOCK_CONST_METHOD0(getIsaHeapGpuAddress, uint64_t());
    MOCK_METHOD1(freeMemory, void(GraphicsAllocation *allocation));
    MOCK_METHOD1(freeMemory, void(const void *ptr));
    MOCK_METHOD1(findAllocation, GraphicsAllocation *(const void *ptr));

    // default mock implementation
    void *doAllocateHostMemory(size_t size, size_t alignment);
    GraphicsAllocation *doCreateGraphicsAllocation(size_t size, size_t alignment);
    PtrOwn<GraphicsAllocation> doCreateGraphicsAllocationForIsa(PtrRef<const void> isaHostMem, size_t size);
    PtrOwn<GraphicsAllocation> doCreateGraphicsAllocationForPrivateMemory(size_t size);
    void doFreeGraphicsAllocation(GraphicsAllocation *allocation);
    void doFreePtr(const void *ptr);
    GraphicsAllocation *doFindAllocation(const void *ptr);

    void track(L0::GraphicsAllocation *alloc);
    void drop(L0::GraphicsAllocation *alloc);
    NEO::SVMAllocsManager::MapBasedAllocationTracker knownAllocations;
    std::unordered_map<NEO::GraphicsAllocation *, L0::GraphicsAllocation *> allocMap;
};

} // namespace ult
} // namespace L0
