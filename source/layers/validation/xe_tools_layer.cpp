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
        xet_device_group_handle_t hDeviceGroup,         ///< [in] Handle of the device group
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
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCreate( hDeviceGroup, version, flags, phSysman );
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
        auto pfnConvertUuidToString = context.xetDdiTable.Sysman.pfnConvertUuidToString;

        if( nullptr == pfnConvertUuidToString )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pUuid )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pSize )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnConvertUuidToString( hSysman, pUuid, pSize, pStr );
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
        auto pfnGetResources = context.xetDdiTable.Sysman.pfnGetResources;

        if( nullptr == pfnGetResources )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hParentResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetResources( hSysman, hParentResource, type, pCount, phResources );
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
        auto pfnGetDeviceResource = context.xetDdiTable.Sysman.pfnGetDeviceResource;

        if( nullptr == pfnGetDeviceResource )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDeviceResource( hSysman, hDevice, phResource );
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
        auto pfnGetResourceByUuid = context.xetDdiTable.Sysman.pfnGetResourceByUuid;

        if( nullptr == pfnGetResourceByUuid )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == uuid )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetResourceByUuid( hSysman, uuid, phResource );
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
        auto pfnGetRasErrors = context.xetDdiTable.Sysman.pfnGetRasErrors;

        if( nullptr == pfnGetRasErrors )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pErrors )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetRasErrors( hSysman, hResource, type, location, threshold, clear, pCount, pErrors );
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
        auto pfnIsSame = context.xetDdiTable.SysmanResource.pfnIsSame;

        if( nullptr == pfnIsSame )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLhs )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hRhs )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pIsSame )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnIsSame( hLhs, hRhs, pIsSame );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetInfo
    xe_result_t __xecall
    xetSysmanResourceGetInfo(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        xet_resource_info_t* pInfo                      ///< [out] Generic information about the resource
        )
    {
        auto pfnGetInfo = context.xetDdiTable.SysmanResource.pfnGetInfo;

        if( nullptr == pfnGetInfo )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pInfo )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetInfo( hResource, pInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanResourceGetParent
    xe_result_t __xecall
    xetSysmanResourceGetParent(
        xet_resource_handle_t hResource,                ///< [in] Handle of the resource
        xet_resource_handle_t* phResource               ///< [out] Handle of the parent resource
        )
    {
        auto pfnGetParent = context.xetDdiTable.SysmanResource.pfnGetParent;

        if( nullptr == pfnGetParent )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetParent( hResource, phResource );
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
        auto pfnGetChildren = context.xetDdiTable.SysmanResource.pfnGetChildren;

        if( nullptr == pfnGetChildren )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetChildren( hResource, pCount, phResources );
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
        auto pfnGetPeers = context.xetDdiTable.SysmanResource.pfnGetPeers;

        if( nullptr == pfnGetPeers )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPeers( hResource, pCount, phResources );
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
        auto pfnGetBoardProperties = context.xetDdiTable.SysmanResource.pfnGetBoardProperties;

        if( nullptr == pfnGetBoardProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetBoardProperties( hResource, count, pRequest );
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
        auto pfnGetDeviceProperties = context.xetDdiTable.SysmanResource.pfnGetDeviceProperties;

        if( nullptr == pfnGetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDeviceProperties( hResource, count, pRequest );
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
        auto pfnSetDeviceProperties = context.xetDdiTable.SysmanResource.pfnSetDeviceProperties;

        if( nullptr == pfnSetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetDeviceProperties( hResource, count, pRequest );
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
        auto pfnGetPsuProperties = context.xetDdiTable.SysmanResource.pfnGetPsuProperties;

        if( nullptr == pfnGetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPsuProperties( hResource, count, pRequest );
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
        auto pfnSetPsuProperties = context.xetDdiTable.SysmanResource.pfnSetPsuProperties;

        if( nullptr == pfnSetPsuProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPsuProperties( hResource, count, pRequest );
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
        auto pfnGetTempProperties = context.xetDdiTable.SysmanResource.pfnGetTempProperties;

        if( nullptr == pfnGetTempProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetTempProperties( hResource, count, pRequest );
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
        auto pfnGetFanProperties = context.xetDdiTable.SysmanResource.pfnGetFanProperties;

        if( nullptr == pfnGetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFanProperties( hResource, count, pRequest );
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
        auto pfnSetFanProperties = context.xetDdiTable.SysmanResource.pfnSetFanProperties;

        if( nullptr == pfnSetFanProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFanProperties( hResource, count, pRequest );
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
        auto pfnGetLedProperties = context.xetDdiTable.SysmanResource.pfnGetLedProperties;

        if( nullptr == pfnGetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetLedProperties( hResource, count, pRequest );
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
        auto pfnSetLedProperties = context.xetDdiTable.SysmanResource.pfnSetLedProperties;

        if( nullptr == pfnSetLedProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetLedProperties( hResource, count, pRequest );
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
        auto pfnGetFirmwareProperties = context.xetDdiTable.SysmanResource.pfnGetFirmwareProperties;

        if( nullptr == pfnGetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFirmwareProperties( hResource, count, pRequest );
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
        auto pfnSetFirmwareProperties = context.xetDdiTable.SysmanResource.pfnSetFirmwareProperties;

        if( nullptr == pfnSetFirmwareProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFirmwareProperties( hResource, count, pRequest );
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
        auto pfnGetPwrProperties = context.xetDdiTable.SysmanResource.pfnGetPwrProperties;

        if( nullptr == pfnGetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPwrProperties( hResource, count, pRequest );
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
        auto pfnSetPwrProperties = context.xetDdiTable.SysmanResource.pfnSetPwrProperties;

        if( nullptr == pfnSetPwrProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPwrProperties( hResource, count, pRequest );
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
        auto pfnGetFreqProperties = context.xetDdiTable.SysmanResource.pfnGetFreqProperties;

        if( nullptr == pfnGetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFreqProperties( hResource, count, pRequest );
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
        auto pfnSetFreqProperties = context.xetDdiTable.SysmanResource.pfnSetFreqProperties;

        if( nullptr == pfnSetFreqProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFreqProperties( hResource, count, pRequest );
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
        auto pfnGetPwrwellProperties = context.xetDdiTable.SysmanResource.pfnGetPwrwellProperties;

        if( nullptr == pfnGetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPwrwellProperties( hResource, count, pRequest );
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
        auto pfnSetPwrwellProperties = context.xetDdiTable.SysmanResource.pfnSetPwrwellProperties;

        if( nullptr == pfnSetPwrwellProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPwrwellProperties( hResource, count, pRequest );
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
        auto pfnGetAccelProperties = context.xetDdiTable.SysmanResource.pfnGetAccelProperties;

        if( nullptr == pfnGetAccelProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAccelProperties( hResource, count, pRequest );
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
        auto pfnGetMemProperties = context.xetDdiTable.SysmanResource.pfnGetMemProperties;

        if( nullptr == pfnGetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMemProperties( hResource, count, pRequest );
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
        auto pfnSetMemProperties = context.xetDdiTable.SysmanResource.pfnSetMemProperties;

        if( nullptr == pfnSetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetMemProperties( hResource, count, pRequest );
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
        auto pfnGetLinkProperties = context.xetDdiTable.SysmanResource.pfnGetLinkProperties;

        if( nullptr == pfnGetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetLinkProperties( hResource, count, pRequest );
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
        auto pfnSetLinkProperties = context.xetDdiTable.SysmanResource.pfnSetLinkProperties;

        if( nullptr == pfnSetLinkProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetLinkProperties( hResource, count, pRequest );
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
        auto pfnRegisterEvents = context.xetDdiTable.Sysman.pfnRegisterEvents;

        if( nullptr == pfnRegisterEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRegisterEvents( hSysman, hResource, events );
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
        auto pfnUnregisterEvents = context.xetDdiTable.Sysman.pfnUnregisterEvents;

        if( nullptr == pfnUnregisterEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hResource )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnUnregisterEvents( hSysman, hResource, events );
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
        auto pfnListenEvents = context.xetDdiTable.Sysman.pfnListenEvents;

        if( nullptr == pfnListenEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEventData )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnListenEvents( hSysman, block, pCount, pEventData );
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

    dditable.pfnConvertUuidToString                      = pDdiTable->pfnConvertUuidToString;
    pDdiTable->pfnConvertUuidToString                    = layer::xetSysmanConvertUuidToString;

    dditable.pfnGetResources                             = pDdiTable->pfnGetResources;
    pDdiTable->pfnGetResources                           = layer::xetSysmanGetResources;

    dditable.pfnGetDeviceResource                        = pDdiTable->pfnGetDeviceResource;
    pDdiTable->pfnGetDeviceResource                      = layer::xetSysmanGetDeviceResource;

    dditable.pfnGetResourceByUuid                        = pDdiTable->pfnGetResourceByUuid;
    pDdiTable->pfnGetResourceByUuid                      = layer::xetSysmanGetResourceByUuid;

    dditable.pfnGetRasErrors                             = pDdiTable->pfnGetRasErrors;
    pDdiTable->pfnGetRasErrors                           = layer::xetSysmanGetRasErrors;

    dditable.pfnRegisterEvents                           = pDdiTable->pfnRegisterEvents;
    pDdiTable->pfnRegisterEvents                         = layer::xetSysmanRegisterEvents;

    dditable.pfnUnregisterEvents                         = pDdiTable->pfnUnregisterEvents;
    pDdiTable->pfnUnregisterEvents                       = layer::xetSysmanUnregisterEvents;

    dditable.pfnListenEvents                             = pDdiTable->pfnListenEvents;
    pDdiTable->pfnListenEvents                           = layer::xetSysmanListenEvents;

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
    auto& dditable = layer::context.xetDdiTable.SysmanResource;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnIsSame                                   = pDdiTable->pfnIsSame;
    pDdiTable->pfnIsSame                                 = layer::xetSysmanResourceIsSame;

    dditable.pfnGetInfo                                  = pDdiTable->pfnGetInfo;
    pDdiTable->pfnGetInfo                                = layer::xetSysmanResourceGetInfo;

    dditable.pfnGetParent                                = pDdiTable->pfnGetParent;
    pDdiTable->pfnGetParent                              = layer::xetSysmanResourceGetParent;

    dditable.pfnGetChildren                              = pDdiTable->pfnGetChildren;
    pDdiTable->pfnGetChildren                            = layer::xetSysmanResourceGetChildren;

    dditable.pfnGetPeers                                 = pDdiTable->pfnGetPeers;
    pDdiTable->pfnGetPeers                               = layer::xetSysmanResourceGetPeers;

    dditable.pfnGetBoardProperties                       = pDdiTable->pfnGetBoardProperties;
    pDdiTable->pfnGetBoardProperties                     = layer::xetSysmanResourceGetBoardProperties;

    dditable.pfnGetDeviceProperties                      = pDdiTable->pfnGetDeviceProperties;
    pDdiTable->pfnGetDeviceProperties                    = layer::xetSysmanResourceGetDeviceProperties;

    dditable.pfnSetDeviceProperties                      = pDdiTable->pfnSetDeviceProperties;
    pDdiTable->pfnSetDeviceProperties                    = layer::xetSysmanResourceSetDeviceProperties;

    dditable.pfnGetPsuProperties                         = pDdiTable->pfnGetPsuProperties;
    pDdiTable->pfnGetPsuProperties                       = layer::xetSysmanResourceGetPsuProperties;

    dditable.pfnSetPsuProperties                         = pDdiTable->pfnSetPsuProperties;
    pDdiTable->pfnSetPsuProperties                       = layer::xetSysmanResourceSetPsuProperties;

    dditable.pfnGetTempProperties                        = pDdiTable->pfnGetTempProperties;
    pDdiTable->pfnGetTempProperties                      = layer::xetSysmanResourceGetTempProperties;

    dditable.pfnGetFanProperties                         = pDdiTable->pfnGetFanProperties;
    pDdiTable->pfnGetFanProperties                       = layer::xetSysmanResourceGetFanProperties;

    dditable.pfnSetFanProperties                         = pDdiTable->pfnSetFanProperties;
    pDdiTable->pfnSetFanProperties                       = layer::xetSysmanResourceSetFanProperties;

    dditable.pfnGetLedProperties                         = pDdiTable->pfnGetLedProperties;
    pDdiTable->pfnGetLedProperties                       = layer::xetSysmanResourceGetLedProperties;

    dditable.pfnSetLedProperties                         = pDdiTable->pfnSetLedProperties;
    pDdiTable->pfnSetLedProperties                       = layer::xetSysmanResourceSetLedProperties;

    dditable.pfnGetFirmwareProperties                    = pDdiTable->pfnGetFirmwareProperties;
    pDdiTable->pfnGetFirmwareProperties                  = layer::xetSysmanResourceGetFirmwareProperties;

    dditable.pfnSetFirmwareProperties                    = pDdiTable->pfnSetFirmwareProperties;
    pDdiTable->pfnSetFirmwareProperties                  = layer::xetSysmanResourceSetFirmwareProperties;

    dditable.pfnGetPwrProperties                         = pDdiTable->pfnGetPwrProperties;
    pDdiTable->pfnGetPwrProperties                       = layer::xetSysmanResourceGetPwrProperties;

    dditable.pfnSetPwrProperties                         = pDdiTable->pfnSetPwrProperties;
    pDdiTable->pfnSetPwrProperties                       = layer::xetSysmanResourceSetPwrProperties;

    dditable.pfnGetFreqProperties                        = pDdiTable->pfnGetFreqProperties;
    pDdiTable->pfnGetFreqProperties                      = layer::xetSysmanResourceGetFreqProperties;

    dditable.pfnSetFreqProperties                        = pDdiTable->pfnSetFreqProperties;
    pDdiTable->pfnSetFreqProperties                      = layer::xetSysmanResourceSetFreqProperties;

    dditable.pfnGetPwrwellProperties                     = pDdiTable->pfnGetPwrwellProperties;
    pDdiTable->pfnGetPwrwellProperties                   = layer::xetSysmanResourceGetPwrwellProperties;

    dditable.pfnSetPwrwellProperties                     = pDdiTable->pfnSetPwrwellProperties;
    pDdiTable->pfnSetPwrwellProperties                   = layer::xetSysmanResourceSetPwrwellProperties;

    dditable.pfnGetAccelProperties                       = pDdiTable->pfnGetAccelProperties;
    pDdiTable->pfnGetAccelProperties                     = layer::xetSysmanResourceGetAccelProperties;

    dditable.pfnGetMemProperties                         = pDdiTable->pfnGetMemProperties;
    pDdiTable->pfnGetMemProperties                       = layer::xetSysmanResourceGetMemProperties;

    dditable.pfnSetMemProperties                         = pDdiTable->pfnSetMemProperties;
    pDdiTable->pfnSetMemProperties                       = layer::xetSysmanResourceSetMemProperties;

    dditable.pfnGetLinkProperties                        = pDdiTable->pfnGetLinkProperties;
    pDdiTable->pfnGetLinkProperties                      = layer::xetSysmanResourceGetLinkProperties;

    dditable.pfnSetLinkProperties                        = pDdiTable->pfnSetLinkProperties;
    pDdiTable->pfnSetLinkProperties                      = layer::xetSysmanResourceSetLinkProperties;

    return result;
}

#if defined(__cplusplus)
};
#endif
