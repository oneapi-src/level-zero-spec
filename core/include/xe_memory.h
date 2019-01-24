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
/// @brief @todo Ben: need a kernel property to indicate indirect shared memory
///        access
#define XE_KERNEL_PROPERTY_INDIRECT_SHARED_ACCESS  0

///////////////////////////////////////////////////////////////////////////////
/// @brief @todo Ben: possible kernel property to indicate indirect device memory
///        access?
#define XE_KERNEL_PROPERTY_INDIRECT_DEVICE_ACCESS  0

///////////////////////////////////////////////////////////////////////////////
/// @brief @todo Ben: possible kernel property to indicate indirect host memory
///        access?
#define XE_KERNEL_PROPERTY_INDIRECT_HOST_ACCESS  0

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - @todo Ben: comprehend multi-tile?
/// 
/// @remarks
///   _Analogues_
///     - **cudaMallocManaged**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + unsupported allocation size
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeSharedMemAlloc(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device
/// 
/// @details
///     - A device allocation is owned by a specific device. In general, a
///       device allocation may only be accessed by the device that owns it.
/// 
/// @remarks
///   _Analogues_
///     - **cudaMalloc**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + unsupported allocation size
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeMemAlloc(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported host allocation flags
typedef enum _xe_host_mem_alloc_flags_t
{
    XE_HOST_MEM_ALLOC_DEFAULT = 0,                  ///< implicit default behavior; uses driver-based heuristics
    XE_HOST_MEM_ALLOC_WRITE_COMBINED = XE_BIT( 0 ), ///< allocate the host memory as write-combined (WC)

} xe_host_mem_alloc_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory
/// 
/// @details
///     - A host allocation is owned by the host process. Host allocations are
///       accessible by the host and all devices. Host allocations are
///       frequently used a staging areas to transfer data to or from devices.
/// 
/// @remarks
///   _Analogues_
///     - **cudaHostAlloc**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + unsupported allocation size
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeHostMemAlloc(
    xe_host_mem_alloc_flags_t flags,                ///< [in] flags controlling specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory
/// 
/// @details
///     - @todo Ben: Should the pointer passed to the ::xeMemFree function be
///       const or non-const?
/// 
/// @remarks
///   _Analogues_
///     - **cudaFree**
///     - **cudaFreeHost**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
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
///     - @todo Ben: do we need to support additional properties: base addr,
///       size, etc? @todo Ben: do we need to support querying the associated
///       device? @todo Ben: should we return all attributes as a (versioned)
///       struct instead?
/// 
/// @remarks
///   _Analogues_
///     - **cudaPointerGetAttributes**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
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
/// @brief Supported memory advice hints
typedef enum _xe_memory_advice_t
{
    XE_MEMORY_ADVICE_TBD = 0,                       ///< @todo Ben: which memory advice hints could/should we support?

} xe_memory_advice_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a shared memory range
/// 
/// @details
///     - Memory advice can be used to override driver heuristics to explicitly
///       control shared memory behavior.
///     - @todo Ben: likely will snap to page boundaries
/// 
/// @remarks
///   _Analogues_
///     - **cudaMemAdvise**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid pointer
///         + invalid advice
xe_result_t __xecall
  xeMemAdvise(
    const xe_device_handle_t hDevice,               ///< [in] handle of the device to apply the advice to
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    );

#endif // _XE_MEMORY_H
