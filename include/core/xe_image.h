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
* @brief Intel Xe Level-Zero APIs for Images
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
#if !defined(_XE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_image_desc_t
typedef enum _xe_image_desc_version_t
{
    XE_IMAGE_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),///< version 1.0

} xe_image_desc_version_t;

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
/// @brief Supported image format layouts
typedef enum _xe_image_format_layout_t
{
    XE_IMAGE_FORMAT_LAYOUT_8,                       ///< 8-bit single component layout
    XE_IMAGE_FORMAT_LAYOUT_16,                      ///< 16-bit single component layout
    XE_IMAGE_FORMAT_LAYOUT_32,                      ///< 32-bit single component layout
    XE_IMAGE_FORMAT_LAYOUT_8_8,                     ///< 2-component 8-bit layout
    XE_IMAGE_FORMAT_LAYOUT_8_8_8_8,                 ///< 4-component 8-bit layout
    XE_IMAGE_FORMAT_LAYOUT_16_16,                   ///< 2-component 16-bit layout
    XE_IMAGE_FORMAT_LAYOUT_16_16_16_16,             ///< 4-component 16-bit layout
    XE_IMAGE_FORMAT_LAYOUT_32_32,                   ///< 2-component 32-bit layout
    XE_IMAGE_FORMAT_LAYOUT_32_32_32_32,             ///< 4-component 32-bit layout
    XE_IMAGE_FORMAT_LAYOUT_10_10_10_2,              ///< 4-component 10_10_10_2 layout
    XE_IMAGE_FORMAT_LAYOUT_11_11_10,                ///< 3-component 11_11_10 layout
    XE_IMAGE_FORMAT_LAYOUT_5_6_5,                   ///< 3-component 5_6_5 layout
    XE_IMAGE_FORMAT_LAYOUT_5_5_5_1,                 ///< 4-component 5_5_5_1 layout
    XE_IMAGE_FORMAT_LAYOUT_4_4_4_4,                 ///< 4-component 4_4_4_4 layout
    XE_IMAGE_FORMAT_LAYOUT_Y8,                      ///< Media Format: Y8. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_NV12,                    ///< Media Format: NV12. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_YUYV,                    ///< Media Format: YUYV. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_VYUY,                    ///< Media Format: VYUY. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_YVYU,                    ///< Media Format: YVYU. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_UYVY,                    ///< Media Format: UYVY. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_AYUV,                    ///< Media Format: AYUV. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_YUAV,                    ///< Media Format: YUAV. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_P010,                    ///< Media Format: P010. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_Y410,                    ///< Media Format: Y410. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_P012,                    ///< Media Format: P012. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_Y16,                     ///< Media Format: Y16. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_P016,                    ///< Media Format: P016. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_Y216,                    ///< Media Format: Y216. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_P216,                    ///< Media Format: P216. Format type and swizzle is ignored for this.
    XE_IMAGE_FORMAT_LAYOUT_P416,                    ///< Media Format: P416. Format type and swizzle is ignored for this.

} xe_image_format_layout_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format types
typedef enum _xe_image_format_type_t
{
    XE_IMAGE_FORMAT_TYPE_UINT,                      ///< Unsigned integer
    XE_IMAGE_FORMAT_TYPE_SINT,                      ///< Signed integer
    XE_IMAGE_FORMAT_TYPE_UNORM,                     ///< Unsigned normalized integer
    XE_IMAGE_FORMAT_TYPE_SNORM,                     ///< Signed normalized integer
    XE_IMAGE_FORMAT_TYPE_FLOAT,                     ///< Float

} xe_image_format_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported image format component swizzle into channel
typedef enum _xe_image_format_swizzle_t
{
    XE_IMAGE_FORMAT_SWIZZLE_R,                      ///< Red component
    XE_IMAGE_FORMAT_SWIZZLE_G,                      ///< Green component
    XE_IMAGE_FORMAT_SWIZZLE_B,                      ///< Blue component
    XE_IMAGE_FORMAT_SWIZZLE_A,                      ///< Alpha component
    XE_IMAGE_FORMAT_SWIZZLE_0,                      ///< Zero
    XE_IMAGE_FORMAT_SWIZZLE_1,                      ///< One
    XE_IMAGE_FORMAT_SWIZZLE_X,                      ///< Don't care

} xe_image_format_swizzle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image format descriptor
typedef struct _xe_image_format_desc_t
{
    xe_image_format_layout_t layout;                ///< [in] image format component layout
    xe_image_format_type_t type;                    ///< [in] image format type
    xe_image_format_swizzle_t x;                    ///< [in] image component swizzle into channel x
    xe_image_format_swizzle_t y;                    ///< [in] image component swizzle into channel y
    xe_image_format_swizzle_t z;                    ///< [in] image component swizzle into channel z
    xe_image_format_swizzle_t w;                    ///< [in] image component swizzle into channel w

} xe_image_format_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image descriptor
typedef struct _xe_image_desc_t
{
    xe_image_desc_version_t version;                ///< [in] ::XE_IMAGE_DESC_VERSION_CURRENT
    xe_image_flag_t flags;                          ///< [in] creation flags
    xe_image_type_t type;                           ///< [in] image type
    xe_image_format_desc_t format;                  ///< [in] image format
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
/// @brief API version of ::xe_image_properties_t
typedef enum _xe_image_properties_version_t
{
    XE_IMAGE_PROPERTIES_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xe_image_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported sampler filtering flags
typedef enum _xe_image_sampler_filter_flags_t
{
    XE_IMAGE_SAMPLER_FILTER_FLAGS_LINEAR = XE_BIT(0),   ///< device supports linear filtering

} xe_image_sampler_filter_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Image properties
typedef struct _xe_image_properties_t
{
    xe_image_properties_version_t version;          ///< [in] ::XE_IMAGE_PROPERTIES_VERSION_CURRENT
    xe_image_sampler_filter_flags_t samplerFilterFlags; ///< [out] supported sampler filtering

} xe_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves supported properties of an image.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == pImageProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_IMAGE_DESC_VERSION_CURRENT < desc->version
xe_result_t __xecall
xeImageGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    );

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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_IMAGE_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeImageCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a image object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the image before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this image
///     - The application may **not** call this function from simultaneous
///       threads with the same image handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_IMAGE_H
