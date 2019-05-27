#include "device.h"
#include "graphics_allocation.h"
#include "memory.h"
#include "memory_manager.h"
#include <cassert>

namespace L0 {

xe_result_t hostMemAlloc(xe_host_mem_alloc_flag_t flags, size_t size, size_t alignment,
                         void **ptr) {
    assert(globalMemoryManager);
    *ptr = globalMemoryManager->allocateHostMemory(size, alignment);

    return XE_RESULT_SUCCESS;
}

xe_result_t ipcCloseMemHandle(const void *ptr) { return XE_RESULT_ERROR_UNSUPPORTED; }

xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) {
    auto ipc = L0MemoryManagerSepecifics::create();
    return ipc->ipcGetMemHandle(ptr, pIpcHandle);
}

xe_result_t ipcOpenMemHandle(xe_device_handle_t hDevice, xe_ipc_mem_handle_t handle,
                             xe_ipc_memory_flag_t flags, void **ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t deviceMemAlloc(xe_device_handle_t hDevice, xe_device_mem_alloc_flag_t flags,
                           size_t size, size_t alignment, void **ptr) {
    void *buffer;
    auto device = Device::fromHandle(hDevice);
    auto l0mms = L0MemoryManagerSepecifics::create();
    std::string shmFileName;
    GraphicsAllocation *allocation;

    assert(device);
    assert(globalMemoryManager);

    // Allocate shred memory (so later can be shared with other proc using IPC)
    buffer = l0mms->allocateShMemory(size, alignment, shmFileName);
    /*FIXME: there is no Windows support for l0mms->allocateShMemor. So, until there is one,
    /* on failure, it will fallback to normal allocations without support for IPC. However,
     * must be updated to fail here
     */
    if (buffer != nullptr) {
        allocation = globalMemoryManager->allocateManagedMemoryFromFault(device, buffer, size);
        allocation->shmFileName = shmFileName;
    } else {
        allocation = globalMemoryManager->allocateManagedMemory(device, size, alignment);
    }

    assert(allocation);
    allocation->allocType = AllocationType::DEVICE;

    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

xe_result_t memFree(const void *ptr) {
    assert(globalMemoryManager);
    globalMemoryManager->freeMemory(ptr);

    return XE_RESULT_SUCCESS;
}

xe_result_t memGetAddressRange(const void *ptr, void **pBase, size_t *pSize) {
    assert(globalMemoryManager);
    return globalMemoryManager->getAddressRange(ptr, pBase, pSize);
}

xe_result_t memGetProperties(const void *ptr, xe_memory_allocation_properties_t *pMemProperties) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t sharedMemAlloc(xe_device_handle_t hDevice, xe_device_mem_alloc_flag_t device_flags,
                           xe_host_mem_alloc_flag_t host_flags, size_t size, size_t alignment,
                           void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    assert(globalMemoryManager);

    auto allocation = globalMemoryManager->allocateManagedMemory(device, size, alignment);
    assert(allocation);
    allocation->allocType = AllocationType::SHARED;

    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

} // namespace L0