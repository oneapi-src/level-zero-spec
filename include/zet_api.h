/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_api.h
 * @version v1.0-r0.9.277
 *
 */
#ifndef _ZET_API_H
#define _ZET_API_H
#if defined(__cplusplus)
#pragma once
#endif

// 'core' API headers
#include "ze_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

#pragma region common
///////////////////////////////////////////////////////////////////////////////
/// @brief Handle to a driver instance
typedef ze_driver_handle_t zet_driver_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of device object
typedef ze_device_handle_t zet_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of command list object
typedef ze_command_list_handle_t zet_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of module object
typedef ze_module_handle_t zet_module_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of function object
typedef ze_kernel_handle_t zet_kernel_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric group's object
typedef struct _zet_metric_group_handle_t *zet_metric_group_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric's object
typedef struct _zet_metric_handle_t *zet_metric_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric tracer's object
typedef struct _zet_metric_tracer_handle_t *zet_metric_tracer_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query pool's object
typedef struct _zet_metric_query_pool_handle_t *zet_metric_query_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query's object
typedef struct _zet_metric_query_handle_t *zet_metric_query_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of tracer object
typedef struct _zet_tracer_handle_t *zet_tracer_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_config_v1_t
typedef struct _zet_debug_config_v1_t zet_debug_config_v1_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_config_t
typedef struct _zet_debug_config_t zet_debug_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_event_info_detached_t
typedef struct _zet_debug_event_info_detached_t zet_debug_event_info_detached_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_event_info_module_t
typedef struct _zet_debug_event_info_module_t zet_debug_event_info_module_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_event_t
typedef struct _zet_debug_event_t zet_debug_event_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_state_section_t
typedef struct _zet_debug_state_section_t zet_debug_state_section_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_state_t
typedef struct _zet_debug_state_t zet_debug_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_group_properties_t
typedef struct _zet_metric_group_properties_t zet_metric_group_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_typed_value_t
typedef struct _zet_typed_value_t zet_typed_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_properties_t
typedef struct _zet_metric_properties_t zet_metric_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_tracer_desc_t
typedef struct _zet_metric_tracer_desc_t zet_metric_tracer_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_query_pool_desc_t
typedef struct _zet_metric_query_pool_desc_t zet_metric_query_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_profile_info_t
typedef struct _zet_profile_info_t zet_profile_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_profile_free_register_token_t
typedef struct _zet_profile_free_register_token_t zet_profile_free_register_token_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_profile_register_sequence_t
typedef struct _zet_profile_register_sequence_t zet_profile_register_sequence_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_tracer_desc_t
typedef struct _zet_tracer_desc_t zet_tracer_desc_t;


