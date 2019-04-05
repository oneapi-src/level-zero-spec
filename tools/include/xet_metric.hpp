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
* @file xet_metric.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Metric
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/metric.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_METRIC_HPP
#define _XET_METRIC_HPP
#if defined(__cplusplus)
#pragma once
#include "xet_common.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric group
    class MetricGroup
    {
    protected:
        ::xet_metric_group_handle_t handle;               ///< handle of metric group object

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
        /// @brief C++ version for ::xet_metric_group_properties_version_t
        enum class metric_group_properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_group_properties_t
        struct metric_group_properties_t
        {
            metric_group_properties_version_t version = metric_group_properties_version_t::CURRENT; ///< [in] ::METRIC_GROUP_PROPERTIES_VERSION_CURRENT
            char name[XET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
            char description[XET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
            metric_group_sampling_type samplingType;        ///< [out] metric group sampling type
            uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                            ///< groups from different domains.
            uint32_t metricCount;                           ///< [out] metric count belonging to this group
            uint32_t rawReportSize;                         ///< [out] size of raw report
            uint32_t calculatedReportSize;                  ///< [out] size of calculated report

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricGroupGetCount
        /// @returns
        ///     - uint32_t: number of metric groups supported by the device
        /// 
        /// @throws result_t
        inline static uint32_t
        GetCount(
            xe::device_handle_t hDevice                     ///< [in] handle of the device object
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricGroupGet
        /// @returns
        ///     - ::metric_group_handle_t: metric group handle
        /// 
        /// @throws result_t
        inline static metric_group_handle_t
        Get(
            xe::device_handle_t hDevice,                    ///< [in] handle of the device
            uint32_t ordinal                                ///< [in] metric group index
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricGroupGetProperties
        /// @returns
        ///     - ::metric_group_properties_t: metric group properties
        /// 
        /// @throws result_t
        inline metric_group_properties_t
        GetProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricGroupCalculateData
        /// @throws result_t
        inline void
        CalculateData(
            uint32_t* pReportCount,                         ///< [in,out] report count to calculate
            uint32_t rawDataSize,                           ///< [in] raw data size
            uint8_t* pRawData,                              ///< [in] raw data to calculate
            uint32_t calculatedDataSize,                    ///< [in] calculated data size
            typed_value_t* pCalculatedData                  ///< [in,out] calculated metrics
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric
    class Metric
    {
    protected:
        ::xet_metric_handle_t handle;                     ///< handle of metric object

    public:
        auto getHandle( void ) const { return handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_type_t
        enum class metric_type_t
        {
            DURATION,                                       ///< Metric type: duration
            EVENT,                                          ///< Metric type: event
            EVENT_WITH_RANGE,                               ///< Metric type: event with range
            THROUGHPUT,                                     ///< Metric type: throughput
            TIMESTAMP,                                      ///< Metric type: timestamp
            FLAG,                                           ///< Metric type: flag
            RATIO,                                          ///< Metric type: ratio
            RAW,                                            ///< Metric type: raw

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_value_type_t
        enum class value_type_t
        {
            UINT32,                                         ///< Value type: uint32
            UINT64,                                         ///< Value type: uint64
            FLOAT,                                          ///< Value type: float
            BOOL,                                           ///< Value type: bool
            STRING,                                         ///< Value type: string

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_typed_value_version_t
        enum class typed_value_version_t
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
        /// @brief C++ version for ::xet_value_t
        union value_t
        {
            uint32_t valueUInt32;                           ///< [out] uint32_t value
            uint64_t valueUInt64;                           ///< [out] uint64_t value
            float valueFloat;                               ///< [out] float value
            xe::bool_t valueBool;                           ///< [out] bool value
            const char* valueString;                        ///< [out] string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_typed_value_t
        struct typed_value_t
        {
            typed_value_version_t version = typed_value_version_t::CURRENT; ///< [in] ::TYPED_VALUE_VERSION_CURRENT
            value_type_t type;                              ///< [out] value type
            value_t value;                                  ///< [out] value of a specified type

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_properties_t
        struct metric_properties_t
        {
            metric_properties_version_t version = metric_properties_version_t::CURRENT; ///< [in] ::METRIC_PROPERTIES_VERSION_CURRENT
            char name[XET_MAX_METRIC_NAME];                 ///< [out] metric name
            char description[XET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
            char component[XET_MAX_METRIC_COMPONENT];       ///< [out] metric component
            uint32_t tierNumber;                            ///< [out] number of tier
            metric_type_t metricType;                       ///< [out] metric type
            value_type_t resultType;                        ///< [out] metric result type
            char resultUnits[XET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricGet
        /// @returns
        ///     - ::metric_handle_t: handle of metric
        /// 
        /// @throws result_t
        inline static metric_handle_t
        Get(
            metric_group_handle_t hMetricGroup,             ///< [in] handle of the metric group
            uint32_t ordinal                                ///< [in] metric index
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricGetProperties
        /// @returns
        ///     - ::metric_properties_t: metric properties
        /// 
        /// @throws result_t
        inline metric_properties_t
        GetProperties(
            void
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric tracer
    class MetricTracer
    {
    protected:
        ::xet_metric_tracer_handle_t handle;              ///< handle of metric tracer object

    public:
        auto getHandle( void ) const { return handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_tracer_desc_version_t
        enum class metric_tracer_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_tracer_desc_t
        struct metric_tracer_desc_t
        {
            metric_tracer_desc_version_t version = metric_tracer_desc_version_t::CURRENT;   ///< [in] ::METRIC_TRACER_DESC_VERSION_CURRENT
            metric_group_handle_t hMetricGroup;             ///< [in] handle of the metric group
            uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                            ///< will be signalled
            uint32_t samplingPeriodNs;                      ///< [in,out] tracer sampling period in nanoseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricTracerOpen
        /// @returns
        ///     - ::metric_tracer_handle_t: handle of metric tracer
        /// 
        /// @throws result_t
        inline static metric_tracer_handle_t
        Open(
            xe::device_handle_t hDevice,                    ///< [in] handle of the device
            metric_tracer_desc_t* pDesc,                    ///< [in,out] metric tracer descriptor
            xe::event_handle_t hNotificationEvent           ///< [in] event used for report availability notification. Must be device
                                                            ///< to host type.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricTracerClose
        /// @throws result_t
        inline void
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricTracerReadData
        /// @throws result_t
        inline void
        ReadData(
            uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
            uint32_t rawDataSize,                           ///< [in] raw data buffer size
            uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query pool
    class MetricQueryPool
    {
    protected:
        ::xet_metric_query_pool_handle_t handle;          ///< handle of metric query pool object

    public:
        auto getHandle( void ) const { return handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_query_pool_flag_t
        enum class metric_query_pool_flag_t
        {
            PERFORMANCE,                                    ///< Performance metric query pool.
            SKIP_EXECUTION,                                 ///< Skips workload execution between begin/end calls.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_query_pool_desc_version_t
        enum class metric_query_pool_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_metric_query_pool_desc_t
        struct metric_query_pool_desc_t
        {
            metric_query_pool_desc_version_t version = metric_query_pool_desc_version_t::CURRENT;   ///< [in] ::METRIC_QUERY_POOL_DESC_VERSION_CURRENT
            metric_query_pool_flag_t flags;                 ///< [in] Query pool type.
            metric_group_handle_t hMetricGroup;             ///< [in] Metric group associated with the query object.
            uint32_t count;                                 ///< [in] Internal slots count within query pool object.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricQueryPoolCreate
        /// @returns
        ///     - ::metric_query_pool_handle_t: handle of metric query pool
        /// 
        /// @throws result_t
        inline static metric_query_pool_handle_t
        Create(
            xe::device_handle_t hDevice,                    ///< [in] handle of the device
            metric_query_pool_desc_t* pDesc                 ///< [in] metric query pool creation data
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricQueryPoolDestroy
        /// @throws result_t
        inline static void
        Destroy(
            metric_query_pool_handle_t hMetricQueryPool     ///< [in] handle of the metric query pool
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricQueryPoolGetMetricQuery
        /// @returns
        ///     - ::metric_query_handle_t: handle of metric query
        /// 
        /// @throws result_t
        inline metric_query_handle_t
        GetMetricQuery(
            uint32_t ordinal                                ///< [in] index of the query within the pool
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query
    class MetricQuery
    {
    protected:
        ::xet_metric_query_handle_t handle;               ///< handle of metric query object

    public:
        auto getHandle( void ) const { return handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetMetricQueryGetData
        /// @throws result_t
        inline void
        GetData(
            uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
            uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
            uint8_t* pRawData                               ///< [in,out] query result data in raw format
            );

    };

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_METRIC_HPP
