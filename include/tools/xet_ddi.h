/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
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
*
* @file xet_ddi.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools
* @endcond
*
******************************************************************************/
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
/// @brief Function-pointer for xetDeviceSetTracingPrologue 
typedef xe_result_t (__xecall *xet_pfnDeviceSetTracingPrologue_t)(
    xet_device_handle_t,
    xet_core_callbacks_t*,
    xet_extended_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetDeviceSetTracingEpilogue 
typedef xe_result_t (__xecall *xet_pfnDeviceSetTracingEpilogue_t)(
    xet_device_handle_t,
    xet_core_callbacks_t*,
    xet_extended_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _xet_device_dditable_t
{
    xet_pfnDeviceActivateMetricGroups_t                         pfnActivateMetricGroups;
    xet_pfnDeviceSetTracingPrologue_t                           pfnSetTracingPrologue;
    xet_pfnDeviceSetTracingEpilogue_t                           pfnSetTracingEpilogue;
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
/// @brief Function-pointer for xetModuleReserveSpace 
typedef xe_result_t (__xecall *xet_pfnModuleReserveSpace_t)(
    xet_module_handle_t,
    size_t,
    void**,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module functions pointers
typedef struct _xet_module_dditable_t
{
    xet_pfnModuleGetDebugInfo_t                                 pfnGetDebugInfo;
    xet_pfnModuleReserveSpace_t                                 pfnReserveSpace;
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
/// @brief Function-pointer for xetMetricGroupGet 
typedef xe_result_t (__xecall *xet_pfnMetricGroupGet_t)(
    xet_device_group_handle_t,
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
/// @brief Function-pointer for xetMetricGroupCalculateData 
typedef xe_result_t (__xecall *xet_pfnMetricGroupCalculateData_t)(
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
    xet_pfnMetricGroupCalculateData_t                           pfnCalculateData;
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
/// @brief Function-pointer for xetPowerCreate 
typedef xe_result_t (__xecall *xet_pfnPowerCreate_t)(
    xet_device_handle_t,
    uint32_t,
    xet_power_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerDestroy 
typedef xe_result_t (__xecall *xet_pfnPowerDestroy_t)(
    xet_power_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetAveragePowerLimit 
typedef xe_result_t (__xecall *xet_pfnPowerGetAveragePowerLimit_t)(
    xet_power_handle_t,
    xet_power_average_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetBurstPowerLimit 
typedef xe_result_t (__xecall *xet_pfnPowerGetBurstPowerLimit_t)(
    xet_power_handle_t,
    xet_power_burst_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetPeakPowerLimit 
typedef xe_result_t (__xecall *xet_pfnPowerGetPeakPowerLimit_t)(
    xet_power_handle_t,
    xet_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetAllPowerLimits 
typedef xe_result_t (__xecall *xet_pfnPowerGetAllPowerLimits_t)(
    xet_power_handle_t,
    xet_power_limits_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetDefaultPowerLimits 
typedef xe_result_t (__xecall *xet_pfnPowerGetDefaultPowerLimits_t)(
    xet_power_handle_t,
    xet_power_limits_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerSetAveragePowerLimit 
typedef xe_result_t (__xecall *xet_pfnPowerSetAveragePowerLimit_t)(
    xet_power_handle_t,
    xet_power_average_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerSetBurstPowerLimit 
typedef xe_result_t (__xecall *xet_pfnPowerSetBurstPowerLimit_t)(
    xet_power_handle_t,
    xet_power_burst_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerSetPeakPowerLimit 
typedef xe_result_t (__xecall *xet_pfnPowerSetPeakPowerLimit_t)(
    xet_power_handle_t,
    xet_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerSetPowerLimits 
typedef xe_result_t (__xecall *xet_pfnPowerSetPowerLimits_t)(
    xet_power_handle_t,
    xet_power_limits_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetEnergyCounter 
typedef xe_result_t (__xecall *xet_pfnPowerGetEnergyCounter_t)(
    xet_power_handle_t,
    uint64_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetTurboMode 
typedef xe_result_t (__xecall *xet_pfnPowerGetTurboMode_t)(
    xet_power_handle_t,
    xet_turbo_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerSetTurboMode 
typedef xe_result_t (__xecall *xet_pfnPowerSetTurboMode_t)(
    xet_power_handle_t,
    xet_turbo_mode_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerFanCount 
typedef xe_result_t (__xecall *xet_pfnPowerFanCount_t)(
    xet_power_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerFanGetProperties 
typedef xe_result_t (__xecall *xet_pfnPowerFanGetProperties_t)(
    xet_power_handle_t,
    uint32_t,
    xet_fan_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerFanGetSpeedTable 
typedef xe_result_t (__xecall *xet_pfnPowerFanGetSpeedTable_t)(
    xet_power_handle_t,
    uint32_t,
    xe_bool_t,
    uint32_t*,
    xet_fan_point_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerFanSetSpeedTable 
typedef xe_result_t (__xecall *xet_pfnPowerFanSetSpeedTable_t)(
    xet_power_handle_t,
    uint32_t,
    uint32_t,
    xet_fan_point_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerFanGetSpeed 
typedef xe_result_t (__xecall *xet_pfnPowerFanGetSpeed_t)(
    xet_power_handle_t,
    uint32_t,
    uint32_t,
    xe_bool_t,
    xet_fan_speed_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerFanSetSpeed 
typedef xe_result_t (__xecall *xet_pfnPowerFanSetSpeed_t)(
    xet_power_handle_t,
    uint32_t,
    uint32_t,
    xet_fan_speed_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerTemperatureSensorCount 
typedef xe_result_t (__xecall *xet_pfnPowerTemperatureSensorCount_t)(
    xet_power_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetTemperatureProperties 
typedef xe_result_t (__xecall *xet_pfnPowerGetTemperatureProperties_t)(
    xet_power_handle_t,
    uint32_t,
    xet_temperature_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetTemperature 
typedef xe_result_t (__xecall *xet_pfnPowerGetTemperature_t)(
    xet_power_handle_t,
    uint32_t,
    uint32_t,
    uint16_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerSetTemperatureThreshold 
typedef xe_result_t (__xecall *xet_pfnPowerSetTemperatureThreshold_t)(
    xet_power_handle_t,
    uint32_t,
    uint16_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerActivityCount 
typedef xe_result_t (__xecall *xet_pfnPowerActivityCount_t)(
    xet_power_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetActivityProperties 
typedef xe_result_t (__xecall *xet_pfnPowerGetActivityProperties_t)(
    xet_power_handle_t,
    uint32_t,
    xet_activity_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetPowerGetActivityCounters 
typedef xe_result_t (__xecall *xet_pfnPowerGetActivityCounters_t)(
    xet_power_handle_t,
    uint32_t,
    uint32_t,
    xet_activity_counters_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Power functions pointers
typedef struct _xet_power_dditable_t
{
    xet_pfnPowerCreate_t                                        pfnCreate;
    xet_pfnPowerDestroy_t                                       pfnDestroy;
    xet_pfnPowerGetAveragePowerLimit_t                          pfnGetAveragePowerLimit;
    xet_pfnPowerGetBurstPowerLimit_t                            pfnGetBurstPowerLimit;
    xet_pfnPowerGetPeakPowerLimit_t                             pfnGetPeakPowerLimit;
    xet_pfnPowerGetAllPowerLimits_t                             pfnGetAllPowerLimits;
    xet_pfnPowerGetDefaultPowerLimits_t                         pfnGetDefaultPowerLimits;
    xet_pfnPowerSetAveragePowerLimit_t                          pfnSetAveragePowerLimit;
    xet_pfnPowerSetBurstPowerLimit_t                            pfnSetBurstPowerLimit;
    xet_pfnPowerSetPeakPowerLimit_t                             pfnSetPeakPowerLimit;
    xet_pfnPowerSetPowerLimits_t                                pfnSetPowerLimits;
    xet_pfnPowerGetEnergyCounter_t                              pfnGetEnergyCounter;
    xet_pfnPowerGetTurboMode_t                                  pfnGetTurboMode;
    xet_pfnPowerSetTurboMode_t                                  pfnSetTurboMode;
    xet_pfnPowerFanCount_t                                      pfnFanCount;
    xet_pfnPowerFanGetProperties_t                              pfnFanGetProperties;
    xet_pfnPowerFanGetSpeedTable_t                              pfnFanGetSpeedTable;
    xet_pfnPowerFanSetSpeedTable_t                              pfnFanSetSpeedTable;
    xet_pfnPowerFanGetSpeed_t                                   pfnFanGetSpeed;
    xet_pfnPowerFanSetSpeed_t                                   pfnFanSetSpeed;
    xet_pfnPowerTemperatureSensorCount_t                        pfnTemperatureSensorCount;
    xet_pfnPowerGetTemperatureProperties_t                      pfnGetTemperatureProperties;
    xet_pfnPowerGetTemperature_t                                pfnGetTemperature;
    xet_pfnPowerSetTemperatureThreshold_t                       pfnSetTemperatureThreshold;
    xet_pfnPowerActivityCount_t                                 pfnActivityCount;
    xet_pfnPowerGetActivityProperties_t                         pfnGetActivityProperties;
    xet_pfnPowerGetActivityCounters_t                           pfnGetActivityCounters;
} xet_power_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
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
xetGetPowerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_power_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetPowerProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetPowerProcAddrTable_t)(
    xe_api_version_t,
    xet_power_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainGet 
typedef xe_result_t (__xecall *xet_pfnFreqDomainGet_t)(
    xet_power_handle_t,
    uint32_t*,
    xet_freq_domain_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainGetProperties 
typedef xe_result_t (__xecall *xet_pfnFreqDomainGetProperties_t)(
    xet_freq_domain_handle_t,
    xet_freq_domain_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainGetSourceFreqDomain 
typedef xe_result_t (__xecall *xet_pfnFreqDomainGetSourceFreqDomain_t)(
    xet_freq_domain_handle_t,
    xet_freq_domain_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainGetSupportedClocks 
typedef xe_result_t (__xecall *xet_pfnFreqDomainGetSupportedClocks_t)(
    xet_freq_domain_handle_t,
    uint32_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainGetSupportedClockDividers 
typedef xe_result_t (__xecall *xet_pfnFreqDomainGetSupportedClockDividers_t)(
    xet_freq_domain_handle_t,
    uint32_t,
    xet_clock_divider_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainGetClockRange 
typedef xe_result_t (__xecall *xet_pfnFreqDomainGetClockRange_t)(
    xet_freq_domain_handle_t,
    uint32_t*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainSetClockRange 
typedef xe_result_t (__xecall *xet_pfnFreqDomainSetClockRange_t)(
    xet_freq_domain_handle_t,
    uint32_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainSetClockDivider 
typedef xe_result_t (__xecall *xet_pfnFreqDomainSetClockDivider_t)(
    xet_freq_domain_handle_t,
    xet_clock_divider_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetFreqDomainGetCurrentFrequency 
typedef xe_result_t (__xecall *xet_pfnFreqDomainGetCurrentFrequency_t)(
    xet_freq_domain_handle_t,
    uint32_t*,
    uint32_t*,
    xet_freq_throttle_reasons_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of FreqDomain functions pointers
typedef struct _xet_freq_domain_dditable_t
{
    xet_pfnFreqDomainGet_t                                      pfnGet;
    xet_pfnFreqDomainGetProperties_t                            pfnGetProperties;
    xet_pfnFreqDomainGetSourceFreqDomain_t                      pfnGetSourceFreqDomain;
    xet_pfnFreqDomainGetSupportedClocks_t                       pfnGetSupportedClocks;
    xet_pfnFreqDomainGetSupportedClockDividers_t                pfnGetSupportedClockDividers;
    xet_pfnFreqDomainGetClockRange_t                            pfnGetClockRange;
    xet_pfnFreqDomainSetClockRange_t                            pfnSetClockRange;
    xet_pfnFreqDomainSetClockDivider_t                          pfnSetClockDivider;
    xet_pfnFreqDomainGetCurrentFrequency_t                      pfnGetCurrentFrequency;
} xet_freq_domain_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FreqDomain table
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
xetGetFreqDomainProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_freq_domain_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetFreqDomainProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetFreqDomainProcAddrTable_t)(
    xe_api_version_t,
    xet_freq_domain_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _xet_dditable_t
{
    xet_global_dditable_t               Global;
    xet_device_dditable_t               Device;
    xet_command_list_dditable_t         CommandList;
    xet_module_dditable_t               Module;
    xet_metric_group_dditable_t         MetricGroup;
    xet_metric_dditable_t               Metric;
    xet_metric_tracer_dditable_t        MetricTracer;
    xet_metric_query_pool_dditable_t    MetricQueryPool;
    xet_metric_query_dditable_t         MetricQuery;
    xet_power_dditable_t                Power;
    xet_freq_domain_dditable_t          FreqDomain;
} xet_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_DDI_H