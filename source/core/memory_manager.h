#pragma once

#include "xe_common.h"
#include "xe_memory.h"
#include "ptr.h"

#include <cstddef>
#include <cstdint>
#include <iostream>

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
    virtual void freeGraphicsAllocation(GraphicsAllocation *allocation) = 0;
    virtual void freeHostMemory(MemAllocation *allocation) = 0;
    virtual void freeMemory(const void *ptr) = 0;

    static void createGlobalMemoryManager();
};

extern MemoryManager *globalMemoryManager;

struct L0MemoryManagerSepecifics {

  public:
    static L0MemoryManagerSepecifics *create();
    virtual xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) = 0;
    virtual xe_result_t ipcOpenMemHandle(xe_device_handle_t hDevice, xe_ipc_mem_handle_t handle,
                                         xe_ipc_memory_flag_t flags, void **ptr) = 0;
    virtual xe_result_t ipcCloseMemHandle(const void *ptr) = 0;
    virtual void *allocateShMemory(size_t size, size_t alignment, std::string &shmFileName) = 0;
    virtual void freeShMemory(GraphicsAllocation *graphAllocation) = 0;
};

} // namespace L0
