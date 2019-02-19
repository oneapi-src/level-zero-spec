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
* @brief Intel Xe Driver APIs for Images
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/image.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_image.h"

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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_IMAGE_DESC_VERSION <= desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCreateImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phImage, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_IMAGE_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hImage, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

