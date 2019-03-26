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
* @file xet_device.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_DEVICE_INL
#define _XET_DEVICE_INL
#if defined(__cplusplus)
#pragma once
#include "xet_device.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceGetMetricGroupCount
    /// 
    /// @returns
    ///     - uint32_t: number of metric groups supported by the device
    /// 
    /// @throws result_t
    inline uint32_t 
    Device::GetMetricGroupCount(
        metric_group_sampling_type type                 ///< [in] metric group sampling type
        )
    {
        // auto result = ::xetDeviceGetMetricGroupCount( handle, type );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::GetMetricGroupCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceGetMetricGroupUniqueIds
    /// 
    /// @throws result_t
    inline void 
    Device::GetMetricGroupUniqueIds(
        metric_group_sampling_type type,                ///< [in] metric group sampling type
        uint32_t count,                                 ///< [in] number of metric groups to retrieve uuids
        xe::_metric_group_uuid_t* pUniqueIds            ///< [in,out] pointer to an array of uuids for metric groups.
        )
    {
        // auto result = ::xetDeviceGetMetricGroupUniqueIds( handle, type, count, pUniqueIds );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::GetMetricGroupUniqueIds");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceGetMetricGroupProperties
    /// 
    /// @returns
    ///     - ::metric_group_properties: device properties
    /// 
    /// @throws result_t
    inline metric_group_properties 
    Device::GetMetricGroupProperties(
        xe::_metric_group_uuid_t uuid                   ///< [in] metric group uuid
        )
    {
        // auto result = ::xetDeviceGetMetricGroupProperties( handle, uuid );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::GetMetricGroupProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceGetMetricGroupMetricProperties
    /// 
    /// @returns
    ///     - ::metric_properties: device properties
    /// 
    /// @throws result_t
    inline metric_properties 
    Device::GetMetricGroupMetricProperties(
        xe::_metric_group_uuid_t uuid,                  ///< [in] metric group uuid
        uint32_t ordinal                                ///< [in] ordinal of the metric
        )
    {
        // auto result = ::xetDeviceGetMetricGroupMetricProperties( handle, uuid, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::GetMetricGroupMetricProperties");
    }

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_DEVICE_INL
