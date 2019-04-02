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
* @file xet_metric.cpp
*
* @brief Intel Xe Level-Zero Tool APIs for Metric
*
* DO NOT EDIT: generated from /scripts/tools/metric.yml
*
******************************************************************************/
#if defined(XET_CPP)
#include "../include/xet_metric.hpp"
#else
#include "../include/xet_metric.h"
#endif
#if !defined(XET_NULLDRV)
#include "metric.h"
#endif

#include <exception>    // @todo: move to common and/or precompiled header
#include <new>

///////////////////////////////////////////////////////////////////////////////
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {e9320c3c91d5fcc7f51082901ddab9866a2e866330d8d67f811978aad0ec812b}
///
__xedllexport xe_result_t __xecall
xetDeviceGetMetricGroupCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xet_metric_group_sampling_type type,            ///< [in] metric group sampling type
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::get()->getMetricGroupCount(hDevice, type, pCount);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pUniqueIds
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {8ca3233d19c52dcd6162204ff86bff9b6ed56edc40132bfa8ad1468c3286557e}
///
__xedllexport xe_result_t __xecall
xetDeviceGetMetricGroupUniqueIds(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xet_metric_group_sampling_type type,            ///< [in] metric group sampling type
    uint32_t count,                                 ///< [in] number of metric groups to retrieve uuids
    xe_metric_group_uuid_t* pUniqueIds              ///< [in,out] pointer to an array of uuids for metric groups.
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pUniqueIds ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::get()->getMetricGroupUniqueIds(hDevice, type, count, pUniqueIds);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the metric group
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pMetricGroupProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {6fbce01a836f4c72bd363dfcc3b45f91f4b8ed199758f7cb453c347f98eb832f}
///
__xedllexport xe_result_t __xecall
xetDeviceGetMetricGroupProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_metric_group_uuid_t uuid,                    ///< [in] metric group uuid
    xet_metric_group_properties* pMetricGroupProperties ///< [out] device properties
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pMetricGroupProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle(hDevice)->getMetricGroupProperties(uuid, pMetricGroupProperties);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pMetricProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {f7a36bf11a68acfa537e3baf31be4d48e1525eaf285f3fd9a78bda0606b95f3a}
///
__xedllexport xe_result_t __xecall
xetDeviceGetMetricGroupMetricProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_metric_group_uuid_t uuid,                    ///< [in] metric group uuid
    uint32_t ordinal,                               ///< [in] ordinal of the metric
    xet_metric_properties* pMetricProperties        ///< [out] device properties
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pMetricProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle(hDevice)->getMetricGroupMetricProperties(uuid, ordinal, pMetricProperties);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

