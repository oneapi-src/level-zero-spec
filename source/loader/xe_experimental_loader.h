/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_experimental_loader.h
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
    using xex_command_list_object_t           = object_t < xex_command_list_handle_t >;
    using xex_command_list_factory_t          = singleton_factory_t < xex_command_list_object_t, xex_command_list_handle_t >;

    using xex_command_graph_object_t          = object_t < xex_command_graph_handle_t >;
    using xex_command_graph_factory_t         = singleton_factory_t < xex_command_graph_object_t, xex_command_graph_handle_t >;

}
