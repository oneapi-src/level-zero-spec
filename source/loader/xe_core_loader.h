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
* @file xe_core_loader.h
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
    using xe_device_group_object_t            = object_t < xe_device_group_handle_t >;
    using xe_device_group_factory_t           = singleton_factory_t < xe_device_group_object_t, xe_device_group_handle_t >;

    using xe_device_object_t                  = object_t < xe_device_handle_t >;
    using xe_device_factory_t                 = singleton_factory_t < xe_device_object_t, xe_device_handle_t >;

    using xe_command_queue_object_t           = object_t < xe_command_queue_handle_t >;
    using xe_command_queue_factory_t          = singleton_factory_t < xe_command_queue_object_t, xe_command_queue_handle_t >;

    using xe_command_list_object_t            = object_t < xe_command_list_handle_t >;
    using xe_command_list_factory_t           = singleton_factory_t < xe_command_list_object_t, xe_command_list_handle_t >;

    using xe_fence_object_t                   = object_t < xe_fence_handle_t >;
    using xe_fence_factory_t                  = singleton_factory_t < xe_fence_object_t, xe_fence_handle_t >;

    using xe_event_pool_object_t              = object_t < xe_event_pool_handle_t >;
    using xe_event_pool_factory_t             = singleton_factory_t < xe_event_pool_object_t, xe_event_pool_handle_t >;

    using xe_event_object_t                   = object_t < xe_event_handle_t >;
    using xe_event_factory_t                  = singleton_factory_t < xe_event_object_t, xe_event_handle_t >;

    using xe_image_object_t                   = object_t < xe_image_handle_t >;
    using xe_image_factory_t                  = singleton_factory_t < xe_image_object_t, xe_image_handle_t >;

    using xe_module_object_t                  = object_t < xe_module_handle_t >;
    using xe_module_factory_t                 = singleton_factory_t < xe_module_object_t, xe_module_handle_t >;

    using xe_module_build_log_object_t        = object_t < xe_module_build_log_handle_t >;
    using xe_module_build_log_factory_t       = singleton_factory_t < xe_module_build_log_object_t, xe_module_build_log_handle_t >;

    using xe_function_object_t                = object_t < xe_function_handle_t >;
    using xe_function_factory_t               = singleton_factory_t < xe_function_object_t, xe_function_handle_t >;

    using xe_sampler_object_t                 = object_t < xe_sampler_handle_t >;
    using xe_sampler_factory_t                = singleton_factory_t < xe_sampler_object_t, xe_sampler_handle_t >;

}
