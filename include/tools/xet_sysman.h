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
#ifndef XET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define XET_STRING_PROPERTY_SIZE  32
#endif // XET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties
typedef struct _xet_sysman_properties_t
{
    xe_device_properties_t core;                    ///< [out] Core device properties
    uint32_t numSubdevices;                         ///< [out] Number of sub-devices
    int8_t serialNumber[XET_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
    int8_t boardNumber[XET_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
    int8_t brandName[XET_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
    int8_t modelName[XET_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
    int8_t vendorName[XET_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
    int8_t driverVersion[XET_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)

} xet_sysman_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about the device
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
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDeviceGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Scheduler mode
typedef enum _xet_sched_mode_t
{
    XET_SCHED_MODE_CONCURRENT = 0,                  ///< Multiple applications or contexts are submitting work concurrently to
                                                    ///< the hardware. When work for one context completes or higher priority
                                                    ///< work arrives, the scheduler organizes to submit the new work to the
                                                    ///< hardware as soon as possible.
    XET_SCHED_MODE_TIMESLICE,                       ///< The scheduler attempts to fairly timeslice hardware execution time
                                                    ///< between multiple contexts submitting work to the hardware
                                                    ///< concurrently.
    XET_SCHED_MODE_EXCLUSIVE,                       ///< Any application or context can run indefinitely on the hardware
                                                    ///< without being preempted or terminated. All pending work for other
                                                    ///< contexts must wait until the running context completes with no further
                                                    ///< submitted work.

} xet_sched_mode_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_SCHED_WATCHDOG_DISABLE
/// @brief Disable forward progress guard timeout.
#define XET_SCHED_WATCHDOG_DISABLE  (~(0ULL))
#endif // XET_SCHED_WATCHDOG_DISABLE

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for concurrent scheduler mode
///        (::XET_SCHED_MODE_CONCURRENT)
typedef struct _xet_sched_concurrent_properties_t
{
    uint64_t watchdogTimeout;                       ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< for a batch of work submitted to a hardware engine to complete or to
                                                    ///< be preempted so as to run another context.
                                                    ///< If this time is exceeded, the hardware engine is reset and the context terminated.
                                                    ///< If set to ::XET_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                    ///< long as it wants without being terminated, but preemption attempts to
                                                    ///< run other contexts are permitted but not enforced.

} xet_sched_concurrent_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for timeslice scheduler mode
///        (::XET_SCHED_MODE_TIMESLICE)
typedef struct _xet_sched_timeslice_properties_t
{
    uint64_t interval;                              ///< [in,out] The average interval in microseconds that a submission for a
                                                    ///< context will run on a hardware engine before being preempted out to
                                                    ///< run a pending submission for another context.
    uint64_t yieldTimeout;                          ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< to preempt a workload running on an engine before deciding to reset
                                                    ///< the hardware engine and terminating the associated context.

} xet_sched_timeslice_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduler mode
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
///         + nullptr == pMode
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + Device does not support scheduler modes.
xe_result_t __xecall
xetSysmanSchedulerGetCurrentMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::XET_SCHED_MODE_CONCURRENT
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
///         + This scheduler mode is not supported. Other modes may be supported unless ::xetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
xe_result_t __xecall
xetSysmanSchedulerGetConcurrentModeProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xe_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    xet_sched_concurrent_properties_t* pConfig      ///< [in] Will contain the current parameters for this mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::XET_SCHED_MODE_TIMESLICE
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
///         + This scheduler mode is not supported. Other modes may be supported unless ::xetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
xe_result_t __xecall
xetSysmanSchedulerGetTimesliceModeProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xe_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    xet_sched_concurrent_properties_t* pConfig      ///< [in] Will contain the current parameters for this mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::XET_SCHED_MODE_CONCURRENT or update
///        scheduler mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized for multiple applications or contexts
///       submitting work concurrently to the hardware. When work for one
///       context completes or higher priority work arrives, the scheduler
///       organizes to submit the new work to the hardware as soon as possible.
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
///         + nullptr == pNeedReboot
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::xetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
xe_result_t __xecall
xetSysmanSchedulerSetConcurrentMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_sched_concurrent_properties_t* pProperties, ///< [in] The properties to use when configurating this mode.
    xe_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::XET_SCHED_MODE_TIMESLICE or update
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///         + nullptr == pNeedReboot
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::xetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
xe_result_t __xecall
xetSysmanSchedulerSetTimesliceMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_sched_concurrent_properties_t* pProperties, ///< [in] The properties to use when configurating this mode.
    xe_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::XET_SCHED_MODE_EXCLUSIVE
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pNeedReboot
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + This scheduler mode is not supported. Other modes may be supported unless ::xetSysmanSchedulerGetCurrentMode() returns the same error in which case no scheduler modes are supported on this device.
xe_result_t __xecall
xetSysmanSchedulerSetExclusiveMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xe_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
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

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out if the device has been repaired (either by the manufacturer
///        or by running diagnostics)
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pWasRepaired
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + This device does not record this information or does not support repair features.
xe_result_t __xecall
xetSysmanDeviceWasRepaired(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    xe_bool_t* pWasRepaired                         ///< [in] Will indicate if the device was repaired
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI address
typedef struct _xet_pci_address_t
{
    uint32_t domain;                                ///< [out] BDF domain
    uint32_t bus;                                   ///< [out] BDF bus
    uint32_t device;                                ///< [out] BDF device
    uint32_t function;                              ///< [out] BDF function

} xet_pci_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI speed
typedef struct _xet_pci_speed_t
{
    uint32_t gen;                                   ///< [out] The link generation
    uint32_t width;                                 ///< [out] The number of lanes
    uint32_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec
    uint32_t maxPacketSize;                         ///< [out] Maximum packet size in bytes.

} xet_pci_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static PCI properties
typedef struct _xet_pci_properties_t
{
    xet_pci_address_t address;                      ///< [out] The BDF address
    uint32_t numBars;                               ///< [out] The number of configured bars
    xet_pci_speed_t maxSpeed;                       ///< [out] Fastest port configuration supported by the device.

} xet_pci_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic PCI state
typedef struct _xet_pci_state_t
{
    xet_pci_speed_t speed;                          ///< [out] The current port configure speed

} xet_pci_state_t;

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
/// @brief Properties of a pci bar
typedef struct _xet_pci_bar_properties_t
{
    xet_pci_bar_type_t type;                        ///< [out] The type of bar
    uint64_t base;                                  ///< [out] Base address of the bar.
    uint64_t size;                                  ///< [out] Size of the bar.

} xet_pci_bar_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI throughput
/// 
/// @details
///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
///       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
///       s1.timestamp))
typedef struct _xet_pci_throughput_t
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

} xet_pci_throughput_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI stats counters
/// 
/// @details
///     - Percent replays is calculated by taking two snapshots (s1, s2) and
///       using the equation: %replay = 10^6 * (s2.replayCounter -
///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _xet_pci_stats_t
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

} xet_pci_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
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
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPciGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current PCI state - current speed
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
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPciGetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a bar
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
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPciGetBarProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::xet_pci_properties_t.numBars -
                                                    ///< 1]).
    xet_pci_bar_properties_t* pProperties           ///< [in] Will contain properties of the specified bar
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI throughput
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
///         + nullptr == pThroughput
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPciGetThroughput(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_pci_throughput_t* pThroughput               ///< [in] Will contain a snapshot of the latest throughput counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats
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
///         + nullptr == pStats
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPciGetStats(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Properties related to device power settings
typedef struct _xet_power_properties_t
{
    xe_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    xe_bool_t canControl;                           ///< [out] Software can change the power limits.
    uint32_t maxLimit;                              ///< [out] The maximum power limit in milliwatts that can be requested.

} xet_power_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy counter snapshot
/// 
/// @details
///     - Average power is calculated by taking two snapshots (s1, s2) and using
///       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
///       s1.timestamp)
typedef struct _xet_power_energy_counter_t
{
    uint64_t energy;                                ///< [out] The monotonic energy counter in microjoules.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when energy was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} xet_power_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy threshold
/// 
/// @details
///     - Energy threshold value, when this value is crossed, pcu will signal an
///       interrupt.
typedef struct _xet_power_energy_threshold_t
{
    uint32_t energy;                                ///< [in,out] The energy threshold in joules.

} xet_power_energy_threshold_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sustained power limits
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency if
///       the power averaged over a window (typically seconds) exceeds this
///       limit.
typedef struct _xet_power_sustained_limit_t
{
    xe_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts
    uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

} xet_power_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Burst power limit
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency of
///       the device if the power averaged over a few milliseconds exceeds a
///       limit known as PL2. Typically PL2 > PL1 so that it permits the
///       frequency to burst higher for short periods than would be otherwise
///       permitted by PL1.
typedef struct _xet_power_burst_limit_t
{
    xe_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} xet_power_burst_limit_t;

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
typedef struct _xet_power_peak_limit_t
{
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} xet_power_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power domains
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGetProperties(
    xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    xet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
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
///         + nullptr == hPower
///         + nullptr == pEnergy
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGetEnergyCounter(
    xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    xet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pThreshold
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGetEnergyThreshold(
    xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    xet_power_energy_threshold_t* pThreshold        ///< [out] The current energy threshold value in joules.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
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
///         + nullptr == hPower
///         + nullptr == pThreshold
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerSetEnergyThreshold(
    xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    xet_power_energy_threshold_t* pThreshold        ///< [in] The energy threshold to be set in joules.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
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
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGetLimits(
    xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    xet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
    xet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
    xet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
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
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerSetLimits(
    xet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    const xet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const xet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const xet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Overcloking modes
typedef enum _xet_oc_mode_t
{
    XET_OC_MODE_INTERPOLATIVE = 0,                  ///< Interpolative Mode.
    XET_OC_MODE_OVERRIDE = 1,                       ///< Override Mode.

} xet_oc_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking error type
typedef enum _xet_oc_error_type_t
{
    XET_OVERCLOCKING_LOCKED = 225,                  ///< The overclocking is locked. Service is read-only.
    XET_OVERCLOCKING_DDOMAIN_SERVICE_NOT_SUPPORTED, ///< The specified domain does not support the requested service.
    XET_OVERCLOCKING_RATIO_EXCEEDS_MAX,             ///< The ratio exceeds maximum overclocking limits.
    XET_OVERCLOCKING_VOLTAGE_EXCEEDS_MAX,           ///< Requested voltage exceeds input regulators max supported voltage.
    XET_OVERCLOCKING_NOT_SUPPORTED,                 ///< No overclocking capability on the Hardware.
    $OVERCLOCKING_INVALID_VR_ADDRESS,               ///< The VR Address provided is illegal.
    $OVERCLOCKING_INVALID_ICCMAX,                   ///< ICCMAX value given is invalid (more than 10 bits) or too low.
    XET_OVERCLOCKING_VOLTAGE_OVERRIDE_DISABLED,     ///< Voltage manipulation attempted when it is disabled.
    XET_OVERCLOCKING_INVALID_COMMAND,               ///< Data setting invalid for the command.

} xet_oc_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking VR Topolgy
/// 
/// @details
///     - Provides all the information related to the VR.
typedef struct _xet_oc_vr_topology
{
    xe_bool_t VccInAuxExists;                       ///< [out] VCCIN_AUX Exists (asserted if separate VR)
    xe_bool_t VccStgPgExists;                       ///< [out] VCCSTG_PG Exists
    xe_bool_t VccStPgExists;                        ///< [out] VCCST_PG Exists
    xe_bool_t VccSfrOcPgExists;                     ///< [out] VCCSFR_OC_PG Exists
    uint16_t VccInAuxLp;                            ///< [out] VCCIN_Aux_LP Level (0: 1.8v, 1: 1.65v)
    uint16_t VccInSvidAddress;                      ///< [out] VCCIN SVID Address
    uint16_t VccInVrType;                           ///< [out] VCCIN VR Type (asserted if SVID)
    uint16_t SvidNotPresent;                        ///< [out] SVID not present
    uint16_t PsysDisabled;                          ///< [out] PSYS Disabled

} xet_oc_vr_topology;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking properties
/// 
/// @details
///     - Provides all the overclocking capabilities and properties supported by
///       the device in the current domain.
typedef struct _xet_oc_capabilities_t
{
    uint16_t MaxOcRatioLimit;                       ///< [out] Max overclocking ratio limit
    uint16_t P0Ratio;                               ///< [out] Fused P0 ratio.
    uint16_t P0Voltage;                             ///< [out] Fused P0 voltage.
    xe_bool_t RatioOcSupported;                     ///< [out] Ratio overclocking supported
    xe_bool_t VoltageOverrideSupported;             ///< [out] Voltage overrides supported
    xe_bool_t VoltageOffsetSupported;               ///< [out] Voltage offset is supported
    xe_bool_t HighVoltModeCapable;                  ///< [out] Capable of high voltage mode
    xe_bool_t HighVoltModeEnabled;                  ///< [out] High voltage mode is enabled
    xet_oc_vr_topology OcVrTopology;                ///< [out] Hold all the Vr Topology properties.

} xet_oc_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking settings override
/// 
/// @details
///     - Provide the current settings to be read or changed.
typedef struct _xet_oc_settings_override_t
{
    uint16_t MaxOcRatio;                            ///< [in,out] Max overclocking ratio
    uint16_t TargetVoltage;                         ///< [in,out] Target Voltage. Units: divide by 2^10 for decimal voltage.
    uint16_t TargetMode;                            ///< [in,out] Overclock Mode: 0 - Interpolative,  1 - Override.
    uint16_t VoltageOffset;                         ///< [in,out] Voltage offset +/-999mV (minimum end voltage cannot be lower
                                                    ///< than 250mV).
    uint32_t ICCMax;                                ///< [in,out] Maximum desired current.
    uint32_t TjMax;                                 ///< [in,out] Maximum temperature in °C.

} xet_oc_settings_override_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan Point.
/// 
/// @details
///     - Temperature is given in °C and fan speed is given as a percentage
///       value
typedef struct _xet_oc_fan_point_t
{
    uint8_t TemperatureDegreesCelsius;              ///< [in] Temperature for current point.
    uint8_t FanSpeedPercent;                        ///< [in] Percentage value, where 0% means stop the fan and 100% means run
                                                    ///< the fan at maximum speed.

} xet_oc_fan_point_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan control settings.
/// 
/// @details
///     - Provide the means to control the fan speed.
typedef struct _xet_oc_fan_control_t
{
    uint32_t FanPointsNumber;                       ///< [in] Number of fan points.
    xet_oc_fan_point_t* pFanPoints;                 ///< [in] Array with FanPointsNumber of points.

} xet_oc_fan_control_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan speed
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
///         + nullptr == hFrequency
///         + nullptr == pFanControl
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencySetFanSpeed(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_oc_fan_control_t* pFanControl               ///< [out] Pointer to the allocated structure.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking capabilities.
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
///         + nullptr == hFrequency
///         + nullptr == pOcCapabilities
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetOcCapabilities(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_oc_capabilities_t* pOcCapabilities          ///< [out] Pointer to the allocated structure.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the Vr topology.
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
///         + nullptr == hFrequency
///         + nullptr == pOcVrTopology
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetOcVrTopology(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_oc_vr_topology* pOcVrTopology               ///< [out] Pointer to the allocated structure.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the Oc override properties.
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
///         + nullptr == hFrequency
///         + nullptr == pOcSettingsOverride
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetOcOverrideProperties(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_oc_settings_override_t* pOcSettingsOverride ///< [out] Pointer to the allocated structure.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the Oc Icc Max.
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
///         + nullptr == hFrequency
///         + nullptr == pOcIccMax
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetOcIccMax(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    uint32_t* pOcIccMax                             ///< [out] Pointer to the allocated uint32.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the Oc Tj Max.
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
///         + nullptr == hFrequency
///         + nullptr == pOcTjMax
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetOcTjMax(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    uint32_t* pOcTjMax                              ///< [out] Pointer to the allocated uint32.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the Oc override properties.
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
///         + nullptr == hFrequency
///         + nullptr == pOcSettingsOverride
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencySetOcOverrideProperties(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_oc_settings_override_t* pOcSettingsOverride ///< [in] Pointer to the allocated structure.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the Oc Icc Max.
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
///         + nullptr == hFrequency
///         + nullptr == pOcIccMax
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencySetOcIccMax(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    uint32_t* pOcIccMax                             ///< [in] Pointer to the allocated uint32.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the Oc Tj Max.
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
///         + nullptr == hFrequency
///         + nullptr == pOcTjMax
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencySetOcTjMax(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    uint32_t* pOcTjMax                              ///< [in] Pointer to the allocated uint32.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domains
typedef enum _xet_freq_domain_t
{
    XET_FREQ_DOMAIN_GPU = 0,                        ///< Frequency of the GPU.
    XET_FREQ_DOMAIN_MEMORY,                         ///< Frequency of the local memory.

} xet_freq_domain_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency properties
/// 
/// @details
///     - Provides the set of frequencies as a list and as a range/step.
///     - It is generally recommended that applications choose frequencies from
///       the list. However applications can also construct the list themselves
///       using the range/steps provided.
typedef struct _xet_freq_properties_t
{
    xet_freq_domain_t type;                         ///< [out] The type of frequency domain (GPU, memory, ...)
    xe_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    xe_bool_t canControl;                           ///< [out] Indicates if software can control the frequency of this domain
    xe_bool_t canOverclock;                         ///< [out] Indicates if software can overclock this frequency domain
    double min;                                     ///< [out] The minimum clock frequency in units of MHz
    double max;                                     ///< [out] The maximum clock frequency in units of MHz
    double step;                                    ///< [out] The step clock frequency in units of MHz
    uint32_t num;                                   ///< [out] The number of clocks in the array pClocks
    const double* pClocks;                          ///< [out] Array of clock frequencies in units of MHz ordered from smallest
                                                    ///< to largest.

} xet_freq_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency range between which the hardware can operate.
typedef struct _xet_freq_range_t
{
    double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.
    double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.

} xet_freq_range_t;

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
/// @brief Frequency state
typedef struct _xet_freq_state_t
{
    double request;                                 ///< [out] The current frequency request in MHz.
    double tdp;                                     ///< [out] The maximum frequency in MHz supported under the current TDP
                                                    ///< conditions
    double efficient;                               ///< [out] The efficient minimum frequency in MHz
    double actual;                                  ///< [out] The resolved frequency in MHz
    uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the hardware
                                                    ///< (Bitfield of (1<<::xet_freq_throttle_reasons_t)).

} xet_freq_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle time snapshot
/// 
/// @details
///     - Percent time throttled is calculated by taking two snapshots (s1, s2)
///       and using the equation: %throttled = (s2.throttleTime -
///       s1.throttleTime) / (s2.timestamp - s1.timestamp)
typedef struct _xet_freq_throttle_time_t
{
    uint64_t throttleTime;                          ///< [out] The monotonic counter of time in microseconds that the frequency
                                                    ///< has been limited by the hardware.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when throttleTime was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} xet_freq_throttle_time_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of frequency domains
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetProperties(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency limits
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
///         + nullptr == hFrequency
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetRange(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_freq_range_t* pLimits                       ///< [in] The range between which the hardware can operate for the
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencySetRange(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    const xet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFrequency
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetState(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency throttle time
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
///         + nullptr == hFrequency
///         + nullptr == pThrottleTime
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetThrottleTime(
    xet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    xet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator engine groups
typedef enum _xet_engine_group_t
{
    XET_ENGINE_GROUP_ALL = 0,                       ///< Access information about all engines combined.
    XET_ENGINE_GROUP_COMPUTE,                       ///< Access information about compute engines.
    XET_ENGINE_GROUP_MEDIA,                         ///< Access information about media engines.

} xet_engine_group_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine group properties
typedef struct _xet_engine_properties_t
{
    xet_engine_group_t type;                        ///< [out] The engine group
    xe_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} xet_engine_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine activity counters
/// 
/// @details
///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
///       using the equation: %util = (s2.activeTime - s1.activeTime) /
///       (s2.timestamp - s1.timestamp)
typedef struct _xet_engine_stats_t
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

} xet_engine_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of engine groups
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanEngineGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEngine
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanEngineGetProperties(
    xet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    xet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity stats for an engine group
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
///         + nullptr == hEngine
///         + nullptr == pStats
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanEngineGetActivity(
    xet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    xet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware components
typedef enum _xet_standby_type_t
{
    XET_STANDBY_TYPE_GLOBAL = 0,                    ///< Control the overall standby policy of the device/sub-device

} xet_standby_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware component properties
typedef struct _xet_standby_properties_t
{
    xet_standby_type_t type;                        ///< [out] Which standby hardware component this controls
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} xet_standby_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby promotion modes
typedef enum _xet_standby_promo_mode_t
{
    XET_STANDBY_PROMO_MODE_DEFAULT = 0,             ///< Best compromise between performance and energy savings.
    XET_STANDBY_PROMO_MODE_NEVER,                   ///< The device/component will never shutdown. This can improve performance
                                                    ///< but uses more energy.

} xet_standby_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of standby controls
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanStandbyGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hStandby
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanStandbyGetProperties(
    xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    xet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current standby promotion mode
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
///         + nullptr == hStandby
///         + nullptr == pMode
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanStandbyGetMode(
    xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    xet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set standby promotion mode
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
///         + nullptr == hStandby
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanStandbySetMode(
    xet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    xet_standby_promo_mode_t mode                   ///< [in] New standby mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Firmware properties
typedef struct _xet_firmware_properties_t
{
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    xe_bool_t canControl;                           ///< [out] Indicates if software can flash the firmware
    int8_t name[XET_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
    int8_t version[XET_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

} xet_firmware_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of firmwares
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFirmwareGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFirmware
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFirmwareGetProperties(
    xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    xet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware checksum
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
///         + nullptr == hFirmware
///         + nullptr == pChecksum
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFirmwareGetChecksum(
    xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFirmware
///         + nullptr == pImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFirmwareFlash(
    xet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory module types
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
/// @brief Memory properties
typedef struct _xet_mem_properties_t
{
    xet_mem_type_t type;                            ///< [out] The memory type
    xe_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    uint64_t size;                                  ///< [out] Physical memory size in bytes

} xet_mem_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory bandwidth
/// 
/// @details
///     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
///       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
///       (s2.timestamp - s1.timestamp))
typedef struct _xet_mem_bandwidth_t
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

} xet_mem_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation
/// 
/// @details
///     - Percent allocation is given by 100 * allocated / total.
///     - Percent free is given by 100 * (total - allocated) / total.
typedef struct _xet_mem_alloc_t
{
    uint64_t allocated;                             ///< [out] The total allocated bytes
    uint64_t total;                                 ///< [out] The total physical memory in bytes

} xet_mem_alloc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of memory modules
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanMemoryGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hMemory
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanMemoryGetProperties(
    xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    xet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory bandwidth
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
///         + nullptr == hMemory
///         + nullptr == pBandwidth
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanMemoryGetBandwidth(
    xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    xet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory allocation
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
///         + nullptr == hMemory
///         + nullptr == pAllocated
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanMemoryGetAllocated(
    xet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    xet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Connectivity switch properties
typedef struct _xet_link_switch_properties_t
{
    xe_bool_t onSubdevice;                          ///< [out] True if the switch is located on a sub-device; false means that
                                                    ///< the switch is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} xet_link_switch_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Connectivity switch state
typedef struct _xet_link_switch_state_t
{
    xe_bool_t enabled;                              ///< [out] Indicates if the switch is enabled/disabled

} xet_link_switch_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of connectivity switches
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkSwitchGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_link_switch_handle_t* phSwitch       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get connectivity switch properties
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
///         + nullptr == hSwitch
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkSwitchGetProperties(
    xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
    xet_link_switch_properties_t* pProperties       ///< [in] Will contain the Switch properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get connectivity switch state
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
///         + nullptr == hSwitch
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkSwitchGetState(
    xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
    xet_link_switch_state_t* pState                 ///< [in] Will contain the current state of the switch (enabled/disabled).
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set connectivity switch state
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
///         + nullptr == hSwitch
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkSwitchSetState(
    xet_sysman_link_switch_handle_t hSwitch,        ///< [in] Handle for the component.
    xe_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Connectivity port speed
typedef struct _xet_link_port_speed_t
{
    uint32_t bitRate;                               ///< [out] Bits/sec that the link is operating at
    uint32_t width;                                 ///< [out] The number of lanes
    uint32_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

} xet_link_port_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Connectivity port properties
typedef struct _xet_link_port_properties_t
{
    uint32_t portNum;                               ///< [out] The port number on the switch
    xet_link_port_speed_t maxSpeed;                 ///< [out] Maximum bandwidth supported by the port

} xet_link_port_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Connectivity port state
typedef struct _xet_link_port_state_t
{
    xe_bool_t isConnected;                          ///< [out] Indicates if the port is connected to a remote Switch
    xet_link_port_speed_t rxSpeed;                  ///< [out] Current maximum receive speed
    xet_link_port_speed_t txSpeed;                  ///< [out] Current maximum transmit speed

} xet_link_port_state_t;

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
typedef struct _xet_link_port_throughput_t
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

} xet_link_port_throughput_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Connectivity port stats counters
/// 
/// @details
///     - Percent replays is calculated by taking two snapshots (s1, s2) and
///       using the equation: %replay = 10^6 * (s2.replayCounter -
///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _xet_link_port_stats_t
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

} xet_link_port_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of connectivity ports in a switch
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
///         + nullptr == hSysmanLinkSwitch
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkSwitchGetPorts(
    xet_sysman_link_switch_handle_t hSysmanLinkSwitch,  ///< [in] SMI handle of the connectivity switch.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_link_port_handle_t* phPort           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get connectivity port properties
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
///         + nullptr == hPort
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkPortGetProperties(
    xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
    xet_link_port_properties_t* pProperties         ///< [in] Will contain properties of the Switch Port
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get connectivity port state
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
///         + nullptr == hPort
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkPortGetState(
    xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
    xet_link_port_state_t* pState                   ///< [in] Will contain the current state of the Switch Port
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get connectivity port throughput
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
///         + nullptr == hPort
///         + nullptr == pThroughput
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkPortGetThroughput(
    xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
    xet_link_port_throughput_t* pThroughput         ///< [in] Will contain the Switch port throughput counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get connectivity port stats
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
///         + nullptr == hPort
///         + nullptr == pStats
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkPortGetStats(
    xet_sysman_link_port_handle_t hPort,            ///< [in] Handle for the component.
    xet_link_port_stats_t* pStats                   ///< [in] Will contain the Switch port stats.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Check if two connectivity ports are physically connected
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
///         + nullptr == hPort
///         + nullptr == hRemotePort
///         + nullptr == pConnected
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLinkPortIsConnected(
    xet_sysman_link_port_handle_t hPort,            ///< [in] Handle of the local connectivity port.
    xet_sysman_link_port_handle_t hRemotePort,      ///< [in] Handle of the remote connectivity port.
    xe_bool_t* pConnected                           ///< [in] Will indicate connected to the remote port.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensors
typedef enum _xet_temp_sensors_t
{
    XET_TEMP_SENSORS_GLOBAL = 0,                    ///< The maximum temperature across all device sensors
    XET_TEMP_SENSORS_GPU,                           ///< The maximum temperature across all sensors in the GPU
    XET_TEMP_SENSORS_MEMORY,                        ///< The maximum temperature across all sensors in the local memory

} xet_temp_sensors_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor properties
typedef struct _xet_temp_properties_t
{
    xet_temp_sensors_t type;                        ///< [out] Which part of the device the temperature sensor measures
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} xet_temp_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of temperature sensors
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanTemperatureGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTemperature
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanTemperatureGetProperties(
    xet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    xet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the temperature from a specified sensor
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
///         + nullptr == hTemperature
///         + nullptr == pTemperature
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanTemperatureRead(
    xet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PSU voltage status
typedef enum _xet_psu_voltage_status_t
{
    XET_PSU_VOLTAGE_STATUS_NORMAL = 0,              ///< No unusual voltages have been detected
    XET_PSU_VOLTAGE_STATUS_OVER,                    ///< Over-voltage has occurred
    XET_PSU_VOLTAGE_STATUS_UNDER,                   ///< Under-voltage has occurred

} xet_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static properties of the power supply
typedef struct _xet_psu_properties_t
{
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    xe_bool_t canControl;                           ///< [out] Indicates if software can control the PSU
    xe_bool_t haveFan;                              ///< [out] True if the power supply has a fan
    uint32_t ampLimit;                              ///< [out] The maximum electrical current in amperes that can be drawn

} xet_psu_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic state of the power supply
typedef struct _xet_psu_state_t
{
    xet_psu_voltage_status_t voltStatus;            ///< [out] The current PSU voltage status
    xe_bool_t fanFailed;                            ///< [out] Indicates if the fan has failed
    uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees celcius
    uint32_t current;                               ///< [out] The amps being drawn in amperes

} xet_psu_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power supplies
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPsuGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPsu
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPsuGetProperties(
    xet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    xet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current power supply state
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
///         + nullptr == hPsu
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPsuGetState(
    xet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    xet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan resource speed mode
typedef enum _xet_fan_speed_mode_t
{
    XET_FAN_SPEED_MODE_DEFAULT = 0,                 ///< The fan speed is operating using the hardware default settings
    XET_FAN_SPEED_MODE_FIXED,                       ///< The fan speed is currently set to a fixed value
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
/// @brief Fan properties
typedef struct _xet_fan_properties_t
{
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    xe_bool_t canControl;                           ///< [out] Indicates if software can control the fan speed
    uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan
    uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

} xet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan configuration
typedef struct _xet_fan_config_t
{
    xet_fan_speed_mode_t mode;                      ///< [in,out] The fan speed mode (fixed, temp-speed table)
    uint32_t speed;                                 ///< [in,out] The fixed fan speed setting
    xet_fan_speed_units_t speedUnits;               ///< [in,out] The units of the fixed fan speed setting
    uint32_t numPoints;                             ///< [in,out] The number of valid points in the fan speed table
    xet_fan_temp_speed_t table[XET_FAN_TEMP_SPEED_PAIR_COUNT];  ///< [in,out] Array of temperature/fan speed pairs

} xet_fan_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan state
typedef struct _xet_fan_state_t
{
    xet_fan_speed_mode_t mode;                      ///< [out] The fan speed mode (default, fixed, temp-speed table)
    xet_fan_speed_units_t speedUnits;               ///< [out] The units of the fan speed
    uint32_t speed;                                 ///< [out] The current fan speed

} xet_fan_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of fans
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFan
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanGetProperties(
    xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    xet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current fan configuration
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
///         + nullptr == hFan
///         + nullptr == pConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanGetConfig(
    xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    xet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan configuration
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
///         + nullptr == hFan
///         + nullptr == pConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanSetConfig(
    xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    const xet_fan_config_t* pConfig                 ///< [in] New fan configuration.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a fan - current mode and speed
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
///         + nullptr == hFan
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanGetState(
    xet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    xet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    xet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief LED properties
typedef struct _xet_led_properties_t
{
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    xe_bool_t canControl;                           ///< [out] Indicates if software can control the LED
    xe_bool_t haveRGB;                              ///< [out] Indicates if the LED is RGB capable

} xet_led_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief LED state
typedef struct _xet_led_state_t
{
    xe_bool_t isOn;                                 ///< [in,out] Indicates if the LED is on or off
    uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
    uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
    uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

} xet_led_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of LEDs
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLedGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hLed
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLedGetProperties(
    xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    xet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a LED - on/off, color
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
///         + nullptr == hLed
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLedGetState(
    xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    xet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set state of a LED - on/off, color
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
///         + nullptr == hLed
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLedSetState(
    xet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    const xet_led_state_t* pState                   ///< [in] New state of the LED.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error type
typedef enum _xet_ras_error_type_t
{
    XET_RAS_ERROR_TYPE_CORRECTABLE = 0,             ///< Errors were corrected by hardware
    XET_RAS_ERROR_TYPE_UNCORRECTABLE,               ///< Error were not corrected

} xet_ras_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS properties
typedef struct _xet_ras_properties_t
{
    xet_ras_error_type_t type;                      ///< [out] The type of RAS error
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    xe_bool_t supported;                            ///< [out] True if RAS is supported on this device
    xe_bool_t enabled;                              ///< [out] True if RAS is enabled on this device

} xet_ras_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error details
typedef struct _xet_ras_details_t
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

} xet_ras_details_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of RAS error sets
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRasGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hRas
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRasGetProperties(
    xet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    xet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hRas
///         + nullptr == pTotalErrors
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + This device does not support RAS.
///     - ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
xe_result_t __xecall
xetSysmanRasGetErrors(
    xet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    xe_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
    xet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _xet_sysman_event_type_t
{
    XET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED = 0,       ///< The frequency is being throttled
    XET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED, ///< Interrupt from the PCU when the energy threshold is crossed.
    XET_SYSMAN_EVENT_TYPE_RAS_ERRORS,               ///< ECC/RAS errors
    XET_SYSMAN_EVENT_TYPE_NUM,                      ///< The number of event types

} xet_sysman_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event properties
typedef struct _xet_event_properties_t
{
    xe_bool_t supportedEvents[XET_SYSMAN_EVENT_TYPE_NUM];   ///< [out] Set to true for the events that are supported

} xet_event_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Request structure used to register/unregister events
typedef struct _xet_event_request_t
{
    xet_sysman_event_type_t event;                  ///< [in] The event type to register.
    uint32_t threshold;                             ///< [in] The application only receives a notification when the total count
                                                    ///< exceeds this value. Set to zero to receive a notification for every
                                                    ///< new event.

} xet_event_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get event properties
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
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanEventsGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_event_properties_t* pProperties             ///< [in] Structure describing event properties
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanEventsRegister(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be registered.
    xet_event_request_t* pEvents                    ///< [in][optional] Events to register.
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanEventsUnregister(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be unregistered.
    xet_event_request_t* pEvents                    ///< [in][optional] Events to unregister.
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
xetSysmanEventsListen(
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
/// @brief Diagnostic test suite type
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
/// @brief Diagnostics test suite properties
typedef struct _xet_diag_properties_t
{
    xet_diag_type_t type;                           ///< [out] The type of diagnostics test suite
    xe_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling SMI handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    const char* name;                               ///< [out] Name of the diagnostics test suite
    uint32_t numTests;                              ///< [out] The number of tests in the test suite
    const xet_diag_test_t* pTests;                  ///< [out] Array of tests (size ::xet_diag_properties_t.numTests), sorted
                                                    ///< by increasing value of ::xet_diag_test_t.index

} xet_diag_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of diagnostics test suites
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDiagnosticsGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    xet_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDiagnostics
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDiagnosticsGetProperties(
    xet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    xet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDiagnostics
///         + nullptr == pResult
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDiagnosticsRunTests(
    xet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    xet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_SYSMAN_H
