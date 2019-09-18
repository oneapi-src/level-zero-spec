/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_tools_layer.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/valddi.cpp.mako
 * @endcond
 *
 */
#include "xe_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetInit
    xe_result_t __xecall
    xetInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        auto pfnInit = context.xetDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
        }

        return pfnInit( flags );
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
        auto pfnGet = context.xetDdiTable.MetricGroup.pfnGet;

        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hDevice, pCount, phMetricGroups );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGroupGetProperties
    xe_result_t __xecall
    xetMetricGroupGetProperties(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        xet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        auto pfnGetProperties = context.xetDdiTable.MetricGroup.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hMetricGroup, pProperties );
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
        auto pfnCalculateMetricValues = context.xetDdiTable.MetricGroup.pfnCalculateMetricValues;

        if( nullptr == pfnCalculateMetricValues )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRawData )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMetricValueCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
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
        auto pfnGet = context.xetDdiTable.Metric.pfnGet;

        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hMetricGroup, pCount, phMetrics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGetProperties
    xe_result_t __xecall
    xetMetricGetProperties(
        xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        xet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        auto pfnGetProperties = context.xetDdiTable.Metric.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetric )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hMetric, pProperties );
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
        auto pfnActivateMetricGroups = context.xetDdiTable.Device.pfnActivateMetricGroups;

        if( nullptr == pfnActivateMetricGroups )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnActivateMetricGroups( hDevice, count, phMetricGroups );
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
        auto pfnOpen = context.xetDdiTable.MetricTracer.pfnOpen;

        if( nullptr == pfnOpen )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phMetricTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XET_METRIC_TRACER_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
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
        auto pfnAppendMetricTracerMarker = context.xetDdiTable.CommandList.pfnAppendMetricTracerMarker;

        if( nullptr == pfnAppendMetricTracerMarker )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricTracerClose
    xe_result_t __xecall
    xetMetricTracerClose(
        xet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
        )
    {
        auto pfnClose = context.xetDdiTable.MetricTracer.pfnClose;

        if( nullptr == pfnClose )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnClose( hMetricTracer );
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
        auto pfnReadData = context.xetDdiTable.MetricTracer.pfnReadData;

        if( nullptr == pfnReadData )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRawDataSize )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );
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
        auto pfnCreate = context.xetDdiTable.MetricQueryPool.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phMetricQueryPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryPoolDestroy
    xe_result_t __xecall
    xetMetricQueryPoolDestroy(
        xet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        auto pfnDestroy = context.xetDdiTable.MetricQueryPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hMetricQueryPool );
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
        auto pfnCreate = context.xetDdiTable.MetricQuery.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phMetricQuery )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCreate( hMetricQueryPool, index, phMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryDestroy
    xe_result_t __xecall
    xetMetricQueryDestroy(
        xet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        auto pfnDestroy = context.xetDdiTable.MetricQuery.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryReset
    xe_result_t __xecall
    xetMetricQueryReset(
        xet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        auto pfnReset = context.xetDdiTable.MetricQuery.pfnReset;

        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReset( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricQueryBegin
    xe_result_t __xecall
    xetCommandListAppendMetricQueryBegin(
        xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        auto pfnAppendMetricQueryBegin = context.xetDdiTable.CommandList.pfnAppendMetricQueryBegin;

        if( nullptr == pfnAppendMetricQueryBegin )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricQuery )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
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
        auto pfnAppendMetricQueryEnd = context.xetDdiTable.CommandList.pfnAppendMetricQueryEnd;

        if( nullptr == pfnAppendMetricQueryEnd )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricQuery )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricMemoryBarrier
    xe_result_t __xecall
    xetCommandListAppendMetricMemoryBarrier(
        xet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        auto pfnAppendMetricMemoryBarrier = context.xetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;

        if( nullptr == pfnAppendMetricMemoryBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricMemoryBarrier( hCommandList );
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
        auto pfnGetData = context.xetDdiTable.MetricQuery.pfnGetData;

        if( nullptr == pfnGetData )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRawDataSize )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
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
        auto pfnGetDebugInfo = context.xetDdiTable.Module.pfnGetDebugInfo;

        if( nullptr == pfnGetDebugInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pSize )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
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
        auto pfnGetFunctionNames = context.xetDdiTable.Module.pfnGetFunctionNames;

        if( nullptr == pfnGetFunctionNames )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFunctionNames( hModule, pCount, pNames );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFunctionGetProfileInfo
    xe_result_t __xecall
    xetFunctionGetProfileInfo(
        xet_function_handle_t hFunction,                ///< [in] handle to function
        xet_profile_info_t* pInfo                       ///< [out] pointer to profile info
        )
    {
        auto pfnGetProfileInfo = context.xetDdiTable.Function.pfnGetProfileInfo;

        if( nullptr == pfnGetProfileInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pInfo )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProfileInfo( hFunction, pInfo );
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
        auto pfnGet = context.xetDdiTable.Sysman.pfnGet;

        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hDevice, version, phSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceGetProperties
    xe_result_t __xecall
    xetSysmanDeviceGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
        )
    {
        auto pfnDeviceGetProperties = context.xetDdiTable.Sysman.pfnDeviceGetProperties;

        if( nullptr == pfnDeviceGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceGetGuardTimeout
    xe_result_t __xecall
    xetSysmanDeviceGetGuardTimeout(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pTimeout                              ///< [in] Returns the guard timeout in milliseconds (a value of
                                                        ///< ::XET_DISABLE_GUARD_TIMEOUT indicates that the guard timeout is
                                                        ///< disabled).
        )
    {
        auto pfnDeviceGetGuardTimeout = context.xetDdiTable.Sysman.pfnDeviceGetGuardTimeout;

        if( nullptr == pfnDeviceGetGuardTimeout )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTimeout )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceGetGuardTimeout( hSysman, pTimeout );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceSetGuardTimeout
    xe_result_t __xecall
    xetSysmanDeviceSetGuardTimeout(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t timeout                                ///< [in] The timeout in milliseconds or ::XET_DISABLE_GUARD_TIMEOUT to
                                                        ///< disable the timeout.
        )
    {
        auto pfnDeviceSetGuardTimeout = context.xetDdiTable.Sysman.pfnDeviceSetGuardTimeout;

        if( nullptr == pfnDeviceSetGuardTimeout )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceSetGuardTimeout( hSysman, timeout );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceReset
    xe_result_t __xecall
    xetSysmanDeviceReset(
        xet_sysman_handle_t hSysman                     ///< [in] SMI handle for the device
        )
    {
        auto pfnDeviceReset = context.xetDdiTable.Sysman.pfnDeviceReset;

        if( nullptr == pfnDeviceReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceReset( hSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceWasRepaired
    xe_result_t __xecall
    xetSysmanDeviceWasRepaired(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        xe_bool_t* pWasRepaired                         ///< [in] Will indicate if the device was repaired
        )
    {
        auto pfnDeviceWasRepaired = context.xetDdiTable.Sysman.pfnDeviceWasRepaired;

        if( nullptr == pfnDeviceWasRepaired )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pWasRepaired )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceWasRepaired( hSysman, pWasRepaired );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetProperties
    xe_result_t __xecall
    xetSysmanPciGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
        )
    {
        auto pfnPciGetProperties = context.xetDdiTable.Sysman.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetState
    xe_result_t __xecall
    xetSysmanPciGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
        )
    {
        auto pfnPciGetState = context.xetDdiTable.Sysman.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetState( hSysman, pState );
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
        auto pfnPciGetBarProperties = context.xetDdiTable.Sysman.pfnPciGetBarProperties;

        if( nullptr == pfnPciGetBarProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetBarProperties( hSysman, barIndex, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetThroughput
    xe_result_t __xecall
    xetSysmanPciGetThroughput(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_throughput_t* pThroughput               ///< [in] Will contain a snapshot of the latest throughput counters.
        )
    {
        auto pfnPciGetThroughput = context.xetDdiTable.Sysman.pfnPciGetThroughput;

        if( nullptr == pfnPciGetThroughput )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThroughput )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetThroughput( hSysman, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetStats
    xe_result_t __xecall
    xetSysmanPciGetStats(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        auto pfnPciGetStats = context.xetDdiTable.Sysman.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetStats( hSysman, pStats );
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
        auto pfnPowerGet = context.xetDdiTable.Sysman.pfnPowerGet;

        if( nullptr == pfnPowerGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPowerGet( hSysman, pCount, phPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetProperties
    xe_result_t __xecall
    xetSysmanPowerGetProperties(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanPower.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hPower, pProperties );
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
        auto pfnGetEnergyCounter = context.xetDdiTable.SysmanPower.pfnGetEnergyCounter;

        if( nullptr == pfnGetEnergyCounter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEnergy )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetEnergyCounter( hPower, pEnergy );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerGetEnergyThreshold(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_energy_threshold_t* pThreshold        ///< [out] The current energy threshold value in joules.
        )
    {
        auto pfnGetEnergyThreshold = context.xetDdiTable.SysmanPower.pfnGetEnergyThreshold;

        if( nullptr == pfnGetEnergyThreshold )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThreshold )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetEnergyThreshold( hPower, pThreshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerSetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerSetEnergyThreshold(
        xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        xet_power_energy_threshold_t* pThreshold        ///< [in] The energy threshold to be set in joules.
        )
    {
        auto pfnSetEnergyThreshold = context.xetDdiTable.SysmanPower.pfnSetEnergyThreshold;

        if( nullptr == pfnSetEnergyThreshold )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThreshold )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetEnergyThreshold( hPower, pThreshold );
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
        auto pfnGetLimits = context.xetDdiTable.SysmanPower.pfnGetLimits;

        if( nullptr == pfnGetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
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
        auto pfnSetLimits = context.xetDdiTable.SysmanPower.pfnSetLimits;

        if( nullptr == pfnSetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetFanSpeed
    xe_result_t __xecall
    xetSysmanFrequencySetFanSpeed(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_fan_control_t* pFanControl               ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnSetFanSpeed = context.xetDdiTable.SysmanFrequency.pfnSetFanSpeed;

        if( nullptr == pfnSetFanSpeed )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanControl )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFanSpeed( hFrequency, pFanControl );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcCapabilities
    xe_result_t __xecall
    xetSysmanFrequencyGetOcCapabilities(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_capabilities_t* pOcCapabilities          ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnGetOcCapabilities = context.xetDdiTable.SysmanFrequency.pfnGetOcCapabilities;

        if( nullptr == pfnGetOcCapabilities )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcCapabilities )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcCapabilities( hFrequency, pOcCapabilities );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcVrTopology
    xe_result_t __xecall
    xetSysmanFrequencyGetOcVrTopology(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_vr_topology* pOcVrTopology               ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnGetOcVrTopology = context.xetDdiTable.SysmanFrequency.pfnGetOcVrTopology;

        if( nullptr == pfnGetOcVrTopology )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcVrTopology )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcVrTopology( hFrequency, pOcVrTopology );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcOverrideProperties
    xe_result_t __xecall
    xetSysmanFrequencyGetOcOverrideProperties(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_settings_override_t* pOcSettingsOverride ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnGetOcOverrideProperties = context.xetDdiTable.SysmanFrequency.pfnGetOcOverrideProperties;

        if( nullptr == pfnGetOcOverrideProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcSettingsOverride )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcOverrideProperties( hFrequency, pOcSettingsOverride );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcIccMax
    xe_result_t __xecall
    xetSysmanFrequencyGetOcIccMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcIccMax                             ///< [out] Pointer to the allocated uint32.
        )
    {
        auto pfnGetOcIccMax = context.xetDdiTable.SysmanFrequency.pfnGetOcIccMax;

        if( nullptr == pfnGetOcIccMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcIccMax )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcIccMax( hFrequency, pOcIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetOcTjMax
    xe_result_t __xecall
    xetSysmanFrequencyGetOcTjMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcTjMax                              ///< [out] Pointer to the allocated uint32.
        )
    {
        auto pfnGetOcTjMax = context.xetDdiTable.SysmanFrequency.pfnGetOcTjMax;

        if( nullptr == pfnGetOcTjMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcTjMax )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcTjMax( hFrequency, pOcTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetOcOverrideProperties
    xe_result_t __xecall
    xetSysmanFrequencySetOcOverrideProperties(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_oc_settings_override_t* pOcSettingsOverride ///< [in] Pointer to the allocated structure.
        )
    {
        auto pfnSetOcOverrideProperties = context.xetDdiTable.SysmanFrequency.pfnSetOcOverrideProperties;

        if( nullptr == pfnSetOcOverrideProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcSettingsOverride )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetOcOverrideProperties( hFrequency, pOcSettingsOverride );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetOcIccMax
    xe_result_t __xecall
    xetSysmanFrequencySetOcIccMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcIccMax                             ///< [in] Pointer to the allocated uint32.
        )
    {
        auto pfnSetOcIccMax = context.xetDdiTable.SysmanFrequency.pfnSetOcIccMax;

        if( nullptr == pfnSetOcIccMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcIccMax )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetOcIccMax( hFrequency, pOcIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetOcTjMax
    xe_result_t __xecall
    xetSysmanFrequencySetOcTjMax(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcTjMax                              ///< [in] Pointer to the allocated uint32.
        )
    {
        auto pfnSetOcTjMax = context.xetDdiTable.SysmanFrequency.pfnSetOcTjMax;

        if( nullptr == pfnSetOcTjMax )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcTjMax )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetOcTjMax( hFrequency, pOcTjMax );
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
        auto pfnFrequencyGet = context.xetDdiTable.Sysman.pfnFrequencyGet;

        if( nullptr == pfnFrequencyGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFrequencyGet( hSysman, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetProperties
    xe_result_t __xecall
    xetSysmanFrequencyGetProperties(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanFrequency.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hFrequency, pProperties );
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
        auto pfnGetRange = context.xetDdiTable.SysmanFrequency.pfnGetRange;

        if( nullptr == pfnGetRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetRange( hFrequency, pLimits );
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
        auto pfnSetRange = context.xetDdiTable.SysmanFrequency.pfnSetRange;

        if( nullptr == pfnSetRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetState
    xe_result_t __xecall
    xetSysmanFrequencyGetState(
        xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        xet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        auto pfnGetState = context.xetDdiTable.SysmanFrequency.pfnGetState;

        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hFrequency, pState );
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
        auto pfnGetThrottleTime = context.xetDdiTable.SysmanFrequency.pfnGetThrottleTime;

        if( nullptr == pfnGetThrottleTime )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThrottleTime )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetThrottleTime( hFrequency, pThrottleTime );
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
        auto pfnEngineGet = context.xetDdiTable.Sysman.pfnEngineGet;

        if( nullptr == pfnEngineGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEngineGet( hSysman, pCount, phEngine );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGetProperties
    xe_result_t __xecall
    xetSysmanEngineGetProperties(
        xet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        xet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanEngine.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hEngine, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGetActivity
    xe_result_t __xecall
    xetSysmanEngineGetActivity(
        xet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        xet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        auto pfnGetActivity = context.xetDdiTable.SysmanEngine.pfnGetActivity;

        if( nullptr == pfnGetActivity )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetActivity( hEngine, pStats );
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
        auto pfnStandbyGet = context.xetDdiTable.Sysman.pfnStandbyGet;

        if( nullptr == pfnStandbyGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnStandbyGet( hSysman, pCount, phStandby );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetProperties
    xe_result_t __xecall
    xetSysmanStandbyGetProperties(
        xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        xet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanStandby.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hStandby, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetMode
    xe_result_t __xecall
    xetSysmanStandbyGetMode(
        xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        xet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
        )
    {
        auto pfnGetMode = context.xetDdiTable.SysmanStandby.pfnGetMode;

        if( nullptr == pfnGetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMode )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMode( hStandby, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbySetMode
    xe_result_t __xecall
    xetSysmanStandbySetMode(
        xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        xet_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        auto pfnSetMode = context.xetDdiTable.SysmanStandby.pfnSetMode;

        if( nullptr == pfnSetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetMode( hStandby, mode );
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
        auto pfnFirmwareGet = context.xetDdiTable.Sysman.pfnFirmwareGet;

        if( nullptr == pfnFirmwareGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFirmwareGet( hSysman, pCount, phFirmware );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetProperties
    xe_result_t __xecall
    xetSysmanFirmwareGetProperties(
        xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        xet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanFirmware.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hFirmware, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetChecksum
    xe_result_t __xecall
    xetSysmanFirmwareGetChecksum(
        xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        auto pfnGetChecksum = context.xetDdiTable.SysmanFirmware.pfnGetChecksum;

        if( nullptr == pfnGetChecksum )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pChecksum )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetChecksum( hFirmware, pChecksum );
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
        auto pfnFlash = context.xetDdiTable.SysmanFirmware.pfnFlash;

        if( nullptr == pfnFlash )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFlash( hFirmware, pImage, size );
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
        auto pfnMemoryGet = context.xetDdiTable.Sysman.pfnMemoryGet;

        if( nullptr == pfnMemoryGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnMemoryGet( hSysman, pCount, phMemory );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetProperties
    xe_result_t __xecall
    xetSysmanMemoryGetProperties(
        xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        xet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanMemory.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hMemory, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetBandwidth
    xe_result_t __xecall
    xetSysmanMemoryGetBandwidth(
        xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        xet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        auto pfnGetBandwidth = context.xetDdiTable.SysmanMemory.pfnGetBandwidth;

        if( nullptr == pfnGetBandwidth )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pBandwidth )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetBandwidth( hMemory, pBandwidth );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetAllocated
    xe_result_t __xecall
    xetSysmanMemoryGetAllocated(
        xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        xet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
        )
    {
        auto pfnGetAllocated = context.xetDdiTable.SysmanMemory.pfnGetAllocated;

        if( nullptr == pfnGetAllocated )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pAllocated )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAllocated( hMemory, pAllocated );
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
        auto pfnLinkSwitchGet = context.xetDdiTable.Sysman.pfnLinkSwitchGet;

        if( nullptr == pfnLinkSwitchGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnLinkSwitchGet( hSysman, pCount, phSwitch );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchGetProperties
    xe_result_t __xecall
    xetSysmanLinkSwitchGetProperties(
        xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        xet_link_switch_properties_t* pProperties       ///< [in] Will contain the Switch properties.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanLinkSwitch.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSwitch )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hSwitch, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchGetState
    xe_result_t __xecall
    xetSysmanLinkSwitchGetState(
        xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        xet_link_switch_state_t* pState                 ///< [in] Will contain the current state of the switch (enabled/disabled).
        )
    {
        auto pfnGetState = context.xetDdiTable.SysmanLinkSwitch.pfnGetState;

        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSwitch )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hSwitch, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkSwitchSetState
    xe_result_t __xecall
    xetSysmanLinkSwitchSetState(
        xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        xe_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
        )
    {
        auto pfnSetState = context.xetDdiTable.SysmanLinkSwitch.pfnSetState;

        if( nullptr == pfnSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSwitch )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetState( hSwitch, enable );
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
        auto pfnGetPorts = context.xetDdiTable.SysmanLinkSwitch.pfnGetPorts;

        if( nullptr == pfnGetPorts )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysmanLinkSwitch )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPorts( hSysmanLinkSwitch, pCount, phPort );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetProperties
    xe_result_t __xecall
    xetSysmanLinkPortGetProperties(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_properties_t* pProperties         ///< [in] Will contain properties of the Switch Port
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanLinkPort.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hPort, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetState
    xe_result_t __xecall
    xetSysmanLinkPortGetState(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_state_t* pState                   ///< [in] Will contain the current state of the Switch Port
        )
    {
        auto pfnGetState = context.xetDdiTable.SysmanLinkPort.pfnGetState;

        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hPort, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetThroughput
    xe_result_t __xecall
    xetSysmanLinkPortGetThroughput(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_throughput_t* pThroughput         ///< [in] Will contain the Switch port throughput counters.
        )
    {
        auto pfnGetThroughput = context.xetDdiTable.SysmanLinkPort.pfnGetThroughput;

        if( nullptr == pfnGetThroughput )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThroughput )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetThroughput( hPort, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLinkPortGetStats
    xe_result_t __xecall
    xetSysmanLinkPortGetStats(
        xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        xet_link_port_stats_t* pStats                   ///< [in] Will contain the Switch port stats.
        )
    {
        auto pfnGetStats = context.xetDdiTable.SysmanLinkPort.pfnGetStats;

        if( nullptr == pfnGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetStats( hPort, pStats );
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
        auto pfnIsConnected = context.xetDdiTable.SysmanLinkPort.pfnIsConnected;

        if( nullptr == pfnIsConnected )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hRemotePort )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConnected )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnIsConnected( hPort, hRemotePort, pConnected );
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
        auto pfnTemperatureGet = context.xetDdiTable.Sysman.pfnTemperatureGet;

        if( nullptr == pfnTemperatureGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnTemperatureGet( hSysman, pCount, phTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureGetProperties
    xe_result_t __xecall
    xetSysmanTemperatureGetProperties(
        xet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        xet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanTemperature.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hTemperature, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureRead
    xe_result_t __xecall
    xetSysmanTemperatureRead(
        xet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
        )
    {
        auto pfnRead = context.xetDdiTable.SysmanTemperature.pfnRead;

        if( nullptr == pfnRead )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTemperature )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRead( hTemperature, pTemperature );
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
        auto pfnPsuGet = context.xetDdiTable.Sysman.pfnPsuGet;

        if( nullptr == pfnPsuGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPsuGet( hSysman, pCount, phPsu );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetProperties
    xe_result_t __xecall
    xetSysmanPsuGetProperties(
        xet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        xet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanPsu.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hPsu, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetState
    xe_result_t __xecall
    xetSysmanPsuGetState(
        xet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        xet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        auto pfnGetState = context.xetDdiTable.SysmanPsu.pfnGetState;

        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hPsu, pState );
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
        auto pfnFanGet = context.xetDdiTable.Sysman.pfnFanGet;

        if( nullptr == pfnFanGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGet( hSysman, pCount, phFan );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetProperties
    xe_result_t __xecall
    xetSysmanFanGetProperties(
        xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        xet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanFan.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hFan, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetConfig
    xe_result_t __xecall
    xetSysmanFanGetConfig(
        xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        xet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        auto pfnGetConfig = context.xetDdiTable.SysmanFan.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanSetConfig
    xe_result_t __xecall
    xetSysmanFanSetConfig(
        xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const xet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        auto pfnSetConfig = context.xetDdiTable.SysmanFan.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetConfig( hFan, pConfig );
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
        auto pfnGetState = context.xetDdiTable.SysmanFan.pfnGetState;

        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hFan, units, pState );
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
        auto pfnLedGet = context.xetDdiTable.Sysman.pfnLedGet;

        if( nullptr == pfnLedGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnLedGet( hSysman, pCount, phLed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetProperties
    xe_result_t __xecall
    xetSysmanLedGetProperties(
        xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        xet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanLed.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hLed, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetState
    xe_result_t __xecall
    xetSysmanLedGetState(
        xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        xet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        auto pfnGetState = context.xetDdiTable.SysmanLed.pfnGetState;

        if( nullptr == pfnGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedSetState
    xe_result_t __xecall
    xetSysmanLedSetState(
        xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const xet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        auto pfnSetState = context.xetDdiTable.SysmanLed.pfnSetState;

        if( nullptr == pfnSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetState( hLed, pState );
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
        auto pfnRasGet = context.xetDdiTable.Sysman.pfnRasGet;

        if( nullptr == pfnRasGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRasGet( hSysman, pCount, phRas );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetProperties
    xe_result_t __xecall
    xetSysmanRasGetProperties(
        xet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        xet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanRas.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hRas, pProperties );
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
        auto pfnGetErrors = context.xetDdiTable.SysmanRas.pfnGetErrors;

        if( nullptr == pfnGetErrors )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTotalErrors )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetErrors( hRas, clear, pTotalErrors, pDetails );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEventsGetProperties
    xe_result_t __xecall
    xetSysmanEventsGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_event_properties_t* pProperties             ///< [in] Structure describing event properties
        )
    {
        auto pfnEventsGetProperties = context.xetDdiTable.Sysman.pfnEventsGetProperties;

        if( nullptr == pfnEventsGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsGetProperties( hSysman, pProperties );
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
        auto pfnEventsRegister = context.xetDdiTable.Sysman.pfnEventsRegister;

        if( nullptr == pfnEventsRegister )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsRegister( hSysman, count, pEvents );
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
        auto pfnEventsUnregister = context.xetDdiTable.Sysman.pfnEventsUnregister;

        if( nullptr == pfnEventsUnregister )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsUnregister( hSysman, count, pEvents );
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
        auto pfnEventsListen = context.xetDdiTable.Sysman.pfnEventsListen;

        if( nullptr == pfnEventsListen )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEvents )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsListen( hSysman, clear, timeout, pEvents );
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
        auto pfnDiagnosticsGet = context.xetDdiTable.Sysman.pfnDiagnosticsGet;

        if( nullptr == pfnDiagnosticsGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsGetProperties
    xe_result_t __xecall
    xetSysmanDiagnosticsGetProperties(
        xet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        xet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        auto pfnGetProperties = context.xetDdiTable.SysmanDiagnostics.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hDiagnostics, pProperties );
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
        auto pfnRunTests = context.xetDdiTable.SysmanDiagnostics.pfnRunTests;

        if( nullptr == pfnRunTests )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pResult )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRunTests( hDiagnostics, start, end, pResult );
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
        auto pfnCreate = context.xetDdiTable.Tracer.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XET_TRACER_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, desc, phTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerDestroy
    xe_result_t __xecall
    xetTracerDestroy(
        xet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
        )
    {
        auto pfnDestroy = context.xetDdiTable.Tracer.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hTracer );
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
        auto pfnSetPrologues = context.xetDdiTable.Tracer.pfnSetPrologues;

        if( nullptr == pfnSetPrologues )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCoreCbs )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPrologues( hTracer, pCoreCbs, pExperimentalCbs );
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
        auto pfnSetEpilogues = context.xetDdiTable.Tracer.pfnSetEpilogues;

        if( nullptr == pfnSetEpilogues )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCoreCbs )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetEpilogues( hTracer, pCoreCbs, pExperimentalCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerSetEnabled
    xe_result_t __xecall
    xetTracerSetEnabled(
        xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        xe_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        auto pfnSetEnabled = context.xetDdiTable.Tracer.pfnSetEnabled;

        if( nullptr == pfnSetEnabled )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetEnabled( hTracer, enable );
    }

} // namespace layer

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
    auto& dditable = layer::context.xetDdiTable.Global;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = layer::xetInit;

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
    auto& dditable = layer::context.xetDdiTable.Device;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnActivateMetricGroups                     = pDdiTable->pfnActivateMetricGroups;
    pDdiTable->pfnActivateMetricGroups                   = layer::xetDeviceActivateMetricGroups;

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
    auto& dditable = layer::context.xetDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnAppendMetricTracerMarker                 = pDdiTable->pfnAppendMetricTracerMarker;
    pDdiTable->pfnAppendMetricTracerMarker               = layer::xetCommandListAppendMetricTracerMarker;

    dditable.pfnAppendMetricQueryBegin                   = pDdiTable->pfnAppendMetricQueryBegin;
    pDdiTable->pfnAppendMetricQueryBegin                 = layer::xetCommandListAppendMetricQueryBegin;

    dditable.pfnAppendMetricQueryEnd                     = pDdiTable->pfnAppendMetricQueryEnd;
    pDdiTable->pfnAppendMetricQueryEnd                   = layer::xetCommandListAppendMetricQueryEnd;

    dditable.pfnAppendMetricMemoryBarrier                = pDdiTable->pfnAppendMetricMemoryBarrier;
    pDdiTable->pfnAppendMetricMemoryBarrier              = layer::xetCommandListAppendMetricMemoryBarrier;

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
    auto& dditable = layer::context.xetDdiTable.Module;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetDebugInfo                             = pDdiTable->pfnGetDebugInfo;
    pDdiTable->pfnGetDebugInfo                           = layer::xetModuleGetDebugInfo;

    dditable.pfnGetFunctionNames                         = pDdiTable->pfnGetFunctionNames;
    pDdiTable->pfnGetFunctionNames                       = layer::xetModuleGetFunctionNames;

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
    auto& dditable = layer::context.xetDdiTable.Function;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProfileInfo                           = pDdiTable->pfnGetProfileInfo;
    pDdiTable->pfnGetProfileInfo                         = layer::xetFunctionGetProfileInfo;

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
    auto& dditable = layer::context.xetDdiTable.MetricGroup;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::xetMetricGroupGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetMetricGroupGetProperties;

    dditable.pfnCalculateMetricValues                    = pDdiTable->pfnCalculateMetricValues;
    pDdiTable->pfnCalculateMetricValues                  = layer::xetMetricGroupCalculateMetricValues;

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
    auto& dditable = layer::context.xetDdiTable.Metric;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::xetMetricGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetMetricGetProperties;

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
    auto& dditable = layer::context.xetDdiTable.MetricTracer;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnOpen                                     = pDdiTable->pfnOpen;
    pDdiTable->pfnOpen                                   = layer::xetMetricTracerOpen;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = layer::xetMetricTracerClose;

    dditable.pfnReadData                                 = pDdiTable->pfnReadData;
    pDdiTable->pfnReadData                               = layer::xetMetricTracerReadData;

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
    auto& dditable = layer::context.xetDdiTable.MetricQueryPool;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xetMetricQueryPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xetMetricQueryPoolDestroy;

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
    auto& dditable = layer::context.xetDdiTable.MetricQuery;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xetMetricQueryCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xetMetricQueryDestroy;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::xetMetricQueryReset;

    dditable.pfnGetData                                  = pDdiTable->pfnGetData;
    pDdiTable->pfnGetData                                = layer::xetMetricQueryGetData;

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
    auto& dditable = layer::context.xetDdiTable.Tracer;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xetTracerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xetTracerDestroy;

    dditable.pfnSetPrologues                             = pDdiTable->pfnSetPrologues;
    pDdiTable->pfnSetPrologues                           = layer::xetTracerSetPrologues;

    dditable.pfnSetEpilogues                             = pDdiTable->pfnSetEpilogues;
    pDdiTable->pfnSetEpilogues                           = layer::xetTracerSetEpilogues;

    dditable.pfnSetEnabled                               = pDdiTable->pfnSetEnabled;
    pDdiTable->pfnSetEnabled                             = layer::xetTracerSetEnabled;

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
    auto& dditable = layer::context.xetDdiTable.Sysman;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::xetSysmanGet;

    dditable.pfnDeviceGetProperties                      = pDdiTable->pfnDeviceGetProperties;
    pDdiTable->pfnDeviceGetProperties                    = layer::xetSysmanDeviceGetProperties;

    dditable.pfnDeviceGetGuardTimeout                    = pDdiTable->pfnDeviceGetGuardTimeout;
    pDdiTable->pfnDeviceGetGuardTimeout                  = layer::xetSysmanDeviceGetGuardTimeout;

    dditable.pfnDeviceSetGuardTimeout                    = pDdiTable->pfnDeviceSetGuardTimeout;
    pDdiTable->pfnDeviceSetGuardTimeout                  = layer::xetSysmanDeviceSetGuardTimeout;

    dditable.pfnDeviceReset                              = pDdiTable->pfnDeviceReset;
    pDdiTable->pfnDeviceReset                            = layer::xetSysmanDeviceReset;

    dditable.pfnDeviceWasRepaired                        = pDdiTable->pfnDeviceWasRepaired;
    pDdiTable->pfnDeviceWasRepaired                      = layer::xetSysmanDeviceWasRepaired;

    dditable.pfnPciGetProperties                         = pDdiTable->pfnPciGetProperties;
    pDdiTable->pfnPciGetProperties                       = layer::xetSysmanPciGetProperties;

    dditable.pfnPciGetState                              = pDdiTable->pfnPciGetState;
    pDdiTable->pfnPciGetState                            = layer::xetSysmanPciGetState;

    dditable.pfnPciGetBarProperties                      = pDdiTable->pfnPciGetBarProperties;
    pDdiTable->pfnPciGetBarProperties                    = layer::xetSysmanPciGetBarProperties;

    dditable.pfnPciGetThroughput                         = pDdiTable->pfnPciGetThroughput;
    pDdiTable->pfnPciGetThroughput                       = layer::xetSysmanPciGetThroughput;

    dditable.pfnPciGetStats                              = pDdiTable->pfnPciGetStats;
    pDdiTable->pfnPciGetStats                            = layer::xetSysmanPciGetStats;

    dditable.pfnPowerGet                                 = pDdiTable->pfnPowerGet;
    pDdiTable->pfnPowerGet                               = layer::xetSysmanPowerGet;

    dditable.pfnFrequencyGet                             = pDdiTable->pfnFrequencyGet;
    pDdiTable->pfnFrequencyGet                           = layer::xetSysmanFrequencyGet;

    dditable.pfnEngineGet                                = pDdiTable->pfnEngineGet;
    pDdiTable->pfnEngineGet                              = layer::xetSysmanEngineGet;

    dditable.pfnStandbyGet                               = pDdiTable->pfnStandbyGet;
    pDdiTable->pfnStandbyGet                             = layer::xetSysmanStandbyGet;

    dditable.pfnFirmwareGet                              = pDdiTable->pfnFirmwareGet;
    pDdiTable->pfnFirmwareGet                            = layer::xetSysmanFirmwareGet;

    dditable.pfnMemoryGet                                = pDdiTable->pfnMemoryGet;
    pDdiTable->pfnMemoryGet                              = layer::xetSysmanMemoryGet;

    dditable.pfnLinkSwitchGet                            = pDdiTable->pfnLinkSwitchGet;
    pDdiTable->pfnLinkSwitchGet                          = layer::xetSysmanLinkSwitchGet;

    dditable.pfnTemperatureGet                           = pDdiTable->pfnTemperatureGet;
    pDdiTable->pfnTemperatureGet                         = layer::xetSysmanTemperatureGet;

    dditable.pfnPsuGet                                   = pDdiTable->pfnPsuGet;
    pDdiTable->pfnPsuGet                                 = layer::xetSysmanPsuGet;

    dditable.pfnFanGet                                   = pDdiTable->pfnFanGet;
    pDdiTable->pfnFanGet                                 = layer::xetSysmanFanGet;

    dditable.pfnLedGet                                   = pDdiTable->pfnLedGet;
    pDdiTable->pfnLedGet                                 = layer::xetSysmanLedGet;

    dditable.pfnRasGet                                   = pDdiTable->pfnRasGet;
    pDdiTable->pfnRasGet                                 = layer::xetSysmanRasGet;

    dditable.pfnEventsGetProperties                      = pDdiTable->pfnEventsGetProperties;
    pDdiTable->pfnEventsGetProperties                    = layer::xetSysmanEventsGetProperties;

    dditable.pfnEventsRegister                           = pDdiTable->pfnEventsRegister;
    pDdiTable->pfnEventsRegister                         = layer::xetSysmanEventsRegister;

    dditable.pfnEventsUnregister                         = pDdiTable->pfnEventsUnregister;
    pDdiTable->pfnEventsUnregister                       = layer::xetSysmanEventsUnregister;

    dditable.pfnEventsListen                             = pDdiTable->pfnEventsListen;
    pDdiTable->pfnEventsListen                           = layer::xetSysmanEventsListen;

    dditable.pfnDiagnosticsGet                           = pDdiTable->pfnDiagnosticsGet;
    pDdiTable->pfnDiagnosticsGet                         = layer::xetSysmanDiagnosticsGet;

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
    auto& dditable = layer::context.xetDdiTable.SysmanPower;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanPowerGetProperties;

    dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
    pDdiTable->pfnGetEnergyCounter                       = layer::xetSysmanPowerGetEnergyCounter;

    dditable.pfnGetEnergyThreshold                       = pDdiTable->pfnGetEnergyThreshold;
    pDdiTable->pfnGetEnergyThreshold                     = layer::xetSysmanPowerGetEnergyThreshold;

    dditable.pfnSetEnergyThreshold                       = pDdiTable->pfnSetEnergyThreshold;
    pDdiTable->pfnSetEnergyThreshold                     = layer::xetSysmanPowerSetEnergyThreshold;

    dditable.pfnGetLimits                                = pDdiTable->pfnGetLimits;
    pDdiTable->pfnGetLimits                              = layer::xetSysmanPowerGetLimits;

    dditable.pfnSetLimits                                = pDdiTable->pfnSetLimits;
    pDdiTable->pfnSetLimits                              = layer::xetSysmanPowerSetLimits;

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
    auto& dditable = layer::context.xetDdiTable.SysmanFrequency;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnSetFanSpeed                              = pDdiTable->pfnSetFanSpeed;
    pDdiTable->pfnSetFanSpeed                            = layer::xetSysmanFrequencySetFanSpeed;

    dditable.pfnGetOcCapabilities                        = pDdiTable->pfnGetOcCapabilities;
    pDdiTable->pfnGetOcCapabilities                      = layer::xetSysmanFrequencyGetOcCapabilities;

    dditable.pfnGetOcVrTopology                          = pDdiTable->pfnGetOcVrTopology;
    pDdiTable->pfnGetOcVrTopology                        = layer::xetSysmanFrequencyGetOcVrTopology;

    dditable.pfnGetOcOverrideProperties                  = pDdiTable->pfnGetOcOverrideProperties;
    pDdiTable->pfnGetOcOverrideProperties                = layer::xetSysmanFrequencyGetOcOverrideProperties;

    dditable.pfnGetOcIccMax                              = pDdiTable->pfnGetOcIccMax;
    pDdiTable->pfnGetOcIccMax                            = layer::xetSysmanFrequencyGetOcIccMax;

    dditable.pfnGetOcTjMax                               = pDdiTable->pfnGetOcTjMax;
    pDdiTable->pfnGetOcTjMax                             = layer::xetSysmanFrequencyGetOcTjMax;

    dditable.pfnSetOcOverrideProperties                  = pDdiTable->pfnSetOcOverrideProperties;
    pDdiTable->pfnSetOcOverrideProperties                = layer::xetSysmanFrequencySetOcOverrideProperties;

    dditable.pfnSetOcIccMax                              = pDdiTable->pfnSetOcIccMax;
    pDdiTable->pfnSetOcIccMax                            = layer::xetSysmanFrequencySetOcIccMax;

    dditable.pfnSetOcTjMax                               = pDdiTable->pfnSetOcTjMax;
    pDdiTable->pfnSetOcTjMax                             = layer::xetSysmanFrequencySetOcTjMax;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanFrequencyGetProperties;

    dditable.pfnGetRange                                 = pDdiTable->pfnGetRange;
    pDdiTable->pfnGetRange                               = layer::xetSysmanFrequencyGetRange;

    dditable.pfnSetRange                                 = pDdiTable->pfnSetRange;
    pDdiTable->pfnSetRange                               = layer::xetSysmanFrequencySetRange;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::xetSysmanFrequencyGetState;

    dditable.pfnGetThrottleTime                          = pDdiTable->pfnGetThrottleTime;
    pDdiTable->pfnGetThrottleTime                        = layer::xetSysmanFrequencyGetThrottleTime;

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
    auto& dditable = layer::context.xetDdiTable.SysmanEngine;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanEngineGetProperties;

    dditable.pfnGetActivity                              = pDdiTable->pfnGetActivity;
    pDdiTable->pfnGetActivity                            = layer::xetSysmanEngineGetActivity;

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
    auto& dditable = layer::context.xetDdiTable.SysmanStandby;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanStandbyGetProperties;

    dditable.pfnGetMode                                  = pDdiTable->pfnGetMode;
    pDdiTable->pfnGetMode                                = layer::xetSysmanStandbyGetMode;

    dditable.pfnSetMode                                  = pDdiTable->pfnSetMode;
    pDdiTable->pfnSetMode                                = layer::xetSysmanStandbySetMode;

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
    auto& dditable = layer::context.xetDdiTable.SysmanFirmware;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanFirmwareGetProperties;

    dditable.pfnGetChecksum                              = pDdiTable->pfnGetChecksum;
    pDdiTable->pfnGetChecksum                            = layer::xetSysmanFirmwareGetChecksum;

    dditable.pfnFlash                                    = pDdiTable->pfnFlash;
    pDdiTable->pfnFlash                                  = layer::xetSysmanFirmwareFlash;

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
    auto& dditable = layer::context.xetDdiTable.SysmanMemory;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanMemoryGetProperties;

    dditable.pfnGetBandwidth                             = pDdiTable->pfnGetBandwidth;
    pDdiTable->pfnGetBandwidth                           = layer::xetSysmanMemoryGetBandwidth;

    dditable.pfnGetAllocated                             = pDdiTable->pfnGetAllocated;
    pDdiTable->pfnGetAllocated                           = layer::xetSysmanMemoryGetAllocated;

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
    auto& dditable = layer::context.xetDdiTable.SysmanLinkSwitch;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanLinkSwitchGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::xetSysmanLinkSwitchGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = layer::xetSysmanLinkSwitchSetState;

    dditable.pfnGetPorts                                 = pDdiTable->pfnGetPorts;
    pDdiTable->pfnGetPorts                               = layer::xetSysmanLinkSwitchGetPorts;

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
    auto& dditable = layer::context.xetDdiTable.SysmanLinkPort;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanLinkPortGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::xetSysmanLinkPortGetState;

    dditable.pfnGetThroughput                            = pDdiTable->pfnGetThroughput;
    pDdiTable->pfnGetThroughput                          = layer::xetSysmanLinkPortGetThroughput;

    dditable.pfnGetStats                                 = pDdiTable->pfnGetStats;
    pDdiTable->pfnGetStats                               = layer::xetSysmanLinkPortGetStats;

    dditable.pfnIsConnected                              = pDdiTable->pfnIsConnected;
    pDdiTable->pfnIsConnected                            = layer::xetSysmanLinkPortIsConnected;

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
    auto& dditable = layer::context.xetDdiTable.SysmanTemperature;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanTemperatureGetProperties;

    dditable.pfnRead                                     = pDdiTable->pfnRead;
    pDdiTable->pfnRead                                   = layer::xetSysmanTemperatureRead;

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
    auto& dditable = layer::context.xetDdiTable.SysmanPsu;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanPsuGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::xetSysmanPsuGetState;

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
    auto& dditable = layer::context.xetDdiTable.SysmanFan;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanFanGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::xetSysmanFanGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::xetSysmanFanSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::xetSysmanFanGetState;

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
    auto& dditable = layer::context.xetDdiTable.SysmanLed;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanLedGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::xetSysmanLedGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = layer::xetSysmanLedSetState;

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
    auto& dditable = layer::context.xetDdiTable.SysmanRas;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanRasGetProperties;

    dditable.pfnGetErrors                                = pDdiTable->pfnGetErrors;
    pDdiTable->pfnGetErrors                              = layer::xetSysmanRasGetErrors;

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
    auto& dditable = layer::context.xetDdiTable.SysmanDiagnostics;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetSysmanDiagnosticsGetProperties;

    dditable.pfnRunTests                                 = pDdiTable->pfnRunTests;
    pDdiTable->pfnRunTests                               = layer::xetSysmanDiagnosticsRunTests;

    return result;
}

#if defined(__cplusplus)
};
#endif
