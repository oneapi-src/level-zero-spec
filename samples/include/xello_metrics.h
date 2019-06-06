#include "xello_init.h"
#include "xet_api.hpp"

//////////////////////////////////////////////////////////////////////////
inline bool init_xet( void )
{
    if( !init_xe() )
        return false;

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
inline xet::MetricGroup* findMetricGroup( xet::DeviceGroup* pDeviceGroup,
    const xet::MetricGroup::sampling_type_t type,
    const char* name = "" )
{
    uint32_t groupCount = 0;
    xet::MetricGroup::Get( pDeviceGroup, &groupCount, nullptr );

    std::vector< xet::MetricGroup*> metricGroups( groupCount );
    xet::MetricGroup::Get( pDeviceGroup, &groupCount, metricGroups.data() );

    xet::MetricGroup* found = nullptr;

    // for each device group, find the first one matching the type
    for( uint32_t grp = 0; grp < groupCount; ++grp )
    {
        auto pMetricGroup = metricGroups[ grp ];
        auto metric_properties = pMetricGroup->GetProperties();

        if( 0 != ( static_cast<uint32_t>(type) & static_cast<uint32_t>(metric_properties.samplingType) ) )
        {
            if( ( 0 == strlen(name) ) || ( 0 == strcmp( name, metric_properties.name ) ) )
            {
                found = pMetricGroup;

                std::cout << "Found " << xet::to_string( type ) << " metric group..." << "\n";
                std::cout << xet::to_string( metric_properties ) << "\n";
            }
        }
    }
    if( !found )
    {
        std::cout << "Did NOT find matching " << xet::to_string( type ) << " device group!" << "\n";
    }

    return found;
}
