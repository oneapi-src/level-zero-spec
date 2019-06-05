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

    xe::DeviceGroup* pDeviceGroup = nullptr;
    if( init() )
        pDeviceGroup = findDeviceGroup( xe::DeviceGroup::device_type_t::GPU );

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