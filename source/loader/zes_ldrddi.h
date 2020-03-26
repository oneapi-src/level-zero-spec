/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_ldrddi.h
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using zes_driver_object_t                 = object_t < zes_driver_handle_t >;
    using zes_driver_factory_t                = singleton_factory_t < zes_driver_object_t, zes_driver_handle_t >;

    using zes_device_object_t                 = object_t < zes_device_handle_t >;
    using zes_device_factory_t                = singleton_factory_t < zes_device_object_t, zes_device_handle_t >;

    using zes_sysman_object_t                 = object_t < zes_sysman_handle_t >;
    using zes_sysman_factory_t                = singleton_factory_t < zes_sysman_object_t, zes_sysman_handle_t >;

    using zes_sysman_sched_object_t           = object_t < zes_sysman_sched_handle_t >;
    using zes_sysman_sched_factory_t          = singleton_factory_t < zes_sysman_sched_object_t, zes_sysman_sched_handle_t >;

    using zes_sysman_perf_object_t            = object_t < zes_sysman_perf_handle_t >;
    using zes_sysman_perf_factory_t           = singleton_factory_t < zes_sysman_perf_object_t, zes_sysman_perf_handle_t >;

    using zes_sysman_pwr_object_t             = object_t < zes_sysman_pwr_handle_t >;
    using zes_sysman_pwr_factory_t            = singleton_factory_t < zes_sysman_pwr_object_t, zes_sysman_pwr_handle_t >;

    using zes_sysman_freq_object_t            = object_t < zes_sysman_freq_handle_t >;
    using zes_sysman_freq_factory_t           = singleton_factory_t < zes_sysman_freq_object_t, zes_sysman_freq_handle_t >;

    using zes_sysman_engine_object_t          = object_t < zes_sysman_engine_handle_t >;
    using zes_sysman_engine_factory_t         = singleton_factory_t < zes_sysman_engine_object_t, zes_sysman_engine_handle_t >;

    using zes_sysman_standby_object_t         = object_t < zes_sysman_standby_handle_t >;
    using zes_sysman_standby_factory_t        = singleton_factory_t < zes_sysman_standby_object_t, zes_sysman_standby_handle_t >;

    using zes_sysman_firmware_object_t        = object_t < zes_sysman_firmware_handle_t >;
    using zes_sysman_firmware_factory_t       = singleton_factory_t < zes_sysman_firmware_object_t, zes_sysman_firmware_handle_t >;

    using zes_sysman_mem_object_t             = object_t < zes_sysman_mem_handle_t >;
    using zes_sysman_mem_factory_t            = singleton_factory_t < zes_sysman_mem_object_t, zes_sysman_mem_handle_t >;

    using zes_sysman_fabric_port_object_t     = object_t < zes_sysman_fabric_port_handle_t >;
    using zes_sysman_fabric_port_factory_t    = singleton_factory_t < zes_sysman_fabric_port_object_t, zes_sysman_fabric_port_handle_t >;

    using zes_sysman_temp_object_t            = object_t < zes_sysman_temp_handle_t >;
    using zes_sysman_temp_factory_t           = singleton_factory_t < zes_sysman_temp_object_t, zes_sysman_temp_handle_t >;

    using zes_sysman_psu_object_t             = object_t < zes_sysman_psu_handle_t >;
    using zes_sysman_psu_factory_t            = singleton_factory_t < zes_sysman_psu_object_t, zes_sysman_psu_handle_t >;

    using zes_sysman_fan_object_t             = object_t < zes_sysman_fan_handle_t >;
    using zes_sysman_fan_factory_t            = singleton_factory_t < zes_sysman_fan_object_t, zes_sysman_fan_handle_t >;

    using zes_sysman_led_object_t             = object_t < zes_sysman_led_handle_t >;
    using zes_sysman_led_factory_t            = singleton_factory_t < zes_sysman_led_object_t, zes_sysman_led_handle_t >;

    using zes_sysman_ras_object_t             = object_t < zes_sysman_ras_handle_t >;
    using zes_sysman_ras_factory_t            = singleton_factory_t < zes_sysman_ras_object_t, zes_sysman_ras_handle_t >;

    using zes_sysman_diag_object_t            = object_t < zes_sysman_diag_handle_t >;
    using zes_sysman_diag_factory_t           = singleton_factory_t < zes_sysman_diag_object_t, zes_sysman_diag_handle_t >;

    using zes_sysman_event_object_t           = object_t < zes_sysman_event_handle_t >;
    using zes_sysman_event_factory_t          = singleton_factory_t < zes_sysman_event_object_t, zes_sysman_event_handle_t >;

}
