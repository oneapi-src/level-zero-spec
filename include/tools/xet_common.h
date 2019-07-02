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
/// @brief Forward-declare xet_board_prop_serial_number_t
typedef struct _xet_board_prop_serial_number_t xet_board_prop_serial_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_board_prop_board_number_t
typedef struct _xet_board_prop_board_number_t xet_board_prop_board_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_pci_bar_info_t
typedef struct _xet_pci_bar_info_t xet_pci_bar_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_brand_t
typedef struct _xet_device_prop_brand_t xet_device_prop_brand_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_model_t
typedef struct _xet_device_prop_model_t xet_device_prop_model_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_deviceid_t
typedef struct _xet_device_prop_deviceid_t xet_device_prop_deviceid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_vendor_name_t
typedef struct _xet_device_prop_vendor_name_t xet_device_prop_vendor_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_accel_asset_t
typedef struct _xet_device_prop_accel_asset_t xet_device_prop_accel_asset_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_accel_assets_t
typedef struct _xet_device_prop_accel_assets_t xet_device_prop_accel_assets_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_driver_version_t
typedef struct _xet_device_prop_driver_version_t xet_device_prop_driver_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_bars_t
typedef struct _xet_device_prop_bars_t xet_device_prop_bars_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_device_prop_error_stats_t
typedef struct _xet_device_prop_error_stats_t xet_device_prop_error_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_psu_prop_voltage_status_t
typedef struct _xet_psu_prop_voltage_status_t xet_psu_prop_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_temp_speed_t
typedef struct _xet_fan_temp_speed_t xet_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_prop_mode_t
typedef struct _xet_fan_prop_mode_t xet_fan_prop_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_prop_fixed_speed_t
typedef struct _xet_fan_prop_fixed_speed_t xet_fan_prop_fixed_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_prop_speed_table_t
typedef struct _xet_fan_prop_speed_table_t xet_fan_prop_speed_table_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_led_prop_state_t
typedef struct _xet_led_prop_state_t xet_led_prop_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_firmware_prop_name_t
typedef struct _xet_firmware_prop_name_t xet_firmware_prop_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_firmware_prop_version_t
typedef struct _xet_firmware_prop_version_t xet_firmware_prop_version_t;

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
/// @brief Forward-declare xet_freq_divider_t
typedef struct _xet_freq_divider_t xet_freq_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_domain_type_t
typedef struct _xet_freq_prop_domain_type_t xet_freq_prop_domain_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_avail_clocks_t
typedef struct _xet_freq_prop_avail_clocks_t xet_freq_prop_avail_clocks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_avail_dividers_t
typedef struct _xet_freq_prop_avail_dividers_t xet_freq_prop_avail_dividers_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_src_freq_t
typedef struct _xet_freq_prop_src_freq_t xet_freq_prop_src_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_dvfs_mode_t
typedef struct _xet_freq_prop_dvfs_mode_t xet_freq_prop_dvfs_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_freq_range_t
typedef struct _xet_freq_prop_freq_range_t xet_freq_prop_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_prop_freq_divider_t
typedef struct _xet_freq_prop_freq_divider_t xet_freq_prop_freq_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_pwrwell_prop_promo_mode_t
typedef struct _xet_pwrwell_prop_promo_mode_t xet_pwrwell_prop_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_mem_retire_info_t
typedef struct _xet_mem_retire_info_t xet_mem_retire_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_mem_prop_type_t
typedef struct _xet_mem_prop_type_t xet_mem_prop_type_t;

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
/// @brief Forward-declare xet_link_prop_type_t
typedef struct _xet_link_prop_type_t xet_link_prop_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_link_prop_bus_address_t
typedef struct _xet_link_prop_bus_address_t xet_link_prop_bus_address_t;

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
