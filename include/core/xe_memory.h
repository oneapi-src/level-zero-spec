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
* @brief Intel Xe Level-Zero APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/memory.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_MEMORY_H
#define _XE_MEMORY_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported device memory allocation flags
typedef enum _xe_device_mem_alloc_flag_t
{
    XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT = 0,           ///< implicit default behavior; uses driver-based heuristics
    XE_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED = XE_BIT( 0 ), ///< device should cache allocation
    XE_DEVICE_MEM_ALLOC_FLAG_BIAS_UNCACHED = XE_BIT( 1 ),   ///< device should not cache allocation (UC)

} xe_device_mem_alloc_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported host memory allocation flags
typedef enum _xe_host_mem_alloc_flag_t
{
    XE_HOST_MEM_ALLOC_FLAG_DEFAULT = 0,             ///< implicit default behavior; uses driver-based heuristics
    XE_HOST_MEM_ALLOC_FLAG_BIAS_CACHED = XE_BIT( 0 ),   ///< host should cache allocation
    XE_HOST_MEM_ALLOC_FLAG_BIAS_UNCACHED = XE_BIT( 1 ), ///< host should not cache allocation (UC)
    XE_HOST_MEM_ALLOC_FLAG_BIAS_WRITE_COMBINED = XE_BIT( 2 ),   ///< host memory should be allocated write-combined (WC)

} xe_host_mem_alloc_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - By default, shared allocations are visible to all devices in the
///       device group.
///     - A shared allocation can be restricted to be only visible to the host
///       and a single device by specifying a single device handle.
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == hDevice
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceGroupAllocSharedMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of a device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::xeDeviceGroupGetMemoryProperties
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to shared allocation
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == hDevice
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceGroupAllocDeviceMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::xeDeviceGroupGetMemoryProperties
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to device allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory
/// 
/// @details
///     - A host allocation is owned by the host process.
///     - Host allocations are accessible by the host and all devices within the
///       device group.
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pptr
///         + unsupported allocation size
///         + unsupported alignment
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceGroupAllocHostMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to host allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory
/// 
/// @details
///     - The application is responsible for making sure the device is not
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupFreeMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    void* ptr                                       ///< [in][release] pointer to memory to free
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_memory_allocation_properties_t
typedef enum _xe_memory_allocation_properties_version_t
{
    XE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xe_memory_allocation_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation type
typedef enum _xe_memory_type_t
{
    XE_MEMORY_TYPE_UNKNOWN = 0,                     ///< the memory pointed to is of unknown type
    XE_MEMORY_TYPE_HOST,                            ///< the memory pointed to is a host allocation
    XE_MEMORY_TYPE_DEVICE,                          ///< the memory pointed to is a device allocation
    XE_MEMORY_TYPE_SHARED,                          ///< the memory pointed to is a shared ownership allocation

} xe_memory_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation properties queried using
///        ::xeDeviceGroupGetMemProperties
typedef struct _xe_memory_allocation_properties_t
{
    xe_memory_allocation_properties_version_t version;  ///< [in] ::XE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
    xe_memory_type_t type;                          ///< [out] type of allocated memory
    uint64_t id;                                    ///< [out] identifier for this allocation

} xe_memory_allocation_properties_t;

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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///         + nullptr == pMemProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] memory pointer to query
    xe_memory_allocation_properties_t* pMemProperties,  ///< [out] query result for memory allocation properties
    xe_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemAddressRange(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///         + nullptr == pIpcHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported IPC memory flags
typedef enum _xe_ipc_memory_flag_t
{
    XE_IPC_MEMORY_FLAG_NONE = 0,                    ///< No special flags

} xe_ipc_memory_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
///        process
/// 
/// @details
///     - Takes an IPC memory handle from a sending process and associates it
///       with a device pointer usable in this process.
///     - The device pointer in this process should not be freed with
///       ::xeDeviceGroupFreeMem, but rather with
///       ::xeDeviceGroupCloseMemIpcHandle.
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == hDevice
///         + nullptr == handle
///         + nullptr == pptr
///         + invalid flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupOpenMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** pptr                                     ///< [out] pointer to device allocation in this process
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle in a receiving process
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::xeDeviceGroupOpenMemIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same pointer.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcCloseMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupCloseMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr                                 ///< [in][release] pointer to device allocation in this process
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_MEMORY_H
