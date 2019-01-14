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
* @file xi_fence.h
*
* @brief Intel Xi Runtime APIs for Fence
*
* DO NOT EDIT: generated from /scripts/specs/fence.yml
*
******************************************************************************/
#ifndef _XI_FENCE_H
#define _XI_FENCE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_fence_desc_t
#define XI_FENCE_DESC_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported fence creation flags
typedef enum _xi_fence_flags_t
{
    XI_FENCE_FLAG_NONE = 0,                         ///< default behavior

} xi_fence_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fence descriptor
typedef struct _xi_fence_desc_t
{
    uint32_t version;                               ///< [in] descriptor version
    xi_fence_flags_t flags;                         ///< [in] creation flags

} xi_fence_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a fence object.
/// @remarks
///   _Analogues_
///     - **cuEventCreate**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for desc
///     + nullptr for phFence
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiFenceCreate(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device
    const xi_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xi_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a fence object.
/// @remarks
///   _Analogues_
///     - **cuEventDestroy**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hFence
///     + fence is enqueued in a command queue
xi_result_t __xicall
  xiFenceDestroy(
    xi_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a signal of the fence into a command queue.
/// @remarks
///   _Analogues_
///     - **cuEventRecord**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
///     + invalid handle for hFence
///     + fence is in signaled state
///     + fence is enqueued in another command queue
xi_result_t __xicall
  xiCommandQueueEnqueueSignalFence(
    xi_command_queue_handle_t hCommandList,         ///< [in] handle of the command queue
    xi_fence_handle_t hFence                        ///< [in] handle of the fence
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a fence to be signaled.
/// @remarks
///   _Analogues_
///     - **cuEventSynchronize**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hFence
///     + fence is not enqueued in a command queue
xi_result_t __xicall
  xiWaitOnFence(
    xi_fence_handle_t hFence                        ///< [in] handle of the fence
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a multiple fences to be signaled.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for phFences
///     + any invalid handle in phFences
///     + any fence is not enqueued in a command queue
xi_result_t __xicall
  xiWaitOnMultipleFences(
    uint32_t numFences,                             ///< [in] number of fences in hFences
    xi_fence_handle_t* phFences                     ///< [in] pointer to array of handles of the fences
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries a fence object's status.
/// @remarks
///   _Analogues_
///     - **cuEventQuery**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_NOT_READY
///     + not signaled
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hFence
///     + fence is not enqueued in a command queue
xi_result_t __xicall
  xiFenceQueryStatus(
    xi_fence_handle_t hFence                        ///< [in] handle of the fence
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries the elapsed time between two signaled fences.
/// @remarks
///   _Analogues_
///     - **cuEventElapsedTime**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hFenceStart
///     + invalid handle for hFenceEnd
///     + either fence not enqueued
///     + nullptr for pTime
xi_result_t __xicall
  xiFenceQueryElapsedTime(
    xi_fence_handle_t hFenceStart,                  ///< [in] handle of the fence
    xi_fence_handle_t hFenceEnd,                    ///< [in] handle of the fence
    double_t* pTime                                 ///< [out] time in milliseconds
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a fence back to the not signaled state
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hFence
xi_result_t __xicall
  xiFenceReset(
    xi_fence_handle_t hFence                        ///< [in] handle of the fence
    );

#endif // _XI_FENCE_H
