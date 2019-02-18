#pragma once
#include "memory_manager.h"
#include "mock.h"
#include "white_box.h"

namespace xe {
namespace ult {

template <>
struct WhiteBox<::xe::MemoryManager> : public ::xe::MemoryManager {
    using BaseClass = ::xe::MemoryManager;
};

using MemoryManager = WhiteBox<::xe::MemoryManager>;

template<>
struct Mock<MemoryManager> : public MemoryManager {
    Mock();
    virtual ~Mock();

    MOCK_METHOD2(allocateDeviceMemory, GraphicsAllocation *(size_t size, size_t alignment));
    MOCK_METHOD2(allocateManagedMemory, GraphicsAllocation *(size_t size, size_t alignment));
    MOCK_METHOD1(freeMemory, void(GraphicsAllocation *allocation));
    MOCK_METHOD1(findAllocation, GraphicsAllocation *(const void *ptr));
};

} // namespace ult
} // namespace xe
