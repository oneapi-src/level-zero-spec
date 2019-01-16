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
* @file xi_cmdqueue.h
*
* @brief Intel Xi Runtime APIs for Command Queue
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/cmdqueue.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_CMDQUEUE_H
#define _XI_CMDQUEUE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_command_queue_desc_t
#define XI_COMMAND_QUEUE_DESC_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue creation flags
typedef enum _xi_command_queue_flags_t
{
    XI_COMMAND_QUEUE_FLAG_DEFAULT = 0,              ///< implicit default behavior; uses runtime-based heuristics
    XI_COMMAND_QUEUE_FLAG_SYNCHRONOUS,              ///< GPU execution always completes immediately on enqueue; CPU thread is blocked using wait on implicit synchronization object
    XI_COMMAND_QUEUE_FLAG_ASYNCHRONOUS,             ///< GPU execution is scheduled and will complete in future; explicit synchronization object must be used to determine completeness

} xi_command_queue_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _xi_command_queue_desc_t
{
    uint32_t version;                               ///< [in] ::XI_COMMAND_QUEUE_DESC_VERSION
    xi_command_queue_flags_t flags;                 ///< [in] creation flags
    uint32_t ordinal;                               ///< [in] must be less than value returned for ::xi_device_properties_t.numAsyncComputeEngines

} xi_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on a context
/// @remarks
///   _Analogues_
///     - **clCreateCommandQueue**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hContext
///     + nullptr for desc
///     + nullptr for phCommandQueue
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiCommandQueueCreate(
    xi_context_handle_t hContext,                   ///< [in] handle of the context
    xi_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xi_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xi_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue
/// @remarks
///   _Analogues_
///     - **clReleaseCommandQueue**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandQueue
xi_result_t __xicall
  xiCommandQueueDestroy(
    xi_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue parameters
typedef enum _xi_command_queue_parameter_t
{
    XI_COMMAND_QUEUE_PARAMETER_PRIORITY = 1,        ///< see ::xi_command_queue_priority_t
    XI_COMMAND_QUEUE_PARAMETER_CACHE_CONFIG,        ///< see ::xi_command_queue_cacheconfig_t

} xi_command_queue_parameter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue priorities
typedef enum _xi_command_queue_priority_t
{
    XI_COMMAND_QUEUE_PRIORITY_NORMAL = 0,           ///< [default] normal priority
    XI_COMMAND_QUEUE_PRIORITY_LOW,                  ///< lower priority than normal
    XI_COMMAND_QUEUE_PRIORITY_HIGH,                 ///< higher priority than normal

} xi_command_queue_priority_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue cache configurations
typedef enum _xi_command_queue_cacheconfig_t
{
    XI_COMMAND_QUEUE_CACHECONFIG_BIAS_NONE,         ///< [default] no cache configuration bias; uses runtime-based heuristics

} xi_command_queue_cacheconfig_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a command queue's parameter
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandQueue
///     + invalid value for attribute
///     + invalid value for value
xi_result_t __xicall
  xiCommandQueueSetParameter(
    xi_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    xi_command_queue_parameter_t parameter,         ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a command queue's parameter
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandQueue
///     + invalid value for attribute
///     + nullptr for value
xi_result_t __xicall
  xiCommandQueueGetParameter(
    xi_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    xi_command_queue_parameter_t parameter,         ///< [in] parameter to change
    uint32_t* value                                 ///< [out] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets all command queue parameters to default state
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandQueue
xi_result_t __xicall
  xiCommandQueueResetParameters(
    xi_command_queue_handle_t hCommandQueue         ///< [in] handle of the command queue
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list into a command queue
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandQueue
///     + invalid handle for hCommandList
xi_result_t __xicall
  xiCommandQueueEnqueueCommandList(
    xi_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    xi_command_list_handle_t hCommandList           ///< [in] handle of the command list to execute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandQueue
xi_result_t __xicall
  xiCommandQueueSynchronize(
    xi_command_queue_handle_t hCommandQueue         ///< [in] handle of the command queue
    );

#endif // _XI_CMDQUEUE_H
