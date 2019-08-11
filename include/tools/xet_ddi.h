/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_ddi.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools
 * @endcond
 *
 */
#ifndef _XET_DDI_H
#define _XET_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xet_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetInit 
typedef xe_result_t (__xecall *xet_pfnInit_t)(
    xe_init_flag_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global functions pointers
typedef struct _xet_global_dditable_t
{
    xet_pfnInit_t                                               pfnInit;
} xet_global_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetGlobalProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetGlobalProcAddrTable_t)(
    xe_api_version_t,
    xet_global_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetDeviceActivateMetricGroups 
typedef xe_result_t (__xecall *xet_pfnDeviceActivateMetricGroups_t)(
    xet_device_handle_t,
    uint32_t,
    xet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _xet_device_dditable_t
{
    xet_pfnDeviceActivateMetricGroups_t                         pfnActivateMetricGroups;
} xet_device_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetDeviceProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetDeviceProcAddrTable_t)(
    xe_api_version_t,
    xet_device_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetCommandListAppendMetricTracerMarker 
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricTracerMarker_t)(
    xet_command_list_handle_t,
    xet_metric_tracer_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetCommandListAppendMetricQueryBegin 
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricQueryBegin_t)(
    xet_command_list_handle_t,
    xet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetCommandListAppendMetricQueryEnd 
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricQueryEnd_t)(
    xet_command_list_handle_t,
    xet_metric_query_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetCommandListAppendMetricMemoryBarrier 
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricMemoryBarrier_t)(
    xet_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _xet_command_list_dditable_t
{
    xet_pfnCommandListAppendMetricTracerMarker_t                pfnAppendMetricTracerMarker;
    xet_pfnCommandListAppendMetricQueryBegin_t                  pfnAppendMetricQueryBegin;
    xet_pfnCommandListAppendMetricQueryEnd_t                    pfnAppendMetricQueryEnd;
    xet_pfnCommandListAppendMetricMemoryBarrier_t               pfnAppendMetricMemoryBarrier;
} xet_command_list_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetCommandListProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetCommandListProcAddrTable_t)(
    xe_api_version_t,
    xet_command_list_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetModuleGetDebugInfo 
typedef xe_result_t (__xecall *xet_pfnModuleGetDebugInfo_t)(
    xet_module_handle_t,
    xet_module_debug_info_format_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetModuleGetFunctionNames 
typedef xe_result_t (__xecall *xet_pfnModuleGetFunctionNames_t)(
    xet_module_handle_t,
    uint32_t*,
    const char**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module functions pointers
typedef struct _xet_module_dditable_t
{
    xet_pfnModuleGetDebugInfo_t                                 pfnGetDebugInfo;
    xet_pfnModuleGetFunctionNames_t                             pfnGetFunctionNames;
} xet_module_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetModuleProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetModuleProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetModuleProcAddrTable_t)(
    xe_api_version_t,
    xet_module_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFunctionGetProfileInfo 
typedef xe_result_t (__xecall *xet_pfnFunctionGetProfileInfo_t)(
    xet_function_handle_t,
    xet_profile_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Function functions pointers
typedef struct _xet_function_dditable_t
{
    xet_pfnFunctionGetProfileInfo_t                             pfnGetProfileInfo;
} xet_function_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetFunctionProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_function_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetFunctionProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetFunctionProcAddrTable_t)(
    xe_api_version_t,
    xet_function_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricGroupGet 
typedef xe_result_t (__xecall *xet_pfnMetricGroupGet_t)(
    xet_device_handle_t,
    uint32_t*,
    xet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricGroupGetProperties 
typedef xe_result_t (__xecall *xet_pfnMetricGroupGetProperties_t)(
    xet_metric_group_handle_t,
    xet_metric_group_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricGroupCalculateMetricValues 
typedef xe_result_t (__xecall *xet_pfnMetricGroupCalculateMetricValues_t)(
    xet_metric_group_handle_t,
    size_t,
    uint8_t*,
    uint32_t*,
    xet_typed_value_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricGroup functions pointers
typedef struct _xet_metric_group_dditable_t
{
    xet_pfnMetricGroupGet_t                                     pfnGet;
    xet_pfnMetricGroupGetProperties_t                           pfnGetProperties;
    xet_pfnMetricGroupCalculateMetricValues_t                   pfnCalculateMetricValues;
} xet_metric_group_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricGroupProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricGroupProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_group_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricGet 
typedef xe_result_t (__xecall *xet_pfnMetricGet_t)(
    xet_metric_group_handle_t,
    uint32_t*,
    xet_metric_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricGetProperties 
typedef xe_result_t (__xecall *xet_pfnMetricGetProperties_t)(
    xet_metric_handle_t,
    xet_metric_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Metric functions pointers
typedef struct _xet_metric_dditable_t
{
    xet_pfnMetricGet_t                                          pfnGet;
    xet_pfnMetricGetProperties_t                                pfnGetProperties;
} xet_metric_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricTracerOpen 
typedef xe_result_t (__xecall *xet_pfnMetricTracerOpen_t)(
    xet_device_handle_t,
    xet_metric_group_handle_t,
    xet_metric_tracer_desc_t*,
    xe_event_handle_t,
    xet_metric_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricTracerClose 
typedef xe_result_t (__xecall *xet_pfnMetricTracerClose_t)(
    xet_metric_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricTracerReadData 
typedef xe_result_t (__xecall *xet_pfnMetricTracerReadData_t)(
    xet_metric_tracer_handle_t,
    uint32_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricTracer functions pointers
typedef struct _xet_metric_tracer_dditable_t
{
    xet_pfnMetricTracerOpen_t                                   pfnOpen;
    xet_pfnMetricTracerClose_t                                  pfnClose;
    xet_pfnMetricTracerReadData_t                               pfnReadData;
} xet_metric_tracer_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricTracerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricTracerProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricTracerProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_tracer_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricQueryPoolCreate 
typedef xe_result_t (__xecall *xet_pfnMetricQueryPoolCreate_t)(
    xet_device_handle_t,
    xet_metric_group_handle_t,
    const xet_metric_query_pool_desc_t*,
    xet_metric_query_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricQueryPoolDestroy 
typedef xe_result_t (__xecall *xet_pfnMetricQueryPoolDestroy_t)(
    xet_metric_query_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQueryPool functions pointers
typedef struct _xet_metric_query_pool_dditable_t
{
    xet_pfnMetricQueryPoolCreate_t                              pfnCreate;
    xet_pfnMetricQueryPoolDestroy_t                             pfnDestroy;
} xet_metric_query_pool_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricQueryPoolProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricQueryPoolProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_query_pool_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricQueryCreate 
typedef xe_result_t (__xecall *xet_pfnMetricQueryCreate_t)(
    xet_metric_query_pool_handle_t,
    uint32_t,
    xet_metric_query_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricQueryDestroy 
typedef xe_result_t (__xecall *xet_pfnMetricQueryDestroy_t)(
    xet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricQueryReset 
typedef xe_result_t (__xecall *xet_pfnMetricQueryReset_t)(
    xet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetMetricQueryGetData 
typedef xe_result_t (__xecall *xet_pfnMetricQueryGetData_t)(
    xet_metric_query_handle_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQuery functions pointers
typedef struct _xet_metric_query_dditable_t
{
    xet_pfnMetricQueryCreate_t                                  pfnCreate;
    xet_pfnMetricQueryDestroy_t                                 pfnDestroy;
    xet_pfnMetricQueryReset_t                                   pfnReset;
    xet_pfnMetricQueryGetData_t                                 pfnGetData;
} xet_metric_query_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricQueryProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricQueryProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_query_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetTracerCreate 
typedef xe_result_t (__xecall *xet_pfnTracerCreate_t)(
    xet_device_handle_t,
    const xet_tracer_desc_t*,
    xet_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetTracerDestroy 
typedef xe_result_t (__xecall *xet_pfnTracerDestroy_t)(
    xet_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetTracerSetPrologues 
typedef xe_result_t (__xecall *xet_pfnTracerSetPrologues_t)(
    xet_tracer_handle_t,
    xet_core_callbacks_t*,
    xet_experimental_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetTracerSetEpilogues 
typedef xe_result_t (__xecall *xet_pfnTracerSetEpilogues_t)(
    xet_tracer_handle_t,
    xet_core_callbacks_t*,
    xet_experimental_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetTracerSetEnabled 
typedef xe_result_t (__xecall *xet_pfnTracerSetEnabled_t)(
    xet_tracer_handle_t,
    xe_bool_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Tracer functions pointers
typedef struct _xet_tracer_dditable_t
{
    xet_pfnTracerCreate_t                                       pfnCreate;
    xet_pfnTracerDestroy_t                                      pfnDestroy;
    xet_pfnTracerSetPrologues_t                                 pfnSetPrologues;
    xet_pfnTracerSetEpilogues_t                                 pfnSetEpilogues;
    xet_pfnTracerSetEnabled_t                                   pfnSetEnabled;
} xet_tracer_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetTracerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetTracerProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetTracerProcAddrTable_t)(
    xe_api_version_t,
    xet_tracer_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGet 
typedef xe_result_t (__xecall *xet_pfnSysmanGet_t)(
    xet_device_handle_t,
    xet_sysman_version_t,
    xet_sysman_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetSubdevice 
typedef xe_result_t (__xecall *xet_pfnSysmanGetSubdevice_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_sysman_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDeviceGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanDeviceGetProperties_t)(
    xet_sysman_handle_t,
    xet_sysman_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDeviceGetOperatingMode 
typedef xe_result_t (__xecall *xet_pfnSysmanDeviceGetOperatingMode_t)(
    xet_sysman_handle_t,
    xet_operating_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDeviceSetOperatingMode 
typedef xe_result_t (__xecall *xet_pfnSysmanDeviceSetOperatingMode_t)(
    xet_sysman_handle_t,
    xet_operating_mode_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDeviceReset 
typedef xe_result_t (__xecall *xet_pfnSysmanDeviceReset_t)(
    xet_sysman_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPowerGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanPowerGetProperties_t)(
    xet_sysman_handle_t,
    xet_power_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPowerGetEnergyCounter 
typedef xe_result_t (__xecall *xet_pfnSysmanPowerGetEnergyCounter_t)(
    xet_sysman_handle_t,
    xet_power_energy_counter_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPowerGetLimits 
typedef xe_result_t (__xecall *xet_pfnSysmanPowerGetLimits_t)(
    xet_sysman_handle_t,
    xet_power_sustained_limit_t*,
    xet_power_burst_limit_t*,
    xet_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPowerSetLimits 
typedef xe_result_t (__xecall *xet_pfnSysmanPowerSetLimits_t)(
    xet_sysman_handle_t,
    const xet_power_sustained_limit_t*,
    const xet_power_burst_limit_t*,
    const xet_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFrequencyGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanFrequencyGetProperties_t)(
    xet_sysman_handle_t,
    xet_freq_domain_t,
    xet_freq_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFrequencyGetLimits 
typedef xe_result_t (__xecall *xet_pfnSysmanFrequencyGetLimits_t)(
    xet_sysman_handle_t,
    xet_freq_domain_t,
    xet_freq_limits_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFrequencySetLimits 
typedef xe_result_t (__xecall *xet_pfnSysmanFrequencySetLimits_t)(
    xet_sysman_handle_t,
    xet_freq_domain_t,
    const xet_freq_limits_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFrequencyGetState 
typedef xe_result_t (__xecall *xet_pfnSysmanFrequencyGetState_t)(
    xet_sysman_handle_t,
    xet_freq_domain_t,
    xet_freq_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFrequencyGetThrottleTime 
typedef xe_result_t (__xecall *xet_pfnSysmanFrequencyGetThrottleTime_t)(
    xet_sysman_handle_t,
    xet_freq_domain_t,
    xet_freq_throttle_time_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanActivityGetStats 
typedef xe_result_t (__xecall *xet_pfnSysmanActivityGetStats_t)(
    xet_sysman_handle_t,
    xet_activity_type_t,
    xet_activity_stats_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanMemoryGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanMemoryGetProperties_t)(
    xet_sysman_handle_t,
    xet_mem_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanMemoryGetBandwidth 
typedef xe_result_t (__xecall *xet_pfnSysmanMemoryGetBandwidth_t)(
    xet_sysman_handle_t,
    xet_mem_bandwidth_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanMemoryGetAllocated 
typedef xe_result_t (__xecall *xet_pfnSysmanMemoryGetAllocated_t)(
    xet_sysman_handle_t,
    xet_mem_alloc_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPciGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanPciGetProperties_t)(
    xet_sysman_handle_t,
    xet_pci_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPciGetState 
typedef xe_result_t (__xecall *xet_pfnSysmanPciGetState_t)(
    xet_sysman_handle_t,
    xet_pci_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPciGetBarProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanPciGetBarProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_pci_bar_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPciGetThroughput 
typedef xe_result_t (__xecall *xet_pfnSysmanPciGetThroughput_t)(
    xet_sysman_handle_t,
    xet_pci_throughput_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPciGetStats 
typedef xe_result_t (__xecall *xet_pfnSysmanPciGetStats_t)(
    xet_sysman_handle_t,
    xet_pci_stats_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSwitchGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSwitchGetProperties_t)(
    xet_sysman_handle_t,
    xet_switch_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSwitchGetState 
typedef xe_result_t (__xecall *xet_pfnSysmanSwitchGetState_t)(
    xet_sysman_handle_t,
    xet_switch_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSwitchSetState 
typedef xe_result_t (__xecall *xet_pfnSysmanSwitchSetState_t)(
    xet_sysman_handle_t,
    xe_bool_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSwitchPortGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSwitchPortGetProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_switch_port_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSwitchPortGetState 
typedef xe_result_t (__xecall *xet_pfnSysmanSwitchPortGetState_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_switch_port_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSwitchPortGetThroughput 
typedef xe_result_t (__xecall *xet_pfnSysmanSwitchPortGetThroughput_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_switch_port_throughput_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSwitchPortGetStats 
typedef xe_result_t (__xecall *xet_pfnSysmanSwitchPortGetStats_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_switch_port_stats_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanTemperatureGet 
typedef xe_result_t (__xecall *xet_pfnSysmanTemperatureGet_t)(
    xet_sysman_handle_t,
    xet_temp_sensors_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanStandbyGetMode 
typedef xe_result_t (__xecall *xet_pfnSysmanStandbyGetMode_t)(
    xet_sysman_handle_t,
    xet_stby_promo_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanStandbySetMode 
typedef xe_result_t (__xecall *xet_pfnSysmanStandbySetMode_t)(
    xet_sysman_handle_t,
    xet_stby_promo_mode_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFirmwareGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanFirmwareGetProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_firmware_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFirmwareGetChecksum 
typedef xe_result_t (__xecall *xet_pfnSysmanFirmwareGetChecksum_t)(
    xet_sysman_handle_t,
    uint32_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFirmwareFlash 
typedef xe_result_t (__xecall *xet_pfnSysmanFirmwareFlash_t)(
    xet_sysman_handle_t,
    uint32_t,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPsuGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanPsuGetProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_psu_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanPsuGetState 
typedef xe_result_t (__xecall *xet_pfnSysmanPsuGetState_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_psu_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFanGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanFanGetProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_fan_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFanGetConfig 
typedef xe_result_t (__xecall *xet_pfnSysmanFanGetConfig_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_fan_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFanSetConfig 
typedef xe_result_t (__xecall *xet_pfnSysmanFanSetConfig_t)(
    xet_sysman_handle_t,
    uint32_t,
    const xet_fan_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanFanGetState 
typedef xe_result_t (__xecall *xet_pfnSysmanFanGetState_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_fan_speed_units_t,
    xet_fan_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanLedGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanLedGetProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_led_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanLedGetState 
typedef xe_result_t (__xecall *xet_pfnSysmanLedGetState_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_led_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanLedSetState 
typedef xe_result_t (__xecall *xet_pfnSysmanLedSetState_t)(
    xet_sysman_handle_t,
    uint32_t,
    const xet_led_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanRasGetProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanRasGetProperties_t)(
    xet_sysman_handle_t,
    xet_ras_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanRasGetErrors 
typedef xe_result_t (__xecall *xet_pfnSysmanRasGetErrors_t)(
    xet_sysman_handle_t,
    xet_ras_error_type_t,
    xe_bool_t,
    uint64_t*,
    xet_ras_details_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanEventsRegister 
typedef xe_result_t (__xecall *xet_pfnSysmanEventsRegister_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_event_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanEventsUnregister 
typedef xe_result_t (__xecall *xet_pfnSysmanEventsUnregister_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_event_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanEventsListen 
typedef xe_result_t (__xecall *xet_pfnSysmanEventsListen_t)(
    xet_sysman_handle_t,
    xe_bool_t,
    uint32_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDiagnosticsGetTestList 
typedef xe_result_t (__xecall *xet_pfnSysmanDiagnosticsGetTestList_t)(
    xet_sysman_handle_t,
    xet_diag_type_t,
    const xet_diag_test_list_t**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDiagnosticsRunTests 
typedef xe_result_t (__xecall *xet_pfnSysmanDiagnosticsRunTests_t)(
    xet_sysman_handle_t,
    xet_diag_type_t,
    uint32_t,
    uint32_t,
    xet_diag_result_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sysman functions pointers
typedef struct _xet_sysman_dditable_t
{
    xet_pfnSysmanGet_t                                          pfnGet;
    xet_pfnSysmanGetSubdevice_t                                 pfnGetSubdevice;
    xet_pfnSysmanDeviceGetProperties_t                          pfnDeviceGetProperties;
    xet_pfnSysmanDeviceGetOperatingMode_t                       pfnDeviceGetOperatingMode;
    xet_pfnSysmanDeviceSetOperatingMode_t                       pfnDeviceSetOperatingMode;
    xet_pfnSysmanDeviceReset_t                                  pfnDeviceReset;
    xet_pfnSysmanPowerGetProperties_t                           pfnPowerGetProperties;
    xet_pfnSysmanPowerGetEnergyCounter_t                        pfnPowerGetEnergyCounter;
    xet_pfnSysmanPowerGetLimits_t                               pfnPowerGetLimits;
    xet_pfnSysmanPowerSetLimits_t                               pfnPowerSetLimits;
    xet_pfnSysmanFrequencyGetProperties_t                       pfnFrequencyGetProperties;
    xet_pfnSysmanFrequencyGetLimits_t                           pfnFrequencyGetLimits;
    xet_pfnSysmanFrequencySetLimits_t                           pfnFrequencySetLimits;
    xet_pfnSysmanFrequencyGetState_t                            pfnFrequencyGetState;
    xet_pfnSysmanFrequencyGetThrottleTime_t                     pfnFrequencyGetThrottleTime;
    xet_pfnSysmanActivityGetStats_t                             pfnActivityGetStats;
    xet_pfnSysmanMemoryGetProperties_t                          pfnMemoryGetProperties;
    xet_pfnSysmanMemoryGetBandwidth_t                           pfnMemoryGetBandwidth;
    xet_pfnSysmanMemoryGetAllocated_t                           pfnMemoryGetAllocated;
    xet_pfnSysmanPciGetProperties_t                             pfnPciGetProperties;
    xet_pfnSysmanPciGetState_t                                  pfnPciGetState;
    xet_pfnSysmanPciGetBarProperties_t                          pfnPciGetBarProperties;
    xet_pfnSysmanPciGetThroughput_t                             pfnPciGetThroughput;
    xet_pfnSysmanPciGetStats_t                                  pfnPciGetStats;
    xet_pfnSysmanSwitchGetProperties_t                          pfnSwitchGetProperties;
    xet_pfnSysmanSwitchGetState_t                               pfnSwitchGetState;
    xet_pfnSysmanSwitchSetState_t                               pfnSwitchSetState;
    xet_pfnSysmanSwitchPortGetProperties_t                      pfnSwitchPortGetProperties;
    xet_pfnSysmanSwitchPortGetState_t                           pfnSwitchPortGetState;
    xet_pfnSysmanSwitchPortGetThroughput_t                      pfnSwitchPortGetThroughput;
    xet_pfnSysmanSwitchPortGetStats_t                           pfnSwitchPortGetStats;
    xet_pfnSysmanTemperatureGet_t                               pfnTemperatureGet;
    xet_pfnSysmanStandbyGetMode_t                               pfnStandbyGetMode;
    xet_pfnSysmanStandbySetMode_t                               pfnStandbySetMode;
    xet_pfnSysmanFirmwareGetProperties_t                        pfnFirmwareGetProperties;
    xet_pfnSysmanFirmwareGetChecksum_t                          pfnFirmwareGetChecksum;
    xet_pfnSysmanFirmwareFlash_t                                pfnFirmwareFlash;
    xet_pfnSysmanPsuGetProperties_t                             pfnPsuGetProperties;
    xet_pfnSysmanPsuGetState_t                                  pfnPsuGetState;
    xet_pfnSysmanFanGetProperties_t                             pfnFanGetProperties;
    xet_pfnSysmanFanGetConfig_t                                 pfnFanGetConfig;
    xet_pfnSysmanFanSetConfig_t                                 pfnFanSetConfig;
    xet_pfnSysmanFanGetState_t                                  pfnFanGetState;
    xet_pfnSysmanLedGetProperties_t                             pfnLedGetProperties;
    xet_pfnSysmanLedGetState_t                                  pfnLedGetState;
    xet_pfnSysmanLedSetState_t                                  pfnLedSetState;
    xet_pfnSysmanRasGetProperties_t                             pfnRasGetProperties;
    xet_pfnSysmanRasGetErrors_t                                 pfnRasGetErrors;
    xet_pfnSysmanEventsRegister_t                               pfnEventsRegister;
    xet_pfnSysmanEventsUnregister_t                             pfnEventsUnregister;
    xet_pfnSysmanEventsListen_t                                 pfnEventsListen;
    xet_pfnSysmanDiagnosticsGetTestList_t                       pfnDiagnosticsGetTestList;
    xet_pfnSysmanDiagnosticsRunTests_t                          pfnDiagnosticsRunTests;
} xet_sysman_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetSysmanProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetSysmanProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetSysmanProcAddrTable_t)(
    xe_api_version_t,
    xet_sysman_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _xet_dditable_t
{
    xet_global_dditable_t               Global;
    xet_device_dditable_t               Device;
    xet_command_list_dditable_t         CommandList;
    xet_module_dditable_t               Module;
    xet_function_dditable_t             Function;
    xet_metric_group_dditable_t         MetricGroup;
    xet_metric_dditable_t               Metric;
    xet_metric_tracer_dditable_t        MetricTracer;
    xet_metric_query_pool_dditable_t    MetricQueryPool;
    xet_metric_query_dditable_t         MetricQuery;
    xet_tracer_dditable_t               Tracer;
    xet_sysman_dditable_t               Sysman;
} xet_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_DDI_H