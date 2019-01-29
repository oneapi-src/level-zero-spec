#pragma once
#include "memory_manager.h"
#include "white_box.h"
#include "gmock/gmock.h"

namespace xe {

template <>
struct WhiteBox<MemoryManager> : public MemoryManager {
};

struct MockMemoryManager : public WhiteBox<MemoryManager> {
    MOCK_METHOD0(allocateDeviceMemory, GraphicsAllocation *());
    MOCK_METHOD1(freeMemory, void (GraphicsAllocation *allocation));
};

} // namespace xe
