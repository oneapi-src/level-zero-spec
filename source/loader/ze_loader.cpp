/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_loader.cpp
 *
 */
#include "ze_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    static const char* known_driver_names[] = {
        MAKE_DRIVER_NAME( "ze_intc_gpu" )
    };

    static const size_t num_known_driver_names =
        sizeof( known_driver_names ) / sizeof( known_driver_names[ 0 ] );


    ///////////////////////////////////////////////////////////////////////////////
    context_t context;


    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        if( getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) )
        {
            auto handle = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "ze_null" ) );
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

        if( getenv_tobool( "ZE_ENABLE_VALIDATION_LAYER" ) )
        {
            validationLayer = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "ze_validation_layer" ) );
        }

        forceIntercept = getenv_tobool( "ZE_ENABLE_LOADER_INTERCEPT" );
    };

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
        FREE_DRIVER_LIBRARY( validationLayer );

        for( auto& drv : drivers )
        {
            FREE_DRIVER_LIBRARY( drv.handle );
        }
    };
}
