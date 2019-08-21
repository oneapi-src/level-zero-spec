/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
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
inline xe::Device* findDevice(
    xe::Driver* pDriver,
    const xe::Driver::device_type_t type )
{
    // get all devices
    uint32_t deviceCount = 0;
    xe::Device::Get( pDriver, &deviceCount );

    std::vector<xe::Device*> devices( deviceCount );
    xe::Device::Get( pDriver, &deviceCount, devices.data() );

    xe::Device* found = nullptr;

    // for each device, find the first one matching the type
    for( uint32_t device = 0; device < deviceCount; ++device )
    {
        auto pDevice = devices[device];

        auto device_properties = pDevice->GetProperties();

        if( type == device_properties.type )
        {
            found = pDevice;

            std::cout << "Found "<< xe::to_string(type) << " device..." << "\n";
            std::cout << "Driver version: " << pDriver->GetDriverVersion() << "\n";
            std::cout << "API version: " << xe::to_string( pDriver->GetApiVersion() ) << "\n";

            std::cout << xe::to_string( device_properties ) << "\n";

            auto compute_properties = pDevice->GetComputeProperties();
            std::cout << xe::to_string( compute_properties ) << "\n";

            uint32_t memoryCount = 0;
            pDevice->GetMemoryProperties( &memoryCount );
            auto pMemoryProperties = new xe::Device::memory_properties_t[ memoryCount ];
            pDevice->GetMemoryProperties( &memoryCount, pMemoryProperties );
            for( uint32_t mem = 0; mem < memoryCount; ++mem )
            {
                std::cout << xe::to_string( pMemoryProperties[ mem ] ) << "\n";
            }
            delete[] pMemoryProperties;

            auto memory_access_properties = pDevice->GetMemoryAccessProperties();
            std::cout << xe::to_string( memory_access_properties ) << "\n";

            auto cache_properties = pDevice->GetCacheProperties();
            std::cout << xe::to_string( cache_properties ) << "\n";

            auto image_properties = pDevice->GetImageProperties();
            std::cout << xe::to_string( image_properties ) << "\n";

            break;
        }
    }

    return found;
}
