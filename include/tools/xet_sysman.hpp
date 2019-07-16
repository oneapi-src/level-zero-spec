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
#ifndef XET_RESOURCE_ID_ANY
/// @brief Any resource
#define XET_RESOURCE_ID_ANY  { XET_RESOURCE_TYPE_ANY, 0x0 }
#endif // XET_RESOURCE_ID_ANY

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
        /// @brief SMI initialization flags (bitfield)
        enum class init_flags_t
        {
            NONE = 0,                                       ///< Default initialization
            WRITE = XE_BIT( 0 ),                            ///< Request write/control access to resources

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource types
        enum class resource_type_t
        {
            PSU = 0,                                        ///< PSU resource
            TEMP,                                           ///< Temperature sensor resource
            FAN,                                            ///< Fan resource
            LED,                                            ///< LED resource
            FIRMWARE,                                       ///< Firmware resource
            PWR,                                            ///< Power domain resource
            FREQ,                                           ///< Frequency domain resource
            PWRWELL,                                        ///< Power-well resource
            ACCEL,                                          ///< Accelerator asset resource
            MEM,                                            ///< Memory resource
            LINK,                                           ///< Link resource
            MAX_TYPES,                                      ///< The number of resource types
            ANY = -1,                                       ///< Any resource filter

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Accelerator assets
        enum class accel_asset_t
        {
            PCIE_CONTROLLER = 0,                            ///< PCIe controller
            IDI_MEM_CONTROLLER,                             ///< IDI memory controller
            HBM_MEM_CONTROLLER,                             ///< HBM memory controller
            L3_CACHE,                                       ///< L3 cache
            BLITTER,                                        ///< Blitter
            VIDEO_DECODER,                                  ///< Video decoder
            VIDEO_ENCODER,                                  ///< Video encoder
            VIDEO_PROCESSING,                               ///< Video processing
            _3D_FF,                                         ///< 3D fixed-function hardware
            _3D_RENDER,                                     ///< 3D programmable shader units
            COMPUTE,                                        ///< Compute units
            SYSTOLIC,                                       ///< Systolic array
            RAYTRACING,                                     ///< Raytracing hardware
            LOCAL_MEM,                                      ///< Local memory
            LINK,                                           ///< High speed link
            MAX_TYPES,                                      ///< The number of accelerator asset types

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
            PCI = XE_BIT( 7 ),                              ///< Error occurred in the PCIe controller
            PCI_ROUTING = XE_BIT( 8 ),                      ///< Error occurred routing PCIe traffic to/from sub-devices
            SGUNIT = XE_BIT( 9 ),                           ///< Errors occurred handling transactions between PCI config space, MMIO
                                                            ///< registers, local memory and sub-devices
            GSC = XE_BIT( 10 ),                             ///< Security errors occurred
            DISPLAY = XE_BIT( 11 ),                         ///< Errors occurred in the display
            SOC = XE_BIT( 12 ),                             ///< Errors occurred in other parts of the device
            GPU_HANG = XE_BIT( 13 ),                        ///< Driver detected that the GPU hardware was non-responsive
            GPU_WARM_RESET = XE_BIT( 14 ),                  ///< Driver performed a GPU warm reset
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
        /// @brief Device resource properties
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
        enum class device_properties_t
        {
            DEVICE_PROP_SERIAL_NUMBER = 0,                  ///< (ro static) The serial number of the device (data:
                                                            ///< ::xet_device_prop_serial_number_t)
            DEVICE_PROP_BOARD_NUMBER,                       ///< (ro static) The board number of the device (data:
                                                            ///< ::xet_device_prop_board_number_t)
            DEVICE_PROP_BRAND,                              ///< (ro static) The brand name of the device (data:
                                                            ///< ::xet_device_prop_brand_t)
            DEVICE_PROP_MODEL,                              ///< (ro static) The model name of the device (data:
                                                            ///< ::xet_device_prop_model_t)
            DEVICE_PROP_DEVICEID,                           ///< (ro static) The device ID of the device (data:
                                                            ///< ::xet_device_prop_deviceid_t)
            DEVICE_PROP_VENDOR_NAME,                        ///< (ro static) The vendor name of the device (data:
                                                            ///< ::xet_device_prop_vendor_name_t)
            DEVICE_PROP_DRIVER_VERSION,                     ///< (ro static) The driver version associated with the device (data:
                                                            ///< ::xet_device_prop_driver_version_t)
            DEVICE_PROP_BARS,                               ///< (ro static) The bars configured for the device (data:
                                                            ///< ::xet_device_prop_bars_t)
            DEVICE_PROP_COLD_SHUTDOWN,                      ///< (wo dynamic) Cold shudown the device (data:
                                                            ///< ::xet_device_prop_cold_shutdown_t)
            DEVICE_PROP_COLD_RESET,                         ///< (wo dynamic) Cold reset the device (data:
                                                            ///< ::xet_device_prop_cold_reset_t)

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
        /// @brief PSU resource properties
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
        enum class psu_properties_t
        {
            PSU_PROP_AMP_LIMIT = 0,                         ///< (ro static) The maximum electrical current in amperes that can be
                                                            ///< drawn (data: ::xet_psu_prop_amp_limit_t)
            PSU_PROP_VOLTAGE_STATUS,                        ///< (ro dynamic) Indicates if under or over voltage has occurred (data:
                                                            ///< ::xet_psu_prop_voltage_status_t)
            PSU_PROP_FAN_FAILURE,                           ///< (ro dynamic) Indicates if the fan has failed (data:
                                                            ///< ::xet_psu_prop_fan_failure_t)
            PSU_PROP_TEMPERATURE,                           ///< (ro dynamic) The current heatsink temperature in degrees celcius
                                                            ///< (data: ::xet_psu_prop_temperature_t)
            PSU_PROP_AMPS,                                  ///< (ro dynamic) The current amps being drawn in amperes (data:
                                                            ///< ::xet_psu_prop_amps_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensor resource properties
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
        enum class temp_properties_t
        {
            TEMP_PROP_TEMPERATURE = 0,                      ///< (ro dynamic) The current temperature of the sensor in degrees celcius
                                                            ///< (data: ::xet_temp_prop_temperature_t)

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
        /// @brief Fan resource properties
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
        enum class fan_properties_t
        {
            FAN_PROP_MAX_RPM = 0,                           ///< (ro static) The maximum RPM of the fan (data:
                                                            ///< ::xet_fan_prop_max_rpm_t)
            FAN_PROP_MAX_TABLE_SIZE,                        ///< (ro static) The maximum number of points in the fan temp/speed table
                                                            ///< (data: ::xet_fan_prop_max_table_size_t)
            FAN_PROP_SPEED_RPM,                             ///< (ro dynamic) The current fan speed in units of revolutions per minute
                                                            ///< (rpm) (data: ::xet_fan_prop_speed_rpm_t)
            FAN_PROP_SPEED_PERCENT,                         ///< (ro dynamic) The current fan speed as a percentage of the maximum
                                                            ///< speed of that fan (data: ::xet_fan_prop_speed_percent_t)
            FAN_PROP_MODE,                                  ///< (ro dynamic) The current fan speed mode (one of
                                                            ///< ::xet_fan_speed_mode_t) (data: ::xet_fan_prop_mode_t)
            FAN_PROP_FIXED_SPEED,                           ///< (rw dynamic) Read/write the fixed speed setting for the fan (data:
                                                            ///< ::xet_fan_prop_fixed_speed_t)
            FAN_PROP_SPEED_TABLE,                           ///< (rw dynamic) Read/write the fan speed table (data:
                                                            ///< ::xet_fan_prop_speed_table_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED resource properties
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
        enum class led_properties_t
        {
            LED_PROP_RGB_CAP = 0,                           ///< (ro static) Indicates if the LED is RGB capable (data:
                                                            ///< ::xet_led_prop_rgb_cap_t)
            LED_PROP_STATE,                                 ///< (rw dynaic) The LED state - on/off and color (data:
                                                            ///< ::xet_led_prop_state_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Firmware resource properties
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
        enum class firmware_properties_t
        {
            FIRMWARE_PROP_NAME = 0,                         ///< (ro static) Name encoded in the loaded firmware image (data:
                                                            ///< ::xet_firmware_prop_name_t)
            FIRMWARE_PROP_VERSION,                          ///< (ro static) The version of the loaded firmware image (data:
                                                            ///< ::xet_firmware_prop_version_t)
            FIRMWARE_PROP_CHECK,                            ///< (ro dynamic) Verify the checksum of the loaded firmware image (data:
                                                            ///< ::xet_firmware_prop_check_t)
            FIRMWARE_PROP_FLASH,                            ///< (wo dynamically) Flash a new firmware image (data:
                                                            ///< ::xet_firmware_prop_flash_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Power domain resource properties
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
        enum class pwr_properties_t
        {
            PWR_PROP_ACCEL_ASSETS = 0,                      ///< (ro static) List of accelerator assets that contribute to this power
                                                            ///< domain (data: ::xet_pwr_prop_accel_assets_t)
            PWR_PROP_MAX_LIMIT,                             ///< (ro static) The maximum power limit that can be requested (data:
                                                            ///< ::xet_pwr_prop_max_limit_t)
            PWR_PROP_ENERGY_COUNTER,                        ///< (ro dynamic) The value of the monotonic energy counter (data:
                                                            ///< ::xet_pwr_prop_energy_counter_t)
            PWR_PROP_SUSTAINED_LIMIT,                       ///< (rw dynamic) The sustained power limit (data:
                                                            ///< ::xet_pwr_prop_sustained_limit_t)
            PWR_PROP_BURST_LIMIT,                           ///< (rw dynamic) The burst power limit (data:
                                                            ///< ::xet_pwr_prop_burst_limit_t)
            PWR_PROP_PEAK_LIMIT,                            ///< (rw dynamic) The peak power limit (data: ::xet_pwr_prop_peak_limit_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency domain types
        enum class freq_domain_type_t
        {
            INDEPENDENT = 0,                                ///< The frequency of this domain can be managed independently of other
                                                            ///< domains
            DEPENDENT,                                      ///< The frequency of this domain is dependent on another domain through a
                                                            ///< clock divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief DVFS mode
        enum class dvfs_mode_t
        {
            MIN = 0,                                        ///< Fixed minimum frequency will be requested unless specific applications
                                                            ///< request otherwise.
            EFFICIENT,                                      ///< Dynamic frequency management that prefers power saving over
                                                            ///< performance.
            STABLE,                                         ///< Fixed frequency that should not be throttled under normal operating
                                                            ///< conditions.
            DEFAULT,                                        ///< Dynamic frequency management that balances power and performance.
            AGGRESSIVE,                                     ///< Dynamic frequency management that trades more power for better
                                                            ///< performance.
            MAX,                                            ///< Fixed maximum frequency.

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
        /// @brief Frequency domain resource properties
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
        enum class freq_properties_t
        {
            FREQ_PROP_ACCEL_ASSETS = 0,                     ///< (ro static) List of accelerator assets that are connected to this
                                                            ///< power domain (data: ::xet_freq_prop_accel_assets_t)
            FREQ_PROP_DOMAIN_TYPE,                          ///< (ro static) The type of frequency domain (data:
                                                            ///< ::xet_freq_prop_domain_type_t)
            FREQ_PROP_AVAIL_CLOCKS,                         ///< (ro static) Available frequency clocks that this domain can run at
                                                            ///< (data: ::xet_freq_prop_avail_clocks_t)
            FREQ_PROP_AVAIL_DIVIDERS,                       ///< (ro static) Available dividers that this domain can run with (data:
                                                            ///< ::xet_freq_prop_avail_dividers_t)
            FREQ_PROP_SRC_FREQ,                             ///< (ro static) Get the resource ID of the source frequency domain
                                                            ///< resource if the type is dependent (data: ::xet_freq_prop_src_freq_t)
            FREQ_PROP_DVFS_MODE,                            ///< (rw dynamic) The operating mode of dynamic frequency management for
                                                            ///< this domain (data: ::xet_freq_prop_dvfs_mode_t)
            FREQ_PROP_FREQ_RANGE,                           ///< (rw dynamic) The frequencies between which dynamic frequency
                                                            ///< management operates (data: ::xet_freq_prop_freq_range_t)
            FREQ_PROP_FREQ_TDP,                             ///< (ro dynamic) The maximum frequency supported under the current TDP
                                                            ///< conditions (data: ::xet_freq_prop_freq_tdp_t)
            FREQ_PROP_FREQ_EFFICIENT,                       ///< (ro dynamic) The efficient minimum frequency (data:
                                                            ///< ::xet_freq_prop_freq_efficient_t)
            FREQ_PROP_FREQ_REQUEST,                         ///< (ro dynamic) The current frequency request (data:
                                                            ///< ::xet_freq_prop_freq_request_t)
            FREQ_PROP_FREQ_RESOLVED,                        ///< (ro dynamic) The resolved frequency (data:
                                                            ///< ::xet_freq_prop_freq_resolved_t)
            FREQ_PROP_FREQ_DIVIDER,                         ///< (rw dynamic) The current frequency divider for dependent frequency
                                                            ///< domains (data: ::xet_freq_prop_freq_divider_t)
            FREQ_PROP_THROTTLE_REASONS,                     ///< (ro dynamic) The reasons that the frequency is being limited by the
                                                            ///< PCU (data: ::xet_freq_prop_throttle_reasons_t)
            FREQ_PROP_THROTTLE_TIME,                        ///< (ro dynamic) The total time that the frequency has been limited by the
                                                            ///< PCU (data: ::xet_freq_prop_throttle_time_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Power-well domain promotion modes
        enum class pwrwell_promo_mode_t
        {
            IMMEDIATE = 0,                                  ///< The power-well will shutdown immediately when all contained units are
                                                            ///< idle.
            EFFICIENT,                                      ///< Favor energy savings over performance. The power-well is more likely
                                                            ///< to shutdown when all contained units are idle, even if this will cause
                                                            ///< some performance degredation.
            DEFAULT,                                        ///< Best compromise between performance and energy savings.
            PERFORMANCE,                                    ///< Favor performance over energy savings. The power-well is more likely
                                                            ///< to stay on when all contained units are idle since it has dedicated
                                                            ///< that more work will be executing shortly.
            NEVER,                                          ///< The power-well will never shutdown. This can improve performance but
                                                            ///< uses more energy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Power-well domain resource properties
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
        enum class pwrwell_properties_t
        {
            PWRWELL_PROP_ACCEL_ASSETS = 0,                  ///< (ro static) List of accelerator assets that are connected to this
                                                            ///< power-well domain (data: ::xet_pwrwell_prop_accel_assets_t)
            PWRWELL_PROP_PROMO_CAP,                         ///< (ro static) Find out if the power-well domain has a programmable
                                                            ///< promotion setting (data: ::xet_pwrwell_prop_promo_cap_t)
            PWRWELL_PROP_PROMO_MODE,                        ///< (rw dynamic) The current promotion mode (data:
                                                            ///< ::xet_pwrwell_prop_promo_mode_t)
            PWRWELL_PROP_UTILIZATION,                       ///< (ro dynamic) Monotonic counters for the amount of time the power-well
                                                            ///< is off/idle/active (data: ::xet_pwrwell_prop_utilization_t)
            PWRWELL_PROP_TRANSITIONS,                       ///< (ro dynamic) The monotonic counter for the number of times that the
                                                            ///< power-well has transitioned between off/idle/active states (data:
                                                            ///< ::xet_pwrwell_prop_transitions_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Accelerator asset resource properties
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
        enum class accel_properties_t
        {
            ACCEL_PROP_ACCEL_ASSETS = 0,                    ///< (ro static) List of accelerator assets that contribute to counters in
                                                            ///< this resource (data: ::xet_accel_prop_accel_assets_t)
            ACCEL_PROP_UTILIZATION,                         ///< (ro dynamic) The total wall time accelerator assets in this resource
                                                            ///< are active (data: ::xet_accel_prop_utilization_t)

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
        /// @brief Memory retire reasons
        enum class mem_retire_reason_t
        {
            MULTIPLE_SINGLE_BIT_ERRORS = 0,                 ///< Memory page has been retired due to multiple single bit ECC errors
            DOUBLE_BIT_ERRORS,                              ///< Memory page has been retired due to one or more double bit ECC errors

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory resource properties
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
        enum class mem_properties_t
        {
            MEM_PROP_TYPE = 0,                              ///< (ro static) The type of memory covered by this resource (data:
                                                            ///< ::xet_mem_prop_type_t)
            MEM_PROP_ECC_CAP,                               ///< (ro static) Indicates if this memory resource supports ECC/RAS
                                                            ///< features (data: ::xet_mem_prop_ecc_cap_t)
            MEM_PROP_BAD_LIST,                              ///< (ro static) Get the list of pages that have been permanently marked
                                                            ///< bad (data: ::xet_mem_prop_bad_list_t)
            MEM_PROP_UTILIZATION,                           ///< (ro dynamic) Get current allocated/unallocated size (data:
                                                            ///< ::xet_mem_prop_utilization_t)
            MEM_PROP_BANDWIDTH,                             ///< (ro dynamic) Get current read/write bandwidth counters and maximum
                                                            ///< bandwidth (data: ::xet_mem_prop_bandwidth_t)
            MEM_PROP_ECC_ENABLE,                            ///< (rw dynamic) Determine if ECC is enabled/disabled or change this
                                                            ///< setting (data: ::xet_mem_prop_ecc_enable_t)
            MEM_PROP_ECC_POISON,                            ///< (wo dynamic) Poison the memory resource (data:
                                                            ///< ::xet_mem_prop_ecc_poison_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Link resource types
        enum class link_type_t
        {
            PCI = 0,                                        ///< PCI connection
            PEER_TO_PEER,                                   ///< Peer-to-peer connection

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Link resource properties
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
        enum class link_properties_t
        {
            LINK_PROP_TYPE = 0,                             ///< (ro static) The type of link (data: ::xet_link_prop_type_t)
            LINK_PROP_BUS_ADDRESS,                          ///< (ro static) The bus address of the link (data:
                                                            ///< ::xet_link_prop_bus_address_t)
            LINK_PROP_PWR_CAP,                              ///< (ro static) Indicates if the link frequency can adjust to control
                                                            ///< power (data: ::xet_link_prop_pwr_cap_t)
            LINK_PROP_AVAIL_SPEEDS,                         ///< (ro static) Available link speeds (data:
                                                            ///< ::xet_link_prop_avail_speeds_t)
            LINK_PROP_MAX_PACKET_SIZE,                      ///< (ro static) Maximum packet size (data:
                                                            ///< ::xet_link_prop_max_packet_size_t)
            LINK_PROP_BANDWIDTH,                            ///< (ro dynamic) Monotonic bandwidth counters (data:
                                                            ///< ::xet_link_prop_bandwidth_t)
            LINK_PROP_SPEED,                                ///< (ro dynamic) Current link speed (data: ::xet_link_prop_speed_t)
            LINK_PROP_SPEED_RANGE,                          ///< (wo dynamic) Set the min/max speeds between which the link can operate
                                                            ///< (data: ::xet_link_prop_speed_range_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event types
        enum class event_type_t
        {
            FREQ_THROTTLED = 0,                             ///< The frequency is being throttled
            FREQ_POLICY_CHANGED,                            ///< Another API client has modified frequency domain properties
            RAS_ERRORS,                                     ///< ECC/RAS errors
            COUNT,                                          ///< The number of event types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource ID
        struct resource_id_t
        {
            resource_type_t type;                           ///< [in,out] Resource type
            uint32_t index;                                 ///< [in,out] Resource index (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::xet_resource_type_t]-1)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Filter RAS errors
        struct ras_filter_t
        {
            resource_id_t resourceId;                       ///< [in] Filter based on resource ID. Set to ::XET_RESOURCE_ID_ANY to get
                                                            ///< errors from anywhere in the device
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
        struct res_error_t
        {
            uint32_t type;                                  ///< [out] Bitfield describing type of error, constructed from one or more
                                                            ///< of ::xet_ras_error_type_t
            uint32_t loc;                                   ///< [out] Bitfield describing structural location of the error,
                                                            ///< constructed from one of ::xet_ras_error_loc_t
            ras_data_type_t dataType;                       ///< [out] How to interpret the data
            uint64_t data;                                  ///< [out] The value of the error - interpretation depends on dataType
            resource_id_t resourceId;                       ///< [out] Resource where the error was generated. If the error doesn't
                                                            ///< come from a specific resource, this will be ::XET_RESOURCE_ID_ANY

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data about one type of accelerator asset
        struct device_prop_accel_asset_t
        {
            accel_asset_t type;                             ///< [out] The type of asset
            uint32_t numBlocks;                             ///< [out] The number of blocks of this asset type
            uint32_t numEngines;                            ///< [out] The number of submission engines for this type of asset

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Generic SMI information about a device
        struct info_t
        {
            uint64_t assetBitfield;                         ///< [out] A bitfield of assets (1<<::xet_accel_asset_t) available in the
                                                            ///< resource
            device_prop_accel_asset_t assetInfo[static_cast<int>(accel_asset_t::MAX_TYPES)];///< [out] Information about each asset.
            uint32_t numRas;                                ///< [out] The total number of RAS elements available for querying in this
                                                            ///< device.
            uint32_t rasTypes;                              ///< [out] Bitfield of the type of RAS elements (::xet_ras_error_type_t)
                                                            ///< available for querying in this device.
            uint32_t rasLocations;                          ///< [out] Bitfield of the structure location of RAS elements
                                                            ///< (::xet_ras_error_loc_t) available for querying in this device.
            uint32_t numResourcesByType[static_cast<int>(resource_type_t::MAX_TYPES)];  ///< [out] The number of resources of each type in this device.

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
        /// @brief Data for property ::XET_DEVICE_PROP_SERIAL_NUMBER
        struct device_prop_serial_number_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_BOARD_NUMBER
        struct device_prop_board_number_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_BRAND
        struct device_prop_brand_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_MODEL
        struct device_prop_model_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_DEVICEID
        struct device_prop_deviceid_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_VENDOR_NAME
        struct device_prop_vendor_name_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_DRIVER_VERSION
        struct device_prop_driver_version_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_DEVICE_PROP_BARS
        struct device_prop_bars_t
        {
            uint32_t num;                                   ///< [out] The number of bars
            const pci_bar_info_t* pBars;                    ///< [out][range(0, num-1)] Information about each bar.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_DEVICE_PROP_COLD_SHUTDOWN
        struct device_prop_cold_shutdown_t
        {
            xe::bool_t doShutdown;                          ///< [in] Set to true to perform a cold shutdown of the device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_DEVICE_PROP_COLD_RESET
        struct device_prop_cold_reset_t
        {
            xe::bool_t doReset;                             ///< [in] Set to true to perform a cold shutdown of the device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a device property
        struct device_property_request_t
        {
            device_properties_t property;                   ///< [in] The property being requested (one of ::xet_device_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PSU_PROP_AMP_LIMIT
        struct psu_prop_amp_limit_t
        {
            uint32_t limit;                                 ///< [out] The maximum electrical current in amperes that can be drawn

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PSU_PROP_VOLTAGE_STATUS
        struct psu_prop_voltage_status_t
        {
            psu_voltage_status_t status;                    ///< [out] The current PSU voltage status)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PSU_PROP_FAN_FAILURE
        struct psu_prop_fan_failure_t
        {
            xe::bool_t status;                              ///< [out] Indicates if the fan has failed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PSU_PROP_TEMPERATURE
        struct psu_prop_temperature_t
        {
            uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees celcius

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PSU_PROP_AMPS
        struct psu_prop_amps_t
        {
            uint32_t current;                               ///< [out] The amps being drawn in amperes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a PSU resource property
        struct psu_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the PSU resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PSU]-1)
            psu_properties_t property;                      ///< [in] The property being requested (one of ::xet_psu_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_TEMP_PROP_TEMPERATURE
        struct temp_prop_temperature_t
        {
            uint32_t temperature;                           ///< [out] The current temperature of the sensor in degrees celcius

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a temperature sensor resource property
        struct temp_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the temperature sensor resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_TEMP]-1)
            temp_properties_t property;                     ///< [in] The property being requested (one of ::xet_temp_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

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
        /// @brief Data for the property ::XET_FAN_PROP_MAX_RPM
        struct fan_prop_max_rpm_t
        {
            uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_MAX_TABLE_SIZE
        struct fan_prop_max_table_size_t
        {
            uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_SPEED_RPM
        struct fan_prop_speed_rpm_t
        {
            uint32_t speed;                                 ///< [out] The current fan speed in units of revolutions per minute (rpm)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_SPEED_PERCENT
        struct fan_prop_speed_percent_t
        {
            uint32_t speed;                                 ///< [out] The current fan speed as a percentage of the maximum speed of
                                                            ///< that fan

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_MODE
        struct fan_prop_mode_t
        {
            fan_speed_mode_t mode;                          ///< [in,out] The current fan speed mode (one of ::xet_fan_speed_mode_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_FIXED_SPEED
        struct fan_prop_fixed_speed_t
        {
            uint32_t speed;                                 ///< [in,out] The speed of the fan
            fan_speed_units_t units;                        ///< [in,out] The units of the member speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_SPEED_TABLE
        struct fan_prop_speed_table_t
        {
            uint32_t* pCount;                               ///< [in,out] The number of temp/speed pairs.
                                                            ///< When reading the current fan speed table, this will be set to the
                                                            ///< number of points returned.
                                                            ///< When setting the fan speed table, this specifies the number of valid
                                                            ///< points in the table.
            fan_temp_speed_t points[XET_FAN_TEMP_SPEED_PAIR_COUNT]; ///< [in,out][range(0, *pCount)] Array of temperature/fan speed pairs

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a fan resource property
        struct fan_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the fan resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FAN]-1)
            fan_properties_t property;                      ///< [in] The property being requested (one of ::xet_fan_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LED_PROP_RGB_CAP
        struct led_prop_rgb_cap_t
        {
            xe::bool_t haveRGB;                             ///< [out] Indicates if the LED is RGB capable

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LED_PROP_STATE
        struct led_prop_state_t
        {
            xe::bool_t isOn;                                ///< [in,out] Indicates if the LED is on or off
            uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
            uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
            uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a LED resource property
        struct led_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the LED resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_LED]-1)
            led_properties_t property;                      ///< [in] The property being requested (one of ::xet_led_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_FIRMWARE_PROP_NAME
        struct firmware_prop_name_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_FIRMWARE_PROP_VERSION
        struct firmware_prop_version_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FIRMWARE_PROP_CHECK
        struct firmware_prop_check_t
        {
            uint32_t checksum;                              ///< [out] The calculated checksum of the loaded firmware image

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FIRMWARE_PROP_FLASH
        struct firmware_prop_flash_t
        {
            void* pImage;                                   ///< [in] Pointer to the image to be flashed
            uint32_t size;                                  ///< [in] Size in bytes of the image pointed to by pImage

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a firmware resource property
        struct firmware_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the firmware resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FIRMWARE]-1)
            firmware_properties_t property;                 ///< [in] The property being requested (one of
                                                            ///< ::xet_firmware_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_ACCEL_ASSETS
        struct pwr_prop_accel_assets_t
        {
            uint64_t assets;                                ///< [out] List of accelerator assets that contribute to this power domain
                                                            ///< (Bitfield of (1<<::xet_accel_asset_t)).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_MAX_LIMIT
        struct pwr_prop_max_limit_t
        {
            uint32_t assets;                                ///< [out] The maximum power limit in milliwatts that can be requested.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_ENERGY_COUNTER
        struct pwr_prop_energy_counter_t
        {
            uint64_t energy;                                ///< [out] The value of the monotonic energy counter in millijoules.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_SUSTAINED_LIMIT
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency if
        ///       the power averaged over a window (typically seconds) exceeds this
        ///       limit.
        struct pwr_prop_sustained_limit_t
        {
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts
            uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_BURST_LIMIT
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency of
        ///       the device if the power averaged over a few milliseconds exceeds a
        ///       limit known as PL2. Typically PL2 > PL1 so that it permits the
        ///       frequency to burst higher for short periods than would be otherwise
        ///       permitted by PL1.
        struct pwr_prop_burst_limit_t
        {
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_PEAK_LIMIT
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
        struct pwr_prop_peak_limit_t
        {
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a power domain resource property
        struct pwr_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the power domain resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PWR]-1)
            pwr_properties_t property;                      ///< [in] The property being requested (one of ::xet_pwr_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency divider element
        /// 
        /// @details
        ///     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_DEPENDENT is
        ///       obtained by the formula:
        ///     - freq = source domain freq * numerator / denominator
        struct freq_divider_t
        {
            uint16_t numerator;                             ///< [in,out] numerator of the ratio
            uint16_t denominator;                           ///< [in,out] denominator of the ratio

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_ACCEL_ASSETS
        struct freq_prop_accel_assets_t
        {
            uint64_t assets;                                ///< [out] List of accelerator assets that are connected to this power
                                                            ///< domain (Bitfield of (1<<::xet_accel_asset_t)).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_DOMAIN_TYPE
        struct freq_prop_domain_type_t
        {
            freq_domain_type_t type;                        ///< [out] The type of frequency domain

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_AVAIL_CLOCKS
        /// 
        /// @details
        ///     - The list is ordered from the smallest frequency to the largest
        ///       frequency.
        struct freq_prop_avail_clocks_t
        {
            uint32_t num;                                   ///< [out] The number of clocks
            const uint32_t* pClocks;                        ///< [out] Array of clock frequencies in MHz ordered from smallest to
                                                            ///< largest.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_AVAIL_DIVIDERS
        /// 
        /// @details
        ///     - The list is ordered from the smallest ratio to the largest ratio.
        struct freq_prop_avail_dividers_t
        {
            uint32_t num;                                   ///< [out] The number of dividers
            const freq_divider_t* pDividers;                ///< [out] Array of numerator/denominator for each divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_SRC_FREQ
        struct freq_prop_src_freq_t
        {
            resource_id_t resourceId;                       ///< [out] The resource ID of the source frequency domain

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_DVFS_MODE
        struct freq_prop_dvfs_mode_t
        {
            dvfs_mode_t mode;                               ///< [in,out] The DVFS operating mode

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_RANGE
        struct freq_prop_freq_range_t
        {
            uint32_t min;                                   ///< [in,out] Minimum frequency in MHz
            uint16_t max;                                   ///< [in,out] Maximum frequency in MHz

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_TDP
        struct freq_prop_freq_tdp_t
        {
            uint32_t freqTdp;                               ///< [out] The maximum frequency in MHz supported under the current TDP
                                                            ///< conditions

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_EFFICIENT
        struct freq_prop_freq_efficient_t
        {
            uint32_t freqEfficient;                         ///< [out] The efficient minimum frequency in MHz

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_REQUEST
        struct freq_prop_freq_request_t
        {
            uint32_t freqRequest;                           ///< [out] The current frequency request in MHz

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_RESOLVED
        struct freq_prop_freq_resolved_t
        {
            uint32_t freqResolved;                          ///< [out] The resolved frequency in MHz

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_DIVIDER
        struct freq_prop_freq_divider_t
        {
            freq_divider_t divider;                         ///< [in,out] The frequency divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_REASONS
        struct freq_prop_throttle_reasons_t
        {
            uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the PCU
                                                            ///< (Bitfield of (1<<::xet_freq_throttle_reasons_t)).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_TIME
        struct freq_prop_throttle_time_t
        {
            uint32_t throttleTime;                          ///< [out] The total time in microseconds that the frequency has been
                                                            ///< limited by the PCU.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a frequency domain resource property
        struct freq_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the frequency domain resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_FREQ]-1)
            freq_properties_t property;                     ///< [in] The property being requested (one of ::xet_freq_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWRWELL_PROP_ACCEL_ASSETS
        struct pwrwell_prop_accel_assets_t
        {
            uint64_t assets;                                ///< [out] List of accelerator assets that are connected to this power-well
                                                            ///< domain (bitfield of (1<<::xet_accel_asset_t)).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_CAP
        struct pwrwell_prop_promo_cap_t
        {
            xe::bool_t canChangePromoMode;                  ///< [out] Indicates if the power-well domain has a programmable promotion
                                                            ///< setting.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_MODE
        struct pwrwell_prop_promo_mode_t
        {
            pwrwell_promo_mode_t mode;                      ///< [in,out] Current promotion mode

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWRWELL_PROP_UTILIZATION
        struct pwrwell_prop_utilization_t
        {
            uint32_t sleepCounter;                          ///< [out] The monotonic counter for the amount of time in microseconds
                                                            ///< that the power-well is off.
            uint32_t idleCounter;                           ///< [out] The monotonic counter for the amount of time in microseconds
                                                            ///< that the power-well is on but not executing any accelerator workloads.
            uint32_t activeCounter;                         ///< [out] The monotonic counter for the amount of time the power-well is
                                                            ///< on and executing accelerator workloads.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWRWELL_PROP_TRANSITIONS
        struct pwrwell_prop_transitions_t
        {
            uint32_t wakeCounter;                           ///< [out] The monotonic counter for the number of times that the
                                                            ///< power-well has transitioned from a sleep state to a powered on state.
            uint32_t execCounter;                           ///< [out] The monotonic counter for the number of times that the
                                                            ///< power-well has transitioned from a sleep or idle state to an active
                                                            ///< state.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a power-well domain resource property
        struct pwrwell_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the power-well domain resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_PWRWELL]-1)
            pwrwell_properties_t property;                  ///< [in] The property being requested (one of ::xet_pwrwell_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_ACCEL_PROP_ACCEL_ASSETS
        struct accel_prop_accel_assets_t
        {
            uint64_t assets;                                ///< [out] List of accelerator assets that contribute to counters in this
                                                            ///< resource (bitfield of (1<<::xet_accel_asset_t)).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_ACCEL_PROP_UTILIZATION
        struct accel_prop_utilization_t
        {
            uint32_t activeCounter;                         ///< [out] Monotonic counter for total wall time in microseconds that
                                                            ///< accelerator assets in this resource are active.
            uint32_t idleCounter;                           ///< [out] Monotonic counter for total wall time in microseconds that no
                                                            ///< accelerator assets in this resource are active.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query an accelerator resource property
        struct accel_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the accelerator resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_ACCEL]-1)
            accel_properties_t property;                    ///< [in] The property being requested (one of ::xet_accel_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retired page info
        struct mem_retire_info_t
        {
            uint64_t address;                               ///< [out] The address of the page
            mem_retire_reason_t reason;                     ///< [out] The reason the page was retired

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_TYPE
        struct mem_prop_type_t
        {
            mem_type_t type;                                ///< [out] The memory type

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_ECC_CAP
        struct mem_prop_ecc_cap_t
        {
            xe::bool_t isEccCapable;                        ///< [out] Indicates if this memory resource supports ECC/RAS features.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_BAD_LIST
        struct mem_prop_bad_list_t
        {
            uint32_t* pCount;                               ///< [in,out] The number of elements in pList
                                                            ///< If pCount is zero, then the driver will update the value with the
                                                            ///< number of elements needed to store the bad list.
                                                            ///< If pCount is less than that required to store the bad list, the driver
                                                            ///< will update the value with the required number of elements and return
                                                            ///< an error.
                                                            ///< If pCount is larger than that required to store the bad list, the
                                                            ///< driver will update the value with the number of elements actually returned.
            mem_retire_info_t* pList;                       ///< [in] Pointer to storage for information about each bad page.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_UTILIZATION
        struct mem_prop_utilization_t
        {
            uint64_t allocated;                             ///< [out] The total allocated bytes
            uint64_t unallocated;                           ///< [out] The total unallocated bytes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_BANDWIDTH
        struct mem_prop_bandwidth_t
        {
            uint32_t readCounter;                           ///< [out] Total bytes read from memory
            uint32_t writeCounter;                          ///< [out] Total bytes written to memory
            uint32_t maxBandwidth;                          ///< [out] Current maximum bandwidth in units of bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_ECC_ENABLE
        struct mem_prop_ecc_enable_t
        {
            xe::bool_t enable;                              ///< [in] Whether or not ECC is enabled

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_ECC_POISON
        struct mem_prop_ecc_poison_t
        {
            xe::bool_t doPoison;                            ///< [out] Poison the memory resource.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a memory resource property
        struct mem_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the memory resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_MEM]-1)
            mem_properties_t property;                      ///< [in] The property being requested (one of ::xet_mem_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

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
        /// @brief Data for property ::XET_LINK_PROP_TYPE
        struct link_prop_type_t
        {
            link_type_t type;                               ///< [out] The type of link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_LINK_PROP_BUS_ADDRESS
        struct link_prop_bus_address_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_PWR_CAP
        struct link_prop_pwr_cap_t
        {
            xe::bool_t havePwrMgmt;                         ///< [out] Indicates if the link frequency can adjust to control power.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_AVAIL_SPEEDS
        /// 
        /// @details
        ///     - The list is ordered from the smallest ratio to the largest ratio.
        struct link_prop_avail_speeds_t
        {
            uint32_t num;                                   ///< [out] The number of elements in pList
            const link_speed_t* pList;                      ///< [out][range(0, num-1)] Pointer to an array of link speeds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_MAX_PACKET_SIZE
        struct link_prop_max_packet_size_t
        {
            uint32_t maxPacketSize;                         ///< [out] Maximum packet size in bytes.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_BANDWIDTH
        struct link_prop_bandwidth_t
        {
            uint32_t recvCounter;                           ///< [out] Total bytes received across the link
            uint32_t sendCounter;                           ///< [out] Total bytes sent across the link
            uint32_t maxBandwidth;                          ///< [out] Maximum bytes/sec that can be transfered acros the link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_SPEED
        struct link_prop_speed_t
        {
            const link_speed_t* pSpeed;                     ///< [out] Pointer to the current speed configuration

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_SPEED_RANGE
        struct link_prop_speed_range_t
        {
            const link_speed_t* pMinSpeed;                  ///< [out] Pointer to the min speed configuration (one of those in the
                                                            ///< array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)
            const link_speed_t* pMaxSpeed;                  ///< [out] Pointer to the max speed configuration (one of those in the
                                                            ///< array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to query a link resource property
        struct link_property_request_t
        {
            uint32_t index;                                 ///< [in] The index of the link resource (0 ...
                                                            ///< ::xet_sysman_info_t.numResourcesByType[::XET_RESOURCE_TYPE_LINK]-1)
            link_properties_t property;                     ///< [in] The property being requested (one of ::xet_link_properties_t).
            void* pData;                                    ///< [in] Pointer to the data for the property.
                                                            ///< Each property has a corresponding data structure. The type of the data
                                                            ///< structure is derived from the property enumerator, converted to
                                                            ///< lower-case with "_t" appended.
            uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Request structure used to register/unregister events
        struct event_request_t
        {
            event_type_t event;                             ///< [in] The event type to register.
            resource_id_t resourceId;                       ///< [in] Only events being generated by the specified resource. If
                                                            ///< ::XET_RESOURCE_ID_ANY, then applies to all events from all resources
                                                            ///< in the device.
            uint32_t threshold;                             ///< [in] The application only receives a notification when the total count
                                                            ///< exceeds this value. Set to zero to receive a notification for every
                                                            ///< new event.

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
        /// @brief Creates a handle to access SMI features for a device
        /// 
        /// @details
        ///     - Initializes internal structures to support SMI features.
        ///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is specified, no
        ///       access right checks are made during initialization. The check is done
        ///       in functions that attempt to control a device.
        ///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is not specified, any
        ///       function attempting to control a device will return
        ///       ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS.
        ///     - Multiple SMI handles can be created for the same device and concurrent
        ///       access through each handle to access underlying hardware resources is
        ///       supported.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **nvmlInit**
        ///     - **rsmi_init**
        /// @returns
        ///     - Sysman*: Handle for accessing SMI features
        /// 
        /// @throws result_t
        static Sysman* __xecall
        Create(
            Device* pDevice,                                ///< [in] Handle of the device
            version_t version,                              ///< [in] SMI version that application was built with
            uint32_t flags                                  ///< [in] Bitfield of ::xet_sysman_init_flags_t
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a SMI handle
        /// 
        /// @details
        ///     - Only once all SMI handles to a device have been destroyed will
        ///       internal data structures be freed from the application memory.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **nvmlShutdown**
        ///     - **rsmi_shut_down**
        /// @throws result_t
        static void __xecall
        Destroy(
            Sysman* pSysman                                 ///< [in][release] SMI handle to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get human-readable name for an accelerator asset
        /// @throws result_t
        void __xecall
        GetAccelAssetName(
            accel_asset_t type,                             ///< [in] The type of accelerator asset
            const char** ppName                             ///< [in] Pointer to the asset name
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get SMI information for a device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetInfo(
            info_t* pInfo                                   ///< [in] Returned information
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get RAS errors that have occurred
        /// 
        /// @details
        ///     - Returned errors can be filtered by resource, type, location and
        ///       threshold.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetRasErrors(
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
            res_error_t* pErrors                            ///< [in] Array of error data
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get device property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetDeviceProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            device_property_request_t* pRequest             ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set device property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetDeviceProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            device_property_request_t* pRequest             ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PSU resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetPsuProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            psu_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set PSU resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetPsuProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            psu_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get temperature sensor resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetTempProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            temp_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get fan resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetFanProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            fan_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set fan resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetFanProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            fan_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get LED resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetLedProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            led_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set LED resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetLedProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            led_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetFirmwareProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            firmware_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set firmware resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetFirmwareProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            firmware_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power domain resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetPwrProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            pwr_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set power power resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetPwrProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            pwr_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency domain resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetFreqProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            freq_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set frequency domain resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetFreqProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            freq_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power-well domain resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetPwrwellProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            pwrwell_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set power-well domain resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetPwrwellProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            pwrwell_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get accelerator resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetAccelProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            accel_property_request_t* pRequest              ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetMemProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            mem_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set memory resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetMemProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            mem_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get link resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetLinkProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            link_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set link resource property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetLinkProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pRequest
            link_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
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
        void __xecall
        GetEvents(
            xe::bool_t clear,                               ///< [in] Clear the event status.
            uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                            ///< check status and return immediately. Set to ::XET_EVENT_WAIT_INFINITE
                                                            ///< to block until events arrive.
            uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                            ///< triggered.
            );

    };

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::init_flags_t to std::string
    std::string to_string( const Sysman::init_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_type_t to std::string
    std::string to_string( const Sysman::resource_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_id_t to std::string
    std::string to_string( const Sysman::resource_id_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_asset_t to std::string
    std::string to_string( const Sysman::accel_asset_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_type_t to std::string
    std::string to_string( const Sysman::ras_error_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_loc_t to std::string
    std::string to_string( const Sysman::ras_error_loc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_data_type_t to std::string
    std::string to_string( const Sysman::ras_data_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_filter_t to std::string
    std::string to_string( const Sysman::ras_filter_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::res_error_t to std::string
    std::string to_string( const Sysman::res_error_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_accel_asset_t to std::string
    std::string to_string( const Sysman::device_prop_accel_asset_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::info_t to std::string
    std::string to_string( const Sysman::info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_type_t to std::string
    std::string to_string( const Sysman::pci_bar_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_info_t to std::string
    std::string to_string( const Sysman::pci_bar_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_properties_t to std::string
    std::string to_string( const Sysman::device_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_serial_number_t to std::string
    std::string to_string( const Sysman::device_prop_serial_number_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_board_number_t to std::string
    std::string to_string( const Sysman::device_prop_board_number_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_brand_t to std::string
    std::string to_string( const Sysman::device_prop_brand_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_model_t to std::string
    std::string to_string( const Sysman::device_prop_model_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_deviceid_t to std::string
    std::string to_string( const Sysman::device_prop_deviceid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_vendor_name_t to std::string
    std::string to_string( const Sysman::device_prop_vendor_name_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_driver_version_t to std::string
    std::string to_string( const Sysman::device_prop_driver_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_bars_t to std::string
    std::string to_string( const Sysman::device_prop_bars_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_cold_shutdown_t to std::string
    std::string to_string( const Sysman::device_prop_cold_shutdown_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_cold_reset_t to std::string
    std::string to_string( const Sysman::device_prop_cold_reset_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_property_request_t to std::string
    std::string to_string( const Sysman::device_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_voltage_status_t to std::string
    std::string to_string( const Sysman::psu_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_properties_t to std::string
    std::string to_string( const Sysman::psu_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_amp_limit_t to std::string
    std::string to_string( const Sysman::psu_prop_amp_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_voltage_status_t to std::string
    std::string to_string( const Sysman::psu_prop_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_fan_failure_t to std::string
    std::string to_string( const Sysman::psu_prop_fan_failure_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_temperature_t to std::string
    std::string to_string( const Sysman::psu_prop_temperature_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_amps_t to std::string
    std::string to_string( const Sysman::psu_prop_amps_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_property_request_t to std::string
    std::string to_string( const Sysman::psu_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_properties_t to std::string
    std::string to_string( const Sysman::temp_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_prop_temperature_t to std::string
    std::string to_string( const Sysman::temp_prop_temperature_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_property_request_t to std::string
    std::string to_string( const Sysman::temp_property_request_t val );

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
    /// @brief Converts Sysman::fan_prop_max_rpm_t to std::string
    std::string to_string( const Sysman::fan_prop_max_rpm_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_max_table_size_t to std::string
    std::string to_string( const Sysman::fan_prop_max_table_size_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_speed_rpm_t to std::string
    std::string to_string( const Sysman::fan_prop_speed_rpm_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_speed_percent_t to std::string
    std::string to_string( const Sysman::fan_prop_speed_percent_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_mode_t to std::string
    std::string to_string( const Sysman::fan_prop_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_fixed_speed_t to std::string
    std::string to_string( const Sysman::fan_prop_fixed_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_speed_table_t to std::string
    std::string to_string( const Sysman::fan_prop_speed_table_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_property_request_t to std::string
    std::string to_string( const Sysman::fan_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_properties_t to std::string
    std::string to_string( const Sysman::led_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_prop_rgb_cap_t to std::string
    std::string to_string( const Sysman::led_prop_rgb_cap_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_prop_state_t to std::string
    std::string to_string( const Sysman::led_prop_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_property_request_t to std::string
    std::string to_string( const Sysman::led_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_properties_t to std::string
    std::string to_string( const Sysman::firmware_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_prop_name_t to std::string
    std::string to_string( const Sysman::firmware_prop_name_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_prop_version_t to std::string
    std::string to_string( const Sysman::firmware_prop_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_prop_check_t to std::string
    std::string to_string( const Sysman::firmware_prop_check_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_prop_flash_t to std::string
    std::string to_string( const Sysman::firmware_prop_flash_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_property_request_t to std::string
    std::string to_string( const Sysman::firmware_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_properties_t to std::string
    std::string to_string( const Sysman::pwr_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::pwr_prop_accel_assets_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_max_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_max_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_energy_counter_t to std::string
    std::string to_string( const Sysman::pwr_prop_energy_counter_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_sustained_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_sustained_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_burst_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_burst_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_peak_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_peak_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_property_request_t to std::string
    std::string to_string( const Sysman::pwr_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_domain_type_t to std::string
    std::string to_string( const Sysman::freq_domain_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::dvfs_mode_t to std::string
    std::string to_string( const Sysman::dvfs_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_throttle_reasons_t to std::string
    std::string to_string( const Sysman::freq_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_divider_t to std::string
    std::string to_string( const Sysman::freq_divider_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_properties_t to std::string
    std::string to_string( const Sysman::freq_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::freq_prop_accel_assets_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_domain_type_t to std::string
    std::string to_string( const Sysman::freq_prop_domain_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_avail_clocks_t to std::string
    std::string to_string( const Sysman::freq_prop_avail_clocks_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_avail_dividers_t to std::string
    std::string to_string( const Sysman::freq_prop_avail_dividers_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_src_freq_t to std::string
    std::string to_string( const Sysman::freq_prop_src_freq_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_dvfs_mode_t to std::string
    std::string to_string( const Sysman::freq_prop_dvfs_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_range_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_range_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_tdp_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_tdp_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_efficient_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_efficient_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_request_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_resolved_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_resolved_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_divider_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_divider_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_throttle_reasons_t to std::string
    std::string to_string( const Sysman::freq_prop_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_throttle_time_t to std::string
    std::string to_string( const Sysman::freq_prop_throttle_time_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_property_request_t to std::string
    std::string to_string( const Sysman::freq_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_promo_mode_t to std::string
    std::string to_string( const Sysman::pwrwell_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_properties_t to std::string
    std::string to_string( const Sysman::pwrwell_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_accel_assets_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_promo_cap_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_promo_cap_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_promo_mode_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_utilization_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_utilization_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_transitions_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_transitions_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_property_request_t to std::string
    std::string to_string( const Sysman::pwrwell_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_properties_t to std::string
    std::string to_string( const Sysman::accel_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::accel_prop_accel_assets_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_prop_utilization_t to std::string
    std::string to_string( const Sysman::accel_prop_utilization_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_property_request_t to std::string
    std::string to_string( const Sysman::accel_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_type_t to std::string
    std::string to_string( const Sysman::mem_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_retire_reason_t to std::string
    std::string to_string( const Sysman::mem_retire_reason_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_retire_info_t to std::string
    std::string to_string( const Sysman::mem_retire_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_properties_t to std::string
    std::string to_string( const Sysman::mem_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_type_t to std::string
    std::string to_string( const Sysman::mem_prop_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_ecc_cap_t to std::string
    std::string to_string( const Sysman::mem_prop_ecc_cap_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_bad_list_t to std::string
    std::string to_string( const Sysman::mem_prop_bad_list_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_utilization_t to std::string
    std::string to_string( const Sysman::mem_prop_utilization_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_bandwidth_t to std::string
    std::string to_string( const Sysman::mem_prop_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_ecc_enable_t to std::string
    std::string to_string( const Sysman::mem_prop_ecc_enable_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_ecc_poison_t to std::string
    std::string to_string( const Sysman::mem_prop_ecc_poison_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_property_request_t to std::string
    std::string to_string( const Sysman::mem_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_type_t to std::string
    std::string to_string( const Sysman::link_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_speed_t to std::string
    std::string to_string( const Sysman::link_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_properties_t to std::string
    std::string to_string( const Sysman::link_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_type_t to std::string
    std::string to_string( const Sysman::link_prop_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_bus_address_t to std::string
    std::string to_string( const Sysman::link_prop_bus_address_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_pwr_cap_t to std::string
    std::string to_string( const Sysman::link_prop_pwr_cap_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_avail_speeds_t to std::string
    std::string to_string( const Sysman::link_prop_avail_speeds_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_max_packet_size_t to std::string
    std::string to_string( const Sysman::link_prop_max_packet_size_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_bandwidth_t to std::string
    std::string to_string( const Sysman::link_prop_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_speed_t to std::string
    std::string to_string( const Sysman::link_prop_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_speed_range_t to std::string
    std::string to_string( const Sysman::link_prop_speed_range_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_property_request_t to std::string
    std::string to_string( const Sysman::link_property_request_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_request_t to std::string
    std::string to_string( const Sysman::event_request_t val );

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_SYSMAN_HPP
