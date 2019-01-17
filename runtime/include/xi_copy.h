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
* @file xi_copy.h
*
* @brief Intel Xi Runtime APIs for Copies
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/copy.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_COPY_H
#define _XI_COPY_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies device or managed memory.
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyBuffer**
///     - clEnqueueReadBuffer
///     - clEnqueueWriteBuffer
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for dstptr
///     + nullptr for srcptr
xi_result_t __xicall
  xiCommandListEncodeMemoryCopy(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xi_device_ptr_t dstptr,                         ///< [in] pointer to destination memory to copy to
    xi_device_ptr_t srcptr,                         ///< [in] pointer to source memory to copy from
    size_t size                                     ///< [in] size in bytes to copy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a resource.
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyImage**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDstResource
///     + invalid handle for hSrcResource
xi_result_t __xicall
  xiCommandListEncodeResourceCopy(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xi_resource_handle_t hDstResource,              ///< [in] handle of destination resource to copy to
    xi_resource_handle_t hSrcResource               ///< [in] handle of source resource to copy from
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Region descriptor
typedef struct _xiResourceRegion
{
    size_t offset;                                  ///< [in] offset in bytes from base
    size_t size;                                    ///< [in] size in bytes from base+offset

} xiResourceRegion;

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region of a resource.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDstResource
///     + invalid handle for hSrcResource
xi_result_t __xicall
  xiCommandListEncodeResourceCopyRegion(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xi_resource_handle_t hDstResource,              ///< [in] handle of destination resource to copy to
    xiResourceRegion* pDstRegion,                   ///< [in] destination region descriptor
    xi_resource_handle_t hSrcResource,              ///< [in] handle of source resource to copy from
    xiResourceRegion* pSrcRegion                    ///< [in] source region descriptor
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies from a resource to device or managed memory.
/// @remarks
///   _Analogues_
///     - clEnqueueReadImage
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for dstptr
///     + invalid handle for hSrcResource
xi_result_t __xicall
  xiCommandListEncodeResourceCopyToMemory(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xi_device_ptr_t dstptr,                         ///< [in] pointer to destination memory to copy to
    xi_resource_handle_t hSrcResource,              ///< [in] handle of source resource to copy from
    xiResourceRegion* pSrcRegion                    ///< [in] source region descriptor
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies to a resource from device or managed memory.
/// @remarks
///   _Analogues_
///     - clEnqueueWriteImage
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDstResource
///     + nullptr for srcptr
xi_result_t __xicall
  xiCommandListEncodeResourceCopyFromMemory(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xi_resource_handle_t hDstResource,              ///< [in] handle of destination resource to copy to
    xiResourceRegion* pDstRegion,                   ///< [in] destination region descriptor
    xi_device_ptr_t srcptr                          ///< [in] pointer to source memory to copy from
    );

#endif // _XI_COPY_H
