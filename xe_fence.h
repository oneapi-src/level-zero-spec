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
* @file xe_fence.h
* 
* @brief Intel Xe Driver APIs for Fence
* 
******************************************************************************/
#ifndef _XE_FENCE_H
#define _XE_FENCE_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported fence creation flags
XE_DECLARE_ENUM( xe_fence_flags_t )
{
    XE_FENCE_FLAG_NONE = 0                  ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Fence descriptor
typedef struct _xe_fence_desc_t
{
    uint32_t version;                       ///< [in] descriptor version

    xe_fence_flags_t flags;                 ///< [in] creation flags
} xe_fence_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of xe_fence_desc_t
#define XE_FENCE_DESC_VERSION   XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a fence object
/// @remarks _Analogues:_
///     - **cuEventCreate**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phFence
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeFenceCreate(
    xe_device_handle_t hDevice,             ///< [in] handle of the device
    xe_fence_desc_t* desc,                  ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence              ///< [out] pointer to handle of fence object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a fence object
/// @remarks _Analogues:_
///     - **cuEventDestroy**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFence
///         + fence is enqueued in a command queue
xe_result_t __xecall
  xeFenceDestroy(
    xe_fence_handle_t hFence                ///< [in] handle of fence object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a signal of the fence into a command queue
/// @remarks _Analogues:_
///     - **cuEventRecord**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hFence
///         + fence is in signaled state
///         + fence is enqueued in another command queue
xe_result_t __xecall
  xeCommandQueueEnqueueSignalFence(
    xe_command_queue_handle_t hCommandList, ///< [in] handle of the command queue
    xe_fence_handle_t hFence                ///< [in] handle of the fence 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a fence to be signaled
/// @remarks _Analogues:_
///     - **cuEventSynchronize**
/// @returns
///     - ::XE_RESULT_SUCCESS - signaled
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFence
///         + fence is not enqueued in a command queue
xe_result_t __xecall
  xeWaitOnFence(
    xe_fence_handle_t hFence                ///< [in] handle of the fence 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries a fence object's status
/// @remarks _Analogues:_
///     - **cuEventQuery**
/// @returns
///     - ::XE_RESULT_SUCCESS - signaled
///     - ::XE_RESULT_NOT_READY - not signaled or not enqueued
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFence
xe_result_t __xecall
  xeFenceQueryStatus(
    xe_fence_handle_t hFence                ///< [in] handle of the fence 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a fence back to the not signaled state
/// @remarks _Analogues:_
///     - none
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFence
xe_result_t __xecall
  xeFenceReset(
    xe_fence_handle_t hFence                ///< [in] handle of the fence 
    );

#endif // _XE_FENCE_H