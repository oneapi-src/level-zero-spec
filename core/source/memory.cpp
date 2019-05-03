#include "device.h"
#include "graphics_allocation.h"
#include "memory.h"
#include "memory_manager.h"
#include <cassert>

namespace L0 {

xe_result_t hostMemAlloc(xe_host_mem_alloc_flag_t flags,
                         size_t size,
                         size_t alignment,
                         void **ptr) {

    *ptr = globalMemoryManager->allocateHostMemory(size, alignment);
    assert(*ptr);

    return XE_RESULT_SUCCESS;
}

xe_result_t ipcCloseMemHandle(const void *ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t ipcGetMemHandle(const void *ptr,
                            xe_ipc_mem_handle_t *pIpcHandle) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t ipcOpenMemHandle(xe_device_handle_t hDevice,
                             xe_ipc_mem_handle_t handle,
                             xe_ipc_memory_flag_t flags,
                             void **ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t memAlloc(xe_device_handle_t hDevice,
                     xe_device_mem_alloc_flag_t flags,
                     size_t size,
                     size_t alignment,
                     void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    assert(globalMemoryManager);

    auto allocation = globalMemoryManager->allocateManagedMemory(device, size, alignment);
    assert(allocation);
    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

xe_result_t memFree(const void *ptr) {
    assert(globalMemoryManager);
    globalMemoryManager->freeMemory(ptr);

    return XE_RESULT_SUCCESS;
}

xe_result_t memGetAddressRange(const void *ptr,
                               void **pBase,
                               size_t *pSize) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t memGetProperties(const void *ptr,
                             xe_memory_allocation_properties_t *pMemProperties) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t sharedMemAlloc(xe_device_handle_t hDevice,
                           xe_device_mem_alloc_flag_t device_flags,
                           xe_host_mem_alloc_flag_t host_flags,
                           size_t size,
                           size_t alignment,
                           void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    assert(globalMemoryManager);

    auto allocation = globalMemoryManager->allocateManagedMemory(device, size, alignment);
    assert(allocation);
    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

} // namespace L0