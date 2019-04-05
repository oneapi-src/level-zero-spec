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
* @file xet_device.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_DEVICE_HPP
#define _XET_DEVICE_HPP
#if defined(__cplusplus)
#pragma once
#include "xet_common.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device : public xe::Device
    {
    protected:
        ::xe_device_handle_t handle;                      ///< handle of device object

    public:
        auto getHandle( void ) const { return handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_group_sampling_type
        enum class metric_group_sampling_type
        {
            METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED = XE_BIT(0), ///< Event based sampling
            METRIC_GROUP_SAMPLING_TYPE_TIME_BASED = XE_BIT(1),  ///< Time based sampling

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceGetMetricGroupCount
        /// @returns
        ///     - uint32_t: number of metric groups supported by the device
        /// 
        /// @throws result_t
        inline uint32_t
        GetMetricGroupCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceGetMetricGroup
        /// @returns
        ///     - ::metric_group_handle_t: metric group handle
        /// 
        /// @throws result_t
        inline metric_group_handle_t
        GetMetricGroup(
            uint32_t ordinal                                ///< [in] metric group index
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceActivateMetricGroups
        /// @throws result_t
        inline void
        ActivateMetricGroups(
            uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
            metric_group_handle_t* phMetricGroups           ///< [in] handles of the metric groups to activate. NULL to deactivate.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceOpenMetricTracer
        /// @returns
        ///     - ::metric_tracer_handle_t: handle of metric tracer
        /// 
        /// @throws result_t
        inline metric_tracer_handle_t
        OpenMetricTracer(
            metric_tracer_desc_t* pDesc,                    ///< [in/out] metric tracer descriptor
            xe::_event_handle_t hNotificationEvent          ///< [in] event used for report availability notification. Must be device
                                                            ///< to host type.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceCreateMetricQueryPool
        /// @returns
        ///     - ::metric_query_pool_handle_t: handle of metric query pool
        /// 
        /// @throws result_t
        inline metric_query_pool_handle_t
        CreateMetricQueryPool(
            metric_query_pool_desc_t* pDesc                 ///< [in] metric query pool creation data
            );

    };

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_DEVICE_HPP
