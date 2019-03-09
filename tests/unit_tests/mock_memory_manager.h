#pragma once
#include "memory_manager.h"
#include "mock.h"
#include "white_box.h"

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

    MOCK_METHOD2(allocateDeviceMemory, GraphicsAllocation *(size_t size, size_t alignment));
    MOCK_METHOD2(allocateManagedMemory, GraphicsAllocation *(size_t size, size_t alignment));
    MOCK_METHOD2(allocateGraphicsMemoryForIsa, GraphicsAllocation *(const void *isaHostMem, size_t size));
    MOCK_CONST_METHOD0(getIsaHeapGpuAddress, uint64_t());
    MOCK_METHOD1(freeMemory, void(GraphicsAllocation *allocation));
    MOCK_METHOD1(findAllocation, GraphicsAllocation *(const void *ptr));
};

} // namespace ult
} // namespace L0
