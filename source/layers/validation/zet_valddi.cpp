/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_valddi.cpp
 * @version v1.0-r0.9.276
 *
 */
#include "ze_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugAttach
    __zedlllocal ze_result_t __zecall
    zetDebugAttach(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
        )
    {
        auto pfnAttach = context.zetDdiTable.Debug.pfnAttach;

        if( nullptr == pfnAttach )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == config )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAttach( hDevice, config, hDebug );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugDetach
    __zedlllocal ze_result_t __zecall
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    {
        auto pfnDetach = context.zetDdiTable.Debug.pfnDetach;

        if( nullptr == pfnDetach )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDetach( hDebug );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetNumThreads
    __zedlllocal ze_result_t __zecall
    zetDebugGetNumThreads(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t* pNumThreads                           ///< [out] the maximal number of threads
        )
    {
        auto pfnGetNumThreads = context.zetDdiTable.Debug.pfnGetNumThreads;

        if( nullptr == pfnGetNumThreads )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNumThreads )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetNumThreads( hDebug, pNumThreads );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadEvent
    __zedlllocal ze_result_t __zecall
    zetDebugReadEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
        size_t size,                                    ///< [in] the size of the buffer in bytes
        void* buffer                                    ///< [in,out] a buffer to hold the event data
        )
    {
        auto pfnReadEvent = context.zetDdiTable.Debug.pfnReadEvent;

        if( nullptr == pfnReadEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadEvent( hDebug, timeout, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugInterrupt
    __zedlllocal ze_result_t __zecall
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto pfnInterrupt = context.zetDdiTable.Debug.pfnInterrupt;

        if( nullptr == pfnInterrupt )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnInterrupt( hDebug, threadid );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugResume
    __zedlllocal ze_result_t __zecall
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto pfnResume = context.zetDdiTable.Debug.pfnResume;

        if( nullptr == pfnResume )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnResume( hDebug, threadid );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadMemory
    __zedlllocal ze_result_t __zecall
    zetDebugReadMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to read from
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    {
        auto pfnReadMemory = context.zetDdiTable.Debug.pfnReadMemory;

        if( nullptr == pfnReadMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadMemory( hDebug, threadid, memSpace, address, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteMemory
    __zedlllocal ze_result_t __zecall
    zetDebugWriteMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to write to
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto pfnWriteMemory = context.zetDdiTable.Debug.pfnWriteMemory;

        if( nullptr == pfnWriteMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnWriteMemory( hDebug, threadid, memSpace, address, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadState
    __zedlllocal ze_result_t __zecall
    zetDebugReadState(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
        )
    {
        auto pfnReadState = context.zetDdiTable.Debug.pfnReadState;

        if( nullptr == pfnReadState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadState( hDebug, threadid, offset, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteState
    __zedlllocal ze_result_t __zecall
    zetDebugWriteState(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto pfnWriteState = context.zetDdiTable.Debug.pfnWriteState;

        if( nullptr == pfnWriteState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnWriteState( hDebug, threadid, offset, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGet
    __zedlllocal ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hDevice, pCount, phMetricGroups );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetProperties
    __zedlllocal ze_result_t __zecall
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.MetricGroup.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hMetricGroup, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMetricValues
    __zedlllocal ze_result_t __zecall
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
        auto pfnCalculateMetricValues = context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;

        if( nullptr == pfnCalculateMetricValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRawData )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pMetricValueCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGet
    __zedlllocal ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hMetricGroup, pCount, phMetrics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGetProperties
    __zedlllocal ze_result_t __zecall
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.Metric.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetric )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hMetric, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceActivateMetricGroups
    __zedlllocal ze_result_t __zecall
    zetDeviceActivateMetricGroups(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                        ///< activate. NULL to deactivate.
        )
    {
        auto pfnActivateMetricGroups = context.zetDdiTable.Device.pfnActivateMetricGroups;

        if( nullptr == pfnActivateMetricGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnActivateMetricGroups( hDevice, count, phMetricGroups );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerOpen
    __zedlllocal ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZET_METRIC_TRACER_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        }

        return pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricTracerMarker
    __zedlllocal ze_result_t __zecall
    zetCommandListAppendMetricTracerMarker(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        auto pfnAppendMetricTracerMarker = context.zetDdiTable.CommandList.pfnAppendMetricTracerMarker;

        if( nullptr == pfnAppendMetricTracerMarker )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerClose
    __zedlllocal ze_result_t __zecall
    zetMetricTracerClose(
        zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
        )
    {
        auto pfnClose = context.zetDdiTable.MetricTracer.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnClose( hMetricTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerReadData
    __zedlllocal ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRawDataSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolCreate
    __zedlllocal ze_result_t __zecall
    zetMetricQueryPoolCreate(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQueryPool.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 1 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolDestroy
    __zedlllocal ze_result_t __zecall
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQueryPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hMetricQueryPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryCreate
    __zedlllocal ze_result_t __zecall
    zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQuery.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnCreate( hMetricQueryPool, index, phMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryDestroy
    __zedlllocal ze_result_t __zecall
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQuery.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryReset
    __zedlllocal ze_result_t __zecall
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        auto pfnReset = context.zetDdiTable.MetricQuery.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnReset( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    __zedlllocal ze_result_t __zecall
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        auto pfnAppendMetricQueryBegin = context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;

        if( nullptr == pfnAppendMetricQueryBegin )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryEnd
    __zedlllocal ze_result_t __zecall
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
        )
    {
        auto pfnAppendMetricQueryEnd = context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;

        if( nullptr == pfnAppendMetricQueryEnd )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    __zedlllocal ze_result_t __zecall
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        auto pfnAppendMetricMemoryBarrier = context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;

        if( nullptr == pfnAppendMetricMemoryBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricMemoryBarrier( hCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryGetData
    __zedlllocal ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRawDataSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetModuleGetDebugInfo
    __zedlllocal ze_result_t __zecall
    zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        auto pfnGetDebugInfo = context.zetDdiTable.Module.pfnGetDebugInfo;

        if( nullptr == pfnGetDebugInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 0 <= format )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetKernelGetProfileInfo
    __zedlllocal ze_result_t __zecall
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
        )
    {
        auto pfnGetProfileInfo = context.zetDdiTable.Kernel.pfnGetProfileInfo;

        if( nullptr == pfnGetProfileInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pInfo )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProfileInfo( hKernel, pInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerCreate
    __zedlllocal ze_result_t __zecall
    zetTracerCreate(
        zet_driver_handle_t hDriver,                    ///< [in] handle of the driver
        const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
        zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
        )
    {
        auto pfnCreate = context.zetDdiTable.Tracer.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == desc->pUserData )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZET_TRACER_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        }

        return pfnCreate( hDriver, desc, phTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerDestroy
    __zedlllocal ze_result_t __zecall
    zetTracerDestroy(
        zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
        )
    {
        auto pfnDestroy = context.zetDdiTable.Tracer.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetPrologues
    __zedlllocal ze_result_t __zecall
    zetTracerSetPrologues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto pfnSetPrologues = context.zetDdiTable.Tracer.pfnSetPrologues;

        if( nullptr == pfnSetPrologues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCoreCbs )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetPrologues( hTracer, pCoreCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEpilogues
    __zedlllocal ze_result_t __zecall
    zetTracerSetEpilogues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto pfnSetEpilogues = context.zetDdiTable.Tracer.pfnSetEpilogues;

        if( nullptr == pfnSetEpilogues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCoreCbs )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetEpilogues( hTracer, pCoreCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEnabled
    __zedlllocal ze_result_t __zecall
    zetTracerSetEnabled(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        auto pfnSetEnabled = context.zetDdiTable.Tracer.pfnSetEnabled;

        if( nullptr == pfnSetEnabled )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetEnabled( hTracer, enable );
    }

} // namespace layer

#if defined(__cplusplus)
extern "C" {
#endif

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
    auto& dditable = layer::context.zetDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetDebugInfo                             = pDdiTable->pfnGetDebugInfo;
    pDdiTable->pfnGetDebugInfo                           = layer::zetModuleGetDebugInfo;

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
    auto& dditable = layer::context.zetDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricGroup;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Metric;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricTracer;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricQueryPool;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricQuery;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Tracer;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto& dditable = layer::context.zetDdiTable.Debug;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAttach                                   = pDdiTable->pfnAttach;
    pDdiTable->pfnAttach                                 = layer::zetDebugAttach;

    dditable.pfnDetach                                   = pDdiTable->pfnDetach;
    pDdiTable->pfnDetach                                 = layer::zetDebugDetach;

    dditable.pfnGetNumThreads                            = pDdiTable->pfnGetNumThreads;
    pDdiTable->pfnGetNumThreads                          = layer::zetDebugGetNumThreads;

    dditable.pfnReadEvent                                = pDdiTable->pfnReadEvent;
    pDdiTable->pfnReadEvent                              = layer::zetDebugReadEvent;

    dditable.pfnInterrupt                                = pDdiTable->pfnInterrupt;
    pDdiTable->pfnInterrupt                              = layer::zetDebugInterrupt;

    dditable.pfnResume                                   = pDdiTable->pfnResume;
    pDdiTable->pfnResume                                 = layer::zetDebugResume;

    dditable.pfnReadMemory                               = pDdiTable->pfnReadMemory;
    pDdiTable->pfnReadMemory                             = layer::zetDebugReadMemory;

    dditable.pfnWriteMemory                              = pDdiTable->pfnWriteMemory;
    pDdiTable->pfnWriteMemory                            = layer::zetDebugWriteMemory;

    dditable.pfnReadState                                = pDdiTable->pfnReadState;
    pDdiTable->pfnReadState                              = layer::zetDebugReadState;

    dditable.pfnWriteState                               = pDdiTable->pfnWriteState;
    pDdiTable->pfnWriteState                             = layer::zetDebugWriteState;

    return result;
}

#if defined(__cplusplus)
};
#endif
