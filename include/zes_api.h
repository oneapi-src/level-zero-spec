/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_api.h
 *
 */
#ifndef _ZES_API_H
#define _ZES_API_H
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
typedef ze_driver_handle_t zes_driver_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of device object
typedef ze_device_handle_t zes_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device scheduler queue
typedef struct _zes_sched_handle_t *zes_sched_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device performance factors
typedef struct _zes_perf_handle_t *zes_perf_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device power domain
typedef struct _zes_pwr_handle_t *zes_pwr_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device frequency domain
typedef struct _zes_freq_handle_t *zes_freq_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device engine group
typedef struct _zes_engine_handle_t *zes_engine_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device standby control
typedef struct _zes_standby_handle_t *zes_standby_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device firmware
typedef struct _zes_firmware_handle_t *zes_firmware_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device memory module
typedef struct _zes_mem_handle_t *zes_mem_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman fabric port
typedef struct _zes_fabric_port_handle_t *zes_fabric_port_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device temperature sensor
typedef struct _zes_temp_handle_t *zes_temp_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device power supply
typedef struct _zes_psu_handle_t *zes_psu_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device fan
typedef struct _zes_fan_handle_t *zes_fan_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device LED
typedef struct _zes_led_handle_t *zes_led_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device RAS error set
typedef struct _zes_ras_handle_t *zes_ras_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device diagnostics test suite
typedef struct _zes_diag_handle_t *zes_diag_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman device event
typedef struct _zes_event_handle_t *zes_event_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_device_state_t
typedef struct _zes_device_state_t zes_device_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_device_properties_t
typedef struct _zes_device_properties_t zes_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_process_state_t
typedef struct _zes_process_state_t zes_process_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_pci_address_t
typedef struct _zes_pci_address_t zes_pci_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_pci_speed_t
typedef struct _zes_pci_speed_t zes_pci_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_pci_properties_t
typedef struct _zes_pci_properties_t zes_pci_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_pci_state_t
typedef struct _zes_pci_state_t zes_pci_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_pci_bar_properties_t
typedef struct _zes_pci_bar_properties_t zes_pci_bar_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_pci_stats_t
typedef struct _zes_pci_stats_t zes_pci_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_diag_test_t
typedef struct _zes_diag_test_t zes_diag_test_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_diag_properties_t
typedef struct _zes_diag_properties_t zes_diag_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_engine_properties_t
typedef struct _zes_engine_properties_t zes_engine_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_engine_stats_t
typedef struct _zes_engine_stats_t zes_engine_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_event_config_t
typedef struct _zes_event_config_t zes_event_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fabric_port_id_t
typedef struct _zes_fabric_port_id_t zes_fabric_port_id_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fabric_port_speed_t
typedef struct _zes_fabric_port_speed_t zes_fabric_port_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fabric_port_properties_t
typedef struct _zes_fabric_port_properties_t zes_fabric_port_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fabric_link_type_t
typedef struct _zes_fabric_link_type_t zes_fabric_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fabric_port_config_t
typedef struct _zes_fabric_port_config_t zes_fabric_port_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fabric_port_state_t
typedef struct _zes_fabric_port_state_t zes_fabric_port_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fabric_port_throughput_t
typedef struct _zes_fabric_port_throughput_t zes_fabric_port_throughput_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fan_temp_speed_t
typedef struct _zes_fan_temp_speed_t zes_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fan_properties_t
typedef struct _zes_fan_properties_t zes_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_fan_config_t
typedef struct _zes_fan_config_t zes_fan_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_firmware_properties_t
typedef struct _zes_firmware_properties_t zes_firmware_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_freq_properties_t
typedef struct _zes_freq_properties_t zes_freq_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_freq_range_t
typedef struct _zes_freq_range_t zes_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_freq_state_t
typedef struct _zes_freq_state_t zes_freq_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_freq_throttle_time_t
typedef struct _zes_freq_throttle_time_t zes_freq_throttle_time_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_oc_capabilities_t
typedef struct _zes_oc_capabilities_t zes_oc_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_oc_config_t
typedef struct _zes_oc_config_t zes_oc_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_led_properties_t
typedef struct _zes_led_properties_t zes_led_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_led_state_t
typedef struct _zes_led_state_t zes_led_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_mem_properties_t
typedef struct _zes_mem_properties_t zes_mem_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_mem_state_t
typedef struct _zes_mem_state_t zes_mem_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_mem_bandwidth_t
typedef struct _zes_mem_bandwidth_t zes_mem_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_perf_properties_t
typedef struct _zes_perf_properties_t zes_perf_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_power_properties_t
typedef struct _zes_power_properties_t zes_power_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_power_energy_counter_t
typedef struct _zes_power_energy_counter_t zes_power_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_power_sustained_limit_t
typedef struct _zes_power_sustained_limit_t zes_power_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_power_burst_limit_t
typedef struct _zes_power_burst_limit_t zes_power_burst_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_power_peak_limit_t
typedef struct _zes_power_peak_limit_t zes_power_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_energy_threshold_t
typedef struct _zes_energy_threshold_t zes_energy_threshold_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_psu_properties_t
typedef struct _zes_psu_properties_t zes_psu_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_psu_state_t
typedef struct _zes_psu_state_t zes_psu_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_ras_properties_t
typedef struct _zes_ras_properties_t zes_ras_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_ras_details_t
typedef struct _zes_ras_details_t zes_ras_details_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_ras_config_t
typedef struct _zes_ras_config_t zes_ras_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_sched_properties_t
typedef struct _zes_sched_properties_t zes_sched_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_sched_timeout_properties_t
typedef struct _zes_sched_timeout_properties_t zes_sched_timeout_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_sched_timeslice_properties_t
typedef struct _zes_sched_timeslice_properties_t zes_sched_timeslice_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_standby_properties_t
typedef struct _zes_standby_properties_t zes_standby_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_temp_properties_t
typedef struct _zes_temp_properties_t zes_temp_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_temp_threshold_t
typedef struct _zes_temp_threshold_t zes_temp_threshold_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zes_temp_config_t
typedef struct _zes_temp_config_t zes_temp_config_t;


