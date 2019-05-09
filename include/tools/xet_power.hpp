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
    protected:
        ::xet_power_handle_t m_handle;                    ///< handle of power object

        Power( void ) = delete;
        Power( 
                xet_power_handle_t handle                       ///< handle of power object
                ) :
                m_handle( handle )
            {}

        ~Power( void ) = default;

        Power( Power const& other ) = delete;
        void operator=( Power const& other ) = delete;

        Power( Power&& other ) = delete;
        void operator=( Power&& other ) = delete;

    public:
        auto getHandle( void ) const { return m_handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_power_init_flags_t
        enum class power_init_flags_t
        {
            NONE = 0,                                       ///< default initialization
            WRITE = XE_BIT( 0 ),                            ///< request access to power controls

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_gpu_domain_t
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
        /// @brief C++ version for ::xet_power_average_limit_version_t
        enum class power_average_limit_version_t
        {
            AVERAGE_POWER_LIMIT_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_turbo_mode_t
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
        /// @brief C++ version for ::xet_power_average_limit_t
        struct power_average_limit_t
        {
            power_average_limit_version_t version = power_average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT; ///< [in] ::AVERAGE_POWER_LIMIT_VERSION_CURRENT
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts
            uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_power_burst_limit_t
        struct power_burst_limit_t
        {
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_power_peak_limit_t
        struct power_peak_limit_t
        {
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_power_limits_t
        struct power_limits_t
        {
            power_average_limit_t averagePowerLimit;        ///< [in,out] average power limit information
            power_burst_limit_t burstPowerLimit;            ///< [in,out] burst power limit information
            power_peak_limit_t peakPowerLimit;              ///< [in,out] peak power limit information

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_fan_properties_t
        struct fan_properties_t
        {
            uint32_t fanCapabilities;                       ///< [in] bitfield of ::fan_capabilities_t
            uint32_t maxRpm;                                ///< [in] maximum RPM of the fan. Will be 0 if maximum is not known.
            uint32_t maxTemperatureSpeedPoints;             ///< [in] the maximum number of temperature/fan-speed points that can be
                                                            ///< programmed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_fan_point_t
        struct fan_point_t
        {
            xe::bool_t fanSpeedInRpm;                       ///< [in,out] false means fanSpeed is in percentage, true means fanSpeed is
                                                            ///< in RPM
            uint16_t temperatureDegreesCentigrate;          ///< [in,out] temperature in degrees centigrate
            uint16_t fanSpeed;                              ///< [in,out] the fan speed as a percentage (or RPM if fanSpeedInRpm is
                                                            ///< true)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_fan_speed_info_t
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
        /// @brief C++ version for ::xet_temperature_properties_t
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
        /// @brief C++ version for ::xet_activity_properties_t
        struct activity_properties_t
        {
            uint32_t blocks;                                ///< [in] bitfield of ::gpu_domain_t whose activity is included in this
                                                            ///< counter

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_activity_counters_t
        struct activity_counters_t
        {
            uint64_t activityCounter;                       ///< [out] Monotonically increasing counter of activity in microseconds
            uint64_t idleCounter;                           ///< [out] Monotonically increasing counter of time blocks are powered on
                                                            ///< but idle in microseconds
            uint64_t timeCounter;                           ///< [out] Monotonically increasing counter of time in microseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerCreate
        /// @returns
        ///     - ::power_handle_t: handle for accessing power features of the device
        /// 
        /// @throws result_t
        inline static power_handle_t
        Create(
            xe::device_handle_t hDevice,                    ///< [in] handle of the device object
            uint32_t flags                                  ///< [in] bitfield of ::power_init_flags_t
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerDestroy
        /// @throws result_t
        inline static void
        Destroy(
            power_handle_t hPower                           ///< [in] handle of the power object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetAveragePowerLimit
        /// @returns
        ///     - ::power_average_limit_t: information about the average power limit
        /// 
        /// @throws result_t
        inline power_average_limit_t
        GetAveragePowerLimit(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetBurstPowerLimit
        /// @returns
        ///     - ::power_burst_limit_t: information about the burst power limit
        /// 
        /// @throws result_t
        inline power_burst_limit_t
        GetBurstPowerLimit(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetPeakPowerLimit
        /// @returns
        ///     - ::power_peak_limit_t: information about the peak power limit
        /// 
        /// @throws result_t
        inline power_peak_limit_t
        GetPeakPowerLimit(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetAllPowerLimits
        /// @returns
        ///     - ::power_limits_t: information about the average/burst/peak power limits
        /// 
        /// @throws result_t
        inline power_limits_t
        GetAllPowerLimits(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetDefaultPowerLimits
        /// @returns
        ///     - ::power_limits_t: information about the default average/burst/peak power limits
        /// 
        /// @throws result_t
        inline power_limits_t
        GetDefaultPowerLimits(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerSetAveragePowerLimit
        /// @throws result_t
        inline void
        SetAveragePowerLimit(
            power_average_limit_t* pLimit                   ///< [in] information about the average power limit
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerSetBurstPowerLimit
        /// @throws result_t
        inline void
        SetBurstPowerLimit(
            power_burst_limit_t* pLimit                     ///< [in] information about the burst power limit
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerSetPeakPowerLimit
        /// @throws result_t
        inline void
        SetPeakPowerLimit(
            power_peak_limit_t* pLimit                      ///< [in] information about the peak power limit
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerSetPowerLimits
        /// @throws result_t
        inline void
        SetPowerLimits(
            power_limits_t* pLimits                         ///< [in] information about the average/burst/peak power limits
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetEnergyCounter
        /// @returns
        ///     - uint64_t: the energy counter in millijoules
        /// 
        /// @throws result_t
        inline uint64_t
        GetEnergyCounter(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetTurboMode
        /// @returns
        ///     - ::turbo_mode_t: turbo mode currently in effect
        /// 
        /// @throws result_t
        inline turbo_mode_t
        GetTurboMode(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerSetTurboMode
        /// @throws result_t
        inline void
        SetTurboMode(
            turbo_mode_t pTurboMode                         ///< [in] new turbo mode
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetFreqDomainCount
        /// @returns
        ///     - uint32_t: the number of frequency domains
        /// 
        /// @throws result_t
        inline uint32_t
        GetFreqDomainCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetFreqDomainHandle
        /// @returns
        ///     - ::freq_domain_handle_t: pointer to handle of frequency domain object
        /// 
        /// @throws result_t
        inline freq_domain_handle_t
        GetFreqDomainHandle(
            uint32_t ordinal                                ///< [in] frequency domain index [0 .. ::PowerGetFreqDomainCount - 1]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerFanCount
        /// @returns
        ///     - uint32_t: the number of fans on the device
        /// 
        /// @throws result_t
        inline uint32_t
        FanCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerFanGetProperties
        /// @returns
        ///     - ::fan_properties_t: pointer to storage for fan properties
        /// 
        /// @throws result_t
        inline fan_properties_t
        FanGetProperties(
            uint32_t fanIndex                               ///< [in] fan index [0 .. ::PowerFanCount - 1]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerFanGetSpeedTable
        /// @returns
        ///     - ::fan_point_t: pointer to an array of temperature/fan-speed points
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
        /// @brief C++ wrapper for ::xetPowerFanSetSpeedTable
        /// @throws result_t
        inline void
        FanSetSpeedTable(
            uint32_t fanIndex,                              ///< [in] fan index [0 .. ::PowerFanCount - 1]
            uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
            fan_point_t* pFanPoints                         ///< [in] pointer to an array of temperature/fan-speed points
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerFanGetSpeed
        /// @returns
        ///     - ::fan_speed_info_t: pointer to an array of current fan speeds
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
        /// @brief C++ wrapper for ::xetPowerFanSetSpeed
        /// @throws result_t
        inline void
        FanSetSpeed(
            uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::PowerFanCount - 1]
            uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                            ///< (startFanIndex)..(startFanIndex + numFans - 1)
            fan_speed_info_t* pFanSpeed                     ///< [in] pointer to an array of current fan speeds
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerTemperatureSensorCount
        /// @returns
        ///     - uint32_t: the number of temperature sensors on the device
        /// 
        /// @throws result_t
        inline uint32_t
        TemperatureSensorCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetTemperatureProperties
        /// @returns
        ///     - ::temperature_properties_t: pointer to properties for this sensor
        /// 
        /// @throws result_t
        inline temperature_properties_t
        GetTemperatureProperties(
            uint32_t sensorIndex                            ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetTemperature
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
        /// @brief C++ wrapper for ::xetPowerSetTemperatureThreshold
        /// @throws result_t
        inline void
        SetTemperatureThreshold(
            uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
            uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                            ///< will be throttled
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerActivityCount
        /// @returns
        ///     - uint32_t: the number of activity counters on the device
        /// 
        /// @throws result_t
        inline uint32_t
        ActivityCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetActivityProperties
        /// @returns
        ///     - ::activity_properties_t: pointer to properties for this activity counter
        /// 
        /// @throws result_t
        inline activity_properties_t
        GetActivityProperties(
            uint32_t activityIndex                          ///< [in] activity counter index [0 .. ::PowerActivityCount]
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetPowerGetActivityCounters
        /// @returns
        ///     - ::activity_counters_t: pointer to an array of activity counter data
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
    protected:
        ::xet_freq_domain_handle_t m_handle;              ///< handle of frequency domain object

        FreqDomain( void ) = delete;
        FreqDomain( 
                xet_freq_domain_handle_t handle                 ///< handle of frequency domain object
                ) :
                m_handle( handle )
            {}

        ~FreqDomain( void ) = default;

        FreqDomain( FreqDomain const& other ) = delete;
        void operator=( FreqDomain const& other ) = delete;

        FreqDomain( FreqDomain&& other ) = delete;
        void operator=( FreqDomain&& other ) = delete;

    public:
        auto getHandle( void ) const { return m_handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_clock_type_t
        enum class clock_type_t
        {
            FIXED = 0,                                      ///< fixed crystal clock
            PLL,                                            ///< phase-locked-loop (PLL) frequency range
            DIVIDER,                                        ///< frequency is linked to another domain by a divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xet_freq_throttle_reasons_t
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
        /// @brief C++ version for ::xet_freq_domain_properties_t
        struct freq_domain_properties_t
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
        /// @brief C++ version for ::xet_clock_divider_t
        struct clock_divider_t
        {
            uint16_t numerator;                             ///< [in,out] numerator of the ratio
            uint16_t denominator;                           ///< [in,out] denominator of the ratio

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetFreqDomainGetProperties
        /// @returns
        ///     - ::freq_domain_properties_t: pointer to properties for the frequency domain
        /// 
        /// @throws result_t
        inline freq_domain_properties_t
        GetProperties(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetFreqDomainGetSourceFreqDomain
        /// @returns
        ///     - ::freq_domain_handle_t: pointer to a handle where the source frequency domain handle will be returned
        /// 
        /// @throws result_t
        inline freq_domain_handle_t
        GetSourceFreqDomain(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetFreqDomainGetSupportedClocks
        /// @returns
        ///     - uint32_t: pointer to array of frequencies
        /// 
        /// @throws result_t
        inline uint32_t
        GetSupportedClocks(
            uint32_t numClockPoints                         ///< [in] number of elements in pClocks
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetFreqDomainGetSupportedClockDividers
        /// @returns
        ///     - ::clock_divider_t: pointer to array of dividers
        /// 
        /// @throws result_t
        inline clock_divider_t
        GetSupportedClockDividers(
            uint32_t numClockDividers                       ///< [in] number of elements in pDividers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetFreqDomainGetClockRange
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
        /// @brief C++ wrapper for ::xetFreqDomainSetClockRange
        /// @throws result_t
        inline void
        SetClockRange(
            uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
            uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetFreqDomainSetClockDivider
        /// @returns
        ///     - ::clock_divider_t: pointer to frequency divider request
        /// 
        /// @throws result_t
        inline clock_divider_t
        SetClockDivider(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetFreqDomainGetCurrentFrequency
        /// @returns
        ///     - uint32_t: current frequency in MHz requested by the driver
        ///     - uint32_t: the actual frequency in MHz
        ///     - ::freq_throttle_reasons_t: the reason the resolved frequency is lower than the request
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
