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
    /// @brief Different value types union
    union value_t
    {
        uint32_t _uint32;                               ///< [out] uint32_t value
        uint64_t _uint64;                               ///< [out] uint64_t value
        float _float;                                   ///< [out] float value
        double _double;                                 ///< [out] double value
        xe::bool_t _bool;                               ///< [out] bool value

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Typed value
    struct typed_value_t
    {
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
            size_t reportSize;                              ///< [out] size of calculated data per-report

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_group_handle_t m_handle = nullptr;       ///< [in] handle of metric group object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricGroup( void ) = delete;
        MetricGroup( 
            metric_group_handle_t handle,                   ///< [in] handle of metric group object
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
        /// @brief Retrieves metric group for a device group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __xecall
        Get(
            DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metric groups available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< metric groups.
            MetricGroup** ppMetricGroup = nullptr           ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                            ///< groups
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a metric group.
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
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __xecall
        CalculateData(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
            uint8_t* pRawData,                              ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
            uint32_t* pCalculatedDataCount,                 ///< [in] pointer to number of entries in calculated data buffer.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of entires to be calculated.
                                                            ///< if count is non-zero, then driver will only calculate that number of entires.
            typed_value_t* pCalculatedData                  ///< [in,out][range(0, *pCalculatedDataSize)] buffer of calculated data
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
        metric_handle_t m_handle;                       ///< [in] handle of metric object
        MetricGroup* m_pMetricGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Metric( void ) = delete;
        Metric( 
            metric_handle_t handle,                         ///< [in] handle of metric object
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
        /// @brief Retrieves metric from a metric group.
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
        /// @brief Retrieves attributes of a metric.
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
        metric_tracer_handle_t m_handle;                ///< [in] handle of metric tracer object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric tracer

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricTracer( void ) = delete;
        MetricTracer( 
            metric_tracer_handle_t handle,                  ///< [in] handle of metric tracer object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric tracer
            );

        ~MetricTracer( void ) = default;

        MetricTracer( MetricTracer const& other ) = delete;
        void operator=( MetricTracer const& other ) = delete;

        MetricTracer( MetricTracer&& other ) = delete;
        void operator=( MetricTracer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens metric tracer for a device.
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
            desc_t* desc,                                   ///< [in,out] metric tracer descriptor
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
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                            ///< reports in raw format
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
            flag_t flags = flag_t::PERFORMANCE;             ///< [in] Query pool type.
            uint32_t count;                                 ///< [in] Internal slots count within query pool object.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_pool_handle_t m_handle;            ///< [in] handle of metric query pool object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric query pool

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQueryPool( void ) = delete;
        MetricQueryPool( 
            metric_query_pool_handle_t handle,              ///< [in] handle of metric query pool object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric query pool
            );

        ~MetricQueryPool( void ) = default;

        MetricQueryPool( MetricQueryPool const& other ) = delete;
        void operator=( MetricQueryPool const& other ) = delete;

        MetricQueryPool( MetricQueryPool&& other ) = delete;
        void operator=( MetricQueryPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool of metric queries.
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
            const desc_t* desc                              ///< [in] metric query pool descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a query pool object.
        /// 
        /// @details
        ///     - The application is responsible for destroying all query handles
        ///       created from the pool before destroying the pool itself
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the any query within the pool before it is
        ///       deleted
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query pool handle.
        /// @throws result_t
        static void __xecall
        Destroy(
            MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query
    class MetricQuery
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_handle_t m_handle;                 ///< [in] handle of metric query object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQuery( void ) = delete;
        MetricQuery( 
            metric_query_handle_t handle,                   ///< [in] handle of metric query object
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
        /// @brief Creates metric query object.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - MetricQuery*: handle of metric query
        /// 
        /// @throws result_t
        static MetricQuery* __xecall
        Create(
            MetricQueryPool* pMetricQueryPool,              ///< [in] pointer to the metric query pool
            uint32_t index                                  ///< [in] index of the query within the pool
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a metric query object.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the query before it is deleted
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query handle.
        /// @throws result_t
        static void __xecall
        Destroy(
            MetricQuery* pMetricQuery                       ///< [in][release] pointer to metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resets a metric query object back to inital state.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the query before it is reset
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query handle.
        /// @throws result_t
        void __xecall
        Reset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves raw data for a given metric query.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __xecall
        GetData(
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                            ///< reports in raw format
            );

    };

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( const value_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_t to std::string
    std::string to_string( const value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_t to std::string
    std::string to_string( const typed_value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type_t to std::string
    std::string to_string( const MetricGroup::sampling_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_version_t to std::string
    std::string to_string( const MetricGroup::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_t to std::string
    std::string to_string( const MetricGroup::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( const Metric::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_version_t to std::string
    std::string to_string( const Metric::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_t to std::string
    std::string to_string( const Metric::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_version_t to std::string
    std::string to_string( const MetricTracer::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_t to std::string
    std::string to_string( const MetricTracer::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::flag_t to std::string
    std::string to_string( const MetricQueryPool::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_version_t to std::string
    std::string to_string( const MetricQueryPool::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_t to std::string
    std::string to_string( const MetricQueryPool::desc_t val );

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_METRIC_HPP
