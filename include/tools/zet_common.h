/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_common.h
 *
 * @brief Intel 'One API' Level-Zero Tool API common types
 *
 */
 
#ifndef _ZET_COMMON_H
#define _ZET_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle to a driver instance
typedef ze_driver_handle_t zet_driver_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of device object
typedef ze_device_handle_t zet_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of command list object
typedef ze_command_list_handle_t zet_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of module object
typedef ze_module_handle_t zet_module_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of function object
typedef ze_kernel_handle_t zet_kernel_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric group's object
typedef struct _zet_metric_group_handle_t *zet_metric_group_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric's object
typedef struct _zet_metric_handle_t *zet_metric_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric tracer's object
typedef struct _zet_metric_tracer_handle_t *zet_metric_tracer_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query pool's object
typedef struct _zet_metric_query_pool_handle_t *zet_metric_query_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query's object
typedef struct _zet_metric_query_handle_t *zet_metric_query_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of tracer object
typedef struct _zet_tracer_handle_t *zet_tracer_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_config_v1_t
typedef struct _zet_debug_config_v1_t zet_debug_config_v1_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_config_t
typedef struct _zet_debug_config_t zet_debug_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_event_info_detached_t
typedef struct _zet_debug_event_info_detached_t zet_debug_event_info_detached_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_event_info_module_t
typedef struct _zet_debug_event_info_module_t zet_debug_event_info_module_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_event_t
typedef struct _zet_debug_event_t zet_debug_event_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_state_section_t
typedef struct _zet_debug_state_section_t zet_debug_state_section_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_debug_state_t
typedef struct _zet_debug_state_t zet_debug_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_group_properties_t
typedef struct _zet_metric_group_properties_t zet_metric_group_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_typed_value_t
typedef struct _zet_typed_value_t zet_typed_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_properties_t
typedef struct _zet_metric_properties_t zet_metric_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_tracer_desc_t
typedef struct _zet_metric_tracer_desc_t zet_metric_tracer_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_metric_query_pool_desc_t
typedef struct _zet_metric_query_pool_desc_t zet_metric_query_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_profile_info_t
typedef struct _zet_profile_info_t zet_profile_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_profile_free_register_token_t
typedef struct _zet_profile_free_register_token_t zet_profile_free_register_token_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_profile_register_sequence_t
typedef struct _zet_profile_register_sequence_t zet_profile_register_sequence_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zet_tracer_desc_t
typedef struct _zet_tracer_desc_t zet_tracer_desc_t;


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_COMMON_H
