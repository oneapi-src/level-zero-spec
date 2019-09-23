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
    xet_sysman_pwr_factory_t            xet_sysman_pwr_factory;
    xet_sysman_freq_factory_t           xet_sysman_freq_factory;
    xet_sysman_engine_factory_t         xet_sysman_engine_factory;
    xet_sysman_standby_factory_t        xet_sysman_standby_factory;
    xet_sysman_firmware_factory_t       xet_sysman_firmware_factory;
    xet_sysman_mem_factory_t            xet_sysman_mem_factory;
    xet_sysman_link_switch_factory_t    xet_sysman_link_switch_factory;
    xet_sysman_link_port_factory_t      xet_sysman_link_port_factory;
    xet_sysman_temp_factory_t           xet_sysman_temp_factory;
    xet_sysman_psu_factory_t            xet_sysman_psu_factory;
    xet_sysman_fan_factory_t            xet_sysman_fan_factory;
    xet_sysman_led_factory_t            xet_sysman_led_factory;
    xet_sysman_ras_factory_t            xet_sysman_ras_factory;
    xet_sysman_diag_factory_t           xet_sysman_diag_factory;

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
        xet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
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
        xet_metric_properties_t* pProperties            ///< [in,out] metric properties
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
    /// @brief Intercept function for xetSysmanSchedulerGetCurrentMode
    xe_result_t __xecall
    xetSysmanSchedulerGetCurrentMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGetCurrentMode = dditable->xet.Sysman.pfnSchedulerGetCurrentMode;
        if( nullptr == pfnSchedulerGetCurrentMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGetCurrentMode( hSysman, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSchedulerGetTimeoutModeProperties
    xe_result_t __xecall
    xetSysmanSchedulerGetTimeoutModeProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xe_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        xet_sched_timeout_properties_t* pConfig         ///< [in] Will contain the current parameters for this mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGetTimeoutModeProperties = dditable->xet.Sysman.pfnSchedulerGetTimeoutModeProperties;
        if( nullptr == pfnSchedulerGetTimeoutModeProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGetTimeoutModeProperties( hSysman, getDefaults, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSchedulerGetTimesliceModeProperties
    xe_result_t __xecall
    xetSysmanSchedulerGetTimesliceModeProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xe_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        xet_sched_timeslice_properties_t* pConfig       ///< [in] Will contain the current parameters for this mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGetTimesliceModeProperties = dditable->xet.Sysman.pfnSchedulerGetTimesliceModeProperties;
        if( nullptr == pfnSchedulerGetTimesliceModeProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGetTimesliceModeProperties( hSysman, getDefaults, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSchedulerSetTimeoutMode
    xe_result_t __xecall
    xetSysmanSchedulerSetTimeoutMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        xe_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetTimeoutMode = dditable->xet.Sysman.pfnSchedulerSetTimeoutMode;
        if( nullptr == pfnSchedulerSetTimeoutMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetTimeoutMode( hSysman, pProperties, pNeedReboot );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSchedulerSetTimesliceMode
    xe_result_t __xecall
    xetSysmanSchedulerSetTimesliceMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        xe_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetTimesliceMode = dditable->xet.Sysman.pfnSchedulerSetTimesliceMode;
        if( nullptr == pfnSchedulerSetTimesliceMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetTimesliceMode( hSysman, pProperties, pNeedReboot );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSchedulerSetExclusiveMode
    xe_result_t __xecall
    xetSysmanSchedulerSetExclusiveMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xe_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetExclusiveMode = dditable->xet.Sysman.pfnSchedulerSetExclusiveMode;
        if( nullptr == pfnSchedulerSetExclusiveMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetExclusiveMode( hSysman, pNeedReboot );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSchedulerSetSingleCmdQueueMode
    xe_result_t __xecall
    xetSysmanSchedulerSetSingleCmdQueueMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xe_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetSingleCmdQueueMode = dditable->xet.Sysman.pfnSchedulerSetSingleCmdQueueMode;
        if( nullptr == pfnSchedulerSetSingleCmdQueueMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetSingleCmdQueueMode( hSysman, pNeedReboot );

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
    /// @brief Intercept function for xetSysmanDeviceWasRepaired
    xe_result_t __xecall
    xetSysmanDeviceWasRepaired(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        xe_bool_t* pWasRepaired                         ///< [in] Will indicate if the device was repaired
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceWasRepaired = dditable->xet.Sysman.pfnDeviceWasRepaired;
        if( nullptr == pfnDeviceWasRepaired )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceWasRepaired( hSysman, pWasRepaired );

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
    /// @brief Intercept function for xetSysmanPowerGet
    xe_result_t __xecall
    xetSysmanPowerGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerGet = dditable->xet.Sysman.pfnPowerGet;
        if( nullptr == pfnPowerGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerGet( hSysman, pCount, phPower );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<xet_sysman_pwr_handle_t>(
                    xet_sysman_pwr_factory.getInstance( phPower[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetProperties
    xe_result_t __xecall
    xetSysmanPowerGetProperties(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanPower.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPower, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetEnergyCounter
    xe_result_t __xecall
    xetSysmanPowerGetEnergyCounter(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyCounter = dditable->xet.SysmanPower.pfnGetEnergyCounter;
        if( nullptr == pfnGetEnergyCounter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyCounter( hPower, pEnergy );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerGetEnergyThreshold(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_energy_threshold_t* pThreshold        ///< [out] The current energy threshold value in joules.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyThreshold = dditable->xet.SysmanPower.pfnGetEnergyThreshold;
        if( nullptr == pfnGetEnergyThreshold )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyThreshold( hPower, pThreshold );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerSetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerSetEnergyThreshold(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_energy_threshold_t* pThreshold        ///< [in] The energy threshold to be set in joules.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnSetEnergyThreshold = dditable->xet.SysmanPower.pfnSetEnergyThreshold;
        if( nullptr == pfnSetEnergyThreshold )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetEnergyThreshold( hPower, pThreshold );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetLimits
    xe_result_t __xecall
    xetSysmanPowerGetLimits(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
        xet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
        xet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetLimits = dditable->xet.SysmanPower.pfnGetLimits;
        if( nullptr == pfnGetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerSetLimits
    xe_result_t __xecall
    xetSysmanPowerSetLimits(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        const xet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const xet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const xet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnSetLimits = dditable->xet.SysmanPower.pfnSetLimits;
        if( nullptr == pfnSetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetFanSpeed
    xe_result_t __xecall
    xetSysmanFrequencySetFanSpeed(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_fan_control_t* pFanControl               ///< [out] Pointer to the allocated structure.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetFanSpeed = dditable->xet.SysmanFrequency.pfnSetFanSpeed;
        if( nullptr == pfnSetFanSpeed )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetFanSpeed( hFrequency, pFanControl );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcCapabilities
    xe_result_t __xecall
    xetSysmanFrequencyGetOcCapabilities(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_capabilities_t* pOcCapabilities          ///< [out] Pointer to the allocated structure.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetOcCapabilities = dditable->xet.SysmanFrequency.pfnGetOcCapabilities;
        if( nullptr == pfnGetOcCapabilities )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetOcCapabilities( hFrequency, pOcCapabilities );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcVrTopology
    xe_result_t __xecall
    xetSysmanFrequencyGetOcVrTopology(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_vr_topology* pOcVrTopology               ///< [out] Pointer to the allocated structure.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetOcVrTopology = dditable->xet.SysmanFrequency.pfnGetOcVrTopology;
        if( nullptr == pfnGetOcVrTopology )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetOcVrTopology( hFrequency, pOcVrTopology );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcOverrideProperties
    xe_result_t __xecall
    xetSysmanFrequencyGetOcOverrideProperties(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_settings_override_t* pOcSettingsOverride ///< [out] Pointer to the allocated structure.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetOcOverrideProperties = dditable->xet.SysmanFrequency.pfnGetOcOverrideProperties;
        if( nullptr == pfnGetOcOverrideProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetOcOverrideProperties( hFrequency, pOcSettingsOverride );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcIccMax
    xe_result_t __xecall
    xetSysmanFrequencyGetOcIccMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcIccMax                             ///< [out] Pointer to the allocated uint32.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetOcIccMax = dditable->xet.SysmanFrequency.pfnGetOcIccMax;
        if( nullptr == pfnGetOcIccMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetOcIccMax( hFrequency, pOcIccMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcTjMax
    xe_result_t __xecall
    xetSysmanFrequencyGetOcTjMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcTjMax                              ///< [out] Pointer to the allocated uint32.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetOcTjMax = dditable->xet.SysmanFrequency.pfnGetOcTjMax;
        if( nullptr == pfnGetOcTjMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetOcTjMax( hFrequency, pOcTjMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetOcOverrideProperties
    xe_result_t __xecall
    xetSysmanFrequencySetOcOverrideProperties(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_settings_override_t* pOcSettingsOverride ///< [in] Pointer to the allocated structure.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetOcOverrideProperties = dditable->xet.SysmanFrequency.pfnSetOcOverrideProperties;
        if( nullptr == pfnSetOcOverrideProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetOcOverrideProperties( hFrequency, pOcSettingsOverride );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetOcIccMax
    xe_result_t __xecall
    xetSysmanFrequencySetOcIccMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcIccMax                             ///< [in] Pointer to the allocated uint32.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetOcIccMax = dditable->xet.SysmanFrequency.pfnSetOcIccMax;
        if( nullptr == pfnSetOcIccMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetOcIccMax( hFrequency, pOcIccMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetOcTjMax
    xe_result_t __xecall
    xetSysmanFrequencySetOcTjMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcTjMax                              ///< [in] Pointer to the allocated uint32.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetOcTjMax = dditable->xet.SysmanFrequency.pfnSetOcTjMax;
        if( nullptr == pfnSetOcTjMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetOcTjMax( hFrequency, pOcTjMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGet
    xe_result_t __xecall
    xetSysmanFrequencyGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencyGet = dditable->xet.Sysman.pfnFrequencyGet;
        if( nullptr == pfnFrequencyGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencyGet( hSysman, pCount, phFrequency );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<xet_sysman_freq_handle_t>(
                    xet_sysman_freq_factory.getInstance( phFrequency[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetProperties
    xe_result_t __xecall
    xetSysmanFrequencyGetProperties(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanFrequency.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFrequency, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetRange
    xe_result_t __xecall
    xetSysmanFrequencyGetRange(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_freq_range_t* pLimits                       ///< [in] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetRange = dditable->xet.SysmanFrequency.pfnGetRange;
        if( nullptr == pfnGetRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetRange( hFrequency, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetRange
    xe_result_t __xecall
    xetSysmanFrequencySetRange(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        const xet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetRange = dditable->xet.SysmanFrequency.pfnSetRange;
        if( nullptr == pfnSetRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetRange( hFrequency, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetState
    xe_result_t __xecall
    xetSysmanFrequencyGetState(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetState = dditable->xet.SysmanFrequency.pfnGetState;
        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetState( hFrequency, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetThrottleTime
    xe_result_t __xecall
    xetSysmanFrequencyGetThrottleTime(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetThrottleTime = dditable->xet.SysmanFrequency.pfnGetThrottleTime;
        if( nullptr == pfnGetThrottleTime )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<xet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetThrottleTime( hFrequency, pThrottleTime );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGet
    xe_result_t __xecall
    xetSysmanEngineGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnEngineGet = dditable->xet.Sysman.pfnEngineGet;
        if( nullptr == pfnEngineGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEngineGet( hSysman, pCount, phEngine );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<xet_sysman_engine_handle_t>(
                    xet_sysman_engine_factory.getInstance( phEngine[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGetProperties
    xe_result_t __xecall
    xetSysmanEngineGetProperties(
        xet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        xet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_engine_object_t*>( hEngine )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanEngine.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<xet_sysman_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetProperties( hEngine, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGetActivity
    xe_result_t __xecall
    xetSysmanEngineGetActivity(
        xet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        xet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_engine_object_t*>( hEngine )->dditable;
        auto pfnGetActivity = dditable->xet.SysmanEngine.pfnGetActivity;
        if( nullptr == pfnGetActivity )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<xet_sysman_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetActivity( hEngine, pStats );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGet
    xe_result_t __xecall
    xetSysmanStandbyGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnStandbyGet = dditable->xet.Sysman.pfnStandbyGet;
        if( nullptr == pfnStandbyGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnStandbyGet( hSysman, pCount, phStandby );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<xet_sysman_standby_handle_t>(
                    xet_sysman_standby_factory.getInstance( phStandby[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetProperties
    xe_result_t __xecall
    xetSysmanStandbyGetProperties(
        xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        xet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanStandby.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<xet_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetProperties( hStandby, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetMode
    xe_result_t __xecall
    xetSysmanStandbyGetMode(
        xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        xet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnGetMode = dditable->xet.SysmanStandby.pfnGetMode;
        if( nullptr == pfnGetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<xet_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetMode( hStandby, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbySetMode
    xe_result_t __xecall
    xetSysmanStandbySetMode(
        xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        xet_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnSetMode = dditable->xet.SysmanStandby.pfnSetMode;
        if( nullptr == pfnSetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<xet_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnSetMode( hStandby, mode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGet
    xe_result_t __xecall
    xetSysmanFirmwareGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFirmwareGet = dditable->xet.Sysman.pfnFirmwareGet;
        if( nullptr == pfnFirmwareGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFirmwareGet( hSysman, pCount, phFirmware );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<xet_sysman_firmware_handle_t>(
                    xet_sysman_firmware_factory.getInstance( phFirmware[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetProperties
    xe_result_t __xecall
    xetSysmanFirmwareGetProperties(
        xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        xet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanFirmware.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<xet_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFirmware, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetChecksum
    xe_result_t __xecall
    xetSysmanFirmwareGetChecksum(
        xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetChecksum = dditable->xet.SysmanFirmware.pfnGetChecksum;
        if( nullptr == pfnGetChecksum )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<xet_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetChecksum( hFirmware, pChecksum );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareFlash
    xe_result_t __xecall
    xetSysmanFirmwareFlash(
        xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnFlash = dditable->xet.SysmanFirmware.pfnFlash;
        if( nullptr == pfnFlash )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<xet_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnFlash( hFirmware, pImage, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGet
    xe_result_t __xecall
    xetSysmanMemoryGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnMemoryGet = dditable->xet.Sysman.pfnMemoryGet;
        if( nullptr == pfnMemoryGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnMemoryGet( hSysman, pCount, phMemory );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<xet_sysman_mem_handle_t>(
                    xet_sysman_mem_factory.getInstance( phMemory[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetProperties
    xe_result_t __xecall
    xetSysmanMemoryGetProperties(
        xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        xet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanMemory.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<xet_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMemory, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetBandwidth
    xe_result_t __xecall
    xetSysmanMemoryGetBandwidth(
        xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        xet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetBandwidth = dditable->xet.SysmanMemory.pfnGetBandwidth;
        if( nullptr == pfnGetBandwidth )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<xet_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetBandwidth( hMemory, pBandwidth );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetAllocated
    xe_result_t __xecall
    xetSysmanMemoryGetAllocated(
        xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        xet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetAllocated = dditable->xet.SysmanMemory.pfnGetAllocated;
        if( nullptr == pfnGetAllocated )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<xet_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetAllocated( hMemory, pAllocated );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchGet
    xe_result_t __xecall
    xetSysmanLinkSwitchGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_link_switch_handle_t* phSwitch       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnLinkSwitchGet = dditable->xet.Sysman.pfnLinkSwitchGet;
        if( nullptr == pfnLinkSwitchGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnLinkSwitchGet( hSysman, pCount, phSwitch );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phSwitch ) && ( i < *pCount ); ++i )
                phSwitch[ i ] = reinterpret_cast<xet_sysman_link_switch_handle_t>(
                    xet_sysman_link_switch_factory.getInstance( phSwitch[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchGetProperties
    xe_result_t __xecall
    xetSysmanLinkSwitchGetProperties(
        xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        xet_link_switch_properties_t* pProperties       ///< [in] Will contain the Switch properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSwitch )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanLinkSwitch.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSwitch = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSwitch )->handle;

        // forward to device-driver
        result = pfnGetProperties( hSwitch, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchGetState
    xe_result_t __xecall
    xetSysmanLinkSwitchGetState(
        xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        xet_link_switch_state_t* pState                 ///< [in] Will contain the current state of the switch (enabled/disabled).
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSwitch )->dditable;
        auto pfnGetState = dditable->xet.SysmanLinkSwitch.pfnGetState;
        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSwitch = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSwitch )->handle;

        // forward to device-driver
        result = pfnGetState( hSwitch, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchSetState
    xe_result_t __xecall
    xetSysmanLinkSwitchSetState(
        xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        xe_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSwitch )->dditable;
        auto pfnSetState = dditable->xet.SysmanLinkSwitch.pfnSetState;
        if( nullptr == pfnSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSwitch = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSwitch )->handle;

        // forward to device-driver
        result = pfnSetState( hSwitch, enable );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchGetPorts
    xe_result_t __xecall
    xetSysmanLinkSwitchGetPorts(
        xet_sysman_link_switch_handle_t hSysmanLinkSwitch,  ///< [in] SMI handle of the connectivity switch.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_link_port_handle_t* phPort           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSysmanLinkSwitch )->dditable;
        auto pfnGetPorts = dditable->xet.SysmanLinkSwitch.pfnGetPorts;
        if( nullptr == pfnGetPorts )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysmanLinkSwitch = reinterpret_cast<xet_sysman_link_switch_object_t*>( hSysmanLinkSwitch )->handle;

        // forward to device-driver
        result = pfnGetPorts( hSysmanLinkSwitch, pCount, phPort );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<xet_sysman_link_port_handle_t>(
                    xet_sysman_link_port_factory.getInstance( phPort[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetProperties
    xe_result_t __xecall
    xetSysmanLinkPortGetProperties(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_properties_t* pProperties         ///< [in] Will contain properties of the Switch Port
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanLinkPort.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPort, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetState
    xe_result_t __xecall
    xetSysmanLinkPortGetState(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_state_t* pState                   ///< [in] Will contain the current state of the Switch Port
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->dditable;
        auto pfnGetState = dditable->xet.SysmanLinkPort.pfnGetState;
        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetState( hPort, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetThroughput
    xe_result_t __xecall
    xetSysmanLinkPortGetThroughput(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_throughput_t* pThroughput         ///< [in] Will contain the Switch port throughput counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->dditable;
        auto pfnGetThroughput = dditable->xet.SysmanLinkPort.pfnGetThroughput;
        if( nullptr == pfnGetThroughput )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetThroughput( hPort, pThroughput );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetStats
    xe_result_t __xecall
    xetSysmanLinkPortGetStats(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_stats_t* pStats                   ///< [in] Will contain the Switch port stats.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->dditable;
        auto pfnGetStats = dditable->xet.SysmanLinkPort.pfnGetStats;
        if( nullptr == pfnGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetStats( hPort, pStats );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortIsConnected
    xe_result_t __xecall
    xetSysmanLinkPortIsConnected(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle of the local connectivity port.
        xet_sysman_link_port_handle_t hRemotePort,      ///< [in] Handle of the remote connectivity port.
        xe_bool_t* pConnected                           ///< [in] Will indicate connected to the remote port.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->dditable;
        auto pfnIsConnected = dditable->xet.SysmanLinkPort.pfnIsConnected;
        if( nullptr == pfnIsConnected )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<xet_sysman_link_port_object_t*>( hPort )->handle;

        // convert loader handle to driver handle
        hRemotePort = reinterpret_cast<xet_sysman_link_port_object_t*>( hRemotePort )->handle;

        // forward to device-driver
        result = pfnIsConnected( hPort, hRemotePort, pConnected );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureGet
    xe_result_t __xecall
    xetSysmanTemperatureGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
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
        result = pfnTemperatureGet( hSysman, pCount, phTemperature );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<xet_sysman_temp_handle_t>(
                    xet_sysman_temp_factory.getInstance( phTemperature[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureGetProperties
    xe_result_t __xecall
    xetSysmanTemperatureGetProperties(
        xet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        xet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanTemperature.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<xet_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetProperties( hTemperature, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureRead
    xe_result_t __xecall
    xetSysmanTemperatureRead(
        xet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnRead = dditable->xet.SysmanTemperature.pfnRead;
        if( nullptr == pfnRead )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<xet_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnRead( hTemperature, pTemperature );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGet
    xe_result_t __xecall
    xetSysmanPsuGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPsuGet = dditable->xet.Sysman.pfnPsuGet;
        if( nullptr == pfnPsuGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPsuGet( hSysman, pCount, phPsu );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<xet_sysman_psu_handle_t>(
                    xet_sysman_psu_factory.getInstance( phPsu[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetProperties
    xe_result_t __xecall
    xetSysmanPsuGetProperties(
        xet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        xet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_psu_object_t*>( hPsu )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanPsu.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<xet_sysman_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPsu, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetState
    xe_result_t __xecall
    xetSysmanPsuGetState(
        xet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        xet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_psu_object_t*>( hPsu )->dditable;
        auto pfnGetState = dditable->xet.SysmanPsu.pfnGetState;
        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<xet_sysman_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetState( hPsu, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGet
    xe_result_t __xecall
    xetSysmanFanGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFanGet = dditable->xet.Sysman.pfnFanGet;
        if( nullptr == pfnFanGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFanGet( hSysman, pCount, phFan );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<xet_sysman_fan_handle_t>(
                    xet_sysman_fan_factory.getInstance( phFan[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetProperties
    xe_result_t __xecall
    xetSysmanFanGetProperties(
        xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        xet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanFan.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFan, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetConfig
    xe_result_t __xecall
    xetSysmanFanGetConfig(
        xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        xet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetConfig = dditable->xet.SysmanFan.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetConfig( hFan, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanSetConfig
    xe_result_t __xecall
    xetSysmanFanSetConfig(
        xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const xet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnSetConfig = dditable->xet.SysmanFan.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnSetConfig( hFan, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetState
    xe_result_t __xecall
    xetSysmanFanGetState(
        xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        xet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        xet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetState = dditable->xet.SysmanFan.pfnGetState;
        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<xet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetState( hFan, units, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGet
    xe_result_t __xecall
    xetSysmanLedGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnLedGet = dditable->xet.Sysman.pfnLedGet;
        if( nullptr == pfnLedGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnLedGet( hSysman, pCount, phLed );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<xet_sysman_led_handle_t>(
                    xet_sysman_led_factory.getInstance( phLed[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetProperties
    xe_result_t __xecall
    xetSysmanLedGetProperties(
        xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        xet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_led_object_t*>( hLed )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanLed.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<xet_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetProperties( hLed, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetState
    xe_result_t __xecall
    xetSysmanLedGetState(
        xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        xet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_led_object_t*>( hLed )->dditable;
        auto pfnGetState = dditable->xet.SysmanLed.pfnGetState;
        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<xet_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetState( hLed, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedSetState
    xe_result_t __xecall
    xetSysmanLedSetState(
        xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const xet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_led_object_t*>( hLed )->dditable;
        auto pfnSetState = dditable->xet.SysmanLed.pfnSetState;
        if( nullptr == pfnSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<xet_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnSetState( hLed, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGet
    xe_result_t __xecall
    xetSysmanRasGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnRasGet = dditable->xet.Sysman.pfnRasGet;
        if( nullptr == pfnRasGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRasGet( hSysman, pCount, phRas );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<xet_sysman_ras_handle_t>(
                    xet_sysman_ras_factory.getInstance( phRas[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetProperties
    xe_result_t __xecall
    xetSysmanRasGetProperties(
        xet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        xet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanRas.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<xet_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetProperties( hRas, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetErrors
    xe_result_t __xecall
    xetSysmanRasGetErrors(
        xet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        xe_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
        xet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetErrors = dditable->xet.SysmanRas.pfnGetErrors;
        if( nullptr == pfnGetErrors )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<xet_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetErrors( hRas, clear, pTotalErrors, pDetails );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEventsGetProperties
    xe_result_t __xecall
    xetSysmanEventsGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_event_properties_t* pProperties             ///< [in] Structure describing event properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnEventsGetProperties = dditable->xet.Sysman.pfnEventsGetProperties;
        if( nullptr == pfnEventsGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEventsGetProperties( hSysman, pProperties );

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
    /// @brief Intercept function for xetSysmanDiagnosticsGet
    xe_result_t __xecall
    xetSysmanDiagnosticsGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        xet_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDiagnosticsGet = dditable->xet.Sysman.pfnDiagnosticsGet;
        if( nullptr == pfnDiagnosticsGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<xet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<xet_sysman_diag_handle_t>(
                    xet_sysman_diag_factory.getInstance( phDiagnostics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsGetProperties
    xe_result_t __xecall
    xetSysmanDiagnosticsGetProperties(
        xet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        xet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetProperties = dditable->xet.SysmanDiagnostics.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<xet_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDiagnostics, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsRunTests
    xe_result_t __xecall
    xetSysmanDiagnosticsRunTests(
        xet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        xet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnRunTests = dditable->xet.SysmanDiagnostics.pfnRunTests;
        if( nullptr == pfnRunTests )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<xet_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnRunTests( hDiagnostics, start, end, pResult );

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
            pDdiTable->pfnSchedulerGetCurrentMode                  = loader::xetSysmanSchedulerGetCurrentMode;
            pDdiTable->pfnSchedulerGetTimeoutModeProperties        = loader::xetSysmanSchedulerGetTimeoutModeProperties;
            pDdiTable->pfnSchedulerGetTimesliceModeProperties      = loader::xetSysmanSchedulerGetTimesliceModeProperties;
            pDdiTable->pfnSchedulerSetTimeoutMode                  = loader::xetSysmanSchedulerSetTimeoutMode;
            pDdiTable->pfnSchedulerSetTimesliceMode                = loader::xetSysmanSchedulerSetTimesliceMode;
            pDdiTable->pfnSchedulerSetExclusiveMode                = loader::xetSysmanSchedulerSetExclusiveMode;
            pDdiTable->pfnSchedulerSetSingleCmdQueueMode           = loader::xetSysmanSchedulerSetSingleCmdQueueMode;
            pDdiTable->pfnDeviceReset                              = loader::xetSysmanDeviceReset;
            pDdiTable->pfnDeviceWasRepaired                        = loader::xetSysmanDeviceWasRepaired;
            pDdiTable->pfnPciGetProperties                         = loader::xetSysmanPciGetProperties;
            pDdiTable->pfnPciGetState                              = loader::xetSysmanPciGetState;
            pDdiTable->pfnPciGetBarProperties                      = loader::xetSysmanPciGetBarProperties;
            pDdiTable->pfnPciGetThroughput                         = loader::xetSysmanPciGetThroughput;
            pDdiTable->pfnPciGetStats                              = loader::xetSysmanPciGetStats;
            pDdiTable->pfnPowerGet                                 = loader::xetSysmanPowerGet;
            pDdiTable->pfnFrequencyGet                             = loader::xetSysmanFrequencyGet;
            pDdiTable->pfnEngineGet                                = loader::xetSysmanEngineGet;
            pDdiTable->pfnStandbyGet                               = loader::xetSysmanStandbyGet;
            pDdiTable->pfnFirmwareGet                              = loader::xetSysmanFirmwareGet;
            pDdiTable->pfnMemoryGet                                = loader::xetSysmanMemoryGet;
            pDdiTable->pfnLinkSwitchGet                            = loader::xetSysmanLinkSwitchGet;
            pDdiTable->pfnTemperatureGet                           = loader::xetSysmanTemperatureGet;
            pDdiTable->pfnPsuGet                                   = loader::xetSysmanPsuGet;
            pDdiTable->pfnFanGet                                   = loader::xetSysmanFanGet;
            pDdiTable->pfnLedGet                                   = loader::xetSysmanLedGet;
            pDdiTable->pfnRasGet                                   = loader::xetSysmanRasGet;
            pDdiTable->pfnEventsGetProperties                      = loader::xetSysmanEventsGetProperties;
            pDdiTable->pfnEventsRegister                           = loader::xetSysmanEventsRegister;
            pDdiTable->pfnEventsUnregister                         = loader::xetSysmanEventsUnregister;
            pDdiTable->pfnEventsListen                             = loader::xetSysmanEventsListen;
            pDdiTable->pfnDiagnosticsGet                           = loader::xetSysmanDiagnosticsGet;
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
/// @brief Exported function for filling application's SysmanPower table
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
xetGetSysmanPowerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanPowerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanPowerProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanPower );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanPowerGetProperties;
            pDdiTable->pfnGetEnergyCounter                         = loader::xetSysmanPowerGetEnergyCounter;
            pDdiTable->pfnGetEnergyThreshold                       = loader::xetSysmanPowerGetEnergyThreshold;
            pDdiTable->pfnSetEnergyThreshold                       = loader::xetSysmanPowerSetEnergyThreshold;
            pDdiTable->pfnGetLimits                                = loader::xetSysmanPowerGetLimits;
            pDdiTable->pfnSetLimits                                = loader::xetSysmanPowerSetLimits;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanPower;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanPowerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
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
xetGetSysmanFrequencyProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanFrequencyProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanFrequency );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnSetFanSpeed                              = loader::xetSysmanFrequencySetFanSpeed;
            pDdiTable->pfnGetOcCapabilities                        = loader::xetSysmanFrequencyGetOcCapabilities;
            pDdiTable->pfnGetOcVrTopology                          = loader::xetSysmanFrequencyGetOcVrTopology;
            pDdiTable->pfnGetOcOverrideProperties                  = loader::xetSysmanFrequencyGetOcOverrideProperties;
            pDdiTable->pfnGetOcIccMax                              = loader::xetSysmanFrequencyGetOcIccMax;
            pDdiTable->pfnGetOcTjMax                               = loader::xetSysmanFrequencyGetOcTjMax;
            pDdiTable->pfnSetOcOverrideProperties                  = loader::xetSysmanFrequencySetOcOverrideProperties;
            pDdiTable->pfnSetOcIccMax                              = loader::xetSysmanFrequencySetOcIccMax;
            pDdiTable->pfnSetOcTjMax                               = loader::xetSysmanFrequencySetOcTjMax;
            pDdiTable->pfnGetProperties                            = loader::xetSysmanFrequencyGetProperties;
            pDdiTable->pfnGetRange                                 = loader::xetSysmanFrequencyGetRange;
            pDdiTable->pfnSetRange                                 = loader::xetSysmanFrequencySetRange;
            pDdiTable->pfnGetState                                 = loader::xetSysmanFrequencyGetState;
            pDdiTable->pfnGetThrottleTime                          = loader::xetSysmanFrequencyGetThrottleTime;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanFrequency;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanFrequencyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanFrequencyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
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
xetGetSysmanEngineProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanEngineProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanEngineProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanEngine );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanEngineGetProperties;
            pDdiTable->pfnGetActivity                              = loader::xetSysmanEngineGetActivity;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanEngine;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanEngineProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanEngineProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
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
xetGetSysmanStandbyProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanStandbyProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanStandby );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanStandbyGetProperties;
            pDdiTable->pfnGetMode                                  = loader::xetSysmanStandbyGetMode;
            pDdiTable->pfnSetMode                                  = loader::xetSysmanStandbySetMode;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanStandby;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanStandbyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanStandbyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
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
xetGetSysmanFirmwareProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanFirmwareProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanFirmware );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanFirmwareGetProperties;
            pDdiTable->pfnGetChecksum                              = loader::xetSysmanFirmwareGetChecksum;
            pDdiTable->pfnFlash                                    = loader::xetSysmanFirmwareFlash;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanFirmware;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanFirmwareProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanFirmwareProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
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
xetGetSysmanMemoryProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanMemoryProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanMemory );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanMemoryGetProperties;
            pDdiTable->pfnGetBandwidth                             = loader::xetSysmanMemoryGetBandwidth;
            pDdiTable->pfnGetAllocated                             = loader::xetSysmanMemoryGetAllocated;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanMemory;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanMemoryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanMemoryProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLinkSwitch table
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
xetGetSysmanLinkSwitchProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_link_switch_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanLinkSwitchProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanLinkSwitchProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanLinkSwitch );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanLinkSwitchGetProperties;
            pDdiTable->pfnGetState                                 = loader::xetSysmanLinkSwitchGetState;
            pDdiTable->pfnSetState                                 = loader::xetSysmanLinkSwitchSetState;
            pDdiTable->pfnGetPorts                                 = loader::xetSysmanLinkSwitchGetPorts;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanLinkSwitch;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanLinkSwitchProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanLinkSwitchProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLinkPort table
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
xetGetSysmanLinkPortProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_link_port_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanLinkPortProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanLinkPortProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanLinkPort );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanLinkPortGetProperties;
            pDdiTable->pfnGetState                                 = loader::xetSysmanLinkPortGetState;
            pDdiTable->pfnGetThroughput                            = loader::xetSysmanLinkPortGetThroughput;
            pDdiTable->pfnGetStats                                 = loader::xetSysmanLinkPortGetStats;
            pDdiTable->pfnIsConnected                              = loader::xetSysmanLinkPortIsConnected;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanLinkPort;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanLinkPortProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanLinkPortProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
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
xetGetSysmanTemperatureProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanTemperatureProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanTemperature );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanTemperatureGetProperties;
            pDdiTable->pfnRead                                     = loader::xetSysmanTemperatureRead;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanTemperature;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanTemperatureProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanTemperatureProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
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
xetGetSysmanPsuProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanPsuProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanPsuProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanPsu );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanPsuGetProperties;
            pDdiTable->pfnGetState                                 = loader::xetSysmanPsuGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanPsu;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanPsuProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanPsuProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
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
xetGetSysmanFanProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanFanProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanFanProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanFan );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanFanGetProperties;
            pDdiTable->pfnGetConfig                                = loader::xetSysmanFanGetConfig;
            pDdiTable->pfnSetConfig                                = loader::xetSysmanFanSetConfig;
            pDdiTable->pfnGetState                                 = loader::xetSysmanFanGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanFan;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanFanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanFanProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
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
xetGetSysmanLedProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanLedProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanLedProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanLed );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanLedGetProperties;
            pDdiTable->pfnGetState                                 = loader::xetSysmanLedGetState;
            pDdiTable->pfnSetState                                 = loader::xetSysmanLedSetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanLed;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanLedProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanLedProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
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
xetGetSysmanRasProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanRasProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanRasProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanRas );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanRasGetProperties;
            pDdiTable->pfnGetErrors                                = loader::xetSysmanRasGetErrors;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanRas;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanRasProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanRasProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
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
xetGetSysmanDiagnosticsProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetSysmanDiagnosticsProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.SysmanDiagnostics );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xetSysmanDiagnosticsGetProperties;
            pDdiTable->pfnRunTests                                 = loader::xetSysmanDiagnosticsRunTests;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.SysmanDiagnostics;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xet_pfnGetSysmanDiagnosticsProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetSysmanDiagnosticsProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
