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
    xet_driver_factory_t                xet_driver_factory;
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnGet = dditable->xet.MetricGroup.pfnGet;
        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGet( hDevice, pCount, phMetricGroups );

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
    /// @brief Intercept function for xetSysmanGet
    xe_result_t __xecall
    xetSysmanGet(
        xet_device_handle_t hDevice,                    ///< [in] Handle of the device
        xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
        xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnGet = dditable->xet.Sysman.pfnGet;
        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGet( hDevice, version, phSysman );

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
    /// @brief Intercept function for xetSysmanDeviceGetProperties
    xe_result_t __xecall
    xetSysmanDeviceGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceGetProperties = dditable->xet.Sysman.pfnDeviceGetProperties;
        if( nullptr == pfnDeviceGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceGetProperties( hSysman, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceGetOperatingMode
    xe_result_t __xecall
    xetSysmanDeviceGetOperatingMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_operating_mode_t* pMode                     ///< [in] The current operating mode of the device.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceGetOperatingMode = dditable->xet.Sysman.pfnDeviceGetOperatingMode;
        if( nullptr == pfnDeviceGetOperatingMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceGetOperatingMode( hSysman, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceSetOperatingMode
    xe_result_t __xecall
    xetSysmanDeviceSetOperatingMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_operating_mode_t pMode                      ///< [in] The new operating mode of the device.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceSetOperatingMode = dditable->xet.Sysman.pfnDeviceSetOperatingMode;
        if( nullptr == pfnDeviceSetOperatingMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceSetOperatingMode( hSysman, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceReset
    xe_result_t __xecall
    xetSysmanDeviceReset(
        xet_sysman_handle_t hSysman                     ///< [in] SMI handle for the device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceReset = dditable->xet.Sysman.pfnDeviceReset;
        if( nullptr == pfnDeviceReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceReset( hSysman );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetProperties
    xe_result_t __xecall
    xetSysmanPowerGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerGetProperties = dditable->xet.Sysman.pfnPowerGetProperties;
        if( nullptr == pfnPowerGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerGetProperties( hSysman, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetEnergyCounter
    xe_result_t __xecall
    xetSysmanPowerGetEnergyCounter(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerGetEnergyCounter = dditable->xet.Sysman.pfnPowerGetEnergyCounter;
        if( nullptr == pfnPowerGetEnergyCounter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerGetEnergyCounter( hSysman, pEnergy );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerGetEnergyThreshold(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_power_energy_threshold_t* pThreshold        ///< [out] The current energy threshold value in joules.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerGetEnergyThreshold = dditable->xet.Sysman.pfnPowerGetEnergyThreshold;
        if( nullptr == pfnPowerGetEnergyThreshold )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerGetEnergyThreshold( hSysman, pThreshold );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerSetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerSetEnergyThreshold(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_power_energy_threshold_t* pThreshold        ///< [in] The energy threshold to be set in joules.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerSetEnergyThreshold = dditable->xet.Sysman.pfnPowerSetEnergyThreshold;
        if( nullptr == pfnPowerSetEnergyThreshold )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerSetEnergyThreshold( hSysman, pThreshold );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetLimits
    xe_result_t __xecall
    xetSysmanPowerGetLimits(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
        xet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
        xet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerGetLimits = dditable->xet.Sysman.pfnPowerGetLimits;
        if( nullptr == pfnPowerGetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerGetLimits( hSysman, pSustained, pBurst, pPeak );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerSetLimits
    xe_result_t __xecall
    xetSysmanPowerSetLimits(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        const xet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const xet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const xet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerSetLimits = dditable->xet.Sysman.pfnPowerSetLimits;
        if( nullptr == pfnPowerSetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerSetLimits( hSysman, pSustained, pBurst, pPeak );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetProperties
    xe_result_t __xecall
    xetSysmanFrequencyGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_freq_domain_t domain,                       ///< [in] The frequency domain.
        xet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencyGetProperties = dditable->xet.Sysman.pfnFrequencyGetProperties;
        if( nullptr == pfnFrequencyGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencyGetProperties( hSysman, domain, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetLimits
    xe_result_t __xecall
    xetSysmanFrequencyGetLimits(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_freq_domain_t domain,                       ///< [in] The frequency domain.
        xet_freq_limits_t* pLimits                      ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencyGetLimits = dditable->xet.Sysman.pfnFrequencyGetLimits;
        if( nullptr == pfnFrequencyGetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencyGetLimits( hSysman, domain, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetLimits
    xe_result_t __xecall
    xetSysmanFrequencySetLimits(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_freq_domain_t domain,                       ///< [in] The frequency domain.
        const xet_freq_limits_t* pLimits                ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencySetLimits = dditable->xet.Sysman.pfnFrequencySetLimits;
        if( nullptr == pfnFrequencySetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencySetLimits( hSysman, domain, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetState
    xe_result_t __xecall
    xetSysmanFrequencyGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_freq_domain_t domain,                       ///< [in] The frequency domain.
        xet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencyGetState = dditable->xet.Sysman.pfnFrequencyGetState;
        if( nullptr == pfnFrequencyGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencyGetState( hSysman, domain, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetThrottleTime
    xe_result_t __xecall
    xetSysmanFrequencyGetThrottleTime(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_freq_domain_t domain,                       ///< [in] The frequency domain.
        xet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencyGetThrottleTime = dditable->xet.Sysman.pfnFrequencyGetThrottleTime;
        if( nullptr == pfnFrequencyGetThrottleTime )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencyGetThrottleTime( hSysman, domain, pThrottleTime );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanActivityGetStats
    xe_result_t __xecall
    xetSysmanActivityGetStats(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_activity_type_t type,                       ///< [in] The type of activity stats.
        xet_activity_stats_t* pStats                    ///< [in] Will contain a snapshot of the activity counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnActivityGetStats = dditable->xet.Sysman.pfnActivityGetStats;
        if( nullptr == pfnActivityGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnActivityGetStats( hSysman, type, pStats );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetProperties
    xe_result_t __xecall
    xetSysmanMemoryGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnMemoryGetProperties = dditable->xet.Sysman.pfnMemoryGetProperties;
        if( nullptr == pfnMemoryGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnMemoryGetProperties( hSysman, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetBandwidth
    xe_result_t __xecall
    xetSysmanMemoryGetBandwidth(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnMemoryGetBandwidth = dditable->xet.Sysman.pfnMemoryGetBandwidth;
        if( nullptr == pfnMemoryGetBandwidth )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnMemoryGetBandwidth( hSysman, pBandwidth );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetAllocated
    xe_result_t __xecall
    xetSysmanMemoryGetAllocated(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnMemoryGetAllocated = dditable->xet.Sysman.pfnMemoryGetAllocated;
        if( nullptr == pfnMemoryGetAllocated )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnMemoryGetAllocated( hSysman, pAllocated );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetProperties
    xe_result_t __xecall
    xetSysmanPciGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetProperties = dditable->xet.Sysman.pfnPciGetProperties;
        if( nullptr == pfnPciGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetProperties( hSysman, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetState
    xe_result_t __xecall
    xetSysmanPciGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetState = dditable->xet.Sysman.pfnPciGetState;
        if( nullptr == pfnPciGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetState( hSysman, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetBarProperties
    xe_result_t __xecall
    xetSysmanPciGetBarProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::xet_pci_properties_t.numBars -
                                                        ///< 1]).
        xet_pci_bar_properties_t* pProperties           ///< [in] Will contain properties of the specified bar
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetBarProperties = dditable->xet.Sysman.pfnPciGetBarProperties;
        if( nullptr == pfnPciGetBarProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetBarProperties( hSysman, barIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetThroughput
    xe_result_t __xecall
    xetSysmanPciGetThroughput(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_throughput_t* pThroughput               ///< [in] Will contain a snapshot of the latest throughput counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetThroughput = dditable->xet.Sysman.pfnPciGetThroughput;
        if( nullptr == pfnPciGetThroughput )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetThroughput( hSysman, pThroughput );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetStats
    xe_result_t __xecall
    xetSysmanPciGetStats(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetStats = dditable->xet.Sysman.pfnPciGetStats;
        if( nullptr == pfnPciGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetStats( hSysman, pStats );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchGetProperties
    xe_result_t __xecall
    xetSysmanSwitchGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                        ///< [::xet_sysman_properties_t.numSwitches - 1]).
        xet_switch_properties_t* pProperties            ///< [in] Will contain the Switch properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSwitchGetProperties = dditable->xet.Sysman.pfnSwitchGetProperties;
        if( nullptr == pfnSwitchGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSwitchGetProperties( hSysman, switchIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchGetState
    xe_result_t __xecall
    xetSysmanSwitchGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                        ///< [::xet_sysman_properties_t.numSwitches - 1]).
        xet_switch_state_t* pState                      ///< [in] Will contain the current state of the switch (enabled/disabled).
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSwitchGetState = dditable->xet.Sysman.pfnSwitchGetState;
        if( nullptr == pfnSwitchGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSwitchGetState( hSysman, switchIndex, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchSetState
    xe_result_t __xecall
    xetSysmanSwitchSetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                        ///< [::xet_sysman_properties_t.numSwitches - 1]).
        xe_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSwitchSetState = dditable->xet.Sysman.pfnSwitchSetState;
        if( nullptr == pfnSwitchSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSwitchSetState( hSysman, switchIndex, enable );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetProperties
    xe_result_t __xecall
    xetSysmanSwitchPortGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                        ///< [::xet_sysman_properties_t.numSwitches - 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_properties_t* pProperties       ///< [in] Will contain properties of the Switch Port
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSwitchPortGetProperties = dditable->xet.Sysman.pfnSwitchPortGetProperties;
        if( nullptr == pfnSwitchPortGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSwitchPortGetProperties( hSysman, switchIndex, portIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetState
    xe_result_t __xecall
    xetSysmanSwitchPortGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                        ///< [::xet_sysman_properties_t.numSwitches - 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_state_t* pState                 ///< [in] Will contain the current state of the Switch Port
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSwitchPortGetState = dditable->xet.Sysman.pfnSwitchPortGetState;
        if( nullptr == pfnSwitchPortGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSwitchPortGetState( hSysman, switchIndex, portIndex, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetThroughput
    xe_result_t __xecall
    xetSysmanSwitchPortGetThroughput(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                        ///< [::xet_sysman_properties_t.numSwitches - 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_throughput_t* pThroughput       ///< [in] Will contain the Switch port throughput counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSwitchPortGetThroughput = dditable->xet.Sysman.pfnSwitchPortGetThroughput;
        if( nullptr == pfnSwitchPortGetThroughput )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSwitchPortGetThroughput( hSysman, switchIndex, portIndex, pThroughput );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetStats
    xe_result_t __xecall
    xetSysmanSwitchPortGetStats(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                        ///< [::xet_sysman_properties_t.numSwitches - 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_stats_t* pStats                 ///< [in] Will contain the Switch port stats.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSwitchPortGetStats = dditable->xet.Sysman.pfnSwitchPortGetStats;
        if( nullptr == pfnSwitchPortGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSwitchPortGetStats( hSysman, switchIndex, portIndex, pStats );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureGet
    xe_result_t __xecall
    xetSysmanTemperatureGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_temp_sensors_t sensor,                      ///< [in] The port address.
        uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnTemperatureGet = dditable->xet.Sysman.pfnTemperatureGet;
        if( nullptr == pfnTemperatureGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnTemperatureGet( hSysman, sensor, pTemperature );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetMode
    xe_result_t __xecall
    xetSysmanStandbyGetMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_stby_promo_mode_t* pMode                    ///< [in] Will contain the current standby mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnStandbyGetMode = dditable->xet.Sysman.pfnStandbyGetMode;
        if( nullptr == pfnStandbyGetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnStandbyGetMode( hSysman, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbySetMode
    xe_result_t __xecall
    xetSysmanStandbySetMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_stby_promo_mode_t mode                      ///< [in] New standby mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnStandbySetMode = dditable->xet.Sysman.pfnStandbySetMode;
        if( nullptr == pfnStandbySetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnStandbySetMode( hSysman, mode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetProperties
    xe_result_t __xecall
    xetSysmanFirmwareGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                        ///< [::xet_sysman_properties_t.numFirmwares - 1]).
        xet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFirmwareGetProperties = dditable->xet.Sysman.pfnFirmwareGetProperties;
        if( nullptr == pfnFirmwareGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFirmwareGetProperties( hSysman, firmwareIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetChecksum
    xe_result_t __xecall
    xetSysmanFirmwareGetChecksum(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                        ///< [::xet_sysman_properties_t.numFirmwares - 1]).
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFirmwareGetChecksum = dditable->xet.Sysman.pfnFirmwareGetChecksum;
        if( nullptr == pfnFirmwareGetChecksum )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFirmwareGetChecksum( hSysman, firmwareIndex, pChecksum );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareFlash
    xe_result_t __xecall
    xetSysmanFirmwareFlash(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                        ///< [::xet_sysman_properties_t.numFirmwares - 1]).
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFirmwareFlash = dditable->xet.Sysman.pfnFirmwareFlash;
        if( nullptr == pfnFirmwareFlash )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFirmwareFlash( hSysman, firmwareIndex, pImage, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetProperties
    xe_result_t __xecall
    xetSysmanPsuGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ...
                                                        ///< [::xet_sysman_properties_t.numPsus - 1]).
        xet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPsuGetProperties = dditable->xet.Sysman.pfnPsuGetProperties;
        if( nullptr == pfnPsuGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPsuGetProperties( hSysman, psuIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetState
    xe_result_t __xecall
    xetSysmanPsuGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ...
                                                        ///< [::xet_sysman_properties_t.numPsus - 1]).
        xet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPsuGetState = dditable->xet.Sysman.pfnPsuGetState;
        if( nullptr == pfnPsuGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPsuGetState( hSysman, psuIndex, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetProperties
    xe_result_t __xecall
    xetSysmanFanGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        xet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFanGetProperties = dditable->xet.Sysman.pfnFanGetProperties;
        if( nullptr == pfnFanGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFanGetProperties( hSysman, fanIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetConfig
    xe_result_t __xecall
    xetSysmanFanGetConfig(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        xet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFanGetConfig = dditable->xet.Sysman.pfnFanGetConfig;
        if( nullptr == pfnFanGetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFanGetConfig( hSysman, fanIndex, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanSetConfig
    xe_result_t __xecall
    xetSysmanFanSetConfig(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        const xet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFanSetConfig = dditable->xet.Sysman.pfnFanSetConfig;
        if( nullptr == pfnFanSetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFanSetConfig( hSysman, fanIndex, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetState
    xe_result_t __xecall
    xetSysmanFanGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        xet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        xet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFanGetState = dditable->xet.Sysman.pfnFanGetState;
        if( nullptr == pfnFanGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFanGetState( hSysman, fanIndex, units, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetProperties
    xe_result_t __xecall
    xetSysmanLedGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                        ///< 1]).
        xet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnLedGetProperties = dditable->xet.Sysman.pfnLedGetProperties;
        if( nullptr == pfnLedGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnLedGetProperties( hSysman, ledIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetState
    xe_result_t __xecall
    xetSysmanLedGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                        ///< 1]).
        xet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnLedGetState = dditable->xet.Sysman.pfnLedGetState;
        if( nullptr == pfnLedGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnLedGetState( hSysman, ledIndex, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedSetState
    xe_result_t __xecall
    xetSysmanLedSetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                        ///< 1]).
        const xet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnLedSetState = dditable->xet.Sysman.pfnLedSetState;
        if( nullptr == pfnLedSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnLedSetState( hSysman, ledIndex, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetProperties
    xe_result_t __xecall
    xetSysmanRasGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnRasGetProperties = dditable->xet.Sysman.pfnRasGetProperties;
        if( nullptr == pfnRasGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRasGetProperties( hSysman, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetErrors
    xe_result_t __xecall
    xetSysmanRasGetErrors(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_ras_error_type_t type,                      ///< [in] The type of errors
        xe_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors of the given type that have
                                                        ///< occurred
        xet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnRasGetErrors = dditable->xet.Sysman.pfnRasGetErrors;
        if( nullptr == pfnRasGetErrors )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRasGetErrors( hSysman, type, clear, pTotalErrors, pDetails );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEventsRegister
    xe_result_t __xecall
    xetSysmanEventsRegister(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be registered.
        xet_event_request_t* pEvents                    ///< [in][optional] Events to register.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnEventsRegister = dditable->xet.Sysman.pfnEventsRegister;
        if( nullptr == pfnEventsRegister )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEventsRegister( hSysman, count, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEventsUnregister
    xe_result_t __xecall
    xetSysmanEventsUnregister(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be unregistered.
        xet_event_request_t* pEvents                    ///< [in][optional] Events to unregister.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnEventsUnregister = dditable->xet.Sysman.pfnEventsUnregister;
        if( nullptr == pfnEventsUnregister )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEventsUnregister( hSysman, count, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEventsListen
    xe_result_t __xecall
    xetSysmanEventsListen(
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
        auto pfnEventsListen = dditable->xet.Sysman.pfnEventsListen;
        if( nullptr == pfnEventsListen )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEventsListen( hSysman, clear, timeout, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsGetTestList
    xe_result_t __xecall
    xetSysmanDiagnosticsGetTestList(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
        const xet_diag_test_list_t** ppTests            ///< [in] Returns a constant pointer to the list of diagnostic tests
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDiagnosticsGetTestList = dditable->xet.Sysman.pfnDiagnosticsGetTestList;
        if( nullptr == pfnDiagnosticsGetTestList )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDiagnosticsGetTestList( hSysman, type, ppTests );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsRunTests
    xe_result_t __xecall
    xetSysmanDiagnosticsRunTests(
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
        auto pfnDiagnosticsRunTests = dditable->xet.Sysman.pfnDiagnosticsRunTests;
        if( nullptr == pfnDiagnosticsRunTests )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDiagnosticsRunTests( hSysman, type, start, end, pResult );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerCreate
    xe_result_t __xecall
    xetTracerCreate(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device
        const xet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
        xet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xet.Tracer.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phTracer );

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
            pDdiTable->pfnGet                                      = loader::xetSysmanGet;
            pDdiTable->pfnDeviceGetProperties                      = loader::xetSysmanDeviceGetProperties;
            pDdiTable->pfnDeviceGetOperatingMode                   = loader::xetSysmanDeviceGetOperatingMode;
            pDdiTable->pfnDeviceSetOperatingMode                   = loader::xetSysmanDeviceSetOperatingMode;
            pDdiTable->pfnDeviceReset                              = loader::xetSysmanDeviceReset;
            pDdiTable->pfnPowerGetProperties                       = loader::xetSysmanPowerGetProperties;
            pDdiTable->pfnPowerGetEnergyCounter                    = loader::xetSysmanPowerGetEnergyCounter;
            pDdiTable->pfnPowerGetEnergyThreshold                  = loader::xetSysmanPowerGetEnergyThreshold;
            pDdiTable->pfnPowerSetEnergyThreshold                  = loader::xetSysmanPowerSetEnergyThreshold;
            pDdiTable->pfnPowerGetLimits                           = loader::xetSysmanPowerGetLimits;
            pDdiTable->pfnPowerSetLimits                           = loader::xetSysmanPowerSetLimits;
            pDdiTable->pfnFrequencyGetProperties                   = loader::xetSysmanFrequencyGetProperties;
            pDdiTable->pfnFrequencyGetLimits                       = loader::xetSysmanFrequencyGetLimits;
            pDdiTable->pfnFrequencySetLimits                       = loader::xetSysmanFrequencySetLimits;
            pDdiTable->pfnFrequencyGetState                        = loader::xetSysmanFrequencyGetState;
            pDdiTable->pfnFrequencyGetThrottleTime                 = loader::xetSysmanFrequencyGetThrottleTime;
            pDdiTable->pfnActivityGetStats                         = loader::xetSysmanActivityGetStats;
            pDdiTable->pfnMemoryGetProperties                      = loader::xetSysmanMemoryGetProperties;
            pDdiTable->pfnMemoryGetBandwidth                       = loader::xetSysmanMemoryGetBandwidth;
            pDdiTable->pfnMemoryGetAllocated                       = loader::xetSysmanMemoryGetAllocated;
            pDdiTable->pfnPciGetProperties                         = loader::xetSysmanPciGetProperties;
            pDdiTable->pfnPciGetState                              = loader::xetSysmanPciGetState;
            pDdiTable->pfnPciGetBarProperties                      = loader::xetSysmanPciGetBarProperties;
            pDdiTable->pfnPciGetThroughput                         = loader::xetSysmanPciGetThroughput;
            pDdiTable->pfnPciGetStats                              = loader::xetSysmanPciGetStats;
            pDdiTable->pfnSwitchGetProperties                      = loader::xetSysmanSwitchGetProperties;
            pDdiTable->pfnSwitchGetState                           = loader::xetSysmanSwitchGetState;
            pDdiTable->pfnSwitchSetState                           = loader::xetSysmanSwitchSetState;
            pDdiTable->pfnSwitchPortGetProperties                  = loader::xetSysmanSwitchPortGetProperties;
            pDdiTable->pfnSwitchPortGetState                       = loader::xetSysmanSwitchPortGetState;
            pDdiTable->pfnSwitchPortGetThroughput                  = loader::xetSysmanSwitchPortGetThroughput;
            pDdiTable->pfnSwitchPortGetStats                       = loader::xetSysmanSwitchPortGetStats;
            pDdiTable->pfnTemperatureGet                           = loader::xetSysmanTemperatureGet;
            pDdiTable->pfnStandbyGetMode                           = loader::xetSysmanStandbyGetMode;
            pDdiTable->pfnStandbySetMode                           = loader::xetSysmanStandbySetMode;
            pDdiTable->pfnFirmwareGetProperties                    = loader::xetSysmanFirmwareGetProperties;
            pDdiTable->pfnFirmwareGetChecksum                      = loader::xetSysmanFirmwareGetChecksum;
            pDdiTable->pfnFirmwareFlash                            = loader::xetSysmanFirmwareFlash;
            pDdiTable->pfnPsuGetProperties                         = loader::xetSysmanPsuGetProperties;
            pDdiTable->pfnPsuGetState                              = loader::xetSysmanPsuGetState;
            pDdiTable->pfnFanGetProperties                         = loader::xetSysmanFanGetProperties;
            pDdiTable->pfnFanGetConfig                             = loader::xetSysmanFanGetConfig;
            pDdiTable->pfnFanSetConfig                             = loader::xetSysmanFanSetConfig;
            pDdiTable->pfnFanGetState                              = loader::xetSysmanFanGetState;
            pDdiTable->pfnLedGetProperties                         = loader::xetSysmanLedGetProperties;
            pDdiTable->pfnLedGetState                              = loader::xetSysmanLedGetState;
            pDdiTable->pfnLedSetState                              = loader::xetSysmanLedSetState;
            pDdiTable->pfnRasGetProperties                         = loader::xetSysmanRasGetProperties;
            pDdiTable->pfnRasGetErrors                             = loader::xetSysmanRasGetErrors;
            pDdiTable->pfnEventsRegister                           = loader::xetSysmanEventsRegister;
            pDdiTable->pfnEventsUnregister                         = loader::xetSysmanEventsUnregister;
            pDdiTable->pfnEventsListen                             = loader::xetSysmanEventsListen;
            pDdiTable->pfnDiagnosticsGetTestList                   = loader::xetSysmanDiagnosticsGetTestList;
            pDdiTable->pfnDiagnosticsRunTests                      = loader::xetSysmanDiagnosticsRunTests;
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
