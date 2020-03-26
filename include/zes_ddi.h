/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_ddi.h
 *
 */
#ifndef _ZES_DDI_H
#define _ZES_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "zes_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanGet 
typedef ze_result_t (__zecall *zes_pfnSysmanGet_t)(
    zes_device_handle_t,
    zes_sysman_version_t,
    zes_sysman_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanDeviceGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanDeviceGetProperties_t)(
    zes_sysman_handle_t,
    zes_sysman_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanDeviceGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanDeviceGetState_t)(
    zes_sysman_handle_t,
    zes_sysman_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanDeviceReset 
typedef ze_result_t (__zecall *zes_pfnSysmanDeviceReset_t)(
    zes_sysman_handle_t,
    ze_bool_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerGet 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_sched_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPerformanceFactorGet 
typedef ze_result_t (__zecall *zes_pfnSysmanPerformanceFactorGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_perf_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanProcessesGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanProcessesGetState_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_process_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPciGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanPciGetProperties_t)(
    zes_sysman_handle_t,
    zes_pci_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPciGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanPciGetState_t)(
    zes_sysman_handle_t,
    zes_pci_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPciGetBars 
typedef ze_result_t (__zecall *zes_pfnSysmanPciGetBars_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_pci_bar_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPciGetStats 
typedef ze_result_t (__zecall *zes_pfnSysmanPciGetStats_t)(
    zes_sysman_handle_t,
    zes_pci_stats_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPowerGet 
typedef ze_result_t (__zecall *zes_pfnSysmanPowerGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_pwr_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyGet 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_freq_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEngineGet 
typedef ze_result_t (__zecall *zes_pfnSysmanEngineGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_engine_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanStandbyGet 
typedef ze_result_t (__zecall *zes_pfnSysmanStandbyGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_standby_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFirmwareGet 
typedef ze_result_t (__zecall *zes_pfnSysmanFirmwareGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_firmware_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanMemoryGet 
typedef ze_result_t (__zecall *zes_pfnSysmanMemoryGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_mem_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFabricPortGet 
typedef ze_result_t (__zecall *zes_pfnSysmanFabricPortGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_fabric_port_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanTemperatureGet 
typedef ze_result_t (__zecall *zes_pfnSysmanTemperatureGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_temp_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPsuGet 
typedef ze_result_t (__zecall *zes_pfnSysmanPsuGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_psu_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFanGet 
typedef ze_result_t (__zecall *zes_pfnSysmanFanGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_fan_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanLedGet 
typedef ze_result_t (__zecall *zes_pfnSysmanLedGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_led_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanRasGet 
typedef ze_result_t (__zecall *zes_pfnSysmanRasGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_ras_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEventGet 
typedef ze_result_t (__zecall *zes_pfnSysmanEventGet_t)(
    zes_sysman_handle_t,
    zes_sysman_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanDiagnosticsGet 
typedef ze_result_t (__zecall *zes_pfnSysmanDiagnosticsGet_t)(
    zes_sysman_handle_t,
    uint32_t*,
    zes_sysman_diag_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sysman functions pointers
typedef struct _zes_sysman_dditable_t
{
    zes_pfnSysmanGet_t                                          pfnGet;
    zes_pfnSysmanDeviceGetProperties_t                          pfnDeviceGetProperties;
    zes_pfnSysmanDeviceGetState_t                               pfnDeviceGetState;
    zes_pfnSysmanDeviceReset_t                                  pfnDeviceReset;
    zes_pfnSysmanSchedulerGet_t                                 pfnSchedulerGet;
    zes_pfnSysmanPerformanceFactorGet_t                         pfnPerformanceFactorGet;
    zes_pfnSysmanProcessesGetState_t                            pfnProcessesGetState;
    zes_pfnSysmanPciGetProperties_t                             pfnPciGetProperties;
    zes_pfnSysmanPciGetState_t                                  pfnPciGetState;
    zes_pfnSysmanPciGetBars_t                                   pfnPciGetBars;
    zes_pfnSysmanPciGetStats_t                                  pfnPciGetStats;
    zes_pfnSysmanPowerGet_t                                     pfnPowerGet;
    zes_pfnSysmanFrequencyGet_t                                 pfnFrequencyGet;
    zes_pfnSysmanEngineGet_t                                    pfnEngineGet;
    zes_pfnSysmanStandbyGet_t                                   pfnStandbyGet;
    zes_pfnSysmanFirmwareGet_t                                  pfnFirmwareGet;
    zes_pfnSysmanMemoryGet_t                                    pfnMemoryGet;
    zes_pfnSysmanFabricPortGet_t                                pfnFabricPortGet;
    zes_pfnSysmanTemperatureGet_t                               pfnTemperatureGet;
    zes_pfnSysmanPsuGet_t                                       pfnPsuGet;
    zes_pfnSysmanFanGet_t                                       pfnFanGet;
    zes_pfnSysmanLedGet_t                                       pfnLedGet;
    zes_pfnSysmanRasGet_t                                       pfnRasGet;
    zes_pfnSysmanEventGet_t                                     pfnEventGet;
    zes_pfnSysmanDiagnosticsGet_t                               pfnDiagnosticsGet;
} zes_sysman_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerGetProperties_t)(
    zes_sysman_sched_handle_t,
    zes_sched_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerGetCurrentMode 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerGetCurrentMode_t)(
    zes_sysman_sched_handle_t,
    zes_sched_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerGetTimeoutModeProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerGetTimeoutModeProperties_t)(
    zes_sysman_sched_handle_t,
    ze_bool_t,
    zes_sched_timeout_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerGetTimesliceModeProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerGetTimesliceModeProperties_t)(
    zes_sysman_sched_handle_t,
    ze_bool_t,
    zes_sched_timeslice_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerSetTimeoutMode 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerSetTimeoutMode_t)(
    zes_sysman_sched_handle_t,
    zes_sched_timeout_properties_t*,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerSetTimesliceMode 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerSetTimesliceMode_t)(
    zes_sysman_sched_handle_t,
    zes_sched_timeslice_properties_t*,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerSetExclusiveMode 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerSetExclusiveMode_t)(
    zes_sysman_sched_handle_t,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanSchedulerSetComputeUnitDebugMode 
typedef ze_result_t (__zecall *zes_pfnSysmanSchedulerSetComputeUnitDebugMode_t)(
    zes_sysman_sched_handle_t,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanScheduler functions pointers
typedef struct _zes_sysman_scheduler_dditable_t
{
    zes_pfnSysmanSchedulerGetProperties_t                       pfnGetProperties;
    zes_pfnSysmanSchedulerGetCurrentMode_t                      pfnGetCurrentMode;
    zes_pfnSysmanSchedulerGetTimeoutModeProperties_t            pfnGetTimeoutModeProperties;
    zes_pfnSysmanSchedulerGetTimesliceModeProperties_t          pfnGetTimesliceModeProperties;
    zes_pfnSysmanSchedulerSetTimeoutMode_t                      pfnSetTimeoutMode;
    zes_pfnSysmanSchedulerSetTimesliceMode_t                    pfnSetTimesliceMode;
    zes_pfnSysmanSchedulerSetExclusiveMode_t                    pfnSetExclusiveMode;
    zes_pfnSysmanSchedulerSetComputeUnitDebugMode_t             pfnSetComputeUnitDebugMode;
} zes_sysman_scheduler_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanScheduler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanSchedulerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_scheduler_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanSchedulerProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanSchedulerProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_scheduler_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPerformanceFactorGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanPerformanceFactorGetProperties_t)(
    zes_sysman_perf_handle_t,
    zes_perf_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPerformanceFactorGetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanPerformanceFactorGetConfig_t)(
    zes_sysman_perf_handle_t,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPerformanceFactorSetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanPerformanceFactorSetConfig_t)(
    zes_sysman_perf_handle_t,
    double
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanPerformanceFactor functions pointers
typedef struct _zes_sysman_performance_factor_dditable_t
{
    zes_pfnSysmanPerformanceFactorGetProperties_t               pfnGetProperties;
    zes_pfnSysmanPerformanceFactorGetConfig_t                   pfnGetConfig;
    zes_pfnSysmanPerformanceFactorSetConfig_t                   pfnSetConfig;
} zes_sysman_performance_factor_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPerformanceFactor table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPerformanceFactorProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_performance_factor_dditable_t* pDdiTable ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanPerformanceFactorProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanPerformanceFactorProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_performance_factor_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPowerGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanPowerGetProperties_t)(
    zes_sysman_pwr_handle_t,
    zes_power_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPowerGetEnergyCounter 
typedef ze_result_t (__zecall *zes_pfnSysmanPowerGetEnergyCounter_t)(
    zes_sysman_pwr_handle_t,
    zes_power_energy_counter_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPowerGetLimits 
typedef ze_result_t (__zecall *zes_pfnSysmanPowerGetLimits_t)(
    zes_sysman_pwr_handle_t,
    zes_power_sustained_limit_t*,
    zes_power_burst_limit_t*,
    zes_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPowerSetLimits 
typedef ze_result_t (__zecall *zes_pfnSysmanPowerSetLimits_t)(
    zes_sysman_pwr_handle_t,
    const zes_power_sustained_limit_t*,
    const zes_power_burst_limit_t*,
    const zes_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPowerGetEnergyThreshold 
typedef ze_result_t (__zecall *zes_pfnSysmanPowerGetEnergyThreshold_t)(
    zes_sysman_pwr_handle_t,
    zes_energy_threshold_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPowerSetEnergyThreshold 
typedef ze_result_t (__zecall *zes_pfnSysmanPowerSetEnergyThreshold_t)(
    zes_sysman_pwr_handle_t,
    double
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanPower functions pointers
typedef struct _zes_sysman_power_dditable_t
{
    zes_pfnSysmanPowerGetProperties_t                           pfnGetProperties;
    zes_pfnSysmanPowerGetEnergyCounter_t                        pfnGetEnergyCounter;
    zes_pfnSysmanPowerGetLimits_t                               pfnGetLimits;
    zes_pfnSysmanPowerSetLimits_t                               pfnSetLimits;
    zes_pfnSysmanPowerGetEnergyThreshold_t                      pfnGetEnergyThreshold;
    zes_pfnSysmanPowerSetEnergyThreshold_t                      pfnSetEnergyThreshold;
} zes_sysman_power_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanPowerProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanPowerProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_power_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyGetProperties_t)(
    zes_sysman_freq_handle_t,
    zes_freq_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyGetAvailableClocks 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyGetAvailableClocks_t)(
    zes_sysman_freq_handle_t,
    uint32_t*,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyGetRange 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyGetRange_t)(
    zes_sysman_freq_handle_t,
    zes_freq_range_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencySetRange 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencySetRange_t)(
    zes_sysman_freq_handle_t,
    const zes_freq_range_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyGetState_t)(
    zes_sysman_freq_handle_t,
    zes_freq_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyGetThrottleTime 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyGetThrottleTime_t)(
    zes_sysman_freq_handle_t,
    zes_freq_throttle_time_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyOcGetCapabilities 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyOcGetCapabilities_t)(
    zes_sysman_freq_handle_t,
    zes_oc_capabilities_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyOcGetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyOcGetConfig_t)(
    zes_sysman_freq_handle_t,
    zes_oc_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyOcSetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyOcSetConfig_t)(
    zes_sysman_freq_handle_t,
    zes_oc_config_t*,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyOcGetIccMax 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyOcGetIccMax_t)(
    zes_sysman_freq_handle_t,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyOcSetIccMax 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyOcSetIccMax_t)(
    zes_sysman_freq_handle_t,
    double
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyOcGetTjMax 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyOcGetTjMax_t)(
    zes_sysman_freq_handle_t,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFrequencyOcSetTjMax 
typedef ze_result_t (__zecall *zes_pfnSysmanFrequencyOcSetTjMax_t)(
    zes_sysman_freq_handle_t,
    double
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFrequency functions pointers
typedef struct _zes_sysman_frequency_dditable_t
{
    zes_pfnSysmanFrequencyGetProperties_t                       pfnGetProperties;
    zes_pfnSysmanFrequencyGetAvailableClocks_t                  pfnGetAvailableClocks;
    zes_pfnSysmanFrequencyGetRange_t                            pfnGetRange;
    zes_pfnSysmanFrequencySetRange_t                            pfnSetRange;
    zes_pfnSysmanFrequencyGetState_t                            pfnGetState;
    zes_pfnSysmanFrequencyGetThrottleTime_t                     pfnGetThrottleTime;
    zes_pfnSysmanFrequencyOcGetCapabilities_t                   pfnOcGetCapabilities;
    zes_pfnSysmanFrequencyOcGetConfig_t                         pfnOcGetConfig;
    zes_pfnSysmanFrequencyOcSetConfig_t                         pfnOcSetConfig;
    zes_pfnSysmanFrequencyOcGetIccMax_t                         pfnOcGetIccMax;
    zes_pfnSysmanFrequencyOcSetIccMax_t                         pfnOcSetIccMax;
    zes_pfnSysmanFrequencyOcGetTjMax_t                          pfnOcGetTjMax;
    zes_pfnSysmanFrequencyOcSetTjMax_t                          pfnOcSetTjMax;
} zes_sysman_frequency_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanFrequencyProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanFrequencyProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_frequency_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEngineGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanEngineGetProperties_t)(
    zes_sysman_engine_handle_t,
    zes_engine_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEngineGetActivity 
typedef ze_result_t (__zecall *zes_pfnSysmanEngineGetActivity_t)(
    zes_sysman_engine_handle_t,
    zes_engine_stats_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanEngine functions pointers
typedef struct _zes_sysman_engine_dditable_t
{
    zes_pfnSysmanEngineGetProperties_t                          pfnGetProperties;
    zes_pfnSysmanEngineGetActivity_t                            pfnGetActivity;
} zes_sysman_engine_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanEngineProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanEngineProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_engine_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanStandbyGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanStandbyGetProperties_t)(
    zes_sysman_standby_handle_t,
    zes_standby_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanStandbyGetMode 
typedef ze_result_t (__zecall *zes_pfnSysmanStandbyGetMode_t)(
    zes_sysman_standby_handle_t,
    zes_standby_promo_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanStandbySetMode 
typedef ze_result_t (__zecall *zes_pfnSysmanStandbySetMode_t)(
    zes_sysman_standby_handle_t,
    zes_standby_promo_mode_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanStandby functions pointers
typedef struct _zes_sysman_standby_dditable_t
{
    zes_pfnSysmanStandbyGetProperties_t                         pfnGetProperties;
    zes_pfnSysmanStandbyGetMode_t                               pfnGetMode;
    zes_pfnSysmanStandbySetMode_t                               pfnSetMode;
} zes_sysman_standby_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanStandbyProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanStandbyProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_standby_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFirmwareGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanFirmwareGetProperties_t)(
    zes_sysman_firmware_handle_t,
    zes_firmware_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFirmwareGetChecksum 
typedef ze_result_t (__zecall *zes_pfnSysmanFirmwareGetChecksum_t)(
    zes_sysman_firmware_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFirmwareFlash 
typedef ze_result_t (__zecall *zes_pfnSysmanFirmwareFlash_t)(
    zes_sysman_firmware_handle_t,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFirmware functions pointers
typedef struct _zes_sysman_firmware_dditable_t
{
    zes_pfnSysmanFirmwareGetProperties_t                        pfnGetProperties;
    zes_pfnSysmanFirmwareGetChecksum_t                          pfnGetChecksum;
    zes_pfnSysmanFirmwareFlash_t                                pfnFlash;
} zes_sysman_firmware_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanFirmwareProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanFirmwareProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_firmware_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanMemoryGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanMemoryGetProperties_t)(
    zes_sysman_mem_handle_t,
    zes_mem_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanMemoryGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanMemoryGetState_t)(
    zes_sysman_mem_handle_t,
    zes_mem_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanMemoryGetBandwidth 
typedef ze_result_t (__zecall *zes_pfnSysmanMemoryGetBandwidth_t)(
    zes_sysman_mem_handle_t,
    zes_mem_bandwidth_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanMemory functions pointers
typedef struct _zes_sysman_memory_dditable_t
{
    zes_pfnSysmanMemoryGetProperties_t                          pfnGetProperties;
    zes_pfnSysmanMemoryGetState_t                               pfnGetState;
    zes_pfnSysmanMemoryGetBandwidth_t                           pfnGetBandwidth;
} zes_sysman_memory_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanMemoryProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanMemoryProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_memory_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFabricPortGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanFabricPortGetProperties_t)(
    zes_sysman_fabric_port_handle_t,
    zes_fabric_port_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFabricPortGetLinkType 
typedef ze_result_t (__zecall *zes_pfnSysmanFabricPortGetLinkType_t)(
    zes_sysman_fabric_port_handle_t,
    ze_bool_t,
    zes_fabric_link_type_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFabricPortGetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanFabricPortGetConfig_t)(
    zes_sysman_fabric_port_handle_t,
    zes_fabric_port_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFabricPortSetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanFabricPortSetConfig_t)(
    zes_sysman_fabric_port_handle_t,
    const zes_fabric_port_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFabricPortGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanFabricPortGetState_t)(
    zes_sysman_fabric_port_handle_t,
    zes_fabric_port_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFabricPortGetThroughput 
typedef ze_result_t (__zecall *zes_pfnSysmanFabricPortGetThroughput_t)(
    zes_sysman_fabric_port_handle_t,
    zes_fabric_port_throughput_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFabricPort functions pointers
typedef struct _zes_sysman_fabric_port_dditable_t
{
    zes_pfnSysmanFabricPortGetProperties_t                      pfnGetProperties;
    zes_pfnSysmanFabricPortGetLinkType_t                        pfnGetLinkType;
    zes_pfnSysmanFabricPortGetConfig_t                          pfnGetConfig;
    zes_pfnSysmanFabricPortSetConfig_t                          pfnSetConfig;
    zes_pfnSysmanFabricPortGetState_t                           pfnGetState;
    zes_pfnSysmanFabricPortGetThroughput_t                      pfnGetThroughput;
} zes_sysman_fabric_port_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_fabric_port_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanFabricPortProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanFabricPortProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_fabric_port_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanTemperatureGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanTemperatureGetProperties_t)(
    zes_sysman_temp_handle_t,
    zes_temp_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanTemperatureGetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanTemperatureGetConfig_t)(
    zes_sysman_temp_handle_t,
    zes_temp_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanTemperatureSetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanTemperatureSetConfig_t)(
    zes_sysman_temp_handle_t,
    const zes_temp_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanTemperatureGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanTemperatureGetState_t)(
    zes_sysman_temp_handle_t,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanTemperature functions pointers
typedef struct _zes_sysman_temperature_dditable_t
{
    zes_pfnSysmanTemperatureGetProperties_t                     pfnGetProperties;
    zes_pfnSysmanTemperatureGetConfig_t                         pfnGetConfig;
    zes_pfnSysmanTemperatureSetConfig_t                         pfnSetConfig;
    zes_pfnSysmanTemperatureGetState_t                          pfnGetState;
} zes_sysman_temperature_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanTemperatureProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanTemperatureProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_temperature_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPsuGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanPsuGetProperties_t)(
    zes_sysman_psu_handle_t,
    zes_psu_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanPsuGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanPsuGetState_t)(
    zes_sysman_psu_handle_t,
    zes_psu_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanPsu functions pointers
typedef struct _zes_sysman_psu_dditable_t
{
    zes_pfnSysmanPsuGetProperties_t                             pfnGetProperties;
    zes_pfnSysmanPsuGetState_t                                  pfnGetState;
} zes_sysman_psu_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanPsuProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanPsuProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_psu_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFanGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanFanGetProperties_t)(
    zes_sysman_fan_handle_t,
    zes_fan_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFanGetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanFanGetConfig_t)(
    zes_sysman_fan_handle_t,
    zes_fan_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFanSetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanFanSetConfig_t)(
    zes_sysman_fan_handle_t,
    const zes_fan_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanFanGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanFanGetState_t)(
    zes_sysman_fan_handle_t,
    zes_fan_speed_units_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFan functions pointers
typedef struct _zes_sysman_fan_dditable_t
{
    zes_pfnSysmanFanGetProperties_t                             pfnGetProperties;
    zes_pfnSysmanFanGetConfig_t                                 pfnGetConfig;
    zes_pfnSysmanFanSetConfig_t                                 pfnSetConfig;
    zes_pfnSysmanFanGetState_t                                  pfnGetState;
} zes_sysman_fan_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanFanProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanFanProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_fan_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanLedGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanLedGetProperties_t)(
    zes_sysman_led_handle_t,
    zes_led_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanLedGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanLedGetState_t)(
    zes_sysman_led_handle_t,
    zes_led_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanLedSetState 
typedef ze_result_t (__zecall *zes_pfnSysmanLedSetState_t)(
    zes_sysman_led_handle_t,
    const zes_led_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanLed functions pointers
typedef struct _zes_sysman_led_dditable_t
{
    zes_pfnSysmanLedGetProperties_t                             pfnGetProperties;
    zes_pfnSysmanLedGetState_t                                  pfnGetState;
    zes_pfnSysmanLedSetState_t                                  pfnSetState;
} zes_sysman_led_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanLedProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanLedProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_led_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanRasGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanRasGetProperties_t)(
    zes_sysman_ras_handle_t,
    zes_ras_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanRasGetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanRasGetConfig_t)(
    zes_sysman_ras_handle_t,
    zes_ras_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanRasSetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanRasSetConfig_t)(
    zes_sysman_ras_handle_t,
    const zes_ras_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanRasGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanRasGetState_t)(
    zes_sysman_ras_handle_t,
    ze_bool_t,
    uint64_t*,
    zes_ras_details_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanRas functions pointers
typedef struct _zes_sysman_ras_dditable_t
{
    zes_pfnSysmanRasGetProperties_t                             pfnGetProperties;
    zes_pfnSysmanRasGetConfig_t                                 pfnGetConfig;
    zes_pfnSysmanRasSetConfig_t                                 pfnSetConfig;
    zes_pfnSysmanRasGetState_t                                  pfnGetState;
} zes_sysman_ras_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanRasProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanRasProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_ras_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanDiagnosticsGetProperties 
typedef ze_result_t (__zecall *zes_pfnSysmanDiagnosticsGetProperties_t)(
    zes_sysman_diag_handle_t,
    zes_diag_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanDiagnosticsGetTests 
typedef ze_result_t (__zecall *zes_pfnSysmanDiagnosticsGetTests_t)(
    zes_sysman_diag_handle_t,
    uint32_t*,
    zes_diag_test_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanDiagnosticsRunTests 
typedef ze_result_t (__zecall *zes_pfnSysmanDiagnosticsRunTests_t)(
    zes_sysman_diag_handle_t,
    uint32_t,
    uint32_t,
    zes_diag_result_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanDiagnostics functions pointers
typedef struct _zes_sysman_diagnostics_dditable_t
{
    zes_pfnSysmanDiagnosticsGetProperties_t                     pfnGetProperties;
    zes_pfnSysmanDiagnosticsGetTests_t                          pfnGetTests;
    zes_pfnSysmanDiagnosticsRunTests_t                          pfnRunTests;
} zes_sysman_diagnostics_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanDiagnosticsProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanDiagnosticsProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_diagnostics_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEventGetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanEventGetConfig_t)(
    zes_sysman_event_handle_t,
    zes_event_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEventSetConfig 
typedef ze_result_t (__zecall *zes_pfnSysmanEventSetConfig_t)(
    zes_sysman_event_handle_t,
    const zes_event_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEventGetState 
typedef ze_result_t (__zecall *zes_pfnSysmanEventGetState_t)(
    zes_sysman_event_handle_t,
    ze_bool_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesSysmanEventListen 
typedef ze_result_t (__zecall *zes_pfnSysmanEventListen_t)(
    ze_driver_handle_t,
    uint32_t,
    uint32_t,
    zes_sysman_event_handle_t*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanEvent functions pointers
typedef struct _zes_sysman_event_dditable_t
{
    zes_pfnSysmanEventGetConfig_t                               pfnGetConfig;
    zes_pfnSysmanEventSetConfig_t                               pfnSetConfig;
    zes_pfnSysmanEventGetState_t                                pfnGetState;
    zes_pfnSysmanEventListen_t                                  pfnListen;
} zes_sysman_event_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEvent table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_event_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zesGetSysmanEventProcAddrTable
typedef ze_result_t (__zecall *zes_pfnGetSysmanEventProcAddrTable_t)(
    ze_api_version_t,
    zes_sysman_event_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _zes_dditable_t
{
    zes_sysman_dditable_t               Sysman;
    zes_sysman_scheduler_dditable_t     SysmanScheduler;
    zes_sysman_performance_factor_dditable_t    SysmanPerformanceFactor;
    zes_sysman_power_dditable_t         SysmanPower;
    zes_sysman_frequency_dditable_t     SysmanFrequency;
    zes_sysman_engine_dditable_t        SysmanEngine;
    zes_sysman_standby_dditable_t       SysmanStandby;
    zes_sysman_firmware_dditable_t      SysmanFirmware;
    zes_sysman_memory_dditable_t        SysmanMemory;
    zes_sysman_fabric_port_dditable_t   SysmanFabricPort;
    zes_sysman_temperature_dditable_t   SysmanTemperature;
    zes_sysman_psu_dditable_t           SysmanPsu;
    zes_sysman_fan_dditable_t           SysmanFan;
    zes_sysman_led_dditable_t           SysmanLed;
    zes_sysman_ras_dditable_t           SysmanRas;
    zes_sysman_diagnostics_dditable_t   SysmanDiagnostics;
    zes_sysman_event_dditable_t         SysmanEvent;
} zes_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZES_DDI_H