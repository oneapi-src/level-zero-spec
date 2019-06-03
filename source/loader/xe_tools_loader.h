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
* @file xe_tools_loader.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/ldrddi.h.mako
* @endcond
*
******************************************************************************/
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using xet_device_object_t                 = object_t < xet_device_handle_t >;
    using xet_device_factory_t                = factory_t < xet_device_object_t >;

    using xet_command_list_object_t           = object_t < xet_command_list_handle_t >;
    using xet_command_list_factory_t          = factory_t < xet_command_list_object_t >;

    using xet_metric_group_object_t           = object_t < xet_metric_group_handle_t >;
    using xet_metric_group_factory_t          = factory_t < xet_metric_group_object_t >;

    using xet_metric_object_t                 = object_t < xet_metric_handle_t >;
    using xet_metric_factory_t                = factory_t < xet_metric_object_t >;

    using xet_metric_tracer_object_t          = object_t < xet_metric_tracer_handle_t >;
    using xet_metric_tracer_factory_t         = factory_t < xet_metric_tracer_object_t >;

    using xet_metric_query_pool_object_t      = object_t < xet_metric_query_pool_handle_t >;
    using xet_metric_query_pool_factory_t     = factory_t < xet_metric_query_pool_object_t >;

    using xet_metric_query_object_t           = object_t < xet_metric_query_handle_t >;
    using xet_metric_query_factory_t          = factory_t < xet_metric_query_object_t >;

    using xet_power_object_t                  = object_t < xet_power_handle_t >;
    using xet_power_factory_t                 = factory_t < xet_power_object_t >;

    using xet_freq_domain_object_t            = object_t < xet_freq_domain_handle_t >;
    using xet_freq_domain_factory_t           = factory_t < xet_freq_domain_object_t >;

}
