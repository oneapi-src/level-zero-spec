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
    xet_res_container_factory_t         xet_res_container_factory;
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
    /// @brief Intercept function for xetPowerCreate
    xe_result_t __xecall
    xetPowerCreate(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device object
        uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
        xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xet.Power.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, flags, pPowerHandle );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerDestroy
    xe_result_t __xecall
    xetPowerDestroy(
        xet_power_handle_t hPower                       ///< [in][release] handle of the power object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnDestroy( hPower );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetAveragePowerLimit
    xe_result_t __xecall
    xetPowerGetAveragePowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetAveragePowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetBurstPowerLimit
    xe_result_t __xecall
    xetPowerGetBurstPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetBurstPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetPeakPowerLimit
    xe_result_t __xecall
    xetPowerGetPeakPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetPeakPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetAllPowerLimits
    xe_result_t __xecall
    xetPowerGetAllPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetAllPowerLimits( hPower, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetDefaultPowerLimits
    xe_result_t __xecall
    xetPowerGetDefaultPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetDefaultPowerLimits( hPower, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetAveragePowerLimit
    xe_result_t __xecall
    xetPowerSetAveragePowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetAveragePowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetBurstPowerLimit
    xe_result_t __xecall
    xetPowerSetBurstPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetBurstPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetPeakPowerLimit
    xe_result_t __xecall
    xetPowerSetPeakPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetPeakPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetPowerLimits
    xe_result_t __xecall
    xetPowerSetPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetPowerLimits( hPower, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetEnergyCounter
    xe_result_t __xecall
    xetPowerGetEnergyCounter(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetEnergyCounter( hPower, pEnergy );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetTurboMode
    xe_result_t __xecall
    xetPowerGetTurboMode(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetTurboMode( hPower, pTurboMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetTurboMode
    xe_result_t __xecall
    xetPowerSetTurboMode(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetTurboMode( hPower, pTurboMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGet
    xe_result_t __xecall
    xetFreqDomainGet(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequency domains.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of frequency domains available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< frequency domains.
                                                        ///< if count is larger than the number of frequency domains available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< frequency domains available.
        xet_freq_domain_handle_t* phFreqDomain          ///< [in,out][optional][range(0, *pCount)] array of handle of frequency
                                                        ///< domains
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGet( hPower, pCount, phFreqDomain );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetProperties
    xe_result_t __xecall
    xetFreqDomainGetProperties(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetProperties( hFreqDomain, pFreqDomainProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetSourceFreqDomain
    xe_result_t __xecall
    xetFreqDomainGetSourceFreqDomain(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_freq_domain_handle_t* phSrcFreqDomain       ///< [out] pointer to a handle where the source frequency domain handle
                                                        ///< will be returned
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetSourceFreqDomain( hFreqDomain, phSrcFreqDomain );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetSupportedClocks
    xe_result_t __xecall
    xetFreqDomainGetSupportedClocks(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t numClockPoints,                        ///< [in] number of elements in pClocks
        uint32_t* pClocks                               ///< [out] pointer to array of frequencies
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetSupportedClocks( hFreqDomain, numClockPoints, pClocks );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetSupportedClockDividers
    xe_result_t __xecall
    xetFreqDomainGetSupportedClockDividers(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t numClockDividers,                      ///< [in] number of elements in pDividers
        xet_clock_divider_t* pDividers                  ///< [out] pointer to array of dividers
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetClockRange
    xe_result_t __xecall
    xetFreqDomainGetClockRange(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t* pMinClock,                            ///< [out] min clock frequency in units of MHz
        uint32_t* pMaxClock                             ///< [out] max clock frequency in units of MHz
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetClockRange( hFreqDomain, pMinClock, pMaxClock );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainSetClockRange
    xe_result_t __xecall
    xetFreqDomainSetClockRange(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
        uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetClockRange( hFreqDomain, minClock, maxClock );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainSetClockDivider
    xe_result_t __xecall
    xetFreqDomainSetClockDivider(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetClockDivider( hFreqDomain, pClockDividerRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetCurrentFrequency
    xe_result_t __xecall
    xetFreqDomainGetCurrentFrequency(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t* pFreqRequest,                         ///< [out] current frequency in MHz requested by the driver
        uint32_t* pFreqResolved,                        ///< [out] the actual frequency in MHz
        xet_freq_throttle_reasons_t* pFreqThrottleReasons   ///< [out] the reason the resolved frequency is lower than the request
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetCurrentFrequency( hFreqDomain, pFreqRequest, pFreqResolved, pFreqThrottleReasons );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanCount
    xe_result_t __xecall
    xetPowerFanCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pFanCount                             ///< [out] the number of fans on the device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnFanCount( hPower, pFanCount );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanGetProperties
    xe_result_t __xecall
    xetPowerFanGetProperties(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        xet_fan_properties_t* pFanProperties            ///< [out] pointer to storage for fan properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnFanGetProperties( hPower, fanIndex, pFanProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanGetSpeedTable
    xe_result_t __xecall
    xetPowerFanGetSpeedTable(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
        uint32_t* pNumFanPoints,                        ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                        ///< number of elements returned
        xet_fan_point_t* pFanPoints                     ///< [out] pointer to an array of temperature/fan-speed points
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanSetSpeedTable
    xe_result_t __xecall
    xetPowerFanSetSpeedTable(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
        xet_fan_point_t* pFanPoints                     ///< [in] pointer to an array of temperature/fan-speed points
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanGetSpeed
    xe_result_t __xecall
    xetPowerFanGetSpeed(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
        xet_fan_speed_info_t* pFanSpeed                 ///< [out] pointer to an array of current fan speeds
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanSetSpeed
    xe_result_t __xecall
    xetPowerFanSetSpeed(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        xet_fan_speed_info_t* pFanSpeed                 ///< [in] pointer to an array of current fan speeds
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerTemperatureSensorCount
    xe_result_t __xecall
    xetPowerTemperatureSensorCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnTemperatureSensorCount( hPower, pSensorCount );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetTemperatureProperties
    xe_result_t __xecall
    xetPowerGetTemperatureProperties(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        xet_temperature_properties_t* pProperties       ///< [out] pointer to properties for this sensor
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetTemperatureProperties( hPower, sensorIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetTemperature
    xe_result_t __xecall
    xetPowerGetTemperature(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        uint32_t numSensors,                            ///< [in] pTemperatures will contain results for sensors index
                                                        ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
        uint16_t* pTemperatures                         ///< [out] pointer to an array of temperatures in units of degrees celsius
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetTemperatureThreshold
    xe_result_t __xecall
    xetPowerSetTemperatureThreshold(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                        ///< will be throttled
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerActivityCount
    xe_result_t __xecall
    xetPowerActivityCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnActivityCount( hPower, pActivityCount );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetActivityProperties
    xe_result_t __xecall
    xetPowerGetActivityProperties(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t activityIndex,                         ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
        xet_activity_properties_t* pProperties          ///< [out] pointer to properties for this activity counter
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetActivityProperties( hPower, activityIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetActivityCounters
    xe_result_t __xecall
    xetPowerGetActivityCounters(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
        uint32_t numCounters,                           ///< [in] pCounters will contain results for activity counter index
                                                        ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
        xet_activity_counters_t* pCounters              ///< [out] pointer to an array of activity counter data
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // forward to device-driver
        result = pfnGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanCreate
    xe_result_t __xecall
    xetSysmanCreate(
        xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
        uint32_t flags,                                 ///< [in] bitfield of ::xet_sysman_init_flags_t
        xet_sysman_handle_t* phSysman                   ///< [out] handle for accessing SMI features
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
        result = pfnCreate( hDeviceGroup, flags, phSysman );

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
    /// @brief Intercept function for xetSysmanGetResourceContainers
    xe_result_t __xecall
    xetSysmanGetResourceContainers(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_res_container_type_t type,                  ///< [in] The type of resource containers to enumerate
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource containers.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of resource containers of the given type that are available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< resource containers of the given type starting from index 0.
                                                        ///< If count is larger than the number of resource containers available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< resource containers of a given type that are available.
        xet_res_container_handle_t* phResContainers     ///< [out][optional][range(0, *pCount)] array of handle of resource
                                                        ///< containers
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetResourceContainers = dditable->xet.Sysman.pfnGetResourceContainers;
        if( nullptr == pfnGetResourceContainers )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetResourceContainers( hSysman, type, pCount, phResContainers );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phResContainers ) && ( i < *pCount ); ++i )
                phResContainers[ i ] = reinterpret_cast<xet_res_container_handle_t>(
                    xet_res_container_factory.getInstance( phResContainers[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetDeviceResourceContainer
    xe_result_t __xecall
    xetSysmanGetDeviceResourceContainer(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xe_device_handle_t hDevice,                     ///< [in] Handle to the device. It must be a member of the same Device
                                                        ///< Group as hSysman was created from.
        xet_res_container_handle_t* phResContainer      ///< [out] Resource container for the specified device.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetDeviceResourceContainer = dditable->xet.Sysman.pfnGetDeviceResourceContainer;
        if( nullptr == pfnGetDeviceResourceContainer )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetDeviceResourceContainer( hSysman, hDevice, phResContainer );

        try
        {
            // convert driver handle to loader handle
            *phResContainer = reinterpret_cast<xet_res_container_handle_t>(
                xet_res_container_factory.getInstance( *phResContainer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetResourceContainerByUuid
    xe_result_t __xecall
    xetSysmanGetResourceContainerByUuid(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_res_container_uuid_t uuid,                  ///< [in] UUID for the resource container.
        xet_res_container_handle_t* phResContainer      ///< [out] Resource container with UUID.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnGetResourceContainerByUuid = dditable->xet.Sysman.pfnGetResourceContainerByUuid;
        if( nullptr == pfnGetResourceContainerByUuid )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnGetResourceContainerByUuid( hSysman, uuid, phResContainer );

        try
        {
            // convert driver handle to loader handle
            *phResContainer = reinterpret_cast<xet_res_container_handle_t>(
                xet_res_container_factory.getInstance( *phResContainer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResContainerGetInfo
    xe_result_t __xecall
    xetSysmanResContainerGetInfo(
        xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
        xet_res_container_info_t* pInfo                 ///< [out] Generic information about the resource container.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->dditable;
        auto pfnGetInfo = dditable->xet.SysmanResContainer.pfnGetInfo;
        if( nullptr == pfnGetInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainer = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->handle;

        // forward to device-driver
        result = pfnGetInfo( hResContainer, pInfo );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResContainerGetParent
    xe_result_t __xecall
    xetSysmanResContainerGetParent(
        xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container.
        xet_res_container_handle_t* phResContainer      ///< [out] Handle of the parent resource container.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->dditable;
        auto pfnGetParent = dditable->xet.SysmanResContainer.pfnGetParent;
        if( nullptr == pfnGetParent )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainer = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->handle;

        // forward to device-driver
        result = pfnGetParent( hResContainer, phResContainer );

        try
        {
            // convert driver handle to loader handle
            *phResContainer = reinterpret_cast<xet_res_container_handle_t>(
                xet_res_container_factory.getInstance( *phResContainer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResContainerGetChildren
    xe_result_t __xecall
    xetSysmanResContainerGetChildren(
        xet_res_container_handle_t hResContainter,      ///< [in] Handle of the resource container
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of child resource containers.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of child resource containers.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< child resource containers starting from index 0.
                                                        ///< If count is larger than the number of child resource containers
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of child resource containers.
        xet_res_container_handle_t* phResContainers     ///< [out][optional][range(0, *pCount)] array of handle of resource
                                                        ///< containers
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainter )->dditable;
        auto pfnGetChildren = dditable->xet.SysmanResContainer.pfnGetChildren;
        if( nullptr == pfnGetChildren )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainter = reinterpret_cast<xet_res_container_object_t*>( hResContainter )->handle;

        // forward to device-driver
        result = pfnGetChildren( hResContainter, pCount, phResContainers );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phResContainers ) && ( i < *pCount ); ++i )
                phResContainers[ i ] = reinterpret_cast<xet_res_container_handle_t>(
                    xet_res_container_factory.getInstance( phResContainers[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResContainerGetPeers
    xe_result_t __xecall
    xetSysmanResContainerGetPeers(
        xet_res_container_handle_t hResContainter,      ///< [in] Handle of the resource container
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of peer resource containers.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of peer resource containers.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< peer resource containers starting from index 0.
                                                        ///< If count is larger than the number of peer resource containers
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of peer resource containers.
        xet_res_container_handle_t* phResContainers     ///< [out][optional][range(0, *pCount)] array of handle of resource
                                                        ///< containers
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainter )->dditable;
        auto pfnGetPeers = dditable->xet.SysmanResContainer.pfnGetPeers;
        if( nullptr == pfnGetPeers )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainter = reinterpret_cast<xet_res_container_object_t*>( hResContainter )->handle;

        // forward to device-driver
        result = pfnGetPeers( hResContainter, pCount, phResContainers );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phResContainers ) && ( i < *pCount ); ++i )
                phResContainers[ i ] = reinterpret_cast<xet_res_container_handle_t>(
                    xet_res_container_factory.getInstance( phResContainers[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResContainerGetResources
    xe_result_t __xecall
    xetSysmanResContainerGetResources(
        xet_res_container_handle_t hResContainter,      ///< [in] Handle of the resource container
        xet_resource_type_t type,                       ///< [in] The type of resources to enumerate
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of resources of the given type that are available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of
                                                        ///< resources of the given type starting from index 0.
                                                        ///< If count is larger than the number of resources available, then the
                                                        ///< driver will update the value with the correct number of resources of a
                                                        ///< given type that are available.
        xet_resource_handle_t* phResources              ///< [out][optional][range(0, *pCount)] array of handle of resources
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainter )->dditable;
        auto pfnGetResources = dditable->xet.SysmanResContainer.pfnGetResources;
        if( nullptr == pfnGetResources )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainter = reinterpret_cast<xet_res_container_object_t*>( hResContainter )->handle;

        // forward to device-driver
        result = pfnGetResources( hResContainter, type, pCount, phResources );

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
    /// @brief Intercept function for xetSysmanResourceGetInfo
    xe_result_t __xecall
    xetSysmanResourceGetInfo(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        xet_resource_info_t* pInfo                      ///< [out] Generic information about the resource.
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
    /// @brief Intercept function for xetSysmanResContainerGetBoardProperties
    xe_result_t __xecall
    xetSysmanResContainerGetBoardProperties(
        xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_board_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->dditable;
        auto pfnGetBoardProperties = dditable->xet.SysmanResContainer.pfnGetBoardProperties;
        if( nullptr == pfnGetBoardProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainer = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->handle;

        // forward to device-driver
        result = pfnGetBoardProperties( hResContainer, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResContainerGetDeviceProperties
    xe_result_t __xecall
    xetSysmanResContainerGetDeviceProperties(
        xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_device_properties_t* pIndexes,              ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->dditable;
        auto pfnGetDeviceProperties = dditable->xet.SysmanResContainer.pfnGetDeviceProperties;
        if( nullptr == pfnGetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainer = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->handle;

        // forward to device-driver
        result = pfnGetDeviceProperties( hResContainer, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResContainerSetDeviceProperties
    xe_result_t __xecall
    xetSysmanResContainerSetDeviceProperties(
        xet_res_container_handle_t hResContainer,       ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_device_properties_t* pIndexes,              ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->dditable;
        auto pfnSetDeviceProperties = dditable->xet.SysmanResContainer.pfnSetDeviceProperties;
        if( nullptr == pfnSetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResContainer = reinterpret_cast<xet_res_container_object_t*>( hResContainer )->handle;

        // forward to device-driver
        result = pfnSetDeviceProperties( hResContainer, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetPsuProperties
    xe_result_t __xecall
    xetSysmanResourceGetPsuProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_psu_properties_t* pIndexes,                 ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetPsuProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetPsuProperties
    xe_result_t __xecall
    xetSysmanResourceSetPsuProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_psu_properties_t* pIndexes,                 ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetPsuProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetTempProperties
    xe_result_t __xecall
    xetSysmanResourceGetTempProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_temp_properties_t* pIndexes,                ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetTempProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetTempProperties
    xe_result_t __xecall
    xetSysmanResourceSetTempProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_temp_properties_t* pIndexes,                ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetTempProperties = dditable->xet.SysmanResource.pfnSetTempProperties;
        if( nullptr == pfnSetTempProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetTempProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetFanProperties
    xe_result_t __xecall
    xetSysmanResourceGetFanProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_fan_properties_t* pIndexes,                 ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetFanProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetFanProperties
    xe_result_t __xecall
    xetSysmanResourceSetFanProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_fan_properties_t* pIndexes,                 ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetFanProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetLedProperties
    xe_result_t __xecall
    xetSysmanResourceGetLedProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_led_properties_t* pIndexes,                 ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetLedProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetLedProperties
    xe_result_t __xecall
    xetSysmanResourceSetLedProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_led_properties_t* pIndexes,                 ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetLedProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetFirmwareProperties
    xe_result_t __xecall
    xetSysmanResourceGetFirmwareProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_firmware_properties_t* pIndexes,            ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetFirmwareProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetFirmwareProperties
    xe_result_t __xecall
    xetSysmanResourceSetFirmwareProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_firmware_properties_t* pIndexes,            ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetFirmwareProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetPwrProperties
    xe_result_t __xecall
    xetSysmanResourceGetPwrProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_pwr_properties_t* pIndexes,                 ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetPwrProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetPwrProperties
    xe_result_t __xecall
    xetSysmanResourceSetPwrProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_pwr_properties_t* pIndexes,                 ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetPwrProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetFreqProperties
    xe_result_t __xecall
    xetSysmanResourceGetFreqProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_freq_properties_t* pIndexes,                ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetFreqProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetFreqProperties
    xe_result_t __xecall
    xetSysmanResourceSetFreqProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_freq_properties_t* pIndexes,                ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetFreqProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetPwrWellProperties
    xe_result_t __xecall
    xetSysmanResourceGetPwrWellProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_pwrwell_properties_t* pIndexes,             ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnGetPwrWellProperties = dditable->xet.SysmanResource.pfnGetPwrWellProperties;
        if( nullptr == pfnGetPwrWellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnGetPwrWellProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetPwrWellProperties
    xe_result_t __xecall
    xetSysmanResourceSetPwrWellProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_pwrwell_properties_t* pIndexes,             ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetPwrWellProperties = dditable->xet.SysmanResource.pfnSetPwrWellProperties;
        if( nullptr == pfnSetPwrWellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetPwrWellProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetAccelProperties
    xe_result_t __xecall
    xetSysmanResourceGetAccelProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_accel_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetAccelProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetAccelProperties
    xe_result_t __xecall
    xetSysmanResourceSetAccelProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_accel_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_resource_object_t*>( hResource )->dditable;
        auto pfnSetAccelProperties = dditable->xet.SysmanResource.pfnSetAccelProperties;
        if( nullptr == pfnSetAccelProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hResource = reinterpret_cast<xet_resource_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnSetAccelProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetMemProperties
    xe_result_t __xecall
    xetSysmanResourceGetMemProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_mem_properties_t* pIndexes,                 ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetMemProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetMemProperties
    xe_result_t __xecall
    xetSysmanResourceSetMemProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_mem_properties_t* pIndexes,                 ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetMemProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetLinkProperties
    xe_result_t __xecall
    xetSysmanResourceGetLinkProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_link_properties_t* pIndexes,                ///< [in] An array of property indexes to be read
        void* pValues,                                  ///< [out] A pointer to storage for the data of the requested properties.
        uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                        ///< If size is zero, then the driver will update the value with the size
                                                        ///< required to store the requested properties.
                                                        ///< If size is less than that required to store the requested data for the
                                                        ///< properties, the driver will update the value with the required size
                                                        ///< and return an error.
                                                        ///< If size is larger than that required to store the requested data for
                                                        ///< the properties, the driver will update the value with the size of the
                                                        ///< data returned.
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
        result = pfnGetLinkProperties( hResource, count, pIndexes, pValues, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceSetLinkProperties
    xe_result_t __xecall
    xetSysmanResourceSetLinkProperties(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource container
        uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
        xet_link_properties_t* pIndexes,                ///< [in] An array of property indexes to be set
        void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                        ///< properties.
        uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
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
        result = pfnSetLinkProperties( hResource, count, pIndexes, pValues, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRegisterEvents
    xe_result_t __xecall
    xetSysmanRegisterEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_res_container_handle_t hResource,           ///< [in] Handle of the resource container. Events from any contained
                                                        ///< devices will be registered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                        ///< from all devices will be registered.
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
        hResource = reinterpret_cast<xet_res_container_object_t*>( hResource )->handle;

        // forward to device-driver
        result = pfnRegisterEvents( hSysman, hResource, events );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanUnregisterEvents
    xe_result_t __xecall
    xetSysmanUnregisterEvents(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_res_container_handle_t hResource,           ///< [in] Handle of the resource container. Events from any contained
                                                        ///< devices will be unregistered.
                                                        ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                        ///< from all devices will be unregistered.
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
        hResource = reinterpret_cast<xet_res_container_object_t*>( hResource )->handle;

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
            pDdiTable->pfnGetResourceContainers                    = loader::xetSysmanGetResourceContainers;
            pDdiTable->pfnGetDeviceResourceContainer               = loader::xetSysmanGetDeviceResourceContainer;
            pDdiTable->pfnGetResourceContainerByUuid               = loader::xetSysmanGetResourceContainerByUuid;
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
/// @brief Exported function for filling application's SysmanResContainer table
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
xetGetSysmanResContainerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_res_container_dditable_t* pDdiTable  ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanResContainerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanResContainerProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanResContainer );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetInfo                                  = loader::xetSysmanResContainerGetInfo;
            pDdiTable->pfnGetParent                                = loader::xetSysmanResContainerGetParent;
            pDdiTable->pfnGetChildren                              = loader::xetSysmanResContainerGetChildren;
            pDdiTable->pfnGetPeers                                 = loader::xetSysmanResContainerGetPeers;
            pDdiTable->pfnGetResources                             = loader::xetSysmanResContainerGetResources;
            pDdiTable->pfnGetBoardProperties                       = loader::xetSysmanResContainerGetBoardProperties;
            pDdiTable->pfnGetDeviceProperties                      = loader::xetSysmanResContainerGetDeviceProperties;
            pDdiTable->pfnSetDeviceProperties                      = loader::xetSysmanResContainerSetDeviceProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanResContainer;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanResContainerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanResContainerProcAddrTable") );
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
            pDdiTable->pfnGetInfo                                  = loader::xetSysmanResourceGetInfo;
            pDdiTable->pfnGetPsuProperties                         = loader::xetSysmanResourceGetPsuProperties;
            pDdiTable->pfnSetPsuProperties                         = loader::xetSysmanResourceSetPsuProperties;
            pDdiTable->pfnGetTempProperties                        = loader::xetSysmanResourceGetTempProperties;
            pDdiTable->pfnSetTempProperties                        = loader::xetSysmanResourceSetTempProperties;
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
            pDdiTable->pfnGetPwrWellProperties                     = loader::xetSysmanResourceGetPwrWellProperties;
            pDdiTable->pfnSetPwrWellProperties                     = loader::xetSysmanResourceSetPwrWellProperties;
            pDdiTable->pfnGetAccelProperties                       = loader::xetSysmanResourceGetAccelProperties;
            pDdiTable->pfnSetAccelProperties                       = loader::xetSysmanResourceSetAccelProperties;
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

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
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
xetGetPowerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_power_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetPowerProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Power );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xetPowerCreate;
            pDdiTable->pfnDestroy                                  = loader::xetPowerDestroy;
            pDdiTable->pfnGetAveragePowerLimit                     = loader::xetPowerGetAveragePowerLimit;
            pDdiTable->pfnGetBurstPowerLimit                       = loader::xetPowerGetBurstPowerLimit;
            pDdiTable->pfnGetPeakPowerLimit                        = loader::xetPowerGetPeakPowerLimit;
            pDdiTable->pfnGetAllPowerLimits                        = loader::xetPowerGetAllPowerLimits;
            pDdiTable->pfnGetDefaultPowerLimits                    = loader::xetPowerGetDefaultPowerLimits;
            pDdiTable->pfnSetAveragePowerLimit                     = loader::xetPowerSetAveragePowerLimit;
            pDdiTable->pfnSetBurstPowerLimit                       = loader::xetPowerSetBurstPowerLimit;
            pDdiTable->pfnSetPeakPowerLimit                        = loader::xetPowerSetPeakPowerLimit;
            pDdiTable->pfnSetPowerLimits                           = loader::xetPowerSetPowerLimits;
            pDdiTable->pfnGetEnergyCounter                         = loader::xetPowerGetEnergyCounter;
            pDdiTable->pfnGetTurboMode                             = loader::xetPowerGetTurboMode;
            pDdiTable->pfnSetTurboMode                             = loader::xetPowerSetTurboMode;
            pDdiTable->pfnFanCount                                 = loader::xetPowerFanCount;
            pDdiTable->pfnFanGetProperties                         = loader::xetPowerFanGetProperties;
            pDdiTable->pfnFanGetSpeedTable                         = loader::xetPowerFanGetSpeedTable;
            pDdiTable->pfnFanSetSpeedTable                         = loader::xetPowerFanSetSpeedTable;
            pDdiTable->pfnFanGetSpeed                              = loader::xetPowerFanGetSpeed;
            pDdiTable->pfnFanSetSpeed                              = loader::xetPowerFanSetSpeed;
            pDdiTable->pfnTemperatureSensorCount                   = loader::xetPowerTemperatureSensorCount;
            pDdiTable->pfnGetTemperatureProperties                 = loader::xetPowerGetTemperatureProperties;
            pDdiTable->pfnGetTemperature                           = loader::xetPowerGetTemperature;
            pDdiTable->pfnSetTemperatureThreshold                  = loader::xetPowerSetTemperatureThreshold;
            pDdiTable->pfnActivityCount                            = loader::xetPowerActivityCount;
            pDdiTable->pfnGetActivityProperties                    = loader::xetPowerGetActivityProperties;
            pDdiTable->pfnGetActivityCounters                      = loader::xetPowerGetActivityCounters;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Power;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetPowerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FreqDomain table
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
xetGetFreqDomainProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_freq_domain_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetFreqDomainProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.FreqDomain );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xetFreqDomainGet;
            pDdiTable->pfnGetProperties                            = loader::xetFreqDomainGetProperties;
            pDdiTable->pfnGetSourceFreqDomain                      = loader::xetFreqDomainGetSourceFreqDomain;
            pDdiTable->pfnGetSupportedClocks                       = loader::xetFreqDomainGetSupportedClocks;
            pDdiTable->pfnGetSupportedClockDividers                = loader::xetFreqDomainGetSupportedClockDividers;
            pDdiTable->pfnGetClockRange                            = loader::xetFreqDomainGetClockRange;
            pDdiTable->pfnSetClockRange                            = loader::xetFreqDomainSetClockRange;
            pDdiTable->pfnSetClockDivider                          = loader::xetFreqDomainSetClockDivider;
            pDdiTable->pfnGetCurrentFrequency                      = loader::xetFreqDomainGetCurrentFrequency;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.FreqDomain;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetFreqDomainProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
