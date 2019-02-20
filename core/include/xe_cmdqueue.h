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
* @file xe_cmdqueue.h
*
* @brief Intel Xe Driver APIs for Command Queue
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/cmdqueue.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDQUEUE_H
#define _XE_CMDQUEUE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_command_queue_desc_t
#define XE_COMMAND_QUEUE_DESC_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue flags
typedef enum _xe_command_queue_flag_t
{
    XE_COMMAND_QUEUE_FLAG_NONE = 0,                 ///< default behavior
    XE_COMMAND_QUEUE_FLAG_COPY_ONLY = XE_BIT(0),    ///< command queue only supports enqueing copy-only command lists
    XE_COMMAND_QUEUE_FLAG_LOGICAL_ONLY = XE_BIT(1), ///< command queue is not tied to a physical command queue; driver may
                                                    ///< dynamically assign based on usage

} xe_command_queue_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue modes
typedef enum _xe_command_queue_mode_t
{
    XE_COMMAND_QUEUE_MODE_DEFAULT = 0,              ///< implicit default behavior; uses driver-based heuristics
    XE_COMMAND_QUEUE_MODE_SYNCHRONOUS,              ///< GPU execution always completes immediately on enqueue; CPU thread is
                                                    ///< blocked using wait on implicit synchronization object
    XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS,             ///< GPU execution is scheduled and will complete in future; explicit
                                                    ///< synchronization object must be used to determine completeness

} xe_command_queue_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue priorities
typedef enum _xe_command_queue_priority_t
{
    XE_COMMAND_QUEUE_PRIORITY_NORMAL = 0,           ///< [default] normal priority
    XE_COMMAND_QUEUE_PRIORITY_LOW,                  ///< lower priority than normal
    XE_COMMAND_QUEUE_PRIORITY_HIGH,                 ///< higher priority than normal

} xe_command_queue_priority_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _xe_command_queue_desc_t
{
    uint32_t version;                               ///< [in] ::XE_COMMAND_QUEUE_DESC_VERSION
    xe_command_queue_flag_t flags;                  ///< [in] creation flags
    xe_command_queue_mode_t mode;                   ///< [in] operation mode
    xe_command_queue_priority_t priority;           ///< [in] priority
    uint32_t ordinal;                               ///< [in] if logical-only flag is set, then must be 0; else-if copy-only
                                                    ///< flag is set, then must be less than
                                                    ///< ::xe_device_properties_t.numAsyncCopyEngines; otherwise must be less
                                                    ///< than ::xe_device_properties_t.numAsyncComputeEngines. When using
                                                    ///< sub-devices the ::xe_device_properties_t.numAsyncComputeEngines must
                                                    ///< be queried from the sub-device being used.

} xe_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on the device.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateCommandQueue**
///     - cuCtxCreate
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_QUEUE_DESC_VERSION <= desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__xedllport xe_result_t __xecall
  xeDeviceCreateCommandQueue(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the command queue before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command queue
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseCommandQueue**
///     - cuCtxDestroy
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
  xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list into a command queue for immediate execution.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkQueueSubmit
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandQueue
///         + nullptr == phCommandLists
///         + 0 for numCommandLists
///         + hFence is in signaled state
///         + hFence is enqueued in another command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
  xeCommandQueueEnqueueCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to enqueue
    xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to enqueue for execution
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue by waiting on the host.
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
///         + nullptr == hCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
__xedllport xe_result_t __xecall
  xeCommandQueueSynchronize(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_CMDQUEUE_H
