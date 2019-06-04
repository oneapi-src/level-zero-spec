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
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for image
    class Image
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::image_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image creation flags
        enum class flag_t
        {
            PROGRAM_READ = XE_BIT( 0 ),                     ///< programs will read contents
            PROGRAM_WRITE = XE_BIT( 1 ),                    ///< programs will write contents
            BIAS_CACHED = XE_BIT( 2 ),                      ///< device should cache contents
            BIAS_UNCACHED = XE_BIT( 3 ),                    ///< device should not cache contents

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image types
        enum class type_t
        {
            _1D,                                            ///< 1D
            _1DARRAY,                                       ///< 1D array
            _2D,                                            ///< 2D
            _2DARRAY,                                       ///< 2D array
            _3D,                                            ///< 3D

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format layouts
        enum class format_layout_t
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
            Y8,                                             ///< Media Format: Y8. Format type and swizzle is ignored for this.
            NV12,                                           ///< Media Format: NV12. Format type and swizzle is ignored for this.
            YUYV,                                           ///< Media Format: YUYV. Format type and swizzle is ignored for this.
            VYUY,                                           ///< Media Format: VYUY. Format type and swizzle is ignored for this.
            YVYU,                                           ///< Media Format: YVYU. Format type and swizzle is ignored for this.
            UYVY,                                           ///< Media Format: UYVY. Format type and swizzle is ignored for this.
            AYUV,                                           ///< Media Format: AYUV. Format type and swizzle is ignored for this.
            YUAV,                                           ///< Media Format: YUAV. Format type and swizzle is ignored for this.
            P010,                                           ///< Media Format: P010. Format type and swizzle is ignored for this.
            Y410,                                           ///< Media Format: Y410. Format type and swizzle is ignored for this.
            P012,                                           ///< Media Format: P012. Format type and swizzle is ignored for this.
            Y16,                                            ///< Media Format: Y16. Format type and swizzle is ignored for this.
            P016,                                           ///< Media Format: P016. Format type and swizzle is ignored for this.
            Y216,                                           ///< Media Format: Y216. Format type and swizzle is ignored for this.
            P216,                                           ///< Media Format: P216. Format type and swizzle is ignored for this.
            P416,                                           ///< Media Format: P416. Format type and swizzle is ignored for this.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format types
        enum class format_type_t
        {
            UINT,                                           ///< Unsigned integer
            SINT,                                           ///< Signed integer
            UNORM,                                          ///< Unsigned normalized integer
            SNORM,                                          ///< Signed normalized integer
            FLOAT,                                          ///< Float

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format component swizzle into channel
        enum class format_swizzle_t
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
        /// @brief API version of ::image_properties_t
        enum class properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported sampler filtering flags
        enum class sampler_filter_flags_t
        {
            LINEAR = XE_BIT(0),                             ///< device supports linear filtering

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image format descriptor
        struct format_desc_t
        {
            format_layout_t layout;                         ///< [in] image format component layout
            format_type_t type;                             ///< [in] image format type
            format_swizzle_t x;                             ///< [in] image component swizzle into channel x
            format_swizzle_t y;                             ///< [in] image component swizzle into channel y
            format_swizzle_t z;                             ///< [in] image component swizzle into channel z
            format_swizzle_t w;                             ///< [in] image component swizzle into channel w

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::IMAGE_DESC_VERSION_CURRENT
            flag_t flags;                                   ///< [in] creation flags
            type_t type;                                    ///< [in] image type
            format_desc_t format;                           ///< [in] image format
            size_t width = 0;                               ///< [in] width in pixels, see
                                                            ///< ::device_image_properties_t::maxImageDims1D/2D/3D
            size_t height = 0;                              ///< [in] height in pixels (2D or 3D only), see
                                                            ///< ::device_image_properties_t::maxImageDims2D/3D
            size_t depth = 0;                               ///< [in] depth in pixels (3D only), see
                                                            ///< ::device_image_properties_t::maxImageDims3D
            size_t arraylevels = 1;                         ///< [in] array levels (array types only), see
                                                            ///< ::device_image_properties_t::maxImageArraySlices
            size_t miplevels = 0;                           ///< [in] mipmap levels (must be 0)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image properties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::IMAGE_PROPERTIES_VERSION_CURRENT
            sampler_filter_flags_t samplerFilterFlags;      ///< [out] supported sampler filtering

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        image_handle_t m_handle;                        ///< [in] handle of image object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the image object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Image( void ) = delete;
        Image( 
            image_handle_t handle,                          ///< [in] handle of image object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the image object
            );

        ~Image( void ) = default;

        Image( Image const& other ) = delete;
        void operator=( Image const& other ) = delete;

        Image( Image&& other ) = delete;
        void operator=( Image&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves supported properties of an image.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - properties_t: pointer to image properties
        /// 
        /// @throws result_t
        static properties_t __xecall
        GetProperties(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to image descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a image object on the device.
        /// 
        /// @details
        ///     - The image is only visible to the device on which it was created.
        ///     - The image can be copied to another device using the
        ///       ::::CommandListAppendImageCopy functions.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clCreateImage
        /// @returns
        ///     - Image*: pointer to handle of image object created
        /// 
        /// @throws result_t
        static Image* __xecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to image descriptor
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
        /// @throws result_t
        static void __xecall
        Destroy(
            Image* pImage                                   ///< [in][release] pointer to image object to destroy
            );

    };

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_version_t to std::string
    std::string to_string( const Image::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::flag_t to std::string
    std::string to_string( const Image::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::type_t to std::string
    std::string to_string( const Image::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_layout_t to std::string
    std::string to_string( const Image::format_layout_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_type_t to std::string
    std::string to_string( const Image::format_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_swizzle_t to std::string
    std::string to_string( const Image::format_swizzle_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_desc_t to std::string
    std::string to_string( const Image::format_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_t to std::string
    std::string to_string( const Image::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_version_t to std::string
    std::string to_string( const Image::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::sampler_filter_flags_t to std::string
    std::string to_string( const Image::sampler_filter_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_t to std::string
    std::string to_string( const Image::properties_t val );

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_IMAGE_HPP
