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
* @file xi_runtime.h
*
* @brief Intel Xi Runtime APIs
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/runtime.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_RUNTIME_H
#define _XI_RUNTIME_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported initialization flags
typedef enum _xi_init_flags_t
{
    XI_INIT_FLAG_NONE = 0,                          ///< default behavior

} xi_init_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the Xi Runtime API and must be called before any other API
///        function.
/// @details
///     - If this function is not called then all other functions will return
///       ::XI_RESULT_ERROR_UNINITIALIZED.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid value for flags
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
xi_result_t __xicall
  xiInit(
    xi_init_flags_t flags                           ///< [in] initialization flags
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported runtime versions
/// @details
///     - Runtime versions contain major and minor attributes, use
///       ::XI_MAJOR_VERSION and ::XI_MINOR_VERSION.
typedef enum _xi_runtime_version_t
{
    XI_RUNTIME_VERSION_1_0 = XI_MAKE_VERSION( 1, 0 ),   ///< 1.0

} xi_runtime_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the current versions of the runtime
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for version
xi_result_t __xicall
  xiRuntimeGetVersion(
    xi_runtime_version_t* version                   ///< [out] runtime version
    );

#endif // _XI_RUNTIME_H
