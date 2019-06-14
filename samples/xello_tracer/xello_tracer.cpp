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

    xe::DeviceGroup* pDeviceGroup = nullptr;
    if( init_xe() )
        pDeviceGroup = findDeviceGroup( xe::DeviceGroup::device_type_t::GPU );

    if( !pDeviceGroup )
        return -1;

    try
    {
        // Get the first device within the device group
        xe::Device* pDevice = nullptr;
        uint32_t deviceCount = 1;
        xe::Device::Get( pDeviceGroup, &deviceCount, &pDevice );

    }
    catch( const xe::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}