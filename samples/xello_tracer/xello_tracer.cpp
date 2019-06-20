/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>
#include <chrono>

#include "xello_init.h"

//////////////////////////////////////////////////////////////////////////
struct my_tracer_data_t
{
    uint32_t instance = 0;
};

using time_point_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

struct my_instance_data_t
{
    time_point_t start;
};


//////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    if( argparse( argc, argv, "-null", "--enable_null_driver" ) )
    {
        putenv( const_cast<char *>( "XE_ENABLE_NULL_DRIVER=1" ) );
    }

    putenv( const_cast<char *>( "XE_ENABLE_INSTRUMENTATION_LAYER=1" ) );
    putenv( const_cast<char *>( "XE_ENABLE_API_TRACING=1" ) );

    xet::DeviceGroup* pDeviceGroup = nullptr;
    if( init_xe() && init_xet() )
        pDeviceGroup = reinterpret_cast<xet::DeviceGroup*>(findDeviceGroup( xe::DeviceGroup::device_type_t::GPU ));

    if( !pDeviceGroup )
        return -1;

    try
    {
        // Get the first device within the device group
        xe::Device* pDevice = nullptr;
        uint32_t deviceCount = 1;
        xe::Device::Get( pDeviceGroup, &deviceCount, &pDevice );

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
            xe::EventPool::Create( pDeviceGroup, &pool_desc, 0, nullptr ),
            []( xe::EventPool* p ){ xe::EventPool::Destroy( p ); } );

        xe::Event::desc_t event_desc;
        event_desc.signal = xe::Event::scope_flag_t::HOST;
        event_desc.index = 0;
        auto pEvent = std::shared_ptr<xe::Event>(
            xe::Event::Create( pEventPool.get(), &event_desc ),
            []( xe::Event* p ){ xe::Event::Destroy( p ); } );

        // Create a tracer for the event call
        my_tracer_data_t gbl;
        xet::Tracer::desc_t tracer_desc;
        tracer_desc.pUserData = &gbl;
        auto pTracer = std::shared_ptr<xet::Tracer>(
            xet::Tracer::Create( pDeviceGroup, &tracer_desc ),
            []( xet::Tracer* p ){ xet::Tracer::Destroy( p ); } );

        // Set the callbacks
        xet::Tracer::core_callbacks_t prologCbs = {};
        prologCbs.CommandList.pfnAppendSignalEventCb = [](
            xe_command_list_append_signal_event_params_t*, xe_result_t,
            void* pTracerUserData,
            void** ppTracerInstanceUserData )
        {
            my_instance_data_t* instance_data = new my_instance_data_t;
            *ppTracerInstanceUserData = instance_data;

            instance_data->start = std::chrono::high_resolution_clock::now();
        };
        pTracer->SetPrologues( &prologCbs );

        xet::Tracer::core_callbacks_t epilogCbs = {};
        epilogCbs.CommandList.pfnAppendSignalEventCb = [](
            xe_command_list_append_signal_event_params_t*, xe_result_t,
            void* pTracerUserData,
            void** ppTracerInstanceUserData )
        {
            auto end = std::chrono::high_resolution_clock::now();

            my_tracer_data_t* tracer_data = reinterpret_cast<my_tracer_data_t*>( pTracerUserData );
            my_instance_data_t* instance_data = *reinterpret_cast<my_instance_data_t**>( ppTracerInstanceUserData );

            std::chrono::duration<double, std::micro> diff = end - instance_data->start;
            std::cout << "AppendSignalEvent #" << tracer_data->instance++ << " took : " << diff.count() << " us\n";

            delete instance_data;
        };
        pTracer->SetEpilogues( &epilogCbs );

        // enable the tracer
        pTracer->SetEnabled( true );

        // signal the event(s) from the device and wait for completion
        pCommandList->AppendSignalEvent( pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );
        pEvent->Reset();

        pCommandList->AppendSignalEvent( pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );
        pEvent->Reset();

    }
    catch( const xe::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}