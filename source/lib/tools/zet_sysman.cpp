/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_sysman.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#include "zet_lib.h"

extern "C" {

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
    )
{
    auto pfnGet = zet_lib::context.ddiTable.Sysman.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGet( hDevice, version, phSysman );
}

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
    )
{
    auto pfnDeviceGetProperties = zet_lib::context.ddiTable.Sysman.pfnDeviceGetProperties;
    if( nullptr == pfnDeviceGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceGetProperties( hSysman, pProperties );
}

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
    )
{
    auto pfnSchedulerGetCurrentMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerGetCurrentMode;
    if( nullptr == pfnSchedulerGetCurrentMode )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSchedulerGetCurrentMode( hSysman, pMode );
}

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
    )
{
    auto pfnSchedulerGetTimeoutModeProperties = zet_lib::context.ddiTable.Sysman.pfnSchedulerGetTimeoutModeProperties;
    if( nullptr == pfnSchedulerGetTimeoutModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSchedulerGetTimeoutModeProperties( hSysman, getDefaults, pConfig );
}

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
    )
{
    auto pfnSchedulerGetTimesliceModeProperties = zet_lib::context.ddiTable.Sysman.pfnSchedulerGetTimesliceModeProperties;
    if( nullptr == pfnSchedulerGetTimesliceModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSchedulerGetTimesliceModeProperties( hSysman, getDefaults, pConfig );
}

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
    )
{
    auto pfnSchedulerSetTimeoutMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetTimeoutMode;
    if( nullptr == pfnSchedulerSetTimeoutMode )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSchedulerSetTimeoutMode( hSysman, pProperties, pNeedReboot );
}

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
    )
{
    auto pfnSchedulerSetTimesliceMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetTimesliceMode;
    if( nullptr == pfnSchedulerSetTimesliceMode )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSchedulerSetTimesliceMode( hSysman, pProperties, pNeedReboot );
}

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
    )
{
    auto pfnSchedulerSetExclusiveMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetExclusiveMode;
    if( nullptr == pfnSchedulerSetExclusiveMode )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSchedulerSetExclusiveMode( hSysman, pNeedReboot );
}

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
    )
{
    auto pfnSchedulerSetComputeUnitDebugMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetComputeUnitDebugMode;
    if( nullptr == pfnSchedulerSetComputeUnitDebugMode )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSchedulerSetComputeUnitDebugMode( hSysman, pNeedReboot );
}

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
    )
{
    auto pfnDeviceReset = zet_lib::context.ddiTable.Sysman.pfnDeviceReset;
    if( nullptr == pfnDeviceReset )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceReset( hSysman );
}

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
    )
{
    auto pfnDeviceWasRepaired = zet_lib::context.ddiTable.Sysman.pfnDeviceWasRepaired;
    if( nullptr == pfnDeviceWasRepaired )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceWasRepaired( hSysman, pWasRepaired );
}

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
    )
{
    auto pfnPciGetProperties = zet_lib::context.ddiTable.Sysman.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnPciGetProperties( hSysman, pProperties );
}

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
    )
{
    auto pfnPciGetState = zet_lib::context.ddiTable.Sysman.pfnPciGetState;
    if( nullptr == pfnPciGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnPciGetState( hSysman, pState );
}

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
    )
{
    auto pfnPciGetBarProperties = zet_lib::context.ddiTable.Sysman.pfnPciGetBarProperties;
    if( nullptr == pfnPciGetBarProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnPciGetBarProperties( hSysman, barIndex, pProperties );
}

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
    )
{
    auto pfnPciGetThroughput = zet_lib::context.ddiTable.Sysman.pfnPciGetThroughput;
    if( nullptr == pfnPciGetThroughput )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnPciGetThroughput( hSysman, pThroughput );
}

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
    )
{
    auto pfnPciGetStats = zet_lib::context.ddiTable.Sysman.pfnPciGetStats;
    if( nullptr == pfnPciGetStats )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnPciGetStats( hSysman, pStats );
}

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
    )
{
    auto pfnPowerGet = zet_lib::context.ddiTable.Sysman.pfnPowerGet;
    if( nullptr == pfnPowerGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnPowerGet( hSysman, pCount, phPower );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanPower.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hPower, pProperties );
}

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
    )
{
    auto pfnGetEnergyCounter = zet_lib::context.ddiTable.SysmanPower.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetEnergyCounter( hPower, pEnergy );
}

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
    )
{
    auto pfnGetEnergyThreshold = zet_lib::context.ddiTable.SysmanPower.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetEnergyThreshold( hPower, pThreshold );
}

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
    )
{
    auto pfnSetEnergyThreshold = zet_lib::context.ddiTable.SysmanPower.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetEnergyThreshold( hPower, pThreshold );
}

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
    )
{
    auto pfnGetLimits = zet_lib::context.ddiTable.SysmanPower.pfnGetLimits;
    if( nullptr == pfnGetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
}

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
    )
{
    auto pfnSetLimits = zet_lib::context.ddiTable.SysmanPower.pfnSetLimits;
    if( nullptr == pfnSetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
}

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
    )
{
    auto pfnGetLastOcError = zet_lib::context.ddiTable.SysmanFrequency.pfnGetLastOcError;
    if( nullptr == pfnGetLastOcError )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLastOcError( hFrequency, pOcError );
}

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
    )
{
    auto pfnGetOcCapabilities = zet_lib::context.ddiTable.SysmanFrequency.pfnGetOcCapabilities;
    if( nullptr == pfnGetOcCapabilities )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetOcCapabilities( hFrequency, pOcCapabilities );
}

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
    )
{
    auto pfnGetOcConfig = zet_lib::context.ddiTable.SysmanFrequency.pfnGetOcConfig;
    if( nullptr == pfnGetOcConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetOcConfig( hFrequency, pOcConfiguration );
}

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
    )
{
    auto pfnSetOcConfig = zet_lib::context.ddiTable.SysmanFrequency.pfnSetOcConfig;
    if( nullptr == pfnSetOcConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetOcConfig( hFrequency, pOcConfiguration );
}

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
    )
{
    auto pfnGetOcIccMax = zet_lib::context.ddiTable.SysmanFrequency.pfnGetOcIccMax;
    if( nullptr == pfnGetOcIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetOcIccMax( hFrequency, pOcIccMax );
}

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
    )
{
    auto pfnSetOcIccMax = zet_lib::context.ddiTable.SysmanFrequency.pfnSetOcIccMax;
    if( nullptr == pfnSetOcIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetOcIccMax( hFrequency, pOcIccMax );
}

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
    )
{
    auto pfnGetOcTjMax = zet_lib::context.ddiTable.SysmanFrequency.pfnGetOcTjMax;
    if( nullptr == pfnGetOcTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetOcTjMax( hFrequency, pOcTjMax );
}

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
    )
{
    auto pfnSetOcTjMax = zet_lib::context.ddiTable.SysmanFrequency.pfnSetOcTjMax;
    if( nullptr == pfnSetOcTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetOcTjMax( hFrequency, pOcTjMax );
}

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
    )
{
    auto pfnFrequencyGet = zet_lib::context.ddiTable.Sysman.pfnFrequencyGet;
    if( nullptr == pfnFrequencyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnFrequencyGet( hSysman, pCount, phFrequency );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFrequency.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hFrequency, pProperties );
}

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
    )
{
    auto pfnGetRange = zet_lib::context.ddiTable.SysmanFrequency.pfnGetRange;
    if( nullptr == pfnGetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetRange( hFrequency, pLimits );
}

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
    )
{
    auto pfnSetRange = zet_lib::context.ddiTable.SysmanFrequency.pfnSetRange;
    if( nullptr == pfnSetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetRange( hFrequency, pLimits );
}

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
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanFrequency.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetState( hFrequency, pState );
}

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
    )
{
    auto pfnGetThrottleTime = zet_lib::context.ddiTable.SysmanFrequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetThrottleTime( hFrequency, pThrottleTime );
}

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
    )
{
    auto pfnEngineGet = zet_lib::context.ddiTable.Sysman.pfnEngineGet;
    if( nullptr == pfnEngineGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnEngineGet( hSysman, pCount, phEngine );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanEngine.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hEngine, pProperties );
}

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
    )
{
    auto pfnGetActivity = zet_lib::context.ddiTable.SysmanEngine.pfnGetActivity;
    if( nullptr == pfnGetActivity )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetActivity( hEngine, pStats );
}

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
    )
{
    auto pfnStandbyGet = zet_lib::context.ddiTable.Sysman.pfnStandbyGet;
    if( nullptr == pfnStandbyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnStandbyGet( hSysman, pCount, phStandby );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanStandby.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hStandby, pProperties );
}

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
    )
{
    auto pfnGetMode = zet_lib::context.ddiTable.SysmanStandby.pfnGetMode;
    if( nullptr == pfnGetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMode( hStandby, pMode );
}

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
    )
{
    auto pfnSetMode = zet_lib::context.ddiTable.SysmanStandby.pfnSetMode;
    if( nullptr == pfnSetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetMode( hStandby, mode );
}

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
    )
{
    auto pfnFirmwareGet = zet_lib::context.ddiTable.Sysman.pfnFirmwareGet;
    if( nullptr == pfnFirmwareGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnFirmwareGet( hSysman, pCount, phFirmware );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFirmware.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hFirmware, pProperties );
}

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
    )
{
    auto pfnGetChecksum = zet_lib::context.ddiTable.SysmanFirmware.pfnGetChecksum;
    if( nullptr == pfnGetChecksum )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetChecksum( hFirmware, pChecksum );
}

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
    )
{
    auto pfnFlash = zet_lib::context.ddiTable.SysmanFirmware.pfnFlash;
    if( nullptr == pfnFlash )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnFlash( hFirmware, pImage, size );
}

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
    )
{
    auto pfnMemoryGet = zet_lib::context.ddiTable.Sysman.pfnMemoryGet;
    if( nullptr == pfnMemoryGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnMemoryGet( hSysman, pCount, phMemory );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanMemory.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hMemory, pProperties );
}

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
    )
{
    auto pfnGetBandwidth = zet_lib::context.ddiTable.SysmanMemory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetBandwidth( hMemory, pBandwidth );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory allocation
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
///         + nullptr == pAllocated
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetSysmanMemoryGetAllocated(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
    )
{
    auto pfnGetAllocated = zet_lib::context.ddiTable.SysmanMemory.pfnGetAllocated;
    if( nullptr == pfnGetAllocated )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAllocated( hMemory, pAllocated );
}

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
    )
{
    auto pfnFabricPortGet = zet_lib::context.ddiTable.Sysman.pfnFabricPortGet;
    if( nullptr == pfnFabricPortGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnFabricPortGet( hSysman, pCount, phPort );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hPort, pProperties );
}

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
    )
{
    auto pfnGetLinkType = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetLinkType;
    if( nullptr == pfnGetLinkType )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLinkType( hPort, verbose, pLinkType );
}

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
    )
{
    auto pfnGetConfig = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetConfig( hPort, pConfig );
}

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
    )
{
    auto pfnSetConfig = zet_lib::context.ddiTable.SysmanFabricPort.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetConfig( hPort, pConfig );
}

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
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetState( hPort, pState );
}

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
    )
{
    auto pfnGetThroughput = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetThroughput( hPort, pThroughput );
}

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
    )
{
    auto pfnTemperatureGet = zet_lib::context.ddiTable.Sysman.pfnTemperatureGet;
    if( nullptr == pfnTemperatureGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnTemperatureGet( hSysman, pCount, phTemperature );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanTemperature.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hTemperature, pProperties );
}

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
    )
{
    auto pfnRead = zet_lib::context.ddiTable.SysmanTemperature.pfnRead;
    if( nullptr == pfnRead )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnRead( hTemperature, pTemperature );
}

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
    )
{
    auto pfnPsuGet = zet_lib::context.ddiTable.Sysman.pfnPsuGet;
    if( nullptr == pfnPsuGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnPsuGet( hSysman, pCount, phPsu );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanPsu.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hPsu, pProperties );
}

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
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanPsu.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetState( hPsu, pState );
}

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
    )
{
    auto pfnFanGet = zet_lib::context.ddiTable.Sysman.pfnFanGet;
    if( nullptr == pfnFanGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnFanGet( hSysman, pCount, phFan );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFan.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hFan, pProperties );
}

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
    )
{
    auto pfnGetConfig = zet_lib::context.ddiTable.SysmanFan.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetConfig( hFan, pConfig );
}

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
    )
{
    auto pfnSetConfig = zet_lib::context.ddiTable.SysmanFan.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetConfig( hFan, pConfig );
}

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
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanFan.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetState( hFan, units, pState );
}

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
    )
{
    auto pfnLedGet = zet_lib::context.ddiTable.Sysman.pfnLedGet;
    if( nullptr == pfnLedGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnLedGet( hSysman, pCount, phLed );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanLed.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hLed, pProperties );
}

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
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanLed.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetState( hLed, pState );
}

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
    )
{
    auto pfnSetState = zet_lib::context.ddiTable.SysmanLed.pfnSetState;
    if( nullptr == pfnSetState )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetState( hLed, pState );
}

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
    )
{
    auto pfnRasGet = zet_lib::context.ddiTable.Sysman.pfnRasGet;
    if( nullptr == pfnRasGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnRasGet( hSysman, pCount, phRas );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanRas.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hRas, pProperties );
}

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
    )
{
    auto pfnGetErrors = zet_lib::context.ddiTable.SysmanRas.pfnGetErrors;
    if( nullptr == pfnGetErrors )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetErrors( hRas, clear, pTotalErrors, pDetails );
}

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
    )
{
    auto pfnEventsGetProperties = zet_lib::context.ddiTable.Sysman.pfnEventsGetProperties;
    if( nullptr == pfnEventsGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnEventsGetProperties( hSysman, pProperties );
}

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
    )
{
    auto pfnEventsRegister = zet_lib::context.ddiTable.Sysman.pfnEventsRegister;
    if( nullptr == pfnEventsRegister )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnEventsRegister( hSysman, count, pEvents );
}

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
    )
{
    auto pfnEventsUnregister = zet_lib::context.ddiTable.Sysman.pfnEventsUnregister;
    if( nullptr == pfnEventsUnregister )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnEventsUnregister( hSysman, count, pEvents );
}

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
    )
{
    auto pfnEventsListen = zet_lib::context.ddiTable.Sysman.pfnEventsListen;
    if( nullptr == pfnEventsListen )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnEventsListen( hSysman, clear, timeout, pEvents );
}

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
    )
{
    auto pfnDiagnosticsGet = zet_lib::context.ddiTable.Sysman.pfnDiagnosticsGet;
    if( nullptr == pfnDiagnosticsGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
}

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
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanDiagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hDiagnostics, pProperties );
}

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
    )
{
    auto pfnRunTests = zet_lib::context.ddiTable.SysmanDiagnostics.pfnRunTests;
    if( nullptr == pfnRunTests )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnRunTests( hDiagnostics, start, end, pResult );
}

} // extern "C"

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    Sysman::Sysman( 
        sysman_handle_t handle,                         ///< [in] handle of SMI object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanPower::SysmanPower( 
        sysman_pwr_handle_t handle,                     ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFrequency::SysmanFrequency( 
        sysman_freq_handle_t handle,                    ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanEngine::SysmanEngine( 
        sysman_engine_handle_t handle,                  ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanStandby::SysmanStandby( 
        sysman_standby_handle_t handle,                 ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFirmware::SysmanFirmware( 
        sysman_firmware_handle_t handle,                ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanMemory::SysmanMemory( 
        sysman_mem_handle_t handle,                     ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFabricPort::SysmanFabricPort( 
        sysman_fabric_port_handle_t handle,             ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanTemperature::SysmanTemperature( 
        sysman_temp_handle_t handle,                    ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanPsu::SysmanPsu( 
        sysman_psu_handle_t handle,                     ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFan::SysmanFan( 
        sysman_fan_handle_t handle,                     ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanLed::SysmanLed( 
        sysman_led_handle_t handle,                     ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanRas::SysmanRas( 
        sysman_ras_handle_t handle,                     ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanDiagnostics::SysmanDiagnostics( 
        sysman_diag_handle_t handle,                    ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the handle to access SMI features for a device
    /// 
    /// @details
    ///     - The returned handle is unique
    /// 
    /// @returns
    ///     - Sysman*: Handle for accessing SMI features
    /// 
    /// @throws result_t
    Sysman* __zecall
    Sysman::Get(
        Device* pDevice,                                ///< [in] Handle of the device
        version_t version                               ///< [in] SMI version that application was built with
        )
    {
        zet_sysman_handle_t hSysman;

        auto result = static_cast<result_t>( ::zetSysmanGet(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            static_cast<zet_sysman_version_t>( version ),
            &hSysman ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::Get" );

        Sysman* pSysman = nullptr;

        try
        {
            pSysman = new Sysman( reinterpret_cast<sysman_handle_t>( hSysman ), pDevice );
        }
        catch( std::bad_alloc& )
        {
            delete pSysman;
            pSysman = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::Get" );
        }

        return pSysman;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties about the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DeviceGetProperties(
        properties_t* pProperties                       ///< [in] Structure that will contain information about the device.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDeviceGetProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_sysman_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::DeviceGetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current scheduler mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::SchedulerGetCurrentMode(
        sched_mode_t* pMode                             ///< [in] Will contain the current scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerGetCurrentMode(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_sched_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::SchedulerGetCurrentMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMEOUT
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::SchedulerGetTimeoutModeProperties(
        ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        sched_timeout_properties_t* pConfig             ///< [in] Will contain the current parameters for this mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerGetTimeoutModeProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( getDefaults ),
            reinterpret_cast<zet_sched_timeout_properties_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::SchedulerGetTimeoutModeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMESLICE
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::SchedulerGetTimesliceModeProperties(
        ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        sched_timeslice_properties_t* pConfig           ///< [in] Will contain the current parameters for this mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerGetTimesliceModeProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( getDefaults ),
            reinterpret_cast<zet_sched_timeslice_properties_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::SchedulerGetTimesliceModeProperties" );
    }

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
    /// @throws result_t
    void __zecall
    Sysman::SchedulerSetTimeoutMode(
        sched_timeout_properties_t* pProperties,        ///< [in] The properties to use when configurating this mode.
        ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetTimeoutMode(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_sched_timeout_properties_t*>( pProperties ),
            reinterpret_cast<ze_bool_t*>( pNeedReboot ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::SchedulerSetTimeoutMode" );
    }

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
    /// @throws result_t
    void __zecall
    Sysman::SchedulerSetTimesliceMode(
        sched_timeslice_properties_t* pProperties,      ///< [in] The properties to use when configurating this mode.
        ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetTimesliceMode(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_sched_timeslice_properties_t*>( pProperties ),
            reinterpret_cast<ze_bool_t*>( pNeedReboot ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::SchedulerSetTimesliceMode" );
    }

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
    /// @throws result_t
    void __zecall
    Sysman::SchedulerSetExclusiveMode(
        ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetExclusiveMode(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<ze_bool_t*>( pNeedReboot ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::SchedulerSetExclusiveMode" );
    }

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
    /// @throws result_t
    void __zecall
    Sysman::SchedulerSetComputeUnitDebugMode(
        ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetComputeUnitDebugMode(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<ze_bool_t*>( pNeedReboot ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::SchedulerSetComputeUnitDebugMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset device
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DeviceReset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDeviceReset(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::DeviceReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out if the device has been repaired (either by the manufacturer
    ///        or by running diagnostics)
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DeviceWasRepaired(
        ze::bool_t* pWasRepaired                        ///< [in] Will indicate if the device was repaired
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDeviceWasRepaired(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<ze_bool_t*>( pWasRepaired ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::DeviceWasRepaired" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI properties - address, max speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetProperties(
        pci_properties_t* pProperties                   ///< [in] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_pci_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::PciGetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current PCI state - current speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetState(
        pci_state_t* pState                             ///< [in] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetState(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_pci_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::PciGetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties of a bar
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetBarProperties(
        uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::zet_pci_properties_t.numBars -
                                                        ///< 1]).
        pci_bar_properties_t* pProperties               ///< [in] Will contain properties of the specified bar
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetBarProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            barIndex,
            reinterpret_cast<zet_pci_bar_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::PciGetBarProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI throughput
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetThroughput(
        pci_throughput_t* pThroughput                   ///< [in] Will contain a snapshot of the latest throughput counters.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetThroughput(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_pci_throughput_t*>( pThroughput ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::PciGetThroughput" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI stats
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetStats(
        pci_stats_t* pStats                             ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetStats(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_pci_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::PciGetStats" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PowerGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanPower** ppPower                           ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_pwr_handle_t> hPower;
        hPower.resize( ( ppPower ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanPowerGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hPower.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::PowerGet" );

        for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
            ppPower[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
                ppPower[ i ] = new SysmanPower( reinterpret_cast<sysman_pwr_handle_t>( hPower[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
            {
                delete ppPower[ i ];
                ppPower[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::PowerGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties related to a power domain
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetProperties(
        power_properties_t* pProperties                 ///< [in] Structure that will contain property data.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetProperties(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPower::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy counter
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetEnergyCounter(
        power_energy_counter_t* pEnergy                 ///< [in] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetEnergyCounter(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_energy_counter_t*>( pEnergy ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPower::GetEnergyCounter" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy threshold
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetEnergyThreshold(
        power_energy_threshold_t* pThreshold            ///< [in] The current energy threshold value in joules.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetEnergyThreshold(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_energy_threshold_t*>( pThreshold ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPower::GetEnergyThreshold" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set energy threshold
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::SetEnergyThreshold(
        power_energy_threshold_t* pThreshold            ///< [in] The energy threshold to be set in joules.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerSetEnergyThreshold(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_energy_threshold_t*>( pThreshold ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPower::SetEnergyThreshold" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetLimits(
        power_sustained_limit_t* pSustained,            ///< [in][optional] The sustained power limit.
        power_burst_limit_t* pBurst,                    ///< [in][optional] The burst power limit.
        power_peak_limit_t* pPeak                       ///< [in][optional] The peak power limit.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetLimits(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<zet_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<zet_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPower::GetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::SetLimits(
        const power_sustained_limit_t* pSustained,      ///< [in][optional] The sustained power limit.
        const power_burst_limit_t* pBurst,              ///< [in][optional] The burst power limit.
        const power_peak_limit_t* pPeak                 ///< [in][optional] The peak power limit.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerSetLimits(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<const zet_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<const zet_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<const zet_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPower::SetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the last overclock error
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetLastOcError(
        oc_error_type_t* pOcError                       ///< [in] Error in ::zet_oc_error_type_t .
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetLastOcError(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_error_type_t*>( pOcError ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetLastOcError" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the overclocking capabilities.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetOcCapabilities(
        oc_capabilities_t* pOcCapabilities              ///< [in] Pointer to the capabilities structure ::zet_oc_capabilities_t.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetOcCapabilities(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_capabilities_t*>( pOcCapabilities ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetOcCapabilities" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the overclocking configuration.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetOcConfig(
        oc_configuration_t* pOcConfiguration            ///< [in] Pointer to the configuration structure ::zet_oc_configuration_t.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetOcConfig(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_configuration_t*>( pOcConfiguration ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetOcConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the overclocking configuration.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::SetOcConfig(
        oc_configuration_t* pOcConfiguration            ///< [in] Pointer to the configuration structure ::zet_oc_configuration_t.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencySetOcConfig(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_configuration_t*>( pOcConfiguration ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::SetOcConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the Icc Max.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetOcIccMax(
        oc_icc_max_t* pOcIccMax                         ///< [in] Pointer to the Icc Max.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetOcIccMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_icc_max_t*>( pOcIccMax ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetOcIccMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the Icc Max.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::SetOcIccMax(
        oc_icc_max_t* pOcIccMax                         ///< [in] Pointer to the Icc Max.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencySetOcIccMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_icc_max_t*>( pOcIccMax ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::SetOcIccMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the TjMax.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetOcTjMax(
        oc_tj_max_t* pOcTjMax                           ///< [in] Pointer to the TjMax.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetOcTjMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_tj_max_t*>( pOcTjMax ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetOcTjMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the TjMax.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::SetOcTjMax(
        oc_tj_max_t* pOcTjMax                           ///< [in] Pointer to the TjMax.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencySetOcTjMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_tj_max_t*>( pOcTjMax ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::SetOcTjMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of frequency domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FrequencyGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFrequency** ppFrequency                   ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_freq_handle_t> hFrequency;
        hFrequency.resize( ( ppFrequency ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFrequencyGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hFrequency.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::FrequencyGet" );

        for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
            ppFrequency[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
                ppFrequency[ i ] = new SysmanFrequency( reinterpret_cast<sysman_freq_handle_t>( hFrequency[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
            {
                delete ppFrequency[ i ];
                ppFrequency[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::FrequencyGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency properties - available frequencies
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetProperties(
        freq_properties_t* pProperties                  ///< [in] The frequency properties for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetProperties(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetRange(
        freq_range_t* pLimits                           ///< [in] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetRange(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set frequency range between which the hardware can operate.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::SetRange(
        const freq_range_t* pLimits                     ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencySetRange(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<const zet_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::SetRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency state - frequency request, actual frequency, TDP
    ///        limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetState(
        freq_state_t* pState                            ///< [in] Frequency state for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetState(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency throttle time
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetThrottleTime(
        freq_throttle_time_t* pThrottleTime             ///< [in] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetThrottleTime(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_throttle_time_t*>( pThrottleTime ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFrequency::GetThrottleTime" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of engine groups
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::EngineGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanEngine** ppEngine                         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_engine_handle_t> hEngine;
        hEngine.resize( ( ppEngine ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanEngineGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hEngine.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::EngineGet" );

        for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
            ppEngine[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
                ppEngine[ i ] = new SysmanEngine( reinterpret_cast<sysman_engine_handle_t>( hEngine[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
            {
                delete ppEngine[ i ];
                ppEngine[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::EngineGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get engine group properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEngine::GetProperties(
        engine_properties_t* pProperties                ///< [in] The properties for the specified engine group.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEngineGetProperties(
            reinterpret_cast<zet_sysman_engine_handle_t>( getHandle() ),
            reinterpret_cast<zet_engine_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanEngine::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the activity stats for an engine group
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEngine::GetActivity(
        engine_stats_t* pStats                          ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEngineGetActivity(
            reinterpret_cast<zet_sysman_engine_handle_t>( getHandle() ),
            reinterpret_cast<zet_engine_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanEngine::GetActivity" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of standby controls
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::StandbyGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanStandby** ppStandby                       ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_standby_handle_t> hStandby;
        hStandby.resize( ( ppStandby ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanStandbyGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hStandby.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::StandbyGet" );

        for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
            ppStandby[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
                ppStandby[ i ] = new SysmanStandby( reinterpret_cast<sysman_standby_handle_t>( hStandby[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
            {
                delete ppStandby[ i ];
                ppStandby[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::StandbyGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get standby hardware component properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanStandby::GetProperties(
        standby_properties_t* pProperties               ///< [in] Will contain the standby hardware properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanStandbyGetProperties(
            reinterpret_cast<zet_sysman_standby_handle_t>( getHandle() ),
            reinterpret_cast<zet_standby_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanStandby::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanStandby::GetMode(
        standby_promo_mode_t* pMode                     ///< [in] Will contain the current standby mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanStandbyGetMode(
            reinterpret_cast<zet_sysman_standby_handle_t>( getHandle() ),
            reinterpret_cast<zet_standby_promo_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanStandby::GetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanStandby::SetMode(
        standby_promo_mode_t mode                       ///< [in] New standby mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanStandbySetMode(
            reinterpret_cast<zet_sysman_standby_handle_t>( getHandle() ),
            static_cast<zet_standby_promo_mode_t>( mode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanStandby::SetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of firmwares
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FirmwareGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFirmware** ppFirmware                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_firmware_handle_t> hFirmware;
        hFirmware.resize( ( ppFirmware ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFirmwareGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hFirmware.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::FirmwareGet" );

        for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
            ppFirmware[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
                ppFirmware[ i ] = new SysmanFirmware( reinterpret_cast<sysman_firmware_handle_t>( hFirmware[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
            {
                delete ppFirmware[ i ];
                ppFirmware[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::FirmwareGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFirmware::GetProperties(
        firmware_properties_t* pProperties              ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFirmwareGetProperties(
            reinterpret_cast<zet_sysman_firmware_handle_t>( getHandle() ),
            reinterpret_cast<zet_firmware_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFirmware::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware checksum
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFirmware::GetChecksum(
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFirmwareGetChecksum(
            reinterpret_cast<zet_sysman_firmware_handle_t>( getHandle() ),
            pChecksum ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFirmware::GetChecksum" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Flash a new firmware image
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFirmware::Flash(
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFirmwareFlash(
            reinterpret_cast<zet_sysman_firmware_handle_t>( getHandle() ),
            pImage,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFirmware::Flash" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of memory modules
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::MemoryGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanMemory** ppMemory                         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_mem_handle_t> hMemory;
        hMemory.resize( ( ppMemory ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanMemoryGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hMemory.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::MemoryGet" );

        for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
            ppMemory[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
                ppMemory[ i ] = new SysmanMemory( reinterpret_cast<sysman_mem_handle_t>( hMemory[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
            {
                delete ppMemory[ i ];
                ppMemory[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::MemoryGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanMemory::GetProperties(
        mem_properties_t* pProperties                   ///< [in] Will contain memory properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanMemoryGetProperties(
            reinterpret_cast<zet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<zet_mem_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanMemory::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory bandwidth
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanMemory::GetBandwidth(
        mem_bandwidth_t* pBandwidth                     ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanMemoryGetBandwidth(
            reinterpret_cast<zet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<zet_mem_bandwidth_t*>( pBandwidth ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanMemory::GetBandwidth" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanMemory::GetAllocated(
        mem_alloc_t* pAllocated                         ///< [in] Will contain the current allocated memory.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanMemoryGetAllocated(
            reinterpret_cast<zet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<zet_mem_alloc_t*>( pAllocated ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanMemory::GetAllocated" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of Fabric ports in a device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FabricPortGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFabricPort** ppPort                       ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_fabric_port_handle_t> hPort;
        hPort.resize( ( ppPort ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFabricPortGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hPort.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::FabricPortGet" );

        for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            ppPort[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
                ppPort[ i ] = new SysmanFabricPort( reinterpret_cast<sysman_fabric_port_handle_t>( hPort[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            {
                delete ppPort[ i ];
                ppPort[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::FabricPortGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetProperties(
        fabric_port_properties_t* pProperties           ///< [in] Will contain properties of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetProperties(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFabricPort::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port link type
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetLinkType(
        ze::bool_t verbose,                             ///< [in] Set to true to get a more detailed report.
        fabric_link_type_t* pLinkType                   ///< [in] Will contain details about the link attached to the Fabric port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetLinkType(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( verbose ),
            reinterpret_cast<zet_fabric_link_type_t*>( pLinkType ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFabricPort::GetLinkType" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetConfig(
        fabric_port_config_t* pConfig                   ///< [in] Will contain configuration of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetConfig(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFabricPort::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set Fabric port configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::SetConfig(
        fabric_port_config_t* pConfig                   ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortSetConfig(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFabricPort::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetState(
        fabric_port_state_t* pState                     ///< [in] Will contain the current state of the Fabric Port
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetState(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFabricPort::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port throughput
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetThroughput(
        fabric_port_throughput_t* pThroughput           ///< [in] Will contain the Fabric port throughput counters and maximum
                                                        ///< bandwidth.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetThroughput(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_throughput_t*>( pThroughput ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFabricPort::GetThroughput" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of temperature sensors
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::TemperatureGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanTemperature** ppTemperature               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_temp_handle_t> hTemperature;
        hTemperature.resize( ( ppTemperature ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanTemperatureGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hTemperature.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::TemperatureGet" );

        for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
            ppTemperature[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
                ppTemperature[ i ] = new SysmanTemperature( reinterpret_cast<sysman_temp_handle_t>( hTemperature[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
            {
                delete ppTemperature[ i ];
                ppTemperature[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::TemperatureGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperature sensor properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanTemperature::GetProperties(
        temp_properties_t* pProperties                  ///< [in] Will contain the temperature sensor properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanTemperatureGetProperties(
            reinterpret_cast<zet_sysman_temp_handle_t>( getHandle() ),
            reinterpret_cast<zet_temp_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanTemperature::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the temperature from a specified sensor
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanTemperature::Read(
        uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanTemperatureRead(
            reinterpret_cast<zet_sysman_temp_handle_t>( getHandle() ),
            pTemperature ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanTemperature::Read" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power supplies
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PsuGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanPsu** ppPsu                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_psu_handle_t> hPsu;
        hPsu.resize( ( ppPsu ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanPsuGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hPsu.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::PsuGet" );

        for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
            ppPsu[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
                ppPsu[ i ] = new SysmanPsu( reinterpret_cast<sysman_psu_handle_t>( hPsu[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
            {
                delete ppPsu[ i ];
                ppPsu[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::PsuGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power supply properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPsu::GetProperties(
        psu_properties_t* pProperties                   ///< [in] Will contain the properties of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPsuGetProperties(
            reinterpret_cast<zet_sysman_psu_handle_t>( getHandle() ),
            reinterpret_cast<zet_psu_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPsu::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current power supply state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPsu::GetState(
        psu_state_t* pState                             ///< [in] Will contain the current state of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPsuGetState(
            reinterpret_cast<zet_sysman_psu_handle_t>( getHandle() ),
            reinterpret_cast<zet_psu_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanPsu::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of fans
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FanGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFan** ppFan                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_fan_handle_t> hFan;
        hFan.resize( ( ppFan ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFanGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hFan.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::FanGet" );

        for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
            ppFan[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
                ppFan[ i ] = new SysmanFan( reinterpret_cast<sysman_fan_handle_t>( hFan[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
            {
                delete ppFan[ i ];
                ppFan[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::FanGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::GetProperties(
        fan_properties_t* pProperties                   ///< [in] Will contain the properties of the fan.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanGetProperties(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<zet_fan_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFan::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current fan configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::GetConfig(
        fan_config_t* pConfig                           ///< [in] Will contain the current configuration of the fan.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanGetConfig(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<zet_fan_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFan::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::SetConfig(
        const fan_config_t* pConfig                     ///< [in] New fan configuration.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanSetConfig(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<const zet_fan_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFan::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a fan - current mode and speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::GetState(
        fan_speed_units_t units,                        ///< [in] The units in which the fan speed should be returned.
        fan_state_t* pState                             ///< [in] Will contain the current state of the fan.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanGetState(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            static_cast<zet_fan_speed_units_t>( units ),
            reinterpret_cast<zet_fan_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanFan::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of LEDs
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::LedGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanLed** ppLed                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_led_handle_t> hLed;
        hLed.resize( ( ppLed ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanLedGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hLed.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::LedGet" );

        for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
            ppLed[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
                ppLed[ i ] = new SysmanLed( reinterpret_cast<sysman_led_handle_t>( hLed[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
            {
                delete ppLed[ i ];
                ppLed[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::LedGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get LED properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanLed::GetProperties(
        led_properties_t* pProperties                   ///< [in] Will contain the properties of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanLedGetProperties(
            reinterpret_cast<zet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<zet_led_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanLed::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a LED - on/off, color
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanLed::GetState(
        led_state_t* pState                             ///< [in] Will contain the current state of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanLedGetState(
            reinterpret_cast<zet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<zet_led_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanLed::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set state of a LED - on/off, color
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanLed::SetState(
        const led_state_t* pState                       ///< [in] New state of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanLedSetState(
            reinterpret_cast<zet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<const zet_led_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanLed::SetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of RAS error sets
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::RasGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanRas** ppRas                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_ras_handle_t> hRas;
        hRas.resize( ( ppRas ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanRasGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hRas.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::RasGet" );

        for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
            ppRas[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
                ppRas[ i ] = new SysmanRas( reinterpret_cast<sysman_ras_handle_t>( hRas[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
            {
                delete ppRas[ i ];
                ppRas[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::RasGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get RAS properties of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanRas::GetProperties(
        ras_properties_t* pProperties                   ///< [in] Structure describing RAS properties
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanRasGetProperties(
            reinterpret_cast<zet_sysman_ras_handle_t>( getHandle() ),
            reinterpret_cast<zet_ras_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanRas::GetProperties" );
    }

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
    /// @throws result_t
    void __zecall
    SysmanRas::GetErrors(
        ze::bool_t clear,                               ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
        ras_details_t* pDetails                         ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanRasGetErrors(
            reinterpret_cast<zet_sysman_ras_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( clear ),
            pTotalErrors,
            reinterpret_cast<zet_ras_details_t*>( pDetails ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanRas::GetErrors" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get event properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::EventsGetProperties(
        event_properties_t* pProperties                 ///< [in] Structure describing event properties
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEventsGetProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_event_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::EventsGetProperties" );
    }

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
    /// @throws result_t
    void __zecall
    Sysman::EventsRegister(
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be registered.
        event_request_t* pEvents                        ///< [in][optional] Events to register.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEventsRegister(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<zet_event_request_t*>( pEvents ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::EventsRegister" );
    }

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
    /// @throws result_t
    void __zecall
    Sysman::EventsUnregister(
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be unregistered.
        event_request_t* pEvents                        ///< [in][optional] Events to unregister.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEventsUnregister(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<zet_event_request_t*>( pEvents ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::EventsUnregister" );
    }

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
    /// @throws result_t
    void __zecall
    Sysman::EventsListen(
        Sysman* pSysman,                                ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                        ///< device for which the application has registered to receive
                                                        ///< notifications.
        ze::bool_t clear,                               ///< [in] Clear the event status.
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                        ///< check status and return immediately. Set to ::ZET_EVENT_WAIT_INFINITE
                                                        ///< to block until events arrive.
        uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::zet_sysman_event_type_t) that have been
                                                        ///< triggered.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEventsListen(
            reinterpret_cast<zet_sysman_handle_t>( pSysman->getHandle() ),
            static_cast<ze_bool_t>( clear ),
            timeout,
            pEvents ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::EventsListen" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of diagnostics test suites
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DiagnosticsGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanDiagnostics** ppDiagnostics               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_diag_handle_t> hDiagnostics;
        hDiagnostics.resize( ( ppDiagnostics ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanDiagnosticsGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hDiagnostics.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Sysman::DiagnosticsGet" );

        for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
            ppDiagnostics[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
                ppDiagnostics[ i ] = new SysmanDiagnostics( reinterpret_cast<sysman_diag_handle_t>( hDiagnostics[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
            {
                delete ppDiagnostics[ i ];
                ppDiagnostics[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Sysman::DiagnosticsGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties of a diagnostics test suite
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanDiagnostics::GetProperties(
        diag_properties_t* pProperties                  ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDiagnosticsGetProperties(
            reinterpret_cast<zet_sysman_diag_handle_t>( getHandle() ),
            reinterpret_cast<zet_diag_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanDiagnostics::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Run a diagnostics test suite, either all tests or a subset of tests.
    /// 
    /// @details
    ///     - This function will block until the diagnostics have completed.
    /// 
    /// @throws result_t
    void __zecall
    SysmanDiagnostics::RunTests(
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        diag_result_t* pResult                          ///< [in] The result of the diagnostics
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDiagnosticsRunTests(
            reinterpret_cast<zet_sysman_diag_handle_t>( getHandle() ),
            start,
            end,
            reinterpret_cast<zet_diag_result_t*>( pResult ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::SysmanDiagnostics::RunTests" );
    }

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::version_t::CURRENT:
            str = "Sysman::version_t::CURRENT";
            break;

        default:
            str = "Sysman::version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::data_type_t to std::string
    std::string to_string( const Sysman::data_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::data_type_t::DATA_INT8:
            str = "Sysman::data_type_t::DATA_INT8";
            break;

        case Sysman::data_type_t::DATA_INT16:
            str = "Sysman::data_type_t::DATA_INT16";
            break;

        case Sysman::data_type_t::DATA_INT32:
            str = "Sysman::data_type_t::DATA_INT32";
            break;

        case Sysman::data_type_t::DATA_INT64:
            str = "Sysman::data_type_t::DATA_INT64";
            break;

        case Sysman::data_type_t::DATA_UINT8:
            str = "Sysman::data_type_t::DATA_UINT8";
            break;

        case Sysman::data_type_t::DATA_UINT16:
            str = "Sysman::data_type_t::DATA_UINT16";
            break;

        case Sysman::data_type_t::DATA_UINT32:
            str = "Sysman::data_type_t::DATA_UINT32";
            break;

        case Sysman::data_type_t::DATA_UINT64:
            str = "Sysman::data_type_t::DATA_UINT64";
            break;

        case Sysman::data_type_t::DATA_FLOAT:
            str = "Sysman::data_type_t::DATA_FLOAT";
            break;

        case Sysman::data_type_t::DATA_DOUBLE:
            str = "Sysman::data_type_t::DATA_DOUBLE";
            break;

        case Sysman::data_type_t::DATA_STRING:
            str = "Sysman::data_type_t::DATA_STRING";
            break;

        default:
            str = "Sysman::data_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::operation_type_t to std::string
    std::string to_string( const Sysman::operation_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::operation_type_t::SET:
            str = "Sysman::operation_type_t::SET";
            break;

        case Sysman::operation_type_t::GET:
            str = "Sysman::operation_type_t::GET";
            break;

        case Sysman::operation_type_t::REGISTER_EVENT:
            str = "Sysman::operation_type_t::REGISTER_EVENT";
            break;

        default:
            str = "Sysman::operation_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::domain_t to std::string
    std::string to_string( const Sysman::domain_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::domain_t::GPU:
            str = "Sysman::domain_t::GPU";
            break;

        case Sysman::domain_t::MEMORY:
            str = "Sysman::domain_t::MEMORY";
            break;

        default:
            str = "Sysman::domain_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_type_t to std::string
    std::string to_string( const Sysman::device_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::device_type_t::INTEGRATED:
            str = "Sysman::device_type_t::INTEGRATED";
            break;

        case Sysman::device_type_t::DISCRETE:
            str = "Sysman::device_type_t::DISCRETE";
            break;

        default:
            str = "Sysman::device_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_mode_t to std::string
    std::string to_string( const Sysman::sched_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::sched_mode_t::TIMEOUT:
            str = "Sysman::sched_mode_t::TIMEOUT";
            break;

        case Sysman::sched_mode_t::TIMESLICE:
            str = "Sysman::sched_mode_t::TIMESLICE";
            break;

        case Sysman::sched_mode_t::EXCLUSIVE:
            str = "Sysman::sched_mode_t::EXCLUSIVE";
            break;

        case Sysman::sched_mode_t::COMPUTE_UNIT_DEBUG:
            str = "Sysman::sched_mode_t::COMPUTE_UNIT_DEBUG";
            break;

        default:
            str = "Sysman::sched_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_type_t to std::string
    std::string to_string( const Sysman::pci_bar_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::pci_bar_type_t::CONFIG:
            str = "Sysman::pci_bar_type_t::CONFIG";
            break;

        case Sysman::pci_bar_type_t::MMIO:
            str = "Sysman::pci_bar_type_t::MMIO";
            break;

        case Sysman::pci_bar_type_t::VRAM:
            str = "Sysman::pci_bar_type_t::VRAM";
            break;

        case Sysman::pci_bar_type_t::ROM:
            str = "Sysman::pci_bar_type_t::ROM";
            break;

        case Sysman::pci_bar_type_t::VGA_IO:
            str = "Sysman::pci_bar_type_t::VGA_IO";
            break;

        case Sysman::pci_bar_type_t::VGA_MEM:
            str = "Sysman::pci_bar_type_t::VGA_MEM";
            break;

        case Sysman::pci_bar_type_t::INDIRECT_IO:
            str = "Sysman::pci_bar_type_t::INDIRECT_IO";
            break;

        case Sysman::pci_bar_type_t::INDIRECT_MEM:
            str = "Sysman::pci_bar_type_t::INDIRECT_MEM";
            break;

        case Sysman::pci_bar_type_t::OTHER:
            str = "Sysman::pci_bar_type_t::OTHER";
            break;

        default:
            str = "Sysman::pci_bar_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::event_type_t::FREQ_THROTTLED:
            str = "Sysman::event_type_t::FREQ_THROTTLED";
            break;

        case Sysman::event_type_t::ENERGY_THRESHOLD_CROSSED:
            str = "Sysman::event_type_t::ENERGY_THRESHOLD_CROSSED";
            break;

        case Sysman::event_type_t::MAX_TEMPERATURE:
            str = "Sysman::event_type_t::MAX_TEMPERATURE";
            break;

        case Sysman::event_type_t::RAS_ERRORS:
            str = "Sysman::event_type_t::RAS_ERRORS";
            break;

        case Sysman::event_type_t::NUM:
            str = "Sysman::event_type_t::NUM";
            break;

        default:
            str = "Sysman::event_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::properties_t to std::string
    std::string to_string( const Sysman::properties_t val )
    {
        std::string str;
        
        str += "Sysman::properties_t::core : ";
        str += to_string(val.core);
        str += "\n";
        
        str += "Sysman::properties_t::numSubdevices : ";
        str += std::to_string(val.numSubdevices);
        str += "\n";
        
        str += "Sysman::properties_t::deviceType : ";
        str += to_string(val.deviceType);
        str += "\n";
        
        str += "Sysman::properties_t::serialNumber : ";
        {
            std::string tmp;
            for( auto& entry : val.serialNumber )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::boardNumber : ";
        {
            std::string tmp;
            for( auto& entry : val.boardNumber )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::brandName : ";
        {
            std::string tmp;
            for( auto& entry : val.brandName )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::modelName : ";
        {
            std::string tmp;
            for( auto& entry : val.modelName )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::vendorName : ";
        {
            std::string tmp;
            for( auto& entry : val.vendorName )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::driverVersion : ";
        {
            std::string tmp;
            for( auto& entry : val.driverVersion )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeout_properties_t to std::string
    std::string to_string( const Sysman::sched_timeout_properties_t val )
    {
        std::string str;
        
        str += "Sysman::sched_timeout_properties_t::watchdogTimeout : ";
        str += std::to_string(val.watchdogTimeout);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeslice_properties_t to std::string
    std::string to_string( const Sysman::sched_timeslice_properties_t val )
    {
        std::string str;
        
        str += "Sysman::sched_timeslice_properties_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";
        
        str += "Sysman::sched_timeslice_properties_t::yieldTimeout : ";
        str += std::to_string(val.yieldTimeout);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_address_t to std::string
    std::string to_string( const Sysman::pci_address_t val )
    {
        std::string str;
        
        str += "Sysman::pci_address_t::domain : ";
        str += std::to_string(val.domain);
        str += "\n";
        
        str += "Sysman::pci_address_t::bus : ";
        str += std::to_string(val.bus);
        str += "\n";
        
        str += "Sysman::pci_address_t::device : ";
        str += std::to_string(val.device);
        str += "\n";
        
        str += "Sysman::pci_address_t::function : ";
        str += std::to_string(val.function);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_speed_t to std::string
    std::string to_string( const Sysman::pci_speed_t val )
    {
        std::string str;
        
        str += "Sysman::pci_speed_t::gen : ";
        str += std::to_string(val.gen);
        str += "\n";
        
        str += "Sysman::pci_speed_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "Sysman::pci_speed_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";
        
        str += "Sysman::pci_speed_t::maxPacketSize : ";
        str += std::to_string(val.maxPacketSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_properties_t to std::string
    std::string to_string( const Sysman::pci_properties_t val )
    {
        std::string str;
        
        str += "Sysman::pci_properties_t::address : ";
        str += to_string(val.address);
        str += "\n";
        
        str += "Sysman::pci_properties_t::numBars : ";
        str += std::to_string(val.numBars);
        str += "\n";
        
        str += "Sysman::pci_properties_t::maxSpeed : ";
        str += to_string(val.maxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_state_t to std::string
    std::string to_string( const Sysman::pci_state_t val )
    {
        std::string str;
        
        str += "Sysman::pci_state_t::speed : ";
        str += to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_properties_t to std::string
    std::string to_string( const Sysman::pci_bar_properties_t val )
    {
        std::string str;
        
        str += "Sysman::pci_bar_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::pci_bar_properties_t::base : ";
        str += std::to_string(val.base);
        str += "\n";
        
        str += "Sysman::pci_bar_properties_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_throughput_t to std::string
    std::string to_string( const Sysman::pci_throughput_t val )
    {
        std::string str;
        
        str += "Sysman::pci_throughput_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "Sysman::pci_throughput_t::rxCounter : ";
        str += std::to_string(val.rxCounter);
        str += "\n";
        
        str += "Sysman::pci_throughput_t::txCounter : ";
        str += std::to_string(val.txCounter);
        str += "\n";
        
        str += "Sysman::pci_throughput_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_stats_t to std::string
    std::string to_string( const Sysman::pci_stats_t val )
    {
        std::string str;
        
        str += "Sysman::pci_stats_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "Sysman::pci_stats_t::replayCounter : ";
        str += std::to_string(val.replayCounter);
        str += "\n";
        
        str += "Sysman::pci_stats_t::packetCounter : ";
        str += std::to_string(val.packetCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_properties_t to std::string
    std::string to_string( const Sysman::event_properties_t val )
    {
        std::string str;
        
        str += "Sysman::event_properties_t::supportedEvents : ";
        {
            std::string tmp;
            for( auto& entry : val.supportedEvents )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_request_t to std::string
    std::string to_string( const Sysman::event_request_t val )
    {
        std::string str;
        
        str += "Sysman::event_request_t::event : ";
        str += to_string(val.event);
        str += "\n";
        
        str += "Sysman::event_request_t::threshold : ";
        str += std::to_string(val.threshold);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_properties_t to std::string
    std::string to_string( const SysmanPower::power_properties_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::maxLimit : ";
        str += std::to_string(val.maxLimit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_energy_counter_t to std::string
    std::string to_string( const SysmanPower::power_energy_counter_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_energy_counter_t::energy : ";
        str += std::to_string(val.energy);
        str += "\n";
        
        str += "SysmanPower::power_energy_counter_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_energy_threshold_t to std::string
    std::string to_string( const SysmanPower::power_energy_threshold_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_energy_threshold_t::energy : ";
        str += std::to_string(val.energy);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_sustained_limit_t to std::string
    std::string to_string( const SysmanPower::power_sustained_limit_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_sustained_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanPower::power_sustained_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";
        
        str += "SysmanPower::power_sustained_limit_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_burst_limit_t to std::string
    std::string to_string( const SysmanPower::power_burst_limit_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_burst_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanPower::power_burst_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_peak_limit_t to std::string
    std::string to_string( const SysmanPower::power_peak_limit_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_peak_limit_t::powerAC : ";
        str += std::to_string(val.powerAC);
        str += "\n";
        
        str += "SysmanPower::power_peak_limit_t::powerDC : ";
        str += std::to_string(val.powerDC);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_mode_t to std::string
    std::string to_string( const SysmanFrequency::oc_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFrequency::oc_mode_t::OVERCLOCKING_INTERPOLATIVE_MODE:
            str = "SysmanFrequency::oc_mode_t::OVERCLOCKING_INTERPOLATIVE_MODE";
            break;

        case SysmanFrequency::oc_mode_t::OVERCLOCKING_OVERRIDE_MODE:
            str = "SysmanFrequency::oc_mode_t::OVERCLOCKING_OVERRIDE_MODE";
            break;

        default:
            str = "SysmanFrequency::oc_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_error_type_t to std::string
    std::string to_string( const SysmanFrequency::oc_error_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_LOCKED:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_LOCKED";
            break;

        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_DDOMAIN_SERVICE_NOT_SUPPORTED:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_DDOMAIN_SERVICE_NOT_SUPPORTED";
            break;

        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_RATIO_EXCEEDS_MAX:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_RATIO_EXCEEDS_MAX";
            break;

        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_VOLTAGE_EXCEEDS_MAX:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_VOLTAGE_EXCEEDS_MAX";
            break;

        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_NOT_SUPPORTED:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_NOT_SUPPORTED";
            break;

        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_INVALID_VR_ADDRESS:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_INVALID_VR_ADDRESS";
            break;

        case SysmanFrequency::oc_error_type_t::OOVERCLOCKING_INVALID_ICCMAX:
            str = "SysmanFrequency::oc_error_type_t::OOVERCLOCKING_INVALID_ICCMAX";
            break;

        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_VOLTAGE_OVERRIDE_DISABLED:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_VOLTAGE_OVERRIDE_DISABLED";
            break;

        case SysmanFrequency::oc_error_type_t::OVERCLOCKING_INVALID_COMMAND:
            str = "SysmanFrequency::oc_error_type_t::OVERCLOCKING_INVALID_COMMAND";
            break;

        default:
            str = "SysmanFrequency::oc_error_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_reasons_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_reasons_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::AVE_PWR_CAP) & bits )
            str += "AVE_PWR_CAP | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::BURST_PWR_CAP) & bits )
            str += "BURST_PWR_CAP | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::CURRENT_LIMIT) & bits )
            str += "CURRENT_LIMIT | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::THERMAL_LIMIT) & bits )
            str += "THERMAL_LIMIT | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::PSU_ALERT) & bits )
            str += "PSU_ALERT | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::SW_RANGE) & bits )
            str += "SW_RANGE | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::HW_RANGE) & bits )
            str += "HW_RANGE | ";

        return ( str.size() > 3 ) 
            ? "SysmanFrequency::freq_throttle_reasons_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "SysmanFrequency::freq_throttle_reasons_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_capabilities_t to std::string
    std::string to_string( const SysmanFrequency::oc_capabilities_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::oc_capabilities_t::MaxOcFrequencyLimit : ";
        str += std::to_string(val.MaxOcFrequencyLimit);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::MaxFactoryDefaultFrequency : ";
        str += std::to_string(val.MaxFactoryDefaultFrequency);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::MaxFactoryDefaultVoltage : ";
        str += std::to_string(val.MaxFactoryDefaultVoltage);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::TjMaxSupported : ";
        str += std::to_string(val.TjMaxSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::IccMaxSupported : ";
        str += std::to_string(val.IccMaxSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::FrequencyOcSupported : ";
        str += std::to_string(val.FrequencyOcSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::VoltageOverrideSupported : ";
        str += std::to_string(val.VoltageOverrideSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::VoltageOffsetSupported : ";
        str += std::to_string(val.VoltageOffsetSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::HighVoltModeCapable : ";
        str += std::to_string(val.HighVoltModeCapable);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::HighVoltModeEnabled : ";
        str += std::to_string(val.HighVoltModeEnabled);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_configuration_t to std::string
    std::string to_string( const SysmanFrequency::oc_configuration_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::oc_configuration_t::OcFrequency : ";
        str += std::to_string(val.OcFrequency);
        str += "\n";
        
        str += "SysmanFrequency::oc_configuration_t::TargetVoltage : ";
        str += std::to_string(val.TargetVoltage);
        str += "\n";
        
        str += "SysmanFrequency::oc_configuration_t::TargetMode : ";
        str += to_string(val.TargetMode);
        str += "\n";
        
        str += "SysmanFrequency::oc_configuration_t::VoltageOffset : ";
        str += std::to_string(val.VoltageOffset);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_icc_max_t to std::string
    std::string to_string( const SysmanFrequency::oc_icc_max_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::oc_icc_max_t::IccMax : ";
        str += std::to_string(val.IccMax);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_tj_max_t to std::string
    std::string to_string( const SysmanFrequency::oc_tj_max_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::oc_tj_max_t::TjMax : ";
        str += std::to_string(val.TjMax);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_properties_t to std::string
    std::string to_string( const SysmanFrequency::freq_properties_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::canOverclock : ";
        str += std::to_string(val.canOverclock);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::max : ";
        str += std::to_string(val.max);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::step : ";
        str += std::to_string(val.step);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::pClocks : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pClocks);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_range_t to std::string
    std::string to_string( const SysmanFrequency::freq_range_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_range_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "SysmanFrequency::freq_range_t::max : ";
        str += std::to_string(val.max);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_state_t to std::string
    std::string to_string( const SysmanFrequency::freq_state_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_state_t::request : ";
        str += std::to_string(val.request);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::tdp : ";
        str += std::to_string(val.tdp);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::efficient : ";
        str += std::to_string(val.efficient);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::actual : ";
        str += std::to_string(val.actual);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::throttleReasons : ";
        str += std::to_string(val.throttleReasons);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_time_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_time_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_throttle_time_t::throttleTime : ";
        str += std::to_string(val.throttleTime);
        str += "\n";
        
        str += "SysmanFrequency::freq_throttle_time_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_group_t to std::string
    std::string to_string( const SysmanEngine::engine_group_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanEngine::engine_group_t::ALL:
            str = "SysmanEngine::engine_group_t::ALL";
            break;

        case SysmanEngine::engine_group_t::COMPUTE_ALL:
            str = "SysmanEngine::engine_group_t::COMPUTE_ALL";
            break;

        case SysmanEngine::engine_group_t::MEDIA_ALL:
            str = "SysmanEngine::engine_group_t::MEDIA_ALL";
            break;

        case SysmanEngine::engine_group_t::COPY_ALL:
            str = "SysmanEngine::engine_group_t::COPY_ALL";
            break;

        default:
            str = "SysmanEngine::engine_group_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_properties_t to std::string
    std::string to_string( const SysmanEngine::engine_properties_t val )
    {
        std::string str;
        
        str += "SysmanEngine::engine_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanEngine::engine_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanEngine::engine_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_stats_t to std::string
    std::string to_string( const SysmanEngine::engine_stats_t val )
    {
        std::string str;
        
        str += "SysmanEngine::engine_stats_t::activeTime : ";
        str += std::to_string(val.activeTime);
        str += "\n";
        
        str += "SysmanEngine::engine_stats_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_type_t to std::string
    std::string to_string( const SysmanStandby::standby_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanStandby::standby_type_t::GLOBAL:
            str = "SysmanStandby::standby_type_t::GLOBAL";
            break;

        default:
            str = "SysmanStandby::standby_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_promo_mode_t to std::string
    std::string to_string( const SysmanStandby::standby_promo_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanStandby::standby_promo_mode_t::DEFAULT:
            str = "SysmanStandby::standby_promo_mode_t::DEFAULT";
            break;

        case SysmanStandby::standby_promo_mode_t::NEVER:
            str = "SysmanStandby::standby_promo_mode_t::NEVER";
            break;

        default:
            str = "SysmanStandby::standby_promo_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_properties_t to std::string
    std::string to_string( const SysmanStandby::standby_properties_t val )
    {
        std::string str;
        
        str += "SysmanStandby::standby_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanStandby::standby_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanStandby::standby_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFirmware::firmware_properties_t to std::string
    std::string to_string( const SysmanFirmware::firmware_properties_t val )
    {
        std::string str;
        
        str += "SysmanFirmware::firmware_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::name : ";
        {
            std::string tmp;
            for( auto& entry : val.name )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::version : ";
        {
            std::string tmp;
            for( auto& entry : val.version )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_type_t to std::string
    std::string to_string( const SysmanMemory::mem_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanMemory::mem_type_t::HBM:
            str = "SysmanMemory::mem_type_t::HBM";
            break;

        case SysmanMemory::mem_type_t::DDR:
            str = "SysmanMemory::mem_type_t::DDR";
            break;

        case SysmanMemory::mem_type_t::SRAM:
            str = "SysmanMemory::mem_type_t::SRAM";
            break;

        case SysmanMemory::mem_type_t::L1:
            str = "SysmanMemory::mem_type_t::L1";
            break;

        case SysmanMemory::mem_type_t::L3:
            str = "SysmanMemory::mem_type_t::L3";
            break;

        case SysmanMemory::mem_type_t::GRF:
            str = "SysmanMemory::mem_type_t::GRF";
            break;

        case SysmanMemory::mem_type_t::SLM:
            str = "SysmanMemory::mem_type_t::SLM";
            break;

        default:
            str = "SysmanMemory::mem_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_properties_t to std::string
    std::string to_string( const SysmanMemory::mem_properties_t val )
    {
        std::string str;
        
        str += "SysmanMemory::mem_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanMemory::mem_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanMemory::mem_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanMemory::mem_properties_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_bandwidth_t to std::string
    std::string to_string( const SysmanMemory::mem_bandwidth_t val )
    {
        std::string str;
        
        str += "SysmanMemory::mem_bandwidth_t::readCounter : ";
        str += std::to_string(val.readCounter);
        str += "\n";
        
        str += "SysmanMemory::mem_bandwidth_t::writeCounter : ";
        str += std::to_string(val.writeCounter);
        str += "\n";
        
        str += "SysmanMemory::mem_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";
        
        str += "SysmanMemory::mem_bandwidth_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_alloc_t to std::string
    std::string to_string( const SysmanMemory::mem_alloc_t val )
    {
        std::string str;
        
        str += "SysmanMemory::mem_alloc_t::allocated : ";
        str += std::to_string(val.allocated);
        str += "\n";
        
        str += "SysmanMemory::mem_alloc_t::total : ";
        str += std::to_string(val.total);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_status_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_status_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFabricPort::fabric_port_status_t::GREEN:
            str = "SysmanFabricPort::fabric_port_status_t::GREEN";
            break;

        case SysmanFabricPort::fabric_port_status_t::YELLOW:
            str = "SysmanFabricPort::fabric_port_status_t::YELLOW";
            break;

        case SysmanFabricPort::fabric_port_status_t::RED:
            str = "SysmanFabricPort::fabric_port_status_t::RED";
            break;

        case SysmanFabricPort::fabric_port_status_t::BLACK:
            str = "SysmanFabricPort::fabric_port_status_t::BLACK";
            break;

        default:
            str = "SysmanFabricPort::fabric_port_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_qual_issues_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_qual_issues_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_qual_issues_t::FEC) & bits )
            str += "FEC | ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_qual_issues_t::LTP_CRC) & bits )
            str += "LTP_CRC | ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_qual_issues_t::SPEED) & bits )
            str += "SPEED | ";

        return ( str.size() > 3 ) 
            ? "SysmanFabricPort::fabric_port_qual_issues_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "SysmanFabricPort::fabric_port_qual_issues_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_stab_issues_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_stab_issues_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_stab_issues_t::TOO_MANY_REPLAYS) & bits )
            str += "TOO_MANY_REPLAYS | ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_stab_issues_t::NO_CONNECT) & bits )
            str += "NO_CONNECT | ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_stab_issues_t::FLAPPING) & bits )
            str += "FLAPPING | ";

        return ( str.size() > 3 ) 
            ? "SysmanFabricPort::fabric_port_stab_issues_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "SysmanFabricPort::fabric_port_stab_issues_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_uuid_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_uuid_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_uuid_t::id : ";
        {
            std::string tmp;
            for( auto& entry : val.id )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_speed_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_speed_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_speed_t::bitRate : ";
        str += std::to_string(val.bitRate);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_speed_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_speed_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_properties_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_properties_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_properties_t::model : ";
        {
            std::string tmp;
            for( auto& entry : val.model )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::portUuid : ";
        str += to_string(val.portUuid);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::maxRxSpeed : ";
        str += to_string(val.maxRxSpeed);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::maxTxSpeed : ";
        str += to_string(val.maxTxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_link_type_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_link_type_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_link_type_t::desc : ";
        {
            std::string tmp;
            for( auto& entry : val.desc )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_config_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_config_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_config_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_config_t::beaconing : ";
        str += std::to_string(val.beaconing);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_state_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_state_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_state_t::status : ";
        str += to_string(val.status);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::qualityIssues : ";
        str += to_string(val.qualityIssues);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::stabilityIssues : ";
        str += to_string(val.stabilityIssues);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::rxSpeed : ";
        str += to_string(val.rxSpeed);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::txSpeed : ";
        str += to_string(val.txSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_throughput_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_throughput_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_throughput_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_throughput_t::rxCounter : ";
        str += std::to_string(val.rxCounter);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_throughput_t::txCounter : ";
        str += std::to_string(val.txCounter);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_throughput_t::rxMaxBandwidth : ";
        str += std::to_string(val.rxMaxBandwidth);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_throughput_t::txMaxBandwidth : ";
        str += std::to_string(val.txMaxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_sensors_t to std::string
    std::string to_string( const SysmanTemperature::temp_sensors_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanTemperature::temp_sensors_t::GLOBAL:
            str = "SysmanTemperature::temp_sensors_t::GLOBAL";
            break;

        case SysmanTemperature::temp_sensors_t::GPU:
            str = "SysmanTemperature::temp_sensors_t::GPU";
            break;

        case SysmanTemperature::temp_sensors_t::MEMORY:
            str = "SysmanTemperature::temp_sensors_t::MEMORY";
            break;

        default:
            str = "SysmanTemperature::temp_sensors_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_properties_t to std::string
    std::string to_string( const SysmanTemperature::temp_properties_t val )
    {
        std::string str;
        
        str += "SysmanTemperature::temp_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanTemperature::temp_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanTemperature::temp_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_voltage_status_t to std::string
    std::string to_string( const SysmanPsu::psu_voltage_status_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanPsu::psu_voltage_status_t::NORMAL:
            str = "SysmanPsu::psu_voltage_status_t::NORMAL";
            break;

        case SysmanPsu::psu_voltage_status_t::OVER:
            str = "SysmanPsu::psu_voltage_status_t::OVER";
            break;

        case SysmanPsu::psu_voltage_status_t::UNDER:
            str = "SysmanPsu::psu_voltage_status_t::UNDER";
            break;

        default:
            str = "SysmanPsu::psu_voltage_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_properties_t to std::string
    std::string to_string( const SysmanPsu::psu_properties_t val )
    {
        std::string str;
        
        str += "SysmanPsu::psu_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanPsu::psu_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanPsu::psu_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanPsu::psu_properties_t::haveFan : ";
        str += std::to_string(val.haveFan);
        str += "\n";
        
        str += "SysmanPsu::psu_properties_t::ampLimit : ";
        str += std::to_string(val.ampLimit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_state_t to std::string
    std::string to_string( const SysmanPsu::psu_state_t val )
    {
        std::string str;
        
        str += "SysmanPsu::psu_state_t::voltStatus : ";
        str += to_string(val.voltStatus);
        str += "\n";
        
        str += "SysmanPsu::psu_state_t::fanFailed : ";
        str += std::to_string(val.fanFailed);
        str += "\n";
        
        str += "SysmanPsu::psu_state_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "SysmanPsu::psu_state_t::current : ";
        str += std::to_string(val.current);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_mode_t to std::string
    std::string to_string( const SysmanFan::fan_speed_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFan::fan_speed_mode_t::DEFAULT:
            str = "SysmanFan::fan_speed_mode_t::DEFAULT";
            break;

        case SysmanFan::fan_speed_mode_t::FIXED:
            str = "SysmanFan::fan_speed_mode_t::FIXED";
            break;

        case SysmanFan::fan_speed_mode_t::TABLE:
            str = "SysmanFan::fan_speed_mode_t::TABLE";
            break;

        default:
            str = "SysmanFan::fan_speed_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_units_t to std::string
    std::string to_string( const SysmanFan::fan_speed_units_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFan::fan_speed_units_t::RPM:
            str = "SysmanFan::fan_speed_units_t::RPM";
            break;

        case SysmanFan::fan_speed_units_t::PERCENT:
            str = "SysmanFan::fan_speed_units_t::PERCENT";
            break;

        default:
            str = "SysmanFan::fan_speed_units_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_temp_speed_t to std::string
    std::string to_string( const SysmanFan::fan_temp_speed_t val )
    {
        std::string str;
        
        str += "SysmanFan::fan_temp_speed_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "SysmanFan::fan_temp_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "SysmanFan::fan_temp_speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_properties_t to std::string
    std::string to_string( const SysmanFan::fan_properties_t val )
    {
        std::string str;
        
        str += "SysmanFan::fan_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::maxSpeed : ";
        str += std::to_string(val.maxSpeed);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::maxPoints : ";
        str += std::to_string(val.maxPoints);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_config_t to std::string
    std::string to_string( const SysmanFan::fan_config_t val )
    {
        std::string str;
        
        str += "SysmanFan::fan_config_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::speedUnits : ";
        str += to_string(val.speedUnits);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::numPoints : ";
        str += std::to_string(val.numPoints);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::table : ";
        {
            std::string tmp;
            for( auto& entry : val.table )
            {
                tmp += to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_state_t to std::string
    std::string to_string( const SysmanFan::fan_state_t val )
    {
        std::string str;
        
        str += "SysmanFan::fan_state_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "SysmanFan::fan_state_t::speedUnits : ";
        str += to_string(val.speedUnits);
        str += "\n";
        
        str += "SysmanFan::fan_state_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_properties_t to std::string
    std::string to_string( const SysmanLed::led_properties_t val )
    {
        std::string str;
        
        str += "SysmanLed::led_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanLed::led_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanLed::led_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanLed::led_properties_t::haveRGB : ";
        str += std::to_string(val.haveRGB);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_state_t to std::string
    std::string to_string( const SysmanLed::led_state_t val )
    {
        std::string str;
        
        str += "SysmanLed::led_state_t::isOn : ";
        str += std::to_string(val.isOn);
        str += "\n";
        
        str += "SysmanLed::led_state_t::red : ";
        str += std::to_string(val.red);
        str += "\n";
        
        str += "SysmanLed::led_state_t::green : ";
        str += std::to_string(val.green);
        str += "\n";
        
        str += "SysmanLed::led_state_t::blue : ";
        str += std::to_string(val.blue);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_error_type_t to std::string
    std::string to_string( const SysmanRas::ras_error_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanRas::ras_error_type_t::CORRECTABLE:
            str = "SysmanRas::ras_error_type_t::CORRECTABLE";
            break;

        case SysmanRas::ras_error_type_t::UNCORRECTABLE:
            str = "SysmanRas::ras_error_type_t::UNCORRECTABLE";
            break;

        default:
            str = "SysmanRas::ras_error_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_properties_t to std::string
    std::string to_string( const SysmanRas::ras_properties_t val )
    {
        std::string str;
        
        str += "SysmanRas::ras_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanRas::ras_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanRas::ras_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanRas::ras_properties_t::supported : ";
        str += std::to_string(val.supported);
        str += "\n";
        
        str += "SysmanRas::ras_properties_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_details_t to std::string
    std::string to_string( const SysmanRas::ras_details_t val )
    {
        std::string str;
        
        str += "SysmanRas::ras_details_t::numResets : ";
        str += std::to_string(val.numResets);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numProgrammingErrors : ";
        str += std::to_string(val.numProgrammingErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numDriverErrors : ";
        str += std::to_string(val.numDriverErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numComputeErrors : ";
        str += std::to_string(val.numComputeErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numNonComputeErrors : ";
        str += std::to_string(val.numNonComputeErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numCacheErrors : ";
        str += std::to_string(val.numCacheErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numMemoryErrors : ";
        str += std::to_string(val.numMemoryErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numPciErrors : ";
        str += std::to_string(val.numPciErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numFabricErrors : ";
        str += std::to_string(val.numFabricErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numDisplayErrors : ";
        str += std::to_string(val.numDisplayErrors);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_type_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanDiagnostics::diag_type_t::SCAN:
            str = "SysmanDiagnostics::diag_type_t::SCAN";
            break;

        case SysmanDiagnostics::diag_type_t::ARRAY:
            str = "SysmanDiagnostics::diag_type_t::ARRAY";
            break;

        default:
            str = "SysmanDiagnostics::diag_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_result_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_result_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanDiagnostics::diag_result_t::NO_ERRORS:
            str = "SysmanDiagnostics::diag_result_t::NO_ERRORS";
            break;

        case SysmanDiagnostics::diag_result_t::ABORT:
            str = "SysmanDiagnostics::diag_result_t::ABORT";
            break;

        case SysmanDiagnostics::diag_result_t::FAIL_CANT_REPAIR:
            str = "SysmanDiagnostics::diag_result_t::FAIL_CANT_REPAIR";
            break;

        case SysmanDiagnostics::diag_result_t::REBOOT_FOR_REPAIR:
            str = "SysmanDiagnostics::diag_result_t::REBOOT_FOR_REPAIR";
            break;

        default:
            str = "SysmanDiagnostics::diag_result_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_test_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_test_t val )
    {
        std::string str;
        
        str += "SysmanDiagnostics::diag_test_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_test_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_properties_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_properties_t val )
    {
        std::string str;
        
        str += "SysmanDiagnostics::diag_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::numTests : ";
        str += std::to_string(val.numTests);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::pTests : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pTests);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

} // namespace zet
