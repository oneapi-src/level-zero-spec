/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
* The source code contained or described herein and all documents related to the  
* source code ("Material") are owned by Intel Corporation or its suppliers or  
* licensors. Title to the Material remains with Intel Corporation or its suppliers  
* and licensors. The Material contains trade secrets and proprietary and confidential  
* information of Intel or its suppliers and licensors. The Material is protected by  
* worldwide copyright and trade secret laws and treaty provisions. No part of the  
* Material may be used, copied, reproduced, modified, published, uploaded, posted  
* transmitted, distributed, or disclosed in any way without Intel's prior express  
* written permission.  
*
* No license under any patent, copyright, trade secret or other intellectual  
* property right is granted to or conferred upon you by disclosure or delivery  
* of the Materials, either expressly, by implication, inducement, estoppel  
* or otherwise. Any license under such intellectual property rights must be  
* express and approved by Intel in writing.  
* @endcond
*
* @file xet_power.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Power
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/power.yml
* @endcond
*
******************************************************************************/
#if defined(XET_CPP)
#include "xet_metric.hpp"
#else
#include "xet_power.h"
#endif
#if !defined(XET_NULLDRV)
#include "power.h"
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an object to access power features on a device
/// 
/// @details
///     - Initializes internal structures to support power management features.
///     - Error ::XE_RESULT_ERROR_UNSUPPORTED is returned if the device does not
///       support access to power management features.
/// 
/// @remarks
///   _Analogues_
///     - **nvmlInit**
///     - **rsmi_init**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == pPowerHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
    xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
    )
{
    return L0::Power::create( hDevice, flags, pPowerHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a power object
/// 
/// @remarks
///   _Analogues_
///     - **nvmlShutdown**
///     - **rsmi_shut_down**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerDestroy(
    xet_power_handle_t hPower                       ///< [in] handle of the power object to destroy
    )
{
    return L0::Power::fromHandle(hPower)->destroy();
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current average power limit information for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
    )
{
    return L0::Power::fromHandle(hPower)->getAveragePowerLimit( pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current burst power limit information for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
    )
{
    return L0::Power::fromHandle(hPower)->getBurstPowerLimit( pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current peak power limit information for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
    )
{
    return L0::Power::fromHandle(hPower)->getPeakPowerLimit( pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get all current power limits for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetAllPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
    )
{
    return L0::Power::fromHandle(hPower)->getAllPowerLimits( pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get default power limits for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetDefaultPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
    )
{
    return L0::Power::fromHandle(hPower)->getDefaultPowerLimits( pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the average power limit for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerSetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
    )
{
    return L0::Power::fromHandle(hPower)->setAveragePowerLimit( pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the burst power limit for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerSetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
    )
{
    return L0::Power::fromHandle(hPower)->setBurstPowerLimit( pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the peak power limit for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerSetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
    )
{
    return L0::Power::fromHandle(hPower)->setPeakPowerLimit( pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the average/burst/peak power limits for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerSetPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
    )
{
    return L0::Power::fromHandle(hPower)->setPowerLimits( pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
/// 
/// @details
///     - Average power = delta(energy counter in millijoules) / delta(time in
///       milliseconds)
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pEnergy
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetEnergyCounter(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
    )
{
    return L0::Power::fromHandle(hPower)->getEnergyCounter( pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current Turbo mode for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pTurboMode
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
    )
{
    return L0::Power::fromHandle(hPower)->getTurboMode( pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current Turbo mode for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerSetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
    )
{
    return L0::Power::fromHandle(hPower)->setTurboMode( pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the number of frequency domains on the device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pNumFreqDomains
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    )
{
    return L0::Power::fromHandle(hPower)->getFreqDomainCount( pNumFreqDomains );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get an object to a frequency domain on a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == phFreqDomain
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetFreqDomain(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t ordinal,                               ///< [in] frequency domain index [0 .. ::xetPowerGetFreqDomainCount - 1]
    xet_freq_domain_handle_t* phFreqDomain          ///< [out] pointer to handle of frequency domain object
    )
{
    return L0::Power::fromHandle(hPower)->getFreqDomain( ordinal, phFreqDomain );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the properties for a frequency domain
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///         + nullptr == pFreqDomainProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainGetProperties(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->getProperties( pFreqDomainProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the source frequency domain handle for a frequency domain of type
///        ::XET_CLOCK_TYPE_DIVIDER
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///         + nullptr == phSrcFreqDomain
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainGetSourceFreqDomain(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_handle_t* phSrcFreqDomain       ///< [out] pointer to a handle where the source frequency domain handle
                                                    ///< will be returned
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->getSourceFreqDomain( phSrcFreqDomain );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get supported frequency points for frequency domains with clock type
///        ::XET_CLOCK_TYPE_PLL
/// 
/// @details
///     - The total available list of frequencies can be found in
///       ::xet_freq_domain_properties_t.numClockPoints.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///         + nullptr == pClocks
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainGetSupportedClocks(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockPoints,                        ///< [in] number of elements in pClocks
    uint32_t* pClocks                               ///< [out] pointer to array of frequencies
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->getSupportedClocks( numClockPoints, pClocks );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get supported frequency dividers for frequency domains with clock type
///        ::XET_CLOCK_TYPE_DIVIDER
/// 
/// @details
///     - The total available list of frequencies can be found in
///       ::xet_freq_domain_properties_t.numClockDividers.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///         + nullptr == pDividers
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainGetSupportedClockDividers(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockDividers,                      ///< [in] number of elements in pDividers
    xet_clock_divider_t* pDividers                  ///< [out] pointer to array of dividers
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->getSupportedClockDividers( numClockDividers, pDividers );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the frequency range for a frequency domain with clock type
///        ::XET_CLOCK_TYPE_PLL.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///         + nullptr == pMinClock
///         + nullptr == pMaxClock
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainGetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pMinClock,                            ///< [out] min clock frequency in units of MHz
    uint32_t* pMaxClock                             ///< [out] max clock frequency in units of MHz
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->getClockRange( pMinClock, pMaxClock );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the frequency range for a frequency domain with clock type
///        ::XET_CLOCK_TYPE_PLL.
/// 
/// @details
///     - Turbo (dynamic hardware frequency management) will select frequencies
///       between this range based on the current Turbo mode in effect.
///     - Setting minClock = maxClock will fix the frequency for that frequency
///       domain.
///     - Setting minClock = 0 will instruct the hardware to use the default min
///       value.
///     - Setting maxClock = 0 will instruct the hardware to use the default max
///       value.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainSetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
    uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->setClockRange( minClock, maxClock );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency divider for a frequency domain with clock type
///        ::XET_CLOCK_TYPE_DIVIDER
/// 
/// @details
///     - This disables dynamic frequency divider management running on the
///       hardware.
///     - Setting pClockDivider to nullptr will enable dynamic frequency divider
///       management.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///         + nullptr == pClockDividerRequest
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainSetClockDivider(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->setClockDivider( pClockDividerRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFreqDomain
///         + nullptr == pFreqRequest
///         + nullptr == pFreqResolved
///         + nullptr == pFreqThrottleReasons
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetFreqDomainGetCurrentFrequency(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pFreqRequest,                         ///< [out] current frequency in MHz requested by the driver
    uint32_t* pFreqResolved,                        ///< [out] the actual frequency in MHz
    xet_freq_throttle_reasons_t* pFreqThrottleReasons   ///< [out] the reason the resolved frequency is lower than the request
    )
{
    return L0::FreqDomain::fromHandle(hFreqDomain)->getCurrentFrequency( pFreqRequest, pFreqResolved, pFreqThrottleReasons );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get number of fans on the device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pFanCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerFanCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pFanCount                             ///< [out] the number of fans on the device
    )
{
    return L0::Power::fromHandle(hPower)->getFanCount( pFanCount );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties for one of the fans on a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pFanProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerFanGetProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xet_fan_properties_t* pFanProperties            ///< [out] pointer to storage for fan properties
    )
{
    return L0::Power::fromHandle(hPower)->getFanProperties(fanIndex, pFanProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan speed table
/// 
/// @details
///     - Set pFanSpeedTable = nullptr to find out the current number of fan
///       speed points in the table.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pNumFanPoints
///         + nullptr == pFanPoints
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerFanGetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    uint32_t* pNumFanPoints,                        ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                    ///< number of elements returned
    xet_fan_point_t* pFanPoints                     ///< [out] pointer to an array of temperature/fan-speed points
    )
{
    return L0::Power::fromHandle(hPower)->getFanSpeedTable( fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan speed table
/// 
/// @details
///     - Use ::xetPowerFanGetProperties to determine acceptable units for fan
///       speed (percent, RPM).
///     - Fan points should be ordered according to increasing temperature.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pFanPoints
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerFanSetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
    xet_fan_point_t* pFanPoints                     ///< [in] pointer to an array of temperature/fan-speed points
    )
{
    return L0::Power::fromHandle(hPower)->setFanSpeedTable( fanIndex, numFanPoints, pFanPoints );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current fan speeds
/// 
/// @details
///     - The array pFanSpeed must contain at least numFans entries.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pFanSpeed
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerFanGetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    xet_fan_speed_info_t* pFanSpeed                 ///< [out] pointer to an array of current fan speeds
    )
{
    return L0::Power::fromHandle(hPower)->getFanSpeed( startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan speeds
/// 
/// @details
///     - Use ::xet_fan_speed_info_t.fanSpeedMode to set whether the speed
///       should be fixed or dynamically controlled
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pFanSpeed
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerFanSetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xet_fan_speed_info_t* pFanSpeed                 ///< [in] pointer to an array of current fan speeds
    )
{
    return L0::Power::fromHandle(hPower)->setFanSpeed( startFanIndex, numFans, pFanSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get number of temperature sensors on the device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pSensorCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerTemperatureSensorCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
    )
{
    return L0::Power::fromHandle(hPower)->getTemperatureSensorCount( pSensorCount );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperatures sensor properties
/// 
/// @details
///     - Temperature sensor index 0 is special - it gives the maximum
///       temperature across all sensors
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetTemperatureProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    xet_temperature_properties_t* pProperties       ///< [out] pointer to properties for this sensor
    )
{
    return L0::Power::fromHandle(hPower)->getTemperatureProperties( sensorIndex, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current temperatures
/// 
/// @details
///     - Temperature sensor index 0 is special - it gives the maximum
///       temperature across all sensors
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pTemperatures
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetTemperature(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint32_t numSensors,                            ///< [in] pTemperatures will contain results for sensors index
                                                    ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
    uint16_t* pTemperatures                         ///< [out] pointer to an array of temperatures in units of degrees celsius
    )
{
    return L0::Power::fromHandle(hPower)->getTemperature( startSensorIndex, numSensors, pTemperatures );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature threshold
/// 
/// @details
///     - Check ::xet_temperature_properties_t.canChangeThreshold to determine
///       if the threshold can be changed.
///     - On most systems, there is only one threshold and sensorIndex should be
///       0.
///     - **This is an overclocking feature and will void device warranty**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerSetTemperatureThreshold(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                    ///< will be throttled
    )
{
    return L0::Power::fromHandle(hPower)->setTemperatureThreshold( sensorIndex, maxTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get number of activity counters
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pActivityCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerActivityCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
    )
{
    return L0::Power::fromHandle(hPower)->getActivityCount( pActivityCount );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get activity counter properties
/// 
/// @details
///     - Activity counter index 0 is special - it acculates activity across all
///       blocks.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetActivityProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t activityIndex,                         ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
    xet_activity_properties_t* pProperties          ///< [out] pointer to properties for this activity counter
    )
{
    return L0::Power::fromHandle(hPower)->getActivityProperties( activityIndex, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get activity counters
/// 
/// @details
///     - Activity counter index 0 is special - it acculates activity across all
///       blocks.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pCounters
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetPowerGetActivityCounters(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
    uint32_t numCounters,                           ///< [in] pCounters will contain results for activity counter index
                                                    ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
    xet_activity_counters_t* pCounters              ///< [out] pointer to an array of activity counter data
    )
{
    return L0::Power::fromHandle(hPower)->getActivityCounters( startCounterIndex, numCounters, pCounters );
}


#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts fan_capabilities_t to std::string
std::string to_string( xet::fan_capabilities_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xet::fan_capabilities_t::GET_SPEED_PERCENTAGE) & bits )
        str += "xet::fan_capabilities_t::GET_SPEED_PERCENTAGE | ";
    if( static_cast<uint32_t>(xet::fan_capabilities_t::SET_SPEED_PERCENTAGE) & bits )
        str += "xet::fan_capabilities_t::SET_SPEED_PERCENTAGE | ";
    if( static_cast<uint32_t>(xet::fan_capabilities_t::GET_SPEED_RPM) & bits )
        str += "xet::fan_capabilities_t::GET_SPEED_RPM | ";
    if( static_cast<uint32_t>(xet::fan_capabilities_t::SET_SPEED_RPM) & bits )
        str += "xet::fan_capabilities_t::SET_SPEED_RPM | ";
    if( static_cast<uint32_t>(xet::fan_capabilities_t::HAVE_TEMPERATURE_SPEED_TABLE) & bits )
        str += "xet::fan_capabilities_t::HAVE_TEMPERATURE_SPEED_TABLE | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts fan_speed_mode_t to std::string
std::string to_string( xet::fan_speed_mode_t val )
{
    switch( val )
    {
    case xet::fan_speed_mode_t::AUTO:
        return std::string("xet::fan_speed_mode_t::AUTO");
    case xet::fan_speed_mode_t::FIXED:
        return std::string("xet::fan_speed_mode_t::FIXED");
    };
    return std::string("xet::fan_speed_mode_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Power::init_flags_t to std::string
std::string to_string( xet::Power::init_flags_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xet::Power::init_flags_t::NONE) & bits )
        str += "xet::Power::init_flags_t::NONE | ";
    if( static_cast<uint32_t>(xet::Power::init_flags_t::WRITE) & bits )
        str += "xet::Power::init_flags_t::WRITE | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Power::gpu_domain_t to std::string
std::string to_string( xet::Power::gpu_domain_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::BASE) & bits )
        str += "xet::Power::gpu_domain_t::BASE | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::VIDEO_DECODE) & bits )
        str += "xet::Power::gpu_domain_t::VIDEO_DECODE | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::VIDEO_ENCODE) & bits )
        str += "xet::Power::gpu_domain_t::VIDEO_ENCODE | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::VIDEO_PROCESSING) & bits )
        str += "xet::Power::gpu_domain_t::VIDEO_PROCESSING | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::_3D_FIXED_FUNCTION) & bits )
        str += "xet::Power::gpu_domain_t::_3D_FIXED_FUNCTION | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::_3D_RENDER) & bits )
        str += "xet::Power::gpu_domain_t::_3D_RENDER | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::COMPUTE) & bits )
        str += "xet::Power::gpu_domain_t::COMPUTE | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::SYSTOLIC_ARRAY) & bits )
        str += "xet::Power::gpu_domain_t::SYSTOLIC_ARRAY | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::RAYTRACING) & bits )
        str += "xet::Power::gpu_domain_t::RAYTRACING | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::LOCAL_MEMORY) & bits )
        str += "xet::Power::gpu_domain_t::LOCAL_MEMORY | ";
    if( static_cast<uint32_t>(xet::Power::gpu_domain_t::BASE_CHIPLET_LINK) & bits )
        str += "xet::Power::gpu_domain_t::BASE_CHIPLET_LINK | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Power::average_limit_version_t to std::string
std::string to_string( xet::Power::average_limit_version_t val )
{
    switch( val )
    {
    case xet::Power::average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT:
        return std::string("xet::Power::average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT");
    };
    return std::string("xet::Power::average_limit_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Power::turbo_mode_t to std::string
std::string to_string( xet::Power::turbo_mode_t val )
{
    switch( val )
    {
    case xet::Power::turbo_mode_t::DISABLED:
        return std::string("xet::Power::turbo_mode_t::DISABLED");
    case xet::Power::turbo_mode_t::DEFAULT:
        return std::string("xet::Power::turbo_mode_t::DEFAULT");
    case xet::Power::turbo_mode_t::MIN_PERFORMANCE:
        return std::string("xet::Power::turbo_mode_t::MIN_PERFORMANCE");
    case xet::Power::turbo_mode_t::EFFICIENT_PERFORMANCE:
        return std::string("xet::Power::turbo_mode_t::EFFICIENT_PERFORMANCE");
    case xet::Power::turbo_mode_t::AGGRESSIVE_PERFORMANCE:
        return std::string("xet::Power::turbo_mode_t::AGGRESSIVE_PERFORMANCE");
    case xet::Power::turbo_mode_t::MAX_PERFORMANCE:
        return std::string("xet::Power::turbo_mode_t::MAX_PERFORMANCE");
    };
    return std::string("xet::Power::turbo_mode_t::?");
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Converts FreqDomain::clock_type_t to std::string
std::string to_string( xet::FreqDomain::clock_type_t val )
{
    switch( val )
    {
    case xet::FreqDomain::clock_type_t::FIXED:
        return std::string("xet::FreqDomain::clock_type_t::FIXED");
    case xet::FreqDomain::clock_type_t::PLL:
        return std::string("xet::FreqDomain::clock_type_t::PLL");
    case xet::FreqDomain::clock_type_t::DIVIDER:
        return std::string("xet::FreqDomain::clock_type_t::DIVIDER");
    };
    return std::string("xet::FreqDomain::clock_type_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts FreqDomain::freq_throttle_reasons_t to std::string
std::string to_string( xet::FreqDomain::freq_throttle_reasons_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::NONE) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::NONE | ";
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::AVE_PWR_CAP) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::AVE_PWR_CAP | ";
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::BURST_PWR_CAP) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::BURST_PWR_CAP | ";
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::CURRENT_LIMIT) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::CURRENT_LIMIT | ";
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::THERMAL_LIMIT) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::THERMAL_LIMIT | ";
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::PSU_ALERT) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::PSU_ALERT | ";
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::SW_RANGE) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::SW_RANGE | ";
    if( static_cast<uint32_t>(xet::FreqDomain::freq_throttle_reasons_t::HW_RANGE) & bits )
        str += "xet::FreqDomain::freq_throttle_reasons_t::HW_RANGE | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}


#endif // _DEBUG
