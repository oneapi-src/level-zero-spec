/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_libapi.cpp
 *
 * @brief C++ static library for zet
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Attach to a device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == config`
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid device handle has been supplied
///         + an invalid configuration has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + attaching to this device is not supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + caller does not have sufficient permissions
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + a debugger is already attached
ze_result_t __zecall
zetDebugAttach(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    const zet_debug_config_t* config,               ///< [in] the debug configuration
    zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
    )
{
    auto pfnAttach = ze_lib::context.zetDdiTable.Debug.pfnAttach;
    if( nullptr == pfnAttach )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAttach( hDevice, config, hDebug );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Close a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle has been supplied
ze_result_t __zecall
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    )
{
    auto pfnDetach = ze_lib::context.zetDdiTable.Debug.pfnDetach;
    if( nullptr == pfnDetach )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDetach( hDebug );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query the number of device threads for a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNumThreads`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle has been supplied
ze_result_t __zecall
zetDebugGetNumThreads(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t* pNumThreads                           ///< [out] the maximal number of threads
    )
{
    auto pfnGetNumThreads = ze_lib::context.zetDdiTable.Debug.pfnGetNumThreads;
    if( nullptr == pfnGetNumThreads )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetNumThreads( hDebug, pNumThreads );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the topmost debug event.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or buffer pointer has been supplied
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///         + the output buffer is too small to hold the event
///     - ::ZE_RESULT_NOT_READY
///         + the timeout expired
ze_result_t __zecall
zetDebugReadEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
    size_t size,                                    ///< [in] the size of the buffer in bytes
    void* buffer                                    ///< [in,out] a buffer to hold the event data
    )
{
    auto pfnReadEvent = ze_lib::context.zetDdiTable.Debug.pfnReadEvent;
    if( nullptr == pfnReadEvent )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadEvent( hDebug, timeout, size, buffer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Interrupt device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is already stopped or unavailable
ze_result_t __zecall
zetDebugInterrupt(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
    )
{
    auto pfnInterrupt = ze_lib::context.zetDdiTable.Debug.pfnInterrupt;
    if( nullptr == pfnInterrupt )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnInterrupt( hDebug, threadid );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Resume device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is already running or unavailable
ze_result_t __zecall
zetDebugResume(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
    )
{
    auto pfnResume = ze_lib::context.zetDdiTable.Debug.pfnResume;
    if( nullptr == pfnResume )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnResume( hDebug, threadid );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read memory.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid address has been supplied
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the memory cannot be accessed from the supplied thread
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
    auto pfnReadMemory = ze_lib::context.zetDdiTable.Debug.pfnReadMemory;
    if( nullptr == pfnReadMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadMemory( hDebug, threadid, memSpace, address, size, buffer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Write memory.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid address has been supplied
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the memory cannot be accessed from the supplied thread
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
    auto pfnWriteMemory = ze_lib::context.zetDdiTable.Debug.pfnWriteMemory;
    if( nullptr == pfnWriteMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnWriteMemory( hDebug, threadid, memSpace, address, size, buffer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read register state.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid offset or size has been supplied
ze_result_t __zecall
zetDebugReadState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
    )
{
    auto pfnReadState = ze_lib::context.zetDdiTable.Debug.pfnReadState;
    if( nullptr == pfnReadState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadState( hDebug, threadid, offset, size, buffer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Write register state.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid offset or size has been supplied
ze_result_t __zecall
zetDebugWriteState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    )
{
    auto pfnWriteState = ze_lib::context.zetDdiTable.Debug.pfnWriteState;
    if( nullptr == pfnWriteState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnWriteState( hDebug, threadid, offset, size, buffer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves metric group for a device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnGet = ze_lib::context.zetDdiTable.MetricGroup.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGet( hDevice, pCount, phMetricGroups );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a metric group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetMetricGroupGetProperties(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.MetricGroup.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hMetricGroup, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Calculates metric values from raw data.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawData`
///         + `nullptr == pMetricValueCount`
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
    auto pfnCalculateMetricValues = ze_lib::context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;
    if( nullptr == pfnCalculateMetricValues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves metric from a metric group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnGet = ze_lib::context.zetDdiTable.Metric.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGet( hMetricGroup, pCount, phMetrics );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a metric.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetric`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetMetricGetProperties(
    zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    zet_metric_properties_t* pProperties            ///< [in,out] metric properties
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.Metric.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hMetric, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Activates metric groups.
/// 
/// @details
///     - MetricGroup must be active until MetricQueryGetDeta and
///       ::zetMetricTracerClose.
///     - Conflicting metric groups cannot be activated, in such case tha call
///       would fail.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
ze_result_t __zecall
zetDeviceActivateMetricGroups(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                    ///< activate. NULL to deactivate.
    )
{
    auto pfnActivateMetricGroups = ze_lib::context.zetDdiTable.Device.pfnActivateMetricGroups;
    if( nullptr == pfnActivateMetricGroups )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnActivateMetricGroups( hDevice, count, phMetricGroups );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens metric tracer for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phMetricTracer`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZET_METRIC_TRACER_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
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
    auto pfnOpen = ze_lib::context.zetDdiTable.MetricTracer.pfnOpen;
    if( nullptr == pfnOpen )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Append metric tracer marker into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricTracer`
ze_result_t __zecall
zetCommandListAppendMetricTracerMarker(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t value                                  ///< [in] tracer marker value
    )
{
    auto pfnAppendMetricTracerMarker = ze_lib::context.zetDdiTable.CommandList.pfnAppendMetricTracerMarker;
    if( nullptr == pfnAppendMetricTracerMarker )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes metric tracer.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same metric tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
ze_result_t __zecall
zetMetricTracerClose(
    zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
    )
{
    auto pfnClose = ze_lib::context.zetDdiTable.MetricTracer.pfnClose;
    if( nullptr == pfnClose )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnClose( hMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from metric tracer.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
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
    auto pfnReadData = ze_lib::context.zetDdiTable.MetricTracer.pfnReadData;
    if( nullptr == pfnReadData )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool of metric queries.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phMetricQueryPool`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
ze_result_t __zecall
zetMetricQueryPoolCreate(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
    const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
    zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    )
{
    auto pfnCreate = ze_lib::context.zetDdiTable.MetricQueryPool.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a query pool object.
/// 
/// @details
///     - The application is responsible for destroying all query handles
///       created from the pool before destroying the pool itself
///     - The application is responsible for making sure the device is not
///       currently referencing the any query within the pool before it is
///       deleted
///     - The application may **not** call this function from simultaneous
///       threads with the same query pool handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQueryPool`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t __zecall
zetMetricQueryPoolDestroy(
    zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
    )
{
    auto pfnDestroy = ze_lib::context.zetDdiTable.MetricQueryPool.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDestroy( hMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates metric query object.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQueryPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phMetricQuery`
ze_result_t __zecall
zetMetricQueryCreate(
    zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t index,                                 ///< [in] index of the query within the pool
    zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    )
{
    auto pfnCreate = ze_lib::context.zetDdiTable.MetricQuery.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCreate( hMetricQueryPool, index, phMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a metric query object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the query before it is deleted
///     - The application may **not** call this function from simultaneous
///       threads with the same query handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t __zecall
zetMetricQueryDestroy(
    zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
    )
{
    auto pfnDestroy = ze_lib::context.zetDdiTable.MetricQuery.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDestroy( hMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets a metric query object back to inital state.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the query before it is reset
///     - The application may **not** call this function from simultaneous
///       threads with the same query handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
ze_result_t __zecall
zetMetricQueryReset(
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
    )
{
    auto pfnReset = ze_lib::context.zetDdiTable.MetricQuery.pfnReset;
    if( nullptr == pfnReset )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReset( hMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query begin into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
ze_result_t __zecall
zetCommandListAppendMetricQueryBegin(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    auto pfnAppendMetricQueryBegin = ze_lib::context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;
    if( nullptr == pfnAppendMetricQueryBegin )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query end into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t __zecall
zetCommandListAppendMetricQueryEnd(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
    )
{
    auto pfnAppendMetricQueryEnd = ze_lib::context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;
    if( nullptr == pfnAppendMetricQueryEnd )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query commands to flush all caches.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t __zecall
zetCommandListAppendMetricMemoryBarrier(
    zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
    )
{
    auto pfnAppendMetricMemoryBarrier = ze_lib::context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;
    if( nullptr == pfnAppendMetricMemoryBarrier )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAppendMetricMemoryBarrier( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves raw data for a given metric query.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
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
    auto pfnGetData = ze_lib::context.zetDdiTable.MetricQuery.pfnGetData;
    if( nullptr == pfnGetData )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve debug info from module.
/// 
/// @details
///     - The caller can pass nullptr for pDebugInfo when querying only for
///       size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + format
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t __zecall
zetModuleGetDebugInfo(
    zet_module_handle_t hModule,                    ///< [in] handle of the module
    zet_module_debug_info_format_t format,          ///< [in] debug info format requested
    size_t* pSize,                                  ///< [in,out] size of debug info in bytes
    uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
    )
{
    auto pfnGetDebugInfo = ze_lib::context.zetDdiTable.Module.pfnGetDebugInfo;
    if( nullptr == pfnGetDebugInfo )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve profiling information generated for the kernel.
/// 
/// @details
///     - Module must be created using the following build option:
///         + "-zet-profile-flags <n>" - enable generation of profile
///           information
///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pInfo`
ze_result_t __zecall
zetKernelGetProfileInfo(
    zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
    zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
    )
{
    auto pfnGetProfileInfo = ze_lib::context.zetDdiTable.Kernel.pfnGetProfileInfo;
    if( nullptr == pfnGetProfileInfo )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProfileInfo( hKernel, pInfo );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the handle to access Sysman features for a device
/// 
/// @details
///     - The returned handle is unique.
///     - ::zet_device_handle_t returned by ::zeDeviceGetSubDevices() are not
///       support. Only use handles returned by ::zeDeviceGet(). All resources
///       on sub-devices can be enumerated through the primary device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + version
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phSysman`
ze_result_t __zecall
zetSysmanGet(
    zet_device_handle_t hDevice,                    ///< [in] Handle of the device
    zet_sysman_version_t version,                   ///< [in] Sysman version that application was built with
    zet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing Sysman features
    )
{
    auto pfnGet = ze_lib::context.zetDdiTable.Sysman.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGet( hDevice, version, phSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanDeviceGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sysman_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
    )
{
    auto pfnDeviceGetProperties = ze_lib::context.zetDdiTable.Sysman.pfnDeviceGetProperties;
    if( nullptr == pfnDeviceGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceGetProperties( hSysman, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about the state of the device - if a reset is
///        required, reasons for the reset and if the device has been repaired
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanDeviceGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sysman_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
    )
{
    auto pfnDeviceGetState = ze_lib::context.zetDdiTable.Sysman.pfnDeviceGetState;
    if( nullptr == pfnDeviceGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceGetState( hSysman, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @details
///     - Performs a PCI bus reset of the device. This will result in all
///       current device state being lost.
///     - All applications using the device should be stopped before calling
///       this function.
///     - If the force argument is specified, all applications using the device
///       will be forcibly killed.
///     - The function will block until the device has restarted or a timeout
///       occurred waiting for the reset to complete.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE - "Reset cannot be performed because applications are using this device."
///     - ::ZE_RESULT_ERROR_UNKNOWN - "There were problems unloading the device driver, performing a bus reset or reloading the device driver."
ze_result_t __zecall
zetSysmanDeviceReset(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                    ///< device will be forcibly killed.
    )
{
    auto pfnDeviceReset = ze_lib::context.zetDdiTable.Sysman.pfnDeviceReset;
    if( nullptr == pfnDeviceReset )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceReset( hSysman, force );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle to a scheduler component
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanSchedulerGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_sched_handle_t* phScheduler          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnSchedulerGet = ze_lib::context.zetDdiTable.Sysman.pfnSchedulerGet;
    if( nullptr == pfnSchedulerGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerGet( hSysman, pCount, phScheduler );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a scheduler component
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanSchedulerGetProperties(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Handle for the component.
    zet_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanScheduler.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hScheduler, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduling mode in effect on a scheduler component.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t __zecall
zetSysmanSchedulerGetCurrentMode(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    zet_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
    )
{
    auto pfnGetCurrentMode = ze_lib::context.zetDdiTable.SysmanScheduler.pfnGetCurrentMode;
    if( nullptr == pfnGetCurrentMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetCurrentMode( hScheduler, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMEOUT
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t __zecall
zetSysmanSchedulerGetTimeoutModeProperties(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
    )
{
    auto pfnGetTimeoutModeProperties = ze_lib::context.zetDdiTable.SysmanScheduler.pfnGetTimeoutModeProperties;
    if( nullptr == pfnGetTimeoutModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMESLICE
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t __zecall
zetSysmanSchedulerGetTimesliceModeProperties(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
    )
{
    auto pfnGetTimesliceModeProperties = ze_lib::context.zetDdiTable.SysmanScheduler.pfnGetTimesliceModeProperties;
    if( nullptr == pfnGetTimesliceModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_TIMEOUT or update scheduler
///        mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized for multiple applications or contexts
///       submitting work to the hardware. When higher priority work arrives,
///       the scheduler attempts to pause the current executing work within some
///       timeout interval, then submits the other work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetTimeoutMode(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    zet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetTimeoutMode = ze_lib::context.zetDdiTable.SysmanScheduler.pfnSetTimeoutMode;
    if( nullptr == pfnSetTimeoutMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_TIMESLICE or update
///        scheduler mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized to provide fair sharing of hardware execution
///       time between multiple contexts submitting work to the hardware
///       concurrently.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetTimesliceMode(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    zet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetTimesliceMode = ze_lib::context.zetDdiTable.SysmanScheduler.pfnSetTimesliceMode;
    if( nullptr == pfnSetTimesliceMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_EXCLUSIVE
/// 
/// @details
///     - This mode is optimized for single application/context use-cases. It
///       permits a context to run indefinitely on the hardware without being
///       preempted or terminated. All pending work for other contexts must wait
///       until the running context completes with no further submitted work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetExclusiveMode(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetExclusiveMode = ze_lib::context.zetDdiTable.SysmanScheduler.pfnSetExclusiveMode;
    if( nullptr == pfnSetExclusiveMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetExclusiveMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_COMPUTE_UNIT_DEBUG
/// 
/// @details
///     - This mode is optimized for application debug. It ensures that only one
///       command queue can execute work on the hardware at a given time. Work
///       is permitted to run as long as needed without enforcing any scheduler
///       fairness policies.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetComputeUnitDebugMode(
    zet_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetComputeUnitDebugMode = ze_lib::context.zetDdiTable.SysmanScheduler.pfnSetComputeUnitDebugMode;
    if( nullptr == pfnSetComputeUnitDebugMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handles to accelerator domains whose performance can be optimized
///        via a Performance Factor
/// 
/// @details
///     - A Performance Factor should be tuned for each workload.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanPerformanceFactorGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_perf_handle_t* phPerf                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnPerformanceFactorGet = ze_lib::context.zetDdiTable.Sysman.pfnPerformanceFactorGet;
    if( nullptr == pfnPerformanceFactorGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPerformanceFactorGet( hSysman, pCount, phPerf );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about a Performance Factor domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanPerformanceFactorGetProperties(
    zet_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
    zet_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                    ///< Factor domain.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanPerformanceFactor.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPerf, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current Performance Factor for a given domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFactor`
ze_result_t __zecall
zetSysmanPerformanceFactorGetConfig(
    zet_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
    double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                    ///< hardware (may not be the same as the requested Performance Factor).
    )
{
    auto pfnGetConfig = ze_lib::context.zetDdiTable.SysmanPerformanceFactor.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hPerf, pFactor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the performance factor for a domain
/// 
/// @details
///     - The Performance Factor is a number between 0 and 100.
///     - A Performance Factor is a hint to the hardware. Depending on the
///       hardware, the request may not be granted. Follow up this function with
///       a call to ::zetSysmanPerformanceFactorGetConfig() to determine the
///       actual factor being used by the hardware.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
ze_result_t __zecall
zetSysmanPerformanceFactorSetConfig(
    zet_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
    double factor                                   ///< [in] The new Performance Factor.
    )
{
    auto pfnSetConfig = ze_lib::context.zetDdiTable.SysmanPerformanceFactor.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hPerf, factor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about host processes using the device
/// 
/// @details
///     - The number of processes connected to the device is dynamic. This means
///       that between a call to determine the correct value of pCount and the
///       subsequent call, the number of processes may have increased. It is
///       recommended that a large array be passed in so as to avoid receiving
///       the error ::ZE_RESULT_ERROR_INVALID_SIZE.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The provided value of pCount is not big enough to store information about all the processes currently attached to the device.
ze_result_t __zecall
zetSysmanProcessesGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of processes currently using the device.
                                                    ///< if count is non-zero but less than the number of processes, the driver
                                                    ///< will set to the number of processes currently using the device and
                                                    ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                    ///< if count is larger than the number of processes, then the driver will
                                                    ///< update the value with the correct number of processes that are returned.
    zet_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                    ///< one for each process currently using the device
    )
{
    auto pfnProcessesGetState = ze_lib::context.zetDdiTable.Sysman.pfnProcessesGetState;
    if( nullptr == pfnProcessesGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnProcessesGetState( hSysman, pCount, pProcesses );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanPciGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
    )
{
    auto pfnPciGetProperties = ze_lib::context.zetDdiTable.Sysman.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetProperties( hSysman, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current PCI state - current speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanPciGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
    )
{
    auto pfnPciGetState = ze_lib::context.zetDdiTable.Sysman.pfnPciGetState;
    if( nullptr == pfnPciGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetState( hSysman, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about each configured bar
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnPciGetBars = ze_lib::context.zetDdiTable.Sysman.pfnPciGetBars;
    if( nullptr == pfnPciGetBars )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetBars( hSysman, pCount, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats - bandwidth, number of packets, number of replays
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zetSysmanPciGetStats(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
    )
{
    auto pfnPciGetStats = ze_lib::context.zetDdiTable.Sysman.pfnPciGetStats;
    if( nullptr == pfnPciGetStats )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetStats( hSysman, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnPowerGet = ze_lib::context.zetDdiTable.Sysman.pfnPowerGet;
    if( nullptr == pfnPowerGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPowerGet( hSysman, pCount, phPower );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a power domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanPowerGetProperties(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanPower.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPower, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEnergy`
ze_result_t __zecall
zetSysmanPowerGetEnergyCounter(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    )
{
    auto pfnGetEnergyCounter = ze_lib::context.zetDdiTable.SysmanPower.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyCounter( hPower, pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
ze_result_t __zecall
zetSysmanPowerGetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit.
    zet_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit.
    zet_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit.
    )
{
    auto pfnGetLimits = ze_lib::context.zetDdiTable.SysmanPower.pfnGetLimits;
    if( nullptr == pfnGetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t __zecall
zetSysmanPowerSetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    const zet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const zet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const zet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    )
{
    auto pfnSetLimits = ze_lib::context.zetDdiTable.SysmanPower.pfnSetLimits;
    if( nullptr == pfnSetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy threshold
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThreshold`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zet_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t __zecall
zetSysmanPowerGetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    )
{
    auto pfnGetEnergyThreshold = ze_lib::context.zetDdiTable.SysmanPower.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyThreshold( hPower, pThreshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - An event ::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED will be
///       generated when the delta energy consumed starting from this call
///       exceeds the specified threshold. Use the function
///       ::zetSysmanEventSetConfig() to start receiving the event.
///     - Only one running process can control the energy threshold at a given
///       time. If another process attempts to change the energy threshold, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zetSysmanPowerGetEnergyThreshold() to determine the process ID
///       currently controlling this setting.
///     - Calling this function will remove any pending energy thresholds and
///       start counting from the time of this call.
///     - Once the energy threshold has been reached and the event generated,
///       the threshold is automatically removed. It is up to the application to
///       request a new threshold.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zet_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process has set the energy threshold.
ze_result_t __zecall
zetSysmanPowerSetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    )
{
    auto pfnSetEnergyThreshold = ze_lib::context.zetDdiTable.SysmanPower.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEnergyThreshold( hPower, threshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of frequency domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnFrequencyGet = ze_lib::context.zetDdiTable.Sysman.pfnFrequencyGet;
    if( nullptr == pfnFrequencyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFrequencyGet( hSysman, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency properties - available frequencies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFrequencyGetProperties(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanFrequency.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFrequency, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get available non-overclocked hardware clock frequencies for the
///        frequency domain
/// 
/// @details
///     - The list of available frequencies is returned in order of slowest to
///       fastest.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnGetAvailableClocks = ze_lib::context.zetDdiTable.SysmanFrequency.pfnGetAvailableClocks;
    if( nullptr == pfnGetAvailableClocks )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
ze_result_t __zecall
zetSysmanFrequencyGetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnGetRange = ze_lib::context.zetDdiTable.SysmanFrequency.pfnGetRange;
    if( nullptr == pfnGetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency range between which the hardware can operate.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencySetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    const zet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnSetRange = ze_lib::context.zetDdiTable.SysmanFrequency.pfnSetRange;
    if( nullptr == pfnSetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency state - frequency request, actual frequency, TDP
///        limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanFrequencyGetState(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanFrequency.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFrequency, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency throttle time
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThrottleTime`
ze_result_t __zecall
zetSysmanFrequencyGetThrottleTime(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    )
{
    auto pfnGetThrottleTime = ze_lib::context.zetDdiTable.SysmanFrequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThrottleTime( hFrequency, pThrottleTime );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking capabilities.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcCapabilities`
ze_result_t __zecall
zetSysmanFrequencyOcGetCapabilities(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                    ///< ::zet_oc_capabilities_t.
    )
{
    auto pfnOcGetCapabilities = ze_lib::context.zetDdiTable.SysmanFrequency.pfnOcGetCapabilities;
    if( nullptr == pfnOcGetCapabilities )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking configuration.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcConfiguration`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
ze_result_t __zecall
zetSysmanFrequencyOcGetConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zet_oc_config_t.
    )
{
    auto pfnOcGetConfig = ze_lib::context.zetDdiTable.SysmanFrequency.pfnOcGetConfig;
    if( nullptr == pfnOcGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetConfig( hFrequency, pOcConfiguration );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the overclocking configuration.
/// 
/// @details
///     - If ::zet_oc_config_t.mode is set to ::ZET_OC_MODE_OFF, overclocking
///       will be turned off and the hardware returned to run with factory
///       voltages/frequencies. Call ::zetSysmanFrequencyOcSetIccMax() and
///       ::zetSysmanFrequencyOcSetTjMax() separately with 0.0 to return those
///       settings to factory defaults.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcConfiguration`
///         + `nullptr == pDeviceRestart`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zet_oc_capabilities_t.maxOcFrequency, ::zet_oc_capabilities_t.maxOcVoltage, ::zet_oc_capabilities_t.minOcVoltageOffset, ::zet_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zet_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencyOcSetConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
    ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                    ///< in order to enable the new overclock settings.
    )
{
    auto pfnOcSetConfig = ze_lib::context.zetDdiTable.SysmanFrequency.pfnOcSetConfig;
    if( nullptr == pfnOcSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum current limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcIccMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + Capability ::zet_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
ze_result_t __zecall
zetSysmanFrequencyOcGetIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                    ///< successful return.
    )
{
    auto pfnOcGetIccMax = ze_lib::context.zetDdiTable.SysmanFrequency.pfnOcGetIccMax;
    if( nullptr == pfnOcGetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetIccMax( hFrequency, pOcIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum current limit setting.
/// 
/// @details
///     - Setting ocIccMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + Capability ::zet_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified current limit is too low or too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencyOcSetIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    )
{
    auto pfnOcSetIccMax = ze_lib::context.zetDdiTable.SysmanFrequency.pfnOcSetIccMax;
    if( nullptr == pfnOcSetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetIccMax( hFrequency, ocIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum temperature limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcTjMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
ze_result_t __zecall
zetSysmanFrequencyOcGetTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                    ///< on successful return.
    )
{
    auto pfnOcGetTjMax = ze_lib::context.zetDdiTable.SysmanFrequency.pfnOcGetTjMax;
    if( nullptr == pfnOcGetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetTjMax( hFrequency, pOcTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum temperature limit setting.
/// 
/// @details
///     - Setting ocTjMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + Capability ::zet_oc_capabilities_t.isTjMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified temperature limit is too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencyOcSetTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    )
{
    auto pfnOcSetTjMax = ze_lib::context.zetDdiTable.SysmanFrequency.pfnOcSetTjMax;
    if( nullptr == pfnOcSetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetTjMax( hFrequency, ocTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of engine groups
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnEngineGet = ze_lib::context.zetDdiTable.Sysman.pfnEngineGet;
    if( nullptr == pfnEngineGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEngineGet( hSysman, pCount, phEngine );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine group properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanEngineGetProperties(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanEngine.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hEngine, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity stats for an engine group
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
ze_result_t __zecall
zetSysmanEngineGetActivity(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                    ///< counters.
    )
{
    auto pfnGetActivity = ze_lib::context.zetDdiTable.SysmanEngine.pfnGetActivity;
    if( nullptr == pfnGetActivity )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetActivity( hEngine, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of standby controls
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnStandbyGet = ze_lib::context.zetDdiTable.Sysman.pfnStandbyGet;
    if( nullptr == pfnStandbyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnStandbyGet( hSysman, pCount, phStandby );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get standby hardware component properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanStandbyGetProperties(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanStandby.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hStandby, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
ze_result_t __zecall
zetSysmanStandbyGetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
    )
{
    auto pfnGetMode = ze_lib::context.zetDdiTable.SysmanStandby.pfnGetMode;
    if( nullptr == pfnGetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetMode( hStandby, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + mode
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanStandbySetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
    )
{
    auto pfnSetMode = ze_lib::context.zetDdiTable.SysmanStandby.pfnSetMode;
    if( nullptr == pfnSetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetMode( hStandby, mode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of firmwares
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnFirmwareGet = ze_lib::context.zetDdiTable.Sysman.pfnFirmwareGet;
    if( nullptr == pfnFirmwareGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFirmwareGet( hSysman, pCount, phFirmware );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFirmwareGetProperties(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    zet_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                    ///< firmware
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanFirmware.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFirmware, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware checksum
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pChecksum`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t __zecall
zetSysmanFirmwareGetChecksum(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
    )
{
    auto pfnGetChecksum = ze_lib::context.zetDdiTable.SysmanFirmware.pfnGetChecksum;
    if( nullptr == pfnGetChecksum )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetChecksum( hFirmware, pChecksum );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Flash a new firmware image
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImage`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t __zecall
zetSysmanFirmwareFlash(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    )
{
    auto pfnFlash = ze_lib::context.zetDdiTable.SysmanFirmware.pfnFlash;
    if( nullptr == pfnFlash )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFlash( hFirmware, pImage, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of memory modules
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnMemoryGet = ze_lib::context.zetDdiTable.Sysman.pfnMemoryGet;
    if( nullptr == pfnMemoryGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnMemoryGet( hSysman, pCount, phMemory );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanMemoryGetProperties(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanMemory.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hMemory, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory state - health, allocated
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanMemoryGetState(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanMemory.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hMemory, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory bandwidth
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBandwidth`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zetSysmanMemoryGetBandwidth(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the current health, free memory, total memory
                                                    ///< size.
    )
{
    auto pfnGetBandwidth = ze_lib::context.zetDdiTable.SysmanMemory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetBandwidth( hMemory, pBandwidth );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of Fabric ports in a device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnFabricPortGet = ze_lib::context.zetDdiTable.Sysman.pfnFabricPortGet;
    if( nullptr == pfnFabricPortGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFabricPortGet( hSysman, pCount, phPort );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFabricPortGetProperties(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanFabricPort.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPort, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port link type
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLinkType`
ze_result_t __zecall
zetSysmanFabricPortGetLinkType(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
    zet_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                    ///< port.
    )
{
    auto pfnGetLinkType = ze_lib::context.zetDdiTable.SysmanFabricPort.pfnGetLinkType;
    if( nullptr == pfnGetLinkType )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLinkType( hPort, verbose, pLinkType );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanFabricPortGetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
    )
{
    auto pfnGetConfig = ze_lib::context.zetDdiTable.SysmanFabricPort.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFabricPortSetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    const zet_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    )
{
    auto pfnSetConfig = ze_lib::context.zetDdiTable.SysmanFabricPort.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port state - status (green/yellow/red/black), reasons for
///        link degradation or instability, current rx/tx speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanFabricPortGetState(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanFabricPort.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPort, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThroughput`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zetSysmanFabricPortGetThroughput(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
    )
{
    auto pfnGetThroughput = ze_lib::context.zetDdiTable.SysmanFabricPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThroughput( hPort, pThroughput );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of temperature sensors
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnTemperatureGet = ze_lib::context.zetDdiTable.Sysman.pfnTemperatureGet;
    if( nullptr == pfnTemperatureGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnTemperatureGet( hSysman, pCount, phTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanTemperatureGetProperties(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zet_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanTemperature.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hTemperature, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature configuration for this sensor - which events are
///        triggered and the trigger conditions
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally this is only supported for temperature sensor ::ZET_TEMP_SENSORS_GLOBAL
///         + One or both of the thresholds is not supported - check ::zet_temp_properties_t.isThreshold1Supported and ::zet_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t __zecall
zetSysmanTemperatureGetConfig(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zet_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
    )
{
    auto pfnGetConfig = ze_lib::context.zetDdiTable.SysmanTemperature.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature configuration for this sensor - indicates which events
///        are triggered and the trigger conditions
/// 
/// @details
///     - Events ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL will be triggered when
///       temperature reaches the critical range. Use the function
///       ::zetSysmanEventSetConfig() to start receiving this event.
///     - Events ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 and
///       ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 will be generated when
///       temperature cross the thresholds set using this function. Use the
///       function ::zetSysmanEventSetConfig() to start receiving these events.
///     - Only one running process can set the temperature configuration at a
///       time. If another process attempts to change the configuration, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zetSysmanTemperatureGetConfig() will return the process ID currently
///       controlling these settings.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally they are only supported for temperature sensor ::ZET_TEMP_SENSORS_GLOBAL
///         + Enabling the critical temperature event is not supported - check ::zet_temp_properties_t.isCriticalTempSupported
///         + One or both of the thresholds is not supported - check ::zet_temp_properties_t.isThreshold1Supported and ::zet_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or both the thresholds is above TjMax (see ::zetSysmanFrequencyOcGetTjMax()). Temperature thresholds must be below this value.
ze_result_t __zecall
zetSysmanTemperatureSetConfig(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    const zet_temp_config_t* pConfig                ///< [in] New configuration.
    )
{
    auto pfnSetConfig = ze_lib::context.zetDdiTable.SysmanTemperature.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the temperature from a specified sensor
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTemperature`
ze_result_t __zecall
zetSysmanTemperatureGetState(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                    ///< in degrees Celsius.
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanTemperature.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hTemperature, pTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power supplies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnPsuGet = ze_lib::context.zetDdiTable.Sysman.pfnPsuGet;
    if( nullptr == pfnPsuGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPsuGet( hSysman, pCount, phPsu );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power supply properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanPsuGetProperties(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanPsu.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPsu, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current power supply state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanPsuGetState(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanPsu.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPsu, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of fans
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnFanGet = ze_lib::context.zetDdiTable.Sysman.pfnFanGet;
    if( nullptr == pfnFanGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFanGet( hSysman, pCount, phFan );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFanGetProperties(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanFan.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFan, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current fan configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanFanGetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
    )
{
    auto pfnGetConfig = ze_lib::context.zetDdiTable.SysmanFan.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFanSetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
    )
{
    auto pfnSetConfig = ze_lib::context.zetDdiTable.SysmanFan.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a fan - current mode and speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + units
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSpeed`
ze_result_t __zecall
zetSysmanFanGetState(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                    ///< requested.
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanFan.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFan, units, pSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of LEDs
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnLedGet = ze_lib::context.zetDdiTable.Sysman.pfnLedGet;
    if( nullptr == pfnLedGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnLedGet( hSysman, pCount, phLed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanLedGetProperties(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanLed.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hLed, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanLedGetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanLed.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanLedSetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    const zet_led_state_t* pState                   ///< [in] New state of the LED.
    )
{
    auto pfnSetState = ze_lib::context.zetDdiTable.SysmanLed.pfnSetState;
    if( nullptr == pfnSetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of all RAS error sets on a device
/// 
/// @details
///     - A RAS error set is a collection of RAS error counters of a given type
///       (correctable/uncorrectable) from hardware blocks contained within a
///       sub-device or within the device.
///     - A device without sub-devices will typically return two handles, one
///       for correctable errors sets and one for uncorrectable error sets.
///     - A device with sub-devices will return RAS error sets for each
///       sub-device and possibly RAS error sets for hardware blocks outside the
///       sub-devices.
///     - If the function completes successfully but pCount is set to 0, RAS
///       features are not available/enabled on this device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnRasGet = ze_lib::context.zetDdiTable.Sysman.pfnRasGet;
    if( nullptr == pfnRasGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnRasGet( hSysman, pCount, phRas );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS properties of a given RAS error set - this enables discovery
///        of the type of RAS error set (correctable/uncorrectable) and if
///        located on a sub-device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanRasGetProperties(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zet_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanRas.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hRas, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the configured
///       threshold, the event ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
///       will be triggered.
///     - When a particular RAS uncorrectable error counter exceeds the
///       configured threshold, the event
///       ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be triggered.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanRasGetConfig(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zet_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                    ///< thresholds used to trigger events
    )
{
    auto pfnGetConfig = ze_lib::context.zetDdiTable.SysmanRas.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the specified
///       threshold, the event ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
///       will be generated.
///     - When a particular RAS uncorrectable error counter exceeds the
///       specified threshold, the event
///       ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be generated.
///     - Call ::zetSysmanRasGetState() and set the clear flag to true to
///       restart event generation once counters have exceeded thresholds.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to set thresholds.
ze_result_t __zecall
zetSysmanRasSetConfig(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    const zet_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    )
{
    auto pfnSetConfig = ze_lib::context.zetDdiTable.SysmanRas.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current value of RAS error counters for a particular error set
/// 
/// @details
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTotalErrors`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t __zecall
zetSysmanRasGetState(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in,out] The number total number of errors that have occurred
    zet_ras_details_t* pDetails                     ///< [in,out][optional] Breakdown of where errors have occurred
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanRas.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hRas, clear, pTotalErrors, pDetails );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the event handle for the specified device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvent`
ze_result_t __zecall
zetSysmanEventGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    zet_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
    )
{
    auto pfnEventGet = ze_lib::context.zetDdiTable.Sysman.pfnEventGet;
    if( nullptr == pfnEventGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEventGet( hSysman, phEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which events are currently registered on the specified device
///        event handler
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanEventGetConfig(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    zet_event_config_t* pConfig                     ///< [in,out] Will contain the current event configuration (list of
                                                    ///< registered events).
    )
{
    auto pfnGetConfig = ze_lib::context.zetDdiTable.SysmanEvent.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hEvent, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set a new event configuration (list of registered events) on the
///        specified device event handler
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanEventSetConfig(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    const zet_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
    )
{
    auto pfnSetConfig = ze_lib::context.zetDdiTable.SysmanEvent.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hEvent, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get events that have been triggered for a specific device
/// 
/// @details
///     - If events have occurred on the specified device event handle, they are
///       returned and the corresponding event status is cleared if the argument
///       clear = true.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEvents`
ze_result_t __zecall
zetSysmanEventGetState(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device.
    ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                    ///< triggered by this device.
    )
{
    auto pfnGetState = ze_lib::context.zetDdiTable.SysmanEvent.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hEvent, clear, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for the specified list of event handles to receive any registered
///        events
/// 
/// @details
///     - If previous events arrived and were not cleared using
///       ::zetSysmanEventGetState(), this call will return immediately.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied event handles are for devices that belong to a different driver handle.
ze_result_t __zecall
zetSysmanEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                    ///< ::ZET_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                    ///< ::ZET_EVENT_WAIT_INFINITE to block until events arrive.
    uint32_t count,                                 ///< [in] Number of handles in phEvents
    zet_sysman_event_handle_t* phEvents,            ///< [in][range(0, count)] Handle of events that should be listened to
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                    ///< triggered by any of the supplied event handles. If timeout is not
                                                    ///< ::ZET_EVENT_WAIT_INFINITE and this value is
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
    )
{
    auto pfnListen = ze_lib::context.zetDdiTable.SysmanEvent.pfnListen;
    if( nullptr == pfnListen )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnListen( hDriver, timeout, count, phEvents, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of diagnostics test suites
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnDiagnosticsGet = ze_lib::context.zetDdiTable.Sysman.pfnDiagnosticsGet;
    if( nullptr == pfnDiagnosticsGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a diagnostics test suite
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanDiagnosticsGetProperties(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    zet_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                    ///< suite
    )
{
    auto pfnGetProperties = ze_lib::context.zetDdiTable.SysmanDiagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hDiagnostics, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get individual tests that can be run separately. Not all test suites
///        permit running individual tests - check
///        ::zet_diag_properties_t.haveTests
/// 
/// @details
///     - The list of available tests is returned in order of increasing test
///       index ::zet_diag_test_t.index.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnGetTests = ze_lib::context.zetDdiTable.SysmanDiagnostics.pfnGetTests;
    if( nullptr == pfnGetTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTests( hDiagnostics, pCount, pTests );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - WARNING: Performancing diagnostics may destroy current device state
///       information. Gracefully close any running workloads before initiating.
///     - To run all tests in a test suite, set start =
///       ::ZET_DIAG_FIRST_TEST_INDEX and end = ::ZET_DIAG_LAST_TEST_INDEX.
///     - If the test suite permits running individual tests,
///       ::zet_diag_properties_t.haveTests will be true. In this case, the
///       function ::zetSysmanDiagnosticsGetTests() can be called to get the
///       list of tests and corresponding indices that can be supplied to the
///       arguments start and end in this function.
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pResult`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform diagnostics.
ze_result_t __zecall
zetSysmanDiagnosticsRunTests(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zet_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
    )
{
    auto pfnRunTests = ze_lib::context.zetDdiTable.SysmanDiagnostics.pfnRunTests;
    if( nullptr == pfnRunTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnRunTests( hDiagnostics, start, end, pResult );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a tracer for the specified driver.
/// 
/// @details
///     - The tracer can only be used on the driver on which it was created.
///     - The tracer is created in the disabled state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pUserData`
///         + `nullptr == phTracer`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZET_TRACER_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zetTracerCreate(
    zet_driver_handle_t hDriver,                    ///< [in] handle of the driver
    const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
    zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
    )
{
    auto pfnCreate = ze_lib::context.zetDdiTable.Tracer.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCreate( hDriver, desc, phTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a tracer.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
///     - The implementation of this function will stall and wait on any
///       outstanding threads executing callbacks before freeing any Host
///       allocations associated with this tracer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t __zecall
zetTracerDestroy(
    zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
    )
{
    auto pfnDestroy = ze_lib::context.zetDdiTable.Tracer.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDestroy( hTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **before** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t __zecall
zetTracerSetPrologues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
    )
{
    auto pfnSetPrologues = ze_lib::context.zetDdiTable.Tracer.pfnSetPrologues;
    if( nullptr == pfnSetPrologues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetPrologues( hTracer, pCoreCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **after** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t __zecall
zetTracerSetEpilogues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
    )
{
    auto pfnSetEpilogues = ze_lib::context.zetDdiTable.Tracer.pfnSetEpilogues;
    if( nullptr == pfnSetEpilogues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEpilogues( hTracer, pCoreCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enables (or disables) the tracer
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
ze_result_t __zecall
zetTracerSetEnabled(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
    )
{
    auto pfnSetEnabled = ze_lib::context.zetDdiTable.Tracer.pfnSetEnabled;
    if( nullptr == pfnSetEnabled )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEnabled( hTracer, enable );
}

} // extern "C"
