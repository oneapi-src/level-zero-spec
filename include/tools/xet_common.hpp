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
#include "xet_api.h"
#include <tuple>
#include "xe_all.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of device object
    class Device;
    using device_handle_t = Device*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of command list object
    class CommandList;
    using command_list_handle_t = CommandList*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric group's object
    class MetricGroup;
    using metric_group_handle_t = MetricGroup*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric's object
    class Metric;
    using metric_handle_t = Metric*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric tracer's object
    class MetricTracer;
    using metric_tracer_handle_t = MetricTracer*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query pool's object
    class MetricQueryPool;
    using metric_query_pool_handle_t = MetricQueryPool*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query's object
    class MetricQuery;
    using metric_query_handle_t = MetricQuery*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of power object
    class Power;
    using power_handle_t = Power*;

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_COMMON_HPP
