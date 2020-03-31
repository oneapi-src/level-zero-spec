/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_ldrddi.h
 * @version v1.0-r0.9.277
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using zet_driver_object_t                 = object_t < zet_driver_handle_t >;
    using zet_driver_factory_t                = singleton_factory_t < zet_driver_object_t, zet_driver_handle_t >;

    using zet_device_object_t                 = object_t < zet_device_handle_t >;
    using zet_device_factory_t                = singleton_factory_t < zet_device_object_t, zet_device_handle_t >;

    using zet_command_list_object_t           = object_t < zet_command_list_handle_t >;
    using zet_command_list_factory_t          = singleton_factory_t < zet_command_list_object_t, zet_command_list_handle_t >;

    using zet_module_object_t                 = object_t < zet_module_handle_t >;
    using zet_module_factory_t                = singleton_factory_t < zet_module_object_t, zet_module_handle_t >;

    using zet_kernel_object_t                 = object_t < zet_kernel_handle_t >;
    using zet_kernel_factory_t                = singleton_factory_t < zet_kernel_object_t, zet_kernel_handle_t >;

    using zet_metric_group_object_t           = object_t < zet_metric_group_handle_t >;
    using zet_metric_group_factory_t          = singleton_factory_t < zet_metric_group_object_t, zet_metric_group_handle_t >;

    using zet_metric_object_t                 = object_t < zet_metric_handle_t >;
    using zet_metric_factory_t                = singleton_factory_t < zet_metric_object_t, zet_metric_handle_t >;

    using zet_metric_tracer_object_t          = object_t < zet_metric_tracer_handle_t >;
    using zet_metric_tracer_factory_t         = singleton_factory_t < zet_metric_tracer_object_t, zet_metric_tracer_handle_t >;

    using zet_metric_query_pool_object_t      = object_t < zet_metric_query_pool_handle_t >;
    using zet_metric_query_pool_factory_t     = singleton_factory_t < zet_metric_query_pool_object_t, zet_metric_query_pool_handle_t >;

    using zet_metric_query_object_t           = object_t < zet_metric_query_handle_t >;
    using zet_metric_query_factory_t          = singleton_factory_t < zet_metric_query_object_t, zet_metric_query_handle_t >;

    using zet_tracer_object_t                 = object_t < zet_tracer_handle_t >;
    using zet_tracer_factory_t                = singleton_factory_t < zet_tracer_object_t, zet_tracer_handle_t >;

    using zet_debug_session_object_t          = object_t < zet_debug_session_handle_t >;
    using zet_debug_session_factory_t         = singleton_factory_t < zet_debug_session_object_t, zet_debug_session_handle_t >;

}
