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
* @file xe_image.h
*
* @brief Intel Xe Driver APIs for Images
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/image.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_IMAGE_H
#define _XE_IMAGE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_image_desc_t
#define XE_IMAGE_DESC_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image creation flags
typedef enum _xe_image_flag_t
{
    XE_IMAGE_FLAG_PROGRAM_READ = XE_BIT( 0 ),       ///< programs will read contents
    XE_IMAGE_FLAG_PROGRAM_WRITE = XE_BIT( 1 ),      ///< programs will write contents
    XE_IMAGE_FLAG_BIAS_CACHED = XE_BIT( 2 ),        ///< device should cache contents
    XE_IMAGE_FLAG_BIAS_UNCACHED = XE_BIT( 3 ),      ///< device should not cache contents

} xe_image_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image types
typedef enum _xe_image_type_t
{
    XE_IMAGE_TYPE_1D,                               ///< 1D
    XE_IMAGE_TYPE_1DARRAY,                          ///< 1D array
    XE_IMAGE_TYPE_2D,                               ///< 2D
    XE_IMAGE_TYPE_2DARRAY,                          ///< 2D array
    XE_IMAGE_TYPE_3D,                               ///< 3D

} xe_image_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image formats
typedef enum _xe_image_format_t
{
    XE_IMAGE_FORMAT_UINT8,                          ///< 8-bit unsigned integer
    XE_IMAGE_FORMAT_UINT16,                         ///< 16-bit unsigned integer
    XE_IMAGE_FORMAT_UINT32,                         ///< 32-bit unsigned integer
    XE_IMAGE_FORMAT_SINT8,                          ///< 8-bit signed integer
    XE_IMAGE_FORMAT_SINT16,                         ///< 16-bit signed integer
    XE_IMAGE_FORMAT_SINT32,                         ///< 32-bit signed integer
    XE_IMAGE_FORMAT_FLOAT16,                        ///< 16-bit float
    XE_IMAGE_FORMAT_FLOAT32,                        ///< 32-bit float

} xe_image_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image descriptor
typedef struct _xe_image_desc_t
{
    uint32_t version;                               ///< [in] ::XE_IMAGE_DESC_VERSION
    xe_image_flag_t flags;                          ///< [in] creation flags
    xe_image_type_t type;                           ///< [in] image type
    xe_image_format_t format;                       ///< [in] image channel format
    uint32_t numChannels;                           ///< [in] number of channels per pixel [1,4]
    size_t width;                                   ///< [in] width in pixels, see
                                                    ///< ::xe_device_memory_properties_t::maxImageDims1D/2D/3D
    size_t height;                                  ///< [in] height in pixels (2D or 3D only), see
                                                    ///< ::xe_device_memory_properties_t::maxImageDims2D/3D
    size_t depth;                                   ///< [in] depth in pixels (3D only), see
                                                    ///< ::xe_device_memory_properties_t::maxImageDims3D
    size_t arraylevels;                             ///< [in] array levels (array types only), see
                                                    ///< ::xe_device_memory_properties_t::maxImageArraySlices
    size_t miplevels;                               ///< [in] mipmap levels (must be 0)

} xe_image_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a image object on the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clCreateImage
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_IMAGE_DESC_VERSION < desc->version
__xedllport xe_result_t __xecall
  xeDeviceCreateImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a image object.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the image before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this image
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
  xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_IMAGE_H
