/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_tools_layer.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/valddi.cpp.mako
 * @endcond
 *
 */
#include "ze_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetInit
    ze_result_t __zecall
    zetInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        auto pfnInit = context.zetDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
        }

        return pfnInit( flags );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGet
    ze_result_t __zecall
    zetMetricGroupGet(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< metric groups.
                                                        ///< if count is larger than the number of metric groups available, then
                                                        ///< the driver will update the value with the correct number of metric
                                                        ///< groups available.
        zet_metric_group_handle_t* phMetricGroups       ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups
        )
    {
        auto pfnGet = context.zetDdiTable.MetricGroup.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hDevice, pCount, phMetricGroups );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetProperties
    ze_result_t __zecall
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.MetricGroup.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hMetricGroup, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMetricValues
    ze_result_t __zecall
    zetMetricGroupCalculateMetricValues(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
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
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                        ///< metrics
        )
    {
        auto pfnCalculateMetricValues = context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;

        if( nullptr == pfnCalculateMetricValues )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRawData )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMetricValueCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGet
    ze_result_t __zecall
    zetMetricGet(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metrics available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                        ///< if count is larger than the number of metrics available, then the
                                                        ///< driver will update the value with the correct number of metrics available.
        zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics
        )
    {
        auto pfnGet = context.zetDdiTable.Metric.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hMetricGroup, pCount, phMetrics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGetProperties
    ze_result_t __zecall
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.Metric.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetric )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hMetric, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceActivateMetricGroups
    ze_result_t __zecall
    zetDeviceActivateMetricGroups(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                        ///< activate. NULL to deactivate.
        )
    {
        auto pfnActivateMetricGroups = context.zetDdiTable.Device.pfnActivateMetricGroups;

        if( nullptr == pfnActivateMetricGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnActivateMetricGroups( hDevice, count, phMetricGroups );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerOpen
    ze_result_t __zecall
    zetMetricTracerOpen(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_tracer_desc_t* desc,                 ///< [in,out] metric tracer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Must
                                                        ///< be device to host type.
        zet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
        )
    {
        auto pfnOpen = context.zetDdiTable.MetricTracer.pfnOpen;

        if( nullptr == pfnOpen )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phMetricTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( ZET_METRIC_TRACER_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricTracerMarker
    ze_result_t __zecall
    zetCommandListAppendMetricTracerMarker(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        auto pfnAppendMetricTracerMarker = context.zetDdiTable.CommandList.pfnAppendMetricTracerMarker;

        if( nullptr == pfnAppendMetricTracerMarker )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerClose
    ze_result_t __zecall
    zetMetricTracerClose(
        zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
        )
    {
        auto pfnClose = context.zetDdiTable.MetricTracer.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnClose( hMetricTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerReadData
    ze_result_t __zecall
    zetMetricTracerReadData(
        zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
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
        auto pfnReadData = context.zetDdiTable.MetricTracer.pfnReadData;

        if( nullptr == pfnReadData )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRawDataSize )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolCreate
    ze_result_t __zecall
    zetMetricQueryPoolCreate(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQueryPool.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolDestroy
    ze_result_t __zecall
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQueryPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hMetricQueryPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryCreate
    ze_result_t __zecall
    zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQuery.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phMetricQuery )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCreate( hMetricQueryPool, index, phMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryDestroy
    ze_result_t __zecall
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQuery.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryReset
    ze_result_t __zecall
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        auto pfnReset = context.zetDdiTable.MetricQuery.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReset( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    ze_result_t __zecall
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        auto pfnAppendMetricQueryBegin = context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;

        if( nullptr == pfnAppendMetricQueryBegin )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryEnd
    ze_result_t __zecall
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
        )
    {
        auto pfnAppendMetricQueryEnd = context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;

        if( nullptr == pfnAppendMetricQueryEnd )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    ze_result_t __zecall
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        auto pfnAppendMetricMemoryBarrier = context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;

        if( nullptr == pfnAppendMetricMemoryBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMetricMemoryBarrier( hCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryGetData
    ze_result_t __zecall
    zetMetricQueryGetData(
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
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
        auto pfnGetData = context.zetDdiTable.MetricQuery.pfnGetData;

        if( nullptr == pfnGetData )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRawDataSize )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetModuleGetDebugInfo
    ze_result_t __zecall
    zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        auto pfnGetDebugInfo = context.zetDdiTable.Module.pfnGetDebugInfo;

        if( nullptr == pfnGetDebugInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pSize )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetModuleGetKernelNames
    ze_result_t __zecall
    zetModuleGetKernelNames(
        zet_module_handle_t hModule,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of names available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of names.
                                                        ///< if count is larger than the number of names available, then the driver
                                                        ///< will update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
        )
    {
        auto pfnGetKernelNames = context.zetDdiTable.Module.pfnGetKernelNames;

        if( nullptr == pfnGetKernelNames )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetKernelNames( hModule, pCount, pNames );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetKernelGetProfileInfo
    ze_result_t __zecall
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
        )
    {
        auto pfnGetProfileInfo = context.zetDdiTable.Kernel.pfnGetProfileInfo;

        if( nullptr == pfnGetProfileInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pInfo )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProfileInfo( hKernel, pInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanGet
    ze_result_t __zecall
    zetSysmanGet(
        zet_device_handle_t hDevice,                    ///< [in] Handle of the device
        zet_sysman_version_t version,                   ///< [in] SMI version that application was built with
        zet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
        )
    {
        auto pfnGet = context.zetDdiTable.Sysman.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hDevice, version, phSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceGetProperties
    ze_result_t __zecall
    zetSysmanDeviceGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
        )
    {
        auto pfnDeviceGetProperties = context.zetDdiTable.Sysman.pfnDeviceGetProperties;

        if( nullptr == pfnDeviceGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetCurrentMode
    ze_result_t __zecall
    zetSysmanSchedulerGetCurrentMode(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
        )
    {
        auto pfnSchedulerGetCurrentMode = context.zetDdiTable.Sysman.pfnSchedulerGetCurrentMode;

        if( nullptr == pfnSchedulerGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSchedulerGetCurrentMode( hSysman, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetTimeoutModeProperties
    ze_result_t __zecall
    zetSysmanSchedulerGetTimeoutModeProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zet_sched_timeout_properties_t* pConfig         ///< [in] Will contain the current parameters for this mode.
        )
    {
        auto pfnSchedulerGetTimeoutModeProperties = context.zetDdiTable.Sysman.pfnSchedulerGetTimeoutModeProperties;

        if( nullptr == pfnSchedulerGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSchedulerGetTimeoutModeProperties( hSysman, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetTimesliceModeProperties
    ze_result_t __zecall
    zetSysmanSchedulerGetTimesliceModeProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zet_sched_timeslice_properties_t* pConfig       ///< [in] Will contain the current parameters for this mode.
        )
    {
        auto pfnSchedulerGetTimesliceModeProperties = context.zetDdiTable.Sysman.pfnSchedulerGetTimesliceModeProperties;

        if( nullptr == pfnSchedulerGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSchedulerGetTimesliceModeProperties( hSysman, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetTimeoutMode
    ze_result_t __zecall
    zetSysmanSchedulerSetTimeoutMode(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetTimeoutMode = context.zetDdiTable.Sysman.pfnSchedulerSetTimeoutMode;

        if( nullptr == pfnSchedulerSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSchedulerSetTimeoutMode( hSysman, pProperties, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetTimesliceMode
    ze_result_t __zecall
    zetSysmanSchedulerSetTimesliceMode(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetTimesliceMode = context.zetDdiTable.Sysman.pfnSchedulerSetTimesliceMode;

        if( nullptr == pfnSchedulerSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSchedulerSetTimesliceMode( hSysman, pProperties, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetExclusiveMode
    ze_result_t __zecall
    zetSysmanSchedulerSetExclusiveMode(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetExclusiveMode = context.zetDdiTable.Sysman.pfnSchedulerSetExclusiveMode;

        if( nullptr == pfnSchedulerSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSchedulerSetExclusiveMode( hSysman, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetComputeUnitDebugMode
    ze_result_t __zecall
    zetSysmanSchedulerSetComputeUnitDebugMode(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetComputeUnitDebugMode = context.zetDdiTable.Sysman.pfnSchedulerSetComputeUnitDebugMode;

        if( nullptr == pfnSchedulerSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSchedulerSetComputeUnitDebugMode( hSysman, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceReset
    ze_result_t __zecall
    zetSysmanDeviceReset(
        zet_sysman_handle_t hSysman                     ///< [in] SMI handle for the device
        )
    {
        auto pfnDeviceReset = context.zetDdiTable.Sysman.pfnDeviceReset;

        if( nullptr == pfnDeviceReset )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceReset( hSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceWasRepaired
    ze_result_t __zecall
    zetSysmanDeviceWasRepaired(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        ze_bool_t* pWasRepaired                         ///< [in] Will indicate if the device was repaired
        )
    {
        auto pfnDeviceWasRepaired = context.zetDdiTable.Sysman.pfnDeviceWasRepaired;

        if( nullptr == pfnDeviceWasRepaired )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pWasRepaired )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDeviceWasRepaired( hSysman, pWasRepaired );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetProperties
    ze_result_t __zecall
    zetSysmanPciGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
        )
    {
        auto pfnPciGetProperties = context.zetDdiTable.Sysman.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetState
    ze_result_t __zecall
    zetSysmanPciGetState(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
        )
    {
        auto pfnPciGetState = context.zetDdiTable.Sysman.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetState( hSysman, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetBarProperties
    ze_result_t __zecall
    zetSysmanPciGetBarProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::zet_pci_properties_t.numBars -
                                                        ///< 1]).
        zet_pci_bar_properties_t* pProperties           ///< [in] Will contain properties of the specified bar
        )
    {
        auto pfnPciGetBarProperties = context.zetDdiTable.Sysman.pfnPciGetBarProperties;

        if( nullptr == pfnPciGetBarProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetBarProperties( hSysman, barIndex, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetThroughput
    ze_result_t __zecall
    zetSysmanPciGetThroughput(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_pci_throughput_t* pThroughput               ///< [in] Will contain a snapshot of the latest throughput counters.
        )
    {
        auto pfnPciGetThroughput = context.zetDdiTable.Sysman.pfnPciGetThroughput;

        if( nullptr == pfnPciGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThroughput )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetThroughput( hSysman, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetStats
    ze_result_t __zecall
    zetSysmanPciGetStats(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        zet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        auto pfnPciGetStats = context.zetDdiTable.Sysman.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPciGetStats( hSysman, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGet
    ze_result_t __zecall
    zetSysmanPowerGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnPowerGet = context.zetDdiTable.Sysman.pfnPowerGet;

        if( nullptr == pfnPowerGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPowerGet( hSysman, pCount, phPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetProperties
    ze_result_t __zecall
    zetSysmanPowerGetProperties(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanPower.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hPower, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetEnergyCounter
    ze_result_t __zecall
    zetSysmanPowerGetEnergyCounter(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto pfnGetEnergyCounter = context.zetDdiTable.SysmanPower.pfnGetEnergyCounter;

        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEnergy )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetEnergyCounter( hPower, pEnergy );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetEnergyThreshold
    ze_result_t __zecall
    zetSysmanPowerGetEnergyThreshold(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_energy_threshold_t* pThreshold        ///< [out] The current energy threshold value in joules.
        )
    {
        auto pfnGetEnergyThreshold = context.zetDdiTable.SysmanPower.pfnGetEnergyThreshold;

        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThreshold )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetEnergyThreshold( hPower, pThreshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerSetEnergyThreshold
    ze_result_t __zecall
    zetSysmanPowerSetEnergyThreshold(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_energy_threshold_t* pThreshold        ///< [in] The energy threshold to be set in joules.
        )
    {
        auto pfnSetEnergyThreshold = context.zetDdiTable.SysmanPower.pfnSetEnergyThreshold;

        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThreshold )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetEnergyThreshold( hPower, pThreshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetLimits
    ze_result_t __zecall
    zetSysmanPowerGetLimits(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
        zet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
        zet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
        )
    {
        auto pfnGetLimits = context.zetDdiTable.SysmanPower.pfnGetLimits;

        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerSetLimits
    ze_result_t __zecall
    zetSysmanPowerSetLimits(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        const zet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const zet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const zet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        auto pfnSetLimits = context.zetDdiTable.SysmanPower.pfnSetLimits;

        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencySetFanSpeed
    ze_result_t __zecall
    zetSysmanFrequencySetFanSpeed(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_fan_control_t* pFanControl               ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnSetFanSpeed = context.zetDdiTable.SysmanFrequency.pfnSetFanSpeed;

        if( nullptr == pfnSetFanSpeed )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanControl )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetFanSpeed( hFrequency, pFanControl );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetOcCapabilities
    ze_result_t __zecall
    zetSysmanFrequencyGetOcCapabilities(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_capabilities_t* pOcCapabilities          ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnGetOcCapabilities = context.zetDdiTable.SysmanFrequency.pfnGetOcCapabilities;

        if( nullptr == pfnGetOcCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcCapabilities )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcCapabilities( hFrequency, pOcCapabilities );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetOcVrTopology
    ze_result_t __zecall
    zetSysmanFrequencyGetOcVrTopology(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_vr_topology* pOcVrTopology               ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnGetOcVrTopology = context.zetDdiTable.SysmanFrequency.pfnGetOcVrTopology;

        if( nullptr == pfnGetOcVrTopology )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcVrTopology )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcVrTopology( hFrequency, pOcVrTopology );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetOcOverrideProperties
    ze_result_t __zecall
    zetSysmanFrequencyGetOcOverrideProperties(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_settings_override_t* pOcSettingsOverride ///< [out] Pointer to the allocated structure.
        )
    {
        auto pfnGetOcOverrideProperties = context.zetDdiTable.SysmanFrequency.pfnGetOcOverrideProperties;

        if( nullptr == pfnGetOcOverrideProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcSettingsOverride )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcOverrideProperties( hFrequency, pOcSettingsOverride );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetOcIccMax
    ze_result_t __zecall
    zetSysmanFrequencyGetOcIccMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcIccMax                             ///< [out] Pointer to the allocated uint32.
        )
    {
        auto pfnGetOcIccMax = context.zetDdiTable.SysmanFrequency.pfnGetOcIccMax;

        if( nullptr == pfnGetOcIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcIccMax )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcIccMax( hFrequency, pOcIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetOcTjMax
    ze_result_t __zecall
    zetSysmanFrequencyGetOcTjMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcTjMax                              ///< [out] Pointer to the allocated uint32.
        )
    {
        auto pfnGetOcTjMax = context.zetDdiTable.SysmanFrequency.pfnGetOcTjMax;

        if( nullptr == pfnGetOcTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcTjMax )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetOcTjMax( hFrequency, pOcTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencySetOcOverrideProperties
    ze_result_t __zecall
    zetSysmanFrequencySetOcOverrideProperties(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_settings_override_t* pOcSettingsOverride ///< [in] Pointer to the allocated structure.
        )
    {
        auto pfnSetOcOverrideProperties = context.zetDdiTable.SysmanFrequency.pfnSetOcOverrideProperties;

        if( nullptr == pfnSetOcOverrideProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcSettingsOverride )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetOcOverrideProperties( hFrequency, pOcSettingsOverride );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencySetOcIccMax
    ze_result_t __zecall
    zetSysmanFrequencySetOcIccMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcIccMax                             ///< [in] Pointer to the allocated uint32.
        )
    {
        auto pfnSetOcIccMax = context.zetDdiTable.SysmanFrequency.pfnSetOcIccMax;

        if( nullptr == pfnSetOcIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcIccMax )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetOcIccMax( hFrequency, pOcIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencySetOcTjMax
    ze_result_t __zecall
    zetSysmanFrequencySetOcTjMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        uint32_t* pOcTjMax                              ///< [in] Pointer to the allocated uint32.
        )
    {
        auto pfnSetOcTjMax = context.zetDdiTable.SysmanFrequency.pfnSetOcTjMax;

        if( nullptr == pfnSetOcTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pOcTjMax )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetOcTjMax( hFrequency, pOcTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGet
    ze_result_t __zecall
    zetSysmanFrequencyGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFrequencyGet = context.zetDdiTable.Sysman.pfnFrequencyGet;

        if( nullptr == pfnFrequencyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFrequencyGet( hSysman, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetProperties
    ze_result_t __zecall
    zetSysmanFrequencyGetProperties(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanFrequency.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hFrequency, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetRange
    ze_result_t __zecall
    zetSysmanFrequencyGetRange(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_range_t* pLimits                       ///< [in] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetRange = context.zetDdiTable.SysmanFrequency.pfnGetRange;

        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencySetRange
    ze_result_t __zecall
    zetSysmanFrequencySetRange(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        const zet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnSetRange = context.zetDdiTable.SysmanFrequency.pfnSetRange;

        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetState
    ze_result_t __zecall
    zetSysmanFrequencyGetState(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanFrequency.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hFrequency, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetThrottleTime
    ze_result_t __zecall
    zetSysmanFrequencyGetThrottleTime(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetThrottleTime = context.zetDdiTable.SysmanFrequency.pfnGetThrottleTime;

        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThrottleTime )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetThrottleTime( hFrequency, pThrottleTime );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGet
    ze_result_t __zecall
    zetSysmanEngineGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnEngineGet = context.zetDdiTable.Sysman.pfnEngineGet;

        if( nullptr == pfnEngineGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEngineGet( hSysman, pCount, phEngine );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetProperties
    ze_result_t __zecall
    zetSysmanEngineGetProperties(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanEngine.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hEngine, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetActivity
    ze_result_t __zecall
    zetSysmanEngineGetActivity(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        auto pfnGetActivity = context.zetDdiTable.SysmanEngine.pfnGetActivity;

        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetActivity( hEngine, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGet
    ze_result_t __zecall
    zetSysmanStandbyGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnStandbyGet = context.zetDdiTable.Sysman.pfnStandbyGet;

        if( nullptr == pfnStandbyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnStandbyGet( hSysman, pCount, phStandby );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetProperties
    ze_result_t __zecall
    zetSysmanStandbyGetProperties(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanStandby.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hStandby, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetMode
    ze_result_t __zecall
    zetSysmanStandbyGetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
        )
    {
        auto pfnGetMode = context.zetDdiTable.SysmanStandby.pfnGetMode;

        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMode( hStandby, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbySetMode
    ze_result_t __zecall
    zetSysmanStandbySetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        auto pfnSetMode = context.zetDdiTable.SysmanStandby.pfnSetMode;

        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetMode( hStandby, mode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGet
    ze_result_t __zecall
    zetSysmanFirmwareGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFirmwareGet = context.zetDdiTable.Sysman.pfnFirmwareGet;

        if( nullptr == pfnFirmwareGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFirmwareGet( hSysman, pCount, phFirmware );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetProperties
    ze_result_t __zecall
    zetSysmanFirmwareGetProperties(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        zet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanFirmware.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hFirmware, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetChecksum
    ze_result_t __zecall
    zetSysmanFirmwareGetChecksum(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        auto pfnGetChecksum = context.zetDdiTable.SysmanFirmware.pfnGetChecksum;

        if( nullptr == pfnGetChecksum )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pChecksum )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetChecksum( hFirmware, pChecksum );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareFlash
    ze_result_t __zecall
    zetSysmanFirmwareFlash(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto pfnFlash = context.zetDdiTable.SysmanFirmware.pfnFlash;

        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pImage )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFlash( hFirmware, pImage, size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGet
    ze_result_t __zecall
    zetSysmanMemoryGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnMemoryGet = context.zetDdiTable.Sysman.pfnMemoryGet;

        if( nullptr == pfnMemoryGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnMemoryGet( hSysman, pCount, phMemory );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetProperties
    ze_result_t __zecall
    zetSysmanMemoryGetProperties(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanMemory.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hMemory, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetBandwidth
    ze_result_t __zecall
    zetSysmanMemoryGetBandwidth(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        auto pfnGetBandwidth = context.zetDdiTable.SysmanMemory.pfnGetBandwidth;

        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pBandwidth )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetBandwidth( hMemory, pBandwidth );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetAllocated
    ze_result_t __zecall
    zetSysmanMemoryGetAllocated(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
        )
    {
        auto pfnGetAllocated = context.zetDdiTable.SysmanMemory.pfnGetAllocated;

        if( nullptr == pfnGetAllocated )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pAllocated )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAllocated( hMemory, pAllocated );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkSwitchGet
    ze_result_t __zecall
    zetSysmanLinkSwitchGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_link_switch_handle_t* phSwitch       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnLinkSwitchGet = context.zetDdiTable.Sysman.pfnLinkSwitchGet;

        if( nullptr == pfnLinkSwitchGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnLinkSwitchGet( hSysman, pCount, phSwitch );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkSwitchGetProperties
    ze_result_t __zecall
    zetSysmanLinkSwitchGetProperties(
        zet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        zet_link_switch_properties_t* pProperties       ///< [in] Will contain the Switch properties.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanLinkSwitch.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSwitch )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hSwitch, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkSwitchGetState
    ze_result_t __zecall
    zetSysmanLinkSwitchGetState(
        zet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        zet_link_switch_state_t* pState                 ///< [in] Will contain the current state of the switch (enabled/disabled).
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanLinkSwitch.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSwitch )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hSwitch, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkSwitchSetState
    ze_result_t __zecall
    zetSysmanLinkSwitchSetState(
        zet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
        ze_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
        )
    {
        auto pfnSetState = context.zetDdiTable.SysmanLinkSwitch.pfnSetState;

        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSwitch )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetState( hSwitch, enable );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkSwitchGetPorts
    ze_result_t __zecall
    zetSysmanLinkSwitchGetPorts(
        zet_sysman_link_switch_handle_t hSysmanLinkSwitch,  ///< [in] SMI handle of the connectivity switch.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_link_port_handle_t* phPort           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnGetPorts = context.zetDdiTable.SysmanLinkSwitch.pfnGetPorts;

        if( nullptr == pfnGetPorts )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysmanLinkSwitch )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPorts( hSysmanLinkSwitch, pCount, phPort );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkPortGetProperties
    ze_result_t __zecall
    zetSysmanLinkPortGetProperties(
        zet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        zet_link_port_properties_t* pProperties         ///< [in] Will contain properties of the Switch Port
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanLinkPort.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hPort, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkPortGetState
    ze_result_t __zecall
    zetSysmanLinkPortGetState(
        zet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        zet_link_port_state_t* pState                   ///< [in] Will contain the current state of the Switch Port
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanLinkPort.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hPort, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkPortGetThroughput
    ze_result_t __zecall
    zetSysmanLinkPortGetThroughput(
        zet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        zet_link_port_throughput_t* pThroughput         ///< [in] Will contain the Switch port throughput counters.
        )
    {
        auto pfnGetThroughput = context.zetDdiTable.SysmanLinkPort.pfnGetThroughput;

        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pThroughput )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetThroughput( hPort, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkPortGetStats
    ze_result_t __zecall
    zetSysmanLinkPortGetStats(
        zet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
        zet_link_port_stats_t* pStats                   ///< [in] Will contain the Switch port stats.
        )
    {
        auto pfnGetStats = context.zetDdiTable.SysmanLinkPort.pfnGetStats;

        if( nullptr == pfnGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetStats( hPort, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLinkPortIsConnected
    ze_result_t __zecall
    zetSysmanLinkPortIsConnected(
        zet_sysman_link_port_handle_t hPort,            ///< [in] Handle of the local connectivity port.
        zet_sysman_link_port_handle_t hRemotePort,      ///< [in] Handle of the remote connectivity port.
        ze_bool_t* pConnected                           ///< [in] Will indicate connected to the remote port.
        )
    {
        auto pfnIsConnected = context.zetDdiTable.SysmanLinkPort.pfnIsConnected;

        if( nullptr == pfnIsConnected )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hRemotePort )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConnected )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnIsConnected( hPort, hRemotePort, pConnected );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGet
    ze_result_t __zecall
    zetSysmanTemperatureGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnTemperatureGet = context.zetDdiTable.Sysman.pfnTemperatureGet;

        if( nullptr == pfnTemperatureGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnTemperatureGet( hSysman, pCount, phTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetProperties
    ze_result_t __zecall
    zetSysmanTemperatureGetProperties(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanTemperature.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hTemperature, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureRead
    ze_result_t __zecall
    zetSysmanTemperatureRead(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
        )
    {
        auto pfnRead = context.zetDdiTable.SysmanTemperature.pfnRead;

        if( nullptr == pfnRead )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTemperature )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRead( hTemperature, pTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGet
    ze_result_t __zecall
    zetSysmanPsuGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnPsuGet = context.zetDdiTable.Sysman.pfnPsuGet;

        if( nullptr == pfnPsuGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnPsuGet( hSysman, pCount, phPsu );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetProperties
    ze_result_t __zecall
    zetSysmanPsuGetProperties(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanPsu.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hPsu, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetState
    ze_result_t __zecall
    zetSysmanPsuGetState(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanPsu.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hPsu, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGet
    ze_result_t __zecall
    zetSysmanFanGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFanGet = context.zetDdiTable.Sysman.pfnFanGet;

        if( nullptr == pfnFanGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGet( hSysman, pCount, phFan );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetProperties
    ze_result_t __zecall
    zetSysmanFanGetProperties(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanFan.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hFan, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetConfig
    ze_result_t __zecall
    zetSysmanFanGetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        auto pfnGetConfig = context.zetDdiTable.SysmanFan.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanSetConfig
    ze_result_t __zecall
    zetSysmanFanSetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        auto pfnSetConfig = context.zetDdiTable.SysmanFan.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetState
    ze_result_t __zecall
    zetSysmanFanGetState(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        zet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanFan.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hFan, units, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGet
    ze_result_t __zecall
    zetSysmanLedGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnLedGet = context.zetDdiTable.Sysman.pfnLedGet;

        if( nullptr == pfnLedGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnLedGet( hSysman, pCount, phLed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetProperties
    ze_result_t __zecall
    zetSysmanLedGetProperties(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanLed.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hLed, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetState
    ze_result_t __zecall
    zetSysmanLedGetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanLed.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedSetState
    ze_result_t __zecall
    zetSysmanLedSetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const zet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        auto pfnSetState = context.zetDdiTable.SysmanLed.pfnSetState;

        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGet
    ze_result_t __zecall
    zetSysmanRasGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnRasGet = context.zetDdiTable.Sysman.pfnRasGet;

        if( nullptr == pfnRasGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRasGet( hSysman, pCount, phRas );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetProperties
    ze_result_t __zecall
    zetSysmanRasGetProperties(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanRas.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hRas, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetErrors
    ze_result_t __zecall
    zetSysmanRasGetErrors(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
        zet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        auto pfnGetErrors = context.zetDdiTable.SysmanRas.pfnGetErrors;

        if( nullptr == pfnGetErrors )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTotalErrors )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetErrors( hRas, clear, pTotalErrors, pDetails );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventsGetProperties
    ze_result_t __zecall
    zetSysmanEventsGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        zet_event_properties_t* pProperties             ///< [in] Structure describing event properties
        )
    {
        auto pfnEventsGetProperties = context.zetDdiTable.Sysman.pfnEventsGetProperties;

        if( nullptr == pfnEventsGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventsRegister
    ze_result_t __zecall
    zetSysmanEventsRegister(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be registered.
        zet_event_request_t* pEvents                    ///< [in][optional] Events to register.
        )
    {
        auto pfnEventsRegister = context.zetDdiTable.Sysman.pfnEventsRegister;

        if( nullptr == pfnEventsRegister )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsRegister( hSysman, count, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventsUnregister
    ze_result_t __zecall
    zetSysmanEventsUnregister(
        zet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be unregistered.
        zet_event_request_t* pEvents                    ///< [in][optional] Events to unregister.
        )
    {
        auto pfnEventsUnregister = context.zetDdiTable.Sysman.pfnEventsUnregister;

        if( nullptr == pfnEventsUnregister )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsUnregister( hSysman, count, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventsListen
    ze_result_t __zecall
    zetSysmanEventsListen(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                        ///< device for which the application has registered to receive
                                                        ///< notifications.
        ze_bool_t clear,                                ///< [in] Clear the event status.
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                        ///< check status and return immediately. Set to ::ZET_EVENT_WAIT_INFINITE
                                                        ///< to block until events arrive.
        uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::zet_sysman_event_type_t) that have been
                                                        ///< triggered.
        )
    {
        auto pfnEventsListen = context.zetDdiTable.Sysman.pfnEventsListen;

        if( nullptr == pfnEventsListen )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pEvents )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEventsListen( hSysman, clear, timeout, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGet
    ze_result_t __zecall
    zetSysmanDiagnosticsGet(
        zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnDiagnosticsGet = context.zetDdiTable.Sysman.pfnDiagnosticsGet;

        if( nullptr == pfnDiagnosticsGet )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGetProperties
    ze_result_t __zecall
    zetSysmanDiagnosticsGetProperties(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        zet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanDiagnostics.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hDiagnostics, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsRunTests
    ze_result_t __zecall
    zetSysmanDiagnosticsRunTests(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
        )
    {
        auto pfnRunTests = context.zetDdiTable.SysmanDiagnostics.pfnRunTests;

        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pResult )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRunTests( hDiagnostics, start, end, pResult );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerCreate
    ze_result_t __zecall
    zetTracerCreate(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
        zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
        )
    {
        auto pfnCreate = context.zetDdiTable.Tracer.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( ZET_TRACER_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, desc, phTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerDestroy
    ze_result_t __zecall
    zetTracerDestroy(
        zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
        )
    {
        auto pfnDestroy = context.zetDdiTable.Tracer.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetPrologues
    ze_result_t __zecall
    zetTracerSetPrologues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
        zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        auto pfnSetPrologues = context.zetDdiTable.Tracer.pfnSetPrologues;

        if( nullptr == pfnSetPrologues )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCoreCbs )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPrologues( hTracer, pCoreCbs, pExperimentalCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEpilogues
    ze_result_t __zecall
    zetTracerSetEpilogues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
        zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        auto pfnSetEpilogues = context.zetDdiTable.Tracer.pfnSetEpilogues;

        if( nullptr == pfnSetEpilogues )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCoreCbs )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetEpilogues( hTracer, pCoreCbs, pExperimentalCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEnabled
    ze_result_t __zecall
    zetTracerSetEnabled(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        auto pfnSetEnabled = context.zetDdiTable.Tracer.pfnSetEnabled;

        if( nullptr == pfnSetEnabled )
            return ZE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = layer::zetInit;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnActivateMetricGroups                     = pDdiTable->pfnActivateMetricGroups;
    pDdiTable->pfnActivateMetricGroups                   = layer::zetDeviceActivateMetricGroups;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAppendMetricTracerMarker                 = pDdiTable->pfnAppendMetricTracerMarker;
    pDdiTable->pfnAppendMetricTracerMarker               = layer::zetCommandListAppendMetricTracerMarker;

    dditable.pfnAppendMetricQueryBegin                   = pDdiTable->pfnAppendMetricQueryBegin;
    pDdiTable->pfnAppendMetricQueryBegin                 = layer::zetCommandListAppendMetricQueryBegin;

    dditable.pfnAppendMetricQueryEnd                     = pDdiTable->pfnAppendMetricQueryEnd;
    pDdiTable->pfnAppendMetricQueryEnd                   = layer::zetCommandListAppendMetricQueryEnd;

    dditable.pfnAppendMetricMemoryBarrier                = pDdiTable->pfnAppendMetricMemoryBarrier;
    pDdiTable->pfnAppendMetricMemoryBarrier              = layer::zetCommandListAppendMetricMemoryBarrier;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetDebugInfo                             = pDdiTable->pfnGetDebugInfo;
    pDdiTable->pfnGetDebugInfo                           = layer::zetModuleGetDebugInfo;

    dditable.pfnGetKernelNames                           = pDdiTable->pfnGetKernelNames;
    pDdiTable->pfnGetKernelNames                         = layer::zetModuleGetKernelNames;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProfileInfo                           = pDdiTable->pfnGetProfileInfo;
    pDdiTable->pfnGetProfileInfo                         = layer::zetKernelGetProfileInfo;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricGroup;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zetMetricGroupGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetMetricGroupGetProperties;

    dditable.pfnCalculateMetricValues                    = pDdiTable->pfnCalculateMetricValues;
    pDdiTable->pfnCalculateMetricValues                  = layer::zetMetricGroupCalculateMetricValues;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Metric;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zetMetricGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetMetricGetProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetMetricTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricTracer;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnOpen                                     = pDdiTable->pfnOpen;
    pDdiTable->pfnOpen                                   = layer::zetMetricTracerOpen;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = layer::zetMetricTracerClose;

    dditable.pfnReadData                                 = pDdiTable->pfnReadData;
    pDdiTable->pfnReadData                               = layer::zetMetricTracerReadData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricQueryPool;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zetMetricQueryPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zetMetricQueryPoolDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricQuery;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zetMetricQueryCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zetMetricQueryDestroy;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::zetMetricQueryReset;

    dditable.pfnGetData                                  = pDdiTable->pfnGetData;
    pDdiTable->pfnGetData                                = layer::zetMetricQueryGetData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Tracer;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zetTracerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zetTracerDestroy;

    dditable.pfnSetPrologues                             = pDdiTable->pfnSetPrologues;
    pDdiTable->pfnSetPrologues                           = layer::zetTracerSetPrologues;

    dditable.pfnSetEpilogues                             = pDdiTable->pfnSetEpilogues;
    pDdiTable->pfnSetEpilogues                           = layer::zetTracerSetEpilogues;

    dditable.pfnSetEnabled                               = pDdiTable->pfnSetEnabled;
    pDdiTable->pfnSetEnabled                             = layer::zetTracerSetEnabled;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Sysman;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zetSysmanGet;

    dditable.pfnDeviceGetProperties                      = pDdiTable->pfnDeviceGetProperties;
    pDdiTable->pfnDeviceGetProperties                    = layer::zetSysmanDeviceGetProperties;

    dditable.pfnSchedulerGetCurrentMode                  = pDdiTable->pfnSchedulerGetCurrentMode;
    pDdiTable->pfnSchedulerGetCurrentMode                = layer::zetSysmanSchedulerGetCurrentMode;

    dditable.pfnSchedulerGetTimeoutModeProperties        = pDdiTable->pfnSchedulerGetTimeoutModeProperties;
    pDdiTable->pfnSchedulerGetTimeoutModeProperties      = layer::zetSysmanSchedulerGetTimeoutModeProperties;

    dditable.pfnSchedulerGetTimesliceModeProperties      = pDdiTable->pfnSchedulerGetTimesliceModeProperties;
    pDdiTable->pfnSchedulerGetTimesliceModeProperties    = layer::zetSysmanSchedulerGetTimesliceModeProperties;

    dditable.pfnSchedulerSetTimeoutMode                  = pDdiTable->pfnSchedulerSetTimeoutMode;
    pDdiTable->pfnSchedulerSetTimeoutMode                = layer::zetSysmanSchedulerSetTimeoutMode;

    dditable.pfnSchedulerSetTimesliceMode                = pDdiTable->pfnSchedulerSetTimesliceMode;
    pDdiTable->pfnSchedulerSetTimesliceMode              = layer::zetSysmanSchedulerSetTimesliceMode;

    dditable.pfnSchedulerSetExclusiveMode                = pDdiTable->pfnSchedulerSetExclusiveMode;
    pDdiTable->pfnSchedulerSetExclusiveMode              = layer::zetSysmanSchedulerSetExclusiveMode;

    dditable.pfnSchedulerSetComputeUnitDebugMode         = pDdiTable->pfnSchedulerSetComputeUnitDebugMode;
    pDdiTable->pfnSchedulerSetComputeUnitDebugMode       = layer::zetSysmanSchedulerSetComputeUnitDebugMode;

    dditable.pfnDeviceReset                              = pDdiTable->pfnDeviceReset;
    pDdiTable->pfnDeviceReset                            = layer::zetSysmanDeviceReset;

    dditable.pfnDeviceWasRepaired                        = pDdiTable->pfnDeviceWasRepaired;
    pDdiTable->pfnDeviceWasRepaired                      = layer::zetSysmanDeviceWasRepaired;

    dditable.pfnPciGetProperties                         = pDdiTable->pfnPciGetProperties;
    pDdiTable->pfnPciGetProperties                       = layer::zetSysmanPciGetProperties;

    dditable.pfnPciGetState                              = pDdiTable->pfnPciGetState;
    pDdiTable->pfnPciGetState                            = layer::zetSysmanPciGetState;

    dditable.pfnPciGetBarProperties                      = pDdiTable->pfnPciGetBarProperties;
    pDdiTable->pfnPciGetBarProperties                    = layer::zetSysmanPciGetBarProperties;

    dditable.pfnPciGetThroughput                         = pDdiTable->pfnPciGetThroughput;
    pDdiTable->pfnPciGetThroughput                       = layer::zetSysmanPciGetThroughput;

    dditable.pfnPciGetStats                              = pDdiTable->pfnPciGetStats;
    pDdiTable->pfnPciGetStats                            = layer::zetSysmanPciGetStats;

    dditable.pfnPowerGet                                 = pDdiTable->pfnPowerGet;
    pDdiTable->pfnPowerGet                               = layer::zetSysmanPowerGet;

    dditable.pfnFrequencyGet                             = pDdiTable->pfnFrequencyGet;
    pDdiTable->pfnFrequencyGet                           = layer::zetSysmanFrequencyGet;

    dditable.pfnEngineGet                                = pDdiTable->pfnEngineGet;
    pDdiTable->pfnEngineGet                              = layer::zetSysmanEngineGet;

    dditable.pfnStandbyGet                               = pDdiTable->pfnStandbyGet;
    pDdiTable->pfnStandbyGet                             = layer::zetSysmanStandbyGet;

    dditable.pfnFirmwareGet                              = pDdiTable->pfnFirmwareGet;
    pDdiTable->pfnFirmwareGet                            = layer::zetSysmanFirmwareGet;

    dditable.pfnMemoryGet                                = pDdiTable->pfnMemoryGet;
    pDdiTable->pfnMemoryGet                              = layer::zetSysmanMemoryGet;

    dditable.pfnLinkSwitchGet                            = pDdiTable->pfnLinkSwitchGet;
    pDdiTable->pfnLinkSwitchGet                          = layer::zetSysmanLinkSwitchGet;

    dditable.pfnTemperatureGet                           = pDdiTable->pfnTemperatureGet;
    pDdiTable->pfnTemperatureGet                         = layer::zetSysmanTemperatureGet;

    dditable.pfnPsuGet                                   = pDdiTable->pfnPsuGet;
    pDdiTable->pfnPsuGet                                 = layer::zetSysmanPsuGet;

    dditable.pfnFanGet                                   = pDdiTable->pfnFanGet;
    pDdiTable->pfnFanGet                                 = layer::zetSysmanFanGet;

    dditable.pfnLedGet                                   = pDdiTable->pfnLedGet;
    pDdiTable->pfnLedGet                                 = layer::zetSysmanLedGet;

    dditable.pfnRasGet                                   = pDdiTable->pfnRasGet;
    pDdiTable->pfnRasGet                                 = layer::zetSysmanRasGet;

    dditable.pfnEventsGetProperties                      = pDdiTable->pfnEventsGetProperties;
    pDdiTable->pfnEventsGetProperties                    = layer::zetSysmanEventsGetProperties;

    dditable.pfnEventsRegister                           = pDdiTable->pfnEventsRegister;
    pDdiTable->pfnEventsRegister                         = layer::zetSysmanEventsRegister;

    dditable.pfnEventsUnregister                         = pDdiTable->pfnEventsUnregister;
    pDdiTable->pfnEventsUnregister                       = layer::zetSysmanEventsUnregister;

    dditable.pfnEventsListen                             = pDdiTable->pfnEventsListen;
    pDdiTable->pfnEventsListen                           = layer::zetSysmanEventsListen;

    dditable.pfnDiagnosticsGet                           = pDdiTable->pfnDiagnosticsGet;
    pDdiTable->pfnDiagnosticsGet                         = layer::zetSysmanDiagnosticsGet;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanPower;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanPowerGetProperties;

    dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
    pDdiTable->pfnGetEnergyCounter                       = layer::zetSysmanPowerGetEnergyCounter;

    dditable.pfnGetEnergyThreshold                       = pDdiTable->pfnGetEnergyThreshold;
    pDdiTable->pfnGetEnergyThreshold                     = layer::zetSysmanPowerGetEnergyThreshold;

    dditable.pfnSetEnergyThreshold                       = pDdiTable->pfnSetEnergyThreshold;
    pDdiTable->pfnSetEnergyThreshold                     = layer::zetSysmanPowerSetEnergyThreshold;

    dditable.pfnGetLimits                                = pDdiTable->pfnGetLimits;
    pDdiTable->pfnGetLimits                              = layer::zetSysmanPowerGetLimits;

    dditable.pfnSetLimits                                = pDdiTable->pfnSetLimits;
    pDdiTable->pfnSetLimits                              = layer::zetSysmanPowerSetLimits;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanFrequency;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnSetFanSpeed                              = pDdiTable->pfnSetFanSpeed;
    pDdiTable->pfnSetFanSpeed                            = layer::zetSysmanFrequencySetFanSpeed;

    dditable.pfnGetOcCapabilities                        = pDdiTable->pfnGetOcCapabilities;
    pDdiTable->pfnGetOcCapabilities                      = layer::zetSysmanFrequencyGetOcCapabilities;

    dditable.pfnGetOcVrTopology                          = pDdiTable->pfnGetOcVrTopology;
    pDdiTable->pfnGetOcVrTopology                        = layer::zetSysmanFrequencyGetOcVrTopology;

    dditable.pfnGetOcOverrideProperties                  = pDdiTable->pfnGetOcOverrideProperties;
    pDdiTable->pfnGetOcOverrideProperties                = layer::zetSysmanFrequencyGetOcOverrideProperties;

    dditable.pfnGetOcIccMax                              = pDdiTable->pfnGetOcIccMax;
    pDdiTable->pfnGetOcIccMax                            = layer::zetSysmanFrequencyGetOcIccMax;

    dditable.pfnGetOcTjMax                               = pDdiTable->pfnGetOcTjMax;
    pDdiTable->pfnGetOcTjMax                             = layer::zetSysmanFrequencyGetOcTjMax;

    dditable.pfnSetOcOverrideProperties                  = pDdiTable->pfnSetOcOverrideProperties;
    pDdiTable->pfnSetOcOverrideProperties                = layer::zetSysmanFrequencySetOcOverrideProperties;

    dditable.pfnSetOcIccMax                              = pDdiTable->pfnSetOcIccMax;
    pDdiTable->pfnSetOcIccMax                            = layer::zetSysmanFrequencySetOcIccMax;

    dditable.pfnSetOcTjMax                               = pDdiTable->pfnSetOcTjMax;
    pDdiTable->pfnSetOcTjMax                             = layer::zetSysmanFrequencySetOcTjMax;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanFrequencyGetProperties;

    dditable.pfnGetRange                                 = pDdiTable->pfnGetRange;
    pDdiTable->pfnGetRange                               = layer::zetSysmanFrequencyGetRange;

    dditable.pfnSetRange                                 = pDdiTable->pfnSetRange;
    pDdiTable->pfnSetRange                               = layer::zetSysmanFrequencySetRange;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanFrequencyGetState;

    dditable.pfnGetThrottleTime                          = pDdiTable->pfnGetThrottleTime;
    pDdiTable->pfnGetThrottleTime                        = layer::zetSysmanFrequencyGetThrottleTime;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanEngine;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanEngineGetProperties;

    dditable.pfnGetActivity                              = pDdiTable->pfnGetActivity;
    pDdiTable->pfnGetActivity                            = layer::zetSysmanEngineGetActivity;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanStandby;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanStandbyGetProperties;

    dditable.pfnGetMode                                  = pDdiTable->pfnGetMode;
    pDdiTable->pfnGetMode                                = layer::zetSysmanStandbyGetMode;

    dditable.pfnSetMode                                  = pDdiTable->pfnSetMode;
    pDdiTable->pfnSetMode                                = layer::zetSysmanStandbySetMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanFirmware;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanFirmwareGetProperties;

    dditable.pfnGetChecksum                              = pDdiTable->pfnGetChecksum;
    pDdiTable->pfnGetChecksum                            = layer::zetSysmanFirmwareGetChecksum;

    dditable.pfnFlash                                    = pDdiTable->pfnFlash;
    pDdiTable->pfnFlash                                  = layer::zetSysmanFirmwareFlash;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanMemory;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanMemoryGetProperties;

    dditable.pfnGetBandwidth                             = pDdiTable->pfnGetBandwidth;
    pDdiTable->pfnGetBandwidth                           = layer::zetSysmanMemoryGetBandwidth;

    dditable.pfnGetAllocated                             = pDdiTable->pfnGetAllocated;
    pDdiTable->pfnGetAllocated                           = layer::zetSysmanMemoryGetAllocated;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLinkSwitch table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanLinkSwitchProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_link_switch_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanLinkSwitch;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanLinkSwitchGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanLinkSwitchGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = layer::zetSysmanLinkSwitchSetState;

    dditable.pfnGetPorts                                 = pDdiTable->pfnGetPorts;
    pDdiTable->pfnGetPorts                               = layer::zetSysmanLinkSwitchGetPorts;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLinkPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanLinkPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_link_port_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanLinkPort;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanLinkPortGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanLinkPortGetState;

    dditable.pfnGetThroughput                            = pDdiTable->pfnGetThroughput;
    pDdiTable->pfnGetThroughput                          = layer::zetSysmanLinkPortGetThroughput;

    dditable.pfnGetStats                                 = pDdiTable->pfnGetStats;
    pDdiTable->pfnGetStats                               = layer::zetSysmanLinkPortGetStats;

    dditable.pfnIsConnected                              = pDdiTable->pfnIsConnected;
    pDdiTable->pfnIsConnected                            = layer::zetSysmanLinkPortIsConnected;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanTemperature;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanTemperatureGetProperties;

    dditable.pfnRead                                     = pDdiTable->pfnRead;
    pDdiTable->pfnRead                                   = layer::zetSysmanTemperatureRead;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanPsu;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanPsuGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanPsuGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanFan;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanFanGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zetSysmanFanGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zetSysmanFanSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanFanGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanLed;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanLedGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanLedGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = layer::zetSysmanLedSetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanRas;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanRasGetProperties;

    dditable.pfnGetErrors                                = pDdiTable->pfnGetErrors;
    pDdiTable->pfnGetErrors                              = layer::zetSysmanRasGetErrors;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zetGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanDiagnostics;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanDiagnosticsGetProperties;

    dditable.pfnRunTests                                 = pDdiTable->pfnRunTests;
    pDdiTable->pfnRunTests                               = layer::zetSysmanDiagnosticsRunTests;

    return result;
}

#if defined(__cplusplus)
};
#endif
