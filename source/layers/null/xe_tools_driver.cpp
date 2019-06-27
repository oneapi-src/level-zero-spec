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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.xetDdiTable.MetricGroup.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDeviceGroup, pCount, phMetricGroups );
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
    /// @brief Intercept function for xetSysmanCreate
    xe_result_t __xecall
    xetSysmanCreate(
        xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
        uint32_t flags,                                 ///< [in] bitfield of ::xet_sysman_init_flags_t
        xet_sysman_handle_t* phSysman                   ///< [out] handle for accessing SMI features
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xetDdiTable.Sysman.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDeviceGroup, flags, phSysman );
        }
        else
        {
            // generic implementation
            *phSysman = reinterpret_cast<xet_sysman_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xetDdiTable.Sysman.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hSysman );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetResourceContainers = context.xetDdiTable.Sysman.pfnGetResourceContainers;
        if( nullptr != pfnGetResourceContainers )
        {
            result = pfnGetResourceContainers( hSysman, type, pCount, phResContainers );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phResContainers ) && ( i < *pCount ); ++i )
                phResContainers[ i ] = reinterpret_cast<xet_res_container_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDeviceResourceContainer = context.xetDdiTable.Sysman.pfnGetDeviceResourceContainer;
        if( nullptr != pfnGetDeviceResourceContainer )
        {
            result = pfnGetDeviceResourceContainer( hSysman, hDevice, phResContainer );
        }
        else
        {
            // generic implementation
            *phResContainer = reinterpret_cast<xet_res_container_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetResourceContainerByUuid = context.xetDdiTable.Sysman.pfnGetResourceContainerByUuid;
        if( nullptr != pfnGetResourceContainerByUuid )
        {
            result = pfnGetResourceContainerByUuid( hSysman, uuid, phResContainer );
        }
        else
        {
            // generic implementation
            *phResContainer = reinterpret_cast<xet_res_container_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetInfo = context.xetDdiTable.SysmanResContainer.pfnGetInfo;
        if( nullptr != pfnGetInfo )
        {
            result = pfnGetInfo( hResContainer, pInfo );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetParent = context.xetDdiTable.SysmanResContainer.pfnGetParent;
        if( nullptr != pfnGetParent )
        {
            result = pfnGetParent( hResContainer, phResContainer );
        }
        else
        {
            // generic implementation
            *phResContainer = reinterpret_cast<xet_res_container_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetChildren = context.xetDdiTable.SysmanResContainer.pfnGetChildren;
        if( nullptr != pfnGetChildren )
        {
            result = pfnGetChildren( hResContainter, pCount, phResContainers );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phResContainers ) && ( i < *pCount ); ++i )
                phResContainers[ i ] = reinterpret_cast<xet_res_container_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetPeers = context.xetDdiTable.SysmanResContainer.pfnGetPeers;
        if( nullptr != pfnGetPeers )
        {
            result = pfnGetPeers( hResContainter, pCount, phResContainers );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phResContainers ) && ( i < *pCount ); ++i )
                phResContainers[ i ] = reinterpret_cast<xet_res_container_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetResources = context.xetDdiTable.SysmanResContainer.pfnGetResources;
        if( nullptr != pfnGetResources )
        {
            result = pfnGetResources( hResContainter, type, pCount, phResources );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phResources ) && ( i < *pCount ); ++i )
                phResources[ i ] = reinterpret_cast<xet_resource_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetInfo = context.xetDdiTable.SysmanResource.pfnGetInfo;
        if( nullptr != pfnGetInfo )
        {
            result = pfnGetInfo( hResource, pInfo );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetBoardProperties = context.xetDdiTable.SysmanResContainer.pfnGetBoardProperties;
        if( nullptr != pfnGetBoardProperties )
        {
            result = pfnGetBoardProperties( hResContainer, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDeviceProperties = context.xetDdiTable.SysmanResContainer.pfnGetDeviceProperties;
        if( nullptr != pfnGetDeviceProperties )
        {
            result = pfnGetDeviceProperties( hResContainer, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetDeviceProperties = context.xetDdiTable.SysmanResContainer.pfnSetDeviceProperties;
        if( nullptr != pfnSetDeviceProperties )
        {
            result = pfnSetDeviceProperties( hResContainer, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetPsuProperties = context.xetDdiTable.SysmanResource.pfnGetPsuProperties;
        if( nullptr != pfnGetPsuProperties )
        {
            result = pfnGetPsuProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetPsuProperties = context.xetDdiTable.SysmanResource.pfnSetPsuProperties;
        if( nullptr != pfnSetPsuProperties )
        {
            result = pfnSetPsuProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTempProperties = context.xetDdiTable.SysmanResource.pfnGetTempProperties;
        if( nullptr != pfnGetTempProperties )
        {
            result = pfnGetTempProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetTempProperties = context.xetDdiTable.SysmanResource.pfnSetTempProperties;
        if( nullptr != pfnSetTempProperties )
        {
            result = pfnSetTempProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFanProperties = context.xetDdiTable.SysmanResource.pfnGetFanProperties;
        if( nullptr != pfnGetFanProperties )
        {
            result = pfnGetFanProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetFanProperties = context.xetDdiTable.SysmanResource.pfnSetFanProperties;
        if( nullptr != pfnSetFanProperties )
        {
            result = pfnSetFanProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLedProperties = context.xetDdiTable.SysmanResource.pfnGetLedProperties;
        if( nullptr != pfnGetLedProperties )
        {
            result = pfnGetLedProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLedProperties = context.xetDdiTable.SysmanResource.pfnSetLedProperties;
        if( nullptr != pfnSetLedProperties )
        {
            result = pfnSetLedProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFirmwareProperties = context.xetDdiTable.SysmanResource.pfnGetFirmwareProperties;
        if( nullptr != pfnGetFirmwareProperties )
        {
            result = pfnGetFirmwareProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetFirmwareProperties = context.xetDdiTable.SysmanResource.pfnSetFirmwareProperties;
        if( nullptr != pfnSetFirmwareProperties )
        {
            result = pfnSetFirmwareProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetPwrProperties = context.xetDdiTable.SysmanResource.pfnGetPwrProperties;
        if( nullptr != pfnGetPwrProperties )
        {
            result = pfnGetPwrProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetPwrProperties = context.xetDdiTable.SysmanResource.pfnSetPwrProperties;
        if( nullptr != pfnSetPwrProperties )
        {
            result = pfnSetPwrProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFreqProperties = context.xetDdiTable.SysmanResource.pfnGetFreqProperties;
        if( nullptr != pfnGetFreqProperties )
        {
            result = pfnGetFreqProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetFreqProperties = context.xetDdiTable.SysmanResource.pfnSetFreqProperties;
        if( nullptr != pfnSetFreqProperties )
        {
            result = pfnSetFreqProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetPwrWellProperties = context.xetDdiTable.SysmanResource.pfnGetPwrWellProperties;
        if( nullptr != pfnGetPwrWellProperties )
        {
            result = pfnGetPwrWellProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetPwrWellProperties = context.xetDdiTable.SysmanResource.pfnSetPwrWellProperties;
        if( nullptr != pfnSetPwrWellProperties )
        {
            result = pfnSetPwrWellProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAccelProperties = context.xetDdiTable.SysmanResource.pfnGetAccelProperties;
        if( nullptr != pfnGetAccelProperties )
        {
            result = pfnGetAccelProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetAccelProperties = context.xetDdiTable.SysmanResource.pfnSetAccelProperties;
        if( nullptr != pfnSetAccelProperties )
        {
            result = pfnSetAccelProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemProperties = context.xetDdiTable.SysmanResource.pfnGetMemProperties;
        if( nullptr != pfnGetMemProperties )
        {
            result = pfnGetMemProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetMemProperties = context.xetDdiTable.SysmanResource.pfnSetMemProperties;
        if( nullptr != pfnSetMemProperties )
        {
            result = pfnSetMemProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLinkProperties = context.xetDdiTable.SysmanResource.pfnGetLinkProperties;
        if( nullptr != pfnGetLinkProperties )
        {
            result = pfnGetLinkProperties( hResource, count, pIndexes, pValues, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLinkProperties = context.xetDdiTable.SysmanResource.pfnSetLinkProperties;
        if( nullptr != pfnSetLinkProperties )
        {
            result = pfnSetLinkProperties( hResource, count, pIndexes, pValues, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRegisterEvents = context.xetDdiTable.Sysman.pfnRegisterEvents;
        if( nullptr != pfnRegisterEvents )
        {
            result = pfnRegisterEvents( hSysman, hResource, events );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnUnregisterEvents = context.xetDdiTable.Sysman.pfnUnregisterEvents;
        if( nullptr != pfnUnregisterEvents )
        {
            result = pfnUnregisterEvents( hSysman, hResource, events );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnListenEvents = context.xetDdiTable.Sysman.pfnListenEvents;
        if( nullptr != pfnListenEvents )
        {
            result = pfnListenEvents( hSysman, block, pCount, pEventData );
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
        xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
        const xet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
        xet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xetDdiTable.Tracer.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDeviceGroup, desc, phTracer );
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

    pDdiTable->pfnCreate                                 = driver::xetSysmanCreate;

    pDdiTable->pfnDestroy                                = driver::xetSysmanDestroy;

    pDdiTable->pfnGetResourceContainers                  = driver::xetSysmanGetResourceContainers;

    pDdiTable->pfnGetDeviceResourceContainer             = driver::xetSysmanGetDeviceResourceContainer;

    pDdiTable->pfnGetResourceContainerByUuid             = driver::xetSysmanGetResourceContainerByUuid;

    pDdiTable->pfnRegisterEvents                         = driver::xetSysmanRegisterEvents;

    pDdiTable->pfnUnregisterEvents                       = driver::xetSysmanUnregisterEvents;

    pDdiTable->pfnListenEvents                           = driver::xetSysmanListenEvents;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetInfo                                = driver::xetSysmanResContainerGetInfo;

    pDdiTable->pfnGetParent                              = driver::xetSysmanResContainerGetParent;

    pDdiTable->pfnGetChildren                            = driver::xetSysmanResContainerGetChildren;

    pDdiTable->pfnGetPeers                               = driver::xetSysmanResContainerGetPeers;

    pDdiTable->pfnGetResources                           = driver::xetSysmanResContainerGetResources;

    pDdiTable->pfnGetBoardProperties                     = driver::xetSysmanResContainerGetBoardProperties;

    pDdiTable->pfnGetDeviceProperties                    = driver::xetSysmanResContainerGetDeviceProperties;

    pDdiTable->pfnSetDeviceProperties                    = driver::xetSysmanResContainerSetDeviceProperties;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetInfo                                = driver::xetSysmanResourceGetInfo;

    pDdiTable->pfnGetPsuProperties                       = driver::xetSysmanResourceGetPsuProperties;

    pDdiTable->pfnSetPsuProperties                       = driver::xetSysmanResourceSetPsuProperties;

    pDdiTable->pfnGetTempProperties                      = driver::xetSysmanResourceGetTempProperties;

    pDdiTable->pfnSetTempProperties                      = driver::xetSysmanResourceSetTempProperties;

    pDdiTable->pfnGetFanProperties                       = driver::xetSysmanResourceGetFanProperties;

    pDdiTable->pfnSetFanProperties                       = driver::xetSysmanResourceSetFanProperties;

    pDdiTable->pfnGetLedProperties                       = driver::xetSysmanResourceGetLedProperties;

    pDdiTable->pfnSetLedProperties                       = driver::xetSysmanResourceSetLedProperties;

    pDdiTable->pfnGetFirmwareProperties                  = driver::xetSysmanResourceGetFirmwareProperties;

    pDdiTable->pfnSetFirmwareProperties                  = driver::xetSysmanResourceSetFirmwareProperties;

    pDdiTable->pfnGetPwrProperties                       = driver::xetSysmanResourceGetPwrProperties;

    pDdiTable->pfnSetPwrProperties                       = driver::xetSysmanResourceSetPwrProperties;

    pDdiTable->pfnGetFreqProperties                      = driver::xetSysmanResourceGetFreqProperties;

    pDdiTable->pfnSetFreqProperties                      = driver::xetSysmanResourceSetFreqProperties;

    pDdiTable->pfnGetPwrWellProperties                   = driver::xetSysmanResourceGetPwrWellProperties;

    pDdiTable->pfnSetPwrWellProperties                   = driver::xetSysmanResourceSetPwrWellProperties;

    pDdiTable->pfnGetAccelProperties                     = driver::xetSysmanResourceGetAccelProperties;

    pDdiTable->pfnSetAccelProperties                     = driver::xetSysmanResourceSetAccelProperties;

    pDdiTable->pfnGetMemProperties                       = driver::xetSysmanResourceGetMemProperties;

    pDdiTable->pfnSetMemProperties                       = driver::xetSysmanResourceSetMemProperties;

    pDdiTable->pfnGetLinkProperties                      = driver::xetSysmanResourceGetLinkProperties;

    pDdiTable->pfnSetLinkProperties                      = driver::xetSysmanResourceSetLinkProperties;

    return result;
}

#if defined(__cplusplus)
};
#endif
