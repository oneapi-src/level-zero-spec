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
* @file xe_copy.h
*
* @brief Intel Xe Driver APIs for Copies
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/copy.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_COPY_H
#define _XE_COPY_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies device or managed memory.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for dstptr
///     + nullptr for srcptr
xe_result_t __xecall
  xeCommandListEncodeMemoryCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_ptr_t dstptr,                         ///< [in] pointer to destination memory to copy to
    xe_device_ptr_t srcptr,                         ///< [in] pointer to source memory to copy from
    size_t size                                     ///< [in] size in bytes to copy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a resource.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDstResource
///     + invalid handle for hSrcResource
xe_result_t __xecall
  xeCommandListEncodeResourceCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_resource_handle_t hDstResource,              ///< [in] handle of destination resource to copy to
    xe_resource_handle_t hSrcResource               ///< [in] handle of source resource to copy from
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Region descriptor
typedef struct _xeResourceRegion
{
    size_t offset;                                  ///< [in] offset in bytes from base
    size_t size;                                    ///< [in] size in bytes from base+offset

} xeResourceRegion;

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region of a resource.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDstResource
///     + invalid handle for hSrcResource
xe_result_t __xecall
  xeCommandListEncodeResourceCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_resource_handle_t hDstResource,              ///< [in] handle of destination resource to copy to
    xeResourceRegion* pDstRegion,                   ///< [in] destination region descriptor
    xe_resource_handle_t hSrcResource,              ///< [in] handle of source resource to copy from
    xeResourceRegion* pSrcRegion                    ///< [in] source region descriptor
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies from a resource to device or managed memory.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for dstptr
///     + invalid handle for hSrcResource
xe_result_t __xecall
  xeCommandListEncodeResourceCopyToMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_ptr_t dstptr,                         ///< [in] pointer to destination memory to copy to
    xe_resource_handle_t hSrcResource,              ///< [in] handle of source resource to copy from
    xeResourceRegion* pSrcRegion                    ///< [in] source region descriptor
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies to a resource from device or managed memory.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDstResource
///     + nullptr for srcptr
xe_result_t __xecall
  xeCommandListEncodeResourceCopyFromMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_resource_handle_t hDstResource,              ///< [in] handle of destination resource to copy to
    xeResourceRegion* pDstRegion,                   ///< [in] destination region descriptor
    xe_device_ptr_t srcptr                          ///< [in] pointer to source memory to copy from
    );

#endif // _XE_COPY_H
