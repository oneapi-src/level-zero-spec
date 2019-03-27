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
* @file xe_cmdlist.h
*
* @brief Intel Xe Level-Zero APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdlist.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDLIST_H
#define _XE_CMDLIST_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_command_list_desc_t
typedef enum _xe_command_list_desc_version_t
{
    XE_COMMAND_LIST_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ), ///< version 1.0

} xe_command_list_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command list creation flags
typedef enum _xe_command_list_flag_t
{
    XE_COMMAND_LIST_FLAG_NONE = 0,                  ///< default behavior
    XE_COMMAND_LIST_FLAG_COPY_ONLY = XE_BIT(0),     ///< command list **only** contains copy operations (and synchronization
                                                    ///< primitives)
    XE_COMMAND_LIST_FLAG_RELAXED_ORDERING = XE_BIT(1),  ///< driver may reorder programs and copys between barriers and
                                                    ///< synchronization primitives
    XE_COMMAND_LIST_FLAG_LOW_LATENCY = XE_BIT(2),   ///< driver should optimize for immediate submission to a command queue
    XE_COMMAND_LIST_FLAG_CROSS_DEVICE = XE_BIT(3),  ///< command list can be shared with another device

} xe_command_list_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _xe_command_list_desc_t
{
    xe_command_list_desc_version_t version;         ///< [in] ::XE_COMMAND_LIST_DESC_VERSION_CURRENT
    xe_command_list_flag_t flags;                   ///< [in] creation flags

} xe_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device for submitting commands to any
///        command queue.
/// 
/// @details
///     - The command list is created in the 'open' state.
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__xedllport xe_result_t __xecall
xeDeviceCreateCommandList(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the command list before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command list.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command list; ready to be executed by a command queue.
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state; ready for appending
///        commands.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the command list before it is reset
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xeCommandListReset(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command list parameters
typedef enum _xe_command_list_parameter_t
{
    XE_COMMAND_LIST_PARAMETER_TBD,                  ///< TBD

} xe_command_list_parameter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a command list's parameter.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - cuCtxSetCacheConfig
///     - cuCtxSetLimit
///     - cuCtxSetSharedMemConfig
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + invalid value for attribute
///         + invalid value for value
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xeCommandListSetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a command list's parameter.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - cuCtxGetCacheConfig
///     - cuCtxGetLimit
///     - cuCtxGetSharedMemConfig
///     - cuCtxGetStreamPriorityRange
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == value
///         + invalid value for attribute
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xeCommandListGetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets all command list parameters to default state.
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reserve a section of contiguous command buffer space within the
///        command list.
/// 
/// @details
///     - The pointer returned is valid for both Host and device access.
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
///         + nullptr == ptr
///         + 0 for size
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xeCommandListReserveSpace(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_CMDLIST_H
