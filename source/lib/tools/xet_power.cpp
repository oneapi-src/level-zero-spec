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
#include "xet_api.hpp"
#include "xet_ddi.h"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    Power::Power( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    FreqDomain::FreqDomain( 
        Power* pPower                                   ///< [in] pointer to parent object
        ) :
        m_pPower( pPower )
    {
    }

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
    /// 
    /// @returns
    ///     - Power: handle for accessing power features of the device
    /// 
    /// @throws result_t
    Power* __xecall
    Power::Create(
        xe::Device* pDevice,                            ///< [in] pointer to the device object
        uint32_t flags                                  ///< [in] bitfield of ::power_init_flags_t
        )
    {
        // auto result = ::xetPowerCreate( handle, pDevice, flags );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::Create");

        return (Power*)0;
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
        Power* pPower                                   ///< [in] pointer to the power object to destroy
        )
    {
        // auto result = ::xetPowerDestroy( handle, pPower );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::Destroy");
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
        // auto result = ::xetPowerGetAveragePowerLimit( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetAveragePowerLimit");

        return average_limit_t{};
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
        // auto result = ::xetPowerGetBurstPowerLimit( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetBurstPowerLimit");

        return burst_limit_t{};
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
        // auto result = ::xetPowerGetPeakPowerLimit( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetPeakPowerLimit");

        return peak_limit_t{};
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
        // auto result = ::xetPowerGetAllPowerLimits( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetAllPowerLimits");

        return limits_t{};
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
        // auto result = ::xetPowerGetDefaultPowerLimits( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetDefaultPowerLimits");

        return limits_t{};
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
        // auto result = ::xetPowerSetAveragePowerLimit( handle, pLimit );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetAveragePowerLimit");
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
        // auto result = ::xetPowerSetBurstPowerLimit( handle, pLimit );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetBurstPowerLimit");
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
        // auto result = ::xetPowerSetPeakPowerLimit( handle, pLimit );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetPeakPowerLimit");
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
        // auto result = ::xetPowerSetPowerLimits( handle, pLimits );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetPowerLimits");
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
        // auto result = ::xetPowerGetEnergyCounter( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetEnergyCounter");

        return uint64_t{};
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
        // auto result = ::xetPowerGetTurboMode( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetTurboMode");

        return turbo_mode_t{};
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
        // auto result = ::xetPowerSetTurboMode( handle, pTurboMode );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetTurboMode");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the number of frequency domains on the device
    /// 
    /// @returns
    ///     - uint32_t: the number of frequency domains
    /// 
    /// @throws result_t
    uint32_t __xecall
    Power::GetFreqDomainCount(
        void
        )
    {
        // auto result = ::xetPowerGetFreqDomainCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetFreqDomainCount");

        return uint32_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get an object to a frequency domain on a device
    /// 
    /// @returns
    ///     - FreqDomain: pointer to handle of frequency domain object
    /// 
    /// @throws result_t
    FreqDomain* __xecall
    Power::GetFreqDomain(
        uint32_t ordinal                                ///< [in] frequency domain index [0 .. ::PowerGetFreqDomainCount - 1]
        )
    {
        // auto result = ::xetPowerGetFreqDomain( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetFreqDomain");

        return (FreqDomain*)0;
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
        // auto result = ::xetFreqDomainGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetProperties");

        return properties_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the source frequency domain handle for a frequency domain of type
    ///        ::CLOCK_TYPE_DIVIDER
    /// 
    /// @returns
    ///     - FreqDomain: pointer to a handle where the source frequency domain handle will be returned
    /// 
    /// @throws result_t
    FreqDomain* __xecall
    FreqDomain::GetSourceFreqDomain(
        void
        )
    {
        // auto result = ::xetFreqDomainGetSourceFreqDomain( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetSourceFreqDomain");

        return (FreqDomain*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get supported frequency points for frequency domains with clock type
    ///        ::CLOCK_TYPE_PLL
    /// 
    /// @details
    ///     - The total available list of frequencies can be found in
    ///       ::freq_domain_properties_t.numClockPoints.
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
        // auto result = ::xetFreqDomainGetSupportedClocks( handle, numClockPoints );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetSupportedClocks");

        return uint32_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get supported frequency dividers for frequency domains with clock type
    ///        ::CLOCK_TYPE_DIVIDER
    /// 
    /// @details
    ///     - The total available list of frequencies can be found in
    ///       ::freq_domain_properties_t.numClockDividers.
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
        // auto result = ::xetFreqDomainGetSupportedClockDividers( handle, numClockDividers );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetSupportedClockDividers");

        return clock_divider_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the frequency range for a frequency domain with clock type
    ///        ::CLOCK_TYPE_PLL.
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
        // auto result = ::xetFreqDomainGetClockRange( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetClockRange");

        return std::tuple<uint32_t, uint32_t>{};
    }

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
    /// 
    /// @throws result_t
    void __xecall
    FreqDomain::SetClockRange(
        uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
        uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
        )
    {
        // auto result = ::xetFreqDomainSetClockRange( handle, minClock, maxClock );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::SetClockRange");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set frequency divider for a frequency domain with clock type
    ///        ::CLOCK_TYPE_DIVIDER
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
        // auto result = ::xetFreqDomainSetClockDivider( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::SetClockDivider");

        return clock_divider_t{};
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
        // auto result = ::xetFreqDomainGetCurrentFrequency( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetCurrentFrequency");

        return std::tuple<uint32_t, uint32_t, freq_throttle_reasons_t>{};
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
        // auto result = ::xetPowerFanCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanCount");

        return uint32_t{};
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
        uint32_t fanIndex                               ///< [in] fan index [0 .. ::PowerFanCount - 1]
        )
    {
        // auto result = ::xetPowerFanGetProperties( handle, fanIndex );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanGetProperties");

        return fan_properties_t{};
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
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::PowerFanCount - 1]
        xe::bool_t fanSpeedInRpm,                       ///< [in] true will request fan speeds in RPM, otherwise in percentage
        uint32_t* pNumFanPoints                         ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                        ///< number of elements returned
        )
    {
        // auto result = ::xetPowerFanGetSpeedTable( handle, fanIndex, fanSpeedInRpm, pNumFanPoints );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanGetSpeedTable");

        return fan_point_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan speed table
    /// 
    /// @details
    ///     - Use ::PowerFanGetProperties to determine acceptable units for fan
    ///       speed (percent, RPM).
    ///     - Fan points should be ordered according to increasing temperature.
    /// 
    /// @throws result_t
    void __xecall
    Power::FanSetSpeedTable(
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::PowerFanCount - 1]
        uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
        fan_point_t* pFanPoints                         ///< [in] pointer to an array of temperature/fan-speed points
        )
    {
        // auto result = ::xetPowerFanSetSpeedTable( handle, fanIndex, numFanPoints, pFanPoints );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanSetSpeedTable");
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
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::PowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        xe::bool_t fanSpeedInRpm                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
        )
    {
        // auto result = ::xetPowerFanGetSpeed( handle, startFanIndex, numFans, fanSpeedInRpm );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanGetSpeed");

        return fan_speed_info_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan speeds
    /// 
    /// @details
    ///     - Use ::fan_speed_info_t.fanSpeedMode to set whether the speed should be
    ///       fixed or dynamically controlled
    /// 
    /// @throws result_t
    void __xecall
    Power::FanSetSpeed(
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::PowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        fan_speed_info_t* pFanSpeed                     ///< [in] pointer to an array of current fan speeds
        )
    {
        // auto result = ::xetPowerFanSetSpeed( handle, startFanIndex, numFans, pFanSpeed );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanSetSpeed");
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
        // auto result = ::xetPowerTemperatureSensorCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::TemperatureSensorCount");

        return uint32_t{};
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
        uint32_t sensorIndex                            ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
        )
    {
        // auto result = ::xetPowerGetTemperatureProperties( handle, sensorIndex );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetTemperatureProperties");

        return temperature_properties_t{};
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
        uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
        uint32_t numSensors                             ///< [in] pTemperatures will contain results for sensors index
                                                        ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
        )
    {
        // auto result = ::xetPowerGetTemperature( handle, startSensorIndex, numSensors );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetTemperature");

        return uint16_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set temperature threshold
    /// 
    /// @details
    ///     - Check ::temperature_properties_t.canChangeThreshold to determine if
    ///       the threshold can be changed.
    ///     - On most systems, there is only one threshold and sensorIndex should be
    ///       0.
    ///     - **This is an overclocking feature and will void device warranty**
    /// 
    /// @throws result_t
    void __xecall
    Power::SetTemperatureThreshold(
        uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
        uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                        ///< will be throttled
        )
    {
        // auto result = ::xetPowerSetTemperatureThreshold( handle, sensorIndex, maxTemperature );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetTemperatureThreshold");
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
        // auto result = ::xetPowerActivityCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::ActivityCount");

        return uint32_t{};
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
        uint32_t activityIndex                          ///< [in] activity counter index [0 .. ::PowerActivityCount]
        )
    {
        // auto result = ::xetPowerGetActivityProperties( handle, activityIndex );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetActivityProperties");

        return activity_properties_t{};
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
        uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::PowerActivityCount]
        uint32_t numCounters                            ///< [in] pCounters will contain results for activity counter index
                                                        ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
        )
    {
        // auto result = ::xetPowerGetActivityCounters( handle, startCounterIndex, numCounters );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetActivityCounters");

        return activity_counters_t{};
    }

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts fan_capabilities_t to std::string
    std::string to_string( fan_capabilities_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(fan_capabilities_t::GET_SPEED_PERCENTAGE) & bits )
            str += "fan_capabilities_t::GET_SPEED_PERCENTAGE | ";
        if( static_cast<uint32_t>(fan_capabilities_t::SET_SPEED_PERCENTAGE) & bits )
            str += "fan_capabilities_t::SET_SPEED_PERCENTAGE | ";
        if( static_cast<uint32_t>(fan_capabilities_t::GET_SPEED_RPM) & bits )
            str += "fan_capabilities_t::GET_SPEED_RPM | ";
        if( static_cast<uint32_t>(fan_capabilities_t::SET_SPEED_RPM) & bits )
            str += "fan_capabilities_t::SET_SPEED_RPM | ";
        if( static_cast<uint32_t>(fan_capabilities_t::HAVE_TEMPERATURE_SPEED_TABLE) & bits )
            str += "fan_capabilities_t::HAVE_TEMPERATURE_SPEED_TABLE | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts fan_speed_mode_t to std::string
    std::string to_string( fan_speed_mode_t val )
    {
        switch( val )
        {
        case fan_speed_mode_t::AUTO:
            return std::string("fan_speed_mode_t::AUTO");
        case fan_speed_mode_t::FIXED:
            return std::string("fan_speed_mode_t::FIXED");
        };
        return std::string("fan_speed_mode_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::init_flags_t to std::string
    std::string to_string( Power::init_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(Power::init_flags_t::NONE) & bits )
            str += "Power::init_flags_t::NONE | ";
        if( static_cast<uint32_t>(Power::init_flags_t::WRITE) & bits )
            str += "Power::init_flags_t::WRITE | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::gpu_domain_t to std::string
    std::string to_string( Power::gpu_domain_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(Power::gpu_domain_t::BASE) & bits )
            str += "Power::gpu_domain_t::BASE | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::VIDEO_DECODE) & bits )
            str += "Power::gpu_domain_t::VIDEO_DECODE | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::VIDEO_ENCODE) & bits )
            str += "Power::gpu_domain_t::VIDEO_ENCODE | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::VIDEO_PROCESSING) & bits )
            str += "Power::gpu_domain_t::VIDEO_PROCESSING | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::_3D_FIXED_FUNCTION) & bits )
            str += "Power::gpu_domain_t::_3D_FIXED_FUNCTION | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::_3D_RENDER) & bits )
            str += "Power::gpu_domain_t::_3D_RENDER | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::COMPUTE) & bits )
            str += "Power::gpu_domain_t::COMPUTE | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::SYSTOLIC_ARRAY) & bits )
            str += "Power::gpu_domain_t::SYSTOLIC_ARRAY | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::RAYTRACING) & bits )
            str += "Power::gpu_domain_t::RAYTRACING | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::LOCAL_MEMORY) & bits )
            str += "Power::gpu_domain_t::LOCAL_MEMORY | ";
        if( static_cast<uint32_t>(Power::gpu_domain_t::BASE_CHIPLET_LINK) & bits )
            str += "Power::gpu_domain_t::BASE_CHIPLET_LINK | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::average_limit_version_t to std::string
    std::string to_string( Power::average_limit_version_t val )
    {
        switch( val )
        {
        case Power::average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT:
            return std::string("Power::average_limit_version_t::AVERAGE_POWER_LIMIT_VERSION_CURRENT");
        };
        return std::string("Power::average_limit_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::turbo_mode_t to std::string
    std::string to_string( Power::turbo_mode_t val )
    {
        switch( val )
        {
        case Power::turbo_mode_t::DISABLED:
            return std::string("Power::turbo_mode_t::DISABLED");
        case Power::turbo_mode_t::DEFAULT:
            return std::string("Power::turbo_mode_t::DEFAULT");
        case Power::turbo_mode_t::MIN_PERFORMANCE:
            return std::string("Power::turbo_mode_t::MIN_PERFORMANCE");
        case Power::turbo_mode_t::EFFICIENT_PERFORMANCE:
            return std::string("Power::turbo_mode_t::EFFICIENT_PERFORMANCE");
        case Power::turbo_mode_t::AGGRESSIVE_PERFORMANCE:
            return std::string("Power::turbo_mode_t::AGGRESSIVE_PERFORMANCE");
        case Power::turbo_mode_t::MAX_PERFORMANCE:
            return std::string("Power::turbo_mode_t::MAX_PERFORMANCE");
        };
        return std::string("Power::turbo_mode_t::?");
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FreqDomain::clock_type_t to std::string
    std::string to_string( FreqDomain::clock_type_t val )
    {
        switch( val )
        {
        case FreqDomain::clock_type_t::FIXED:
            return std::string("FreqDomain::clock_type_t::FIXED");
        case FreqDomain::clock_type_t::PLL:
            return std::string("FreqDomain::clock_type_t::PLL");
        case FreqDomain::clock_type_t::DIVIDER:
            return std::string("FreqDomain::clock_type_t::DIVIDER");
        };
        return std::string("FreqDomain::clock_type_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FreqDomain::freq_throttle_reasons_t to std::string
    std::string to_string( FreqDomain::freq_throttle_reasons_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::NONE) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::NONE | ";
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::AVE_PWR_CAP) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::AVE_PWR_CAP | ";
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::BURST_PWR_CAP) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::BURST_PWR_CAP | ";
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::CURRENT_LIMIT) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::CURRENT_LIMIT | ";
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::THERMAL_LIMIT) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::THERMAL_LIMIT | ";
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::PSU_ALERT) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::PSU_ALERT | ";
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::SW_RANGE) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::SW_RANGE | ";
        if( static_cast<uint32_t>(FreqDomain::freq_throttle_reasons_t::HW_RANGE) & bits )
            str += "FreqDomain::freq_throttle_reasons_t::HW_RANGE | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }


#endif // _DEBUG
} // namespace xet
