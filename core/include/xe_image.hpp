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
* @file xe_image.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Images
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/image.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_IMAGE_HPP
#define _XE_IMAGE_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for image
    class Image
    {
    protected:
        ::xe_image_handle_t handle;                       ///< handle of image object
        ::xe_image_desc_t desc;                           ///< descriptor of the image object

    public:
        auto getHandle( void ) const { return handle; }
        auto getDesc( void ) const { return desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_desc_version_t
        enum class image_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_flag_t
        enum class image_flag_t
        {
            PROGRAM_READ = XE_BIT( 0 ),                     ///< programs will read contents
            PROGRAM_WRITE = XE_BIT( 1 ),                    ///< programs will write contents
            BIAS_CACHED = XE_BIT( 2 ),                      ///< device should cache contents
            BIAS_UNCACHED = XE_BIT( 3 ),                    ///< device should not cache contents

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_type_t
        enum class image_type_t
        {
            _1D,                                            ///< 1D
            _1DARRAY,                                       ///< 1D array
            _2D,                                            ///< 2D
            _2DARRAY,                                       ///< 2D array
            _3D,                                            ///< 3D

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_format_layout_t
        enum class image_format_layout_t
        {
            _8,                                             ///< 8-bit single component layout
            _16,                                            ///< 16-bit single component layout
            _32,                                            ///< 32-bit single component layout
            _8_8,                                           ///< 2-component 8-bit layout
            _8_8_8_8,                                       ///< 4-component 8-bit layout
            _16_16,                                         ///< 2-component 16-bit layout
            _16_16_16_16,                                   ///< 4-component 16-bit layout
            _32_32,                                         ///< 2-component 32-bit layout
            _32_32_32_32,                                   ///< 4-component 32-bit layout
            _10_10_10_2,                                    ///< 4-component 10_10_10_2 layout
            _11_11_10,                                      ///< 3-component 11_11_10 layout
            _5_6_5,                                         ///< 3-component 5_6_5 layout
            _5_5_5_1,                                       ///< 4-component 5_5_5_1 layout
            _4_4_4_4,                                       ///< 4-component 4_4_4_4 layout

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_format_type_t
        enum class image_format_type_t
        {
            UINT,                                           ///< Unsigned integer
            SINT,                                           ///< Signed integer
            UNORM,                                          ///< Unsigned normalized integer
            SNORM,                                          ///< Signed normalized integer
            FLOAT,                                          ///< Float

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_format_swizzle_t
        enum class image_format_swizzle_t
        {
            R,                                              ///< Red component
            G,                                              ///< Green component
            B,                                              ///< Blue component
            A,                                              ///< Alpha component
            _0,                                             ///< Zero
            _1,                                             ///< One
            X,                                              ///< Don't care

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_properties_version_t
        enum class image_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_sampler_filter_flags_t
        enum class image_sampler_filter_flags_t
        {
            LINEAR = XE_BIT(0),                             ///< device supports linear filtering

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_format_desc_t
        struct image_format_desc_t
        {
            image_format_layout_t layout;                   ///< [in] image format component layout
            image_format_type_t type;                       ///< [in] image format type
            image_format_swizzle_t x;                       ///< [in] image component swizzle into channel x
            image_format_swizzle_t y;                       ///< [in] image component swizzle into channel y
            image_format_swizzle_t z;                       ///< [in] image component swizzle into channel z
            image_format_swizzle_t w;                       ///< [in] image component swizzle into channel w

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_desc_t
        struct image_desc_t
        {
            image_desc_version_t version = image_desc_version_t::CURRENT;   ///< [in] ::IMAGE_DESC_VERSION_CURRENT
            image_flag_t flags;                             ///< [in] creation flags
            image_type_t type;                              ///< [in] image type
            image_format_desc_t format;                     ///< [in] image format
            size_t width = 0;                               ///< [in] width in pixels, see
                                                            ///< ::device_memory_properties_t::maxImageDims1D/2D/3D
            size_t height = 0;                              ///< [in] height in pixels (2D or 3D only), see
                                                            ///< ::device_memory_properties_t::maxImageDims2D/3D
            size_t depth = 0;                               ///< [in] depth in pixels (3D only), see
                                                            ///< ::device_memory_properties_t::maxImageDims3D
            size_t arraylevels = 1;                         ///< [in] array levels (array types only), see
                                                            ///< ::device_memory_properties_t::maxImageArraySlices
            size_t miplevels = 0;                           ///< [in] mipmap levels (must be 0)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_properties_t
        struct image_properties_t
        {
            image_properties_version_t version = image_properties_version_t::CURRENT;   ///< [in] ::IMAGE_PROPERTIES_VERSION_CURRENT
            image_sampler_filter_flags_t samplerFilterFlags;///< [out] supported sampler filtering

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeImageGetProperties
        /// @returns
        ///     - ::image_properties_t: pointer to image properties
        /// 
        /// @throws result_t
        inline static image_properties_t
        GetProperties(
            device_handle_t hDevice,                        ///< [in] handle of the device
            const image_desc_t* desc                        ///< [in] pointer to image descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeImageCreate
        /// @returns
        ///     - ::image_handle_t: pointer to handle of image object created
        /// 
        /// @throws result_t
        inline static image_handle_t
        Create(
            device_handle_t hDevice,                        ///< [in] handle of the device
            const image_desc_t* desc                        ///< [in] pointer to image descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeImageDestroy
        /// @throws result_t
        inline static void
        Destroy(
            image_handle_t hImage                           ///< [in] handle of image object to destroy
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_IMAGE_HPP
