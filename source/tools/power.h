#pragma once
#include "xet_api.h"

struct _xet_power_handle_t {};

struct _xet_freq_domain_handle_t {};

namespace L0 {

struct Power : _xet_power_handle_t {
    static xe_result_t create(xe_device_handle_t hDevice, uint32_t flags,
                              xet_power_handle_t *pPowerHandle) {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    virtual xe_result_t destroy() = 0;
    virtual xe_result_t getAveragePowerLimit(xet_power_average_limit_t *pLimit) = 0;
    virtual xe_result_t getBurstPowerLimit(xet_power_burst_limit_t *pLimit) = 0;
    virtual xe_result_t getPeakPowerLimit(xet_power_peak_limit_t *pLimit) = 0;
    virtual xe_result_t getAllPowerLimits(xet_power_limits_t *pLimits) = 0;
    virtual xe_result_t getDefaultPowerLimits(xet_power_limits_t *pLimits) = 0;
    virtual xe_result_t setAveragePowerLimit(xet_power_average_limit_t *pLimit) = 0;
    virtual xe_result_t setBurstPowerLimit(xet_power_burst_limit_t *pLimit) = 0;
    virtual xe_result_t setPeakPowerLimit(xet_power_peak_limit_t *pLimit) = 0;
    virtual xe_result_t setPowerLimits(xet_power_limits_t *pLimits) = 0;
    virtual xe_result_t getEnergyCounter(uint64_t *pEnergy) = 0;
    virtual xe_result_t getTurboMode(xet_turbo_mode_t *pTurboMode) = 0;
    virtual xe_result_t setTurboMode(xet_turbo_mode_t pTurboMode) = 0;
    virtual xe_result_t getFreqDomainCount(uint32_t *pNumFreqDomains) = 0;
    virtual xe_result_t getFreqDomain(uint32_t ordinal, xet_freq_domain_handle_t *phFreqDomain) = 0;
    virtual xe_result_t getFanCount(uint32_t *pFanCount) = 0;
    virtual xe_result_t getFanProperties(uint32_t fanIndex,
                                         xet_fan_properties_t *pFanProperties) = 0;
    virtual xe_result_t getFanSpeedTable(uint32_t fanIndex, xe_bool_t fanSpeedInRpm,
                                         uint32_t *pNumFanPoints, xet_fan_point_t *pFanPoints) = 0;
    virtual xe_result_t setFanSpeedTable(uint32_t fanIndex, uint32_t numFanPoints,
                                         xet_fan_point_t *pFanPoints) = 0;
    virtual xe_result_t getFanSpeed(uint32_t startFanIndex, uint32_t numFans,
                                    xe_bool_t fanSpeedInRpm, xet_fan_speed_info_t *pFanSpeed) = 0;
    virtual xe_result_t setFanSpeed(uint32_t startFanIndex, uint32_t numFans,
                                    xet_fan_speed_info_t *pFanSpeed) = 0;
    virtual xe_result_t getTemperatureSensorCount(uint32_t *pSensorCount) = 0;
    virtual xe_result_t getTemperatureProperties(uint32_t sensorIndex,
                                                 xet_temperature_properties_t *pProperties) = 0;
    virtual xe_result_t getTemperature(uint32_t startSensorIndex, uint32_t numSensors,
                                       uint16_t *pTemperatures) = 0;
    virtual xe_result_t setTemperatureThreshold(uint32_t sensorIndex, uint16_t maxTemperature) = 0;
    virtual xe_result_t getActivityCount(uint32_t *pActivityCount) = 0;
    virtual xe_result_t getActivityProperties(uint32_t activityIndex,
                                              xet_activity_properties_t *pProperties) = 0;
    virtual xe_result_t getActivityCounters(uint32_t startCounterIndex, uint32_t numCounters,
                                            xet_activity_counters_t *pCounters) = 0;

    static Power *fromHandle(xet_power_handle_t handle) { return static_cast<Power *>(handle); }

    inline xet_power_handle_t toHandle() { return this; }
};

struct FreqDomain : _xet_freq_domain_handle_t {
    virtual xe_result_t getProperties(xet_freq_domain_properties_t *pFreqDomainProperties) = 0;
    virtual xe_result_t getSourceFreqDomain(xet_freq_domain_handle_t *phSrcFreqDomain) = 0;
    virtual xe_result_t getSupportedClocks(uint32_t numClockPoints, uint32_t *pClocks) = 0;
    virtual xe_result_t getSupportedClockDividers(uint32_t numClockDividers,
                                                  xet_clock_divider_t *pDividers) = 0;
    virtual xe_result_t getClockRange(uint32_t *pMinClock, uint32_t *pMaxClock) = 0;
    virtual xe_result_t setClockRange(uint32_t minClock, uint32_t maxClock) = 0;
    virtual xe_result_t setClockDivider(xet_clock_divider_t *pClockDividerRequest) = 0;
    virtual xe_result_t getCurrentFrequency(uint32_t *pFreqRequest, uint32_t *pFreqResolved,
                                            xet_freq_throttle_reasons_t *pFreqThrottleReasons) = 0;

    static FreqDomain *fromHandle(xet_freq_domain_handle_t handle) {
        return static_cast<FreqDomain *>(handle);
    }

    inline xet_freq_domain_handle_t toHandle() { return this; }
};

} // namespace L0
