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
* @file xe_copy.h
*
* @brief Intel Xe Driver APIs for Copies
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/copy.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_COPY_H
#define _XE_COPY_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies host, device, or shared memory.
/// 
/// @details
///     - The memory pointed to by both srcptr and dstptr must be accessible by
///       the device on which the command list is created.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyBuffer**
///     - **clEnqueueReadBuffer**
///     - **clEnqueueWriteBuffer**
///     - **clEnqueueSVMMemcpy**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == srcptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
  xeCommandListEncodeMemoryCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size                                     ///< [in] size in bytes to copy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a image.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyImage**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
  xeCommandListEncodeImageCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage                     ///< [in] handle of source image to copy from
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Region descriptor
typedef struct _xe_image_region_t
{
    size_t offset;                                  ///< [in] offset in bytes from base
    size_t size;                                    ///< [in] size in bytes from base+offset

} xe_image_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region of a image to another image.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
  xeCommandListEncodeImageCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies from a image to device or shared memory.
/// 
/// @details
///     - The memory pointed to by dstptr must be accessible by the device on
///       which the command list is created.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueReadImage
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
  xeCommandListEncodeImageCopyToMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies to a image from device or shared memory.
/// 
/// @details
///     - The memory pointed to by srcptr must be accessible by the device on
///       which the command list is created.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueWriteImage
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == srcptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
  xeCommandListEncodeImageCopyFromMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    void* srcptr                                    ///< [in] pointer to source memory to copy from
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Asynchronously prefetches shared memory to the device associated with
///        the specified command list
/// 
/// @details
///     - This is a hint to improve performance only and is not required for
///       correctness.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - Prefetch to Host and Peer Device are not supported.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - cudaMemPrefetchAsync
///     - clEnqueueSVMMigrateMem
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
  xeCommandListEncodeMemoryPrefetch(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory region to prefetch
    size_t count                                    ///< [in] size in bytes of the memory region to prefetch
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory advice hints
typedef enum _xe_memory_advice_t
{
    XE_MEMORY_ADVICE_SET_READ_MOSTLY = 0,           ///< hint that memory will be read from frequently and written to rarely
    XE_MEMORY_ADVICE_CLEAR_READ_MOSTLY,             ///< removes the affect of ::XE_MEMORY_ADVICE_SET_READ_MOSTLY
    XE_MEMORY_ADVICE_SET_PREFERRED_LOCATION,        ///< hint that the preferred memory location is the specified device
    XE_MEMORY_ADVICE_CLEAR_PREFERRED_LOCATION,      ///< removes the affect of ::XE_MEMORY_ADVICE_SET_PREFERRED_LOCATION
    XE_MEMORY_ADVICE_SET_ACCESSED_BY,               ///< hint that memory will be accessed by the specified device
    XE_MEMORY_ADVICE_CLEAR_ACCESSED_BY,             ///< removes the affect of ::XE_MEMORY_ADVICE_SET_ACCESSED_BY
    XE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY,         ///< hints that memory will mostly be accessed non-atomically
    XE_MEMORY_ADVICE_CLEAR_NON_ATOMIC_MOSTLY,       ///< removes the affect of ::XE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
    XE_MEMORY_ADVICE_BIAS_CACHED,                   ///< hints that memory should be cached
    XE_MEMORY_ADVICE_BIAS_UNCACHED,                 ///< hints that memory should be not be cached

} xe_memory_advice_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a shared memory range
/// 
/// @details
///     - Memory advice is a performance hint only; applications are not
///       required to use this for functionality.
///     - Memory advice can be used to override driver heuristics to explicitly
///       control shared memory behavior.
///     - Not all memory advice may be supported by all devices.
///     - Memory advice may only be supported at a device-specific granularity,
///       such as at a page boundary. In this case, the memory range may be
///       expanded such that the start and end of the range satisfy granularity
///       requirements.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaMemAdvise**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDevice
///         + nullptr == ptr
///         + invalid value for advice
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
  xeCommandListEncodeMemAdvise(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_COPY_H
