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

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_group_properties_version_t
        enum class metric_group_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_properties_version_t
        enum class metric_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_t
        enum class metric_t
        {

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_value_t
        enum class metric_value_t
        {

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_group_properties
        struct metric_group_properties
        {
            metric_group_properties_version_t version = metric_group_properties_version_t::CURRENT; ///< [in] ::METRIC_GROUP_PROPERTIES_VERSION_CURRENT
            char name[XET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
            char description[XET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
            metric_group_sampling_type samplingType;        ///< [out]
            uint32_t domain;                                ///< [out] cannot use simultaneous metric groups from different domains
            uint32_t numMetrics;                            ///< [out] number of metrics in the group
            size_t sizeMetrics;                             ///< [out] size in bytes of the metrics in the group

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_properties
        struct metric_properties
        {
            metric_properties_version_t version = metric_properties_version_t::CURRENT; ///< [in] ::METRIC_PROPERTIES_VERSION_CURRENT
            char name[XET_MAX_METRIC_NAME];                 ///< [out] metric name
            char description[XET_MAX_METRIC_DESCRIPTION];   ///< metric description
            char component[XET_MAX_METRIC_NAME];            ///< metric device component

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceGetMetricGroupCount
        /// @returns
        ///     - uint32_t: number of metric groups supported by the device
        /// 
        /// @throws result_t
        inline static uint32_t
        GetMetricGroupCount(
            metric_group_sampling_type type                 ///< [in] metric group sampling type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceGetMetricGroupUniqueIds
        /// @throws result_t
        inline static void
        GetMetricGroupUniqueIds(
            metric_group_sampling_type type,                ///< [in] metric group sampling type
            uint32_t count,                                 ///< [in] number of metric groups to retrieve uuids
            xe::_metric_group_uuid_t* pUniqueIds            ///< [in,out] pointer to an array of uuids for metric groups.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceGetMetricGroupProperties
        /// @returns
        ///     - ::metric_group_properties: device properties
        /// 
        /// @throws result_t
        inline metric_group_properties
        GetMetricGroupProperties(
            xe::_metric_group_uuid_t uuid                   ///< [in] metric group uuid
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetDeviceGetMetricGroupMetricProperties
        /// @returns
        ///     - ::metric_properties: device properties
        /// 
        /// @throws result_t
        inline metric_properties
        GetMetricGroupMetricProperties(
            xe::_metric_group_uuid_t uuid,                  ///< [in] metric group uuid
            uint32_t ordinal                                ///< [in] ordinal of the metric
            );

    };

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_DEVICE_HPP
