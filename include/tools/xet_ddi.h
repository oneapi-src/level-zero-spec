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
    xet_device_group_handle_t,
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
/// @brief Function-pointer for xetSysmanCreate 
typedef xe_result_t (__xecall *xet_pfnSysmanCreate_t)(
    xet_device_handle_t,
    xet_sysman_version_t,
    uint32_t,
    xet_sysman_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDestroy 
typedef xe_result_t (__xecall *xet_pfnSysmanDestroy_t)(
    xet_sysman_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetAccelAssetName 
typedef xe_result_t (__xecall *xet_pfnSysmanGetAccelAssetName_t)(
    xet_sysman_handle_t,
    xet_accel_asset_t,
    const char**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetInfo 
typedef xe_result_t (__xecall *xet_pfnSysmanGetInfo_t)(
    xet_sysman_handle_t,
    xet_sysman_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetRasErrors 
typedef xe_result_t (__xecall *xet_pfnSysmanGetRasErrors_t)(
    xet_sysman_handle_t,
    xet_ras_filter_t*,
    xe_bool_t,
    uint32_t*,
    xet_res_error_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableDeviceProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableDeviceProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_device_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetDeviceProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetDeviceProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_device_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetDeviceProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetDeviceProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_device_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailablePsuProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailablePsuProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_psu_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetPsuProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetPsuProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_psu_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetPsuProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetPsuProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_psu_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableTempProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableTempProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_temp_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetTempProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetTempProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_temp_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableFanProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableFanProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_fan_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetFanProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetFanProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_fan_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetFanProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetFanProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_fan_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableLedProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableLedProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_led_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetLedProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetLedProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_led_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetLedProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetLedProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_led_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableFirmwareProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableFirmwareProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_firmware_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetFirmwareProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetFirmwareProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_firmware_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetFirmwareProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetFirmwareProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_firmware_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailablePwrProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailablePwrProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_pwr_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetPwrProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetPwrProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_pwr_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetPwrProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetPwrProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_pwr_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableFreqProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableFreqProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_freq_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetFreqProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetFreqProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_freq_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetFreqProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetFreqProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_freq_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailablePwrwellProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailablePwrwellProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_pwrwell_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetPwrwellProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetPwrwellProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_pwrwell_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetPwrwellProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetPwrwellProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_pwrwell_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableAccelProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableAccelProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_accel_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetAccelProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetAccelProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_accel_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableMemProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableMemProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_mem_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetMemProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetMemProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_mem_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetMemProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetMemProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_mem_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanAvailableLinkProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanAvailableLinkProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_link_prop_capability_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetLinkProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanGetLinkProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_link_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSetLinkProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanSetLinkProperties_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_link_property_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanSupportedEvents 
typedef xe_result_t (__xecall *xet_pfnSysmanSupportedEvents_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_event_support_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanRegisterEvents 
typedef xe_result_t (__xecall *xet_pfnSysmanRegisterEvents_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_event_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanUnregisterEvents 
typedef xe_result_t (__xecall *xet_pfnSysmanUnregisterEvents_t)(
    xet_sysman_handle_t,
    uint32_t,
    xet_event_request_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetEvents 
typedef xe_result_t (__xecall *xet_pfnSysmanGetEvents_t)(
    xet_sysman_handle_t,
    xe_bool_t,
    uint32_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sysman functions pointers
typedef struct _xet_sysman_dditable_t
{
    xet_pfnSysmanCreate_t                                       pfnCreate;
    xet_pfnSysmanDestroy_t                                      pfnDestroy;
    xet_pfnSysmanGetAccelAssetName_t                            pfnGetAccelAssetName;
    xet_pfnSysmanGetInfo_t                                      pfnGetInfo;
    xet_pfnSysmanGetRasErrors_t                                 pfnGetRasErrors;
    xet_pfnSysmanAvailableDeviceProperties_t                    pfnAvailableDeviceProperties;
    xet_pfnSysmanGetDeviceProperties_t                          pfnGetDeviceProperties;
    xet_pfnSysmanSetDeviceProperties_t                          pfnSetDeviceProperties;
    xet_pfnSysmanAvailablePsuProperties_t                       pfnAvailablePsuProperties;
    xet_pfnSysmanGetPsuProperties_t                             pfnGetPsuProperties;
    xet_pfnSysmanSetPsuProperties_t                             pfnSetPsuProperties;
    xet_pfnSysmanAvailableTempProperties_t                      pfnAvailableTempProperties;
    xet_pfnSysmanGetTempProperties_t                            pfnGetTempProperties;
    xet_pfnSysmanAvailableFanProperties_t                       pfnAvailableFanProperties;
    xet_pfnSysmanGetFanProperties_t                             pfnGetFanProperties;
    xet_pfnSysmanSetFanProperties_t                             pfnSetFanProperties;
    xet_pfnSysmanAvailableLedProperties_t                       pfnAvailableLedProperties;
    xet_pfnSysmanGetLedProperties_t                             pfnGetLedProperties;
    xet_pfnSysmanSetLedProperties_t                             pfnSetLedProperties;
    xet_pfnSysmanAvailableFirmwareProperties_t                  pfnAvailableFirmwareProperties;
    xet_pfnSysmanGetFirmwareProperties_t                        pfnGetFirmwareProperties;
    xet_pfnSysmanSetFirmwareProperties_t                        pfnSetFirmwareProperties;
    xet_pfnSysmanAvailablePwrProperties_t                       pfnAvailablePwrProperties;
    xet_pfnSysmanGetPwrProperties_t                             pfnGetPwrProperties;
    xet_pfnSysmanSetPwrProperties_t                             pfnSetPwrProperties;
    xet_pfnSysmanAvailableFreqProperties_t                      pfnAvailableFreqProperties;
    xet_pfnSysmanGetFreqProperties_t                            pfnGetFreqProperties;
    xet_pfnSysmanSetFreqProperties_t                            pfnSetFreqProperties;
    xet_pfnSysmanAvailablePwrwellProperties_t                   pfnAvailablePwrwellProperties;
    xet_pfnSysmanGetPwrwellProperties_t                         pfnGetPwrwellProperties;
    xet_pfnSysmanSetPwrwellProperties_t                         pfnSetPwrwellProperties;
    xet_pfnSysmanAvailableAccelProperties_t                     pfnAvailableAccelProperties;
    xet_pfnSysmanGetAccelProperties_t                           pfnGetAccelProperties;
    xet_pfnSysmanAvailableMemProperties_t                       pfnAvailableMemProperties;
    xet_pfnSysmanGetMemProperties_t                             pfnGetMemProperties;
    xet_pfnSysmanSetMemProperties_t                             pfnSetMemProperties;
    xet_pfnSysmanAvailableLinkProperties_t                      pfnAvailableLinkProperties;
    xet_pfnSysmanGetLinkProperties_t                            pfnGetLinkProperties;
    xet_pfnSysmanSetLinkProperties_t                            pfnSetLinkProperties;
    xet_pfnSysmanSupportedEvents_t                              pfnSupportedEvents;
    xet_pfnSysmanRegisterEvents_t                               pfnRegisterEvents;
    xet_pfnSysmanUnregisterEvents_t                             pfnUnregisterEvents;
    xet_pfnSysmanGetEvents_t                                    pfnGetEvents;
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