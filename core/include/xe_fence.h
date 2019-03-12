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
* @file xe_fence.h
*
* @brief Intel Xe Driver APIs for Fence
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/fence.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_FENCE_H
#define _XE_FENCE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_fence_desc_t
typedef enum _xe_fence_desc_version_t
{
    XE_FENCE_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),///< version 1.0

} xe_fence_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported fence creation flags
typedef enum _xe_fence_flag_t
{
    XE_FENCE_FLAG_NONE = 0,                         ///< default behavior

} xe_fence_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fence descriptor
typedef struct _xe_fence_desc_t
{
    xe_fence_desc_version_t version;                ///< [in] ::XE_FENCE_DESC_VERSION_CURRENT
    xe_fence_flag_t flags;                          ///< [in] creation flags

} xe_fence_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a fence object on the device's command queue.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCreateFence**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandQueue
///         + nullptr == desc
///         + nullptr == phFence
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_FENCE_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__xedllport xe_result_t __xecall
  xeCommandQueueCreateFence(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a fence object.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the fence before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this fence
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkDestroyFence**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFence
///         + fence is enqueued in a command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
  xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a fence to be signaled.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkWaitForFences**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFence
///         + fence is not enqueued in a command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
__xedllport xe_result_t __xecall
  xeHostWaitOnFence(
    xe_fence_handle_t hFence,                       ///< [in] handle of the fence
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY; if zero, then
                                                    ///< operates exactly like ::xeFenceQueryStatus; if MAX_UINT32, then
                                                    ///< function will not return until complete or device is lost.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries a fence object's status.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkGetFenceStatus**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFence
///         + fence is not enqueued in a command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + not signaled
__xedllport xe_result_t __xecall
  xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a fence back to the not signaled state.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkResetFences**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFence
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
  xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_FENCE_H
