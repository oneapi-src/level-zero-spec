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
* @file xet_metric.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Metric
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/metric.yml
* @endcond
*
******************************************************************************/
#include "xet_lib.h"

extern "C" {

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
    )
{
    auto pfnGet = xet_lib::lib.ddiTable.MetricGroup.pfnGet;

#if _DEBUG
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGet( hDeviceGroup, pCount, phMetricGroup );
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
    auto pfnGetProperties = xet_lib::lib.ddiTable.MetricGroup.pfnGetProperties;

#if _DEBUG
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetProperties( hMetricGroup, pProperties );
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
///         + nullptr == phMetric
///         + invalid metric group handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGet(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t ordinal,                               ///< [in] ordinal of metric to retrieve; must be less than
                                                    ///< ::xet_metric_group_properties_t::metricCount
    xet_metric_handle_t* phMetric                   ///< [out] handle of metric
    )
{
    auto pfnGet = xet_lib::lib.ddiTable.Metric.pfnGet;

#if _DEBUG
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGet( hMetricGroup, ordinal, phMetric );
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
    auto pfnGetProperties = xet_lib::lib.ddiTable.Metric.pfnGetProperties;

#if _DEBUG
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetProperties( hMetric, pProperties );
}

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
    )
{
    auto pfnCalculateData = xet_lib::lib.ddiTable.MetricGroup.pfnCalculateData;

#if _DEBUG
    if( nullptr == pfnCalculateData )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCalculateData( hMetricGroup, count, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );
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
///         + nullptr == phMetricGroups
///         + invalid metric groups
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetDeviceActivateMetricGroups(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    xet_metric_group_handle_t* phMetricGroups       ///< [in][range(0, count)] handles of the metric groups to activate. NULL
                                                    ///< to deactivate.
    )
{
    auto pfnActivateMetricGroups = xet_lib::lib.ddiTable.Device.pfnActivateMetricGroups;

#if _DEBUG
    if( nullptr == pfnActivateMetricGroups )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    )
{
    auto pfnOpen = xet_lib::lib.ddiTable.MetricTracer.pfnOpen;

#if _DEBUG
    if( nullptr == pfnOpen )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnOpen( hDevice, hMetricGroup, pDesc, hNotificationEvent, phMetricTracer );
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
    auto pfnAppendMetricTracerMarker = xet_lib::lib.ddiTable.CommandList.pfnAppendMetricTracerMarker;

#if _DEBUG
    if( nullptr == pfnAppendMetricTracerMarker )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnClose = xet_lib::lib.ddiTable.MetricTracer.pfnClose;

#if _DEBUG
    if( nullptr == pfnClose )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    )
{
    auto pfnReadData = xet_lib::lib.ddiTable.MetricTracer.pfnReadData;

#if _DEBUG
    if( nullptr == pfnReadData )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnReadData( hMetricTracer, pReportCount, rawDataSize, pRawData );
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
    )
{
    auto pfnCreate = xet_lib::lib.ddiTable.MetricQueryPool.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hDevice, hMetricGroup, pDesc, phMetricQueryPool );
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
    auto pfnDestroy = xet_lib::lib.ddiTable.MetricQueryPool.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnCreate = xet_lib::lib.ddiTable.MetricQuery.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnDestroy = xet_lib::lib.ddiTable.MetricQuery.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnReset = xet_lib::lib.ddiTable.MetricQuery.pfnReset;

#if _DEBUG
    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnAppendMetricQueryBegin = xet_lib::lib.ddiTable.CommandList.pfnAppendMetricQueryBegin;

#if _DEBUG
    if( nullptr == pfnAppendMetricQueryBegin )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
///         + nullptr == hCompletionEvent
///         + invalid handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
    xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
    )
{
    auto pfnAppendMetricQueryEnd = xet_lib::lib.ddiTable.CommandList.pfnAppendMetricQueryEnd;

#if _DEBUG
    if( nullptr == pfnAppendMetricQueryEnd )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
    auto pfnAppendMetricMemoryBarrier = xet_lib::lib.ddiTable.CommandList.pfnAppendMetricMemoryBarrier;

#if _DEBUG
    if( nullptr == pfnAppendMetricMemoryBarrier )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendMetricMemoryBarrier( hCommandList );
}

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
    )
{
    auto pfnGetData = xet_lib::lib.ddiTable.MetricQuery.pfnGetData;

#if _DEBUG
    if( nullptr == pfnGetData )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetData( hMetricQuery, count, rawDataSize, pRawData );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    MetricGroup::MetricGroup( 
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Metric::Metric( 
        MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
        ) :
        m_pMetricGroup( pMetricGroup )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricTracer::MetricTracer( 
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQueryPool::MetricQueryPool( 
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQuery::MetricQuery( 
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves metric group for a device group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricGroup::Get(
        DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< metric groups.
        MetricGroup** ppMetricGroup                     ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                        ///< groups
        )
    {
        thread_local std::vector<xet_metric_group_handle_t> hMetricGroup;
        hMetricGroup.resize( ( ppMetricGroup ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetMetricGroupGet(
            reinterpret_cast<xet_device_group_handle_t>( pDeviceGroup->getHandle() ),
            pCount,
            hMetricGroup.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricGroup::Get" );

        for( uint32_t i = 0; ( ppMetricGroup ) && ( i < *pCount ); ++i )
            ppMetricGroup[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMetricGroup ) && ( i < *pCount ); ++i )
                ppMetricGroup[ i ] = new MetricGroup( nullptr );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppMetricGroup ) && ( i < *pCount ); ++i )
            {
                delete ppMetricGroup[ i ];
                ppMetricGroup[ i ] = nullptr;
            }

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
    /// @brief Retrieves metric from a metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - Metric*: handle of metric
    /// 
    /// @throws result_t
    Metric* __xecall
    Metric::Get(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        uint32_t ordinal                                ///< [in] ordinal of metric to retrieve; must be less than
                                                        ///< ::metric_group_properties_t::metricCount
        )
    {
        xet_metric_handle_t hMetric;

        auto result = static_cast<result_t>( ::xetMetricGet(
            reinterpret_cast<xet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            ordinal,
            &hMetric ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Metric::Get" );

        Metric* pMetric = nullptr;

        try
        {
            pMetric = new Metric( pMetricGroup );
        }
        catch( std::bad_alloc& )
        {
            delete pMetric;
            pMetric = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Metric::Get" );
        }

        return pMetric;
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
    /// @brief Calculates counter values from raw data.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads wth the same metric group handle.
    /// 
    /// @throws result_t
    void __xecall
    MetricGroup::CalculateData(
        uint32_t count,                                 ///< [in,out] number of reports to calculate
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        uint8_t* pRawData,                              ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        size_t calculatedDataSize,                      ///< [in] size in bytes of calculated metrics
        typed_value_t* pCalculatedData                  ///< [in,out][range(0, calculatedDataSize)] buffer of calculated metrics
        )
    {
        auto result = static_cast<result_t>( ::xetMetricGroupCalculateData(
            reinterpret_cast<xet_metric_group_handle_t>( getHandle() ),
            count,
            rawDataSize,
            pRawData,
            calculatedDataSize,
            reinterpret_cast<xet_typed_value_t*>( pCalculatedData ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricGroup::CalculateData" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Activates metric groups.
    /// 
    /// @details
    ///     - MetricGroup must be active until MetricQueryGetDeta and
    ///       ::MetricTracerClose.
    ///     - Conflicting metric groups cannot be activated, in such case tha call
    ///       would fail.
    /// 
    /// @throws result_t
    void __xecall
    Device::ActivateMetricGroups(
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        MetricGroup** ppMetricGroups                    ///< [in][range(0, count)] handles of the metric groups to activate. NULL
                                                        ///< to deactivate.
        )
    {
        thread_local std::vector<xet_metric_group_handle_t> hMetricGroups;
        hMetricGroups.resize( 0 );
        hMetricGroups.reserve( count );
        for( uint32_t i = 0; i < count; ++i )
            hMetricGroups.emplace_back( reinterpret_cast<xet_metric_group_handle_t>( ppMetricGroups[ i ]->getHandle() ) );

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
        desc_t* pDesc,                                  ///< [in,out] metric tracer descriptor
        xe::Event* pNotificationEvent                   ///< [in] event used for report availability notification. Must be device
                                                        ///< to host type.
        )
    {
        xet_metric_tracer_handle_t hMetricTracer;

        auto result = static_cast<result_t>( ::xetMetricTracerOpen(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<xet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<xet_metric_tracer_desc_t*>( pDesc ),
            reinterpret_cast<xe_event_handle_t>( pNotificationEvent->getHandle() ),
            &hMetricTracer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricTracer::Open" );

        MetricTracer* pMetricTracer = nullptr;

        try
        {
            pMetricTracer = new MetricTracer( pDevice );
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
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data buffer size
        uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
        )
    {
        auto result = static_cast<result_t>( ::xetMetricTracerReadData(
            reinterpret_cast<xet_metric_tracer_handle_t>( getHandle() ),
            pReportCount,
            rawDataSize,
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
        desc_t* pDesc                                   ///< [in] metric query pool creation data
        )
    {
        xet_metric_query_pool_handle_t hMetricQueryPool;

        auto result = static_cast<result_t>( ::xetMetricQueryPoolCreate(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<xet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<xet_metric_query_pool_desc_t*>( pDesc ),
            &hMetricQueryPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQueryPool::Create" );

        MetricQueryPool* pMetricQueryPool = nullptr;

        try
        {
            pMetricQueryPool = new MetricQueryPool( pDevice );
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
            pMetricQuery = new MetricQuery( nullptr );
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
        xe::Event* pCompletionEvent                     ///< [in] pointer to the completion event to signal
        )
    {
        auto result = static_cast<result_t>( ::xetCommandListAppendMetricQueryEnd(
            reinterpret_cast<xet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xet_metric_query_handle_t>( pMetricQuery->getHandle() ),
            reinterpret_cast<xe_event_handle_t>( pCompletionEvent->getHandle() ) ) );

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
    /// @brief Retrieves raw data for a given metric query slot.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricQuery::GetData(
        uint32_t count,                                 ///< [in] number of query reports to read
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        uint8_t* pRawData                               ///< [in,out][range(0, rawDataSize)] buffer containing query results in raw
                                                        ///< format
        )
    {
        auto result = static_cast<result_t>( ::xetMetricQueryGetData(
            reinterpret_cast<xet_metric_query_handle_t>( getHandle() ),
            count,
            rawDataSize,
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

        case value_type_t::FLOAT:
            str = "value_type_t::FLOAT";
            break;

        case value_type_t::BOOL:
            str = "value_type_t::BOOL";
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
        
        str += "value_t::valueUInt32 : ";
        str += std::to_string(val.valueUInt32);
        str += "\n";
        
        str += "value_t::valueUInt64 : ";
        str += std::to_string(val.valueUInt64);
        str += "\n";
        
        str += "value_t::valueFloat : ";
        str += std::to_string(val.valueFloat);
        str += "\n";
        
        str += "value_t::valueBool : ";
        str += std::to_string(val.valueBool);
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
        if( 0 == bits ) return std::string("{}");

        std::string str;
        
        if( static_cast<uint32_t>(MetricGroup::sampling_type_t::EVENT_BASED) & bits )
            str += "MetricGroup::sampling_type_t::EVENT_BASED | ";
        
        if( static_cast<uint32_t>(MetricGroup::sampling_type_t::TIME_BASED) & bits )
            str += "MetricGroup::sampling_type_t::TIME_BASED | ";

        return "{ " + str.substr(0, str.size() - 3) + " }";
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
        
        str += "MetricGroup::properties_t::rawReportSize : ";
        str += std::to_string(val.rawReportSize);
        str += "\n";
        
        str += "MetricGroup::properties_t::calculatedReportSize : ";
        str += std::to_string(val.calculatedReportSize);
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
