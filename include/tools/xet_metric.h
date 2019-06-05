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
* @file xet_metric.h
*
* @brief Intel Xe Level-Zero Tool APIs for Metric
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/metric.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_METRIC_H
#define _XET_METRIC_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves metric group for a device group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pCount
///         + devices do not contain a given metric group
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupGet(
    xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of metric groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< metric groups.
    xet_metric_group_handle_t* phMetricGroup        ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups
    );

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
/// @brief Metric group sampling type
typedef enum _xet_metric_group_sampling_type_t
{
    XET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED = XE_BIT(0), ///< Event based sampling
    XET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED = XE_BIT(1),  ///< Time based sampling

} xet_metric_group_sampling_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_metric_group_properties_t
typedef enum _xet_metric_group_properties_version_t
{
    XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xet_metric_group_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric group properties queried using ::xetMetricGroupGetProperties
typedef struct _xet_metric_group_properties_t
{
    xet_metric_group_properties_version_t version;  ///< [in] ::XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
    char name[XET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
    char description[XET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
    xet_metric_group_sampling_type_t samplingType;  ///< [out] metric group sampling type
    uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                    ///< groups from different domains.
    uint32_t metricCount;                           ///< [out] metric count belonging to this group
    size_t rawReportSize;                           ///< [out] size of raw report
    size_t calculatedReportSize;                    ///< [out] size of calculated report

} xet_metric_group_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a metric group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricGroup
///         + nullptr == pProperties
///         + invalid metric group handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupGetProperties(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    );

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

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric types
typedef enum _xet_metric_type_t
{
    XET_METRIC_TYPE_DURATION,                       ///< Metric type: duration
    XET_METRIC_TYPE_EVENT,                          ///< Metric type: event
    XET_METRIC_TYPE_EVENT_WITH_RANGE,               ///< Metric type: event with range
    XET_METRIC_TYPE_THROUGHPUT,                     ///< Metric type: throughput
    XET_METRIC_TYPE_TIMESTAMP,                      ///< Metric type: timestamp
    XET_METRIC_TYPE_FLAG,                           ///< Metric type: flag
    XET_METRIC_TYPE_RATIO,                          ///< Metric type: ratio
    XET_METRIC_TYPE_RAW,                            ///< Metric type: raw

} xet_metric_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Value types
typedef enum _xet_value_type_t
{
    XET_VALUE_TYPE_UINT32,                          ///< Value type: uint32
    XET_VALUE_TYPE_UINT64,                          ///< Value type: uint64
    XET_VALUE_TYPE_FLOAT,                           ///< Value type: float
    XET_VALUE_TYPE_BOOL,                            ///< Value type: bool

} xet_value_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Different value types union
typedef union _xet_value_t
{
    uint32_t valueUInt32;                           ///< [out] uint32_t value
    uint64_t valueUInt64;                           ///< [out] uint64_t value
    float valueFloat;                               ///< [out] float value
    xe_bool_t valueBool;                            ///< [out] bool value

} xet_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Typed value
typedef struct _xet_typed_value_t
{
    xet_value_type_t type;                          ///< [out] value type
    xet_value_t value;                              ///< [out] value of a specified type

} xet_typed_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_metric_properties_t
typedef enum _xet_metric_properties_version_t
{
    XET_METRIC_PROPERTIES_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),///< version 1.0

} xet_metric_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric properties queried using ::xetMetricGetProperties
typedef struct _xet_metric_properties_t
{
    xet_metric_properties_version_t version;        ///< [in] ::XET_METRIC_PROPERTIES_VERSION_CURRENT
    char name[XET_MAX_METRIC_NAME];                 ///< [out] metric name
    char description[XET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
    char component[XET_MAX_METRIC_COMPONENT];       ///< [out] metric component
    uint32_t tierNumber;                            ///< [out] number of tier
    xet_metric_type_t metricType;                   ///< [out] metric type
    xet_value_type_t resultType;                    ///< [out] metric result type
    char resultUnits[XET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

} xet_metric_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves metric from a metric group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricGroup
///         + nullptr == phMetric
///         + invalid metric group handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGet(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t ordinal,                               ///< [in] ordinal of metric to retrieve; must be less than
                                                    ///< ::xet_metric_group_properties_t::metricCount
    xet_metric_handle_t* phMetric                   ///< [out] handle of metric
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a metric.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetric
///         + nullptr == pProperties
///         + invalid handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGetProperties(
    xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    xet_metric_properties_t* pProperties            ///< [out] metric properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Calculates counter values from raw data.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads wth the same metric group handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricGroup
///         + nullptr == pRawData
///         + nullptr == pCalculatedData
///         + invalid metric group handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupCalculateData(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t count,                                 ///< [in,out] number of reports to calculate
    size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
    uint8_t* pRawData,                              ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
    size_t calculatedDataSize,                      ///< [in] size in bytes of calculated metrics
    xet_typed_value_t* pCalculatedData              ///< [in,out][range(0, calculatedDataSize)] buffer of calculated metrics
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Activates metric groups.
/// 
/// @details
///     - MetricGroup must be active until MetricQueryGetDeta and
///       ::xetMetricTracerClose.
///     - Conflicting metric groups cannot be activated, in such case tha call
///       would fail.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == phMetricGroups
///         + invalid metric groups
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetDeviceActivateMetricGroups(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    xet_metric_group_handle_t* phMetricGroups       ///< [in][range(0, count)] handles of the metric groups to activate. NULL
                                                    ///< to deactivate.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_metric_tracer_desc_t
typedef enum _xet_metric_tracer_desc_version_t
{
    XET_METRIC_TRACER_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} xet_metric_tracer_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric tracer descriptor
typedef struct _xet_metric_tracer_desc_t
{
    xet_metric_tracer_desc_version_t version;       ///< [in] ::XET_METRIC_TRACER_DESC_VERSION_CURRENT
    uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                    ///< will be signalled
    uint32_t samplingPeriod;                        ///< [in,out] tracer sampling period in nanoseconds

} xet_metric_tracer_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens metric tracer for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hMetricGroup
///         + nullptr == pDesc
///         + nullptr == hNotificationEvent
///         + nullptr == phMetricTracer
///         + devices do not support metric tracer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XET_METRIC_TRACER_DESC_VERSION_CURRENT < pDesc->version
xe_result_t __xecall
xetMetricTracerOpen(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_tracer_desc_t* pDesc,                ///< [in,out] metric tracer descriptor
    xe_event_handle_t hNotificationEvent,           ///< [in] event used for report availability notification. Must be device
                                                    ///< to host type.
    xet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Append metric tracer marker into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hMetricTracer
///         + command list do not support metric tracer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetCommandListAppendMetricTracerMarker(
    xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t value                                  ///< [in] tracer marker value
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes metric tracer.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same metric tracer handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricTracer
///         + invalid metric tracer handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from metric tracer.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricTracer
///         + nullptr == pReportCount
///         + nullptr == pRawData
///         + invalid metric tracer handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricTracerReadData(
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
    uint32_t rawDataSize,                           ///< [in] raw data buffer size
    uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric query pool types
typedef enum _xet_metric_query_pool_flag_t
{
    XET_METRIC_QUERY_POOL_FLAG_PERFORMANCE,         ///< Performance metric query pool.
    XET_METRIC_QUERY_POOL_FLAG_SKIP_EXECUTION,      ///< Skips workload execution between begin/end calls.

} xet_metric_query_pool_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_metric_query_pool_desc_t
typedef enum _xet_metric_query_pool_desc_version_t
{
    XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} xet_metric_query_pool_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric query pool description
typedef struct _xet_metric_query_pool_desc_t
{
    xet_metric_query_pool_desc_version_t version;   ///< [in] ::XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT
    xet_metric_query_pool_flag_t flags;             ///< [in] Query pool type.
    uint32_t count;                                 ///< [in] Internal slots count within query pool object.

} xet_metric_query_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool of metric queries.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hMetricGroup
///         + nullptr == pDesc
///         + nullptr == phMetricQueryPool
///         + invalid device handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < pDesc->version
xe_result_t __xecall
xetMetricQueryPoolCreate(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    xet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
    xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
    xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
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
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricQueryPool
///         + invalid metric query pool handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates metric query object.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricQueryPool
///         + nullptr == phMetricQuery
///         + invalid device handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricQueryCreate(
    xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t index,                                 ///< [in] index of the query within the pool
    xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a metric query object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the query before it is deleted
///     - The application may **not** call this function from simultaneous
///       threads with the same query handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricQuery
///         + invalid device handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricQueryDestroy(
    xet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets a metric query object back to inital state.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the query before it is reset
///     - The application may **not** call this function from simultaneous
///       threads with the same query handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricQuery
///         + invalid device handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricQueryReset(
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query begin into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hMetricQuery
///         + invalid handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query end into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hMetricQuery
///         + nullptr == hCompletionEvent
///         + invalid handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
    xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query commands to flush all caches.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + invalid command list handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xet_command_list_handle_t hCommandList          ///< [in] handle of the command list
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves raw data for a given metric query slot.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMetricQuery
///         + nullptr == pRawData
///         + invalid metric query handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricQueryGetData(
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    uint32_t count,                                 ///< [in] number of query reports to read
    size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
    uint8_t* pRawData                               ///< [in,out][range(0, rawDataSize)] buffer containing query results in raw
                                                    ///< format
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_METRIC_H
