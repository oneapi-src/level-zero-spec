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
* @file xe_loader.h
*
******************************************************************************/
#ifndef _XE_LOADER_H
#define _XE_LOADER_H
#if defined(__cplusplus)
#pragma once
#endif
#include <tuple>
#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"
#include "xe_util.h"

//////////////////////////////////////////////////////////////////////////
using xe_device_group_object_t      = std::tuple < xe_device_group_handle_t, xe_dditable_t* >;
using xe_device_object_t            = std::tuple < xe_device_handle_t, xe_dditable_t* >;
using xe_command_list_object_t      = std::tuple < xe_command_list_handle_t, xe_dditable_t* >;
using xe_command_queue_object_t     = std::tuple < xe_command_queue_handle_t, xe_dditable_t* >;
using xe_fence_object_t             = std::tuple < xe_fence_handle_t, xe_dditable_t* >;
using xe_event_pool_object_t        = std::tuple < xe_event_pool_handle_t, xe_dditable_t* >;
using xe_event_object_t             = std::tuple < xe_event_handle_t, xe_dditable_t* >;
using xe_image_object_t             = std::tuple < xe_image_handle_t, xe_dditable_t* >;
using xe_module_object_t            = std::tuple < xe_module_handle_t, xe_dditable_t* >;
using xe_module_build_log_object_t  = std::tuple < xe_module_build_log_handle_t, xe_dditable_t* >;
using xe_function_object_t          = std::tuple < xe_function_handle_t, xe_dditable_t* >;
using xe_sampler_object_t           = std::tuple < xe_sampler_handle_t, xe_dditable_t* >;

using xex_device_object_t           = std::tuple < xe_device_handle_t, xex_dditable_t* >;
using xex_command_graph_object_t    = std::tuple < xex_command_graph_handle_t, xex_dditable_t* >;

using xet_device_object_t               = std::tuple < xe_device_handle_t, xet_dditable_t* >;
using xet_command_list_object_t         = std::tuple < xe_command_list_handle_t, xet_dditable_t* >;
using xet_event_object_t                = std::tuple < xe_event_handle_t, xet_dditable_t* >;
using xet_metric_group_object_t         = std::tuple < xet_metric_group_handle_t, xet_dditable_t* >;
using xet_metric_object_t               = std::tuple < xet_metric_handle_t, xet_dditable_t* >;
using xet_metric_tracer_object_t        = std::tuple < xet_metric_tracer_handle_t, xet_dditable_t* >;
using xet_metric_query_pool_object_t    = std::tuple < xet_metric_query_pool_handle_t, xet_dditable_t* >;
using xet_metric_query_object_t         = std::tuple < xet_metric_query_handle_t, xet_dditable_t* >;
using xet_power_object_t                = std::tuple < xet_power_handle_t, xet_dditable_t* >;
using xet_freq_domain_object_t          = std::tuple < xet_freq_domain_handle_t, xet_dditable_t* >;


namespace xe_loader
{
    ///////////////////////////////////////////////////////////////////////////////
    class Loader
    {
    public:
        xe_api_version_t version = XE_API_VERSION_1_0;

        HMODULE commonDriver = nullptr;
        HMODULE validationLayer = nullptr;

        Loader();
        ~Loader();

        xe_global_dditable_t   xeGlobalDdiTable = {};
        xex_global_dditable_t  xexGlobalDdiTable = {};
        xet_global_dditable_t  xetGlobalDdiTable = {};
    };

    extern Loader loader;

} // namespace xe_loader
#endif // _XE_LOADER_H