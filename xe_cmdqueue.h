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
/// @brief Command Queue creation flags
XE_DECLARE_ENUM( xe_command_queue_flags_t )
{
    XE_COMMAND_QUEUE_FLAG_DEFAULT = 0,      ///< implicit default behavior (driver heuristics)
    XE_COMMAND_QUEUE_FLAG_SYNCHRONOUS,      ///< GPU execution always completes immediately on enqueue; 
                                            ///< CPU thread is blocked using wait on implicit synchronization object
    XE_COMMAND_QUEUE_FLAG_ASYNCHRONOUS,     ///< GPU execution is scheduled and will complete in future;
                                            ///< explicit synchronization object must be used to determine completeness
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _xe_command_queue_desc_t
{
    xe_command_queue_flags_t flags;             ///< [in] creation flags
} xe_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on a device
/// @details A command queue is a FIFO stream used to submit work to the device.
///     The command queue maintains some machine state, which is inherited by
///     subsequent execution.
/// @details _replaces cuCtxCreate and cuCtxGetCurrent_
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandQueueCreate(
    xe_device_handle_t hDevice,                 ///< [in] handle of the device
    xe_command_queue_desc_t* desc,              ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue   ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue
/// @details _replaces cuCtxDestroy_
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue     ///< [in] handle of command queue object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
XE_DECLARE_ENUM( xe_command_queue_parameter_t )
{
    XE_COMMAND_QUEUE_PARAMETER_PRIORITY = 1,    ///< @see xe_command_queue_priority_t
    XE_COMMAND_QUEUE_PARAMETER_CACHE_CONFIG,    ///< @see xe_command_queue_cacheconfig_t
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a command queue's parameter
/// @details _replaces cuCtxSetCacheConfig, cuCtxSetLimit, and
///     cuCtxSetSharedMemConfig_
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandQueueSetParameter(
    xe_command_queue_handle_t hCommandQueue,    ///< [in] handle of command queue
    xe_command_queue_parameter_t parameter,     ///< [in] parameter to change
    uint32_t value                              ///< [in] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a command queue's parameter
/// @details _replaces cuCtxGetCacheConfig, cuCtxGetLimit, cuCtxGetSharedMemConfig,
///     and cuCtxGetStreamPriorityRange_
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandQueueGetParameter(
    xe_command_queue_handle_t hCommandQueue,    ///< [in] handle of command queue
    xe_command_queue_parameter_t parameter,     ///< [in] parameter to change
    uint32_t* value                             ///< [out] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets all command queue parameters to default state
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandQueueResetParameters(
    xe_command_queue_handle_t hCommandQueue     ///< [in] handle of command queue
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list into a command queue
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandQueueEnqueueCommandList(
    xe_command_queue_handle_t hCommandQueue,    ///< [in] handle of the command queue
    xe_command_list_handle_t hCommandList       ///< [in] handle of the command list to execute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue
/// @details _replaces cuCtxSynchronize_
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandQueueSynchronize(
    xe_command_queue_handle_t hCommandQueue     ///< [in] handle of command queue
    );

#endif // _XE_CMDQUEUE_H