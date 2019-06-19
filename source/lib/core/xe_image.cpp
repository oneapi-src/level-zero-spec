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
* @file xe_image.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Images
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/image.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

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
    )
{
    auto pfnGetProperties = xe_lib::context.ddiTable.Image.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hDevice, desc, pImageProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a image object on the device.
/// 
/// @details
///     - The image is only visible to the device on which it was created.
///     - The image can be copied to another device using the
///       ::::xeCommandListAppendImageCopy functions.
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
    )
{
    auto pfnCreate = xe_lib::context.ddiTable.Image.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDevice, desc, phImage );
}

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
    xe_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
    )
{
    auto pfnDestroy = xe_lib::context.ddiTable.Image.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hImage );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Image::Image( 
        image_handle_t handle,                          ///< [in] handle of image object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the image object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves supported properties of an image.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - properties_t: pointer to image properties
    /// 
    /// @throws result_t
    Image::properties_t __xecall
    Image::GetProperties(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        xe_image_properties_t imageProperties;

        auto result = static_cast<result_t>( ::xeImageGetProperties(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const xe_image_desc_t*>( desc ),
            &imageProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Image::GetProperties" );

        return *reinterpret_cast<properties_t*>( &imageProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a image object on the device.
    /// 
    /// @details
    ///     - The image is only visible to the device on which it was created.
    ///     - The image can be copied to another device using the
    ///       ::::xeCommandListAppendImageCopy functions.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clCreateImage
    /// 
    /// @returns
    ///     - Image*: pointer to handle of image object created
    /// 
    /// @throws result_t
    Image* __xecall
    Image::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        xe_image_handle_t hImage;

        auto result = static_cast<result_t>( ::xeImageCreate(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const xe_image_desc_t*>( desc ),
            &hImage ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Image::Create" );

        Image* pImage = nullptr;

        try
        {
            pImage = new Image( reinterpret_cast<image_handle_t>( hImage ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pImage;
            pImage = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Image::Create" );
        }

        return pImage;
    }

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
    /// @throws result_t
    void __xecall
    Image::Destroy(
        Image* pImage                                   ///< [in][release] pointer to image object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xeImageDestroy(
            reinterpret_cast<xe_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Image::Destroy" );

        delete pImage;
    }

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_version_t to std::string
    std::string to_string( const Image::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::desc_version_t::CURRENT:
            str = "Image::desc_version_t::CURRENT";
            break;

        default:
            str = "Image::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::flag_t to std::string
    std::string to_string( const Image::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(Image::flag_t::PROGRAM_READ) & bits )
            str += "PROGRAM_READ | ";
        
        if( static_cast<uint32_t>(Image::flag_t::PROGRAM_WRITE) & bits )
            str += "PROGRAM_WRITE | ";
        
        if( static_cast<uint32_t>(Image::flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Image::flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";

        return ( str.size() > 3 ) 
            ? "Image::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Image::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::type_t to std::string
    std::string to_string( const Image::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::type_t::_1D:
            str = "Image::type_t::_1D";
            break;

        case Image::type_t::_1DARRAY:
            str = "Image::type_t::_1DARRAY";
            break;

        case Image::type_t::_2D:
            str = "Image::type_t::_2D";
            break;

        case Image::type_t::_2DARRAY:
            str = "Image::type_t::_2DARRAY";
            break;

        case Image::type_t::_3D:
            str = "Image::type_t::_3D";
            break;

        default:
            str = "Image::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_layout_t to std::string
    std::string to_string( const Image::format_layout_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_layout_t::_8:
            str = "Image::format_layout_t::_8";
            break;

        case Image::format_layout_t::_16:
            str = "Image::format_layout_t::_16";
            break;

        case Image::format_layout_t::_32:
            str = "Image::format_layout_t::_32";
            break;

        case Image::format_layout_t::_8_8:
            str = "Image::format_layout_t::_8_8";
            break;

        case Image::format_layout_t::_8_8_8_8:
            str = "Image::format_layout_t::_8_8_8_8";
            break;

        case Image::format_layout_t::_16_16:
            str = "Image::format_layout_t::_16_16";
            break;

        case Image::format_layout_t::_16_16_16_16:
            str = "Image::format_layout_t::_16_16_16_16";
            break;

        case Image::format_layout_t::_32_32:
            str = "Image::format_layout_t::_32_32";
            break;

        case Image::format_layout_t::_32_32_32_32:
            str = "Image::format_layout_t::_32_32_32_32";
            break;

        case Image::format_layout_t::_10_10_10_2:
            str = "Image::format_layout_t::_10_10_10_2";
            break;

        case Image::format_layout_t::_11_11_10:
            str = "Image::format_layout_t::_11_11_10";
            break;

        case Image::format_layout_t::_5_6_5:
            str = "Image::format_layout_t::_5_6_5";
            break;

        case Image::format_layout_t::_5_5_5_1:
            str = "Image::format_layout_t::_5_5_5_1";
            break;

        case Image::format_layout_t::_4_4_4_4:
            str = "Image::format_layout_t::_4_4_4_4";
            break;

        case Image::format_layout_t::Y8:
            str = "Image::format_layout_t::Y8";
            break;

        case Image::format_layout_t::NV12:
            str = "Image::format_layout_t::NV12";
            break;

        case Image::format_layout_t::YUYV:
            str = "Image::format_layout_t::YUYV";
            break;

        case Image::format_layout_t::VYUY:
            str = "Image::format_layout_t::VYUY";
            break;

        case Image::format_layout_t::YVYU:
            str = "Image::format_layout_t::YVYU";
            break;

        case Image::format_layout_t::UYVY:
            str = "Image::format_layout_t::UYVY";
            break;

        case Image::format_layout_t::AYUV:
            str = "Image::format_layout_t::AYUV";
            break;

        case Image::format_layout_t::YUAV:
            str = "Image::format_layout_t::YUAV";
            break;

        case Image::format_layout_t::P010:
            str = "Image::format_layout_t::P010";
            break;

        case Image::format_layout_t::Y410:
            str = "Image::format_layout_t::Y410";
            break;

        case Image::format_layout_t::P012:
            str = "Image::format_layout_t::P012";
            break;

        case Image::format_layout_t::Y16:
            str = "Image::format_layout_t::Y16";
            break;

        case Image::format_layout_t::P016:
            str = "Image::format_layout_t::P016";
            break;

        case Image::format_layout_t::Y216:
            str = "Image::format_layout_t::Y216";
            break;

        case Image::format_layout_t::P216:
            str = "Image::format_layout_t::P216";
            break;

        case Image::format_layout_t::P416:
            str = "Image::format_layout_t::P416";
            break;

        default:
            str = "Image::format_layout_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_type_t to std::string
    std::string to_string( const Image::format_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_type_t::UINT:
            str = "Image::format_type_t::UINT";
            break;

        case Image::format_type_t::SINT:
            str = "Image::format_type_t::SINT";
            break;

        case Image::format_type_t::UNORM:
            str = "Image::format_type_t::UNORM";
            break;

        case Image::format_type_t::SNORM:
            str = "Image::format_type_t::SNORM";
            break;

        case Image::format_type_t::FLOAT:
            str = "Image::format_type_t::FLOAT";
            break;

        default:
            str = "Image::format_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_swizzle_t to std::string
    std::string to_string( const Image::format_swizzle_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_swizzle_t::R:
            str = "Image::format_swizzle_t::R";
            break;

        case Image::format_swizzle_t::G:
            str = "Image::format_swizzle_t::G";
            break;

        case Image::format_swizzle_t::B:
            str = "Image::format_swizzle_t::B";
            break;

        case Image::format_swizzle_t::A:
            str = "Image::format_swizzle_t::A";
            break;

        case Image::format_swizzle_t::_0:
            str = "Image::format_swizzle_t::_0";
            break;

        case Image::format_swizzle_t::_1:
            str = "Image::format_swizzle_t::_1";
            break;

        case Image::format_swizzle_t::X:
            str = "Image::format_swizzle_t::X";
            break;

        default:
            str = "Image::format_swizzle_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_version_t to std::string
    std::string to_string( const Image::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::properties_version_t::CURRENT:
            str = "Image::properties_version_t::CURRENT";
            break;

        default:
            str = "Image::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::sampler_filter_flags_t to std::string
    std::string to_string( const Image::sampler_filter_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Image::sampler_filter_flags_t::POINT) & bits )
            str += "POINT | ";
        
        if( static_cast<uint32_t>(Image::sampler_filter_flags_t::LINEAR) & bits )
            str += "LINEAR | ";

        return ( str.size() > 3 ) 
            ? "Image::sampler_filter_flags_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Image::sampler_filter_flags_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_desc_t to std::string
    std::string to_string( const Image::format_desc_t val )
    {
        std::string str;
        
        str += "Image::format_desc_t::layout : ";
        str += to_string(val.layout);
        str += "\n";
        
        str += "Image::format_desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Image::format_desc_t::x : ";
        str += to_string(val.x);
        str += "\n";
        
        str += "Image::format_desc_t::y : ";
        str += to_string(val.y);
        str += "\n";
        
        str += "Image::format_desc_t::z : ";
        str += to_string(val.z);
        str += "\n";
        
        str += "Image::format_desc_t::w : ";
        str += to_string(val.w);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_t to std::string
    std::string to_string( const Image::desc_t val )
    {
        std::string str;
        
        str += "Image::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Image::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Image::desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Image::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Image::desc_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "Image::desc_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "Image::desc_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";
        
        str += "Image::desc_t::arraylevels : ";
        str += std::to_string(val.arraylevels);
        str += "\n";
        
        str += "Image::desc_t::miplevels : ";
        str += std::to_string(val.miplevels);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_t to std::string
    std::string to_string( const Image::properties_t val )
    {
        std::string str;
        
        str += "Image::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Image::properties_t::samplerFilterFlags : ";
        str += to_string(val.samplerFilterFlags);
        str += "\n";

        return str;
    }

} // namespace xe
