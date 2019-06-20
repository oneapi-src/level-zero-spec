/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_core_loader.h
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
    using xe_device_group_object_t            = object_t < xe_device_group_handle_t >;
    using xe_device_group_factory_t           = singleton_factory_t < xe_device_group_object_t, xe_device_group_handle_t >;

    using xe_device_object_t                  = object_t < xe_device_handle_t >;
    using xe_device_factory_t                 = singleton_factory_t < xe_device_object_t, xe_device_handle_t >;

    using xe_command_queue_object_t           = object_t < xe_command_queue_handle_t >;
    using xe_command_queue_factory_t          = singleton_factory_t < xe_command_queue_object_t, xe_command_queue_handle_t >;

    using xe_command_list_object_t            = object_t < xe_command_list_handle_t >;
    using xe_command_list_factory_t           = singleton_factory_t < xe_command_list_object_t, xe_command_list_handle_t >;

    using xe_fence_object_t                   = object_t < xe_fence_handle_t >;
    using xe_fence_factory_t                  = singleton_factory_t < xe_fence_object_t, xe_fence_handle_t >;

    using xe_event_pool_object_t              = object_t < xe_event_pool_handle_t >;
    using xe_event_pool_factory_t             = singleton_factory_t < xe_event_pool_object_t, xe_event_pool_handle_t >;

    using xe_event_object_t                   = object_t < xe_event_handle_t >;
    using xe_event_factory_t                  = singleton_factory_t < xe_event_object_t, xe_event_handle_t >;

    using xe_image_object_t                   = object_t < xe_image_handle_t >;
    using xe_image_factory_t                  = singleton_factory_t < xe_image_object_t, xe_image_handle_t >;

    using xe_module_object_t                  = object_t < xe_module_handle_t >;
    using xe_module_factory_t                 = singleton_factory_t < xe_module_object_t, xe_module_handle_t >;

    using xe_module_build_log_object_t        = object_t < xe_module_build_log_handle_t >;
    using xe_module_build_log_factory_t       = singleton_factory_t < xe_module_build_log_object_t, xe_module_build_log_handle_t >;

    using xe_function_object_t                = object_t < xe_function_handle_t >;
    using xe_function_factory_t               = singleton_factory_t < xe_function_object_t, xe_function_handle_t >;

    using xe_sampler_object_t                 = object_t < xe_sampler_handle_t >;
    using xe_sampler_factory_t                = singleton_factory_t < xe_sampler_object_t, xe_sampler_handle_t >;

}
