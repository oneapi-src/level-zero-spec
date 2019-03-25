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
* @brief Intel Xe Level-Zero APIs for Memory
*
* DO NOT EDIT: generated from /scripts/core/memory.yml
*
******************************************************************************/
#if defined(XE_CPP)
#include "../include/xe_memory.hpp"
#else
#include "../include/xe_memory.h"
#endif
#if !defined(XE_NULLDRV)
#include "memory.h"
#endif

#include <exception>    // @todo: move to common and/or precompiled header
#include <new>

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - The application may call this function from simultaneous threads.
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
///         + nullptr == hDevice
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///
/// @hash {06027dab60bcf973738603e2570f5473a33c2470844fdf37848462286595f5bd}
///
__xedllexport xe_result_t __xecall
xeSharedMemAlloc(
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
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::sharedMemAlloc(hDevice, device_flags, host_flags, size, alignment, ptr);
#endif
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
///         + nullptr == hDevice
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///
/// @hash {00c7d568c1470ecc7b25b7bb8bfa87e9428b9a4023484c53ee46e6632e24d16d}
///
__xedllexport xe_result_t __xecall
xeMemAlloc(
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
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::memAlloc(hDevice, flags, size, alignment, ptr);
#endif
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
///     - Host allocations are frequently used as staging areas to transfer data
///       to or from devices.
///     - The application may call this function from simultaneous threads.
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
///         + nullptr == ptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///
/// @hash {1d6e17bf2c1a28348c73f66fed634fa8611c4ba0a55d2bbd3b66cd0ccd43d135}
///
__xedllexport xe_result_t __xecall
xeHostMemAlloc(
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
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::hostMemAlloc(flags, size, alignment, ptr);
#endif
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
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {f31f2669e6b64c981d8d808f22b3861f67eeda5515d908b5ef3f68fa0b978a76}
///
__xedllexport xe_result_t __xecall
xeMemFree(
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::memFree(ptr);
#endif
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
/// @brief Retrieves attributes of a memory allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
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
///         + nullptr == ptr
///         + nullptr == pMemProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {84370f3c7760a2035de32f9afeb5b566ebb950ce455fe2ecdb99e5bcf7765280}
///
__xedllexport xe_result_t __xecall
xeMemGetProperties(
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pMemProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::memGetProperties(ptr, pMemProperties);
#endif
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
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {fd71df4f1ab1c85ed6c2aa71d5f7610e183f911da4b91620e510db3afe3e8a7f}
///
__xedllexport xe_result_t __xecall
xeMemGetAddressRange(
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::memGetAddressRange(ptr, pBase, pSize);
#endif
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
///         + nullptr == ptr
///         + nullptr == pIpcHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {585dead12b324b42d61a826c27087bff3757fae42fc4330167bdf00f40ebdab3}
///
__xedllexport xe_result_t __xecall
xeIpcGetMemHandle(
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
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pIpcHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::ipcGetMemHandle(ptr, pIpcHandle);
#endif
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
///         + nullptr == hDevice
///         + nullptr == handle
///         + nullptr == ptr
///         + invalid flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {0e37c65a263c2417b2dd960fd35019700d1242246e4c1f1a2efb384c5f2dbf44}
///
__xedllexport xe_result_t __xecall
xeIpcOpenMemHandle(
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
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == handle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::ipcOpenMemHandle(hDevice, handle, flags, ptr);
#endif
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
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {426a1b963393017daf05d12da2351f29b3e011d7c52ca1e498c3bc3222e9ceca}
///
__xedllexport xe_result_t __xecall
xeIpcCloseMemHandle(
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::ipcCloseMemHandle(ptr);
#endif
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

