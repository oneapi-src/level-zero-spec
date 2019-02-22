#pragma once
#include "xe_all.h"

namespace xe {

xe_result_t __xecall
xeMemFree(
    xe_mem_allocator_handle_t hMemAllocHandle, ///< [in] handle of memory allocator for this allocation
    const void *ptr                            ///< [in] pointer to memory to free
);

xe_result_t __xecall
xeSharedMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle, ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                ///< [in] handle of the device
    xe_device_mem_alloc_flag_t device_flags,   ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flag_t host_flags,       ///< [in] flags specifying additional host allocation controls
    size_t size,                               ///< [in] size in bytes to allocate
    size_t alignment,                          ///< [in] minimum alignment in bytes for the allocation
    void **ptr                                 ///< [out] pointer to shared allocation
);

} // namespace xe