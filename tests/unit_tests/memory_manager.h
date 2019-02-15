#pragma once

namespace xe {
struct GraphicsAllocation;

struct MemoryManager {
    virtual GraphicsAllocation *allocateDeviceMemory(size_t size) = 0;
    virtual GraphicsAllocation *findAllocation(const void *ptr) = 0;
    virtual void freeMemory(GraphicsAllocation *allocation) = 0;

    static MemoryManager *create(void *memoryManagerRT);
};

} // namespace xe
