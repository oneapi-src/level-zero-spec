/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_api.hpp
 * @version v0.91-271
 *
 */
#ifndef _ZET_API_HPP
#define _ZET_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "zet_api.h"

// 'core' C++ API headers
#include "ze_api.hpp"

#pragma region common
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle to a driver instance
    class Driver;
    struct _driver_handle_t;
    using driver_handle_t = _driver_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of device object
    class Device;
    struct _device_handle_t;
    using device_handle_t = _device_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of module object
    class Module;
    struct _module_handle_t;
    using module_handle_t = _module_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of function object
    class Kernel;
    struct _kernel_handle_t;
    using kernel_handle_t = _kernel_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric group's object
    class MetricGroup;
    struct _metric_group_handle_t;
    using metric_group_handle_t = _metric_group_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric's object
    class Metric;
    struct _metric_handle_t;
    using metric_handle_t = _metric_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric tracer's object
    class MetricTracer;
    struct _metric_tracer_handle_t;
    using metric_tracer_handle_t = _metric_tracer_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query pool's object
    class MetricQueryPool;
    struct _metric_query_pool_handle_t;
    using metric_query_pool_handle_t = _metric_query_pool_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query's object
    class MetricQuery;
    struct _metric_query_handle_t;
    using metric_query_handle_t = _metric_query_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of tracer object
    class Tracer;
    struct _tracer_handle_t;
    using tracer_handle_t = _tracer_handle_t*;

} // namespace zet

namespace zet
{
} // namespace zet

namespace zet
{
    using result_t = ze::result_t;
    using exception_t = ze::exception_t;

} // namespace zet
#pragma endregion
#pragma region device
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for driver instance
    class Driver : public ze::Driver
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Driver::Driver;

        ~Driver( void ) = default;

        Driver( Driver const& other ) = delete;
        void operator=( Driver const& other ) = delete;

        Driver( Driver&& other ) = delete;
        void operator=( Driver&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device : public ze::Device
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Device::Device;

        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Activates metric groups.
        /// 
        /// @details
        ///     - MetricGroup must be active until MetricQueryGetDeta and
        ///       ::zetMetricTracerClose.
        ///     - Conflicting metric groups cannot be activated, in such case tha call
        ///       would fail.
        /// @throws result_t
        void __zecall
        ActivateMetricGroups(
            uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
            MetricGroup** ppMetricGroups = nullptr          ///< [in][optional][range(0, count)] handles of the metric groups to
                                                            ///< activate. NULL to deactivate.
            );

    };

} // namespace zet

