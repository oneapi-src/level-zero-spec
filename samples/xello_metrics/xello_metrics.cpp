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

    xet::DeviceGroup* pDeviceGroup = nullptr;
    if( init_xet() )
        pDeviceGroup = reinterpret_cast<xet::DeviceGroup*>( findDeviceGroup( xe::DeviceGroup::device_type_t::GPU ) );
    if( !pDeviceGroup )
        return -1;

    // Find an event-based metric group
    auto pMetricGroup = findMetricGroup( pDeviceGroup, xet::MetricGroup::sampling_type_t::EVENT_BASED );
    if( !pMetricGroup )
        return -1;

    try
    {
        // Get the first device within the device group
        xet::Device* pDevice = nullptr;
        uint32_t deviceCount = 1;
        xe::Device::Get( reinterpret_cast<xe::DeviceGroup*>( pDeviceGroup ), &deviceCount, reinterpret_cast<xe::Device**>( &pDevice ) );

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
            xe::EventPool::Create( reinterpret_cast<xe::DeviceGroup*>( pDeviceGroup ), &pool_desc, 0, nullptr ),
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

        // Read raw data from query
        size_t rawDataSize = 0;
        pQuery->GetData( &rawDataSize, nullptr );
        std::vector<uint8_t> rawData( rawDataSize );
        pQuery->GetData( &rawDataSize, rawData.data() );

        // Calculate results
        uint32_t calcDataCount = 0;
        xet::MetricGroup::CalculateData( pMetricGroup, rawDataSize, rawData.data(), &calcDataCount, nullptr );
        std::vector<xet::typed_value_t> calcData( pMetricGroup->GetProperties().reportSize * calcDataCount );
        xet::MetricGroup::CalculateData( pMetricGroup, rawDataSize, rawData.data(), &calcDataCount, calcData.data() );

        // Report results
        std::cout << "Compute Basic results:\n";
        for( auto& entry : calcData )
        {
            std::cout << xet::to_string( entry );
        }
    }
    catch( const xe::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}