/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_tools_loader.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/ldrddi.h.mako
 * @endcond
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using xet_driver_object_t                 = object_t < xet_driver_handle_t >;
    using xet_driver_factory_t                = singleton_factory_t < xet_driver_object_t, xet_driver_handle_t >;

    using xet_device_object_t                 = object_t < xet_device_handle_t >;
    using xet_device_factory_t                = singleton_factory_t < xet_device_object_t, xet_device_handle_t >;

    using xet_command_list_object_t           = object_t < xet_command_list_handle_t >;
    using xet_command_list_factory_t          = singleton_factory_t < xet_command_list_object_t, xet_command_list_handle_t >;

    using xet_module_object_t                 = object_t < xet_module_handle_t >;
    using xet_module_factory_t                = singleton_factory_t < xet_module_object_t, xet_module_handle_t >;

    using xet_kernel_object_t                 = object_t < xet_kernel_handle_t >;
    using xet_kernel_factory_t                = singleton_factory_t < xet_kernel_object_t, xet_kernel_handle_t >;

    using xet_metric_group_object_t           = object_t < xet_metric_group_handle_t >;
    using xet_metric_group_factory_t          = singleton_factory_t < xet_metric_group_object_t, xet_metric_group_handle_t >;

    using xet_metric_object_t                 = object_t < xet_metric_handle_t >;
    using xet_metric_factory_t                = singleton_factory_t < xet_metric_object_t, xet_metric_handle_t >;

    using xet_metric_tracer_object_t          = object_t < xet_metric_tracer_handle_t >;
    using xet_metric_tracer_factory_t         = singleton_factory_t < xet_metric_tracer_object_t, xet_metric_tracer_handle_t >;

    using xet_metric_query_pool_object_t      = object_t < xet_metric_query_pool_handle_t >;
    using xet_metric_query_pool_factory_t     = singleton_factory_t < xet_metric_query_pool_object_t, xet_metric_query_pool_handle_t >;

    using xet_metric_query_object_t           = object_t < xet_metric_query_handle_t >;
    using xet_metric_query_factory_t          = singleton_factory_t < xet_metric_query_object_t, xet_metric_query_handle_t >;

    using xet_tracer_object_t                 = object_t < xet_tracer_handle_t >;
    using xet_tracer_factory_t                = singleton_factory_t < xet_tracer_object_t, xet_tracer_handle_t >;

    using xet_sysman_object_t                 = object_t < xet_sysman_handle_t >;
    using xet_sysman_factory_t                = singleton_factory_t < xet_sysman_object_t, xet_sysman_handle_t >;

    using xet_sysman_pwr_object_t             = object_t < xet_sysman_pwr_handle_t >;
    using xet_sysman_pwr_factory_t            = singleton_factory_t < xet_sysman_pwr_object_t, xet_sysman_pwr_handle_t >;

    using xet_sysman_freq_object_t            = object_t < xet_sysman_freq_handle_t >;
    using xet_sysman_freq_factory_t           = singleton_factory_t < xet_sysman_freq_object_t, xet_sysman_freq_handle_t >;

    using xet_sysman_engine_object_t          = object_t < xet_sysman_engine_handle_t >;
    using xet_sysman_engine_factory_t         = singleton_factory_t < xet_sysman_engine_object_t, xet_sysman_engine_handle_t >;

    using xet_sysman_standby_object_t         = object_t < xet_sysman_standby_handle_t >;
    using xet_sysman_standby_factory_t        = singleton_factory_t < xet_sysman_standby_object_t, xet_sysman_standby_handle_t >;

    using xet_sysman_firmware_object_t        = object_t < xet_sysman_firmware_handle_t >;
    using xet_sysman_firmware_factory_t       = singleton_factory_t < xet_sysman_firmware_object_t, xet_sysman_firmware_handle_t >;

    using xet_sysman_mem_object_t             = object_t < xet_sysman_mem_handle_t >;
    using xet_sysman_mem_factory_t            = singleton_factory_t < xet_sysman_mem_object_t, xet_sysman_mem_handle_t >;

    using xet_sysman_link_switch_object_t     = object_t < xet_sysman_link_switch_handle_t >;
    using xet_sysman_link_switch_factory_t    = singleton_factory_t < xet_sysman_link_switch_object_t, xet_sysman_link_switch_handle_t >;

    using xet_sysman_link_port_object_t       = object_t < xet_sysman_link_port_handle_t >;
    using xet_sysman_link_port_factory_t      = singleton_factory_t < xet_sysman_link_port_object_t, xet_sysman_link_port_handle_t >;

    using xet_sysman_temp_object_t            = object_t < xet_sysman_temp_handle_t >;
    using xet_sysman_temp_factory_t           = singleton_factory_t < xet_sysman_temp_object_t, xet_sysman_temp_handle_t >;

    using xet_sysman_psu_object_t             = object_t < xet_sysman_psu_handle_t >;
    using xet_sysman_psu_factory_t            = singleton_factory_t < xet_sysman_psu_object_t, xet_sysman_psu_handle_t >;

    using xet_sysman_fan_object_t             = object_t < xet_sysman_fan_handle_t >;
    using xet_sysman_fan_factory_t            = singleton_factory_t < xet_sysman_fan_object_t, xet_sysman_fan_handle_t >;

    using xet_sysman_led_object_t             = object_t < xet_sysman_led_handle_t >;
    using xet_sysman_led_factory_t            = singleton_factory_t < xet_sysman_led_object_t, xet_sysman_led_handle_t >;

    using xet_sysman_ras_object_t             = object_t < xet_sysman_ras_handle_t >;
    using xet_sysman_ras_factory_t            = singleton_factory_t < xet_sysman_ras_object_t, xet_sysman_ras_handle_t >;

    using xet_sysman_diag_object_t            = object_t < xet_sysman_diag_handle_t >;
    using xet_sysman_diag_factory_t           = singleton_factory_t < xet_sysman_diag_object_t, xet_sysman_diag_handle_t >;

}
