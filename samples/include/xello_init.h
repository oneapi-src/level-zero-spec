#pragma once
#include <vector>
#include <iostream>
#include "xe_api.hpp"
#include "xet_api.hpp"

//////////////////////////////////////////////////////////////////////////
inline bool argparse( int argc, char *argv[],
    const char *shortName, const char *longName )
{
    char **arg = &argv[ 1 ];
    char **argE = &argv[ argc ];

    for( ; arg != argE; ++arg )
        if( ( 0 == strcmp( *arg, shortName ) ) || ( 0 == strcmp( *arg, longName ) ) )
            return true;

    return false;
}

//////////////////////////////////////////////////////////////////////////
inline bool init_xe( void )
{
    try
    {
        // Initialize the driver
        xe::Init( xe::init_flag_t::NONE );
        std::cout << "Driver initialized.\n";
    }
    catch( const xe::exception_t& e )
    {
        std::cout << "Driver not initialized!\n";
        std::cout << e.what();
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
inline bool init_xet( void )
{
    try
    {
        // Initialize the driver
        xet::Init( xe::init_flag_t::NONE );
        std::cout << "Tools initialized.\n";
    }
    catch( const xe::exception_t& e )
    {
        std::cout << "Tools not initialized!\n";
        std::cout << e.what();
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
inline xe::DeviceGroup* findDeviceGroup(
    const xe::DeviceGroup::device_type_t type )
{
    // get all device groups
    uint32_t groupCount = 0;
    xe::DeviceGroup::Get( &groupCount );

    std::vector<xe::DeviceGroup*> deviceGroups( groupCount );
    xe::DeviceGroup::Get( &groupCount, deviceGroups.data() );

    xe::DeviceGroup* found = nullptr;

    // for each device group, find the first one matching the type
    for( uint32_t grp = 0; grp < groupCount; ++grp )
    {
        auto pDeviceGroup = deviceGroups[ grp ];
        auto device_properties = pDeviceGroup->GetDeviceProperties();

        if( type == device_properties.type )
        {
            found = pDeviceGroup;

            std::cout << "Found "<< xe::to_string(type) << " device group..." << "\n";
            std::cout << "Driver version: " << pDeviceGroup->GetDriverVersion() << "\n";
            std::cout << "API version: " << xe::to_string( pDeviceGroup->GetApiVersion() ) << "\n";

            std::cout << xe::to_string( device_properties ) << "\n";

            auto compute_properties = pDeviceGroup->GetComputeProperties();
            std::cout << xe::to_string( compute_properties ) << "\n";

            uint32_t memoryCount = 0;
            pDeviceGroup->GetMemoryProperties( &memoryCount );
            auto pMemoryProperties = new xe::DeviceGroup::device_memory_properties_t[ memoryCount ];
            pDeviceGroup->GetMemoryProperties( &memoryCount, pMemoryProperties );
            for( uint32_t mem = 0; mem < memoryCount; ++mem )
            {
                std::cout << xe::to_string( pMemoryProperties[ mem ] ) << "\n";
            }
            delete[] pMemoryProperties;

            auto memory_access_properties = pDeviceGroup->GetMemoryAccessProperties();
            std::cout << xe::to_string( memory_access_properties ) << "\n";

            auto cache_properties = pDeviceGroup->GetCacheProperties();
            std::cout << xe::to_string( cache_properties ) << "\n";

            auto image_properties = pDeviceGroup->GetImageProperties();
            std::cout << xe::to_string( image_properties ) << "\n";
        }
    }
    if( !found )
    {
        std::cout << "Did NOT find matching " << xe::to_string(type) <<" device group!" << "\n";
    }

    return found;
}
