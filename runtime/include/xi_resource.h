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
* @file xi_resource.h
*
* @brief Intel Xi Runtime APIs for Resource
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/resource.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_RESOURCE_H
#define _XI_RESOURCE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_resource_desc_t
#define XI_RESOURCE_DESC_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported resource creation flags
typedef enum _xi_resource_flags_t
{
    XI_RESOURCE_FLAG_NONE = 0,                      ///< default behavior

} xi_resource_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource descriptor
typedef struct _xi_resource_desc_t
{
    uint32_t version;                               ///< [in] ::XI_RESOURCE_DESC_VERSION
    xi_resource_flags_t flags;                      ///< [in] creation flags

} xi_resource_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource object.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for desc
///     + nullptr for phResource
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiResourceCreate(
    const xi_resource_desc_t* desc,                 ///< [in] pointer to resource descriptor
    xi_resource_handle_t* phResource                ///< [out] pointer to handle of resource object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a resource object.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hResource
xi_result_t __xicall
  xiResourceDestroy(
    xi_resource_handle_t hResource                  ///< [in] handle of resource object to destroy
    );

#endif // _XI_RESOURCE_H
