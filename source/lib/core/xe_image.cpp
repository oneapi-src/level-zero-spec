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
    auto pfnGetProperties = xe_lib::lib.xeImage.pfnGetProperties;

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
    auto pfnCreate = xe_lib::lib.xeImage.pfnCreate;

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
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    auto pfnDestroy = xe_lib::lib.xeImage.pfnDestroy;

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
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t& desc                              ///< [in] descriptor of the image object
        ) :
        m_pDevice( pDevice ),
        m_desc( desc )
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
        // auto result = ::xeImageGetProperties( handle, pDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Image::GetProperties");

        return properties_t{};
    }

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
    ///     - Image: pointer to handle of image object created
    /// 
    /// @throws result_t
    Image* __xecall
    Image::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        // auto result = ::xeImageCreate( handle, pDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Image::Create");

        return (Image*)0;
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
        Image* pImage                                   ///< [in] pointer to image object to destroy
        )
    {
        // auto result = ::xeImageDestroy( handle, pImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Image::Destroy");
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_version_t to std::string
    std::string to_string( xe::Image::desc_version_t val )
    {
        switch( val )
        {
        case xe::Image::desc_version_t::CURRENT:
            return std::string("xe::Image::desc_version_t::CURRENT");
        };
        return std::string("xe::Image::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::flag_t to std::string
    std::string to_string( xe::Image::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
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
    /// @brief Converts Image::type_t to std::string
    std::string to_string( xe::Image::type_t val )
    {
        switch( val )
        {
        case xe::Image::type_t::_1D:
            return std::string("xe::Image::type_t::_1D");
        case xe::Image::type_t::_1DARRAY:
            return std::string("xe::Image::type_t::_1DARRAY");
        case xe::Image::type_t::_2D:
            return std::string("xe::Image::type_t::_2D");
        case xe::Image::type_t::_2DARRAY:
            return std::string("xe::Image::type_t::_2DARRAY");
        case xe::Image::type_t::_3D:
            return std::string("xe::Image::type_t::_3D");
        };
        return std::string("xe::Image::type_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_layout_t to std::string
    std::string to_string( xe::Image::format_layout_t val )
    {
        switch( val )
        {
        case xe::Image::format_layout_t::_8:
            return std::string("xe::Image::format_layout_t::_8");
        case xe::Image::format_layout_t::_16:
            return std::string("xe::Image::format_layout_t::_16");
        case xe::Image::format_layout_t::_32:
            return std::string("xe::Image::format_layout_t::_32");
        case xe::Image::format_layout_t::_8_8:
            return std::string("xe::Image::format_layout_t::_8_8");
        case xe::Image::format_layout_t::_8_8_8_8:
            return std::string("xe::Image::format_layout_t::_8_8_8_8");
        case xe::Image::format_layout_t::_16_16:
            return std::string("xe::Image::format_layout_t::_16_16");
        case xe::Image::format_layout_t::_16_16_16_16:
            return std::string("xe::Image::format_layout_t::_16_16_16_16");
        case xe::Image::format_layout_t::_32_32:
            return std::string("xe::Image::format_layout_t::_32_32");
        case xe::Image::format_layout_t::_32_32_32_32:
            return std::string("xe::Image::format_layout_t::_32_32_32_32");
        case xe::Image::format_layout_t::_10_10_10_2:
            return std::string("xe::Image::format_layout_t::_10_10_10_2");
        case xe::Image::format_layout_t::_11_11_10:
            return std::string("xe::Image::format_layout_t::_11_11_10");
        case xe::Image::format_layout_t::_5_6_5:
            return std::string("xe::Image::format_layout_t::_5_6_5");
        case xe::Image::format_layout_t::_5_5_5_1:
            return std::string("xe::Image::format_layout_t::_5_5_5_1");
        case xe::Image::format_layout_t::_4_4_4_4:
            return std::string("xe::Image::format_layout_t::_4_4_4_4");
        case xe::Image::format_layout_t::Y8:
            return std::string("xe::Image::format_layout_t::Y8");
        case xe::Image::format_layout_t::NV12:
            return std::string("xe::Image::format_layout_t::NV12");
        case xe::Image::format_layout_t::YUYV:
            return std::string("xe::Image::format_layout_t::YUYV");
        case xe::Image::format_layout_t::VYUY:
            return std::string("xe::Image::format_layout_t::VYUY");
        case xe::Image::format_layout_t::YVYU:
            return std::string("xe::Image::format_layout_t::YVYU");
        case xe::Image::format_layout_t::UYVY:
            return std::string("xe::Image::format_layout_t::UYVY");
        case xe::Image::format_layout_t::AYUV:
            return std::string("xe::Image::format_layout_t::AYUV");
        case xe::Image::format_layout_t::YUAV:
            return std::string("xe::Image::format_layout_t::YUAV");
        case xe::Image::format_layout_t::P010:
            return std::string("xe::Image::format_layout_t::P010");
        case xe::Image::format_layout_t::Y410:
            return std::string("xe::Image::format_layout_t::Y410");
        case xe::Image::format_layout_t::P012:
            return std::string("xe::Image::format_layout_t::P012");
        case xe::Image::format_layout_t::Y16:
            return std::string("xe::Image::format_layout_t::Y16");
        case xe::Image::format_layout_t::P016:
            return std::string("xe::Image::format_layout_t::P016");
        case xe::Image::format_layout_t::Y216:
            return std::string("xe::Image::format_layout_t::Y216");
        case xe::Image::format_layout_t::P216:
            return std::string("xe::Image::format_layout_t::P216");
        case xe::Image::format_layout_t::P416:
            return std::string("xe::Image::format_layout_t::P416");
        };
        return std::string("xe::Image::format_layout_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_type_t to std::string
    std::string to_string( xe::Image::format_type_t val )
    {
        switch( val )
        {
        case xe::Image::format_type_t::UINT:
            return std::string("xe::Image::format_type_t::UINT");
        case xe::Image::format_type_t::SINT:
            return std::string("xe::Image::format_type_t::SINT");
        case xe::Image::format_type_t::UNORM:
            return std::string("xe::Image::format_type_t::UNORM");
        case xe::Image::format_type_t::SNORM:
            return std::string("xe::Image::format_type_t::SNORM");
        case xe::Image::format_type_t::FLOAT:
            return std::string("xe::Image::format_type_t::FLOAT");
        };
        return std::string("xe::Image::format_type_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_swizzle_t to std::string
    std::string to_string( xe::Image::format_swizzle_t val )
    {
        switch( val )
        {
        case xe::Image::format_swizzle_t::R:
            return std::string("xe::Image::format_swizzle_t::R");
        case xe::Image::format_swizzle_t::G:
            return std::string("xe::Image::format_swizzle_t::G");
        case xe::Image::format_swizzle_t::B:
            return std::string("xe::Image::format_swizzle_t::B");
        case xe::Image::format_swizzle_t::A:
            return std::string("xe::Image::format_swizzle_t::A");
        case xe::Image::format_swizzle_t::_0:
            return std::string("xe::Image::format_swizzle_t::_0");
        case xe::Image::format_swizzle_t::_1:
            return std::string("xe::Image::format_swizzle_t::_1");
        case xe::Image::format_swizzle_t::X:
            return std::string("xe::Image::format_swizzle_t::X");
        };
        return std::string("xe::Image::format_swizzle_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_version_t to std::string
    std::string to_string( xe::Image::properties_version_t val )
    {
        switch( val )
        {
        case xe::Image::properties_version_t::CURRENT:
            return std::string("xe::Image::properties_version_t::CURRENT");
        };
        return std::string("xe::Image::properties_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::sampler_filter_flags_t to std::string
    std::string to_string( xe::Image::sampler_filter_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::Image::sampler_filter_flags_t::LINEAR) & bits )
            str += "xe::Image::sampler_filter_flags_t::LINEAR | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }


#endif // _DEBUG
