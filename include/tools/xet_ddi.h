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
    xet_device_group_handle_t,
    uint32_t,
    xet_sysman_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanDestroy 
typedef xe_result_t (__xecall *xet_pfnSysmanDestroy_t)(
    xet_sysman_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetResourceContainers 
typedef xe_result_t (__xecall *xet_pfnSysmanGetResourceContainers_t)(
    xet_sysman_handle_t,
    xet_res_container_type_t,
    uint32_t*,
    xet_res_container_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetDeviceResourceContainer 
typedef xe_result_t (__xecall *xet_pfnSysmanGetDeviceResourceContainer_t)(
    xet_sysman_handle_t,
    xe_device_handle_t,
    xet_res_container_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanGetResourceContainerByUuid 
typedef xe_result_t (__xecall *xet_pfnSysmanGetResourceContainerByUuid_t)(
    xet_sysman_handle_t,
    xet_res_container_uuid_t*,
    xet_res_container_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanRegisterEvents 
typedef xe_result_t (__xecall *xet_pfnSysmanRegisterEvents_t)(
    xet_sysman_handle_t,
    xet_res_container_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanUnregisterEvents 
typedef xe_result_t (__xecall *xet_pfnSysmanUnregisterEvents_t)(
    xet_sysman_handle_t,
    xet_res_container_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanListenEvents 
typedef xe_result_t (__xecall *xet_pfnSysmanListenEvents_t)(
    xet_sysman_handle_t,
    xe_bool_t,
    uint32_t*,
    xet_sysman_event_data_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sysman functions pointers
typedef struct _xet_sysman_dditable_t
{
    xet_pfnSysmanCreate_t                                       pfnCreate;
    xet_pfnSysmanDestroy_t                                      pfnDestroy;
    xet_pfnSysmanGetResourceContainers_t                        pfnGetResourceContainers;
    xet_pfnSysmanGetDeviceResourceContainer_t                   pfnGetDeviceResourceContainer;
    xet_pfnSysmanGetResourceContainerByUuid_t                   pfnGetResourceContainerByUuid;
    xet_pfnSysmanRegisterEvents_t                               pfnRegisterEvents;
    xet_pfnSysmanUnregisterEvents_t                             pfnUnregisterEvents;
    xet_pfnSysmanListenEvents_t                                 pfnListenEvents;
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
/// @brief Function-pointer for xetSysmanResContainerGetInfo 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetInfo_t)(
    xet_res_container_handle_t,
    xet_res_container_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerGetParent 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetParent_t)(
    xet_res_container_handle_t,
    xet_res_container_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerGetChildren 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetChildren_t)(
    xet_res_container_handle_t,
    uint32_t*,
    xet_res_container_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerGetPeers 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetPeers_t)(
    xet_res_container_handle_t,
    uint32_t*,
    xet_res_container_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerGetAccelAssetName 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetAccelAssetName_t)(
    xet_res_container_handle_t,
    xet_accel_asset_t,
    const char**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerGetResources 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetResources_t)(
    xet_res_container_handle_t,
    xet_resource_type_t,
    uint32_t*,
    xet_resource_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerGetBoardProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetBoardProperties_t)(
    xet_res_container_handle_t,
    uint32_t,
    const xet_board_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerGetDeviceProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerGetDeviceProperties_t)(
    xet_res_container_handle_t,
    uint32_t,
    const xet_device_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResContainerSetDeviceProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResContainerSetDeviceProperties_t)(
    xet_res_container_handle_t,
    uint32_t,
    const xet_device_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanResContainer functions pointers
typedef struct _xet_sysman_res_container_dditable_t
{
    xet_pfnSysmanResContainerGetInfo_t                          pfnGetInfo;
    xet_pfnSysmanResContainerGetParent_t                        pfnGetParent;
    xet_pfnSysmanResContainerGetChildren_t                      pfnGetChildren;
    xet_pfnSysmanResContainerGetPeers_t                         pfnGetPeers;
    xet_pfnSysmanResContainerGetAccelAssetName_t                pfnGetAccelAssetName;
    xet_pfnSysmanResContainerGetResources_t                     pfnGetResources;
    xet_pfnSysmanResContainerGetBoardProperties_t               pfnGetBoardProperties;
    xet_pfnSysmanResContainerGetDeviceProperties_t              pfnGetDeviceProperties;
    xet_pfnSysmanResContainerSetDeviceProperties_t              pfnSetDeviceProperties;
} xet_sysman_res_container_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanResContainer table
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
xetGetSysmanResContainerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_res_container_dditable_t* pDdiTable  ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetSysmanResContainerProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetSysmanResContainerProcAddrTable_t)(
    xe_api_version_t,
    xet_sysman_res_container_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetInfo 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetInfo_t)(
    xet_resource_handle_t,
    xet_resource_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetPsuProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetPsuProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_psu_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetPsuProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetPsuProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_psu_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetTempProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetTempProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_temp_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetTempProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetTempProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_temp_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetFanProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetFanProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_fan_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetFanProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetFanProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_fan_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetLedProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetLedProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_led_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetLedProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetLedProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_led_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetFirmwareProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetFirmwareProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_firmware_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetFirmwareProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetFirmwareProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_firmware_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetPwrProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetPwrProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_pwr_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetPwrProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetPwrProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_pwr_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetFreqProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetFreqProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_freq_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetFreqProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetFreqProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_freq_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetPwrWellProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetPwrWellProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_pwrwell_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetPwrWellProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetPwrWellProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_pwrwell_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetAccelProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetAccelProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_accel_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetAccelProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetAccelProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_accel_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetMemProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetMemProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_mem_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetMemProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetMemProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_mem_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceGetLinkProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceGetLinkProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_link_properties_t*,
    void*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetSysmanResourceSetLinkProperties 
typedef xe_result_t (__xecall *xet_pfnSysmanResourceSetLinkProperties_t)(
    xet_resource_handle_t,
    uint32_t,
    const xet_link_properties_t*,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanResource functions pointers
typedef struct _xet_sysman_resource_dditable_t
{
    xet_pfnSysmanResourceGetInfo_t                              pfnGetInfo;
    xet_pfnSysmanResourceGetPsuProperties_t                     pfnGetPsuProperties;
    xet_pfnSysmanResourceSetPsuProperties_t                     pfnSetPsuProperties;
    xet_pfnSysmanResourceGetTempProperties_t                    pfnGetTempProperties;
    xet_pfnSysmanResourceSetTempProperties_t                    pfnSetTempProperties;
    xet_pfnSysmanResourceGetFanProperties_t                     pfnGetFanProperties;
    xet_pfnSysmanResourceSetFanProperties_t                     pfnSetFanProperties;
    xet_pfnSysmanResourceGetLedProperties_t                     pfnGetLedProperties;
    xet_pfnSysmanResourceSetLedProperties_t                     pfnSetLedProperties;
    xet_pfnSysmanResourceGetFirmwareProperties_t                pfnGetFirmwareProperties;
    xet_pfnSysmanResourceSetFirmwareProperties_t                pfnSetFirmwareProperties;
    xet_pfnSysmanResourceGetPwrProperties_t                     pfnGetPwrProperties;
    xet_pfnSysmanResourceSetPwrProperties_t                     pfnSetPwrProperties;
    xet_pfnSysmanResourceGetFreqProperties_t                    pfnGetFreqProperties;
    xet_pfnSysmanResourceSetFreqProperties_t                    pfnSetFreqProperties;
    xet_pfnSysmanResourceGetPwrWellProperties_t                 pfnGetPwrWellProperties;
    xet_pfnSysmanResourceSetPwrWellProperties_t                 pfnSetPwrWellProperties;
    xet_pfnSysmanResourceGetAccelProperties_t                   pfnGetAccelProperties;
    xet_pfnSysmanResourceSetAccelProperties_t                   pfnSetAccelProperties;
    xet_pfnSysmanResourceGetMemProperties_t                     pfnGetMemProperties;
    xet_pfnSysmanResourceSetMemProperties_t                     pfnSetMemProperties;
    xet_pfnSysmanResourceGetLinkProperties_t                    pfnGetLinkProperties;
    xet_pfnSysmanResourceSetLinkProperties_t                    pfnSetLinkProperties;
} xet_sysman_resource_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanResource table
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
xetGetSysmanResourceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_resource_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetSysmanResourceProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetSysmanResourceProcAddrTable_t)(
    xe_api_version_t,
    xet_sysman_resource_dditable_t*
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
    xet_sysman_res_container_dditable_t SysmanResContainer;
    xet_sysman_resource_dditable_t      SysmanResource;
} xet_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_DDI_H