#pragma endregion
#pragma region device
#pragma endregion
#pragma region cmdlist
#pragma endregion
#pragma region debug
///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_API_VERSION
/// @brief The API version.
#define ZET_DEBUG_API_VERSION  1
#endif // ZET_DEBUG_API_VERSION

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug session handle
typedef struct _zet_debug_session_handle_t *zet_debug_session_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug configuration: version 1
typedef struct _zet_debug_config_v1_t
{
    int pid;                                        ///< The host process identifier

} zet_debug_config_v1_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug configuration: version-dependent fields
typedef union _zet_debug_config_variants_t
{
    zet_debug_config_v1_t v1;                       ///< Version 1

} zet_debug_config_variants_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug configuration
typedef struct _zet_debug_config_t
{
    uint16_t version;                               ///< The requested program debug API version
    zet_debug_config_variants_t variant;            ///< Version-specific fields

} zet_debug_config_t;

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
__ze_api_export ze_result_t __zecall
zetDebugAttach(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    const zet_debug_config_t* config,               ///< [in] the debug configuration
    zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
    );

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
__ze_api_export ze_result_t __zecall
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    );

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
__ze_api_export ze_result_t __zecall
zetDebugGetNumThreads(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t* pNumThreads                           ///< [out] the maximal number of threads
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_TIMEOUT_INFINITE
/// @brief An infinite timeout.
#define ZET_DEBUG_TIMEOUT_INFINITE  0xffffffffffffffffull
#endif // ZET_DEBUG_TIMEOUT_INFINITE

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug event flags.
typedef enum _zet_debug_event_flags_t
{
    ZET_DEBUG_EVENT_FLAG_NONE = 0,                  ///< No event flags
    ZET_DEBUG_EVENT_FLAG_STOPPED = ZE_BIT(0),       ///< The reporting thread stopped

} zet_debug_event_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug event types.
typedef enum _zet_debug_event_type_t
{
    ZET_DEBUG_EVENT_INVALID = 0,                    ///< The event is invalid
    ZET_DEBUG_EVENT_DETACHED,                       ///< The tool was detached
    ZET_DEBUG_EVENT_PROCESS_ENTRY,                  ///< The debuggee process created command queues on the device
    ZET_DEBUG_EVENT_PROCESS_EXIT,                   ///< The debuggee process destroyed all command queues on the device
    ZET_DEBUG_EVENT_MODULE_LOAD,                    ///< An in-memory module was loaded onto the device
    ZET_DEBUG_EVENT_MODULE_UNLOAD,                  ///< An in-memory module is about to get unloaded from the device
    ZET_DEBUG_EVENT_EXCEPTION,                      ///< The thread stopped due to a device exception

} zet_debug_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug detach reason.
typedef enum _zet_debug_detach_reason_t
{
    ZET_DEBUG_DETACH_INVALID = 0,                   ///< The detach reason is not valid
    ZET_DEBUG_DETACH_HOST_EXIT,                     ///< The host process exited

} zet_debug_detach_reason_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_NONE
/// @brief No thread on the device.
#define ZET_DEBUG_THREAD_NONE  0xffffffffffffffffull
#endif // ZET_DEBUG_THREAD_NONE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_ALL
/// @brief All threads on the device.
#define ZET_DEBUG_THREAD_ALL  0xfffffffffffffffeull
#endif // ZET_DEBUG_THREAD_ALL

///////////////////////////////////////////////////////////////////////////////
/// @brief Event information for ::ZET_DEBUG_EVENT_DETACHED
typedef struct _zet_debug_event_info_detached_t
{
    uint8_t reason;                                 ///< The detach reason

} zet_debug_event_info_detached_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event information for ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD
typedef struct _zet_debug_event_info_module_t
{
    uint64_t moduleBegin;                           ///< The begin address of the in-memory module
    uint64_t moduleEnd;                             ///< The end address of the in-memory module
    uint64_t load;                                  ///< The load address of the module on the device

} zet_debug_event_info_module_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event type specific information
typedef union _zet_debug_event_info_t
{
    zet_debug_event_info_detached_t detached;       ///< type == ::ZET_DEBUG_EVENT_DETACHED
    zet_debug_event_info_module_t module;           ///< type == ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD

} zet_debug_event_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief A debug event on the device.
typedef struct _zet_debug_event_t
{
    uint8_t type;                                   ///< The event type
    uint64_t thread;                                ///< The thread reporting the event
    uint64_t flags;                                 ///< A bit-vector of ::zet_debug_event_flags_t
    zet_debug_event_info_t info;                    ///< Event type specific information

} zet_debug_event_t;

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
__ze_api_export ze_result_t __zecall
zetDebugReadEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
    size_t size,                                    ///< [in] the size of the buffer in bytes
    void* buffer                                    ///< [in,out] a buffer to hold the event data
    );

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
__ze_api_export ze_result_t __zecall
zetDebugInterrupt(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
    );

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
__ze_api_export ze_result_t __zecall
zetDebugResume(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory spaces for Intel Graphics devices.
typedef enum _zet_debug_memory_space_intel_graphics_t
{
    ZET_DEBUG_MEMORY_SPACE_GEN_DEFAULT = 0,         ///< default memory space (attribute may be omitted)
    ZET_DEBUG_MEMORY_SPACE_GEN_SLM,                 ///< shared local memory space

} zet_debug_memory_space_intel_graphics_t;

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
__ze_api_export ze_result_t __zecall
zetDebugReadMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
    int memSpace,                                   ///< [in] the (device-specific) memory space
    uint64_t address,                               ///< [in] the virtual address of the memory to read from
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
    );

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
__ze_api_export ze_result_t __zecall
zetDebugWriteMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
    int memSpace,                                   ///< [in] the (device-specific) memory space
    uint64_t address,                               ///< [in] the virtual address of the memory to write to
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Register file types for Intel Graphics devices.
typedef enum _zet_debug_state_intel_graphics_t
{
    ZET_DEBUG_STATE_GEN_INVALID = 0,                ///< An invalid register file
    ZET_DEBUG_STATE_GEN_GRF,                        ///< The general register file
    ZET_DEBUG_STATE_GEN_ACC,                        ///< The accumulator register file
    ZET_DEBUG_STATE_GEN_ADDR,                       ///< The address register file
    ZET_DEBUG_STATE_GEN_FLAG,                       ///< The flags register file

} zet_debug_state_intel_graphics_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief A register file descriptor.
typedef struct _zet_debug_state_section_t
{
    uint16_t type;                                  ///< The register file type type
    uint16_t version;                               ///< The register file version
    uint32_t size;                                  ///< The size of the register file in bytes
    uint64_t offset;                                ///< The offset into the register state area

} zet_debug_state_section_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief A register state descriptor.
typedef struct _zet_debug_state_t
{
    uint32_t size;                                  ///< The size of the register state object in bytes
    uint8_t headerSize;                             ///< The size of the register state descriptor in bytes
    uint8_t secSize;                                ///< The size of the register file descriptors in bytes
    uint16_t numSec;                                ///< The number of register file descriptors

} zet_debug_state_t;

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
__ze_api_export ze_result_t __zecall
zetDebugReadState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
    );

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
__ze_api_export ze_result_t __zecall
zetDebugWriteState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    );

