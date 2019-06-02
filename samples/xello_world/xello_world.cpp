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

    // Initialize the driver
    xe::Init( xe::init_flag_t::NONE );
    std::cout << "Driver initialized\n";

    // Get the first device group
    uint32_t groupCount = 1;
    xe::DeviceGroup* pDeviceGroup = nullptr;
    xe::DeviceGroup::Get( &groupCount, &pDeviceGroup );

    auto device_properties = pDeviceGroup->GetProperties();
    // todo: to_string( device_properties );

    auto compute_properties = pDeviceGroup->GetComputeProperties();
    // todo: to_string( compute_properties );

    // Get the first device within the device group
    uint32_t deviceCount = 1;
    xe::Device* pDevice = nullptr;
    xe::Device::Get( pDeviceGroup, &deviceCount, &pDevice );

    return 0;
}