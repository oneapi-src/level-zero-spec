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
    using xet_device_group_object_t           = object_t < xet_device_group_handle_t >;
    using xet_device_group_factory_t          = singleton_factory_t < xet_device_group_object_t, xet_device_group_handle_t >;

    using xet_device_object_t                 = object_t < xet_device_handle_t >;
    using xet_device_factory_t                = singleton_factory_t < xet_device_object_t, xet_device_handle_t >;

    using xet_command_list_object_t           = object_t < xet_command_list_handle_t >;
    using xet_command_list_factory_t          = singleton_factory_t < xet_command_list_object_t, xet_command_list_handle_t >;

    using xet_module_object_t                 = object_t < xet_module_handle_t >;
    using xet_module_factory_t                = singleton_factory_t < xet_module_object_t, xet_module_handle_t >;

    using xet_function_object_t               = object_t < xet_function_handle_t >;
    using xet_function_factory_t              = singleton_factory_t < xet_function_object_t, xet_function_handle_t >;

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

    using xet_power_object_t                  = object_t < xet_power_handle_t >;
    using xet_power_factory_t                 = singleton_factory_t < xet_power_object_t, xet_power_handle_t >;

    using xet_freq_domain_object_t            = object_t < xet_freq_domain_handle_t >;
    using xet_freq_domain_factory_t           = singleton_factory_t < xet_freq_domain_object_t, xet_freq_domain_handle_t >;

}
