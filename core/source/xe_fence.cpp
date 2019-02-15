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
* @file xe_fence.cpp
*
* @brief Intel Xe Driver APIs for Fence
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/fence.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_fence.h"

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
///         + ::XE_FENCE_DESC_VERSION <= desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandQueueCreateFence(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandQueue, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phFence, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_FENCE_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFence, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeHostWaitOnFence(
    xe_fence_handle_t hFence,                       ///< [in] handle of the fence
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if -1, then function will not return
                                                    ///< until complete.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFence, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a multiple fences to be signaled.
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
///         + nullptr == phFences
///         + nullptr == any handle in phFences
///         + any fence is not enqueued in a command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeHostWaitOnMultipleFences(
    uint32_t numFences,                             ///< [in] number of fences in hFences
    xe_fence_handle_t* phFences,                    ///< [in] pointer to array of handles of the fences
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if -1, then function will not return
                                                    ///< until complete.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == phFences, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFence, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries the elapsed time between two signaled fences.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFenceStart
///         + nullptr == hFenceEnd
///         + nullptr == pTime
///         + either fence not enqueued
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFenceQueryElapsedTime(
    xe_fence_handle_t hFenceStart,                  ///< [in] handle of the fence
    xe_fence_handle_t hFenceEnd,                    ///< [in] handle of the fence
    double_t* pTime                                 ///< [out] time in milliseconds
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFenceStart, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFenceEnd, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pTime, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFence, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

