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
* @file xi_cmdlist.h
*
* @brief Intel Xi Runtime APIs for Command List
*
* DO NOT EDIT: generated from /scripts/specs/cmdlist.yml
*
******************************************************************************/
#ifndef _XI_CMDLIST_H
#define _XI_CMDLIST_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_command_list_desc_t
#define XI_COMMAND_LIST_DESC_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command List creation flags
typedef enum _xi_command_list_flags_t
{
    XI_COMMAND_LIST_FLAG_NONE = 0,                  ///< default behavior

} xi_command_list_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _xi_command_list_desc_t
{
    uint32_t version;                               ///< [in] ::XI_COMMAND_LIST_DESC_VERSION
    xi_command_list_flags_t flags;                  ///< [in] creation flags

} xi_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for desc
///     + nullptr for phCommandList
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiCommandListCreate(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device
    const xi_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xi_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
xi_result_t __xicall
  xiCommandListDestroy(
    xi_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Close a command list
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
xi_result_t __xicall
  xiCommandListClose(
    xi_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
xi_result_t __xicall
  xiCommandListReset(
    xi_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    );

#endif // _XI_CMDLIST_H
