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
#include "xe_api.hpp"
#include "xe_api.h"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Image::Image( 
        Device* pDevice,                                ///< [in] pointer to parent object
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
    ///     - The application is responsible for making sure the GPU is not
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
