#pragma once

namespace xe {
struct GraphicsAllocation;

struct MemoryManager {
    virtual GraphicsAllocation *allocateDeviceMemory() = 0;
    virtual void freeMemory(GraphicsAllocation *allocation) = 0;

    static MemoryManager *create(void *memoryManagerRT);
};

} // namespace xe
