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
* @file xe_loader.cpp
*
******************************************************************************/
#include "xe_loader.h"

//////////////////////////////////////////////////////////////////////////
template<>
xe_device_group_object_t::factory_t     xe_device_group_object_t::factory;
template<>
xe_device_object_t::factory_t           xe_device_object_t::factory;
template<>
xe_command_list_object_t::factory_t     xe_command_list_object_t::factory;
template<>
xe_command_queue_object_t::factory_t    xe_command_queue_object_t::factory;
template<>
xe_fence_object_t::factory_t            xe_fence_object_t::factory;
template<>
xe_event_pool_object_t::factory_t       xe_event_pool_object_t::factory;
template<>
xe_event_object_t::factory_t            xe_event_object_t::factory;
template<>
xe_image_object_t::factory_t            xe_image_object_t::factory;
template<>
xe_module_object_t::factory_t           xe_module_object_t::factory;
template<>
xe_module_build_log_object_t::factory_t xe_module_build_log_object_t::factory;
template<>
xe_function_object_t::factory_t         xe_function_object_t::factory;
template<>
xe_sampler_object_t::factory_t          xe_sampler_object_t::factory;

template<>
xex_device_object_t::factory_t          xex_device_object_t::factory;
template<>
xex_command_graph_object_t::factory_t   xex_command_graph_object_t::factory;

template<>
xet_device_object_t::factory_t              xet_device_object_t::factory;
template<>
xet_command_list_object_t::factory_t        xet_command_list_object_t::factory;
template<>
xet_event_object_t::factory_t               xet_event_object_t::factory;
template<>
xet_metric_group_object_t::factory_t        xet_metric_group_object_t::factory;
template<>
xet_metric_object_t::factory_t              xet_metric_object_t::factory;
template<>
xet_metric_tracer_object_t::factory_t       xet_metric_tracer_object_t::factory;
template<>
xet_metric_query_pool_object_t::factory_t   xet_metric_query_pool_object_t::factory;
template<>
xet_metric_query_object_t::factory_t        xet_metric_query_object_t::factory;
template<>
xet_power_object_t::factory_t               xet_power_object_t::factory;
template<>
xet_freq_domain_object_t::factory_t         xet_freq_domain_object_t::factory;

///////////////////////////////////////////////////////////////////////////////
static const char* known_driver_names[] = { 
    MAKE_DRIVER_NAME( "xe_intc_gpu" )
};

static const size_t num_known_driver_names =
    sizeof( known_driver_names ) / sizeof( known_driver_names[ 0 ] );


///////////////////////////////////////////////////////////////////////////////
Loader loader;


///////////////////////////////////////////////////////////////////////////////
Loader::Loader()
{
    if( getenv_tobool( "XE_ENABLE_NULL_DRIVER" ) )
    {
        auto handle = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "xe_null" ) );
        if( NULL != handle )
        {
            drivers.emplace_back();
            drivers.rbegin()->handle = handle;
        }
    }
    else
    {
        drivers.reserve( num_known_driver_names );
        for( auto name : known_driver_names )
        {
            auto handle = LOAD_DRIVER_LIBRARY( name );
            if( NULL != handle )
            {
                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
            }

        }
    }

    if( getenv_tobool( "XE_ENABLE_VALIDATION_LAYER" ) )
    {
        validationLayer = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "xe_validation_layer" ) );
    }

    forceIntercept = getenv_tobool( "XE_ENABLE_LOADER_INTERCEPT" );
};

///////////////////////////////////////////////////////////////////////////////
Loader::~Loader()
{
    FREE_DRIVER_LIBRARY( validationLayer );

    for( auto& drv : drivers )
    {
        FREE_DRIVER_LIBRARY( drv.handle );
    }
};
