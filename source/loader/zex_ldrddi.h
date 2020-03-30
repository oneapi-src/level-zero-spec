/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_ldrddi.h
 * @version v0.91-271
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using zex_command_list_object_t           = object_t < zex_command_list_handle_t >;
    using zex_command_list_factory_t          = singleton_factory_t < zex_command_list_object_t, zex_command_list_handle_t >;

    using zex_command_graph_object_t          = object_t < zex_command_graph_handle_t >;
    using zex_command_graph_factory_t         = singleton_factory_t < zex_command_graph_object_t, zex_command_graph_handle_t >;

}