namespace zet
{
} // namespace zet
#pragma endregion
#pragma region cmdlist
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList : public ze::CommandList
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::CommandList::CommandList;

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Append metric tracer marker into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricTracerMarker(
            MetricTracer* pMetricTracer,                    ///< [in] pointer to the metric tracer
            uint32_t value                                  ///< [in] tracer marker value
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query begin into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricQueryBegin(
            MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query end into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricQueryEnd(
            MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
            ze::Event* pCompletionEvent = nullptr           ///< [in][optional] pointer to the completion event to signal
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query commands to flush all caches.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricMemoryBarrier(
            void
            );

    };

} // namespace zet

namespace zet
{
} // namespace zet
#pragma endregion
#pragma region debug
///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_API_VERSION
/// @brief The API version.
#define ZET_DEBUG_API_VERSION  1
#endif // ZET_DEBUG_API_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_TIMEOUT_INFINITE
/// @brief An infinite timeout.
#define ZET_DEBUG_TIMEOUT_INFINITE  0xffffffffffffffffull
#endif // ZET_DEBUG_TIMEOUT_INFINITE

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

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Debug session handle
    class Debug;
    struct _debug_session_handle_t;
    using debug_session_handle_t = _debug_session_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for Debug API
    class Debug
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug event flags.
        enum class event_flags_t
        {
            DEBUG_EVENT_FLAG_NONE = 0,                      ///< No event flags
            DEBUG_EVENT_FLAG_STOPPED = ZE_BIT(0),           ///< The reporting thread stopped

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug event types.
        enum class event_type_t
        {
            DEBUG_EVENT_INVALID = 0,                        ///< The event is invalid
            DEBUG_EVENT_DETACHED,                           ///< The tool was detached
            DEBUG_EVENT_PROCESS_ENTRY,                      ///< The debuggee process created command queues on the device
            DEBUG_EVENT_PROCESS_EXIT,                       ///< The debuggee process destroyed all command queues on the device
            DEBUG_EVENT_MODULE_LOAD,                        ///< An in-memory module was loaded onto the device
            DEBUG_EVENT_MODULE_UNLOAD,                      ///< An in-memory module is about to get unloaded from the device
            DEBUG_EVENT_EXCEPTION,                          ///< The thread stopped due to a device exception

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug detach reason.
        enum class detach_reason_t
        {
            DEBUG_DETACH_INVALID = 0,                       ///< The detach reason is not valid
            DEBUG_DETACH_HOST_EXIT,                         ///< The host process exited

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory spaces for Intel Graphics devices.
        enum class memory_space_intel_graphics_t
        {
            DEBUG_MEMORY_SPACE_GEN_DEFAULT = 0,             ///< default memory space (attribute may be omitted)
            DEBUG_MEMORY_SPACE_GEN_SLM,                     ///< shared local memory space

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Register file types for Intel Graphics devices.
        enum class state_intel_graphics_t
        {
            DEBUG_STATE_GEN_INVALID = 0,                    ///< An invalid register file
            DEBUG_STATE_GEN_GRF,                            ///< The general register file
            DEBUG_STATE_GEN_ACC,                            ///< The accumulator register file
            DEBUG_STATE_GEN_ADDR,                           ///< The address register file
            DEBUG_STATE_GEN_FLAG,                           ///< The flags register file

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug configuration: version 1
        struct config_v1_t
        {
            int pid;                                        ///< The host process identifier

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug configuration: version-dependent fields
        union config_variants_t
        {
            config_v1_t v1;                                 ///< Version 1

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug configuration
        struct config_t
        {
            uint16_t version;                               ///< The requested program debug API version
            config_variants_t variant;                      ///< Version-specific fields

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event information for ::ZET_DEBUG_EVENT_DETACHED
        struct event_info_detached_t
        {
            uint8_t reason;                                 ///< The detach reason

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event information for ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD
        struct event_info_module_t
        {
            uint64_t moduleBegin;                           ///< The begin address of the in-memory module
            uint64_t moduleEnd;                             ///< The end address of the in-memory module
            uint64_t load;                                  ///< The load address of the module on the device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event type specific information
        union event_info_t
        {
            event_info_detached_t detached;                 ///< type == ::ZET_DEBUG_EVENT_DETACHED
            event_info_module_t module;                     ///< type == ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief A debug event on the device.
        struct event_t
        {
            uint8_t type;                                   ///< The event type
            uint64_t thread;                                ///< The thread reporting the event
            uint64_t flags;                                 ///< A bit-vector of ::zet_debug_event_flags_t
            event_info_t info;                              ///< Event type specific information

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief A register file descriptor.
        struct state_section_t
        {
            uint16_t type;                                  ///< The register file type type
            uint16_t version;                               ///< The register file version
            uint32_t size;                                  ///< The size of the register file in bytes
            uint64_t offset;                                ///< The offset into the register state area

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief A register state descriptor.
        struct state_t
        {
            uint32_t size;                                  ///< The size of the register state object in bytes
            uint8_t headerSize;                             ///< The size of the register state descriptor in bytes
            uint8_t secSize;                                ///< The size of the register file descriptors in bytes
            uint16_t numSec;                                ///< The number of register file descriptors

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        debug_session_handle_t m_handle;                ///< [in] debug session handle

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Debug( void ) = delete;
        Debug( 
            debug_session_handle_t handle                   ///< [in] debug session handle
            );

        ~Debug( void ) = default;

        Debug( Debug const& other ) = delete;
        void operator=( Debug const& other ) = delete;

        Debug( Debug&& other ) = delete;
        void operator=( Debug&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Attach to a device.
        /// @returns
        ///     - Debug*: debug session handle
        /// 
        /// @throws result_t
        static Debug* __zecall
        Attach(
            Device* pDevice,                                ///< [in] device handle
            const config_t* config                          ///< [in] the debug configuration
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Close a debug session.
        /// @throws result_t
        void __zecall
        Detach(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query the number of device threads for a debug session.
        /// @returns
        ///     - uint64_t: the maximal number of threads
        /// 
        /// @throws result_t
        uint64_t __zecall
        GetNumThreads(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read the topmost debug event.
        /// @returns
        ///     - ze::bool_t:'0' when ZE::RESULT_NOT_READY
        /// @throws result_t
        ze::bool_t __zecall
        ReadEvent(
            uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
            size_t size,                                    ///< [in] the size of the buffer in bytes
            void* buffer                                    ///< [in,out] a buffer to hold the event data
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Interrupt device threads.
        /// @throws result_t
        void __zecall
        Interrupt(
            uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resume device threads.
        /// @throws result_t
        void __zecall
        Resume(
            uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read memory.
        /// @throws result_t
        void __zecall
        ReadMemory(
            uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
            int memSpace,                                   ///< [in] the (device-specific) memory space
            uint64_t address,                               ///< [in] the virtual address of the memory to read from
            size_t size,                                    ///< [in] the number of bytes to read
            void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Write memory.
        /// @throws result_t
        void __zecall
        WriteMemory(
            uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
            int memSpace,                                   ///< [in] the (device-specific) memory space
            uint64_t address,                               ///< [in] the virtual address of the memory to write to
            size_t size,                                    ///< [in] the number of bytes to write
            const void* buffer                              ///< [in] a buffer holding the pattern to write
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read register state.
        /// @throws result_t
        void __zecall
        ReadState(
            uint64_t threadid,                              ///< [in] the thread context
            uint64_t offset,                                ///< [in] the offset into the register state area
            size_t size,                                    ///< [in] the number of bytes to read
            void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Write register state.
        /// @throws result_t
        void __zecall
        WriteState(
            uint64_t threadid,                              ///< [in] the thread context
            uint64_t offset,                                ///< [in] the offset into the register state area
            size_t size,                                    ///< [in] the number of bytes to write
            const void* buffer                              ///< [in] a buffer holding the pattern to write
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_v1_t to std::string
    std::string to_string( const Debug::config_v1_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_variants_t to std::string
    std::string to_string( const Debug::config_variants_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_t to std::string
    std::string to_string( const Debug::config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_flags_t to std::string
    std::string to_string( const Debug::event_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_type_t to std::string
    std::string to_string( const Debug::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::detach_reason_t to std::string
    std::string to_string( const Debug::detach_reason_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_detached_t to std::string
    std::string to_string( const Debug::event_info_detached_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_module_t to std::string
    std::string to_string( const Debug::event_info_module_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_t to std::string
    std::string to_string( const Debug::event_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_t to std::string
    std::string to_string( const Debug::event_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_intel_graphics_t to std::string
    std::string to_string( const Debug::memory_space_intel_graphics_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_intel_graphics_t to std::string
    std::string to_string( const Debug::state_intel_graphics_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_section_t to std::string
    std::string to_string( const Debug::state_section_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_t to std::string
    std::string to_string( const Debug::state_t val );

} // namespace zet
#pragma endregion
#pragma region metric
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

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported value types
    enum class value_type_t
    {
        UINT32,                                         ///< 32-bit unsigned-integer
        UINT64,                                         ///< 64-bit unsigned-integer
        FLOAT32,                                        ///< 32-bit floating-point
        FLOAT64,                                        ///< 64-bit floating-point
        BOOL8,                                          ///< 8-bit boolean

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Union of values
    union value_t
    {
        uint32_t ui32;                                  ///< [out] 32-bit unsigned-integer
        uint64_t ui64;                                  ///< [out] 32-bit unsigned-integer
        float fp32;                                     ///< [out] 32-bit floating-point
        double fp64;                                    ///< [out] 64-bit floating-point
        ze::bool_t b8;                                  ///< [out] 8-bit boolean

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Typed value
    struct typed_value_t
    {
        value_type_t type;                              ///< [out] type of value
        value_t value;                                  ///< [out] value

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric group
    class MetricGroup
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group sampling type
        enum class sampling_type_t
        {
            EVENT_BASED = ZE_BIT(0),                        ///< Event based sampling
            TIME_BASED = ZE_BIT(1),                         ///< Time based sampling

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_group_properties_t
        enum class properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group properties queried using ::zetMetricGroupGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
            char name[ZET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
            char description[ZET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
            sampling_type_t samplingType;                   ///< [out] metric group sampling type
            uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                            ///< groups from different domains.
            uint32_t maxCommandQueueGroupOrdinal;           ///< [out] tracers and queries of this metric group cannot be submitted to
                                                            ///< a command queue group with a larger ordinal value.
                                                            ///< See ::ze_command_queue_desc_t for more information on how to specify
                                                            ///< the command queue's group ordinal.
            uint32_t metricCount;                           ///< [out] metric count belonging to this group

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_group_handle_t m_handle = nullptr;       ///< [in] handle of metric group object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricGroup( void ) = delete;
        MetricGroup( 
            metric_group_handle_t handle,                   ///< [in] handle of metric group object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricGroup( void ) = default;

        MetricGroup( MetricGroup const& other ) = delete;
        void operator=( MetricGroup const& other ) = delete;

        MetricGroup( MetricGroup&& other ) = delete;
        void operator=( MetricGroup&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves metric group for a device.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __zecall
        Get(
            Device* pDevice,                                ///< [in] pointer to the device
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metric groups available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< metric groups.
                                                            ///< if count is larger than the number of metric groups available, then
                                                            ///< the driver will update the value with the correct number of metric
                                                            ///< groups available.
            MetricGroup** ppMetricGroups = nullptr          ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                            ///< groups
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pProperties                       ///< [in,out] metric group properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Calculates metric values from raw data.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __zecall
        CalculateMetricValues(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
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
            typed_value_t* pMetricValues = nullptr          ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                            ///< metrics
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric
    class Metric
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric types
        enum class type_t
        {
            DURATION,                                       ///< Metric type: duration
            EVENT,                                          ///< Metric type: event
            EVENT_WITH_RANGE,                               ///< Metric type: event with range
            THROUGHPUT,                                     ///< Metric type: throughput
            TIMESTAMP,                                      ///< Metric type: timestamp
            FLAG,                                           ///< Metric type: flag
            RATIO,                                          ///< Metric type: ratio
            RAW,                                            ///< Metric type: raw

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_properties_t
        enum class properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric properties queried using ::zetMetricGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZET_METRIC_PROPERTIES_VERSION_CURRENT
            char name[ZET_MAX_METRIC_NAME];                 ///< [out] metric name
            char description[ZET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
            char component[ZET_MAX_METRIC_COMPONENT];       ///< [out] metric component
            uint32_t tierNumber;                            ///< [out] number of tier
            type_t metricType;                              ///< [out] metric type
            value_type_t resultType;                        ///< [out] metric result type
            char resultUnits[ZET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_handle_t m_handle;                       ///< [in] handle of metric object
        MetricGroup* m_pMetricGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Metric( void ) = delete;
        Metric( 
            metric_handle_t handle,                         ///< [in] handle of metric object
            MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
            );

        ~Metric( void ) = default;

        Metric( Metric const& other ) = delete;
        void operator=( Metric const& other ) = delete;

        Metric( Metric&& other ) = delete;
        void operator=( Metric&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getMetricgroup( void ) const { return m_pMetricGroup; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves metric from a metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __zecall
        Get(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metrics available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                            ///< if count is larger than the number of metrics available, then the
                                                            ///< driver will update the value with the correct number of metrics available.
            Metric** ppMetrics = nullptr                    ///< [in,out][optional][range(0, *pCount)] array of pointer to metrics
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a metric.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pProperties                       ///< [in,out] metric properties
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric tracer
    class MetricTracer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_tracer_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric tracer descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZET_METRIC_TRACER_DESC_VERSION_CURRENT
            uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                            ///< will be signalled
            uint32_t samplingPeriod;                        ///< [in,out] tracer sampling period in nanoseconds

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_tracer_handle_t m_handle;                ///< [in] handle of metric tracer object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric tracer

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricTracer( void ) = delete;
        MetricTracer( 
            metric_tracer_handle_t handle,                  ///< [in] handle of metric tracer object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric tracer
            );

        ~MetricTracer( void ) = default;

        MetricTracer( MetricTracer const& other ) = delete;
        void operator=( MetricTracer const& other ) = delete;

        MetricTracer( MetricTracer&& other ) = delete;
        void operator=( MetricTracer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens metric tracer for a device.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// @returns
        ///     - MetricTracer*: handle of metric tracer
        /// 
        /// @throws result_t
        static MetricTracer* __zecall
        Open(
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            desc_t* desc,                                   ///< [in,out] metric tracer descriptor
            ze::Event* pNotificationEvent = nullptr         ///< [in][optional] event used for report availability notification. Must
                                                            ///< be device to host type.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes metric tracer.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same metric tracer handle.
        /// @throws result_t
        void __zecall
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reads data from metric tracer.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        ReadData(
            uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                            ///< if UINT32_MAX, then function will retrieve all reports available
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
                                                            ///< if size is larger than size needed for all reports, then driver will
                                                            ///< update the value with the actual size needed.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                            ///< reports in raw format
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query pool
    class MetricQueryPool
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_query_pool_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool types
        enum class flag_t
        {
            PERFORMANCE,                                    ///< Performance metric query pool.
            SKIP_EXECUTION,                                 ///< Skips workload execution between begin/end calls.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool description
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::PERFORMANCE;             ///< [in] Query pool type.
            uint32_t count;                                 ///< [in] Internal slots count within query pool object.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_pool_handle_t m_handle;            ///< [in] handle of metric query pool object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric query pool

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQueryPool( void ) = delete;
        MetricQueryPool( 
            metric_query_pool_handle_t handle,              ///< [in] handle of metric query pool object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric query pool
            );

        ~MetricQueryPool( void ) = default;

        MetricQueryPool( MetricQueryPool const& other ) = delete;
        void operator=( MetricQueryPool const& other ) = delete;

        MetricQueryPool( MetricQueryPool&& other ) = delete;
        void operator=( MetricQueryPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool of metric queries.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - MetricQueryPool*: handle of metric query pool
        /// 
        /// @throws result_t
        static MetricQueryPool* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] metric group associated with the query object.
            const desc_t* desc                              ///< [in] metric query pool descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query
    class MetricQuery
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_handle_t m_handle;                 ///< [in] handle of metric query object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQuery( void ) = delete;
        MetricQuery( 
            metric_query_handle_t handle,                   ///< [in] handle of metric query object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricQuery( void ) = default;

        MetricQuery( MetricQuery const& other ) = delete;
        void operator=( MetricQuery const& other ) = delete;

        MetricQuery( MetricQuery&& other ) = delete;
        void operator=( MetricQuery&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates metric query object.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - MetricQuery*: handle of metric query
        /// 
        /// @throws result_t
        static MetricQuery* __zecall
        Create(
            MetricQueryPool* pMetricQueryPool,              ///< [in] pointer to the metric query pool
            uint32_t index                                  ///< [in] index of the query within the pool
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a metric query object.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the query before it is deleted
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query handle.
        /// @throws result_t
        static void __zecall
        Destroy(
            MetricQuery* pMetricQuery                       ///< [in][release] pointer to metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resets a metric query object back to inital state.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the query before it is reset
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query handle.
        /// @throws result_t
        void __zecall
        Reset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves raw data for a given metric query.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetData(
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
                                                            ///< if size is larger than size needed for all reports, then driver will
                                                            ///< update the value with the actual size needed.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                            ///< reports in raw format
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( const value_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_t to std::string
    std::string to_string( const value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_t to std::string
    std::string to_string( const typed_value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type_t to std::string
    std::string to_string( const MetricGroup::sampling_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_version_t to std::string
    std::string to_string( const MetricGroup::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_t to std::string
    std::string to_string( const MetricGroup::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( const Metric::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_version_t to std::string
    std::string to_string( const Metric::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_t to std::string
    std::string to_string( const Metric::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_version_t to std::string
    std::string to_string( const MetricTracer::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_t to std::string
    std::string to_string( const MetricTracer::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_version_t to std::string
    std::string to_string( const MetricQueryPool::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::flag_t to std::string
    std::string to_string( const MetricQueryPool::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_t to std::string
    std::string to_string( const MetricQueryPool::desc_t val );

} // namespace zet
#pragma endregion
#pragma region module
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module : public ze::Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module debug info formats.
        enum class debug_info_format_t
        {
            ELF_DWARF,                                      ///< Format is ELF/DWARF

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Module::Module;

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

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
        /// @throws result_t
        void __zecall
        GetDebugInfo(
            debug_info_format_t format,                     ///< [in] debug info format requested
            size_t* pSize,                                  ///< [in,out] size of debug info in bytes
            uint8_t* pDebugInfo = nullptr                   ///< [in,out][optional] byte pointer to debug info
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for kernel
    class Kernel : public ze::Kernel
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_profile_info_t
        enum class profile_info_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supportted profile features
        enum class profile_flag_t
        {
            REGISTER_REALLOCATION = ZE_BIT(0),              ///< request the compiler attempt to minimize register usage as much as
                                                            ///< possible to allow for instrumentation
            FREE_REGISTER_INFO = ZE_BIT(1),                 ///< request the compiler generate free register info

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported profile token types
        enum class profile_token_type_t
        {
            FREE_REGISTER,                                  ///< GRF info

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profiling meta-data for instrumentation
        struct profile_info_t
        {
            profile_info_version_t version = profile_info_version_t::CURRENT;   ///< [in] ::ZET_PROFILE_INFO_VERSION_CURRENT
            profile_flag_t flags;                           ///< [out] indicates which flags were enabled during compilation
            uint32_t numTokens;                             ///< [out] number of tokens immediately following this structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile free register token detailing unused registers in the current
        ///        function
        struct profile_free_register_token_t
        {
            profile_token_type_t type;                      ///< [out] type of token
            uint32_t size;                                  ///< [out] total size of the token, in bytes
            uint32_t count;                                 ///< [out] number of register sequences immediately following this
                                                            ///< structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile register sequence detailing consecutive bytes, all of which
        ///        are unused
        struct profile_register_sequence_t
        {
            uint32_t start;                                 ///< [out] starting byte in the register table, representing the start of
                                                            ///< unused bytes in the current function
            uint32_t count;                                 ///< [out] number of consecutive bytes in the sequence, starting from start

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Kernel::Kernel;

        ~Kernel( void ) = default;

        Kernel( Kernel const& other ) = delete;
        void operator=( Kernel const& other ) = delete;

        Kernel( Kernel&& other ) = delete;
        void operator=( Kernel&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

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
        /// @returns
        ///     - profile_info_t: pointer to profile info
        /// 
        /// @throws result_t
        profile_info_t __zecall
        GetProfileInfo(
            void
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::debug_info_format_t to std::string
    std::string to_string( const Module::debug_info_format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_info_version_t to std::string
    std::string to_string( const Kernel::profile_info_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_flag_t to std::string
    std::string to_string( const Kernel::profile_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_info_t to std::string
    std::string to_string( const Kernel::profile_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_token_type_t to std::string
    std::string to_string( const Kernel::profile_token_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_free_register_token_t to std::string
    std::string to_string( const Kernel::profile_free_register_token_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_register_sequence_t to std::string
    std::string to_string( const Kernel::profile_register_sequence_t val );

} // namespace zet
#pragma endregion
#pragma region pin
namespace zet
{
} // namespace zet

namespace zet
{
} // namespace zet
#pragma endregion
#pragma region tracing
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for tracer
    class Tracer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Alias the existing callbacks definition for 'core' callbacks
        using core_callbacks_t = ze_callbacks_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_tracer_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Tracer descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZET_TRACER_DESC_VERSION_CURRENT
            void* pUserData;                                ///< [in] pointer passed to every tracer's callbacks

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        tracer_handle_t m_handle;                       ///< [in] handle of tracer object
        Driver* m_pDriver;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the tracer object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Tracer( void ) = delete;
        Tracer( 
            tracer_handle_t handle,                         ///< [in] handle of tracer object
            Driver* pDriver,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the tracer object
            );

        ~Tracer( void ) = default;

        Tracer( Tracer const& other ) = delete;
        void operator=( Tracer const& other ) = delete;

        Tracer( Tracer&& other ) = delete;
        void operator=( Tracer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a tracer for the specified driver.
        /// 
        /// @details
        ///     - The tracer can only be used on the driver on which it was created.
        ///     - The tracer is created in the disabled state.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Tracer*: pointer to handle of tracer object created
        /// 
        /// @throws result_t
        static Tracer* __zecall
        Create(
            Driver* pDriver,                                ///< [in] pointer to the driver
            const desc_t* desc                              ///< [in] pointer to tracer descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            Tracer* pTracer                                 ///< [in][release] pointer to tracer object to destroy
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
        /// @throws result_t
        void __zecall
        SetPrologues(
            core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
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
        /// @throws result_t
        void __zecall
        SetEpilogues(
            core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Enables (or disables) the tracer
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void __zecall
        SetEnabled(
            ze::bool_t enable                               ///< [in] enable the tracer if true; disable if false
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_version_t to std::string
    std::string to_string( const Tracer::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_t to std::string
    std::string to_string( const Tracer::desc_t val );

} // namespace zet
#pragma endregion
#endif // defined(__cplusplus)
#endif // _ZET_API_HPP