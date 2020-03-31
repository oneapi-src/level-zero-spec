/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_libapi.cpp
 * @version v1.0-r0.9.276
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
