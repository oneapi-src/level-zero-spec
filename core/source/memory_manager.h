#pragma once

#include "ptr.h"

#include <cstddef>
#include <cstdint>

namespace L0 {
struct GraphicsAllocation;

struct MemoryManager {
    virtual GraphicsAllocation *allocateDeviceMemory(size_t size, size_t alignment) = 0;
    virtual GraphicsAllocation *allocateManagedMemory(size_t size, size_t alignment) = 0;
    virtual PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForIsa(PtrRef<const void> isaHostMem, size_t size) = 0;
    virtual uint64_t getIsaHeapGpuAddress() const = 0;
    virtual GraphicsAllocation *findAllocation(const void *ptr) = 0;
    virtual void freeMemory(GraphicsAllocation *allocation) = 0;

    static MemoryManager *create(void *memoryManagerRT);
};

} // namespace L0
