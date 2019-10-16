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
#include "ze_api.hpp"
#include "zex_api.hpp"
#include "zet_api.hpp"

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
inline bool init_ze( void )
{
    try
    {
        // Initialize the driver
        ze::Init( ze::init_flag_t::NONE );
        std::cout << "Driver initialized.\n";
    }
    catch( const ze::exception_t& e )
    {
        std::cout << "Driver not initialized!\n";
        std::cout << e.what();
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
inline bool init_zex( void )
{
    try
    {
        // Initialize the driver
        zex::Init( ze::init_flag_t::NONE );
        std::cout << "Experimental Driver initialized.\n";
    }
    catch( const ze::exception_t& e )
    {
        std::cout << "Experimental Driver not initialized!\n";
        std::cout << e.what();
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
inline bool init_zet( void )
{
    try
    {
        // Initialize the driver
        zet::Init( ze::init_flag_t::NONE );
        std::cout << "Tools initialized.\n";
    }
    catch( const ze::exception_t& e )
    {
        std::cout << "Tools not initialized!\n";
        std::cout << e.what();
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
inline ze::Device* findDevice(
    ze::Driver* pDriver,
    const ze::Driver::device_type_t type )
{
    // get all devices
    uint32_t deviceCount = 0;
    ze::Device::Get( pDriver, &deviceCount );

    std::vector<ze::Device*> devices( deviceCount );
    ze::Device::Get( pDriver, &deviceCount, devices.data() );

    ze::Device* found = nullptr;

    // for each device, find the first one matching the type
    for( uint32_t device = 0; device < deviceCount; ++device )
    {
        auto pDevice = devices[device];

        ze::Device::properties_t device_properties;
        pDevice->GetProperties( &device_properties );

        if( type == device_properties.type )
        {
            found = pDevice;

            std::cout << "Found "<< ze::to_string(type) << " device..." << "\n";
            std::cout << "Driver version: " << pDriver->GetDriverVersion() << "\n";
            std::cout << "API version: " << ze::to_string( pDriver->GetApiVersion() ) << "\n";

            std::cout << ze::to_string( device_properties ) << "\n";

            ze::Device::compute_properties_t compute_properties;
            pDevice->GetComputeProperties( &compute_properties );
            std::cout << ze::to_string( compute_properties ) << "\n";

            uint32_t memoryCount = 0;
            pDevice->GetMemoryProperties( &memoryCount );
            auto pMemoryProperties = new ze::Device::memory_properties_t[ memoryCount ];
            pDevice->GetMemoryProperties( &memoryCount, pMemoryProperties );
            for( uint32_t mem = 0; mem < memoryCount; ++mem )
            {
                std::cout << ze::to_string( pMemoryProperties[ mem ] ) << "\n";
            }
            delete[] pMemoryProperties;

            ze::Device::memory_access_properties_t memory_access_properties;
            pDevice->GetMemoryAccessProperties( &memory_access_properties );
            std::cout << ze::to_string( memory_access_properties ) << "\n";

            ze::Device::cache_properties_t cache_properties;
            pDevice->GetCacheProperties( &cache_properties );
            std::cout << ze::to_string( cache_properties ) << "\n";

            ze::Device::image_properties_t image_properties;
            pDevice->GetImageProperties( &image_properties );
            std::cout << ze::to_string( image_properties ) << "\n";

            break;
        }
    }

    return found;
}
