#include "device.h"
#include "graphics_allocation.h"
#include "memory.h"
#include "memory_manager.h"
#include <cassert>

//TODO: Need to exploit
struct _xe_mem_allocator_handle_t {
};

namespace xe {

xe_result_t createMemAllocator(xe_mem_allocator_handle_t *phMemAllocHandle) {
    *phMemAllocHandle = new _xe_mem_allocator_handle_t;
    return XE_RESULT_SUCCESS;
}

xe_result_t hostMemAlloc(xe_mem_allocator_handle_t hMemAllocHandle,
                         xe_host_mem_alloc_flag_t flags,
                         size_t size,
                         size_t alignment,
                         void **ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t ipcCloseMemHandle(xe_mem_allocator_handle_t hMemAllocHandle,
                              const void *ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t ipcGetMemHandle(xe_mem_allocator_handle_t hMemAllocHandle,
                            const void *ptr,
                            xe_ipc_mem_handle_t *pIpcHandle) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t ipcOpenMemHandle(xe_mem_allocator_handle_t hMemAllocHandle,
                             xe_device_handle_t hDevice,
                             xe_ipc_mem_handle_t handle,
                             xe_ipc_memory_flag_t flags,
                             void **ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t memAlloc(xe_mem_allocator_handle_t hMemAllocHandle,
                     xe_device_handle_t hDevice,
                     xe_device_mem_alloc_flag_t flags,
                     size_t size,
                     size_t alignment,
                     void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);

    auto allocation = memoryManager->allocateManagedMemory(size, alignment);
    assert(allocation);
    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

xe_result_t memAllocatorDestroy(xe_mem_allocator_handle_t hMemAllocHandle) {
    delete hMemAllocHandle;
    return XE_RESULT_SUCCESS;
}

xe_result_t memFree(xe_mem_allocator_handle_t hMemAllocHandle,
                    const void *ptr) {
    //TODO: Currently leaking memory.  Need to route to UnifiedMemoryManager
    return XE_RESULT_SUCCESS;
}

xe_result_t memGetAddressRange(xe_mem_allocator_handle_t hMemAllocHandle,
                               const void *ptr,
                               void **pBase,
                               size_t *pSize) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t memGetProperty(xe_mem_allocator_handle_t hMemAllocHandle,
                           const void *ptr,
                           xe_memory_property_t property,
                           void *pValue) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t sharedMemAlloc(xe_mem_allocator_handle_t hMemAllocHandle,
                           xe_device_handle_t hDevice,
                           xe_device_mem_alloc_flag_t device_flags,
                           xe_host_mem_alloc_flag_t host_flags,
                           size_t size,
                           size_t alignment,
                           void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);

    auto allocation = memoryManager->allocateManagedMemory(size, alignment);
    assert(allocation);
    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

} // namespace xe