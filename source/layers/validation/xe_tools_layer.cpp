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
        auto pfnGet = context.xetDdiTable.MetricGroup.pfnGet;

        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hDeviceGroup, pCount, phMetricGroups );
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
    /// @brief Intercept function for xetSysmanCreate
    xe_result_t __xecall
    xetSysmanCreate(
        xet_device_handle_t hDevice,                    ///< [in] Handle of the device
        xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
        uint32_t flags,                                 ///< [in] Bitfield of ::xet_sysman_init_flags_t
        xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
        )
    {
        auto pfnCreate = context.xetDdiTable.Sysman.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCreate( hDevice, version, flags, phSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDestroy
    xe_result_t __xecall
    xetSysmanDestroy(
        xet_sysman_handle_t hSysman                     ///< [in][release] SMI handle to destroy
        )
    {
        auto pfnDestroy = context.xetDdiTable.Sysman.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hSysman );
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
        auto pfnGetAccelAssetName = context.xetDdiTable.Sysman.pfnGetAccelAssetName;

        if( nullptr == pfnGetAccelAssetName )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ppName )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAccelAssetName( hSysman, type, ppName );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetInfo
    xe_result_t __xecall
    xetSysmanGetInfo(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of a device
        xet_sysman_info_t* pInfo                        ///< [in] Returned information
        )
    {
        auto pfnGetInfo = context.xetDdiTable.Sysman.pfnGetInfo;

        if( nullptr == pfnGetInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pInfo )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetInfo( hSysman, pInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanGetRasErrors
    xe_result_t __xecall
    xetSysmanGetRasErrors(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
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
        auto pfnGetRasErrors = context.xetDdiTable.Sysman.pfnGetRasErrors;

        if( nullptr == pfnGetRasErrors )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pErrors )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetRasErrors( hSysman, clear, pCount, pErrors );
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
        auto pfnGetDeviceProperties = context.xetDdiTable.Sysman.pfnGetDeviceProperties;

        if( nullptr == pfnGetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDeviceProperties( hSysman, count, pRequest );
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
        auto pfnSetDeviceProperties = context.xetDdiTable.Sysman.pfnSetDeviceProperties;

        if( nullptr == pfnSetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetDeviceProperties( hSysman, count, pRequest );
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
        auto pfnGetPsuProperties = context.xetDdiTable.Sysman.pfnGetPsuProperties;

        if( nullptr == pfnGetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPsuProperties( hSysman, count, pRequest );
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
        auto pfnSetPsuProperties = context.xetDdiTable.Sysman.pfnSetPsuProperties;

        if( nullptr == pfnSetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPsuProperties( hSysman, count, pRequest );
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
        auto pfnGetTempProperties = context.xetDdiTable.Sysman.pfnGetTempProperties;

        if( nullptr == pfnGetTempProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetTempProperties( hSysman, count, pRequest );
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
        auto pfnGetFanProperties = context.xetDdiTable.Sysman.pfnGetFanProperties;

        if( nullptr == pfnGetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFanProperties( hSysman, count, pRequest );
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
        auto pfnSetFanProperties = context.xetDdiTable.Sysman.pfnSetFanProperties;

        if( nullptr == pfnSetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFanProperties( hSysman, count, pRequest );
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
        auto pfnGetLedProperties = context.xetDdiTable.Sysman.pfnGetLedProperties;

        if( nullptr == pfnGetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetLedProperties( hSysman, count, pRequest );
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
        auto pfnSetLedProperties = context.xetDdiTable.Sysman.pfnSetLedProperties;

        if( nullptr == pfnSetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetLedProperties( hSysman, count, pRequest );
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
        auto pfnGetFirmwareProperties = context.xetDdiTable.Sysman.pfnGetFirmwareProperties;

        if( nullptr == pfnGetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFirmwareProperties( hSysman, count, pRequest );
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
        auto pfnSetFirmwareProperties = context.xetDdiTable.Sysman.pfnSetFirmwareProperties;

        if( nullptr == pfnSetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFirmwareProperties( hSysman, count, pRequest );
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
        auto pfnGetPwrProperties = context.xetDdiTable.Sysman.pfnGetPwrProperties;

        if( nullptr == pfnGetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPwrProperties( hSysman, count, pRequest );
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
        auto pfnSetPwrProperties = context.xetDdiTable.Sysman.pfnSetPwrProperties;

        if( nullptr == pfnSetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPwrProperties( hSysman, count, pRequest );
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
        auto pfnGetFreqProperties = context.xetDdiTable.Sysman.pfnGetFreqProperties;

        if( nullptr == pfnGetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFreqProperties( hSysman, count, pRequest );
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
        auto pfnSetFreqProperties = context.xetDdiTable.Sysman.pfnSetFreqProperties;

        if( nullptr == pfnSetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFreqProperties( hSysman, count, pRequest );
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
        auto pfnGetPwrwellProperties = context.xetDdiTable.Sysman.pfnGetPwrwellProperties;

        if( nullptr == pfnGetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPwrwellProperties( hSysman, count, pRequest );
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
        auto pfnSetPwrwellProperties = context.xetDdiTable.Sysman.pfnSetPwrwellProperties;

        if( nullptr == pfnSetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPwrwellProperties( hSysman, count, pRequest );
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
        auto pfnGetAccelProperties = context.xetDdiTable.Sysman.pfnGetAccelProperties;

        if( nullptr == pfnGetAccelProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAccelProperties( hSysman, count, pRequest );
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
        auto pfnGetMemProperties = context.xetDdiTable.Sysman.pfnGetMemProperties;

        if( nullptr == pfnGetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMemProperties( hSysman, count, pRequest );
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
        auto pfnSetMemProperties = context.xetDdiTable.Sysman.pfnSetMemProperties;

        if( nullptr == pfnSetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetMemProperties( hSysman, count, pRequest );
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
        auto pfnGetLinkProperties = context.xetDdiTable.Sysman.pfnGetLinkProperties;

        if( nullptr == pfnGetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetLinkProperties( hSysman, count, pRequest );
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
        auto pfnSetLinkProperties = context.xetDdiTable.Sysman.pfnSetLinkProperties;

        if( nullptr == pfnSetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetLinkProperties( hSysman, count, pRequest );
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
        auto pfnRegisterEvents = context.xetDdiTable.Sysman.pfnRegisterEvents;

        if( nullptr == pfnRegisterEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEvents )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRegisterEvents( hSysman, count, pEvents );
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
        auto pfnUnregisterEvents = context.xetDdiTable.Sysman.pfnUnregisterEvents;

        if( nullptr == pfnUnregisterEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEvents )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnUnregisterEvents( hSysman, count, pEvents );
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
        auto pfnGetEvents = context.xetDdiTable.Sysman.pfnGetEvents;

        if( nullptr == pfnGetEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEvents )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetEvents( hSysman, clear, timeout, pEvents );
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
        auto pfnCreate = context.xetDdiTable.Tracer.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phTracer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XET_TRACER_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDeviceGroup, desc, phTracer );
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

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xetSysmanCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xetSysmanDestroy;

    dditable.pfnGetAccelAssetName                        = pDdiTable->pfnGetAccelAssetName;
    pDdiTable->pfnGetAccelAssetName                      = layer::xetSysmanGetAccelAssetName;

    dditable.pfnGetInfo                                  = pDdiTable->pfnGetInfo;
    pDdiTable->pfnGetInfo                                = layer::xetSysmanGetInfo;

    dditable.pfnGetRasErrors                             = pDdiTable->pfnGetRasErrors;
    pDdiTable->pfnGetRasErrors                           = layer::xetSysmanGetRasErrors;

    dditable.pfnGetDeviceProperties                      = pDdiTable->pfnGetDeviceProperties;
    pDdiTable->pfnGetDeviceProperties                    = layer::xetSysmanGetDeviceProperties;

    dditable.pfnSetDeviceProperties                      = pDdiTable->pfnSetDeviceProperties;
    pDdiTable->pfnSetDeviceProperties                    = layer::xetSysmanSetDeviceProperties;

    dditable.pfnGetPsuProperties                         = pDdiTable->pfnGetPsuProperties;
    pDdiTable->pfnGetPsuProperties                       = layer::xetSysmanGetPsuProperties;

    dditable.pfnSetPsuProperties                         = pDdiTable->pfnSetPsuProperties;
    pDdiTable->pfnSetPsuProperties                       = layer::xetSysmanSetPsuProperties;

    dditable.pfnGetTempProperties                        = pDdiTable->pfnGetTempProperties;
    pDdiTable->pfnGetTempProperties                      = layer::xetSysmanGetTempProperties;

    dditable.pfnGetFanProperties                         = pDdiTable->pfnGetFanProperties;
    pDdiTable->pfnGetFanProperties                       = layer::xetSysmanGetFanProperties;

    dditable.pfnSetFanProperties                         = pDdiTable->pfnSetFanProperties;
    pDdiTable->pfnSetFanProperties                       = layer::xetSysmanSetFanProperties;

    dditable.pfnGetLedProperties                         = pDdiTable->pfnGetLedProperties;
    pDdiTable->pfnGetLedProperties                       = layer::xetSysmanGetLedProperties;

    dditable.pfnSetLedProperties                         = pDdiTable->pfnSetLedProperties;
    pDdiTable->pfnSetLedProperties                       = layer::xetSysmanSetLedProperties;

    dditable.pfnGetFirmwareProperties                    = pDdiTable->pfnGetFirmwareProperties;
    pDdiTable->pfnGetFirmwareProperties                  = layer::xetSysmanGetFirmwareProperties;

    dditable.pfnSetFirmwareProperties                    = pDdiTable->pfnSetFirmwareProperties;
    pDdiTable->pfnSetFirmwareProperties                  = layer::xetSysmanSetFirmwareProperties;

    dditable.pfnGetPwrProperties                         = pDdiTable->pfnGetPwrProperties;
    pDdiTable->pfnGetPwrProperties                       = layer::xetSysmanGetPwrProperties;

    dditable.pfnSetPwrProperties                         = pDdiTable->pfnSetPwrProperties;
    pDdiTable->pfnSetPwrProperties                       = layer::xetSysmanSetPwrProperties;

    dditable.pfnGetFreqProperties                        = pDdiTable->pfnGetFreqProperties;
    pDdiTable->pfnGetFreqProperties                      = layer::xetSysmanGetFreqProperties;

    dditable.pfnSetFreqProperties                        = pDdiTable->pfnSetFreqProperties;
    pDdiTable->pfnSetFreqProperties                      = layer::xetSysmanSetFreqProperties;

    dditable.pfnGetPwrwellProperties                     = pDdiTable->pfnGetPwrwellProperties;
    pDdiTable->pfnGetPwrwellProperties                   = layer::xetSysmanGetPwrwellProperties;

    dditable.pfnSetPwrwellProperties                     = pDdiTable->pfnSetPwrwellProperties;
    pDdiTable->pfnSetPwrwellProperties                   = layer::xetSysmanSetPwrwellProperties;

    dditable.pfnGetAccelProperties                       = pDdiTable->pfnGetAccelProperties;
    pDdiTable->pfnGetAccelProperties                     = layer::xetSysmanGetAccelProperties;

    dditable.pfnGetMemProperties                         = pDdiTable->pfnGetMemProperties;
    pDdiTable->pfnGetMemProperties                       = layer::xetSysmanGetMemProperties;

    dditable.pfnSetMemProperties                         = pDdiTable->pfnSetMemProperties;
    pDdiTable->pfnSetMemProperties                       = layer::xetSysmanSetMemProperties;

    dditable.pfnGetLinkProperties                        = pDdiTable->pfnGetLinkProperties;
    pDdiTable->pfnGetLinkProperties                      = layer::xetSysmanGetLinkProperties;

    dditable.pfnSetLinkProperties                        = pDdiTable->pfnSetLinkProperties;
    pDdiTable->pfnSetLinkProperties                      = layer::xetSysmanSetLinkProperties;

    dditable.pfnRegisterEvents                           = pDdiTable->pfnRegisterEvents;
    pDdiTable->pfnRegisterEvents                         = layer::xetSysmanRegisterEvents;

    dditable.pfnUnregisterEvents                         = pDdiTable->pfnUnregisterEvents;
    pDdiTable->pfnUnregisterEvents                       = layer::xetSysmanUnregisterEvents;

    dditable.pfnGetEvents                                = pDdiTable->pfnGetEvents;
    pDdiTable->pfnGetEvents                              = layer::xetSysmanGetEvents;

    return result;
}

#if defined(__cplusplus)
};
#endif
