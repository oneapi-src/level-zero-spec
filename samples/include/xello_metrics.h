#include "xello_init.h"
#include "xet_api.hpp"

//////////////////////////////////////////////////////////////////////////
inline xet::MetricGroup* findMetricGroup( xet::Device* pDevice,
    const xet::MetricGroup::sampling_type_t type,
    const char* name )
{
    uint32_t groupCount = 0;
    xet::MetricGroup::Get( pDevice, &groupCount, nullptr );

    auto ppMetricGroup = new xet::MetricGroup*[ groupCount ];
    xet::MetricGroup::Get( pDevice, &groupCount, ppMetricGroup );

    xet::MetricGroup* found = nullptr;

    // for each device group, find the first one matching the type
    for( uint32_t grp = 0; grp < groupCount; ++grp )
    {
        auto pMetricGroup = ppMetricGroup[ grp ];
        auto metric_properties = pMetricGroup->GetProperties();

        if( 0 != ( static_cast<uint32_t>(type) & static_cast<uint32_t>(metric_properties.samplingType) ) )
        {
            if( 0 == strcmp( name, metric_properties.name ) )
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

    delete[] ppMetricGroup;
    return found;
}
