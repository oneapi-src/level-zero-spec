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
* @file xe_semaphore.h
* 
* @brief Intel Xe Driver APIs for Semaphore
* 
******************************************************************************/
#ifndef _XE_SEMAPHORE_H
#define _XE_SEMAPHORE_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported semaphore creation flags
XE_DECLARE_ENUM( xe_semaphore_flags_t )
{
    XE_SEMAPHORE_FLAG_NONE = 0                  ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief
typedef uint64_t xe_semaphore_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Semaphore descriptor
typedef struct _xe_semaphore_desc_t
{
    uint32_t version;                       ///< [in] descriptor version

    xe_semaphore_flags_t flags;             ///< [in] creation flags
} xe_semaphore_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of xe_semaphore_desc_t
#define XE_SEMAPHORE_DESC_VERSION   XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an semaphore object
/// @remarks _Analogues:_
///     - **cuEventCreate**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phSemaphore
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeSemaphoreCreate(
    xe_device_handle_t hDevice,             ///< [in] handle of the device
    xe_semaphore_desc_t* desc,              ///< [in] pointer to semaphore descriptor
    xe_semaphore_handle_t* phSemaphore      ///< [out] pointer to handle of semaphore object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an semaphore object
/// @remarks _Analogues:_
///     - **cuEventDestroy**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hSemaphore
xe_result_t __xecall
  xeSemaphoreDestroy(
    xe_semaphore_handle_t hSemaphore        ///< [in] handle of semaphore object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an semaphore signal into a command list
/// @remarks _Analogues:_
///     - **cuEventRecord**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hSemaphore
xe_result_t __xecall
  xeCommandListEncodeSemaphoreSignal(
    xe_command_list_handle_t hCommandList,  ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,       ///< [in] handle of the semaphore 
    xe_semaphore_value_t value                  ///< [in] the value to write on signal
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported semaphore wait operations
XE_DECLARE_ENUM( xe_semaphore_wait_operation_t )
{
    XE_SEMAPHORE_WAIT_OPERATION_EQUAL_TO = 1,           ///< semaphore value == wait value
    XE_SEMAPHORE_WAIT_OPERATION_NOT_EQUAL_TO,           ///< semaphore value != wait value
    XE_SEMAPHORE_WAIT_OPERATION_GREATER_THAN,           ///< semaphore value > wait value
    XE_SEMAPHORE_WAIT_OPERATION_GREATER_OR_EQUAL_TO,    ///< semaphore value >= wait value
    XE_SEMAPHORE_WAIT_OPERATION_LESS_THAN,              ///< semaphore value < wait value
    XE_SEMAPHORE_WAIT_OPERATION_LESS_OR_EQUAL_TO,       ///< semaphore value <= wait value
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an semaphore wait into a command list
/// @remarks _Analogues:_
///     - cuEventRecord
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hSemaphore
xe_result_t __xecall
  xeCommandListEncodeSemaphoreWait(
    xe_command_list_handle_t hCommandList,  ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore 
    xe_semaphore_wait_operation_t operation,    ///< [in] wait operation type
    xe_semaphore_value_t value                  ///< [in] the value to wait upon
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an semaphore object's value
/// @remarks _Analogues:_
///     - **cuEventQuery**
///     - cuEventSynchronize
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hSemaphore
///         + nullptr for value
xe_result_t __xecall
  xeSemaphoreQuery(
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore 
    xe_semaphore_value_t* value                 ///< [out] the current value of the semaphore
    );

#endif // _XE_SEMAPHORE_H