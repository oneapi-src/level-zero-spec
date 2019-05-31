#include <stdlib.h>
#include "xe_api.h"
#include <iostream>

int main()
{
    //Enable only null driver by default
    putenv( const_cast<char *>("XE_ENABLE_NULL_DRIVER=1") );
    if (getenv(const_cast<char *>("XE_ENABLE_LOADER_INTERCEPT=0")) == nullptr)
        putenv( const_cast<char *>("XE_ENABLE_LOADER_INTERCEPT=0") );
    if (getenv(const_cast<char *>("XE_ENABLE_VALIDATION_LAYER=0")) == nullptr)
        putenv( const_cast<char *>("XE_ENABLE_VALIDATION_LAYER=0") );
    if (getenv(const_cast<char *>("XE_ENABLE_PARAMETER_VALIDATION=0")) == nullptr)
        putenv( const_cast<char *>("XE_ENABLE_PARAMETER_VALIDATION=0") );

    // Initialize the driver
    xeInit( XE_INIT_FLAG_NONE );
    std::cout << "Driver initialized\n";

    // Get the first device group
    uint32_t groupCount = 1;
    xe_device_group_handle_t hDeviceGroup = nullptr;
    xeGetDeviceGroups( &groupCount, &hDeviceGroup );
    std::cout << "Number of device groups found: " << groupCount << "\n";

    xe_device_properties_t device_properties = {};
    xeDeviceGroupGetProperties( hDeviceGroup, &device_properties );
    // todo: to_string( device_properties );

    xe_device_compute_properties_t compute_properties = {};
    xeDeviceGroupGetComputeProperties( hDeviceGroup, &compute_properties );
    // todo: to_string( compute_properties );

    // Get the first device within the device group
    xe_device_handle_t hDevice = nullptr;
    uint32_t deviceCount = 1;
    xeDeviceGroupGetDevices( hDeviceGroup, &deviceCount, &hDevice );
    std::cout << "Number of devices found: " << groupCount << "\n";

    return 0;
}