#pragma once

#include "xe_common.h"
#include "ptr.h"

#include <cstddef>
#include <cstdint>

namespace NEO {
class GraphicsAllocation;
}

namespace L0 {
struct Device;
struct MemAllocation;
struct GraphicsAllocation;

struct MemoryManager {
    virtual void *allocateHostMemory(size_t size, size_t alignment) = 0;
    virtual GraphicsAllocation *allocateDeviceMemory(Device *device, size_t size,
                                                     size_t alignment) = 0;
    virtual GraphicsAllocation *allocateManagedMemory(Device *device, size_t size,
                                                      size_t alignment) = 0;
    virtual GraphicsAllocation *allocateManagedMemoryFromFault(Device *device, void *buffer,
                                                               size_t size) = 0;
    virtual PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForIsa(PtrRef<const void> isaHostMem,
                                                                    size_t size) = 0;
    virtual PtrOwn<GraphicsAllocation> allocateGraphicsMemoryForPrivateMemory(size_t size) = 0;
    virtual xe_result_t getAddressRange(const void *ptr, void **pBase, size_t *pSize) = 0;
    virtual uint64_t getIsaHeapGpuAddress() const = 0;
    virtual GraphicsAllocation *findGraphicsAllocation(const void *ptr) = 0;
    virtual MemAllocation *findMemAllocation(const void *ptr) = 0;
    virtual bool checkMemoryAccessFromDevice(Device *device, const void *ptr) = 0;
    virtual void freeMemory(GraphicsAllocation *allocation) = 0;
    virtual void freeMemory(const void *ptr) = 0;

    static void createGlobalMemoryManager();
};

extern MemoryManager *globalMemoryManager;

} // namespace L0
