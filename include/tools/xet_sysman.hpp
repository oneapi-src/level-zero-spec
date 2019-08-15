/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_sysman.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#ifndef _XET_SYSMAN_HPP
#define _XET_SYSMAN_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define XET_STRING_PROPERTY_SIZE  32
#endif // XET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define XET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // XET_FAN_TEMP_SPEED_PAIR_COUNT

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_EVENT_WAIT_INFINITE
/// @brief Wait infinitely for events to arrive.
#define XET_EVENT_WAIT_INFINITE  0xFFFFFFFF
#endif // XET_EVENT_WAIT_INFINITE

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_DIAG_FIRST_TEST_INDEX
/// @brief Diagnostic test index to use for the very first test.
#define XET_DIAG_FIRST_TEST_INDEX  0x0
#endif // XET_DIAG_FIRST_TEST_INDEX

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_DIAG_LAST_TEST_INDEX
/// @brief Diagnostic test index to use for the very last test.
#define XET_DIAG_LAST_TEST_INDEX  0xFFFFFFFF
#endif // XET_DIAG_LAST_TEST_INDEX

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for SMI of a device
    class Sysman
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of SMI
        enum class version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device mode
        enum class operating_mode_t
        {
            DEFAULT = 0,                                    ///< Multiple workloads are running on the device
            EXCLUSIVE_COMPUTE_PROCESS,                      ///< A single process submitting compute workloads can monopolize the
                                                            ///< accelerator resources

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency domains
        enum class freq_domain_t
        {
            GPU = 0,                                        ///< Frequency of the GPU.
            MEMORY,                                         ///< Frequency of the local memory.
            NUM,                                            ///< The total number of frequency domains.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event types
        enum class event_type_t
        {
            FREQ_THROTTLED = 0,                             ///< The frequency is being throttled
            ENERGY_THRESHOLD_CROSSED,                       ///< Interrupt from the PCU when the energy threshold is crossed.
            RAS_ERRORS,                                     ///< ECC/RAS errors
            NUM,                                            ///< The number of event types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency throttle reasons
        enum class freq_throttle_reasons_t
        {
            NONE = 0,                                       ///< frequency not throttled
            AVE_PWR_CAP = XE_BIT( 0 ),                      ///< frequency throttled due to average power excursion (PL1)
            BURST_PWR_CAP = XE_BIT( 1 ),                    ///< frequency throttled due to burst power excursion (PL2)
            CURRENT_LIMIT = XE_BIT( 2 ),                    ///< frequency throttled due to current excursion (PL4)
            THERMAL_LIMIT = XE_BIT( 3 ),                    ///< frequency throttled due to thermal excursion (T > TjMax)
            PSU_ALERT = XE_BIT( 4 ),                        ///< frequency throttled due to power supply assertion
            SW_RANGE = XE_BIT( 5 ),                         ///< frequency throttled due to software supplied frequency range
            HW_RANGE = XE_BIT( 6 ),                         ///< frequency throttled due to a sub block that has a lower frequency
                                                            ///< range when it receives clocks

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Activity components
        enum class activity_type_t
        {
            GLOBAL = 0,                                     ///< Overall activity of all accelerators on the device.
            COMPUTE,                                        ///< Activity of all compute accelerators on the device.
            MEDIA,                                          ///< Activity of all media accelerators on the device.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory resource types
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
        /// @brief Temperature sensors
        enum class temp_sensors_t
        {
            GLOBAL = 0,                                     ///< The maximum temperature across all device sensors
            GPU,                                            ///< The maximum temperature across all sensors in the GPU
            MEMORY,                                         ///< The maximum temperature across all sensors in the local memory
            NUM,                                            ///< The number of sensors

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby promotion modes
        enum class stby_promo_mode_t
        {
            DEFAULT = 0,                                    ///< Best compromise between performance and energy savings.
            NEVER,                                          ///< The device/component will never shutdown. This can improve performance
                                                            ///< but uses more energy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PSU voltage status
        enum class psu_voltage_status_t
        {
            NORMAL = 0,                                     ///< No unusual voltages have been detected
            OVER,                                           ///< Over-voltage has occurred
            UNDER,                                          ///< Under-voltage has occurred

        };

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
        /// @brief RAS error type
        enum class ras_error_type_t
        {
            CORRECTABLE = 0,                                ///< Errors were corrected by hardware
            UNCORRECTABLE,                                  ///< Error were not corrected
            NUM,                                            ///< The number of error types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic type
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
        /// @brief Device properties
        struct properties_t
        {
            xe::Driver::device_type_t type;                 ///< [out] generic device type
            uint32_t vendorId;                              ///< [out] vendorId from PCI configuration
            uint32_t deviceId;                              ///< [out] deviceId from PCI configuration
            xe::Driver::device_uuid_t uuid;                 ///< [out] Device UUID
            xe::bool_t isSubdevice;                         ///< [out] If this handle refers to a sub-device.
            uint32_t subdeviceId;                           ///< [out] sub-device id. Only valid if isSubdevice is true.
            int8_t serialNumber[XET_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
            int8_t boardNumber[XET_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
            int8_t brandName[XET_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
            int8_t modelName[XET_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
            int8_t vendorName[XET_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
            int8_t driverVersion[XET_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)
            xe::bool_t numSwitches;                         ///< [out] The number of switches on the device
            uint32_t numFirmwares;                          ///< [out] Number of firmwares that can be managed
            uint32_t numPsus;                               ///< [out] Number of power supply units that can be managed
            uint32_t numFans;                               ///< [out] Number of fans that can be managed
            uint32_t numLeds;                               ///< [out] Number of LEDs that can be managed
            xe::bool_t supportedEvents[static_cast<int>(event_type_t::NUM)];///< [out] Set to true for the events that are supported

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Properties related to device power settings
        struct power_properties_t
        {
            xe::bool_t canControl;                          ///< [out] Software can change the power limits.
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
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
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
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
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
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

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
            xe::bool_t canControl;                          ///< [out] Indicates if software can control the frequency of this domain
            xe::bool_t canOverclock;                        ///< [out] Indicates if software can overclock this frequency domain
            double min;                                     ///< [out] The minimum clock frequency in units of MHz
            double max;                                     ///< [out] The maximum clock frequency in units of MHz
            double step;                                    ///< [out] The step clock frequency in units of MHz
            uint32_t num;                                   ///< [out] The number of clocks in the array pClocks
            const double* pClocks;                          ///< [out] Array of clock frequencies in units of MHz ordered from smallest
                                                            ///< to largest.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency limits between which the hardware can operate.
        struct freq_limits_t
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
                                                            ///< (Bitfield of (1<<::xet_freq_throttle_reasons_t)).

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

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Activity counters
        /// 
        /// @details
        ///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %util = (s2.activeTime - s1.activeTime) /
        ///       (s2.timestamp - s1.timestamp)
        struct activity_stats_t
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

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory properties
        struct mem_properties_t
        {
            mem_type_t type;                                ///< [out] The memory type
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
        /// @brief Switch properties
        struct switch_properties_t
        {
            uint32_t numPorts;                              ///< [out] The number of ports
            xe::bool_t onSubdevice;                         ///< [out] True if the switch is located on a sub-device; false means that
                                                            ///< the switch is on the device of the calling SMI handle
            xe::Driver::device_uuid_t subdeviceUuid;        ///< [out] If onSubdevice is true, this gives the UUID of the sub-device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Switch state
        struct switch_state_t
        {
            xe::bool_t enabled;                             ///< [out] Indicates if the switch is enabled/disabled

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Switch port speed
        struct switch_port_speed_t
        {
            uint32_t bitRate;                               ///< [out] Bits/sec that the link is operating at
            uint32_t width;                                 ///< [out] The number of lanes
            uint32_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Switch Port properties
        struct switch_port_properties_t
        {
            switch_port_speed_t maxSpeed;                   ///< [out] Maximum bandwidth supported by the port

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Switch Port state
        struct switch_port_state_t
        {
            xe::bool_t isConnected;                         ///< [out] Indicates if the port is connected to a remote Switch
            xe::Driver::device_uuid_t remoteDeviceUuid;     ///< [out] If connected is true, this gives the device UUID where the port
                                                            ///< connects
            uint32_t remoteDeviceSwitchIndex;               ///< [out] If connected is true, this gives the switch index on the remote
                                                            ///< device where the port connects
            uint32_t remoteSwitchPortIndex;                 ///< [out] If connected is true, this gives the port index on the remote
                                                            ///< switch
            switch_port_speed_t rxSpeed;                    ///< [out] Current maximum receive speed
            switch_port_speed_t txSpeed;                    ///< [out] Current maximum transmit speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Switch Port throughput
        /// 
        /// @details
        ///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
        ///       using the equation:
        ///     -     %rx_bandwidth = 10^6 * (s2.rxCounter - s1.rxCounter) /
        ///       (s2.rxMaxBandwidth * (s2.timestamp - s1.timestamp))
        ///     -     %tx_bandwidth = 10^6 * (s2.txCounter - s1.txCounter) /
        ///       (s2.txMaxBandwidth * (s2.timestamp - s1.timestamp))
        struct switch_port_throughput_t
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
        /// @brief Switch Port stats counters
        /// 
        /// @details
        ///     - Percent replays is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %replay = 10^6 * (s2.replayCounter -
        ///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
        struct switch_port_stats_t
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
        /// @brief Firmware properties
        struct firmware_properties_t
        {
            xe::bool_t canControl;                          ///< [out] Indicates if software can flash the firmware
            int8_t name[XET_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
            int8_t version[XET_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Static properties of the power supply
        struct psu_properties_t
        {
            xe::bool_t canControl;                          ///< [out] Indicates if software can control the PSU
            xe::bool_t haveFan;                             ///< [out] True if the power supply has a fan
            uint32_t ampLimit;                              ///< [out] The maximum electrical current in amperes that can be drawn

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamic state of the power supply
        struct psu_state_t
        {
            psu_voltage_status_t voltStatus;                ///< [out] The current PSU voltage status
            xe::bool_t fanFailed;                           ///< [out] Indicates if the fan has failed
            uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees celcius
            uint32_t current;                               ///< [out] The amps being drawn in amperes

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
            xe::bool_t canControl;                          ///< [out] Indicates if software can control the fan speed
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
            fan_temp_speed_t table[XET_FAN_TEMP_SPEED_PAIR_COUNT];  ///< [in,out] Array of temperature/fan speed pairs

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan state
        struct fan_state_t
        {
            fan_speed_mode_t mode;                          ///< [out] The fan speed mode (default, fixed, temp-speed table)
            fan_speed_units_t speedUnits;                   ///< [out] The units of the fan speed
            uint32_t speed;                                 ///< [out] The current fan speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED properties
        struct led_properties_t
        {
            xe::bool_t canControl;                          ///< [out] Indicates if software can control the LED
            xe::bool_t haveRGB;                             ///< [out] Indicates if the LED is RGB capable

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED state
        struct led_state_t
        {
            xe::bool_t isOn;                                ///< [in,out] Indicates if the LED is on or off
            uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
            uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
            uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS properties
        struct ras_properties_t
        {
            xe::bool_t supported;                           ///< [out] True if RAS is supported on this device
            xe::bool_t enabled;                             ///< [out] True if RAS is enabled on this device
            xe::bool_t repaired;                            ///< [out] True if the device has been repaired

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error details
        struct ras_details_t
        {
            uint64_t numResets;                             ///< [out] The number of accelerator resets that have taken place
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
            uint64_t numSwitchErrors;                       ///< [out] The number of errors that have occurred in the P2P links
            uint64_t numDisplayErrors;                      ///< [out] The number of errors that have occurred in the display

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

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic test
        struct diag_test_t
        {
            uint32_t index;                                 ///< [out] Index of the test
            const char* name;                               ///< [out] Name of the test

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief List of all diagnostic tests of a given type ::xet_diag_type_t
        struct diag_test_list_t
        {
            diag_type_t type;                               ///< [out] The type of tests
            uint32_t count;                                 ///< [out] The number of tests in the array pTests
            diag_test_t* pTests;                            ///< [out] Array of tests, sorted by increasing value of
                                                            ///< ::xet_diag_test_t.index

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
        static Sysman* __xecall
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
        void __xecall
        DeviceGetProperties(
            properties_t* pProperties                       ///< [in] Structure that will contain information about the device.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get operating mode of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        DeviceGetOperatingMode(
            operating_mode_t* pMode                         ///< [in] The current operating mode of the device.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set operating mode of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        DeviceSetOperatingMode(
            operating_mode_t pMode                          ///< [in] The new operating mode of the device.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset device
        /// @throws result_t
        void __xecall
        DeviceReset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties related to power
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        PowerGetProperties(
            power_properties_t* pProperties                 ///< [in] Structure that will contain property data.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get energy counter
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        PowerGetEnergyCounter(
            power_energy_counter_t* pEnergy                 ///< [in] Will contain the latest snapshot of the energy counter and
                                                            ///< timestamp when the last counter value was measured.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get energy threshold
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - power_energy_threshold_t: The current energy threshold value in joules.
        /// 
        /// @throws result_t
        power_energy_threshold_t __xecall
        PowerGetEnergyThreshold(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set energy threshold
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        PowerSetEnergyThreshold(
            power_energy_threshold_t* pThreshold            ///< [in] The energy threshold to be set in joules.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        PowerGetLimits(
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
        void __xecall
        PowerSetLimits(
            const power_sustained_limit_t* pSustained = nullptr,///< [in][optional] The sustained power limit.
            const power_burst_limit_t* pBurst = nullptr,    ///< [in][optional] The burst power limit.
            const power_peak_limit_t* pPeak = nullptr       ///< [in][optional] The peak power limit.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency properties - available frequencies
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FrequencyGetProperties(
            freq_domain_t domain,                           ///< [in] The frequency domain.
            freq_properties_t* pProperties                  ///< [in] The frequency properties for the specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current frequency limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FrequencyGetLimits(
            freq_domain_t domain,                           ///< [in] The frequency domain.
            freq_limits_t* pLimits                          ///< [in] The limits between which the hardware can operate for the
                                                            ///< specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set frequency limits between which the hardware can operate.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FrequencySetLimits(
            freq_domain_t domain,                           ///< [in] The frequency domain.
            const freq_limits_t* pLimits                    ///< [in] The limits between which the hardware can operate for the
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
        void __xecall
        FrequencyGetState(
            freq_domain_t domain,                           ///< [in] The frequency domain.
            freq_state_t* pState                            ///< [in] Frequency state for the specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency throttle time
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FrequencyGetThrottleTime(
            freq_domain_t domain,                           ///< [in] The frequency domain.
            freq_throttle_time_t* pThrottleTime             ///< [in] Will contain a snapshot of the throttle time counters for the
                                                            ///< specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the activity counters of a part of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        ActivityGetStats(
            activity_type_t type,                           ///< [in] The type of activity stats.
            activity_stats_t* pStats                        ///< [in] Will contain a snapshot of the activity counters.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        MemoryGetProperties(
            mem_properties_t* pProperties                   ///< [in] Will contain memory properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory bandwidth
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        MemoryGetBandwidth(
            mem_bandwidth_t* pBandwidth                     ///< [in] Will contain a snapshot of the bandwidth counters.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        MemoryGetAllocated(
            mem_alloc_t* pAllocated                         ///< [in] Will contain the current allocated memory.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PCI properties - address, max speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
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
        void __xecall
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
        void __xecall
        PciGetBarProperties(
            uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::xet_pci_properties_t.numBars -
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
        void __xecall
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
        void __xecall
        PciGetStats(
            pci_stats_t* pStats                             ///< [in] Will contain a snapshot of the latest stats.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Switch properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SwitchGetProperties(
            uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                            ///< [::xet_sysman_properties_t.numSwitches - 1]).
            switch_properties_t* pProperties                ///< [in] Will contain the Switch properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Switch state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SwitchGetState(
            uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                            ///< [::xet_sysman_properties_t.numSwitches - 1]).
            switch_state_t* pState                          ///< [in] Will contain the current state of the switch (enabled/disabled).
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set Switch state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SwitchSetState(
            uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                            ///< [::xet_sysman_properties_t.numSwitches - 1]).
            xe::bool_t enable                               ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Switch Port properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SwitchPortGetProperties(
            uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                            ///< [::xet_sysman_properties_t.numSwitches - 1]).
            uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                            ///< - 1]).
            switch_port_properties_t* pProperties           ///< [in] Will contain properties of the Switch Port
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Switch Port state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SwitchPortGetState(
            uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                            ///< [::xet_sysman_properties_t.numSwitches - 1]).
            uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                            ///< - 1]).
            switch_port_state_t* pState                     ///< [in] Will contain the current state of the Switch Port
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Switch Port throughput
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SwitchPortGetThroughput(
            uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                            ///< [::xet_sysman_properties_t.numSwitches - 1]).
            uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                            ///< - 1]).
            switch_port_throughput_t* pThroughput           ///< [in] Will contain the Switch port throughput counters.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Switch Port stats
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SwitchPortGetStats(
            uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                            ///< [::xet_sysman_properties_t.numSwitches - 1]).
            uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                            ///< - 1]).
            switch_port_stats_t* pStats                     ///< [in] Will contain the Switch port stats.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the temperature from a specified sensor
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        TemperatureGet(
            temp_sensors_t sensor,                          ///< [in] The port address.
            uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the current standby promotion mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        StandbyGetMode(
            stby_promo_mode_t* pMode                        ///< [in] Will contain the current standby mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set standby promotion mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        StandbySetMode(
            stby_promo_mode_t mode                          ///< [in] New standby mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FirmwareGetProperties(
            uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                            ///< [::xet_sysman_properties_t.numFirmwares - 1]).
            firmware_properties_t* pProperties              ///< [in] Pointer to an array that will hold the properties of the firmware
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware checksum
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FirmwareGetChecksum(
            uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                            ///< [::xet_sysman_properties_t.numFirmwares - 1]).
            uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Flash a new firmware image
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FirmwareFlash(
            uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                            ///< [::xet_sysman_properties_t.numFirmwares - 1]).
            void* pImage,                                   ///< [in] Image of the new firmware to flash.
            uint32_t size                                   ///< [in] Size of the flash image.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power supply properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        PsuGetProperties(
            uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ...
                                                            ///< [::xet_sysman_properties_t.numPsus - 1]).
            psu_properties_t* pProperties                   ///< [in] Will contain the properties of the power supply.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current power supply state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        PsuGetState(
            uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ...
                                                            ///< [::xet_sysman_properties_t.numPsus - 1]).
            psu_state_t* pState                             ///< [in] Will contain the current state of the power supply.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get fan properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FanGetProperties(
            uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                            ///< 1]).
            fan_properties_t* pProperties                   ///< [in] Will contain the properties of the fan.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current fan configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FanGetConfig(
            uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                            ///< 1]).
            fan_config_t* pConfig                           ///< [in] Will contain the current configuration of the fan.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set fan configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FanSetConfig(
            uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                            ///< 1]).
            const fan_config_t* pConfig                     ///< [in] New fan configuration.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current state of a fan - current mode and speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        FanGetState(
            uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                            ///< 1]).
            fan_speed_units_t units,                        ///< [in] The units in which the fan speed should be returned.
            fan_state_t* pState                             ///< [in] Will contain the current state of the fan.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get LED properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        LedGetProperties(
            uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                            ///< 1]).
            led_properties_t* pProperties                   ///< [in] Will contain the properties of the LED.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current state of a LED - on/off, color
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        LedGetState(
            uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                            ///< 1]).
            led_state_t* pState                             ///< [in] Will contain the current state of the LED.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set state of a LED - on/off, color
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        LedSetState(
            uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                            ///< 1]).
            const led_state_t* pState                       ///< [in] New state of the LED.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get RAS properties of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        RasGetProperties(
            ras_properties_t* pProperties                   ///< [in] Structure describing RAS properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the number of errors of a given type
        /// 
        /// @details
        ///     - Clearing errors will affect other threads/applications - the counter
        ///       values will start from zero.
        ///     - Clearing errors requires write permissions.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        RasGetErrors(
            ras_error_type_t type,                          ///< [in] The type of errors
            xe::bool_t clear,                               ///< [in] Set to 1 to clear the counters of this type
            uint64_t* pTotalErrors,                         ///< [in] The number total number of errors of the given type that have
                                                            ///< occurred
            ras_details_t* pDetails = nullptr               ///< [in][optional] Breakdown of where errors have occurred
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
        void __xecall
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
        void __xecall
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
        ///       ::XET_EVENT_WAIT_INFINITE. Then call this function for each device
        ///       with clear = true and timeout = 0.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __xecall
        EventsListen(
            Sysman* pSysman,                                ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                            ///< device for which the application has registered to receive
                                                            ///< notifications.
            xe::bool_t clear,                               ///< [in] Clear the event status.
            uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                            ///< check status and return immediately. Set to ::XET_EVENT_WAIT_INFINITE
                                                            ///< to block until events arrive.
            uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                            ///< triggered.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get diagnostic tests
        /// 
        /// @details
        ///     - Tests are returned in order of increasing index.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        DiagnosticsGetTestList(
            diag_type_t type,                               ///< [in] Type of diagnostic to run
            const diag_test_list_t** ppTests                ///< [in] Returns a constant pointer to the list of diagnostic tests
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Run diagnostics
        /// 
        /// @details
        ///     - This function will block until the diagnostics have completed.
        /// @throws result_t
        void __xecall
        DiagnosticsRunTests(
            diag_type_t type,                               ///< [in] Type of diagnostic to run
            uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                            ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
            uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                            ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
            diag_result_t* pResult                          ///< [in] The result of the diagnostics
            );

    };

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::operating_mode_t to std::string
    std::string to_string( const Sysman::operating_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_domain_t to std::string
    std::string to_string( const Sysman::freq_domain_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::properties_t to std::string
    std::string to_string( const Sysman::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::power_properties_t to std::string
    std::string to_string( const Sysman::power_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::power_energy_counter_t to std::string
    std::string to_string( const Sysman::power_energy_counter_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::power_energy_threshold_t to std::string
    std::string to_string( const Sysman::power_energy_threshold_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::power_sustained_limit_t to std::string
    std::string to_string( const Sysman::power_sustained_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::power_burst_limit_t to std::string
    std::string to_string( const Sysman::power_burst_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::power_peak_limit_t to std::string
    std::string to_string( const Sysman::power_peak_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_properties_t to std::string
    std::string to_string( const Sysman::freq_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_limits_t to std::string
    std::string to_string( const Sysman::freq_limits_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_throttle_reasons_t to std::string
    std::string to_string( const Sysman::freq_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_state_t to std::string
    std::string to_string( const Sysman::freq_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_throttle_time_t to std::string
    std::string to_string( const Sysman::freq_throttle_time_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::activity_type_t to std::string
    std::string to_string( const Sysman::activity_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::activity_stats_t to std::string
    std::string to_string( const Sysman::activity_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_type_t to std::string
    std::string to_string( const Sysman::mem_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_properties_t to std::string
    std::string to_string( const Sysman::mem_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_bandwidth_t to std::string
    std::string to_string( const Sysman::mem_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_alloc_t to std::string
    std::string to_string( const Sysman::mem_alloc_t val );

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
    /// @brief Converts Sysman::switch_properties_t to std::string
    std::string to_string( const Sysman::switch_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::switch_state_t to std::string
    std::string to_string( const Sysman::switch_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::switch_port_speed_t to std::string
    std::string to_string( const Sysman::switch_port_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::switch_port_properties_t to std::string
    std::string to_string( const Sysman::switch_port_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::switch_port_state_t to std::string
    std::string to_string( const Sysman::switch_port_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::switch_port_throughput_t to std::string
    std::string to_string( const Sysman::switch_port_throughput_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::switch_port_stats_t to std::string
    std::string to_string( const Sysman::switch_port_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_sensors_t to std::string
    std::string to_string( const Sysman::temp_sensors_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::stby_promo_mode_t to std::string
    std::string to_string( const Sysman::stby_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_properties_t to std::string
    std::string to_string( const Sysman::firmware_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_voltage_status_t to std::string
    std::string to_string( const Sysman::psu_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_properties_t to std::string
    std::string to_string( const Sysman::psu_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_state_t to std::string
    std::string to_string( const Sysman::psu_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_speed_mode_t to std::string
    std::string to_string( const Sysman::fan_speed_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_speed_units_t to std::string
    std::string to_string( const Sysman::fan_speed_units_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_temp_speed_t to std::string
    std::string to_string( const Sysman::fan_temp_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_properties_t to std::string
    std::string to_string( const Sysman::fan_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_config_t to std::string
    std::string to_string( const Sysman::fan_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_state_t to std::string
    std::string to_string( const Sysman::fan_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_properties_t to std::string
    std::string to_string( const Sysman::led_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_state_t to std::string
    std::string to_string( const Sysman::led_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_properties_t to std::string
    std::string to_string( const Sysman::ras_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_type_t to std::string
    std::string to_string( const Sysman::ras_error_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_details_t to std::string
    std::string to_string( const Sysman::ras_details_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_request_t to std::string
    std::string to_string( const Sysman::event_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_type_t to std::string
    std::string to_string( const Sysman::diag_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_result_t to std::string
    std::string to_string( const Sysman::diag_result_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_test_t to std::string
    std::string to_string( const Sysman::diag_test_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_test_list_t to std::string
    std::string to_string( const Sysman::diag_test_list_t val );

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_SYSMAN_HPP
