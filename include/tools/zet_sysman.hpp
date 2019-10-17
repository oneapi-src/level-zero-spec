/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_sysman.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#ifndef _ZET_SYSMAN_HPP
#define _ZET_SYSMAN_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define ZET_STRING_PROPERTY_SIZE  32
#endif // ZET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_SCHED_WATCHDOG_DISABLE
/// @brief Disable forward progress guard timeout.
#define ZET_SCHED_WATCHDOG_DISABLE  (~(0ULL))
#endif // ZET_SCHED_WATCHDOG_DISABLE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define ZET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // ZET_FAN_TEMP_SPEED_PAIR_COUNT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_EVENT_WAIT_INFINITE
/// @brief Wait infinitely for events to arrive.
#define ZET_EVENT_WAIT_INFINITE  0xFFFFFFFF
#endif // ZET_EVENT_WAIT_INFINITE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DIAG_FIRST_TEST_INDEX
/// @brief Diagnostic test index to use for the very first test.
#define ZET_DIAG_FIRST_TEST_INDEX  0x0
#endif // ZET_DIAG_FIRST_TEST_INDEX

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DIAG_LAST_TEST_INDEX
/// @brief Diagnostic test index to use for the very last test.
#define ZET_DIAG_LAST_TEST_INDEX  0xFFFFFFFF
#endif // ZET_DIAG_LAST_TEST_INDEX

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device
    class Sysman
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of SMI
        enum class version_t
        {
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device Type
        enum class device_type_t
        {
            INTEGRATED = 0,                                 ///< The device is an integrated GPU
            DISCRETE,                                       ///< The device is a discrete GPU

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Scheduler mode
        enum class sched_mode_t
        {
            TIMEOUT = 0,                                    ///< Multiple applications or contexts are submitting work to the hardware.
                                                            ///< When higher priority work arrives, the scheduler attempts to pause the
                                                            ///< current executing work within some timeout interval, then submits the
                                                            ///< other work.
            TIMESLICE,                                      ///< The scheduler attempts to fairly timeslice hardware execution time
                                                            ///< between multiple contexts submitting work to the hardware
                                                            ///< concurrently.
            EXCLUSIVE,                                      ///< Any application or context can run indefinitely on the hardware
                                                            ///< without being preempted or terminated. All pending work for other
                                                            ///< contexts must wait until the running context completes with no further
                                                            ///< submitted work.
            COMPUTE_UNIT_DEBUG,                             ///< Scheduler ensures that submission of workloads to the hardware is
                                                            ///< optimized for compute unit debugging.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI bar types
        enum class pci_bar_type_t
        {
            CONFIG = 0,                                     ///< PCI configuration space
            MMIO,                                           ///< MMIO registers
            VRAM,                                           ///< VRAM aperture
            ROM,                                            ///< ROM aperture
            VGA_IO,                                         ///< Legacy VGA IO ports
            VGA_MEM,                                        ///< Legacy VGA memory
            INDIRECT_IO,                                    ///< Indirect IO port access
            INDIRECT_MEM,                                   ///< Indirect memory access
            OTHER,                                          ///< Other type of PCI bar

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event types
        enum class event_type_t
        {
            FREQ_THROTTLED = 0,                             ///< The frequency is being throttled
            ENERGY_THRESHOLD_CROSSED,                       ///< Interrupt from the PCU when the energy threshold is crossed.
            MAX_TEMPERATURE,                                ///< Interrupt from the PCU when the energy Max temperature is reached.
            RAS_ERRORS,                                     ///< ECC/RAS errors
            NUM,                                            ///< The number of event types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties
        struct properties_t
        {
            ze::Device::properties_t core;                  ///< [out] Core device properties
            uint32_t numSubdevices;                         ///< [out] Number of sub-devices
            device_type_t deviceType;                       ///< [out] Device type
            int8_t serialNumber[ZET_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
            int8_t boardNumber[ZET_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
            int8_t brandName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
            int8_t modelName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
            int8_t vendorName[ZET_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
            int8_t driverVersion[ZET_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Configuration for timeout scheduler mode (::ZET_SCHED_MODE_TIMEOUT)
        struct sched_timeout_properties_t
        {
            uint64_t watchdogTimeout;                       ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                            ///< for a batch of work submitted to a hardware engine to complete or to
                                                            ///< be preempted so as to run another context.
                                                            ///< If this time is exceeded, the hardware engine is reset and the context terminated.
                                                            ///< If set to ::ZET_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                            ///< long as it wants without being terminated, but preemption attempts to
                                                            ///< run other contexts are permitted but not enforced.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Configuration for timeslice scheduler mode
        ///        (::ZET_SCHED_MODE_TIMESLICE)
        struct sched_timeslice_properties_t
        {
            uint64_t interval;                              ///< [in,out] The average interval in microseconds that a submission for a
                                                            ///< context will run on a hardware engine before being preempted out to
                                                            ///< run a pending submission for another context.
            uint64_t yieldTimeout;                          ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                            ///< to preempt a workload running on an engine before deciding to reset
                                                            ///< the hardware engine and terminating the associated context.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI address
        struct pci_address_t
        {
            uint32_t domain;                                ///< [out] BDF domain
            uint32_t bus;                                   ///< [out] BDF bus
            uint32_t device;                                ///< [out] BDF device
            uint32_t function;                              ///< [out] BDF function

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI speed
        struct pci_speed_t
        {
            uint32_t gen;                                   ///< [out] The link generation
            uint32_t width;                                 ///< [out] The number of lanes
            uint32_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec
            uint32_t maxPacketSize;                         ///< [out] Maximum packet size in bytes.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Static PCI properties
        struct pci_properties_t
        {
            pci_address_t address;                          ///< [out] The BDF address
            uint32_t numBars;                               ///< [out] The number of configured bars
            pci_speed_t maxSpeed;                           ///< [out] Fastest port configuration supported by the device.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamic PCI state
        struct pci_state_t
        {
            pci_speed_t speed;                              ///< [out] The current port configure speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Properties of a pci bar
        struct pci_bar_properties_t
        {
            pci_bar_type_t type;                            ///< [out] The type of bar
            uint64_t base;                                  ///< [out] Base address of the bar.
            uint64_t size;                                  ///< [out] Size of the bar.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI throughput
        /// 
        /// @details
        ///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
        ///       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
        ///       s1.timestamp))
        struct pci_throughput_t
        {
            uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when the measurement
                                                            ///< was made.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.
            uint64_t rxCounter;                             ///< [out] Monotonic counter for the number of bytes received
            uint64_t txCounter;                             ///< [out] Monotonic counter for the number of bytes transmitted (including
                                                            ///< replays)
            uint32_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec under the current
                                                            ///< configuration

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI stats counters
        /// 
        /// @details
        ///     - Percent replays is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %replay = 10^6 * (s2.replayCounter -
        ///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
        struct pci_stats_t
        {
            uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when the measurement
                                                            ///< was made.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.
            uint64_t replayCounter;                         ///< [out] Monotonic counter for the number of replay packets
            uint64_t packetCounter;                         ///< [out] Monotonic counter for the number of packets

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event properties
        struct event_properties_t
        {
            ze::bool_t supportedEvents[static_cast<int>(event_type_t::NUM)];///< [out] Set to true for the events that are supported

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to register/unregister events
        struct event_request_t
        {
            event_type_t event;                             ///< [in] The event type to register.
            uint32_t threshold;                             ///< [in] The application only receives a notification when the total count
                                                            ///< exceeds this value. Set to zero to receive a notification for every
                                                            ///< new event.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_handle_t m_handle = nullptr;             ///< [in] handle of SMI object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sysman( void ) = delete;
        Sysman( 
            sysman_handle_t handle,                         ///< [in] handle of SMI object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~Sysman( void ) = default;

        Sysman( Sysman const& other ) = delete;
        void operator=( Sysman const& other ) = delete;

        Sysman( Sysman&& other ) = delete;
        void operator=( Sysman&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the handle to access SMI features for a device
        /// 
        /// @details
        ///     - The returned handle is unique
        /// @returns
        ///     - Sysman*: Handle for accessing SMI features
        /// 
        /// @throws result_t
        static Sysman* __zecall
        Get(
            Device* pDevice,                                ///< [in] Handle of the device
            version_t version                               ///< [in] SMI version that application was built with
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties about the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        DeviceGetProperties(
            properties_t* pProperties                       ///< [in] Structure that will contain information about the device.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current scheduler mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SchedulerGetCurrentMode(
            sched_mode_t* pMode                             ///< [in] Will contain the current scheduler mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMEOUT
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SchedulerGetTimeoutModeProperties(
            ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                            ///< this mode, otherwise it will return the current properties.
            sched_timeout_properties_t* pConfig             ///< [in] Will contain the current parameters for this mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMESLICE
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SchedulerGetTimesliceModeProperties(
            ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                            ///< this mode, otherwise it will return the current properties.
            sched_timeslice_properties_t* pConfig           ///< [in] Will contain the current parameters for this mode.
            );

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
        /// @throws result_t
        void __zecall
        SchedulerSetTimeoutMode(
            sched_timeout_properties_t* pProperties,        ///< [in] The properties to use when configurating this mode.
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                            ///< scheduler mode.
            );

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
        /// @throws result_t
        void __zecall
        SchedulerSetTimesliceMode(
            sched_timeslice_properties_t* pProperties,      ///< [in] The properties to use when configurating this mode.
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                            ///< scheduler mode.
            );

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
        /// @throws result_t
        void __zecall
        SchedulerSetExclusiveMode(
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                            ///< scheduler mode.
            );

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
        /// @throws result_t
        void __zecall
        SchedulerSetComputeUnitDebugMode(
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                            ///< scheduler mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset device
        /// @throws result_t
        void __zecall
        DeviceReset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Find out if the device has been repaired (either by the manufacturer
        ///        or by running diagnostics)
        /// @throws result_t
        void __zecall
        DeviceWasRepaired(
            ze::bool_t* pWasRepaired                        ///< [in] Will indicate if the device was repaired
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PCI properties - address, max speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetProperties(
            pci_properties_t* pProperties                   ///< [in] Will contain the PCI properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current PCI state - current speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetState(
            pci_state_t* pState                             ///< [in] Will contain the PCI properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties of a bar
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetBarProperties(
            uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::zet_pci_properties_t.numBars -
                                                            ///< 1]).
            pci_bar_properties_t* pProperties               ///< [in] Will contain properties of the specified bar
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PCI throughput
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetThroughput(
            pci_throughput_t* pThroughput                   ///< [in] Will contain a snapshot of the latest throughput counters.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PCI stats
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetStats(
            pci_stats_t* pStats                             ///< [in] Will contain a snapshot of the latest stats.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of power domains
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PowerGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanPower** ppPower = nullptr                 ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of frequency domains
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        FrequencyGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanFrequency** ppFrequency = nullptr         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of engine groups
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        EngineGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanEngine** ppEngine = nullptr               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of standby controls
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        StandbyGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanStandby** ppStandby = nullptr             ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of firmwares
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        FirmwareGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanFirmware** ppFirmware = nullptr           ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of memory modules
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        MemoryGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanMemory** ppMemory = nullptr               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of connectivity switches
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        LinkSwitchGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanLinkSwitch** ppSwitch = nullptr           ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of temperature sensors
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        TemperatureGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanTemperature** ppTemperature = nullptr     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of power supplies
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PsuGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanPsu** ppPsu = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of fans
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        FanGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanFan** ppFan = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of LEDs
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        LedGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanLed** ppLed = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of RAS error sets
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        RasGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanRas** ppRas = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get event properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        EventsGetProperties(
            event_properties_t* pProperties                 ///< [in] Structure describing event properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Register to receive events
        /// 
        /// @details
        ///     - This will only register the specified list of events. If other events
        ///       have been registered, notifications for them will continue.
        ///     - Set count to zero to receive notifications for all events.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        EventsRegister(
            uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                            ///< be registered.
            event_request_t* pEvents = nullptr              ///< [in][optional] Events to register.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Unregister events
        /// 
        /// @details
        ///     - This will only unregister the specified list of events. If other
        ///       events have been registered, notifications for them will continue.
        ///     - Set count to zero to no longer receive any notifications.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        EventsUnregister(
            uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                            ///< be unregistered.
            event_request_t* pEvents = nullptr              ///< [in][optional] Events to unregister.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get events that have been triggered for a specific device or from all
        ///        registered devices
        /// 
        /// @details
        ///     - If events have occurred, they are returned and the corresponding event
        ///       status is cleared if the argument clear = true.
        ///     - If listening to events from multiple devices, it is recommended to
        ///       call this function with hSysman = nullptr, clear = false and timeout =
        ///       ::ZET_EVENT_WAIT_INFINITE. Then call this function for each device
        ///       with clear = true and timeout = 0.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __zecall
        EventsListen(
            Sysman* pSysman,                                ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                            ///< device for which the application has registered to receive
                                                            ///< notifications.
            ze::bool_t clear,                               ///< [in] Clear the event status.
            uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                            ///< check status and return immediately. Set to ::ZET_EVENT_WAIT_INFINITE
                                                            ///< to block until events arrive.
            uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::zet_sysman_event_type_t) that have been
                                                            ///< triggered.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of diagnostics test suites
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        DiagnosticsGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanDiagnostics** ppDiagnostics = nullptr     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device power domain
    class SysmanPower
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Properties related to device power settings
        struct power_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Software can change the power limits.
            uint32_t maxLimit;                              ///< [out] The maximum power limit in milliwatts that can be requested.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Energy counter snapshot
        /// 
        /// @details
        ///     - Average power is calculated by taking two snapshots (s1, s2) and using
        ///       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
        ///       s1.timestamp)
        struct power_energy_counter_t
        {
            uint64_t energy;                                ///< [out] The monotonic energy counter in microjoules.
            uint64_t timestamp;                             ///< [out] Microsecond timestamp when energy was captured.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Energy threshold
        /// 
        /// @details
        ///     - Energy threshold value, when this value is crossed, pcu will signal an
        ///       interrupt.
        struct power_energy_threshold_t
        {
            uint32_t energy;                                ///< [in,out] The energy threshold in joules.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sustained power limits
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency if
        ///       the power averaged over a window (typically seconds) exceeds this
        ///       limit.
        struct power_sustained_limit_t
        {
            ze::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts
            uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Burst power limit
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency of
        ///       the device if the power averaged over a few milliseconds exceeds a
        ///       limit known as PL2. Typically PL2 > PL1 so that it permits the
        ///       frequency to burst higher for short periods than would be otherwise
        ///       permitted by PL1.
        struct power_burst_limit_t
        {
            ze::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Peak power limit
        /// 
        /// @details
        ///     - The power controller (Punit) will preemptively throttle the operating
        ///       frequency of the device when the instantaneous power exceeds this
        ///       limit. The limit is known as PL4. It expresses the maximum power that
        ///       can be drawn from the power supply.
        ///     - If this power limit is removed or set too high, the power supply will
        ///       generate an interrupt when it detects an overcurrent condition and the
        ///       power controller will throttle the device frequencies down to min. It
        ///       is thus better to tune the PL4 value in order to avoid such
        ///       excursions.
        struct power_peak_limit_t
        {
            uint32_t powerAC;                               ///< [in,out] power limit in milliwatts for the AC power source.
            uint32_t powerDC;                               ///< [in,out] power limit in milliwatts for the DC power source. This is
                                                            ///< ignored if the product does not have a battery.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_pwr_handle_t m_handle = nullptr;         ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanPower( void ) = delete;
        SysmanPower( 
            sysman_pwr_handle_t handle,                     ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanPower( void ) = default;

        SysmanPower( SysmanPower const& other ) = delete;
        void operator=( SysmanPower const& other ) = delete;

        SysmanPower( SysmanPower&& other ) = delete;
        void operator=( SysmanPower&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties related to a power domain
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            power_properties_t* pProperties                 ///< [in] Structure that will contain property data.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get energy counter
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetEnergyCounter(
            power_energy_counter_t* pEnergy                 ///< [in] Will contain the latest snapshot of the energy counter and
                                                            ///< timestamp when the last counter value was measured.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get energy threshold
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetEnergyThreshold(
            power_energy_threshold_t* pThreshold            ///< [in] The current energy threshold value in joules.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set energy threshold
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetEnergyThreshold(
            power_energy_threshold_t* pThreshold            ///< [in] The energy threshold to be set in joules.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetLimits(
            power_sustained_limit_t* pSustained = nullptr,  ///< [in][optional] The sustained power limit.
            power_burst_limit_t* pBurst = nullptr,          ///< [in][optional] The burst power limit.
            power_peak_limit_t* pPeak = nullptr             ///< [in][optional] The peak power limit.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set power limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetLimits(
            const power_sustained_limit_t* pSustained = nullptr,///< [in][optional] The sustained power limit.
            const power_burst_limit_t* pBurst = nullptr,    ///< [in][optional] The burst power limit.
            const power_peak_limit_t* pPeak = nullptr       ///< [in][optional] The peak power limit.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device frequency domain
    class SysmanFrequency
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Overclocking modes
        enum class oc_mode_t
        {
            OVERCLOCKING_INTERPOLATIVE_MODE = 0,            ///< Interpolative Mode.
            OVERCLOCKING_OVERRIDE_MODE = 1,                 ///< Override Mode.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Over clocking error type
        enum class oc_error_type_t
        {
            OVERCLOCKING_LOCKED = 225,                      ///< The overclocking is locked. Service is read-only.
            OVERCLOCKING_DDOMAIN_SERVICE_NOT_SUPPORTED,     ///< The specified domain does not support the requested service.
            OVERCLOCKING_RATIO_EXCEEDS_MAX,                 ///< The ratio exceeds maximum overclocking limits.
            OVERCLOCKING_VOLTAGE_EXCEEDS_MAX,               ///< Requested voltage exceeds input regulators max supported voltage.
            OVERCLOCKING_NOT_SUPPORTED,                     ///< No overclocking capability on the Hardware.
            OVERCLOCKING_INVALID_VR_ADDRESS,                ///< The VR Address provided is illegal.
            OOVERCLOCKING_INVALID_ICCMAX,                   ///< ICCMAX value given is invalid (more than 10 bits) or too low.
            OVERCLOCKING_VOLTAGE_OVERRIDE_DISABLED,         ///< Voltage manipulation attempted when it is disabled.
            OVERCLOCKING_INVALID_COMMAND,                   ///< Data setting invalid for the command.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency domains
        enum class freq_domain_t
        {
            GPU = 0,                                        ///< Frequency of the GPU.
            MEMORY,                                         ///< Frequency of the local memory.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency throttle reasons
        enum class freq_throttle_reasons_t
        {
            NONE = 0,                                       ///< frequency not throttled
            AVE_PWR_CAP = ZE_BIT( 0 ),                      ///< frequency throttled due to average power excursion (PL1)
            BURST_PWR_CAP = ZE_BIT( 1 ),                    ///< frequency throttled due to burst power excursion (PL2)
            CURRENT_LIMIT = ZE_BIT( 2 ),                    ///< frequency throttled due to current excursion (PL4)
            THERMAL_LIMIT = ZE_BIT( 3 ),                    ///< frequency throttled due to thermal excursion (T > TjMax)
            PSU_ALERT = ZE_BIT( 4 ),                        ///< frequency throttled due to power supply assertion
            SW_RANGE = ZE_BIT( 5 ),                         ///< frequency throttled due to software supplied frequency range
            HW_RANGE = ZE_BIT( 6 ),                         ///< frequency throttled due to a sub block that has a lower frequency
                                                            ///< range when it receives clocks

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Overclocking properties
        /// 
        /// @details
        ///     - Provides all the overclocking capabilities and properties supported by
        ///       the device in the current domain.
        struct oc_capabilities_t
        {
            double MaxOcFrequencyLimit;                     ///< [out] Max overclocking frequency limit in Mhz.
            double MaxFactoryDefaultFrequency;              ///< [out] Maximum factory default frequency in Mhz.
            double MaxFactoryDefaultVoltage;                ///< [out] Maximum factory default voltage in Votls.
            ze::bool_t TjMaxSupported;                      ///< [out] is the TjMax supported on this domain.
            ze::bool_t IccMaxSupported;                     ///< [out] is the Icc supported on this domain.
            ze::bool_t FrequencyOcSupported;                ///< [out] Frequency overclocking supported
            ze::bool_t VoltageOverrideSupported;            ///< [out] Voltage overrides supported
            ze::bool_t VoltageOffsetSupported;              ///< [out] Voltage offset is supported
            ze::bool_t HighVoltModeCapable;                 ///< [out] Capable of high voltage mode
            ze::bool_t HighVoltModeEnabled;                 ///< [out] High voltage mode is enabled

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Overclocking configuration
        /// 
        /// @details
        ///     - Provide the current settings to be read or changed.
        struct oc_configuration_t
        {
            double OcFrequency;                             ///< [in,out] Overclocking Frequency
            double TargetVoltage;                           ///< [in,out] Target voltage in Volts
            oc_mode_t TargetMode;                           ///< [in,out] Overclock Mode ::zet_oc_mode_t.
            double VoltageOffset;                           ///< [in,out] Voltage offset in Volts.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Maximum desired current.
        /// 
        /// @details
        ///     - For overclock-able parts this holds the maximum desired current if the
        ///       domains supports it.
        struct oc_icc_max_t
        {
            double IccMax;                                  ///< [in,out] Maximum desired current in Amperes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature Junction Maximum.
        /// 
        /// @details
        ///     - For overclock-able parts this holds the maximum temperature limit at
        ///       which the part will throttle if the domains supports it.
        struct oc_tj_max_t
        {
            double TjMax;                                   ///< [in,out] Maximum desired current in degrees celcius.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency properties
        /// 
        /// @details
        ///     - Provides the set of frequencies as a list and as a range/step.
        ///     - It is generally recommended that applications choose frequencies from
        ///       the list. However applications can also construct the list themselves
        ///       using the range/steps provided.
        struct freq_properties_t
        {
            freq_domain_t type;                             ///< [out] The type of frequency domain (GPU, memory, ...)
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can control the frequency of this domain
            ze::bool_t canOverclock;                        ///< [out] Indicates if software can overclock this frequency domain
            double min;                                     ///< [out] The minimum clock frequency in units of MHz
            double max;                                     ///< [out] The maximum clock frequency in units of MHz
            double step;                                    ///< [out] The step clock frequency in units of MHz
            uint32_t num;                                   ///< [out] The number of clocks in the array pClocks
            const double* pClocks;                          ///< [out] Array of clock frequencies in units of MHz ordered from smallest
                                                            ///< to largest.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency range between which the hardware can operate.
        struct freq_range_t
        {
            double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                            ///< management will not request frequencies. Setting to 0 will use the
                                                            ///< hardware default value.
            double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                            ///< management will not request frequencies. Setting to 0 will use the
                                                            ///< hardware default value.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency state
        struct freq_state_t
        {
            double request;                                 ///< [out] The current frequency request in MHz.
            double tdp;                                     ///< [out] The maximum frequency in MHz supported under the current TDP
                                                            ///< conditions
            double efficient;                               ///< [out] The efficient minimum frequency in MHz
            double actual;                                  ///< [out] The resolved frequency in MHz
            uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the hardware
                                                            ///< (Bitfield of (1<<::zet_freq_throttle_reasons_t)).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency throttle time snapshot
        /// 
        /// @details
        ///     - Percent time throttled is calculated by taking two snapshots (s1, s2)
        ///       and using the equation: %throttled = (s2.throttleTime -
        ///       s1.throttleTime) / (s2.timestamp - s1.timestamp)
        struct freq_throttle_time_t
        {
            uint64_t throttleTime;                          ///< [out] The monotonic counter of time in microseconds that the frequency
                                                            ///< has been limited by the hardware.
            uint64_t timestamp;                             ///< [out] Microsecond timestamp when throttleTime was captured.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_freq_handle_t m_handle = nullptr;        ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanFrequency( void ) = delete;
        SysmanFrequency( 
            sysman_freq_handle_t handle,                    ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanFrequency( void ) = default;

        SysmanFrequency( SysmanFrequency const& other ) = delete;
        void operator=( SysmanFrequency const& other ) = delete;

        SysmanFrequency( SysmanFrequency&& other ) = delete;
        void operator=( SysmanFrequency&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the last overclock error
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetLastOcError(
            oc_error_type_t* pOcError                       ///< [in] Error in ::zet_oc_error_type_t .
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the overclocking capabilities.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetOcCapabilities(
            oc_capabilities_t* pOcCapabilities              ///< [in] Pointer to the capabilities structure ::zet_oc_capabilities_t.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the overclocking configuration.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetOcConfig(
            oc_configuration_t* pOcConfiguration            ///< [in] Pointer to the configuration structure ::zet_oc_configuration_t.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the overclocking configuration.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetOcConfig(
            oc_configuration_t* pOcConfiguration            ///< [in] Pointer to the configuration structure ::zet_oc_configuration_t.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the Icc Max.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetOcIccMax(
            oc_icc_max_t* pOcIccMax                         ///< [in] Pointer to the Icc Max.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the Icc Max.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetOcIccMax(
            oc_icc_max_t* pOcIccMax                         ///< [in] Pointer to the Icc Max.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the TjMax.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetOcTjMax(
            oc_tj_max_t* pOcTjMax                           ///< [in] Pointer to the TjMax.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the TjMax.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetOcTjMax(
            oc_tj_max_t* pOcTjMax                           ///< [in] Pointer to the TjMax.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency properties - available frequencies
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            freq_properties_t* pProperties                  ///< [in] The frequency properties for the specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current frequency limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetRange(
            freq_range_t* pLimits                           ///< [in] The range between which the hardware can operate for the
                                                            ///< specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set frequency range between which the hardware can operate.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetRange(
            const freq_range_t* pLimits                     ///< [in] The limits between which the hardware can operate for the
                                                            ///< specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current frequency state - frequency request, actual frequency, TDP
        ///        limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            freq_state_t* pState                            ///< [in] Frequency state for the specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency throttle time
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetThrottleTime(
            freq_throttle_time_t* pThrottleTime             ///< [in] Will contain a snapshot of the throttle time counters for the
                                                            ///< specified domain.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device engine group
    class SysmanEngine
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Accelerator engine groups
        enum class engine_group_t
        {
            ALL = 0,                                        ///< Access information about all engines combined.
            COMPUTE,                                        ///< Access information about compute engines.
            MEDIA,                                          ///< Access information about media engines.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Engine group properties
        struct engine_properties_t
        {
            engine_group_t type;                            ///< [out] The engine group
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Engine activity counters
        /// 
        /// @details
        ///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %util = (s2.activeTime - s1.activeTime) /
        ///       (s2.timestamp - s1.timestamp)
        struct engine_stats_t
        {
            uint64_t activeTime;                            ///< [out] Monotonic counter for time in microseconds that this resource is
                                                            ///< actively running workloads.
            uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when activeTime
                                                            ///< counter was sampled.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_engine_handle_t m_handle = nullptr;      ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanEngine( void ) = delete;
        SysmanEngine( 
            sysman_engine_handle_t handle,                  ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanEngine( void ) = default;

        SysmanEngine( SysmanEngine const& other ) = delete;
        void operator=( SysmanEngine const& other ) = delete;

        SysmanEngine( SysmanEngine&& other ) = delete;
        void operator=( SysmanEngine&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get engine group properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            engine_properties_t* pProperties                ///< [in] The properties for the specified engine group.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the activity stats for an engine group
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetActivity(
            engine_stats_t* pStats                          ///< [in] Will contain a snapshot of the engine group activity counters.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI standby control
    class SysmanStandby
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby hardware components
        enum class standby_type_t
        {
            GLOBAL = 0,                                     ///< Control the overall standby policy of the device/sub-device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby promotion modes
        enum class standby_promo_mode_t
        {
            DEFAULT = 0,                                    ///< Best compromise between performance and energy savings.
            NEVER,                                          ///< The device/component will never shutdown. This can improve performance
                                                            ///< but uses more energy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby hardware component properties
        struct standby_properties_t
        {
            standby_type_t type;                            ///< [out] Which standby hardware component this controls
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_standby_handle_t m_handle = nullptr;     ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanStandby( void ) = delete;
        SysmanStandby( 
            sysman_standby_handle_t handle,                 ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanStandby( void ) = default;

        SysmanStandby( SysmanStandby const& other ) = delete;
        void operator=( SysmanStandby const& other ) = delete;

        SysmanStandby( SysmanStandby&& other ) = delete;
        void operator=( SysmanStandby&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get standby hardware component properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            standby_properties_t* pProperties               ///< [in] Will contain the standby hardware properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the current standby promotion mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetMode(
            standby_promo_mode_t* pMode                     ///< [in] Will contain the current standby mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set standby promotion mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetMode(
            standby_promo_mode_t mode                       ///< [in] New standby mode.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device firmware
    class SysmanFirmware
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Firmware properties
        struct firmware_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can flash the firmware
            int8_t name[ZET_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
            int8_t version[ZET_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_firmware_handle_t m_handle = nullptr;    ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanFirmware( void ) = delete;
        SysmanFirmware( 
            sysman_firmware_handle_t handle,                ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanFirmware( void ) = default;

        SysmanFirmware( SysmanFirmware const& other ) = delete;
        void operator=( SysmanFirmware const& other ) = delete;

        SysmanFirmware( SysmanFirmware&& other ) = delete;
        void operator=( SysmanFirmware&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            firmware_properties_t* pProperties              ///< [in] Pointer to an array that will hold the properties of the firmware
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware checksum
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetChecksum(
            uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Flash a new firmware image
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        Flash(
            void* pImage,                                   ///< [in] Image of the new firmware to flash.
            uint32_t size                                   ///< [in] Size of the flash image.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device memory module
    class SysmanMemory
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory module types
        enum class mem_type_t
        {
            HBM = 0,                                        ///< HBM memory
            DDR,                                            ///< DDR memory
            SRAM,                                           ///< SRAM memory
            L1,                                             ///< L1 cache
            L3,                                             ///< L3 cache
            GRF,                                            ///< Execution unit register file
            SLM,                                            ///< Execution unit shared local memory

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory properties
        struct mem_properties_t
        {
            mem_type_t type;                                ///< [out] The memory type
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            uint64_t size;                                  ///< [out] Physical memory size in bytes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory bandwidth
        /// 
        /// @details
        ///     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
        ///       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
        ///       (s2.timestamp - s1.timestamp))
        struct mem_bandwidth_t
        {
            uint64_t readCounter;                           ///< [out] Total bytes read from memory
            uint64_t writeCounter;                          ///< [out] Total bytes written to memory
            uint64_t maxBandwidth;                          ///< [out] Current maximum bandwidth in units of bytes/sec
            uint64_t timestamp;                             ///< [out] The timestamp when these measurements were sampled.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory allocation
        /// 
        /// @details
        ///     - Percent allocation is given by 100 * allocated / total.
        ///     - Percent free is given by 100 * (total - allocated) / total.
        struct mem_alloc_t
        {
            uint64_t allocated;                             ///< [out] The total allocated bytes
            uint64_t total;                                 ///< [out] The total physical memory in bytes

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_mem_handle_t m_handle = nullptr;         ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanMemory( void ) = delete;
        SysmanMemory( 
            sysman_mem_handle_t handle,                     ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanMemory( void ) = default;

        SysmanMemory( SysmanMemory const& other ) = delete;
        void operator=( SysmanMemory const& other ) = delete;

        SysmanMemory( SysmanMemory&& other ) = delete;
        void operator=( SysmanMemory&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            mem_properties_t* pProperties                   ///< [in] Will contain memory properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory bandwidth
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetBandwidth(
            mem_bandwidth_t* pBandwidth                     ///< [in] Will contain a snapshot of the bandwidth counters.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetAllocated(
            mem_alloc_t* pAllocated                         ///< [in] Will contain the current allocated memory.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device connectivity switch
    class SysmanLinkSwitch
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Connectivity switch properties
        struct link_switch_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the switch is located on a sub-device; false means that
                                                            ///< the switch is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Connectivity switch state
        struct link_switch_state_t
        {
            ze::bool_t enabled;                             ///< [out] Indicates if the switch is enabled/disabled

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_link_switch_handle_t m_handle = nullptr; ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanLinkSwitch( void ) = delete;
        SysmanLinkSwitch( 
            sysman_link_switch_handle_t handle,             ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanLinkSwitch( void ) = default;

        SysmanLinkSwitch( SysmanLinkSwitch const& other ) = delete;
        void operator=( SysmanLinkSwitch const& other ) = delete;

        SysmanLinkSwitch( SysmanLinkSwitch&& other ) = delete;
        void operator=( SysmanLinkSwitch&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get connectivity switch properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            link_switch_properties_t* pProperties           ///< [in] Will contain the Switch properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get connectivity switch state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            link_switch_state_t* pState                     ///< [in] Will contain the current state of the switch (enabled/disabled).
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set connectivity switch state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetState(
            ze::bool_t enable                               ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of connectivity ports in a switch
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetPorts(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanLinkPort** ppPort = nullptr               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device connectivity port
    class SysmanLinkPort
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Connectivity port speed
        struct link_port_speed_t
        {
            uint32_t bitRate;                               ///< [out] Bits/sec that the link is operating at
            uint32_t width;                                 ///< [out] The number of lanes
            uint32_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Connectivity port properties
        struct link_port_properties_t
        {
            uint32_t portNum;                               ///< [out] The port number on the switch
            link_port_speed_t maxSpeed;                     ///< [out] Maximum bandwidth supported by the port

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Connectivity port state
        struct link_port_state_t
        {
            ze::bool_t isConnected;                         ///< [out] Indicates if the port is connected to a remote Switch
            link_port_speed_t rxSpeed;                      ///< [out] Current maximum receive speed
            link_port_speed_t txSpeed;                      ///< [out] Current maximum transmit speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Connectivity port throughput
        /// 
        /// @details
        ///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
        ///       using the equation:
        ///     -     %rx_bandwidth = 10^6 * (s2.rxCounter - s1.rxCounter) /
        ///       (s2.rxMaxBandwidth * (s2.timestamp - s1.timestamp))
        ///     -     %tx_bandwidth = 10^6 * (s2.txCounter - s1.txCounter) /
        ///       (s2.txMaxBandwidth * (s2.timestamp - s1.timestamp))
        struct link_port_throughput_t
        {
            uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when the measurement
                                                            ///< was made.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.
            uint64_t rxCounter;                             ///< [out] Monotonic counter for the number of bytes received
            uint64_t txCounter;                             ///< [out] Monotonic counter for the number of bytes transmitted
            uint32_t rxMaxBandwidth;                        ///< [out] The current maximum bandwidth in bytes/sec for receiving packats
            uint32_t txMaxBandwidth;                        ///< [out] The current maximum bandwidth in bytes/sec for transmitting
                                                            ///< packets

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Connectivity port stats counters
        /// 
        /// @details
        ///     - Percent replays is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %replay = 10^6 * (s2.replayCounter -
        ///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
        struct link_port_stats_t
        {
            uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when the measurement
                                                            ///< was made.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.
            uint64_t replayCounter;                         ///< [out] Monotonic counter for the number of replay packets
            uint64_t packetCounter;                         ///< [out] Monotonic counter for the number of packets

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_link_port_handle_t m_handle = nullptr;   ///< [in] handle of SMI object
        SysmanLinkSwitch* m_pSysmanLinkSwitch;          ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanLinkPort( void ) = delete;
        SysmanLinkPort( 
            sysman_link_port_handle_t handle,               ///< [in] handle of SMI object
            SysmanLinkSwitch* pSysmanLinkSwitch             ///< [in] pointer to owner object
            );

        ~SysmanLinkPort( void ) = default;

        SysmanLinkPort( SysmanLinkPort const& other ) = delete;
        void operator=( SysmanLinkPort const& other ) = delete;

        SysmanLinkPort( SysmanLinkPort&& other ) = delete;
        void operator=( SysmanLinkPort&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysmanlinkswitch( void ) const { return m_pSysmanLinkSwitch; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get connectivity port properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            link_port_properties_t* pProperties             ///< [in] Will contain properties of the Switch Port
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get connectivity port state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            link_port_state_t* pState                       ///< [in] Will contain the current state of the Switch Port
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get connectivity port throughput
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetThroughput(
            link_port_throughput_t* pThroughput             ///< [in] Will contain the Switch port throughput counters.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get connectivity port stats
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetStats(
            link_port_stats_t* pStats                       ///< [in] Will contain the Switch port stats.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Check if two connectivity ports are physically connected
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        IsConnected(
            SysmanLinkPort* pRemotePort,                    ///< [in] Handle of the remote connectivity port.
            ze::bool_t* pConnected                          ///< [in] Will indicate connected to the remote port.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device temperature sensor
    class SysmanTemperature
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensors
        enum class temp_sensors_t
        {
            GLOBAL = 0,                                     ///< The maximum temperature across all device sensors
            GPU,                                            ///< The maximum temperature across all sensors in the GPU
            MEMORY,                                         ///< The maximum temperature across all sensors in the local memory

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensor properties
        struct temp_properties_t
        {
            temp_sensors_t type;                            ///< [out] Which part of the device the temperature sensor measures
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_temp_handle_t m_handle = nullptr;        ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanTemperature( void ) = delete;
        SysmanTemperature( 
            sysman_temp_handle_t handle,                    ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanTemperature( void ) = default;

        SysmanTemperature( SysmanTemperature const& other ) = delete;
        void operator=( SysmanTemperature const& other ) = delete;

        SysmanTemperature( SysmanTemperature&& other ) = delete;
        void operator=( SysmanTemperature&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get temperature sensor properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            temp_properties_t* pProperties                  ///< [in] Will contain the temperature sensor properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the temperature from a specified sensor
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        Read(
            uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device power supply
    class SysmanPsu
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PSU voltage status
        enum class psu_voltage_status_t
        {
            NORMAL = 0,                                     ///< No unusual voltages have been detected
            OVER,                                           ///< Over-voltage has occurred
            UNDER,                                          ///< Under-voltage has occurred

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Static properties of the power supply
        struct psu_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can control the PSU
            ze::bool_t haveFan;                             ///< [out] True if the power supply has a fan
            uint32_t ampLimit;                              ///< [out] The maximum electrical current in amperes that can be drawn

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamic state of the power supply
        struct psu_state_t
        {
            psu_voltage_status_t voltStatus;                ///< [out] The current PSU voltage status
            ze::bool_t fanFailed;                           ///< [out] Indicates if the fan has failed
            uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees celcius
            uint32_t current;                               ///< [out] The amps being drawn in amperes

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_psu_handle_t m_handle = nullptr;         ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanPsu( void ) = delete;
        SysmanPsu( 
            sysman_psu_handle_t handle,                     ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanPsu( void ) = default;

        SysmanPsu( SysmanPsu const& other ) = delete;
        void operator=( SysmanPsu const& other ) = delete;

        SysmanPsu( SysmanPsu&& other ) = delete;
        void operator=( SysmanPsu&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power supply properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            psu_properties_t* pProperties                   ///< [in] Will contain the properties of the power supply.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current power supply state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            psu_state_t* pState                             ///< [in] Will contain the current state of the power supply.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device fan
    class SysmanFan
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan resource speed mode
        enum class fan_speed_mode_t
        {
            DEFAULT = 0,                                    ///< The fan speed is operating using the hardware default settings
            FIXED,                                          ///< The fan speed is currently set to a fixed value
            TABLE,                                          ///< The fan speed is currently controlled dynamically by hardware based on
                                                            ///< a temp/speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan speed units
        enum class fan_speed_units_t
        {
            RPM = 0,                                        ///< The fan speed is in units of revolutions per minute (rpm)
            PERCENT,                                        ///< The fan speed is a percentage of the maximum speed of the fan

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan temperature/speed pair
        struct fan_temp_speed_t
        {
            uint32_t temperature;                           ///< [in,out] Temperature in degrees celcius
            uint32_t speed;                                 ///< [in,out] The speed of the fan
            fan_speed_units_t units;                        ///< [in,out] The units of the member speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan properties
        struct fan_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can control the fan speed
            uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan
            uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan configuration
        struct fan_config_t
        {
            fan_speed_mode_t mode;                          ///< [in,out] The fan speed mode (fixed, temp-speed table)
            uint32_t speed;                                 ///< [in,out] The fixed fan speed setting
            fan_speed_units_t speedUnits;                   ///< [in,out] The units of the fixed fan speed setting
            uint32_t numPoints;                             ///< [in,out] The number of valid points in the fan speed table
            fan_temp_speed_t table[ZET_FAN_TEMP_SPEED_PAIR_COUNT];  ///< [in,out] Array of temperature/fan speed pairs

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan state
        struct fan_state_t
        {
            fan_speed_mode_t mode;                          ///< [out] The fan speed mode (default, fixed, temp-speed table)
            fan_speed_units_t speedUnits;                   ///< [out] The units of the fan speed
            uint32_t speed;                                 ///< [out] The current fan speed

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_fan_handle_t m_handle = nullptr;         ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanFan( void ) = delete;
        SysmanFan( 
            sysman_fan_handle_t handle,                     ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanFan( void ) = default;

        SysmanFan( SysmanFan const& other ) = delete;
        void operator=( SysmanFan const& other ) = delete;

        SysmanFan( SysmanFan&& other ) = delete;
        void operator=( SysmanFan&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get fan properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            fan_properties_t* pProperties                   ///< [in] Will contain the properties of the fan.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current fan configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetConfig(
            fan_config_t* pConfig                           ///< [in] Will contain the current configuration of the fan.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set fan configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetConfig(
            const fan_config_t* pConfig                     ///< [in] New fan configuration.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current state of a fan - current mode and speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            fan_speed_units_t units,                        ///< [in] The units in which the fan speed should be returned.
            fan_state_t* pState                             ///< [in] Will contain the current state of the fan.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device LED
    class SysmanLed
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED properties
        struct led_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can control the LED
            ze::bool_t haveRGB;                             ///< [out] Indicates if the LED is RGB capable

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED state
        struct led_state_t
        {
            ze::bool_t isOn;                                ///< [in,out] Indicates if the LED is on or off
            uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
            uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
            uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_led_handle_t m_handle = nullptr;         ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanLed( void ) = delete;
        SysmanLed( 
            sysman_led_handle_t handle,                     ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanLed( void ) = default;

        SysmanLed( SysmanLed const& other ) = delete;
        void operator=( SysmanLed const& other ) = delete;

        SysmanLed( SysmanLed&& other ) = delete;
        void operator=( SysmanLed&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get LED properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            led_properties_t* pProperties                   ///< [in] Will contain the properties of the LED.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current state of a LED - on/off, color
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            led_state_t* pState                             ///< [in] Will contain the current state of the LED.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set state of a LED - on/off, color
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetState(
            const led_state_t* pState                       ///< [in] New state of the LED.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device RAS error set
    class SysmanRas
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error type
        enum class ras_error_type_t
        {
            CORRECTABLE = 0,                                ///< Errors were corrected by hardware
            UNCORRECTABLE,                                  ///< Error were not corrected

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS properties
        struct ras_properties_t
        {
            ras_error_type_t type;                          ///< [out] The type of RAS error
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t supported;                           ///< [out] True if RAS is supported on this device
            ze::bool_t enabled;                             ///< [out] True if RAS is enabled on this device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error details
        struct ras_details_t
        {
            uint64_t numResets;                             ///< [out] The number of device resets that have taken place
            uint64_t numProgrammingErrors;                  ///< [out] The number of hardware exceptions generated by the way workloads
                                                            ///< have programmed the hardware
            uint64_t numDriverErrors;                       ///< [out] The number of low level driver communication errors have
                                                            ///< occurred
            uint64_t numComputeErrors;                      ///< [out] The number of errors that have occurred in the compute
                                                            ///< accelerator hardware
            uint64_t numNonComputeErrors;                   ///< [out] The number of errors that have occurred in the fixed-function
                                                            ///< accelerator hardware
            uint64_t numCacheErrors;                        ///< [out] The number of errors that have occurred in caches
                                                            ///< (L1/L3/register file/shared local memory/sampler)
            uint64_t numMemoryErrors;                       ///< [out] The number of errors that have occurred in the local memory
            uint64_t numPciErrors;                          ///< [out] The number of errors that have occurred in the PCI link
            uint64_t numSwitchErrors;                       ///< [out] The number of errors that have occurred in the high-speed
                                                            ///< connectivity links
            uint64_t numDisplayErrors;                      ///< [out] The number of errors that have occurred in the display

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_ras_handle_t m_handle = nullptr;         ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanRas( void ) = delete;
        SysmanRas( 
            sysman_ras_handle_t handle,                     ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanRas( void ) = default;

        SysmanRas( SysmanRas const& other ) = delete;
        void operator=( SysmanRas const& other ) = delete;

        SysmanRas( SysmanRas&& other ) = delete;
        void operator=( SysmanRas&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get RAS properties of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            ras_properties_t* pProperties                   ///< [in] Structure describing RAS properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the number of errors of a given RAS error set
        /// 
        /// @details
        ///     - Clearing errors will affect other threads/applications - the counter
        ///       values will start from zero.
        ///     - Clearing errors requires write permissions.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetErrors(
            ze::bool_t clear,                               ///< [in] Set to 1 to clear the counters of this type
            uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
            ras_details_t* pDetails = nullptr               ///< [in][optional] Breakdown of where errors have occurred
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a SMI device diagnostic test suite
    class SysmanDiagnostics
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic test suite type
        enum class diag_type_t
        {
            SCAN = 0,                                       ///< Run SCAN diagnostics
            ARRAY,                                          ///< Run Array diagnostics

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic results
        enum class diag_result_t
        {
            NO_ERRORS = 0,                                  ///< Diagnostic completed without finding errors to repair
            ABORT,                                          ///< Diagnostic had problems running tests
            FAIL_CANT_REPAIR,                               ///< Diagnostic had problems setting up repairs
            REBOOT_FOR_REPAIR,                              ///< Diagnostics found errors, setup for repair and reboot is required to
                                                            ///< complete the process

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic test
        struct diag_test_t
        {
            uint32_t index;                                 ///< [out] Index of the test
            const char* name;                               ///< [out] Name of the test

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostics test suite properties
        struct diag_properties_t
        {
            diag_type_t type;                               ///< [out] The type of diagnostics test suite
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling SMI handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            const char* name;                               ///< [out] Name of the diagnostics test suite
            uint32_t numTests;                              ///< [out] The number of tests in the test suite
            const diag_test_t* pTests;                      ///< [out] Array of tests (size ::zet_diag_properties_t.numTests), sorted
                                                            ///< by increasing value of ::zet_diag_test_t.index

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_diag_handle_t m_handle = nullptr;        ///< [in] handle of SMI object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanDiagnostics( void ) = delete;
        SysmanDiagnostics( 
            sysman_diag_handle_t handle,                    ///< [in] handle of SMI object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanDiagnostics( void ) = default;

        SysmanDiagnostics( SysmanDiagnostics const& other ) = delete;
        void operator=( SysmanDiagnostics const& other ) = delete;

        SysmanDiagnostics( SysmanDiagnostics&& other ) = delete;
        void operator=( SysmanDiagnostics&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties of a diagnostics test suite
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            diag_properties_t* pProperties                  ///< [in] Structure describing the properties of a diagnostics test suite
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Run a diagnostics test suite, either all tests or a subset of tests.
        /// 
        /// @details
        ///     - This function will block until the diagnostics have completed.
        /// @throws result_t
        void __zecall
        RunTests(
            uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                            ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
            uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                            ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
            diag_result_t* pResult                          ///< [in] The result of the diagnostics
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_type_t to std::string
    std::string to_string( const Sysman::device_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::properties_t to std::string
    std::string to_string( const Sysman::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_mode_t to std::string
    std::string to_string( const Sysman::sched_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeout_properties_t to std::string
    std::string to_string( const Sysman::sched_timeout_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeslice_properties_t to std::string
    std::string to_string( const Sysman::sched_timeslice_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_address_t to std::string
    std::string to_string( const Sysman::pci_address_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_speed_t to std::string
    std::string to_string( const Sysman::pci_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_properties_t to std::string
    std::string to_string( const Sysman::pci_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_state_t to std::string
    std::string to_string( const Sysman::pci_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_type_t to std::string
    std::string to_string( const Sysman::pci_bar_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_properties_t to std::string
    std::string to_string( const Sysman::pci_bar_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_throughput_t to std::string
    std::string to_string( const Sysman::pci_throughput_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_stats_t to std::string
    std::string to_string( const Sysman::pci_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_properties_t to std::string
    std::string to_string( const Sysman::event_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_request_t to std::string
    std::string to_string( const Sysman::event_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_properties_t to std::string
    std::string to_string( const SysmanPower::power_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_energy_counter_t to std::string
    std::string to_string( const SysmanPower::power_energy_counter_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_energy_threshold_t to std::string
    std::string to_string( const SysmanPower::power_energy_threshold_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_sustained_limit_t to std::string
    std::string to_string( const SysmanPower::power_sustained_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_burst_limit_t to std::string
    std::string to_string( const SysmanPower::power_burst_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_peak_limit_t to std::string
    std::string to_string( const SysmanPower::power_peak_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_mode_t to std::string
    std::string to_string( const SysmanFrequency::oc_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_error_type_t to std::string
    std::string to_string( const SysmanFrequency::oc_error_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_capabilities_t to std::string
    std::string to_string( const SysmanFrequency::oc_capabilities_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_configuration_t to std::string
    std::string to_string( const SysmanFrequency::oc_configuration_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_icc_max_t to std::string
    std::string to_string( const SysmanFrequency::oc_icc_max_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_tj_max_t to std::string
    std::string to_string( const SysmanFrequency::oc_tj_max_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_domain_t to std::string
    std::string to_string( const SysmanFrequency::freq_domain_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_properties_t to std::string
    std::string to_string( const SysmanFrequency::freq_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_range_t to std::string
    std::string to_string( const SysmanFrequency::freq_range_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_reasons_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_state_t to std::string
    std::string to_string( const SysmanFrequency::freq_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_time_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_time_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_group_t to std::string
    std::string to_string( const SysmanEngine::engine_group_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_properties_t to std::string
    std::string to_string( const SysmanEngine::engine_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_stats_t to std::string
    std::string to_string( const SysmanEngine::engine_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_type_t to std::string
    std::string to_string( const SysmanStandby::standby_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_properties_t to std::string
    std::string to_string( const SysmanStandby::standby_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_promo_mode_t to std::string
    std::string to_string( const SysmanStandby::standby_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFirmware::firmware_properties_t to std::string
    std::string to_string( const SysmanFirmware::firmware_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_type_t to std::string
    std::string to_string( const SysmanMemory::mem_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_properties_t to std::string
    std::string to_string( const SysmanMemory::mem_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_bandwidth_t to std::string
    std::string to_string( const SysmanMemory::mem_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_alloc_t to std::string
    std::string to_string( const SysmanMemory::mem_alloc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkSwitch::link_switch_properties_t to std::string
    std::string to_string( const SysmanLinkSwitch::link_switch_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkSwitch::link_switch_state_t to std::string
    std::string to_string( const SysmanLinkSwitch::link_switch_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_speed_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_properties_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_state_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_throughput_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_throughput_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_stats_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_sensors_t to std::string
    std::string to_string( const SysmanTemperature::temp_sensors_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_properties_t to std::string
    std::string to_string( const SysmanTemperature::temp_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_voltage_status_t to std::string
    std::string to_string( const SysmanPsu::psu_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_properties_t to std::string
    std::string to_string( const SysmanPsu::psu_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_state_t to std::string
    std::string to_string( const SysmanPsu::psu_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_mode_t to std::string
    std::string to_string( const SysmanFan::fan_speed_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_units_t to std::string
    std::string to_string( const SysmanFan::fan_speed_units_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_temp_speed_t to std::string
    std::string to_string( const SysmanFan::fan_temp_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_properties_t to std::string
    std::string to_string( const SysmanFan::fan_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_config_t to std::string
    std::string to_string( const SysmanFan::fan_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_state_t to std::string
    std::string to_string( const SysmanFan::fan_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_properties_t to std::string
    std::string to_string( const SysmanLed::led_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_state_t to std::string
    std::string to_string( const SysmanLed::led_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_error_type_t to std::string
    std::string to_string( const SysmanRas::ras_error_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_properties_t to std::string
    std::string to_string( const SysmanRas::ras_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_details_t to std::string
    std::string to_string( const SysmanRas::ras_details_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_type_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_result_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_result_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_test_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_test_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_properties_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_properties_t val );

} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_SYSMAN_HPP
