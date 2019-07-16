/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_common.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool API common types
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/common.yml
 * @endcond
 *
 */
#ifndef _XET_COMMON_HPP
#define _XET_COMMON_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of device group object
    class DeviceGroup;
    struct _device_group_handle_t;
    using device_group_handle_t = _device_group_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of device object
    class Device;
    struct _device_handle_t;
    using device_handle_t = _device_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of module object
    class Module;
    struct _module_handle_t;
    using module_handle_t = _module_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of function object
    class Function;
    struct _function_handle_t;
    using function_handle_t = _function_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric group's object
    class MetricGroup;
    struct _metric_group_handle_t;
    using metric_group_handle_t = _metric_group_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric's object
    class Metric;
    struct _metric_handle_t;
    using metric_handle_t = _metric_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric tracer's object
    class MetricTracer;
    struct _metric_tracer_handle_t;
    using metric_tracer_handle_t = _metric_tracer_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query pool's object
    class MetricQueryPool;
    struct _metric_query_pool_handle_t;
    using metric_query_pool_handle_t = _metric_query_pool_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query's object
    class MetricQuery;
    struct _metric_query_handle_t;
    using metric_query_handle_t = _metric_query_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of tracer object
    class Tracer;
    struct _tracer_handle_t;
    using tracer_handle_t = _tracer_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for accessing System Resource Management features
    class Sysman;
    struct _sysman_handle_t;
    using sysman_handle_t = _sysman_handle_t*;

} // namespace xet

namespace xet
{
} // namespace xet

namespace xet
{
    using result_t = xe::result_t;
    using exception_t = xe::exception_t;

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_COMMON_HPP
