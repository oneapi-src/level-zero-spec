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

    xe_device_group_handle_t* allDeviceGroups = (xe_device_group_handle_t*)
        malloc( groupCount * sizeof( xe_device_group_handle_t ) );
    xeGetDeviceGroups( &groupCount, allDeviceGroups );


    // Find the first GPU device group
    xe_device_group_handle_t hDeviceGroup = nullptr;
    for( uint32_t i = 0; i < groupCount; ++i )
    {
        xe_device_properties_t device_properties;
        xeDeviceGroupGetProperties( allDeviceGroups[ i ], &device_properties );

        if( XE_DEVICE_TYPE_GPU == device_properties.type )
        {
            hDeviceGroup = allDeviceGroups[ i ];
            break;
        }
    }
    if( nullptr == hDeviceGroup )
        return 0; // no GPU devices found


    // Get the first device within the device group
    xe_device_handle_t hDevice = nullptr;
    uint32_t deviceCount = 1;
    xeDeviceGroupGetDevices( hDeviceGroup, &deviceCount, &hDevice );

    return 0;
}