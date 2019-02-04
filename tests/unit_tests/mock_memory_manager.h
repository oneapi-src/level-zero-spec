#pragma once
#include "memory_manager.h"
#include "white_box.h"
#include "gmock/gmock.h"

namespace xe {
namespace ult {

template <>
struct WhiteBox<::xe::MemoryManager> : public ::xe::MemoryManager {
    using BaseClass = ::xe::MemoryManager;
};

struct MockMemoryManager : public WhiteBox<::xe::MemoryManager> {
    MockMemoryManager();
    virtual ~MockMemoryManager();

    MOCK_METHOD0(allocateDeviceMemory, GraphicsAllocation *());
    MOCK_METHOD1(freeMemory, void(GraphicsAllocation *allocation));
};

using MemoryManager = WhiteBox<::xe::MemoryManager>;

} // namespace ult
} // namespace xe
