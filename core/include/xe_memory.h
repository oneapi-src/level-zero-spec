/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
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
*
* @file xe_memory.h
*
* @brief Intel Xe Driver APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/memory.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_MEMORY_H
#define _XE_MEMORY_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported device memory allocation flags
typedef enum _xe_device_mem_alloc_flags_t
{
    XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT = 0,           ///< implicit default behavior; uses driver-based heuristics
    XE_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED = XE_BIT( 0 ), ///< device should cache allocation
    XE_DEVICE_MEM_ALLOC_FLAG_BIAS_UNCACHED = XE_BIT( 1 ),   ///< device should not cache allocation (UC)

} xe_device_mem_alloc_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported host memory allocation flags
typedef enum _xe_host_mem_alloc_flags_t
{
    XE_HOST_MEM_ALLOC_FLAG_DEFAULT = 0,             ///< implicit default behavior; uses driver-based heuristics
    XE_HOST_MEM_ALLOC_FLAG_BIAS_CACHED = XE_BIT( 0 ),   ///< host should cache allocation
    XE_HOST_MEM_ALLOC_FLAG_BIAS_UNCACHED = XE_BIT( 1 ), ///< host should not cache allocation (UC)
    XE_HOST_MEM_ALLOC_FLAG_BIAS_WRITE_COMBINED = XE_BIT( 2 ),   ///< host memory should be allocated write-combined (WC)

} xe_host_mem_alloc_flags_t;

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + unsupported allocation size
///         + nullptr for ptr
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeSharedMemAlloc(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flags_t device_flags,       ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flags_t host_flags,           ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + unsupported allocation size
///         + nullptr for ptr
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeMemAlloc(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flags_t flags,              ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + unsupported allocation size
///         + nullptr for ptr
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeHostMemAlloc(
    xe_host_mem_alloc_flags_t flags,                ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid pointer
xe_result_t __xecall
  xeMemFree(
    const void* ptr                                 ///< [in] pointer to memory to free
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation type
typedef enum _xe_memory_type_t
{
    XE_MEMORY_TYPE_UNKNOWN = 0,                     ///< the memory pointed to was not allocated by Xe
    XE_MEMORY_TYPE_HOST,                            ///< the memory pointed to is a host allocation
    XE_MEMORY_TYPE_DEVICE,                          ///< the memory pointed to is a device allocation
    XE_MEMORY_TYPE_SHARED,                          ///< the memory pointed to is a shared ownership allocation

} xe_memory_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory allocation query properties
typedef enum _xe_memory_property_t
{
    XE_MEMORY_TYPE = 0,                             ///< see ::xe_memory_type_t

} xe_memory_property_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a property of an allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaPointerGetAttributes**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid pointer
///         + invalid property
xe_result_t __xecall
  xeMemGetProperty(
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_property_t property,                  ///< [in] Property of the allocation to query
    uint32_t* value                                 ///< [out] Value of the queried property
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid pointer
xe_result_t __xecall
  xeIpcGetMemHandle(
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported IPC memory flags
typedef enum _xe_ipc_memory_flags_t
{
    XE_IPC_MEMORY_FLAGS_NONE = 0,                   ///< No special flags

} xe_ipc_memory_flags_t;

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid handle for handle
///         + invalid flags
///         + nullptr for ptr
xe_result_t __xecall
  xeIpcOpenMemHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid ptr
xe_result_t __xecall
  xeIpcCloseMemHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    const void* ptr                                 ///< [in] pointer to memory to free
    );

#endif // _XE_MEMORY_H
