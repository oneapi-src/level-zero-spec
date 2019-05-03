#pragma once

#include "ptr.h"

#include <cstddef>
#include <cstdint>

namespace NEO {
class GraphicsAllocation;
}

namespace L0 {
struct GraphicsAllocation;

struct MemoryManager {
    virtual void *allocateHostMemory(size_t size, size_t alignment) = 0;
    virtual GraphicsAllocation *allocateDeviceMemory(size_t size, size_t alignment) = 0;
    virtual GraphicsAllocation *allocateManagedMemory(size_t size, size_t alignment) = 0;
    virtual GraphicsAllocation *allocateManagedMemoryFromFault(void *buffer, size_t size) = 0;
    virtual PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForIsa(PtrRef<const void> isaHostMem, size_t size) = 0;
    virtual PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForPrivateMemory(size_t size) = 0;
    virtual uint64_t getIsaHeapGpuAddress() const = 0;
    virtual GraphicsAllocation *findAllocation(const void *ptr) = 0;
    virtual void freeMemory(GraphicsAllocation *allocation) = 0;
    virtual void freeMemory(const void *ptr) = 0;

    static void createGlobalMemoryManager();
};

extern MemoryManager *globalMemoryManager;

} // namespace L0
