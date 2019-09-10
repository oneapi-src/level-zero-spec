/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_sysman.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#include "xet_lib.h"

extern "C" {

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
    )
{
    auto pfnGet = xet_lib::context.ddiTable.Sysman.pfnGet;
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnDeviceGetProperties = xet_lib::context.ddiTable.Sysman.pfnDeviceGetProperties;
    if( nullptr == pfnDeviceGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceGetProperties( hSysman, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get optimization mode of the device
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
xe_result_t __xecall
xetSysmanDeviceGetOptimizationMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_optimization_mode_t* pMode                  ///< [in] The current optimization mode of the device.
    )
{
    auto pfnDeviceGetOptimizationMode = xet_lib::context.ddiTable.Sysman.pfnDeviceGetOptimizationMode;
    if( nullptr == pfnDeviceGetOptimizationMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceGetOptimizationMode( hSysman, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set optimization mode of the device
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDeviceSetOptimizationMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_optimization_mode_t pMode                   ///< [in] The new optimization mode of the device.
    )
{
    auto pfnDeviceSetOptimizationMode = xet_lib::context.ddiTable.Sysman.pfnDeviceSetOptimizationMode;
    if( nullptr == pfnDeviceSetOptimizationMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceSetOptimizationMode( hSysman, pMode );
}

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
    )
{
    auto pfnDeviceReset = xet_lib::context.ddiTable.Sysman.pfnDeviceReset;
    if( nullptr == pfnDeviceReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceReset( hSysman );
}

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
    )
{
    auto pfnPciGetProperties = xet_lib::context.ddiTable.Sysman.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnPciGetState = xet_lib::context.ddiTable.Sysman.pfnPciGetState;
    if( nullptr == pfnPciGetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnPciGetBarProperties = xet_lib::context.ddiTable.Sysman.pfnPciGetBarProperties;
    if( nullptr == pfnPciGetBarProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnPciGetThroughput = xet_lib::context.ddiTable.Sysman.pfnPciGetThroughput;
    if( nullptr == pfnPciGetThroughput )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnPciGetStats = xet_lib::context.ddiTable.Sysman.pfnPciGetStats;
    if( nullptr == pfnPciGetStats )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnPowerGet = xet_lib::context.ddiTable.Sysman.pfnPowerGet;
    if( nullptr == pfnPowerGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanPower.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetEnergyCounter = xet_lib::context.ddiTable.SysmanPower.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetEnergyThreshold = xet_lib::context.ddiTable.SysmanPower.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnSetEnergyThreshold = xet_lib::context.ddiTable.SysmanPower.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetLimits = xet_lib::context.ddiTable.SysmanPower.pfnGetLimits;
    if( nullptr == pfnGetLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnSetLimits = xet_lib::context.ddiTable.SysmanPower.pfnSetLimits;
    if( nullptr == pfnSetLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
}

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
    )
{
    auto pfnFrequencyGet = xet_lib::context.ddiTable.Sysman.pfnFrequencyGet;
    if( nullptr == pfnFrequencyGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanFrequency.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetRange = xet_lib::context.ddiTable.SysmanFrequency.pfnGetRange;
    if( nullptr == pfnGetRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnSetRange = xet_lib::context.ddiTable.SysmanFrequency.pfnSetRange;
    if( nullptr == pfnSetRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetState = xet_lib::context.ddiTable.SysmanFrequency.pfnGetState;
    if( nullptr == pfnGetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetThrottleTime = xet_lib::context.ddiTable.SysmanFrequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnEngineGet = xet_lib::context.ddiTable.Sysman.pfnEngineGet;
    if( nullptr == pfnEngineGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanEngine.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetActivity = xet_lib::context.ddiTable.SysmanEngine.pfnGetActivity;
    if( nullptr == pfnGetActivity )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnStandbyGet = xet_lib::context.ddiTable.Sysman.pfnStandbyGet;
    if( nullptr == pfnStandbyGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanStandby.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetMode = xet_lib::context.ddiTable.SysmanStandby.pfnGetMode;
    if( nullptr == pfnGetMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnSetMode = xet_lib::context.ddiTable.SysmanStandby.pfnSetMode;
    if( nullptr == pfnSetMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnFirmwareGet = xet_lib::context.ddiTable.Sysman.pfnFirmwareGet;
    if( nullptr == pfnFirmwareGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanFirmware.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetChecksum = xet_lib::context.ddiTable.SysmanFirmware.pfnGetChecksum;
    if( nullptr == pfnGetChecksum )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnFlash = xet_lib::context.ddiTable.SysmanFirmware.pfnFlash;
    if( nullptr == pfnFlash )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnMemoryGet = xet_lib::context.ddiTable.Sysman.pfnMemoryGet;
    if( nullptr == pfnMemoryGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanMemory.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetBandwidth = xet_lib::context.ddiTable.SysmanMemory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetAllocated = xet_lib::context.ddiTable.SysmanMemory.pfnGetAllocated;
    if( nullptr == pfnGetAllocated )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAllocated( hMemory, pAllocated );
}

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
    )
{
    auto pfnLinkSwitchGet = xet_lib::context.ddiTable.Sysman.pfnLinkSwitchGet;
    if( nullptr == pfnLinkSwitchGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnLinkSwitchGet( hSysman, pCount, phSwitch );
}

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanLinkSwitch.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hSwitch, pProperties );
}

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
    )
{
    auto pfnGetState = xet_lib::context.ddiTable.SysmanLinkSwitch.pfnGetState;
    if( nullptr == pfnGetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetState( hSwitch, pState );
}

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
    )
{
    auto pfnSetState = xet_lib::context.ddiTable.SysmanLinkSwitch.pfnSetState;
    if( nullptr == pfnSetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetState( hSwitch, enable );
}

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
    )
{
    auto pfnGetPorts = xet_lib::context.ddiTable.SysmanLinkSwitch.pfnGetPorts;
    if( nullptr == pfnGetPorts )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPorts( hSysmanLinkSwitch, pCount, phPort );
}

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanLinkPort.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hPort, pProperties );
}

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
    )
{
    auto pfnGetState = xet_lib::context.ddiTable.SysmanLinkPort.pfnGetState;
    if( nullptr == pfnGetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetState( hPort, pState );
}

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
    )
{
    auto pfnGetThroughput = xet_lib::context.ddiTable.SysmanLinkPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetThroughput( hPort, pThroughput );
}

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
    )
{
    auto pfnGetStats = xet_lib::context.ddiTable.SysmanLinkPort.pfnGetStats;
    if( nullptr == pfnGetStats )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetStats( hPort, pStats );
}

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
    )
{
    auto pfnIsConnected = xet_lib::context.ddiTable.SysmanLinkPort.pfnIsConnected;
    if( nullptr == pfnIsConnected )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnIsConnected( hPort, hRemotePort, pConnected );
}

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
    )
{
    auto pfnTemperatureGet = xet_lib::context.ddiTable.Sysman.pfnTemperatureGet;
    if( nullptr == pfnTemperatureGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanTemperature.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnRead = xet_lib::context.ddiTable.SysmanTemperature.pfnRead;
    if( nullptr == pfnRead )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnPsuGet = xet_lib::context.ddiTable.Sysman.pfnPsuGet;
    if( nullptr == pfnPsuGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanPsu.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetState = xet_lib::context.ddiTable.SysmanPsu.pfnGetState;
    if( nullptr == pfnGetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnFanGet = xet_lib::context.ddiTable.Sysman.pfnFanGet;
    if( nullptr == pfnFanGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanFan.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetConfig = xet_lib::context.ddiTable.SysmanFan.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnSetConfig = xet_lib::context.ddiTable.SysmanFan.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetState = xet_lib::context.ddiTable.SysmanFan.pfnGetState;
    if( nullptr == pfnGetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnLedGet = xet_lib::context.ddiTable.Sysman.pfnLedGet;
    if( nullptr == pfnLedGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanLed.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetState = xet_lib::context.ddiTable.SysmanLed.pfnGetState;
    if( nullptr == pfnGetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnSetState = xet_lib::context.ddiTable.SysmanLed.pfnSetState;
    if( nullptr == pfnSetState )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnRasGet = xet_lib::context.ddiTable.Sysman.pfnRasGet;
    if( nullptr == pfnRasGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanRas.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetErrors = xet_lib::context.ddiTable.SysmanRas.pfnGetErrors;
    if( nullptr == pfnGetErrors )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnEventsGetProperties = xet_lib::context.ddiTable.Sysman.pfnEventsGetProperties;
    if( nullptr == pfnEventsGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnEventsRegister = xet_lib::context.ddiTable.Sysman.pfnEventsRegister;
    if( nullptr == pfnEventsRegister )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnEventsUnregister = xet_lib::context.ddiTable.Sysman.pfnEventsUnregister;
    if( nullptr == pfnEventsUnregister )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnEventsListen = xet_lib::context.ddiTable.Sysman.pfnEventsListen;
    if( nullptr == pfnEventsListen )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnDiagnosticsGet = xet_lib::context.ddiTable.Sysman.pfnDiagnosticsGet;
    if( nullptr == pfnDiagnosticsGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.SysmanDiagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hDiagnostics, pProperties );
}

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
    )
{
    auto pfnRunTests = xet_lib::context.ddiTable.SysmanDiagnostics.pfnRunTests;
    if( nullptr == pfnRunTests )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRunTests( hDiagnostics, start, end, pResult );
}

} // extern "C"

namespace xet
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
    SysmanLinkSwitch::SysmanLinkSwitch( 
        sysman_link_switch_handle_t handle,             ///< [in] handle of SMI object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanLinkPort::SysmanLinkPort( 
        sysman_link_port_handle_t handle,               ///< [in] handle of SMI object
        SysmanLinkSwitch* pSysmanLinkSwitch             ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysmanLinkSwitch( pSysmanLinkSwitch )
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
    Sysman* __xecall
    Sysman::Get(
        Device* pDevice,                                ///< [in] Handle of the device
        version_t version                               ///< [in] SMI version that application was built with
        )
    {
        xet_sysman_handle_t hSysman;

        auto result = static_cast<result_t>( ::xetSysmanGet(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            static_cast<xet_sysman_version_t>( version ),
            &hSysman ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::Get" );

        Sysman* pSysman = nullptr;

        try
        {
            pSysman = new Sysman( reinterpret_cast<sysman_handle_t>( hSysman ), pDevice );
        }
        catch( std::bad_alloc& )
        {
            delete pSysman;
            pSysman = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::Get" );
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
    void __xecall
    Sysman::DeviceGetProperties(
        properties_t* pProperties                       ///< [in] Structure that will contain information about the device.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDeviceGetProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_sysman_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::DeviceGetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get optimization mode of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::DeviceGetOptimizationMode(
        optimization_mode_t* pMode                      ///< [in] The current optimization mode of the device.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDeviceGetOptimizationMode(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_optimization_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::DeviceGetOptimizationMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set optimization mode of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::DeviceSetOptimizationMode(
        optimization_mode_t pMode                       ///< [in] The new optimization mode of the device.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDeviceSetOptimizationMode(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            static_cast<xet_optimization_mode_t>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::DeviceSetOptimizationMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset device
    /// 
    /// @throws result_t
    void __xecall
    Sysman::DeviceReset(
        void
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDeviceReset(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::DeviceReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI properties - address, max speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::PciGetProperties(
        pci_properties_t* pProperties                   ///< [in] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPciGetProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_pci_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::PciGetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current PCI state - current speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::PciGetState(
        pci_state_t* pState                             ///< [in] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPciGetState(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_pci_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::PciGetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties of a bar
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::PciGetBarProperties(
        uint32_t barIndex,                              ///< [in] The index of the bar (0 ... [::xet_pci_properties_t.numBars -
                                                        ///< 1]).
        pci_bar_properties_t* pProperties               ///< [in] Will contain properties of the specified bar
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPciGetBarProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            barIndex,
            reinterpret_cast<xet_pci_bar_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::PciGetBarProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI throughput
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::PciGetThroughput(
        pci_throughput_t* pThroughput                   ///< [in] Will contain a snapshot of the latest throughput counters.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPciGetThroughput(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_pci_throughput_t*>( pThroughput ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::PciGetThroughput" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI stats
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::PciGetStats(
        pci_stats_t* pStats                             ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPciGetStats(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_pci_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::PciGetStats" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_pwr_handle_t> hPower;
        hPower.resize( ( ppPower ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanPowerGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hPower.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::PowerGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::PowerGet" );
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
    void __xecall
    SysmanPower::GetProperties(
        power_properties_t* pProperties                 ///< [in] Structure that will contain property data.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPowerGetProperties(
            reinterpret_cast<xet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPower::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy counter
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanPower::GetEnergyCounter(
        power_energy_counter_t* pEnergy                 ///< [in] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPowerGetEnergyCounter(
            reinterpret_cast<xet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_energy_counter_t*>( pEnergy ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPower::GetEnergyCounter" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy threshold
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - power_energy_threshold_t: The current energy threshold value in joules.
    /// 
    /// @throws result_t
    SysmanPower::power_energy_threshold_t __xecall
    SysmanPower::GetEnergyThreshold(
        void
        )
    {
        xet_power_energy_threshold_t threshold;

        auto result = static_cast<result_t>( ::xetSysmanPowerGetEnergyThreshold(
            reinterpret_cast<xet_sysman_pwr_handle_t>( getHandle() ),
            &threshold ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPower::GetEnergyThreshold" );

        return *reinterpret_cast<power_energy_threshold_t*>( &threshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set energy threshold
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanPower::SetEnergyThreshold(
        power_energy_threshold_t* pThreshold            ///< [in] The energy threshold to be set in joules.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPowerSetEnergyThreshold(
            reinterpret_cast<xet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_energy_threshold_t*>( pThreshold ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPower::SetEnergyThreshold" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanPower::GetLimits(
        power_sustained_limit_t* pSustained,            ///< [in][optional] The sustained power limit.
        power_burst_limit_t* pBurst,                    ///< [in][optional] The burst power limit.
        power_peak_limit_t* pPeak                       ///< [in][optional] The peak power limit.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPowerGetLimits(
            reinterpret_cast<xet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<xet_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<xet_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPower::GetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanPower::SetLimits(
        const power_sustained_limit_t* pSustained,      ///< [in][optional] The sustained power limit.
        const power_burst_limit_t* pBurst,              ///< [in][optional] The burst power limit.
        const power_peak_limit_t* pPeak                 ///< [in][optional] The peak power limit.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPowerSetLimits(
            reinterpret_cast<xet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<const xet_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<const xet_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<const xet_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPower::SetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of frequency domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_freq_handle_t> hFrequency;
        hFrequency.resize( ( ppFrequency ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanFrequencyGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hFrequency.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::FrequencyGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::FrequencyGet" );
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
    void __xecall
    SysmanFrequency::GetProperties(
        freq_properties_t* pProperties                  ///< [in] The frequency properties for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFrequencyGetProperties(
            reinterpret_cast<xet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<xet_freq_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFrequency::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFrequency::GetRange(
        freq_range_t* pLimits                           ///< [in] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFrequencyGetRange(
            reinterpret_cast<xet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<xet_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFrequency::GetRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set frequency range between which the hardware can operate.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFrequency::SetRange(
        const freq_range_t* pLimits                     ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFrequencySetRange(
            reinterpret_cast<xet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<const xet_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFrequency::SetRange" );
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
    void __xecall
    SysmanFrequency::GetState(
        freq_state_t* pState                            ///< [in] Frequency state for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFrequencyGetState(
            reinterpret_cast<xet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<xet_freq_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFrequency::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency throttle time
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFrequency::GetThrottleTime(
        freq_throttle_time_t* pThrottleTime             ///< [in] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFrequencyGetThrottleTime(
            reinterpret_cast<xet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<xet_freq_throttle_time_t*>( pThrottleTime ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFrequency::GetThrottleTime" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of engine groups
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_engine_handle_t> hEngine;
        hEngine.resize( ( ppEngine ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanEngineGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hEngine.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::EngineGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::EngineGet" );
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
    void __xecall
    SysmanEngine::GetProperties(
        engine_properties_t* pProperties                ///< [in] The properties for the specified engine group.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanEngineGetProperties(
            reinterpret_cast<xet_sysman_engine_handle_t>( getHandle() ),
            reinterpret_cast<xet_engine_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanEngine::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the activity stats for an engine group
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanEngine::GetActivity(
        engine_stats_t* pStats                          ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanEngineGetActivity(
            reinterpret_cast<xet_sysman_engine_handle_t>( getHandle() ),
            reinterpret_cast<xet_engine_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanEngine::GetActivity" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of standby controls
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_standby_handle_t> hStandby;
        hStandby.resize( ( ppStandby ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanStandbyGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hStandby.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::StandbyGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::StandbyGet" );
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
    void __xecall
    SysmanStandby::GetProperties(
        standby_properties_t* pProperties               ///< [in] Will contain the standby hardware properties.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanStandbyGetProperties(
            reinterpret_cast<xet_sysman_standby_handle_t>( getHandle() ),
            reinterpret_cast<xet_standby_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanStandby::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanStandby::GetMode(
        standby_promo_mode_t* pMode                     ///< [in] Will contain the current standby mode.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanStandbyGetMode(
            reinterpret_cast<xet_sysman_standby_handle_t>( getHandle() ),
            reinterpret_cast<xet_standby_promo_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanStandby::GetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanStandby::SetMode(
        standby_promo_mode_t mode                       ///< [in] New standby mode.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanStandbySetMode(
            reinterpret_cast<xet_sysman_standby_handle_t>( getHandle() ),
            static_cast<xet_standby_promo_mode_t>( mode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanStandby::SetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of firmwares
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_firmware_handle_t> hFirmware;
        hFirmware.resize( ( ppFirmware ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanFirmwareGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hFirmware.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::FirmwareGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::FirmwareGet" );
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
    void __xecall
    SysmanFirmware::GetProperties(
        firmware_properties_t* pProperties              ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFirmwareGetProperties(
            reinterpret_cast<xet_sysman_firmware_handle_t>( getHandle() ),
            reinterpret_cast<xet_firmware_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFirmware::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware checksum
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFirmware::GetChecksum(
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFirmwareGetChecksum(
            reinterpret_cast<xet_sysman_firmware_handle_t>( getHandle() ),
            pChecksum ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFirmware::GetChecksum" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Flash a new firmware image
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFirmware::Flash(
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFirmwareFlash(
            reinterpret_cast<xet_sysman_firmware_handle_t>( getHandle() ),
            pImage,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFirmware::Flash" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of memory modules
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_mem_handle_t> hMemory;
        hMemory.resize( ( ppMemory ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanMemoryGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hMemory.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::MemoryGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::MemoryGet" );
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
    void __xecall
    SysmanMemory::GetProperties(
        mem_properties_t* pProperties                   ///< [in] Will contain memory properties.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanMemoryGetProperties(
            reinterpret_cast<xet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<xet_mem_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanMemory::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory bandwidth
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanMemory::GetBandwidth(
        mem_bandwidth_t* pBandwidth                     ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanMemoryGetBandwidth(
            reinterpret_cast<xet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<xet_mem_bandwidth_t*>( pBandwidth ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanMemory::GetBandwidth" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanMemory::GetAllocated(
        mem_alloc_t* pAllocated                         ///< [in] Will contain the current allocated memory.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanMemoryGetAllocated(
            reinterpret_cast<xet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<xet_mem_alloc_t*>( pAllocated ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanMemory::GetAllocated" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of connectivity switches
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::LinkSwitchGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanLinkSwitch** ppSwitch                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<xet_sysman_link_switch_handle_t> hSwitch;
        hSwitch.resize( ( ppSwitch ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanLinkSwitchGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hSwitch.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::LinkSwitchGet" );

        for( uint32_t i = 0; ( ppSwitch ) && ( i < *pCount ); ++i )
            ppSwitch[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppSwitch ) && ( i < *pCount ); ++i )
                ppSwitch[ i ] = new SysmanLinkSwitch( reinterpret_cast<sysman_link_switch_handle_t>( hSwitch[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppSwitch ) && ( i < *pCount ); ++i )
            {
                delete ppSwitch[ i ];
                ppSwitch[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::LinkSwitchGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get connectivity switch properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkSwitch::GetProperties(
        link_switch_properties_t* pProperties           ///< [in] Will contain the Switch properties.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkSwitchGetProperties(
            reinterpret_cast<xet_sysman_link_switch_handle_t>( getHandle() ),
            reinterpret_cast<xet_link_switch_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkSwitch::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get connectivity switch state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkSwitch::GetState(
        link_switch_state_t* pState                     ///< [in] Will contain the current state of the switch (enabled/disabled).
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkSwitchGetState(
            reinterpret_cast<xet_sysman_link_switch_handle_t>( getHandle() ),
            reinterpret_cast<xet_link_switch_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkSwitch::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set connectivity switch state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkSwitch::SetState(
        xe::bool_t enable                               ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkSwitchSetState(
            reinterpret_cast<xet_sysman_link_switch_handle_t>( getHandle() ),
            static_cast<xe_bool_t>( enable ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkSwitch::SetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of connectivity ports in a switch
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkSwitch::GetPorts(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanLinkPort** ppPort                         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<xet_sysman_link_port_handle_t> hPort;
        hPort.resize( ( ppPort ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanLinkSwitchGetPorts(
            reinterpret_cast<xet_sysman_link_switch_handle_t>( getHandle() ),
            pCount,
            hPort.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkSwitch::GetPorts" );

        for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            ppPort[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
                ppPort[ i ] = new SysmanLinkPort( reinterpret_cast<sysman_link_port_handle_t>( hPort[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            {
                delete ppPort[ i ];
                ppPort[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::SysmanLinkSwitch::GetPorts" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get connectivity port properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkPort::GetProperties(
        link_port_properties_t* pProperties             ///< [in] Will contain properties of the Switch Port
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkPortGetProperties(
            reinterpret_cast<xet_sysman_link_port_handle_t>( getHandle() ),
            reinterpret_cast<xet_link_port_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkPort::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get connectivity port state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkPort::GetState(
        link_port_state_t* pState                       ///< [in] Will contain the current state of the Switch Port
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkPortGetState(
            reinterpret_cast<xet_sysman_link_port_handle_t>( getHandle() ),
            reinterpret_cast<xet_link_port_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkPort::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get connectivity port throughput
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkPort::GetThroughput(
        link_port_throughput_t* pThroughput             ///< [in] Will contain the Switch port throughput counters.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkPortGetThroughput(
            reinterpret_cast<xet_sysman_link_port_handle_t>( getHandle() ),
            reinterpret_cast<xet_link_port_throughput_t*>( pThroughput ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkPort::GetThroughput" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get connectivity port stats
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkPort::GetStats(
        link_port_stats_t* pStats                       ///< [in] Will contain the Switch port stats.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkPortGetStats(
            reinterpret_cast<xet_sysman_link_port_handle_t>( getHandle() ),
            reinterpret_cast<xet_link_port_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkPort::GetStats" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Check if two connectivity ports are physically connected
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLinkPort::IsConnected(
        SysmanLinkPort* pRemotePort,                    ///< [in] Handle of the remote connectivity port.
        xe::bool_t* pConnected                          ///< [in] Will indicate connected to the remote port.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLinkPortIsConnected(
            reinterpret_cast<xet_sysman_link_port_handle_t>( getHandle() ),
            reinterpret_cast<xet_sysman_link_port_handle_t>( pRemotePort->getHandle() ),
            reinterpret_cast<xe_bool_t*>( pConnected ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLinkPort::IsConnected" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of temperature sensors
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_temp_handle_t> hTemperature;
        hTemperature.resize( ( ppTemperature ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanTemperatureGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hTemperature.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::TemperatureGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::TemperatureGet" );
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
    void __xecall
    SysmanTemperature::GetProperties(
        temp_properties_t* pProperties                  ///< [in] Will contain the temperature sensor properties.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanTemperatureGetProperties(
            reinterpret_cast<xet_sysman_temp_handle_t>( getHandle() ),
            reinterpret_cast<xet_temp_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanTemperature::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the temperature from a specified sensor
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanTemperature::Read(
        uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanTemperatureRead(
            reinterpret_cast<xet_sysman_temp_handle_t>( getHandle() ),
            pTemperature ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanTemperature::Read" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power supplies
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_psu_handle_t> hPsu;
        hPsu.resize( ( ppPsu ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanPsuGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hPsu.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::PsuGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::PsuGet" );
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
    void __xecall
    SysmanPsu::GetProperties(
        psu_properties_t* pProperties                   ///< [in] Will contain the properties of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPsuGetProperties(
            reinterpret_cast<xet_sysman_psu_handle_t>( getHandle() ),
            reinterpret_cast<xet_psu_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPsu::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current power supply state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanPsu::GetState(
        psu_state_t* pState                             ///< [in] Will contain the current state of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanPsuGetState(
            reinterpret_cast<xet_sysman_psu_handle_t>( getHandle() ),
            reinterpret_cast<xet_psu_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanPsu::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of fans
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_fan_handle_t> hFan;
        hFan.resize( ( ppFan ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanFanGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hFan.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::FanGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::FanGet" );
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
    void __xecall
    SysmanFan::GetProperties(
        fan_properties_t* pProperties                   ///< [in] Will contain the properties of the fan.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFanGetProperties(
            reinterpret_cast<xet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<xet_fan_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFan::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current fan configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFan::GetConfig(
        fan_config_t* pConfig                           ///< [in] Will contain the current configuration of the fan.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFanGetConfig(
            reinterpret_cast<xet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<xet_fan_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFan::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFan::SetConfig(
        const fan_config_t* pConfig                     ///< [in] New fan configuration.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFanSetConfig(
            reinterpret_cast<xet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<const xet_fan_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFan::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a fan - current mode and speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanFan::GetState(
        fan_speed_units_t units,                        ///< [in] The units in which the fan speed should be returned.
        fan_state_t* pState                             ///< [in] Will contain the current state of the fan.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanFanGetState(
            reinterpret_cast<xet_sysman_fan_handle_t>( getHandle() ),
            static_cast<xet_fan_speed_units_t>( units ),
            reinterpret_cast<xet_fan_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanFan::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of LEDs
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_led_handle_t> hLed;
        hLed.resize( ( ppLed ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanLedGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hLed.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::LedGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::LedGet" );
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
    void __xecall
    SysmanLed::GetProperties(
        led_properties_t* pProperties                   ///< [in] Will contain the properties of the LED.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLedGetProperties(
            reinterpret_cast<xet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<xet_led_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLed::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a LED - on/off, color
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLed::GetState(
        led_state_t* pState                             ///< [in] Will contain the current state of the LED.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLedGetState(
            reinterpret_cast<xet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<xet_led_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLed::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set state of a LED - on/off, color
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    SysmanLed::SetState(
        const led_state_t* pState                       ///< [in] New state of the LED.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanLedSetState(
            reinterpret_cast<xet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<const xet_led_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanLed::SetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of RAS error sets
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_ras_handle_t> hRas;
        hRas.resize( ( ppRas ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanRasGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hRas.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::RasGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::RasGet" );
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
    void __xecall
    SysmanRas::GetProperties(
        ras_properties_t* pProperties                   ///< [in] Structure describing RAS properties
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanRasGetProperties(
            reinterpret_cast<xet_sysman_ras_handle_t>( getHandle() ),
            reinterpret_cast<xet_ras_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanRas::GetProperties" );
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
    void __xecall
    SysmanRas::GetErrors(
        xe::bool_t clear,                               ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
        ras_details_t* pDetails                         ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanRasGetErrors(
            reinterpret_cast<xet_sysman_ras_handle_t>( getHandle() ),
            static_cast<xe_bool_t>( clear ),
            pTotalErrors,
            reinterpret_cast<xet_ras_details_t*>( pDetails ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanRas::GetErrors" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get event properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::EventsGetProperties(
        event_properties_t* pProperties                 ///< [in] Structure describing event properties
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanEventsGetProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_event_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::EventsGetProperties" );
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
    void __xecall
    Sysman::EventsRegister(
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be registered.
        event_request_t* pEvents                        ///< [in][optional] Events to register.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanEventsRegister(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_event_request_t*>( pEvents ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::EventsRegister" );
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
    void __xecall
    Sysman::EventsUnregister(
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be unregistered.
        event_request_t* pEvents                        ///< [in][optional] Events to unregister.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanEventsUnregister(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_event_request_t*>( pEvents ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::EventsUnregister" );
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
    ///       ::XET_EVENT_WAIT_INFINITE. Then call this function for each device
    ///       with clear = true and timeout = 0.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::EventsListen(
        Sysman* pSysman,                                ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                        ///< device for which the application has registered to receive
                                                        ///< notifications.
        xe::bool_t clear,                               ///< [in] Clear the event status.
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                        ///< check status and return immediately. Set to ::XET_EVENT_WAIT_INFINITE
                                                        ///< to block until events arrive.
        uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                        ///< triggered.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanEventsListen(
            reinterpret_cast<xet_sysman_handle_t>( pSysman->getHandle() ),
            static_cast<xe_bool_t>( clear ),
            timeout,
            pEvents ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::EventsListen" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of diagnostics test suites
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
        thread_local std::vector<xet_sysman_diag_handle_t> hDiagnostics;
        hDiagnostics.resize( ( ppDiagnostics ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetSysmanDiagnosticsGet(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            pCount,
            hDiagnostics.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::DiagnosticsGet" );

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

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::DiagnosticsGet" );
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
    void __xecall
    SysmanDiagnostics::GetProperties(
        diag_properties_t* pProperties                  ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDiagnosticsGetProperties(
            reinterpret_cast<xet_sysman_diag_handle_t>( getHandle() ),
            reinterpret_cast<xet_diag_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanDiagnostics::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Run a diagnostics test suite, either all tests or a subset of tests.
    /// 
    /// @details
    ///     - This function will block until the diagnostics have completed.
    /// 
    /// @throws result_t
    void __xecall
    SysmanDiagnostics::RunTests(
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        diag_result_t* pResult                          ///< [in] The result of the diagnostics
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDiagnosticsRunTests(
            reinterpret_cast<xet_sysman_diag_handle_t>( getHandle() ),
            start,
            end,
            reinterpret_cast<xet_diag_result_t*>( pResult ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::SysmanDiagnostics::RunTests" );
    }

} // namespace xet

namespace xet
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
    /// @brief Converts Sysman::optimization_mode_t to std::string
    std::string to_string( const Sysman::optimization_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::optimization_mode_t::DEFAULT:
            str = "Sysman::optimization_mode_t::DEFAULT";
            break;

        case Sysman::optimization_mode_t::SINGLE_PROCESS_COMPUTE:
            str = "Sysman::optimization_mode_t::SINGLE_PROCESS_COMPUTE";
            break;

        default:
            str = "Sysman::optimization_mode_t::?";
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
        
        str += "Sysman::properties_t::wasRepaired : ";
        str += std::to_string(val.wasRepaired);
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
        
        str += "Sysman::pci_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Sysman::pci_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
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
    /// @brief Converts SysmanPower::power_domain_t to std::string
    std::string to_string( const SysmanPower::power_domain_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanPower::power_domain_t::PWR_DOMAIN_TOTAL:
            str = "SysmanPower::power_domain_t::PWR_DOMAIN_TOTAL";
            break;

        default:
            str = "SysmanPower::power_domain_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_properties_t to std::string
    std::string to_string( const SysmanPower::power_properties_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
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
        
        str += "SysmanPower::power_peak_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_domain_t to std::string
    std::string to_string( const SysmanFrequency::freq_domain_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFrequency::freq_domain_t::GPU:
            str = "SysmanFrequency::freq_domain_t::GPU";
            break;

        case SysmanFrequency::freq_domain_t::MEMORY:
            str = "SysmanFrequency::freq_domain_t::MEMORY";
            break;

        default:
            str = "SysmanFrequency::freq_domain_t::?";
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

        case SysmanEngine::engine_group_t::COMPUTE:
            str = "SysmanEngine::engine_group_t::COMPUTE";
            break;

        case SysmanEngine::engine_group_t::MEDIA:
            str = "SysmanEngine::engine_group_t::MEDIA";
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
    /// @brief Converts SysmanLinkSwitch::link_switch_properties_t to std::string
    std::string to_string( const SysmanLinkSwitch::link_switch_properties_t val )
    {
        std::string str;
        
        str += "SysmanLinkSwitch::link_switch_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanLinkSwitch::link_switch_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkSwitch::link_switch_state_t to std::string
    std::string to_string( const SysmanLinkSwitch::link_switch_state_t val )
    {
        std::string str;
        
        str += "SysmanLinkSwitch::link_switch_state_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_speed_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_speed_t val )
    {
        std::string str;
        
        str += "SysmanLinkPort::link_port_speed_t::bitRate : ";
        str += std::to_string(val.bitRate);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_speed_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_speed_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_properties_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_properties_t val )
    {
        std::string str;
        
        str += "SysmanLinkPort::link_port_properties_t::portNum : ";
        str += std::to_string(val.portNum);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_properties_t::maxSpeed : ";
        str += to_string(val.maxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_state_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_state_t val )
    {
        std::string str;
        
        str += "SysmanLinkPort::link_port_state_t::isConnected : ";
        str += std::to_string(val.isConnected);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_state_t::rxSpeed : ";
        str += to_string(val.rxSpeed);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_state_t::txSpeed : ";
        str += to_string(val.txSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_throughput_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_throughput_t val )
    {
        std::string str;
        
        str += "SysmanLinkPort::link_port_throughput_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_throughput_t::rxCounter : ";
        str += std::to_string(val.rxCounter);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_throughput_t::txCounter : ";
        str += std::to_string(val.txCounter);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_throughput_t::rxMaxBandwidth : ";
        str += std::to_string(val.rxMaxBandwidth);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_throughput_t::txMaxBandwidth : ";
        str += std::to_string(val.txMaxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLinkPort::link_port_stats_t to std::string
    std::string to_string( const SysmanLinkPort::link_port_stats_t val )
    {
        std::string str;
        
        str += "SysmanLinkPort::link_port_stats_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_stats_t::replayCounter : ";
        str += std::to_string(val.replayCounter);
        str += "\n";
        
        str += "SysmanLinkPort::link_port_stats_t::packetCounter : ";
        str += std::to_string(val.packetCounter);
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
        
        str += "SysmanRas::ras_details_t::numSwitchErrors : ";
        str += std::to_string(val.numSwitchErrors);
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

} // namespace xet
