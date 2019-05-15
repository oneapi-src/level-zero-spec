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
* @file xe_layer.h
*
******************************************************************************/
#ifndef _XE_LAYER_H
#define _XE_LAYER_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"
#include "xe_util.h"

///////////////////////////////////////////////////////////////////////////////
class xe_layer
{
public:
    xe_api_version_t version = XE_API_VERSION_1_0;

    bool enableParameterValidation = false;
    bool enableHandleLifetime = false;
    bool enableMemoryTracker = false;
    bool enableThreadingValidation = false;

    xe_global_apitable_t            xeGlobal = {};
    xe_device_group_apitable_t      xeDeviceGroup = {};
    xe_device_apitable_t            xeDevice = {};
    xe_context_apitable_t           xeContext = {};
    xe_command_list_apitable_t      xeCommandList = {};
    xe_command_queue_apitable_t     xeCommandQueue = {};
    xe_fence_apitable_t             xeFence = {};
    xe_event_pool_apitable_t        xeEventPool = {};
    xe_event_apitable_t             xeEvent = {};
    xe_image_apitable_t             xeImage = {};
    xe_module_apitable_t            xeModule = {};
    xe_module_build_log_apitable_t  xeModuleBuildLog = {};
    xe_function_apitable_t          xeFunction = {};
    xe_sampler_apitable_t           xeSampler = {};

    xex_command_graph_apitable_t    xexCommandGraph = {};

    xet_device_apitable_t               xetDevice = {};
    xet_command_list_apitable_t         xetCommandList = {};
    xet_metric_group_apitable_t         xetMetricGroup = {};
    xet_metric_apitable_t               xetMetric = {};
    xet_metric_tracer_apitable_t        xetMetricTracer = {};
    xet_metric_query_pool_apitable_t    xetMetricQueryPool = {};
    xet_metric_query_apitable_t         xetMetricQuery = {};
    xet_power_apitable_t                xetPower = {};
    xet_freq_domain_apitable_t          xetFreqDomain = {};

    xe_layer();
    ~xe_layer();
};

extern xe_layer context;

#endif // _XE_LAYER_H