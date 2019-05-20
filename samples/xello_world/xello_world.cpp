#include <stdlib.h>
#include "xe_api.h"

int main()
{
    putenv( "XE_ENABLE_VALIDATION_LAYER=1" );
    putenv( "XE_ENABLE_PARAMETER_VALIDATION=1" );

    // Initialize the driver
    xeInit( XE_INIT_FLAG_NONE );

    // Discover all the device groups and devices
    uint32_t groupCount = 0;
    xeGetDeviceGroups( &groupCount, nullptr );
    xe_device_group_handle_t* arrDeviceGroups = (xe_device_group_handle_t*)
        malloc( groupCount * sizeof( xe_device_group_handle_t ) );
    xeGetDeviceGroups( &groupCount, arrDeviceGroups );

    // Query device group properties
    uint32_t i = 0;
    for( ; i < groupCount; ++i )
    {
        xe_device_properties_t device_properties;
        xeDeviceGroupGetProperties( arrDeviceGroups[ i ], &device_properties );
        //if( XE_DEVICE_TYPE_GPU == device_properties.type )
        //    break;
    }

    if( i == groupCount )
        return 0; // no GPU devices found

    // Get all the devices within the device group
    uint32_t deviceCount = 0;
    xeDeviceGroupGetDevices( arrDeviceGroups[ i ], &deviceCount, nullptr );
    xe_device_handle_t* arrDevices = (xe_device_handle_t*)
        malloc( deviceCount * sizeof( xe_device_handle_t ) );
    xeDeviceGroupGetDevices( arrDeviceGroups[ i ], &deviceCount, arrDevices );

    return 0;
}