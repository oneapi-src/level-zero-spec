/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_metric.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Metric
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/metric.yml
 * @endcond
 *
 */
#include "xet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves metric group for a device.
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
///         + nullptr == pCount
///         + devices do not contain a given metric group
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupGet(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of metric groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< metric groups.
                                                    ///< if count is larger than the number of metric groups available, then
                                                    ///< the driver will update the value with the correct number of metric
                                                    ///< groups available.
    xet_metric_group_handle_t* phMetricGroups       ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups
    )
{
    auto pfnGet = xet_lib::context.ddiTable.MetricGroup.pfnGet;
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGet( hDevice, pCount, phMetricGroups );
}

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.MetricGroup.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hMetricGroup, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Calculates metric values from raw data.
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
///         + nullptr == pRawData
///         + nullptr == pMetricValueCount
///         + invalid metric group handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupCalculateMetricValues(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
    uint8_t* pRawData,                              ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
    uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of metric values to be calculated.
                                                    ///< if count is non-zero, then driver will only calculate that number of
                                                    ///< metric values.
                                                    ///< if count is larger than the number available in the raw data buffer,
                                                    ///< then the driver will update the value with the actual number of metric
                                                    ///< values to be calculated.
    xet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                    ///< metrics
    )
{
    auto pfnCalculateMetricValues = xet_lib::context.ddiTable.MetricGroup.pfnCalculateMetricValues;
    if( nullptr == pfnCalculateMetricValues )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
}

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
///         + nullptr == pCount
///         + invalid metric group handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGet(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of metrics available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                    ///< if count is larger than the number of metrics available, then the
                                                    ///< driver will update the value with the correct number of metrics available.
    xet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics
    )
{
    auto pfnGet = xet_lib::context.ddiTable.Metric.pfnGet;
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGet( hMetricGroup, pCount, phMetrics );
}

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.Metric.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hMetric, pProperties );
}

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
///         + invalid metric groups
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetDeviceActivateMetricGroups(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    xet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                    ///< activate. NULL to deactivate.
    )
{
    auto pfnActivateMetricGroups = xet_lib::context.ddiTable.Device.pfnActivateMetricGroups;
    if( nullptr == pfnActivateMetricGroups )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnActivateMetricGroups( hDevice, count, phMetricGroups );
}

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
///         + nullptr == desc
///         + nullptr == phMetricTracer
///         + devices do not support metric tracer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XET_METRIC_TRACER_DESC_VERSION_CURRENT < desc->version
xe_result_t __xecall
xetMetricTracerOpen(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_tracer_desc_t* desc,                 ///< [in,out] metric tracer descriptor
    xe_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Must
                                                    ///< be device to host type.
    xet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    )
{
    auto pfnOpen = xet_lib::context.ddiTable.MetricTracer.pfnOpen;
    if( nullptr == pfnOpen )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
}

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
    )
{
    auto pfnAppendMetricTracerMarker = xet_lib::context.ddiTable.CommandList.pfnAppendMetricTracerMarker;
    if( nullptr == pfnAppendMetricTracerMarker )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
}

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
    )
{
    auto pfnClose = xet_lib::context.ddiTable.MetricTracer.pfnClose;
    if( nullptr == pfnClose )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnClose( hMetricTracer );
}

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
///         + nullptr == pRawDataSize
///         + invalid metric tracer handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricTracerReadData(
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                    ///< if UINT32_MAX, then function will retrieve all reports available
    size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                    ///< if size is zero, then the driver will update the value with the total
                                                    ///< size in bytes needed for all reports available.
                                                    ///< if size is non-zero, then driver will only retrieve the number of
                                                    ///< reports that fit into the buffer.
                                                    ///< if size is larger than size needed for all reports, then driver will
                                                    ///< update the value with the actual size needed.
    uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                    ///< reports in raw format
    )
{
    auto pfnReadData = xet_lib::context.ddiTable.MetricTracer.pfnReadData;
    if( nullptr == pfnReadData )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );
}

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
///         + nullptr == desc
///         + nullptr == phMetricQueryPool
///         + invalid device handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < desc->version
xe_result_t __xecall
xetMetricQueryPoolCreate(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    xet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
    const xet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
    xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    )
{
    auto pfnCreate = xet_lib::context.ddiTable.MetricQueryPool.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
}

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
    )
{
    auto pfnDestroy = xet_lib::context.ddiTable.MetricQueryPool.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hMetricQueryPool );
}

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
    )
{
    auto pfnCreate = xet_lib::context.ddiTable.MetricQuery.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hMetricQueryPool, index, phMetricQuery );
}

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
    )
{
    auto pfnDestroy = xet_lib::context.ddiTable.MetricQuery.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hMetricQuery );
}

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
    )
{
    auto pfnReset = xet_lib::context.ddiTable.MetricQuery.pfnReset;
    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnReset( hMetricQuery );
}

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
    )
{
    auto pfnAppendMetricQueryBegin = xet_lib::context.ddiTable.CommandList.pfnAppendMetricQueryBegin;
    if( nullptr == pfnAppendMetricQueryBegin )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
}

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
///         + invalid handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
    xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    xe_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
    )
{
    auto pfnAppendMetricQueryEnd = xet_lib::context.ddiTable.CommandList.pfnAppendMetricQueryEnd;
    if( nullptr == pfnAppendMetricQueryEnd )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
}

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
    )
{
    auto pfnAppendMetricMemoryBarrier = xet_lib::context.ddiTable.CommandList.pfnAppendMetricMemoryBarrier;
    if( nullptr == pfnAppendMetricMemoryBarrier )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMetricMemoryBarrier( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves raw data for a given metric query.
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
///         + nullptr == pRawDataSize
///         + invalid metric query handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricQueryGetData(
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                    ///< if size is zero, then the driver will update the value with the total
                                                    ///< size in bytes needed for all reports available.
                                                    ///< if size is non-zero, then driver will only retrieve the number of
                                                    ///< reports that fit into the buffer.
                                                    ///< if size is larger than size needed for all reports, then driver will
                                                    ///< update the value with the actual size needed.
    uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                    ///< reports in raw format
    )
{
    auto pfnGetData = xet_lib::context.ddiTable.MetricQuery.pfnGetData;
    if( nullptr == pfnGetData )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    MetricGroup::MetricGroup( 
        metric_group_handle_t handle,                   ///< [in] handle of metric group object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Metric::Metric( 
        metric_handle_t handle,                         ///< [in] handle of metric object
        MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pMetricGroup( pMetricGroup )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricTracer::MetricTracer( 
        metric_tracer_handle_t handle,                  ///< [in] handle of metric tracer object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the metric tracer
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQueryPool::MetricQueryPool( 
        metric_query_pool_handle_t handle,              ///< [in] handle of metric query pool object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the metric query pool
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQuery::MetricQuery( 
        metric_query_handle_t handle,                   ///< [in] handle of metric query object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves metric group for a device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricGroup::Get(
        Device* pDevice,                                ///< [in] pointer to the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< metric groups.
                                                        ///< if count is larger than the number of metric groups available, then
                                                        ///< the driver will update the value with the correct number of metric
                                                        ///< groups available.
        MetricGroup** ppMetricGroups                    ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                        ///< groups
        )
    {
        thread_local std::vector<xet_metric_group_handle_t> hMetricGroups;
        hMetricGroups.resize( ( ppMetricGroups ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetMetricGroupGet(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            pCount,
            hMetricGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricGroup::Get" );

        for( uint32_t i = 0; ( ppMetricGroups ) && ( i < *pCount ); ++i )
            ppMetricGroups[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMetricGroups ) && ( i < *pCount ); ++i )
                ppMetricGroups[ i ] = xet_lib::context.metricGroupFactory.getInstance( reinterpret_cast<metric_group_handle_t>( hMetricGroups[ i ] ), pDevice );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::MetricGroup::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - properties_t: metric group properties
    /// 
    /// @throws result_t
    MetricGroup::properties_t __xecall
    MetricGroup::GetProperties(
        void
        )
    {
        xet_metric_group_properties_t properties;

        auto result = static_cast<result_t>( ::xetMetricGroupGetProperties(
            reinterpret_cast<xet_metric_group_handle_t>( getHandle() ),
            &properties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricGroup::GetProperties" );

        return *reinterpret_cast<properties_t*>( &properties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Calculates metric values from raw data.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricGroup::CalculateMetricValues(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        uint8_t* pRawData,                              ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric values to be calculated.
                                                        ///< if count is non-zero, then driver will only calculate that number of
                                                        ///< metric values.
                                                        ///< if count is larger than the number available in the raw data buffer,
                                                        ///< then the driver will update the value with the actual number of metric
                                                        ///< values to be calculated.
        typed_value_t* pMetricValues                    ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                        ///< metrics
        )
    {
        auto result = static_cast<result_t>( ::xetMetricGroupCalculateMetricValues(
            reinterpret_cast<xet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            rawDataSize,
            pRawData,
            pMetricValueCount,
            reinterpret_cast<xet_typed_value_t*>( pMetricValues ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricGroup::CalculateMetricValues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves metric from a metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    Metric::Get(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metrics available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                        ///< if count is larger than the number of metrics available, then the
                                                        ///< driver will update the value with the correct number of metrics available.
        Metric** ppMetrics                              ///< [in,out][optional][range(0, *pCount)] array of pointer to metrics
        )
    {
        thread_local std::vector<xet_metric_handle_t> hMetrics;
        hMetrics.resize( ( ppMetrics ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetMetricGet(
            reinterpret_cast<xet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            pCount,
            hMetrics.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Metric::Get" );

        for( uint32_t i = 0; ( ppMetrics ) && ( i < *pCount ); ++i )
            ppMetrics[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMetrics ) && ( i < *pCount ); ++i )
                ppMetrics[ i ] = xet_lib::context.metricFactory.getInstance( reinterpret_cast<metric_handle_t>( hMetrics[ i ] ), pMetricGroup );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Metric::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a metric.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - properties_t: metric properties
    /// 
    /// @throws result_t
    Metric::properties_t __xecall
    Metric::GetProperties(
        void
        )
    {
        xet_metric_properties_t properties;

        auto result = static_cast<result_t>( ::xetMetricGetProperties(
            reinterpret_cast<xet_metric_handle_t>( getHandle() ),
            &properties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Metric::GetProperties" );

        return *reinterpret_cast<properties_t*>( &properties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Activates metric groups.
    /// 
    /// @details
    ///     - MetricGroup must be active until MetricQueryGetDeta and
    ///       ::xetMetricTracerClose.
    ///     - Conflicting metric groups cannot be activated, in such case tha call
    ///       would fail.
    /// 
    /// @throws result_t
    void __xecall
    Device::ActivateMetricGroups(
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        MetricGroup** ppMetricGroups                    ///< [in][optional][range(0, count)] handles of the metric groups to
                                                        ///< activate. NULL to deactivate.
        )
    {
        thread_local std::vector<xet_metric_group_handle_t> hMetricGroups;
        hMetricGroups.resize( 0 );
        hMetricGroups.reserve( count );
        for( uint32_t i = 0; i < count; ++i )
            hMetricGroups.emplace_back( ( ppMetricGroups ) ? reinterpret_cast<xet_metric_group_handle_t>( ppMetricGroups[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::xetDeviceActivateMetricGroups(
            reinterpret_cast<xet_device_handle_t>( getHandle() ),
            count,
            hMetricGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Device::ActivateMetricGroups" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens metric tracer for a device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @returns
    ///     - MetricTracer*: handle of metric tracer
    /// 
    /// @throws result_t
    MetricTracer* __xecall
    MetricTracer::Open(
        Device* pDevice,                                ///< [in] pointer to the device
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        desc_t* desc,                                   ///< [in,out] metric tracer descriptor
        xe::Event* pNotificationEvent                   ///< [in][optional] event used for report availability notification. Must
                                                        ///< be device to host type.
        )
    {
        xet_metric_tracer_handle_t hMetricTracer;

        auto result = static_cast<result_t>( ::xetMetricTracerOpen(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<xet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<xet_metric_tracer_desc_t*>( desc ),
            ( pNotificationEvent ) ? reinterpret_cast<xe_event_handle_t>( pNotificationEvent->getHandle() ) : nullptr,
            &hMetricTracer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricTracer::Open" );

        MetricTracer* pMetricTracer = nullptr;

        try
        {
            pMetricTracer = new MetricTracer( reinterpret_cast<metric_tracer_handle_t>( hMetricTracer ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricTracer;
            pMetricTracer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::MetricTracer::Open" );
        }

        return pMetricTracer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Append metric tracer marker into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricTracerMarker(
        MetricTracer* pMetricTracer,                    ///< [in] pointer to the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        auto result = static_cast<result_t>( ::xetCommandListAppendMetricTracerMarker(
            reinterpret_cast<xet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xet_metric_tracer_handle_t>( pMetricTracer->getHandle() ),
            value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::CommandList::AppendMetricTracerMarker" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes metric tracer.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same metric tracer handle.
    /// 
    /// @throws result_t
    void __xecall
    MetricTracer::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::xetMetricTracerClose(
            reinterpret_cast<xet_metric_tracer_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricTracer::Close" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reads data from metric tracer.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricTracer::ReadData(
        uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                        ///< if UINT32_MAX, then function will retrieve all reports available
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< reports in raw format
        )
    {
        auto result = static_cast<result_t>( ::xetMetricTracerReadData(
            reinterpret_cast<xet_metric_tracer_handle_t>( getHandle() ),
            maxReportCount,
            pRawDataSize,
            pRawData ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricTracer::ReadData" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a pool of metric queries.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQueryPool*: handle of metric query pool
    /// 
    /// @throws result_t
    MetricQueryPool* __xecall
    MetricQueryPool::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        MetricGroup* pMetricGroup,                      ///< [in] metric group associated with the query object.
        const desc_t* desc                              ///< [in] metric query pool descriptor
        )
    {
        xet_metric_query_pool_handle_t hMetricQueryPool;

        auto result = static_cast<result_t>( ::xetMetricQueryPoolCreate(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<xet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<const xet_metric_query_pool_desc_t*>( desc ),
            &hMetricQueryPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQueryPool::Create" );

        MetricQueryPool* pMetricQueryPool = nullptr;

        try
        {
            pMetricQueryPool = new MetricQueryPool( reinterpret_cast<metric_query_pool_handle_t>( hMetricQueryPool ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricQueryPool;
            pMetricQueryPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::MetricQueryPool::Create" );
        }

        return pMetricQueryPool;
    }

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
    /// @throws result_t
    void __xecall
    MetricQueryPool::Destroy(
        MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
        )
    {
        auto result = static_cast<result_t>( ::xetMetricQueryPoolDestroy(
            reinterpret_cast<xet_metric_query_pool_handle_t>( pMetricQueryPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQueryPool::Destroy" );

        delete pMetricQueryPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates metric query object.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQuery*: handle of metric query
    /// 
    /// @throws result_t
    MetricQuery* __xecall
    MetricQuery::Create(
        MetricQueryPool* pMetricQueryPool,              ///< [in] pointer to the metric query pool
        uint32_t index                                  ///< [in] index of the query within the pool
        )
    {
        xet_metric_query_handle_t hMetricQuery;

        auto result = static_cast<result_t>( ::xetMetricQueryCreate(
            reinterpret_cast<xet_metric_query_pool_handle_t>( pMetricQueryPool->getHandle() ),
            index,
            &hMetricQuery ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQuery::Create" );

        MetricQuery* pMetricQuery = nullptr;

        try
        {
            pMetricQuery = new MetricQuery( reinterpret_cast<metric_query_handle_t>( hMetricQuery ), nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricQuery;
            pMetricQuery = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::MetricQuery::Create" );
        }

        return pMetricQuery;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a metric query object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the query before it is deleted
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query handle.
    /// 
    /// @throws result_t
    void __xecall
    MetricQuery::Destroy(
        MetricQuery* pMetricQuery                       ///< [in][release] pointer to metric query
        )
    {
        auto result = static_cast<result_t>( ::xetMetricQueryDestroy(
            reinterpret_cast<xet_metric_query_handle_t>( pMetricQuery->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQuery::Destroy" );

        delete pMetricQuery;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Resets a metric query object back to inital state.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the query before it is reset
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query handle.
    /// 
    /// @throws result_t
    void __xecall
    MetricQuery::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::xetMetricQueryReset(
            reinterpret_cast<xet_metric_query_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQuery::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query begin into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricQueryBegin(
        MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
        )
    {
        auto result = static_cast<result_t>( ::xetCommandListAppendMetricQueryBegin(
            reinterpret_cast<xet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xet_metric_query_handle_t>( pMetricQuery->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::CommandList::AppendMetricQueryBegin" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query end into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricQueryEnd(
        MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
        xe::Event* pCompletionEvent                     ///< [in][optional] pointer to the completion event to signal
        )
    {
        auto result = static_cast<result_t>( ::xetCommandListAppendMetricQueryEnd(
            reinterpret_cast<xet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xet_metric_query_handle_t>( pMetricQuery->getHandle() ),
            ( pCompletionEvent ) ? reinterpret_cast<xe_event_handle_t>( pCompletionEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::CommandList::AppendMetricQueryEnd" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query commands to flush all caches.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricMemoryBarrier(
        void
        )
    {
        auto result = static_cast<result_t>( ::xetCommandListAppendMetricMemoryBarrier(
            reinterpret_cast<xet_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::CommandList::AppendMetricMemoryBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves raw data for a given metric query.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricQuery::GetData(
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                        ///< reports in raw format
        )
    {
        auto result = static_cast<result_t>( ::xetMetricQueryGetData(
            reinterpret_cast<xet_metric_query_handle_t>( getHandle() ),
            pRawDataSize,
            pRawData ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQuery::GetData" );
    }

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( const value_type_t val )
    {
        std::string str;

        switch( val )
        {
        case value_type_t::UINT32:
            str = "value_type_t::UINT32";
            break;

        case value_type_t::UINT64:
            str = "value_type_t::UINT64";
            break;

        case value_type_t::FLOAT32:
            str = "value_type_t::FLOAT32";
            break;

        case value_type_t::FLOAT64:
            str = "value_type_t::FLOAT64";
            break;

        case value_type_t::BOOL8:
            str = "value_type_t::BOOL8";
            break;

        default:
            str = "value_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_t to std::string
    std::string to_string( const value_t val )
    {
        std::string str;
        
        str += "value_t::ui32 : ";
        str += std::to_string(val.ui32);
        str += "\n";
        
        str += "value_t::ui64 : ";
        str += std::to_string(val.ui64);
        str += "\n";
        
        str += "value_t::fp32 : ";
        str += std::to_string(val.fp32);
        str += "\n";
        
        str += "value_t::fp64 : ";
        str += std::to_string(val.fp64);
        str += "\n";
        
        str += "value_t::b8 : ";
        str += std::to_string(val.b8);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_t to std::string
    std::string to_string( const typed_value_t val )
    {
        std::string str;
        
        str += "typed_value_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "typed_value_t::value : ";
        str += to_string(val.value);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type_t to std::string
    std::string to_string( const MetricGroup::sampling_type_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(MetricGroup::sampling_type_t::EVENT_BASED) & bits )
            str += "EVENT_BASED | ";
        
        if( static_cast<uint32_t>(MetricGroup::sampling_type_t::TIME_BASED) & bits )
            str += "TIME_BASED | ";

        return ( str.size() > 3 ) 
            ? "MetricGroup::sampling_type_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "MetricGroup::sampling_type_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_version_t to std::string
    std::string to_string( const MetricGroup::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricGroup::properties_version_t::CURRENT:
            str = "MetricGroup::properties_version_t::CURRENT";
            break;

        default:
            str = "MetricGroup::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_t to std::string
    std::string to_string( const MetricGroup::properties_t val )
    {
        std::string str;
        
        str += "MetricGroup::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "MetricGroup::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "MetricGroup::properties_t::description : ";
        str += val.description;
        str += "\n";
        
        str += "MetricGroup::properties_t::samplingType : ";
        str += to_string(val.samplingType);
        str += "\n";
        
        str += "MetricGroup::properties_t::domain : ";
        str += std::to_string(val.domain);
        str += "\n";
        
        str += "MetricGroup::properties_t::metricCount : ";
        str += std::to_string(val.metricCount);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( const Metric::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Metric::type_t::DURATION:
            str = "Metric::type_t::DURATION";
            break;

        case Metric::type_t::EVENT:
            str = "Metric::type_t::EVENT";
            break;

        case Metric::type_t::EVENT_WITH_RANGE:
            str = "Metric::type_t::EVENT_WITH_RANGE";
            break;

        case Metric::type_t::THROUGHPUT:
            str = "Metric::type_t::THROUGHPUT";
            break;

        case Metric::type_t::TIMESTAMP:
            str = "Metric::type_t::TIMESTAMP";
            break;

        case Metric::type_t::FLAG:
            str = "Metric::type_t::FLAG";
            break;

        case Metric::type_t::RATIO:
            str = "Metric::type_t::RATIO";
            break;

        case Metric::type_t::RAW:
            str = "Metric::type_t::RAW";
            break;

        default:
            str = "Metric::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_version_t to std::string
    std::string to_string( const Metric::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Metric::properties_version_t::CURRENT:
            str = "Metric::properties_version_t::CURRENT";
            break;

        default:
            str = "Metric::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_t to std::string
    std::string to_string( const Metric::properties_t val )
    {
        std::string str;
        
        str += "Metric::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Metric::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Metric::properties_t::description : ";
        str += val.description;
        str += "\n";
        
        str += "Metric::properties_t::component : ";
        str += val.component;
        str += "\n";
        
        str += "Metric::properties_t::tierNumber : ";
        str += std::to_string(val.tierNumber);
        str += "\n";
        
        str += "Metric::properties_t::metricType : ";
        str += to_string(val.metricType);
        str += "\n";
        
        str += "Metric::properties_t::resultType : ";
        str += to_string(val.resultType);
        str += "\n";
        
        str += "Metric::properties_t::resultUnits : ";
        str += val.resultUnits;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_version_t to std::string
    std::string to_string( const MetricTracer::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricTracer::desc_version_t::CURRENT:
            str = "MetricTracer::desc_version_t::CURRENT";
            break;

        default:
            str = "MetricTracer::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_t to std::string
    std::string to_string( const MetricTracer::desc_t val )
    {
        std::string str;
        
        str += "MetricTracer::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "MetricTracer::desc_t::notifyEveryNReports : ";
        str += std::to_string(val.notifyEveryNReports);
        str += "\n";
        
        str += "MetricTracer::desc_t::samplingPeriod : ";
        str += std::to_string(val.samplingPeriod);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_version_t to std::string
    std::string to_string( const MetricQueryPool::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricQueryPool::desc_version_t::CURRENT:
            str = "MetricQueryPool::desc_version_t::CURRENT";
            break;

        default:
            str = "MetricQueryPool::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::flag_t to std::string
    std::string to_string( const MetricQueryPool::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricQueryPool::flag_t::PERFORMANCE:
            str = "MetricQueryPool::flag_t::PERFORMANCE";
            break;

        case MetricQueryPool::flag_t::SKIP_EXECUTION:
            str = "MetricQueryPool::flag_t::SKIP_EXECUTION";
            break;

        default:
            str = "MetricQueryPool::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_t to std::string
    std::string to_string( const MetricQueryPool::desc_t val )
    {
        std::string str;
        
        str += "MetricQueryPool::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "MetricQueryPool::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "MetricQueryPool::desc_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

} // namespace xet
