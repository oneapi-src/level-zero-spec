/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "xello_metrics.h"

//////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    if( argparse( argc, argv, "-null", "--enable_null_driver" ) )
    {
        putenv( const_cast<char *>( "XE_ENABLE_NULL_DRIVER=1" ) );
    }

    const xe::Driver::device_type_t type = xe::Driver::device_type_t::GPU;

    xet::Driver* pDriver = nullptr;
    xet::Device* pDevice = nullptr;
    if( init_xe() && init_xet() )
    {
        uint32_t driverCount = 0;
        xe::GetDrivers( &driverCount );

        std::vector<xe::Driver*> drivers( driverCount );
        xe::GetDrivers( &driverCount, drivers.data() );

        for( uint32_t driver = 0; driver < driverCount; ++driver )
        {
            pDriver = reinterpret_cast<xet::Driver*>( drivers[driver] );
            pDevice = reinterpret_cast<xet::Device*>( findDevice( pDriver, type ) );
            if( pDevice )
            {
                break;
            }
        }
    }
    if( !pDevice )
        return -1;

    // Find an event-based metric group
    auto pMetricGroup = findMetricGroup( pDevice, xet::MetricGroup::sampling_type_t::EVENT_BASED );
    if( !pMetricGroup )
        return -1;

    try
    {
        // Active the metric group on the device
        pDevice->ActivateMetricGroups( 1, &pMetricGroup );

        // Create an immediate command list for direct submission
        xe::CommandQueue::desc_t queue_desc;
        auto pCommandList = std::shared_ptr<xet::CommandList>(
            reinterpret_cast<xet::CommandList*>( xe::CommandList::CreateImmediate( pDevice, &queue_desc ) ),
            []( xet::CommandList* p ){ xe::CommandList::Destroy( reinterpret_cast<xe::CommandList*>( p ) ); } );

        // Create an event to be signaled by the device
        uint32_t numSamples = 1;
        xe::EventPool::desc_t pool_desc;
        pool_desc.flags = xe::EventPool::flag_t::HOST_VISIBLE;
        pool_desc.count = numSamples;
        auto pEventPool = std::shared_ptr<xe::EventPool>(
            xe::EventPool::Create( pDriver, &pool_desc, 0, nullptr ),
            []( xe::EventPool* p ){ xe::EventPool::Destroy( p ); } );

        xe::Event::desc_t event_desc;
        event_desc.signal = xe::Event::scope_flag_t::HOST;
        event_desc.index = 0;
        auto pEvent = std::shared_ptr<xe::Event>(
            xe::Event::Create( pEventPool.get(), &event_desc ),
            []( xe::Event* p ){ xe::Event::Destroy( p ); } );

        // Create metric query
        xet::MetricQueryPool::desc_t query_pool_desc;
        query_pool_desc.count = numSamples;
        auto pQueryPool = std::shared_ptr<xet::MetricQueryPool>(
            xet::MetricQueryPool::Create( pDevice, pMetricGroup, &query_pool_desc ),
            []( xet::MetricQueryPool* p ){ xet::MetricQueryPool::Destroy( p ); } );

        auto pQuery = std::shared_ptr<xet::MetricQuery>(
            xet::MetricQuery::Create( pQueryPool.get(), 0 ),
            []( xet::MetricQuery* p ){ xet::MetricQuery::Destroy( p ); } );

        // Sample data from device and wait for completion
        pCommandList->AppendMetricQueryBegin( pQuery.get() );
        pCommandList->AppendMetricQueryEnd( pQuery.get(), pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );

        calculateResults( pMetricGroup, pQuery.get() );
    }
    catch( const xe::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}