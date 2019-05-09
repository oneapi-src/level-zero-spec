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
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xet_device.hpp"

namespace xet
{
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
        MetricGroup* phMetricGroups                     ///< [in] handles of the metric groups to activate. NULL to deactivate.
        )
    {
        // auto result = ::xetDeviceActivateMetricGroups( handle, count, phMetricGroups );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::ActivateMetricGroups");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetDevicePowerInit
    /// 
    /// @details
    ///     - Initializes internal structures to support power management features.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **nvmlInit**
    ///     - **rsmi_init**
    /// 
    /// @returns
    ///     - Power: handle for accessing power features of the device
    /// 
    /// @throws result_t
    inline Power* 
    Device::PowerInit(
        uint32_t flags                                  ///< [in] bitfield of ::power_init_flags_t
        )
    {
        // auto result = ::xetDevicePowerInit( handle, flags );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::PowerInit");
    }

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_DEVICE_INL
