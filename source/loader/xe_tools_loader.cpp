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
    xet_resource_factory_t              xet_resource_factory;

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
        xet_device_group_handle_t hDeviceGroup,         ///< [in] Handle of the device group
        xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
        uint32_t flags,                                 ///< [in] Bitfield of ::xet_sysman_init_flags_t
        xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnCreate = dditable->xet.Sysman.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xet_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnCreate( hDeviceGroup, version, flags, phSysman );

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
    /// @brief Intercept function for xetSysmanConvertUuidToString
    xe_result_t __xecall
    xetSysmanConvertUuidToString(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        const xet_resource_uuid_t* pUuid,               ///< [in] Pointer to a Sysman UUID
        uint32_t* pSize,                                ///< [in,out] Pointer to the size of the string buffer pointed to by pStr.
                                                        ///< If size is zero, the storage size including end-of-string terminator
                                                        ///< will be returned.
                                                        ///< If size is non-zero and less than the required length, the storage
                                                        ///< size including end-of-string terminator will be returned and an error
                                                        ///< status given.
                                                        ///< If size is non-zero and larger than the required length, the number of
                                                        ///< characters stored in the buffer including the end-of-string terminator
                                                        ///< will be returned.
        char* pStr                                      ///< [in][optional] Pointer to storage for the string representation of the
                                                        ///< UUID
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnConvertUuidToString = dditable->xet.Sysman.pfnConvertUuidToString;
        if( nullptr == pfnConvertUuidToString )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnConvertUuidToString( hSysman, pUuid, pSize, pStr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetResources
    xe_result_t __xecall
    xetSysmanGetResources(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_resource_handle_t hParentResource,          ///< [in] Handle of the parent resource object (can be
                                                        ///< ::XET_INVALID_SYSMAN_RESOURCE_HANDLE)
        xet_resource_type_t type,                       ///< [in] The type of resources to enumerate
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of resources that would be returned.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< resources of the given type starting from index 0.
                                                        ///< If count is larger than the number of resource that will be returned,
                                                        ///< then the driver will update the value with actual number returned.
        xet_resource_handle_t* phResources              ///< [out][optional][range(0, *pCount)] Array of resources resources
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetResources = dditable->xet.Sysman.pfnGetResources;
        if( nullptr == pfnGetResources )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // convert loader handle to driver handle
        hParentResource = reinterpret_cast<xet_resource_object_t*>( hParentResource )->handle;

        // forward to device-driver
        result = pfnGetResources( hSysman, hParentResource, type, pCount, phResources );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phResources ) && ( i < *pCount ); ++i )
                phResources[ i ] = reinterpret_cast<xet_resource_handle_t>(
                    xet_resource_factory.getInstance( phResources[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetDeviceResource
    xe_result_t __xecall
    xetSysmanGetDeviceResource(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xe_device_handle_t hDevice,                     ///< [in] Handle to the device.
        xet_resource_handle_t* phResource               ///< [out] Resource handle for the specified device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetDeviceResource = dditable->xet.Sysman.pfnGetDeviceResource;
        if( nullptr == pfnGetDeviceResource )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetDeviceResource( hSysman, hDevice, phResource );

        try
        {
            // convert driver handle to loader handle
            *phResource = reinterpret_cast<xet_resource_handle_t>(
                xet_resource_factory.getInstance( *phResource, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetResourceByUuid
    xe_result_t __xecall
    xetSysmanGetResourceByUuid(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        const xet_resource_uuid_t* uuid,                ///< [in] UUID for the resource
        xet_resource_handle_t* phResource               ///< [out] Resource handle
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetResourceByUuid = dditable->xet.Sysman.pfnGetResourceByUuid;
        if( nullptr == pfnGetResourceByUuid )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetResourceByUuid( hSysman, uuid, phResource );

        try
        {
            // convert driver handle to loader handle
            *phResource = reinterpret_cast<xet_resource_handle_t>(
                xet_resource_factory.getInstance( *phResource, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetRasErrors
    xe_result_t __xecall
    xetSysmanGetRasErrors(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource. If specified, only errors within that
                                                        ///< resource of child resources are returned. Otherwise all errors are
                                                        ///< returned.
        uint32_t type,                                  ///< [in] Bitfield of error types to filter - one or more of
                                                        ///< ::xet_ras_error_type_t. Set to ::XET_RAS_ERROR_TYPE_ALL to have all
                                                        ///< error types returned.
        uint32_t location,                              ///< [in] Bitfield of error locations to filter - one or more of
                                                        ///< ::xet_ras_error_loc_t. Set to ::XET_RAS_ERROR_LOC_ALL to have all
                                                        ///< error locations returned.
        uint32_t threshold,                             ///< [in] Only return error elements that have occurred at least this
                                                        ///< number of times.
                                                        ///< If set to 0, will get a list of all possible RAS elements, even those
                                                        ///< that have not had errors.
                                                        ///< For error elements of type ::XET_RAS_DATA_TYPE_OCCURRED, there is no
                                                        ///< underlying counter, so they will always be returned independent of the
                                                        ///< threshold setting.
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
        xet_res_error_t* pErrors                        ///< [in] Array of error data
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

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetRasErrors( hSysman, hResource, type, location, threshold, clear, pCount, pErrors );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceIsSame
    xe_result_t __xecall
    xetSysmanResourceIsSame(
        xet_resource_handle_t hLhs,                     ///< [in] Handle of of the resources
        xet_resource_handle_t hRhs,                     ///< [in] Handle of the other resource
        xe_bool_t* pIsSame                              ///< [in] Sets to True if the two resources reference the same underlying
                                                        ///< hardware object
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hLhs )->dditable;
        auto pfnIsSame = dditable->xet.SysmanResource.pfnIsSame;
        if( nullptr == pfnIsSame )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hLhs = reinterpret_cast<xet_resource_object_t*>( hLhs )->handle;

        // convert loader handle to driver handle
        hRhs = reinterpret_cast<xet_resource_object_t*>( hRhs )->handle;

        // forward to device-driver
        result = pfnIsSame( hLhs, hRhs, pIsSame );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetInfo
    xe_result_t __xecall
    xetSysmanResourceGetInfo(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        xet_resource_info_t* pInfo                      ///< [out] Generic information about the resource
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetInfo = dditable->xet.SysmanResource.pfnGetInfo;
        if( nullptr == pfnGetInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetInfo( hResource, pInfo );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetParent
    xe_result_t __xecall
    xetSysmanResourceGetParent(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        xet_resource_handle_t* phResource               ///< [out] Handle of the parent resource
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetParent = dditable->xet.SysmanResource.pfnGetParent;
        if( nullptr == pfnGetParent )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetParent( hResource, phResource );

        try
        {
            // convert driver handle to loader handle
            *phResource = reinterpret_cast<xet_resource_handle_t>(
                xet_resource_factory.getInstance( *phResource, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetChildren
    xe_result_t __xecall
    xetSysmanResourceGetChildren(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of child resources.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< child resources starting from index 0.
                                                        ///< If count is larger than the number of child resources that will be
                                                        ///< returned, then the driver will update the value with the resources
                                                        ///< actually returned.
        xet_resource_handle_t* phResources              ///< [out][optional][range(0, *pCount)] Array of resource handles.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetChildren = dditable->xet.SysmanResource.pfnGetChildren;
        if( nullptr == pfnGetChildren )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetChildren( hResource, pCount, phResources );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phResources ) && ( i < *pCount ); ++i )
                phResources[ i ] = reinterpret_cast<xet_resource_handle_t>(
                    xet_resource_factory.getInstance( phResources[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetPeers
    xe_result_t __xecall
    xetSysmanResourceGetPeers(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array phResources.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of peer resources.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< peer resources starting from index 0.
                                                        ///< If count is larger than the number of peer resources that will be
                                                        ///< returned, then the driver will update the value with the resources
                                                        ///< actually returned.
        xet_resource_handle_t* phResources              ///< [out][optional][range(0, *pCount)] Array of resource handles.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetPeers = dditable->xet.SysmanResource.pfnGetPeers;
        if( nullptr == pfnGetPeers )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetPeers( hResource, pCount, phResources );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phResources ) && ( i < *pCount ); ++i )
                phResources[ i ] = reinterpret_cast<xet_resource_handle_t>(
                    xet_resource_factory.getInstance( phResources[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetBoardProperties
    xe_result_t __xecall
    xetSysmanResourceGetBoardProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_board_property_request_t* pRequest          ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetBoardProperties = dditable->xet.SysmanResource.pfnGetBoardProperties;
        if( nullptr == pfnGetBoardProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetBoardProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetDeviceProperties
    xe_result_t __xecall
    xetSysmanResourceGetDeviceProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetDeviceProperties = dditable->xet.SysmanResource.pfnGetDeviceProperties;
        if( nullptr == pfnGetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetDeviceProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetDeviceProperties
    xe_result_t __xecall
    xetSysmanResourceSetDeviceProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetDeviceProperties = dditable->xet.SysmanResource.pfnSetDeviceProperties;
        if( nullptr == pfnSetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetDeviceProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetPsuProperties
    xe_result_t __xecall
    xetSysmanResourceGetPsuProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetPsuProperties = dditable->xet.SysmanResource.pfnGetPsuProperties;
        if( nullptr == pfnGetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetPsuProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetPsuProperties
    xe_result_t __xecall
    xetSysmanResourceSetPsuProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetPsuProperties = dditable->xet.SysmanResource.pfnSetPsuProperties;
        if( nullptr == pfnSetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetPsuProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetTempProperties
    xe_result_t __xecall
    xetSysmanResourceGetTempProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_temp_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetTempProperties = dditable->xet.SysmanResource.pfnGetTempProperties;
        if( nullptr == pfnGetTempProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetTempProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetFanProperties
    xe_result_t __xecall
    xetSysmanResourceGetFanProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetFanProperties = dditable->xet.SysmanResource.pfnGetFanProperties;
        if( nullptr == pfnGetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetFanProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetFanProperties
    xe_result_t __xecall
    xetSysmanResourceSetFanProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetFanProperties = dditable->xet.SysmanResource.pfnSetFanProperties;
        if( nullptr == pfnSetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetFanProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetLedProperties
    xe_result_t __xecall
    xetSysmanResourceGetLedProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetLedProperties = dditable->xet.SysmanResource.pfnGetLedProperties;
        if( nullptr == pfnGetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetLedProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetLedProperties
    xe_result_t __xecall
    xetSysmanResourceSetLedProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetLedProperties = dditable->xet.SysmanResource.pfnSetLedProperties;
        if( nullptr == pfnSetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetLedProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetFirmwareProperties
    xe_result_t __xecall
    xetSysmanResourceGetFirmwareProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetFirmwareProperties = dditable->xet.SysmanResource.pfnGetFirmwareProperties;
        if( nullptr == pfnGetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetFirmwareProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetFirmwareProperties
    xe_result_t __xecall
    xetSysmanResourceSetFirmwareProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetFirmwareProperties = dditable->xet.SysmanResource.pfnSetFirmwareProperties;
        if( nullptr == pfnSetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetFirmwareProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetPwrProperties
    xe_result_t __xecall
    xetSysmanResourceGetPwrProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetPwrProperties = dditable->xet.SysmanResource.pfnGetPwrProperties;
        if( nullptr == pfnGetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetPwrProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetPwrProperties
    xe_result_t __xecall
    xetSysmanResourceSetPwrProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetPwrProperties = dditable->xet.SysmanResource.pfnSetPwrProperties;
        if( nullptr == pfnSetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetPwrProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetFreqProperties
    xe_result_t __xecall
    xetSysmanResourceGetFreqProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetFreqProperties = dditable->xet.SysmanResource.pfnGetFreqProperties;
        if( nullptr == pfnGetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetFreqProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetFreqProperties
    xe_result_t __xecall
    xetSysmanResourceSetFreqProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetFreqProperties = dditable->xet.SysmanResource.pfnSetFreqProperties;
        if( nullptr == pfnSetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetFreqProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetPwrwellProperties
    xe_result_t __xecall
    xetSysmanResourceGetPwrwellProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetPwrwellProperties = dditable->xet.SysmanResource.pfnGetPwrwellProperties;
        if( nullptr == pfnGetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetPwrwellProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetPwrwellProperties
    xe_result_t __xecall
    xetSysmanResourceSetPwrwellProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetPwrwellProperties = dditable->xet.SysmanResource.pfnSetPwrwellProperties;
        if( nullptr == pfnSetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetPwrwellProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetAccelProperties
    xe_result_t __xecall
    xetSysmanResourceGetAccelProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_accel_property_request_t* pRequest          ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetAccelProperties = dditable->xet.SysmanResource.pfnGetAccelProperties;
        if( nullptr == pfnGetAccelProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetAccelProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetMemProperties
    xe_result_t __xecall
    xetSysmanResourceGetMemProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetMemProperties = dditable->xet.SysmanResource.pfnGetMemProperties;
        if( nullptr == pfnGetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetMemProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetMemProperties
    xe_result_t __xecall
    xetSysmanResourceSetMemProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetMemProperties = dditable->xet.SysmanResource.pfnSetMemProperties;
        if( nullptr == pfnSetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetMemProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetLinkProperties
    xe_result_t __xecall
    xetSysmanResourceGetLinkProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetLinkProperties = dditable->xet.SysmanResource.pfnGetLinkProperties;
        if( nullptr == pfnGetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetLinkProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetLinkProperties
    xe_result_t __xecall
    xetSysmanResourceSetLinkProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetLinkProperties = dditable->xet.SysmanResource.pfnSetLinkProperties;
        if( nullptr == pfnSetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetLinkProperties( hResource, count, pRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRegisterEvents
    xe_result_t __xecall
    xetSysmanRegisterEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_resource_handle_t hResource,                ///< [in] Handle of the parent resource. Events from any contained devices
                                                        ///< will be registered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RESOURCE_HANDLE, events from all
                                                        ///< devices will be registered.
        uint32_t events                                 ///< [in] Bitfield of events to register.
                                                        ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                        ///< Set to (~0) to register to receive all events.
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

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnRegisterEvents( hSysman, hResource, events );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanUnregisterEvents
    xe_result_t __xecall
    xetSysmanUnregisterEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_resource_handle_t hResource,                ///< [in] Handle of the parent resource. Events from any contained devices
                                                        ///< will be unregistered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RESOURCE_HANDLE, events from all
                                                        ///< devices will be unregistered.
        uint32_t events                                 ///< [in] Bitfield of events to unregister.
                                                        ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                        ///< Set to (~0) to unregister all events.
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

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnUnregisterEvents( hSysman, hResource, events );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanListenEvents
    xe_result_t __xecall
    xetSysmanListenEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xe_bool_t block,                                ///< [in] If set to true, the call will block the calling thread
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array pointed to by pEventData.
                                                        ///< If size is zero, then the driver will update the value with the number
                                                        ///< of elements needed to retrieve the list of events.
                                                        ///< If size is less than that required to store the list of events, the
                                                        ///< driver will update the value with the required number of elements and
                                                        ///< return an error.
                                                        ///< If size is larger than that required to store the list of events, the
                                                        ///< driver will update the value with the number of elements actually returned.
        xet_sysman_event_data_t* pEventData             ///< [in] Pointer to an array of event data
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnListenEvents = dditable->xet.Sysman.pfnListenEvents;
        if( nullptr == pfnListenEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnListenEvents( hSysman, block, pCount, pEventData );

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
            pDdiTable->pfnConvertUuidToString                      = loader::xetSysmanConvertUuidToString;
            pDdiTable->pfnGetResources                             = loader::xetSysmanGetResources;
            pDdiTable->pfnGetDeviceResource                        = loader::xetSysmanGetDeviceResource;
            pDdiTable->pfnGetResourceByUuid                        = loader::xetSysmanGetResourceByUuid;
            pDdiTable->pfnGetRasErrors                             = loader::xetSysmanGetRasErrors;
            pDdiTable->pfnRegisterEvents                           = loader::xetSysmanRegisterEvents;
            pDdiTable->pfnUnregisterEvents                         = loader::xetSysmanUnregisterEvents;
            pDdiTable->pfnListenEvents                             = loader::xetSysmanListenEvents;
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

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanResource table
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
xetGetSysmanResourceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_resource_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanResourceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanResourceProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanResource );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnIsSame                                   = loader::xetSysmanResourceIsSame;
            pDdiTable->pfnGetInfo                                  = loader::xetSysmanResourceGetInfo;
            pDdiTable->pfnGetParent                                = loader::xetSysmanResourceGetParent;
            pDdiTable->pfnGetChildren                              = loader::xetSysmanResourceGetChildren;
            pDdiTable->pfnGetPeers                                 = loader::xetSysmanResourceGetPeers;
            pDdiTable->pfnGetBoardProperties                       = loader::xetSysmanResourceGetBoardProperties;
            pDdiTable->pfnGetDeviceProperties                      = loader::xetSysmanResourceGetDeviceProperties;
            pDdiTable->pfnSetDeviceProperties                      = loader::xetSysmanResourceSetDeviceProperties;
            pDdiTable->pfnGetPsuProperties                         = loader::xetSysmanResourceGetPsuProperties;
            pDdiTable->pfnSetPsuProperties                         = loader::xetSysmanResourceSetPsuProperties;
            pDdiTable->pfnGetTempProperties                        = loader::xetSysmanResourceGetTempProperties;
            pDdiTable->pfnGetFanProperties                         = loader::xetSysmanResourceGetFanProperties;
            pDdiTable->pfnSetFanProperties                         = loader::xetSysmanResourceSetFanProperties;
            pDdiTable->pfnGetLedProperties                         = loader::xetSysmanResourceGetLedProperties;
            pDdiTable->pfnSetLedProperties                         = loader::xetSysmanResourceSetLedProperties;
            pDdiTable->pfnGetFirmwareProperties                    = loader::xetSysmanResourceGetFirmwareProperties;
            pDdiTable->pfnSetFirmwareProperties                    = loader::xetSysmanResourceSetFirmwareProperties;
            pDdiTable->pfnGetPwrProperties                         = loader::xetSysmanResourceGetPwrProperties;
            pDdiTable->pfnSetPwrProperties                         = loader::xetSysmanResourceSetPwrProperties;
            pDdiTable->pfnGetFreqProperties                        = loader::xetSysmanResourceGetFreqProperties;
            pDdiTable->pfnSetFreqProperties                        = loader::xetSysmanResourceSetFreqProperties;
            pDdiTable->pfnGetPwrwellProperties                     = loader::xetSysmanResourceGetPwrwellProperties;
            pDdiTable->pfnSetPwrwellProperties                     = loader::xetSysmanResourceSetPwrwellProperties;
            pDdiTable->pfnGetAccelProperties                       = loader::xetSysmanResourceGetAccelProperties;
            pDdiTable->pfnGetMemProperties                         = loader::xetSysmanResourceGetMemProperties;
            pDdiTable->pfnSetMemProperties                         = loader::xetSysmanResourceSetMemProperties;
            pDdiTable->pfnGetLinkProperties                        = loader::xetSysmanResourceGetLinkProperties;
            pDdiTable->pfnSetLinkProperties                        = loader::xetSysmanResourceSetLinkProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanResource;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanResourceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanResourceProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
