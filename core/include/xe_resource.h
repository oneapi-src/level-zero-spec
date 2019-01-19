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
* @file xe_resource.h
*
* @brief Intel Xe Driver APIs for Resource
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/resource.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_RESOURCE_H
#define _XE_RESOURCE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_resource_desc_t
#define XE_RESOURCE_DESC_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported resource creation flags
typedef enum _xe_resource_flags_t
{
    XE_RESOURCE_FLAG_KERNEL_READ = XE_BIT( 0 ),     ///< kernels may read contents
    XE_RESOURCE_FLAG_KERNEL_WRITE = XE_BIT( 1 ),    ///< kernels may write contents
    XE_RESOURCE_FLAG_HOST_READ = XE_BIT( 2 ),       ///< host may read contents
    XE_RESOURCE_FLAG_HOST_WRITE = XE_BIT( 3 ),      ///< host may write contents

} xe_resource_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported resource types
typedef enum _xe_resource_type_t
{
    XE_RESOURCE_TYPE_BUFFER,                        ///< buffer
    XE_RESOURCE_TYPE_1D,                            ///< 1D
    XE_RESOURCE_TYPE_1DARRAY,                       ///< 1D array
    XE_RESOURCE_TYPE_2D,                            ///< 2D
    XE_RESOURCE_TYPE_2DARRAY,                       ///< 2D array
    XE_RESOURCE_TYPE_3D,                            ///< 3D

} xe_resource_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported resource formats
typedef enum _xe_resource_format_t
{
    XE_RESOURCE_FORMAT_UINT8,                       ///< 8-bit unsigned integer
    XE_RESOURCE_FORMAT_UINT16,                      ///< 16-bit unsigned integer
    XE_RESOURCE_FORMAT_UINT32,                      ///< 32-bit unsigned integer
    XE_RESOURCE_FORMAT_SINT8,                       ///< 8-bit signed integer
    XE_RESOURCE_FORMAT_SINT16,                      ///< 16-bit signed integer
    XE_RESOURCE_FORMAT_SINT32,                      ///< 32-bit signed integer
    XE_RESOURCE_FORMAT_FLOAT16,                     ///< 16-bit float
    XE_RESOURCE_FORMAT_FLOAT32,                     ///< 32-bit float

} xe_resource_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource descriptor
typedef struct _xe_resource_desc_t
{
    uint32_t version;                               ///< [in] ::XE_RESOURCE_DESC_VERSION
    xe_resource_flags_t flags;                      ///< [in] creation flags
    xe_resource_type_t type;                        ///< [in] resource type
    xe_resource_format_t format;                    ///< [in] resource channel format
    uint32_t numChannels;                           ///< [in] number of channels per pixel
    size_t width;                                   ///< [in] width in pixels
    size_t height;                                  ///< [in] height in pixels (2D or 3D only)
    size_t depth;                                   ///< [in] depth in pixels (3D only)
    size_t arraylevels;                             ///< [in] array levels (array types only)
    size_t miplevels;                               ///< [in] mipmap levels (must be 0)

} xe_resource_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource object.
/// @remarks
///   _Analogues_
///     - clCreateImage
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr for desc
///         + nullptr for phResource
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeResourceCreate(
    const xe_resource_desc_t* desc,                 ///< [in] pointer to resource descriptor
    xe_resource_handle_t* phResource                ///< [out] pointer to handle of resource object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a resource object.
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hResource
xe_result_t __xecall
  xeResourceDestroy(
    xe_resource_handle_t hResource                  ///< [in] handle of resource object to destroy
    );

#endif // _XE_RESOURCE_H
