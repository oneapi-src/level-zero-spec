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
        void
        )
    {
        // auto result = ::xetDeviceGetMetricGroupCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::GetMetricGroupCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceGetMetricGroup
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same device handle.
    /// 
    /// @returns
    ///     - ::metric_group_handle_t: metric group handle
    /// 
    /// @throws result_t
    inline metric_group_handle_t 
    Device::GetMetricGroup(
        uint32_t ordinal                                ///< [in] metric group index
        )
    {
        // auto result = ::xetDeviceGetMetricGroup( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::GetMetricGroup");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceActivateMetricGroups
    /// 
    /// @details
    ///     - MetricGroup must be active until MetricQueryGetDeta and
    ///       ::MetricTracerClose.
    ///     - Conflicting metric groups cannot be activated, in such case tha call
    ///       would fail.
    /// 
    /// @throws result_t
    inline void 
    Device::ActivateMetricGroups(
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        metric_group_handle_t* phMetricGroups           ///< [in] handles of the metric groups to activate. NULL to deactivate
        )
    {
        // auto result = ::xetDeviceActivateMetricGroups( handle, count, phMetricGroups );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::ActivateMetricGroups");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceOpenMetricTracer
    /// 
    /// @details
    ///     - The application may not call this function from simultaneous threads
    ///       with the same device handle.
    /// 
    /// @returns
    ///     - ::metric_tracer_handle_t: handle of metric tracer
    /// 
    /// @throws result_t
    inline metric_tracer_handle_t 
    Device::OpenMetricTracer(
        metric_tracer_desc_t* desc                      ///< [in/out] metric tracer descriptor
        )
    {
        // auto result = ::xetDeviceOpenMetricTracer( handle, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::OpenMetricTracer");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDeviceCreateMetricQueryPool
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same device handle.
    /// 
    /// @returns
    ///     - ::metric_query_pool_handle_t: handle of metric query pool
    /// 
    /// @throws result_t
    inline metric_query_pool_handle_t 
    Device::CreateMetricQueryPool(
        metric_query_pool_desc_t* pDesc                 ///< [in] metric query pool creation data
        )
    {
        // auto result = ::xetDeviceCreateMetricQueryPool( handle, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::CreateMetricQueryPool");
    }

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_DEVICE_INL
