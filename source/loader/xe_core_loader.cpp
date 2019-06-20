/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_core_loader.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/ldrddi.cpp.mako
 * @endcond
 *
 */
#include "xe_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    xe_device_group_factory_t           xe_device_group_factory;
    xe_device_factory_t                 xe_device_factory;
    xe_command_queue_factory_t          xe_command_queue_factory;
    xe_command_list_factory_t           xe_command_list_factory;
    xe_fence_factory_t                  xe_fence_factory;
    xe_event_pool_factory_t             xe_event_pool_factory;
    xe_event_factory_t                  xe_event_factory;
    xe_image_factory_t                  xe_image_factory;
    xe_module_factory_t                 xe_module_factory;
    xe_module_build_log_factory_t       xe_module_build_log_factory;
    xe_function_factory_t               xe_function_factory;
    xe_sampler_factory_t                xe_sampler_factory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeInit
    xe_result_t __xecall
    xeInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        for( auto& drv : context.drivers )
        {
            if( XE_RESULT_SUCCESS == result )
            {
                result = drv.dditable.xe.Global.pfnInit( flags );
            }
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetDriverVersion
    xe_result_t __xecall
    xeDeviceGroupGetDriverVersion(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
        uint32_t* version                               ///< [out] driver version
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetDriverVersion = dditable->xe.DeviceGroup.pfnGetDriverVersion;
        if( nullptr == pfnGetDriverVersion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetDriverVersion( hDeviceGroup, version );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGet
    xe_result_t __xecall
    xeDeviceGroupGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of device groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< device groups.
                                                        ///< if count is larger than the number of device groups available, then
                                                        ///< the driver will update the value with the correct number of device
                                                        ///< groups available.
        xe_device_group_handle_t* phDeviceGroups        ///< [in,out][optional][range(0, *pCount)] array of handle of device groups
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        uint32_t total_count = 0;

        for( auto& drv : context.drivers )
        {
            uint32_t count = 0;

            result = drv.dditable.xe.DeviceGroup.pfnGet( &count, nullptr );
            if( XE_RESULT_SUCCESS != result ) break;

            if( ( 0 < *pCount ) && ( *pCount > total_count + count ) )
                break;

            if( nullptr != phDeviceGroups )
            {
                result = drv.dditable.xe.DeviceGroup.pfnGet( &count, &phDeviceGroups[ total_count ] );
                if( XE_RESULT_SUCCESS != result ) break;

                try
                {
                    for( uint32_t i = total_count; i < count; ++i )
                        phDeviceGroups[ i ] = reinterpret_cast<xe_device_group_handle_t>( 
                            xe_device_group_factory.getInstance( phDeviceGroups[ i ], &drv.dditable ) );
                }
                catch( std::bad_alloc& )
                {
                    result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
                }
            }

            total_count += count;
        }

        if( XE_RESULT_SUCCESS == result )
            *pCount = total_count;

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGet
    xe_result_t __xecall
    xeDeviceGet(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                        ///< if count is larger than the number of devices available, then the
                                                        ///< driver will update the value with the correct number of devices available.
        xe_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGet = dditable->xe.Device.pfnGet;
        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGet( hDeviceGroup, pCount, phDevices );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDevices ) && ( i < *pCount ); ++i )
                phDevices[ i ] = reinterpret_cast<xe_device_handle_t>(
                    xe_device_factory.getInstance( phDevices[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetSubDevices
    xe_result_t __xecall
    xeDeviceGetSubDevices(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of sub-devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                        ///< if count is larger than the number of sub-devices available, then the
                                                        ///< driver will update the value with the correct number of sub-devices available.
        xe_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnGetSubDevices = dditable->xe.Device.pfnGetSubDevices;
        if( nullptr == pfnGetSubDevices )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetSubDevices( hDevice, pCount, phSubdevices );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phSubdevices ) && ( i < *pCount ); ++i )
                phSubdevices[ i ] = reinterpret_cast<xe_device_handle_t>(
                    xe_device_factory.getInstance( phSubdevices[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetApiVersion
    xe_result_t __xecall
    xeDeviceGroupGetApiVersion(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_api_version_t* version                       ///< [out] api version
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetApiVersion = dditable->xe.DeviceGroup.pfnGetApiVersion;
        if( nullptr == pfnGetApiVersion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetApiVersion( hDeviceGroup, version );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetDeviceProperties
    xe_result_t __xecall
    xeDeviceGroupGetDeviceProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetDeviceProperties = dditable->xe.DeviceGroup.pfnGetDeviceProperties;
        if( nullptr == pfnGetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetDeviceProperties( hDeviceGroup, pDeviceProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetComputeProperties
    xe_result_t __xecall
    xeDeviceGroupGetComputeProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetComputeProperties = dditable->xe.DeviceGroup.pfnGetComputeProperties;
        if( nullptr == pfnGetComputeProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetComputeProperties( hDeviceGroup, pComputeProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetMemoryProperties
    xe_result_t __xecall
    xeDeviceGroupGetMemoryProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties supported.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of memory properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< memory properties.
                                                        ///< if count is larger than the number of memory properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< memory properties available.
        xe_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetMemoryProperties = dditable->xe.DeviceGroup.pfnGetMemoryProperties;
        if( nullptr == pfnGetMemoryProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetMemoryProperties( hDeviceGroup, pCount, pMemProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetMemoryAccessProperties
    xe_result_t __xecall
    xeDeviceGroupGetMemoryAccessProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_memory_access_properties_t* pMemAccessProperties  ///< [out] query result for memory access properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetMemoryAccessProperties = dditable->xe.DeviceGroup.pfnGetMemoryAccessProperties;
        if( nullptr == pfnGetMemoryAccessProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetMemoryAccessProperties( hDeviceGroup, pMemAccessProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetCacheProperties
    xe_result_t __xecall
    xeDeviceGroupGetCacheProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_cache_properties_t* pCacheProperties  ///< [out] query result for cache properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetCacheProperties = dditable->xe.DeviceGroup.pfnGetCacheProperties;
        if( nullptr == pfnGetCacheProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetCacheProperties( hDeviceGroup, pCacheProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetImageProperties
    xe_result_t __xecall
    xeDeviceGroupGetImageProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_image_properties_t* pImageProperties  ///< [out] query result for image properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetImageProperties = dditable->xe.DeviceGroup.pfnGetImageProperties;
        if( nullptr == pfnGetImageProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetImageProperties( hDeviceGroup, pImageProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetP2PProperties
    xe_result_t __xecall
    xeDeviceGetP2PProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnGetP2PProperties = dditable->xe.Device.pfnGetP2PProperties;
        if( nullptr == pfnGetP2PProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hPeerDevice = reinterpret_cast<xe_device_object_t*>( hPeerDevice )->handle;

        // forward to device-driver
        result = pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceCanAccessPeer
    xe_result_t __xecall
    xeDeviceCanAccessPeer(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_bool_t* value                                ///< [out] returned access capability
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCanAccessPeer = dditable->xe.Device.pfnCanAccessPeer;
        if( nullptr == pfnCanAccessPeer )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hPeerDevice = reinterpret_cast<xe_device_object_t*>( hPeerDevice )->handle;

        // forward to device-driver
        result = pfnCanAccessPeer( hDevice, hPeerDevice, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceSetIntermediateCacheConfig
    xe_result_t __xecall
    xeDeviceSetIntermediateCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnSetIntermediateCacheConfig = dditable->xe.Device.pfnSetIntermediateCacheConfig;
        if( nullptr == pfnSetIntermediateCacheConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnSetIntermediateCacheConfig( hDevice, CacheConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceSetLastLevelCacheConfig
    xe_result_t __xecall
    xeDeviceSetLastLevelCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnSetLastLevelCacheConfig = dditable->xe.Device.pfnSetLastLevelCacheConfig;
        if( nullptr == pfnSetLastLevelCacheConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnSetLastLevelCacheConfig( hDevice, CacheConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandQueueCreate
    xe_result_t __xecall
    xeCommandQueueCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xe.CommandQueue.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phCommandQueue );

        try
        {
            // convert driver handle to loader handle
            *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>(
                xe_command_queue_factory.getInstance( *phCommandQueue, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandQueueDestroy
    xe_result_t __xecall
    xeCommandQueueDestroy(
        xe_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnDestroy = dditable->xe.CommandQueue.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandQueue );

        // release loader handle
        xe_command_queue_factory.release( hCommandQueue );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandQueueExecuteCommandLists
    xe_result_t __xecall
    xeCommandQueueExecuteCommandLists(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        xe_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnExecuteCommandLists = dditable->xe.CommandQueue.pfnExecuteCommandLists;
        if( nullptr == pfnExecuteCommandLists )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phCommandLists ) && ( i < numCommandLists ); ++i )
            phCommandLists[ i ] = reinterpret_cast<xe_command_list_object_t*>( phCommandLists[ i ] )->handle;

        // convert loader handle to driver handle
        hFence = ( hFence ) ? reinterpret_cast<xe_fence_object_t*>( hFence )->handle : nullptr;

        // forward to device-driver
        result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandQueueSynchronize
    xe_result_t __xecall
    xeCommandQueueSynchronize(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnSynchronize = dditable->xe.CommandQueue.pfnSynchronize;
        if( nullptr == pfnSynchronize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnSynchronize( hCommandQueue, timeout );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListCreate
    xe_result_t __xecall
    xeCommandListCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xe.CommandList.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phCommandList );

        try
        {
            // convert driver handle to loader handle
            *phCommandList = reinterpret_cast<xe_command_list_handle_t>(
                xe_command_list_factory.getInstance( *phCommandList, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListCreateImmediate
    xe_result_t __xecall
    xeCommandListCreateImmediate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCreateImmediate = dditable->xe.CommandList.pfnCreateImmediate;
        if( nullptr == pfnCreateImmediate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreateImmediate( hDevice, altdesc, phCommandList );

        try
        {
            // convert driver handle to loader handle
            *phCommandList = reinterpret_cast<xe_command_list_handle_t>(
                xe_command_list_factory.getInstance( *phCommandList, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListDestroy
    xe_result_t __xecall
    xeCommandListDestroy(
        xe_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnDestroy = dditable->xe.CommandList.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandList );

        // release loader handle
        xe_command_list_factory.release( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListClose
    xe_result_t __xecall
    xeCommandListClose(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnClose = dditable->xe.CommandList.pfnClose;
        if( nullptr == pfnClose )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnClose( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListReset
    xe_result_t __xecall
    xeCommandListReset(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnReset = dditable->xe.CommandList.pfnReset;
        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnReset( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListSetParameter
    xe_result_t __xecall
    xeCommandListSetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to change
        uint32_t value                                  ///< [in] value of attribute
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnSetParameter = dditable->xe.CommandList.pfnSetParameter;
        if( nullptr == pfnSetParameter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnSetParameter( hCommandList, parameter, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListGetParameter
    xe_result_t __xecall
    xeCommandListGetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
        uint32_t* value                                 ///< [out] value of attribute
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnGetParameter = dditable->xe.CommandList.pfnGetParameter;
        if( nullptr == pfnGetParameter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnGetParameter( hCommandList, parameter, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListResetParameters
    xe_result_t __xecall
    xeCommandListResetParameters(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnResetParameters = dditable->xe.CommandList.pfnResetParameters;
        if( nullptr == pfnResetParameters )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnResetParameters( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendBarrier
    xe_result_t __xecall
    xeCommandListAppendBarrier(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendBarrier = dditable->xe.CommandList.pfnAppendBarrier;
        if( nullptr == pfnAppendBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<xe_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendMemoryRangesBarrier
    xe_result_t __xecall
    xeCommandListAppendMemoryRangesBarrier(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryRangesBarrier = dditable->xe.CommandList.pfnAppendMemoryRangesBarrier;
        if( nullptr == pfnAppendMemoryRangesBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<xe_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceSystemBarrier
    xe_result_t __xecall
    xeDeviceSystemBarrier(
        xe_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnSystemBarrier = dditable->xe.Device.pfnSystemBarrier;
        if( nullptr == pfnSystemBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnSystemBarrier( hDevice );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceRegisterCLMemory
    #if XE_ENABLE_OCL_INTEROP
    xe_result_t __xecall
    xeDeviceRegisterCLMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnRegisterCLMemory = dditable->xe.Device.pfnRegisterCLMemory;
        if( nullptr == pfnRegisterCLMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnRegisterCLMemory( hDevice, context, mem, ptr );

        return result;
    }
    #endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceRegisterCLProgram
    #if XE_ENABLE_OCL_INTEROP
    xe_result_t __xecall
    xeDeviceRegisterCLProgram(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnRegisterCLProgram = dditable->xe.Device.pfnRegisterCLProgram;
        if( nullptr == pfnRegisterCLProgram )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnRegisterCLProgram( hDevice, context, program, phModule );

        try
        {
            // convert driver handle to loader handle
            *phModule = reinterpret_cast<xe_module_handle_t>(
                xe_module_factory.getInstance( *phModule, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }
    #endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceRegisterCLCommandQueue
    #if XE_ENABLE_OCL_INTEROP
    xe_result_t __xecall
    xeDeviceRegisterCLCommandQueue(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnRegisterCLCommandQueue = dditable->xe.Device.pfnRegisterCLCommandQueue;
        if( nullptr == pfnRegisterCLCommandQueue )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );

        try
        {
            // convert driver handle to loader handle
            *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>(
                xe_command_queue_factory.getInstance( *phCommandQueue, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }
    #endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendMemoryCopy
    xe_result_t __xecall
    xeCommandListAppendMemoryCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryCopy = dditable->xe.CommandList.pfnAppendMemoryCopy;
        if( nullptr == pfnAppendMemoryCopy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<xe_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendMemorySet
    xe_result_t __xecall
    xeCommandListAppendMemorySet(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initailize
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemorySet = dditable->xe.CommandList.pfnAppendMemorySet;
        if( nullptr == pfnAppendMemorySet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<xe_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendMemoryCopyRegion
    xe_result_t __xecall
    xeCommandListAppendMemoryCopyRegion(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const xe_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const xe_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryCopyRegion = dditable->xe.CommandList.pfnAppendMemoryCopyRegion;
        if( nullptr == pfnAppendMemoryCopyRegion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<xe_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendImageCopy
    xe_result_t __xecall
    xeCommandListAppendImageCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopy = dditable->xe.CommandList.pfnAppendImageCopy;
        if( nullptr == pfnAppendImageCopy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<xe_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<xe_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<xe_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendImageCopyRegion
    xe_result_t __xecall
    xeCommandListAppendImageCopyRegion(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyRegion = dditable->xe.CommandList.pfnAppendImageCopyRegion;
        if( nullptr == pfnAppendImageCopyRegion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<xe_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<xe_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<xe_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendImageCopyToMemory
    xe_result_t __xecall
    xeCommandListAppendImageCopyToMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyToMemory = dditable->xe.CommandList.pfnAppendImageCopyToMemory;
        if( nullptr == pfnAppendImageCopyToMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<xe_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<xe_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendImageCopyFromMemory
    xe_result_t __xecall
    xeCommandListAppendImageCopyFromMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyFromMemory = dditable->xe.CommandList.pfnAppendImageCopyFromMemory;
        if( nullptr == pfnAppendImageCopyFromMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<xe_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<xe_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendMemoryPrefetch
    xe_result_t __xecall
    xeCommandListAppendMemoryPrefetch(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryPrefetch = dditable->xe.CommandList.pfnAppendMemoryPrefetch;
        if( nullptr == pfnAppendMemoryPrefetch )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendMemAdvise
    xe_result_t __xecall
    xeCommandListAppendMemAdvise(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemAdvise = dditable->xe.CommandList.pfnAppendMemAdvise;
        if( nullptr == pfnAppendMemAdvise )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolCreate
    xe_result_t __xecall
    xeEventPoolCreate(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group
        const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        xe_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices in the device group.
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnCreate = dditable->xe.EventPool.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phDevices ) && ( i < numDevices ); ++i )
            phDevices[ i ] = reinterpret_cast<xe_device_object_t*>( phDevices[ i ] )->handle;

        // forward to device-driver
        result = pfnCreate( hDeviceGroup, desc, numDevices, phDevices, phEventPool );

        try
        {
            // convert driver handle to loader handle
            *phEventPool = reinterpret_cast<xe_event_pool_handle_t>(
                xe_event_pool_factory.getInstance( *phEventPool, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolDestroy
    xe_result_t __xecall
    xeEventPoolDestroy(
        xe_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnDestroy = dditable->xe.EventPool.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnDestroy( hEventPool );

        // release loader handle
        xe_event_pool_factory.release( hEventPool );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventCreate
    xe_result_t __xecall
    xeEventCreate(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnCreate = dditable->xe.Event.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnCreate( hEventPool, desc, phEvent );

        try
        {
            // convert driver handle to loader handle
            *phEvent = reinterpret_cast<xe_event_handle_t>(
                xe_event_factory.getInstance( *phEvent, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventDestroy
    xe_result_t __xecall
    xeEventDestroy(
        xe_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_object_t*>( hEvent )->dditable;
        auto pfnDestroy = dditable->xe.Event.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<xe_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnDestroy( hEvent );

        // release loader handle
        xe_event_factory.release( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolGetIpcHandle
    xe_result_t __xecall
    xeEventPoolGetIpcHandle(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnGetIpcHandle = dditable->xe.EventPool.pfnGetIpcHandle;
        if( nullptr == pfnGetIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnGetIpcHandle( hEventPool, phIpc );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolOpenIpcHandle
    xe_result_t __xecall
    xeEventPoolOpenIpcHandle(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
        xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnOpenIpcHandle = dditable->xe.EventPool.pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnOpenIpcHandle( hDevice, hIpc, phEventPool );

        try
        {
            // convert driver handle to loader handle
            *phEventPool = reinterpret_cast<xe_event_pool_handle_t>(
                xe_event_pool_factory.getInstance( *phEventPool, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolCloseIpcHandle
    xe_result_t __xecall
    xeEventPoolCloseIpcHandle(
        xe_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnCloseIpcHandle = dditable->xe.EventPool.pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<xe_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnCloseIpcHandle( hEventPool );

        // release loader handle
        xe_event_pool_factory.release( hEventPool );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendSignalEvent
    xe_result_t __xecall
    xeCommandListAppendSignalEvent(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendSignalEvent = dditable->xe.CommandList.pfnAppendSignalEvent;
        if( nullptr == pfnAppendSignalEvent )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<xe_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnAppendSignalEvent( hCommandList, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendWaitOnEvents
    xe_result_t __xecall
    xeCommandListAppendWaitOnEvents(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        xe_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                        ///< continuing
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendWaitOnEvents = dditable->xe.CommandList.pfnAppendWaitOnEvents;
        if( nullptr == pfnAppendWaitOnEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phEvents ) && ( i < numEvents ); ++i )
            phEvents[ i ] = reinterpret_cast<xe_event_object_t*>( phEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventHostSignal
    xe_result_t __xecall
    xeEventHostSignal(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_object_t*>( hEvent )->dditable;
        auto pfnHostSignal = dditable->xe.Event.pfnHostSignal;
        if( nullptr == pfnHostSignal )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<xe_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnHostSignal( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventHostSynchronize
    xe_result_t __xecall
    xeEventHostSynchronize(
        xe_event_handle_t hEvent,                       ///< [in] handle of the event
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_object_t*>( hEvent )->dditable;
        auto pfnHostSynchronize = dditable->xe.Event.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<xe_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnHostSynchronize( hEvent, timeout );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventQueryStatus
    xe_result_t __xecall
    xeEventQueryStatus(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_object_t*>( hEvent )->dditable;
        auto pfnQueryStatus = dditable->xe.Event.pfnQueryStatus;
        if( nullptr == pfnQueryStatus )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<xe_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnQueryStatus( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendEventReset
    xe_result_t __xecall
    xeCommandListAppendEventReset(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendEventReset = dditable->xe.CommandList.pfnAppendEventReset;
        if( nullptr == pfnAppendEventReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<xe_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnAppendEventReset( hCommandList, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventReset
    xe_result_t __xecall
    xeEventReset(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_event_object_t*>( hEvent )->dditable;
        auto pfnReset = dditable->xe.Event.pfnReset;
        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<xe_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnReset( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceCreate
    xe_result_t __xecall
    xeFenceCreate(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnCreate = dditable->xe.Fence.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnCreate( hCommandQueue, desc, phFence );

        try
        {
            // convert driver handle to loader handle
            *phFence = reinterpret_cast<xe_fence_handle_t>(
                xe_fence_factory.getInstance( *phFence, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceDestroy
    xe_result_t __xecall
    xeFenceDestroy(
        xe_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_fence_object_t*>( hFence )->dditable;
        auto pfnDestroy = dditable->xe.Fence.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<xe_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnDestroy( hFence );

        // release loader handle
        xe_fence_factory.release( hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceHostSynchronize
    xe_result_t __xecall
    xeFenceHostSynchronize(
        xe_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_fence_object_t*>( hFence )->dditable;
        auto pfnHostSynchronize = dditable->xe.Fence.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<xe_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnHostSynchronize( hFence, timeout );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceQueryStatus
    xe_result_t __xecall
    xeFenceQueryStatus(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_fence_object_t*>( hFence )->dditable;
        auto pfnQueryStatus = dditable->xe.Fence.pfnQueryStatus;
        if( nullptr == pfnQueryStatus )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<xe_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnQueryStatus( hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceReset
    xe_result_t __xecall
    xeFenceReset(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_fence_object_t*>( hFence )->dditable;
        auto pfnReset = dditable->xe.Fence.pfnReset;
        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<xe_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnReset( hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeImageGetProperties
    xe_result_t __xecall
    xeImageGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnGetProperties = dditable->xe.Image.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDevice, desc, pImageProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeImageCreate
    xe_result_t __xecall
    xeImageCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xe.Image.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phImage );

        try
        {
            // convert driver handle to loader handle
            *phImage = reinterpret_cast<xe_image_handle_t>(
                xe_image_factory.getInstance( *phImage, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeImageDestroy
    xe_result_t __xecall
    xeImageDestroy(
        xe_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_image_object_t*>( hImage )->dditable;
        auto pfnDestroy = dditable->xe.Image.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<xe_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnDestroy( hImage );

        // release loader handle
        xe_image_factory.release( hImage );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupAllocSharedMem
    xe_result_t __xecall
    xeDeviceGroupAllocSharedMem(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_handle_t hDevice,                     ///< [in] handle of a device
        xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGroupGetMemoryProperties
        xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnAllocSharedMem = dditable->xe.DeviceGroup.pfnAllocSharedMem;
        if( nullptr == pfnAllocSharedMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnAllocSharedMem( hDeviceGroup, hDevice, device_flags, ordinal, host_flags, size, alignment, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupAllocDeviceMem
    xe_result_t __xecall
    xeDeviceGroupAllocDeviceMem(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGroupGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnAllocDeviceMem = dditable->xe.DeviceGroup.pfnAllocDeviceMem;
        if( nullptr == pfnAllocDeviceMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnAllocDeviceMem( hDeviceGroup, hDevice, flags, ordinal, size, alignment, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupAllocHostMem
    xe_result_t __xecall
    xeDeviceGroupAllocHostMem(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnAllocHostMem = dditable->xe.DeviceGroup.pfnAllocHostMem;
        if( nullptr == pfnAllocHostMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnAllocHostMem( hDeviceGroup, flags, size, alignment, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupFreeMem
    xe_result_t __xecall
    xeDeviceGroupFreeMem(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnFreeMem = dditable->xe.DeviceGroup.pfnFreeMem;
        if( nullptr == pfnFreeMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnFreeMem( hDeviceGroup, ptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetMemProperties
    xe_result_t __xecall
    xeDeviceGroupGetMemProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        const void* ptr,                                ///< [in] memory pointer to query
        xe_memory_allocation_properties_t* pMemProperties,  ///< [out] query result for memory allocation properties
        xe_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetMemProperties = dditable->xe.DeviceGroup.pfnGetMemProperties;
        if( nullptr == pfnGetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetMemProperties( hDeviceGroup, ptr, pMemProperties, phDevice );

        try
        {
            // convert driver handle to loader handle
            if( nullptr != phDevice )
                *phDevice = reinterpret_cast<xe_device_handle_t>(
                    xe_device_factory.getInstance( *phDevice, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetMemAddressRange
    xe_result_t __xecall
    xeDeviceGroupGetMemAddressRange(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetMemAddressRange = dditable->xe.DeviceGroup.pfnGetMemAddressRange;
        if( nullptr == pfnGetMemAddressRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetMemAddressRange( hDeviceGroup, ptr, pBase, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetMemIpcHandle
    xe_result_t __xecall
    xeDeviceGroupGetMemIpcHandle(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnGetMemIpcHandle = dditable->xe.DeviceGroup.pfnGetMemIpcHandle;
        if( nullptr == pfnGetMemIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnGetMemIpcHandle( hDeviceGroup, ptr, pIpcHandle );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupOpenMemIpcHandle
    xe_result_t __xecall
    xeDeviceGroupOpenMemIpcHandle(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnOpenMemIpcHandle = dditable->xe.DeviceGroup.pfnOpenMemIpcHandle;
        if( nullptr == pfnOpenMemIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnOpenMemIpcHandle( hDeviceGroup, hDevice, handle, flags, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupCloseMemIpcHandle
    xe_result_t __xecall
    xeDeviceGroupCloseMemIpcHandle(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->dditable;
        auto pfnCloseMemIpcHandle = dditable->xe.DeviceGroup.pfnCloseMemIpcHandle;
        if( nullptr == pfnCloseMemIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDeviceGroup = reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup )->handle;

        // forward to device-driver
        result = pfnCloseMemIpcHandle( hDeviceGroup, ptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleCreate
    xe_result_t __xecall
    xeModuleCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        xe_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xe.Module.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phModule, phBuildLog );

        try
        {
            // convert driver handle to loader handle
            *phModule = reinterpret_cast<xe_module_handle_t>(
                xe_module_factory.getInstance( *phModule, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        try
        {
            // convert driver handle to loader handle
            if( nullptr != phBuildLog )
                *phBuildLog = reinterpret_cast<xe_module_build_log_handle_t>(
                    xe_module_build_log_factory.getInstance( *phBuildLog, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleDestroy
    xe_result_t __xecall
    xeModuleDestroy(
        xe_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_module_object_t*>( hModule )->dditable;
        auto pfnDestroy = dditable->xe.Module.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<xe_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnDestroy( hModule );

        // release loader handle
        xe_module_factory.release( hModule );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleBuildLogDestroy
    xe_result_t __xecall
    xeModuleBuildLogDestroy(
        xe_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_module_build_log_object_t*>( hModuleBuildLog )->dditable;
        auto pfnDestroy = dditable->xe.ModuleBuildLog.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModuleBuildLog = reinterpret_cast<xe_module_build_log_object_t*>( hModuleBuildLog )->handle;

        // forward to device-driver
        result = pfnDestroy( hModuleBuildLog );

        // release loader handle
        xe_module_build_log_factory.release( hModuleBuildLog );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleBuildLogGetString
    xe_result_t __xecall
    xeModuleBuildLogGetString(
        xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_module_build_log_object_t*>( hModuleBuildLog )->dditable;
        auto pfnGetString = dditable->xe.ModuleBuildLog.pfnGetString;
        if( nullptr == pfnGetString )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModuleBuildLog = reinterpret_cast<xe_module_build_log_object_t*>( hModuleBuildLog )->handle;

        // forward to device-driver
        result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleGetNativeBinary
    xe_result_t __xecall
    xeModuleGetNativeBinary(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_module_object_t*>( hModule )->dditable;
        auto pfnGetNativeBinary = dditable->xe.Module.pfnGetNativeBinary;
        if( nullptr == pfnGetNativeBinary )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<xe_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleGetGlobalPointer
    xe_result_t __xecall
    xeModuleGetGlobalPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        const char* pGlobalName,                        ///< [in] name of function in global
        void** pptr                                     ///< [out] device visible pointer
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_module_object_t*>( hModule )->dditable;
        auto pfnGetGlobalPointer = dditable->xe.Module.pfnGetGlobalPointer;
        if( nullptr == pfnGetGlobalPointer )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<xe_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetGlobalPointer( hModule, pGlobalName, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionCreate
    xe_result_t __xecall
    xeFunctionCreate(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const xe_function_desc_t* desc,                 ///< [in] pointer to function descriptor
        xe_function_handle_t* phFunction                ///< [out] handle of the Function object
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_module_object_t*>( hModule )->dditable;
        auto pfnCreate = dditable->xe.Function.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<xe_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnCreate( hModule, desc, phFunction );

        try
        {
            // convert driver handle to loader handle
            *phFunction = reinterpret_cast<xe_function_handle_t>(
                xe_function_factory.getInstance( *phFunction, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionDestroy
    xe_result_t __xecall
    xeFunctionDestroy(
        xe_function_handle_t hFunction                  ///< [in][release] handle of the function object
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_function_object_t*>( hFunction )->dditable;
        auto pfnDestroy = dditable->xe.Function.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // forward to device-driver
        result = pfnDestroy( hFunction );

        // release loader handle
        xe_function_factory.release( hFunction );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleGetFunctionPointer
    xe_result_t __xecall
    xeModuleGetFunctionPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_module_object_t*>( hModule )->dditable;
        auto pfnGetFunctionPointer = dditable->xe.Module.pfnGetFunctionPointer;
        if( nullptr == pfnGetFunctionPointer )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<xe_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionSetGroupSize
    xe_result_t __xecall
    xeFunctionSetGroupSize(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_function_object_t*>( hFunction )->dditable;
        auto pfnSetGroupSize = dditable->xe.Function.pfnSetGroupSize;
        if( nullptr == pfnSetGroupSize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // forward to device-driver
        result = pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionSuggestGroupSize
    xe_result_t __xecall
    xeFunctionSuggestGroupSize(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension.
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_function_object_t*>( hFunction )->dditable;
        auto pfnSuggestGroupSize = dditable->xe.Function.pfnSuggestGroupSize;
        if( nullptr == pfnSuggestGroupSize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // forward to device-driver
        result = pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionSetArgumentValue
    xe_result_t __xecall
    xeFunctionSetArgumentValue(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function args object.
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_function_object_t*>( hFunction )->dditable;
        auto pfnSetArgumentValue = dditable->xe.Function.pfnSetArgumentValue;
        if( nullptr == pfnSetArgumentValue )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // forward to device-driver
        result = pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionSetAttribute
    xe_result_t __xecall
    xeFunctionSetAttribute(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function.
        xe_function_set_attribute_t attr,               ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_function_object_t*>( hFunction )->dditable;
        auto pfnSetAttribute = dditable->xe.Function.pfnSetAttribute;
        if( nullptr == pfnSetAttribute )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // forward to device-driver
        result = pfnSetAttribute( hFunction, attr, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionGetAttribute
    xe_result_t __xecall
    xeFunctionGetAttribute(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        xe_function_get_attribute_t attr,               ///< [in] attribute to query
        uint32_t* pValue                                ///< [out] returned attribute value
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_function_object_t*>( hFunction )->dditable;
        auto pfnGetAttribute = dditable->xe.Function.pfnGetAttribute;
        if( nullptr == pfnGetAttribute )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // forward to device-driver
        result = pfnGetAttribute( hFunction, attr, pValue );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendLaunchFunction
    xe_result_t __xecall
    xeCommandListAppendLaunchFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] launch function arguments.
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchFunction = dditable->xe.CommandList.pfnAppendLaunchFunction;
        if( nullptr == pfnAppendLaunchFunction )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<xe_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendLaunchFunctionIndirect
    xe_result_t __xecall
    xeCommandListAppendLaunchFunctionIndirect(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain launch arguments
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchFunctionIndirect = dditable->xe.CommandList.pfnAppendLaunchFunctionIndirect;
        if( nullptr == pfnAppendLaunchFunctionIndirect )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hFunction = reinterpret_cast<xe_function_object_t*>( hFunction )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<xe_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendLaunchMultipleFunctionsIndirect
    xe_result_t __xecall
    xeCommandListAppendLaunchMultipleFunctionsIndirect(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
        xe_function_handle_t* phFunctions,              ///< [in][range(0, numFunctions)] handles of the function objects
        const uint32_t* pNumLaunchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of launch arguments; value must be less-than or equal-to
                                                        ///< numFunctions
        const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in][range(0, numFunctions)] pointer to device buffer that will
                                                        ///< contain a contiguous array of launch arguments
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchMultipleFunctionsIndirect = dditable->xe.CommandList.pfnAppendLaunchMultipleFunctionsIndirect;
        if( nullptr == pfnAppendLaunchMultipleFunctionsIndirect )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phFunctions ) && ( i < numFunctions ); ++i )
            phFunctions[ i ] = reinterpret_cast<xe_function_object_t*>( phFunctions[ i ] )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<xe_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendLaunchHostFunction
    xe_result_t __xecall
    xeCommandListAppendLaunchHostFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData,                                ///< [in] pointer to user data to pass to host function.
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchHostFunction = dditable->xe.CommandList.pfnAppendLaunchHostFunction;
        if( nullptr == pfnAppendLaunchHostFunction )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xe_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<xe_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceMakeMemoryResident
    xe_result_t __xecall
    xeDeviceMakeMemoryResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnMakeMemoryResident = dditable->xe.Device.pfnMakeMemoryResident;
        if( nullptr == pfnMakeMemoryResident )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnMakeMemoryResident( hDevice, ptr, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceEvictMemory
    xe_result_t __xecall
    xeDeviceEvictMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnEvictMemory = dditable->xe.Device.pfnEvictMemory;
        if( nullptr == pfnEvictMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEvictMemory( hDevice, ptr, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceMakeImageResident
    xe_result_t __xecall
    xeDeviceMakeImageResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnMakeImageResident = dditable->xe.Device.pfnMakeImageResident;
        if( nullptr == pfnMakeImageResident )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<xe_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnMakeImageResident( hDevice, hImage );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceEvictImage
    xe_result_t __xecall
    xeDeviceEvictImage(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnEvictImage = dditable->xe.Device.pfnEvictImage;
        if( nullptr == pfnEvictImage )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<xe_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnEvictImage( hDevice, hImage );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeSamplerCreate
    xe_result_t __xecall
    xeSamplerCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xe.Sampler.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phSampler );

        try
        {
            // convert driver handle to loader handle
            *phSampler = reinterpret_cast<xe_sampler_handle_t>(
                xe_sampler_factory.getInstance( *phSampler, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeSamplerDestroy
    xe_result_t __xecall
    xeSamplerDestroy(
        xe_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_sampler_object_t*>( hSampler )->dditable;
        auto pfnDestroy = dditable->xe.Sampler.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hSampler = reinterpret_cast<xe_sampler_object_t*>( hSampler )->handle;

        // forward to device-driver
        result = pfnDestroy( hSampler );

        // release loader handle
        xe_sampler_factory.release( hSampler );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetGlobalProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Global );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnInit                                     = loader::xeInit;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetGlobalProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetDeviceProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Device );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xeDeviceGet;
            pDdiTable->pfnGetSubDevices                            = loader::xeDeviceGetSubDevices;
            pDdiTable->pfnGetP2PProperties                         = loader::xeDeviceGetP2PProperties;
            pDdiTable->pfnCanAccessPeer                            = loader::xeDeviceCanAccessPeer;
            pDdiTable->pfnSetIntermediateCacheConfig               = loader::xeDeviceSetIntermediateCacheConfig;
            pDdiTable->pfnSetLastLevelCacheConfig                  = loader::xeDeviceSetLastLevelCacheConfig;
            pDdiTable->pfnSystemBarrier                            = loader::xeDeviceSystemBarrier;
        #if XE_ENABLE_OCL_INTEROP
            pDdiTable->pfnRegisterCLMemory                         = loader::xeDeviceRegisterCLMemory;
        #endif
        #if XE_ENABLE_OCL_INTEROP
            pDdiTable->pfnRegisterCLProgram                        = loader::xeDeviceRegisterCLProgram;
        #endif
        #if XE_ENABLE_OCL_INTEROP
            pDdiTable->pfnRegisterCLCommandQueue                   = loader::xeDeviceRegisterCLCommandQueue;
        #endif
            pDdiTable->pfnMakeMemoryResident                       = loader::xeDeviceMakeMemoryResident;
            pDdiTable->pfnEvictMemory                              = loader::xeDeviceEvictMemory;
            pDdiTable->pfnMakeImageResident                        = loader::xeDeviceMakeImageResident;
            pDdiTable->pfnEvictImage                               = loader::xeDeviceEvictImage;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetDeviceProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_group_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetDeviceGroupProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetDeviceGroupProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.DeviceGroup );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xeDeviceGroupGet;
            pDdiTable->pfnGetDriverVersion                         = loader::xeDeviceGroupGetDriverVersion;
            pDdiTable->pfnGetApiVersion                            = loader::xeDeviceGroupGetApiVersion;
            pDdiTable->pfnGetDeviceProperties                      = loader::xeDeviceGroupGetDeviceProperties;
            pDdiTable->pfnGetComputeProperties                     = loader::xeDeviceGroupGetComputeProperties;
            pDdiTable->pfnGetMemoryProperties                      = loader::xeDeviceGroupGetMemoryProperties;
            pDdiTable->pfnGetMemoryAccessProperties                = loader::xeDeviceGroupGetMemoryAccessProperties;
            pDdiTable->pfnGetCacheProperties                       = loader::xeDeviceGroupGetCacheProperties;
            pDdiTable->pfnGetImageProperties                       = loader::xeDeviceGroupGetImageProperties;
            pDdiTable->pfnAllocSharedMem                           = loader::xeDeviceGroupAllocSharedMem;
            pDdiTable->pfnAllocDeviceMem                           = loader::xeDeviceGroupAllocDeviceMem;
            pDdiTable->pfnAllocHostMem                             = loader::xeDeviceGroupAllocHostMem;
            pDdiTable->pfnFreeMem                                  = loader::xeDeviceGroupFreeMem;
            pDdiTable->pfnGetMemProperties                         = loader::xeDeviceGroupGetMemProperties;
            pDdiTable->pfnGetMemAddressRange                       = loader::xeDeviceGroupGetMemAddressRange;
            pDdiTable->pfnGetMemIpcHandle                          = loader::xeDeviceGroupGetMemIpcHandle;
            pDdiTable->pfnOpenMemIpcHandle                         = loader::xeDeviceGroupOpenMemIpcHandle;
            pDdiTable->pfnCloseMemIpcHandle                        = loader::xeDeviceGroupCloseMemIpcHandle;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.DeviceGroup;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetDeviceGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetDeviceGroupProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandQueueProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetCommandQueueProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.CommandQueue );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeCommandQueueCreate;
            pDdiTable->pfnDestroy                                  = loader::xeCommandQueueDestroy;
            pDdiTable->pfnExecuteCommandLists                      = loader::xeCommandQueueExecuteCommandLists;
            pDdiTable->pfnSynchronize                              = loader::xeCommandQueueSynchronize;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.CommandQueue;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetCommandQueueProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetCommandListProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.CommandList );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeCommandListCreate;
            pDdiTable->pfnCreateImmediate                          = loader::xeCommandListCreateImmediate;
            pDdiTable->pfnDestroy                                  = loader::xeCommandListDestroy;
            pDdiTable->pfnClose                                    = loader::xeCommandListClose;
            pDdiTable->pfnReset                                    = loader::xeCommandListReset;
            pDdiTable->pfnSetParameter                             = loader::xeCommandListSetParameter;
            pDdiTable->pfnGetParameter                             = loader::xeCommandListGetParameter;
            pDdiTable->pfnResetParameters                          = loader::xeCommandListResetParameters;
            pDdiTable->pfnAppendBarrier                            = loader::xeCommandListAppendBarrier;
            pDdiTable->pfnAppendMemoryRangesBarrier                = loader::xeCommandListAppendMemoryRangesBarrier;
            pDdiTable->pfnAppendMemoryCopy                         = loader::xeCommandListAppendMemoryCopy;
            pDdiTable->pfnAppendMemorySet                          = loader::xeCommandListAppendMemorySet;
            pDdiTable->pfnAppendMemoryCopyRegion                   = loader::xeCommandListAppendMemoryCopyRegion;
            pDdiTable->pfnAppendImageCopy                          = loader::xeCommandListAppendImageCopy;
            pDdiTable->pfnAppendImageCopyRegion                    = loader::xeCommandListAppendImageCopyRegion;
            pDdiTable->pfnAppendImageCopyToMemory                  = loader::xeCommandListAppendImageCopyToMemory;
            pDdiTable->pfnAppendImageCopyFromMemory                = loader::xeCommandListAppendImageCopyFromMemory;
            pDdiTable->pfnAppendMemoryPrefetch                     = loader::xeCommandListAppendMemoryPrefetch;
            pDdiTable->pfnAppendMemAdvise                          = loader::xeCommandListAppendMemAdvise;
            pDdiTable->pfnAppendSignalEvent                        = loader::xeCommandListAppendSignalEvent;
            pDdiTable->pfnAppendWaitOnEvents                       = loader::xeCommandListAppendWaitOnEvents;
            pDdiTable->pfnAppendEventReset                         = loader::xeCommandListAppendEventReset;
            pDdiTable->pfnAppendLaunchFunction                     = loader::xeCommandListAppendLaunchFunction;
            pDdiTable->pfnAppendLaunchFunctionIndirect             = loader::xeCommandListAppendLaunchFunctionIndirect;
            pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect    = loader::xeCommandListAppendLaunchMultipleFunctionsIndirect;
            pDdiTable->pfnAppendLaunchHostFunction                 = loader::xeCommandListAppendLaunchHostFunction;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetCommandListProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFenceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetFenceProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Fence );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeFenceCreate;
            pDdiTable->pfnDestroy                                  = loader::xeFenceDestroy;
            pDdiTable->pfnHostSynchronize                          = loader::xeFenceHostSynchronize;
            pDdiTable->pfnQueryStatus                              = loader::xeFenceQueryStatus;
            pDdiTable->pfnReset                                    = loader::xeFenceReset;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Fence;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetFenceProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetEventPoolProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.EventPool );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeEventPoolCreate;
            pDdiTable->pfnDestroy                                  = loader::xeEventPoolDestroy;
            pDdiTable->pfnGetIpcHandle                             = loader::xeEventPoolGetIpcHandle;
            pDdiTable->pfnOpenIpcHandle                            = loader::xeEventPoolOpenIpcHandle;
            pDdiTable->pfnCloseIpcHandle                           = loader::xeEventPoolCloseIpcHandle;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.EventPool;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetEventPoolProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetEventProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Event );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeEventCreate;
            pDdiTable->pfnDestroy                                  = loader::xeEventDestroy;
            pDdiTable->pfnHostSignal                               = loader::xeEventHostSignal;
            pDdiTable->pfnHostSynchronize                          = loader::xeEventHostSynchronize;
            pDdiTable->pfnQueryStatus                              = loader::xeEventQueryStatus;
            pDdiTable->pfnReset                                    = loader::xeEventReset;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Event;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetEventProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetImageProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetImageProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Image );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::xeImageGetProperties;
            pDdiTable->pfnCreate                                   = loader::xeImageCreate;
            pDdiTable->pfnDestroy                                  = loader::xeImageDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Image;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetImageProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetModuleProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Module );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeModuleCreate;
            pDdiTable->pfnDestroy                                  = loader::xeModuleDestroy;
            pDdiTable->pfnGetNativeBinary                          = loader::xeModuleGetNativeBinary;
            pDdiTable->pfnGetGlobalPointer                         = loader::xeModuleGetGlobalPointer;
            pDdiTable->pfnGetFunctionPointer                       = loader::xeModuleGetFunctionPointer;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Module;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetModuleProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleBuildLogProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetModuleBuildLogProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.ModuleBuildLog );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnDestroy                                  = loader::xeModuleBuildLogDestroy;
            pDdiTable->pfnGetString                                = loader::xeModuleBuildLogGetString;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.ModuleBuildLog;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetModuleBuildLogProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFunctionProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_function_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetFunctionProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Function );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeFunctionCreate;
            pDdiTable->pfnDestroy                                  = loader::xeFunctionDestroy;
            pDdiTable->pfnSetGroupSize                             = loader::xeFunctionSetGroupSize;
            pDdiTable->pfnSuggestGroupSize                         = loader::xeFunctionSuggestGroupSize;
            pDdiTable->pfnSetArgumentValue                         = loader::xeFunctionSetArgumentValue;
            pDdiTable->pfnSetAttribute                             = loader::xeFunctionSetAttribute;
            pDdiTable->pfnGetAttribute                             = loader::xeFunctionGetAttribute;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Function;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetFunctionProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetSamplerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xeGetSamplerProcAddrTable") );
            result = getTable( version, &drv.dditable.xe.Sampler );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xeSamplerCreate;
            pDdiTable->pfnDestroy                                  = loader::xeSamplerDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xe.Sampler;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xeGetSamplerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
