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
        /// @brief C++ version for ::xe_image_format_t
        enum class image_format_t
        {
            UINT8,                                          ///< 8-bit unsigned integer
            UINT16,                                         ///< 16-bit unsigned integer
            UINT32,                                         ///< 32-bit unsigned integer
            SINT8,                                          ///< 8-bit signed integer
            SINT16,                                         ///< 16-bit signed integer
            SINT32,                                         ///< 32-bit signed integer
            UNORM8,                                         ///< 8-bit unsigned normalized integer
            UNORM16,                                        ///< 16-bit unsigned normalized integer
            UNORM32,                                        ///< 32-bit unsigned normalized integer
            SNORM8,                                         ///< 8-bit signed normalized integer
            SNORM16,                                        ///< 16-bit signed normalized integer
            SNORM32,                                        ///< 32-bit signed normalized integer
            FLOAT16,                                        ///< 16-bit float
            FLOAT32,                                        ///< 32-bit float

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
        /// @brief C++ version for ::xe_image_desc_t
        struct image_desc_t
        {
            image_desc_version_t version = image_desc_version_t::CURRENT;   ///< [in] ::IMAGE_DESC_VERSION_CURRENT
            image_flag_t flags;                             ///< [in] creation flags
            image_type_t type;                              ///< [in] image type
            image_format_t format;                          ///< [in] image channel format
            uint32_t numChannels = 1;                       ///< [in] number of channels per pixel [1,4]
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