#pragma endregion
#pragma region device
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of Sysman
typedef enum _zes_version_t
{
    ZES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ), ///< version 0.91

} zes_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define ZES_STRING_PROPERTY_SIZE  64
#endif // ZES_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Types of accelerator engines
typedef enum _zes_engine_type_t
{
    ZES_ENGINE_TYPE_OTHER = 0,                      ///< Undefined types of accelerators.
    ZES_ENGINE_TYPE_COMPUTE,                        ///< Engines that process compute kernels.
    ZES_ENGINE_TYPE_3D,                             ///< Engines that process 3D content
    ZES_ENGINE_TYPE_MEDIA,                          ///< Engines that process media workloads
    ZES_ENGINE_TYPE_DMA,                            ///< Engines that copy blocks of data

} zes_engine_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device repair status
typedef enum _zes_repair_status_t
{
    ZES_REPAIR_STATUS_UNSUPPORTED = 0,              ///< The device does not support in-field repairs.
    ZES_REPAIR_STATUS_NOT_PERFORMED,                ///< The device has never been repaired.
    ZES_REPAIR_STATUS_PERFORMED,                    ///< The device has been repaired.

} zes_repair_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device reset reasons
typedef enum _zes_reset_reasons_t
{
    ZES_RESET_REASONS_NONE = 0,                     ///< The device does not need to be reset
    ZES_RESET_REASONS_WEDGED = ZE_BIT( 0 ),         ///< The device needs to be reset because one or more parts of the hardware
                                                    ///< is wedged
    ZES_RESET_REASONS_REPAIR = ZE_BIT( 1 ),         ///< The device needs to be reset in order to complete in-field repairs

} zes_reset_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device state
typedef struct _zes_device_state_t
{
    uint32_t reset;                                 ///< [out] Indicates if the device needs to be reset and for what reasons
                                                    ///< (bitfield of ::zes_reset_reasons_t)
    zes_repair_status_t repaired;                   ///< [out] Indicates if the device has been repaired

} zes_device_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties
typedef struct _zes_device_properties_t
{
    ze_device_properties_t core;                    ///< [out] Core device properties
    uint32_t numSubdevices;                         ///< [out] Number of sub-devices
    int8_t serialNumber[ZES_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
    int8_t boardNumber[ZES_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
    int8_t brandName[ZES_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
    int8_t modelName[ZES_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
    int8_t vendorName[ZES_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
    int8_t driverVersion[ZES_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)

} zes_device_properties_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
__ze_api_export ze_result_t __zecall
zesDeviceGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
    );

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
__ze_api_export ze_result_t __zecall
zesDeviceGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
    );

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE - "Reset cannot be performed because applications are using this device."
///     - ::ZE_RESULT_ERROR_UNKNOWN - "There were problems unloading the device driver, performing a bus reset or reloading the device driver."
__ze_api_export ze_result_t __zecall
zesDeviceReset(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                    ///< device will be forcibly killed.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Contains information about a process that has an open connection with
///        this device
/// 
/// @details
///     - The application can use the process ID to query the OS for the owner
///       and the path to the executable.
typedef struct _zes_process_state_t
{
    uint32_t processId;                             ///< [out] Host OS process ID.
    int64_t memSize;                                ///< [out] Device memory size in bytes allocated by this process (may not
                                                    ///< necessarily be resident on the device at the time of reading).
    uint64_t engines;                               ///< [out] Bitfield of accelerator engines being used by this process (or
                                                    ///< 1<<::zes_engine_type_t together).

} zes_process_state_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The provided value of pCount is not big enough to store information about all the processes currently attached to the device.
__ze_api_export ze_result_t __zecall
zesDeviceProcessesGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of processes currently using the device.
                                                    ///< if count is non-zero but less than the number of processes, the driver
                                                    ///< will set to the number of processes currently using the device and
                                                    ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                    ///< if count is larger than the number of processes, then the driver will
                                                    ///< update the value with the correct number of processes that are returned.
    zes_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                    ///< one for each process currently using the device
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI address
typedef struct _zes_pci_address_t
{
    uint32_t domain;                                ///< [out] BDF domain
    uint32_t bus;                                   ///< [out] BDF bus
    uint32_t device;                                ///< [out] BDF device
    uint32_t function;                              ///< [out] BDF function

} zes_pci_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI speed
typedef struct _zes_pci_speed_t
{
    uint32_t gen;                                   ///< [out] The link generation
    uint32_t width;                                 ///< [out] The number of lanes
    uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

} zes_pci_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static PCI properties
typedef struct _zes_pci_properties_t
{
    zes_pci_address_t address;                      ///< [out] The BDF address
    zes_pci_speed_t maxSpeed;                       ///< [out] Fastest port configuration supported by the device.

} zes_pci_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI link status
typedef enum _zes_pci_link_status_t
{
    ZES_PCI_LINK_STATUS_GREEN = 0,                  ///< The link is up and operating as expected
    ZES_PCI_LINK_STATUS_YELLOW,                     ///< The link is up but has quality and/or bandwidth degradation
    ZES_PCI_LINK_STATUS_RED,                        ///< The link has stability issues and preventing workloads making forward
                                                    ///< progress

} zes_pci_link_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI link quality degradation reasons
typedef enum _zes_pci_link_qual_issues_t
{
    ZES_PCI_LINK_QUAL_ISSUES_NONE = 0,              ///< There are no quality issues with the link at this time
    ZES_PCI_LINK_QUAL_ISSUES_REPLAYS = ZE_BIT( 0 ), ///< An significant number of replays are occurring
    ZES_PCI_LINK_QUAL_ISSUES_SPEED = ZE_BIT( 1 ),   ///< There is a degradation in the maximum bandwidth of the link

} zes_pci_link_qual_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI link stability issues
typedef enum _zes_pci_link_stab_issues_t
{
    ZES_PCI_LINK_STAB_ISSUES_NONE = 0,              ///< There are no connection stability issues at this time
    ZES_PCI_LINK_STAB_ISSUES_RETRAINING = ZE_BIT( 0 ),  ///< Link retraining has occurred to deal with quality issues

} zes_pci_link_stab_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic PCI state
typedef struct _zes_pci_state_t
{
    zes_pci_link_status_t status;                   ///< [out] The current status of the port
    zes_pci_link_qual_issues_t qualityIssues;       ///< [out] If status is ::ZES_PCI_LINK_STATUS_YELLOW, this gives a bitfield
                                                    ///< of quality issues that have been detected
    zes_pci_link_stab_issues_t stabilityIssues;     ///< [out] If status is ::ZES_PCI_LINK_STATUS_RED, this gives a bitfield of
                                                    ///< reasons for the connection instability
    zes_pci_speed_t speed;                          ///< [out] The current port configure speed

} zes_pci_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI bar types
typedef enum _zes_pci_bar_type_t
{
    ZES_PCI_BAR_TYPE_MMIO = 0,                      ///< MMIO registers
    ZES_PCI_BAR_TYPE_ROM,                           ///< ROM aperture
    ZES_PCI_BAR_TYPE_MEM,                           ///< Device memory

} zes_pci_bar_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Properties of a pci bar
typedef struct _zes_pci_bar_properties_t
{
    zes_pci_bar_type_t type;                        ///< [out] The type of bar
    uint32_t index;                                 ///< [out] The index of the bar
    uint64_t base;                                  ///< [out] Base address of the bar.
    uint64_t size;                                  ///< [out] Size of the bar.

} zes_pci_bar_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI stats counters
/// 
/// @details
///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
///       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
///       s1.timestamp))
///     - Percent replays is calculated by taking two snapshots (s1, s2) and
///       using the equation: %replay = 10^6 * (s2.replayCounter -
///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _zes_pci_stats_t
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
    uint64_t rxCounter;                             ///< [out] Monotonic counter for the number of bytes received
    uint64_t txCounter;                             ///< [out] Monotonic counter for the number of bytes transmitted (including
                                                    ///< replays)
    zes_pci_speed_t speed;                          ///< [out] The current speed of the link

} zes_pci_stats_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
__ze_api_export ze_result_t __zecall
zesDevicePciGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
    );

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
__ze_api_export ze_result_t __zecall
zesDevicePciGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
    );

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDevicePciGetBars(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of bars.
                                                    ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                    ///< if count is larger than the number of bar, then the driver will update
                                                    ///< the value with the correct number of bars that are returned.
    zes_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of bar properties
    );

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
__ze_api_export ze_result_t __zecall
zesDevicePciGetStats(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
    );

#pragma endregion
#pragma region diagnostics
///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic test suite type
typedef enum _zes_diag_type_t
{
    ZES_DIAG_TYPE_SCAN = 0,                         ///< Run SCAN diagnostics
    ZES_DIAG_TYPE_ARRAY,                            ///< Run Array diagnostics

} zes_diag_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic results
typedef enum _zes_diag_result_t
{
    ZES_DIAG_RESULT_NO_ERRORS = 0,                  ///< Diagnostic completed without finding errors to repair
    ZES_DIAG_RESULT_ABORT,                          ///< Diagnostic had problems running tests
    ZES_DIAG_RESULT_FAIL_CANT_REPAIR,               ///< Diagnostic had problems setting up repairs
    ZES_DIAG_RESULT_REBOOT_FOR_REPAIR,              ///< Diagnostics found errors, setup for repair and reboot is required to
                                                    ///< complete the process

} zes_diag_result_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_DIAG_FIRST_TEST_INDEX
/// @brief Diagnostic test index to use for the very first test.
#define ZES_DIAG_FIRST_TEST_INDEX  0x0
#endif // ZES_DIAG_FIRST_TEST_INDEX

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_DIAG_LAST_TEST_INDEX
/// @brief Diagnostic test index to use for the very last test.
#define ZES_DIAG_LAST_TEST_INDEX  0xFFFFFFFF
#endif // ZES_DIAG_LAST_TEST_INDEX

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic test
typedef struct _zes_diag_test_t
{
    uint32_t index;                                 ///< [out] Index of the test
    char name[ZES_STRING_PROPERTY_SIZE];            ///< [out] Name of the test

} zes_diag_test_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostics test suite properties
typedef struct _zes_diag_properties_t
{
    zes_diag_type_t type;                           ///< [out] The type of diagnostics test suite
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    char name[ZES_STRING_PROPERTY_SIZE];            ///< [out] Name of the diagnostics test suite
    ze_bool_t haveTests;                            ///< [out] Indicates if this test suite has individual tests which can be
                                                    ///< run separately (use the function ::zesDiagnosticsGetTests() to get the
                                                    ///< list of these tests)

} zes_diag_properties_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumDiagnosticTestSuites(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_diag_handle_t* phDiagnostics                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesDiagnosticsGetProperties(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                    ///< suite
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get individual tests that can be run separately. Not all test suites
///        permit running individual tests - check
///        ::zes_diag_properties_t.haveTests
/// 
/// @details
///     - The list of available tests is returned in order of increasing test
///       index ::zes_diag_test_t.index.
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
__ze_api_export ze_result_t __zecall
zesDiagnosticsGetTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of tests available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                    ///< If count is larger than the number of tests available, then the driver
                                                    ///< will update the value with the correct number of tests available.
    zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                    ///< increasing value of ::zes_diag_test_t.index
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - WARNING: Performancing diagnostics may destroy current device state
///       information. Gracefully close any running workloads before initiating.
///     - To run all tests in a test suite, set start =
///       ::ZES_DIAG_FIRST_TEST_INDEX and end = ::ZES_DIAG_LAST_TEST_INDEX.
///     - If the test suite permits running individual tests,
///       ::zes_diag_properties_t.haveTests will be true. In this case, the
///       function ::zesDiagnosticsGetTests() can be called to get the list of
///       tests and corresponding indices that can be supplied to the arguments
///       start and end in this function.
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
__ze_api_export ze_result_t __zecall
zesDiagnosticsRunTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
    );

#pragma endregion
#pragma region engine
///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator engine groups
typedef enum _zes_engine_group_t
{
    ZES_ENGINE_GROUP_ALL = 0,                       ///< Access information about all engines combined.
    ZES_ENGINE_GROUP_COMPUTE_ALL,                   ///< Access information about all compute engines combined.
    ZES_ENGINE_GROUP_MEDIA_ALL,                     ///< Access information about all media engines combined.
    ZES_ENGINE_GROUP_COPY_ALL,                      ///< Access information about all copy (blitter) engines combined.

} zes_engine_group_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine group properties
typedef struct _zes_engine_properties_t
{
    zes_engine_group_t type;                        ///< [out] The engine group
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zes_engine_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine activity counters
/// 
/// @details
///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
///       using the equation: %util = (s2.activeTime - s1.activeTime) /
///       (s2.timestamp - s1.timestamp)
typedef struct _zes_engine_stats_t
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

} zes_engine_stats_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumEngineGroups(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_engine_handle_t* phEngine                   ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesEngineGetProperties(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
    );

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
__ze_api_export ze_result_t __zecall
zesEngineGetActivity(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                    ///< counters.
    );

#pragma endregion
#pragma region events
///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _zes_event_type_t
{
    ZES_EVENT_TYPE_NONE = 0,                        ///< Specifies no events
    ZES_EVENT_TYPE_DEVICE_RESET = ZE_BIT( 0 ),      ///< Event is triggered when the driver is going to reset the device
    ZES_EVENT_TYPE_DEVICE_SLEEP_STATE_ENTER = ZE_BIT( 1 ),  ///< Event is triggered when the driver is about to put the device into a
                                                    ///< deep sleep state
    ZES_EVENT_TYPE_DEVICE_SLEEP_STATE_EXIT = ZE_BIT( 2 ),   ///< Event is triggered when the driver is waking the device up from a deep
                                                    ///< sleep state
    ZES_EVENT_TYPE_FREQ_THROTTLED = ZE_BIT( 3 ),    ///< Event is triggered when the frequency starts being throttled
    ZES_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED = ZE_BIT( 4 ),  ///< Event is triggered when the energy consumption threshold is reached
                                                    ///< (use ::zesPowerSetEnergyThreshold() to configure).
    ZES_EVENT_TYPE_TEMP_CRITICAL = ZE_BIT( 5 ),     ///< Event is triggered when the critical temperature is reached (use
                                                    ///< ::zesTemperatureSetConfig() to configure - disabled by default).
    ZES_EVENT_TYPE_TEMP_THRESHOLD1 = ZE_BIT( 6 ),   ///< Event is triggered when the temperature crosses threshold 1 (use
                                                    ///< ::zesTemperatureSetConfig() to configure - disabled by default).
    ZES_EVENT_TYPE_TEMP_THRESHOLD2 = ZE_BIT( 7 ),   ///< Event is triggered when the temperature crosses threshold 2 (use
                                                    ///< ::zesTemperatureSetConfig() to configure - disabled by default).
    ZES_EVENT_TYPE_MEM_HEALTH = ZE_BIT( 8 ),        ///< Event is triggered when the health of device memory changes.
    ZES_EVENT_TYPE_FABRIC_PORT_HEALTH = ZE_BIT( 9 ),///< Event is triggered when the health of fabric ports change.
    ZES_EVENT_TYPE_PCI_LINK_HEALTH = ZE_BIT( 10 ),  ///< Event is triggered when the health of the PCI link changes.
    ZES_EVENT_TYPE_RAS_CORRECTABLE_ERRORS = ZE_BIT( 11 ),   ///< Event is triggered when accelerator RAS correctable errors cross
                                                    ///< thresholds (use ::zesRasSetConfig() to configure - disabled by
                                                    ///< default).
    ZES_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS = ZE_BIT( 12 ), ///< Event is triggered when accelerator RAS uncorrectable errors cross
                                                    ///< thresholds (use ::zesRasSetConfig() to configure - disabled by
                                                    ///< default).
    ZES_EVENT_TYPE_DEVICE_RESET_REQUIRED = ZE_BIT( 14 ),///< Event is triggered when the device needs to be reset (use
                                                    ///< ::zesDeviceGetState() to determine the reasons for the reset).
    ZES_EVENT_TYPE_ALL = 0x0FFF,                    ///< Specifies all events

} zes_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event configuration for a device
typedef struct _zes_event_config_t
{
    uint32_t registered;                            ///< [in,out] List of registered events (Bitfield of events
                                                    ///< ::zes_event_type_t). ::ZES_EVENT_TYPE_NONE indicates there are no
                                                    ///< registered events. ::ZES_EVENT_TYPE_ALL indicates that all events are
                                                    ///< registered.

} zes_event_config_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvent`
__ze_api_export ze_result_t __zecall
zesDeviceCreateEvents(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    zes_event_handle_t* phEvent                     ///< [out] The event handle for the specified device.
    );

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
__ze_api_export ze_result_t __zecall
zesEventGetConfig(
    zes_event_handle_t hEvent,                      ///< [in] The event handle for the device
    zes_event_config_t* pConfig                     ///< [in,out] Will contain the current event configuration (list of
                                                    ///< registered events).
    );

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
__ze_api_export ze_result_t __zecall
zesEventSetConfig(
    zes_event_handle_t hEvent,                      ///< [in] The event handle for the device
    const zes_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
    );

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
__ze_api_export ze_result_t __zecall
zesEventGetState(
    zes_event_handle_t hEvent,                      ///< [in] The event handle for the device.
    ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_event_type_t that have been
                                                    ///< triggered by this device.
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_EVENT_WAIT_NONE
/// @brief Don't wait - just check if there are any new events
#define ZES_EVENT_WAIT_NONE  0x0
#endif // ZES_EVENT_WAIT_NONE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_EVENT_WAIT_INFINITE
/// @brief Wait infinitely for events to arrive.
#define ZES_EVENT_WAIT_INFINITE  0xFFFFFFFF
#endif // ZES_EVENT_WAIT_INFINITE

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for the specified list of event handles to receive any registered
///        events
/// 
/// @details
///     - If previous events arrived and were not cleared using
///       ::zesEventGetState(), this call will return immediately.
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
__ze_api_export ze_result_t __zecall
zesEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                    ///< ::ZES_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                    ///< ::ZES_EVENT_WAIT_INFINITE to block until events arrive.
    uint32_t count,                                 ///< [in] Number of handles in phEvents
    zes_event_handle_t* phEvents,                   ///< [in][range(0, count)] Handle of events that should be listened to
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_event_type_t that have been
                                                    ///< triggered by any of the supplied event handles. If timeout is not
                                                    ///< ::ZES_EVENT_WAIT_INFINITE and this value is ::ZES_EVENT_TYPE_NONE,
                                                    ///< then a timeout has occurred.
    );

#pragma endregion
#pragma region fabric
///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_MAX_FABRIC_PORT_MODEL_SIZE
/// @brief Maximum Fabric port model string size
#define ZES_MAX_FABRIC_PORT_MODEL_SIZE  256
#endif // ZES_MAX_FABRIC_PORT_MODEL_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_MAX_FABRIC_LINK_TYPE_SIZE
/// @brief Maximum size of the buffer that will return information about link
///        types
#define ZES_MAX_FABRIC_LINK_TYPE_SIZE  256
#endif // ZES_MAX_FABRIC_LINK_TYPE_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port status
typedef enum _zes_fabric_port_status_t
{
    ZES_FABRIC_PORT_STATUS_GREEN = 0,               ///< The port is up and operating as expected
    ZES_FABRIC_PORT_STATUS_YELLOW,                  ///< The port is up but has quality and/or speed degradation
    ZES_FABRIC_PORT_STATUS_RED,                     ///< Port connection instabilities are preventing workloads making forward
                                                    ///< progress
    ZES_FABRIC_PORT_STATUS_BLACK,                   ///< The port is configured down

} zes_fabric_port_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port quality degradation reasons
typedef enum _zes_fabric_port_qual_issues_t
{
    ZES_FABRIC_PORT_QUAL_ISSUES_NONE = 0,           ///< There are no quality issues with the link at this time
    ZES_FABRIC_PORT_QUAL_LINK_ERRORS = ZE_BIT( 0 ), ///< Excessive link errors are occurring
    ZES_FABRIC_PORT_QUAL_ISSUES_SPEED = ZE_BIT( 1 ),///< There is a degradation in the bitrate and/or width of the link

} zes_fabric_port_qual_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port stability issues
typedef enum _zes_fabric_port_stab_issues_t
{
    ZES_FABRIC_PORT_STAB_ISSUES_NONE = 0,           ///< There are no connection stability issues at this time
    ZES_FABRIC_PORT_STAB_ISSUES_FAILED = ZE_BIT( 0 ),   ///< A previously operating link has failed. Hardware will automatically
                                                    ///< retrain this port. This state will persist until either the physical
                                                    ///< connection is removed or the link trains successfully.
    ZES_FABRIC_PORT_STAB_ISSUES_TRAINING_TIMEOUT = ZE_BIT( 1 ), ///< A connection has not been established within an expected time.
                                                    ///< Hardware will continue to attempt port training. This status will
                                                    ///< persist until either the physical connection is removed or the link
                                                    ///< successfully trains.
    ZES_FABRIC_PORT_STAB_ISSUES_FLAPPING = ZE_BIT( 2 ), ///< Port has excessively trained and then transitioned down for some
                                                    ///< period of time. Driver will allow port to continue to train, but will
                                                    ///< not enable the port for use until the port has been disabled and
                                                    ///< subsequently re-enabled using ::zesFabricPortSetConfig().

} zes_fabric_port_stab_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Unique identifier for a fabric port
/// 
/// @details
///     - This not a universal identifier. The identified is garanteed to be
///       unique for the current hardware configuration of the system. Changes
///       in the hardware may result in a different identifier for a given port.
///     - The main purpose of this identifier to build up an instantaneous
///       topology map of system connectivity. An application should enumerate
///       all fabric ports and match ::zes_fabric_port_state_t.remotePortId to
///       ::zes_fabric_port_properties_t.portId.
typedef struct _zes_fabric_port_id_t
{
    uint32_t fabricId;                              ///< [out] Unique identifier for the fabric end-point
    uint32_t attachId;                              ///< [out] Unique identifier for the device attachment point
    uint8_t portNumber;                             ///< [out] The logical port number (this is typically marked somewhere on
                                                    ///< the physical device)

} zes_fabric_port_id_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port speed in one direction
typedef struct _zes_fabric_port_speed_t
{
    uint64_t bitRate;                               ///< [out] Bits/sec that the link is operating at
    uint32_t width;                                 ///< [out] The number of lanes

} zes_fabric_port_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port properties
typedef struct _zes_fabric_port_properties_t
{
    int8_t model[ZES_MAX_FABRIC_PORT_MODEL_SIZE];   ///< [out] Description of port technology
    ze_bool_t onSubdevice;                          ///< [out] True if the port is located on a sub-device; false means that
                                                    ///< the port is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    zes_fabric_port_id_t portId;                    ///< [out] The unique port identifier
    zes_fabric_port_speed_t maxRxSpeed;             ///< [out] Maximum speed supported by the receive side of the port
    zes_fabric_port_speed_t maxTxSpeed;             ///< [out] Maximum speed supported by the transmit side of the port

} zes_fabric_port_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides information about the fabric link attached to a port
typedef struct _zes_fabric_link_type_t
{
    int8_t desc[ZES_MAX_FABRIC_LINK_TYPE_SIZE];     ///< [out] This provides a static textural description of the physic
                                                    ///< attachment type

} zes_fabric_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port configuration
typedef struct _zes_fabric_port_config_t
{
    ze_bool_t enabled;                              ///< [in,out] Port is configured up/down
    ze_bool_t beaconing;                            ///< [in,out] Beaconing is configured on/off

} zes_fabric_port_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port state
typedef struct _zes_fabric_port_state_t
{
    zes_fabric_port_status_t status;                ///< [out] The current status of the port
    zes_fabric_port_qual_issues_t qualityIssues;    ///< [out] If status is ::ZES_FABRIC_PORT_STATUS_YELLOW, this gives a
                                                    ///< bitfield of quality issues that have been detected
    zes_fabric_port_stab_issues_t stabilityIssues;  ///< [out] If status is ::ZES_FABRIC_PORT_STATUS_RED, this gives a bitfield
                                                    ///< of reasons for the connection instability
    zes_fabric_port_id_t remotePortId;              ///< [out] The unique port identifier for the remote connection point
    zes_fabric_port_speed_t rxSpeed;                ///< [out] Current maximum receive speed
    zes_fabric_port_speed_t txSpeed;                ///< [out] Current maximum transmit speed

} zes_fabric_port_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port throughput.
typedef struct _zes_fabric_port_throughput_t
{
    uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when the measurement
                                                    ///< was made.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.
    uint64_t rxCounter;                             ///< [out] Monotonic counter for the number of bytes received. This
                                                    ///< includes all protocol overhead, not only the GPU traffic.
    uint64_t txCounter;                             ///< [out] Monotonic counter for the number of bytes transmitted. This
                                                    ///< includes all protocol overhead, not only the GPU traffic.

} zes_fabric_port_throughput_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumFabricPorts(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_fabric_port_handle_t* phPort                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesFabricPortGetProperties(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
    );

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
__ze_api_export ze_result_t __zecall
zesFabricPortGetLinkType(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
    zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                    ///< port.
    );

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
__ze_api_export ze_result_t __zecall
zesFabricPortGetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
    );

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
__ze_api_export ze_result_t __zecall
zesFabricPortSetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    );

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
__ze_api_export ze_result_t __zecall
zesFabricPortGetState(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
    );

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
__ze_api_export ze_result_t __zecall
zesFabricPortGetThroughput(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
    );

#pragma endregion
#pragma region fan
///////////////////////////////////////////////////////////////////////////////
/// @brief Fan resource speed mode
typedef enum _zes_fan_speed_mode_t
{
    ZES_FAN_SPEED_MODE_DEFAULT = 0,                 ///< The fan speed is operating using the hardware default settings
    ZES_FAN_SPEED_MODE_FIXED,                       ///< The fan speed is currently set to a fixed value
    ZES_FAN_SPEED_MODE_TABLE,                       ///< The fan speed is currently controlled dynamically by hardware based on
                                                    ///< a temp/speed table

} zes_fan_speed_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan speed units
typedef enum _zes_fan_speed_units_t
{
    ZES_FAN_SPEED_UNITS_RPM = 0,                    ///< The fan speed is in units of revolutions per minute (rpm)
    ZES_FAN_SPEED_UNITS_PERCENT,                    ///< The fan speed is a percentage of the maximum speed of the fan

} zes_fan_speed_units_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan temperature/speed pair
typedef struct _zes_fan_temp_speed_t
{
    uint32_t temperature;                           ///< [in,out] Temperature in degrees Celsius.
    uint32_t speed;                                 ///< [in,out] The speed of the fan
    zes_fan_speed_units_t units;                    ///< [in,out] The units of the member speed

} zes_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define ZES_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // ZES_FAN_TEMP_SPEED_PAIR_COUNT

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan properties
typedef struct _zes_fan_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the fan speed assuming the
                                                    ///< user has permissions
    uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan
    uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

} zes_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan configuration
typedef struct _zes_fan_config_t
{
    zes_fan_speed_mode_t mode;                      ///< [in,out] The fan speed mode (fixed, temp-speed table)
    uint32_t speed;                                 ///< [in,out] The fixed fan speed setting
    zes_fan_speed_units_t speedUnits;               ///< [in,out] The units of the fixed fan speed setting
    uint32_t numPoints;                             ///< [in,out] The number of valid points in the fan speed table
    zes_fan_temp_speed_t table[ZES_FAN_TEMP_SPEED_PAIR_COUNT];  ///< [in,out] Array of temperature/fan speed pairs

} zes_fan_config_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumFans(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_fan_handle_t* phFan                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesFanGetProperties(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
    );

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
__ze_api_export ze_result_t __zecall
zesFanGetConfig(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
    );

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
__ze_api_export ze_result_t __zecall
zesFanSetConfig(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    const zes_fan_config_t* pConfig                 ///< [in] New fan configuration.
    );

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
__ze_api_export ze_result_t __zecall
zesFanGetState(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                    ///< requested.
    );

#pragma endregion
#pragma region firmware
///////////////////////////////////////////////////////////////////////////////
/// @brief Firmware properties
typedef struct _zes_firmware_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can flash the firmware assuming the user
                                                    ///< has permissions
    int8_t name[ZES_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
    int8_t version[ZES_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

} zes_firmware_properties_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumFirmwares(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_firmware_handle_t* phFirmware               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesFirmwareGetProperties(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                    ///< firmware
    );

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
__ze_api_export ze_result_t __zecall
zesFirmwareGetChecksum(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
    );

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
__ze_api_export ze_result_t __zecall
zesFirmwareFlash(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    );

#pragma endregion
#pragma region frequency
///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domains.
typedef enum _zes_freq_domain_t
{
    ZES_FREQ_DOMAIN_GPU = 0,                        ///< GPU Core Domain.
    ZES_FREQ_DOMAIN_MEMORY,                         ///< Local Memory Domain.

} zes_freq_domain_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency properties
/// 
/// @details
///     - Indicates if this frequency domain can be overclocked (if true,
///       functions such as ::zesFrequencyOcSetConfig() are supported).
///     - The min/max hardware frequencies are specified for non-overclock
///       configurations. For overclock configurations, use
///       ::zesFrequencyOcGetConfig() to determine the maximum frequency that
///       can be requested.
///     - If step is non-zero, the available frequencies are (min, min + step,
///       min + 2xstep, ..., max). Otherwise, call
///       ::zesFrequencyGetAvailableClocks() to get the list of frequencies that
///       can be requested.
typedef struct _zes_freq_properties_t
{
    zes_freq_domain_t type;                         ///< [out] The hardware block that this frequency domain controls (GPU,
                                                    ///< memory, ...)
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the frequency of this domain
                                                    ///< assuming the user has permissions
    ze_bool_t isThrottleEventSupported;             ///< [out] Indicates if software can register to receive event
                                                    ///< ::ZES_EVENT_TYPE_FREQ_THROTTLED
    double min;                                     ///< [out] The minimum hardware clock frequency in units of MHz
    double max;                                     ///< [out] The maximum non-overclock hardware clock frequency in units of
                                                    ///< MHz.
    double step;                                    ///< [out] The minimum step-size for clock frequencies in units of MHz. The
                                                    ///< hardware will clamp intermediate frequencies to lowest multiplier of
                                                    ///< this number.

} zes_freq_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency range between which the hardware can operate.
typedef struct _zes_freq_range_t
{
    double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.
    double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.

} zes_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle reasons
typedef enum _zes_freq_throttle_reasons_t
{
    ZES_FREQ_THROTTLE_REASONS_NONE = 0,             ///< frequency not throttled
    ZES_FREQ_THROTTLE_REASONS_AVE_PWR_CAP = ZE_BIT( 0 ),///< frequency throttled due to average power excursion (PL1)
    ZES_FREQ_THROTTLE_REASONS_BURST_PWR_CAP = ZE_BIT( 1 ),  ///< frequency throttled due to burst power excursion (PL2)
    ZES_FREQ_THROTTLE_REASONS_CURRENT_LIMIT = ZE_BIT( 2 ),  ///< frequency throttled due to current excursion (PL4)
    ZES_FREQ_THROTTLE_REASONS_THERMAL_LIMIT = ZE_BIT( 3 ),  ///< frequency throttled due to thermal excursion (T > TjMax)
    ZES_FREQ_THROTTLE_REASONS_PSU_ALERT = ZE_BIT( 4 ),  ///< frequency throttled due to power supply assertion
    ZES_FREQ_THROTTLE_REASONS_SW_RANGE = ZE_BIT( 5 ),   ///< frequency throttled due to software supplied frequency range
    ZES_FREQ_THROTTLE_REASONS_HW_RANGE = ZE_BIT( 6 ),   ///< frequency throttled due to a sub block that has a lower frequency
                                                    ///< range when it receives clocks

} zes_freq_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency state
typedef struct _zes_freq_state_t
{
    double request;                                 ///< [out] The current frequency request in MHz.
    double tdp;                                     ///< [out] The maximum frequency in MHz supported under the current TDP
                                                    ///< conditions
    double efficient;                               ///< [out] The efficient minimum frequency in MHz
    double actual;                                  ///< [out] The resolved frequency in MHz
    uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the hardware
                                                    ///< (Bitfield of ::zes_freq_throttle_reasons_t).

} zes_freq_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle time snapshot
/// 
/// @details
///     - Percent time throttled is calculated by taking two snapshots (s1, s2)
///       and using the equation: %throttled = (s2.throttleTime -
///       s1.throttleTime) / (s2.timestamp - s1.timestamp)
typedef struct _zes_freq_throttle_time_t
{
    uint64_t throttleTime;                          ///< [out] The monotonic counter of time in microseconds that the frequency
                                                    ///< has been limited by the hardware.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when throttleTime was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zes_freq_throttle_time_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking modes
typedef enum _zes_oc_mode_t
{
    ZES_OC_MODE_OFF = 0,                            ///< Overclocking if off - hardware is running using factory default
                                                    ///< voltages/frequencies.
    ZES_OC_MODE_OVERRIDE,                           ///< Overclock override mode - In this mode, a fixed user-supplied voltage
                                                    ///< is applied independent of the frequency request. The maximum permitted
                                                    ///< frequency can also be increased.
    ZES_OC_MODE_INTERPOLATIVE,                      ///< Overclock interpolative mode - In this mode, the voltage/frequency
                                                    ///< curve can be extended with a new voltage/frequency point that will be
                                                    ///< interpolated. The existing voltage/frequency points can also be offset
                                                    ///< (up or down) by a fixed voltage.

} zes_oc_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking properties
/// 
/// @details
///     - Provides all the overclocking capabilities and properties supported by
///       the device for the frequency domain.
typedef struct _zes_oc_capabilities_t
{
    ze_bool_t isOcSupported;                        ///< [out] Indicates if any overclocking features are supported on this
                                                    ///< frequency domain.
    double maxFactoryDefaultFrequency;              ///< [out] Factory default non-overclock maximum frequency in Mhz.
    double maxFactoryDefaultVoltage;                ///< [out] Factory default voltage used for the non-overclock maximum
                                                    ///< frequency in MHz.
    double maxOcFrequency;                          ///< [out] Maximum hardware overclocking frequency limit in Mhz.
    double minOcVoltageOffset;                      ///< [out] The minimum voltage offset that can be applied to the
                                                    ///< voltage/frequency curve. Note that this number can be negative.
    double maxOcVoltageOffset;                      ///< [out] The maximum voltage offset that can be applied to the
                                                    ///< voltage/frequency curve.
    double maxOcVoltage;                            ///< [out] The maximum overclock voltage that hardware supports.
    ze_bool_t isTjMaxSupported;                     ///< [out] Indicates if the maximum temperature limit (TjMax) can be
                                                    ///< changed for this frequency domain.
    ze_bool_t isIccMaxSupported;                    ///< [out] Indicates if the maximum current (IccMax) can be changed for
                                                    ///< this frequency domain.
    ze_bool_t isHighVoltModeCapable;                ///< [out] Indicates if this frequency domains supports a feature to set
                                                    ///< very high voltages.
    ze_bool_t isHighVoltModeEnabled;                ///< [out] Indicates if very high voltages are permitted on this frequency
                                                    ///< domain.

} zes_oc_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking configuration
/// 
/// @details
///     - Overclock settings
typedef struct _zes_oc_config_t
{
    zes_oc_mode_t mode;                             ///< [in,out] Overclock Mode ::zes_oc_mode_t.
    double frequency;                               ///< [in,out] Overclocking Frequency in MHz. This cannot be greater than
                                                    ///< ::zes_oc_capabilities_t.maxOcFrequency.
    double voltageTarget;                           ///< [in,out] Overclock voltage in Volts. This cannot be greater than
                                                    ///< ::zes_oc_capabilities_t.maxOcVoltage.
    double voltageOffset;                           ///< [in,out] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                    ///< can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset,
                                                    ///< ::zes_oc_capabilities_t.maxOcVoltageOffset).

} zes_oc_config_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumFrequencyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_freq_handle_t* phFrequency                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesFrequencyGetProperties(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zesFrequencyGetAvailableClocks(
    zes_freq_handle_t hFrequency,                   ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of frequencies available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                    ///< If count is larger than the number of frequencies available, then the
                                                    ///< driver will update the value with the correct number of frequencies available.
    double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                    ///< MHz and sorted from slowest to fastest
    );

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
__ze_api_export ze_result_t __zecall
zesFrequencyGetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                    ///< specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zesFrequencySetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zesFrequencyGetState(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zesFrequencyGetThrottleTime(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zesFrequencyOcGetCapabilities(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                    ///< ::zes_oc_capabilities_t.
    );

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
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
__ze_api_export ze_result_t __zecall
zesFrequencyOcGetConfig(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zes_oc_config_t.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the overclocking configuration.
/// 
/// @details
///     - If ::zes_oc_config_t.mode is set to ::ZES_OC_MODE_OFF, overclocking
///       will be turned off and the hardware returned to run with factory
///       voltages/frequencies. Call ::zesFrequencyOcSetIccMax() and
///       ::zesFrequencyOcSetTjMax() separately with 0.0 to return those
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
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
__ze_api_export ze_result_t __zecall
zesFrequencyOcSetConfig(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zes_oc_config_t.
    ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                    ///< in order to enable the new overclock settings.
    );

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
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
__ze_api_export ze_result_t __zecall
zesFrequencyOcGetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                    ///< successful return.
    );

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
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified current limit is too low or too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
__ze_api_export ze_result_t __zecall
zesFrequencyOcSetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    );

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
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
__ze_api_export ze_result_t __zecall
zesFrequencyOcGetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                    ///< on successful return.
    );

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
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isTjMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified temperature limit is too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
__ze_api_export ze_result_t __zecall
zesFrequencyOcSetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    );

#pragma endregion
#pragma region led
///////////////////////////////////////////////////////////////////////////////
/// @brief LED properties
typedef struct _zes_led_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the LED assuming the user has
                                                    ///< permissions
    ze_bool_t haveRGB;                              ///< [out] Indicates if the LED is RGB capable

} zes_led_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief LED state
typedef struct _zes_led_state_t
{
    ze_bool_t isOn;                                 ///< [in,out] Indicates if the LED is on or off
    uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
    uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
    uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

} zes_led_state_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumLeds(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_led_handle_t* phLed                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesLedGetProperties(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
    );

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
__ze_api_export ze_result_t __zecall
zesLedGetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
    );

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
__ze_api_export ze_result_t __zecall
zesLedSetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    const zes_led_state_t* pState                   ///< [in] New state of the LED.
    );

#pragma endregion
#pragma region memory
///////////////////////////////////////////////////////////////////////////////
/// @brief Memory module types
typedef enum _zes_mem_type_t
{
    ZES_MEM_TYPE_HBM = 0,                           ///< HBM memory
    ZES_MEM_TYPE_DDR,                               ///< DDR memory
    ZES_MEM_TYPE_SRAM,                              ///< SRAM memory
    ZES_MEM_TYPE_L1,                                ///< L1 cache
    ZES_MEM_TYPE_L3,                                ///< L3 cache
    ZES_MEM_TYPE_GRF,                               ///< Execution unit register file
    ZES_MEM_TYPE_SLM,                               ///< Execution unit shared local memory

} zes_mem_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory health
typedef enum _zes_mem_health_t
{
    ZES_MEM_HEALTH_OK = 0,                          ///< All memory channels are healthy
    ZES_MEM_HEALTH_DEGRADED,                        ///< Excessive correctable errors have been detected on one or more
                                                    ///< channels. Device should be reset.
    ZES_MEM_HEALTH_CRITICAL,                        ///< Operating with reduced memory to cover banks with too many
                                                    ///< uncorrectable errors.
    ZES_MEM_HEALTH_REPLACE,                         ///< Device should be replaced due to excessive uncorrectable errors.

} zes_mem_health_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory properties
typedef struct _zes_mem_properties_t
{
    zes_mem_type_t type;                            ///< [out] The memory type
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    uint64_t physicalSize;                          ///< [out] Physical memory size in bytes

} zes_mem_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory state - health, allocated
/// 
/// @details
///     - Percent allocation is given by 100 * allocatedSize / maxSize.
///     - Percent free is given by 100 * (maxSize - allocatedSize) / maxSize.
typedef struct _zes_mem_state_t
{
    zes_mem_health_t health;                        ///< [out] Indicates the health of the memory
    uint64_t free;                                  ///< [out] The free memory in bytes
    uint64_t size;                                  ///< [out] The total allocatable memory in bytes (can be less than
                                                    ///< ::zes_mem_properties_t.physicalSize)

} zes_mem_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory bandwidth
/// 
/// @details
///     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
///       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
///       (s2.timestamp - s1.timestamp))
typedef struct _zes_mem_bandwidth_t
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

} zes_mem_bandwidth_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumMemoryModules(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_mem_handle_t* phMemory                      ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesMemoryGetProperties(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
    );

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
__ze_api_export ze_result_t __zecall
zesMemoryGetState(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
    );

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
__ze_api_export ze_result_t __zecall
zesMemoryGetBandwidth(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the current health, free memory, total memory
                                                    ///< size.
    );

#pragma endregion
#pragma region performance
///////////////////////////////////////////////////////////////////////////////
/// @brief Static information about a Performance Factor domain
typedef struct _zes_perf_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if this Performance Factor affects accelerators located on
                                                    ///< a sub-device
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    uint64_t engines;                               ///< [out] Bitfield of accelerator engines that are affected by this
                                                    ///< Performance Factor (bitfield of 1<<::zes_engine_type_t).

} zes_perf_properties_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumPerformanceFactorDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_perf_handle_t* phPerf                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesPerformanceFactorGetProperties(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                    ///< Factor domain.
    );

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
__ze_api_export ze_result_t __zecall
zesPerformanceFactorGetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                    ///< hardware (may not be the same as the requested Performance Factor).
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the performance factor for a domain
/// 
/// @details
///     - The Performance Factor is a number between 0 and 100.
///     - A Performance Factor is a hint to the hardware. Depending on the
///       hardware, the request may not be granted. Follow up this function with
///       a call to ::zesPerformanceFactorGetConfig() to determine the actual
///       factor being used by the hardware.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
__ze_api_export ze_result_t __zecall
zesPerformanceFactorSetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double factor                                   ///< [in] The new Performance Factor.
    );

#pragma endregion
#pragma region power
///////////////////////////////////////////////////////////////////////////////
/// @brief Properties related to device power settings
typedef struct _zes_power_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Software can change the power limits of this domain assuming the
                                                    ///< user has permissions.
    ze_bool_t isEnergyThresholdSupported;           ///< [out] Indicates if this power domain supports the energy threshold
                                                    ///< event (::ZES_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED).
    uint32_t defaultLimit;                          ///< [out] The factory default TDP power limit of the part in milliwatts.
    uint32_t minLimit;                              ///< [out] The minimum power limit in milliwatts that can be requested.
    uint32_t maxLimit;                              ///< [out] The maximum power limit in milliwatts that can be requested.

} zes_power_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy counter snapshot
/// 
/// @details
///     - Average power is calculated by taking two snapshots (s1, s2) and using
///       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
///       s1.timestamp)
typedef struct _zes_power_energy_counter_t
{
    uint64_t energy;                                ///< [out] The monotonic energy counter in microjoules.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when energy was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zes_power_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sustained power limits
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency if
///       the power averaged over a window (typically seconds) exceeds this
///       limit.
typedef struct _zes_power_sustained_limit_t
{
    ze_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts
    uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

} zes_power_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Burst power limit
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency of
///       the device if the power averaged over a few milliseconds exceeds a
///       limit known as PL2. Typically PL2 > PL1 so that it permits the
///       frequency to burst higher for short periods than would be otherwise
///       permitted by PL1.
typedef struct _zes_power_burst_limit_t
{
    ze_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} zes_power_burst_limit_t;

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
typedef struct _zes_power_peak_limit_t
{
    uint32_t powerAC;                               ///< [in,out] power limit in milliwatts for the AC power source.
    uint32_t powerDC;                               ///< [in,out] power limit in milliwatts for the DC power source. This is
                                                    ///< ignored if the product does not have a battery.

} zes_power_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy threshold
/// 
/// @details
///     - .
typedef struct _zes_energy_threshold_t
{
    ze_bool_t enable;                               ///< [in,out] Indicates if the energy threshold is enabled.
    double threshold;                               ///< [in,out] The energy threshold in Joules. Will be 0.0 if no threshold
                                                    ///< has been set.
    uint32_t processId;                             ///< [in,out] The host process ID that set the energy threshold. Will be
                                                    ///< 0xFFFFFFFF if no threshold has been set.

} zes_energy_threshold_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumPowerDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_pwr_handle_t* phPower                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesPowerGetProperties(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    );

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
__ze_api_export ze_result_t __zecall
zesPowerGetEnergyCounter(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    );

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
__ze_api_export ze_result_t __zecall
zesPowerGetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit.
    zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit.
    zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit.
    );

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
__ze_api_export ze_result_t __zecall
zesPowerSetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    );

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
///         + Energy threshold not supported on this power domain (check ::zes_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
__ze_api_export ze_result_t __zecall
zesPowerGetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - An event ::ZES_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED will be generated
///       when the delta energy consumed starting from this call exceeds the
///       specified threshold. Use the function ::zesEventSetConfig() to start
///       receiving the event.
///     - Only one running process can control the energy threshold at a given
///       time. If another process attempts to change the energy threshold, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesPowerGetEnergyThreshold() to determine the process ID currently
///       controlling this setting.
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
///         + Energy threshold not supported on this power domain (check ::zes_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process has set the energy threshold.
__ze_api_export ze_result_t __zecall
zesPowerSetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    );

#pragma endregion
#pragma region psu
///////////////////////////////////////////////////////////////////////////////
/// @brief PSU voltage status
typedef enum _zes_psu_voltage_status_t
{
    ZES_PSU_VOLTAGE_STATUS_NORMAL = 0,              ///< No unusual voltages have been detected
    ZES_PSU_VOLTAGE_STATUS_OVER,                    ///< Over-voltage has occurred
    ZES_PSU_VOLTAGE_STATUS_UNDER,                   ///< Under-voltage has occurred

} zes_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static properties of the power supply
typedef struct _zes_psu_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t haveFan;                              ///< [out] True if the power supply has a fan
    uint32_t ampLimit;                              ///< [out] The maximum electrical current in amperes that can be drawn

} zes_psu_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic state of the power supply
typedef struct _zes_psu_state_t
{
    zes_psu_voltage_status_t voltStatus;            ///< [out] The current PSU voltage status
    ze_bool_t fanFailed;                            ///< [out] Indicates if the fan has failed
    uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees Celsius.
    uint32_t current;                               ///< [out] The amps being drawn in amperes

} zes_psu_state_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumPsus(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_psu_handle_t* phPsu                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesPsuGetProperties(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
    );

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
__ze_api_export ze_result_t __zecall
zesPsuGetState(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
    );

#pragma endregion
#pragma region ras
///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error type
typedef enum _zes_ras_error_type_t
{
    ZES_RAS_ERROR_TYPE_CORRECTABLE = 0,             ///< Errors were corrected by hardware
    ZES_RAS_ERROR_TYPE_UNCORRECTABLE,               ///< Error were not corrected

} zes_ras_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS properties
typedef struct _zes_ras_properties_t
{
    zes_ras_error_type_t type;                      ///< [out] The type of RAS error
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zes_ras_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error details
typedef struct _zes_ras_details_t
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
    uint64_t numDisplayErrors;                      ///< [out] The number of errors that have occurred in the display

} zes_ras_details_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error configuration - thresholds used for triggering RAS events
///        (::ZES_EVENT_TYPE_RAS_CORRECTABLE_ERRORS,
///        ::ZES_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS)
/// 
/// @details
///     - The driver maintains a total counter which is updated every time a
///       hardware block covered by the corresponding RAS error set notifies
///       that an error has occurred. When this total count goes above the
///       totalThreshold specified below, a RAS event is triggered.
///     - The driver also maintains a counter for each category of RAS error
///       (see ::zes_ras_details_t for a breakdown). Each time a hardware block
///       of that category notifies that an error has occurred, that
///       corresponding category counter is updated. When it goes above the
///       threshold specified in detailedThresholds, a RAS event is triggered.
typedef struct _zes_ras_config_t
{
    uint64_t totalThreshold;                        ///< [in,out] If the total RAS errors exceeds this threshold, the event
                                                    ///< will be triggered. A value of 0ULL disables triggering the event based
                                                    ///< on the total counter.
    zes_ras_details_t detailedThresholds;           ///< [in,out] If the RAS errors for each category exceed the threshold for
                                                    ///< that category, the event will be triggered. A value of 0ULL will
                                                    ///< disable an event being triggered for that category.
    uint32_t processId;                             ///< [out] Host processId that set this configuration (ignored when setting
                                                    ///< the configuration).

} zes_ras_config_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumRasErrorSets(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_ras_handle_t* phRas                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesRasGetProperties(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the configured
///       threshold, the event ::ZES_EVENT_TYPE_RAS_CORRECTABLE_ERRORS will be
///       triggered.
///     - When a particular RAS uncorrectable error counter exceeds the
///       configured threshold, the event
///       ::ZES_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be triggered.
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
__ze_api_export ze_result_t __zecall
zesRasGetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                    ///< thresholds used to trigger events
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the specified
///       threshold, the event ::ZES_EVENT_TYPE_RAS_CORRECTABLE_ERRORS will be
///       generated.
///     - When a particular RAS uncorrectable error counter exceeds the
///       specified threshold, the event
///       ::ZES_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be generated.
///     - Call ::zesRasGetState() and set the clear flag to true to restart
///       event generation once counters have exceeded thresholds.
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
__ze_api_export ze_result_t __zecall
zesRasSetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    );

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
__ze_api_export ze_result_t __zecall
zesRasGetState(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in,out] The number total number of errors that have occurred
    zes_ras_details_t* pDetails                     ///< [in,out][optional] Breakdown of where errors have occurred
    );

#pragma endregion
#pragma region scheduler
///////////////////////////////////////////////////////////////////////////////
/// @brief Scheduler mode
typedef enum _zes_sched_mode_t
{
    ZES_SCHED_MODE_TIMEOUT = 0,                     ///< Multiple applications or contexts are submitting work to the hardware.
                                                    ///< When higher priority work arrives, the scheduler attempts to pause the
                                                    ///< current executing work within some timeout interval, then submits the
                                                    ///< other work.
    ZES_SCHED_MODE_TIMESLICE,                       ///< The scheduler attempts to fairly timeslice hardware execution time
                                                    ///< between multiple contexts submitting work to the hardware
                                                    ///< concurrently.
    ZES_SCHED_MODE_EXCLUSIVE,                       ///< Any application or context can run indefinitely on the hardware
                                                    ///< without being preempted or terminated. All pending work for other
                                                    ///< contexts must wait until the running context completes with no further
                                                    ///< submitted work.
    ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG,              ///< Scheduler ensures that submission of workloads to the hardware is
                                                    ///< optimized for compute unit debugging.

} zes_sched_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Properties related to scheduler component
typedef struct _zes_sched_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Software can change the scheduler component configuration
                                                    ///< assuming the user has permissions.
    uint64_t engines;                               ///< [out] Bitfield of accelerator engines that are controlled by this
                                                    ///< scheduler component (bitfield of 1<<::zes_engine_type_t).
    uint32_t supportedModes;                        ///< [out] Bitfield of scheduler modes that can be configured for this
                                                    ///< scheduler component (bitfield of 1<<::zes_sched_mode_t).

} zes_sched_properties_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZES_SCHED_WATCHDOG_DISABLE
/// @brief Disable forward progress guard timeout.
#define ZES_SCHED_WATCHDOG_DISABLE  (~(0ULL))
#endif // ZES_SCHED_WATCHDOG_DISABLE

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for timeout scheduler mode (::ZES_SCHED_MODE_TIMEOUT)
typedef struct _zes_sched_timeout_properties_t
{
    uint64_t watchdogTimeout;                       ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< for a batch of work submitted to a hardware engine to complete or to
                                                    ///< be preempted so as to run another context.
                                                    ///< If this time is exceeded, the hardware engine is reset and the context terminated.
                                                    ///< If set to ::ZES_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                    ///< long as it wants without being terminated, but preemption attempts to
                                                    ///< run other contexts are permitted but not enforced.

} zes_sched_timeout_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for timeslice scheduler mode
///        (::ZES_SCHED_MODE_TIMESLICE)
typedef struct _zes_sched_timeslice_properties_t
{
    uint64_t interval;                              ///< [in,out] The average interval in microseconds that a submission for a
                                                    ///< context will run on a hardware engine before being preempted out to
                                                    ///< run a pending submission for another context.
    uint64_t yieldTimeout;                          ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< to preempt a workload running on an engine before deciding to reset
                                                    ///< the hardware engine and terminating the associated context.

} zes_sched_timeslice_properties_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumSchedulers(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sched_handle_t* phScheduler                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesSchedulerGetProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
    zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    );

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
__ze_api_export ze_result_t __zecall
zesSchedulerGetCurrentMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMEOUT
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
__ze_api_export ze_result_t __zecall
zesSchedulerGetTimeoutModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMESLICE
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
__ze_api_export ze_result_t __zecall
zesSchedulerGetTimesliceModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMEOUT or update scheduler
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
__ze_api_export ze_result_t __zecall
zesSchedulerSetTimeoutMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMESLICE or update
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
__ze_api_export ze_result_t __zecall
zesSchedulerSetTimesliceMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_EXCLUSIVE
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
__ze_api_export ze_result_t __zecall
zesSchedulerSetExclusiveMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG
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
__ze_api_export ze_result_t __zecall
zesSchedulerSetComputeUnitDebugMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    );

#pragma endregion
#pragma region standby
///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware components
typedef enum _zes_standby_type_t
{
    ZES_STANDBY_TYPE_GLOBAL = 0,                    ///< Control the overall standby policy of the device/sub-device

} zes_standby_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware component properties
typedef struct _zes_standby_properties_t
{
    zes_standby_type_t type;                        ///< [out] Which standby hardware component this controls
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zes_standby_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby promotion modes
typedef enum _zes_standby_promo_mode_t
{
    ZES_STANDBY_PROMO_MODE_DEFAULT = 0,             ///< Best compromise between performance and energy savings.
    ZES_STANDBY_PROMO_MODE_NEVER,                   ///< The device/component will never shutdown. This can improve performance
                                                    ///< but uses more energy.

} zes_standby_promo_mode_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumStandbyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_standby_handle_t* phStandby                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesStandbyGetProperties(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
    );

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
__ze_api_export ze_result_t __zecall
zesStandbyGetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
    );

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
__ze_api_export ze_result_t __zecall
zesStandbySetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
    );

#pragma endregion
#pragma region temperature
///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensors
typedef enum _zes_temp_sensors_t
{
    ZES_TEMP_SENSORS_GLOBAL = 0,                    ///< The maximum temperature across all device sensors
    ZES_TEMP_SENSORS_GPU,                           ///< The maximum temperature across all sensors in the GPU
    ZES_TEMP_SENSORS_MEMORY,                        ///< The maximum temperature across all sensors in the local memory

} zes_temp_sensors_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor properties
typedef struct _zes_temp_properties_t
{
    zes_temp_sensors_t type;                        ///< [out] Which part of the device the temperature sensor measures
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t isCriticalTempSupported;              ///< [out] Indicates if the critical temperature event
                                                    ///< ::ZES_EVENT_TYPE_TEMP_CRITICAL is supported
    ze_bool_t isThreshold1Supported;                ///< [out] Indicates if the temperature threshold 1 event
                                                    ///< ::ZES_EVENT_TYPE_TEMP_THRESHOLD1 is supported
    ze_bool_t isThreshold2Supported;                ///< [out] Indicates if the temperature threshold 2 event
                                                    ///< ::ZES_EVENT_TYPE_TEMP_THRESHOLD2 is supported

} zes_temp_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor threshold
typedef struct _zes_temp_threshold_t
{
    ze_bool_t enableLowToHigh;                      ///< [in,out] Trigger an event when the temperature crosses from below the
                                                    ///< threshold to above.
    ze_bool_t enableHighToLow;                      ///< [in,out] Trigger an event when the temperature crosses from above the
                                                    ///< threshold to below.
    double threshold;                               ///< [in,out] The threshold in degrees Celsius.

} zes_temp_threshold_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature configuration - which events should be triggered and the
///        trigger conditions.
typedef struct _zes_temp_config_t
{
    ze_bool_t enableCritical;                       ///< [in,out] Indicates if event ::ZES_EVENT_TYPE_TEMP_CRITICAL should be
                                                    ///< triggered by the driver.
    zes_temp_threshold_t threshold1;                ///< [in,out] Configuration controlling if and when event
                                                    ///< ::ZES_EVENT_TYPE_TEMP_THRESHOLD1 should be triggered by the driver.
    zes_temp_threshold_t threshold2;                ///< [in,out] Configuration controlling if and when event
                                                    ///< ::ZES_EVENT_TYPE_TEMP_THRESHOLD2 should be triggered by the driver.
    uint32_t processId;                             ///< [out] Host processId that set this configuration (ignored when setting
                                                    ///< the configuration).

} zes_temp_config_t;

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
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zesDeviceEnumTemperatureSensors(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_temp_handle_t* phTemperature                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

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
__ze_api_export ze_result_t __zecall
zesTemperatureGetProperties(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
    );

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
///         + Temperature thresholds are not supported on this temperature sensor. Generally this is only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL
///         + One or both of the thresholds is not supported - check ::zes_temp_properties_t.isThreshold1Supported and ::zes_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
__ze_api_export ze_result_t __zecall
zesTemperatureGetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature configuration for this sensor - indicates which events
///        are triggered and the trigger conditions
/// 
/// @details
///     - Events ::ZES_EVENT_TYPE_TEMP_CRITICAL will be triggered when
///       temperature reaches the critical range. Use the function
///       ::zesEventSetConfig() to start receiving this event.
///     - Events ::ZES_EVENT_TYPE_TEMP_THRESHOLD1 and
///       ::ZES_EVENT_TYPE_TEMP_THRESHOLD2 will be generated when temperature
///       cross the thresholds set using this function. Use the function
///       ::zesEventSetConfig() to start receiving these events.
///     - Only one running process can set the temperature configuration at a
///       time. If another process attempts to change the configuration, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesTemperatureGetConfig() will return the process ID currently
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
///         + Temperature thresholds are not supported on this temperature sensor. Generally they are only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL
///         + Enabling the critical temperature event is not supported - check ::zes_temp_properties_t.isCriticalTempSupported
///         + One or both of the thresholds is not supported - check ::zes_temp_properties_t.isThreshold1Supported and ::zes_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or both the thresholds is above TjMax (see ::zesFrequencyOcGetTjMax()). Temperature thresholds must be below this value.
__ze_api_export ze_result_t __zecall
zesTemperatureSetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    const zes_temp_config_t* pConfig                ///< [in] New configuration.
    );

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
__ze_api_export ze_result_t __zecall
zesTemperatureGetState(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                    ///< in degrees Celsius.
    );

#pragma endregion

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZES_API_H