#pragma once
#include "xe_api.h"
#include "driver.h"

namespace L0 {

xe_result_t hostMemAlloc(xe_host_mem_alloc_flag_t flags, size_t size, size_t alignment, void **ptr);

xe_result_t ipcCloseMemHandle(const void *ptr);

xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle);

xe_result_t ipcOpenMemHandle(xe_device_handle_t hDevice, xe_ipc_mem_handle_t handle,
                             xe_ipc_memory_flag_t flags, void **ptr);

xe_result_t deviceMemAlloc(xe_device_handle_t hDevice, xe_device_mem_alloc_flag_t flags, size_t size,
                     size_t alignment, void **ptr);

xe_result_t memFree(const void *ptr);

xe_result_t memGetAddressRange(const void *ptr, void **pBase, size_t *pSize);

xe_result_t memGetProperties(const void *ptr, xe_memory_allocation_properties_t *pMemProperties);

xe_result_t sharedMemAlloc(xe_device_handle_t hDevice, xe_device_mem_alloc_flag_t device_flags,
                           xe_host_mem_alloc_flag_t host_flags, size_t size, size_t alignment,
                           void **ptr);

} // namespace L0