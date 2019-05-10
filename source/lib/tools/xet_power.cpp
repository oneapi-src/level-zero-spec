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

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    Power::Power( 
        power_handle_t handle                           ///< handle of power object
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerCreate
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
    inline Power* 
    Power::Create(
        xe::Device* hDevice,                            ///< [in] handle of the device object
        uint32_t flags                                  ///< [in] bitfield of ::power_init_flags_t
        )
    {
        // auto result = ::xetPowerCreate( handle, hDevice, flags );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerDestroy
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **nvmlShutdown**
    ///     - **rsmi_shut_down**
    /// 
    /// @throws result_t
    inline void 
    Power::Destroy(
        Power* hPower                                   ///< [in] handle of the power object to destroy
        )
    {
        // auto result = ::xetPowerDestroy( handle, hPower );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetAveragePowerLimit
    /// 
    /// @returns
    ///     - average_limit_t: information about the average power limit
    /// 
    /// @throws result_t
    inline Power::average_limit_t 
    Power::GetAveragePowerLimit(
        void
        )
    {
        // auto result = ::xetPowerGetAveragePowerLimit( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetAveragePowerLimit");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetBurstPowerLimit
    /// 
    /// @returns
    ///     - burst_limit_t: information about the burst power limit
    /// 
    /// @throws result_t
    inline Power::burst_limit_t 
    Power::GetBurstPowerLimit(
        void
        )
    {
        // auto result = ::xetPowerGetBurstPowerLimit( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetBurstPowerLimit");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetPeakPowerLimit
    /// 
    /// @returns
    ///     - peak_limit_t: information about the peak power limit
    /// 
    /// @throws result_t
    inline Power::peak_limit_t 
    Power::GetPeakPowerLimit(
        void
        )
    {
        // auto result = ::xetPowerGetPeakPowerLimit( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetPeakPowerLimit");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetAllPowerLimits
    /// 
    /// @returns
    ///     - limits_t: information about the average/burst/peak power limits
    /// 
    /// @throws result_t
    inline Power::limits_t 
    Power::GetAllPowerLimits(
        void
        )
    {
        // auto result = ::xetPowerGetAllPowerLimits( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetAllPowerLimits");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetDefaultPowerLimits
    /// 
    /// @returns
    ///     - limits_t: information about the default average/burst/peak power limits
    /// 
    /// @throws result_t
    inline Power::limits_t 
    Power::GetDefaultPowerLimits(
        void
        )
    {
        // auto result = ::xetPowerGetDefaultPowerLimits( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetDefaultPowerLimits");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerSetAveragePowerLimit
    /// 
    /// @throws result_t
    inline void 
    Power::SetAveragePowerLimit(
        average_limit_t* pLimit                         ///< [in] information about the average power limit
        )
    {
        // auto result = ::xetPowerSetAveragePowerLimit( handle, pLimit );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetAveragePowerLimit");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerSetBurstPowerLimit
    /// 
    /// @throws result_t
    inline void 
    Power::SetBurstPowerLimit(
        burst_limit_t* pLimit                           ///< [in] information about the burst power limit
        )
    {
        // auto result = ::xetPowerSetBurstPowerLimit( handle, pLimit );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetBurstPowerLimit");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerSetPeakPowerLimit
    /// 
    /// @throws result_t
    inline void 
    Power::SetPeakPowerLimit(
        peak_limit_t* pLimit                            ///< [in] information about the peak power limit
        )
    {
        // auto result = ::xetPowerSetPeakPowerLimit( handle, pLimit );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetPeakPowerLimit");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerSetPowerLimits
    /// 
    /// @throws result_t
    inline void 
    Power::SetPowerLimits(
        limits_t* pLimits                               ///< [in] information about the average/burst/peak power limits
        )
    {
        // auto result = ::xetPowerSetPowerLimits( handle, pLimits );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetPowerLimits");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetEnergyCounter
    /// 
    /// @details
    ///     - Average power = delta(energy counter in millijoules) / delta(time in
    ///       milliseconds)
    /// 
    /// @returns
    ///     - uint64_t: the energy counter in millijoules
    /// 
    /// @throws result_t
    inline uint64_t 
    Power::GetEnergyCounter(
        void
        )
    {
        // auto result = ::xetPowerGetEnergyCounter( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetEnergyCounter");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetTurboMode
    /// 
    /// @returns
    ///     - turbo_mode_t: turbo mode currently in effect
    /// 
    /// @throws result_t
    inline Power::turbo_mode_t 
    Power::GetTurboMode(
        void
        )
    {
        // auto result = ::xetPowerGetTurboMode( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetTurboMode");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerSetTurboMode
    /// 
    /// @throws result_t
    inline void 
    Power::SetTurboMode(
        turbo_mode_t pTurboMode                         ///< [in] new turbo mode
        )
    {
        // auto result = ::xetPowerSetTurboMode( handle, pTurboMode );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::SetTurboMode");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetFreqDomainCount
    /// 
    /// @returns
    ///     - uint32_t: the number of frequency domains
    /// 
    /// @throws result_t
    inline uint32_t 
    Power::GetFreqDomainCount(
        void
        )
    {
        // auto result = ::xetPowerGetFreqDomainCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetFreqDomainCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetFreqDomainHandle
    /// 
    /// @returns
    ///     - FreqDomain: pointer to handle of frequency domain object
    /// 
    /// @throws result_t
    inline FreqDomain* 
    Power::GetFreqDomainHandle(
        uint32_t ordinal                                ///< [in] frequency domain index [0 .. ::PowerGetFreqDomainCount - 1]
        )
    {
        // auto result = ::xetPowerGetFreqDomainHandle( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetFreqDomainHandle");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerFanCount
    /// 
    /// @returns
    ///     - uint32_t: the number of fans on the device
    /// 
    /// @throws result_t
    inline uint32_t 
    Power::FanCount(
        void
        )
    {
        // auto result = ::xetPowerFanCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerFanGetProperties
    /// 
    /// @returns
    ///     - fan_properties_t: pointer to storage for fan properties
    /// 
    /// @throws result_t
    inline Power::fan_properties_t 
    Power::FanGetProperties(
        uint32_t fanIndex                               ///< [in] fan index [0 .. ::PowerFanCount - 1]
        )
    {
        // auto result = ::xetPowerFanGetProperties( handle, fanIndex );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanGetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerFanGetSpeedTable
    /// 
    /// @details
    ///     - Set pFanSpeedTable = nullptr to find out the current number of fan
    ///       speed points in the table.
    /// 
    /// @returns
    ///     - fan_point_t: pointer to an array of temperature/fan-speed points
    /// 
    /// @throws result_t
    inline Power::fan_point_t 
    Power::FanGetSpeedTable(
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::PowerFanCount - 1]
        xe::bool_t fanSpeedInRpm,                       ///< [in] true will request fan speeds in RPM, otherwise in percentage
        uint32_t* pNumFanPoints                         ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                        ///< number of elements returned
        )
    {
        // auto result = ::xetPowerFanGetSpeedTable( handle, fanIndex, fanSpeedInRpm, pNumFanPoints );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanGetSpeedTable");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerFanSetSpeedTable
    /// 
    /// @details
    ///     - Use ::PowerFanGetProperties to determine acceptable units for fan
    ///       speed (percent, RPM).
    ///     - Fan points should be ordered according to increasing temperature.
    /// 
    /// @throws result_t
    inline void 
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
    /// @brief C++ wrapper for ::xetPowerFanGetSpeed
    /// 
    /// @details
    ///     - The array pFanSpeed must contain at least numFans entries.
    /// 
    /// @returns
    ///     - fan_speed_info_t: pointer to an array of current fan speeds
    /// 
    /// @throws result_t
    inline Power::fan_speed_info_t 
    Power::FanGetSpeed(
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::PowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        xe::bool_t fanSpeedInRpm                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
        )
    {
        // auto result = ::xetPowerFanGetSpeed( handle, startFanIndex, numFans, fanSpeedInRpm );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::FanGetSpeed");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerFanSetSpeed
    /// 
    /// @details
    ///     - Use ::fan_speed_info_t.fanSpeedMode to set whether the speed should be
    ///       fixed or dynamically controlled
    /// 
    /// @throws result_t
    inline void 
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
    /// @brief C++ wrapper for ::xetPowerTemperatureSensorCount
    /// 
    /// @returns
    ///     - uint32_t: the number of temperature sensors on the device
    /// 
    /// @throws result_t
    inline uint32_t 
    Power::TemperatureSensorCount(
        void
        )
    {
        // auto result = ::xetPowerTemperatureSensorCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::TemperatureSensorCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetTemperatureProperties
    /// 
    /// @details
    ///     - Temperature sensor index 0 is special - it gives the maximum
    ///       temperature across all sensors
    /// 
    /// @returns
    ///     - temperature_properties_t: pointer to properties for this sensor
    /// 
    /// @throws result_t
    inline Power::temperature_properties_t 
    Power::GetTemperatureProperties(
        uint32_t sensorIndex                            ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
        )
    {
        // auto result = ::xetPowerGetTemperatureProperties( handle, sensorIndex );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetTemperatureProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetTemperature
    /// 
    /// @details
    ///     - Temperature sensor index 0 is special - it gives the maximum
    ///       temperature across all sensors
    /// 
    /// @returns
    ///     - uint16_t: pointer to an array of temperatures in units of degrees celsius
    /// 
    /// @throws result_t
    inline uint16_t 
    Power::GetTemperature(
        uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::PowerTemperatureSensorCount]
        uint32_t numSensors                             ///< [in] pTemperatures will contain results for sensors index
                                                        ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
        )
    {
        // auto result = ::xetPowerGetTemperature( handle, startSensorIndex, numSensors );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetTemperature");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerSetTemperatureThreshold
    /// 
    /// @details
    ///     - Check ::temperature_properties_t.canChangeThreshold to determine if
    ///       the threshold can be changed.
    ///     - On most systems, there is only one threshold and sensorIndex should be
    ///       0.
    ///     - **This is an overclocking feature and will void device warranty**
    /// 
    /// @throws result_t
    inline void 
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
    /// @brief C++ wrapper for ::xetPowerActivityCount
    /// 
    /// @returns
    ///     - uint32_t: the number of activity counters on the device
    /// 
    /// @throws result_t
    inline uint32_t 
    Power::ActivityCount(
        void
        )
    {
        // auto result = ::xetPowerActivityCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::ActivityCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetActivityProperties
    /// 
    /// @details
    ///     - Activity counter index 0 is special - it acculates activity across all
    ///       blocks.
    /// 
    /// @returns
    ///     - activity_properties_t: pointer to properties for this activity counter
    /// 
    /// @throws result_t
    inline Power::activity_properties_t 
    Power::GetActivityProperties(
        uint32_t activityIndex                          ///< [in] activity counter index [0 .. ::PowerActivityCount]
        )
    {
        // auto result = ::xetPowerGetActivityProperties( handle, activityIndex );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetActivityProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetPowerGetActivityCounters
    /// 
    /// @details
    ///     - Activity counter index 0 is special - it acculates activity across all
    ///       blocks.
    /// 
    /// @returns
    ///     - activity_counters_t: pointer to an array of activity counter data
    /// 
    /// @throws result_t
    inline Power::activity_counters_t 
    Power::GetActivityCounters(
        uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::PowerActivityCount]
        uint32_t numCounters                            ///< [in] pCounters will contain results for activity counter index
                                                        ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
        )
    {
        // auto result = ::xetPowerGetActivityCounters( handle, startCounterIndex, numCounters );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Power::GetActivityCounters");
    }

    ///////////////////////////////////////////////////////////////////////////////
    FreqDomain::FreqDomain( 
        freq_domain_handle_t handle                     ///< handle of frequency domain object
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainGetProperties
    /// 
    /// @returns
    ///     - properties_t: pointer to properties for the frequency domain
    /// 
    /// @throws result_t
    inline FreqDomain::properties_t 
    FreqDomain::GetProperties(
        void
        )
    {
        // auto result = ::xetFreqDomainGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainGetSourceFreqDomain
    /// 
    /// @returns
    ///     - FreqDomain: pointer to a handle where the source frequency domain handle will be returned
    /// 
    /// @throws result_t
    inline FreqDomain* 
    FreqDomain::GetSourceFreqDomain(
        void
        )
    {
        // auto result = ::xetFreqDomainGetSourceFreqDomain( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetSourceFreqDomain");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainGetSupportedClocks
    /// 
    /// @details
    ///     - The total available list of frequencies can be found in
    ///       ::freq_domain_properties_t.numClockPoints.
    /// 
    /// @returns
    ///     - uint32_t: pointer to array of frequencies
    /// 
    /// @throws result_t
    inline uint32_t 
    FreqDomain::GetSupportedClocks(
        uint32_t numClockPoints                         ///< [in] number of elements in pClocks
        )
    {
        // auto result = ::xetFreqDomainGetSupportedClocks( handle, numClockPoints );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetSupportedClocks");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainGetSupportedClockDividers
    /// 
    /// @details
    ///     - The total available list of frequencies can be found in
    ///       ::freq_domain_properties_t.numClockDividers.
    /// 
    /// @returns
    ///     - clock_divider_t: pointer to array of dividers
    /// 
    /// @throws result_t
    inline FreqDomain::clock_divider_t 
    FreqDomain::GetSupportedClockDividers(
        uint32_t numClockDividers                       ///< [in] number of elements in pDividers
        )
    {
        // auto result = ::xetFreqDomainGetSupportedClockDividers( handle, numClockDividers );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetSupportedClockDividers");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainGetClockRange
    /// 
    /// @returns
    ///     - uint32_t: min clock frequency in units of MHz
    ///     - uint32_t: max clock frequency in units of MHz
    /// 
    /// @throws result_t
    inline std::tuple<uint32_t, uint32_t> 
    FreqDomain::GetClockRange(
        void
        )
    {
        // auto result = ::xetFreqDomainGetClockRange( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetClockRange");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainSetClockRange
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
    inline void 
    FreqDomain::SetClockRange(
        uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
        uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
        )
    {
        // auto result = ::xetFreqDomainSetClockRange( handle, minClock, maxClock );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::SetClockRange");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainSetClockDivider
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
    inline FreqDomain::clock_divider_t 
    FreqDomain::SetClockDivider(
        void
        )
    {
        // auto result = ::xetFreqDomainSetClockDivider( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::SetClockDivider");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetFreqDomainGetCurrentFrequency
    /// 
    /// @returns
    ///     - uint32_t: current frequency in MHz requested by the driver
    ///     - uint32_t: the actual frequency in MHz
    ///     - freq_throttle_reasons_t: the reason the resolved frequency is lower than the request
    /// 
    /// @throws result_t
    inline std::tuple<uint32_t, uint32_t, FreqDomain::freq_throttle_reasons_t> 
    FreqDomain::GetCurrentFrequency(
        void
        )
    {
        // auto result = ::xetFreqDomainGetCurrentFrequency( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::FreqDomain::GetCurrentFrequency");
    }

} // namespace xet
