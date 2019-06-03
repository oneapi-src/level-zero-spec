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
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_MAX_METRIC_GROUP_NAME
/// @brief Maximum metric group name string size
#define XET_MAX_METRIC_GROUP_NAME  256
#endif // XET_MAX_METRIC_GROUP_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_MAX_METRIC_GROUP_DESCRIPTION
/// @brief Maximum metric group description string size
#define XET_MAX_METRIC_GROUP_DESCRIPTION  256
#endif // XET_MAX_METRIC_GROUP_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_MAX_METRIC_NAME
/// @brief Maximum metric name string size
#define XET_MAX_METRIC_NAME  256
#endif // XET_MAX_METRIC_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_MAX_METRIC_DESCRIPTION
/// @brief Maximum metric description string size
#define XET_MAX_METRIC_DESCRIPTION  256
#endif // XET_MAX_METRIC_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_MAX_METRIC_COMPONENT
/// @brief Maximum metric component string size
#define XET_MAX_METRIC_COMPONENT  256
#endif // XET_MAX_METRIC_COMPONENT

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_MAX_METRIC_RESULT_UNITS
/// @brief Maximum metric result units string size
#define XET_MAX_METRIC_RESULT_UNITS  256
#endif // XET_MAX_METRIC_RESULT_UNITS

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Value types
    enum class value_type_t
    {
        UINT32,                                         ///< Value type: uint32
        UINT64,                                         ///< Value type: uint64
        FLOAT,                                          ///< Value type: float
        BOOL,                                           ///< Value type: bool

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief API version of ::typed_value_t
    enum class typed_value_version_t
    {
        CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Different value types union
    union value_t
    {
        uint32_t valueUInt32;                           ///< [out] uint32_t value
        uint64_t valueUInt64;                           ///< [out] uint64_t value
        float valueFloat;                               ///< [out] float value
        xe::bool_t valueBool;                           ///< [out] bool value

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Typed value
    struct typed_value_t
    {
        typed_value_version_t version = typed_value_version_t::CURRENT; ///< [in] ::TYPED_VALUE_VERSION_CURRENT
        value_type_t type;                              ///< [out] value type
        value_t value;                                  ///< [out] value of a specified type

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric group
    class MetricGroup
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group sampling type
        enum class sampling_type_t
        {
            EVENT_BASED = XE_BIT(0),                        ///< Event based sampling
            TIME_BASED = XE_BIT(1),                         ///< Time based sampling

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::metric_group_properties_t
        enum class properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group properties queried using ::MetricGroupGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::METRIC_GROUP_PROPERTIES_VERSION_CURRENT
            char name[XET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
            char description[XET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
            sampling_type_t samplingType;                   ///< [out] metric group sampling type
            uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                            ///< groups from different domains.
            uint32_t metricCount;                           ///< [out] metric count belonging to this group
            uint32_t rawReportSize;                         ///< [out] size of raw report
            uint32_t calculatedReportSize;                  ///< [out] size of calculated report

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_group_handle_t m_handle = nullptr;       ///< handle of metric group object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricGroup( void ) = delete;
        MetricGroup( 
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricGroup( void ) = default;

        MetricGroup( MetricGroup const& other ) = delete;
        void operator=( MetricGroup const& other ) = delete;

        MetricGroup( MetricGroup&& other ) = delete;
        void operator=( MetricGroup&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns metric group handle for a device.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __xecall
        Get(
            Device* pDevice,                                ///< [in] pointer to the device
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metric groups available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< metric groups.
            MetricGroup** ppMetricGroup = nullptr           ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                            ///< groups
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns properties for a given metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - properties_t: metric group properties
        /// 
        /// @throws result_t
        properties_t __xecall
        GetProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Calculates counter values from raw data.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads wth the same metric group handle.
        /// @throws result_t
        void __xecall
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
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric types
        enum class type_t
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
        /// @brief API version of ::metric_properties_t
        enum class properties_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric properties queried using ::MetricGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::METRIC_PROPERTIES_VERSION_CURRENT
            char name[XET_MAX_METRIC_NAME];                 ///< [out] metric name
            char description[XET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
            char component[XET_MAX_METRIC_COMPONENT];       ///< [out] metric component
            uint32_t tierNumber;                            ///< [out] number of tier
            type_t metricType;                              ///< [out] metric type
            value_type_t resultType;                        ///< [out] metric result type
            char resultUnits[XET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_handle_t m_handle;                       ///< handle of metric object
        MetricGroup* m_pMetricGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Metric( void ) = delete;
        Metric( 
            MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
            );

        ~Metric( void ) = default;

        Metric( Metric const& other ) = delete;
        void operator=( Metric const& other ) = delete;

        Metric( Metric&& other ) = delete;
        void operator=( Metric&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getMetricgroup( void ) const { return m_pMetricGroup; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves metric from a given metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - Metric*: handle of metric
        /// 
        /// @throws result_t
        static Metric* __xecall
        Get(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            uint32_t ordinal                                ///< [in] ordinal of metric to retrieve; must be less than
                                                            ///< ::metric_group_properties_t::metricCount
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns metric properties.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - properties_t: metric properties
        /// 
        /// @throws result_t
        properties_t __xecall
        GetProperties(
            void
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric tracer
    class MetricTracer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::metric_tracer_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric tracer descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::METRIC_TRACER_DESC_VERSION_CURRENT
            uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                            ///< will be signalled
            uint32_t samplingPeriod;                        ///< [in,out] tracer sampling period in nanoseconds

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_tracer_handle_t m_handle;                ///< handle of metric tracer object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricTracer( void ) = delete;
        MetricTracer( 
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricTracer( void ) = default;

        MetricTracer( MetricTracer const& other ) = delete;
        void operator=( MetricTracer const& other ) = delete;

        MetricTracer( MetricTracer&& other ) = delete;
        void operator=( MetricTracer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens metric tracer for a given device.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// @returns
        ///     - MetricTracer*: handle of metric tracer
        /// 
        /// @throws result_t
        static MetricTracer* __xecall
        Open(
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            desc_t* pDesc,                                  ///< [in,out] metric tracer descriptor
            xe::Event* pNotificationEvent                   ///< [in] event used for report availability notification. Must be device
                                                            ///< to host type.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes metric tracer.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same metric tracer handle.
        /// @throws result_t
        void __xecall
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reads data from metric tracer.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __xecall
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
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool types
        enum class flag_t
        {
            PERFORMANCE,                                    ///< Performance metric query pool.
            SKIP_EXECUTION,                                 ///< Skips workload execution between begin/end calls.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::metric_query_pool_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool description
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::METRIC_QUERY_POOL_DESC_VERSION_CURRENT
            flag_t flags;                                   ///< [in] Query pool type.
            uint32_t count;                                 ///< [in] Internal slots count within query pool object.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_pool_handle_t m_handle;            ///< handle of metric query pool object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQueryPool( void ) = delete;
        MetricQueryPool( 
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricQueryPool( void ) = default;

        MetricQueryPool( MetricQueryPool const& other ) = delete;
        void operator=( MetricQueryPool const& other ) = delete;

        MetricQueryPool( MetricQueryPool&& other ) = delete;
        void operator=( MetricQueryPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates metric query pool.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - MetricQueryPool*: handle of metric query pool
        /// 
        /// @throws result_t
        static MetricQueryPool* __xecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] metric group associated with the query object.
            desc_t* pDesc                                   ///< [in] metric query pool creation data
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys query pool object.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query pool handle.
        /// @throws result_t
        static void __xecall
        Destroy(
            MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns metric query handle from a given metric query pool.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - MetricQuery*: handle of metric query
        /// 
        /// @throws result_t
        MetricQuery* __xecall
        GetMetricQuery(
            uint32_t index                                  ///< [in] index of the query within the pool
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query
    class MetricQuery
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_handle_t m_handle;                 ///< handle of metric query object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQuery( void ) = delete;
        MetricQuery( 
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricQuery( void ) = default;

        MetricQuery( MetricQuery const& other ) = delete;
        void operator=( MetricQuery const& other ) = delete;

        MetricQuery( MetricQuery&& other ) = delete;
        void operator=( MetricQuery&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns raw data for a given metric query slot.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __xecall
        GetData(
            uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
            uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
            uint8_t* pRawData                               ///< [in,out] query result data in raw format
            );

    };

} // namespace xet

#ifdef _DEBUG
namespace std
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::value_type_t to std::string
    string to_string( const xet::value_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::typed_value_version_t to std::string
    string to_string( const xet::typed_value_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::value_t to std::string
    string to_string( const xet::value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::typed_value_t to std::string
    string to_string( const xet::typed_value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricGroup::sampling_type_t to std::string
    string to_string( const xet::MetricGroup::sampling_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricGroup::properties_version_t to std::string
    string to_string( const xet::MetricGroup::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricGroup::properties_t to std::string
    string to_string( const xet::MetricGroup::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::Metric::type_t to std::string
    string to_string( const xet::Metric::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::Metric::properties_version_t to std::string
    string to_string( const xet::Metric::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::Metric::properties_t to std::string
    string to_string( const xet::Metric::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricTracer::desc_version_t to std::string
    string to_string( const xet::MetricTracer::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricTracer::desc_t to std::string
    string to_string( const xet::MetricTracer::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricQueryPool::flag_t to std::string
    string to_string( const xet::MetricQueryPool::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricQueryPool::desc_version_t to std::string
    string to_string( const xet::MetricQueryPool::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xet::MetricQueryPool::desc_t to std::string
    string to_string( const xet::MetricQueryPool::desc_t val );

} // namespace std
#endif // _DEBUG
#endif // defined(__cplusplus)
#endif // _XET_METRIC_HPP
