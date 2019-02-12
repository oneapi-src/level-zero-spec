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
* @brief Intel Xe Driver APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/cmdlist.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDLIST_H
#define _XE_CMDLIST_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_command_list_desc_t
#define XE_COMMAND_LIST_DESC_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command list creation flags
typedef enum _xe_command_list_flags_t
{
    XE_COMMAND_LIST_FLAG_NONE = 0,                  ///< default behavior
    XE_COMMAND_LIST_FLAG_COPY_ONLY = XE_BIT(0),     ///< command list **only** contains copy operations (and synchronization
                                                    ///< primitives)
    XE_COMMAND_LIST_FLAG_RELAXED_ORDERING = XE_BIT(1),  ///< driver may reorder programs and copys between barriers and
                                                    ///< synchronization primitives
    XE_COMMAND_LIST_FLAG_LOW_LATENCY = XE_BIT(2),   ///< driver should optimize for immediate submission to a command queue
    XE_COMMAND_LIST_FLAG_CROSS_DEVICE = XE_BIT(3),  ///< command list can be shared with another device

} xe_command_list_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _xe_command_list_desc_t
{
    uint32_t version;                               ///< [in] ::XE_COMMAND_LIST_DESC_VERSION
    xe_command_list_flags_t flags;                  ///< [in] creation flags

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phCommandList
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeDeviceCreateCommandList(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a command list on the device for submitting commands to any
///        command queue.
/// 
/// @details
///     - The command list to be copied must be closed.
///     - The command list created will be in the 'open' state.
///     - If the device is a different than the one used to create the source
///       command list, then it must have been created using the
///       ::XE_COMMAND_LIST_FLAG_CROSS_DEVICE flag.
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid handle for hCommandList
///         + nullptr for phCommandList
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeDeviceCopyCommandList(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_command_list_handle_t hCommandList,          ///< [in] handle to command list to copy
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command list; ready to be enqueued into a command queue.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state; ready for encoding
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid value for attribute
///         + invalid value for value
xe_result_t __xecall
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid value for attribute
///         + nullptr for value
xe_result_t __xecall
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encode a command list into another command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + 0 for numCommandLists
///         + nullptr for phCommandLists
///         + invalid handle in phCommandLists
xe_result_t __xecall
  xeCommandListEncodeCommandLists(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numCommandLists,                       ///< [in] number of command lists to encode
    xe_command_list_handle_t* phCommandLists        ///< [in] list of handles of the command lists to encode for execution
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Support command formats
typedef enum _xe_command_format_t
{
    XE_COMMAND_FORMAT_NATIVE,                       ///< The commands are native device-specific format

} xe_command_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Encode a pre-formatted blob of commands into the comamnd list.
/// 
/// @details
///     - The commands are gaurenteed to be contiguous in the command buffer
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid value for format
///         + 0 for size
///         + nullptr for pBlob
xe_result_t __xecall
  xeCommandListEncodeCommands(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_command_format_t format,                     ///< [in] format of the command blob
    size_t size,                                    ///< [in] size (in bytes) of the command blob
    void* pBlob                                     ///< [in] pointer to blob of commands to encode into the command list
    );

#endif // _XE_CMDLIST_H
