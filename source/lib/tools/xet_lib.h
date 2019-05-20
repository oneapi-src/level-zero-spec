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
* @file xet_lib.h
*
******************************************************************************/
#ifndef _XET_LIB_H
#define _XET_LIB_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xet_api.hpp"
#include "xet_ddi.h"
#include "xe_util.h"

namespace xet_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    class Library
    {
    public:
        HMODULE loader = nullptr;

        Library();
        ~Library();

        xe_result_t Init();

        xet_global_apitable_t               xetGlobal = {};
        xet_device_apitable_t               xetDevice = {};
        xet_command_list_apitable_t         xetCommandList = {};
        xet_metric_group_apitable_t         xetMetricGroup = {};
        xet_metric_apitable_t               xetMetric = {};
        xet_metric_tracer_apitable_t        xetMetricTracer = {};
        xet_metric_query_pool_apitable_t    xetMetricQueryPool = {};
        xet_metric_query_apitable_t         xetMetricQuery = {};
        xet_power_apitable_t                xetPower = {};
        xet_freq_domain_apitable_t          xetFreqDomain = {};
        xet_sysman_apitable_t               xetSysman = {};
    };

    extern Library lib;

} // namespace xet_lib
#endif // _XET_LIB_H