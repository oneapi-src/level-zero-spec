#pragma once
#include "memory_manager.h"
#include "white_box.h"
#include "gmock/gmock.h"

template <>
struct WhiteBox<xe::MemoryManager> : public xe::MemoryManager {
};

namespace xe {

struct MockMemoryManager : public WhiteBox<MemoryManager> {
    MOCK_METHOD0(allocateDeviceMemory, GraphicsAllocation *());
    MOCK_METHOD1(freeMemory, void (GraphicsAllocation *allocation));
};

} // namespace xe
