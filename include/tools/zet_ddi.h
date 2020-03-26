/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_ddi.h
 *
 */
#ifndef _ZET_DDI_H
#define _ZET_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "zet_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDeviceActivateMetricGroups 
typedef ze_result_t (__zecall *zet_pfnDeviceActivateMetricGroups_t)(
    zet_device_handle_t,
    uint32_t,
    zet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _zet_device_dditable_t
{
    zet_pfnDeviceActivateMetricGroups_t                         pfnActivateMetricGroups;
} zet_device_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetDeviceProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetDeviceProcAddrTable_t)(
    ze_api_version_t,
    zet_device_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricTracerMarker 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricTracerMarker_t)(
    zet_command_list_handle_t,
    zet_metric_tracer_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricQueryBegin 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricQueryBegin_t)(
    zet_command_list_handle_t,
    zet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricQueryEnd 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricQueryEnd_t)(
    zet_command_list_handle_t,
    zet_metric_query_handle_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricMemoryBarrier 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricMemoryBarrier_t)(
    zet_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _zet_command_list_dditable_t
{
    zet_pfnCommandListAppendMetricTracerMarker_t                pfnAppendMetricTracerMarker;
    zet_pfnCommandListAppendMetricQueryBegin_t                  pfnAppendMetricQueryBegin;
    zet_pfnCommandListAppendMetricQueryEnd_t                    pfnAppendMetricQueryEnd;
    zet_pfnCommandListAppendMetricMemoryBarrier_t               pfnAppendMetricMemoryBarrier;
} zet_command_list_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetCommandListProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetCommandListProcAddrTable_t)(
    ze_api_version_t,
    zet_command_list_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetModuleGetDebugInfo 
typedef ze_result_t (__zecall *zet_pfnModuleGetDebugInfo_t)(
    zet_module_handle_t,
    zet_module_debug_info_format_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module functions pointers
typedef struct _zet_module_dditable_t
{
    zet_pfnModuleGetDebugInfo_t                                 pfnGetDebugInfo;
} zet_module_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetModuleProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetModuleProcAddrTable_t)(
    ze_api_version_t,
    zet_module_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetKernelGetProfileInfo 
typedef ze_result_t (__zecall *zet_pfnKernelGetProfileInfo_t)(
    zet_kernel_handle_t,
    zet_profile_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Kernel functions pointers
typedef struct _zet_kernel_dditable_t
{
    zet_pfnKernelGetProfileInfo_t                               pfnGetProfileInfo;
} zet_kernel_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetKernelProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetKernelProcAddrTable_t)(
    ze_api_version_t,
    zet_kernel_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGroupGet 
typedef ze_result_t (__zecall *zet_pfnMetricGroupGet_t)(
    zet_device_handle_t,
    uint32_t*,
    zet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGroupGetProperties 
typedef ze_result_t (__zecall *zet_pfnMetricGroupGetProperties_t)(
    zet_metric_group_handle_t,
    zet_metric_group_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGroupCalculateMetricValues 
typedef ze_result_t (__zecall *zet_pfnMetricGroupCalculateMetricValues_t)(
    zet_metric_group_handle_t,
    size_t,
    const uint8_t*,
    uint32_t*,
    zet_typed_value_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricGroup functions pointers
typedef struct _zet_metric_group_dditable_t
{
    zet_pfnMetricGroupGet_t                                     pfnGet;
    zet_pfnMetricGroupGetProperties_t                           pfnGetProperties;
    zet_pfnMetricGroupCalculateMetricValues_t                   pfnCalculateMetricValues;
} zet_metric_group_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricGroupProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricGroupProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_group_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGet 
typedef ze_result_t (__zecall *zet_pfnMetricGet_t)(
    zet_metric_group_handle_t,
    uint32_t*,
    zet_metric_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGetProperties 
typedef ze_result_t (__zecall *zet_pfnMetricGetProperties_t)(
    zet_metric_handle_t,
    zet_metric_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Metric functions pointers
typedef struct _zet_metric_dditable_t
{
    zet_pfnMetricGet_t                                          pfnGet;
    zet_pfnMetricGetProperties_t                                pfnGetProperties;
} zet_metric_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricTracerOpen 
typedef ze_result_t (__zecall *zet_pfnMetricTracerOpen_t)(
    zet_device_handle_t,
    zet_metric_group_handle_t,
    zet_metric_tracer_desc_t*,
    ze_event_handle_t,
    zet_metric_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricTracerClose 
typedef ze_result_t (__zecall *zet_pfnMetricTracerClose_t)(
    zet_metric_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricTracerReadData 
typedef ze_result_t (__zecall *zet_pfnMetricTracerReadData_t)(
    zet_metric_tracer_handle_t,
    uint32_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricTracer functions pointers
typedef struct _zet_metric_tracer_dditable_t
{
    zet_pfnMetricTracerOpen_t                                   pfnOpen;
    zet_pfnMetricTracerClose_t                                  pfnClose;
    zet_pfnMetricTracerReadData_t                               pfnReadData;
} zet_metric_tracer_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricTracerProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricTracerProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_tracer_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryPoolCreate 
typedef ze_result_t (__zecall *zet_pfnMetricQueryPoolCreate_t)(
    zet_device_handle_t,
    zet_metric_group_handle_t,
    const zet_metric_query_pool_desc_t*,
    zet_metric_query_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryPoolDestroy 
typedef ze_result_t (__zecall *zet_pfnMetricQueryPoolDestroy_t)(
    zet_metric_query_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQueryPool functions pointers
typedef struct _zet_metric_query_pool_dditable_t
{
    zet_pfnMetricQueryPoolCreate_t                              pfnCreate;
    zet_pfnMetricQueryPoolDestroy_t                             pfnDestroy;
} zet_metric_query_pool_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricQueryPoolProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricQueryPoolProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_query_pool_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryCreate 
typedef ze_result_t (__zecall *zet_pfnMetricQueryCreate_t)(
    zet_metric_query_pool_handle_t,
    uint32_t,
    zet_metric_query_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryDestroy 
typedef ze_result_t (__zecall *zet_pfnMetricQueryDestroy_t)(
    zet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryReset 
typedef ze_result_t (__zecall *zet_pfnMetricQueryReset_t)(
    zet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryGetData 
typedef ze_result_t (__zecall *zet_pfnMetricQueryGetData_t)(
    zet_metric_query_handle_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQuery functions pointers
typedef struct _zet_metric_query_dditable_t
{
    zet_pfnMetricQueryCreate_t                                  pfnCreate;
    zet_pfnMetricQueryDestroy_t                                 pfnDestroy;
    zet_pfnMetricQueryReset_t                                   pfnReset;
    zet_pfnMetricQueryGetData_t                                 pfnGetData;
} zet_metric_query_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricQueryProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricQueryProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_query_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerCreate 
typedef ze_result_t (__zecall *zet_pfnTracerCreate_t)(
    zet_driver_handle_t,
    const zet_tracer_desc_t*,
    zet_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerDestroy 
typedef ze_result_t (__zecall *zet_pfnTracerDestroy_t)(
    zet_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerSetPrologues 
typedef ze_result_t (__zecall *zet_pfnTracerSetPrologues_t)(
    zet_tracer_handle_t,
    zet_core_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerSetEpilogues 
typedef ze_result_t (__zecall *zet_pfnTracerSetEpilogues_t)(
    zet_tracer_handle_t,
    zet_core_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerSetEnabled 
typedef ze_result_t (__zecall *zet_pfnTracerSetEnabled_t)(
    zet_tracer_handle_t,
    ze_bool_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Tracer functions pointers
typedef struct _zet_tracer_dditable_t
{
    zet_pfnTracerCreate_t                                       pfnCreate;
    zet_pfnTracerDestroy_t                                      pfnDestroy;
    zet_pfnTracerSetPrologues_t                                 pfnSetPrologues;
    zet_pfnTracerSetEpilogues_t                                 pfnSetEpilogues;
    zet_pfnTracerSetEnabled_t                                   pfnSetEnabled;
} zet_tracer_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetTracerProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetTracerProcAddrTable_t)(
    ze_api_version_t,
    zet_tracer_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugAttach 
typedef ze_result_t (__zecall *zet_pfnDebugAttach_t)(
    zet_device_handle_t,
    const zet_debug_config_t*,
    zet_debug_session_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugDetach 
typedef ze_result_t (__zecall *zet_pfnDebugDetach_t)(
    zet_debug_session_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugGetNumThreads 
typedef ze_result_t (__zecall *zet_pfnDebugGetNumThreads_t)(
    zet_debug_session_handle_t,
    uint64_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugReadEvent 
typedef ze_result_t (__zecall *zet_pfnDebugReadEvent_t)(
    zet_debug_session_handle_t,
    uint64_t,
    size_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugInterrupt 
typedef ze_result_t (__zecall *zet_pfnDebugInterrupt_t)(
    zet_debug_session_handle_t,
    uint64_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugResume 
typedef ze_result_t (__zecall *zet_pfnDebugResume_t)(
    zet_debug_session_handle_t,
    uint64_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugReadMemory 
typedef ze_result_t (__zecall *zet_pfnDebugReadMemory_t)(
    zet_debug_session_handle_t,
    uint64_t,
    int,
    uint64_t,
    size_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugWriteMemory 
typedef ze_result_t (__zecall *zet_pfnDebugWriteMemory_t)(
    zet_debug_session_handle_t,
    uint64_t,
    int,
    uint64_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugReadState 
typedef ze_result_t (__zecall *zet_pfnDebugReadState_t)(
    zet_debug_session_handle_t,
    uint64_t,
    uint64_t,
    size_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugWriteState 
typedef ze_result_t (__zecall *zet_pfnDebugWriteState_t)(
    zet_debug_session_handle_t,
    uint64_t,
    uint64_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Debug functions pointers
typedef struct _zet_debug_dditable_t
{
    zet_pfnDebugAttach_t                                        pfnAttach;
    zet_pfnDebugDetach_t                                        pfnDetach;
    zet_pfnDebugGetNumThreads_t                                 pfnGetNumThreads;
    zet_pfnDebugReadEvent_t                                     pfnReadEvent;
    zet_pfnDebugInterrupt_t                                     pfnInterrupt;
    zet_pfnDebugResume_t                                        pfnResume;
    zet_pfnDebugReadMemory_t                                    pfnReadMemory;
    zet_pfnDebugWriteMemory_t                                   pfnWriteMemory;
    zet_pfnDebugReadState_t                                     pfnReadState;
    zet_pfnDebugWriteState_t                                    pfnWriteState;
} zet_debug_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Debug table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetDebugProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetDebugProcAddrTable_t)(
    ze_api_version_t,
    zet_debug_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _zet_dditable_t
{
    zet_device_dditable_t               Device;
    zet_command_list_dditable_t         CommandList;
    zet_module_dditable_t               Module;
    zet_kernel_dditable_t               Kernel;
    zet_metric_group_dditable_t         MetricGroup;
    zet_metric_dditable_t               Metric;
    zet_metric_tracer_dditable_t        MetricTracer;
    zet_metric_query_pool_dditable_t    MetricQueryPool;
    zet_metric_query_dditable_t         MetricQuery;
    zet_tracer_dditable_t               Tracer;
    zet_debug_dditable_t                Debug;
} zet_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_DDI_H