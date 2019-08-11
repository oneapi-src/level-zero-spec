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
        xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
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
        xet_metric_properties_t* pProperties            ///< [out] metric properties
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
    /// @brief Intercept function for xetSysmanGetSubdevice
    xe_result_t __xecall
    xetSysmanGetSubdevice(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the sub-device.
        xet_sysman_handle_t* phSysmanSubdevice          ///< [out] The handle for accessing the sub-device.
        )
    {
        auto pfnGetSubdevice = context.xetDdiTable.Sysman.pfnGetSubdevice;

        if( nullptr == pfnGetSubdevice )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phSysmanSubdevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetSubdevice( hSysman, ordinal, phSysmanSubdevice );
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
    /// @brief Intercept function for xetSysmanDeviceGetOperatingMode
    xe_result_t __xecall
    xetSysmanDeviceGetOperatingMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_operating_mode_t* pMode                     ///< [in] The current operating mode of the device.
        )
    {
        auto pfnDeviceGetOperatingMode = context.xetDdiTable.Sysman.pfnDeviceGetOperatingMode;

        if( nullptr == pfnDeviceGetOperatingMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMode )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceGetOperatingMode( hSysman, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceSetOperatingMode
    xe_result_t __xecall
    xetSysmanDeviceSetOperatingMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_operating_mode_t pMode                      ///< [in] The new operating mode of the device.
        )
    {
        auto pfnDeviceSetOperatingMode = context.xetDdiTable.Sysman.pfnDeviceSetOperatingMode;

        if( nullptr == pfnDeviceSetOperatingMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceSetOperatingMode( hSysman, pMode );
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
    /// @brief Intercept function for xetSysmanPowerGetProperties
    xe_result_t __xecall
    xetSysmanPowerGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        auto pfnPowerGetProperties = context.xetDdiTable.Sysman.pfnPowerGetProperties;

        if( nullptr == pfnPowerGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPowerGetProperties( hSysman, pProperties );
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
        auto pfnPowerGetEnergyCounter = context.xetDdiTable.Sysman.pfnPowerGetEnergyCounter;

        if( nullptr == pfnPowerGetEnergyCounter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEnergy )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPowerGetEnergyCounter( hSysman, pEnergy );
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
        auto pfnPowerGetLimits = context.xetDdiTable.Sysman.pfnPowerGetLimits;

        if( nullptr == pfnPowerGetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPowerGetLimits( hSysman, pSustained, pBurst, pPeak );
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
        auto pfnPowerSetLimits = context.xetDdiTable.Sysman.pfnPowerSetLimits;

        if( nullptr == pfnPowerSetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPowerSetLimits( hSysman, pSustained, pBurst, pPeak );
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
        auto pfnFrequencyGetProperties = context.xetDdiTable.Sysman.pfnFrequencyGetProperties;

        if( nullptr == pfnFrequencyGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFrequencyGetProperties( hSysman, domain, pProperties );
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
        auto pfnFrequencyGetLimits = context.xetDdiTable.Sysman.pfnFrequencyGetLimits;

        if( nullptr == pfnFrequencyGetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFrequencyGetLimits( hSysman, domain, pLimits );
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
        auto pfnFrequencySetLimits = context.xetDdiTable.Sysman.pfnFrequencySetLimits;

        if( nullptr == pfnFrequencySetLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFrequencySetLimits( hSysman, domain, pLimits );
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
        auto pfnFrequencyGetState = context.xetDdiTable.Sysman.pfnFrequencyGetState;

        if( nullptr == pfnFrequencyGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFrequencyGetState( hSysman, domain, pState );
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
        auto pfnFrequencyGetThrottleTime = context.xetDdiTable.Sysman.pfnFrequencyGetThrottleTime;

        if( nullptr == pfnFrequencyGetThrottleTime )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThrottleTime )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFrequencyGetThrottleTime( hSysman, domain, pThrottleTime );
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
        auto pfnActivityGetStats = context.xetDdiTable.Sysman.pfnActivityGetStats;

        if( nullptr == pfnActivityGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnActivityGetStats( hSysman, type, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetProperties
    xe_result_t __xecall
    xetSysmanMemoryGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        auto pfnMemoryGetProperties = context.xetDdiTable.Sysman.pfnMemoryGetProperties;

        if( nullptr == pfnMemoryGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnMemoryGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetBandwidth
    xe_result_t __xecall
    xetSysmanMemoryGetBandwidth(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        auto pfnMemoryGetBandwidth = context.xetDdiTable.Sysman.pfnMemoryGetBandwidth;

        if( nullptr == pfnMemoryGetBandwidth )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pBandwidth )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnMemoryGetBandwidth( hSysman, pBandwidth );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetAllocated
    xe_result_t __xecall
    xetSysmanMemoryGetAllocated(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
        )
    {
        auto pfnMemoryGetAllocated = context.xetDdiTable.Sysman.pfnMemoryGetAllocated;

        if( nullptr == pfnMemoryGetAllocated )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pAllocated )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnMemoryGetAllocated( hSysman, pAllocated );
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
        uint32_t ordinal,                               ///< [in] The index of the port (0 ... [::xet_pci_properties_t.numBars -
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

        return pfnPciGetBarProperties( hSysman, ordinal, pProperties );
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
    /// @brief Intercept function for xetSysmanSwitchGetProperties
    xe_result_t __xecall
    xetSysmanSwitchGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_switch_properties_t* pProperties            ///< [in] Will contain the Switch properties.
        )
    {
        auto pfnSwitchGetProperties = context.xetDdiTable.Sysman.pfnSwitchGetProperties;

        if( nullptr == pfnSwitchGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSwitchGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchGetState
    xe_result_t __xecall
    xetSysmanSwitchGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_switch_state_t* pState                      ///< [in] Will contain the current state of the switch (enabled/disabled).
        )
    {
        auto pfnSwitchGetState = context.xetDdiTable.Sysman.pfnSwitchGetState;

        if( nullptr == pfnSwitchGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSwitchGetState( hSysman, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchSetState
    xe_result_t __xecall
    xetSysmanSwitchSetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xe_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
        )
    {
        auto pfnSwitchSetState = context.xetDdiTable.Sysman.pfnSwitchSetState;

        if( nullptr == pfnSwitchSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSwitchSetState( hSysman, enable );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetProperties
    xe_result_t __xecall
    xetSysmanSwitchPortGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_properties_t* pProperties       ///< [in] Will contain properties of the Switch Port
        )
    {
        auto pfnSwitchPortGetProperties = context.xetDdiTable.Sysman.pfnSwitchPortGetProperties;

        if( nullptr == pfnSwitchPortGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSwitchPortGetProperties( hSysman, ordinal, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetState
    xe_result_t __xecall
    xetSysmanSwitchPortGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_state_t* pState                 ///< [in] Will contain the current state of the Switch Port
        )
    {
        auto pfnSwitchPortGetState = context.xetDdiTable.Sysman.pfnSwitchPortGetState;

        if( nullptr == pfnSwitchPortGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSwitchPortGetState( hSysman, ordinal, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetThroughput
    xe_result_t __xecall
    xetSysmanSwitchPortGetThroughput(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_throughput_t* pThroughput       ///< [in] Will contain the Switch port throughput counters.
        )
    {
        auto pfnSwitchPortGetThroughput = context.xetDdiTable.Sysman.pfnSwitchPortGetThroughput;

        if( nullptr == pfnSwitchPortGetThroughput )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThroughput )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSwitchPortGetThroughput( hSysman, ordinal, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetStats
    xe_result_t __xecall
    xetSysmanSwitchPortGetStats(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_stats_t* pStats                 ///< [in] Will contain the Switch port stats.
        )
    {
        auto pfnSwitchPortGetStats = context.xetDdiTable.Sysman.pfnSwitchPortGetStats;

        if( nullptr == pfnSwitchPortGetStats )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSwitchPortGetStats( hSysman, ordinal, pStats );
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
        auto pfnTemperatureGet = context.xetDdiTable.Sysman.pfnTemperatureGet;

        if( nullptr == pfnTemperatureGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTemperature )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnTemperatureGet( hSysman, sensor, pTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetMode
    xe_result_t __xecall
    xetSysmanStandbyGetMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_stby_promo_mode_t* pMode                    ///< [in] Will contain the current standby mode.
        )
    {
        auto pfnStandbyGetMode = context.xetDdiTable.Sysman.pfnStandbyGetMode;

        if( nullptr == pfnStandbyGetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMode )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnStandbyGetMode( hSysman, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbySetMode
    xe_result_t __xecall
    xetSysmanStandbySetMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_stby_promo_mode_t mode                      ///< [in] New standby mode.
        )
    {
        auto pfnStandbySetMode = context.xetDdiTable.Sysman.pfnStandbySetMode;

        if( nullptr == pfnStandbySetMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnStandbySetMode( hSysman, mode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetProperties
    xe_result_t __xecall
    xetSysmanFirmwareGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the firmware (0 ...
                                                        ///< [::xet_sysman_properties_t.numFirmwares - 1]).
        xet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        auto pfnFirmwareGetProperties = context.xetDdiTable.Sysman.pfnFirmwareGetProperties;

        if( nullptr == pfnFirmwareGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFirmwareGetProperties( hSysman, ordinal, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetChecksum
    xe_result_t __xecall
    xetSysmanFirmwareGetChecksum(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the firmware (0 ...
                                                        ///< [::xet_sysman_properties_t.numFirmwares - 1]).
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        auto pfnFirmwareGetChecksum = context.xetDdiTable.Sysman.pfnFirmwareGetChecksum;

        if( nullptr == pfnFirmwareGetChecksum )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pChecksum )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFirmwareGetChecksum( hSysman, ordinal, pChecksum );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareFlash
    xe_result_t __xecall
    xetSysmanFirmwareFlash(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the firmware (0 ...
                                                        ///< [::xet_sysman_properties_t.numFirmwares - 1]).
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto pfnFirmwareFlash = context.xetDdiTable.Sysman.pfnFirmwareFlash;

        if( nullptr == pfnFirmwareFlash )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFirmwareFlash( hSysman, ordinal, pImage, size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetProperties
    xe_result_t __xecall
    xetSysmanPsuGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the power supply (0 ...
                                                        ///< [::xet_sysman_properties_t.numPsus - 1]).
        xet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        auto pfnPsuGetProperties = context.xetDdiTable.Sysman.pfnPsuGetProperties;

        if( nullptr == pfnPsuGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPsuGetProperties( hSysman, ordinal, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetState
    xe_result_t __xecall
    xetSysmanPsuGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the power supply (0 ...
                                                        ///< [::xet_sysman_properties_t.numPsus - 1]).
        xet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        auto pfnPsuGetState = context.xetDdiTable.Sysman.pfnPsuGetState;

        if( nullptr == pfnPsuGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPsuGetState( hSysman, ordinal, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetProperties
    xe_result_t __xecall
    xetSysmanFanGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        xet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        auto pfnFanGetProperties = context.xetDdiTable.Sysman.pfnFanGetProperties;

        if( nullptr == pfnFanGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGetProperties( hSysman, ordinal, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetConfig
    xe_result_t __xecall
    xetSysmanFanGetConfig(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        xet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        auto pfnFanGetConfig = context.xetDdiTable.Sysman.pfnFanGetConfig;

        if( nullptr == pfnFanGetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGetConfig( hSysman, ordinal, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanSetConfig
    xe_result_t __xecall
    xetSysmanFanSetConfig(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        const xet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        auto pfnFanSetConfig = context.xetDdiTable.Sysman.pfnFanSetConfig;

        if( nullptr == pfnFanSetConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanSetConfig( hSysman, ordinal, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetState
    xe_result_t __xecall
    xetSysmanFanGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                        ///< 1]).
        xet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        xet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
        )
    {
        auto pfnFanGetState = context.xetDdiTable.Sysman.pfnFanGetState;

        if( nullptr == pfnFanGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGetState( hSysman, ordinal, units, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetProperties
    xe_result_t __xecall
    xetSysmanLedGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                        ///< 1]).
        xet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        auto pfnLedGetProperties = context.xetDdiTable.Sysman.pfnLedGetProperties;

        if( nullptr == pfnLedGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnLedGetProperties( hSysman, ordinal, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetState
    xe_result_t __xecall
    xetSysmanLedGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                        ///< 1]).
        xet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        auto pfnLedGetState = context.xetDdiTable.Sysman.pfnLedGetState;

        if( nullptr == pfnLedGetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnLedGetState( hSysman, ordinal, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedSetState
    xe_result_t __xecall
    xetSysmanLedSetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ordinal,                               ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                        ///< 1]).
        const xet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        auto pfnLedSetState = context.xetDdiTable.Sysman.pfnLedSetState;

        if( nullptr == pfnLedSetState )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnLedSetState( hSysman, ordinal, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetProperties
    xe_result_t __xecall
    xetSysmanRasGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        xet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        auto pfnRasGetProperties = context.xetDdiTable.Sysman.pfnRasGetProperties;

        if( nullptr == pfnRasGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRasGetProperties( hSysman, pProperties );
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
        auto pfnRasGetErrors = context.xetDdiTable.Sysman.pfnRasGetErrors;

        if( nullptr == pfnRasGetErrors )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTotalErrors )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRasGetErrors( hSysman, type, clear, pTotalErrors, pDetails );
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
    /// @brief Intercept function for xetSysmanDiagnosticsGetTestList
    xe_result_t __xecall
    xetSysmanDiagnosticsGetTestList(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
        const xet_diag_test_list_t** ppTests            ///< [in] Returns a constant pointer to the list of diagnostic tests
        )
    {
        auto pfnDiagnosticsGetTestList = context.xetDdiTable.Sysman.pfnDiagnosticsGetTestList;

        if( nullptr == pfnDiagnosticsGetTestList )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ppTests )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDiagnosticsGetTestList( hSysman, type, ppTests );
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
        auto pfnDiagnosticsRunTests = context.xetDdiTable.Sysman.pfnDiagnosticsRunTests;

        if( nullptr == pfnDiagnosticsRunTests )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pResult )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDiagnosticsRunTests( hSysman, type, start, end, pResult );
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

    dditable.pfnGetSubdevice                             = pDdiTable->pfnGetSubdevice;
    pDdiTable->pfnGetSubdevice                           = layer::xetSysmanGetSubdevice;

    dditable.pfnDeviceGetProperties                      = pDdiTable->pfnDeviceGetProperties;
    pDdiTable->pfnDeviceGetProperties                    = layer::xetSysmanDeviceGetProperties;

    dditable.pfnDeviceGetOperatingMode                   = pDdiTable->pfnDeviceGetOperatingMode;
    pDdiTable->pfnDeviceGetOperatingMode                 = layer::xetSysmanDeviceGetOperatingMode;

    dditable.pfnDeviceSetOperatingMode                   = pDdiTable->pfnDeviceSetOperatingMode;
    pDdiTable->pfnDeviceSetOperatingMode                 = layer::xetSysmanDeviceSetOperatingMode;

    dditable.pfnDeviceReset                              = pDdiTable->pfnDeviceReset;
    pDdiTable->pfnDeviceReset                            = layer::xetSysmanDeviceReset;

    dditable.pfnPowerGetProperties                       = pDdiTable->pfnPowerGetProperties;
    pDdiTable->pfnPowerGetProperties                     = layer::xetSysmanPowerGetProperties;

    dditable.pfnPowerGetEnergyCounter                    = pDdiTable->pfnPowerGetEnergyCounter;
    pDdiTable->pfnPowerGetEnergyCounter                  = layer::xetSysmanPowerGetEnergyCounter;

    dditable.pfnPowerGetLimits                           = pDdiTable->pfnPowerGetLimits;
    pDdiTable->pfnPowerGetLimits                         = layer::xetSysmanPowerGetLimits;

    dditable.pfnPowerSetLimits                           = pDdiTable->pfnPowerSetLimits;
    pDdiTable->pfnPowerSetLimits                         = layer::xetSysmanPowerSetLimits;

    dditable.pfnFrequencyGetProperties                   = pDdiTable->pfnFrequencyGetProperties;
    pDdiTable->pfnFrequencyGetProperties                 = layer::xetSysmanFrequencyGetProperties;

    dditable.pfnFrequencyGetLimits                       = pDdiTable->pfnFrequencyGetLimits;
    pDdiTable->pfnFrequencyGetLimits                     = layer::xetSysmanFrequencyGetLimits;

    dditable.pfnFrequencySetLimits                       = pDdiTable->pfnFrequencySetLimits;
    pDdiTable->pfnFrequencySetLimits                     = layer::xetSysmanFrequencySetLimits;

    dditable.pfnFrequencyGetState                        = pDdiTable->pfnFrequencyGetState;
    pDdiTable->pfnFrequencyGetState                      = layer::xetSysmanFrequencyGetState;

    dditable.pfnFrequencyGetThrottleTime                 = pDdiTable->pfnFrequencyGetThrottleTime;
    pDdiTable->pfnFrequencyGetThrottleTime               = layer::xetSysmanFrequencyGetThrottleTime;

    dditable.pfnActivityGetStats                         = pDdiTable->pfnActivityGetStats;
    pDdiTable->pfnActivityGetStats                       = layer::xetSysmanActivityGetStats;

    dditable.pfnMemoryGetProperties                      = pDdiTable->pfnMemoryGetProperties;
    pDdiTable->pfnMemoryGetProperties                    = layer::xetSysmanMemoryGetProperties;

    dditable.pfnMemoryGetBandwidth                       = pDdiTable->pfnMemoryGetBandwidth;
    pDdiTable->pfnMemoryGetBandwidth                     = layer::xetSysmanMemoryGetBandwidth;

    dditable.pfnMemoryGetAllocated                       = pDdiTable->pfnMemoryGetAllocated;
    pDdiTable->pfnMemoryGetAllocated                     = layer::xetSysmanMemoryGetAllocated;

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

    dditable.pfnSwitchGetProperties                      = pDdiTable->pfnSwitchGetProperties;
    pDdiTable->pfnSwitchGetProperties                    = layer::xetSysmanSwitchGetProperties;

    dditable.pfnSwitchGetState                           = pDdiTable->pfnSwitchGetState;
    pDdiTable->pfnSwitchGetState                         = layer::xetSysmanSwitchGetState;

    dditable.pfnSwitchSetState                           = pDdiTable->pfnSwitchSetState;
    pDdiTable->pfnSwitchSetState                         = layer::xetSysmanSwitchSetState;

    dditable.pfnSwitchPortGetProperties                  = pDdiTable->pfnSwitchPortGetProperties;
    pDdiTable->pfnSwitchPortGetProperties                = layer::xetSysmanSwitchPortGetProperties;

    dditable.pfnSwitchPortGetState                       = pDdiTable->pfnSwitchPortGetState;
    pDdiTable->pfnSwitchPortGetState                     = layer::xetSysmanSwitchPortGetState;

    dditable.pfnSwitchPortGetThroughput                  = pDdiTable->pfnSwitchPortGetThroughput;
    pDdiTable->pfnSwitchPortGetThroughput                = layer::xetSysmanSwitchPortGetThroughput;

    dditable.pfnSwitchPortGetStats                       = pDdiTable->pfnSwitchPortGetStats;
    pDdiTable->pfnSwitchPortGetStats                     = layer::xetSysmanSwitchPortGetStats;

    dditable.pfnTemperatureGet                           = pDdiTable->pfnTemperatureGet;
    pDdiTable->pfnTemperatureGet                         = layer::xetSysmanTemperatureGet;

    dditable.pfnStandbyGetMode                           = pDdiTable->pfnStandbyGetMode;
    pDdiTable->pfnStandbyGetMode                         = layer::xetSysmanStandbyGetMode;

    dditable.pfnStandbySetMode                           = pDdiTable->pfnStandbySetMode;
    pDdiTable->pfnStandbySetMode                         = layer::xetSysmanStandbySetMode;

    dditable.pfnFirmwareGetProperties                    = pDdiTable->pfnFirmwareGetProperties;
    pDdiTable->pfnFirmwareGetProperties                  = layer::xetSysmanFirmwareGetProperties;

    dditable.pfnFirmwareGetChecksum                      = pDdiTable->pfnFirmwareGetChecksum;
    pDdiTable->pfnFirmwareGetChecksum                    = layer::xetSysmanFirmwareGetChecksum;

    dditable.pfnFirmwareFlash                            = pDdiTable->pfnFirmwareFlash;
    pDdiTable->pfnFirmwareFlash                          = layer::xetSysmanFirmwareFlash;

    dditable.pfnPsuGetProperties                         = pDdiTable->pfnPsuGetProperties;
    pDdiTable->pfnPsuGetProperties                       = layer::xetSysmanPsuGetProperties;

    dditable.pfnPsuGetState                              = pDdiTable->pfnPsuGetState;
    pDdiTable->pfnPsuGetState                            = layer::xetSysmanPsuGetState;

    dditable.pfnFanGetProperties                         = pDdiTable->pfnFanGetProperties;
    pDdiTable->pfnFanGetProperties                       = layer::xetSysmanFanGetProperties;

    dditable.pfnFanGetConfig                             = pDdiTable->pfnFanGetConfig;
    pDdiTable->pfnFanGetConfig                           = layer::xetSysmanFanGetConfig;

    dditable.pfnFanSetConfig                             = pDdiTable->pfnFanSetConfig;
    pDdiTable->pfnFanSetConfig                           = layer::xetSysmanFanSetConfig;

    dditable.pfnFanGetState                              = pDdiTable->pfnFanGetState;
    pDdiTable->pfnFanGetState                            = layer::xetSysmanFanGetState;

    dditable.pfnLedGetProperties                         = pDdiTable->pfnLedGetProperties;
    pDdiTable->pfnLedGetProperties                       = layer::xetSysmanLedGetProperties;

    dditable.pfnLedGetState                              = pDdiTable->pfnLedGetState;
    pDdiTable->pfnLedGetState                            = layer::xetSysmanLedGetState;

    dditable.pfnLedSetState                              = pDdiTable->pfnLedSetState;
    pDdiTable->pfnLedSetState                            = layer::xetSysmanLedSetState;

    dditable.pfnRasGetProperties                         = pDdiTable->pfnRasGetProperties;
    pDdiTable->pfnRasGetProperties                       = layer::xetSysmanRasGetProperties;

    dditable.pfnRasGetErrors                             = pDdiTable->pfnRasGetErrors;
    pDdiTable->pfnRasGetErrors                           = layer::xetSysmanRasGetErrors;

    dditable.pfnEventsRegister                           = pDdiTable->pfnEventsRegister;
    pDdiTable->pfnEventsRegister                         = layer::xetSysmanEventsRegister;

    dditable.pfnEventsUnregister                         = pDdiTable->pfnEventsUnregister;
    pDdiTable->pfnEventsUnregister                       = layer::xetSysmanEventsUnregister;

    dditable.pfnEventsListen                             = pDdiTable->pfnEventsListen;
    pDdiTable->pfnEventsListen                           = layer::xetSysmanEventsListen;

    dditable.pfnDiagnosticsGetTestList                   = pDdiTable->pfnDiagnosticsGetTestList;
    pDdiTable->pfnDiagnosticsGetTestList                 = layer::xetSysmanDiagnosticsGetTestList;

    dditable.pfnDiagnosticsRunTests                      = pDdiTable->pfnDiagnosticsRunTests;
    pDdiTable->pfnDiagnosticsRunTests                    = layer::xetSysmanDiagnosticsRunTests;

    return result;
}

#if defined(__cplusplus)
};
#endif
