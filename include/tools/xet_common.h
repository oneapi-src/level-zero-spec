/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_common.h
 *
 * @brief Intel 'One API' Level-Zero Tool API common types
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/common.yml
 * @endcond
 *
 */
#ifndef _XET_COMMON_H
#define _XET_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of device group object
typedef xe_device_group_handle_t xet_device_group_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of device object
typedef xe_device_handle_t xet_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of command list object
typedef xe_command_list_handle_t xet_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of module object
typedef xe_module_handle_t xet_module_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of function object
typedef xe_function_handle_t xet_function_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric group's object
typedef struct _xet_metric_group_handle_t *xet_metric_group_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric's object
typedef struct _xet_metric_handle_t *xet_metric_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric tracer's object
typedef struct _xet_metric_tracer_handle_t *xet_metric_tracer_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query pool's object
typedef struct _xet_metric_query_pool_handle_t *xet_metric_query_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query's object
typedef struct _xet_metric_query_handle_t *xet_metric_query_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of tracer object
typedef struct _xet_tracer_handle_t *xet_tracer_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of power object
typedef struct _xet_power_handle_t *xet_power_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of a frequency domain on a device
typedef struct _xet_freq_domain_handle_t *xet_freq_domain_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_group_properties_t
typedef struct _xet_metric_group_properties_t xet_metric_group_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_typed_value_t
typedef struct _xet_typed_value_t xet_typed_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_properties_t
typedef struct _xet_metric_properties_t xet_metric_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_tracer_desc_t
typedef struct _xet_metric_tracer_desc_t xet_metric_tracer_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_query_pool_desc_t
typedef struct _xet_metric_query_pool_desc_t xet_metric_query_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_profile_info_t
typedef struct _xet_profile_info_t xet_profile_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_profile_free_register_token_t
typedef struct _xet_profile_free_register_token_t xet_profile_free_register_token_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_profile_register_sequence_t
typedef struct _xet_profile_register_sequence_t xet_profile_register_sequence_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_average_limit_t
typedef struct _xet_power_average_limit_t xet_power_average_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_burst_limit_t
typedef struct _xet_power_burst_limit_t xet_power_burst_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_peak_limit_t
typedef struct _xet_power_peak_limit_t xet_power_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_limits_t
typedef struct _xet_power_limits_t xet_power_limits_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_domain_properties_t
typedef struct _xet_freq_domain_properties_t xet_freq_domain_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_clock_divider_t
typedef struct _xet_clock_divider_t xet_clock_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_properties_t
typedef struct _xet_fan_properties_t xet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_point_t
typedef struct _xet_fan_point_t xet_fan_point_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_speed_info_t
typedef struct _xet_fan_speed_info_t xet_fan_speed_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_temperature_properties_t
typedef struct _xet_temperature_properties_t xet_temperature_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_activity_properties_t
typedef struct _xet_activity_properties_t xet_activity_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_activity_counters_t
typedef struct _xet_activity_counters_t xet_activity_counters_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_tracer_desc_t
typedef struct _xet_tracer_desc_t xet_tracer_desc_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_COMMON_H
