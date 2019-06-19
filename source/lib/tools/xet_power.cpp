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
#include "xet_lib.h"

extern "C" {

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
xe_result_t __xecall
xetPowerCreate(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device object
    uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
    xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
    )
{
    auto pfnCreate = xet_lib::context.ddiTable.Power.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDevice, flags, pPowerHandle );
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
xe_result_t __xecall
xetPowerDestroy(
    xet_power_handle_t hPower                       ///< [in][release] handle of the power object to destroy
    )
{
    auto pfnDestroy = xet_lib::context.ddiTable.Power.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hPower );
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
xe_result_t __xecall
xetPowerGetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
    )
{
    auto pfnGetAveragePowerLimit = xet_lib::context.ddiTable.Power.pfnGetAveragePowerLimit;
    if( nullptr == pfnGetAveragePowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAveragePowerLimit( hPower, pLimit );
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
xe_result_t __xecall
xetPowerGetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
    )
{
    auto pfnGetBurstPowerLimit = xet_lib::context.ddiTable.Power.pfnGetBurstPowerLimit;
    if( nullptr == pfnGetBurstPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetBurstPowerLimit( hPower, pLimit );
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
xe_result_t __xecall
xetPowerGetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
    )
{
    auto pfnGetPeakPowerLimit = xet_lib::context.ddiTable.Power.pfnGetPeakPowerLimit;
    if( nullptr == pfnGetPeakPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPeakPowerLimit( hPower, pLimit );
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
xe_result_t __xecall
xetPowerGetAllPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
    )
{
    auto pfnGetAllPowerLimits = xet_lib::context.ddiTable.Power.pfnGetAllPowerLimits;
    if( nullptr == pfnGetAllPowerLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAllPowerLimits( hPower, pLimits );
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
xe_result_t __xecall
xetPowerGetDefaultPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
    )
{
    auto pfnGetDefaultPowerLimits = xet_lib::context.ddiTable.Power.pfnGetDefaultPowerLimits;
    if( nullptr == pfnGetDefaultPowerLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDefaultPowerLimits( hPower, pLimits );
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
xe_result_t __xecall
xetPowerSetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
    )
{
    auto pfnSetAveragePowerLimit = xet_lib::context.ddiTable.Power.pfnSetAveragePowerLimit;
    if( nullptr == pfnSetAveragePowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetAveragePowerLimit( hPower, pLimit );
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
xe_result_t __xecall
xetPowerSetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
    )
{
    auto pfnSetBurstPowerLimit = xet_lib::context.ddiTable.Power.pfnSetBurstPowerLimit;
    if( nullptr == pfnSetBurstPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetBurstPowerLimit( hPower, pLimit );
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
xe_result_t __xecall
xetPowerSetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
    )
{
    auto pfnSetPeakPowerLimit = xet_lib::context.ddiTable.Power.pfnSetPeakPowerLimit;
    if( nullptr == pfnSetPeakPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPeakPowerLimit( hPower, pLimit );
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
xe_result_t __xecall
xetPowerSetPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
    )
{
    auto pfnSetPowerLimits = xet_lib::context.ddiTable.Power.pfnSetPowerLimits;
    if( nullptr == pfnSetPowerLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPowerLimits( hPower, pLimits );
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
xe_result_t __xecall
xetPowerGetEnergyCounter(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
    )
{
    auto pfnGetEnergyCounter = xet_lib::context.ddiTable.Power.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetEnergyCounter( hPower, pEnergy );
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
xe_result_t __xecall
xetPowerGetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
    )
{
    auto pfnGetTurboMode = xet_lib::context.ddiTable.Power.pfnGetTurboMode;
    if( nullptr == pfnGetTurboMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetTurboMode( hPower, pTurboMode );
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
xe_result_t __xecall
xetPowerSetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
    )
{
    auto pfnSetTurboMode = xet_lib::context.ddiTable.Power.pfnSetTurboMode;
    if( nullptr == pfnSetTurboMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetTurboMode( hPower, pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves frequency domains on a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hPower
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetFreqDomainGet(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of frequency domains.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of frequency domains available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< frequency domains.
                                                    ///< if count is larger than the number of frequency domains available,
                                                    ///< then the driver will update the value with the correct number of
                                                    ///< frequency domains available.
    xet_freq_domain_handle_t* phFreqDomain          ///< [in,out][optional][range(0, *pCount)] array of handle of frequency
                                                    ///< domains
    )
{
    auto pfnGet = xet_lib::context.ddiTable.FreqDomain.pfnGet;
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGet( hPower, pCount, phFreqDomain );
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
xe_result_t __xecall
xetFreqDomainGetProperties(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.FreqDomain.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hFreqDomain, pFreqDomainProperties );
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
xe_result_t __xecall
xetFreqDomainGetSourceFreqDomain(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_handle_t* phSrcFreqDomain       ///< [out] pointer to a handle where the source frequency domain handle
                                                    ///< will be returned
    )
{
    auto pfnGetSourceFreqDomain = xet_lib::context.ddiTable.FreqDomain.pfnGetSourceFreqDomain;
    if( nullptr == pfnGetSourceFreqDomain )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetSourceFreqDomain( hFreqDomain, phSrcFreqDomain );
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
xe_result_t __xecall
xetFreqDomainGetSupportedClocks(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockPoints,                        ///< [in] number of elements in pClocks
    uint32_t* pClocks                               ///< [out] pointer to array of frequencies
    )
{
    auto pfnGetSupportedClocks = xet_lib::context.ddiTable.FreqDomain.pfnGetSupportedClocks;
    if( nullptr == pfnGetSupportedClocks )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetSupportedClocks( hFreqDomain, numClockPoints, pClocks );
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
xe_result_t __xecall
xetFreqDomainGetSupportedClockDividers(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockDividers,                      ///< [in] number of elements in pDividers
    xet_clock_divider_t* pDividers                  ///< [out] pointer to array of dividers
    )
{
    auto pfnGetSupportedClockDividers = xet_lib::context.ddiTable.FreqDomain.pfnGetSupportedClockDividers;
    if( nullptr == pfnGetSupportedClockDividers )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );
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
xe_result_t __xecall
xetFreqDomainGetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pMinClock,                            ///< [out] min clock frequency in units of MHz
    uint32_t* pMaxClock                             ///< [out] max clock frequency in units of MHz
    )
{
    auto pfnGetClockRange = xet_lib::context.ddiTable.FreqDomain.pfnGetClockRange;
    if( nullptr == pfnGetClockRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetClockRange( hFreqDomain, pMinClock, pMaxClock );
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
xe_result_t __xecall
xetFreqDomainSetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
    uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
    )
{
    auto pfnSetClockRange = xet_lib::context.ddiTable.FreqDomain.pfnSetClockRange;
    if( nullptr == pfnSetClockRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetClockRange( hFreqDomain, minClock, maxClock );
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
xe_result_t __xecall
xetFreqDomainSetClockDivider(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
    )
{
    auto pfnSetClockDivider = xet_lib::context.ddiTable.FreqDomain.pfnSetClockDivider;
    if( nullptr == pfnSetClockDivider )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetClockDivider( hFreqDomain, pClockDividerRequest );
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
xe_result_t __xecall
xetFreqDomainGetCurrentFrequency(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pFreqRequest,                         ///< [out] current frequency in MHz requested by the driver
    uint32_t* pFreqResolved,                        ///< [out] the actual frequency in MHz
    xet_freq_throttle_reasons_t* pFreqThrottleReasons   ///< [out] the reason the resolved frequency is lower than the request
    )
{
    auto pfnGetCurrentFrequency = xet_lib::context.ddiTable.FreqDomain.pfnGetCurrentFrequency;
    if( nullptr == pfnGetCurrentFrequency )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetCurrentFrequency( hFreqDomain, pFreqRequest, pFreqResolved, pFreqThrottleReasons );
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
xe_result_t __xecall
xetPowerFanCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pFanCount                             ///< [out] the number of fans on the device
    )
{
    auto pfnFanCount = xet_lib::context.ddiTable.Power.pfnFanCount;
    if( nullptr == pfnFanCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnFanCount( hPower, pFanCount );
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
xe_result_t __xecall
xetPowerFanGetProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xet_fan_properties_t* pFanProperties            ///< [out] pointer to storage for fan properties
    )
{
    auto pfnFanGetProperties = xet_lib::context.ddiTable.Power.pfnFanGetProperties;
    if( nullptr == pfnFanGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnFanGetProperties( hPower, fanIndex, pFanProperties );
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
xe_result_t __xecall
xetPowerFanGetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    uint32_t* pNumFanPoints,                        ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                    ///< number of elements returned
    xet_fan_point_t* pFanPoints                     ///< [out] pointer to an array of temperature/fan-speed points
    )
{
    auto pfnFanGetSpeedTable = xet_lib::context.ddiTable.Power.pfnFanGetSpeedTable;
    if( nullptr == pfnFanGetSpeedTable )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );
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
xe_result_t __xecall
xetPowerFanSetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
    xet_fan_point_t* pFanPoints                     ///< [in] pointer to an array of temperature/fan-speed points
    )
{
    auto pfnFanSetSpeedTable = xet_lib::context.ddiTable.Power.pfnFanSetSpeedTable;
    if( nullptr == pfnFanSetSpeedTable )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );
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
xe_result_t __xecall
xetPowerFanGetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    xet_fan_speed_info_t* pFanSpeed                 ///< [out] pointer to an array of current fan speeds
    )
{
    auto pfnFanGetSpeed = xet_lib::context.ddiTable.Power.pfnFanGetSpeed;
    if( nullptr == pfnFanGetSpeed )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );
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
xe_result_t __xecall
xetPowerFanSetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xet_fan_speed_info_t* pFanSpeed                 ///< [in] pointer to an array of current fan speeds
    )
{
    auto pfnFanSetSpeed = xet_lib::context.ddiTable.Power.pfnFanSetSpeed;
    if( nullptr == pfnFanSetSpeed )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );
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
xe_result_t __xecall
xetPowerTemperatureSensorCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
    )
{
    auto pfnTemperatureSensorCount = xet_lib::context.ddiTable.Power.pfnTemperatureSensorCount;
    if( nullptr == pfnTemperatureSensorCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnTemperatureSensorCount( hPower, pSensorCount );
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
xe_result_t __xecall
xetPowerGetTemperatureProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    xet_temperature_properties_t* pProperties       ///< [out] pointer to properties for this sensor
    )
{
    auto pfnGetTemperatureProperties = xet_lib::context.ddiTable.Power.pfnGetTemperatureProperties;
    if( nullptr == pfnGetTemperatureProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetTemperatureProperties( hPower, sensorIndex, pProperties );
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
xe_result_t __xecall
xetPowerGetTemperature(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint32_t numSensors,                            ///< [in] pTemperatures will contain results for sensors index
                                                    ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
    uint16_t* pTemperatures                         ///< [out] pointer to an array of temperatures in units of degrees celsius
    )
{
    auto pfnGetTemperature = xet_lib::context.ddiTable.Power.pfnGetTemperature;
    if( nullptr == pfnGetTemperature )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );
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
xe_result_t __xecall
xetPowerSetTemperatureThreshold(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                    ///< will be throttled
    )
{
    auto pfnSetTemperatureThreshold = xet_lib::context.ddiTable.Power.pfnSetTemperatureThreshold;
    if( nullptr == pfnSetTemperatureThreshold )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );
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
xe_result_t __xecall
xetPowerActivityCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
    )
{
    auto pfnActivityCount = xet_lib::context.ddiTable.Power.pfnActivityCount;
    if( nullptr == pfnActivityCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnActivityCount( hPower, pActivityCount );
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
xe_result_t __xecall
xetPowerGetActivityProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t activityIndex,                         ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
    xet_activity_properties_t* pProperties          ///< [out] pointer to properties for this activity counter
    )
{
    auto pfnGetActivityProperties = xet_lib::context.ddiTable.Power.pfnGetActivityProperties;
    if( nullptr == pfnGetActivityProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetActivityProperties( hPower, activityIndex, pProperties );
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
xe_result_t __xecall
xetPowerGetActivityCounters(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
    uint32_t numCounters,                           ///< [in] pCounters will contain results for activity counter index
                                                    ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
    xet_activity_counters_t* pCounters              ///< [out] pointer to an array of activity counter data
    )
{
    auto pfnGetActivityCounters = xet_lib::context.ddiTable.Power.pfnGetActivityCounters;
    if( nullptr == pfnGetActivityCounters )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    Power::Power( 
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    FreqDomain::FreqDomain( 
        Power* pPower                                   ///< [in] pointer to owner object
        ) :
        m_pPower( pPower )
    {
    }

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
    ///     - Power*: handle for accessing power features of the device
    /// 
    /// @throws result_t
    Power* __xecall
    Power::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        uint32_t flags                                  ///< [in] bitfield of ::xet_power_init_flags_t
        )
    {
        xet_power_handle_t powerHandle;

        auto result = static_cast<result_t>( ::xetPowerCreate(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            flags,
            &powerHandle ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::Create" );

        Power* pPowerHandle = nullptr;

        try
        {
            pPowerHandle = new Power( pDevice );
        }
        catch( std::bad_alloc& )
        {
            delete pPowerHandle;
            pPowerHandle = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Power::Create" );
        }

        return pPowerHandle;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a power object
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **nvmlShutdown**
    ///     - **rsmi_shut_down**
    /// 
    /// @throws result_t
    void __xecall
    Power::Destroy(
        Power* pPower                                   ///< [in][release] pointer to the power object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xetPowerDestroy(
            reinterpret_cast<xet_power_handle_t>( pPower->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::Destroy" );

        delete pPower;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current average power limit information for a device
    /// 
    /// @returns
    ///     - average_limit_t: information about the average power limit
    /// 
    /// @throws result_t
    Power::average_limit_t __xecall
    Power::GetAveragePowerLimit(
        void
        )
    {
        xet_power_average_limit_t limit;

        auto result = static_cast<result_t>( ::xetPowerGetAveragePowerLimit(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &limit ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetAveragePowerLimit" );

        return *reinterpret_cast<average_limit_t*>( &limit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current burst power limit information for a device
    /// 
    /// @returns
    ///     - burst_limit_t: information about the burst power limit
    /// 
    /// @throws result_t
    Power::burst_limit_t __xecall
    Power::GetBurstPowerLimit(
        void
        )
    {
        xet_power_burst_limit_t limit;

        auto result = static_cast<result_t>( ::xetPowerGetBurstPowerLimit(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &limit ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetBurstPowerLimit" );

        return *reinterpret_cast<burst_limit_t*>( &limit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current peak power limit information for a device
    /// 
    /// @returns
    ///     - peak_limit_t: information about the peak power limit
    /// 
    /// @throws result_t
    Power::peak_limit_t __xecall
    Power::GetPeakPowerLimit(
        void
        )
    {
        xet_power_peak_limit_t limit;

        auto result = static_cast<result_t>( ::xetPowerGetPeakPowerLimit(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &limit ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetPeakPowerLimit" );

        return *reinterpret_cast<peak_limit_t*>( &limit );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get all current power limits for a device
    /// 
    /// @returns
    ///     - limits_t: information about the average/burst/peak power limits
    /// 
    /// @throws result_t
    Power::limits_t __xecall
    Power::GetAllPowerLimits(
        void
        )
    {
        xet_power_limits_t limits;

        auto result = static_cast<result_t>( ::xetPowerGetAllPowerLimits(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &limits ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetAllPowerLimits" );

        return *reinterpret_cast<limits_t*>( &limits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get default power limits for a device
    /// 
    /// @returns
    ///     - limits_t: information about the default average/burst/peak power limits
    /// 
    /// @throws result_t
    Power::limits_t __xecall
    Power::GetDefaultPowerLimits(
        void
        )
    {
        xet_power_limits_t limits;

        auto result = static_cast<result_t>( ::xetPowerGetDefaultPowerLimits(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &limits ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetDefaultPowerLimits" );

        return *reinterpret_cast<limits_t*>( &limits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the average power limit for a device
    /// 
    /// @throws result_t
    void __xecall
    Power::SetAveragePowerLimit(
        average_limit_t* pLimit                         ///< [in] information about the average power limit
        )
    {
        auto result = static_cast<result_t>( ::xetPowerSetAveragePowerLimit(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_average_limit_t*>( pLimit ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::SetAveragePowerLimit" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the burst power limit for a device
    /// 
    /// @throws result_t
    void __xecall
    Power::SetBurstPowerLimit(
        burst_limit_t* pLimit                           ///< [in] information about the burst power limit
        )
    {
        auto result = static_cast<result_t>( ::xetPowerSetBurstPowerLimit(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_burst_limit_t*>( pLimit ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::SetBurstPowerLimit" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the peak power limit for a device
    /// 
    /// @throws result_t
    void __xecall
    Power::SetPeakPowerLimit(
        peak_limit_t* pLimit                            ///< [in] information about the peak power limit
        )
    {
        auto result = static_cast<result_t>( ::xetPowerSetPeakPowerLimit(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_peak_limit_t*>( pLimit ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::SetPeakPowerLimit" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the average/burst/peak power limits for a device
    /// 
    /// @throws result_t
    void __xecall
    Power::SetPowerLimits(
        limits_t* pLimits                               ///< [in] information about the average/burst/peak power limits
        )
    {
        auto result = static_cast<result_t>( ::xetPowerSetPowerLimits(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            reinterpret_cast<xet_power_limits_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::SetPowerLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy counter
    /// 
    /// @details
    ///     - Average power = delta(energy counter in millijoules) / delta(time in
    ///       milliseconds)
    /// 
    /// @returns
    ///     - uint64_t: the energy counter in millijoules
    /// 
    /// @throws result_t
    uint64_t __xecall
    Power::GetEnergyCounter(
        void
        )
    {
        uint64_t energy;

        auto result = static_cast<result_t>( ::xetPowerGetEnergyCounter(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &energy ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetEnergyCounter" );

        return energy;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current Turbo mode for a device
    /// 
    /// @returns
    ///     - turbo_mode_t: turbo mode currently in effect
    /// 
    /// @throws result_t
    Power::turbo_mode_t __xecall
    Power::GetTurboMode(
        void
        )
    {
        xet_turbo_mode_t turboMode;

        auto result = static_cast<result_t>( ::xetPowerGetTurboMode(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &turboMode ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetTurboMode" );

        return *reinterpret_cast<turbo_mode_t*>( &turboMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the current Turbo mode for a device
    /// 
    /// @throws result_t
    void __xecall
    Power::SetTurboMode(
        turbo_mode_t pTurboMode                         ///< [in] new turbo mode
        )
    {
        auto result = static_cast<result_t>( ::xetPowerSetTurboMode(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            static_cast<xet_turbo_mode_t>( pTurboMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::SetTurboMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves frequency domains on a device
    /// 
    /// @throws result_t
    void __xecall
    FreqDomain::Get(
        Power* pPower,                                  ///< [in] pointer to the power object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequency domains.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of frequency domains available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< frequency domains.
                                                        ///< if count is larger than the number of frequency domains available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< frequency domains available.
        FreqDomain** ppFreqDomain                       ///< [in,out][optional][range(0, *pCount)] array of pointer to frequency
                                                        ///< domains
        )
    {
        thread_local std::vector<xet_freq_domain_handle_t> hFreqDomain;
        hFreqDomain.resize( ( ppFreqDomain ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xetFreqDomainGet(
            reinterpret_cast<xet_power_handle_t>( pPower->getHandle() ),
            pCount,
            hFreqDomain.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::Get" );

        for( uint32_t i = 0; ( ppFreqDomain ) && ( i < *pCount ); ++i )
            ppFreqDomain[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFreqDomain ) && ( i < *pCount ); ++i )
                ppFreqDomain[ i ] = new FreqDomain( pPower );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFreqDomain ) && ( i < *pCount ); ++i )
            {
                delete ppFreqDomain[ i ];
                ppFreqDomain[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::FreqDomain::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the properties for a frequency domain
    /// 
    /// @returns
    ///     - properties_t: pointer to properties for the frequency domain
    /// 
    /// @throws result_t
    FreqDomain::properties_t __xecall
    FreqDomain::GetProperties(
        void
        )
    {
        xet_freq_domain_properties_t freqDomainProperties;

        auto result = static_cast<result_t>( ::xetFreqDomainGetProperties(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            &freqDomainProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::GetProperties" );

        return *reinterpret_cast<properties_t*>( &freqDomainProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the source frequency domain handle for a frequency domain of type
    ///        ::XET_CLOCK_TYPE_DIVIDER
    /// 
    /// @returns
    ///     - FreqDomain*: pointer to a handle where the source frequency domain handle will be returned
    /// 
    /// @throws result_t
    FreqDomain* __xecall
    FreqDomain::GetSourceFreqDomain(
        void
        )
    {
        xet_freq_domain_handle_t hSrcFreqDomain;

        auto result = static_cast<result_t>( ::xetFreqDomainGetSourceFreqDomain(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            &hSrcFreqDomain ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::GetSourceFreqDomain" );

        FreqDomain* pSrcFreqDomain = nullptr;

        try
        {
            pSrcFreqDomain = new FreqDomain( m_pPower );
        }
        catch( std::bad_alloc& )
        {
            delete pSrcFreqDomain;
            pSrcFreqDomain = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::FreqDomain::GetSourceFreqDomain" );
        }

        return pSrcFreqDomain;
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
    ///     - uint32_t: pointer to array of frequencies
    /// 
    /// @throws result_t
    uint32_t __xecall
    FreqDomain::GetSupportedClocks(
        uint32_t numClockPoints                         ///< [in] number of elements in pClocks
        )
    {
        uint32_t clocks;

        auto result = static_cast<result_t>( ::xetFreqDomainGetSupportedClocks(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            numClockPoints,
            &clocks ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::GetSupportedClocks" );

        return clocks;
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
    ///     - clock_divider_t: pointer to array of dividers
    /// 
    /// @throws result_t
    FreqDomain::clock_divider_t __xecall
    FreqDomain::GetSupportedClockDividers(
        uint32_t numClockDividers                       ///< [in] number of elements in pDividers
        )
    {
        xet_clock_divider_t dividers;

        auto result = static_cast<result_t>( ::xetFreqDomainGetSupportedClockDividers(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            numClockDividers,
            &dividers ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::GetSupportedClockDividers" );

        return *reinterpret_cast<clock_divider_t*>( &dividers );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the frequency range for a frequency domain with clock type
    ///        ::XET_CLOCK_TYPE_PLL.
    /// 
    /// @returns
    ///     - uint32_t: min clock frequency in units of MHz
    ///     - uint32_t: max clock frequency in units of MHz
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t> __xecall
    FreqDomain::GetClockRange(
        void
        )
    {
        uint32_t minClock;

        uint32_t maxClock;

        auto result = static_cast<result_t>( ::xetFreqDomainGetClockRange(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            &minClock,
            &maxClock ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::GetClockRange" );

        return std::make_tuple( minClock, maxClock );
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
    /// @throws result_t
    void __xecall
    FreqDomain::SetClockRange(
        uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
        uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
        )
    {
        auto result = static_cast<result_t>( ::xetFreqDomainSetClockRange(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            minClock,
            maxClock ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::SetClockRange" );
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
    ///     - clock_divider_t: pointer to frequency divider request
    /// 
    /// @throws result_t
    FreqDomain::clock_divider_t __xecall
    FreqDomain::SetClockDivider(
        void
        )
    {
        xet_clock_divider_t clockDividerRequest;

        auto result = static_cast<result_t>( ::xetFreqDomainSetClockDivider(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            &clockDividerRequest ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::SetClockDivider" );

        return *reinterpret_cast<clock_divider_t*>( &clockDividerRequest );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency
    /// 
    /// @returns
    ///     - uint32_t: current frequency in MHz requested by the driver
    ///     - uint32_t: the actual frequency in MHz
    ///     - freq_throttle_reasons_t: the reason the resolved frequency is lower than the request
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t, FreqDomain::freq_throttle_reasons_t> __xecall
    FreqDomain::GetCurrentFrequency(
        void
        )
    {
        uint32_t freqRequest;

        uint32_t freqResolved;

        xet_freq_throttle_reasons_t freqThrottleReasons;

        auto result = static_cast<result_t>( ::xetFreqDomainGetCurrentFrequency(
            reinterpret_cast<xet_freq_domain_handle_t>( getHandle() ),
            &freqRequest,
            &freqResolved,
            &freqThrottleReasons ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::FreqDomain::GetCurrentFrequency" );

        return std::make_tuple( freqRequest, freqResolved, *reinterpret_cast<freq_throttle_reasons_t*>( &freqThrottleReasons ) );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get number of fans on the device
    /// 
    /// @returns
    ///     - uint32_t: the number of fans on the device
    /// 
    /// @throws result_t
    uint32_t __xecall
    Power::FanCount(
        void
        )
    {
        uint32_t fanCount;

        auto result = static_cast<result_t>( ::xetPowerFanCount(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &fanCount ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::FanCount" );

        return fanCount;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan properties for one of the fans on a device
    /// 
    /// @returns
    ///     - fan_properties_t: pointer to storage for fan properties
    /// 
    /// @throws result_t
    Power::fan_properties_t __xecall
    Power::FanGetProperties(
        uint32_t fanIndex                               ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        )
    {
        xet_fan_properties_t fanProperties;

        auto result = static_cast<result_t>( ::xetPowerFanGetProperties(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            fanIndex,
            &fanProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::FanGetProperties" );

        return *reinterpret_cast<fan_properties_t*>( &fanProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan speed table
    /// 
    /// @details
    ///     - Set pFanSpeedTable = nullptr to find out the current number of fan
    ///       speed points in the table.
    /// 
    /// @returns
    ///     - fan_point_t: pointer to an array of temperature/fan-speed points
    /// 
    /// @throws result_t
    Power::fan_point_t __xecall
    Power::FanGetSpeedTable(
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        xe::bool_t fanSpeedInRpm,                       ///< [in] true will request fan speeds in RPM, otherwise in percentage
        uint32_t* pNumFanPoints                         ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                        ///< number of elements returned
        )
    {
        xet_fan_point_t fanPoints;

        auto result = static_cast<result_t>( ::xetPowerFanGetSpeedTable(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            fanIndex,
            static_cast<xe_bool_t>( fanSpeedInRpm ),
            pNumFanPoints,
            &fanPoints ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::FanGetSpeedTable" );

        return *reinterpret_cast<fan_point_t*>( &fanPoints );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan speed table
    /// 
    /// @details
    ///     - Use ::xetPowerFanGetProperties to determine acceptable units for fan
    ///       speed (percent, RPM).
    ///     - Fan points should be ordered according to increasing temperature.
    /// 
    /// @throws result_t
    void __xecall
    Power::FanSetSpeedTable(
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
        fan_point_t* pFanPoints                         ///< [in] pointer to an array of temperature/fan-speed points
        )
    {
        auto result = static_cast<result_t>( ::xetPowerFanSetSpeedTable(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            fanIndex,
            numFanPoints,
            reinterpret_cast<xet_fan_point_t*>( pFanPoints ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::FanSetSpeedTable" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current fan speeds
    /// 
    /// @details
    ///     - The array pFanSpeed must contain at least numFans entries.
    /// 
    /// @returns
    ///     - fan_speed_info_t: pointer to an array of current fan speeds
    /// 
    /// @throws result_t
    Power::fan_speed_info_t __xecall
    Power::FanGetSpeed(
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        xe::bool_t fanSpeedInRpm                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
        )
    {
        xet_fan_speed_info_t fanSpeed;

        auto result = static_cast<result_t>( ::xetPowerFanGetSpeed(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            startFanIndex,
            numFans,
            static_cast<xe_bool_t>( fanSpeedInRpm ),
            &fanSpeed ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::FanGetSpeed" );

        return *reinterpret_cast<fan_speed_info_t*>( &fanSpeed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan speeds
    /// 
    /// @details
    ///     - Use ::xet_fan_speed_info_t.fanSpeedMode to set whether the speed
    ///       should be fixed or dynamically controlled
    /// 
    /// @throws result_t
    void __xecall
    Power::FanSetSpeed(
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        fan_speed_info_t* pFanSpeed                     ///< [in] pointer to an array of current fan speeds
        )
    {
        auto result = static_cast<result_t>( ::xetPowerFanSetSpeed(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            startFanIndex,
            numFans,
            reinterpret_cast<xet_fan_speed_info_t*>( pFanSpeed ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::FanSetSpeed" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get number of temperature sensors on the device
    /// 
    /// @returns
    ///     - uint32_t: the number of temperature sensors on the device
    /// 
    /// @throws result_t
    uint32_t __xecall
    Power::TemperatureSensorCount(
        void
        )
    {
        uint32_t sensorCount;

        auto result = static_cast<result_t>( ::xetPowerTemperatureSensorCount(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &sensorCount ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::TemperatureSensorCount" );

        return sensorCount;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperatures sensor properties
    /// 
    /// @details
    ///     - Temperature sensor index 0 is special - it gives the maximum
    ///       temperature across all sensors
    /// 
    /// @returns
    ///     - temperature_properties_t: pointer to properties for this sensor
    /// 
    /// @throws result_t
    Power::temperature_properties_t __xecall
    Power::GetTemperatureProperties(
        uint32_t sensorIndex                            ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        )
    {
        xet_temperature_properties_t properties;

        auto result = static_cast<result_t>( ::xetPowerGetTemperatureProperties(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            sensorIndex,
            &properties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetTemperatureProperties" );

        return *reinterpret_cast<temperature_properties_t*>( &properties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current temperatures
    /// 
    /// @details
    ///     - Temperature sensor index 0 is special - it gives the maximum
    ///       temperature across all sensors
    /// 
    /// @returns
    ///     - uint16_t: pointer to an array of temperatures in units of degrees celsius
    /// 
    /// @throws result_t
    uint16_t __xecall
    Power::GetTemperature(
        uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        uint32_t numSensors                             ///< [in] pTemperatures will contain results for sensors index
                                                        ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
        )
    {
        uint16_t temperatures;

        auto result = static_cast<result_t>( ::xetPowerGetTemperature(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            startSensorIndex,
            numSensors,
            &temperatures ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetTemperature" );

        return temperatures;
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
    /// @throws result_t
    void __xecall
    Power::SetTemperatureThreshold(
        uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                        ///< will be throttled
        )
    {
        auto result = static_cast<result_t>( ::xetPowerSetTemperatureThreshold(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            sensorIndex,
            maxTemperature ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::SetTemperatureThreshold" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get number of activity counters
    /// 
    /// @returns
    ///     - uint32_t: the number of activity counters on the device
    /// 
    /// @throws result_t
    uint32_t __xecall
    Power::ActivityCount(
        void
        )
    {
        uint32_t activityCount;

        auto result = static_cast<result_t>( ::xetPowerActivityCount(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            &activityCount ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::ActivityCount" );

        return activityCount;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get activity counter properties
    /// 
    /// @details
    ///     - Activity counter index 0 is special - it acculates activity across all
    ///       blocks.
    /// 
    /// @returns
    ///     - activity_properties_t: pointer to properties for this activity counter
    /// 
    /// @throws result_t
    Power::activity_properties_t __xecall
    Power::GetActivityProperties(
        uint32_t activityIndex                          ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
        )
    {
        xet_activity_properties_t properties;

        auto result = static_cast<result_t>( ::xetPowerGetActivityProperties(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            activityIndex,
            &properties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetActivityProperties" );

        return *reinterpret_cast<activity_properties_t*>( &properties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get activity counters
    /// 
    /// @details
    ///     - Activity counter index 0 is special - it acculates activity across all
    ///       blocks.
    /// 
    /// @returns
    ///     - activity_counters_t: pointer to an array of activity counter data
    /// 
    /// @throws result_t
    Power::activity_counters_t __xecall
    Power::GetActivityCounters(
        uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
        uint32_t numCounters                            ///< [in] pCounters will contain results for activity counter index
                                                        ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
        )
    {
        xet_activity_counters_t counters;

        auto result = static_cast<result_t>( ::xetPowerGetActivityCounters(
            reinterpret_cast<xet_power_handle_t>( getHandle() ),
            startCounterIndex,
            numCounters,
            &counters ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Power::GetActivityCounters" );

        return *reinterpret_cast<activity_counters_t*>( &counters );
    }

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts fan_capabilities_t to std::string
    std::string to_string( const fan_capabilities_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(fan_capabilities_t::GET_SPEED_PERCENTAGE) & bits )
            str += "GET_SPEED_PERCENTAGE | ";
        
        if( static_cast<uint32_t>(fan_capabilities_t::SET_SPEED_PERCENTAGE) & bits )
            str += "SET_SPEED_PERCENTAGE | ";
        
        if( static_cast<uint32_t>(fan_capabilities_t::GET_SPEED_RPM) & bits )
            str += "GET_SPEED_RPM | ";
        
        if( static_cast<uint32_t>(fan_capabilities_t::SET_SPEED_RPM) & bits )
            str += "SET_SPEED_RPM | ";
        
        if( static_cast<uint32_t>(fan_capabilities_t::HAVE_TEMPERATURE_SPEED_TABLE) & bits )
            str += "HAVE_TEMPERATURE_SPEED_TABLE | ";

        return ( str.size() > 3 ) 
            ? "fan_capabilities_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "fan_capabilities_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts fan_speed_mode_t to std::string
    std::string to_string( const fan_speed_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case fan_speed_mode_t::AUTO:
            str = "fan_speed_mode_t::AUTO";
            break;

        case fan_speed_mode_t::FIXED:
            str = "fan_speed_mode_t::FIXED";
            break;

        default:
            str = "fan_speed_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::init_flags_t to std::string
    std::string to_string( const Power::init_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Power::init_flags_t::WRITE) & bits )
            str += "WRITE | ";

        return ( str.size() > 3 ) 
            ? "Power::init_flags_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Power::init_flags_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::gpu_domain_t to std::string
    std::string to_string( const Power::gpu_domain_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::BASE) & bits )
            str += "BASE | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::VIDEO_DECODE) & bits )
            str += "VIDEO_DECODE | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::VIDEO_ENCODE) & bits )
            str += "VIDEO_ENCODE | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::VIDEO_PROCESSING) & bits )
            str += "VIDEO_PROCESSING | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::_3D_FIXED_FUNCTION) & bits )
            str += "_3D_FIXED_FUNCTION | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::_3D_RENDER) & bits )
            str += "_3D_RENDER | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::COMPUTE) & bits )
            str += "COMPUTE | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::SYSTOLIC_ARRAY) & bits )
            str += "SYSTOLIC_ARRAY | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::RAYTRACING) & bits )
            str += "RAYTRACING | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::LOCAL_MEMORY) & bits )
            str += "LOCAL_MEMORY | ";
        
        if( static_cast<uint32_t>(Power::gpu_domain_t::BASE_CHIPLET_LINK) & bits )
            str += "BASE_CHIPLET_LINK | ";

        return ( str.size() > 3 ) 
            ? "Power::gpu_domain_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Power::gpu_domain_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::average_limit_version_t to std::string
    std::string to_string( const Power::average_limit_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Power::average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT:
            str = "Power::average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT";
            break;

        default:
            str = "Power::average_limit_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::turbo_mode_t to std::string
    std::string to_string( const Power::turbo_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Power::turbo_mode_t::DISABLED:
            str = "Power::turbo_mode_t::DISABLED";
            break;

        case Power::turbo_mode_t::DEFAULT:
            str = "Power::turbo_mode_t::DEFAULT";
            break;

        case Power::turbo_mode_t::MIN_PERFORMANCE:
            str = "Power::turbo_mode_t::MIN_PERFORMANCE";
            break;

        case Power::turbo_mode_t::EFFICIENT_PERFORMANCE:
            str = "Power::turbo_mode_t::EFFICIENT_PERFORMANCE";
            break;

        case Power::turbo_mode_t::AGGRESSIVE_PERFORMANCE:
            str = "Power::turbo_mode_t::AGGRESSIVE_PERFORMANCE";
            break;

        case Power::turbo_mode_t::MAX_PERFORMANCE:
            str = "Power::turbo_mode_t::MAX_PERFORMANCE";
            break;

        default:
            str = "Power::turbo_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::average_limit_t to std::string
    std::string to_string( const Power::average_limit_t val )
    {
        std::string str;
        
        str += "Power::average_limit_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Power::average_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Power::average_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";
        
        str += "Power::average_limit_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::burst_limit_t to std::string
    std::string to_string( const Power::burst_limit_t val )
    {
        std::string str;
        
        str += "Power::burst_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Power::burst_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::peak_limit_t to std::string
    std::string to_string( const Power::peak_limit_t val )
    {
        std::string str;
        
        str += "Power::peak_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::limits_t to std::string
    std::string to_string( const Power::limits_t val )
    {
        std::string str;
        
        str += "Power::limits_t::averagePowerLimit : ";
        str += to_string(val.averagePowerLimit);
        str += "\n";
        
        str += "Power::limits_t::burstPowerLimit : ";
        str += to_string(val.burstPowerLimit);
        str += "\n";
        
        str += "Power::limits_t::peakPowerLimit : ";
        str += to_string(val.peakPowerLimit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::fan_properties_t to std::string
    std::string to_string( const Power::fan_properties_t val )
    {
        std::string str;
        
        str += "Power::fan_properties_t::fanCapabilities : ";
        str += std::to_string(val.fanCapabilities);
        str += "\n";
        
        str += "Power::fan_properties_t::maxRpm : ";
        str += std::to_string(val.maxRpm);
        str += "\n";
        
        str += "Power::fan_properties_t::maxTemperatureSpeedPoints : ";
        str += std::to_string(val.maxTemperatureSpeedPoints);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::fan_point_t to std::string
    std::string to_string( const Power::fan_point_t val )
    {
        std::string str;
        
        str += "Power::fan_point_t::fanSpeedInRpm : ";
        str += std::to_string(val.fanSpeedInRpm);
        str += "\n";
        
        str += "Power::fan_point_t::temperatureDegreesCentigrate : ";
        str += std::to_string(val.temperatureDegreesCentigrate);
        str += "\n";
        
        str += "Power::fan_point_t::fanSpeed : ";
        str += std::to_string(val.fanSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::fan_speed_info_t to std::string
    std::string to_string( const Power::fan_speed_info_t val )
    {
        std::string str;
        
        str += "Power::fan_speed_info_t::fanSpeedInRpm : ";
        str += std::to_string(val.fanSpeedInRpm);
        str += "\n";
        
        str += "Power::fan_speed_info_t::fanSpeedMode : ";
        str += to_string(val.fanSpeedMode);
        str += "\n";
        
        str += "Power::fan_speed_info_t::fanSpeed : ";
        str += std::to_string(val.fanSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::temperature_properties_t to std::string
    std::string to_string( const Power::temperature_properties_t val )
    {
        std::string str;
        
        str += "Power::temperature_properties_t::location : ";
        str += std::to_string(val.location);
        str += "\n";
        
        str += "Power::temperature_properties_t::maxTemperature : ";
        str += std::to_string(val.maxTemperature);
        str += "\n";
        
        str += "Power::temperature_properties_t::shutdownTemperature : ";
        str += std::to_string(val.shutdownTemperature);
        str += "\n";
        
        str += "Power::temperature_properties_t::canChangeThreshold : ";
        str += std::to_string(val.canChangeThreshold);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::activity_properties_t to std::string
    std::string to_string( const Power::activity_properties_t val )
    {
        std::string str;
        
        str += "Power::activity_properties_t::blocks : ";
        str += std::to_string(val.blocks);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::activity_counters_t to std::string
    std::string to_string( const Power::activity_counters_t val )
    {
        std::string str;
        
        str += "Power::activity_counters_t::activityCounter : ";
        str += std::to_string(val.activityCounter);
        str += "\n";
        
        str += "Power::activity_counters_t::idleCounter : ";
        str += std::to_string(val.idleCounter);
        str += "\n";
        
        str += "Power::activity_counters_t::timeCounter : ";
        str += std::to_string(val.timeCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FreqDomain::clock_type_t to std::string
    std::string to_string( const FreqDomain::clock_type_t val )
    {
        std::string str;

        switch( val )
        {
        case FreqDomain::clock_type_t::FIXED:
            str = "FreqDomain::clock_type_t::FIXED";
            break;

        case FreqDomain::clock_type_t::PLL:
            str = "FreqDomain::clock_type_t::PLL";
            break;

        case FreqDomain::clock_type_t::DIVIDER:
            str = "FreqDomain::clock_type_t::DIVIDER";
            break;

        default:
            str = "FreqDomain::clock_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FreqDomain::freq_throttle_reasons_t to std::string
    std::string to_string( const FreqDomain::freq_throttle_reasons_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::AVE_PWR_CAP) & bits )
            str += "AVE_PWR_CAP | ";
        
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::BURST_PWR_CAP) & bits )
            str += "BURST_PWR_CAP | ";
        
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::CURRENT_LIMIT) & bits )
            str += "CURRENT_LIMIT | ";
        
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::THERMAL_LIMIT) & bits )
            str += "THERMAL_LIMIT | ";
        
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::PSU_ALERT) & bits )
            str += "PSU_ALERT | ";
        
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::SW_RANGE) & bits )
            str += "SW_RANGE | ";
        
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::HW_RANGE) & bits )
            str += "HW_RANGE | ";

        return ( str.size() > 3 ) 
            ? "FreqDomain::freq_throttle_reasons_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "FreqDomain::freq_throttle_reasons_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FreqDomain::properties_t to std::string
    std::string to_string( const FreqDomain::properties_t val )
    {
        std::string str;
        
        str += "FreqDomain::properties_t::gpuDomains : ";
        str += std::to_string(val.gpuDomains);
        str += "\n";
        
        str += "FreqDomain::properties_t::clockType : ";
        str += to_string(val.clockType);
        str += "\n";
        
        str += "FreqDomain::properties_t::minClock : ";
        str += std::to_string(val.minClock);
        str += "\n";
        
        str += "FreqDomain::properties_t::maxClock : ";
        str += std::to_string(val.maxClock);
        str += "\n";
        
        str += "FreqDomain::properties_t::numClockPoints : ";
        str += std::to_string(val.numClockPoints);
        str += "\n";
        
        str += "FreqDomain::properties_t::numClockDividers : ";
        str += std::to_string(val.numClockDividers);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FreqDomain::clock_divider_t to std::string
    std::string to_string( const FreqDomain::clock_divider_t val )
    {
        std::string str;
        
        str += "FreqDomain::clock_divider_t::numerator : ";
        str += std::to_string(val.numerator);
        str += "\n";
        
        str += "FreqDomain::clock_divider_t::denominator : ";
        str += std::to_string(val.denominator);
        str += "\n";

        return str;
    }

} // namespace xet
