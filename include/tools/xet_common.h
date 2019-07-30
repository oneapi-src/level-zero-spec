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
/// @brief Forward-declare xet_pci_bar_info_t
typedef struct _xet_pci_bar_info_t xet_pci_bar_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_serial_number_t
typedef struct _xet_resprop_dev_serial_number_t xet_resprop_dev_serial_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_board_number_t
typedef struct _xet_resprop_dev_board_number_t xet_resprop_dev_board_number_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_brand_t
typedef struct _xet_resprop_dev_brand_t xet_resprop_dev_brand_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_model_t
typedef struct _xet_resprop_dev_model_t xet_resprop_dev_model_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_deviceid_t
typedef struct _xet_resprop_dev_deviceid_t xet_resprop_dev_deviceid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_vendor_name_t
typedef struct _xet_resprop_dev_vendor_name_t xet_resprop_dev_vendor_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_driver_version_t
typedef struct _xet_resprop_dev_driver_version_t xet_resprop_dev_driver_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_dev_bars_t
typedef struct _xet_resprop_dev_bars_t xet_resprop_dev_bars_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_pwr_max_limit_t
typedef struct _xet_resprop_pwr_max_limit_t xet_resprop_pwr_max_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_pwr_energy_counter_t
typedef struct _xet_resprop_pwr_energy_counter_t xet_resprop_pwr_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_pwr_sustained_limit_t
typedef struct _xet_resprop_pwr_sustained_limit_t xet_resprop_pwr_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_pwr_burst_limit_t
typedef struct _xet_resprop_pwr_burst_limit_t xet_resprop_pwr_burst_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_pwr_peak_limit_t
typedef struct _xet_resprop_pwr_peak_limit_t xet_resprop_pwr_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_avail_clocks_t
typedef struct _xet_resprop_freq_avail_clocks_t xet_resprop_freq_avail_clocks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_range_t
typedef struct _xet_resprop_freq_range_t xet_resprop_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_requested_freq_t
typedef struct _xet_resprop_freq_requested_freq_t xet_resprop_freq_requested_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_tdp_freq_t
typedef struct _xet_resprop_freq_tdp_freq_t xet_resprop_freq_tdp_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_efficient_freq_t
typedef struct _xet_resprop_freq_efficient_freq_t xet_resprop_freq_efficient_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_resolved_freq_t
typedef struct _xet_resprop_freq_resolved_freq_t xet_resprop_freq_resolved_freq_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_throttle_reasons_t
typedef struct _xet_resprop_freq_throttle_reasons_t xet_resprop_freq_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_freq_throttle_time_t
typedef struct _xet_resprop_freq_throttle_time_t xet_resprop_freq_throttle_time_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_util_counters_t
typedef struct _xet_resprop_util_counters_t xet_resprop_util_counters_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_mem_type_t
typedef struct _xet_resprop_mem_type_t xet_resprop_mem_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_mem_utilization_t
typedef struct _xet_resprop_mem_utilization_t xet_resprop_mem_utilization_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_mem_bandwidth_t
typedef struct _xet_resprop_mem_bandwidth_t xet_resprop_mem_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_link_speed_t
typedef struct _xet_link_speed_t xet_link_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_type_t
typedef struct _xet_resprop_link_type_t xet_resprop_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_bus_address_t
typedef struct _xet_resprop_link_bus_address_t xet_resprop_link_bus_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_peer_device_t
typedef struct _xet_resprop_link_peer_device_t xet_resprop_link_peer_device_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_avail_speeds_t
typedef struct _xet_resprop_link_avail_speeds_t xet_resprop_link_avail_speeds_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_max_packet_size_t
typedef struct _xet_resprop_link_max_packet_size_t xet_resprop_link_max_packet_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_bandwidth_t
typedef struct _xet_resprop_link_bandwidth_t xet_resprop_link_bandwidth_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_speed_t
typedef struct _xet_resprop_link_speed_t xet_resprop_link_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_link_speed_range_t
typedef struct _xet_resprop_link_speed_range_t xet_resprop_link_speed_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_temp_temperature_t
typedef struct _xet_resprop_temp_temperature_t xet_resprop_temp_temperature_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_stby_promo_mode_t
typedef struct _xet_resprop_stby_promo_mode_t xet_resprop_stby_promo_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fw_name_t
typedef struct _xet_resprop_fw_name_t xet_resprop_fw_name_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fw_version_t
typedef struct _xet_resprop_fw_version_t xet_resprop_fw_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fw_check_t
typedef struct _xet_resprop_fw_check_t xet_resprop_fw_check_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fw_flash_t
typedef struct _xet_resprop_fw_flash_t xet_resprop_fw_flash_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_psu_amp_limit_t
typedef struct _xet_resprop_psu_amp_limit_t xet_resprop_psu_amp_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_psu_voltage_status_t
typedef struct _xet_resprop_psu_voltage_status_t xet_resprop_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_psu_fan_failure_t
typedef struct _xet_resprop_psu_fan_failure_t xet_resprop_psu_fan_failure_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_psu_temperature_t
typedef struct _xet_resprop_psu_temperature_t xet_resprop_psu_temperature_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_psu_amps_t
typedef struct _xet_resprop_psu_amps_t xet_resprop_psu_amps_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_temp_speed_t
typedef struct _xet_fan_temp_speed_t xet_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fan_max_rpm_t
typedef struct _xet_resprop_fan_max_rpm_t xet_resprop_fan_max_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fan_max_table_size_t
typedef struct _xet_resprop_fan_max_table_size_t xet_resprop_fan_max_table_size_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fan_speed_rpm_t
typedef struct _xet_resprop_fan_speed_rpm_t xet_resprop_fan_speed_rpm_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fan_speed_percent_t
typedef struct _xet_resprop_fan_speed_percent_t xet_resprop_fan_speed_percent_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fan_mode_t
typedef struct _xet_resprop_fan_mode_t xet_resprop_fan_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fan_fixed_speed_t
typedef struct _xet_resprop_fan_fixed_speed_t xet_resprop_fan_fixed_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_fan_speed_table_t
typedef struct _xet_resprop_fan_speed_table_t xet_resprop_fan_speed_table_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_led_rgb_cap_t
typedef struct _xet_resprop_led_rgb_cap_t xet_resprop_led_rgb_cap_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_led_state_t
typedef struct _xet_resprop_led_state_t xet_resprop_led_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resid_info_t
typedef struct _xet_resid_info_t xet_resid_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_info_t
typedef struct _xet_resprop_info_t xet_resprop_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_resprop_request_t
typedef struct _xet_resprop_request_t xet_resprop_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_ras_config_t
typedef struct _xet_ras_config_t xet_ras_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_ras_filter_t
typedef struct _xet_ras_filter_t xet_ras_filter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_ras_error_t
typedef struct _xet_ras_error_t xet_ras_error_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_event_support_t
typedef struct _xet_event_support_t xet_event_support_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_event_request_t
typedef struct _xet_event_request_t xet_event_request_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_diag_test_t
typedef struct _xet_diag_test_t xet_diag_test_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_diag_test_list_t
typedef struct _xet_diag_test_list_t xet_diag_test_list_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_tracer_desc_t
typedef struct _xet_tracer_desc_t xet_tracer_desc_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_COMMON_H
