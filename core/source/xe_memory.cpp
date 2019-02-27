/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
* The source code contained or described herein and all documents related to the  
* source code ("Material") are owned by Intel Corporation or its suppliers or  
* licensors. Title to the Material remains with Intel Corporation or its suppliers  
* and licensors. The Material contains trade secrets and proprietary and confidential  
* information of Intel or its suppliers and licensors. The Material is protected by  
* worldwide copyright and trade secret laws and treaty provisions. No part of the  
* Material may be used, copied, reproduced, modified, published, uploaded, posted  
* transmitted, distributed, or disclosed in any way without Intel's prior express  
* written permission.  
*
* No license under any patent, copyright, trade secret or other intellectual  
* property right is granted to or conferred upon you by disclosure or delivery  
* of the Materials, either expressly, by implication, inducement, estoppel  
* or otherwise. Any license under such intellectual property rights must be  
* express and approved by Intel in writing.  
* @endcond
*
* @file xe_memory.cpp
*
* @brief Intel Xe Driver APIs for Memory
*
* DO NOT EDIT: generated from /scripts/<type>/memory.yml
*
******************************************************************************/
#include "../include/xe_memory.h"
#include "memory.h"

#include <exception>    // @todo: move to common and/or precompiled header
#include <new>

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an handle to a memory allocator
/// 
/// @details
///     - Memory allocators store information about allocations.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == phMemAllocHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {9f40961e245036a4f5bae21b30b0fe1eff983d3e3a2c375fa0e5c2ab9e9139f8}
///
__xedllexport xe_result_t __xecall
  xeCreateMemAllocator(
    xe_mem_allocator_handle_t* phMemAllocHandle     ///< [out] Returned memory allocator handle
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == phMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::createMemAllocator(phMemAllocHandle);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a memory allocator
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing any memory allocations associated with this
///       allocator before it is deleted.
///     - The implementation of this function will immediately free all memory
///       allocations associated with this allocator.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {a2eb24e400146e03f62a0c76e948d2746c332fa8aa4fa3d9927bce3e413a5c84}
///
__xedllexport xe_result_t __xecall
  xeMemAllocatorDestroy(
    xe_mem_allocator_handle_t hMemAllocHandle       ///< [in] handle of memory allocator to destroy
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::memAllocatorDestroy(hMemAllocHandle);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaMallocManaged**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == hDevice
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///
/// @hash {8e4c3077c3008f398c65e52226a9ed7ab31d689ef7666070143cd630c14449a8}
///
__xedllexport xe_result_t __xecall
  xeSharedMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::sharedMemAlloc(hMemAllocHandle, hDevice, device_flags, host_flags, size, alignment, ptr);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device
/// 
/// @details
///     - A device allocation is owned by a specific device.
///     - In general, a device allocation may only be accessed by the device
///       that owns it.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaMalloc**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == hDevice
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///
/// @hash {0c3d522d0293cd5605447882683b2164912ede21c5b24b68e2b486f7a7a32bdc}
///
__xedllexport xe_result_t __xecall
  xeMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::memAlloc(hMemAllocHandle, hDevice, flags, size, alignment, ptr);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory
/// 
/// @details
///     - A host allocation is owned by the host process.
///     - Host allocations are accessible by the host and all devices.
///     - Host allocations are frequently used a staging areas to transfer data
///       to or from devices.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaHostAlloc**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///
/// @hash {f2ceab5a53b2c88ef4d17b001d09cf385937bfef71f155e4844751ac93f1bf4f}
///
__xedllexport xe_result_t __xecall
  xeHostMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::hostMemAlloc(hMemAllocHandle, flags, size, alignment, ptr);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the memory before it is freed
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this memory
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFree**
///     - **cudaFreeHost**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {6995e132992157fdad5d71e539141cbc0908cfd0a01322624ba3e9d1ffd763fd}
///
__xedllexport xe_result_t __xecall
  xeMemFree(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::memFree(hMemAllocHandle, ptr);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a property of an allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuPointerGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == ptr
///         + nullptr == pValue
///         + invalid property
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {ca0bc083b4f2907561e61a65f87ffa3527cf21e340760ef655b0905f766be102}
///
__xedllexport xe_result_t __xecall
  xeMemGetProperty(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_property_t property,                  ///< [in] Property of the allocation to query
    void* pValue                                    ///< [out] Value of the queried property
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pValue ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::memGetProperty(hMemAllocHandle, ptr, property, pValue);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the base address and/or size of an allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuMemGetAddressRange**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == ptr
///         + nullptr == pBase
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {674ca4659d3c7a33527c6aa498eabdf2a8532d1ecc1707e9374ecf5ebf5219ef}
///
__xedllexport xe_result_t __xecall
  xeMemGetAddressRange(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [out] Returned base address of the allocation (optional)
    size_t* pSize                                   ///< [out] Returned size of the allocation (optional)
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pBase ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pSize ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::memGetAddressRange(hMemAllocHandle, ptr, pBase, pSize);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle for the specified allocation in the
///        sending process
/// 
/// @details
///     - Takes a pointer to the base of a device memory allocation and exports
///       it for use in another process.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcGetMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == ptr
///         + nullptr == pIpcHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b05b49f5ce22e128e73ca066bf16b7d9b0d6d5c7c360c9041811c0db939aeaba}
///
__xedllexport xe_result_t __xecall
  xeIpcGetMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pIpcHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::ipcGetMemHandle(hMemAllocHandle, ptr, pIpcHandle);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
///        process
/// 
/// @details
///     - Takes an IPC memory handle from a sending process and associates it
///       with a device pointer usable in this process.
///     - The device pointer in this process should not be freed with
///       ::xeMemFree, but rather with ::xeIpcCloseMemHandle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcOpenMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == hDevice
///         + nullptr == handle
///         + nullptr == ptr
///         + invalid flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b81880e4766e54a7ec95bc1c35670d6197d46e5ac553160316faad314f7a59ba}
///
__xedllexport xe_result_t __xecall
  xeIpcOpenMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == handle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::ipcOpenMemHandle(hMemAllocHandle, hDevice, handle, flags, ptr);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle in a receiving process
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::xeIpcOpenMemHandle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcCloseMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hMemAllocHandle
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {393624ba03af311b28cec458da8b4789d05f7d3754dcf393c3c6dc9bb063bd45}
///
__xedllexport xe_result_t __xecall
  xeIpcCloseMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hMemAllocHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::ipcCloseMemHandle(hMemAllocHandle, ptr);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

