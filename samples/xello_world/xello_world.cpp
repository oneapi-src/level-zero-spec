/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "xello_init.h"

//////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    if( argparse( argc, argv, "-null", "--enable_null_driver" ) )
    {
        putenv( const_cast<char *>( "XE_ENABLE_NULL_DRIVER=1" ) );
    }
    if( argparse( argc, argv, "-ldr", "--force_loader_intercepts" ) )
    {
        putenv( const_cast<char *>( "XE_ENABLE_LOADER_INTERCEPT=1" ) );
    }
    if( argparse( argc, argv, "-val", "--enable_validation_layer" ) )
    {
        putenv( const_cast<char *>( "XE_ENABLE_VALIDATION_LAYER=1" ) );
        putenv( const_cast<char *>( "XE_ENABLE_PARAMETER_VALIDATION=1" ) );
    }

    const xe::Driver::device_type_t type = xe::Driver::device_type_t::GPU;

    xe::Driver* pDriver = nullptr;
    xe::Device* pDevice = nullptr;
    if( init_xe() )
    {
        uint32_t driverCount = 0;
        xe::GetDrivers( &driverCount );

        std::vector<xe::Driver*> drivers( driverCount );
        xe::GetDrivers( &driverCount, drivers.data() );

        for( uint32_t driver = 0; driver < driverCount; ++driver )
        {
            pDriver = drivers[driver];
            pDevice = findDevice( pDriver, type );
            if( pDevice )
            {
                break;
            }
        }
    }

    if( !pDevice )
    {
        std::cout << "Did NOT find matching " << xe::to_string(type) <<" device!" << "\n";
        return -1;
    }

    try
    {
        // Create an immediate command list for direct submission
        xe::CommandQueue::desc_t queue_desc;
        auto pCommandList = std::shared_ptr<xe::CommandList>(
            xe::CommandList::CreateImmediate( pDevice, &queue_desc ),
            []( xe::CommandList* p ){ xe::CommandList::Destroy( p ); } );

        // Create an event to be signaled by the device
        xe::EventPool::desc_t pool_desc;
        pool_desc.flags = xe::EventPool::flag_t::HOST_VISIBLE;
        pool_desc.count = 1;
        auto pEventPool = std::shared_ptr<xe::EventPool>(
            xe::EventPool::Create( pDriver, &pool_desc, 0, nullptr ),
            []( xe::EventPool* p ){ xe::EventPool::Destroy( p ); } );

        xe::Event::desc_t event_desc;
        event_desc.signal = xe::Event::scope_flag_t::HOST;
        event_desc.index = 0;
        auto pEvent = std::shared_ptr<xe::Event>(
            xe::Event::Create( pEventPool.get(), &event_desc ),
            []( xe::Event* p ){ xe::Event::Destroy( p ); } );

        // signal the event from the device and wait for completion
        pCommandList->AppendSignalEvent( pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );
        std::cout << "Congratulations, the device completed execution!\n";
    }
    catch( const xe::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}