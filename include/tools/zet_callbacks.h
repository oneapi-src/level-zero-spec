/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_callbacks.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools
 * @endcond
 *
 */
#ifndef _ZET_CALLBACKS_H
#define _ZET_CALLBACKS_H
#if defined(__cplusplus)
#pragma once
#endif
#include "zet_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetInit 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_init_params_t
{
    ze_init_flag_t* pflags;
} zet_init_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetInit 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnInitCb_t)(
    zet_init_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _zet_global_callbacks_t
{
    zet_pfnInitCb_t                                                 pfnInitCb;
} zet_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetDeviceActivateMetricGroups 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_device_activate_metric_groups_params_t
{
    zet_device_handle_t* phDevice;
    uint32_t* pcount;
    zet_metric_group_handle_t** pphMetricGroups;
} zet_device_activate_metric_groups_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetDeviceActivateMetricGroups 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnDeviceActivateMetricGroupsCb_t)(
    zet_device_activate_metric_groups_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device callback functions pointers
typedef struct _zet_device_callbacks_t
{
    zet_pfnDeviceActivateMetricGroupsCb_t                           pfnActivateMetricGroupsCb;
} zet_device_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetCommandListAppendMetricTracerMarker 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_command_list_append_metric_tracer_marker_params_t
{
    zet_command_list_handle_t* phCommandList;
    zet_metric_tracer_handle_t* phMetricTracer;
    uint32_t* pvalue;
} zet_command_list_append_metric_tracer_marker_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetCommandListAppendMetricTracerMarker 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnCommandListAppendMetricTracerMarkerCb_t)(
    zet_command_list_append_metric_tracer_marker_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetCommandListAppendMetricQueryBegin 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_command_list_append_metric_query_begin_params_t
{
    zet_command_list_handle_t* phCommandList;
    zet_metric_query_handle_t* phMetricQuery;
} zet_command_list_append_metric_query_begin_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetCommandListAppendMetricQueryBegin 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnCommandListAppendMetricQueryBeginCb_t)(
    zet_command_list_append_metric_query_begin_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetCommandListAppendMetricQueryEnd 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_command_list_append_metric_query_end_params_t
{
    zet_command_list_handle_t* phCommandList;
    zet_metric_query_handle_t* phMetricQuery;
    ze_event_handle_t* phCompletionEvent;
} zet_command_list_append_metric_query_end_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetCommandListAppendMetricQueryEnd 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnCommandListAppendMetricQueryEndCb_t)(
    zet_command_list_append_metric_query_end_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetCommandListAppendMetricMemoryBarrier 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_command_list_append_metric_memory_barrier_params_t
{
    zet_command_list_handle_t* phCommandList;
} zet_command_list_append_metric_memory_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetCommandListAppendMetricMemoryBarrier 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnCommandListAppendMetricMemoryBarrierCb_t)(
    zet_command_list_append_metric_memory_barrier_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList callback functions pointers
typedef struct _zet_command_list_callbacks_t
{
    zet_pfnCommandListAppendMetricTracerMarkerCb_t                  pfnAppendMetricTracerMarkerCb;
    zet_pfnCommandListAppendMetricQueryBeginCb_t                    pfnAppendMetricQueryBeginCb;
    zet_pfnCommandListAppendMetricQueryEndCb_t                      pfnAppendMetricQueryEndCb;
    zet_pfnCommandListAppendMetricMemoryBarrierCb_t                 pfnAppendMetricMemoryBarrierCb;
} zet_command_list_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetModuleGetDebugInfo 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_module_get_debug_info_params_t
{
    zet_module_handle_t* phModule;
    zet_module_debug_info_format_t* pformat;
    size_t** ppSize;
    uint8_t** ppDebugInfo;
} zet_module_get_debug_info_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetModuleGetDebugInfo 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnModuleGetDebugInfoCb_t)(
    zet_module_get_debug_info_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetModuleGetKernelNames 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_module_get_kernel_names_params_t
{
    zet_module_handle_t* phModule;
    uint32_t** ppCount;
    const char*** ppNames;
} zet_module_get_kernel_names_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetModuleGetKernelNames 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnModuleGetKernelNamesCb_t)(
    zet_module_get_kernel_names_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module callback functions pointers
typedef struct _zet_module_callbacks_t
{
    zet_pfnModuleGetDebugInfoCb_t                                   pfnGetDebugInfoCb;
    zet_pfnModuleGetKernelNamesCb_t                                 pfnGetKernelNamesCb;
} zet_module_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetKernelGetProfileInfo 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_kernel_get_profile_info_params_t
{
    zet_kernel_handle_t* phKernel;
    zet_profile_info_t** ppInfo;
} zet_kernel_get_profile_info_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetKernelGetProfileInfo 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnKernelGetProfileInfoCb_t)(
    zet_kernel_get_profile_info_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Kernel callback functions pointers
typedef struct _zet_kernel_callbacks_t
{
    zet_pfnKernelGetProfileInfoCb_t                                 pfnGetProfileInfoCb;
} zet_kernel_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricGroupGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_group_get_params_t
{
    zet_device_handle_t* phDevice;
    uint32_t** ppCount;
    zet_metric_group_handle_t** pphMetricGroups;
} zet_metric_group_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricGroupGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricGroupGetCb_t)(
    zet_metric_group_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricGroupGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_group_get_properties_params_t
{
    zet_metric_group_handle_t* phMetricGroup;
    zet_metric_group_properties_t** ppProperties;
} zet_metric_group_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricGroupGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricGroupGetPropertiesCb_t)(
    zet_metric_group_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricGroupCalculateMetricValues 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_group_calculate_metric_values_params_t
{
    zet_metric_group_handle_t* phMetricGroup;
    size_t* prawDataSize;
    uint8_t** ppRawData;
    uint32_t** ppMetricValueCount;
    zet_typed_value_t** ppMetricValues;
} zet_metric_group_calculate_metric_values_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricGroupCalculateMetricValues 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricGroupCalculateMetricValuesCb_t)(
    zet_metric_group_calculate_metric_values_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricGroup callback functions pointers
typedef struct _zet_metric_group_callbacks_t
{
    zet_pfnMetricGroupGetCb_t                                       pfnGetCb;
    zet_pfnMetricGroupGetPropertiesCb_t                             pfnGetPropertiesCb;
    zet_pfnMetricGroupCalculateMetricValuesCb_t                     pfnCalculateMetricValuesCb;
} zet_metric_group_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_get_params_t
{
    zet_metric_group_handle_t* phMetricGroup;
    uint32_t** ppCount;
    zet_metric_handle_t** pphMetrics;
} zet_metric_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricGetCb_t)(
    zet_metric_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_get_properties_params_t
{
    zet_metric_handle_t* phMetric;
    zet_metric_properties_t** ppProperties;
} zet_metric_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricGetPropertiesCb_t)(
    zet_metric_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Metric callback functions pointers
typedef struct _zet_metric_callbacks_t
{
    zet_pfnMetricGetCb_t                                            pfnGetCb;
    zet_pfnMetricGetPropertiesCb_t                                  pfnGetPropertiesCb;
} zet_metric_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricTracerOpen 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_tracer_open_params_t
{
    zet_device_handle_t* phDevice;
    zet_metric_group_handle_t* phMetricGroup;
    zet_metric_tracer_desc_t** pdesc;
    ze_event_handle_t* phNotificationEvent;
    zet_metric_tracer_handle_t** pphMetricTracer;
} zet_metric_tracer_open_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricTracerOpen 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricTracerOpenCb_t)(
    zet_metric_tracer_open_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricTracerClose 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_tracer_close_params_t
{
    zet_metric_tracer_handle_t* phMetricTracer;
} zet_metric_tracer_close_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricTracerClose 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricTracerCloseCb_t)(
    zet_metric_tracer_close_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricTracerReadData 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_tracer_read_data_params_t
{
    zet_metric_tracer_handle_t* phMetricTracer;
    uint32_t* pmaxReportCount;
    size_t** ppRawDataSize;
    uint8_t** ppRawData;
} zet_metric_tracer_read_data_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricTracerReadData 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricTracerReadDataCb_t)(
    zet_metric_tracer_read_data_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricTracer callback functions pointers
typedef struct _zet_metric_tracer_callbacks_t
{
    zet_pfnMetricTracerOpenCb_t                                     pfnOpenCb;
    zet_pfnMetricTracerCloseCb_t                                    pfnCloseCb;
    zet_pfnMetricTracerReadDataCb_t                                 pfnReadDataCb;
} zet_metric_tracer_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricQueryPoolCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_query_pool_create_params_t
{
    zet_device_handle_t* phDevice;
    zet_metric_group_handle_t* phMetricGroup;
    const zet_metric_query_pool_desc_t** pdesc;
    zet_metric_query_pool_handle_t** pphMetricQueryPool;
} zet_metric_query_pool_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricQueryPoolCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricQueryPoolCreateCb_t)(
    zet_metric_query_pool_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricQueryPoolDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_query_pool_destroy_params_t
{
    zet_metric_query_pool_handle_t* phMetricQueryPool;
} zet_metric_query_pool_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricQueryPoolDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricQueryPoolDestroyCb_t)(
    zet_metric_query_pool_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQueryPool callback functions pointers
typedef struct _zet_metric_query_pool_callbacks_t
{
    zet_pfnMetricQueryPoolCreateCb_t                                pfnCreateCb;
    zet_pfnMetricQueryPoolDestroyCb_t                               pfnDestroyCb;
} zet_metric_query_pool_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricQueryCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_query_create_params_t
{
    zet_metric_query_pool_handle_t* phMetricQueryPool;
    uint32_t* pindex;
    zet_metric_query_handle_t** pphMetricQuery;
} zet_metric_query_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricQueryCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricQueryCreateCb_t)(
    zet_metric_query_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricQueryDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_query_destroy_params_t
{
    zet_metric_query_handle_t* phMetricQuery;
} zet_metric_query_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricQueryDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricQueryDestroyCb_t)(
    zet_metric_query_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricQueryReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_query_reset_params_t
{
    zet_metric_query_handle_t* phMetricQuery;
} zet_metric_query_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricQueryReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricQueryResetCb_t)(
    zet_metric_query_reset_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetMetricQueryGetData 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_metric_query_get_data_params_t
{
    zet_metric_query_handle_t* phMetricQuery;
    size_t** ppRawDataSize;
    uint8_t** ppRawData;
} zet_metric_query_get_data_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetMetricQueryGetData 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnMetricQueryGetDataCb_t)(
    zet_metric_query_get_data_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQuery callback functions pointers
typedef struct _zet_metric_query_callbacks_t
{
    zet_pfnMetricQueryCreateCb_t                                    pfnCreateCb;
    zet_pfnMetricQueryDestroyCb_t                                   pfnDestroyCb;
    zet_pfnMetricQueryResetCb_t                                     pfnResetCb;
    zet_pfnMetricQueryGetDataCb_t                                   pfnGetDataCb;
} zet_metric_query_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetTracerCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_tracer_create_params_t
{
    zet_device_handle_t* phDevice;
    const zet_tracer_desc_t** pdesc;
    zet_tracer_handle_t** pphTracer;
} zet_tracer_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetTracerCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnTracerCreateCb_t)(
    zet_tracer_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetTracerDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_tracer_destroy_params_t
{
    zet_tracer_handle_t* phTracer;
} zet_tracer_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetTracerDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnTracerDestroyCb_t)(
    zet_tracer_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetTracerSetPrologues 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_tracer_set_prologues_params_t
{
    zet_tracer_handle_t* phTracer;
    zet_core_callbacks_t** ppCoreCbs;
    zet_experimental_callbacks_t** ppExperimentalCbs;
} zet_tracer_set_prologues_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetTracerSetPrologues 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnTracerSetProloguesCb_t)(
    zet_tracer_set_prologues_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetTracerSetEpilogues 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_tracer_set_epilogues_params_t
{
    zet_tracer_handle_t* phTracer;
    zet_core_callbacks_t** ppCoreCbs;
    zet_experimental_callbacks_t** ppExperimentalCbs;
} zet_tracer_set_epilogues_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetTracerSetEpilogues 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnTracerSetEpiloguesCb_t)(
    zet_tracer_set_epilogues_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetTracerSetEnabled 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_tracer_set_enabled_params_t
{
    zet_tracer_handle_t* phTracer;
    ze_bool_t* penable;
} zet_tracer_set_enabled_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetTracerSetEnabled 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnTracerSetEnabledCb_t)(
    zet_tracer_set_enabled_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Tracer callback functions pointers
typedef struct _zet_tracer_callbacks_t
{
    zet_pfnTracerCreateCb_t                                         pfnCreateCb;
    zet_pfnTracerDestroyCb_t                                        pfnDestroyCb;
    zet_pfnTracerSetProloguesCb_t                                   pfnSetProloguesCb;
    zet_pfnTracerSetEpiloguesCb_t                                   pfnSetEpiloguesCb;
    zet_pfnTracerSetEnabledCb_t                                     pfnSetEnabledCb;
} zet_tracer_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_get_params_t
{
    zet_device_handle_t* phDevice;
    zet_sysman_version_t* pversion;
    zet_sysman_handle_t** pphSysman;
} zet_sysman_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanGetCb_t)(
    zet_sysman_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanDeviceGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_device_get_properties_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_sysman_properties_t** ppProperties;
} zet_sysman_device_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanDeviceGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanDeviceGetPropertiesCb_t)(
    zet_sysman_device_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanSchedulerGetCurrentMode 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_scheduler_get_current_mode_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_sched_mode_t** ppMode;
} zet_sysman_scheduler_get_current_mode_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanSchedulerGetCurrentMode 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanSchedulerGetCurrentModeCb_t)(
    zet_sysman_scheduler_get_current_mode_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanSchedulerGetTimeoutModeProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_scheduler_get_timeout_mode_properties_params_t
{
    zet_sysman_handle_t* phSysman;
    ze_bool_t* pgetDefaults;
    zet_sched_timeout_properties_t** ppConfig;
} zet_sysman_scheduler_get_timeout_mode_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanSchedulerGetTimeoutModeProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanSchedulerGetTimeoutModePropertiesCb_t)(
    zet_sysman_scheduler_get_timeout_mode_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanSchedulerGetTimesliceModeProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_scheduler_get_timeslice_mode_properties_params_t
{
    zet_sysman_handle_t* phSysman;
    ze_bool_t* pgetDefaults;
    zet_sched_timeslice_properties_t** ppConfig;
} zet_sysman_scheduler_get_timeslice_mode_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanSchedulerGetTimesliceModeProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanSchedulerGetTimesliceModePropertiesCb_t)(
    zet_sysman_scheduler_get_timeslice_mode_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanSchedulerSetTimeoutMode 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_scheduler_set_timeout_mode_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_sched_timeout_properties_t** ppProperties;
    ze_bool_t** ppNeedReboot;
} zet_sysman_scheduler_set_timeout_mode_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanSchedulerSetTimeoutMode 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanSchedulerSetTimeoutModeCb_t)(
    zet_sysman_scheduler_set_timeout_mode_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanSchedulerSetTimesliceMode 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_scheduler_set_timeslice_mode_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_sched_timeslice_properties_t** ppProperties;
    ze_bool_t** ppNeedReboot;
} zet_sysman_scheduler_set_timeslice_mode_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanSchedulerSetTimesliceMode 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanSchedulerSetTimesliceModeCb_t)(
    zet_sysman_scheduler_set_timeslice_mode_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanSchedulerSetExclusiveMode 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_scheduler_set_exclusive_mode_params_t
{
    zet_sysman_handle_t* phSysman;
    ze_bool_t** ppNeedReboot;
} zet_sysman_scheduler_set_exclusive_mode_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanSchedulerSetExclusiveMode 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanSchedulerSetExclusiveModeCb_t)(
    zet_sysman_scheduler_set_exclusive_mode_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanSchedulerSetComputeUnitDebugMode 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_scheduler_set_compute_unit_debug_mode_params_t
{
    zet_sysman_handle_t* phSysman;
    ze_bool_t** ppNeedReboot;
} zet_sysman_scheduler_set_compute_unit_debug_mode_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanSchedulerSetComputeUnitDebugMode 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanSchedulerSetComputeUnitDebugModeCb_t)(
    zet_sysman_scheduler_set_compute_unit_debug_mode_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanDeviceReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_device_reset_params_t
{
    zet_sysman_handle_t* phSysman;
} zet_sysman_device_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanDeviceReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanDeviceResetCb_t)(
    zet_sysman_device_reset_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanDeviceWasRepaired 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_device_was_repaired_params_t
{
    zet_sysman_handle_t* phSysman;
    ze_bool_t** ppWasRepaired;
} zet_sysman_device_was_repaired_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanDeviceWasRepaired 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanDeviceWasRepairedCb_t)(
    zet_sysman_device_was_repaired_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPciGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_pci_get_properties_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_pci_properties_t** ppProperties;
} zet_sysman_pci_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPciGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPciGetPropertiesCb_t)(
    zet_sysman_pci_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPciGetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_pci_get_state_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_pci_state_t** ppState;
} zet_sysman_pci_get_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPciGetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPciGetStateCb_t)(
    zet_sysman_pci_get_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPciGetBarProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_pci_get_bar_properties_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t* pbarIndex;
    zet_pci_bar_properties_t** ppProperties;
} zet_sysman_pci_get_bar_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPciGetBarProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPciGetBarPropertiesCb_t)(
    zet_sysman_pci_get_bar_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPciGetThroughput 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_pci_get_throughput_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_pci_throughput_t** ppThroughput;
} zet_sysman_pci_get_throughput_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPciGetThroughput 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPciGetThroughputCb_t)(
    zet_sysman_pci_get_throughput_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPciGetStats 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_pci_get_stats_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_pci_stats_t** ppStats;
} zet_sysman_pci_get_stats_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPciGetStats 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPciGetStatsCb_t)(
    zet_sysman_pci_get_stats_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_pwr_handle_t** pphPower;
} zet_sysman_power_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerGetCb_t)(
    zet_sysman_power_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_freq_handle_t** pphFrequency;
} zet_sysman_frequency_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetCb_t)(
    zet_sysman_frequency_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanEngineGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_engine_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_engine_handle_t** pphEngine;
} zet_sysman_engine_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanEngineGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanEngineGetCb_t)(
    zet_sysman_engine_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanStandbyGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_standby_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_standby_handle_t** pphStandby;
} zet_sysman_standby_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanStandbyGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanStandbyGetCb_t)(
    zet_sysman_standby_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFirmwareGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_firmware_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_firmware_handle_t** pphFirmware;
} zet_sysman_firmware_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFirmwareGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFirmwareGetCb_t)(
    zet_sysman_firmware_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanMemoryGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_memory_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_mem_handle_t** pphMemory;
} zet_sysman_memory_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanMemoryGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanMemoryGetCb_t)(
    zet_sysman_memory_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkSwitchGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_switch_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_link_switch_handle_t** pphSwitch;
} zet_sysman_link_switch_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkSwitchGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkSwitchGetCb_t)(
    zet_sysman_link_switch_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanTemperatureGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_temperature_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_temp_handle_t** pphTemperature;
} zet_sysman_temperature_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanTemperatureGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanTemperatureGetCb_t)(
    zet_sysman_temperature_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPsuGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_psu_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_psu_handle_t** pphPsu;
} zet_sysman_psu_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPsuGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPsuGetCb_t)(
    zet_sysman_psu_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFanGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_fan_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_fan_handle_t** pphFan;
} zet_sysman_fan_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFanGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFanGetCb_t)(
    zet_sysman_fan_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLedGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_led_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_led_handle_t** pphLed;
} zet_sysman_led_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLedGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLedGetCb_t)(
    zet_sysman_led_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanRasGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_ras_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_ras_handle_t** pphRas;
} zet_sysman_ras_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanRasGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanRasGetCb_t)(
    zet_sysman_ras_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanEventsGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_events_get_properties_params_t
{
    zet_sysman_handle_t* phSysman;
    zet_event_properties_t** ppProperties;
} zet_sysman_events_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanEventsGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanEventsGetPropertiesCb_t)(
    zet_sysman_events_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanEventsRegister 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_events_register_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t* pcount;
    zet_event_request_t** ppEvents;
} zet_sysman_events_register_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanEventsRegister 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanEventsRegisterCb_t)(
    zet_sysman_events_register_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanEventsUnregister 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_events_unregister_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t* pcount;
    zet_event_request_t** ppEvents;
} zet_sysman_events_unregister_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanEventsUnregister 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanEventsUnregisterCb_t)(
    zet_sysman_events_unregister_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanEventsListen 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_events_listen_params_t
{
    zet_sysman_handle_t* phSysman;
    ze_bool_t* pclear;
    uint32_t* ptimeout;
    uint32_t** ppEvents;
} zet_sysman_events_listen_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanEventsListen 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanEventsListenCb_t)(
    zet_sysman_events_listen_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanDiagnosticsGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_diagnostics_get_params_t
{
    zet_sysman_handle_t* phSysman;
    uint32_t** ppCount;
    zet_sysman_diag_handle_t** pphDiagnostics;
} zet_sysman_diagnostics_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanDiagnosticsGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanDiagnosticsGetCb_t)(
    zet_sysman_diagnostics_get_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sysman callback functions pointers
typedef struct _zet_sysman_callbacks_t
{
    zet_pfnSysmanGetCb_t                                            pfnGetCb;
    zet_pfnSysmanDeviceGetPropertiesCb_t                            pfnDeviceGetPropertiesCb;
    zet_pfnSysmanSchedulerGetCurrentModeCb_t                        pfnSchedulerGetCurrentModeCb;
    zet_pfnSysmanSchedulerGetTimeoutModePropertiesCb_t              pfnSchedulerGetTimeoutModePropertiesCb;
    zet_pfnSysmanSchedulerGetTimesliceModePropertiesCb_t            pfnSchedulerGetTimesliceModePropertiesCb;
    zet_pfnSysmanSchedulerSetTimeoutModeCb_t                        pfnSchedulerSetTimeoutModeCb;
    zet_pfnSysmanSchedulerSetTimesliceModeCb_t                      pfnSchedulerSetTimesliceModeCb;
    zet_pfnSysmanSchedulerSetExclusiveModeCb_t                      pfnSchedulerSetExclusiveModeCb;
    zet_pfnSysmanSchedulerSetComputeUnitDebugModeCb_t               pfnSchedulerSetComputeUnitDebugModeCb;
    zet_pfnSysmanDeviceResetCb_t                                    pfnDeviceResetCb;
    zet_pfnSysmanDeviceWasRepairedCb_t                              pfnDeviceWasRepairedCb;
    zet_pfnSysmanPciGetPropertiesCb_t                               pfnPciGetPropertiesCb;
    zet_pfnSysmanPciGetStateCb_t                                    pfnPciGetStateCb;
    zet_pfnSysmanPciGetBarPropertiesCb_t                            pfnPciGetBarPropertiesCb;
    zet_pfnSysmanPciGetThroughputCb_t                               pfnPciGetThroughputCb;
    zet_pfnSysmanPciGetStatsCb_t                                    pfnPciGetStatsCb;
    zet_pfnSysmanPowerGetCb_t                                       pfnPowerGetCb;
    zet_pfnSysmanFrequencyGetCb_t                                   pfnFrequencyGetCb;
    zet_pfnSysmanEngineGetCb_t                                      pfnEngineGetCb;
    zet_pfnSysmanStandbyGetCb_t                                     pfnStandbyGetCb;
    zet_pfnSysmanFirmwareGetCb_t                                    pfnFirmwareGetCb;
    zet_pfnSysmanMemoryGetCb_t                                      pfnMemoryGetCb;
    zet_pfnSysmanLinkSwitchGetCb_t                                  pfnLinkSwitchGetCb;
    zet_pfnSysmanTemperatureGetCb_t                                 pfnTemperatureGetCb;
    zet_pfnSysmanPsuGetCb_t                                         pfnPsuGetCb;
    zet_pfnSysmanFanGetCb_t                                         pfnFanGetCb;
    zet_pfnSysmanLedGetCb_t                                         pfnLedGetCb;
    zet_pfnSysmanRasGetCb_t                                         pfnRasGetCb;
    zet_pfnSysmanEventsGetPropertiesCb_t                            pfnEventsGetPropertiesCb;
    zet_pfnSysmanEventsRegisterCb_t                                 pfnEventsRegisterCb;
    zet_pfnSysmanEventsUnregisterCb_t                               pfnEventsUnregisterCb;
    zet_pfnSysmanEventsListenCb_t                                   pfnEventsListenCb;
    zet_pfnSysmanDiagnosticsGetCb_t                                 pfnDiagnosticsGetCb;
} zet_sysman_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerSetOcIccMax 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_set_oc_icc_max_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    uint32_t** pOcIccMax;
} zet_sysman_power_set_oc_icc_max_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerSetOcIccMax 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerSetOcIccMaxCb_t)(
    zet_sysman_power_set_oc_icc_max_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerSetOcTjMax 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_set_oc_tj_max_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    uint32_t** pOcTjMax;
} zet_sysman_power_set_oc_tj_max_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerSetOcTjMax 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerSetOcTjMaxCb_t)(
    zet_sysman_power_set_oc_tj_max_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_get_properties_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    zet_power_properties_t** ppProperties;
} zet_sysman_power_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerGetPropertiesCb_t)(
    zet_sysman_power_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerGetEnergyCounter 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_get_energy_counter_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    zet_power_energy_counter_t** ppEnergy;
} zet_sysman_power_get_energy_counter_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerGetEnergyCounter 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerGetEnergyCounterCb_t)(
    zet_sysman_power_get_energy_counter_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerGetEnergyThreshold 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_get_energy_threshold_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    zet_power_energy_threshold_t** ppThreshold;
} zet_sysman_power_get_energy_threshold_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerGetEnergyThreshold 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerGetEnergyThresholdCb_t)(
    zet_sysman_power_get_energy_threshold_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerSetEnergyThreshold 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_set_energy_threshold_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    zet_power_energy_threshold_t** ppThreshold;
} zet_sysman_power_set_energy_threshold_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerSetEnergyThreshold 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerSetEnergyThresholdCb_t)(
    zet_sysman_power_set_energy_threshold_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerGetLimits 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_get_limits_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    zet_power_sustained_limit_t** ppSustained;
    zet_power_burst_limit_t** ppBurst;
    zet_power_peak_limit_t** ppPeak;
} zet_sysman_power_get_limits_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerGetLimits 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerGetLimitsCb_t)(
    zet_sysman_power_get_limits_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPowerSetLimits 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_power_set_limits_params_t
{
    zet_sysman_pwr_handle_t* phPower;
    const zet_power_sustained_limit_t** ppSustained;
    const zet_power_burst_limit_t** ppBurst;
    const zet_power_peak_limit_t** ppPeak;
} zet_sysman_power_set_limits_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPowerSetLimits 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPowerSetLimitsCb_t)(
    zet_sysman_power_set_limits_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanPower callback functions pointers
typedef struct _zet_sysman_power_callbacks_t
{
    zet_pfnSysmanPowerSetOcIccMaxCb_t                               pfnSetOcIccMaxCb;
    zet_pfnSysmanPowerSetOcTjMaxCb_t                                pfnSetOcTjMaxCb;
    zet_pfnSysmanPowerGetPropertiesCb_t                             pfnGetPropertiesCb;
    zet_pfnSysmanPowerGetEnergyCounterCb_t                          pfnGetEnergyCounterCb;
    zet_pfnSysmanPowerGetEnergyThresholdCb_t                        pfnGetEnergyThresholdCb;
    zet_pfnSysmanPowerSetEnergyThresholdCb_t                        pfnSetEnergyThresholdCb;
    zet_pfnSysmanPowerGetLimitsCb_t                                 pfnGetLimitsCb;
    zet_pfnSysmanPowerSetLimitsCb_t                                 pfnSetLimitsCb;
} zet_sysman_power_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetLastOcError 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_last_oc_error_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_error_type_t** ppOcError;
} zet_sysman_frequency_get_last_oc_error_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetLastOcError 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetLastOcErrorCb_t)(
    zet_sysman_frequency_get_last_oc_error_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetOcCapabilities 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_oc_capabilities_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_capabilities_t** ppOcCapabilities;
} zet_sysman_frequency_get_oc_capabilities_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetOcCapabilities 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetOcCapabilitiesCb_t)(
    zet_sysman_frequency_get_oc_capabilities_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetOcConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_oc_config_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_configuration_t** ppOcConfiguration;
} zet_sysman_frequency_get_oc_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetOcConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetOcConfigCb_t)(
    zet_sysman_frequency_get_oc_config_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencySetOcConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_set_oc_config_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_configuration_t** ppOcConfiguration;
} zet_sysman_frequency_set_oc_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencySetOcConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencySetOcConfigCb_t)(
    zet_sysman_frequency_set_oc_config_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetOcIccMax 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_oc_icc_max_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_icc_max_t** ppOcIccMax;
} zet_sysman_frequency_get_oc_icc_max_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetOcIccMax 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetOcIccMaxCb_t)(
    zet_sysman_frequency_get_oc_icc_max_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencySetOcIccMax 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_set_oc_icc_max_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_icc_max_t** ppOcIccMax;
} zet_sysman_frequency_set_oc_icc_max_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencySetOcIccMax 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencySetOcIccMaxCb_t)(
    zet_sysman_frequency_set_oc_icc_max_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetOcTjMax 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_oc_tj_max_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_tj_max_t** ppOcTjMax;
} zet_sysman_frequency_get_oc_tj_max_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetOcTjMax 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetOcTjMaxCb_t)(
    zet_sysman_frequency_get_oc_tj_max_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencySetOcTjMax 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_set_oc_tj_max_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_oc_tj_max_t** ppOcTjMax;
} zet_sysman_frequency_set_oc_tj_max_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencySetOcTjMax 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencySetOcTjMaxCb_t)(
    zet_sysman_frequency_set_oc_tj_max_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_properties_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_freq_properties_t** ppProperties;
} zet_sysman_frequency_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetPropertiesCb_t)(
    zet_sysman_frequency_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetRange 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_range_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_freq_range_t** ppLimits;
} zet_sysman_frequency_get_range_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetRange 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetRangeCb_t)(
    zet_sysman_frequency_get_range_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencySetRange 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_set_range_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    const zet_freq_range_t** ppLimits;
} zet_sysman_frequency_set_range_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencySetRange 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencySetRangeCb_t)(
    zet_sysman_frequency_set_range_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_state_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_freq_state_t** ppState;
} zet_sysman_frequency_get_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetStateCb_t)(
    zet_sysman_frequency_get_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFrequencyGetThrottleTime 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_frequency_get_throttle_time_params_t
{
    zet_sysman_freq_handle_t* phFrequency;
    zet_freq_throttle_time_t** ppThrottleTime;
} zet_sysman_frequency_get_throttle_time_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFrequencyGetThrottleTime 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFrequencyGetThrottleTimeCb_t)(
    zet_sysman_frequency_get_throttle_time_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFrequency callback functions pointers
typedef struct _zet_sysman_frequency_callbacks_t
{
    zet_pfnSysmanFrequencyGetLastOcErrorCb_t                        pfnGetLastOcErrorCb;
    zet_pfnSysmanFrequencyGetOcCapabilitiesCb_t                     pfnGetOcCapabilitiesCb;
    zet_pfnSysmanFrequencyGetOcConfigCb_t                           pfnGetOcConfigCb;
    zet_pfnSysmanFrequencySetOcConfigCb_t                           pfnSetOcConfigCb;
    zet_pfnSysmanFrequencyGetOcIccMaxCb_t                           pfnGetOcIccMaxCb;
    zet_pfnSysmanFrequencySetOcIccMaxCb_t                           pfnSetOcIccMaxCb;
    zet_pfnSysmanFrequencyGetOcTjMaxCb_t                            pfnGetOcTjMaxCb;
    zet_pfnSysmanFrequencySetOcTjMaxCb_t                            pfnSetOcTjMaxCb;
    zet_pfnSysmanFrequencyGetPropertiesCb_t                         pfnGetPropertiesCb;
    zet_pfnSysmanFrequencyGetRangeCb_t                              pfnGetRangeCb;
    zet_pfnSysmanFrequencySetRangeCb_t                              pfnSetRangeCb;
    zet_pfnSysmanFrequencyGetStateCb_t                              pfnGetStateCb;
    zet_pfnSysmanFrequencyGetThrottleTimeCb_t                       pfnGetThrottleTimeCb;
} zet_sysman_frequency_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanEngineGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_engine_get_properties_params_t
{
    zet_sysman_engine_handle_t* phEngine;
    zet_engine_properties_t** ppProperties;
} zet_sysman_engine_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanEngineGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanEngineGetPropertiesCb_t)(
    zet_sysman_engine_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanEngineGetActivity 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_engine_get_activity_params_t
{
    zet_sysman_engine_handle_t* phEngine;
    zet_engine_stats_t** ppStats;
} zet_sysman_engine_get_activity_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanEngineGetActivity 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanEngineGetActivityCb_t)(
    zet_sysman_engine_get_activity_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanEngine callback functions pointers
typedef struct _zet_sysman_engine_callbacks_t
{
    zet_pfnSysmanEngineGetPropertiesCb_t                            pfnGetPropertiesCb;
    zet_pfnSysmanEngineGetActivityCb_t                              pfnGetActivityCb;
} zet_sysman_engine_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanStandbyGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_standby_get_properties_params_t
{
    zet_sysman_standby_handle_t* phStandby;
    zet_standby_properties_t** ppProperties;
} zet_sysman_standby_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanStandbyGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanStandbyGetPropertiesCb_t)(
    zet_sysman_standby_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanStandbyGetMode 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_standby_get_mode_params_t
{
    zet_sysman_standby_handle_t* phStandby;
    zet_standby_promo_mode_t** ppMode;
} zet_sysman_standby_get_mode_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanStandbyGetMode 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanStandbyGetModeCb_t)(
    zet_sysman_standby_get_mode_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanStandbySetMode 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_standby_set_mode_params_t
{
    zet_sysman_standby_handle_t* phStandby;
    zet_standby_promo_mode_t* pmode;
} zet_sysman_standby_set_mode_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanStandbySetMode 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanStandbySetModeCb_t)(
    zet_sysman_standby_set_mode_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanStandby callback functions pointers
typedef struct _zet_sysman_standby_callbacks_t
{
    zet_pfnSysmanStandbyGetPropertiesCb_t                           pfnGetPropertiesCb;
    zet_pfnSysmanStandbyGetModeCb_t                                 pfnGetModeCb;
    zet_pfnSysmanStandbySetModeCb_t                                 pfnSetModeCb;
} zet_sysman_standby_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFirmwareGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_firmware_get_properties_params_t
{
    zet_sysman_firmware_handle_t* phFirmware;
    zet_firmware_properties_t** ppProperties;
} zet_sysman_firmware_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFirmwareGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFirmwareGetPropertiesCb_t)(
    zet_sysman_firmware_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFirmwareGetChecksum 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_firmware_get_checksum_params_t
{
    zet_sysman_firmware_handle_t* phFirmware;
    uint32_t** ppChecksum;
} zet_sysman_firmware_get_checksum_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFirmwareGetChecksum 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFirmwareGetChecksumCb_t)(
    zet_sysman_firmware_get_checksum_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFirmwareFlash 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_firmware_flash_params_t
{
    zet_sysman_firmware_handle_t* phFirmware;
    void** ppImage;
    uint32_t* psize;
} zet_sysman_firmware_flash_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFirmwareFlash 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFirmwareFlashCb_t)(
    zet_sysman_firmware_flash_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFirmware callback functions pointers
typedef struct _zet_sysman_firmware_callbacks_t
{
    zet_pfnSysmanFirmwareGetPropertiesCb_t                          pfnGetPropertiesCb;
    zet_pfnSysmanFirmwareGetChecksumCb_t                            pfnGetChecksumCb;
    zet_pfnSysmanFirmwareFlashCb_t                                  pfnFlashCb;
} zet_sysman_firmware_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanMemoryGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_memory_get_properties_params_t
{
    zet_sysman_mem_handle_t* phMemory;
    zet_mem_properties_t** ppProperties;
} zet_sysman_memory_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanMemoryGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanMemoryGetPropertiesCb_t)(
    zet_sysman_memory_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanMemoryGetBandwidth 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_memory_get_bandwidth_params_t
{
    zet_sysman_mem_handle_t* phMemory;
    zet_mem_bandwidth_t** ppBandwidth;
} zet_sysman_memory_get_bandwidth_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanMemoryGetBandwidth 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanMemoryGetBandwidthCb_t)(
    zet_sysman_memory_get_bandwidth_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanMemoryGetAllocated 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_memory_get_allocated_params_t
{
    zet_sysman_mem_handle_t* phMemory;
    zet_mem_alloc_t** ppAllocated;
} zet_sysman_memory_get_allocated_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanMemoryGetAllocated 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanMemoryGetAllocatedCb_t)(
    zet_sysman_memory_get_allocated_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanMemory callback functions pointers
typedef struct _zet_sysman_memory_callbacks_t
{
    zet_pfnSysmanMemoryGetPropertiesCb_t                            pfnGetPropertiesCb;
    zet_pfnSysmanMemoryGetBandwidthCb_t                             pfnGetBandwidthCb;
    zet_pfnSysmanMemoryGetAllocatedCb_t                             pfnGetAllocatedCb;
} zet_sysman_memory_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkSwitchGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_switch_get_properties_params_t
{
    zet_sysman_link_switch_handle_t* phSwitch;
    zet_link_switch_properties_t** ppProperties;
} zet_sysman_link_switch_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkSwitchGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkSwitchGetPropertiesCb_t)(
    zet_sysman_link_switch_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkSwitchGetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_switch_get_state_params_t
{
    zet_sysman_link_switch_handle_t* phSwitch;
    zet_link_switch_state_t** ppState;
} zet_sysman_link_switch_get_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkSwitchGetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkSwitchGetStateCb_t)(
    zet_sysman_link_switch_get_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkSwitchSetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_switch_set_state_params_t
{
    zet_sysman_link_switch_handle_t* phSwitch;
    ze_bool_t* penable;
} zet_sysman_link_switch_set_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkSwitchSetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkSwitchSetStateCb_t)(
    zet_sysman_link_switch_set_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkSwitchGetPorts 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_switch_get_ports_params_t
{
    zet_sysman_link_switch_handle_t* phSysmanLinkSwitch;
    uint32_t** ppCount;
    zet_sysman_link_port_handle_t** pphPort;
} zet_sysman_link_switch_get_ports_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkSwitchGetPorts 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkSwitchGetPortsCb_t)(
    zet_sysman_link_switch_get_ports_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanLinkSwitch callback functions pointers
typedef struct _zet_sysman_link_switch_callbacks_t
{
    zet_pfnSysmanLinkSwitchGetPropertiesCb_t                        pfnGetPropertiesCb;
    zet_pfnSysmanLinkSwitchGetStateCb_t                             pfnGetStateCb;
    zet_pfnSysmanLinkSwitchSetStateCb_t                             pfnSetStateCb;
    zet_pfnSysmanLinkSwitchGetPortsCb_t                             pfnGetPortsCb;
} zet_sysman_link_switch_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkPortGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_port_get_properties_params_t
{
    zet_sysman_link_port_handle_t* phPort;
    zet_link_port_properties_t** ppProperties;
} zet_sysman_link_port_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkPortGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkPortGetPropertiesCb_t)(
    zet_sysman_link_port_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkPortGetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_port_get_state_params_t
{
    zet_sysman_link_port_handle_t* phPort;
    zet_link_port_state_t** ppState;
} zet_sysman_link_port_get_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkPortGetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkPortGetStateCb_t)(
    zet_sysman_link_port_get_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkPortGetThroughput 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_port_get_throughput_params_t
{
    zet_sysman_link_port_handle_t* phPort;
    zet_link_port_throughput_t** ppThroughput;
} zet_sysman_link_port_get_throughput_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkPortGetThroughput 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkPortGetThroughputCb_t)(
    zet_sysman_link_port_get_throughput_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkPortGetStats 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_port_get_stats_params_t
{
    zet_sysman_link_port_handle_t* phPort;
    zet_link_port_stats_t** ppStats;
} zet_sysman_link_port_get_stats_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkPortGetStats 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkPortGetStatsCb_t)(
    zet_sysman_link_port_get_stats_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLinkPortIsConnected 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_link_port_is_connected_params_t
{
    zet_sysman_link_port_handle_t* phPort;
    zet_sysman_link_port_handle_t* phRemotePort;
    ze_bool_t** ppConnected;
} zet_sysman_link_port_is_connected_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLinkPortIsConnected 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLinkPortIsConnectedCb_t)(
    zet_sysman_link_port_is_connected_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanLinkPort callback functions pointers
typedef struct _zet_sysman_link_port_callbacks_t
{
    zet_pfnSysmanLinkPortGetPropertiesCb_t                          pfnGetPropertiesCb;
    zet_pfnSysmanLinkPortGetStateCb_t                               pfnGetStateCb;
    zet_pfnSysmanLinkPortGetThroughputCb_t                          pfnGetThroughputCb;
    zet_pfnSysmanLinkPortGetStatsCb_t                               pfnGetStatsCb;
    zet_pfnSysmanLinkPortIsConnectedCb_t                            pfnIsConnectedCb;
} zet_sysman_link_port_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanTemperatureGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_temperature_get_properties_params_t
{
    zet_sysman_temp_handle_t* phTemperature;
    zet_temp_properties_t** ppProperties;
} zet_sysman_temperature_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanTemperatureGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanTemperatureGetPropertiesCb_t)(
    zet_sysman_temperature_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanTemperatureRead 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_temperature_read_params_t
{
    zet_sysman_temp_handle_t* phTemperature;
    uint32_t** ppTemperature;
} zet_sysman_temperature_read_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanTemperatureRead 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanTemperatureReadCb_t)(
    zet_sysman_temperature_read_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanTemperature callback functions pointers
typedef struct _zet_sysman_temperature_callbacks_t
{
    zet_pfnSysmanTemperatureGetPropertiesCb_t                       pfnGetPropertiesCb;
    zet_pfnSysmanTemperatureReadCb_t                                pfnReadCb;
} zet_sysman_temperature_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPsuGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_psu_get_properties_params_t
{
    zet_sysman_psu_handle_t* phPsu;
    zet_psu_properties_t** ppProperties;
} zet_sysman_psu_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPsuGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPsuGetPropertiesCb_t)(
    zet_sysman_psu_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanPsuGetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_psu_get_state_params_t
{
    zet_sysman_psu_handle_t* phPsu;
    zet_psu_state_t** ppState;
} zet_sysman_psu_get_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanPsuGetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanPsuGetStateCb_t)(
    zet_sysman_psu_get_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanPsu callback functions pointers
typedef struct _zet_sysman_psu_callbacks_t
{
    zet_pfnSysmanPsuGetPropertiesCb_t                               pfnGetPropertiesCb;
    zet_pfnSysmanPsuGetStateCb_t                                    pfnGetStateCb;
} zet_sysman_psu_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFanGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_fan_get_properties_params_t
{
    zet_sysman_fan_handle_t* phFan;
    zet_fan_properties_t** ppProperties;
} zet_sysman_fan_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFanGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFanGetPropertiesCb_t)(
    zet_sysman_fan_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFanGetConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_fan_get_config_params_t
{
    zet_sysman_fan_handle_t* phFan;
    zet_fan_config_t** ppConfig;
} zet_sysman_fan_get_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFanGetConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFanGetConfigCb_t)(
    zet_sysman_fan_get_config_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFanSetConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_fan_set_config_params_t
{
    zet_sysman_fan_handle_t* phFan;
    const zet_fan_config_t** ppConfig;
} zet_sysman_fan_set_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFanSetConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFanSetConfigCb_t)(
    zet_sysman_fan_set_config_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanFanGetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_fan_get_state_params_t
{
    zet_sysman_fan_handle_t* phFan;
    zet_fan_speed_units_t* punits;
    zet_fan_state_t** ppState;
} zet_sysman_fan_get_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanFanGetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanFanGetStateCb_t)(
    zet_sysman_fan_get_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFan callback functions pointers
typedef struct _zet_sysman_fan_callbacks_t
{
    zet_pfnSysmanFanGetPropertiesCb_t                               pfnGetPropertiesCb;
    zet_pfnSysmanFanGetConfigCb_t                                   pfnGetConfigCb;
    zet_pfnSysmanFanSetConfigCb_t                                   pfnSetConfigCb;
    zet_pfnSysmanFanGetStateCb_t                                    pfnGetStateCb;
} zet_sysman_fan_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLedGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_led_get_properties_params_t
{
    zet_sysman_led_handle_t* phLed;
    zet_led_properties_t** ppProperties;
} zet_sysman_led_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLedGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLedGetPropertiesCb_t)(
    zet_sysman_led_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLedGetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_led_get_state_params_t
{
    zet_sysman_led_handle_t* phLed;
    zet_led_state_t** ppState;
} zet_sysman_led_get_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLedGetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLedGetStateCb_t)(
    zet_sysman_led_get_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanLedSetState 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_led_set_state_params_t
{
    zet_sysman_led_handle_t* phLed;
    const zet_led_state_t** ppState;
} zet_sysman_led_set_state_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanLedSetState 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanLedSetStateCb_t)(
    zet_sysman_led_set_state_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanLed callback functions pointers
typedef struct _zet_sysman_led_callbacks_t
{
    zet_pfnSysmanLedGetPropertiesCb_t                               pfnGetPropertiesCb;
    zet_pfnSysmanLedGetStateCb_t                                    pfnGetStateCb;
    zet_pfnSysmanLedSetStateCb_t                                    pfnSetStateCb;
} zet_sysman_led_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanRasGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_ras_get_properties_params_t
{
    zet_sysman_ras_handle_t* phRas;
    zet_ras_properties_t** ppProperties;
} zet_sysman_ras_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanRasGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanRasGetPropertiesCb_t)(
    zet_sysman_ras_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanRasGetErrors 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_ras_get_errors_params_t
{
    zet_sysman_ras_handle_t* phRas;
    ze_bool_t* pclear;
    uint64_t** ppTotalErrors;
    zet_ras_details_t** ppDetails;
} zet_sysman_ras_get_errors_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanRasGetErrors 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanRasGetErrorsCb_t)(
    zet_sysman_ras_get_errors_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanRas callback functions pointers
typedef struct _zet_sysman_ras_callbacks_t
{
    zet_pfnSysmanRasGetPropertiesCb_t                               pfnGetPropertiesCb;
    zet_pfnSysmanRasGetErrorsCb_t                                   pfnGetErrorsCb;
} zet_sysman_ras_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanDiagnosticsGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_diagnostics_get_properties_params_t
{
    zet_sysman_diag_handle_t* phDiagnostics;
    zet_diag_properties_t** ppProperties;
} zet_sysman_diagnostics_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanDiagnosticsGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanDiagnosticsGetPropertiesCb_t)(
    zet_sysman_diagnostics_get_properties_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zetSysmanDiagnosticsRunTests 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zet_sysman_diagnostics_run_tests_params_t
{
    zet_sysman_diag_handle_t* phDiagnostics;
    uint32_t* pstart;
    uint32_t* pend;
    zet_diag_result_t** ppResult;
} zet_sysman_diagnostics_run_tests_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zetSysmanDiagnosticsRunTests 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zet_pfnSysmanDiagnosticsRunTestsCb_t)(
    zet_sysman_diagnostics_run_tests_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanDiagnostics callback functions pointers
typedef struct _zet_sysman_diagnostics_callbacks_t
{
    zet_pfnSysmanDiagnosticsGetPropertiesCb_t                       pfnGetPropertiesCb;
    zet_pfnSysmanDiagnosticsRunTestsCb_t                            pfnRunTestsCb;
} zet_sysman_diagnostics_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _zet_callbacks_t
{
    zet_global_callbacks_t              Global;
    zet_device_callbacks_t              Device;
    zet_command_list_callbacks_t        CommandList;
    zet_module_callbacks_t              Module;
    zet_kernel_callbacks_t              Kernel;
    zet_metric_group_callbacks_t        MetricGroup;
    zet_metric_callbacks_t              Metric;
    zet_metric_tracer_callbacks_t       MetricTracer;
    zet_metric_query_pool_callbacks_t   MetricQueryPool;
    zet_metric_query_callbacks_t        MetricQuery;
    zet_tracer_callbacks_t              Tracer;
    zet_sysman_callbacks_t              Sysman;
    zet_sysman_power_callbacks_t        SysmanPower;
    zet_sysman_frequency_callbacks_t    SysmanFrequency;
    zet_sysman_engine_callbacks_t       SysmanEngine;
    zet_sysman_standby_callbacks_t      SysmanStandby;
    zet_sysman_firmware_callbacks_t     SysmanFirmware;
    zet_sysman_memory_callbacks_t       SysmanMemory;
    zet_sysman_link_switch_callbacks_t  SysmanLinkSwitch;
    zet_sysman_link_port_callbacks_t    SysmanLinkPort;
    zet_sysman_temperature_callbacks_t  SysmanTemperature;
    zet_sysman_psu_callbacks_t          SysmanPsu;
    zet_sysman_fan_callbacks_t          SysmanFan;
    zet_sysman_led_callbacks_t          SysmanLed;
    zet_sysman_ras_callbacks_t          SysmanRas;
    zet_sysman_diagnostics_callbacks_t  SysmanDiagnostics;
} zet_callbacks_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_CALLBACKS_H