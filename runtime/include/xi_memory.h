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
* @file xi_memory.h
*
* @brief Intel Xi Runtime APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/memory.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_MEMORY_H
#define _XI_MEMORY_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices. @todo Comprehend multi-tile.
/// @remarks
///   _Analogues_
///     - **cudaMallocManaged**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hContext
///     + invalid handle for hDevice
///     + unsupported allocation size
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiSharedMemAlloc(
    const xi_context_handle_t hContext,             ///< [in] handle of the context
    const xi_device_handle_t hDevice,               ///< [in] handle of the device
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device
/// @details
///     - A device allocation is owned by a specific device. In general, a
///       device allocation may only be accessed by the device that owns it.
/// @remarks
///   _Analogues_
///     - **cudaMalloc**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hContext
///     + invalid handle for hDevice
///     + unsupported allocation size
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiMemAlloc(
    const xi_context_handle_t hContext,             ///< [in] handle of the context
    const xi_device_handle_t hDevice,               ///< [in] handle of the device
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported host allocation flags
typedef enum _xi_host_mem_alloc_flags_t
{
    XI_HOST_MEM_ALLOC_DEFAULT = 0,                  ///< implicit default behavior; uses driver-based heuristics
    XI_HOST_MEM_ALLOC_WRITE_COMBINED = XI_BIT( 0 ), ///< allocate the host memory as write-combined (WC)

} xi_host_mem_alloc_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory
/// @details
///     - A host allocation is owned by the host process. Host allocations are
///       accessible by the host and all devices. Host allocations are
///       frequently used a staging areas to transfer data to or from devices.
/// @remarks
///   _Analogues_
///     - **cudaHostAlloc**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hContext
///     + invalid handle for hDevice
///     + unsupported allocation size
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiHostMemAlloc(
    const xi_context_handle_t hContext,             ///< [in] handle of the context
    xi_host_mem_alloc_flags_t flags,                ///< [in] flags controlling specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory
/// @details
///     - @todo Should the pointer passed to the ::xiMemFree function be const
///       or non-const?
/// @remarks
///   _Analogues_
///     - **cudaFree**
///     - **cudaFreeHost**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hContext
///     + invalid pointer
xi_result_t __xicall
  xiMemFree(
    const xi_context_handle_t hContext,             ///< [in] handle of the context
    const void* ptr                                 ///< [in] pointer to memory to free
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory advice hints
typedef enum _xi_memory_advice_t
{
    XI_MEMORY_ADVICE_NONE = 0,                      ///< @todo

} xi_memory_advice_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a shared memory range
/// @details
///     - Memory advice can be used to override driver heuristics to explicitly
///       control shared memory behavior. @todo likely will snap to page
///       boundaries @todo which memory advise hints could/should we support?
/// @remarks
///   _Analogues_
///     - **cudaMemAdvise**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hContext
///     + invalid handle for hDevice
///     + invalid pointer
///     + invalid advice
xi_result_t __xicall
  xiMemAdvise(
    const xi_context_handle_t hContext,             ///< [in] handle of the context
    const xi_device_handle_t hDevice,               ///< [in] handle of the device to apply the advice to
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xi_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    );

#endif // _XI_MEMORY_H
