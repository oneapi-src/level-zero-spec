/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
* The source code contained or described herein and all documents related to the  
* source code ("Material") are owned by Intel Corporation or its suppliers or  
* licensors. Title to the Material remains with Intel Corporation or its suppliers  
* and licensors. The Material contains trade secrets and proprietary and confidential  
* information of Intel or its suppliers and licensors. The Material is protected by  
* worldwide copyright and trade secret laws and treaty provisions. No part of the  
* Material may be used, copied, reproduced, modified, published, uploaded, posted  
* transmitted, distributed, or disclosed in any way without Intel's prior express  
* written permission.  
*
* No license under any patent, copyright, trade secret or other intellectual  
* property right is granted to or conferred upon you by disclosure or delivery  
* of the Materials, either expressly, by implication, inducement, estoppel  
* or otherwise. Any license under such intellectual property rights must be  
* express and approved by Intel in writing.  
* @endcond
*
* @file xet_common.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/common.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_COMMON_HPP
#define _XET_COMMON_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_api.hpp"

namespace xet
{
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
    /// @brief Handle of power object
    class Power;
    struct _power_handle_t;
    using power_handle_t = _power_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of a frequency domain on a device
    class FreqDomain;
    struct _freq_domain_handle_t;
    using freq_domain_handle_t = _freq_domain_handle_t*;

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