#pragma endregion
#pragma region metric
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
__ze_api_export ze_result_t __zecall
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
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_GROUP_NAME
/// @brief Maximum metric group name string size
#define ZET_MAX_METRIC_GROUP_NAME  256
#endif // ZET_MAX_METRIC_GROUP_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_GROUP_DESCRIPTION
/// @brief Maximum metric group description string size
#define ZET_MAX_METRIC_GROUP_DESCRIPTION  256
#endif // ZET_MAX_METRIC_GROUP_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric group sampling type
typedef enum _zet_metric_group_sampling_type_t
{
    ZET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED = ZE_BIT(0), ///< Event based sampling
    ZET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED = ZE_BIT(1),  ///< Time based sampling

} zet_metric_group_sampling_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_group_properties_t
typedef enum _zet_metric_group_properties_version_t
{
    ZET_METRIC_GROUP_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0
    ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< latest known version

} zet_metric_group_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric group properties queried using ::zetMetricGroupGetProperties
typedef struct _zet_metric_group_properties_t
{
    zet_metric_group_properties_version_t version;  ///< [in] ::ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
    char name[ZET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
    char description[ZET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
    zet_metric_group_sampling_type_t samplingType;  ///< [out] metric group sampling type
    uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                    ///< groups from different domains.
    uint32_t maxCommandQueueGroupOrdinal;           ///< [out] tracers and queries of this metric group cannot be submitted to
                                                    ///< a command queue group with a larger ordinal value.
                                                    ///< See ::ze_command_queue_desc_t for more information on how to specify
                                                    ///< the command queue's group ordinal.
    uint32_t metricCount;                           ///< [out] metric count belonging to this group

} zet_metric_group_properties_t;

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
__ze_api_export ze_result_t __zecall
zetMetricGroupGetProperties(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric types
typedef enum _zet_metric_type_t
{
    ZET_METRIC_TYPE_DURATION,                       ///< Metric type: duration
    ZET_METRIC_TYPE_EVENT,                          ///< Metric type: event
    ZET_METRIC_TYPE_EVENT_WITH_RANGE,               ///< Metric type: event with range
    ZET_METRIC_TYPE_THROUGHPUT,                     ///< Metric type: throughput
    ZET_METRIC_TYPE_TIMESTAMP,                      ///< Metric type: timestamp
    ZET_METRIC_TYPE_FLAG,                           ///< Metric type: flag
    ZET_METRIC_TYPE_RATIO,                          ///< Metric type: ratio
    ZET_METRIC_TYPE_RAW,                            ///< Metric type: raw

} zet_metric_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported value types
typedef enum _zet_value_type_t
{
    ZET_VALUE_TYPE_UINT32,                          ///< 32-bit unsigned-integer
    ZET_VALUE_TYPE_UINT64,                          ///< 64-bit unsigned-integer
    ZET_VALUE_TYPE_FLOAT32,                         ///< 32-bit floating-point
    ZET_VALUE_TYPE_FLOAT64,                         ///< 64-bit floating-point
    ZET_VALUE_TYPE_BOOL8,                           ///< 8-bit boolean

} zet_value_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Union of values
typedef union _zet_value_t
{
    uint32_t ui32;                                  ///< [out] 32-bit unsigned-integer
    uint64_t ui64;                                  ///< [out] 32-bit unsigned-integer
    float fp32;                                     ///< [out] 32-bit floating-point
    double fp64;                                    ///< [out] 64-bit floating-point
    ze_bool_t b8;                                   ///< [out] 8-bit boolean

} zet_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Typed value
typedef struct _zet_typed_value_t
{
    zet_value_type_t type;                          ///< [out] type of value
    zet_value_t value;                              ///< [out] value

} zet_typed_value_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetMetricGet(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of metrics available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                    ///< if count is larger than the number of metrics available, then the
                                                    ///< driver will update the value with the correct number of metrics available.
    zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_NAME
/// @brief Maximum metric name string size
#define ZET_MAX_METRIC_NAME  256
#endif // ZET_MAX_METRIC_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_DESCRIPTION
/// @brief Maximum metric description string size
#define ZET_MAX_METRIC_DESCRIPTION  256
#endif // ZET_MAX_METRIC_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_COMPONENT
/// @brief Maximum metric component string size
#define ZET_MAX_METRIC_COMPONENT  256
#endif // ZET_MAX_METRIC_COMPONENT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_RESULT_UNITS
/// @brief Maximum metric result units string size
#define ZET_MAX_METRIC_RESULT_UNITS  256
#endif // ZET_MAX_METRIC_RESULT_UNITS

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_properties_t
typedef enum _zet_metric_properties_version_t
{
    ZET_METRIC_PROPERTIES_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),///< version 1.0
    ZET_METRIC_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),///< latest known version

} zet_metric_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric properties queried using ::zetMetricGetProperties
typedef struct _zet_metric_properties_t
{
    zet_metric_properties_version_t version;        ///< [in] ::ZET_METRIC_PROPERTIES_VERSION_CURRENT
    char name[ZET_MAX_METRIC_NAME];                 ///< [out] metric name
    char description[ZET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
    char component[ZET_MAX_METRIC_COMPONENT];       ///< [out] metric component
    uint32_t tierNumber;                            ///< [out] number of tier
    zet_metric_type_t metricType;                   ///< [out] metric type
    zet_value_type_t resultType;                    ///< [out] metric result type
    char resultUnits[ZET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

} zet_metric_properties_t;

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
__ze_api_export ze_result_t __zecall
zetMetricGetProperties(
    zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    zet_metric_properties_t* pProperties            ///< [in,out] metric properties
    );

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
__ze_api_export ze_result_t __zecall
zetDeviceActivateMetricGroups(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                    ///< activate. NULL to deactivate.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_tracer_desc_t
typedef enum _zet_metric_tracer_desc_version_t
{
    ZET_METRIC_TRACER_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZET_METRIC_TRACER_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} zet_metric_tracer_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric tracer descriptor
typedef struct _zet_metric_tracer_desc_t
{
    zet_metric_tracer_desc_version_t version;       ///< [in] ::ZET_METRIC_TRACER_DESC_VERSION_CURRENT
    uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                    ///< will be signalled
    uint32_t samplingPeriod;                        ///< [in,out] tracer sampling period in nanoseconds

} zet_metric_tracer_desc_t;

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
__ze_api_export ze_result_t __zecall
zetMetricTracerOpen(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_tracer_desc_t* desc,                 ///< [in,out] metric tracer descriptor
    ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Must
                                                    ///< be device to host type.
    zet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    );

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
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricTracerMarker(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t value                                  ///< [in] tracer marker value
    );

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
__ze_api_export ze_result_t __zecall
zetMetricTracerClose(
    zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
    );

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
__ze_api_export ze_result_t __zecall
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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_query_pool_desc_t
typedef enum _zet_metric_query_pool_desc_version_t
{
    ZET_METRIC_QUERY_POOL_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0
    ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< latest known version

} zet_metric_query_pool_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric query pool types
typedef enum _zet_metric_query_pool_flag_t
{
    ZET_METRIC_QUERY_POOL_FLAG_PERFORMANCE,         ///< Performance metric query pool.
    ZET_METRIC_QUERY_POOL_FLAG_SKIP_EXECUTION,      ///< Skips workload execution between begin/end calls.

} zet_metric_query_pool_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric query pool description
typedef struct _zet_metric_query_pool_desc_t
{
    zet_metric_query_pool_desc_version_t version;   ///< [in] ::ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT
    zet_metric_query_pool_flag_t flags;             ///< [in] Query pool type.
    uint32_t count;                                 ///< [in] Internal slots count within query pool object.

} zet_metric_query_pool_desc_t;

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
__ze_api_export ze_result_t __zecall
zetMetricQueryPoolCreate(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
    const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
    zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    );

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
__ze_api_export ze_result_t __zecall
zetMetricQueryPoolDestroy(
    zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
    );

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
__ze_api_export ze_result_t __zecall
zetMetricQueryCreate(
    zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t index,                                 ///< [in] index of the query within the pool
    zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    );

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
__ze_api_export ze_result_t __zecall
zetMetricQueryDestroy(
    zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
    );

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
__ze_api_export ze_result_t __zecall
zetMetricQueryReset(
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
    );

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
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricQueryBegin(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    );

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
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricQueryEnd(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
    );

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
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricMemoryBarrier(
    zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
    );

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
__ze_api_export ze_result_t __zecall
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
    );

#pragma endregion
#pragma region module
///////////////////////////////////////////////////////////////////////////////
/// @brief Supported module debug info formats.
typedef enum _zet_module_debug_info_format_t
{
    ZET_MODULE_DEBUG_INFO_FORMAT_ELF_DWARF,         ///< Format is ELF/DWARF

} zet_module_debug_info_format_t;

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
__ze_api_export ze_result_t __zecall
zetModuleGetDebugInfo(
    zet_module_handle_t hModule,                    ///< [in] handle of the module
    zet_module_debug_info_format_t format,          ///< [in] debug info format requested
    size_t* pSize,                                  ///< [in,out] size of debug info in bytes
    uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
    );

#pragma endregion
#pragma region pin
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_profile_info_t
typedef enum _zet_profile_info_version_t
{
    ZET_PROFILE_INFO_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0
    ZET_PROFILE_INFO_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< latest known version

} zet_profile_info_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supportted profile features
typedef enum _zet_profile_flag_t
{
    ZET_PROFILE_FLAG_REGISTER_REALLOCATION = ZE_BIT(0), ///< request the compiler attempt to minimize register usage as much as
                                                    ///< possible to allow for instrumentation
    ZET_PROFILE_FLAG_FREE_REGISTER_INFO = ZE_BIT(1),///< request the compiler generate free register info

} zet_profile_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profiling meta-data for instrumentation
typedef struct _zet_profile_info_t
{
    zet_profile_info_version_t version;             ///< [in] ::ZET_PROFILE_INFO_VERSION_CURRENT
    zet_profile_flag_t flags;                       ///< [out] indicates which flags were enabled during compilation
    uint32_t numTokens;                             ///< [out] number of tokens immediately following this structure

} zet_profile_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported profile token types
typedef enum _zet_profile_token_type_t
{
    ZET_PROFILE_TOKEN_TYPE_FREE_REGISTER,           ///< GRF info

} zet_profile_token_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profile free register token detailing unused registers in the current
///        function
typedef struct _zet_profile_free_register_token_t
{
    zet_profile_token_type_t type;                  ///< [out] type of token
    uint32_t size;                                  ///< [out] total size of the token, in bytes
    uint32_t count;                                 ///< [out] number of register sequences immediately following this
                                                    ///< structure

} zet_profile_free_register_token_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profile register sequence detailing consecutive bytes, all of which
///        are unused
typedef struct _zet_profile_register_sequence_t
{
    uint32_t start;                                 ///< [out] starting byte in the register table, representing the start of
                                                    ///< unused bytes in the current function
    uint32_t count;                                 ///< [out] number of consecutive bytes in the sequence, starting from start

} zet_profile_register_sequence_t;

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
__ze_api_export ze_result_t __zecall
zetKernelGetProfileInfo(
    zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
    zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
    );

#pragma endregion
#pragma region tracing
///////////////////////////////////////////////////////////////////////////////
/// @brief Alias the existing callbacks definition for 'core' callbacks
typedef ze_callbacks_t zet_core_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_tracer_desc_t
typedef enum _zet_tracer_desc_version_t
{
    ZET_TRACER_DESC_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0
    ZET_TRACER_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< latest known version

} zet_tracer_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Tracer descriptor
typedef struct _zet_tracer_desc_t
{
    zet_tracer_desc_version_t version;              ///< [in] ::ZET_TRACER_DESC_VERSION_CURRENT
    void* pUserData;                                ///< [in] pointer passed to every tracer's callbacks

} zet_tracer_desc_t;

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
__ze_api_export ze_result_t __zecall
zetTracerCreate(
    zet_driver_handle_t hDriver,                    ///< [in] handle of the driver
    const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
    zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
    );

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
__ze_api_export ze_result_t __zecall
zetTracerDestroy(
    zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
    );

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
__ze_api_export ze_result_t __zecall
zetTracerSetPrologues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
    );

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
__ze_api_export ze_result_t __zecall
zetTracerSetEpilogues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
    );

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
__ze_api_export ze_result_t __zecall
zetTracerSetEnabled(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
    );

#pragma endregion

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_API_H