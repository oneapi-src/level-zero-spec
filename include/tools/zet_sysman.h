/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_sysman.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#ifndef _ZET_SYSMAN_H
#define _ZET_SYSMAN_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of SMI
typedef enum _zet_sysman_version_t
{
    ZET_SYSMAN_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} zet_sysman_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the handle to access SMI features for a device
/// 
/// @details
///     - The returned handle is unique
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == phSysman
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanGet(
    zet_device_handle_t hDevice,                    ///< [in] Handle of the device
    zet_sysman_version_t version,                   ///< [in] SMI version that application was built with
    zet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define ZET_STRING_PROPERTY_SIZE  32
#endif // ZET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Data Type
typedef enum _zet_data_type_t
{
    ZET_DATA_INT8 = 0,                              ///< 8 bit signed integer.
    ZET_DATA_INT16,                                 ///< 16 bit signed integer.
    ZET_DATA_INT32,                                 ///< 32 bit signed integer.
    ZET_DATA_INT64,                                 ///< 64 bit signed integer.
    ZET_DATA_UINT8,                                 ///< 8 bit unsigned integer.
    ZET_DATA_UINT16,                                ///< 16 bit unsigned integer.
    ZET_DATA_UINT32,                                ///< 32 bit unsigned integer.
    ZET_DATA_UINT64,                                ///< 64 bit unsigned integer.
    ZET_DATA_FLOAT,                                 ///< Single precision floating point.
    ZET_DATA_DOUBLE,                                ///< Double precision floating point.
    ZET_DATA_STRING,                                ///< Null terminated Strings.

} zet_data_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Operation Type
typedef enum _zet_operation_type_t
{
    ZET_OPERATION_TYPE_SET = 0,                     ///< This enum represent a Set Type Operation.
    ZET_OPERATION_TYPE_GET,                         ///< This enum represent a Get Type Operation.
    ZET_OPERATION_TYPE_REGISTER_EVENT,              ///< This enum used to register an event.

} zet_operation_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Domains for Power and Frequency.
typedef enum _zet_domain_t
{
    ZET_DOMAIN_GPU = 0,                             ///< GPU Core Domain.
    ZET_DOMAIN_MEMORY,                              ///< Local Memory Domain.

} zet_domain_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device Type
typedef enum _zet_device_type_t
{
    ZET_DEVICE_TYPE_INTEGRATED = 0,                 ///< The device is an integrated GPU
    ZET_DEVICE_TYPE_DISCRETE,                       ///< The device is a discrete GPU

} zet_device_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties
typedef struct _zet_sysman_properties_t
{
    ze_device_properties_t core;                    ///< [out] Core device properties
    uint32_t numSubdevices;                         ///< [out] Number of sub-devices
    zet_device_type_t deviceType;                   ///< [out] Device type
    int8_t serialNumber[ZET_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
    int8_t boardNumber[ZET_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
    int8_t brandName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
    int8_t modelName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
    int8_t vendorName[ZET_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
    int8_t driverVersion[ZET_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)

} zet_sysman_properties_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanDeviceGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Scheduler mode
typedef enum _zet_sched_mode_t
{
    ZET_SCHED_MODE_TIMEOUT = 0,                     ///< Multiple applications or contexts are submitting work to the hardware.
                                                    ///< When higher priority work arrives, the scheduler attempts to pause the
                                                    ///< current executing work within some timeout interval, then submits the
                                                    ///< other work.
    ZET_SCHED_MODE_TIMESLICE,                       ///< The scheduler attempts to fairly timeslice hardware execution time
                                                    ///< between multiple contexts submitting work to the hardware
                                                    ///< concurrently.
    ZET_SCHED_MODE_EXCLUSIVE,                       ///< Any application or context can run indefinitely on the hardware
                                                    ///< without being preempted or terminated. All pending work for other
                                                    ///< contexts must wait until the running context completes with no further
                                                    ///< submitted work.
    ZET_SCHED_MODE_COMPUTE_UNIT_DEBUG,              ///< Scheduler ensures that submission of workloads to the hardware is
                                                    ///< optimized for compute unit debugging.

} zet_sched_mode_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_SCHED_WATCHDOG_DISABLE
/// @brief Disable forward progress guard timeout.
#define ZET_SCHED_WATCHDOG_DISABLE  (~(0ULL))
#endif // ZET_SCHED_WATCHDOG_DISABLE

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for timeout scheduler mode (::ZET_SCHED_MODE_TIMEOUT)
typedef struct _zet_sched_timeout_properties_t
{
    uint64_t watchdogTimeout;                       ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< for a batch of work submitted to a hardware engine to complete or to
                                                    ///< be preempted so as to run another context.
                                                    ///< If this time is exceeded, the hardware engine is reset and the context terminated.
                                                    ///< If set to ::ZET_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                    ///< long as it wants without being terminated, but preemption attempts to
                                                    ///< run other contexts are permitted but not enforced.

} zet_sched_timeout_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for timeslice scheduler mode
///        (::ZET_SCHED_MODE_TIMESLICE)
typedef struct _zet_sched_timeslice_properties_t
{
    uint64_t interval;                              ///< [in,out] The average interval in microseconds that a submission for a
                                                    ///< context will run on a hardware engine before being preempted out to
                                                    ///< run a pending submission for another context.
    uint64_t yieldTimeout;                          ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< to preempt a workload running on an engine before deciding to reset
                                                    ///< the hardware engine and terminating the associated context.

} zet_sched_timeslice_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduler mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pMode
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + Device does not support scheduler modes.
ze_result_t __zecall
zetSysmanSchedulerGetCurrentMode(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
    );

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::zetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
ze_result_t __zecall
zetSysmanSchedulerGetTimeoutModeProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeout_properties_t* pConfig         ///< [in] Will contain the current parameters for this mode.
    );

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::zetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
ze_result_t __zecall
zetSysmanSchedulerGetTimesliceModeProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeslice_properties_t* pConfig       ///< [in] Will contain the current parameters for this mode.
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///         + nullptr == pNeedReboot
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::zetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
ze_result_t __zecall
zetSysmanSchedulerSetTimeoutMode(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///         + nullptr == pNeedReboot
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::zetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
ze_result_t __zecall
zetSysmanSchedulerSetTimesliceMode(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pNeedReboot
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::zetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
ze_result_t __zecall
zetSysmanSchedulerSetExclusiveMode(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pNeedReboot
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::zetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
ze_result_t __zecall
zetSysmanSchedulerSetComputeUnitDebugMode(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanDeviceReset(
    zet_sysman_handle_t hSysman                     ///< [in] SMI handle for the device
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out if the device has been repaired (either by the manufacturer
///        or by running diagnostics)
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pWasRepaired
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This device does not record this information or does not support repair features.
ze_result_t __zecall
zetSysmanDeviceWasRepaired(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    ze_bool_t* pWasRepaired                         ///< [in] Will indicate if the device was repaired
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI address
typedef struct _zet_pci_address_t
{
    uint32_t domain;                                ///< [out] BDF domain
    uint32_t bus;                                   ///< [out] BDF bus
    uint32_t device;                                ///< [out] BDF device
    uint32_t function;                              ///< [out] BDF function

} zet_pci_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI speed
typedef struct _zet_pci_speed_t
{
    uint32_t gen;                                   ///< [out] The link generation
    uint32_t width;                                 ///< [out] The number of lanes
    uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec
    uint32_t maxPacketSize;                         ///< [out] Maximum packet size in bytes.

} zet_pci_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static PCI properties
typedef struct _zet_pci_properties_t
{
    zet_pci_address_t address;                      ///< [out] The BDF address
    uint32_t numBars;                               ///< [out] The number of configured bars
    zet_pci_speed_t maxSpeed;                       ///< [out] Fastest port configuration supported by the device.

} zet_pci_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic PCI state
typedef struct _zet_pci_state_t
{
    zet_pci_speed_t speed;                          ///< [out] The current port configure speed

} zet_pci_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI bar types
typedef enum _zet_pci_bar_type_t
{
    ZET_PCI_BAR_TYPE_CONFIG = 0,                    ///< PCI configuration space
    ZET_PCI_BAR_TYPE_MMIO,                          ///< MMIO registers
    ZET_PCI_BAR_TYPE_VRAM,                          ///< VRAM aperture
    ZET_PCI_BAR_TYPE_ROM,                           ///< ROM aperture
    ZET_PCI_BAR_TYPE_VGA_IO,                        ///< Legacy VGA IO ports
    ZET_PCI_BAR_TYPE_VGA_MEM,                       ///< Legacy VGA memory
    ZET_PCI_BAR_TYPE_INDIRECT_IO,                   ///< Indirect IO port access
    ZET_PCI_BAR_TYPE_INDIRECT_MEM,                  ///< Indirect memory access
    ZET_PCI_BAR_TYPE_OTHER,                         ///< Other type of PCI bar

} zet_pci_bar_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Properties of a pci bar
typedef struct _zet_pci_bar_properties_t
{
    zet_pci_bar_type_t type;                        ///< [out] The type of bar
    uint64_t base;                                  ///< [out] Base address of the bar.
    uint64_t size;                                  ///< [out] Size of the bar.

} zet_pci_bar_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI throughput
/// 
/// @details
///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
///       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
///       s1.timestamp))
typedef struct _zet_pci_throughput_t
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
    uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec under the current
                                                    ///< configuration

} zet_pci_throughput_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI stats counters
/// 
/// @details
///     - Percent replays is calculated by taking two snapshots (s1, s2) and
///       using the equation: %replay = 10^6 * (s2.replayCounter -
///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _zet_pci_stats_t
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

} zet_pci_stats_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPciGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPciGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a bar
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPciGetBarProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::zet_pci_properties_t.numBars -
                                                    ///< 1]).
    zet_pci_bar_properties_t* pProperties           ///< [in] Will contain properties of the specified bar
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI throughput
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pThroughput
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPciGetThroughput(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_pci_throughput_t* pThroughput               ///< [in] Will contain a snapshot of the latest throughput counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pStats
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPciGetStats(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    zet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Properties related to device power settings
typedef struct _zet_power_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Software can change the power limits.
    uint32_t maxLimit;                              ///< [out] The maximum power limit in milliwatts that can be requested.

} zet_power_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy counter snapshot
/// 
/// @details
///     - Average power is calculated by taking two snapshots (s1, s2) and using
///       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
///       s1.timestamp)
typedef struct _zet_power_energy_counter_t
{
    uint64_t energy;                                ///< [out] The monotonic energy counter in microjoules.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when energy was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zet_power_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy threshold
/// 
/// @details
///     - Energy threshold value, when this value is crossed, pcu will signal an
///       interrupt.
typedef struct _zet_power_energy_threshold_t
{
    uint32_t energy;                                ///< [in,out] The energy threshold in joules.

} zet_power_energy_threshold_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sustained power limits
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency if
///       the power averaged over a window (typically seconds) exceeds this
///       limit.
typedef struct _zet_power_sustained_limit_t
{
    ze_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts
    uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

} zet_power_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Burst power limit
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency of
///       the device if the power averaged over a few milliseconds exceeds a
///       limit known as PL2. Typically PL2 > PL1 so that it permits the
///       frequency to burst higher for short periods than would be otherwise
///       permitted by PL1.
typedef struct _zet_power_burst_limit_t
{
    ze_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} zet_power_burst_limit_t;

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
typedef struct _zet_power_peak_limit_t
{
    uint32_t powerAC;                               ///< [in,out] power limit in milliwatts for the AC power source.
    uint32_t powerDC;                               ///< [in,out] power limit in milliwatts for the DC power source. This is
                                                    ///< ignored if the product does not have a battery.

} zet_power_peak_limit_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPowerGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPowerGetProperties(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pEnergy
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPowerGetEnergyCounter(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pThreshold
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPowerGetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_energy_threshold_t* pThreshold        ///< [in] The current energy threshold value in joules.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pThreshold
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_ERROR_DEVICE_IS_IN_USE
///         + The device is in use, meaning that the GPU is under Over clocking, applying energy threshold under overclocking is not supported.
ze_result_t __zecall
zetSysmanPowerSetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_energy_threshold_t* pThreshold        ///< [in] The energy threshold to be set in joules.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPowerGetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
    zet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
    zet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_ERROR_DEVICE_IS_IN_USE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t __zecall
zetSysmanPowerSetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    const zet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const zet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const zet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking modes
typedef enum _zet_oc_mode_t
{
    ZET_OVERCLOCKING_INTERPOLATIVE_MODE = 0,        ///< Interpolative Mode.
    ZET_OVERCLOCKING_OVERRIDE_MODE = 1,             ///< Override Mode.

} zet_oc_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Over clocking error type
typedef enum _zet_oc_error_type_t
{
    ZET_OVERCLOCKING_LOCKED = 225,                  ///< The overclocking is locked. Service is read-only.
    ZET_OVERCLOCKING_DDOMAIN_SERVICE_NOT_SUPPORTED, ///< The specified domain does not support the requested service.
    ZET_OVERCLOCKING_RATIO_EXCEEDS_MAX,             ///< The ratio exceeds maximum overclocking limits.
    ZET_OVERCLOCKING_VOLTAGE_EXCEEDS_MAX,           ///< Requested voltage exceeds input regulators max supported voltage.
    ZET_OVERCLOCKING_NOT_SUPPORTED,                 ///< No overclocking capability on the Hardware.
    ZET_OVERCLOCKING_INVALID_VR_ADDRESS,            ///< The VR Address provided is illegal.
    ZET_OOVERCLOCKING_INVALID_ICCMAX,               ///< ICCMAX value given is invalid (more than 10 bits) or too low.
    ZET_OVERCLOCKING_VOLTAGE_OVERRIDE_DISABLED,     ///< Voltage manipulation attempted when it is disabled.
    ZET_OVERCLOCKING_INVALID_COMMAND,               ///< Data setting invalid for the command.

} zet_oc_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking properties
/// 
/// @details
///     - Provides all the overclocking capabilities and properties supported by
///       the device in the current domain.
typedef struct _zet_oc_capabilities_t
{
    double MaxOcFrequencyLimit;                     ///< [out] Max overclocking frequency limit in Mhz.
    double MaxFactoryDefaultFrequency;              ///< [out] Maximum factory default frequency in Mhz.
    double MaxFactoryDefaultVoltage;                ///< [out] Maximum factory default voltage in Votls.
    ze_bool_t TjMaxSupported;                       ///< [out] is the TjMax supported on this domain.
    ze_bool_t IccMaxSupported;                      ///< [out] is the Icc supported on this domain.
    ze_bool_t FrequencyOcSupported;                 ///< [out] Frequency overclocking supported
    ze_bool_t VoltageOverrideSupported;             ///< [out] Voltage overrides supported
    ze_bool_t VoltageOffsetSupported;               ///< [out] Voltage offset is supported
    ze_bool_t HighVoltModeCapable;                  ///< [out] Capable of high voltage mode
    ze_bool_t HighVoltModeEnabled;                  ///< [out] High voltage mode is enabled

} zet_oc_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking configuration
/// 
/// @details
///     - Provide the current settings to be read or changed.
typedef struct _zet_oc_configuration_t
{
    double OcFrequency;                             ///< [in,out] Overclocking Frequency
    double TargetVoltage;                           ///< [in,out] Target voltage in Volts
    zet_oc_mode_t TargetMode;                       ///< [in,out] Overclock Mode ::zet_oc_mode_t.
    double VoltageOffset;                           ///< [in,out] Voltage offset in Volts.

} zet_oc_configuration_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the last overclock error
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcError
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetLastOcError(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_error_type_t* pOcError                   ///< [in] Error in ::zet_oc_error_type_t .
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcCapabilities
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetOcCapabilities(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_capabilities_t* pOcCapabilities          ///< [in] Pointer to the capabilities structure ::zet_oc_capabilities_t.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking configuration.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcConfiguration
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetOcConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_configuration_t* pOcConfiguration        ///< [in] Pointer to the configuration structure ::zet_oc_configuration_t.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the overclocking configuration.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcConfiguration
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencySetOcConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_configuration_t* pOcConfiguration        ///< [in] Pointer to the configuration structure ::zet_oc_configuration_t.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Maximum desired current.
/// 
/// @details
///     - For overclock-able parts this holds the maximum desired current if the
///       domains supports it.
typedef struct _zet_oc_icc_max_t
{
    double IccMax;                                  ///< [in,out] Maximum desired current in Amperes

} zet_oc_icc_max_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature Junction Maximum.
/// 
/// @details
///     - For overclock-able parts this holds the maximum temperature limit at
///       which the part will throttle if the domains supports it.
typedef struct _zet_oc_tj_max_t
{
    double TjMax;                                   ///< [in,out] Maximum desired current in degrees celcius.

} zet_oc_tj_max_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the Icc Max.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcIccMax
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetOcIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_icc_max_t* pOcIccMax                     ///< [in] Pointer to the Icc Max.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the Icc Max.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcIccMax
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencySetOcIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_icc_max_t* pOcIccMax                     ///< [in] Pointer to the Icc Max.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the TjMax.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcTjMax
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetOcTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_tj_max_t* pOcTjMax                       ///< [in] Pointer to the TjMax.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the TjMax.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pOcTjMax
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencySetOcTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_tj_max_t* pOcTjMax                       ///< [in] Pointer to the TjMax.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency properties
/// 
/// @details
///     - Provides the set of frequencies as a list and as a range/step.
///     - It is generally recommended that applications choose frequencies from
///       the list. However applications can also construct the list themselves
///       using the range/steps provided.
typedef struct _zet_freq_properties_t
{
    zet_domain_t type;                              ///< [out] The type of frequency domain (GPU, memory, ...)
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the frequency of this domain
    ze_bool_t canOverclock;                         ///< [out] Indicates if software can overclock this frequency domain
    double min;                                     ///< [out] The minimum clock frequency in units of MHz
    double max;                                     ///< [out] The maximum clock frequency in units of MHz
    double step;                                    ///< [out] The step clock frequency in units of MHz
    uint32_t num;                                   ///< [out] The number of clocks in the array pClocks
    const double* pClocks;                          ///< [out] Array of clock frequencies in units of MHz ordered from smallest
                                                    ///< to largest.

} zet_freq_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency range between which the hardware can operate.
typedef struct _zet_freq_range_t
{
    double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.
    double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.

} zet_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle reasons
typedef enum _zet_freq_throttle_reasons_t
{
    ZET_FREQ_THROTTLE_REASONS_NONE = 0,             ///< frequency not throttled
    ZET_FREQ_THROTTLE_REASONS_AVE_PWR_CAP = ZE_BIT( 0 ),///< frequency throttled due to average power excursion (PL1)
    ZET_FREQ_THROTTLE_REASONS_BURST_PWR_CAP = ZE_BIT( 1 ),  ///< frequency throttled due to burst power excursion (PL2)
    ZET_FREQ_THROTTLE_REASONS_CURRENT_LIMIT = ZE_BIT( 2 ),  ///< frequency throttled due to current excursion (PL4)
    ZET_FREQ_THROTTLE_REASONS_THERMAL_LIMIT = ZE_BIT( 3 ),  ///< frequency throttled due to thermal excursion (T > TjMax)
    ZET_FREQ_THROTTLE_REASONS_PSU_ALERT = ZE_BIT( 4 ),  ///< frequency throttled due to power supply assertion
    ZET_FREQ_THROTTLE_REASONS_SW_RANGE = ZE_BIT( 5 ),   ///< frequency throttled due to software supplied frequency range
    ZET_FREQ_THROTTLE_REASONS_HW_RANGE = ZE_BIT( 6 ),   ///< frequency throttled due to a sub block that has a lower frequency
                                                    ///< range when it receives clocks

} zet_freq_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency state
typedef struct _zet_freq_state_t
{
    double request;                                 ///< [out] The current frequency request in MHz.
    double tdp;                                     ///< [out] The maximum frequency in MHz supported under the current TDP
                                                    ///< conditions
    double efficient;                               ///< [out] The efficient minimum frequency in MHz
    double actual;                                  ///< [out] The resolved frequency in MHz
    uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the hardware
                                                    ///< (Bitfield of (1<<::zet_freq_throttle_reasons_t)).

} zet_freq_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle time snapshot
/// 
/// @details
///     - Percent time throttled is calculated by taking two snapshots (s1, s2)
///       and using the equation: %throttled = (s2.throttleTime -
///       s1.throttleTime) / (s2.timestamp - s1.timestamp)
typedef struct _zet_freq_throttle_time_t
{
    uint64_t throttleTime;                          ///< [out] The monotonic counter of time in microseconds that the frequency
                                                    ///< has been limited by the hardware.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when throttleTime was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zet_freq_throttle_time_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetProperties(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pLimits
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_range_t* pLimits                       ///< [in] The range between which the hardware can operate for the
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pLimits
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencySetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    const zet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetState(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pThrottleTime
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFrequencyGetThrottleTime(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator engine groups
typedef enum _zet_engine_group_t
{
    ZET_ENGINE_GROUP_ALL = 0,                       ///< Access information about all engines combined.
    ZET_ENGINE_GROUP_COMPUTE_ALL,                   ///< Access information about all compute engines combined.
    ZET_ENGINE_GROUP_MEDIA_ALL,                     ///< Access information about all media engines combined.
    ZET_ENGINE_GROUP_COPY_ALL,                      ///< Access information about all copy (blitter) engines combined.

} zet_engine_group_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine group properties
typedef struct _zet_engine_properties_t
{
    zet_engine_group_t type;                        ///< [out] The engine group
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zet_engine_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine activity counters
/// 
/// @details
///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
///       using the equation: %util = (s2.activeTime - s1.activeTime) /
///       (s2.timestamp - s1.timestamp)
typedef struct _zet_engine_stats_t
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

} zet_engine_stats_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanEngineGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEngine
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanEngineGetProperties(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEngine
///         + nullptr == pStats
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanEngineGetActivity(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware components
typedef enum _zet_standby_type_t
{
    ZET_STANDBY_TYPE_GLOBAL = 0,                    ///< Control the overall standby policy of the device/sub-device

} zet_standby_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware component properties
typedef struct _zet_standby_properties_t
{
    zet_standby_type_t type;                        ///< [out] Which standby hardware component this controls
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zet_standby_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby promotion modes
typedef enum _zet_standby_promo_mode_t
{
    ZET_STANDBY_PROMO_MODE_DEFAULT = 0,             ///< Best compromise between performance and energy savings.
    ZET_STANDBY_PROMO_MODE_NEVER,                   ///< The device/component will never shutdown. This can improve performance
                                                    ///< but uses more energy.

} zet_standby_promo_mode_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanStandbyGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hStandby
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanStandbyGetProperties(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hStandby
///         + nullptr == pMode
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanStandbyGetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hStandby
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanStandbySetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Firmware properties
typedef struct _zet_firmware_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can flash the firmware
    int8_t name[ZET_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
    int8_t version[ZET_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

} zet_firmware_properties_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFirmwareGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFirmware
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFirmwareGetProperties(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    zet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFirmware
///         + nullptr == pChecksum
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFirmwareGetChecksum(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFirmware
///         + nullptr == pImage
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFirmwareFlash(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory module types
typedef enum _zet_mem_type_t
{
    ZET_MEM_TYPE_HBM = 0,                           ///< HBM memory
    ZET_MEM_TYPE_DDR,                               ///< DDR memory
    ZET_MEM_TYPE_SRAM,                              ///< SRAM memory
    ZET_MEM_TYPE_L1,                                ///< L1 cache
    ZET_MEM_TYPE_L3,                                ///< L3 cache
    ZET_MEM_TYPE_GRF,                               ///< Execution unit register file
    ZET_MEM_TYPE_SLM,                               ///< Execution unit shared local memory

} zet_mem_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory health
typedef enum _zet_mem_health_t
{
    ZET_MEM_HEALTH_OK = 0,                          ///< All memory channels are healthy
    ZET_MEM_HEALTH_DEGRADED,                        ///< Excessive correctable errors have been detected on one or more
                                                    ///< channels. Device should be reset.
    ZET_MEM_HEALTH_CRITICAL,                        ///< Operating with reduced memory to cover banks with too many
                                                    ///< uncorrectable errors.
    ZET_MEM_HEALTH_REPLACE,                         ///< Device should be replaced due to excessive uncorrectable errors.

} zet_mem_health_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory properties
typedef struct _zet_mem_properties_t
{
    zet_mem_type_t type;                            ///< [out] The memory type
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    uint64_t physicalSize;                          ///< [out] Physical memory size in bytes

} zet_mem_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory state - health, allocated
/// 
/// @details
///     - Percent allocation is given by 100 * allocatedSize / maxSize.
///     - Percent free is given by 100 * (maxSize - allocatedSize) / maxSize.
typedef struct _zet_mem_state_t
{
    zet_mem_health_t health;                        ///< [out] Indicates the health of the memory
    uint64_t allocatedSize;                         ///< [out] The total allocated bytes
    uint64_t maxSize;                               ///< [out] The total allocatable memory in bytes (can be less than
                                                    ///< ::zet_mem_properties_t.physicalSize)

} zet_mem_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory bandwidth
/// 
/// @details
///     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
///       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
///       (s2.timestamp - s1.timestamp))
typedef struct _zet_mem_bandwidth_t
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

} zet_mem_bandwidth_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanMemoryGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMemory
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanMemoryGetProperties(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMemory
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanMemoryGetState(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_state_t* pState                         ///< [in] Will contain the current health and allocated memory.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMemory
///         + nullptr == pBandwidth
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanMemoryGetBandwidth(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_FABRIC_PORT_MODEL_SIZE
/// @brief Maximum Fabric port model string size
#define ZET_MAX_FABRIC_PORT_MODEL_SIZE  256
#endif // ZET_MAX_FABRIC_PORT_MODEL_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_FABRIC_PORT_UUID_SIZE
/// @brief Maximum fabric port uuid size in bytes
#define ZET_MAX_FABRIC_PORT_UUID_SIZE  72
#endif // ZET_MAX_FABRIC_PORT_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_FABRIC_LINK_TYPE_SIZE
/// @brief Maximum size of the buffer that will return information about link
///        types
#define ZET_MAX_FABRIC_LINK_TYPE_SIZE  256
#endif // ZET_MAX_FABRIC_LINK_TYPE_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port status
typedef enum _zet_fabric_port_status_t
{
    ZET_FABRIC_PORT_STATUS_GREEN = 0,               ///< The port is up and operating as expected
    ZET_FABRIC_PORT_STATUS_YELLOW,                  ///< The port is up but has quality and/or bandwidth degradation
    ZET_FABRIC_PORT_STATUS_RED,                     ///< Port connection instabilities are preventing workloads making forward
                                                    ///< progress
    ZET_FABRIC_PORT_STATUS_BLACK,                   ///< The port is configured down

} zet_fabric_port_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port quality degradation reasons
typedef enum _zet_fabric_port_qual_issues_t
{
    ZET_FABRIC_PORT_QUAL_ISSUES_NONE = 0,           ///< There are no quality issues with the link at this time
    ZET_FABRIC_PORT_QUAL_ISSUES_FEC = ZE_BIT( 0 ),  ///< Excessive FEC (forward error correction) are occurring
    ZET_FABRIC_PORT_QUAL_ISSUES_LTP_CRC = ZE_BIT( 1 ),  ///< Excessive LTP CRC failure induced replays are occurring
    ZET_FABRIC_PORT_QUAL_ISSUES_SPEED = ZE_BIT( 2 ),///< There is a degradation in the maximum bandwidth of the port

} zet_fabric_port_qual_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port stability issues
typedef enum _zet_fabric_port_stab_issues_t
{
    ZET_FABRIC_PORT_STAB_ISSUES_NONE = 0,           ///< There are no connection stability issues at this time
    ZET_FABRIC_PORT_STAB_ISSUES_TOO_MANY_REPLAYS = ZE_BIT( 0 ), ///< Sequential replay failure is inducing link retraining
    ZET_FABRIC_PORT_STAB_ISSUES_NO_CONNECT = ZE_BIT( 1 ),   ///< A connection was never able to be established through the link
    ZET_FABRIC_PORT_STAB_ISSUES_FLAPPING = ZE_BIT( 2 ), ///< The port is flapping

} zet_fabric_port_stab_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port universal unique id (UUID)
typedef struct _zet_fabric_port_uuid_t
{
    uint8_t id[ZET_MAX_FABRIC_PORT_UUID_SIZE];      ///< [out] Frabric port universal unique id

} zet_fabric_port_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port speed in one direction
typedef struct _zet_fabric_port_speed_t
{
    uint64_t bitRate;                               ///< [out] Bits/sec that the link is operating at
    uint32_t width;                                 ///< [out] The number of lanes
    uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

} zet_fabric_port_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port properties
typedef struct _zet_fabric_port_properties_t
{
    int8_t model[ZET_MAX_FABRIC_PORT_MODEL_SIZE];   ///< [out] Description of port technology
    ze_bool_t onSubdevice;                          ///< [out] True if the port is located on a sub-device; false means that
                                                    ///< the port is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    zet_fabric_port_uuid_t portUuid;                ///< [out] The port universal unique id
    zet_fabric_port_speed_t maxRxSpeed;             ///< [out] Maximum bandwidth supported by the receive side of the port
    zet_fabric_port_speed_t maxTxSpeed;             ///< [out] Maximum bandwidth supported by the transmit side of the port

} zet_fabric_port_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides information about the fabric link attached to a port
typedef struct _zet_fabric_link_type_t
{
    int8_t desc[ZET_MAX_FABRIC_LINK_TYPE_SIZE];     ///< [out] This provides a textural description of a link attached to a
                                                    ///< port. It contains the following information:
                                                    ///< - Link material
                                                    ///< - Link technology
                                                    ///< - Cable manufacturer
                                                    ///< - Temperature
                                                    ///< - Power
                                                    ///< - Attachment type:
                                                    ///<    - Disconnected
                                                    ///<    - Hardwired/fixed/etched connector
                                                    ///<    - Active copper
                                                    ///<    - QSOP
                                                    ///<    - AOC

} zet_fabric_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port configuration
typedef struct _zet_fabric_port_config_t
{
    ze_bool_t enabled;                              ///< [in,out] Port is configured up/down
    ze_bool_t beaconing;                            ///< [in,out] Beaconing is configured on/off

} zet_fabric_port_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port state
typedef struct _zet_fabric_port_state_t
{
    zet_fabric_port_status_t status;                ///< [out] The current status of the port
    zet_fabric_port_qual_issues_t qualityIssues;    ///< [out] If status is ::ZET_FABRIC_PORT_STATUS_YELLOW, this gives a
                                                    ///< bitfield of quality issues that have been detected
    zet_fabric_port_stab_issues_t stabilityIssues;  ///< [out] If status is ::ZET_FABRIC_PORT_STATUS_RED, this gives a bitfield
                                                    ///< of reasons for the connection instability
    zet_fabric_port_speed_t rxSpeed;                ///< [out] Current maximum receive speed
    zet_fabric_port_speed_t txSpeed;                ///< [out] Current maximum transmit speed

} zet_fabric_port_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port throughput
/// 
/// @details
///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
///       using the equation:
///     -     %rx_bandwidth = 10^6 * (s2.rxCounter - s1.rxCounter) /
///       (s2.rxMaxBandwidth * (s2.timestamp - s1.timestamp))
///     -     %tx_bandwidth = 10^6 * (s2.txCounter - s1.txCounter) /
///       (s2.txMaxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _zet_fabric_port_throughput_t
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
    uint64_t rxMaxBandwidth;                        ///< [out] The current maximum bandwidth in bytes/sec for receiving packats
    uint64_t txMaxBandwidth;                        ///< [out] The current maximum bandwidth in bytes/sec for transmitting
                                                    ///< packets

} zet_fabric_port_throughput_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFabricPortGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_fabric_port_handle_t* phPort         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPort
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFabricPortGetProperties(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_properties_t* pProperties       ///< [in] Will contain properties of the Fabric Port.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPort
///         + nullptr == pLinkType
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFabricPortGetLinkType(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
    zet_fabric_link_type_t* pLinkType               ///< [in] Will contain details about the link attached to the Fabric port.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPort
///         + nullptr == pConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFabricPortGetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_config_t* pConfig               ///< [in] Will contain configuration of the Fabric Port.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPort
///         + nullptr == pConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFabricPortSetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_config_t* pConfig               ///< [in] Contains new configuration of the Fabric Port.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPort
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFabricPortGetState(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_state_t* pState                 ///< [in] Will contain the current state of the Fabric Port
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPort
///         + nullptr == pThroughput
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFabricPortGetThroughput(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_throughput_t* pThroughput       ///< [in] Will contain the Fabric port throughput counters and maximum
                                                    ///< bandwidth.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensors
typedef enum _zet_temp_sensors_t
{
    ZET_TEMP_SENSORS_GLOBAL = 0,                    ///< The maximum temperature across all device sensors
    ZET_TEMP_SENSORS_GPU,                           ///< The maximum temperature across all sensors in the GPU
    ZET_TEMP_SENSORS_MEMORY,                        ///< The maximum temperature across all sensors in the local memory

} zet_temp_sensors_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor properties
typedef struct _zet_temp_properties_t
{
    zet_temp_sensors_t type;                        ///< [out] Which part of the device the temperature sensor measures
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zet_temp_properties_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanTemperatureGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTemperature
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanTemperatureGetProperties(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTemperature
///         + nullptr == pTemperature
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanTemperatureRead(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PSU voltage status
typedef enum _zet_psu_voltage_status_t
{
    ZET_PSU_VOLTAGE_STATUS_NORMAL = 0,              ///< No unusual voltages have been detected
    ZET_PSU_VOLTAGE_STATUS_OVER,                    ///< Over-voltage has occurred
    ZET_PSU_VOLTAGE_STATUS_UNDER,                   ///< Under-voltage has occurred

} zet_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static properties of the power supply
typedef struct _zet_psu_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the PSU
    ze_bool_t haveFan;                              ///< [out] True if the power supply has a fan
    uint32_t ampLimit;                              ///< [out] The maximum electrical current in amperes that can be drawn

} zet_psu_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic state of the power supply
typedef struct _zet_psu_state_t
{
    zet_psu_voltage_status_t voltStatus;            ///< [out] The current PSU voltage status
    ze_bool_t fanFailed;                            ///< [out] Indicates if the fan has failed
    uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees Celsius.
    uint32_t current;                               ///< [out] The amps being drawn in amperes

} zet_psu_state_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPsuGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPsu
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPsuGetProperties(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPsu
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanPsuGetState(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan resource speed mode
typedef enum _zet_fan_speed_mode_t
{
    ZET_FAN_SPEED_MODE_DEFAULT = 0,                 ///< The fan speed is operating using the hardware default settings
    ZET_FAN_SPEED_MODE_FIXED,                       ///< The fan speed is currently set to a fixed value
    ZET_FAN_SPEED_MODE_TABLE,                       ///< The fan speed is currently controlled dynamically by hardware based on
                                                    ///< a temp/speed table

} zet_fan_speed_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan speed units
typedef enum _zet_fan_speed_units_t
{
    ZET_FAN_SPEED_UNITS_RPM = 0,                    ///< The fan speed is in units of revolutions per minute (rpm)
    ZET_FAN_SPEED_UNITS_PERCENT,                    ///< The fan speed is a percentage of the maximum speed of the fan

} zet_fan_speed_units_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan temperature/speed pair
typedef struct _zet_fan_temp_speed_t
{
    uint32_t temperature;                           ///< [in,out] Temperature in degrees Celsius.
    uint32_t speed;                                 ///< [in,out] The speed of the fan
    zet_fan_speed_units_t units;                    ///< [in,out] The units of the member speed

} zet_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define ZET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // ZET_FAN_TEMP_SPEED_PAIR_COUNT

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan properties
typedef struct _zet_fan_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the fan speed
    uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan
    uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

} zet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan configuration
typedef struct _zet_fan_config_t
{
    zet_fan_speed_mode_t mode;                      ///< [in,out] The fan speed mode (fixed, temp-speed table)
    uint32_t speed;                                 ///< [in,out] The fixed fan speed setting
    zet_fan_speed_units_t speedUnits;               ///< [in,out] The units of the fixed fan speed setting
    uint32_t numPoints;                             ///< [in,out] The number of valid points in the fan speed table
    zet_fan_temp_speed_t table[ZET_FAN_TEMP_SPEED_PAIR_COUNT];  ///< [in,out] Array of temperature/fan speed pairs

} zet_fan_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan state
typedef struct _zet_fan_state_t
{
    zet_fan_speed_mode_t mode;                      ///< [out] The fan speed mode (default, fixed, temp-speed table)
    zet_fan_speed_units_t speedUnits;               ///< [out] The units of the fan speed
    uint32_t speed;                                 ///< [out] The current fan speed

} zet_fan_state_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFanGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFan
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFanGetProperties(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFan
///         + nullptr == pConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFanGetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFan
///         + nullptr == pConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFanSetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFan
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanFanGetState(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    zet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief LED properties
typedef struct _zet_led_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the LED
    ze_bool_t haveRGB;                              ///< [out] Indicates if the LED is RGB capable

} zet_led_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief LED state
typedef struct _zet_led_state_t
{
    ze_bool_t isOn;                                 ///< [in,out] Indicates if the LED is on or off
    uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
    uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
    uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

} zet_led_state_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanLedGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hLed
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanLedGetProperties(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hLed
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanLedGetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hLed
///         + nullptr == pState
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanLedSetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    const zet_led_state_t* pState                   ///< [in] New state of the LED.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error type
typedef enum _zet_ras_error_type_t
{
    ZET_RAS_ERROR_TYPE_CORRECTABLE = 0,             ///< Errors were corrected by hardware
    ZET_RAS_ERROR_TYPE_UNCORRECTABLE,               ///< Error were not corrected

} zet_ras_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS properties
typedef struct _zet_ras_properties_t
{
    zet_ras_error_type_t type;                      ///< [out] The type of RAS error
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t supported;                            ///< [out] True if RAS is supported on this device
    ze_bool_t enabled;                              ///< [out] True if RAS is enabled on this device

} zet_ras_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error details
typedef struct _zet_ras_details_t
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
    uint64_t numFabricErrors;                       ///< [out] The number of errors that have occurred in the high-speed fabric
                                                    ///< ports
    uint64_t numDisplayErrors;                      ///< [out] The number of errors that have occurred in the display

} zet_ras_details_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of RAS error sets
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanRasGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hRas
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanRasGetProperties(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hRas
///         + nullptr == pTotalErrors
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + This device does not support RAS.
///     - ::ZE_RESULT_ERROR_INSUFFICENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t __zecall
zetSysmanRasGetErrors(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
    zet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _zet_sysman_event_type_t
{
    ZET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED = 0,       ///< The frequency is being throttled
    ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED, ///< Interrupt from the PCU when the energy threshold is crossed.
    ZET_SYSMAN_EVENT_TYPE_MAX_TEMPERATURE,          ///< Interrupt from the PCU when the energy Max temperature is reached.
    ZET_SYSMAN_EVENT_TYPE_RAS_ERRORS,               ///< ECC/RAS errors
    ZET_SYSMAN_EVENT_TYPE_NUM,                      ///< The number of event types

} zet_sysman_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event properties
typedef struct _zet_event_properties_t
{
    ze_bool_t supportedEvents[ZET_SYSMAN_EVENT_TYPE_NUM];   ///< [out] Set to true for the events that are supported

} zet_event_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to register/unregister events
typedef struct _zet_event_request_t
{
    zet_sysman_event_type_t event;                  ///< [in] The event type to register.
    uint32_t threshold;                             ///< [in] The application only receives a notification when the total count
                                                    ///< exceeds this value. Set to zero to receive a notification for every
                                                    ///< new event.

} zet_event_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get event properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanEventsGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    zet_event_properties_t* pProperties             ///< [in] Structure describing event properties
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanEventsRegister(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be registered.
    zet_event_request_t* pEvents                    ///< [in][optional] Events to register.
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanEventsUnregister(
    zet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be unregistered.
    zet_event_request_t* pEvents                    ///< [in][optional] Events to unregister.
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_EVENT_WAIT_INFINITE
/// @brief Wait infinitely for events to arrive.
#define ZET_EVENT_WAIT_INFINITE  0xFFFFFFFF
#endif // ZET_EVENT_WAIT_INFINITE

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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEvents
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanEventsListen(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                    ///< device for which the application has registered to receive
                                                    ///< notifications.
    ze_bool_t clear,                                ///< [in] Clear the event status.
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                    ///< check status and return immediately. Set to ::ZET_EVENT_WAIT_INFINITE
                                                    ///< to block until events arrive.
    uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::zet_sysman_event_type_t) that have been
                                                    ///< triggered.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic test suite type
typedef enum _zet_diag_type_t
{
    ZET_DIAG_TYPE_SCAN = 0,                         ///< Run SCAN diagnostics
    ZET_DIAG_TYPE_ARRAY,                            ///< Run Array diagnostics

} zet_diag_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic results
typedef enum _zet_diag_result_t
{
    ZET_DIAG_RESULT_NO_ERRORS = 0,                  ///< Diagnostic completed without finding errors to repair
    ZET_DIAG_RESULT_ABORT,                          ///< Diagnostic had problems running tests
    ZET_DIAG_RESULT_FAIL_CANT_REPAIR,               ///< Diagnostic had problems setting up repairs
    ZET_DIAG_RESULT_REBOOT_FOR_REPAIR,              ///< Diagnostics found errors, setup for repair and reboot is required to
                                                    ///< complete the process

} zet_diag_result_t;

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

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic test
typedef struct _zet_diag_test_t
{
    uint32_t index;                                 ///< [out] Index of the test
    const char* name;                               ///< [out] Name of the test

} zet_diag_test_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostics test suite properties
typedef struct _zet_diag_properties_t
{
    zet_diag_type_t type;                           ///< [out] The type of diagnostics test suite
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    const char* name;                               ///< [out] Name of the diagnostics test suite
    uint32_t numTests;                              ///< [out] The number of tests in the test suite
    const zet_diag_test_t* pTests;                  ///< [out] Array of tests (size ::zet_diag_properties_t.numTests), sorted
                                                    ///< by increasing value of ::zet_diag_test_t.index

} zet_diag_properties_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanDiagnosticsGet(
    zet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDiagnostics
///         + nullptr == pProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanDiagnosticsGetProperties(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    zet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDiagnostics
///         + nullptr == pResult
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanDiagnosticsRunTests(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_SYSMAN_H
