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
/// @brief Handle to a memory allocator
typedef struct _xe_mem_allocator_handle_t *xe_mem_allocator_handle_t;

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr for pMemAllocHandle
xe_result_t __xecall
  xeCreateMemAllocator(
    xe_mem_allocator_handle_t* phMemAllocHandle     ///< [out] Returned memory allocator handle
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hMemAllocHandle
xe_result_t __xecall
  xeMemAllocatorDestroy(
    xe_mem_allocator_handle_t hMemAllocHandle       ///< [in] handle of memory allocator to destroy
    );

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
///         + invalid handle for hMemAllocHandle
///         + invalid handle for hDevice
///         + unsupported allocation size
///         + unsupported alignment
///         + nullptr for ptr
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeSharedMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flags_t device_flags,       ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flags_t host_flags,           ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
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
///         + invalid handle for hMemAllocHandle
///         + invalid handle for hDevice
///         + unsupported allocation size
///         + unsupported alignment
///         + nullptr for ptr
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flags_t flags,              ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
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
///         + invalid handle for hMemAllocHandle
///         + unsupported allocation size
///         + unsupported alignment
///         + nullptr for ptr
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeHostMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_host_mem_alloc_flags_t flags,                ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
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
///         + invalid handle for hMemAllocHandle
///         + invalid ptr
xe_result_t __xecall
  xeMemFree(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
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
    XE_MEMORY_TYPE = 0,                             ///< returns the type of allocated memory, see ::xe_memory_type_t

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
///     - **cuPointerGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hMemAllocHandle
///         + invalid ptr
///         + invalid property
///         + nullptr for pValue
xe_result_t __xecall
  xeMemGetProperty(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_property_t property,                  ///< [in] Property of the allocation to query
    void* pValue                                    ///< [out] Value of the queried property
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hMemAllocHandle
///         + invalid ptr
///         + nullptr for both pBase and pSize
xe_result_t __xecall
  xeMemGetAddressRange(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [out] Returned base address of the allocation (optional)
    size_t* pSize                                   ///< [out] Returned size of the allocation (optional)
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
///         + invalid handle for hMemAllocHandle
///         + invalid ptr
///         + nullptr for pIpcHandle
xe_result_t __xecall
  xeIpcGetMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
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
///         + invalid handle for hMemAllocHandle
///         + invalid handle for hDevice
///         + invalid handle for handle
///         + invalid flags
///         + nullptr for ptr
xe_result_t __xecall
  xeIpcOpenMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
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
///         + invalid handle for hMemAllocHandle
///         + invalid ptr
xe_result_t __xecall
  xeIpcCloseMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    );

#endif // _XE_MEMORY_H
