/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_common.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Experimental API common types
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/common.yml
 * @endcond
 *
 */
#ifndef _XEX_COMMON_HPP
#define _XEX_COMMON_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command graph object
    class CommandGraph;
    struct _command_graph_handle_t;
    using command_graph_handle_t = _command_graph_handle_t*;

} // namespace xex

namespace xex
{
} // namespace xex

namespace xex
{
    using result_t = xe::result_t;
    using exception_t = xe::exception_t;

} // namespace xex
#endif // defined(__cplusplus)
#endif // _XEX_COMMON_HPP
