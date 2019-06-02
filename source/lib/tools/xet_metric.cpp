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
/// @brief Returns metric group count for a given device.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupGetCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    )
{
    auto pfnGetCount = xet_lib::lib.ddiTable.MetricGroup.pfnGetCount;

#if _DEBUG
    if( nullptr == pfnGetCount )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetCount( hDevice, pCount );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns metric group handle for a device.
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
///         + nullptr == phMetricGroup
///         + devices do not contain a given metric group
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupGet(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t ordinal,                               ///< [in] metric group index
    xet_metric_group_handle_t* phMetricGroup        ///< [out] metric group handle
    )
{
    auto pfnGet = xet_lib::lib.ddiTable.MetricGroup.pfnGet;

#if _DEBUG
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGet( hDevice, ordinal, phMetricGroup );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns properties for a given metric group.
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
/// @brief Returns metric from a given metric group.
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
    uint32_t ordinal,                               ///< [in] metric index
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
/// @brief Returns metric properties.
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
///         + nullptr == pReportCount
///         + nullptr == pRawData
///         + nullptr == pCalculatedData
///         + invalid metric group handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricGroupCalculateData(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t* pReportCount,                         ///< [in,out] report count to calculate
    uint32_t rawDataSize,                           ///< [in] raw data size
    uint8_t* pRawData,                              ///< [in] raw data to calculate
    uint32_t calculatedDataSize,                    ///< [in] calculated data size
    xet_typed_value_t* pCalculatedData              ///< [in,out] calculated metrics
    )
{
    auto pfnCalculateData = xet_lib::lib.ddiTable.MetricGroup.pfnCalculateData;

#if _DEBUG
    if( nullptr == pfnCalculateData )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCalculateData( hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );
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
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
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
/// @brief Opens metric tracer for a given device.
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
///         + nullptr == pDesc
///         + nullptr == hNotificationEvent
///         + nullptr == phMetricTracer
///         + devices do not support metric tracer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XET_METRIC_TRACER_DESC_VERSION_CURRENT < pDesc->version
xe_result_t __xecall
xetMetricTracerOpen(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
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

    return pfnOpen( hDevice, pDesc, hNotificationEvent, phMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Append metric tracer marker to a given command list.
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
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
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
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
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
/// @brief Creates metric query pool.
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
///         + nullptr == pDesc
///         + nullptr == phMetricQueryPool
///         + invalid device handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < pDesc->version
xe_result_t __xecall
xetMetricQueryPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
    xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    )
{
    auto pfnCreate = xet_lib::lib.ddiTable.MetricQueryPool.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hDevice, pDesc, phMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys query pool object.
/// 
/// @details
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
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
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
/// @brief Returns metric query handle from a given metric query pool.
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
xetMetricQueryPoolGetMetricQuery(
    xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t ordinal,                               ///< [in] index of the query within the pool
    xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    )
{
    auto pfnGetMetricQuery = xet_lib::lib.ddiTable.MetricQueryPool.pfnGetMetricQuery;

#if _DEBUG
    if( nullptr == pfnGetMetricQuery )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetMetricQuery( hMetricQueryPool, ordinal, phMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query begin commands to command list.
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
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
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
/// @brief Appends metric query end commands to command list.
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
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
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
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
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
/// @brief Returns raw data for a given metric query slot.
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
///         + nullptr == pReportCount
///         + nullptr == pRawData
///         + invalid metric query handle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetMetricQueryGetData(
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
    uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
    uint8_t* pRawData                               ///< [in,out] query result data in raw format
    )
{
    auto pfnGetData = xet_lib::lib.ddiTable.MetricQuery.pfnGetData;

#if _DEBUG
    if( nullptr == pfnGetData )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );
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
    /// @brief Returns metric group count for a given device.
    /// 
    /// @returns
    ///     - uint32_t: number of metric groups supported by the device
    /// 
    /// @throws result_t
    uint32_t __xecall
    MetricGroup::GetCount(
        xe::Device* pDevice                             ///< [in] pointer to the device object
        )
    {
        uint32_t count;

        auto result = static_cast<result_t>( ::xetMetricGroupGetCount(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            &count ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricGroup::GetCount" );

        return count;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns metric group handle for a device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricGroup*: metric group handle
    /// 
    /// @throws result_t
    MetricGroup* __xecall
    MetricGroup::Get(
        xe::Device* pDevice,                            ///< [in] pointer to the device
        uint32_t ordinal                                ///< [in] metric group index
        )
    {
        xet_metric_group_handle_t hMetricGroup;

        auto result = static_cast<result_t>( ::xetMetricGroupGet(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            ordinal,
            &hMetricGroup ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricGroup::Get" );

        MetricGroup* pMetricGroup = nullptr;

        try
        {
            pMetricGroup = new MetricGroup( pDevice );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricGroup;
            pMetricGroup = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::MetricGroup::Get" );
        }

        return pMetricGroup;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns properties for a given metric group.
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
    /// @brief Returns metric from a given metric group.
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
        uint32_t ordinal                                ///< [in] metric index
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
    /// @brief Returns metric properties.
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
        uint32_t* pReportCount,                         ///< [in,out] report count to calculate
        uint32_t rawDataSize,                           ///< [in] raw data size
        uint8_t* pRawData,                              ///< [in] raw data to calculate
        uint32_t calculatedDataSize,                    ///< [in] calculated data size
        typed_value_t* pCalculatedData                  ///< [in,out] calculated metrics
        )
    {
        auto result = static_cast<result_t>( ::xetMetricGroupCalculateData(
            reinterpret_cast<xet_metric_group_handle_t>( getHandle() ),
            pReportCount,
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
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            count,
            hMetricGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Device::ActivateMetricGroups" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens metric tracer for a given device.
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
        xe::Device* pDevice,                            ///< [in] pointer to the device
        desc_t* pDesc,                                  ///< [in,out] metric tracer descriptor
        xe::Event* pNotificationEvent                   ///< [in] event used for report availability notification. Must be device
                                                        ///< to host type.
        )
    {
        xet_metric_tracer_handle_t hMetricTracer;

        auto result = static_cast<result_t>( ::xetMetricTracerOpen(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
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
    /// @brief Append metric tracer marker to a given command list.
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
            reinterpret_cast<xe_command_list_handle_t>( pCommandList->getHandle() ),
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
    /// @brief Creates metric query pool.
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
        xe::Device* pDevice,                            ///< [in] pointer to the device
        desc_t* pDesc                                   ///< [in] metric query pool creation data
        )
    {
        xet_metric_query_pool_handle_t hMetricQueryPool;

        auto result = static_cast<result_t>( ::xetMetricQueryPoolCreate(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
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
    /// @brief Destroys query pool object.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query pool handle.
    /// 
    /// @throws result_t
    void __xecall
    MetricQueryPool::Destroy(
        MetricQueryPool* pMetricQueryPool               ///< [in] pointer to the metric query pool
        )
    {
        auto result = static_cast<result_t>( ::xetMetricQueryPoolDestroy(
            reinterpret_cast<xet_metric_query_pool_handle_t>( pMetricQueryPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQueryPool::Destroy" );

        delete pMetricQueryPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns metric query handle from a given metric query pool.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQuery*: handle of metric query
    /// 
    /// @throws result_t
    MetricQuery* __xecall
    MetricQueryPool::GetMetricQuery(
        uint32_t ordinal                                ///< [in] index of the query within the pool
        )
    {
        xet_metric_query_handle_t hMetricQuery;

        auto result = static_cast<result_t>( ::xetMetricQueryPoolGetMetricQuery(
            reinterpret_cast<xet_metric_query_pool_handle_t>( getHandle() ),
            ordinal,
            &hMetricQuery ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQueryPool::GetMetricQuery" );

        MetricQuery* pMetricQuery = nullptr;

        try
        {
            pMetricQuery = new MetricQuery( nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricQuery;
            pMetricQuery = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::MetricQueryPool::GetMetricQuery" );
        }

        return pMetricQuery;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query begin commands to command list.
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
            reinterpret_cast<xe_command_list_handle_t>( pCommandList->getHandle() ),
            reinterpret_cast<xet_metric_query_handle_t>( pMetricQuery->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::CommandList::AppendMetricQueryBegin" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query end commands to command list.
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
            reinterpret_cast<xe_command_list_handle_t>( pCommandList->getHandle() ),
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
            reinterpret_cast<xe_command_list_handle_t>( pCommandList->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::CommandList::AppendMetricMemoryBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns raw data for a given metric query slot.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricQuery::GetData(
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
        uint8_t* pRawData                               ///< [in,out] query result data in raw format
        )
    {
        auto result = static_cast<result_t>( ::xetMetricQueryGetData(
            reinterpret_cast<xet_metric_query_handle_t>( getHandle() ),
            pReportCount,
            rawDataSize,
            pRawData ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::MetricQuery::GetData" );
    }

} // namespace xet

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts value_type_t to std::string
std::string to_string( xet::value_type_t val )
{
    switch( val )
    {
    case xet::value_type_t::UINT32:
        return std::string("xet::value_type_t::UINT32");
    case xet::value_type_t::UINT64:
        return std::string("xet::value_type_t::UINT64");
    case xet::value_type_t::FLOAT:
        return std::string("xet::value_type_t::FLOAT");
    case xet::value_type_t::BOOL:
        return std::string("xet::value_type_t::BOOL");
    };
    return std::string("xet::value_type_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts typed_value_version_t to std::string
std::string to_string( xet::typed_value_version_t val )
{
    switch( val )
    {
    case xet::typed_value_version_t::CURRENT:
        return std::string("xet::typed_value_version_t::CURRENT");
    };
    return std::string("xet::typed_value_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts MetricGroup::sampling_type_t to std::string
std::string to_string( xet::MetricGroup::sampling_type_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xet::MetricGroup::sampling_type_t::EVENT_BASED) & bits )
        str += "xet::MetricGroup::sampling_type_t::EVENT_BASED | ";
    if( static_cast<uint32_t>(xet::MetricGroup::sampling_type_t::TIME_BASED) & bits )
        str += "xet::MetricGroup::sampling_type_t::TIME_BASED | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts MetricGroup::properties_version_t to std::string
std::string to_string( xet::MetricGroup::properties_version_t val )
{
    switch( val )
    {
    case xet::MetricGroup::properties_version_t::CURRENT:
        return std::string("xet::MetricGroup::properties_version_t::CURRENT");
    };
    return std::string("xet::MetricGroup::properties_version_t::?");
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Metric::type_t to std::string
std::string to_string( xet::Metric::type_t val )
{
    switch( val )
    {
    case xet::Metric::type_t::DURATION:
        return std::string("xet::Metric::type_t::DURATION");
    case xet::Metric::type_t::EVENT:
        return std::string("xet::Metric::type_t::EVENT");
    case xet::Metric::type_t::EVENT_WITH_RANGE:
        return std::string("xet::Metric::type_t::EVENT_WITH_RANGE");
    case xet::Metric::type_t::THROUGHPUT:
        return std::string("xet::Metric::type_t::THROUGHPUT");
    case xet::Metric::type_t::TIMESTAMP:
        return std::string("xet::Metric::type_t::TIMESTAMP");
    case xet::Metric::type_t::FLAG:
        return std::string("xet::Metric::type_t::FLAG");
    case xet::Metric::type_t::RATIO:
        return std::string("xet::Metric::type_t::RATIO");
    case xet::Metric::type_t::RAW:
        return std::string("xet::Metric::type_t::RAW");
    };
    return std::string("xet::Metric::type_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Metric::properties_version_t to std::string
std::string to_string( xet::Metric::properties_version_t val )
{
    switch( val )
    {
    case xet::Metric::properties_version_t::CURRENT:
        return std::string("xet::Metric::properties_version_t::CURRENT");
    };
    return std::string("xet::Metric::properties_version_t::?");
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Converts MetricTracer::desc_version_t to std::string
std::string to_string( xet::MetricTracer::desc_version_t val )
{
    switch( val )
    {
    case xet::MetricTracer::desc_version_t::CURRENT:
        return std::string("xet::MetricTracer::desc_version_t::CURRENT");
    };
    return std::string("xet::MetricTracer::desc_version_t::?");
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Converts MetricQueryPool::flag_t to std::string
std::string to_string( xet::MetricQueryPool::flag_t val )
{
    switch( val )
    {
    case xet::MetricQueryPool::flag_t::PERFORMANCE:
        return std::string("xet::MetricQueryPool::flag_t::PERFORMANCE");
    case xet::MetricQueryPool::flag_t::SKIP_EXECUTION:
        return std::string("xet::MetricQueryPool::flag_t::SKIP_EXECUTION");
    };
    return std::string("xet::MetricQueryPool::flag_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts MetricQueryPool::desc_version_t to std::string
std::string to_string( xet::MetricQueryPool::desc_version_t val )
{
    switch( val )
    {
    case xet::MetricQueryPool::desc_version_t::CURRENT:
        return std::string("xet::MetricQueryPool::desc_version_t::CURRENT");
    };
    return std::string("xet::MetricQueryPool::desc_version_t::?");
}



#endif // _DEBUG
