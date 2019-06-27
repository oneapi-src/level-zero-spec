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
/// @brief Handle for accessing System Resource Management features
typedef struct _xet_sysman_handle_t *xet_sysman_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_INVALID_SYSMAN_HANDLE
/// @brief Invalid System Resource Management handle
#define XET_INVALID_SYSMAN_HANDLE  NULL
#endif // XET_INVALID_SYSMAN_HANDLE

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman resource container
typedef struct _xet_res_container_handle_t *xet_res_container_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE
/// @brief Invalid Sysman resource container handle
#define XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE  NULL
#endif // XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle for a Sysman resource
typedef struct _xet_resource_handle_t *xet_resource_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_INVALID_SYSMAN_RESOURCE_HANDLE
/// @brief Invalid Sysman resource handle
#define XET_INVALID_SYSMAN_RESOURCE_HANDLE  NULL
#endif // XET_INVALID_SYSMAN_RESOURCE_HANDLE

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
/// @brief Forward-declare xet_res_container_uuid_t
typedef struct _xet_res_container_uuid_t xet_res_container_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_res_container_info_t
typedef struct _xet_res_container_info_t xet_res_container_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resource_uuid_t
typedef struct _xet_resource_uuid_t xet_resource_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resource_info_t
typedef struct _xet_resource_info_t xet_resource_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_string_property_t
typedef struct _xet_string_property_t xet_string_property_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_pci_bar_info_t
typedef struct _xet_pci_bar_info_t xet_pci_bar_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_accel_asset_t
typedef struct _xet_device_prop_accel_asset_t xet_device_prop_accel_asset_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_accel_assest_t
typedef struct _xet_device_prop_accel_assest_t xet_device_prop_accel_assest_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_bars_t
typedef struct _xet_device_prop_bars_t xet_device_prop_bars_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_error_stats_t
typedef struct _xet_device_prop_error_stats_t xet_device_prop_error_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_speed_t
typedef struct _xet_fan_speed_t xet_fan_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_temp_speed_t
typedef struct _xet_fan_temp_speed_t xet_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_prop_speed_table_t
typedef struct _xet_fan_prop_speed_table_t xet_fan_prop_speed_table_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_led_state_t
typedef struct _xet_led_state_t xet_led_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_firmware_prop_check_t
typedef struct _xet_firmware_prop_check_t xet_firmware_prop_check_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_firmware_prop_flash_t
typedef struct _xet_firmware_prop_flash_t xet_firmware_prop_flash_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_pwr_prop_sustained_limit_t
typedef struct _xet_pwr_prop_sustained_limit_t xet_pwr_prop_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_pwr_prop_burst_limit_t
typedef struct _xet_pwr_prop_burst_limit_t xet_pwr_prop_burst_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_pwr_prop_peak_limit_t
typedef struct _xet_pwr_prop_peak_limit_t xet_pwr_prop_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_range_t
typedef struct _xet_freq_range_t xet_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_divider_t
typedef struct _xet_freq_divider_t xet_freq_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_avail_clocks_t
typedef struct _xet_freq_prop_avail_clocks_t xet_freq_prop_avail_clocks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_avail_dividers_t
typedef struct _xet_freq_prop_avail_dividers_t xet_freq_prop_avail_dividers_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_mem_retire_info_t
typedef struct _xet_mem_retire_info_t xet_mem_retire_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_mem_prop_bad_list_t
typedef struct _xet_mem_prop_bad_list_t xet_mem_prop_bad_list_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_mem_prop_utilization_t
typedef struct _xet_mem_prop_utilization_t xet_mem_prop_utilization_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_mem_prop_bandwidth_t
typedef struct _xet_mem_prop_bandwidth_t xet_mem_prop_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_mem_prop_ecc_counters_t
typedef struct _xet_mem_prop_ecc_counters_t xet_mem_prop_ecc_counters_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_link_speed_t
typedef struct _xet_link_speed_t xet_link_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_link_prop_avail_speeds_t
typedef struct _xet_link_prop_avail_speeds_t xet_link_prop_avail_speeds_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_link_prop_bandwidth_t
typedef struct _xet_link_prop_bandwidth_t xet_link_prop_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_link_prop_speed_t
typedef struct _xet_link_prop_speed_t xet_link_prop_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_link_prop_speed_range_t
typedef struct _xet_link_prop_speed_range_t xet_link_prop_speed_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_sysman_event_data_t
typedef struct _xet_sysman_event_data_t xet_sysman_event_data_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_tracer_desc_t
typedef struct _xet_tracer_desc_t xet_tracer_desc_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_COMMON_H
