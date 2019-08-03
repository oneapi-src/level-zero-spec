/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_sysman.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#ifndef _XET_SYSMAN_H
#define _XET_SYSMAN_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of SMI
typedef enum _xet_sysman_version_t
{
    XET_SYSMAN_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} xet_sysman_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the handle to access SMI features for a device
/// 
/// @details
///     - The returned handle is unique
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == phSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGet(
    xet_device_handle_t hDevice,                    ///< [in] Handle of the device
    xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
    xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource types
typedef enum _xet_resource_type_t
{
    XET_RESOURCE_TYPE_DEV = 0x0,                    ///< Inventory resource
    XET_RESOURCE_TYPE_PWR = 0x1,                    ///< Power domain resource
    XET_RESOURCE_TYPE_FREQ = 0x2,                   ///< Frequency domain resource
    XET_RESOURCE_TYPE_UTIL = 0x3,                   ///< Resource used to monitor GPU utilization
    XET_RESOURCE_TYPE_MEM = 0x4,                    ///< Memory resource
    XET_RESOURCE_TYPE_LINK = 0x5,                   ///< Link resource
    XET_RESOURCE_TYPE_TEMP = 0x6,                   ///< Temperature sensor resource
    XET_RESOURCE_TYPE_STBY = 0x7,                   ///< Resource used to control standby mode
    XET_RESOURCE_TYPE_FW = 0x8,                     ///< Firmware resource
    XET_RESOURCE_TYPE_PSU = 0x9,                    ///< PSU resource
    XET_RESOURCE_TYPE_FAN = 0xA,                    ///< Fan resource
    XET_RESOURCE_TYPE_LED = 0xB,                    ///< LED resource
    XET_RESOURCE_TYPE_ANY = -1,                     ///< Any resource filter

} xet_resource_type_t;

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
typedef enum _xet_resid_t
{
    XET_RESID_DEV_INVENTORY = 0,                    ///< General device inventory
    XET_RESID_PWR_TOTAL = 0x10000,                  ///< Device total power
    XET_RESID_FREQ_GPU = 0x20000,                   ///< GPU frequency
    XET_RESID_FREQ_LOCAL_MEM = 0x20001,             ///< Local memory frequency
    XET_RESID_UTIL_GPU = 0x30000,                   ///< Utilization of the entire GPU
    XET_RESID_UTIL_COMPUTE = 0x30001,               ///< Utilization of the compute/3D units
    XET_RESID_UTIL_MEDIA = 0x30002,                 ///< Utilization of the media units
    XET_RESID_UTIL_VIDEO_DECODE = 0x30003,          ///< Utilization of the video decode units
    XET_RESID_UTIL_VIDEO_ENCODE = 0x30004,          ///< Utilization of the video encode units
    XET_RESID_MEM_LOCAL = 0x40000,                  ///< Local GPU memory
    XET_RESID_LINK_PCIE = 0x50000,                  ///< PCIe link
    XET_RESID_LINK_CD_PORT1 = 0x50001,              ///< High speed companion die switch port 1
    XET_RESID_LINK_CD_PORT2 = 0x50002,              ///< High speed companion die switch port 2
    XET_RESID_LINK_CD_PORT3 = 0x50003,              ///< High speed companion die switch port 3
    XET_RESID_LINK_CD_PORT4 = 0x50004,              ///< High speed companion die switch port 4
    XET_RESID_LINK_CD_PORT5 = 0x50005,              ///< High speed companion die switch port 5
    XET_RESID_LINK_CD_PORT6 = 0x50006,              ///< High speed companion die switch port 6
    XET_RESID_LINK_CD_PORT7 = 0x50007,              ///< High speed companion die switch port 7
    XET_RESID_LINK_CD_PORT8 = 0x50008,              ///< High speed companion die switch port 8
    XET_RESID_LINK_CD_PORT9 = 0x50009,              ///< High speed companion die switch port 9
    XET_RESID_LINK_CD_PORT10 = 0x5000A,             ///< High speed companion die switch port 10
    XET_RESID_LINK_CD_PORT11 = 0x5000B,             ///< High speed companion die switch port 11
    XET_RESID_LINK_CD_PORT12 = 0x5000C,             ///< High speed companion die switch port 12
    XET_RESID_LINK_CD_PORT13 = 0x5000D,             ///< High speed companion die switch port 13
    XET_RESID_LINK_CD_PORT14 = 0x5000E,             ///< High speed companion die switch port 14
    XET_RESID_LINK_CD_PORT15 = 0x5000F,             ///< High speed companion die switch port 15
    XET_RESID_LINK_CD_PORT16 = 0x50010,             ///< High speed companion die switch port 16
    XET_RESID_TEMP_MAX = 0x60000,                   ///< The maximum temperature reported by the sensors in the device
    XET_RESID_TEMP_GPU = 0x60001,                   ///< The maximum temperature reported by the sensors in the GPU component
                                                    ///< of the device
    XET_RESID_TEMP_LOCAL_MEM = 0x60002,             ///< The maximum temperature reported by the sensors in the local memory of
                                                    ///< device
    XET_RESID_STBY_GLOBAL = 0x70000,                ///< Control sleep promotion of the common parts of the device
    XET_RESID_STBY_COMPUTE = 0x70001,               ///< Control sleep promotion of the compute components of the GPU
    XET_RESID_STBY_MEDIA = 0x70002,                 ///< Control sleep promotion of the media components of the GPU
    XET_RESID_FW_1 = 0x80001,                       ///< Firmware 1
    XET_RESID_FW_2 = 0x80002,                       ///< Firmware 2
    XET_RESID_FW_3 = 0x80003,                       ///< Firmware 3
    XET_RESID_FW_4 = 0x80004,                       ///< Firmware 4
    XET_RESID_FW_5 = 0x80005,                       ///< Firmware 5
    XET_RESID_FW_6 = 0x80006,                       ///< Firmware 6
    XET_RESID_FW_7 = 0x80007,                       ///< Firmware 7
    XET_RESID_FW_8 = 0x80008,                       ///< Firmware 8
    XET_RESID_FW_9 = 0x80009,                       ///< Firmware 9
    XET_RESID_FW_10 = 0x8000A,                      ///< Firmware 10
    XET_RESID_FW_11 = 0x8000B,                      ///< Firmware 11
    XET_RESID_FW_12 = 0x8000C,                      ///< Firmware 12
    XET_RESID_FW_13 = 0x8000D,                      ///< Firmware 13
    XET_RESID_FW_14 = 0x8000E,                      ///< Firmware 14
    XET_RESID_FW_15 = 0x8000F,                      ///< Firmware 15
    XET_RESID_FW_16 = 0x80010,                      ///< Firmware 16
    XET_RESID_FW_17 = 0x80011,                      ///< Firmware 17
    XET_RESID_FW_18 = 0x80012,                      ///< Firmware 18
    XET_RESID_FW_19 = 0x80013,                      ///< Firmware 19
    XET_RESID_FW_20 = 0x80014,                      ///< Firmware 20
    XET_RESID_PSU_MAIN = 0x90000,                   ///< Primary power supply
    XET_RESID_PSU_AUX = 0x90001,                    ///< Auxilary power supply
    XET_RESID_PSU_1 = 0x90002,                      ///< Power supply 1
    XET_RESID_PSU_2 = 0x90003,                      ///< Power supply 2
    XET_RESID_FAN_MAIN = 0xA0000,                   ///< The main fan
    XET_RESID_FAN_1 = 0xA0001,                      ///< Fan 1
    XET_RESID_FAN_2 = 0xA0002,                      ///< Fan 2
    XET_RESID_FAN_3 = 0xA0003,                      ///< Fan 3
    XET_RESID_LED_MAIN = 0xB0000,                   ///< The main LED
    XET_RESID_LED_1 = 0xB0001,                      ///< LED 1
    XET_RESID_LED_2 = 0xB0002,                      ///< LED 1
    XET_RESID_LED_3 = 0xB0003,                      ///< LED 1
    XET_RESID_ANY = -1,                             ///< Any resource ID

} xet_resid_t;

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
typedef enum _xet_resprop_t
{
    XET_RESPROP_DEV_SERIAL_NUMBER = 0x00000,        ///< (ro static) The serial number of the device (data:
                                                    ///< ::xet_resprop_dev_serial_number_t)
    XET_RESPROP_DEV_BOARD_NUMBER = 0x00001,         ///< (ro static) The board number of the device (data:
                                                    ///< ::xet_resprop_dev_board_number_t)
    XET_RESPROP_DEV_BRAND = 0x00002,                ///< (ro static) The brand name of the device (data:
                                                    ///< ::xet_resprop_dev_brand_t)
    XET_RESPROP_DEV_MODEL = 0x00003,                ///< (ro static) The model name of the device (data:
                                                    ///< ::xet_resprop_dev_model_t)
    XET_RESPROP_DEV_DEVICEID = 0x00004,             ///< (ro static) The device ID of the device (data:
                                                    ///< ::xet_resprop_dev_deviceid_t)
    XET_RESPROP_DEV_VENDOR_NAME = 0x00005,          ///< (ro static) The vendor name of the device (data:
                                                    ///< ::xet_resprop_dev_vendor_name_t)
    XET_RESPROP_DEV_DRIVER_VERSION = 0x00006,       ///< (ro static) The driver version associated with the device (data:
                                                    ///< ::xet_resprop_dev_driver_version_t)
    XET_RESPROP_DEV_BARS = 0x00007,                 ///< (ro static) The bars configured for the device (data:
                                                    ///< ::xet_resprop_dev_bars_t)
    XET_RESPROP_DEV_UUID = 0x00008,                 ///< (ro static) Universal Unique ID for the device (data:
                                                    ///< ::xet_resprop_dev_uuid_t)
    XET_RESPROP_PWR_MAX_LIMIT = 0x10000,            ///< (ro static) The maximum power limit that can be requested (data:
                                                    ///< ::xet_resprop_pwr_max_limit_t)
    XET_RESPROP_PWR_ENERGY_COUNTER = 0x10001,       ///< (ro dynamic) The value of the monotonic energy counter (data:
                                                    ///< ::xet_resprop_pwr_energy_counter_t)
    XET_RESPROP_PWR_SUSTAINED_LIMIT = 0x10002,      ///< (rw dynamic) The sustained power limit (data:
                                                    ///< ::xet_resprop_pwr_sustained_limit_t)
    XET_RESPROP_PWR_BURST_LIMIT = 0x10003,          ///< (rw dynamic) The burst power limit (data:
                                                    ///< ::xet_resprop_pwr_burst_limit_t)
    XET_RESPROP_PWR_PEAK_LIMIT = 0x10004,           ///< (rw dynamic) The peak power limit (data:
                                                    ///< ::xet_resprop_pwr_peak_limit_t)
    XET_RESPROP_FREQ_AVAIL_CLOCKS = 0x20000,        ///< (ro static) Available frequency clocks that this domain can run at
                                                    ///< (data: ::xet_resprop_freq_avail_clocks_t)
    XET_RESPROP_FREQ_RANGE = 0x20001,               ///< (rw dynamic) The current frequency range (data:
                                                    ///< ::xet_resprop_freq_range_t)
    XET_RESPROP_FREQ_REQUESTED_FREQ = 0x20002,      ///< (ro dynamic) The current frequency request (data:
                                                    ///< ::xet_resprop_freq_requested_freq_t)
    XET_RESPROP_FREQ_TDP_FREQ = 0x20003,            ///< (ro dynamic) The maximum frequency supported under the current TDP
                                                    ///< conditions (data: ::xet_resprop_freq_tdp_freq_t)
    XET_RESPROP_FREQ_EFFICIENT_FREQ = 0x20004,      ///< (ro dynamic) The efficient minimum frequency (data:
                                                    ///< ::xet_resprop_freq_efficient_freq_t)
    XET_RESPROP_FREQ_RESOLVED_FREQ = 0x20005,       ///< (ro dynamic) The resolved frequency (data:
                                                    ///< ::xet_resprop_freq_resolved_freq_t)
    XET_RESPROP_FREQ_THROTTLE_REASONS = 0x20006,    ///< (ro dynamic) The reasons that the frequency is being limited by the
                                                    ///< PCU (data: ::xet_resprop_freq_throttle_reasons_t)
    XET_RESPROP_FREQ_THROTTLE_TIME = 0x20007,       ///< (ro dynamic) The total time that the frequency has been limited by the
                                                    ///< PCU (data: ::xet_resprop_freq_throttle_time_t)
    XET_RESPROP_UTIL_COUNTERS = 0x30000,            ///< (ro dynamic) The total wall time this resource is active (data:
                                                    ///< ::xet_resprop_util_counters_t)
    XET_RESPROP_MEM_TYPE = 0x40000,                 ///< (ro static) The type of memory covered by this resource (data:
                                                    ///< ::xet_resprop_mem_type_t)
    XET_RESPROP_MEM_UTILIZATION = 0x40001,          ///< (ro dynamic) Get current allocated/unallocated size (data:
                                                    ///< ::xet_resprop_mem_utilization_t)
    XET_RESPROP_MEM_BANDWIDTH = 0x40002,            ///< (ro dynamic) Get current read/write bandwidth counters and maximum
                                                    ///< bandwidth (data: ::xet_resprop_mem_bandwidth_t)
    XET_RESPROP_LINK_TYPE = 0x50000,                ///< (ro static) The type of link (data: ::xet_resprop_link_type_t)
    XET_RESPROP_LINK_BUS_ADDRESS = 0x50001,         ///< (ro static) The bus address of the link (data:
                                                    ///< ::xet_resprop_link_bus_address_t)
    XET_RESPROP_LINK_PEER_DEVICE = 0x50002,         ///< (ro static) For links of type ::XET_LINK_TYPE_CD_PORT, this gives the
                                                    ///< UUID of the peer device (data: ::xet_resprop_link_peer_device_t)
    XET_RESPROP_LINK_AVAIL_SPEEDS = 0x50003,        ///< (ro static) Available link speeds (data:
                                                    ///< ::xet_resprop_link_avail_speeds_t)
    XET_RESPROP_LINK_MAX_PACKET_SIZE = 0x50004,     ///< (ro static) Maximum packet size (data:
                                                    ///< ::xet_resprop_link_max_packet_size_t)
    XET_RESPROP_LINK_STATE = 0x50005,               ///< (rw dynamic) Link state (enabled/disabled) (data:
                                                    ///< ::xet_resprop_link_state_t)
    XET_RESPROP_LINK_BANDWIDTH = 0x50006,           ///< (ro dynamic) Monotonic bandwidth counters (data:
                                                    ///< ::xet_resprop_link_bandwidth_t)
    XET_RESPROP_LINK_SPEED = 0x50007,               ///< (ro dynamic) Current link speed (data: ::xet_resprop_link_speed_t)
    XET_RESPROP_LINK_SPEED_RANGE = 0x50008,         ///< (wo dynamic) Set the min/max speeds between which the link can operate
                                                    ///< (data: ::xet_resprop_link_speed_range_t)
    XET_RESPROP_TEMP_TEMPERATURE = 0x60000,         ///< (ro dynamic) The current temperature of the sensor in degrees celcius
                                                    ///< (data: ::xet_resprop_temp_temperature_t)
    XET_RESPROP_STBY_PROMO_MODE = 0x70000,          ///< (rw dynamic) The current promotion mode (data:
                                                    ///< ::xet_resprop_stby_promo_mode_t)
    XET_RESPROP_FW_NAME = 0x80000,                  ///< (ro static) Name encoded in the loaded firmware image (data:
                                                    ///< ::xet_resprop_fw_name_t)
    XET_RESPROP_FW_VERSION = 0x80001,               ///< (ro static) The version of the loaded firmware image (data:
                                                    ///< ::xet_resprop_fw_version_t)
    XET_RESPROP_FW_CHECK = 0x80002,                 ///< (ro dynamic) Verify the checksum of the loaded firmware image (data:
                                                    ///< ::xet_resprop_fw_check_t)
    XET_RESPROP_FW_FLASH = 0x80003,                 ///< (wo dynamically) Flash a new firmware image (data:
                                                    ///< ::xet_resprop_fw_flash_t)
    XET_RESPROP_PSU_AMP_LIMIT = 0x90000,            ///< (ro static) The maximum electrical current in amperes that can be
                                                    ///< drawn (data: ::xet_resprop_psu_amp_limit_t)
    XET_RESPROP_PSU_VOLTAGE_STATUS = 0x90001,       ///< (ro dynamic) Indicates if under or over voltage has occurred (data:
                                                    ///< ::xet_resprop_psu_voltage_status_t)
    XET_RESPROP_PSU_FAN_FAILURE = 0x90002,          ///< (ro dynamic) Indicates if the fan has failed (data:
                                                    ///< ::xet_resprop_psu_fan_failure_t)
    XET_RESPROP_PSU_TEMPERATURE = 0x90003,          ///< (ro dynamic) The current heatsink temperature in degrees celcius
                                                    ///< (data: ::xet_resprop_psu_temperature_t)
    XET_RESPROP_PSU_AMPS = 0x90004,                 ///< (ro dynamic) The current amps being drawn in amperes (data:
                                                    ///< ::xet_resprop_psu_amps_t)
    XET_RESPROP_FAN_MAX_RPM = 0xA0000,              ///< (ro static) The maximum RPM of the fan (data:
                                                    ///< ::xet_resprop_fan_max_rpm_t)
    XET_RESPROP_FAN_MAX_TABLE_SIZE = 0xA0001,       ///< (ro static) The maximum number of points in the fan temp/speed table
                                                    ///< (data: ::xet_resprop_fan_max_table_size_t)
    XET_RESPROP_FAN_SPEED_RPM = 0xA0002,            ///< (ro dynamic) The current fan speed in units of revolutions per minute
                                                    ///< (rpm) (data: ::xet_resprop_fan_speed_rpm_t)
    XET_RESPROP_FAN_SPEED_PERCENT = 0xA0003,        ///< (ro dynamic) The current fan speed as a percentage of the maximum
                                                    ///< speed of that fan (data: ::xet_resprop_fan_speed_percent_t)
    XET_RESPROP_FAN_MODE = 0xA0004,                 ///< (ro dynamic) The current fan speed mode (one of
                                                    ///< ::xet_fan_speed_mode_t) (data: ::xet_resprop_fan_mode_t)
    XET_RESPROP_FAN_FIXED_SPEED = 0xA0005,          ///< (rw dynamic) Read/write the fixed speed setting for the fan (data:
                                                    ///< ::xet_resprop_fan_fixed_speed_t)
    XET_RESPROP_FAN_SPEED_TABLE = 0xA0006,          ///< (rw dynamic) Read/write the fan speed table (data:
                                                    ///< ::xet_resprop_fan_speed_table_t)
    XET_RESPROP_LED_RGB_CAP = 0xB0000,              ///< (ro static) Indicates if the LED is RGB capable (data:
                                                    ///< ::xet_resprop_led_rgb_cap_t)
    XET_RESPROP_LED_STATE = 0xB0001,                ///< (rw dynaic) The LED state - on/off and color (data:
                                                    ///< ::xet_resprop_led_state_t)

} xet_resprop_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define XET_STRING_PROPERTY_SIZE  32
#endif // XET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI bar types
typedef enum _xet_pci_bar_type_t
{
    XET_PCI_BAR_TYPE_CONFIG = 0,                    ///< PCI configuration space
    XET_PCI_BAR_TYPE_MMIO,                          ///< MMIO registers
    XET_PCI_BAR_TYPE_VRAM,                          ///< VRAM aperture
    XET_PCI_BAR_TYPE_ROM,                           ///< ROM aperture
    XET_PCI_BAR_TYPE_VGA_IO,                        ///< Legacy VGA IO ports
    XET_PCI_BAR_TYPE_VGA_MEM,                       ///< Legacy VGA memory
    XET_PCI_BAR_TYPE_INDIRECT_IO,                   ///< Indirect IO port access
    XET_PCI_BAR_TYPE_INDIRECT_MEM,                  ///< Indirect memory access
    XET_PCI_BAR_TYPE_OTHER,                         ///< Other type of PCI bar

} xet_pci_bar_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for a PCI bar
typedef struct _xet_pci_bar_info_t
{
    xet_pci_bar_type_t type;                        ///< [out] The type of bar
    uint64_t base;                                  ///< [out] Base address of the bar.
    uint64_t size;                                  ///< [out] Size of the bar.

} xet_pci_bar_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_DEV_SERIAL_NUMBER
typedef struct _xet_resprop_dev_serial_number_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_dev_serial_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_DEV_BOARD_NUMBER
typedef struct _xet_resprop_dev_board_number_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_dev_board_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_DEV_BRAND
typedef struct _xet_resprop_dev_brand_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_dev_brand_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_DEV_MODEL
typedef struct _xet_resprop_dev_model_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_dev_model_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_DEV_DEVICEID
typedef struct _xet_resprop_dev_deviceid_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_dev_deviceid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_DEV_VENDOR_NAME
typedef struct _xet_resprop_dev_vendor_name_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_dev_vendor_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_DEV_DRIVER_VERSION
typedef struct _xet_resprop_dev_driver_version_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_dev_driver_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_DEV_BARS
typedef struct _xet_resprop_dev_bars_t
{
    uint32_t num;                                   ///< [out] The number of bars
    const xet_pci_bar_info_t* pBars;                ///< [out][range(0, num-1)] Information about each bar.

} xet_resprop_dev_bars_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_DEV_UUID
typedef struct _xet_resprop_dev_uuid_t
{
    xe_device_uuid_t uuid;                          ///< [out] Device UUID

} xet_resprop_dev_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PWR_MAX_LIMIT
typedef struct _xet_resprop_pwr_max_limit_t
{
    uint32_t limit;                                 ///< [out] The maximum power limit in milliwatts that can be requested.

} xet_resprop_pwr_max_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PWR_ENERGY_COUNTER
typedef struct _xet_resprop_pwr_energy_counter_t
{
    uint64_t energy;                                ///< [out] The value of the monotonic energy counter in millijoules.

} xet_resprop_pwr_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PWR_SUSTAINED_LIMIT
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency if
///       the power averaged over a window (typically seconds) exceeds this
///       limit.
typedef struct _xet_resprop_pwr_sustained_limit_t
{
    xe_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts
    uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

} xet_resprop_pwr_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PWR_BURST_LIMIT
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency of
///       the device if the power averaged over a few milliseconds exceeds a
///       limit known as PL2. Typically PL2 > PL1 so that it permits the
///       frequency to burst higher for short periods than would be otherwise
///       permitted by PL1.
typedef struct _xet_resprop_pwr_burst_limit_t
{
    xe_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} xet_resprop_pwr_burst_limit_t;

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
typedef struct _xet_resprop_pwr_peak_limit_t
{
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} xet_resprop_pwr_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle reasons
typedef enum _xet_freq_throttle_reasons_t
{
    XET_FREQ_THROTTLE_REASONS_NONE = 0,             ///< frequency not throttled
    XET_FREQ_THROTTLE_REASONS_AVE_PWR_CAP = XE_BIT( 0 ),///< frequency throttled due to average power excursion (PL1)
    XET_FREQ_THROTTLE_REASONS_BURST_PWR_CAP = XE_BIT( 1 ),  ///< frequency throttled due to burst power excursion (PL2)
    XET_FREQ_THROTTLE_REASONS_CURRENT_LIMIT = XE_BIT( 2 ),  ///< frequency throttled due to current excursion (PL4)
    XET_FREQ_THROTTLE_REASONS_THERMAL_LIMIT = XE_BIT( 3 ),  ///< frequency throttled due to thermal excursion (T > TjMax)
    XET_FREQ_THROTTLE_REASONS_PSU_ALERT = XE_BIT( 4 ),  ///< frequency throttled due to power supply assertion
    XET_FREQ_THROTTLE_REASONS_SW_RANGE = XE_BIT( 5 ),   ///< frequency throttled due to software supplied frequency range
    XET_FREQ_THROTTLE_REASONS_HW_RANGE = XE_BIT( 6 ),   ///< frequency throttled due to a sub block that has a lower frequency
                                                    ///< range when it receives clocks

} xet_freq_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_AVAIL_CLOCKS
/// 
/// @details
///     - Provides the set of frequencies as a list and as a range/step.
///     - It is generally recommended that applications choose frequencies from
///       the list. However applications can also construct the list themselves
///       using the range/steps provided.
typedef struct _xet_resprop_freq_avail_clocks_t
{
    double min;                                     ///< [out] The minimum clock frequency in units of MHz
    double max;                                     ///< [out] The maximum clock frequency in units of MHz
    double step;                                    ///< [out] The step clock frequency in units of MHz
    uint32_t num;                                   ///< [out] The number of clocks
    const double* pClocks;                          ///< [out] Array of clock frequencies in units of MHz ordered from smallest
                                                    ///< to largest.

} xet_resprop_freq_avail_clocks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_RANGE
typedef struct _xet_resprop_freq_range_t
{
    double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will return the
                                                    ///< hardware default value.
    double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will return the
                                                    ///< hardware default value.

} xet_resprop_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_REQUESTED_FREQ
typedef struct _xet_resprop_freq_requested_freq_t
{
    double freqRequest;                             ///< [out] The current frequency request in MHz.

} xet_resprop_freq_requested_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_TDP_FREQ
typedef struct _xet_resprop_freq_tdp_freq_t
{
    double freqTdp;                                 ///< [out] The maximum frequency in MHz supported under the current TDP
                                                    ///< conditions

} xet_resprop_freq_tdp_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_EFFICIENT_FREQ
typedef struct _xet_resprop_freq_efficient_freq_t
{
    double freqEfficient;                           ///< [out] The efficient minimum frequency in MHz

} xet_resprop_freq_efficient_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_RESOLVED_FREQ
typedef struct _xet_resprop_freq_resolved_freq_t
{
    double freqResolved;                            ///< [out] The resolved frequency in MHz

} xet_resprop_freq_resolved_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_THROTTLE_REASONS
typedef struct _xet_resprop_freq_throttle_reasons_t
{
    uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the PCU
                                                    ///< (Bitfield of (1<<::xet_freq_throttle_reasons_t)).

} xet_resprop_freq_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FREQ_THROTTLE_TIME
typedef struct _xet_resprop_freq_throttle_time_t
{
    uint32_t throttleTime;                          ///< [out] The total time in microseconds that the frequency has been
                                                    ///< limited by the PCU.

} xet_resprop_freq_throttle_time_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_UTIL_COUNTERS
/// 
/// @details
///     - Percentage utilization is given by the equation: 100 *
///       delta(activeCounter) / ( delta(activeCounter) + delta(idleCounter) ).
typedef struct _xet_resprop_util_counters_t
{
    uint32_t activeCounter;                         ///< [out] Monotonic counter for total wall time in microseconds that this
                                                    ///< resource is actively running workloads.
    uint32_t idleCounter;                           ///< [out] Monotonic counter for total wall time in microseconds that this
                                                    ///< resource is not actively running any workloads.

} xet_resprop_util_counters_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory resource types
typedef enum _xet_mem_type_t
{
    XET_MEM_TYPE_HBM = 0,                           ///< HBM memory
    XET_MEM_TYPE_DDR,                               ///< DDR memory
    XET_MEM_TYPE_SRAM,                              ///< SRAM memory
    XET_MEM_TYPE_L1,                                ///< L1 cache
    XET_MEM_TYPE_L3,                                ///< L3 cache
    XET_MEM_TYPE_GRF,                               ///< Execution unit register file
    XET_MEM_TYPE_SLM,                               ///< Execution unit shared local memory

} xet_mem_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_MEM_TYPE
typedef struct _xet_resprop_mem_type_t
{
    xet_mem_type_t type;                            ///< [out] The memory type

} xet_resprop_mem_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_MEM_UTILIZATION
/// 
/// @details
///     - The total physical memory is the sum of all others (stolen + bad +
///       allocated + unallocated).
///     - Percent software memory utilization given by 100 * allocated /
///       (allocated + unallocated).
///     - Percent bad memory given by 100 * bad / total
typedef struct _xet_resprop_mem_utilization_t
{
    uint64_t total;                                 ///< [out] The total physical memory in bytes
    uint64_t stolen;                                ///< [out] The total stolen memory in bytes
    uint64_t bad;                                   ///< [out] The total bad memory in bytes
    uint64_t allocated;                             ///< [out] The total allocated bytes
    uint64_t unallocated;                           ///< [out] The total unallocated bytes

} xet_resprop_mem_utilization_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_MEM_BANDWIDTH
typedef struct _xet_resprop_mem_bandwidth_t
{
    uint32_t readCounter;                           ///< [out] Total bytes read from memory
    uint32_t writeCounter;                          ///< [out] Total bytes written to memory
    uint32_t maxBandwidth;                          ///< [out] Current maximum bandwidth in units of bytes/sec

} xet_resprop_mem_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Link resource types
typedef enum _xet_link_type_t
{
    XET_LINK_TYPE_PCI = 0,                          ///< PCI connection
    XET_LINK_TYPE_CD_PORT,                          ///< Companion die physical port

} xet_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Link speed element
typedef struct _xet_link_speed_t
{
    uint32_t numLanes;                              ///< [out] The number of lanes used by the link
    uint32_t speed;                                 ///< [out] The frequency of the link in units of MHz
    uint32_t bandwidth;                             ///< [out] The maximum bandwidth in units of bytes/sec

} xet_link_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_LINK_TYPE
typedef struct _xet_resprop_link_type_t
{
    xet_link_type_t type;                           ///< [out] The type of link

} xet_resprop_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_LINK_BUS_ADDRESS
typedef struct _xet_resprop_link_bus_address_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_link_bus_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_LINK_PEER_DEVICE
typedef struct _xet_resprop_link_peer_device_t
{
    xe_device_uuid_t uuid;                          ///< [out] UUID of the peer device connected to through this link

} xet_resprop_link_peer_device_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LINK_AVAIL_SPEEDS
/// 
/// @details
///     - The list is ordered from the smallest ratio to the largest ratio.
typedef struct _xet_resprop_link_avail_speeds_t
{
    uint32_t num;                                   ///< [out] The number of elements in pList
    const xet_link_speed_t* pList;                  ///< [out][range(0, num-1)] Pointer to an array of link speeds

} xet_resprop_link_avail_speeds_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LINK_STATE
typedef struct _xet_resprop_link_state_t
{
    xe_bool_t enable;                               ///< [out] Indicates if the link is disabled/endabled.

} xet_resprop_link_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LINK_MAX_PACKET_SIZE
typedef struct _xet_resprop_link_max_packet_size_t
{
    uint32_t maxPacketSize;                         ///< [out] Maximum packet size in bytes.

} xet_resprop_link_max_packet_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LINK_BANDWIDTH
typedef struct _xet_resprop_link_bandwidth_t
{
    uint32_t recvCounter;                           ///< [out] Total bytes received across the link
    uint32_t sendCounter;                           ///< [out] Total bytes sent across the link
    uint32_t maxBandwidth;                          ///< [out] Maximum bytes/sec that can be transfered acros the link

} xet_resprop_link_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LINK_SPEED
typedef struct _xet_resprop_link_speed_t
{
    const xet_link_speed_t* pSpeed;                 ///< [out] Pointer to the current speed configuration

} xet_resprop_link_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LINK_SPEED_RANGE
typedef struct _xet_resprop_link_speed_range_t
{
    const xet_link_speed_t* pMinSpeed;              ///< [out] Pointer to the min speed configuration (one of those in the
                                                    ///< array returned by property ::XET_RESPROP_LINK_AVAIL_SPEEDS)
    const xet_link_speed_t* pMaxSpeed;              ///< [out] Pointer to the max speed configuration (one of those in the
                                                    ///< array returned by property ::XET_RESPROP_LINK_AVAIL_SPEEDS)

} xet_resprop_link_speed_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_TEMP_TEMPERATURE
typedef struct _xet_resprop_temp_temperature_t
{
    uint32_t temperature;                           ///< [out] The current temperature of the sensor in degrees celcius

} xet_resprop_temp_temperature_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby promotion modes
typedef enum _xet_stby_promo_mode_t
{
    XET_STBY_PROMO_MODE_IMMEDIATE = 0,              ///< The device/component will shutdown immediately when all contained
                                                    ///< units are idle. This improves energy savings at the expense of
                                                    ///< performance.
    XET_STBY_PROMO_MODE_DEFAULT,                    ///< Best compromise between performance and energy savings.
    XET_STBY_PROMO_MODE_NEVER,                      ///< The device/component will never shutdown. This can improve performance
                                                    ///< but uses more energy.

} xet_stby_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_STBY_PROMO_MODE
typedef struct _xet_resprop_stby_promo_mode_t
{
    xet_stby_promo_mode_t mode;                     ///< [in,out] Current promotion mode

} xet_resprop_stby_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_FW_NAME
typedef struct _xet_resprop_fw_name_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_fw_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for property ::XET_RESPROP_FW_VERSION
typedef struct _xet_resprop_fw_version_t
{
    int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

} xet_resprop_fw_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FW_CHECK
typedef struct _xet_resprop_fw_check_t
{
    uint32_t checksum;                              ///< [out] The calculated checksum of the loaded firmware image

} xet_resprop_fw_check_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FW_FLASH
typedef struct _xet_resprop_fw_flash_t
{
    void* pImage;                                   ///< [in] Pointer to the image to be flashed
    uint32_t size;                                  ///< [in] Size in bytes of the image pointed to by pImage

} xet_resprop_fw_flash_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PSU voltage status
typedef enum _xet_psu_voltage_status_t
{
    XET_PSU_VOLTAGE_STATUS_NORMAL = 0,              ///< No unusual voltages have been detected
    XET_PSU_VOLTAGE_STATUS_OVER,                    ///< Over-voltage has occurred
    XET_PSU_VOLTAGE_STATUS_UNDER,                   ///< Under-voltage has occurred

} xet_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PSU_AMP_LIMIT
typedef struct _xet_resprop_psu_amp_limit_t
{
    uint32_t limit;                                 ///< [out] The maximum electrical current in amperes that can be drawn

} xet_resprop_psu_amp_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PSU_VOLTAGE_STATUS
typedef struct _xet_resprop_psu_voltage_status_t
{
    xet_psu_voltage_status_t status;                ///< [out] The current PSU voltage status)

} xet_resprop_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PSU_FAN_FAILURE
typedef struct _xet_resprop_psu_fan_failure_t
{
    xe_bool_t status;                               ///< [out] Indicates if the fan has failed

} xet_resprop_psu_fan_failure_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PSU_TEMPERATURE
typedef struct _xet_resprop_psu_temperature_t
{
    uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees celcius

} xet_resprop_psu_temperature_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_PSU_AMPS
typedef struct _xet_resprop_psu_amps_t
{
    uint32_t current;                               ///< [out] The amps being drawn in amperes

} xet_resprop_psu_amps_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan resource speed mode
typedef enum _xet_fan_speed_mode_t
{
    XET_FAN_SPEED_MODE_FIXED = 0,                   ///< The fan speed is currently set to a fixed value
    XET_FAN_SPEED_MODE_TABLE,                       ///< The fan speed is currently controlled dynamically by hardware based on
                                                    ///< a temp/speed table

} xet_fan_speed_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan speed units
typedef enum _xet_fan_speed_units_t
{
    XET_FAN_SPEED_UNITS_RPM = 0,                    ///< The fan speed is in units of revolutions per minute (rpm)
    XET_FAN_SPEED_UNITS_PERCENT,                    ///< The fan speed is a percentage of the maximum speed of the fan

} xet_fan_speed_units_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan temperature/speed pair
typedef struct _xet_fan_temp_speed_t
{
    uint32_t temperature;                           ///< [in,out] Temperature in degrees celcius
    uint32_t speed;                                 ///< [in,out] The speed of the fan
    xet_fan_speed_units_t units;                    ///< [in,out] The units of the member speed

} xet_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define XET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // XET_FAN_TEMP_SPEED_PAIR_COUNT

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FAN_MAX_RPM
typedef struct _xet_resprop_fan_max_rpm_t
{
    uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan

} xet_resprop_fan_max_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FAN_MAX_TABLE_SIZE
typedef struct _xet_resprop_fan_max_table_size_t
{
    uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

} xet_resprop_fan_max_table_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FAN_SPEED_RPM
typedef struct _xet_resprop_fan_speed_rpm_t
{
    uint32_t speed;                                 ///< [out] The current fan speed in units of revolutions per minute (rpm)

} xet_resprop_fan_speed_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FAN_SPEED_PERCENT
typedef struct _xet_resprop_fan_speed_percent_t
{
    uint32_t speed;                                 ///< [out] The current fan speed as a percentage of the maximum speed of
                                                    ///< that fan

} xet_resprop_fan_speed_percent_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FAN_MODE
typedef struct _xet_resprop_fan_mode_t
{
    xet_fan_speed_mode_t mode;                      ///< [in,out] The current fan speed mode (one of ::xet_fan_speed_mode_t)

} xet_resprop_fan_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FAN_FIXED_SPEED
typedef struct _xet_resprop_fan_fixed_speed_t
{
    uint32_t speed;                                 ///< [in,out] The speed of the fan
    xet_fan_speed_units_t units;                    ///< [in,out] The units of the member speed

} xet_resprop_fan_fixed_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_FAN_SPEED_TABLE
typedef struct _xet_resprop_fan_speed_table_t
{
    uint32_t* pCount;                               ///< [in,out] The number of temp/speed pairs.
                                                    ///< When reading the current fan speed table, this will be set to the
                                                    ///< number of points returned.
                                                    ///< When setting the fan speed table, this specifies the number of valid
                                                    ///< points in the table.
    xet_fan_temp_speed_t points[XET_FAN_TEMP_SPEED_PAIR_COUNT]; ///< [in,out][range(0, *pCount)] Array of temperature/fan speed pairs

} xet_resprop_fan_speed_table_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LED_RGB_CAP
typedef struct _xet_resprop_led_rgb_cap_t
{
    xe_bool_t haveRGB;                              ///< [out] Indicates if the LED is RGB capable

} xet_resprop_led_rgb_cap_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Data for the property ::XET_RESPROP_LED_STATE
typedef struct _xet_resprop_led_state_t
{
    xe_bool_t isOn;                                 ///< [in,out] Indicates if the LED is on or off
    uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
    uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
    uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

} xet_resprop_led_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Property support
typedef enum _xet_prop_support_t
{
    XET_PROP_SUPPORT_NONE = 0,                      ///< The property is not supported by this version of the API
    XET_PROP_SUPPORT_API = XE_BIT( 0 ),             ///< The property is supported by the the API
    XET_PROP_SUPPORT_DEVICE_CLASS = XE_BIT( 1 ),    ///< The property is supported for the class of device
    XET_PROP_SUPPORT_DEVICE = XE_BIT( 2 ),          ///< The property is supported for the device

} xet_prop_support_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Property access permissions
typedef enum _xet_prop_access_t
{
    XET_PROP_ACCESS_NO_PERMISSIONS = 0,             ///< The application does not have read-write access to the property
    XET_PROP_ACCESS_READ_PERMISSIONS = XE_BIT( 0 ), ///< The application has only read access to the property
    XET_PROP_ACCESS_WRITE_PERMISSIONS = XE_BIT( 1 ),///< The application has write access to the property

} xet_prop_access_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Structure containing information about a resource
typedef struct _xet_resid_info_t
{
    xet_resid_t id;                                 ///< [in] The ID of the resource
    xet_resource_type_t type;                       ///< [in] The type of resource
    const char* pName;                              ///< [out] The name of the resource
    const char* pDesc;                              ///< [out] Human readable description of this resouce
    xe_bool_t available;                            ///< [out] Set to TRUE if the resource with this ID is available on the
                                                    ///< device, otherwise set to FALSE
    xe_bool_t propsOnSubdevices;                    ///< [out] Set to TRUE if this resource will change properties on
                                                    ///< sub-devices or is merging telemetry from sub-devices

} xet_resid_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out if specific resources are available on this device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pResources
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetResourceInfo(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the the array pResources
    xet_resid_info_t* pResources                    ///< [in] Pointer to an array that hold the ID of resources on input and
                                                    ///< will contain the availability on output
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get list of resources available on this device of a given type
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///         + nullptr == pResources
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetResources(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_resource_type_t type,                       ///< [in] Get a list of resources of given type. If this is
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
    xet_resid_info_t* pResources                    ///< [in] Pointer to an array that will hold the ID of information about
                                                    ///< supported resources
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to get resource property info
typedef struct _xet_resprop_info_t
{
    xet_resprop_t property;                         ///< [in] The property
    xet_resource_type_t resourceType;               ///< [out] The type of resource this property is used with
    const char* pName;                              ///< [out] Resource property name
    const char* pDesc;                              ///< [out] Human readable description of this property
    xet_prop_support_t support;                     ///< [out] API support for the property
    xet_prop_access_t access;                       ///< [out] The access permissions for the property
    uint32_t minGetInterval;                        ///< [out] The minimum interval in microseconds between reads to this
                                                    ///< property
    uint32_t minSetInterval;                        ///< [out] The minimum interval in microseconds between writes to this
                                                    ///< property

} xet_resprop_info_t;

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
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetPropertyInfo(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pProperties
    xet_resprop_info_t* pProperties                 ///< [in] Pointer to an array of property info. Contains the property ID on
                                                    ///< input and the property info completed on output
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to query a resource property value
typedef struct _xet_resprop_request_t
{
    xet_resid_t resource;                           ///< [in] The resource ID
    xet_resprop_t property;                         ///< [in] The property being requested
    void* pData;                                    ///< [in] Pointer to the data for the property.
                                                    ///< Each property has a corresponding data structure. The type of the data
                                                    ///< structure is derived from the property enumerator, converted to
                                                    ///< lower-case with "_t" appended.
    uint32_t size;                                  ///< [in] The size of the data structure pointed to by pData.
    xe_result_t status;                             ///< [out] Indicates if the request was successful or not.
                                                    ///< ::XE_RESULT_SUCCESS - Data was successful read or updated.
                                                    ///< ::XE_RESULT_ERROR_DEVICE_ACCESS - Problem reading or writing device data.
                                                    ///< ::XE_RESULT_ERROR_INVALID_ARGUMENT - Resource ID or property ID are
                                                    ///< invalid or size does not match required storage for property data.
                                                    ///< ::XE_RESULT_ERROR_UNSUPPORTED - Resource ID and/or property ID not
                                                    ///< supported on this device.
                                                    ///< ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS - Insufficient permission to
                                                    ///< access this property.

} xet_resprop_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get resource property data
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pRequest
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_UNKNOWN
///         + One or more of the specified resource/properties had access errors. Check ::xet_resprop_request_t.status for each request.
xe_result_t __xecall
xetSysmanGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_resprop_request_t* pRequest                 ///< [in] Pointer to list of properties and corresponding data storage
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set resource property data
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pRequest
///         + An invalid resource index was specified in one or more of the requests
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + One or more requested properties is not supported on this device
xe_result_t __xecall
xetSysmanSetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_resprop_request_t* pRequest                 ///< [in] Pointer to list of properties and corresponding data storage
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error type
typedef enum _xet_ras_error_type_t
{
    XET_RAS_ERROR_TYPE_NONE = 0,                    ///< No error type
    XET_RAS_ERROR_TYPE_FATAL = XE_BIT( 0 ),         ///< Error was fatal
    XET_RAS_ERROR_TYPE_NON_FATAL = XE_BIT( 1 ),     ///< Error was not fatal
    XET_RAS_ERROR_TYPE_CORRECTABLE = XE_BIT( 2 ),   ///< Error was corrected
    XET_RAS_ERROR_TYPE_UNCORRECTABLE = XE_BIT( 3 ), ///< Error was not corrected
    XET_RAS_ERROR_TYPE_PARITY = XE_BIT( 4 ),        ///< Parity error occurred
    XET_RAS_ERROR_TYPE_SINGLE_BIT = XE_BIT( 5 ),    ///< Single bit error occurred
    XET_RAS_ERROR_TYPE_DOUBLE_BIT = XE_BIT( 6 ),    ///< Single bit error occurred
    XET_RAS_ERROR_TYPE_REPLAY = XE_BIT( 7 ),        ///< Replay occurred
    XET_RAS_ERROR_TYPE_RESET = XE_BIT( 8 ),         ///< Resets occurred
    XET_RAS_ERROR_TYPE_ALL = ~0,                    ///< Select all error types

} xet_ras_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error structural location
typedef enum _xet_ras_error_loc_t
{
    XET_RAS_ERROR_LOC_NONE = 0,                     ///< No location
    XET_RAS_ERROR_LOC_MAIN_MEM = XE_BIT( 0 ),       ///< Error occurred in main onboard memory
    XET_RAS_ERROR_LOC_L3_CACHE = XE_BIT( 1 ),       ///< Error occurred in L3 cache
    XET_RAS_ERROR_LOC_SAMPLER_SRAM = XE_BIT( 2 ),   ///< Error occurred in sampler SRAM
    XET_RAS_ERROR_LOC_GUC_SRAM = XE_BIT( 3 ),       ///< Error occurred in microcontroller SRAM
    XET_RAS_ERROR_LOC_INST_CACHE = XE_BIT( 4 ),     ///< Error occurred in the compute unit instruction cache
    XET_RAS_ERROR_LOC_GRF = XE_BIT( 5 ),            ///< Error occurred in the compute unit register file
    XET_RAS_ERROR_LOC_SLM = XE_BIT( 6 ),            ///< Error occurred in the compute unit shared local memory
    XET_RAS_ERROR_LOC_MESSAGING = XE_BIT( 7 ),      ///< Errors occurred handling transactions between PCI config space, MMIO
                                                    ///< registers, local memory and sub-devices
    XET_RAS_ERROR_LOC_SECURITY = XE_BIT( 8 ),       ///< Security errors occurred
    XET_RAS_ERROR_LOC_DISPLAY = XE_BIT( 9 ),        ///< Errors occurred in the display
    XET_RAS_ERROR_LOC_SOC = XE_BIT( 10 ),           ///< Errors occurred in other parts of the device
    XET_RAS_ERROR_LOC_GPU_HANG = XE_BIT( 11 ),      ///< Driver detected that the GPU hardware was non-responsive
    XET_RAS_ERROR_LOC_PCI = XE_BIT( 12 ),           ///< Error occurred in the PCIe controller
    XET_RAS_ERROR_LOC_PCI_ROUTING = XE_BIT( 13 ),   ///< Error occurred routing PCIe traffic to/from sub-devices
    XET_RAS_ERROR_LOC_P2P_LINK = XE_BIT( 14 ),      ///< Errors detected with peer-to-peer connection
    XET_RAS_ERROR_LOC_ALL = ~0,                     ///< Select all error locations

} xet_ras_error_loc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS configuration
typedef struct _xet_ras_config_t
{
    uint32_t numRas;                                ///< [in] Total number of RAS counters available on this device
    uint32_t rasTypes;                              ///< [in] All RAS types supported on this device (bitfield of
                                                    ///< ::xet_ras_error_type_t)
    uint32_t rasLocations;                          ///< [in] All structural locations where RAS is supported on this device
                                                    ///< (bitfield of ::xet_ras_error_loc_t)
    uint32_t enabled;                               ///< [in] All structural locations where RAS is currently enabled on this
                                                    ///< device (bitfield of ::xet_ras_error_loc_t)

} xet_ras_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS data type
typedef enum _xet_ras_data_type_t
{
    XET_RAS_DATA_TYPE_NONE = 0,                     ///< Errors not supported
    XET_RAS_DATA_TYPE_OCCURRED,                     ///< Indicates if an error occurred
    XET_RAS_DATA_TYPE_COUNTER,                      ///< Provides a counter for the number of errors that have occurred

} xet_ras_data_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Filter RAS errors
typedef struct _xet_ras_filter_t
{
    xet_resid_t resourceId;                         ///< [in] Filter based on resource ID. Set to ::XET_RESID_ANY to get errors
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

} xet_ras_filter_t;

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
/// @brief RAS error
typedef struct _xet_ras_error_t
{
    const char* pName;                              ///< [out] Name of this error
    const char* pDesc;                              ///< [out] Human readable description of this error
    uint32_t type;                                  ///< [out] Bitfield describing type of error, constructed from one or more
                                                    ///< of ::xet_ras_error_type_t
    uint32_t loc;                                   ///< [out] Bitfield describing structural location of the error,
                                                    ///< constructed from one of ::xet_ras_error_loc_t
    xet_ras_data_type_t dataType;                   ///< [out] How to interpret the data
    uint64_t data;                                  ///< [out] The value of the error - interpretation depends on dataType
    uint64_t accumulated;                           ///< [out] The accumulated value of the error (never cleared until device
                                                    ///< driver is reloaded)
    xet_resid_t resourceId;                         ///< [out] Resource where the error was generated. If the error doesn't
                                                    ///< come from a specific resource, this will be ::XET_RESID_ANY

} xet_ras_error_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetRasConfig(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_ras_config_t* pConfig                       ///< [in] Pointer to storage for current RAS configuration
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Setup (enable/disable) RAS
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEnabledLoc
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRasSetup(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
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
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pFilter
///         + nullptr == pCount
///         + nullptr == pErrors
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_ARRAY_SIZE_TOO_SMALL
///         + The array doesn't have enough elements to store all the errors
xe_result_t __xecall
xetSysmanGetRasErrors(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_ras_filter_t* pFilter,                      ///< [in] Filter for RAS errors to return
    xe_bool_t clear,                                ///< [in] Set to true to clear the underlying counters after they are
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
    xet_ras_error_t* pErrors                        ///< [in] Array of error data
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _xet_sysman_event_type_t
{
    XET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED = 0,       ///< The frequency is being throttled
    XET_SYSMAN_EVENT_TYPE_RAS_ERRORS,               ///< ECC/RAS errors
    XET_SYSMAN_EVENT_TYPE_COUNT,                    ///< The number of event types

} xet_sysman_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure to determine events that are supported
typedef struct _xet_event_support_t
{
    xet_sysman_event_type_t event;                  ///< [in] The event
    xe_bool_t supported;                            ///< [out] Set to true/false to know if the event is supported

} xet_event_support_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which events are supported on a given device
/// 
/// @details
///     - Event support is the same for all devices with the same device ID.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pAccess
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanSupportedEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pAccess
    xet_event_support_t* pAccess                    ///< [in] Pointer to an array of event support requests
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to register/unregister events
typedef struct _xet_event_request_t
{
    xet_sysman_event_type_t event;                  ///< [in] The event type to register.
    xet_resid_t resourceId;                         ///< [in] Only events being generated by the specified resource. If
                                                    ///< ::XET_RESID_ANY, then applies to all events from all resources in the
                                                    ///< device.
    uint32_t threshold;                             ///< [in] The application only receives a notification when the total count
                                                    ///< exceeds this value. Set to zero to receive a notification for every
                                                    ///< new event.

} xet_event_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Register to receive events
/// 
/// @details
///     - This will only register the specified list of events. If other events
///       have been registered, notifications for them will continue.
///     - Set count to zero to receive notifications for all events.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRegisterEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be registered.
    xet_event_request_t* pEvents                    ///< [in] Events to register.
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
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanUnregisterEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be unregistered.
    xet_event_request_t* pEvents                    ///< [in] Events to unregister.
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_EVENT_WAIT_INFINITE
/// @brief Wait infinitely for events to arrive.
#define XET_EVENT_WAIT_INFINITE  0xFFFFFFFF
#endif // XET_EVENT_WAIT_INFINITE

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
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                    ///< device for which the application has registered to receive
                                                    ///< notifications.
    xe_bool_t clear,                                ///< [in] Clear the event status.
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                    ///< check status and return immediately. Set to ::XET_EVENT_WAIT_INFINITE
                                                    ///< to block until events arrive.
    uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                    ///< triggered.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic type
typedef enum _xet_diag_type_t
{
    XET_DIAG_TYPE_SCAN = 0,                         ///< Run SCAN diagnostics
    XET_DIAG_TYPE_ARRAY,                            ///< Run Array diagnostics

} xet_diag_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic results
typedef enum _xet_diag_result_t
{
    XET_DIAG_RESULT_NO_ERRORS = 0,                  ///< Diagnostic completed without finding errors to repair
    XET_DIAG_RESULT_ABORT,                          ///< Diagnostic had problems running tests
    XET_DIAG_RESULT_FAIL_CANT_REPAIR,               ///< Diagnostic had problems setting up repairs
    XET_DIAG_RESULT_REBOOT_FOR_REPAIR,              ///< Diagnostics found errors, setup for repair and reboot is required to
                                                    ///< complete the process

} xet_diag_result_t;

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

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic test
typedef struct _xet_diag_test_t
{
    uint32_t index;                                 ///< [out] Index of the test
    const char* name;                               ///< [out] Name of the test

} xet_diag_test_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief List of all diagnostic tests of a given type ::xet_diag_type_t
typedef struct _xet_diag_test_list_t
{
    xet_diag_type_t type;                           ///< [out] The type of tests
    uint32_t count;                                 ///< [out] The number of tests in the array pTests
    xet_diag_test_t* pTests;                        ///< [out] Array of tests, sorted by increasing value of
                                                    ///< ::xet_diag_test_t.index

} xet_diag_test_list_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get diagnostic tests
/// 
/// @details
///     - Tests are returned in order of increasing index.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == ppTests
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetDiagnosticTests(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
    const xet_diag_test_list_t** ppTests            ///< [in] Returns a constant pointer to the list of diagnostic tests
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Run diagnostics
/// 
/// @details
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pResult
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRunDiagnosticTests(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    xet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDeviceReset(
    xet_sysman_handle_t hSysman                     ///< [in] SMI handle for the device
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_SYSMAN_H
