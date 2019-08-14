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
/// @brief Device mode
typedef enum _xet_operating_mode_t
{
    XET_OPERATING_MODE_DEFAULT = 0,                 ///< Multiple workloads are running on the device
    XET_OPERATING_MODE_EXCLUSIVE_COMPUTE_PROCESS,   ///< A single process submitting compute workloads can monopolize the
                                                    ///< accelerator resources

} xet_operating_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domains
typedef enum _xet_freq_domain_t
{
    XET_FREQ_DOMAIN_GPU = 0,                        ///< Frequency of the GPU.
    XET_FREQ_DOMAIN_MEMORY,                         ///< Frequency of the local memory.
    XET_FREQ_DOMAIN_NUM,                            ///< The total number of frequency domains.

} xet_freq_domain_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _xet_sysman_event_type_t
{
    XET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED = 0,       ///< The frequency is being throttled
    XET_SYSMAN_EVENT_TYPE_PCU_INTERRUPT,            ///< Interrupt from the PCU
    XET_SYSMAN_EVENT_TYPE_RAS_ERRORS,               ///< ECC/RAS errors
    XET_SYSMAN_EVENT_TYPE_NUM,                      ///< The number of event types

} xet_sysman_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties
typedef struct _xet_sysman_properties_t
{
    xe_device_type_t type;                          ///< [out] generic device type
    uint32_t vendorId;                              ///< [out] vendorId from PCI configuration
    uint32_t deviceId;                              ///< [out] deviceId from PCI configuration
    xe_device_uuid_t uuid;                          ///< [out] Device UUID
    xe_bool_t isSubdevice;                          ///< [out] If this handle refers to a sub-device.
    uint32_t subdeviceId;                           ///< [out] sub-device id. Only valid if isSubdevice is true.
    int8_t serialNumber[XET_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
    int8_t boardNumber[XET_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
    int8_t brandName[XET_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
    int8_t modelName[XET_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
    int8_t vendorName[XET_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
    int8_t driverVersion[XET_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)
    xe_bool_t numSwitches;                          ///< [out] The number of switches on the device
    uint32_t numFirmwares;                          ///< [out] Number of firmwares that can be managed
    uint32_t numPsus;                               ///< [out] Number of power supply units that can be managed
    uint32_t numFans;                               ///< [out] Number of fans that can be managed
    uint32_t numLeds;                               ///< [out] Number of LEDs that can be managed
    xe_bool_t supportedEvents[XET_SYSMAN_EVENT_TYPE_NUM];   ///< [out] Set to true for the events that are supported

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
/// @brief Get operating mode of the device
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
xetSysmanDeviceGetOperatingMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_operating_mode_t* pMode                     ///< [in] The current operating mode of the device.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set operating mode of the device
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
xetSysmanDeviceSetOperatingMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_operating_mode_t pMode                      ///< [in] The new operating mode of the device.
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
/// @brief Properties related to device power settings
typedef struct _xet_power_properties_t
{
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
/// @brief Get properties related to power
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
xetSysmanPowerGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
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
///         + nullptr == hSysman
///         + nullptr == pEnergy
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGetEnergyCounter(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
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
///         + nullptr == hSysman
///         + nullptr == pThreshold
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGetEnergyThreshold(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
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
///         + nullptr == hSysman
///         + nullptr == pThreshold
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerSetEnergyThreshold(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
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
///         + nullptr == hSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerGetLimits(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
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
///         + nullptr == hSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPowerSetLimits(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    const xet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const xet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const xet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    );

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
/// @brief Frequency limits between which the hardware can operate.
typedef struct _xet_freq_limits_t
{
    double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.
    double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.

} xet_freq_limits_t;

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
/// @brief PCU interrupt reasons
typedef enum _xet_pcu_interrupt_reasons_t
{
    XET_PCU_INTERRUPT_DUTY_CYCLE_CHANGE = XE_BIT( 1 ),  ///< signaled every time the duty cycle changes
    XET_PCU_INTERRUPT_DUTY_CYCLE_EXIT = XE_BIT( 2 ),///< signaled at the end of the duty cycle stalling
    XET_PCU_INTERRUPT_DITY_CYCLE_ENTRY = XE_BIT( 3 ),   ///< signaled at the beginning of the duty cycle stalling
    XET_PCU_INTERRUPT_ENERGY_THRESHOLD_CROSSED = XE_BIT( 4 ),   ///< signaled when the energy threshold is crossed

} xet_pcu_interrupt_reasons_t;

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
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_freq_domain_t domain,                       ///< [in] The frequency domain.
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
///         + nullptr == hSysman
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetLimits(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_freq_domain_t domain,                       ///< [in] The frequency domain.
    xet_freq_limits_t* pLimits                      ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency limits between which the hardware can operate.
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
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencySetLimits(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_freq_domain_t domain,                       ///< [in] The frequency domain.
    const xet_freq_limits_t* pLimits                ///< [in] The limits between which the hardware can operate for the
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
///         + nullptr == hSysman
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_freq_domain_t domain,                       ///< [in] The frequency domain.
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
///         + nullptr == hSysman
///         + nullptr == pThrottleTime
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFrequencyGetThrottleTime(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_freq_domain_t domain,                       ///< [in] The frequency domain.
    xet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Activity components
typedef enum _xet_activity_type_t
{
    XET_ACTIVITY_TYPE_GLOBAL = 0,                   ///< Overall activity of all accelerators on the device.
    XET_ACTIVITY_TYPE_COMPUTE,                      ///< Activity of all compute accelerators on the device.
    XET_ACTIVITY_TYPE_MEDIA,                        ///< Activity of all media accelerators on the device.

} xet_activity_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Activity counters
/// 
/// @details
///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
///       using the equation: %util = (s2.activeTime - s1.activeTime) /
///       (s2.timestamp - s1.timestamp)
typedef struct _xet_activity_stats_t
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

} xet_activity_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity counters of a part of the device
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
xetSysmanActivityGetStats(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_activity_type_t type,                       ///< [in] The type of activity stats.
    xet_activity_stats_t* pStats                    ///< [in] Will contain a snapshot of the activity counters.
    );

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
/// @brief Memory properties
typedef struct _xet_mem_properties_t
{
    xet_mem_type_t type;                            ///< [out] The memory type
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
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanMemoryGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
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
///         + nullptr == hSysman
///         + nullptr == pBandwidth
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanMemoryGetBandwidth(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
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
///         + nullptr == hSysman
///         + nullptr == pAllocated
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanMemoryGetAllocated(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_mem_alloc_t* pAllocated                     ///< [in] Will contain the current allocated memory.
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
/// @brief Switch GUID address
typedef struct _xet_switch_guid_t
{
    uint8_t guid[8];                                ///< [out] GUID of the Switch

} xet_switch_guid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Switch properties
typedef struct _xet_switch_properties_t
{
    xet_switch_guid_t switchGuid;                   ///< [out] Address of this Switch
    uint32_t numPorts;                              ///< [out] The number of ports
    xe_bool_t onSubdevice;                          ///< [out] True if the switch is located on a sub-device; false means that
                                                    ///< the switch is on the device of the calling SMI handle
    xe_device_uuid_t subdeviceUuid;                 ///< [out] If onSubdevice is true, this gives the UUID of the sub-device

} xet_switch_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Switch state
typedef struct _xet_switch_state_t
{
    xe_bool_t enabled;                              ///< [out] Indicates if the switch is enabled/disabled

} xet_switch_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Switch port speed
typedef struct _xet_switch_port_speed_t
{
    uint32_t bitRate;                               ///< [out] Bits/sec that the link is operating at
    uint32_t width;                                 ///< [out] The number of lanes
    uint32_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

} xet_switch_port_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Switch Port properties
typedef struct _xet_switch_port_properties_t
{
    xet_switch_port_speed_t maxSpeed;               ///< [out] Maximum bandwidth supported by the port

} xet_switch_port_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Switch Port state
typedef struct _xet_switch_port_state_t
{
    xe_bool_t isConnected;                          ///< [out] Indicates if the port is connected to a remote Switch
    xet_switch_guid_t remoteSwitchGuid;             ///< [out] If connected is true, this gives the address of the remote
                                                    ///< switch to which this port connects
    uint32_t remoteSwitchPortIndex;                 ///< [out] If connected is true, this gives the port index on the remote
                                                    ///< switch
    xet_switch_port_speed_t rxSpeed;                ///< [out] Current maximum receive speed
    xet_switch_port_speed_t txSpeed;                ///< [out] Current maximum transmit speed

} xet_switch_port_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Switch Port throughput
/// 
/// @details
///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
///       using the equation:
///     -     %rx_bandwidth = 10^6 * (s2.rxCounter - s1.rxCounter) /
///       (s2.rxMaxBandwidth * (s2.timestamp - s1.timestamp))
///     -     %tx_bandwidth = 10^6 * (s2.txCounter - s1.txCounter) /
///       (s2.txMaxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _xet_switch_port_throughput_t
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

} xet_switch_port_throughput_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Switch Port stats counters
/// 
/// @details
///     - Percent replays is calculated by taking two snapshots (s1, s2) and
///       using the equation: %replay = 10^6 * (s2.replayCounter -
///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _xet_switch_port_stats_t
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

} xet_switch_port_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Switch properties
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
xetSysmanSwitchGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                    ///< [::xet_sysman_properties_t.numSwitches - 1]).
    xet_switch_properties_t* pProperties            ///< [in] Will contain the Switch properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Switch state
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
xetSysmanSwitchGetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                    ///< [::xet_sysman_properties_t.numSwitches - 1]).
    xet_switch_state_t* pState                      ///< [in] Will contain the current state of the switch (enabled/disabled).
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set Switch state
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
xetSysmanSwitchSetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                    ///< [::xet_sysman_properties_t.numSwitches - 1]).
    xe_bool_t enable                                ///< [in] Set to true to enable the Switch, otherwise it will be disabled.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Switch Port properties
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
xetSysmanSwitchPortGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                    ///< [::xet_sysman_properties_t.numSwitches - 1]).
    uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                    ///< - 1]).
    xet_switch_port_properties_t* pProperties       ///< [in] Will contain properties of the Switch Port
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Switch Port state
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
xetSysmanSwitchPortGetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                    ///< [::xet_sysman_properties_t.numSwitches - 1]).
    uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                    ///< - 1]).
    xet_switch_port_state_t* pState                 ///< [in] Will contain the current state of the Switch Port
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Switch Port throughput
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
xetSysmanSwitchPortGetThroughput(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                    ///< [::xet_sysman_properties_t.numSwitches - 1]).
    uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                    ///< - 1]).
    xet_switch_port_throughput_t* pThroughput       ///< [in] Will contain the Switch port throughput counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Switch Port stats
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
xetSysmanSwitchPortGetStats(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t switchIndex,                           ///< [in] The index of the switch (0 ...
                                                    ///< [::xet_sysman_properties_t.numSwitches - 1]).
    uint32_t portIndex,                             ///< [in] The index of the port (0 ... [::xet_switch_properties_t.numPorts
                                                    ///< - 1]).
    xet_switch_port_stats_t* pStats                 ///< [in] Will contain the Switch port stats.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensors
typedef enum _xet_temp_sensors_t
{
    XET_TEMP_SENSORS_GLOBAL = 0,                    ///< The maximum temperature across all device sensors
    XET_TEMP_SENSORS_GPU,                           ///< The maximum temperature across all sensors in the GPU
    XET_TEMP_SENSORS_MEMORY,                        ///< The maximum temperature across all sensors in the local memory
    XET_TEMP_SENSORS_NUM,                           ///< The number of sensors

} xet_temp_sensors_t;

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
///         + nullptr == hSysman
///         + nullptr == pTemperature
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanTemperatureGet(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_temp_sensors_t sensor,                      ///< [in] The port address.
    uint32_t* pTemperature                          ///< [in] Will contain the temperature read from the specified sensor.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby promotion modes
typedef enum _xet_stby_promo_mode_t
{
    XET_STBY_PROMO_MODE_DEFAULT = 0,                ///< Best compromise between performance and energy savings.
    XET_STBY_PROMO_MODE_NEVER,                      ///< The device/component will never shutdown. This can improve performance
                                                    ///< but uses more energy.

} xet_stby_promo_mode_t;

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
///         + nullptr == hSysman
///         + nullptr == pMode
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanStandbyGetMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_stby_promo_mode_t* pMode                    ///< [in] Will contain the current standby mode.
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
///         + nullptr == hSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanStandbySetMode(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_stby_promo_mode_t mode                      ///< [in] New standby mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Firmware properties
typedef struct _xet_firmware_properties_t
{
    xe_bool_t canControl;                           ///< [out] Indicates if software can flash the firmware
    int8_t name[XET_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
    int8_t version[XET_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

} xet_firmware_properties_t;

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
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFirmwareGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                    ///< [::xet_sysman_properties_t.numFirmwares - 1]).
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
///         + nullptr == hSysman
///         + nullptr == pChecksum
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFirmwareGetChecksum(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                    ///< [::xet_sysman_properties_t.numFirmwares - 1]).
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
///         + nullptr == hSysman
///         + nullptr == pImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFirmwareFlash(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t firmwareIndex,                         ///< [in] The index of the firmware (0 ...
                                                    ///< [::xet_sysman_properties_t.numFirmwares - 1]).
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
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
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPsuGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ...
                                                    ///< [::xet_sysman_properties_t.numPsus - 1]).
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
///         + nullptr == hSysman
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanPsuGetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t psuIndex,                              ///< [in] The index of the power supply (0 ...
                                                    ///< [::xet_sysman_properties_t.numPsus - 1]).
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
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                    ///< 1]).
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
///         + nullptr == hSysman
///         + nullptr == pConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanGetConfig(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                    ///< 1]).
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
///         + nullptr == hSysman
///         + nullptr == pConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanSetConfig(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                    ///< 1]).
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
///         + nullptr == hSysman
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanFanGetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t fanIndex,                              ///< [in] The index of the fan (0 ... [::xet_sysman_properties_t.numFans -
                                                    ///< 1]).
    xet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    xet_fan_state_t* pState                         ///< [in] Will contain the current state of the fan.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief LED properties
typedef struct _xet_led_properties_t
{
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
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLedGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                    ///< 1]).
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
///         + nullptr == hSysman
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLedGetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                    ///< 1]).
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
///         + nullptr == hSysman
///         + nullptr == pState
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanLedSetState(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t ledIndex,                              ///< [in] The index of the LED (0 ... [::xet_sysman_properties_t.numLeds -
                                                    ///< 1]).
    const xet_led_state_t* pState                   ///< [in] New state of the LED.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS properties
typedef struct _xet_ras_properties_t
{
    xe_bool_t supported;                            ///< [out] True if RAS is supported on this device
    xe_bool_t enabled;                              ///< [out] True if RAS is enabled on this device
    xe_bool_t repaired;                             ///< [out] True if the device has been repaired

} xet_ras_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error type
typedef enum _xet_ras_error_type_t
{
    XET_RAS_ERROR_TYPE_CORRECTABLE = 0,             ///< Errors were corrected by hardware
    XET_RAS_ERROR_TYPE_UNCORRECTABLE,               ///< Error were not corrected
    XET_RAS_ERROR_TYPE_NUM,                         ///< The number of error types

} xet_ras_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error details
typedef struct _xet_ras_details_t
{
    uint64_t numResets;                             ///< [out] The number of accelerator resets that have taken place
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
    uint64_t numSwitchErrors;                       ///< [out] The number of errors that have occurred in the P2P links
    uint64_t numDisplayErrors;                      ///< [out] The number of errors that have occurred in the display

} xet_ras_details_t;

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
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRasGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the number of errors of a given type
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
///         + nullptr == hSysman
///         + nullptr == pTotalErrors
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + This device does not support RAS.
///     - ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
xe_result_t __xecall
xetSysmanRasGetErrors(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_ras_error_type_t type,                      ///< [in] The type of errors
    xe_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in] The number total number of errors of the given type that have
                                                    ///< occurred
    xet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
    );

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
xetSysmanDiagnosticsGetTestList(
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
xetSysmanDiagnosticsRunTests(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
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
