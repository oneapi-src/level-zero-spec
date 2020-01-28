/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_common.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Experimental API common types
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/common.yml
 * @endcond
 *
 */
#ifndef _ZEX_COMMON_HPP
#define _ZEX_COMMON_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zex
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

} // namespace zex

namespace zex
{
} // namespace zex

namespace zex
{
    using result_t = ze::result_t;
    using exception_t = ze::exception_t;

} // namespace zex
#endif // defined(__cplusplus)
#endif // _ZEX_COMMON_HPP
