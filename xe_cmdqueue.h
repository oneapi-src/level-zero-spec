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
* @file xe_cmdqueue.h
* 
* @brief Intel Xe Driver APIs for Command Queue
* 
******************************************************************************/
#ifndef _XE_CMDQUEUE_H
#define _XE_CMDQUEUE_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue creation flags
XE_DECLARE_ENUM( xe_command_queue_flags_t )
{
    XE_COMMAND_QUEUE_FLAG_DEFAULT = 0,      ///< implicit default behavior; uses driver-based heuristics
    XE_COMMAND_QUEUE_FLAG_SYNCHRONOUS,      ///< GPU execution always completes immediately on enqueue; 
                                            ///< CPU thread is blocked using wait on implicit synchronization object
    XE_COMMAND_QUEUE_FLAG_ASYNCHRONOUS,     ///< GPU execution is scheduled and will complete in future;
                                            ///< explicit synchronization object must be used to determine completeness
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _xe_command_queue_desc_t
{
    const uint32_t version = XE_MAKE_VERSION( 1, 0 );   ///< [in] descriptor version

    xe_command_queue_flags_t flags;                     ///< [in] creation flags
} xe_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on a device
/// @details 
///     - A command queue represents a FIFO of command lists submitted to the device.
///     - The command queue maintains some machine state, which is inherited by
///       subsequent execution. See ::xe_command_queue_parameter_t for details.
///     - Multiple command queues may be created by an application.  For example,
///       an application may want to create a command queue per CPU thread.
///     - There is no implicit binding of command queues to CPU threads. Therefore,
///       an application may share a command queue handle across multiple CPU
///       threads. However, the application is responsible for ensuring that 
///       multiple CPU threads do not access the same command queue simultaneously.
///
/// @remarks _Analogues:_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phCommandQueue
///     - ::XE_RESULT_ERROR_OUT_OF_MEMORY
xe_result_t __xecall
  xeCommandQueueCreate(
    xe_device_handle_t hDevice,                 ///< [in] handle of the device
    xe_command_queue_desc_t* desc,              ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue   ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue
/// @details
///     - The application is responsible for making sure the GPU is not currently
///       executing from a command queue before it is deleted.  This is 
///       typically done by tracking command list events, but may also be
///       handled by calling ::xeCommandQueueSynchronize.
///
/// @remarks _Analogues:_
///     - **cuCtxDestroy**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
xe_result_t __xecall
  xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue     ///< [in] handle of command queue object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue parameters
XE_DECLARE_ENUM( xe_command_queue_parameter_t )
{
    XE_COMMAND_QUEUE_PARAMETER_PRIORITY = 1,    ///< see ::xe_command_queue_priority_t
    XE_COMMAND_QUEUE_PARAMETER_CACHE_CONFIG,    ///< see ::xe_command_queue_cacheconfig_t
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue priorities
XE_DECLARE_ENUM( xe_command_queue_priority_t )
{
    XE_COMMAND_QUEUE_PRIORITY_NORMAL = 0        ///< [default] normal priority
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue cache configurations
XE_DECLARE_ENUM( xe_command_queue_cacheconfig_t )
{
    XE_COMMAND_QUEUE_CACHECONFIG_BIAS_NONE = 0  ///< [default] no cache configuration bias; uses driver-based heuristics
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a command queue's parameter
/// @remarks _Analogues:_
///     - cuCtxSetCacheConfig
///     - cuCtxSetLimit
///     - cuCtxSetSharedMemConfig
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
///         + invalid value for attribute
///         + invalid value for value
xe_result_t __xecall
  xeCommandQueueSetParameter(
    xe_command_queue_handle_t hCommandQueue,    ///< [in] handle of command queue
    xe_command_queue_parameter_t parameter,     ///< [in] parameter to change
    uint32_t value                              ///< [in] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a command queue's parameter
/// @remarks _Analogues:_
///     - cuCtxGetCacheConfig
///     - cuCtxGetLimit
///     - cuCtxGetSharedMemConfig
///     - cuCtxGetStreamPriorityRange
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
///         + invalid value for attribute
///         + nullptr for value
xe_result_t __xecall
  xeCommandQueueGetParameter(
    xe_command_queue_handle_t hCommandQueue,    ///< [in] handle of command queue
    xe_command_queue_parameter_t parameter,     ///< [in] parameter to change
    uint32_t* value                             ///< [out] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets all command queue parameters to default state
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
xe_result_t __xecall
  xeCommandQueueResetParameters(
    xe_command_queue_handle_t hCommandQueue     ///< [in] handle of command queue
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list into a command queue
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandQueueEnqueueCommandList(
    xe_command_queue_handle_t hCommandQueue,    ///< [in] handle of the command queue
    xe_command_list_handle_t hCommandList       ///< [in] handle of the command list to execute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue
/// @remarks _Analogues:_
///     - **cuCtxSynchronize**
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
xe_result_t __xecall
  xeCommandQueueSynchronize(
    xe_command_queue_handle_t hCommandQueue     ///< [in] handle of command queue
    );

#endif // _XE_CMDQUEUE_H