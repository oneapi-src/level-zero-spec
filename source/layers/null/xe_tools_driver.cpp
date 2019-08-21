/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_tools_driver.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
 * @endcond
 *
 */
#include "xe_null.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetInit
    xe_result_t __xecall
    xetInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInit = context.xetDdiTable.Global.pfnInit;
        if( nullptr != pfnInit )
        {
            result = pfnInit( flags );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.xetDdiTable.MetricGroup.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDevice, pCount, phMetricGroups );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < *pCount ); ++i )
                phMetricGroups[ i ] = reinterpret_cast<xet_metric_group_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.xetDdiTable.MetricGroup.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hMetricGroup, pProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCalculateMetricValues = context.xetDdiTable.MetricGroup.pfnCalculateMetricValues;
        if( nullptr != pfnCalculateMetricValues )
        {
            result = pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.xetDdiTable.Metric.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hMetricGroup, pCount, phMetrics );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetrics ) && ( i < *pCount ); ++i )
                phMetrics[ i ] = reinterpret_cast<xet_metric_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.xetDdiTable.Metric.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hMetric, pProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnActivateMetricGroups = context.xetDdiTable.Device.pfnActivateMetricGroups;
        if( nullptr != pfnActivateMetricGroups )
        {
            result = pfnActivateMetricGroups( hDevice, count, phMetricGroups );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpen = context.xetDdiTable.MetricTracer.pfnOpen;
        if( nullptr != pfnOpen )
        {
            result = pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
        }
        else
        {
            // generic implementation
            *phMetricTracer = reinterpret_cast<xet_metric_tracer_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricTracerMarker = context.xetDdiTable.CommandList.pfnAppendMetricTracerMarker;
        if( nullptr != pfnAppendMetricTracerMarker )
        {
            result = pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.xetDdiTable.MetricTracer.pfnClose;
        if( nullptr != pfnClose )
        {
            result = pfnClose( hMetricTracer );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadData = context.xetDdiTable.MetricTracer.pfnReadData;
        if( nullptr != pfnReadData )
        {
            result = pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xetDdiTable.MetricQueryPool.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
        }
        else
        {
            // generic implementation
            *phMetricQueryPool = reinterpret_cast<xet_metric_query_pool_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xetDdiTable.MetricQueryPool.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hMetricQueryPool );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xetDdiTable.MetricQuery.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hMetricQueryPool, index, phMetricQuery );
        }
        else
        {
            // generic implementation
            *phMetricQuery = reinterpret_cast<xet_metric_query_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xetDdiTable.MetricQuery.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hMetricQuery );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.xetDdiTable.MetricQuery.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hMetricQuery );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricQueryBegin = context.xetDdiTable.CommandList.pfnAppendMetricQueryBegin;
        if( nullptr != pfnAppendMetricQueryBegin )
        {
            result = pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricQueryEnd = context.xetDdiTable.CommandList.pfnAppendMetricQueryEnd;
        if( nullptr != pfnAppendMetricQueryEnd )
        {
            result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricMemoryBarrier = context.xetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;
        if( nullptr != pfnAppendMetricMemoryBarrier )
        {
            result = pfnAppendMetricMemoryBarrier( hCommandList );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetData = context.xetDdiTable.MetricQuery.pfnGetData;
        if( nullptr != pfnGetData )
        {
            result = pfnGetData( hMetricQuery, pRawDataSize, pRawData );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDebugInfo = context.xetDdiTable.Module.pfnGetDebugInfo;
        if( nullptr != pfnGetDebugInfo )
        {
            result = pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFunctionNames = context.xetDdiTable.Module.pfnGetFunctionNames;
        if( nullptr != pfnGetFunctionNames )
        {
            result = pfnGetFunctionNames( hModule, pCount, pNames );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProfileInfo = context.xetDdiTable.Function.pfnGetProfileInfo;
        if( nullptr != pfnGetProfileInfo )
        {
            result = pfnGetProfileInfo( hFunction, pInfo );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.xetDdiTable.Sysman.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDevice, version, phSysman );
        }
        else
        {
            // generic implementation
            *phSysman = reinterpret_cast<xet_sysman_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceGetProperties = context.xetDdiTable.Sysman.pfnDeviceGetProperties;
        if( nullptr != pfnDeviceGetProperties )
        {
            result = pfnDeviceGetProperties( hSysman, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceGetOptimizationMode
    xe_result_t __xecall
    xetSysmanDeviceGetOptimizationMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_optimization_mode_t* pMode                  ///< [in] The current optimization mode of the device.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceGetOptimizationMode = context.xetDdiTable.Sysman.pfnDeviceGetOptimizationMode;
        if( nullptr != pfnDeviceGetOptimizationMode )
        {
            result = pfnDeviceGetOptimizationMode( hSysman, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDeviceSetOptimizationMode
    xe_result_t __xecall
    xetSysmanDeviceSetOptimizationMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        xet_optimization_mode_t pMode                   ///< [in] The new optimization mode of the device.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceSetOptimizationMode = context.xetDdiTable.Sysman.pfnDeviceSetOptimizationMode;
        if( nullptr != pfnDeviceSetOptimizationMode )
        {
            result = pfnDeviceSetOptimizationMode( hSysman, pMode );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceReset = context.xetDdiTable.Sysman.pfnDeviceReset;
        if( nullptr != pfnDeviceReset )
        {
            result = pfnDeviceReset( hSysman );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetCount
    xe_result_t __xecall
    xetSysmanPowerGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of power domains.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerGetCount = context.xetDdiTable.Sysman.pfnPowerGetCount;
        if( nullptr != pfnPowerGetCount )
        {
            result = pfnPowerGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetProperties
    xe_result_t __xecall
    xetSysmanPowerGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pwrIndex,                              ///< [in] The index of the power domain (0 ... [::xetSysmanPowerGetCount()
                                                        ///< - 1]).
        xet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerGetProperties = context.xetDdiTable.Sysman.pfnPowerGetProperties;
        if( nullptr != pfnPowerGetProperties )
        {
            result = pfnPowerGetProperties( hSysman, pwrIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetEnergyCounter
    xe_result_t __xecall
    xetSysmanPowerGetEnergyCounter(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pwrIndex,                              ///< [in] The index of the power domain (0 ... [::xetSysmanPowerGetCount()
                                                        ///< - 1]).
        xet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerGetEnergyCounter = context.xetDdiTable.Sysman.pfnPowerGetEnergyCounter;
        if( nullptr != pfnPowerGetEnergyCounter )
        {
            result = pfnPowerGetEnergyCounter( hSysman, pwrIndex, pEnergy );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerGetEnergyThreshold(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pwrIndex,                              ///< [in] The index of the power domain (0 ... [::xetSysmanPowerGetCount()
                                                        ///< - 1]).
        xet_power_energy_threshold_t* pThreshold        ///< [out] The current energy threshold value in joules.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerGetEnergyThreshold = context.xetDdiTable.Sysman.pfnPowerGetEnergyThreshold;
        if( nullptr != pfnPowerGetEnergyThreshold )
        {
            result = pfnPowerGetEnergyThreshold( hSysman, pwrIndex, pThreshold );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerSetEnergyThreshold
    xe_result_t __xecall
    xetSysmanPowerSetEnergyThreshold(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pwrIndex,                              ///< [in] The index of the power domain (0 ... [::xetSysmanPowerGetCount()
                                                        ///< - 1]).
        xet_power_energy_threshold_t* pThreshold        ///< [in] The energy threshold to be set in joules.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerSetEnergyThreshold = context.xetDdiTable.Sysman.pfnPowerSetEnergyThreshold;
        if( nullptr != pfnPowerSetEnergyThreshold )
        {
            result = pfnPowerSetEnergyThreshold( hSysman, pwrIndex, pThreshold );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerGetLimits
    xe_result_t __xecall
    xetSysmanPowerGetLimits(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pwrIndex,                              ///< [in] The index of the power domain (0 ... [::xetSysmanPowerGetCount()
                                                        ///< - 1]).
        xet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
        xet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
        xet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerGetLimits = context.xetDdiTable.Sysman.pfnPowerGetLimits;
        if( nullptr != pfnPowerGetLimits )
        {
            result = pfnPowerGetLimits( hSysman, pwrIndex, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPowerSetLimits
    xe_result_t __xecall
    xetSysmanPowerSetLimits(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pwrIndex,                              ///< [in] The index of the power domain (0 ... [::xetSysmanPowerGetCount()
                                                        ///< - 1]).
        const xet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const xet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const xet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerSetLimits = context.xetDdiTable.Sysman.pfnPowerSetLimits;
        if( nullptr != pfnPowerSetLimits )
        {
            result = pfnPowerSetLimits( hSysman, pwrIndex, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetCount
    xe_result_t __xecall
    xetSysmanFrequencyGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of frequency domains.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencyGetCount = context.xetDdiTable.Sysman.pfnFrequencyGetCount;
        if( nullptr != pfnFrequencyGetCount )
        {
            result = pfnFrequencyGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetProperties
    xe_result_t __xecall
    xetSysmanFrequencyGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t freqIndex,                             ///< [in] The index of the frequency domain (0 ...
                                                        ///< [::xetSysmanFrequencyGetCount() - 1]).
        xet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencyGetProperties = context.xetDdiTable.Sysman.pfnFrequencyGetProperties;
        if( nullptr != pfnFrequencyGetProperties )
        {
            result = pfnFrequencyGetProperties( hSysman, freqIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetRange
    xe_result_t __xecall
    xetSysmanFrequencyGetRange(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t freqIndex,                             ///< [in] The index of the frequency domain (0 ...
                                                        ///< [::xetSysmanFrequencyGetCount() - 1]).
        xet_freq_range_t* pLimits                       ///< [in] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencyGetRange = context.xetDdiTable.Sysman.pfnFrequencyGetRange;
        if( nullptr != pfnFrequencyGetRange )
        {
            result = pfnFrequencyGetRange( hSysman, freqIndex, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencySetRange
    xe_result_t __xecall
    xetSysmanFrequencySetRange(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t freqIndex,                             ///< [in] The index of the frequency domain (0 ...
                                                        ///< [::xetSysmanFrequencyGetCount() - 1]).
        const xet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencySetRange = context.xetDdiTable.Sysman.pfnFrequencySetRange;
        if( nullptr != pfnFrequencySetRange )
        {
            result = pfnFrequencySetRange( hSysman, freqIndex, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetState
    xe_result_t __xecall
    xetSysmanFrequencyGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t freqIndex,                             ///< [in] The index of the frequency domain (0 ...
                                                        ///< [::xetSysmanFrequencyGetCount() - 1]).
        xet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencyGetState = context.xetDdiTable.Sysman.pfnFrequencyGetState;
        if( nullptr != pfnFrequencyGetState )
        {
            result = pfnFrequencyGetState( hSysman, freqIndex, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFrequencyGetThrottleTime
    xe_result_t __xecall
    xetSysmanFrequencyGetThrottleTime(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t freqIndex,                             ///< [in] The index of the frequency domain (0 ...
                                                        ///< [::xetSysmanFrequencyGetCount() - 1]).
        xet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencyGetThrottleTime = context.xetDdiTable.Sysman.pfnFrequencyGetThrottleTime;
        if( nullptr != pfnFrequencyGetThrottleTime )
        {
            result = pfnFrequencyGetThrottleTime( hSysman, freqIndex, pThrottleTime );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGetCount
    xe_result_t __xecall
    xetSysmanEngineGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of engine groups.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEngineGetCount = context.xetDdiTable.Sysman.pfnEngineGetCount;
        if( nullptr != pfnEngineGetCount )
        {
            result = pfnEngineGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGetProperties
    xe_result_t __xecall
    xetSysmanEngineGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t engineIndex,                           ///< [in] The index of the engine group (0 ... [::xetSysmanEngineGetCount()
                                                        ///< - 1]).
        xet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEngineGetProperties = context.xetDdiTable.Sysman.pfnEngineGetProperties;
        if( nullptr != pfnEngineGetProperties )
        {
            result = pfnEngineGetProperties( hSysman, engineIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanEngineGetActivity
    xe_result_t __xecall
    xetSysmanEngineGetActivity(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t engineIndex,                           ///< [in] The index of the engine group (0 ... [::xetSysmanEngineGetCount()
                                                        ///< - 1]).
        xet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEngineGetActivity = context.xetDdiTable.Sysman.pfnEngineGetActivity;
        if( nullptr != pfnEngineGetActivity )
        {
            result = pfnEngineGetActivity( hSysman, engineIndex, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetCount
    xe_result_t __xecall
    xetSysmanMemoryGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of memory modules.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMemoryGetCount = context.xetDdiTable.Sysman.pfnMemoryGetCount;
        if( nullptr != pfnMemoryGetCount )
        {
            result = pfnMemoryGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetProperties
    xe_result_t __xecall
    xetSysmanMemoryGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t memIndex,                              ///< [in] The index of the memory module (0 ...
                                                        ///< [::xetSysmanMemoryGetCount() - 1]).
        xet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMemoryGetProperties = context.xetDdiTable.Sysman.pfnMemoryGetProperties;
        if( nullptr != pfnMemoryGetProperties )
        {
            result = pfnMemoryGetProperties( hSysman, memIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetBandwidth
    xe_result_t __xecall
    xetSysmanMemoryGetBandwidth(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t memIndex,                              ///< [in] The index of the memory module (0 ...
                                                        ///< [::xetSysmanMemoryGetCount() - 1]).
        xet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMemoryGetBandwidth = context.xetDdiTable.Sysman.pfnMemoryGetBandwidth;
        if( nullptr != pfnMemoryGetBandwidth )
        {
            result = pfnMemoryGetBandwidth( hSysman, memIndex, pBandwidth );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanMemoryGetAllocated
    xe_result_t __xecall
    xetSysmanMemoryGetAllocated(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t memIndex,                              ///< [in] The index of the memory module (0 ...
                                                        ///< [::xetSysmanMemoryGetCount() - 1]).
        xet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMemoryGetAllocated = context.xetDdiTable.Sysman.pfnMemoryGetAllocated;
        if( nullptr != pfnMemoryGetAllocated )
        {
            result = pfnMemoryGetAllocated( hSysman, memIndex, pAllocated );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetCount
    xe_result_t __xecall
    xetSysmanPciGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of PCI end-points.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetCount = context.xetDdiTable.Sysman.pfnPciGetCount;
        if( nullptr != pfnPciGetCount )
        {
            result = pfnPciGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetProperties
    xe_result_t __xecall
    xetSysmanPciGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pciIndex,                              ///< [in] The index of the PCI end-point (0 ... [::xetSysmanPciGetCount() -
                                                        ///< 1]).
        xet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetProperties = context.xetDdiTable.Sysman.pfnPciGetProperties;
        if( nullptr != pfnPciGetProperties )
        {
            result = pfnPciGetProperties( hSysman, pciIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetState
    xe_result_t __xecall
    xetSysmanPciGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pciIndex,                              ///< [in] The index of the PCI end-point (0 ... [::xetSysmanPciGetCount() -
                                                        ///< 1]).
        xet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetState = context.xetDdiTable.Sysman.pfnPciGetState;
        if( nullptr != pfnPciGetState )
        {
            result = pfnPciGetState( hSysman, pciIndex, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetBarProperties
    xe_result_t __xecall
    xetSysmanPciGetBarProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pciIndex,                              ///< [in] The index of the PCI end-point (0 ... [::xetSysmanPciGetCount() -
                                                        ///< 1]).
        uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::xet_pci_properties_t.numBars -
                                                        ///< 1]).
        xet_pci_bar_properties_t* pProperties           ///< [in] Will contain properties of the specified bar
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetBarProperties = context.xetDdiTable.Sysman.pfnPciGetBarProperties;
        if( nullptr != pfnPciGetBarProperties )
        {
            result = pfnPciGetBarProperties( hSysman, pciIndex, barIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetThroughput
    xe_result_t __xecall
    xetSysmanPciGetThroughput(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pciIndex,                              ///< [in] The index of the PCI end-point (0 ... [::xetSysmanPciGetCount() -
                                                        ///< 1]).
        xet_pci_throughput_t* pThroughput               ///< [in] Will contain a snapshot of the latest throughput counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetThroughput = context.xetDdiTable.Sysman.pfnPciGetThroughput;
        if( nullptr != pfnPciGetThroughput )
        {
            result = pfnPciGetThroughput( hSysman, pciIndex, pThroughput );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPciGetStats
    xe_result_t __xecall
    xetSysmanPciGetStats(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t pciIndex,                              ///< [in] The index of the PCI end-point (0 ... [::xetSysmanPciGetCount() -
                                                        ///< 1]).
        xet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetStats = context.xetDdiTable.Sysman.pfnPciGetStats;
        if( nullptr != pfnPciGetStats )
        {
            result = pfnPciGetStats( hSysman, pciIndex, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchGetCount
    xe_result_t __xecall
    xetSysmanSwitchGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of high-speed switches.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchGetCount = context.xetDdiTable.Sysman.pfnSwitchGetCount;
        if( nullptr != pfnSwitchGetCount )
        {
            result = pfnSwitchGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchGetProperties
    xe_result_t __xecall
    xetSysmanSwitchGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ... [::xetSysmanSwitchGetCount() -
                                                        ///< 1]).
        xet_switch_properties_t* pProperties            ///< [in] Will contain the Switch properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchGetProperties = context.xetDdiTable.Sysman.pfnSwitchGetProperties;
        if( nullptr != pfnSwitchGetProperties )
        {
            result = pfnSwitchGetProperties( hSysman, switchIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchGetState
    xe_result_t __xecall
    xetSysmanSwitchGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ... [::xetSysmanSwitchGetCount() -
                                                        ///< 1]).
        xet_switch_state_t* pState                      ///< [in] Will contain the current state of the switch (enabled/disabled).
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchGetState = context.xetDdiTable.Sysman.pfnSwitchGetState;
        if( nullptr != pfnSwitchGetState )
        {
            result = pfnSwitchGetState( hSysman, switchIndex, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchSetState
    xe_result_t __xecall
    xetSysmanSwitchSetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ... [::xetSysmanSwitchGetCount() -
                                                        ///< 1]).
        xe_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchSetState = context.xetDdiTable.Sysman.pfnSwitchSetState;
        if( nullptr != pfnSwitchSetState )
        {
            result = pfnSwitchSetState( hSysman, switchIndex, enable );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetProperties
    xe_result_t __xecall
    xetSysmanSwitchPortGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ... [::xetSysmanSwitchGetCount() -
                                                        ///< 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_properties_t* pProperties       ///< [in] Will contain properties of the Switch Port
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchPortGetProperties = context.xetDdiTable.Sysman.pfnSwitchPortGetProperties;
        if( nullptr != pfnSwitchPortGetProperties )
        {
            result = pfnSwitchPortGetProperties( hSysman, switchIndex, portIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetState
    xe_result_t __xecall
    xetSysmanSwitchPortGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ... [::xetSysmanSwitchGetCount() -
                                                        ///< 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_state_t* pState                 ///< [in] Will contain the current state of the Switch Port
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchPortGetState = context.xetDdiTable.Sysman.pfnSwitchPortGetState;
        if( nullptr != pfnSwitchPortGetState )
        {
            result = pfnSwitchPortGetState( hSysman, switchIndex, portIndex, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetThroughput
    xe_result_t __xecall
    xetSysmanSwitchPortGetThroughput(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ... [::xetSysmanSwitchGetCount() -
                                                        ///< 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_throughput_t* pThroughput       ///< [in] Will contain the Switch port throughput counters.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchPortGetThroughput = context.xetDdiTable.Sysman.pfnSwitchPortGetThroughput;
        if( nullptr != pfnSwitchPortGetThroughput )
        {
            result = pfnSwitchPortGetThroughput( hSysman, switchIndex, portIndex, pThroughput );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanSwitchPortGetStats
    xe_result_t __xecall
    xetSysmanSwitchPortGetStats(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t switchIndex,                           ///< [in] The index of the switch (0 ... [::xetSysmanSwitchGetCount() -
                                                        ///< 1]).
        uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                        ///< - 1]).
        xet_switch_port_stats_t* pStats                 ///< [in] Will contain the Switch port stats.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSwitchPortGetStats = context.xetDdiTable.Sysman.pfnSwitchPortGetStats;
        if( nullptr != pfnSwitchPortGetStats )
        {
            result = pfnSwitchPortGetStats( hSysman, switchIndex, portIndex, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureGetCount
    xe_result_t __xecall
    xetSysmanTemperatureGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of temperature sensors.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnTemperatureGetCount = context.xetDdiTable.Sysman.pfnTemperatureGetCount;
        if( nullptr != pfnTemperatureGetCount )
        {
            result = pfnTemperatureGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureGetProperties
    xe_result_t __xecall
    xetSysmanTemperatureGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t tempIndex,                             ///< [in] The index of the temperature sensor (0 ...
                                                        ///< [::xetSysmanTemperatureGetCount() - 1]).
        xet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnTemperatureGetProperties = context.xetDdiTable.Sysman.pfnTemperatureGetProperties;
        if( nullptr != pfnTemperatureGetProperties )
        {
            result = pfnTemperatureGetProperties( hSysman, tempIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanTemperatureGet
    xe_result_t __xecall
    xetSysmanTemperatureGet(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t tempIndex,                             ///< [in] The index of the temperature sensor (0 ...
                                                        ///< [::xetSysmanTemperatureGetCount() - 1]).
        uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnTemperatureGet = context.xetDdiTable.Sysman.pfnTemperatureGet;
        if( nullptr != pfnTemperatureGet )
        {
            result = pfnTemperatureGet( hSysman, tempIndex, pTemperature );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetCount
    xe_result_t __xecall
    xetSysmanStandbyGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of standby hardware components.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnStandbyGetCount = context.xetDdiTable.Sysman.pfnStandbyGetCount;
        if( nullptr != pfnStandbyGetCount )
        {
            result = pfnStandbyGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetProperties
    xe_result_t __xecall
    xetSysmanStandbyGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t stbyIndex,                             ///< [in] The index of the standby hardware component (0 ...
                                                        ///< [::xetSysmanStandbyGetCount() - 1]).
        xet_stby_properties_t* pProperties              ///< [in] Will contain the standby hardware properties.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnStandbyGetProperties = context.xetDdiTable.Sysman.pfnStandbyGetProperties;
        if( nullptr != pfnStandbyGetProperties )
        {
            result = pfnStandbyGetProperties( hSysman, stbyIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbyGetMode
    xe_result_t __xecall
    xetSysmanStandbyGetMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t stbyIndex,                             ///< [in] The index of the standby hardware component (0 ...
                                                        ///< [::xetSysmanStandbyGetCount() - 1]).
        xet_stby_promo_mode_t* pMode                    ///< [in] Will contain the current standby mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnStandbyGetMode = context.xetDdiTable.Sysman.pfnStandbyGetMode;
        if( nullptr != pfnStandbyGetMode )
        {
            result = pfnStandbyGetMode( hSysman, stbyIndex, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanStandbySetMode
    xe_result_t __xecall
    xetSysmanStandbySetMode(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t stbyIndex,                             ///< [in] The index of the standby hardware component (0 ...
                                                        ///< [::xetSysmanStandbyGetCount() - 1]).
        xet_stby_promo_mode_t mode                      ///< [in] New standby mode.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnStandbySetMode = context.xetDdiTable.Sysman.pfnStandbySetMode;
        if( nullptr != pfnStandbySetMode )
        {
            result = pfnStandbySetMode( hSysman, stbyIndex, mode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetCount
    xe_result_t __xecall
    xetSysmanFirmwareGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of firmwares.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFirmwareGetCount = context.xetDdiTable.Sysman.pfnFirmwareGetCount;
        if( nullptr != pfnFirmwareGetCount )
        {
            result = pfnFirmwareGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetProperties
    xe_result_t __xecall
    xetSysmanFirmwareGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ... [::xetSysmanFirmwareGetCount() -
                                                        ///< 1]).
        xet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFirmwareGetProperties = context.xetDdiTable.Sysman.pfnFirmwareGetProperties;
        if( nullptr != pfnFirmwareGetProperties )
        {
            result = pfnFirmwareGetProperties( hSysman, firmwareIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareGetChecksum
    xe_result_t __xecall
    xetSysmanFirmwareGetChecksum(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ... [::xetSysmanFirmwareGetCount() -
                                                        ///< 1]).
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFirmwareGetChecksum = context.xetDdiTable.Sysman.pfnFirmwareGetChecksum;
        if( nullptr != pfnFirmwareGetChecksum )
        {
            result = pfnFirmwareGetChecksum( hSysman, firmwareIndex, pChecksum );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFirmwareFlash
    xe_result_t __xecall
    xetSysmanFirmwareFlash(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ... [::xetSysmanFirmwareGetCount() -
                                                        ///< 1]).
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFirmwareFlash = context.xetDdiTable.Sysman.pfnFirmwareFlash;
        if( nullptr != pfnFirmwareFlash )
        {
            result = pfnFirmwareFlash( hSysman, firmwareIndex, pImage, size );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetCount
    xe_result_t __xecall
    xetSysmanPsuGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of PSUs.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPsuGetCount = context.xetDdiTable.Sysman.pfnPsuGetCount;
        if( nullptr != pfnPsuGetCount )
        {
            result = pfnPsuGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetProperties
    xe_result_t __xecall
    xetSysmanPsuGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ... [::xetSysmanPsuGetCount() -
                                                        ///< 1]).
        xet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPsuGetProperties = context.xetDdiTable.Sysman.pfnPsuGetProperties;
        if( nullptr != pfnPsuGetProperties )
        {
            result = pfnPsuGetProperties( hSysman, psuIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanPsuGetState
    xe_result_t __xecall
    xetSysmanPsuGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ... [::xetSysmanPsuGetCount() -
                                                        ///< 1]).
        xet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPsuGetState = context.xetDdiTable.Sysman.pfnPsuGetState;
        if( nullptr != pfnPsuGetState )
        {
            result = pfnPsuGetState( hSysman, psuIndex, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetCount
    xe_result_t __xecall
    xetSysmanFanGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of fans.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFanGetCount = context.xetDdiTable.Sysman.pfnFanGetCount;
        if( nullptr != pfnFanGetCount )
        {
            result = pfnFanGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetProperties
    xe_result_t __xecall
    xetSysmanFanGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xetSysmanFanGetCount() - 1]).
        xet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFanGetProperties = context.xetDdiTable.Sysman.pfnFanGetProperties;
        if( nullptr != pfnFanGetProperties )
        {
            result = pfnFanGetProperties( hSysman, fanIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetConfig
    xe_result_t __xecall
    xetSysmanFanGetConfig(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xetSysmanFanGetCount() - 1]).
        xet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFanGetConfig = context.xetDdiTable.Sysman.pfnFanGetConfig;
        if( nullptr != pfnFanGetConfig )
        {
            result = pfnFanGetConfig( hSysman, fanIndex, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanSetConfig
    xe_result_t __xecall
    xetSysmanFanSetConfig(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xetSysmanFanGetCount() - 1]).
        const xet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFanSetConfig = context.xetDdiTable.Sysman.pfnFanSetConfig;
        if( nullptr != pfnFanSetConfig )
        {
            result = pfnFanSetConfig( hSysman, fanIndex, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanFanGetState
    xe_result_t __xecall
    xetSysmanFanGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xetSysmanFanGetCount() - 1]).
        xet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        xet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFanGetState = context.xetDdiTable.Sysman.pfnFanGetState;
        if( nullptr != pfnFanGetState )
        {
            result = pfnFanGetState( hSysman, fanIndex, units, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetCount
    xe_result_t __xecall
    xetSysmanLedGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of LEDs.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnLedGetCount = context.xetDdiTable.Sysman.pfnLedGetCount;
        if( nullptr != pfnLedGetCount )
        {
            result = pfnLedGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetProperties
    xe_result_t __xecall
    xetSysmanLedGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xetSysmanLedGetCount() - 1]).
        xet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnLedGetProperties = context.xetDdiTable.Sysman.pfnLedGetProperties;
        if( nullptr != pfnLedGetProperties )
        {
            result = pfnLedGetProperties( hSysman, ledIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedGetState
    xe_result_t __xecall
    xetSysmanLedGetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xetSysmanLedGetCount() - 1]).
        xet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnLedGetState = context.xetDdiTable.Sysman.pfnLedGetState;
        if( nullptr != pfnLedGetState )
        {
            result = pfnLedGetState( hSysman, ledIndex, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanLedSetState
    xe_result_t __xecall
    xetSysmanLedSetState(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xetSysmanLedGetCount() - 1]).
        const xet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnLedSetState = context.xetDdiTable.Sysman.pfnLedSetState;
        if( nullptr != pfnLedSetState )
        {
            result = pfnLedSetState( hSysman, ledIndex, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetCount
    xe_result_t __xecall
    xetSysmanRasGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of RAS errors sets.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRasGetCount = context.xetDdiTable.Sysman.pfnRasGetCount;
        if( nullptr != pfnRasGetCount )
        {
            result = pfnRasGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetProperties
    xe_result_t __xecall
    xetSysmanRasGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        uint32_t rasIndex,                              ///< [in] The index of the RAS error set (0 ... [::xetSysmanRasGetCount() -
                                                        ///< 1]).
        xet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRasGetProperties = context.xetDdiTable.Sysman.pfnRasGetProperties;
        if( nullptr != pfnRasGetProperties )
        {
            result = pfnRasGetProperties( hSysman, rasIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanRasGetErrors
    xe_result_t __xecall
    xetSysmanRasGetErrors(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        uint32_t rasIndex,                              ///< [in] The index of the RAS error set (0 ... [::xetSysmanRasGetCount() -
                                                        ///< 1]).
        xe_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
        xet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRasGetErrors = context.xetDdiTable.Sysman.pfnRasGetErrors;
        if( nullptr != pfnRasGetErrors )
        {
            result = pfnRasGetErrors( hSysman, rasIndex, clear, pTotalErrors, pDetails );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventsGetProperties = context.xetDdiTable.Sysman.pfnEventsGetProperties;
        if( nullptr != pfnEventsGetProperties )
        {
            result = pfnEventsGetProperties( hSysman, pProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventsRegister = context.xetDdiTable.Sysman.pfnEventsRegister;
        if( nullptr != pfnEventsRegister )
        {
            result = pfnEventsRegister( hSysman, count, pEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventsUnregister = context.xetDdiTable.Sysman.pfnEventsUnregister;
        if( nullptr != pfnEventsUnregister )
        {
            result = pfnEventsUnregister( hSysman, count, pEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventsListen = context.xetDdiTable.Sysman.pfnEventsListen;
        if( nullptr != pfnEventsListen )
        {
            result = pfnEventsListen( hSysman, clear, timeout, pEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsGetCount
    xe_result_t __xecall
    xetSysmanDiagnosticsGetCount(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
        uint32_t* pCount                                ///< [in] The number of diagnostic test suites.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDiagnosticsGetCount = context.xetDdiTable.Sysman.pfnDiagnosticsGetCount;
        if( nullptr != pfnDiagnosticsGetCount )
        {
            result = pfnDiagnosticsGetCount( hSysman, pCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsGetProperties
    xe_result_t __xecall
    xetSysmanDiagnosticsGetProperties(
        xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
        uint32_t testIndex,                             ///< [in] The index of a diagnostics test (0 ...
                                                        ///< [::xetSysmanDiagnosticsGetCount() - 1]).
        xet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDiagnosticsGetProperties = context.xetDdiTable.Sysman.pfnDiagnosticsGetProperties;
        if( nullptr != pfnDiagnosticsGetProperties )
        {
            result = pfnDiagnosticsGetProperties( hSysman, testIndex, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetSysmanDiagnosticsRunTests
    xe_result_t __xecall
    xetSysmanDiagnosticsRunTests(
        xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
        uint32_t testIndex,                             ///< [in] The index of a diagnostics test (0 ...
                                                        ///< [::xetSysmanDiagnosticsGetCount() - 1]).
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        xet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDiagnosticsRunTests = context.xetDdiTable.Sysman.pfnDiagnosticsRunTests;
        if( nullptr != pfnDiagnosticsRunTests )
        {
            result = pfnDiagnosticsRunTests( hSysman, testIndex, start, end, pResult );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xetDdiTable.Tracer.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phTracer );
        }
        else
        {
            // generic implementation
            *phTracer = reinterpret_cast<xet_tracer_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xetDdiTable.Tracer.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hTracer );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetPrologues = context.xetDdiTable.Tracer.pfnSetPrologues;
        if( nullptr != pfnSetPrologues )
        {
            result = pfnSetPrologues( hTracer, pCoreCbs, pExperimentalCbs );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEpilogues = context.xetDdiTable.Tracer.pfnSetEpilogues;
        if( nullptr != pfnSetEpilogues )
        {
            result = pfnSetEpilogues( hTracer, pCoreCbs, pExperimentalCbs );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEnabled = context.xetDdiTable.Tracer.pfnSetEnabled;
        if( nullptr != pfnSetEnabled )
        {
            result = pfnSetEnabled( hTracer, enable );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

} // namespace driver

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnInit                                   = driver::xetInit;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnActivateMetricGroups                   = driver::xetDeviceActivateMetricGroups;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnAppendMetricTracerMarker               = driver::xetCommandListAppendMetricTracerMarker;

    pDdiTable->pfnAppendMetricQueryBegin                 = driver::xetCommandListAppendMetricQueryBegin;

    pDdiTable->pfnAppendMetricQueryEnd                   = driver::xetCommandListAppendMetricQueryEnd;

    pDdiTable->pfnAppendMetricMemoryBarrier              = driver::xetCommandListAppendMetricMemoryBarrier;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetDebugInfo                           = driver::xetModuleGetDebugInfo;

    pDdiTable->pfnGetFunctionNames                       = driver::xetModuleGetFunctionNames;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetProfileInfo                         = driver::xetFunctionGetProfileInfo;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::xetMetricGroupGet;

    pDdiTable->pfnGetProperties                          = driver::xetMetricGroupGetProperties;

    pDdiTable->pfnCalculateMetricValues                  = driver::xetMetricGroupCalculateMetricValues;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::xetMetricGet;

    pDdiTable->pfnGetProperties                          = driver::xetMetricGetProperties;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnOpen                                   = driver::xetMetricTracerOpen;

    pDdiTable->pfnClose                                  = driver::xetMetricTracerClose;

    pDdiTable->pfnReadData                               = driver::xetMetricTracerReadData;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xetMetricQueryPoolCreate;

    pDdiTable->pfnDestroy                                = driver::xetMetricQueryPoolDestroy;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xetMetricQueryCreate;

    pDdiTable->pfnDestroy                                = driver::xetMetricQueryDestroy;

    pDdiTable->pfnReset                                  = driver::xetMetricQueryReset;

    pDdiTable->pfnGetData                                = driver::xetMetricQueryGetData;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xetTracerCreate;

    pDdiTable->pfnDestroy                                = driver::xetTracerDestroy;

    pDdiTable->pfnSetPrologues                           = driver::xetTracerSetPrologues;

    pDdiTable->pfnSetEpilogues                           = driver::xetTracerSetEpilogues;

    pDdiTable->pfnSetEnabled                             = driver::xetTracerSetEnabled;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::xetSysmanGet;

    pDdiTable->pfnDeviceGetProperties                    = driver::xetSysmanDeviceGetProperties;

    pDdiTable->pfnDeviceGetOptimizationMode              = driver::xetSysmanDeviceGetOptimizationMode;

    pDdiTable->pfnDeviceSetOptimizationMode              = driver::xetSysmanDeviceSetOptimizationMode;

    pDdiTable->pfnDeviceReset                            = driver::xetSysmanDeviceReset;

    pDdiTable->pfnPowerGetCount                          = driver::xetSysmanPowerGetCount;

    pDdiTable->pfnPowerGetProperties                     = driver::xetSysmanPowerGetProperties;

    pDdiTable->pfnPowerGetEnergyCounter                  = driver::xetSysmanPowerGetEnergyCounter;

    pDdiTable->pfnPowerGetEnergyThreshold                = driver::xetSysmanPowerGetEnergyThreshold;

    pDdiTable->pfnPowerSetEnergyThreshold                = driver::xetSysmanPowerSetEnergyThreshold;

    pDdiTable->pfnPowerGetLimits                         = driver::xetSysmanPowerGetLimits;

    pDdiTable->pfnPowerSetLimits                         = driver::xetSysmanPowerSetLimits;

    pDdiTable->pfnFrequencyGetCount                      = driver::xetSysmanFrequencyGetCount;

    pDdiTable->pfnFrequencyGetProperties                 = driver::xetSysmanFrequencyGetProperties;

    pDdiTable->pfnFrequencyGetRange                      = driver::xetSysmanFrequencyGetRange;

    pDdiTable->pfnFrequencySetRange                      = driver::xetSysmanFrequencySetRange;

    pDdiTable->pfnFrequencyGetState                      = driver::xetSysmanFrequencyGetState;

    pDdiTable->pfnFrequencyGetThrottleTime               = driver::xetSysmanFrequencyGetThrottleTime;

    pDdiTable->pfnEngineGetCount                         = driver::xetSysmanEngineGetCount;

    pDdiTable->pfnEngineGetProperties                    = driver::xetSysmanEngineGetProperties;

    pDdiTable->pfnEngineGetActivity                      = driver::xetSysmanEngineGetActivity;

    pDdiTable->pfnMemoryGetCount                         = driver::xetSysmanMemoryGetCount;

    pDdiTable->pfnMemoryGetProperties                    = driver::xetSysmanMemoryGetProperties;

    pDdiTable->pfnMemoryGetBandwidth                     = driver::xetSysmanMemoryGetBandwidth;

    pDdiTable->pfnMemoryGetAllocated                     = driver::xetSysmanMemoryGetAllocated;

    pDdiTable->pfnPciGetCount                            = driver::xetSysmanPciGetCount;

    pDdiTable->pfnPciGetProperties                       = driver::xetSysmanPciGetProperties;

    pDdiTable->pfnPciGetState                            = driver::xetSysmanPciGetState;

    pDdiTable->pfnPciGetBarProperties                    = driver::xetSysmanPciGetBarProperties;

    pDdiTable->pfnPciGetThroughput                       = driver::xetSysmanPciGetThroughput;

    pDdiTable->pfnPciGetStats                            = driver::xetSysmanPciGetStats;

    pDdiTable->pfnSwitchGetCount                         = driver::xetSysmanSwitchGetCount;

    pDdiTable->pfnSwitchGetProperties                    = driver::xetSysmanSwitchGetProperties;

    pDdiTable->pfnSwitchGetState                         = driver::xetSysmanSwitchGetState;

    pDdiTable->pfnSwitchSetState                         = driver::xetSysmanSwitchSetState;

    pDdiTable->pfnSwitchPortGetProperties                = driver::xetSysmanSwitchPortGetProperties;

    pDdiTable->pfnSwitchPortGetState                     = driver::xetSysmanSwitchPortGetState;

    pDdiTable->pfnSwitchPortGetThroughput                = driver::xetSysmanSwitchPortGetThroughput;

    pDdiTable->pfnSwitchPortGetStats                     = driver::xetSysmanSwitchPortGetStats;

    pDdiTable->pfnTemperatureGetCount                    = driver::xetSysmanTemperatureGetCount;

    pDdiTable->pfnTemperatureGetProperties               = driver::xetSysmanTemperatureGetProperties;

    pDdiTable->pfnTemperatureGet                         = driver::xetSysmanTemperatureGet;

    pDdiTable->pfnStandbyGetCount                        = driver::xetSysmanStandbyGetCount;

    pDdiTable->pfnStandbyGetProperties                   = driver::xetSysmanStandbyGetProperties;

    pDdiTable->pfnStandbyGetMode                         = driver::xetSysmanStandbyGetMode;

    pDdiTable->pfnStandbySetMode                         = driver::xetSysmanStandbySetMode;

    pDdiTable->pfnFirmwareGetCount                       = driver::xetSysmanFirmwareGetCount;

    pDdiTable->pfnFirmwareGetProperties                  = driver::xetSysmanFirmwareGetProperties;

    pDdiTable->pfnFirmwareGetChecksum                    = driver::xetSysmanFirmwareGetChecksum;

    pDdiTable->pfnFirmwareFlash                          = driver::xetSysmanFirmwareFlash;

    pDdiTable->pfnPsuGetCount                            = driver::xetSysmanPsuGetCount;

    pDdiTable->pfnPsuGetProperties                       = driver::xetSysmanPsuGetProperties;

    pDdiTable->pfnPsuGetState                            = driver::xetSysmanPsuGetState;

    pDdiTable->pfnFanGetCount                            = driver::xetSysmanFanGetCount;

    pDdiTable->pfnFanGetProperties                       = driver::xetSysmanFanGetProperties;

    pDdiTable->pfnFanGetConfig                           = driver::xetSysmanFanGetConfig;

    pDdiTable->pfnFanSetConfig                           = driver::xetSysmanFanSetConfig;

    pDdiTable->pfnFanGetState                            = driver::xetSysmanFanGetState;

    pDdiTable->pfnLedGetCount                            = driver::xetSysmanLedGetCount;

    pDdiTable->pfnLedGetProperties                       = driver::xetSysmanLedGetProperties;

    pDdiTable->pfnLedGetState                            = driver::xetSysmanLedGetState;

    pDdiTable->pfnLedSetState                            = driver::xetSysmanLedSetState;

    pDdiTable->pfnRasGetCount                            = driver::xetSysmanRasGetCount;

    pDdiTable->pfnRasGetProperties                       = driver::xetSysmanRasGetProperties;

    pDdiTable->pfnRasGetErrors                           = driver::xetSysmanRasGetErrors;

    pDdiTable->pfnEventsGetProperties                    = driver::xetSysmanEventsGetProperties;

    pDdiTable->pfnEventsRegister                         = driver::xetSysmanEventsRegister;

    pDdiTable->pfnEventsUnregister                       = driver::xetSysmanEventsUnregister;

    pDdiTable->pfnEventsListen                           = driver::xetSysmanEventsListen;

    pDdiTable->pfnDiagnosticsGetCount                    = driver::xetSysmanDiagnosticsGetCount;

    pDdiTable->pfnDiagnosticsGetProperties               = driver::xetSysmanDiagnosticsGetProperties;

    pDdiTable->pfnDiagnosticsRunTests                    = driver::xetSysmanDiagnosticsRunTests;

    return result;
}

#if defined(__cplusplus)
};
#endif
