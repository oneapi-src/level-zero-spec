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
    auto pfnGetProperties = xe_lib::lib.ddiTable.Image.pfnGetProperties;

#if _DEBUG
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnCreate = xe_lib::lib.ddiTable.Image.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnDestroy = xe_lib::lib.ddiTable.Image.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    ///       ::::CommandListAppendImageCopy functions.
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

#ifdef _DEBUG
namespace std
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::desc_version_t to std::string
    string to_string( const xe::Image::desc_version_t val )
    {
        string str;

        switch( val )
        {
        case xe::Image::desc_version_t::CURRENT:
            str = "xe::Image::desc_version_t::CURRENT";
            break;

        default:
            str = "xe::Image::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::flag_t to std::string
    string to_string( const xe::Image::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return string("{}");

        string str;
        
        if( static_cast<uint32_t>(xe::Image::flag_t::PROGRAM_READ) & bits )
            str += "xe::Image::flag_t::PROGRAM_READ | ";
        
        if( static_cast<uint32_t>(xe::Image::flag_t::PROGRAM_WRITE) & bits )
            str += "xe::Image::flag_t::PROGRAM_WRITE | ";
        
        if( static_cast<uint32_t>(xe::Image::flag_t::BIAS_CACHED) & bits )
            str += "xe::Image::flag_t::BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(xe::Image::flag_t::BIAS_UNCACHED) & bits )
            str += "xe::Image::flag_t::BIAS_UNCACHED | ";

        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::type_t to std::string
    string to_string( const xe::Image::type_t val )
    {
        string str;

        switch( val )
        {
        case xe::Image::type_t::_1D:
            str = "xe::Image::type_t::_1D";
            break;

        case xe::Image::type_t::_1DARRAY:
            str = "xe::Image::type_t::_1DARRAY";
            break;

        case xe::Image::type_t::_2D:
            str = "xe::Image::type_t::_2D";
            break;

        case xe::Image::type_t::_2DARRAY:
            str = "xe::Image::type_t::_2DARRAY";
            break;

        case xe::Image::type_t::_3D:
            str = "xe::Image::type_t::_3D";
            break;

        default:
            str = "xe::Image::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::format_layout_t to std::string
    string to_string( const xe::Image::format_layout_t val )
    {
        string str;

        switch( val )
        {
        case xe::Image::format_layout_t::_8:
            str = "xe::Image::format_layout_t::_8";
            break;

        case xe::Image::format_layout_t::_16:
            str = "xe::Image::format_layout_t::_16";
            break;

        case xe::Image::format_layout_t::_32:
            str = "xe::Image::format_layout_t::_32";
            break;

        case xe::Image::format_layout_t::_8_8:
            str = "xe::Image::format_layout_t::_8_8";
            break;

        case xe::Image::format_layout_t::_8_8_8_8:
            str = "xe::Image::format_layout_t::_8_8_8_8";
            break;

        case xe::Image::format_layout_t::_16_16:
            str = "xe::Image::format_layout_t::_16_16";
            break;

        case xe::Image::format_layout_t::_16_16_16_16:
            str = "xe::Image::format_layout_t::_16_16_16_16";
            break;

        case xe::Image::format_layout_t::_32_32:
            str = "xe::Image::format_layout_t::_32_32";
            break;

        case xe::Image::format_layout_t::_32_32_32_32:
            str = "xe::Image::format_layout_t::_32_32_32_32";
            break;

        case xe::Image::format_layout_t::_10_10_10_2:
            str = "xe::Image::format_layout_t::_10_10_10_2";
            break;

        case xe::Image::format_layout_t::_11_11_10:
            str = "xe::Image::format_layout_t::_11_11_10";
            break;

        case xe::Image::format_layout_t::_5_6_5:
            str = "xe::Image::format_layout_t::_5_6_5";
            break;

        case xe::Image::format_layout_t::_5_5_5_1:
            str = "xe::Image::format_layout_t::_5_5_5_1";
            break;

        case xe::Image::format_layout_t::_4_4_4_4:
            str = "xe::Image::format_layout_t::_4_4_4_4";
            break;

        case xe::Image::format_layout_t::Y8:
            str = "xe::Image::format_layout_t::Y8";
            break;

        case xe::Image::format_layout_t::NV12:
            str = "xe::Image::format_layout_t::NV12";
            break;

        case xe::Image::format_layout_t::YUYV:
            str = "xe::Image::format_layout_t::YUYV";
            break;

        case xe::Image::format_layout_t::VYUY:
            str = "xe::Image::format_layout_t::VYUY";
            break;

        case xe::Image::format_layout_t::YVYU:
            str = "xe::Image::format_layout_t::YVYU";
            break;

        case xe::Image::format_layout_t::UYVY:
            str = "xe::Image::format_layout_t::UYVY";
            break;

        case xe::Image::format_layout_t::AYUV:
            str = "xe::Image::format_layout_t::AYUV";
            break;

        case xe::Image::format_layout_t::YUAV:
            str = "xe::Image::format_layout_t::YUAV";
            break;

        case xe::Image::format_layout_t::P010:
            str = "xe::Image::format_layout_t::P010";
            break;

        case xe::Image::format_layout_t::Y410:
            str = "xe::Image::format_layout_t::Y410";
            break;

        case xe::Image::format_layout_t::P012:
            str = "xe::Image::format_layout_t::P012";
            break;

        case xe::Image::format_layout_t::Y16:
            str = "xe::Image::format_layout_t::Y16";
            break;

        case xe::Image::format_layout_t::P016:
            str = "xe::Image::format_layout_t::P016";
            break;

        case xe::Image::format_layout_t::Y216:
            str = "xe::Image::format_layout_t::Y216";
            break;

        case xe::Image::format_layout_t::P216:
            str = "xe::Image::format_layout_t::P216";
            break;

        case xe::Image::format_layout_t::P416:
            str = "xe::Image::format_layout_t::P416";
            break;

        default:
            str = "xe::Image::format_layout_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::format_type_t to std::string
    string to_string( const xe::Image::format_type_t val )
    {
        string str;

        switch( val )
        {
        case xe::Image::format_type_t::UINT:
            str = "xe::Image::format_type_t::UINT";
            break;

        case xe::Image::format_type_t::SINT:
            str = "xe::Image::format_type_t::SINT";
            break;

        case xe::Image::format_type_t::UNORM:
            str = "xe::Image::format_type_t::UNORM";
            break;

        case xe::Image::format_type_t::SNORM:
            str = "xe::Image::format_type_t::SNORM";
            break;

        case xe::Image::format_type_t::FLOAT:
            str = "xe::Image::format_type_t::FLOAT";
            break;

        default:
            str = "xe::Image::format_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::format_swizzle_t to std::string
    string to_string( const xe::Image::format_swizzle_t val )
    {
        string str;

        switch( val )
        {
        case xe::Image::format_swizzle_t::R:
            str = "xe::Image::format_swizzle_t::R";
            break;

        case xe::Image::format_swizzle_t::G:
            str = "xe::Image::format_swizzle_t::G";
            break;

        case xe::Image::format_swizzle_t::B:
            str = "xe::Image::format_swizzle_t::B";
            break;

        case xe::Image::format_swizzle_t::A:
            str = "xe::Image::format_swizzle_t::A";
            break;

        case xe::Image::format_swizzle_t::_0:
            str = "xe::Image::format_swizzle_t::_0";
            break;

        case xe::Image::format_swizzle_t::_1:
            str = "xe::Image::format_swizzle_t::_1";
            break;

        case xe::Image::format_swizzle_t::X:
            str = "xe::Image::format_swizzle_t::X";
            break;

        default:
            str = "xe::Image::format_swizzle_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::properties_version_t to std::string
    string to_string( const xe::Image::properties_version_t val )
    {
        string str;

        switch( val )
        {
        case xe::Image::properties_version_t::CURRENT:
            str = "xe::Image::properties_version_t::CURRENT";
            break;

        default:
            str = "xe::Image::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::sampler_filter_flags_t to std::string
    string to_string( const xe::Image::sampler_filter_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return string("{}");

        string str;
        
        if( static_cast<uint32_t>(xe::Image::sampler_filter_flags_t::LINEAR) & bits )
            str += "xe::Image::sampler_filter_flags_t::LINEAR | ";

        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::format_desc_t to std::string
    string to_string( const xe::Image::format_desc_t val )
    {
        string str;
        
        str += "xe::Image::format_desc_t::layout : ";
        str += to_string(val.layout);
        str += "\n";
        
        str += "xe::Image::format_desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "xe::Image::format_desc_t::x : ";
        str += to_string(val.x);
        str += "\n";
        
        str += "xe::Image::format_desc_t::y : ";
        str += to_string(val.y);
        str += "\n";
        
        str += "xe::Image::format_desc_t::z : ";
        str += to_string(val.z);
        str += "\n";
        
        str += "xe::Image::format_desc_t::w : ";
        str += to_string(val.w);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::desc_t to std::string
    string to_string( const xe::Image::desc_t val )
    {
        string str;
        
        str += "xe::Image::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "xe::Image::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "xe::Image::desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "xe::Image::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "xe::Image::desc_t::width : ";
        str += to_string(val.width);
        str += "\n";
        
        str += "xe::Image::desc_t::height : ";
        str += to_string(val.height);
        str += "\n";
        
        str += "xe::Image::desc_t::depth : ";
        str += to_string(val.depth);
        str += "\n";
        
        str += "xe::Image::desc_t::arraylevels : ";
        str += to_string(val.arraylevels);
        str += "\n";
        
        str += "xe::Image::desc_t::miplevels : ";
        str += to_string(val.miplevels);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::Image::properties_t to std::string
    string to_string( const xe::Image::properties_t val )
    {
        string str;
        
        str += "xe::Image::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "xe::Image::properties_t::samplerFilterFlags : ";
        str += to_string(val.samplerFilterFlags);
        str += "\n";

        return str;
    }

} // namespace std
#endif // _DEBUG
