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
* @file xet_power.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Power
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/power.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_POWER_HPP
#define _XET_POWER_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xet_common.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Fan capabilities
    enum class fan_capabilities_t
    {
        GET_SPEED_PERCENTAGE = XE_BIT( 0 ),             ///< can query fan speed as a percentage
        SET_SPEED_PERCENTAGE = XE_BIT( 1 ),             ///< can set fan speed as a percentage
        GET_SPEED_RPM = XE_BIT( 2 ),                    ///< can query fan speed as rpm
        SET_SPEED_RPM = XE_BIT( 3 ),                    ///< can set fan speed as rpm
        HAVE_TEMPERATURE_SPEED_TABLE = XE_BIT( 4 ),     ///< can set temperature/fan speed table

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Fan speed modes
    enum class fan_speed_mode_t
    {
        AUTO = 0,                                       ///< fan speed is dynamically controlled based on temperature
        FIXED,                                          ///< fan speed is fixed

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for power
    class Power
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Power initialization flags (bitfield)
        enum class init_flags_t
        {
            NONE = 0,                                       ///< default initialization
            WRITE = XE_BIT( 0 ),                            ///< request access to power controls

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief GPU domains
        enum class gpu_domain_t
        {
            BASE = XE_BIT( 0 ),                             ///< base die
            VIDEO_DECODE = XE_BIT( 1 ),                     ///< video decode engines
            VIDEO_ENCODE = XE_BIT( 2 ),                     ///< video encode engines
            VIDEO_PROCESSING = XE_BIT( 3 ),                 ///< video processing engines
            _3D_FIXED_FUNCTION = XE_BIT( 4 ),               ///< 3D fixed-function
            _3D_RENDER = XE_BIT( 5 ),                       ///< 3D programmable engines
            COMPUTE = XE_BIT( 6 ),                          ///< compute engines
            SYSTOLIC_ARRAY = XE_BIT( 7 ),                   ///< systolic array engines
            RAYTRACING = XE_BIT( 8 ),                       ///< raytracing engines
            LOCAL_MEMORY = XE_BIT( 9 ),                     ///< local memory
            BASE_CHIPLET_LINK = XE_BIT( 10 ),               ///< link between base die and chiplet

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::power_average_limit_t
        enum class average_limit_version_t
        {
            AVERAGE_POWER_LIMIT_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Turbo (dynamic hardware frequency management) modes
        enum class turbo_mode_t
        {
            DISABLED = 0,                                   ///< DVFS is currently disabled - frequency is fixed
            DEFAULT,                                        ///< hardware default DVFS (typically EFFICIENT)
            MIN_PERFORMANCE,                                ///< min efficient frequency unless specific applications require otherwise
            EFFICIENT_PERFORMANCE,                          ///< balanced power and performance
            AGGRESSIVE_PERFORMANCE,                         ///< aggressively favor performance over power
            MAX_PERFORMANCE,                                ///< fixed max frequency unless limited by thermals/power

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Average power limit
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency of
        ///       the device if the power averaged over a window (typically seconds)
        ///       exceeds a limit known as PL1.
        struct average_limit_t
        {
            average_limit_version_t version = average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT; ///< [in] ::AVERAGE_POWER_LIMIT_VERSION_CURRENT
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts
            uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Burst power limit
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency of
        ///       the device if the power averaged over a few milliseconds exceeds a
        ///       limit known as PL2. Typically PL2 > PL1 so that it permits the
        ///       frequency to burst higher for short periods than would be otherwise
        ///       permitted by PL1.
        struct burst_limit_t
        {
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

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
        struct peak_limit_t
        {
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief All power limits
        struct limits_t
        {
            average_limit_t averagePowerLimit;              ///< [in,out] average power limit information
            burst_limit_t burstPowerLimit;                  ///< [in,out] burst power limit information
            peak_limit_t peakPowerLimit;                    ///< [in,out] peak power limit information

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan properties
        struct fan_properties_t
        {
            uint32_t fanCapabilities;                       ///< [in] bitfield of ::fan_capabilities_t
            uint32_t maxRpm;                                ///< [in] maximum RPM of the fan. Will be 0 if maximum is not known.
            uint32_t maxTemperatureSpeedPoints;             ///< [in] the maximum number of temperature/fan-speed points that can be
                                                            ///< programmed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature/fan-speed point
        struct fan_point_t
        {
            xe::bool_t fanSpeedInRpm;                       ///< [in,out] false means fanSpeed is in percentage, true means fanSpeed is
                                                            ///< in RPM
            uint16_t temperatureDegreesCentigrate;          ///< [in,out] temperature in degrees centigrate
            uint16_t fanSpeed;                              ///< [in,out] the fan speed as a percentage (or RPM if fanSpeedInRpm is
                                                            ///< true)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan speed info
        struct fan_speed_info_t
        {
            xe::bool_t fanSpeedInRpm;                       ///< [in,out] false means fanSpeed is in percentage, true means fanSpeed is
                                                            ///< in RPM
            fan_speed_mode_t fanSpeedMode;                  ///< [in,out] whether the fan speed is fixed or being controlled
                                                            ///< dynamically
            uint16_t fanSpeed;                              ///< [in,out] the fan speed as a percentage (or RPM if fanSpeedInRpm is
                                                            ///< true)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensor properties
        /// 
        /// @details
        ///     - Temperature sensor index 0 is special - it is a virtual sensor that
        ///       gives the max across all sensors. The member **location** equals
        ///       0xFFFFFFFF in this case.
        ///     - Most systems apply the temperature threshold globally. In this case,
        ///       member **canChangeThreshold** will only be true for sensor index 0.
        struct temperature_properties_t
        {
            uint32_t location;                              ///< [in] bitfield of ::gpu_domain_t whose temperature is measured by this
                                                            ///< sensor
            uint16_t maxTemperature;                        ///< [in] the temperature limit in celsius beyond which the power control
                                                            ///< unit (Punit) will throttle the frequency
            uint16_t shutdownTemperature;                   ///< [in] the temperature limit in celsius beyond which the power control
                                                            ///< unit (Punit) will shutdown the device
            xe::bool_t canChangeThreshold;                  ///< [in] true indicates that this a different threshold can be set

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Activity counter properties
        /// 
        /// @details
        ///     - Activity counter 0 is a normalized accumulation of activity across all
        ///       blocks. The member **blocks** equals 0xFFFFFFFF in this case.
        struct activity_properties_t
        {
            uint32_t blocks;                                ///< [in] bitfield of ::gpu_domain_t whose activity is included in this
                                                            ///< counter

        };

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
        struct activity_counters_t
        {
            uint64_t activityCounter;                       ///< [out] Monotonically increasing counter of activity in microseconds
            uint64_t idleCounter;                           ///< [out] Monotonically increasing counter of time blocks are powered on
                                                            ///< but idle in microseconds
            uint64_t timeCounter;                           ///< [out] Monotonically increasing counter of time in microseconds

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        power_handle_t m_handle;                        ///< handle of power object

        ///////////////////////////////////////////////////////////////////////////////
        Power( void ) = delete;
        Power( 
            power_handle_t handle                           ///< handle of power object
            );

        ~Power( void ) = default;

        Power( Power const& other ) = delete;
        void operator=( Power const& other ) = delete;

        Power( Power&& other ) = delete;
        void operator=( Power&& other ) = delete;

    public:
        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates an object to access power features on a device
        /// 
        /// @details
        ///     - Initializes internal structures to support power management features.
        ///     - Error ::XERESULT_ERROR_UNSUPPORTED is returned if the device does not
        ///       support access to power management features.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **nvmlInit**
        ///     - **rsmi_init**
        /// @returns
        ///     - Power: handle for accessing power features of the device
        /// 
        /// @throws result_t
        inline static Power*
        Create(
            xe::Device* hDevice,                            ///< [in] handle of the device object
            uint32_t flags                                  ///< [in] bitfield of ::power_init_flags_t
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a power object
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **nvmlShutdown**
        ///     - **rsmi_shut_down**
        /// @throws result_t
        inline static void
        Destroy(
            Power* hPower                                   ///< [in] handle of the power object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current average power limit information for a device
        /// @returns
        ///     - average_limit_t: information about the average power limit
        /// 
        /// @throws result_t
        inline average_limit_t
        GetAveragePowerLimit(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current burst power limit information for a device
        /// @returns
        ///     - burst_limit_t: information about the burst power limit
        /// 
        /// @throws result_t
        inline burst_limit_t
        GetBurstPowerLimit(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current peak power limit information for a device
        /// @returns
        ///     - peak_limit_t: information about the peak power limit
        /// 
        /// @throws result_t
        inline peak_limit_t
        GetPeakPowerLimit(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get all current power limits for a device
        /// @returns
        ///     - limits_t: information about the average/burst/peak power limits
        /// 
        /// @throws result_t
        inline limits_t
        GetAllPowerLimits(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get default power limits for a device
        /// @returns
        ///     - limits_t: information about the default average/burst/peak power limits
        /// 
        /// @throws result_t
        inline limits_t
        GetDefaultPowerLimits(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the average power limit for a device
        /// @throws result_t
        inline void
        SetAveragePowerLimit(
            average_limit_t* pLimit                         ///< [in] information about the average power limit
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the burst power limit for a device
        /// @throws result_t
        inline void
        SetBurstPowerLimit(
            burst_limit_t* pLimit                           ///< [in] information about the burst power limit
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the peak power limit for a device
        /// @throws result_t
        inline void
        SetPeakPowerLimit(
            peak_limit_t* pLimit                            ///< [in] information about the peak power limit
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the average/burst/peak power limits for a device
        /// @throws result_t
        inline void
        SetPowerLimits(
            limits_t* pLimits                               ///< [in] information about the average/burst/peak power limits
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get energy counter
        /// 
        /// @details
        ///     - Average power = delta(energy counter in millijoules) / delta(time in
        ///       milliseconds)
        /// @returns
        ///     - uint64_t: the energy counter in millijoules
        /// 
        /// @throws result_t
        inline uint64_t
        GetEnergyCounter(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the current Turbo mode for a device
        /// @returns
        ///     - turbo_mode_t: turbo mode currently in effect
        /// 
        /// @throws result_t
        inline turbo_mode_t
        GetTurboMode(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the current Turbo mode for a device
        /// @throws result_t
        inline void
        SetTurboMode(
            turbo_mode_t pTurboMode                         ///< [in] new turbo mode
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the number of frequency domains on the device
        /// @returns
        ///     - uint32_t: the number of frequency domains
        /// 
        /// @throws result_t
        inline uint32_t
        GetFreqDomainCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get an object to a frequency domain on a device
        /// @returns
        ///     - FreqDomain: pointer to handle of frequency domain object
        /// 
        /// @throws result_t
        inline FreqDomain*
        GetFreqDomainHandle(
            uint32_t ordinal                                ///< [in] frequency domain index [0 .. ::PowerGetFreqDomainCount - 1]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get number of fans on the device
        /// @returns
        ///     - uint32_t: the number of fans on the device
        /// 
        /// @throws result_t
        inline uint32_t
        FanCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get fan properties for one of the fans on a device
        /// @returns
        ///     - fan_properties_t: pointer to storage for fan properties
        /// 
        /// @throws result_t
        inline fan_properties_t
        FanGetProperties(
            uint32_t fanIndex                               ///< [in] fan index [0 .. ::PowerFanCount - 1]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get fan speed table
        /// 
        /// @details
        ///     - Set pFanSpeedTable = nullptr to find out the current number of fan
        ///       speed points in the table.
        /// @returns
        ///     - fan_point_t: pointer to an array of temperature/fan-speed points
        /// 
        /// @throws result_t
        inline fan_point_t
        FanGetSpeedTable(
            uint32_t fanIndex,                              ///< [in] fan index [0 .. ::PowerFanCount - 1]
            xe::bool_t fanSpeedInRpm,                       ///< [in] true will request fan speeds in RPM, otherwise in percentage
            uint32_t* pNumFanPoints                         ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                            ///< number of elements returned
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set fan speed table
        /// 
        /// @details
        ///     - Use ::PowerFanGetProperties to determine acceptable units for fan
        ///       speed (percent, RPM).
        ///     - Fan points should be ordered according to increasing temperature.
        /// @throws result_t
        inline void
        FanSetSpeedTable(
            uint32_t fanIndex,                              ///< [in] fan index [0 .. ::PowerFanCount - 1]
            uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
            fan_point_t* pFanPoints                         ///< [in] pointer to an array of temperature/fan-speed points
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current fan speeds
        /// 
        /// @details
        ///     - The array pFanSpeed must contain at least numFans entries.
        /// @returns
        ///     - fan_speed_info_t: pointer to an array of current fan speeds
        /// 
        /// @throws result_t
        inline fan_speed_info_t
        FanGetSpeed(
            uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::PowerFanCount - 1]
            uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                            ///< (startFanIndex)..(startFanIndex + numFans - 1)
            xe::bool_t fanSpeedInRpm                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set fan speeds
        /// 
        /// @details
        ///     - Use ::fan_speed_info_t.fanSpeedMode to set whether the speed should be
        ///       fixed or dynamically controlled
        /// @throws result_t
        inline void
        FanSetSpeed(
            uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::PowerFanCount - 1]
            uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                            ///< (startFanIndex)..(startFanIndex + numFans - 1)
            fan_speed_info_t* pFanSpeed                     ///< [in] pointer to an array of current fan speeds
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get number of temperature sensors on the device
        /// @returns
        ///     - uint32_t: the number of temperature sensors on the device
        /// 
        /// @throws result_t
        inline uint32_t
        TemperatureSensorCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get temperatures sensor properties
        /// 
        /// @details
        ///     - Temperature sensor index 0 is special - it gives the maximum
        ///       temperature across all sensors
        /// @returns
        ///     - temperature_properties_t: pointer to properties for this sensor
        /// 
        /// @throws result_t
        inline temperature_properties_t
        GetTemperatureProperties(
            uint32_t sensorIndex                            ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current temperatures
        /// 
        /// @details
        ///     - Temperature sensor index 0 is special - it gives the maximum
        ///       temperature across all sensors
        /// @returns
        ///     - uint16_t: pointer to an array of temperatures in units of degrees celsius
        /// 
        /// @throws result_t
        inline uint16_t
        GetTemperature(
            uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
            uint32_t numSensors                             ///< [in] pTemperatures will contain results for sensors index
                                                            ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set temperature threshold
        /// 
        /// @details
        ///     - Check ::temperature_properties_t.canChangeThreshold to determine if
        ///       the threshold can be changed.
        ///     - On most systems, there is only one threshold and sensorIndex should be
        ///       0.
        ///     - **This is an overclocking feature and will void device warranty**
        /// @throws result_t
        inline void
        SetTemperatureThreshold(
            uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
            uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                            ///< will be throttled
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get number of activity counters
        /// @returns
        ///     - uint32_t: the number of activity counters on the device
        /// 
        /// @throws result_t
        inline uint32_t
        ActivityCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get activity counter properties
        /// 
        /// @details
        ///     - Activity counter index 0 is special - it acculates activity across all
        ///       blocks.
        /// @returns
        ///     - activity_properties_t: pointer to properties for this activity counter
        /// 
        /// @throws result_t
        inline activity_properties_t
        GetActivityProperties(
            uint32_t activityIndex                          ///< [in] activity counter index [0 .. ::PowerActivityCount]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get activity counters
        /// 
        /// @details
        ///     - Activity counter index 0 is special - it acculates activity across all
        ///       blocks.
        /// @returns
        ///     - activity_counters_t: pointer to an array of activity counter data
        /// 
        /// @throws result_t
        inline activity_counters_t
        GetActivityCounters(
            uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::PowerActivityCount]
            uint32_t numCounters                            ///< [in] pCounters will contain results for activity counter index
                                                            ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for frequency domain
    class FreqDomain
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Clock types
        enum class clock_type_t
        {
            FIXED = 0,                                      ///< fixed crystal clock
            PLL,                                            ///< phase-locked-loop (PLL) frequency range
            DIVIDER,                                        ///< frequency is linked to another domain by a divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency throttle reasons
        enum class freq_throttle_reasons_t
        {
            NONE = 0,                                       ///< frequency not throttled
            AVE_PWR_CAP = XE_BIT( 0 ),                      ///< frequency throttled due to average power excursion (PL1)
            BURST_PWR_CAP = XE_BIT( 1 ),                    ///< frequency throttled due to burst power excursion (PL2)
            CURRENT_LIMIT = XE_BIT( 2 ),                    ///< frequency throttled due to current excursion (PL4)
            THERMAL_LIMIT = XE_BIT( 3 ),                    ///< frequency throttled due to thermal excursion (T > TjMax)
            PSU_ALERT = XE_BIT( 4 ),                        ///< frequency throttled due to power supply assertion
            SW_RANGE = XE_BIT( 5 ),                         ///< frequency throttled due to software supplied frequency range
            HW_RANGE = XE_BIT( 6 ),                         ///< frequency throttled due to a sub block that has a lower frequency
                                                            ///< range when it receives clocks

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Properties of a frequency domain
        /// 
        /// @details
        ///     - A frequency domain contains one or more GPU functional blocks - see
        ///       ::gpu_domain_t
        ///     - There is more than one type of clock - check clockType
        ///     - For clock type ::CLOCK_TYPE_FIXED, minClock and maxClock will be the
        ///       same and numClockPoints will be 1.
        ///     - For clock type ::CLOCK_TYPE_PLL, numClockPoints is given for
        ///       informational purposes. Do not assume the frequency step between
        ///       min/max clocks is (max - min) / (numClockPoints - 1). Instead, use the
        ///       function ::FreqDomainGetSupportedClocks to get the list of all
        ///       supported clocks between min/max.
        ///     - For clock type ::CLOCK_TYPE_DIVIDER, the frequency of the domain is
        ///       given by multiplying the divider by the frequency of the source
        ///       domain. The possible divider values can be obtained using the function
        ///       ::FreqDomainGetSupportedClockDividers. For this clock type,
        ///       minClock/maxClock specifies the total range of frequencies whereas the
        ///       actual range depends on the current divider value.
        struct properties_t
        {
            uint32_t gpuDomains;                            ///< [in] bitfield of xex_gpu_domain_t
            clock_type_t clockType;                         ///< [in] clock type
            uint32_t minClock;                              ///< [in] minimum frequency of the domain
            uint32_t maxClock;                              ///< [in] maximum frequency of the domain
            uint32_t numClockPoints;                        ///< [in] number of discrete clock points between and including min/max
            uint32_t numClockDividers;                      ///< [in] for clock type ::CLOCK_TYPE_DIVIDER, this gives the number of
                                                            ///< dividers available

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency divider configuration
        /// 
        /// @details
        ///     - The frequency of a domain of type ::CLOCK_TYPE_DIVIDER is obtained by
        ///       the formula:
        ///     - freq = source domain freq * numerator / denominator
        struct clock_divider_t
        {
            uint16_t numerator;                             ///< [in,out] numerator of the ratio
            uint16_t denominator;                           ///< [in,out] denominator of the ratio

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        freq_domain_handle_t m_handle;                  ///< handle of frequency domain object

        ///////////////////////////////////////////////////////////////////////////////
        FreqDomain( void ) = delete;
        FreqDomain( 
            freq_domain_handle_t handle                     ///< handle of frequency domain object
            );

        ~FreqDomain( void ) = default;

        FreqDomain( FreqDomain const& other ) = delete;
        void operator=( FreqDomain const& other ) = delete;

        FreqDomain( FreqDomain&& other ) = delete;
        void operator=( FreqDomain&& other ) = delete;

    public:
        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the properties for a frequency domain
        /// @returns
        ///     - properties_t: pointer to properties for the frequency domain
        /// 
        /// @throws result_t
        inline properties_t
        GetProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the source frequency domain handle for a frequency domain of type
        ///        ::CLOCK_TYPE_DIVIDER
        /// @returns
        ///     - FreqDomain: pointer to a handle where the source frequency domain handle will be returned
        /// 
        /// @throws result_t
        inline FreqDomain*
        GetSourceFreqDomain(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get supported frequency points for frequency domains with clock type
        ///        ::CLOCK_TYPE_PLL
        /// 
        /// @details
        ///     - The total available list of frequencies can be found in
        ///       ::freq_domain_properties_t.numClockPoints.
        /// @returns
        ///     - uint32_t: pointer to array of frequencies
        /// 
        /// @throws result_t
        inline uint32_t
        GetSupportedClocks(
            uint32_t numClockPoints                         ///< [in] number of elements in pClocks
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get supported frequency dividers for frequency domains with clock type
        ///        ::CLOCK_TYPE_DIVIDER
        /// 
        /// @details
        ///     - The total available list of frequencies can be found in
        ///       ::freq_domain_properties_t.numClockDividers.
        /// @returns
        ///     - clock_divider_t: pointer to array of dividers
        /// 
        /// @throws result_t
        inline clock_divider_t
        GetSupportedClockDividers(
            uint32_t numClockDividers                       ///< [in] number of elements in pDividers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the frequency range for a frequency domain with clock type
        ///        ::CLOCK_TYPE_PLL.
        /// @returns
        ///     - uint32_t: min clock frequency in units of MHz
        ///     - uint32_t: max clock frequency in units of MHz
        /// 
        /// @throws result_t
        inline std::tuple<uint32_t, uint32_t>
        GetClockRange(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the frequency range for a frequency domain with clock type
        ///        ::CLOCK_TYPE_PLL.
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
        /// @throws result_t
        inline void
        SetClockRange(
            uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
            uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set frequency divider for a frequency domain with clock type
        ///        ::CLOCK_TYPE_DIVIDER
        /// 
        /// @details
        ///     - This disables dynamic frequency divider management running on the
        ///       hardware.
        ///     - Setting pClockDivider to nullptr will enable dynamic frequency divider
        ///       management.
        /// @returns
        ///     - clock_divider_t: pointer to frequency divider request
        /// 
        /// @throws result_t
        inline clock_divider_t
        SetClockDivider(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current frequency
        /// @returns
        ///     - uint32_t: current frequency in MHz requested by the driver
        ///     - uint32_t: the actual frequency in MHz
        ///     - freq_throttle_reasons_t: the reason the resolved frequency is lower than the request
        /// 
        /// @throws result_t
        inline std::tuple<uint32_t, uint32_t, freq_throttle_reasons_t>
        GetCurrentFrequency(
            void
            );

    };

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_POWER_HPP
