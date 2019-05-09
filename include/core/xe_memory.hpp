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
* @file xe_memory.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/memory.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_MEMORY_HPP
#define _XE_MEMORY_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported device memory allocation flags
    enum class device_mem_alloc_flag_t
    {
        DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
        BIAS_CACHED = XE_BIT( 0 ),                      ///< device should cache allocation
        BIAS_UNCACHED = XE_BIT( 1 ),                    ///< device should not cache allocation (UC)

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported host memory allocation flags
    enum class host_mem_alloc_flag_t
    {
        DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
        BIAS_CACHED = XE_BIT( 0 ),                      ///< host should cache allocation
        BIAS_UNCACHED = XE_BIT( 1 ),                    ///< host should not cache allocation (UC)
        BIAS_WRITE_COMBINED = XE_BIT( 2 ),              ///< host memory should be allocated write-combined (WC)

    };

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
    ///     - void*: pointer to shared allocation
    /// 
    /// @throws result_t
    inline void*
    SharedMemAlloc(
        Device* hDevice,                                ///< [in] handle of the device
        device_mem_alloc_flag_t device_flags,           ///< [in] flags specifying additional device allocation controls
        host_mem_alloc_flag_t host_flags,               ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        );

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
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    inline void*
    DeviceMemAlloc(
        Device* hDevice,                                ///< [in] handle of the device
        device_mem_alloc_flag_t flags,                  ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        );

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
    ///     - void*: pointer to host allocation
    /// 
    /// @throws result_t
    inline void*
    HostMemAlloc(
        host_mem_alloc_flag_t flags,                    ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Frees allocated host memory, device memory, or shared memory
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the memory before it is freed
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this memory
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFree**
    ///     - **cudaFreeHost**
    /// 
    /// @throws result_t
    inline void
    MemFree(
        const void* ptr                                 ///< [in] pointer to memory to free
        );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief API version of ::memory_allocation_properties_t
    enum class memory_allocation_properties_version_t
    {
        CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Memory allocation type
    enum class memory_type_t
    {
        UNKNOWN = 0,                                    ///< the memory pointed to is of unknown type
        HOST,                                           ///< the memory pointed to is a host allocation
        DEVICE,                                         ///< the memory pointed to is a device allocation
        SHARED,                                         ///< the memory pointed to is a shared ownership allocation

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Memory allocation properties queried using ::MemGetProperties
    struct memory_allocation_properties_t
    {
        memory_allocation_properties_version_t version = memory_allocation_properties_version_t::CURRENT;   ///< [in] ::MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
        memory_type_t type;                             ///< [out] Type of allocated memory
        Device* device;                                 ///< [out] Device handle associated with this allocation (optional)
        uint64_t id;                                    ///< [out] Identifier for this allocation

    };

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
    ///     - memory_allocation_properties_t: Query result for memory allocation properties
    /// 
    /// @throws result_t
    inline memory_allocation_properties_t
    MemGetProperties(
        const void* ptr                                 ///< [in] Pointer to query
        );

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
    /// @throws result_t
    inline void
    MemGetAddressRange(
        const void* ptr,                                ///< [in] Pointer to query
        void** pBase = nullptr,                         ///< [in,out][optional] base address of the allocation
        size_t* pSize = nullptr                         ///< [in,out][optional] size of the allocation
        );

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
    ///     - ipc_mem_handle_t: Returned IPC memory handle
    /// 
    /// @throws result_t
    inline ipc_mem_handle_t
    IpcGetMemHandle(
        const void* ptr                                 ///< [in] Pointer to the device memory allocation
        );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported IPC memory flags
    enum class ipc_memory_flag_t
    {
        NONE = 0,                                       ///< No special flags

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
    ///        process
    /// 
    /// @details
    ///     - Takes an IPC memory handle from a sending process and associates it
    ///       with a device pointer usable in this process.
    ///     - The device pointer in this process should not be freed with ::MemFree,
    ///       but rather with ::IpcCloseMemHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcOpenMemHandle**
    /// 
    /// @returns
    ///     - void*: pointer to device allocation in this process
    /// 
    /// @throws result_t
    inline void*
    IpcOpenMemHandle(
        Device* hDevice,                                ///< [in] handle of the device to associate with the IPC memory handle
        ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
        ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
        );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC memory handle in a receiving process
    /// 
    /// @details
    ///     - Closes an IPC memory handle by unmapping memory that was opened in
    ///       this process using ::IpcOpenMemHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcCloseMemHandle**
    /// 
    /// @throws result_t
    inline void
    IpcCloseMemHandle(
        const void* ptr                                 ///< [in] pointer to device allocation in this process
        );

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_MEMORY_HPP
