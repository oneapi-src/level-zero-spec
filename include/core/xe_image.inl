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
* @file xe_image.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Images
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/image.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_IMAGE_INL
#define _XE_IMAGE_INL
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_image.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Image::Image( 
        Device* pDevice,                                ///< pointer to parent object
        image_handle_t handle,                          ///< handle of image object
        desc_t desc                                     ///< descriptor of the image object
        ) :
        m_pDevice( pDevice ),
        m_handle( handle ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeImageGetProperties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - properties_t: pointer to image properties
    /// 
    /// @throws result_t
    inline Image::properties_t 
    Image::GetProperties(
        Device* hDevice,                                ///< [in] handle of the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        // auto result = ::xeImageGetProperties( handle, hDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Image::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeImageCreate
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
    inline Image* 
    Image::Create(
        Device* hDevice,                                ///< [in] handle of the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        // auto result = ::xeImageCreate( handle, hDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Image::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeImageDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the image before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this image
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same image handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Image::Destroy(
        Image* hImage                                   ///< [in] handle of image object to destroy
        )
    {
        // auto result = ::xeImageDestroy( handle, hImage );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Image::Destroy");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_IMAGE_INL
