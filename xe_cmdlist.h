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
* @file xe_cmdlist.h
* 
* @brief Intel Xe Driver APIs for Command List
* 
******************************************************************************/
#ifndef _XE_CMDLIST_H
#define _XE_CMDLIST_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command List creation flags
XE_DECLARE_ENUM( xe_command_list_flags_t )
{
    XE_COMMAND_LIST_FLAG_NONE = 0               ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _xe_command_list_desc_t
{
    const uint32_t version = XE_MAKE_VERSION( 1, 0 );   ///< [in] descriptor version

    xe_command_list_flags_t flags;                      ///< [in] creation flags
} xe_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list
/// @details
///     - A command list represents a sequence of commands for execution on
///       a command queue.
///     - The command list maintains some machine state, which is inherited by
///       subsequent commands. See ::xe_command_list_parameter_t for details.
///     - Command lists do not inherit state from other command lists executed
///       on the same command queue.  i.e. each command list begins execution
///       in its own state.
///     - Multiple command lists may be created by an application.  For example,
///       an application may want to create multiple command lists per command queue.
///     - There is no implicit association between a command list and a 
///       command queue. Therefore, a command list may be submitted to any, or
///       multiple command queues.
///     - There is no implicit binding of command lists to CPU threads. Therefore,
///       an application may share a command list handle across multiple CPU
///       threads. However, the application is responsible for ensuring that 
///       multiple CPU threads do not access the same command list simultaneously.
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phCommandList
///     - ::XE_RESULT_ERROR_OUT_OF_MEMORY
xe_result_t __xecall
  xeCommandListCreate(
    xe_device_handle_t hDevice,                 ///< [in] handle of the device
    xe_command_list_desc_t* desc,               ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList     ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list
///     - The application is responsible for making sure the GPU is not currently
///       executing from a command list before it is deleted.  This should be
///       handled by tracking a completion event associated with the command list.
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandListDestroy(
    xe_command_list_handle_t hCommandList       ///< [in] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state
///     - The application is responsible for making sure the GPU is not currently
///       executing from a command list before it is reset.  This should be
///       handled by tracking a completion event associated with the command list.
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandListReset(
    xe_command_list_handle_t hCommandList       ///< [in] handle of command list object to destroy
    );

#endif // _XE_CMDLIST_H