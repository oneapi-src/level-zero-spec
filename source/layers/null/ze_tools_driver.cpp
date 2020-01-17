/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_tools_driver.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
 * @endcond
 *
 */
#include "ze_null.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetInit
    ze_result_t __zecall
    zetInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInit = context.zetDdiTable.Global.pfnInit;
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
    /// @brief Intercept function for zetDebugAttach
    ze_result_t __zecall
    zetDebugAttach(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAttach = context.zetDdiTable.Debug.pfnAttach;
        if( nullptr != pfnAttach )
        {
            result = pfnAttach( hDevice, config, hDebug );
        }
        else
        {
            // generic implementation
            *hDebug = reinterpret_cast<zet_debug_session_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugDetach
    ze_result_t __zecall
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDetach = context.zetDdiTable.Debug.pfnDetach;
        if( nullptr != pfnDetach )
        {
            result = pfnDetach( hDebug );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetNumThreads
    ze_result_t __zecall
    zetDebugGetNumThreads(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t* pNumThreads                           ///< [out] the maximal number of threads
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetNumThreads = context.zetDdiTable.Debug.pfnGetNumThreads;
        if( nullptr != pfnGetNumThreads )
        {
            result = pfnGetNumThreads( hDebug, pNumThreads );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadEvent
    ze_result_t __zecall
    zetDebugReadEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
        size_t size,                                    ///< [in] the size of the buffer in bytes
        void* buffer                                    ///< [in,out] a buffer to hold the event data
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadEvent = context.zetDdiTable.Debug.pfnReadEvent;
        if( nullptr != pfnReadEvent )
        {
            result = pfnReadEvent( hDebug, timeout, size, buffer );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugInterrupt
    ze_result_t __zecall
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInterrupt = context.zetDdiTable.Debug.pfnInterrupt;
        if( nullptr != pfnInterrupt )
        {
            result = pfnInterrupt( hDebug, threadid );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugResume
    ze_result_t __zecall
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnResume = context.zetDdiTable.Debug.pfnResume;
        if( nullptr != pfnResume )
        {
            result = pfnResume( hDebug, threadid );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadMemory
    ze_result_t __zecall
    zetDebugReadMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to read from
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadMemory = context.zetDdiTable.Debug.pfnReadMemory;
        if( nullptr != pfnReadMemory )
        {
            result = pfnReadMemory( hDebug, threadid, memSpace, address, size, buffer );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteMemory
    ze_result_t __zecall
    zetDebugWriteMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to write to
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnWriteMemory = context.zetDdiTable.Debug.pfnWriteMemory;
        if( nullptr != pfnWriteMemory )
        {
            result = pfnWriteMemory( hDebug, threadid, memSpace, address, size, buffer );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadState
    ze_result_t __zecall
    zetDebugReadState(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadState = context.zetDdiTable.Debug.pfnReadState;
        if( nullptr != pfnReadState )
        {
            result = pfnReadState( hDebug, threadid, offset, size, buffer );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteState
    ze_result_t __zecall
    zetDebugWriteState(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnWriteState = context.zetDdiTable.Debug.pfnWriteState;
        if( nullptr != pfnWriteState )
        {
            result = pfnWriteState( hDebug, threadid, offset, size, buffer );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zetDdiTable.MetricGroup.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDevice, pCount, phMetricGroups );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < *pCount ); ++i )
                phMetricGroups[ i ] = reinterpret_cast<zet_metric_group_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetProperties
    ze_result_t __zecall
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.MetricGroup.pfnGetProperties;
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
    /// @brief Intercept function for zetMetricGroupCalculateMetricValues
    ze_result_t __zecall
    zetMetricGroupCalculateMetricValues(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCalculateMetricValues = context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zetDdiTable.Metric.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hMetricGroup, pCount, phMetrics );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetrics ) && ( i < *pCount ); ++i )
                phMetrics[ i ] = reinterpret_cast<zet_metric_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGetProperties
    ze_result_t __zecall
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.Metric.pfnGetProperties;
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
    /// @brief Intercept function for zetDeviceActivateMetricGroups
    ze_result_t __zecall
    zetDeviceActivateMetricGroups(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                        ///< activate. NULL to deactivate.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnActivateMetricGroups = context.zetDdiTable.Device.pfnActivateMetricGroups;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpen = context.zetDdiTable.MetricTracer.pfnOpen;
        if( nullptr != pfnOpen )
        {
            result = pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
        }
        else
        {
            // generic implementation
            *phMetricTracer = reinterpret_cast<zet_metric_tracer_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricTracerMarker = context.zetDdiTable.CommandList.pfnAppendMetricTracerMarker;
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
    /// @brief Intercept function for zetMetricTracerClose
    ze_result_t __zecall
    zetMetricTracerClose(
        zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.zetDdiTable.MetricTracer.pfnClose;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadData = context.zetDdiTable.MetricTracer.pfnReadData;
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
    /// @brief Intercept function for zetMetricQueryPoolCreate
    ze_result_t __zecall
    zetMetricQueryPoolCreate(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zetDdiTable.MetricQueryPool.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
        }
        else
        {
            // generic implementation
            *phMetricQueryPool = reinterpret_cast<zet_metric_query_pool_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolDestroy
    ze_result_t __zecall
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zetDdiTable.MetricQueryPool.pfnDestroy;
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
    /// @brief Intercept function for zetMetricQueryCreate
    ze_result_t __zecall
    zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zetDdiTable.MetricQuery.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hMetricQueryPool, index, phMetricQuery );
        }
        else
        {
            // generic implementation
            *phMetricQuery = reinterpret_cast<zet_metric_query_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryDestroy
    ze_result_t __zecall
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zetDdiTable.MetricQuery.pfnDestroy;
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
    /// @brief Intercept function for zetMetricQueryReset
    ze_result_t __zecall
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zetDdiTable.MetricQuery.pfnReset;
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
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    ze_result_t __zecall
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricQueryBegin = context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;
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
    /// @brief Intercept function for zetCommandListAppendMetricQueryEnd
    ze_result_t __zecall
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricQueryEnd = context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;
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
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    ze_result_t __zecall
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricMemoryBarrier = context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetData = context.zetDdiTable.MetricQuery.pfnGetData;
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
    /// @brief Intercept function for zetModuleGetDebugInfo
    ze_result_t __zecall
    zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDebugInfo = context.zetDdiTable.Module.pfnGetDebugInfo;
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
    /// @brief Intercept function for zetKernelGetProfileInfo
    ze_result_t __zecall
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProfileInfo = context.zetDdiTable.Kernel.pfnGetProfileInfo;
        if( nullptr != pfnGetProfileInfo )
        {
            result = pfnGetProfileInfo( hKernel, pInfo );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanGet
    ze_result_t __zecall
    zetSysmanGet(
        zet_device_handle_t hDevice,                    ///< [in] Handle of the device
        zet_sysman_version_t version,                   ///< [in] Sysman version that application was built with
        zet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing Sysman features
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zetDdiTable.Sysman.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDevice, version, phSysman );
        }
        else
        {
            // generic implementation
            *phSysman = reinterpret_cast<zet_sysman_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceGetProperties
    ze_result_t __zecall
    zetSysmanDeviceGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceGetProperties = context.zetDdiTable.Sysman.pfnDeviceGetProperties;
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
    /// @brief Intercept function for zetSysmanSchedulerGetSupportedModes
    ze_result_t __zecall
    zetSysmanSchedulerGetSupportedModes(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of scheduler modes.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of supported modes.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< supported scheduler modes.
                                                        ///< if count is larger than the number of supported scheduler modes, then
                                                        ///< the driver will update the value with the correct number of supported
                                                        ///< scheduler modes that are returned.
        zet_sched_mode_t* pModes                        ///< [in,out][optional][range(0, *pCount)] Array of supported scheduler
                                                        ///< modes
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerGetSupportedModes = context.zetDdiTable.Sysman.pfnSchedulerGetSupportedModes;
        if( nullptr != pfnSchedulerGetSupportedModes )
        {
            result = pfnSchedulerGetSupportedModes( hSysman, pCount, pModes );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetCurrentMode
    ze_result_t __zecall
    zetSysmanSchedulerGetCurrentMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerGetCurrentMode = context.zetDdiTable.Sysman.pfnSchedulerGetCurrentMode;
        if( nullptr != pfnSchedulerGetCurrentMode )
        {
            result = pfnSchedulerGetCurrentMode( hSysman, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetTimeoutModeProperties
    ze_result_t __zecall
    zetSysmanSchedulerGetTimeoutModeProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zet_sched_timeout_properties_t* pConfig         ///< [in] Will contain the current parameters for this mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerGetTimeoutModeProperties = context.zetDdiTable.Sysman.pfnSchedulerGetTimeoutModeProperties;
        if( nullptr != pfnSchedulerGetTimeoutModeProperties )
        {
            result = pfnSchedulerGetTimeoutModeProperties( hSysman, getDefaults, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetTimesliceModeProperties
    ze_result_t __zecall
    zetSysmanSchedulerGetTimesliceModeProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zet_sched_timeslice_properties_t* pConfig       ///< [in] Will contain the current parameters for this mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerGetTimesliceModeProperties = context.zetDdiTable.Sysman.pfnSchedulerGetTimesliceModeProperties;
        if( nullptr != pfnSchedulerGetTimesliceModeProperties )
        {
            result = pfnSchedulerGetTimesliceModeProperties( hSysman, getDefaults, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetTimeoutMode
    ze_result_t __zecall
    zetSysmanSchedulerSetTimeoutMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerSetTimeoutMode = context.zetDdiTable.Sysman.pfnSchedulerSetTimeoutMode;
        if( nullptr != pfnSchedulerSetTimeoutMode )
        {
            result = pfnSchedulerSetTimeoutMode( hSysman, pProperties, pNeedReboot );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetTimesliceMode
    ze_result_t __zecall
    zetSysmanSchedulerSetTimesliceMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerSetTimesliceMode = context.zetDdiTable.Sysman.pfnSchedulerSetTimesliceMode;
        if( nullptr != pfnSchedulerSetTimesliceMode )
        {
            result = pfnSchedulerSetTimesliceMode( hSysman, pProperties, pNeedReboot );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetExclusiveMode
    ze_result_t __zecall
    zetSysmanSchedulerSetExclusiveMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerSetExclusiveMode = context.zetDdiTable.Sysman.pfnSchedulerSetExclusiveMode;
        if( nullptr != pfnSchedulerSetExclusiveMode )
        {
            result = pfnSchedulerSetExclusiveMode( hSysman, pNeedReboot );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetComputeUnitDebugMode
    ze_result_t __zecall
    zetSysmanSchedulerSetComputeUnitDebugMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerSetComputeUnitDebugMode = context.zetDdiTable.Sysman.pfnSchedulerSetComputeUnitDebugMode;
        if( nullptr != pfnSchedulerSetComputeUnitDebugMode )
        {
            result = pfnSchedulerSetComputeUnitDebugMode( hSysman, pNeedReboot );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileGetSupported
    ze_result_t __zecall
    zetSysmanPerformanceProfileGetSupported(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of performance profiles.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of supported performance profiles.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< supported performance profiles.
                                                        ///< if count is larger than the number of supported performance profiles,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< supported performance profiles that are returned.
        zet_perf_profile_t* pProfiles                   ///< [in,out][optional][range(0, *pCount)] Array of supported performance
                                                        ///< profiles
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPerformanceProfileGetSupported = context.zetDdiTable.Sysman.pfnPerformanceProfileGetSupported;
        if( nullptr != pfnPerformanceProfileGetSupported )
        {
            result = pfnPerformanceProfileGetSupported( hSysman, pCount, pProfiles );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileGet
    ze_result_t __zecall
    zetSysmanPerformanceProfileGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_perf_profile_t* pProfile                    ///< [in] The performance profile currently loaded.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPerformanceProfileGet = context.zetDdiTable.Sysman.pfnPerformanceProfileGet;
        if( nullptr != pfnPerformanceProfileGet )
        {
            result = pfnPerformanceProfileGet( hSysman, pProfile );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileSet
    ze_result_t __zecall
    zetSysmanPerformanceProfileSet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_perf_profile_t profile                      ///< [in] The performance profile to load.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPerformanceProfileSet = context.zetDdiTable.Sysman.pfnPerformanceProfileSet;
        if( nullptr != pfnPerformanceProfileSet )
        {
            result = pfnPerformanceProfileSet( hSysman, profile );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanProcessesGetState
    ze_result_t __zecall
    zetSysmanProcessesGetState(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of processes currently using the device.
                                                        ///< if count is non-zero, then driver will only retrieve that number of processes.
                                                        ///< if count is larger than the number of processes, then the driver will
                                                        ///< update the value with the correct number of processes that are returned.
        zet_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                        ///< one for each process currently using the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnProcessesGetState = context.zetDdiTable.Sysman.pfnProcessesGetState;
        if( nullptr != pfnProcessesGetState )
        {
            result = pfnProcessesGetState( hSysman, pCount, pProcesses );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceReset
    ze_result_t __zecall
    zetSysmanDeviceReset(
        zet_sysman_handle_t hSysman                     ///< [in] Sysman handle for the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceReset = context.zetDdiTable.Sysman.pfnDeviceReset;
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
    /// @brief Intercept function for zetSysmanDeviceGetRepairStatus
    ze_result_t __zecall
    zetSysmanDeviceGetRepairStatus(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zet_repair_status_t* pRepairStatus              ///< [in] Will indicate if the device was repaired
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceGetRepairStatus = context.zetDdiTable.Sysman.pfnDeviceGetRepairStatus;
        if( nullptr != pfnDeviceGetRepairStatus )
        {
            result = pfnDeviceGetRepairStatus( hSysman, pRepairStatus );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetProperties
    ze_result_t __zecall
    zetSysmanPciGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetProperties = context.zetDdiTable.Sysman.pfnPciGetProperties;
        if( nullptr != pfnPciGetProperties )
        {
            result = pfnPciGetProperties( hSysman, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetState
    ze_result_t __zecall
    zetSysmanPciGetState(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetState = context.zetDdiTable.Sysman.pfnPciGetState;
        if( nullptr != pfnPciGetState )
        {
            result = pfnPciGetState( hSysman, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetBars
    ze_result_t __zecall
    zetSysmanPciGetBars(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of bars.
                                                        ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                        ///< if count is larger than the number of bar, then the driver will update
                                                        ///< the value with the correct number of bars that are returned.
        zet_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of bar properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetBars = context.zetDdiTable.Sysman.pfnPciGetBars;
        if( nullptr != pfnPciGetBars )
        {
            result = pfnPciGetBars( hSysman, pCount, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetStats
    ze_result_t __zecall
    zetSysmanPciGetStats(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetStats = context.zetDdiTable.Sysman.pfnPciGetStats;
        if( nullptr != pfnPciGetStats )
        {
            result = pfnPciGetStats( hSysman, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGet
    ze_result_t __zecall
    zetSysmanPowerGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerGet = context.zetDdiTable.Sysman.pfnPowerGet;
        if( nullptr != pfnPowerGet )
        {
            result = pfnPowerGet( hSysman, pCount, phPower );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<zet_sysman_pwr_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetProperties
    ze_result_t __zecall
    zetSysmanPowerGetProperties(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanPower.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPower, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetEnergyCounter = context.zetDdiTable.SysmanPower.pfnGetEnergyCounter;
        if( nullptr != pfnGetEnergyCounter )
        {
            result = pfnGetEnergyCounter( hPower, pEnergy );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLimits = context.zetDdiTable.SysmanPower.pfnGetLimits;
        if( nullptr != pfnGetLimits )
        {
            result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLimits = context.zetDdiTable.SysmanPower.pfnSetLimits;
        if( nullptr != pfnSetLimits )
        {
            result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetEnergyThreshold
    ze_result_t __zecall
    zetSysmanPowerGetEnergyThreshold(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_energy_threshold_t* pThreshold              ///< [in] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetEnergyThreshold = context.zetDdiTable.SysmanPower.pfnGetEnergyThreshold;
        if( nullptr != pfnGetEnergyThreshold )
        {
            result = pfnGetEnergyThreshold( hPower, pThreshold );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerSetEnergyThreshold
    ze_result_t __zecall
    zetSysmanPowerSetEnergyThreshold(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEnergyThreshold = context.zetDdiTable.SysmanPower.pfnSetEnergyThreshold;
        if( nullptr != pfnSetEnergyThreshold )
        {
            result = pfnSetEnergyThreshold( hPower, threshold );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGet
    ze_result_t __zecall
    zetSysmanFrequencyGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencyGet = context.zetDdiTable.Sysman.pfnFrequencyGet;
        if( nullptr != pfnFrequencyGet )
        {
            result = pfnFrequencyGet( hSysman, pCount, phFrequency );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<zet_sysman_freq_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetProperties
    ze_result_t __zecall
    zetSysmanFrequencyGetProperties(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanFrequency.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFrequency, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetAvailableClocks
    ze_result_t __zecall
    zetSysmanFrequencyGetAvailableClocks(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of frequencies available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                        ///< If count is larger than the number of frequencies available, then the
                                                        ///< driver will update the value with the correct number of frequencies available.
        double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                        ///< MHz and sorted from slowest to fastest
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAvailableClocks = context.zetDdiTable.SysmanFrequency.pfnGetAvailableClocks;
        if( nullptr != pfnGetAvailableClocks )
        {
            result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetRange = context.zetDdiTable.SysmanFrequency.pfnGetRange;
        if( nullptr != pfnGetRange )
        {
            result = pfnGetRange( hFrequency, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetRange = context.zetDdiTable.SysmanFrequency.pfnSetRange;
        if( nullptr != pfnSetRange )
        {
            result = pfnSetRange( hFrequency, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetState
    ze_result_t __zecall
    zetSysmanFrequencyGetState(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanFrequency.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hFrequency, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetThrottleTime = context.zetDdiTable.SysmanFrequency.pfnGetThrottleTime;
        if( nullptr != pfnGetThrottleTime )
        {
            result = pfnGetThrottleTime( hFrequency, pThrottleTime );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetCapabilities
    ze_result_t __zecall
    zetSysmanFrequencyOcGetCapabilities(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_capabilities_t* pOcCapabilities          ///< [in] Pointer to the capabilities structure ::zet_oc_capabilities_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetCapabilities = context.zetDdiTable.SysmanFrequency.pfnOcGetCapabilities;
        if( nullptr != pfnOcGetCapabilities )
        {
            result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetConfig
    ze_result_t __zecall
    zetSysmanFrequencyOcGetConfig(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_config_t* pOcConfiguration               ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetConfig = context.zetDdiTable.SysmanFrequency.pfnOcGetConfig;
        if( nullptr != pfnOcGetConfig )
        {
            result = pfnOcGetConfig( hFrequency, pOcConfiguration );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetConfig
    ze_result_t __zecall
    zetSysmanFrequencyOcSetConfig(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
        ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                        ///< in order to enable the new overclock settings.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetConfig = context.zetDdiTable.SysmanFrequency.pfnOcSetConfig;
        if( nullptr != pfnOcSetConfig )
        {
            result = pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetIccMax
    ze_result_t __zecall
    zetSysmanFrequencyOcGetIccMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in] Will contain the maximum current limit in Amperes on successful
                                                        ///< return.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetIccMax = context.zetDdiTable.SysmanFrequency.pfnOcGetIccMax;
        if( nullptr != pfnOcGetIccMax )
        {
            result = pfnOcGetIccMax( hFrequency, pOcIccMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetIccMax
    ze_result_t __zecall
    zetSysmanFrequencyOcSetIccMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetIccMax = context.zetDdiTable.SysmanFrequency.pfnOcSetIccMax;
        if( nullptr != pfnOcSetIccMax )
        {
            result = pfnOcSetIccMax( hFrequency, ocIccMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetTjMax
    ze_result_t __zecall
    zetSysmanFrequencyOcGetTjMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in] Will contain the maximum temperature limit in degrees Celsius on
                                                        ///< successful return.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetTjMax = context.zetDdiTable.SysmanFrequency.pfnOcGetTjMax;
        if( nullptr != pfnOcGetTjMax )
        {
            result = pfnOcGetTjMax( hFrequency, pOcTjMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetTjMax
    ze_result_t __zecall
    zetSysmanFrequencyOcSetTjMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetTjMax = context.zetDdiTable.SysmanFrequency.pfnOcSetTjMax;
        if( nullptr != pfnOcSetTjMax )
        {
            result = pfnOcSetTjMax( hFrequency, ocTjMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGet
    ze_result_t __zecall
    zetSysmanEngineGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEngineGet = context.zetDdiTable.Sysman.pfnEngineGet;
        if( nullptr != pfnEngineGet )
        {
            result = pfnEngineGet( hSysman, pCount, phEngine );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<zet_sysman_engine_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetProperties
    ze_result_t __zecall
    zetSysmanEngineGetProperties(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanEngine.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hEngine, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetActivity
    ze_result_t __zecall
    zetSysmanEngineGetActivity(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetActivity = context.zetDdiTable.SysmanEngine.pfnGetActivity;
        if( nullptr != pfnGetActivity )
        {
            result = pfnGetActivity( hEngine, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGet
    ze_result_t __zecall
    zetSysmanStandbyGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnStandbyGet = context.zetDdiTable.Sysman.pfnStandbyGet;
        if( nullptr != pfnStandbyGet )
        {
            result = pfnStandbyGet( hSysman, pCount, phStandby );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<zet_sysman_standby_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetProperties
    ze_result_t __zecall
    zetSysmanStandbyGetProperties(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanStandby.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hStandby, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetMode
    ze_result_t __zecall
    zetSysmanStandbyGetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMode = context.zetDdiTable.SysmanStandby.pfnGetMode;
        if( nullptr != pfnGetMode )
        {
            result = pfnGetMode( hStandby, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbySetMode
    ze_result_t __zecall
    zetSysmanStandbySetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetMode = context.zetDdiTable.SysmanStandby.pfnSetMode;
        if( nullptr != pfnSetMode )
        {
            result = pfnSetMode( hStandby, mode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGet
    ze_result_t __zecall
    zetSysmanFirmwareGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFirmwareGet = context.zetDdiTable.Sysman.pfnFirmwareGet;
        if( nullptr != pfnFirmwareGet )
        {
            result = pfnFirmwareGet( hSysman, pCount, phFirmware );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<zet_sysman_firmware_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetProperties
    ze_result_t __zecall
    zetSysmanFirmwareGetProperties(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        zet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanFirmware.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFirmware, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetChecksum
    ze_result_t __zecall
    zetSysmanFirmwareGetChecksum(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetChecksum = context.zetDdiTable.SysmanFirmware.pfnGetChecksum;
        if( nullptr != pfnGetChecksum )
        {
            result = pfnGetChecksum( hFirmware, pChecksum );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFlash = context.zetDdiTable.SysmanFirmware.pfnFlash;
        if( nullptr != pfnFlash )
        {
            result = pfnFlash( hFirmware, pImage, size );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGet
    ze_result_t __zecall
    zetSysmanMemoryGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMemoryGet = context.zetDdiTable.Sysman.pfnMemoryGet;
        if( nullptr != pfnMemoryGet )
        {
            result = pfnMemoryGet( hSysman, pCount, phMemory );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<zet_sysman_mem_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetProperties
    ze_result_t __zecall
    zetSysmanMemoryGetProperties(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanMemory.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hMemory, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetState
    ze_result_t __zecall
    zetSysmanMemoryGetState(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_state_t* pState                         ///< [in] Will contain the current health and allocated memory.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanMemory.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hMemory, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetBandwidth
    ze_result_t __zecall
    zetSysmanMemoryGetBandwidth(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetBandwidth = context.zetDdiTable.SysmanMemory.pfnGetBandwidth;
        if( nullptr != pfnGetBandwidth )
        {
            result = pfnGetBandwidth( hMemory, pBandwidth );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGet
    ze_result_t __zecall
    zetSysmanFabricPortGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_fabric_port_handle_t* phPort         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFabricPortGet = context.zetDdiTable.Sysman.pfnFabricPortGet;
        if( nullptr != pfnFabricPortGet )
        {
            result = pfnFabricPortGet( hSysman, pCount, phPort );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<zet_sysman_fabric_port_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetProperties
    ze_result_t __zecall
    zetSysmanFabricPortGetProperties(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_properties_t* pProperties       ///< [in] Will contain properties of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanFabricPort.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPort, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetLinkType
    ze_result_t __zecall
    zetSysmanFabricPortGetLinkType(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
        zet_fabric_link_type_t* pLinkType               ///< [in] Will contain details about the link attached to the Fabric port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLinkType = context.zetDdiTable.SysmanFabricPort.pfnGetLinkType;
        if( nullptr != pfnGetLinkType )
        {
            result = pfnGetLinkType( hPort, verbose, pLinkType );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetConfig
    ze_result_t __zecall
    zetSysmanFabricPortGetConfig(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_config_t* pConfig               ///< [in] Will contain configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zetDdiTable.SysmanFabricPort.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hPort, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortSetConfig
    ze_result_t __zecall
    zetSysmanFabricPortSetConfig(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        const zet_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zetDdiTable.SysmanFabricPort.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hPort, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetState
    ze_result_t __zecall
    zetSysmanFabricPortGetState(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_state_t* pState                 ///< [in] Will contain the current state of the Fabric Port
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanFabricPort.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hPort, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetThroughput
    ze_result_t __zecall
    zetSysmanFabricPortGetThroughput(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_throughput_t* pThroughput       ///< [in] Will contain the Fabric port throughput counters and maximum
                                                        ///< bandwidth.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetThroughput = context.zetDdiTable.SysmanFabricPort.pfnGetThroughput;
        if( nullptr != pfnGetThroughput )
        {
            result = pfnGetThroughput( hPort, pThroughput );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGet
    ze_result_t __zecall
    zetSysmanTemperatureGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnTemperatureGet = context.zetDdiTable.Sysman.pfnTemperatureGet;
        if( nullptr != pfnTemperatureGet )
        {
            result = pfnTemperatureGet( hSysman, pCount, phTemperature );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<zet_sysman_temp_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetProperties
    ze_result_t __zecall
    zetSysmanTemperatureGetProperties(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanTemperature.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hTemperature, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetConfig
    ze_result_t __zecall
    zetSysmanTemperatureGetConfig(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zet_temp_config_t* pConfig                      ///< [in] Returns current configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zetDdiTable.SysmanTemperature.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hTemperature, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureSetConfig
    ze_result_t __zecall
    zetSysmanTemperatureSetConfig(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        const zet_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zetDdiTable.SysmanTemperature.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hTemperature, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetState
    ze_result_t __zecall
    zetSysmanTemperatureGetState(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        double* pTemperature                            ///< [in] Will contain the temperature read from the specified sensor in
                                                        ///< degrees Celcius.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanTemperature.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hTemperature, pTemperature );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGet
    ze_result_t __zecall
    zetSysmanPsuGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPsuGet = context.zetDdiTable.Sysman.pfnPsuGet;
        if( nullptr != pfnPsuGet )
        {
            result = pfnPsuGet( hSysman, pCount, phPsu );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<zet_sysman_psu_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetProperties
    ze_result_t __zecall
    zetSysmanPsuGetProperties(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanPsu.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPsu, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetState
    ze_result_t __zecall
    zetSysmanPsuGetState(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanPsu.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hPsu, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGet
    ze_result_t __zecall
    zetSysmanFanGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFanGet = context.zetDdiTable.Sysman.pfnFanGet;
        if( nullptr != pfnFanGet )
        {
            result = pfnFanGet( hSysman, pCount, phFan );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<zet_sysman_fan_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetProperties
    ze_result_t __zecall
    zetSysmanFanGetProperties(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanFan.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFan, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetConfig
    ze_result_t __zecall
    zetSysmanFanGetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zetDdiTable.SysmanFan.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hFan, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanSetConfig
    ze_result_t __zecall
    zetSysmanFanSetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zetDdiTable.SysmanFan.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hFan, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetState
    ze_result_t __zecall
    zetSysmanFanGetState(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        uint32_t* pSpeed                                ///< [in] Will contain the current speed of the fan in the units requested.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanFan.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hFan, units, pSpeed );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGet
    ze_result_t __zecall
    zetSysmanLedGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnLedGet = context.zetDdiTable.Sysman.pfnLedGet;
        if( nullptr != pfnLedGet )
        {
            result = pfnLedGet( hSysman, pCount, phLed );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<zet_sysman_led_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetProperties
    ze_result_t __zecall
    zetSysmanLedGetProperties(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanLed.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hLed, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetState
    ze_result_t __zecall
    zetSysmanLedGetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanLed.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hLed, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedSetState
    ze_result_t __zecall
    zetSysmanLedSetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const zet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetState = context.zetDdiTable.SysmanLed.pfnSetState;
        if( nullptr != pfnSetState )
        {
            result = pfnSetState( hLed, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGet
    ze_result_t __zecall
    zetSysmanRasGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRasGet = context.zetDdiTable.Sysman.pfnRasGet;
        if( nullptr != pfnRasGet )
        {
            result = pfnRasGet( hSysman, pCount, phRas );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<zet_sysman_ras_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetProperties
    ze_result_t __zecall
    zetSysmanRasGetProperties(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanRas.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hRas, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetConfig
    ze_result_t __zecall
    zetSysmanRasGetConfig(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zet_ras_config_t* pConfig                       ///< [in] Will be populed with the current RAS configuration - thresholds
                                                        ///< used to trigger events
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zetDdiTable.SysmanRas.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hRas, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasSetConfig
    ze_result_t __zecall
    zetSysmanRasSetConfig(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        const zet_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zetDdiTable.SysmanRas.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hRas, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetState
    ze_result_t __zecall
    zetSysmanRasGetState(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
        zet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanRas.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hRas, clear, pTotalErrors, pDetails );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventGet
    ze_result_t __zecall
    zetSysmanEventGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zet_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventGet = context.zetDdiTable.Sysman.pfnEventGet;
        if( nullptr != pfnEventGet )
        {
            result = pfnEventGet( hSysman, phEvent );
        }
        else
        {
            // generic implementation
            *phEvent = reinterpret_cast<zet_sysman_event_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventGetConfig
    ze_result_t __zecall
    zetSysmanEventGetConfig(
        zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        zet_event_config_t* pConfig                     ///< [in] Will contain the current event configuration (list of registered
                                                        ///< events).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zetDdiTable.SysmanEvent.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hEvent, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventSetConfig
    ze_result_t __zecall
    zetSysmanEventSetConfig(
        zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        const zet_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zetDdiTable.SysmanEvent.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hEvent, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventGetState
    ze_result_t __zecall
    zetSysmanEventGetState(
        zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device.
        ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
        uint32_t* pEvents                               ///< [in] Bitfield of events ::zet_sysman_event_type_t that have been
                                                        ///< triggered by this device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zetDdiTable.SysmanEvent.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hEvent, clear, pEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventListen
    ze_result_t __zecall
    zetSysmanEventListen(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                        ///< ::ZET_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                        ///< ::ZET_EVENT_WAIT_INFINITE to block until events arrive.
        uint32_t count,                                 ///< [in] Number of handles in phEvents
        zet_sysman_event_handle_t* phEvents,            ///< [in][range(0, count)] Handle of events that should be listened to
        uint32_t* pEvents                               ///< [in] Bitfield of events ::zet_sysman_event_type_t that have been
                                                        ///< triggered by any of the supplied event handles. If timeout is not
                                                        ///< ::ZET_EVENT_WAIT_INFINITE and this value is
                                                        ///< ::ZET_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnListen = context.zetDdiTable.SysmanEvent.pfnListen;
        if( nullptr != pfnListen )
        {
            result = pfnListen( hDriver, timeout, count, phEvents, pEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGet
    ze_result_t __zecall
    zetSysmanDiagnosticsGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDiagnosticsGet = context.zetDdiTable.Sysman.pfnDiagnosticsGet;
        if( nullptr != pfnDiagnosticsGet )
        {
            result = pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<zet_sysman_diag_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGetProperties
    ze_result_t __zecall
    zetSysmanDiagnosticsGetProperties(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        zet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.SysmanDiagnostics.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDiagnostics, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGetTests
    ze_result_t __zecall
    zetSysmanDiagnosticsGetTests(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of tests available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                        ///< If count is larger than the number of tests available, then the driver
                                                        ///< will update the value with the correct number of tests available.
        zet_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                        ///< increasing value of ::zet_diag_test_t.index
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTests = context.zetDdiTable.SysmanDiagnostics.pfnGetTests;
        if( nullptr != pfnGetTests )
        {
            result = pfnGetTests( hDiagnostics, pCount, pTests );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRunTests = context.zetDdiTable.SysmanDiagnostics.pfnRunTests;
        if( nullptr != pfnRunTests )
        {
            result = pfnRunTests( hDiagnostics, start, end, pResult );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerCreate
    ze_result_t __zecall
    zetTracerCreate(
        zet_driver_handle_t hDriver,                    ///< [in] handle of the driver
        const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
        zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zetDdiTable.Tracer.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDriver, desc, phTracer );
        }
        else
        {
            // generic implementation
            *phTracer = reinterpret_cast<zet_tracer_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerDestroy
    ze_result_t __zecall
    zetTracerDestroy(
        zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zetDdiTable.Tracer.pfnDestroy;
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
    /// @brief Intercept function for zetTracerSetPrologues
    ze_result_t __zecall
    zetTracerSetPrologues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
        zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetPrologues = context.zetDdiTable.Tracer.pfnSetPrologues;
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
    /// @brief Intercept function for zetTracerSetEpilogues
    ze_result_t __zecall
    zetTracerSetEpilogues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
        zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEpilogues = context.zetDdiTable.Tracer.pfnSetEpilogues;
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
    /// @brief Intercept function for zetTracerSetEnabled
    ze_result_t __zecall
    zetTracerSetEnabled(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEnabled = context.zetDdiTable.Tracer.pfnSetEnabled;
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnInit                                   = driver::zetInit;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnActivateMetricGroups                   = driver::zetDeviceActivateMetricGroups;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnAppendMetricTracerMarker               = driver::zetCommandListAppendMetricTracerMarker;

    pDdiTable->pfnAppendMetricQueryBegin                 = driver::zetCommandListAppendMetricQueryBegin;

    pDdiTable->pfnAppendMetricQueryEnd                   = driver::zetCommandListAppendMetricQueryEnd;

    pDdiTable->pfnAppendMetricMemoryBarrier              = driver::zetCommandListAppendMetricMemoryBarrier;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetDebugInfo                           = driver::zetModuleGetDebugInfo;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProfileInfo                         = driver::zetKernelGetProfileInfo;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::zetMetricGroupGet;

    pDdiTable->pfnGetProperties                          = driver::zetMetricGroupGetProperties;

    pDdiTable->pfnCalculateMetricValues                  = driver::zetMetricGroupCalculateMetricValues;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::zetMetricGet;

    pDdiTable->pfnGetProperties                          = driver::zetMetricGetProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnOpen                                   = driver::zetMetricTracerOpen;

    pDdiTable->pfnClose                                  = driver::zetMetricTracerClose;

    pDdiTable->pfnReadData                               = driver::zetMetricTracerReadData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::zetMetricQueryPoolCreate;

    pDdiTable->pfnDestroy                                = driver::zetMetricQueryPoolDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::zetMetricQueryCreate;

    pDdiTable->pfnDestroy                                = driver::zetMetricQueryDestroy;

    pDdiTable->pfnReset                                  = driver::zetMetricQueryReset;

    pDdiTable->pfnGetData                                = driver::zetMetricQueryGetData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::zetTracerCreate;

    pDdiTable->pfnDestroy                                = driver::zetTracerDestroy;

    pDdiTable->pfnSetPrologues                           = driver::zetTracerSetPrologues;

    pDdiTable->pfnSetEpilogues                           = driver::zetTracerSetEpilogues;

    pDdiTable->pfnSetEnabled                             = driver::zetTracerSetEnabled;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::zetSysmanGet;

    pDdiTable->pfnDeviceGetProperties                    = driver::zetSysmanDeviceGetProperties;

    pDdiTable->pfnSchedulerGetSupportedModes             = driver::zetSysmanSchedulerGetSupportedModes;

    pDdiTable->pfnSchedulerGetCurrentMode                = driver::zetSysmanSchedulerGetCurrentMode;

    pDdiTable->pfnSchedulerGetTimeoutModeProperties      = driver::zetSysmanSchedulerGetTimeoutModeProperties;

    pDdiTable->pfnSchedulerGetTimesliceModeProperties    = driver::zetSysmanSchedulerGetTimesliceModeProperties;

    pDdiTable->pfnSchedulerSetTimeoutMode                = driver::zetSysmanSchedulerSetTimeoutMode;

    pDdiTable->pfnSchedulerSetTimesliceMode              = driver::zetSysmanSchedulerSetTimesliceMode;

    pDdiTable->pfnSchedulerSetExclusiveMode              = driver::zetSysmanSchedulerSetExclusiveMode;

    pDdiTable->pfnSchedulerSetComputeUnitDebugMode       = driver::zetSysmanSchedulerSetComputeUnitDebugMode;

    pDdiTable->pfnPerformanceProfileGetSupported         = driver::zetSysmanPerformanceProfileGetSupported;

    pDdiTable->pfnPerformanceProfileGet                  = driver::zetSysmanPerformanceProfileGet;

    pDdiTable->pfnPerformanceProfileSet                  = driver::zetSysmanPerformanceProfileSet;

    pDdiTable->pfnProcessesGetState                      = driver::zetSysmanProcessesGetState;

    pDdiTable->pfnDeviceReset                            = driver::zetSysmanDeviceReset;

    pDdiTable->pfnDeviceGetRepairStatus                  = driver::zetSysmanDeviceGetRepairStatus;

    pDdiTable->pfnPciGetProperties                       = driver::zetSysmanPciGetProperties;

    pDdiTable->pfnPciGetState                            = driver::zetSysmanPciGetState;

    pDdiTable->pfnPciGetBars                             = driver::zetSysmanPciGetBars;

    pDdiTable->pfnPciGetStats                            = driver::zetSysmanPciGetStats;

    pDdiTable->pfnPowerGet                               = driver::zetSysmanPowerGet;

    pDdiTable->pfnFrequencyGet                           = driver::zetSysmanFrequencyGet;

    pDdiTable->pfnEngineGet                              = driver::zetSysmanEngineGet;

    pDdiTable->pfnStandbyGet                             = driver::zetSysmanStandbyGet;

    pDdiTable->pfnFirmwareGet                            = driver::zetSysmanFirmwareGet;

    pDdiTable->pfnMemoryGet                              = driver::zetSysmanMemoryGet;

    pDdiTable->pfnFabricPortGet                          = driver::zetSysmanFabricPortGet;

    pDdiTable->pfnTemperatureGet                         = driver::zetSysmanTemperatureGet;

    pDdiTable->pfnPsuGet                                 = driver::zetSysmanPsuGet;

    pDdiTable->pfnFanGet                                 = driver::zetSysmanFanGet;

    pDdiTable->pfnLedGet                                 = driver::zetSysmanLedGet;

    pDdiTable->pfnRasGet                                 = driver::zetSysmanRasGet;

    pDdiTable->pfnEventGet                               = driver::zetSysmanEventGet;

    pDdiTable->pfnDiagnosticsGet                         = driver::zetSysmanDiagnosticsGet;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanPowerGetProperties;

    pDdiTable->pfnGetEnergyCounter                       = driver::zetSysmanPowerGetEnergyCounter;

    pDdiTable->pfnGetLimits                              = driver::zetSysmanPowerGetLimits;

    pDdiTable->pfnSetLimits                              = driver::zetSysmanPowerSetLimits;

    pDdiTable->pfnGetEnergyThreshold                     = driver::zetSysmanPowerGetEnergyThreshold;

    pDdiTable->pfnSetEnergyThreshold                     = driver::zetSysmanPowerSetEnergyThreshold;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanFrequencyGetProperties;

    pDdiTable->pfnGetAvailableClocks                     = driver::zetSysmanFrequencyGetAvailableClocks;

    pDdiTable->pfnGetRange                               = driver::zetSysmanFrequencyGetRange;

    pDdiTable->pfnSetRange                               = driver::zetSysmanFrequencySetRange;

    pDdiTable->pfnGetState                               = driver::zetSysmanFrequencyGetState;

    pDdiTable->pfnGetThrottleTime                        = driver::zetSysmanFrequencyGetThrottleTime;

    pDdiTable->pfnOcGetCapabilities                      = driver::zetSysmanFrequencyOcGetCapabilities;

    pDdiTable->pfnOcGetConfig                            = driver::zetSysmanFrequencyOcGetConfig;

    pDdiTable->pfnOcSetConfig                            = driver::zetSysmanFrequencyOcSetConfig;

    pDdiTable->pfnOcGetIccMax                            = driver::zetSysmanFrequencyOcGetIccMax;

    pDdiTable->pfnOcSetIccMax                            = driver::zetSysmanFrequencyOcSetIccMax;

    pDdiTable->pfnOcGetTjMax                             = driver::zetSysmanFrequencyOcGetTjMax;

    pDdiTable->pfnOcSetTjMax                             = driver::zetSysmanFrequencyOcSetTjMax;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanEngineGetProperties;

    pDdiTable->pfnGetActivity                            = driver::zetSysmanEngineGetActivity;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanStandbyGetProperties;

    pDdiTable->pfnGetMode                                = driver::zetSysmanStandbyGetMode;

    pDdiTable->pfnSetMode                                = driver::zetSysmanStandbySetMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanFirmwareGetProperties;

    pDdiTable->pfnGetChecksum                            = driver::zetSysmanFirmwareGetChecksum;

    pDdiTable->pfnFlash                                  = driver::zetSysmanFirmwareFlash;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanMemoryGetProperties;

    pDdiTable->pfnGetState                               = driver::zetSysmanMemoryGetState;

    pDdiTable->pfnGetBandwidth                           = driver::zetSysmanMemoryGetBandwidth;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fabric_port_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanFabricPortGetProperties;

    pDdiTable->pfnGetLinkType                            = driver::zetSysmanFabricPortGetLinkType;

    pDdiTable->pfnGetConfig                              = driver::zetSysmanFabricPortGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zetSysmanFabricPortSetConfig;

    pDdiTable->pfnGetState                               = driver::zetSysmanFabricPortGetState;

    pDdiTable->pfnGetThroughput                          = driver::zetSysmanFabricPortGetThroughput;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanTemperatureGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zetSysmanTemperatureGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zetSysmanTemperatureSetConfig;

    pDdiTable->pfnGetState                               = driver::zetSysmanTemperatureGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanPsuGetProperties;

    pDdiTable->pfnGetState                               = driver::zetSysmanPsuGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanFanGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zetSysmanFanGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zetSysmanFanSetConfig;

    pDdiTable->pfnGetState                               = driver::zetSysmanFanGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanLedGetProperties;

    pDdiTable->pfnGetState                               = driver::zetSysmanLedGetState;

    pDdiTable->pfnSetState                               = driver::zetSysmanLedSetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanRasGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zetSysmanRasGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zetSysmanRasSetConfig;

    pDdiTable->pfnGetState                               = driver::zetSysmanRasGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zetSysmanDiagnosticsGetProperties;

    pDdiTable->pfnGetTests                               = driver::zetSysmanDiagnosticsGetTests;

    pDdiTable->pfnRunTests                               = driver::zetSysmanDiagnosticsRunTests;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEvent table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_event_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetConfig                              = driver::zetSysmanEventGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zetSysmanEventSetConfig;

    pDdiTable->pfnGetState                               = driver::zetSysmanEventGetState;

    pDdiTable->pfnListen                                 = driver::zetSysmanEventListen;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Debug table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnAttach                                 = driver::zetDebugAttach;

    pDdiTable->pfnDetach                                 = driver::zetDebugDetach;

    pDdiTable->pfnGetNumThreads                          = driver::zetDebugGetNumThreads;

    pDdiTable->pfnReadEvent                              = driver::zetDebugReadEvent;

    pDdiTable->pfnInterrupt                              = driver::zetDebugInterrupt;

    pDdiTable->pfnResume                                 = driver::zetDebugResume;

    pDdiTable->pfnReadMemory                             = driver::zetDebugReadMemory;

    pDdiTable->pfnWriteMemory                            = driver::zetDebugWriteMemory;

    pDdiTable->pfnReadState                              = driver::zetDebugReadState;

    pDdiTable->pfnWriteState                             = driver::zetDebugWriteState;

    return result;
}

#if defined(__cplusplus)
};
#endif
