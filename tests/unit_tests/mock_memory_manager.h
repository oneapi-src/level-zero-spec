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

    MOCK_METHOD1(allocateDeviceMemory, GraphicsAllocation *(size_t size));
    MOCK_METHOD1(freeMemory, void(GraphicsAllocation *allocation));
};

} // namespace ult
} // namespace xe
