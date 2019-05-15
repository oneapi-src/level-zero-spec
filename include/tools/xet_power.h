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
* @file xet_power.h
*
* @brief Intel Xe Level-Zero Tool APIs for Power
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/power.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_POWER_H
#define _XET_POWER_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xet_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Power initialization flags (bitfield)
typedef enum _xet_power_init_flags_t
{
    XET_POWER_INIT_FLAGS_NONE = 0,                  ///< default initialization
    XET_POWER_INIT_FLAGS_WRITE = XE_BIT( 0 ),       ///< request access to power controls

} xet_power_init_flags_t;

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
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
    xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
    );

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
    xet_power_handle_t hPower                       ///< [in] handle of the power object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief GPU domains
typedef enum _xet_gpu_domain_t
{
    XET_GPU_DOMAIN_BASE = XE_BIT( 0 ),              ///< base die
    XET_GPU_DOMAIN_VIDEO_DECODE = XE_BIT( 1 ),      ///< video decode engines
    XET_GPU_DOMAIN_VIDEO_ENCODE = XE_BIT( 2 ),      ///< video encode engines
    XET_GPU_DOMAIN_VIDEO_PROCESSING = XE_BIT( 3 ),  ///< video processing engines
    XET_GPU_DOMAIN_3D_FIXED_FUNCTION = XE_BIT( 4 ), ///< 3D fixed-function
    XET_GPU_DOMAIN_3D_RENDER = XE_BIT( 5 ),         ///< 3D programmable engines
    XET_GPU_DOMAIN_COMPUTE = XE_BIT( 6 ),           ///< compute engines
    XET_GPU_DOMAIN_SYSTOLIC_ARRAY = XE_BIT( 7 ),    ///< systolic array engines
    XET_GPU_DOMAIN_RAYTRACING = XE_BIT( 8 ),        ///< raytracing engines
    XET_GPU_DOMAIN_LOCAL_MEMORY = XE_BIT( 9 ),      ///< local memory
    XET_GPU_DOMAIN_BASE_CHIPLET_LINK = XE_BIT( 10 ),///< link between base die and chiplet

} xet_gpu_domain_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_power_average_limit_t
typedef enum _xet_power_average_limit_version_t
{
    XET_AVERAGE_POWER_LIMIT_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xet_power_average_limit_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Average power limit
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency of
///       the device if the power averaged over a window (typically seconds)
///       exceeds a limit known as PL1.
typedef struct _xet_power_average_limit_t
{
    xet_power_average_limit_version_t version;      ///< [in] ::XET_AVERAGE_POWER_LIMIT_VERSION_CURRENT
    xe_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts
    uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

} xet_power_average_limit_t;

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
/// @brief All power limits
typedef struct _xet_power_limits_t
{
    xet_power_average_limit_t averagePowerLimit;    ///< [in,out] average power limit information
    xet_power_burst_limit_t burstPowerLimit;        ///< [in,out] burst power limit information
    xet_power_peak_limit_t peakPowerLimit;          ///< [in,out] peak power limit information

} xet_power_limits_t;

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Turbo (dynamic hardware frequency management) modes
typedef enum _xet_turbo_mode_t
{
    XET_TURBO_MODE_DISABLED = 0,                    ///< DVFS is currently disabled - frequency is fixed
    XET_TURBO_MODE_DEFAULT,                         ///< hardware default DVFS (typically EFFICIENT)
    XET_TURBO_MODE_MIN_PERFORMANCE,                 ///< min efficient frequency unless specific applications require otherwise
    XET_TURBO_MODE_EFFICIENT_PERFORMANCE,           ///< balanced power and performance
    XET_TURBO_MODE_AGGRESSIVE_PERFORMANCE,          ///< aggressively favor performance over power
    XET_TURBO_MODE_MAX_PERFORMANCE,                 ///< fixed max frequency unless limited by thermals/power

} xet_turbo_mode_t;

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Clock types
typedef enum _xet_clock_type_t
{
    XET_CLOCK_TYPE_FIXED = 0,                       ///< fixed crystal clock
    XET_CLOCK_TYPE_PLL,                             ///< phase-locked-loop (PLL) frequency range
    XET_CLOCK_TYPE_DIVIDER,                         ///< frequency is linked to another domain by a divider

} xet_clock_type_t;

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
/// @brief Properties of a frequency domain
/// 
/// @details
///     - A frequency domain contains one or more GPU functional blocks - see
///       ::xet_gpu_domain_t
///     - There is more than one type of clock - check clockType
///     - For clock type ::XET_CLOCK_TYPE_FIXED, minClock and maxClock will be
///       the same and numClockPoints will be 1.
///     - For clock type ::XET_CLOCK_TYPE_PLL, numClockPoints is given for
///       informational purposes. Do not assume the frequency step between
///       min/max clocks is (max - min) / (numClockPoints - 1). Instead, use the
///       function ::xetFreqDomainGetSupportedClocks to get the list of all
///       supported clocks between min/max.
///     - For clock type ::XET_CLOCK_TYPE_DIVIDER, the frequency of the domain
///       is given by multiplying the divider by the frequency of the source
///       domain. The possible divider values can be obtained using the function
///       ::xetFreqDomainGetSupportedClockDividers. For this clock type,
///       minClock/maxClock specifies the total range of frequencies whereas the
///       actual range depends on the current divider value.
typedef struct _xet_freq_domain_properties_t
{
    uint32_t gpuDomains;                            ///< [in] bitfield of xex_gpu_domain_t
    xet_clock_type_t clockType;                     ///< [in] clock type
    uint32_t minClock;                              ///< [in] minimum frequency of the domain
    uint32_t maxClock;                              ///< [in] maximum frequency of the domain
    uint32_t numClockPoints;                        ///< [in] number of discrete clock points between and including min/max
    uint32_t numClockDividers;                      ///< [in] for clock type ::XET_CLOCK_TYPE_DIVIDER, this gives the number of
                                                    ///< dividers available

} xet_freq_domain_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency divider configuration
/// 
/// @details
///     - The frequency of a domain of type ::XET_CLOCK_TYPE_DIVIDER is obtained
///       by the formula:
///     - freq = source domain freq * numerator / denominator
typedef struct _xet_clock_divider_t
{
    uint16_t numerator;                             ///< [in,out] numerator of the ratio
    uint16_t denominator;                           ///< [in,out] denominator of the ratio

} xet_clock_divider_t;

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
xe_result_t __xecall
xetPowerGetFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    );

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
xe_result_t __xecall
xetPowerGetFreqDomain(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t ordinal,                               ///< [in] frequency domain index [0 .. ::xetPowerGetFreqDomainCount - 1]
    xet_freq_domain_handle_t* phFreqDomain          ///< [out] pointer to handle of frequency domain object
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan capabilities
typedef enum _xet_fan_capabilities_t
{
    XET_FAN_CAPABILITIES_GET_SPEED_PERCENTAGE = XE_BIT( 0 ),///< can query fan speed as a percentage
    XET_FAN_CAPABILITIES_SET_SPEED_PERCENTAGE = XE_BIT( 1 ),///< can set fan speed as a percentage
    XET_FAN_CAPABILITIES_GET_SPEED_RPM = XE_BIT( 2 ),   ///< can query fan speed as rpm
    XET_FAN_CAPABILITIES_SET_SPEED_RPM = XE_BIT( 3 ),   ///< can set fan speed as rpm
    XET_FAN_CAPABILITIES_HAVE_TEMPERATURE_SPEED_TABLE = XE_BIT( 4 ),///< can set temperature/fan speed table

} xet_fan_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan speed modes
typedef enum _xet_fan_speed_mode_t
{
    XET_FAN_SPEED_MODE_AUTO = 0,                    ///< fan speed is dynamically controlled based on temperature
    XET_FAN_SPEED_MODE_FIXED,                       ///< fan speed is fixed

} xet_fan_speed_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan properties
typedef struct _xet_fan_properties_t
{
    uint32_t fanCapabilities;                       ///< [in] bitfield of ::xet_fan_capabilities_t
    uint32_t maxRpm;                                ///< [in] maximum RPM of the fan. Will be 0 if maximum is not known.
    uint32_t maxTemperatureSpeedPoints;             ///< [in] the maximum number of temperature/fan-speed points that can be
                                                    ///< programmed

} xet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature/fan-speed point
typedef struct _xet_fan_point_t
{
    xe_bool_t fanSpeedInRpm;                        ///< [in,out] false means fanSpeed is in percentage, true means fanSpeed is
                                                    ///< in RPM
    uint16_t temperatureDegreesCentigrate;          ///< [in,out] temperature in degrees centigrate
    uint16_t fanSpeed;                              ///< [in,out] the fan speed as a percentage (or RPM if fanSpeedInRpm is
                                                    ///< true)

} xet_fan_point_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan speed info
typedef struct _xet_fan_speed_info_t
{
    xe_bool_t fanSpeedInRpm;                        ///< [in,out] false means fanSpeed is in percentage, true means fanSpeed is
                                                    ///< in RPM
    xet_fan_speed_mode_t fanSpeedMode;              ///< [in,out] whether the fan speed is fixed or being controlled
                                                    ///< dynamically
    uint16_t fanSpeed;                              ///< [in,out] the fan speed as a percentage (or RPM if fanSpeedInRpm is
                                                    ///< true)

} xet_fan_speed_info_t;

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor properties
/// 
/// @details
///     - Temperature sensor index 0 is special - it is a virtual sensor that
///       gives the max across all sensors. The member **location** equals
///       0xFFFFFFFF in this case.
///     - Most systems apply the temperature threshold globally. In this case,
///       member **canChangeThreshold** will only be true for sensor index 0.
typedef struct _xet_temperature_properties_t
{
    uint32_t location;                              ///< [in] bitfield of ::xet_gpu_domain_t whose temperature is measured by
                                                    ///< this sensor
    uint16_t maxTemperature;                        ///< [in] the temperature limit in celsius beyond which the power control
                                                    ///< unit (Punit) will throttle the frequency
    uint16_t shutdownTemperature;                   ///< [in] the temperature limit in celsius beyond which the power control
                                                    ///< unit (Punit) will shutdown the device
    xe_bool_t canChangeThreshold;                   ///< [in] true indicates that this a different threshold can be set

} xet_temperature_properties_t;

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
    );

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
    );

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Activity counter properties
/// 
/// @details
///     - Activity counter 0 is a normalized accumulation of activity across all
///       blocks. The member **blocks** equals 0xFFFFFFFF in this case.
typedef struct _xet_activity_properties_t
{
    uint32_t blocks;                                ///< [in] bitfield of ::xet_gpu_domain_t whose activity is included in this
                                                    ///< counter

} xet_activity_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Activity counter data
/// 
/// @details
///     - Activity counter 0 is a normalized accumulation of activity across all
///       blocks.
///     - Samples these counters between two points and calculate utilization by
///       dividing delta(activityCounter) / delta(timeCounter).
///     - Powered down time is given by timeCounter - activityCounter -
///       idleCounter.
typedef struct _xet_activity_counters_t
{
    uint64_t activityCounter;                       ///< [out] Monotonically increasing counter of activity in microseconds
    uint64_t idleCounter;                           ///< [out] Monotonically increasing counter of time blocks are powered on
                                                    ///< but idle in microseconds
    uint64_t timeCounter;                           ///< [out] Monotonically increasing counter of time in microseconds

} xet_activity_counters_t;

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
    );

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
    );

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
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_POWER_H
