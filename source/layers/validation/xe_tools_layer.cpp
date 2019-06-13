/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
* The source code contained or described herein and all documents related to the  
* source code ("Material") are owned by Intel Corporation or its suppliers or  
* licensors. Title to the Material remains with Intel Corporation or its suppliers  
* and licensors. The Material contains trade secrets and proprietary and confidential  
* information of Intel or its suppliers and licensors. The Material is protected by  
* worldwide copyright and trade secret laws and treaty provisions. No part of the  
* Material may be used, copied, reproduced, modified, published, uploaded, posted  
* transmitted, distributed, or disclosed in any way without Intel's prior express  
* written permission.  
*
* No license under any patent, copyright, trade secret or other intellectual  
* property right is granted to or conferred upon you by disclosure or delivery  
* of the Materials, either expressly, by implication, inducement, estoppel  
* or otherwise. Any license under such intellectual property rights must be  
* express and approved by Intel in writing.  
* @endcond
*
* @file xe_tools_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/valddi.cpp.mako
* @endcond
*
******************************************************************************/
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
        xet_metric_group_handle_t* phMetricGroups       ///< [in][range(0, count)] handles of the metric groups to activate. NULL
                                                        ///< to deactivate.
        )
    {
        auto pfnActivateMetricGroups = context.xetDdiTable.Device.pfnActivateMetricGroups;

        if( nullptr == pfnActivateMetricGroups )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phMetricGroups )
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
    /// @brief Intercept function for xetPowerCreate
    xe_result_t __xecall
    xetPowerCreate(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device object
        uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
        xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
        )
    {
        auto pfnCreate = context.xetDdiTable.Power.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pPowerHandle )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCreate( hDevice, flags, pPowerHandle );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerDestroy
    xe_result_t __xecall
    xetPowerDestroy(
        xet_power_handle_t hPower                       ///< [in][release] handle of the power object to destroy
        )
    {
        auto pfnDestroy = context.xetDdiTable.Power.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetAveragePowerLimit
    xe_result_t __xecall
    xetPowerGetAveragePowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
        )
    {
        auto pfnGetAveragePowerLimit = context.xetDdiTable.Power.pfnGetAveragePowerLimit;

        if( nullptr == pfnGetAveragePowerLimit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimit )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAveragePowerLimit( hPower, pLimit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetBurstPowerLimit
    xe_result_t __xecall
    xetPowerGetBurstPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
        )
    {
        auto pfnGetBurstPowerLimit = context.xetDdiTable.Power.pfnGetBurstPowerLimit;

        if( nullptr == pfnGetBurstPowerLimit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimit )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetBurstPowerLimit( hPower, pLimit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetPeakPowerLimit
    xe_result_t __xecall
    xetPowerGetPeakPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
        )
    {
        auto pfnGetPeakPowerLimit = context.xetDdiTable.Power.pfnGetPeakPowerLimit;

        if( nullptr == pfnGetPeakPowerLimit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimit )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetPeakPowerLimit( hPower, pLimit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetAllPowerLimits
    xe_result_t __xecall
    xetPowerGetAllPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
        )
    {
        auto pfnGetAllPowerLimits = context.xetDdiTable.Power.pfnGetAllPowerLimits;

        if( nullptr == pfnGetAllPowerLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAllPowerLimits( hPower, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetDefaultPowerLimits
    xe_result_t __xecall
    xetPowerGetDefaultPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
        )
    {
        auto pfnGetDefaultPowerLimits = context.xetDdiTable.Power.pfnGetDefaultPowerLimits;

        if( nullptr == pfnGetDefaultPowerLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDefaultPowerLimits( hPower, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetAveragePowerLimit
    xe_result_t __xecall
    xetPowerSetAveragePowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
        )
    {
        auto pfnSetAveragePowerLimit = context.xetDdiTable.Power.pfnSetAveragePowerLimit;

        if( nullptr == pfnSetAveragePowerLimit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimit )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetAveragePowerLimit( hPower, pLimit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetBurstPowerLimit
    xe_result_t __xecall
    xetPowerSetBurstPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
        )
    {
        auto pfnSetBurstPowerLimit = context.xetDdiTable.Power.pfnSetBurstPowerLimit;

        if( nullptr == pfnSetBurstPowerLimit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimit )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetBurstPowerLimit( hPower, pLimit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetPeakPowerLimit
    xe_result_t __xecall
    xetPowerSetPeakPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
        )
    {
        auto pfnSetPeakPowerLimit = context.xetDdiTable.Power.pfnSetPeakPowerLimit;

        if( nullptr == pfnSetPeakPowerLimit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimit )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPeakPowerLimit( hPower, pLimit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetPowerLimits
    xe_result_t __xecall
    xetPowerSetPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
        )
    {
        auto pfnSetPowerLimits = context.xetDdiTable.Power.pfnSetPowerLimits;

        if( nullptr == pfnSetPowerLimits )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLimits )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetPowerLimits( hPower, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetEnergyCounter
    xe_result_t __xecall
    xetPowerGetEnergyCounter(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
        )
    {
        auto pfnGetEnergyCounter = context.xetDdiTable.Power.pfnGetEnergyCounter;

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
    /// @brief Intercept function for xetPowerGetTurboMode
    xe_result_t __xecall
    xetPowerGetTurboMode(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
        )
    {
        auto pfnGetTurboMode = context.xetDdiTable.Power.pfnGetTurboMode;

        if( nullptr == pfnGetTurboMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTurboMode )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetTurboMode( hPower, pTurboMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetTurboMode
    xe_result_t __xecall
    xetPowerSetTurboMode(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
        )
    {
        auto pfnSetTurboMode = context.xetDdiTable.Power.pfnSetTurboMode;

        if( nullptr == pfnSetTurboMode )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetTurboMode( hPower, pTurboMode );
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
        auto pfnGet = context.xetDdiTable.FreqDomain.pfnGet;

        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hPower, pCount, phFreqDomain );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetProperties
    xe_result_t __xecall
    xetFreqDomainGetProperties(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
        )
    {
        auto pfnGetProperties = context.xetDdiTable.FreqDomain.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFreqDomainProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetProperties( hFreqDomain, pFreqDomainProperties );
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
        auto pfnGetSourceFreqDomain = context.xetDdiTable.FreqDomain.pfnGetSourceFreqDomain;

        if( nullptr == pfnGetSourceFreqDomain )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phSrcFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetSourceFreqDomain( hFreqDomain, phSrcFreqDomain );
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
        auto pfnGetSupportedClocks = context.xetDdiTable.FreqDomain.pfnGetSupportedClocks;

        if( nullptr == pfnGetSupportedClocks )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pClocks )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetSupportedClocks( hFreqDomain, numClockPoints, pClocks );
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
        auto pfnGetSupportedClockDividers = context.xetDdiTable.FreqDomain.pfnGetSupportedClockDividers;

        if( nullptr == pfnGetSupportedClockDividers )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pDividers )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );
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
        auto pfnGetClockRange = context.xetDdiTable.FreqDomain.pfnGetClockRange;

        if( nullptr == pfnGetClockRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMinClock )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMaxClock )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetClockRange( hFreqDomain, pMinClock, pMaxClock );
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
        auto pfnSetClockRange = context.xetDdiTable.FreqDomain.pfnSetClockRange;

        if( nullptr == pfnSetClockRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetClockRange( hFreqDomain, minClock, maxClock );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainSetClockDivider
    xe_result_t __xecall
    xetFreqDomainSetClockDivider(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
        )
    {
        auto pfnSetClockDivider = context.xetDdiTable.FreqDomain.pfnSetClockDivider;

        if( nullptr == pfnSetClockDivider )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pClockDividerRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetClockDivider( hFreqDomain, pClockDividerRequest );
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
        auto pfnGetCurrentFrequency = context.xetDdiTable.FreqDomain.pfnGetCurrentFrequency;

        if( nullptr == pfnGetCurrentFrequency )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFreqDomain )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFreqRequest )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFreqResolved )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFreqThrottleReasons )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetCurrentFrequency( hFreqDomain, pFreqRequest, pFreqResolved, pFreqThrottleReasons );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanCount
    xe_result_t __xecall
    xetPowerFanCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pFanCount                             ///< [out] the number of fans on the device
        )
    {
        auto pfnFanCount = context.xetDdiTable.Power.pfnFanCount;

        if( nullptr == pfnFanCount )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanCount( hPower, pFanCount );
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
        auto pfnFanGetProperties = context.xetDdiTable.Power.pfnFanGetProperties;

        if( nullptr == pfnFanGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGetProperties( hPower, fanIndex, pFanProperties );
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
        auto pfnFanGetSpeedTable = context.xetDdiTable.Power.pfnFanGetSpeedTable;

        if( nullptr == pfnFanGetSpeedTable )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pNumFanPoints )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanPoints )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );
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
        auto pfnFanSetSpeedTable = context.xetDdiTable.Power.pfnFanSetSpeedTable;

        if( nullptr == pfnFanSetSpeedTable )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanPoints )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );
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
        auto pfnFanGetSpeed = context.xetDdiTable.Power.pfnFanGetSpeed;

        if( nullptr == pfnFanGetSpeed )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanSpeed )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );
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
        auto pfnFanSetSpeed = context.xetDdiTable.Power.pfnFanSetSpeed;

        if( nullptr == pfnFanSetSpeed )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFanSpeed )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerTemperatureSensorCount
    xe_result_t __xecall
    xetPowerTemperatureSensorCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
        )
    {
        auto pfnTemperatureSensorCount = context.xetDdiTable.Power.pfnTemperatureSensorCount;

        if( nullptr == pfnTemperatureSensorCount )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pSensorCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnTemperatureSensorCount( hPower, pSensorCount );
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
        auto pfnGetTemperatureProperties = context.xetDdiTable.Power.pfnGetTemperatureProperties;

        if( nullptr == pfnGetTemperatureProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetTemperatureProperties( hPower, sensorIndex, pProperties );
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
        auto pfnGetTemperature = context.xetDdiTable.Power.pfnGetTemperature;

        if( nullptr == pfnGetTemperature )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pTemperatures )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );
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
        auto pfnSetTemperatureThreshold = context.xetDdiTable.Power.pfnSetTemperatureThreshold;

        if( nullptr == pfnSetTemperatureThreshold )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerActivityCount
    xe_result_t __xecall
    xetPowerActivityCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
        )
    {
        auto pfnActivityCount = context.xetDdiTable.Power.pfnActivityCount;

        if( nullptr == pfnActivityCount )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pActivityCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnActivityCount( hPower, pActivityCount );
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
        auto pfnGetActivityProperties = context.xetDdiTable.Power.pfnGetActivityProperties;

        if( nullptr == pfnGetActivityProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetActivityProperties( hPower, activityIndex, pProperties );
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
        auto pfnGetActivityCounters = context.xetDdiTable.Power.pfnGetActivityCounters;

        if( nullptr == pfnGetActivityCounters )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCounters )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );
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
        xet_extended_callbacks_t* pExtendedCbs          ///< [in][optional] pointer to table of 'extended' callback function
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

        return pfnSetPrologues( hTracer, pCoreCbs, pExtendedCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetTracerSetEpilogues
    xe_result_t __xecall
    xetTracerSetEpilogues(
        xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        xet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
        xet_extended_callbacks_t* pExtendedCbs          ///< [in][optional] pointer to table of 'extended' callback function
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

        return pfnSetEpilogues( hTracer, pCoreCbs, pExtendedCbs );
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
    auto& dditable = layer::context.xetDdiTable.Power;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xetPowerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xetPowerDestroy;

    dditable.pfnGetAveragePowerLimit                     = pDdiTable->pfnGetAveragePowerLimit;
    pDdiTable->pfnGetAveragePowerLimit                   = layer::xetPowerGetAveragePowerLimit;

    dditable.pfnGetBurstPowerLimit                       = pDdiTable->pfnGetBurstPowerLimit;
    pDdiTable->pfnGetBurstPowerLimit                     = layer::xetPowerGetBurstPowerLimit;

    dditable.pfnGetPeakPowerLimit                        = pDdiTable->pfnGetPeakPowerLimit;
    pDdiTable->pfnGetPeakPowerLimit                      = layer::xetPowerGetPeakPowerLimit;

    dditable.pfnGetAllPowerLimits                        = pDdiTable->pfnGetAllPowerLimits;
    pDdiTable->pfnGetAllPowerLimits                      = layer::xetPowerGetAllPowerLimits;

    dditable.pfnGetDefaultPowerLimits                    = pDdiTable->pfnGetDefaultPowerLimits;
    pDdiTable->pfnGetDefaultPowerLimits                  = layer::xetPowerGetDefaultPowerLimits;

    dditable.pfnSetAveragePowerLimit                     = pDdiTable->pfnSetAveragePowerLimit;
    pDdiTable->pfnSetAveragePowerLimit                   = layer::xetPowerSetAveragePowerLimit;

    dditable.pfnSetBurstPowerLimit                       = pDdiTable->pfnSetBurstPowerLimit;
    pDdiTable->pfnSetBurstPowerLimit                     = layer::xetPowerSetBurstPowerLimit;

    dditable.pfnSetPeakPowerLimit                        = pDdiTable->pfnSetPeakPowerLimit;
    pDdiTable->pfnSetPeakPowerLimit                      = layer::xetPowerSetPeakPowerLimit;

    dditable.pfnSetPowerLimits                           = pDdiTable->pfnSetPowerLimits;
    pDdiTable->pfnSetPowerLimits                         = layer::xetPowerSetPowerLimits;

    dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
    pDdiTable->pfnGetEnergyCounter                       = layer::xetPowerGetEnergyCounter;

    dditable.pfnGetTurboMode                             = pDdiTable->pfnGetTurboMode;
    pDdiTable->pfnGetTurboMode                           = layer::xetPowerGetTurboMode;

    dditable.pfnSetTurboMode                             = pDdiTable->pfnSetTurboMode;
    pDdiTable->pfnSetTurboMode                           = layer::xetPowerSetTurboMode;

    dditable.pfnFanCount                                 = pDdiTable->pfnFanCount;
    pDdiTable->pfnFanCount                               = layer::xetPowerFanCount;

    dditable.pfnFanGetProperties                         = pDdiTable->pfnFanGetProperties;
    pDdiTable->pfnFanGetProperties                       = layer::xetPowerFanGetProperties;

    dditable.pfnFanGetSpeedTable                         = pDdiTable->pfnFanGetSpeedTable;
    pDdiTable->pfnFanGetSpeedTable                       = layer::xetPowerFanGetSpeedTable;

    dditable.pfnFanSetSpeedTable                         = pDdiTable->pfnFanSetSpeedTable;
    pDdiTable->pfnFanSetSpeedTable                       = layer::xetPowerFanSetSpeedTable;

    dditable.pfnFanGetSpeed                              = pDdiTable->pfnFanGetSpeed;
    pDdiTable->pfnFanGetSpeed                            = layer::xetPowerFanGetSpeed;

    dditable.pfnFanSetSpeed                              = pDdiTable->pfnFanSetSpeed;
    pDdiTable->pfnFanSetSpeed                            = layer::xetPowerFanSetSpeed;

    dditable.pfnTemperatureSensorCount                   = pDdiTable->pfnTemperatureSensorCount;
    pDdiTable->pfnTemperatureSensorCount                 = layer::xetPowerTemperatureSensorCount;

    dditable.pfnGetTemperatureProperties                 = pDdiTable->pfnGetTemperatureProperties;
    pDdiTable->pfnGetTemperatureProperties               = layer::xetPowerGetTemperatureProperties;

    dditable.pfnGetTemperature                           = pDdiTable->pfnGetTemperature;
    pDdiTable->pfnGetTemperature                         = layer::xetPowerGetTemperature;

    dditable.pfnSetTemperatureThreshold                  = pDdiTable->pfnSetTemperatureThreshold;
    pDdiTable->pfnSetTemperatureThreshold                = layer::xetPowerSetTemperatureThreshold;

    dditable.pfnActivityCount                            = pDdiTable->pfnActivityCount;
    pDdiTable->pfnActivityCount                          = layer::xetPowerActivityCount;

    dditable.pfnGetActivityProperties                    = pDdiTable->pfnGetActivityProperties;
    pDdiTable->pfnGetActivityProperties                  = layer::xetPowerGetActivityProperties;

    dditable.pfnGetActivityCounters                      = pDdiTable->pfnGetActivityCounters;
    pDdiTable->pfnGetActivityCounters                    = layer::xetPowerGetActivityCounters;

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
    auto& dditable = layer::context.xetDdiTable.FreqDomain;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::xetFreqDomainGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xetFreqDomainGetProperties;

    dditable.pfnGetSourceFreqDomain                      = pDdiTable->pfnGetSourceFreqDomain;
    pDdiTable->pfnGetSourceFreqDomain                    = layer::xetFreqDomainGetSourceFreqDomain;

    dditable.pfnGetSupportedClocks                       = pDdiTable->pfnGetSupportedClocks;
    pDdiTable->pfnGetSupportedClocks                     = layer::xetFreqDomainGetSupportedClocks;

    dditable.pfnGetSupportedClockDividers                = pDdiTable->pfnGetSupportedClockDividers;
    pDdiTable->pfnGetSupportedClockDividers              = layer::xetFreqDomainGetSupportedClockDividers;

    dditable.pfnGetClockRange                            = pDdiTable->pfnGetClockRange;
    pDdiTable->pfnGetClockRange                          = layer::xetFreqDomainGetClockRange;

    dditable.pfnSetClockRange                            = pDdiTable->pfnSetClockRange;
    pDdiTable->pfnSetClockRange                          = layer::xetFreqDomainSetClockRange;

    dditable.pfnSetClockDivider                          = pDdiTable->pfnSetClockDivider;
    pDdiTable->pfnSetClockDivider                        = layer::xetFreqDomainSetClockDivider;

    dditable.pfnGetCurrentFrequency                      = pDdiTable->pfnGetCurrentFrequency;
    pDdiTable->pfnGetCurrentFrequency                    = layer::xetFreqDomainGetCurrentFrequency;

    return result;
}

#if defined(__cplusplus)
};
#endif
