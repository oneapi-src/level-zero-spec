/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_tools_loader.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/ldrddi.cpp.mako
 * @endcond
 *
 */
#include "xe_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    xet_device_group_factory_t          xet_device_group_factory;
    xet_device_factory_t                xet_device_factory;
    xet_command_list_factory_t          xet_command_list_factory;
    xet_module_factory_t                xet_module_factory;
    xet_function_factory_t              xet_function_factory;
    xet_metric_group_factory_t          xet_metric_group_factory;
    xet_metric_factory_t                xet_metric_factory;
    xet_metric_tracer_factory_t         xet_metric_tracer_factory;
    xet_metric_query_pool_factory_t     xet_metric_query_pool_factory;
    xet_metric_query_factory_t          xet_metric_query_factory;
    xet_tracer_factory_t                xet_tracer_factory;
    xet_sysman_factory_t                xet_sysman_factory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetInit
    xe_result_t __xecall
    xetInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        for( auto& drv : context.drivers )
        {
            if( XE_RESULT_SUCCESS == result )
            {
                result = drv.dditable.xet.Global.pfnInit( flags );
            }
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGroupGet
    xe_result_t __xecall
    xetMetricGroupGet(
        xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGet = dditable->xet.MetricGroup.pfnGet;
        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xet_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGet( hDeviceGroup, pCount, phMetricGroups );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < *pCount ); ++i )
                phMetricGroups[ i ] = reinterpret_cast<xet_metric_group_handle_t>(
                    xet_metric_group_factory.getInstance( phMetricGroups[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGroupGetProperties
    xe_result_t __xecall
    xetMetricGroupGetProperties(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnGetProperties = dditable->xet.MetricGroup.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMetricGroup, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGroupCalculateMetricValues
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnCalculateMetricValues = dditable->xet.MetricGroup.pfnCalculateMetricValues;
        if( nullptr == pfnCalculateMetricValues )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGet
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnGet = dditable->xet.Metric.pfnGet;
        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGet( hMetricGroup, pCount, phMetrics );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetrics ) && ( i < *pCount ); ++i )
                phMetrics[ i ] = reinterpret_cast<xet_metric_handle_t>(
                    xet_metric_factory.getInstance( phMetrics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGetProperties
    xe_result_t __xecall
    xetMetricGetProperties(
        xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        xet_metric_properties_t* pProperties            ///< [out] metric properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_object_t*>( hMetric )->dditable;
        auto pfnGetProperties = dditable->xet.Metric.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetric = reinterpret_cast<xet_metric_object_t*>( hMetric )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMetric, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetDeviceActivateMetricGroups
    xe_result_t __xecall
    xetDeviceActivateMetricGroups(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        xet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                        ///< activate. NULL to deactivate.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnActivateMetricGroups = dditable->xet.Device.pfnActivateMetricGroups;
        if( nullptr == pfnActivateMetricGroups )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < count ); ++i )
            phMetricGroups[ i ] = reinterpret_cast<xet_metric_group_object_t*>( phMetricGroups[ i ] )->handle;

        // forward to device-driver
        result = pfnActivateMetricGroups( hDevice, count, phMetricGroups );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricTracerOpen
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnOpen = dditable->xet.MetricTracer.pfnOpen;
        if( nullptr == pfnOpen )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // convert loader handle to driver handle
        hNotificationEvent = ( hNotificationEvent ) ? reinterpret_cast<xe_event_object_t*>( hNotificationEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );

        try
        {
            // convert driver handle to loader handle
            *phMetricTracer = reinterpret_cast<xet_metric_tracer_handle_t>(
                xet_metric_tracer_factory.getInstance( *phMetricTracer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricTracerMarker
    xe_result_t __xecall
    xetCommandListAppendMetricTracerMarker(
        xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricTracerMarker = dditable->xet.CommandList.pfnAppendMetricTracerMarker;
        if( nullptr == pfnAppendMetricTracerMarker )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricTracerClose
    xe_result_t __xecall
    xetMetricTracerClose(
        xet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->dditable;
        auto pfnClose = dditable->xet.MetricTracer.pfnClose;
        if( nullptr == pfnClose )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnClose( hMetricTracer );

        // release loader handle
        xet_metric_tracer_factory.release( hMetricTracer );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricTracerReadData
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->dditable;
        auto pfnReadData = dditable->xet.MetricTracer.pfnReadData;
        if( nullptr == pfnReadData )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryPoolCreate
    xe_result_t __xecall
    xetMetricQueryPoolCreate(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device
        xet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const xet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xet.MetricQueryPool.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );

        try
        {
            // convert driver handle to loader handle
            *phMetricQueryPool = reinterpret_cast<xet_metric_query_pool_handle_t>(
                xet_metric_query_pool_factory.getInstance( *phMetricQueryPool, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryPoolDestroy
    xe_result_t __xecall
    xetMetricQueryPoolDestroy(
        xet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;
        auto pfnDestroy = dditable->xet.MetricQueryPool.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        result = pfnDestroy( hMetricQueryPool );

        // release loader handle
        xet_metric_query_pool_factory.release( hMetricQueryPool );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryCreate
    xe_result_t __xecall
    xetMetricQueryCreate(
        xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;
        auto pfnCreate = dditable->xet.MetricQuery.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        result = pfnCreate( hMetricQueryPool, index, phMetricQuery );

        try
        {
            // convert driver handle to loader handle
            *phMetricQuery = reinterpret_cast<xet_metric_query_handle_t>(
                xet_metric_query_factory.getInstance( *phMetricQuery, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryDestroy
    xe_result_t __xecall
    xetMetricQueryDestroy(
        xet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnDestroy = dditable->xet.MetricQuery.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnDestroy( hMetricQuery );

        // release loader handle
        xet_metric_query_factory.release( hMetricQuery );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryReset
    xe_result_t __xecall
    xetMetricQueryReset(
        xet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnReset = dditable->xet.MetricQuery.pfnReset;
        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnReset( hMetricQuery );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricQueryBegin
    xe_result_t __xecall
    xetCommandListAppendMetricQueryBegin(
        xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricQueryBegin = dditable->xet.CommandList.pfnAppendMetricQueryBegin;
        if( nullptr == pfnAppendMetricQueryBegin )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricQueryEnd
    xe_result_t __xecall
    xetCommandListAppendMetricQueryEnd(
        xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        xe_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricQueryEnd = dditable->xet.CommandList.pfnAppendMetricQueryEnd;
        if( nullptr == pfnAppendMetricQueryEnd )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // convert loader handle to driver handle
        hCompletionEvent = ( hCompletionEvent ) ? reinterpret_cast<xe_event_object_t*>( hCompletionEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricMemoryBarrier
    xe_result_t __xecall
    xetCommandListAppendMetricMemoryBarrier(
        xet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricMemoryBarrier = dditable->xet.CommandList.pfnAppendMetricMemoryBarrier;
        if( nullptr == pfnAppendMetricMemoryBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnAppendMetricMemoryBarrier( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryGetData
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnGetData = dditable->xet.MetricQuery.pfnGetData;
        if( nullptr == pfnGetData )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnGetData( hMetricQuery, pRawDataSize, pRawData );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetModuleGetDebugInfo
    xe_result_t __xecall
    xetModuleGetDebugInfo(
        xet_module_handle_t hModule,                    ///< [in] handle of the module
        xet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_module_object_t*>( hModule )->dditable;
        auto pfnGetDebugInfo = dditable->xet.Module.pfnGetDebugInfo;
        if( nullptr == pfnGetDebugInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<xet_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetModuleGetFunctionNames
    xe_result_t __xecall
    xetModuleGetFunctionNames(
        xet_module_handle_t hModule,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of names available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of names.
                                                        ///< if count is larger than the number of names available, then the driver
                                                        ///< will update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_module_object_t*>( hModule )->dditable;
        auto pfnGetFunctionNames = dditable->xet.Module.pfnGetFunctionNames;
        if( nullptr == pfnGetFunctionNames )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<xet_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetFunctionNames( hModule, pCount, pNames );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFunctionGetProfileInfo
    xe_result_t __xecall
    xetFunctionGetProfileInfo(
        xet_function_handle_t hFunction,                ///< [in] handle to function
        xet_profile_info_t* pInfo                       ///< [out] pointer to profile info
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_function_object_t*>( hFunction )->dditable;
        auto pfnGetProfileInfo = dditable->xet.Function.pfnGetProfileInfo;
        if( nullptr == pfnGetProfileInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xet_function_object_t*>( hFunction )->handle;

        // forward to device-driver
        result = pfnGetProfileInfo( hFunction, pInfo );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanCreate
    xe_result_t __xecall
    xetSysmanCreate(
        xet_device_handle_t hDevice,                    ///< [in] Handle of the device
        xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
        uint32_t flags,                                 ///< [in] Bitfield of ::xet_sysman_init_flags_t
        xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xet.Sysman.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, version, flags, phSysman );

        try
        {
            // convert driver handle to loader handle
            *phSysman = reinterpret_cast<xet_sysman_handle_t>(
                xet_sysman_factory.getInstance( *phSysman, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDestroy
    xe_result_t __xecall
    xetSysmanDestroy(
        xet_sysman_handle_t hSysman                     ///< [in][release] SMI handle to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDestroy = dditable->xet.Sysman.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDestroy( hSysman );

        // release loader handle
        xet_sysman_factory.release( hSysman );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetAccelAssetName
    xe_result_t __xecall
    xetSysmanGetAccelAssetName(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle
        xet_accel_asset_t type,                         ///< [in] The type of accelerator asset
        const char** ppName                             ///< [in] Pointer to the asset name
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetAccelAssetName = dditable->xet.Sysman.pfnGetAccelAssetName;
        if( nullptr == pfnGetAccelAssetName )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetAccelAssetName( hSysman, type, ppName );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetInfo
    xe_result_t __xecall
    xetSysmanGetInfo(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of a device
        xet_sysman_info_t* pInfo                        ///< [in] Returned information
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetInfo = dditable->xet.Sysman.pfnGetInfo;
        if( nullptr == pfnGetInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetInfo( hSysman, pInfo );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasSetup
    xe_result_t __xecall
    xetSysmanRasSetup(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        uint32_t enableLoc,                             ///< [in] Structural locations where RAS should be enabled (bitfield of
                                                        ///< ::xet_ras_error_loc_t)
        uint32_t disableLoc,                            ///< [in] Structural locations where RAS should be disabled (bitfield of
                                                        ///< ::xet_ras_error_loc_t)
        uint32_t* pEnabledLoc                           ///< [in] Structural locations where RAS is currently enabled after
                                                        ///< applying enableLoc and disableLoc (bitfield of ::xet_ras_error_loc_t)
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnRasSetup = dditable->xet.Sysman.pfnRasSetup;
        if( nullptr == pfnRasSetup )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRasSetup( hSysman, enableLoc, disableLoc, pEnabledLoc );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetRasErrors
    xe_result_t __xecall
    xetSysmanGetRasErrors(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_ras_filter_t* pFilter,                      ///< [in] Filter for RAS errors to return
        xe_bool_t clear,                                ///< [in] Set to true to clear the underlying counters after they are
                                                        ///< returned
        uint32_t* pCount,                               ///< [in] Pointer to the number of elements in the array pErrors.
                                                        ///< If count is 0 or pErrors is nullptr, driver will update with the
                                                        ///< number of errors matching the specified filters. Counters are not cleared.
                                                        ///< If count is non-zero and less than the number of matching errors,
                                                        ///< driver will update with the number of errors matching the specified
                                                        ///< filters. No data is returned and counters are not cleared.
                                                        ///< If count is greater than or equal to the number of matching errors,
                                                        ///< all data is returned, counters are cleared if requested and count will
                                                        ///< be set to actual number of errors returned.
        xet_ras_error_t* pErrors                        ///< [in] Array of error data
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetRasErrors = dditable->xet.Sysman.pfnGetRasErrors;
        if( nullptr == pfnGetRasErrors )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetRasErrors( hSysman, pFilter, clear, pCount, pErrors );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableDeviceProperties
    xe_result_t __xecall
    xetSysmanAvailableDeviceProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_device_prop_capability_t* pCap              ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableDeviceProperties = dditable->xet.Sysman.pfnAvailableDeviceProperties;
        if( nullptr == pfnAvailableDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableDeviceProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetDeviceProperties
    xe_result_t __xecall
    xetSysmanGetDeviceProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetDeviceProperties = dditable->xet.Sysman.pfnGetDeviceProperties;
        if( nullptr == pfnGetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetDeviceProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetDeviceProperties
    xe_result_t __xecall
    xetSysmanSetDeviceProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetDeviceProperties = dditable->xet.Sysman.pfnSetDeviceProperties;
        if( nullptr == pfnSetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetDeviceProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailablePsuProperties
    xe_result_t __xecall
    xetSysmanAvailablePsuProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_psu_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailablePsuProperties = dditable->xet.Sysman.pfnAvailablePsuProperties;
        if( nullptr == pfnAvailablePsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailablePsuProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetPsuProperties
    xe_result_t __xecall
    xetSysmanGetPsuProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetPsuProperties = dditable->xet.Sysman.pfnGetPsuProperties;
        if( nullptr == pfnGetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetPsuProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetPsuProperties
    xe_result_t __xecall
    xetSysmanSetPsuProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetPsuProperties = dditable->xet.Sysman.pfnSetPsuProperties;
        if( nullptr == pfnSetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetPsuProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableTempProperties
    xe_result_t __xecall
    xetSysmanAvailableTempProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_temp_prop_capability_t* pCap                ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableTempProperties = dditable->xet.Sysman.pfnAvailableTempProperties;
        if( nullptr == pfnAvailableTempProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableTempProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetTempProperties
    xe_result_t __xecall
    xetSysmanGetTempProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_temp_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetTempProperties = dditable->xet.Sysman.pfnGetTempProperties;
        if( nullptr == pfnGetTempProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetTempProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableFanProperties
    xe_result_t __xecall
    xetSysmanAvailableFanProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_fan_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableFanProperties = dditable->xet.Sysman.pfnAvailableFanProperties;
        if( nullptr == pfnAvailableFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableFanProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetFanProperties
    xe_result_t __xecall
    xetSysmanGetFanProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetFanProperties = dditable->xet.Sysman.pfnGetFanProperties;
        if( nullptr == pfnGetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetFanProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetFanProperties
    xe_result_t __xecall
    xetSysmanSetFanProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetFanProperties = dditable->xet.Sysman.pfnSetFanProperties;
        if( nullptr == pfnSetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetFanProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableLedProperties
    xe_result_t __xecall
    xetSysmanAvailableLedProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_led_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableLedProperties = dditable->xet.Sysman.pfnAvailableLedProperties;
        if( nullptr == pfnAvailableLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableLedProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetLedProperties
    xe_result_t __xecall
    xetSysmanGetLedProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetLedProperties = dditable->xet.Sysman.pfnGetLedProperties;
        if( nullptr == pfnGetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetLedProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetLedProperties
    xe_result_t __xecall
    xetSysmanSetLedProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetLedProperties = dditable->xet.Sysman.pfnSetLedProperties;
        if( nullptr == pfnSetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetLedProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableFirmwareProperties
    xe_result_t __xecall
    xetSysmanAvailableFirmwareProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_firmware_prop_capability_t* pCap            ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableFirmwareProperties = dditable->xet.Sysman.pfnAvailableFirmwareProperties;
        if( nullptr == pfnAvailableFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableFirmwareProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetFirmwareProperties
    xe_result_t __xecall
    xetSysmanGetFirmwareProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetFirmwareProperties = dditable->xet.Sysman.pfnGetFirmwareProperties;
        if( nullptr == pfnGetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetFirmwareProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetFirmwareProperties
    xe_result_t __xecall
    xetSysmanSetFirmwareProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetFirmwareProperties = dditable->xet.Sysman.pfnSetFirmwareProperties;
        if( nullptr == pfnSetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetFirmwareProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailablePwrProperties
    xe_result_t __xecall
    xetSysmanAvailablePwrProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_pwr_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailablePwrProperties = dditable->xet.Sysman.pfnAvailablePwrProperties;
        if( nullptr == pfnAvailablePwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailablePwrProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetPwrProperties
    xe_result_t __xecall
    xetSysmanGetPwrProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetPwrProperties = dditable->xet.Sysman.pfnGetPwrProperties;
        if( nullptr == pfnGetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetPwrProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetPwrProperties
    xe_result_t __xecall
    xetSysmanSetPwrProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetPwrProperties = dditable->xet.Sysman.pfnSetPwrProperties;
        if( nullptr == pfnSetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetPwrProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableFreqProperties
    xe_result_t __xecall
    xetSysmanAvailableFreqProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_freq_prop_capability_t* pCap                ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableFreqProperties = dditable->xet.Sysman.pfnAvailableFreqProperties;
        if( nullptr == pfnAvailableFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableFreqProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetFreqProperties
    xe_result_t __xecall
    xetSysmanGetFreqProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetFreqProperties = dditable->xet.Sysman.pfnGetFreqProperties;
        if( nullptr == pfnGetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetFreqProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetFreqProperties
    xe_result_t __xecall
    xetSysmanSetFreqProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetFreqProperties = dditable->xet.Sysman.pfnSetFreqProperties;
        if( nullptr == pfnSetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetFreqProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailablePwrwellProperties
    xe_result_t __xecall
    xetSysmanAvailablePwrwellProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_pwrwell_prop_capability_t* pCap             ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailablePwrwellProperties = dditable->xet.Sysman.pfnAvailablePwrwellProperties;
        if( nullptr == pfnAvailablePwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailablePwrwellProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetPwrwellProperties
    xe_result_t __xecall
    xetSysmanGetPwrwellProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetPwrwellProperties = dditable->xet.Sysman.pfnGetPwrwellProperties;
        if( nullptr == pfnGetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetPwrwellProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetPwrwellProperties
    xe_result_t __xecall
    xetSysmanSetPwrwellProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetPwrwellProperties = dditable->xet.Sysman.pfnSetPwrwellProperties;
        if( nullptr == pfnSetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetPwrwellProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableAccelProperties
    xe_result_t __xecall
    xetSysmanAvailableAccelProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_accel_prop_capability_t* pCap               ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableAccelProperties = dditable->xet.Sysman.pfnAvailableAccelProperties;
        if( nullptr == pfnAvailableAccelProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableAccelProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetAccelProperties
    xe_result_t __xecall
    xetSysmanGetAccelProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_accel_property_request_t* pRequest          ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetAccelProperties = dditable->xet.Sysman.pfnGetAccelProperties;
        if( nullptr == pfnGetAccelProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetAccelProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableMemProperties
    xe_result_t __xecall
    xetSysmanAvailableMemProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_mem_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableMemProperties = dditable->xet.Sysman.pfnAvailableMemProperties;
        if( nullptr == pfnAvailableMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableMemProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetMemProperties
    xe_result_t __xecall
    xetSysmanGetMemProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetMemProperties = dditable->xet.Sysman.pfnGetMemProperties;
        if( nullptr == pfnGetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetMemProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetMemProperties
    xe_result_t __xecall
    xetSysmanSetMemProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetMemProperties = dditable->xet.Sysman.pfnSetMemProperties;
        if( nullptr == pfnSetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetMemProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanAvailableLinkProperties
    xe_result_t __xecall
    xetSysmanAvailableLinkProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        xet_link_prop_capability_t* pCap                ///< [in] Pointer to an array of avilable property requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnAvailableLinkProperties = dditable->xet.Sysman.pfnAvailableLinkProperties;
        if( nullptr == pfnAvailableLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnAvailableLinkProperties( hSysman, count, pCap );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetLinkProperties
    xe_result_t __xecall
    xetSysmanGetLinkProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetLinkProperties = dditable->xet.Sysman.pfnGetLinkProperties;
        if( nullptr == pfnGetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetLinkProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSetLinkProperties
    xe_result_t __xecall
    xetSysmanSetLinkProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSetLinkProperties = dditable->xet.Sysman.pfnSetLinkProperties;
        if( nullptr == pfnSetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSetLinkProperties( hSysman, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSupportedEvents
    xe_result_t __xecall
    xetSysmanSupportedEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t count,                                 ///< [in] The number of entries in the array pAccess
        xet_event_support_t* pAccess                    ///< [in] Pointer to an array of event support requests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSupportedEvents = dditable->xet.Sysman.pfnSupportedEvents;
        if( nullptr == pfnSupportedEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSupportedEvents( hSysman, count, pAccess );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRegisterEvents
    xe_result_t __xecall
    xetSysmanRegisterEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be registered.
        xet_event_request_t* pEvents                    ///< [in] Events to register.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnRegisterEvents = dditable->xet.Sysman.pfnRegisterEvents;
        if( nullptr == pfnRegisterEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRegisterEvents( hSysman, count, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanUnregisterEvents
    xe_result_t __xecall
    xetSysmanUnregisterEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be unregistered.
        xet_event_request_t* pEvents                    ///< [in] Events to unregister.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnUnregisterEvents = dditable->xet.Sysman.pfnUnregisterEvents;
        if( nullptr == pfnUnregisterEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnUnregisterEvents( hSysman, count, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetDiagnosticTests
    xe_result_t __xecall
    xetSysmanGetDiagnosticTests(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
        const xet_diag_test_list_t** ppTests            ///< [in] Returns a constant pointer to the list of diagnostic tests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetDiagnosticTests = dditable->xet.Sysman.pfnGetDiagnosticTests;
        if( nullptr == pfnGetDiagnosticTests )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetDiagnosticTests( hSysman, type, ppTests );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRunDiagnosticTests
    xe_result_t __xecall
    xetSysmanRunDiagnosticTests(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        xet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnRunDiagnosticTests = dditable->xet.Sysman.pfnRunDiagnosticTests;
        if( nullptr == pfnRunDiagnosticTests )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRunDiagnosticTests( hSysman, type, start, end, pResult );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetEvents
    xe_result_t __xecall
    xetSysmanGetEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                        ///< device for which the application has registered to receive
                                                        ///< notifications.
        xe_bool_t clear,                                ///< [in] Clear the event status.
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                        ///< check status and return immediately. Set to ::XET_EVENT_WAIT_INFINITE
                                                        ///< to block until events arrive.
        uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                        ///< triggered.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetEvents = dditable->xet.Sysman.pfnGetEvents;
        if( nullptr == pfnGetEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetEvents( hSysman, clear, timeout, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerCreate
    xe_result_t __xecall
    xetTracerCreate(
        xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
        const xet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
        xet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnCreate = dditable->xet.Tracer.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xet_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnCreate( hDeviceGroup, desc, phTracer );

        try
        {
            // convert driver handle to loader handle
            *phTracer = reinterpret_cast<xet_tracer_handle_t>(
                xet_tracer_factory.getInstance( *phTracer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerDestroy
    xe_result_t __xecall
    xetTracerDestroy(
        xet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_tracer_object_t*>( hTracer )->dditable;
        auto pfnDestroy = dditable->xet.Tracer.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<xet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnDestroy( hTracer );

        // release loader handle
        xet_tracer_factory.release( hTracer );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerSetPrologues
    xe_result_t __xecall
    xetTracerSetPrologues(
        xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        xet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
        xet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_tracer_object_t*>( hTracer )->dditable;
        auto pfnSetPrologues = dditable->xet.Tracer.pfnSetPrologues;
        if( nullptr == pfnSetPrologues )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<xet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetPrologues( hTracer, pCoreCbs, pExperimentalCbs );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerSetEpilogues
    xe_result_t __xecall
    xetTracerSetEpilogues(
        xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        xet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
        xet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_tracer_object_t*>( hTracer )->dditable;
        auto pfnSetEpilogues = dditable->xet.Tracer.pfnSetEpilogues;
        if( nullptr == pfnSetEpilogues )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<xet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetEpilogues( hTracer, pCoreCbs, pExperimentalCbs );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerSetEnabled
    xe_result_t __xecall
    xetTracerSetEnabled(
        xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        xe_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_tracer_object_t*>( hTracer )->dditable;
        auto pfnSetEnabled = dditable->xet.Tracer.pfnSetEnabled;
        if( nullptr == pfnSetEnabled )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<xet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetEnabled( hTracer, enable );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetGlobalProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Global );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnInit                                     = loader::xetInit;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetGlobalProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetDeviceProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Device );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnActivateMetricGroups                     = loader::xetDeviceActivateMetricGroups;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetDeviceProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetCommandListProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.CommandList );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnAppendMetricTracerMarker                 = loader::xetCommandListAppendMetricTracerMarker;
            pDdiTable->pfnAppendMetricQueryBegin                   = loader::xetCommandListAppendMetricQueryBegin;
            pDdiTable->pfnAppendMetricQueryEnd                     = loader::xetCommandListAppendMetricQueryEnd;
            pDdiTable->pfnAppendMetricMemoryBarrier                = loader::xetCommandListAppendMetricMemoryBarrier;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetCommandListProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetModuleProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetModuleProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Module );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetDebugInfo                             = loader::xetModuleGetDebugInfo;
            pDdiTable->pfnGetFunctionNames                         = loader::xetModuleGetFunctionNames;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Module;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetModuleProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetFunctionProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_function_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetFunctionProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetFunctionProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Function );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProfileInfo                           = loader::xetFunctionGetProfileInfo;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Function;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetFunctionProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetFunctionProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricGroupProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricGroup );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xetMetricGroupGet;
            pDdiTable->pfnGetProperties                            = loader::xetMetricGroupGetProperties;
            pDdiTable->pfnCalculateMetricValues                    = loader::xetMetricGroupCalculateMetricValues;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricGroup;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricGroupProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Metric );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xetMetricGet;
            pDdiTable->pfnGetProperties                            = loader::xetMetricGetProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Metric;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricTracerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricTracerProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricTracer );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnOpen                                     = loader::xetMetricTracerOpen;
            pDdiTable->pfnClose                                    = loader::xetMetricTracerClose;
            pDdiTable->pfnReadData                                 = loader::xetMetricTracerReadData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricTracer;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricTracerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricQueryPoolProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricQueryPool );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xetMetricQueryPoolCreate;
            pDdiTable->pfnDestroy                                  = loader::xetMetricQueryPoolDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricQueryPool;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricQueryPoolProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricQueryProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricQuery );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xetMetricQueryCreate;
            pDdiTable->pfnDestroy                                  = loader::xetMetricQueryDestroy;
            pDdiTable->pfnReset                                    = loader::xetMetricQueryReset;
            pDdiTable->pfnGetData                                  = loader::xetMetricQueryGetData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricQuery;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricQueryProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetTracerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetTracerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetTracerProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Tracer );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xetTracerCreate;
            pDdiTable->pfnDestroy                                  = loader::xetTracerDestroy;
            pDdiTable->pfnSetPrologues                             = loader::xetTracerSetPrologues;
            pDdiTable->pfnSetEpilogues                             = loader::xetTracerSetEpilogues;
            pDdiTable->pfnSetEnabled                               = loader::xetTracerSetEnabled;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Tracer;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetTracerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetTracerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetSysmanProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Sysman );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xetSysmanCreate;
            pDdiTable->pfnDestroy                                  = loader::xetSysmanDestroy;
            pDdiTable->pfnGetAccelAssetName                        = loader::xetSysmanGetAccelAssetName;
            pDdiTable->pfnGetInfo                                  = loader::xetSysmanGetInfo;
            pDdiTable->pfnRasSetup                                 = loader::xetSysmanRasSetup;
            pDdiTable->pfnGetRasErrors                             = loader::xetSysmanGetRasErrors;
            pDdiTable->pfnAvailableDeviceProperties                = loader::xetSysmanAvailableDeviceProperties;
            pDdiTable->pfnGetDeviceProperties                      = loader::xetSysmanGetDeviceProperties;
            pDdiTable->pfnSetDeviceProperties                      = loader::xetSysmanSetDeviceProperties;
            pDdiTable->pfnAvailablePsuProperties                   = loader::xetSysmanAvailablePsuProperties;
            pDdiTable->pfnGetPsuProperties                         = loader::xetSysmanGetPsuProperties;
            pDdiTable->pfnSetPsuProperties                         = loader::xetSysmanSetPsuProperties;
            pDdiTable->pfnAvailableTempProperties                  = loader::xetSysmanAvailableTempProperties;
            pDdiTable->pfnGetTempProperties                        = loader::xetSysmanGetTempProperties;
            pDdiTable->pfnAvailableFanProperties                   = loader::xetSysmanAvailableFanProperties;
            pDdiTable->pfnGetFanProperties                         = loader::xetSysmanGetFanProperties;
            pDdiTable->pfnSetFanProperties                         = loader::xetSysmanSetFanProperties;
            pDdiTable->pfnAvailableLedProperties                   = loader::xetSysmanAvailableLedProperties;
            pDdiTable->pfnGetLedProperties                         = loader::xetSysmanGetLedProperties;
            pDdiTable->pfnSetLedProperties                         = loader::xetSysmanSetLedProperties;
            pDdiTable->pfnAvailableFirmwareProperties              = loader::xetSysmanAvailableFirmwareProperties;
            pDdiTable->pfnGetFirmwareProperties                    = loader::xetSysmanGetFirmwareProperties;
            pDdiTable->pfnSetFirmwareProperties                    = loader::xetSysmanSetFirmwareProperties;
            pDdiTable->pfnAvailablePwrProperties                   = loader::xetSysmanAvailablePwrProperties;
            pDdiTable->pfnGetPwrProperties                         = loader::xetSysmanGetPwrProperties;
            pDdiTable->pfnSetPwrProperties                         = loader::xetSysmanSetPwrProperties;
            pDdiTable->pfnAvailableFreqProperties                  = loader::xetSysmanAvailableFreqProperties;
            pDdiTable->pfnGetFreqProperties                        = loader::xetSysmanGetFreqProperties;
            pDdiTable->pfnSetFreqProperties                        = loader::xetSysmanSetFreqProperties;
            pDdiTable->pfnAvailablePwrwellProperties               = loader::xetSysmanAvailablePwrwellProperties;
            pDdiTable->pfnGetPwrwellProperties                     = loader::xetSysmanGetPwrwellProperties;
            pDdiTable->pfnSetPwrwellProperties                     = loader::xetSysmanSetPwrwellProperties;
            pDdiTable->pfnAvailableAccelProperties                 = loader::xetSysmanAvailableAccelProperties;
            pDdiTable->pfnGetAccelProperties                       = loader::xetSysmanGetAccelProperties;
            pDdiTable->pfnAvailableMemProperties                   = loader::xetSysmanAvailableMemProperties;
            pDdiTable->pfnGetMemProperties                         = loader::xetSysmanGetMemProperties;
            pDdiTable->pfnSetMemProperties                         = loader::xetSysmanSetMemProperties;
            pDdiTable->pfnAvailableLinkProperties                  = loader::xetSysmanAvailableLinkProperties;
            pDdiTable->pfnGetLinkProperties                        = loader::xetSysmanGetLinkProperties;
            pDdiTable->pfnSetLinkProperties                        = loader::xetSysmanSetLinkProperties;
            pDdiTable->pfnSupportedEvents                          = loader::xetSysmanSupportedEvents;
            pDdiTable->pfnRegisterEvents                           = loader::xetSysmanRegisterEvents;
            pDdiTable->pfnUnregisterEvents                         = loader::xetSysmanUnregisterEvents;
            pDdiTable->pfnGetDiagnosticTests                       = loader::xetSysmanGetDiagnosticTests;
            pDdiTable->pfnRunDiagnosticTests                       = loader::xetSysmanRunDiagnosticTests;
            pDdiTable->pfnGetEvents                                = loader::xetSysmanGetEvents;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Sysman;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
