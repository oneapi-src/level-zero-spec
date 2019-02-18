#pragma once

namespace xe {
struct GraphicsAllocation;

struct MemoryManager {
    virtual GraphicsAllocation *allocateDeviceMemory(size_t size, size_t alignment) = 0;
    virtual GraphicsAllocation *allocateManagedMemory(size_t size, size_t alignment) = 0;
    virtual GraphicsAllocation *findAllocation(const void *ptr) = 0;
    virtual void freeMemory(GraphicsAllocation *allocation) = 0;

    static MemoryManager *create(void *memoryManagerRT);
};

} // namespace xe
