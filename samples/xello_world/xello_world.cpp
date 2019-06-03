#include <stdlib.h>
#include "xe_api.hpp"
#include <iostream>

int main()
{
    if( 0 )
    {
        // for testing purposes
        putenv( const_cast<char *>( "XE_ENABLE_NULL_DRIVER=1" ) );
        putenv( const_cast<char *>( "XE_ENABLE_LOADER_INTERCEPT=1" ) );
        putenv( const_cast<char *>( "XE_ENABLE_VALIDATION_LAYER=1" ) );
        putenv( const_cast<char *>( "XE_ENABLE_PARAMETER_VALIDATION=1" ) );
    }

    try
    {
        // Initialize the driver
        xe::Init( xe::init_flag_t::NONE );
        std::cout << "Driver initialized\n";
    }
    catch( const xe::exception_t& e)
    {
        std::cout << "Driver not initialized!\n";
        std::cout << e.what();
        return -1;
    }

    // Get the first device group
    uint32_t groupCount = 0;
    xe::DeviceGroup::Get( &groupCount, nullptr );

    auto ppDeviceGroup = new xe::DeviceGroup*[ groupCount ];
    xe::DeviceGroup::Get( &groupCount, ppDeviceGroup );

    for( uint32_t grp = 0; grp < groupCount; ++grp )
    {
        auto pDeviceGroup = ppDeviceGroup[ grp ];

        std::cout << "Driver version: " << pDeviceGroup->GetDriverVersion() << "\n";
        std::cout << "API version: " << std::to_string( pDeviceGroup->GetApiVersion() ) << "\n";

        auto device_properties = pDeviceGroup->GetDeviceProperties();
        std::cout << std::to_string( device_properties ) << "\n";

        auto compute_properties = pDeviceGroup->GetComputeProperties();
        std::cout << std::to_string( compute_properties ) << "\n";

        uint32_t memoryCount = 0;
        pDeviceGroup->GetMemoryProperties( &memoryCount, nullptr );
        auto pMemoryProperties = new xe::DeviceGroup::device_memory_properties_t[ memoryCount ];
        pDeviceGroup->GetMemoryProperties( &memoryCount, pMemoryProperties );
        for( uint32_t mem = 0; mem < memoryCount; ++mem )
        {
            std::cout << std::to_string( pMemoryProperties[ mem ] ) << "\n";
        }

        auto memory_access_properties = pDeviceGroup->GetMemoryAccessProperties();
        std::cout << std::to_string( memory_access_properties ) << "\n";

        auto cache_properties = pDeviceGroup->GetCacheProperties();
        std::cout << std::to_string( cache_properties ) << "\n";

        auto image_properties = pDeviceGroup->GetImageProperties();
        std::cout << std::to_string( image_properties ) << "\n";
    }

    // Get the first device within the device group
    uint32_t deviceCount = 1;
    xe::Device* pDevice = nullptr;
    xe::Device::Get( ppDeviceGroup[ 0 ], &deviceCount, &pDevice );

    delete[] ppDeviceGroup;
    return 0;
}