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
* @file xi_context.h
*
* @brief Intel Xi Runtime APIs for Context
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/context.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_CONTEXT_H
#define _XI_CONTEXT_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_context_desc_t
#define XI_CONTEXT_DESC_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported context creation flags
typedef enum _xi_context_flags_t
{
    XI_CONTEXT_FLAG_NONE = 0,                       ///< default behavior

} xi_context_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Context descriptor
typedef struct _xi_context_desc_t
{
    uint32_t version;                               ///< [in] ::XI_CONTEXT_DESC_VERSION
    xi_context_flags_t flags;                       ///< [in] creation flags
    uint32_t numDevices;                            ///< [in] number of devices in hDevices
    xi_device_handle_t* hDevices;                   ///< [in] pointer to array of handles of the devices

} xi_context_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a context.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for desc
///     + 0 for desc.numDevices
///     + invalid handle in desc.hDevices
///     + nullptr for phContext
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiContextCreate(
    const xi_context_desc_t* desc,                  ///< [in] pointer to context descriptor
    xi_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a context.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hContext
xi_result_t __xicall
  xiContextDestroy(
    xi_context_handle_t hContext                    ///< [in] handle of context object to destroy
    );

#endif // _XI_CONTEXT_H
