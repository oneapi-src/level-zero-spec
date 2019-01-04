/**************************************************************************//**
* 
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
* 
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
* 
* @file xe_device.h
* 
* @brief Intel Xe Driver APIs for Device
* 
******************************************************************************/
#ifndef _XE_DEVICE_H
#define _XE_DEVICE_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Reports the number of devices
/// @details _replaces cuDeviceGetCount_
xe_result_t __xecall
  xeDeviceGetCount(
    uint32_t* count                 ///< [out] number of devices available
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a handle to the device object
/// @details _replaces cuDeviceGet_
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeDeviceGet( 
    uint32_t ordinal,               ///< [in] ordinal of device to retrieve
    xe_device_handle_t* phDevice    ///< [out] pointer to handle of device object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines API versions
/// @details API versions contain major and minor attributes,
///     use XE_MAJOR_VERSION and XE_MINOR_VERSION
XE_DECLARE_ENUM( xe_api_version_t )
{
    XE_API_VERSION_1_0 = XE_MAKE_VERSION( 1, 0 )
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the device
/// @details _replaces cuCtxGetApiVersion_
xe_result_t __xecall
  xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,     ///< [in] handle of the device object
    xe_api_version_t* version       ///< [out] api version
    );


///////////////////////////////////////////////////////////////////////////////
XE_DECLARE_ENUM( xe_device_attribute_t )
{
    XE_DEVICE_ATTRIBUTE_MAX_THREADS = 1,            ///< maximum number of threads supported
    XE_DEVICE_ATTRIBUTE_MAX_SIMULTANEOUS_QUEUES,    ///< maximum number of command queues that can execute in parallel
    XE_DEVICE_ATTRIBUTE_TOTAL_MEMORY,               ///< total amount of memory available, in megabytes
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves an attribute of the device
/// @details _replaces cuDeviceGetAttribute and cuDeviceTotalMem_
xe_result_t __xecall
  xeDeviceGetAttribute(
    xe_device_handle_t hDevice,         ///< [in] handle of the device object
    xe_device_attribute_t attribute,    ///< [in] attribute to query
    uint32_t* value                     ///< [out] value of the attribute
    );
    
#endif // _XE_DEVICE_H