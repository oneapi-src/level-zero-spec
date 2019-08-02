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
#ifndef XET_RAS_FILTER_ALL_COUNTERS
/// @brief Filter to get all RAS error counters
#define XET_RAS_FILTER_ALL_COUNTERS  { XET_RESID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 0 }
#endif // XET_RAS_FILTER_ALL_COUNTERS

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_RAS_FILTER_ALL_ERRORS
/// @brief Filter to get all RAS error counters that have errors
#define XET_RAS_FILTER_ALL_ERRORS  { XET_RESID_ANY, (uint32_t)XET_RAS_ERROR_TYPE_ALL, (uint32_t)XET_RAS_ERROR_LOC_ALL, 1 }
#endif // XET_RAS_FILTER_ALL_ERRORS

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
    /// @brief C++ wrapper for SMI of a device group
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
        /// @brief Resource types
        enum class resource_type_t
        {
            DEV = 0x0,                                      ///< Inventory resource
            PWR = 0x1,                                      ///< Power domain resource
            FREQ = 0x2,                                     ///< Frequency domain resource
            UTIL = 0x3,                                     ///< Resource used to monitor GPU utilization
            MEM = 0x4,                                      ///< Memory resource
            LINK = 0x5,                                     ///< Link resource
            TEMP = 0x6,                                     ///< Temperature sensor resource
            STBY = 0x7,                                     ///< Resource used to control standby mode
            FW = 0x8,                                       ///< Firmware resource
            PSU = 0x9,                                      ///< PSU resource
            FAN = 0xA,                                      ///< Fan resource
            LED = 0xB,                                      ///< LED resource
            ANY = -1,                                       ///< Any resource filter

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource ID
        /// 
        /// @details
        ///     - Every resource in the system has a unique identify.
        ///     - Resource IDs will always have the same value between versions of the
        ///       API.
        ///     - Never assume that resources of the same type have numerically
        ///       sequential values.
        ///     - The resource ID has the resource type (::xet_resource_type_t) in the
        ///       upper 16 bits.
        enum class resid_t
        {
            DEV_INVENTORY = 0,                              ///< General device inventory
            PWR_TOTAL = 0x10000,                            ///< Device total power
            FREQ_GPU = 0x20000,                             ///< GPU frequency
            FREQ_LOCAL_MEM = 0x20001,                       ///< Local memory frequency
            UTIL_GPU = 0x30000,                             ///< Utilization of the entire GPU
            UTIL_COMPUTE = 0x30001,                         ///< Utilization of the compute/3D units
            UTIL_MEDIA = 0x30002,                           ///< Utilization of the media units
            UTIL_VIDEO_DECODE = 0x30003,                    ///< Utilization of the video decode units
            UTIL_VIDEO_ENCODE = 0x30004,                    ///< Utilization of the video encode units
            MEM_LOCAL = 0x40000,                            ///< Local GPU memory
            LINK_PCIE = 0x50000,                            ///< PCIe link
            LINK_CD_PORT1 = 0x50001,                        ///< High speed companion die switch port 1
            LINK_CD_PORT2 = 0x50002,                        ///< High speed companion die switch port 2
            LINK_CD_PORT3 = 0x50003,                        ///< High speed companion die switch port 3
            LINK_CD_PORT4 = 0x50004,                        ///< High speed companion die switch port 4
            LINK_CD_PORT5 = 0x50005,                        ///< High speed companion die switch port 5
            LINK_CD_PORT6 = 0x50006,                        ///< High speed companion die switch port 6
            LINK_CD_PORT7 = 0x50007,                        ///< High speed companion die switch port 7
            LINK_CD_PORT8 = 0x50008,                        ///< High speed companion die switch port 8
            LINK_CD_PORT9 = 0x50009,                        ///< High speed companion die switch port 9
            LINK_CD_PORT10 = 0x5000A,                       ///< High speed companion die switch port 10
            LINK_CD_PORT11 = 0x5000B,                       ///< High speed companion die switch port 11
            LINK_CD_PORT12 = 0x5000C,                       ///< High speed companion die switch port 12
            LINK_CD_PORT13 = 0x5000D,                       ///< High speed companion die switch port 13
            LINK_CD_PORT14 = 0x5000E,                       ///< High speed companion die switch port 14
            LINK_CD_PORT15 = 0x5000F,                       ///< High speed companion die switch port 15
            LINK_CD_PORT16 = 0x50010,                       ///< High speed companion die switch port 16
            TEMP_MAX = 0x60000,                             ///< The maximum temperature reported by the sensors in the device
            TEMP_GPU = 0x60001,                             ///< The maximum temperature reported by the sensors in the GPU component
                                                            ///< of the device
            TEMP_LOCAL_MEM = 0x60002,                       ///< The maximum temperature reported by the sensors in the local memory of
                                                            ///< device
            STBY_GLOBAL = 0x70000,                          ///< Control sleep promotion of the common parts of the device
            STBY_COMPUTE = 0x70001,                         ///< Control sleep promotion of the compute components of the GPU
            STBY_MEDIA = 0x70002,                           ///< Control sleep promotion of the media components of the GPU
            FW_1 = 0x80001,                                 ///< Firmware 1
            FW_2 = 0x80002,                                 ///< Firmware 2
            FW_3 = 0x80003,                                 ///< Firmware 3
            FW_4 = 0x80004,                                 ///< Firmware 4
            FW_5 = 0x80005,                                 ///< Firmware 5
            FW_6 = 0x80006,                                 ///< Firmware 6
            FW_7 = 0x80007,                                 ///< Firmware 7
            FW_8 = 0x80008,                                 ///< Firmware 8
            FW_9 = 0x80009,                                 ///< Firmware 9
            FW_10 = 0x8000A,                                ///< Firmware 10
            FW_11 = 0x8000B,                                ///< Firmware 11
            FW_12 = 0x8000C,                                ///< Firmware 12
            FW_13 = 0x8000D,                                ///< Firmware 13
            FW_14 = 0x8000E,                                ///< Firmware 14
            FW_15 = 0x8000F,                                ///< Firmware 15
            FW_16 = 0x80010,                                ///< Firmware 16
            FW_17 = 0x80011,                                ///< Firmware 17
            FW_18 = 0x80012,                                ///< Firmware 18
            FW_19 = 0x80013,                                ///< Firmware 19
            FW_20 = 0x80014,                                ///< Firmware 20
            PSU_MAIN = 0x90000,                             ///< Primary power supply
            PSU_AUX = 0x90001,                              ///< Auxilary power supply
            PSU_1 = 0x90002,                                ///< Power supply 1
            PSU_2 = 0x90003,                                ///< Power supply 2
            FAN_MAIN = 0xA0000,                             ///< The main fan
            FAN_1 = 0xA0001,                                ///< Fan 1
            FAN_2 = 0xA0002,                                ///< Fan 2
            FAN_3 = 0xA0003,                                ///< Fan 3
            LED_MAIN = 0xB0000,                             ///< The main LED
            LED_1 = 0xB0001,                                ///< LED 1
            LED_2 = 0xB0002,                                ///< LED 1
            LED_3 = 0xB0003,                                ///< LED 1
            ANY = -1,                                       ///< Any resource ID

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource properties
        /// 
        /// @details
        ///     - For every property, there is a corresponding structure used to hold
        ///       the property data. The type of the data structure is derived from the
        ///       property enumerator, converted to lower-case with '_t' appended.
        ///     - Properties can be either read-only (ro), write-only (wo) or read-write
        ///       (rw).
        ///     - Properties can be either static or dynamic. Static properties are set
        ///       during initialization and will not change during the lifetime of the
        ///       application. Dynamic properties can change at any time and should be
        ///       reread.
        enum class resprop_t
        {
            DEV_SERIAL_NUMBER = 0x00000,                    ///< (ro static) The serial number of the device (data:
                                                            ///< ::xet_resprop_dev_serial_number_t)
            DEV_BOARD_NUMBER = 0x00001,                     ///< (ro static) The board number of the device (data:
                                                            ///< ::xet_resprop_dev_board_number_t)
            DEV_BRAND = 0x00002,                            ///< (ro static) The brand name of the device (data:
                                                            ///< ::xet_resprop_dev_brand_t)
            DEV_MODEL = 0x00003,                            ///< (ro static) The model name of the device (data:
                                                            ///< ::xet_resprop_dev_model_t)
            DEV_DEVICEID = 0x00004,                         ///< (ro static) The device ID of the device (data:
                                                            ///< ::xet_resprop_dev_deviceid_t)
            DEV_VENDOR_NAME = 0x00005,                      ///< (ro static) The vendor name of the device (data:
                                                            ///< ::xet_resprop_dev_vendor_name_t)
            DEV_DRIVER_VERSION = 0x00006,                   ///< (ro static) The driver version associated with the device (data:
                                                            ///< ::xet_resprop_dev_driver_version_t)
            DEV_BARS = 0x00007,                             ///< (ro static) The bars configured for the device (data:
                                                            ///< ::xet_resprop_dev_bars_t)
            PWR_MAX_LIMIT = 0x10000,                        ///< (ro static) The maximum power limit that can be requested (data:
                                                            ///< ::xet_resprop_pwr_max_limit_t)
            PWR_ENERGY_COUNTER = 0x10001,                   ///< (ro dynamic) The value of the monotonic energy counter (data:
                                                            ///< ::xet_resprop_pwr_energy_counter_t)
            PWR_SUSTAINED_LIMIT = 0x10002,                  ///< (rw dynamic) The sustained power limit (data:
                                                            ///< ::xet_resprop_pwr_sustained_limit_t)
            PWR_BURST_LIMIT = 0x10003,                      ///< (rw dynamic) The burst power limit (data:
                                                            ///< ::xet_resprop_pwr_burst_limit_t)
            PWR_PEAK_LIMIT = 0x10004,                       ///< (rw dynamic) The peak power limit (data:
                                                            ///< ::xet_resprop_pwr_peak_limit_t)
            FREQ_AVAIL_CLOCKS = 0x20000,                    ///< (ro static) Available frequency clocks that this domain can run at
                                                            ///< (data: ::xet_resprop_freq_avail_clocks_t)
            FREQ_RANGE = 0x20001,                           ///< (rw dynamic) The current frequency range (data:
                                                            ///< ::xet_resprop_freq_range_t)
            FREQ_REQUESTED_FREQ = 0x20002,                  ///< (ro dynamic) The current frequency request (data:
                                                            ///< ::xet_resprop_freq_requested_freq_t)
            FREQ_TDP_FREQ = 0x20003,                        ///< (ro dynamic) The maximum frequency supported under the current TDP
                                                            ///< conditions (data: ::xet_resprop_freq_tdp_freq_t)
            FREQ_EFFICIENT_FREQ = 0x20004,                  ///< (ro dynamic) The efficient minimum frequency (data:
                                                            ///< ::xet_resprop_freq_efficient_freq_t)
            FREQ_RESOLVED_FREQ = 0x20005,                   ///< (ro dynamic) The resolved frequency (data:
                                                            ///< ::xet_resprop_freq_resolved_freq_t)
            FREQ_THROTTLE_REASONS = 0x20006,                ///< (ro dynamic) The reasons that the frequency is being limited by the
                                                            ///< PCU (data: ::xet_resprop_freq_throttle_reasons_t)
            FREQ_THROTTLE_TIME = 0x20007,                   ///< (ro dynamic) The total time that the frequency has been limited by the
                                                            ///< PCU (data: ::xet_resprop_freq_throttle_time_t)
            UTIL_COUNTERS = 0x30000,                        ///< (ro dynamic) The total wall time this resource is active (data:
                                                            ///< ::xet_resprop_util_counters_t)
            MEM_TYPE = 0x40000,                             ///< (ro static) The type of memory covered by this resource (data:
                                                            ///< ::xet_resprop_mem_type_t)
            MEM_UTILIZATION = 0x40001,                      ///< (ro dynamic) Get current allocated/unallocated size (data:
                                                            ///< ::xet_resprop_mem_utilization_t)
            MEM_BANDWIDTH = 0x40002,                        ///< (ro dynamic) Get current read/write bandwidth counters and maximum
                                                            ///< bandwidth (data: ::xet_resprop_mem_bandwidth_t)
            LINK_TYPE = 0x50000,                            ///< (ro static) The type of link (data: ::xet_resprop_link_type_t)
            LINK_BUS_ADDRESS = 0x50001,                     ///< (ro static) The bus address of the link (data:
                                                            ///< ::xet_resprop_link_bus_address_t)
            LINK_PEER_DEVICE = 0x50002,                     ///< (ro static) For links of type ::XET_LINK_TYPE_CD_PORT, this gives the
                                                            ///< UUID of the peer device (data: ::xet_resprop_link_peer_device_t)
            LINK_AVAIL_SPEEDS = 0x50003,                    ///< (ro static) Available link speeds (data:
                                                            ///< ::xet_resprop_link_avail_speeds_t)
            LINK_MAX_PACKET_SIZE = 0x50004,                 ///< (ro static) Maximum packet size (data:
                                                            ///< ::xet_resprop_link_max_packet_size_t)
            LINK_STATE = 0x50005,                           ///< (rw dynamic) Link state (enabled/disabled) (data:
                                                            ///< ::xet_resprop_link_state_t)
            LINK_BANDWIDTH = 0x50006,                       ///< (ro dynamic) Monotonic bandwidth counters (data:
                                                            ///< ::xet_resprop_link_bandwidth_t)
            LINK_SPEED = 0x50007,                           ///< (ro dynamic) Current link speed (data: ::xet_resprop_link_speed_t)
            LINK_SPEED_RANGE = 0x50008,                     ///< (wo dynamic) Set the min/max speeds between which the link can operate
                                                            ///< (data: ::xet_resprop_link_speed_range_t)
            TEMP_TEMPERATURE = 0x60000,                     ///< (ro dynamic) The current temperature of the sensor in degrees celcius
                                                            ///< (data: ::xet_resprop_temp_temperature_t)
            STBY_PROMO_MODE = 0x70000,                      ///< (rw dynamic) The current promotion mode (data:
                                                            ///< ::xet_resprop_stby_promo_mode_t)
            FW_NAME = 0x80000,                              ///< (ro static) Name encoded in the loaded firmware image (data:
                                                            ///< ::xet_resprop_fw_name_t)
            FW_VERSION = 0x80001,                           ///< (ro static) The version of the loaded firmware image (data:
                                                            ///< ::xet_resprop_fw_version_t)
            FW_CHECK = 0x80002,                             ///< (ro dynamic) Verify the checksum of the loaded firmware image (data:
                                                            ///< ::xet_resprop_fw_check_t)
            FW_FLASH = 0x80003,                             ///< (wo dynamically) Flash a new firmware image (data:
                                                            ///< ::xet_resprop_fw_flash_t)
            PSU_AMP_LIMIT = 0x90000,                        ///< (ro static) The maximum electrical current in amperes that can be
                                                            ///< drawn (data: ::xet_resprop_psu_amp_limit_t)
            PSU_VOLTAGE_STATUS = 0x90001,                   ///< (ro dynamic) Indicates if under or over voltage has occurred (data:
                                                            ///< ::xet_resprop_psu_voltage_status_t)
            PSU_FAN_FAILURE = 0x90002,                      ///< (ro dynamic) Indicates if the fan has failed (data:
                                                            ///< ::xet_resprop_psu_fan_failure_t)
            PSU_TEMPERATURE = 0x90003,                      ///< (ro dynamic) The current heatsink temperature in degrees celcius
                                                            ///< (data: ::xet_resprop_psu_temperature_t)
            PSU_AMPS = 0x90004,                             ///< (ro dynamic) The current amps being drawn in amperes (data:
                                                            ///< ::xet_resprop_psu_amps_t)
            FAN_MAX_RPM = 0xA0000,                          ///< (ro static) The maximum RPM of the fan (data:
                                                            ///< ::xet_resprop_fan_max_rpm_t)
            FAN_MAX_TABLE_SIZE = 0xA0001,                   ///< (ro static) The maximum number of points in the fan temp/speed table
                                                            ///< (data: ::xet_resprop_fan_max_table_size_t)
            FAN_SPEED_RPM = 0xA0002,                        ///< (ro dynamic) The current fan speed in units of revolutions per minute
                                                            ///< (rpm) (data: ::xet_resprop_fan_speed_rpm_t)
            FAN_SPEED_PERCENT = 0xA0003,                    ///< (ro dynamic) The current fan speed as a percentage of the maximum
                                                            ///< speed of that fan (data: ::xet_resprop_fan_speed_percent_t)
            FAN_MODE = 0xA0004,                             ///< (ro dynamic) The current fan speed mode (one of
                                                            ///< ::xet_fan_speed_mode_t) (data: ::xet_resprop_fan_mode_t)
            FAN_FIXED_SPEED = 0xA0005,                      ///< (rw dynamic) Read/write the fixed speed setting for the fan (data:
                                                            ///< ::xet_resprop_fan_fixed_speed_t)
            FAN_SPEED_TABLE = 0xA0006,                      ///< (rw dynamic) Read/write the fan speed table (data:
                                                            ///< ::xet_resprop_fan_speed_table_t)
            LED_RGB_CAP = 0xB0000,                          ///< (ro static) Indicates if the LED is RGB capable (data:
                                                            ///< ::xet_resprop_led_rgb_cap_t)
            LED_STATE = 0xB0001,                            ///< (rw dynaic) The LED state - on/off and color (data:
                                                            ///< ::xet_resprop_led_state_t)

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
        /// @brief Link resource types
        enum class link_type_t
        {
            PCI = 0,                                        ///< PCI connection
            CD_PORT,                                        ///< Companion die physical port

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby promotion modes
        enum class stby_promo_mode_t
        {
            IMMEDIATE = 0,                                  ///< The device/component will shutdown immediately when all contained
                                                            ///< units are idle. This improves energy savings at the expense of
                                                            ///< performance.
            DEFAULT,                                        ///< Best compromise between performance and energy savings.
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
            FIXED = 0,                                      ///< The fan speed is currently set to a fixed value
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
        /// @brief Property support
        enum class prop_support_t
        {
            NONE = 0,                                       ///< The property is not supported by this version of the API
            API = XE_BIT( 0 ),                              ///< The property is supported by the the API
            DEVICE_CLASS = XE_BIT( 1 ),                     ///< The property is supported for the class of device
            DEVICE = XE_BIT( 2 ),                           ///< The property is supported for the device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Property access permissions
        enum class prop_access_t
        {
            NO_PERMISSIONS = 0,                             ///< The application does not have read-write access to the property
            READ_PERMISSIONS = XE_BIT( 0 ),                 ///< The application has only read access to the property
            WRITE_PERMISSIONS = XE_BIT( 1 ),                ///< The application has write access to the property

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error type
        enum class ras_error_type_t
        {
            NONE = 0,                                       ///< No error type
            FATAL = XE_BIT( 0 ),                            ///< Error was fatal
            NON_FATAL = XE_BIT( 1 ),                        ///< Error was not fatal
            CORRECTABLE = XE_BIT( 2 ),                      ///< Error was corrected
            UNCORRECTABLE = XE_BIT( 3 ),                    ///< Error was not corrected
            PARITY = XE_BIT( 4 ),                           ///< Parity error occurred
            SINGLE_BIT = XE_BIT( 5 ),                       ///< Single bit error occurred
            DOUBLE_BIT = XE_BIT( 6 ),                       ///< Single bit error occurred
            REPLAY = XE_BIT( 7 ),                           ///< Replay occurred
            RESET = XE_BIT( 8 ),                            ///< Resets occurred
            ALL = ~0,                                       ///< Select all error types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error structural location
        enum class ras_error_loc_t
        {
            NONE = 0,                                       ///< No location
            MAIN_MEM = XE_BIT( 0 ),                         ///< Error occurred in main onboard memory
            L3_CACHE = XE_BIT( 1 ),                         ///< Error occurred in L3 cache
            SAMPLER_SRAM = XE_BIT( 2 ),                     ///< Error occurred in sampler SRAM
            GUC_SRAM = XE_BIT( 3 ),                         ///< Error occurred in microcontroller SRAM
            INST_CACHE = XE_BIT( 4 ),                       ///< Error occurred in the compute unit instruction cache
            GRF = XE_BIT( 5 ),                              ///< Error occurred in the compute unit register file
            SLM = XE_BIT( 6 ),                              ///< Error occurred in the compute unit shared local memory
            MESSAGING = XE_BIT( 7 ),                        ///< Errors occurred handling transactions between PCI config space, MMIO
                                                            ///< registers, local memory and sub-devices
            SECURITY = XE_BIT( 8 ),                         ///< Security errors occurred
            DISPLAY = XE_BIT( 9 ),                          ///< Errors occurred in the display
            SOC = XE_BIT( 10 ),                             ///< Errors occurred in other parts of the device
            GPU_HANG = XE_BIT( 11 ),                        ///< Driver detected that the GPU hardware was non-responsive
            PCI = XE_BIT( 12 ),                             ///< Error occurred in the PCIe controller
            PCI_ROUTING = XE_BIT( 13 ),                     ///< Error occurred routing PCIe traffic to/from sub-devices
            P2P_LINK = XE_BIT( 14 ),                        ///< Errors detected with peer-to-peer connection
            ALL = ~0,                                       ///< Select all error locations

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS data type
        enum class ras_data_type_t
        {
            NONE = 0,                                       ///< Errors not supported
            OCCURRED,                                       ///< Indicates if an error occurred
            COUNTER,                                        ///< Provides a counter for the number of errors that have occurred

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event types
        enum class event_type_t
        {
            FREQ_THROTTLED = 0,                             ///< The frequency is being throttled
            RAS_ERRORS,                                     ///< ECC/RAS errors
            COUNT,                                          ///< The number of event types

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
        /// @brief Data for a PCI bar
        struct pci_bar_info_t
        {
            pci_bar_type_t type;                            ///< [out] The type of bar
            uint64_t base;                                  ///< [out] Base address of the bar.
            uint64_t size;                                  ///< [out] Size of the bar.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_DEV_SERIAL_NUMBER
        struct resprop_dev_serial_number_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_DEV_BOARD_NUMBER
        struct resprop_dev_board_number_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_DEV_BRAND
        struct resprop_dev_brand_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_DEV_MODEL
        struct resprop_dev_model_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_DEV_DEVICEID
        struct resprop_dev_deviceid_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_DEV_VENDOR_NAME
        struct resprop_dev_vendor_name_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_DEV_DRIVER_VERSION
        struct resprop_dev_driver_version_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_DEV_BARS
        struct resprop_dev_bars_t
        {
            uint32_t num;                                   ///< [out] The number of bars
            const pci_bar_info_t* pBars;                    ///< [out][range(0, num-1)] Information about each bar.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PWR_MAX_LIMIT
        struct resprop_pwr_max_limit_t
        {
            uint32_t limit;                                 ///< [out] The maximum power limit in milliwatts that can be requested.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PWR_ENERGY_COUNTER
        struct resprop_pwr_energy_counter_t
        {
            uint64_t energy;                                ///< [out] The value of the monotonic energy counter in millijoules.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PWR_SUSTAINED_LIMIT
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency if
        ///       the power averaged over a window (typically seconds) exceeds this
        ///       limit.
        struct resprop_pwr_sustained_limit_t
        {
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts
            uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PWR_BURST_LIMIT
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency of
        ///       the device if the power averaged over a few milliseconds exceeds a
        ///       limit known as PL2. Typically PL2 > PL1 so that it permits the
        ///       frequency to burst higher for short periods than would be otherwise
        ///       permitted by PL1.
        struct resprop_pwr_burst_limit_t
        {
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PWR_PEAK_LIMIT
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
        struct resprop_pwr_peak_limit_t
        {
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_AVAIL_CLOCKS
        /// 
        /// @details
        ///     - Provides the set of frequencies as a list and as a range/step.
        ///     - It is generally recommended that applications choose frequencies from
        ///       the list. However applications can also construct the list themselves
        ///       using the range/steps provided.
        struct resprop_freq_avail_clocks_t
        {
            double min;                                     ///< [out] The minimum clock frequency in units of MHz
            double max;                                     ///< [out] The maximum clock frequency in units of MHz
            double step;                                    ///< [out] The step clock frequency in units of MHz
            uint32_t num;                                   ///< [out] The number of clocks
            const double* pClocks;                          ///< [out] Array of clock frequencies in units of MHz ordered from smallest
                                                            ///< to largest.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_RANGE
        struct resprop_freq_range_t
        {
            double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                            ///< management will not request frequencies. Setting to 0 will return the
                                                            ///< hardware default value.
            double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                            ///< management will not request frequencies. Setting to 0 will return the
                                                            ///< hardware default value.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_REQUESTED_FREQ
        struct resprop_freq_requested_freq_t
        {
            double freqRequest;                             ///< [out] The current frequency request in MHz.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_TDP_FREQ
        struct resprop_freq_tdp_freq_t
        {
            double freqTdp;                                 ///< [out] The maximum frequency in MHz supported under the current TDP
                                                            ///< conditions

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_EFFICIENT_FREQ
        struct resprop_freq_efficient_freq_t
        {
            double freqEfficient;                           ///< [out] The efficient minimum frequency in MHz

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_RESOLVED_FREQ
        struct resprop_freq_resolved_freq_t
        {
            double freqResolved;                            ///< [out] The resolved frequency in MHz

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_THROTTLE_REASONS
        struct resprop_freq_throttle_reasons_t
        {
            uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the PCU
                                                            ///< (Bitfield of (1<<::xet_freq_throttle_reasons_t)).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FREQ_THROTTLE_TIME
        struct resprop_freq_throttle_time_t
        {
            uint32_t throttleTime;                          ///< [out] The total time in microseconds that the frequency has been
                                                            ///< limited by the PCU.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_UTIL_COUNTERS
        /// 
        /// @details
        ///     - Percentage utilization is given by the equation: 100 *
        ///       delta(activeCounter) / ( delta(activeCounter) + delta(idleCounter) ).
        struct resprop_util_counters_t
        {
            uint32_t activeCounter;                         ///< [out] Monotonic counter for total wall time in microseconds that this
                                                            ///< resource is actively running workloads.
            uint32_t idleCounter;                           ///< [out] Monotonic counter for total wall time in microseconds that this
                                                            ///< resource is not actively running any workloads.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_MEM_TYPE
        struct resprop_mem_type_t
        {
            mem_type_t type;                                ///< [out] The memory type

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_MEM_UTILIZATION
        /// 
        /// @details
        ///     - The total physical memory is the sum of all others (stolen + bad +
        ///       allocated + unallocated).
        ///     - Percent software memory utilization given by 100 * allocated /
        ///       (allocated + unallocated).
        ///     - Percent bad memory given by 100 * bad / total
        struct resprop_mem_utilization_t
        {
            uint64_t total;                                 ///< [out] The total physical memory in bytes
            uint64_t stolen;                                ///< [out] The total stolen memory in bytes
            uint64_t bad;                                   ///< [out] The total bad memory in bytes
            uint64_t allocated;                             ///< [out] The total allocated bytes
            uint64_t unallocated;                           ///< [out] The total unallocated bytes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_MEM_BANDWIDTH
        struct resprop_mem_bandwidth_t
        {
            uint32_t readCounter;                           ///< [out] Total bytes read from memory
            uint32_t writeCounter;                          ///< [out] Total bytes written to memory
            uint32_t maxBandwidth;                          ///< [out] Current maximum bandwidth in units of bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Link speed element
        struct link_speed_t
        {
            uint32_t numLanes;                              ///< [out] The number of lanes used by the link
            uint32_t speed;                                 ///< [out] The frequency of the link in units of MHz
            uint32_t bandwidth;                             ///< [out] The maximum bandwidth in units of bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_LINK_TYPE
        struct resprop_link_type_t
        {
            link_type_t type;                               ///< [out] The type of link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_LINK_BUS_ADDRESS
        struct resprop_link_bus_address_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_LINK_PEER_DEVICE
        struct resprop_link_peer_device_t
        {
            xe::DeviceGroup::device_uuid_t uuid;            ///< [out] UUID of the peer device connected to through this link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LINK_AVAIL_SPEEDS
        /// 
        /// @details
        ///     - The list is ordered from the smallest ratio to the largest ratio.
        struct resprop_link_avail_speeds_t
        {
            uint32_t num;                                   ///< [out] The number of elements in pList
            const link_speed_t* pList;                      ///< [out][range(0, num-1)] Pointer to an array of link speeds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LINK_STATE
        struct resprop_link_state_t
        {
            xe::bool_t enable;                              ///< [out] Indicates if the link is disabled/endabled.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LINK_MAX_PACKET_SIZE
        struct resprop_link_max_packet_size_t
        {
            uint32_t maxPacketSize;                         ///< [out] Maximum packet size in bytes.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LINK_BANDWIDTH
        struct resprop_link_bandwidth_t
        {
            uint32_t recvCounter;                           ///< [out] Total bytes received across the link
            uint32_t sendCounter;                           ///< [out] Total bytes sent across the link
            uint32_t maxBandwidth;                          ///< [out] Maximum bytes/sec that can be transfered acros the link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LINK_SPEED
        struct resprop_link_speed_t
        {
            const link_speed_t* pSpeed;                     ///< [out] Pointer to the current speed configuration

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LINK_SPEED_RANGE
        struct resprop_link_speed_range_t
        {
            const link_speed_t* pMinSpeed;                  ///< [out] Pointer to the min speed configuration (one of those in the
                                                            ///< array returned by property ::XET_RESPROP_LINK_AVAIL_SPEEDS)
            const link_speed_t* pMaxSpeed;                  ///< [out] Pointer to the max speed configuration (one of those in the
                                                            ///< array returned by property ::XET_RESPROP_LINK_AVAIL_SPEEDS)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_TEMP_TEMPERATURE
        struct resprop_temp_temperature_t
        {
            uint32_t temperature;                           ///< [out] The current temperature of the sensor in degrees celcius

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_STBY_PROMO_MODE
        struct resprop_stby_promo_mode_t
        {
            stby_promo_mode_t mode;                         ///< [in,out] Current promotion mode

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_FW_NAME
        struct resprop_fw_name_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_RESPROP_FW_VERSION
        struct resprop_fw_version_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FW_CHECK
        struct resprop_fw_check_t
        {
            uint32_t checksum;                              ///< [out] The calculated checksum of the loaded firmware image

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FW_FLASH
        struct resprop_fw_flash_t
        {
            void* pImage;                                   ///< [in] Pointer to the image to be flashed
            uint32_t size;                                  ///< [in] Size in bytes of the image pointed to by pImage

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PSU_AMP_LIMIT
        struct resprop_psu_amp_limit_t
        {
            uint32_t limit;                                 ///< [out] The maximum electrical current in amperes that can be drawn

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PSU_VOLTAGE_STATUS
        struct resprop_psu_voltage_status_t
        {
            psu_voltage_status_t status;                    ///< [out] The current PSU voltage status)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PSU_FAN_FAILURE
        struct resprop_psu_fan_failure_t
        {
            xe::bool_t status;                              ///< [out] Indicates if the fan has failed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PSU_TEMPERATURE
        struct resprop_psu_temperature_t
        {
            uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees celcius

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_PSU_AMPS
        struct resprop_psu_amps_t
        {
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
        /// @brief Data for the property ::XET_RESPROP_FAN_MAX_RPM
        struct resprop_fan_max_rpm_t
        {
            uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FAN_MAX_TABLE_SIZE
        struct resprop_fan_max_table_size_t
        {
            uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FAN_SPEED_RPM
        struct resprop_fan_speed_rpm_t
        {
            uint32_t speed;                                 ///< [out] The current fan speed in units of revolutions per minute (rpm)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FAN_SPEED_PERCENT
        struct resprop_fan_speed_percent_t
        {
            uint32_t speed;                                 ///< [out] The current fan speed as a percentage of the maximum speed of
                                                            ///< that fan

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FAN_MODE
        struct resprop_fan_mode_t
        {
            fan_speed_mode_t mode;                          ///< [in,out] The current fan speed mode (one of ::xet_fan_speed_mode_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FAN_FIXED_SPEED
        struct resprop_fan_fixed_speed_t
        {
            uint32_t speed;                                 ///< [in,out] The speed of the fan
            fan_speed_units_t units;                        ///< [in,out] The units of the member speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_FAN_SPEED_TABLE
        struct resprop_fan_speed_table_t
        {
            uint32_t* pCount;                               ///< [in,out] The number of temp/speed pairs.
                                                            ///< When reading the current fan speed table, this will be set to the
                                                            ///< number of points returned.
                                                            ///< When setting the fan speed table, this specifies the number of valid
                                                            ///< points in the table.
            fan_temp_speed_t points[XET_FAN_TEMP_SPEED_PAIR_COUNT]; ///< [in,out][range(0, *pCount)] Array of temperature/fan speed pairs

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LED_RGB_CAP
        struct resprop_led_rgb_cap_t
        {
            xe::bool_t haveRGB;                             ///< [out] Indicates if the LED is RGB capable

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_RESPROP_LED_STATE
        struct resprop_led_state_t
        {
            xe::bool_t isOn;                                ///< [in,out] Indicates if the LED is on or off
            uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
            uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
            uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Structure containing information about a resource
        struct resid_info_t
        {
            resid_t id;                                     ///< [in] The ID of the resource
            resource_type_t type;                           ///< [in] The type of resource
            const char* pName;                              ///< [out] The name of the resource
            const char* pDesc;                              ///< [out] Human readable description of this resouce
            xe::bool_t available;                           ///< [out] Set to TRUE if the resource with this ID is available on the
                                                            ///< device, otherwise set to FALSE
            xe::bool_t propsOnSubdevices;                   ///< [out] Set to TRUE if this resource will change properties on
                                                            ///< sub-devices or is merging telemetry from sub-devices

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure to get resource property info
        struct resprop_info_t
        {
            resprop_t property;                             ///< [in] The property
            resource_type_t resourceType;                   ///< [out] The type of resource this property is used with
            const char* pName;                              ///< [out] Resource property name
            const char* pDesc;                              ///< [out] Human readable description of this property
            prop_support_t support;                         ///< [out] API support for the property
            prop_access_t access;                           ///< [out] The access permissions for the property
            uint32_t minGetInterval;                        ///< [out] The minimum interval in microseconds between reads to this
                                                            ///< property
            uint32_t minSetInterval;                        ///< [out] The minimum interval in microseconds between writes to this
                                                            ///< property

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a resource property value
        struct resprop_request_t
        {
            resid_t resource;                               ///< [in] The resource ID
            resprop_t property;                             ///< [in] The property being requested
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.
            xe::result_t status;                            ///< [out] Indicates if the request was successful or not.
                                                            ///< ::XE_RESULT_SUCCESS - Data was successful read or updated.
                                                            ///< ::XE_RESULT_ERROR_DEVICE_ACCESS - Problem reading or writing device data.
                                                            ///< ::XE_RESULT_ERROR_INVALID_ARGUMENT - Resource ID or property ID are
                                                            ///< invalid or size does not match required storage for property data.
                                                            ///< ::XE_RESULT_ERROR_UNSUPPORTED - Resource ID and/or property ID not
                                                            ///< supported on this device.
                                                            ///< ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS - Insufficient permission to
                                                            ///< access this property.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS configuration
        struct ras_config_t
        {
            uint32_t numRas;                                ///< [in] Total number of RAS counters available on this device
            uint32_t rasTypes;                              ///< [in] All RAS types supported on this device (bitfield of
                                                            ///< ::xet_ras_error_type_t)
            uint32_t rasLocations;                          ///< [in] All structural locations where RAS is supported on this device
                                                            ///< (bitfield of ::xet_ras_error_loc_t)
            uint32_t enabled;                               ///< [in] All structural locations where RAS is currently enabled on this
                                                            ///< device (bitfield of ::xet_ras_error_loc_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Filter RAS errors
        struct ras_filter_t
        {
            resid_t resourceId;                             ///< [in] Filter based on resource ID. Set to ::XET_RESID_ANY to get errors
                                                            ///< from anywhere in the device
            uint32_t type;                                  ///< [in] Bitfield of error types to filter - one or more of
                                                            ///< ::xet_ras_error_type_t. Set to ::XET_RAS_ERROR_TYPE_ALL to have all
                                                            ///< error types returned.
            uint32_t location;                              ///< [in] Bitfield of error locations to filter - one or more of
                                                            ///< ::xet_ras_error_loc_t. Set to ::XET_RAS_ERROR_LOC_ALL to have all
                                                            ///< error locations returned.
            uint32_t threshold;                             ///< [in] Only return error elements that have occurred at least this
                                                            ///< number of times.
                                                            ///< If set to 0, will get a list of all possible RAS elements, even those
                                                            ///< that have not had errors.
                                                            ///< For error elements of type ::XET_RAS_DATA_TYPE_OCCURRED, there is no
                                                            ///< underlying counter, so they will always be returned independent of the
                                                            ///< threshold setting.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error
        struct ras_error_t
        {
            const char* pName;                              ///< [out] Name of this error
            const char* pDesc;                              ///< [out] Human readable description of this error
            uint32_t type;                                  ///< [out] Bitfield describing type of error, constructed from one or more
                                                            ///< of ::xet_ras_error_type_t
            uint32_t loc;                                   ///< [out] Bitfield describing structural location of the error,
                                                            ///< constructed from one of ::xet_ras_error_loc_t
            ras_data_type_t dataType;                       ///< [out] How to interpret the data
            uint64_t data;                                  ///< [out] The value of the error - interpretation depends on dataType
            uint64_t accumulated;                           ///< [out] The accumulated value of the error (never cleared until device
                                                            ///< driver is reloaded)
            resid_t resourceId;                             ///< [out] Resource where the error was generated. If the error doesn't
                                                            ///< come from a specific resource, this will be ::XET_RESID_ANY

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure to determine events that are supported
        struct event_support_t
        {
            event_type_t event;                             ///< [in] The event
            xe::bool_t supported;                           ///< [out] Set to true/false to know if the event is supported

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to register/unregister events
        struct event_request_t
        {
            event_type_t event;                             ///< [in] The event type to register.
            resid_t resourceId;                             ///< [in] Only events being generated by the specified resource. If
                                                            ///< ::XET_RESID_ANY, then applies to all events from all resources in the
                                                            ///< device.
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
        DeviceGroup* m_pDeviceGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sysman( void ) = delete;
        Sysman( 
            sysman_handle_t handle,                         ///< [in] handle of SMI object
            DeviceGroup* pDeviceGroup                       ///< [in] pointer to owner object
            );

        ~Sysman( void ) = default;

        Sysman( Sysman const& other ) = delete;
        void operator=( Sysman const& other ) = delete;

        Sysman( Sysman&& other ) = delete;
        void operator=( Sysman&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevicegroup( void ) const { return m_pDeviceGroup; }

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
        /// @brief Find out if specific resources are available on this device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetResourceInfo(
            uint32_t count,                                 ///< [in] The number of entries in the the array pResources
            resid_info_t* pResources                        ///< [in] Pointer to an array that hold the ID of resources on input and
                                                            ///< will contain the availability on output
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get list of resources available on this device of a given type
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetResources(
            resource_type_t type,                           ///< [in] Get a list of resources of given type. If this is
                                                            ///< ::XET_RESOURCE_TYPE_ANY, then all resources will be returned.
            uint32_t* pCount,                               ///< [in] Pointer to the number of elements in the array pResources.
                                                            ///< If count is 0 or pResources is nullptr, driver will update with the
                                                            ///< number of supported resources on this device.
                                                            ///< If count is non-zero and less than the number of supported resources,
                                                            ///< driver will update with the number of resources. No data is returned
                                                            ///< and an error is generated.
                                                            ///< If count is greater than or equal to the number of supported
                                                            ///< resources, all data is returned and count will be set to the number of
                                                            ///< returned resources.
            resid_info_t* pResources                        ///< [in] Pointer to an array that will hold the ID of information about
                                                            ///< supported resources
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Find out which resources properties are available on a given device
        /// 
        /// @details
        ///     - Access rights are specific to the device. Need to check separately on
        ///       each device.
        ///     - API support is based on the device class and doesn't need to be
        ///       checked for each device.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetPropertyInfo(
            uint32_t count,                                 ///< [in] The number of entries in the array pProperties
            resprop_info_t* pProperties                     ///< [in] Pointer to an array of property info. Contains the property ID on
                                                            ///< input and the property info completed on output
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            resprop_request_t* pRequest                     ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            resprop_request_t* pRequest                     ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get RAS configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetRasConfig(
            ras_config_t* pConfig                           ///< [in] Pointer to storage for current RAS configuration
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Setup (enable/disable) RAS
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        RasSetup(
            uint32_t enableLoc,                             ///< [in] Structural locations where RAS should be enabled (bitfield of
                                                            ///< ::xet_ras_error_loc_t)
            uint32_t disableLoc,                            ///< [in] Structural locations where RAS should be disabled (bitfield of
                                                            ///< ::xet_ras_error_loc_t)
            uint32_t* pEnabledLoc                           ///< [in] Structural locations where RAS is currently enabled after
                                                            ///< applying enableLoc and disableLoc (bitfield of ::xet_ras_error_loc_t)
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get RAS errors that have occurred
        /// 
        /// @details
        ///     - Returned errors can be filtered by resource, type, location and
        ///       threshold.
        ///     - Clearing error counters will affect any subsequent calls to this
        ///       function from any application. Accumulated counter values are not
        ///       affected by this.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetRasErrors(
            ras_filter_t* pFilter,                          ///< [in] Filter for RAS errors to return
            xe::bool_t clear,                               ///< [in] Set to true to clear the underlying counters after they are
                                                            ///< returned
            uint32_t* pCount,                               ///< [in] Pointer to the number of elements in the array pErrors.
                                                            ///< If count is 0 or pErrors is nullptr, driver will update with the
                                                            ///< number of errors matching the specified filters. Counters are not cleared.
                                                            ///< If count is non-zero and less than the number of matching errors,
                                                            ///< driver will update with the number of errors matching the specified
                                                            ///< filters. No data is returned and counters are not cleared.
                                                            ///< If count is greater than or equal to the number of matching errors,
                                                            ///< all data is returned, counters are cleared if requested and count will
                                                            ///< be set to actual number of errors returned.
            ras_error_t* pErrors                            ///< [in] Array of error data
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Find out which events are supported on a given device
        /// 
        /// @details
        ///     - Event support is the same for all devices with the same device ID.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SupportedEvents(
            uint32_t count,                                 ///< [in] The number of entries in the array pAccess
            event_support_t* pAccess                        ///< [in] Pointer to an array of event support requests
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
        RegisterEvents(
            uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                            ///< be registered.
            event_request_t* pEvents                        ///< [in] Events to register.
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
        UnregisterEvents(
            uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                            ///< be unregistered.
            event_request_t* pEvents                        ///< [in] Events to unregister.
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
        GetEvents(
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
        GetDiagnosticTests(
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
        RunDiagnosticTests(
            diag_type_t type,                               ///< [in] Type of diagnostic to run
            uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                            ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
            uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                            ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
            diag_result_t* pResult                          ///< [in] The result of the diagnostics
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset device
        /// @throws result_t
        void __xecall
        DeviceReset(
            void
            );

    };

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_type_t to std::string
    std::string to_string( const Sysman::resource_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resid_t to std::string
    std::string to_string( const Sysman::resid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_t to std::string
    std::string to_string( const Sysman::resprop_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_type_t to std::string
    std::string to_string( const Sysman::pci_bar_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_info_t to std::string
    std::string to_string( const Sysman::pci_bar_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_serial_number_t to std::string
    std::string to_string( const Sysman::resprop_dev_serial_number_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_board_number_t to std::string
    std::string to_string( const Sysman::resprop_dev_board_number_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_brand_t to std::string
    std::string to_string( const Sysman::resprop_dev_brand_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_model_t to std::string
    std::string to_string( const Sysman::resprop_dev_model_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_deviceid_t to std::string
    std::string to_string( const Sysman::resprop_dev_deviceid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_vendor_name_t to std::string
    std::string to_string( const Sysman::resprop_dev_vendor_name_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_driver_version_t to std::string
    std::string to_string( const Sysman::resprop_dev_driver_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_bars_t to std::string
    std::string to_string( const Sysman::resprop_dev_bars_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_max_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_max_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_energy_counter_t to std::string
    std::string to_string( const Sysman::resprop_pwr_energy_counter_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_sustained_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_sustained_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_burst_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_burst_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_peak_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_peak_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_throttle_reasons_t to std::string
    std::string to_string( const Sysman::freq_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_avail_clocks_t to std::string
    std::string to_string( const Sysman::resprop_freq_avail_clocks_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_range_t to std::string
    std::string to_string( const Sysman::resprop_freq_range_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_requested_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_requested_freq_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_tdp_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_tdp_freq_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_efficient_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_efficient_freq_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_resolved_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_resolved_freq_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_throttle_reasons_t to std::string
    std::string to_string( const Sysman::resprop_freq_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_throttle_time_t to std::string
    std::string to_string( const Sysman::resprop_freq_throttle_time_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_util_counters_t to std::string
    std::string to_string( const Sysman::resprop_util_counters_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_type_t to std::string
    std::string to_string( const Sysman::mem_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_mem_type_t to std::string
    std::string to_string( const Sysman::resprop_mem_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_mem_utilization_t to std::string
    std::string to_string( const Sysman::resprop_mem_utilization_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_mem_bandwidth_t to std::string
    std::string to_string( const Sysman::resprop_mem_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_type_t to std::string
    std::string to_string( const Sysman::link_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_speed_t to std::string
    std::string to_string( const Sysman::link_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_type_t to std::string
    std::string to_string( const Sysman::resprop_link_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_bus_address_t to std::string
    std::string to_string( const Sysman::resprop_link_bus_address_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_peer_device_t to std::string
    std::string to_string( const Sysman::resprop_link_peer_device_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_avail_speeds_t to std::string
    std::string to_string( const Sysman::resprop_link_avail_speeds_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_state_t to std::string
    std::string to_string( const Sysman::resprop_link_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_max_packet_size_t to std::string
    std::string to_string( const Sysman::resprop_link_max_packet_size_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_bandwidth_t to std::string
    std::string to_string( const Sysman::resprop_link_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_speed_t to std::string
    std::string to_string( const Sysman::resprop_link_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_speed_range_t to std::string
    std::string to_string( const Sysman::resprop_link_speed_range_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_temp_temperature_t to std::string
    std::string to_string( const Sysman::resprop_temp_temperature_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::stby_promo_mode_t to std::string
    std::string to_string( const Sysman::stby_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_stby_promo_mode_t to std::string
    std::string to_string( const Sysman::resprop_stby_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_name_t to std::string
    std::string to_string( const Sysman::resprop_fw_name_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_version_t to std::string
    std::string to_string( const Sysman::resprop_fw_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_check_t to std::string
    std::string to_string( const Sysman::resprop_fw_check_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_flash_t to std::string
    std::string to_string( const Sysman::resprop_fw_flash_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_voltage_status_t to std::string
    std::string to_string( const Sysman::psu_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_amp_limit_t to std::string
    std::string to_string( const Sysman::resprop_psu_amp_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_voltage_status_t to std::string
    std::string to_string( const Sysman::resprop_psu_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_fan_failure_t to std::string
    std::string to_string( const Sysman::resprop_psu_fan_failure_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_temperature_t to std::string
    std::string to_string( const Sysman::resprop_psu_temperature_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_amps_t to std::string
    std::string to_string( const Sysman::resprop_psu_amps_t val );

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
    /// @brief Converts Sysman::resprop_fan_max_rpm_t to std::string
    std::string to_string( const Sysman::resprop_fan_max_rpm_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_max_table_size_t to std::string
    std::string to_string( const Sysman::resprop_fan_max_table_size_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_speed_rpm_t to std::string
    std::string to_string( const Sysman::resprop_fan_speed_rpm_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_speed_percent_t to std::string
    std::string to_string( const Sysman::resprop_fan_speed_percent_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_mode_t to std::string
    std::string to_string( const Sysman::resprop_fan_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_fixed_speed_t to std::string
    std::string to_string( const Sysman::resprop_fan_fixed_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_speed_table_t to std::string
    std::string to_string( const Sysman::resprop_fan_speed_table_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_led_rgb_cap_t to std::string
    std::string to_string( const Sysman::resprop_led_rgb_cap_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_led_state_t to std::string
    std::string to_string( const Sysman::resprop_led_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::prop_support_t to std::string
    std::string to_string( const Sysman::prop_support_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::prop_access_t to std::string
    std::string to_string( const Sysman::prop_access_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resid_info_t to std::string
    std::string to_string( const Sysman::resid_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_info_t to std::string
    std::string to_string( const Sysman::resprop_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_request_t to std::string
    std::string to_string( const Sysman::resprop_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_type_t to std::string
    std::string to_string( const Sysman::ras_error_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_loc_t to std::string
    std::string to_string( const Sysman::ras_error_loc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_config_t to std::string
    std::string to_string( const Sysman::ras_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_data_type_t to std::string
    std::string to_string( const Sysman::ras_data_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_filter_t to std::string
    std::string to_string( const Sysman::ras_filter_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_t to std::string
    std::string to_string( const Sysman::ras_error_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_support_t to std::string
    std::string to_string( const Sysman::event_support_t val );

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
