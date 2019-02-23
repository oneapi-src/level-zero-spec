#pragma once
#include "xe_all.h"
#include "driver.h"

namespace xe {

xe_result_t createMemAllocator(xe_mem_allocator_handle_t *phMemAllocHandle);

xe_result_t hostMemAlloc(xe_mem_allocator_handle_t hMemAllocHandle,
                         xe_host_mem_alloc_flag_t flags,
                         size_t size,
                         size_t alignment,
                         void **ptr);

xe_result_t ipcCloseMemHandle(xe_mem_allocator_handle_t hMemAllocHandle,
                              const void *ptr);

xe_result_t ipcGetMemHandle(xe_mem_allocator_handle_t hMemAllocHandle,
                            const void *ptr,
                            xe_ipc_mem_handle_t *pIpcHandle);

xe_result_t ipcOpenMemHandle(xe_mem_allocator_handle_t hMemAllocHandle,
                             xe_device_handle_t hDevice,
                             xe_ipc_mem_handle_t handle,
                             xe_ipc_memory_flag_t flags,
                             void **ptr);

xe_result_t memAlloc(xe_mem_allocator_handle_t hMemAllocHandle,
                     xe_device_handle_t hDevice,
                     xe_device_mem_alloc_flag_t flags,
                     size_t size,
                     size_t alignment,
                     void **ptr);

xe_result_t memAllocatorDestroy(xe_mem_allocator_handle_t hMemAllocHandle);

xe_result_t memFree(xe_mem_allocator_handle_t hMemAllocHandle,
                    const void *ptr);

xe_result_t memGetAddressRange(xe_mem_allocator_handle_t hMemAllocHandle,
                               const void *ptr,
                               void **pBase,
                               size_t *pSize);

xe_result_t memGetProperty(xe_mem_allocator_handle_t hMemAllocHandle,
                           const void *ptr,
                           xe_memory_property_t property,
                           void *pValue);

xe_result_t sharedMemAlloc(xe_mem_allocator_handle_t hMemAllocHandle,
                           xe_device_handle_t hDevice,
                           xe_device_mem_alloc_flag_t device_flags,
                           xe_host_mem_alloc_flag_t host_flags,
                           size_t size,
                           size_t alignment,
                           void **ptr);

} // namespace xe