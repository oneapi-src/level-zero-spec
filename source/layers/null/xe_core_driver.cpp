/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
* The source code contained or described herein and all documents related to the  
* source code ("Material") are owned by Intel Corporation or its suppliers or  
* licensors. Title to the Material remains with Intel Corporation or its suppliers  
* and licensors. The Material contains trade secrets and proprietary and confidential  
* information of Intel or its suppliers and licensors. The Material is protected by  
* worldwide copyright and trade secret laws and treaty provisions. No part of the  
* Material may be used, copied, reproduced, modified, published, uploaded, posted  
* transmitted, distributed, or disclosed in any way without Intel's prior express  
* written permission.  
*
* No license under any patent, copyright, trade secret or other intellectual  
* property right is granted to or conferred upon you by disclosure or delivery  
* of the Materials, either expressly, by implication, inducement, estoppel  
* or otherwise. Any license under such intellectual property rights must be  
* express and approved by Intel in writing.  
* @endcond
*
* @file xe_core_driver.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_null.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeInit
    xe_result_t __xecall
    xeInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnInit = context.xePrologueCbs.Global.pfnInit;
            if( nullptr != pfnInit )
                pfnInit( flags );
        }

        if( context.enableTracing )
        {
            auto pfnInit = context.xeEpilogueCbs.Global.pfnInit;
            if( nullptr != pfnInit )
                pfnInit( flags );
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

        if( context.enableTracing )
        {
            auto pfnGetDriverVersion = context.xePrologueCbs.DeviceGroup.pfnGetDriverVersion;
            if( nullptr != pfnGetDriverVersion )
                pfnGetDriverVersion( hDeviceGroup, version );
        }

        *version = 0;

        if( context.enableTracing )
        {
            auto pfnGetDriverVersion = context.xeEpilogueCbs.DeviceGroup.pfnGetDriverVersion;
            if( nullptr != pfnGetDriverVersion )
                pfnGetDriverVersion( hDeviceGroup, version );
        }

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

        if( context.enableTracing )
        {
            auto pfnGet = context.xePrologueCbs.DeviceGroup.pfnGet;
            if( nullptr != pfnGet )
                pfnGet( pCount, phDeviceGroups );
        }

        *pCount = 1;
        if( nullptr != phDeviceGroups ) *reinterpret_cast<void**>(phDeviceGroups) = context.get();

        if( context.enableTracing )
        {
            auto pfnGet = context.xeEpilogueCbs.DeviceGroup.pfnGet;
            if( nullptr != pfnGet )
                pfnGet( pCount, phDeviceGroups );
        }

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

        if( context.enableTracing )
        {
            auto pfnGet = context.xePrologueCbs.Device.pfnGet;
            if( nullptr != pfnGet )
                pfnGet( hDeviceGroup, pCount, phDevices );
        }

        *pCount = 1;
        if( nullptr != phDevices ) *reinterpret_cast<void**>(phDevices) = context.get() ;

        if( context.enableTracing )
        {
            auto pfnGet = context.xeEpilogueCbs.Device.pfnGet;
            if( nullptr != pfnGet )
                pfnGet( hDeviceGroup, pCount, phDevices );
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

        if( context.enableTracing )
        {
            auto pfnGetSubDevices = context.xePrologueCbs.Device.pfnGetSubDevices;
            if( nullptr != pfnGetSubDevices )
                pfnGetSubDevices( hDevice, pCount, phSubdevices );
        }

        for( size_t i = 0; ( nullptr != phSubdevices ) && ( i < *pCount ); ++i )
            phSubdevices[ i ] = reinterpret_cast<xe_device_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnGetSubDevices = context.xeEpilogueCbs.Device.pfnGetSubDevices;
            if( nullptr != pfnGetSubDevices )
                pfnGetSubDevices( hDevice, pCount, phSubdevices );
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

        if( context.enableTracing )
        {
            auto pfnGetApiVersion = context.xePrologueCbs.DeviceGroup.pfnGetApiVersion;
            if( nullptr != pfnGetApiVersion )
                pfnGetApiVersion( hDeviceGroup, version );
        }

        *version = context.version;

        if( context.enableTracing )
        {
            auto pfnGetApiVersion = context.xeEpilogueCbs.DeviceGroup.pfnGetApiVersion;
            if( nullptr != pfnGetApiVersion )
                pfnGetApiVersion( hDeviceGroup, version );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetDeviceProperties = context.xePrologueCbs.DeviceGroup.pfnGetDeviceProperties;
            if( nullptr != pfnGetDeviceProperties )
                pfnGetDeviceProperties( hDeviceGroup, pDeviceProperties );
        }

        *pDeviceProperties = context.deviceProperties;

        if( context.enableTracing )
        {
            auto pfnGetDeviceProperties = context.xeEpilogueCbs.DeviceGroup.pfnGetDeviceProperties;
            if( nullptr != pfnGetDeviceProperties )
                pfnGetDeviceProperties( hDeviceGroup, pDeviceProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetComputeProperties = context.xePrologueCbs.DeviceGroup.pfnGetComputeProperties;
            if( nullptr != pfnGetComputeProperties )
                pfnGetComputeProperties( hDeviceGroup, pComputeProperties );
        }

        *pComputeProperties = context.computeProperties;

        if( context.enableTracing )
        {
            auto pfnGetComputeProperties = context.xeEpilogueCbs.DeviceGroup.pfnGetComputeProperties;
            if( nullptr != pfnGetComputeProperties )
                pfnGetComputeProperties( hDeviceGroup, pComputeProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetMemoryProperties = context.xePrologueCbs.DeviceGroup.pfnGetMemoryProperties;
            if( nullptr != pfnGetMemoryProperties )
                pfnGetMemoryProperties( hDeviceGroup, pCount, pMemProperties );
        }

        *pCount = 1;
        if( nullptr != pMemProperties ) *pMemProperties = context.memoryProperties;

        if( context.enableTracing )
        {
            auto pfnGetMemoryProperties = context.xeEpilogueCbs.DeviceGroup.pfnGetMemoryProperties;
            if( nullptr != pfnGetMemoryProperties )
                pfnGetMemoryProperties( hDeviceGroup, pCount, pMemProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetMemoryAccessProperties = context.xePrologueCbs.DeviceGroup.pfnGetMemoryAccessProperties;
            if( nullptr != pfnGetMemoryAccessProperties )
                pfnGetMemoryAccessProperties( hDeviceGroup, pMemAccessProperties );
        }

        *pMemAccessProperties = context.memoryAccessProperties;

        if( context.enableTracing )
        {
            auto pfnGetMemoryAccessProperties = context.xeEpilogueCbs.DeviceGroup.pfnGetMemoryAccessProperties;
            if( nullptr != pfnGetMemoryAccessProperties )
                pfnGetMemoryAccessProperties( hDeviceGroup, pMemAccessProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetCacheProperties = context.xePrologueCbs.DeviceGroup.pfnGetCacheProperties;
            if( nullptr != pfnGetCacheProperties )
                pfnGetCacheProperties( hDeviceGroup, pCacheProperties );
        }

        *pCacheProperties = context.cacheProperties;

        if( context.enableTracing )
        {
            auto pfnGetCacheProperties = context.xeEpilogueCbs.DeviceGroup.pfnGetCacheProperties;
            if( nullptr != pfnGetCacheProperties )
                pfnGetCacheProperties( hDeviceGroup, pCacheProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetImageProperties = context.xePrologueCbs.DeviceGroup.pfnGetImageProperties;
            if( nullptr != pfnGetImageProperties )
                pfnGetImageProperties( hDeviceGroup, pImageProperties );
        }

        *pImageProperties = context.imageProperties;

        if( context.enableTracing )
        {
            auto pfnGetImageProperties = context.xeEpilogueCbs.DeviceGroup.pfnGetImageProperties;
            if( nullptr != pfnGetImageProperties )
                pfnGetImageProperties( hDeviceGroup, pImageProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetP2PProperties = context.xePrologueCbs.Device.pfnGetP2PProperties;
            if( nullptr != pfnGetP2PProperties )
                pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
        }

        *pP2PProperties = context.p2pProperties;

        if( context.enableTracing )
        {
            auto pfnGetP2PProperties = context.xeEpilogueCbs.Device.pfnGetP2PProperties;
            if( nullptr != pfnGetP2PProperties )
                pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnCanAccessPeer = context.xePrologueCbs.Device.pfnCanAccessPeer;
            if( nullptr != pfnCanAccessPeer )
                pfnCanAccessPeer( hDevice, hPeerDevice, value );
        }

        *value = 0;

        if( context.enableTracing )
        {
            auto pfnCanAccessPeer = context.xeEpilogueCbs.Device.pfnCanAccessPeer;
            if( nullptr != pfnCanAccessPeer )
                pfnCanAccessPeer( hDevice, hPeerDevice, value );
        }

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

        if( context.enableTracing )
        {
            auto pfnSetIntermediateCacheConfig = context.xePrologueCbs.Device.pfnSetIntermediateCacheConfig;
            if( nullptr != pfnSetIntermediateCacheConfig )
                pfnSetIntermediateCacheConfig( hDevice, CacheConfig );
        }

        if( context.enableTracing )
        {
            auto pfnSetIntermediateCacheConfig = context.xeEpilogueCbs.Device.pfnSetIntermediateCacheConfig;
            if( nullptr != pfnSetIntermediateCacheConfig )
                pfnSetIntermediateCacheConfig( hDevice, CacheConfig );
        }

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

        if( context.enableTracing )
        {
            auto pfnSetLastLevelCacheConfig = context.xePrologueCbs.Device.pfnSetLastLevelCacheConfig;
            if( nullptr != pfnSetLastLevelCacheConfig )
                pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
        }

        if( context.enableTracing )
        {
            auto pfnSetLastLevelCacheConfig = context.xeEpilogueCbs.Device.pfnSetLastLevelCacheConfig;
            if( nullptr != pfnSetLastLevelCacheConfig )
                pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.CommandQueue.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phCommandQueue );
        }

        *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.CommandQueue.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phCommandQueue );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.CommandQueue.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hCommandQueue );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.CommandQueue.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hCommandQueue );
        }

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

        if( context.enableTracing )
        {
            auto pfnExecuteCommandLists = context.xePrologueCbs.CommandQueue.pfnExecuteCommandLists;
            if( nullptr != pfnExecuteCommandLists )
                pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
        }

        if( context.enableTracing )
        {
            auto pfnExecuteCommandLists = context.xeEpilogueCbs.CommandQueue.pfnExecuteCommandLists;
            if( nullptr != pfnExecuteCommandLists )
                pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
        }

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
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnSynchronize = context.xePrologueCbs.CommandQueue.pfnSynchronize;
            if( nullptr != pfnSynchronize )
                pfnSynchronize( hCommandQueue, timeout );
        }

        if( context.enableTracing )
        {
            auto pfnSynchronize = context.xeEpilogueCbs.CommandQueue.pfnSynchronize;
            if( nullptr != pfnSynchronize )
                pfnSynchronize( hCommandQueue, timeout );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.CommandList.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phCommandList );
        }

        *phCommandList = reinterpret_cast<xe_command_list_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.CommandList.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phCommandList );
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

        if( context.enableTracing )
        {
            auto pfnCreateImmediate = context.xePrologueCbs.CommandList.pfnCreateImmediate;
            if( nullptr != pfnCreateImmediate )
                pfnCreateImmediate( hDevice, altdesc, phCommandList );
        }

        *phCommandList = reinterpret_cast<xe_command_list_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreateImmediate = context.xeEpilogueCbs.CommandList.pfnCreateImmediate;
            if( nullptr != pfnCreateImmediate )
                pfnCreateImmediate( hDevice, altdesc, phCommandList );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.CommandList.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hCommandList );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.CommandList.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hCommandList );
        }

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

        if( context.enableTracing )
        {
            auto pfnClose = context.xePrologueCbs.CommandList.pfnClose;
            if( nullptr != pfnClose )
                pfnClose( hCommandList );
        }

        if( context.enableTracing )
        {
            auto pfnClose = context.xeEpilogueCbs.CommandList.pfnClose;
            if( nullptr != pfnClose )
                pfnClose( hCommandList );
        }

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

        if( context.enableTracing )
        {
            auto pfnReset = context.xePrologueCbs.CommandList.pfnReset;
            if( nullptr != pfnReset )
                pfnReset( hCommandList );
        }

        if( context.enableTracing )
        {
            auto pfnReset = context.xeEpilogueCbs.CommandList.pfnReset;
            if( nullptr != pfnReset )
                pfnReset( hCommandList );
        }

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

        if( context.enableTracing )
        {
            auto pfnSetParameter = context.xePrologueCbs.CommandList.pfnSetParameter;
            if( nullptr != pfnSetParameter )
                pfnSetParameter( hCommandList, parameter, value );
        }

        if( context.enableTracing )
        {
            auto pfnSetParameter = context.xeEpilogueCbs.CommandList.pfnSetParameter;
            if( nullptr != pfnSetParameter )
                pfnSetParameter( hCommandList, parameter, value );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetParameter = context.xePrologueCbs.CommandList.pfnGetParameter;
            if( nullptr != pfnGetParameter )
                pfnGetParameter( hCommandList, parameter, value );
        }

        if( context.enableTracing )
        {
            auto pfnGetParameter = context.xeEpilogueCbs.CommandList.pfnGetParameter;
            if( nullptr != pfnGetParameter )
                pfnGetParameter( hCommandList, parameter, value );
        }

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

        if( context.enableTracing )
        {
            auto pfnResetParameters = context.xePrologueCbs.CommandList.pfnResetParameters;
            if( nullptr != pfnResetParameters )
                pfnResetParameters( hCommandList );
        }

        if( context.enableTracing )
        {
            auto pfnResetParameters = context.xeEpilogueCbs.CommandList.pfnResetParameters;
            if( nullptr != pfnResetParameters )
                pfnResetParameters( hCommandList );
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListReserveSpace
    xe_result_t __xecall
    xeCommandListReserveSpace(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnReserveSpace = context.xePrologueCbs.CommandList.pfnReserveSpace;
            if( nullptr != pfnReserveSpace )
                pfnReserveSpace( hCommandList, size, ptr );
        }

        if( context.enableTracing )
        {
            auto pfnReserveSpace = context.xeEpilogueCbs.CommandList.pfnReserveSpace;
            if( nullptr != pfnReserveSpace )
                pfnReserveSpace( hCommandList, size, ptr );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendBarrier = context.xePrologueCbs.CommandList.pfnAppendBarrier;
            if( nullptr != pfnAppendBarrier )
                pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
        }

        if( context.enableTracing )
        {
            auto pfnAppendBarrier = context.xeEpilogueCbs.CommandList.pfnAppendBarrier;
            if( nullptr != pfnAppendBarrier )
                pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendMemoryRangesBarrier = context.xePrologueCbs.CommandList.pfnAppendMemoryRangesBarrier;
            if( nullptr != pfnAppendMemoryRangesBarrier )
                pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
        }

        if( context.enableTracing )
        {
            auto pfnAppendMemoryRangesBarrier = context.xeEpilogueCbs.CommandList.pfnAppendMemoryRangesBarrier;
            if( nullptr != pfnAppendMemoryRangesBarrier )
                pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
        }

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

        if( context.enableTracing )
        {
            auto pfnSystemBarrier = context.xePrologueCbs.Device.pfnSystemBarrier;
            if( nullptr != pfnSystemBarrier )
                pfnSystemBarrier( hDevice );
        }

        if( context.enableTracing )
        {
            auto pfnSystemBarrier = context.xeEpilogueCbs.Device.pfnSystemBarrier;
            if( nullptr != pfnSystemBarrier )
                pfnSystemBarrier( hDevice );
        }

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

        if( context.enableTracing )
        {
            auto pfnRegisterCLMemory = context.xePrologueCbs.Device.pfnRegisterCLMemory;
            if( nullptr != pfnRegisterCLMemory )
                pfnRegisterCLMemory( hDevice, context, mem, ptr );
        }

        if( context.enableTracing )
        {
            auto pfnRegisterCLMemory = context.xeEpilogueCbs.Device.pfnRegisterCLMemory;
            if( nullptr != pfnRegisterCLMemory )
                pfnRegisterCLMemory( hDevice, context, mem, ptr );
        }

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

        if( context.enableTracing )
        {
            auto pfnRegisterCLProgram = context.xePrologueCbs.Device.pfnRegisterCLProgram;
            if( nullptr != pfnRegisterCLProgram )
                pfnRegisterCLProgram( hDevice, context, program, phModule );
        }

        *phModule = reinterpret_cast<xe_module_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnRegisterCLProgram = context.xeEpilogueCbs.Device.pfnRegisterCLProgram;
            if( nullptr != pfnRegisterCLProgram )
                pfnRegisterCLProgram( hDevice, context, program, phModule );
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

        if( context.enableTracing )
        {
            auto pfnRegisterCLCommandQueue = context.xePrologueCbs.Device.pfnRegisterCLCommandQueue;
            if( nullptr != pfnRegisterCLCommandQueue )
                pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
        }

        *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnRegisterCLCommandQueue = context.xeEpilogueCbs.Device.pfnRegisterCLCommandQueue;
            if( nullptr != pfnRegisterCLCommandQueue )
                pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
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

        if( context.enableTracing )
        {
            auto pfnAppendMemoryCopy = context.xePrologueCbs.CommandList.pfnAppendMemoryCopy;
            if( nullptr != pfnAppendMemoryCopy )
                pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendMemoryCopy = context.xeEpilogueCbs.CommandList.pfnAppendMemoryCopy;
            if( nullptr != pfnAppendMemoryCopy )
                pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendMemorySet = context.xePrologueCbs.CommandList.pfnAppendMemorySet;
            if( nullptr != pfnAppendMemorySet )
                pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendMemorySet = context.xeEpilogueCbs.CommandList.pfnAppendMemorySet;
            if( nullptr != pfnAppendMemorySet )
                pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendMemoryCopyRegion
    xe_result_t __xecall
    xeCommandListAppendMemoryCopyRegion(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        xe_copy_region_t* dstRegion,                    ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        xe_copy_region_t* srcRegion,                    ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnAppendMemoryCopyRegion = context.xePrologueCbs.CommandList.pfnAppendMemoryCopyRegion;
            if( nullptr != pfnAppendMemoryCopyRegion )
                pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendMemoryCopyRegion = context.xeEpilogueCbs.CommandList.pfnAppendMemoryCopyRegion;
            if( nullptr != pfnAppendMemoryCopyRegion )
                pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendImageCopy = context.xePrologueCbs.CommandList.pfnAppendImageCopy;
            if( nullptr != pfnAppendImageCopy )
                pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendImageCopy = context.xeEpilogueCbs.CommandList.pfnAppendImageCopy;
            if( nullptr != pfnAppendImageCopy )
                pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendImageCopyRegion
    xe_result_t __xecall
    xeCommandListAppendImageCopyRegion(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnAppendImageCopyRegion = context.xePrologueCbs.CommandList.pfnAppendImageCopyRegion;
            if( nullptr != pfnAppendImageCopyRegion )
                pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendImageCopyRegion = context.xeEpilogueCbs.CommandList.pfnAppendImageCopyRegion;
            if( nullptr != pfnAppendImageCopyRegion )
                pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendImageCopyToMemory
    xe_result_t __xecall
    xeCommandListAppendImageCopyToMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnAppendImageCopyToMemory = context.xePrologueCbs.CommandList.pfnAppendImageCopyToMemory;
            if( nullptr != pfnAppendImageCopyToMemory )
                pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendImageCopyToMemory = context.xeEpilogueCbs.CommandList.pfnAppendImageCopyToMemory;
            if( nullptr != pfnAppendImageCopyToMemory )
                pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendImageCopyFromMemory
    xe_result_t __xecall
    xeCommandListAppendImageCopyFromMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnAppendImageCopyFromMemory = context.xePrologueCbs.CommandList.pfnAppendImageCopyFromMemory;
            if( nullptr != pfnAppendImageCopyFromMemory )
                pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendImageCopyFromMemory = context.xeEpilogueCbs.CommandList.pfnAppendImageCopyFromMemory;
            if( nullptr != pfnAppendImageCopyFromMemory )
                pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendMemoryPrefetch = context.xePrologueCbs.CommandList.pfnAppendMemoryPrefetch;
            if( nullptr != pfnAppendMemoryPrefetch )
                pfnAppendMemoryPrefetch( hCommandList, ptr, size );
        }

        if( context.enableTracing )
        {
            auto pfnAppendMemoryPrefetch = context.xeEpilogueCbs.CommandList.pfnAppendMemoryPrefetch;
            if( nullptr != pfnAppendMemoryPrefetch )
                pfnAppendMemoryPrefetch( hCommandList, ptr, size );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendMemAdvise = context.xePrologueCbs.CommandList.pfnAppendMemAdvise;
            if( nullptr != pfnAppendMemAdvise )
                pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
        }

        if( context.enableTracing )
        {
            auto pfnAppendMemAdvise = context.xeEpilogueCbs.CommandList.pfnAppendMemAdvise;
            if( nullptr != pfnAppendMemAdvise )
                pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.EventPool.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDeviceGroup, desc, numDevices, phDevices, phEventPool );
        }

        *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.EventPool.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDeviceGroup, desc, numDevices, phDevices, phEventPool );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.EventPool.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hEventPool );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.EventPool.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hEventPool );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.Event.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hEventPool, desc, phEvent );
        }

        *phEvent = reinterpret_cast<xe_event_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.Event.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hEventPool, desc, phEvent );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.Event.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hEvent );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.Event.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetIpcHandle = context.xePrologueCbs.EventPool.pfnGetIpcHandle;
            if( nullptr != pfnGetIpcHandle )
                pfnGetIpcHandle( hEventPool, phIpc );
        }

        if( context.enableTracing )
        {
            auto pfnGetIpcHandle = context.xeEpilogueCbs.EventPool.pfnGetIpcHandle;
            if( nullptr != pfnGetIpcHandle )
                pfnGetIpcHandle( hEventPool, phIpc );
        }

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

        if( context.enableTracing )
        {
            auto pfnOpenIpcHandle = context.xePrologueCbs.EventPool.pfnOpenIpcHandle;
            if( nullptr != pfnOpenIpcHandle )
                pfnOpenIpcHandle( hDevice, hIpc, phEventPool );
        }

        *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnOpenIpcHandle = context.xeEpilogueCbs.EventPool.pfnOpenIpcHandle;
            if( nullptr != pfnOpenIpcHandle )
                pfnOpenIpcHandle( hDevice, hIpc, phEventPool );
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

        if( context.enableTracing )
        {
            auto pfnCloseIpcHandle = context.xePrologueCbs.EventPool.pfnCloseIpcHandle;
            if( nullptr != pfnCloseIpcHandle )
                pfnCloseIpcHandle( hEventPool );
        }


        if( context.enableTracing )
        {
            auto pfnCloseIpcHandle = context.xeEpilogueCbs.EventPool.pfnCloseIpcHandle;
            if( nullptr != pfnCloseIpcHandle )
                pfnCloseIpcHandle( hEventPool );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendSignalEvent = context.xePrologueCbs.CommandList.pfnAppendSignalEvent;
            if( nullptr != pfnAppendSignalEvent )
                pfnAppendSignalEvent( hCommandList, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendSignalEvent = context.xeEpilogueCbs.CommandList.pfnAppendSignalEvent;
            if( nullptr != pfnAppendSignalEvent )
                pfnAppendSignalEvent( hCommandList, hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendWaitOnEvents = context.xePrologueCbs.CommandList.pfnAppendWaitOnEvents;
            if( nullptr != pfnAppendWaitOnEvents )
                pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
        }

        if( context.enableTracing )
        {
            auto pfnAppendWaitOnEvents = context.xeEpilogueCbs.CommandList.pfnAppendWaitOnEvents;
            if( nullptr != pfnAppendWaitOnEvents )
                pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
        }

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

        if( context.enableTracing )
        {
            auto pfnHostSignal = context.xePrologueCbs.Event.pfnHostSignal;
            if( nullptr != pfnHostSignal )
                pfnHostSignal( hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnHostSignal = context.xeEpilogueCbs.Event.pfnHostSignal;
            if( nullptr != pfnHostSignal )
                pfnHostSignal( hEvent );
        }

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
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnHostSynchronize = context.xePrologueCbs.Event.pfnHostSynchronize;
            if( nullptr != pfnHostSynchronize )
                pfnHostSynchronize( hEvent, timeout );
        }

        if( context.enableTracing )
        {
            auto pfnHostSynchronize = context.xeEpilogueCbs.Event.pfnHostSynchronize;
            if( nullptr != pfnHostSynchronize )
                pfnHostSynchronize( hEvent, timeout );
        }

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

        if( context.enableTracing )
        {
            auto pfnQueryStatus = context.xePrologueCbs.Event.pfnQueryStatus;
            if( nullptr != pfnQueryStatus )
                pfnQueryStatus( hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnQueryStatus = context.xeEpilogueCbs.Event.pfnQueryStatus;
            if( nullptr != pfnQueryStatus )
                pfnQueryStatus( hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendEventReset = context.xePrologueCbs.CommandList.pfnAppendEventReset;
            if( nullptr != pfnAppendEventReset )
                pfnAppendEventReset( hCommandList, hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnAppendEventReset = context.xeEpilogueCbs.CommandList.pfnAppendEventReset;
            if( nullptr != pfnAppendEventReset )
                pfnAppendEventReset( hCommandList, hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnReset = context.xePrologueCbs.Event.pfnReset;
            if( nullptr != pfnReset )
                pfnReset( hEvent );
        }

        if( context.enableTracing )
        {
            auto pfnReset = context.xeEpilogueCbs.Event.pfnReset;
            if( nullptr != pfnReset )
                pfnReset( hEvent );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.Fence.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hCommandQueue, desc, phFence );
        }

        *phFence = reinterpret_cast<xe_fence_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.Fence.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hCommandQueue, desc, phFence );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.Fence.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hFence );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.Fence.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hFence );
        }

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
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnHostSynchronize = context.xePrologueCbs.Fence.pfnHostSynchronize;
            if( nullptr != pfnHostSynchronize )
                pfnHostSynchronize( hFence, timeout );
        }

        if( context.enableTracing )
        {
            auto pfnHostSynchronize = context.xeEpilogueCbs.Fence.pfnHostSynchronize;
            if( nullptr != pfnHostSynchronize )
                pfnHostSynchronize( hFence, timeout );
        }

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

        if( context.enableTracing )
        {
            auto pfnQueryStatus = context.xePrologueCbs.Fence.pfnQueryStatus;
            if( nullptr != pfnQueryStatus )
                pfnQueryStatus( hFence );
        }

        if( context.enableTracing )
        {
            auto pfnQueryStatus = context.xeEpilogueCbs.Fence.pfnQueryStatus;
            if( nullptr != pfnQueryStatus )
                pfnQueryStatus( hFence );
        }

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

        if( context.enableTracing )
        {
            auto pfnReset = context.xePrologueCbs.Fence.pfnReset;
            if( nullptr != pfnReset )
                pfnReset( hFence );
        }

        if( context.enableTracing )
        {
            auto pfnReset = context.xeEpilogueCbs.Fence.pfnReset;
            if( nullptr != pfnReset )
                pfnReset( hFence );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetProperties = context.xePrologueCbs.Image.pfnGetProperties;
            if( nullptr != pfnGetProperties )
                pfnGetProperties( hDevice, desc, pImageProperties );
        }

        if( context.enableTracing )
        {
            auto pfnGetProperties = context.xeEpilogueCbs.Image.pfnGetProperties;
            if( nullptr != pfnGetProperties )
                pfnGetProperties( hDevice, desc, pImageProperties );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.Image.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phImage );
        }

        *phImage = reinterpret_cast<xe_image_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.Image.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phImage );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.Image.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hImage );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.Image.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hImage );
        }

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
        void** ptr                                      ///< [out] pointer to shared allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnAllocSharedMem = context.xePrologueCbs.DeviceGroup.pfnAllocSharedMem;
            if( nullptr != pfnAllocSharedMem )
                pfnAllocSharedMem( hDeviceGroup, hDevice, device_flags, ordinal, host_flags, size, alignment, ptr );
        }

        *ptr = malloc( size );

        if( context.enableTracing )
        {
            auto pfnAllocSharedMem = context.xeEpilogueCbs.DeviceGroup.pfnAllocSharedMem;
            if( nullptr != pfnAllocSharedMem )
                pfnAllocSharedMem( hDeviceGroup, hDevice, device_flags, ordinal, host_flags, size, alignment, ptr );
        }

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
        void** ptr                                      ///< [out] pointer to device allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnAllocDeviceMem = context.xePrologueCbs.DeviceGroup.pfnAllocDeviceMem;
            if( nullptr != pfnAllocDeviceMem )
                pfnAllocDeviceMem( hDeviceGroup, hDevice, flags, ordinal, size, alignment, ptr );
        }

        *ptr = malloc( size );

        if( context.enableTracing )
        {
            auto pfnAllocDeviceMem = context.xeEpilogueCbs.DeviceGroup.pfnAllocDeviceMem;
            if( nullptr != pfnAllocDeviceMem )
                pfnAllocDeviceMem( hDeviceGroup, hDevice, flags, ordinal, size, alignment, ptr );
        }

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
        void** ptr                                      ///< [out] pointer to host allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnAllocHostMem = context.xePrologueCbs.DeviceGroup.pfnAllocHostMem;
            if( nullptr != pfnAllocHostMem )
                pfnAllocHostMem( hDeviceGroup, flags, size, alignment, ptr );
        }

        *ptr = malloc( size );

        if( context.enableTracing )
        {
            auto pfnAllocHostMem = context.xeEpilogueCbs.DeviceGroup.pfnAllocHostMem;
            if( nullptr != pfnAllocHostMem )
                pfnAllocHostMem( hDeviceGroup, flags, size, alignment, ptr );
        }

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

        if( context.enableTracing )
        {
            auto pfnFreeMem = context.xePrologueCbs.DeviceGroup.pfnFreeMem;
            if( nullptr != pfnFreeMem )
                pfnFreeMem( hDeviceGroup, ptr );
        }

        free( ptr );

        if( context.enableTracing )
        {
            auto pfnFreeMem = context.xeEpilogueCbs.DeviceGroup.pfnFreeMem;
            if( nullptr != pfnFreeMem )
                pfnFreeMem( hDeviceGroup, ptr );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetMemProperties = context.xePrologueCbs.DeviceGroup.pfnGetMemProperties;
            if( nullptr != pfnGetMemProperties )
                pfnGetMemProperties( hDeviceGroup, ptr, pMemProperties, phDevice );
        }

        *pMemProperties = {};

        if( context.enableTracing )
        {
            auto pfnGetMemProperties = context.xeEpilogueCbs.DeviceGroup.pfnGetMemProperties;
            if( nullptr != pfnGetMemProperties )
                pfnGetMemProperties( hDeviceGroup, ptr, pMemProperties, phDevice );
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

        if( context.enableTracing )
        {
            auto pfnGetMemAddressRange = context.xePrologueCbs.DeviceGroup.pfnGetMemAddressRange;
            if( nullptr != pfnGetMemAddressRange )
                pfnGetMemAddressRange( hDeviceGroup, ptr, pBase, pSize );
        }

        if( context.enableTracing )
        {
            auto pfnGetMemAddressRange = context.xeEpilogueCbs.DeviceGroup.pfnGetMemAddressRange;
            if( nullptr != pfnGetMemAddressRange )
                pfnGetMemAddressRange( hDeviceGroup, ptr, pBase, pSize );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetMemIpcHandle = context.xePrologueCbs.DeviceGroup.pfnGetMemIpcHandle;
            if( nullptr != pfnGetMemIpcHandle )
                pfnGetMemIpcHandle( hDeviceGroup, ptr, pIpcHandle );
        }

        if( context.enableTracing )
        {
            auto pfnGetMemIpcHandle = context.xeEpilogueCbs.DeviceGroup.pfnGetMemIpcHandle;
            if( nullptr != pfnGetMemIpcHandle )
                pfnGetMemIpcHandle( hDeviceGroup, ptr, pIpcHandle );
        }

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
        void** ptr                                      ///< [out] pointer to device allocation in this process
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnOpenMemIpcHandle = context.xePrologueCbs.DeviceGroup.pfnOpenMemIpcHandle;
            if( nullptr != pfnOpenMemIpcHandle )
                pfnOpenMemIpcHandle( hDeviceGroup, hDevice, handle, flags, ptr );
        }

        if( context.enableTracing )
        {
            auto pfnOpenMemIpcHandle = context.xeEpilogueCbs.DeviceGroup.pfnOpenMemIpcHandle;
            if( nullptr != pfnOpenMemIpcHandle )
                pfnOpenMemIpcHandle( hDeviceGroup, hDevice, handle, flags, ptr );
        }

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

        if( context.enableTracing )
        {
            auto pfnCloseMemIpcHandle = context.xePrologueCbs.DeviceGroup.pfnCloseMemIpcHandle;
            if( nullptr != pfnCloseMemIpcHandle )
                pfnCloseMemIpcHandle( hDeviceGroup, ptr );
        }

        if( context.enableTracing )
        {
            auto pfnCloseMemIpcHandle = context.xeEpilogueCbs.DeviceGroup.pfnCloseMemIpcHandle;
            if( nullptr != pfnCloseMemIpcHandle )
                pfnCloseMemIpcHandle( hDeviceGroup, ptr );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.Module.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phModule, phBuildLog );
        }

        *phModule = reinterpret_cast<xe_module_handle_t>( context.get() );

        if( nullptr != phBuildLog ) *phBuildLog = reinterpret_cast<xe_module_build_log_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.Module.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phModule, phBuildLog );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.Module.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hModule );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.Module.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hModule );
        }

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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.ModuleBuildLog.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hModuleBuildLog );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.ModuleBuildLog.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hModuleBuildLog );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetString = context.xePrologueCbs.ModuleBuildLog.pfnGetString;
            if( nullptr != pfnGetString )
                pfnGetString( hModuleBuildLog, pSize, pBuildLog );
        }

        if( context.enableTracing )
        {
            auto pfnGetString = context.xeEpilogueCbs.ModuleBuildLog.pfnGetString;
            if( nullptr != pfnGetString )
                pfnGetString( hModuleBuildLog, pSize, pBuildLog );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetNativeBinary = context.xePrologueCbs.Module.pfnGetNativeBinary;
            if( nullptr != pfnGetNativeBinary )
                pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
        }

        if( context.enableTracing )
        {
            auto pfnGetNativeBinary = context.xeEpilogueCbs.Module.pfnGetNativeBinary;
            if( nullptr != pfnGetNativeBinary )
                pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleGetGlobalPointer
    xe_result_t __xecall
    xeModuleGetGlobalPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        const char* pGlobalName,                        ///< [in] name of function in global
        void** pPtr                                     ///< [out] device visible pointer
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        if( context.enableTracing )
        {
            auto pfnGetGlobalPointer = context.xePrologueCbs.Module.pfnGetGlobalPointer;
            if( nullptr != pfnGetGlobalPointer )
                pfnGetGlobalPointer( hModule, pGlobalName, pPtr );
        }

        if( context.enableTracing )
        {
            auto pfnGetGlobalPointer = context.xeEpilogueCbs.Module.pfnGetGlobalPointer;
            if( nullptr != pfnGetGlobalPointer )
                pfnGetGlobalPointer( hModule, pGlobalName, pPtr );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.Function.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hModule, desc, phFunction );
        }

        *phFunction = reinterpret_cast<xe_function_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.Function.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hModule, desc, phFunction );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.Function.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hFunction );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.Function.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hFunction );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetFunctionPointer = context.xePrologueCbs.Module.pfnGetFunctionPointer;
            if( nullptr != pfnGetFunctionPointer )
                pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
        }

        if( context.enableTracing )
        {
            auto pfnGetFunctionPointer = context.xeEpilogueCbs.Module.pfnGetFunctionPointer;
            if( nullptr != pfnGetFunctionPointer )
                pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
        }

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

        if( context.enableTracing )
        {
            auto pfnSetGroupSize = context.xePrologueCbs.Function.pfnSetGroupSize;
            if( nullptr != pfnSetGroupSize )
                pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
        }

        if( context.enableTracing )
        {
            auto pfnSetGroupSize = context.xeEpilogueCbs.Function.pfnSetGroupSize;
            if( nullptr != pfnSetGroupSize )
                pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
        }

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

        if( context.enableTracing )
        {
            auto pfnSuggestGroupSize = context.xePrologueCbs.Function.pfnSuggestGroupSize;
            if( nullptr != pfnSuggestGroupSize )
                pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        }

        if( context.enableTracing )
        {
            auto pfnSuggestGroupSize = context.xeEpilogueCbs.Function.pfnSuggestGroupSize;
            if( nullptr != pfnSuggestGroupSize )
                pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        }

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

        if( context.enableTracing )
        {
            auto pfnSetArgumentValue = context.xePrologueCbs.Function.pfnSetArgumentValue;
            if( nullptr != pfnSetArgumentValue )
                pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
        }

        if( context.enableTracing )
        {
            auto pfnSetArgumentValue = context.xeEpilogueCbs.Function.pfnSetArgumentValue;
            if( nullptr != pfnSetArgumentValue )
                pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
        }

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

        if( context.enableTracing )
        {
            auto pfnSetAttribute = context.xePrologueCbs.Function.pfnSetAttribute;
            if( nullptr != pfnSetAttribute )
                pfnSetAttribute( hFunction, attr, value );
        }

        if( context.enableTracing )
        {
            auto pfnSetAttribute = context.xeEpilogueCbs.Function.pfnSetAttribute;
            if( nullptr != pfnSetAttribute )
                pfnSetAttribute( hFunction, attr, value );
        }

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

        if( context.enableTracing )
        {
            auto pfnGetAttribute = context.xePrologueCbs.Function.pfnGetAttribute;
            if( nullptr != pfnGetAttribute )
                pfnGetAttribute( hFunction, attr, pValue );
        }

        if( context.enableTracing )
        {
            auto pfnGetAttribute = context.xeEpilogueCbs.Function.pfnGetAttribute;
            if( nullptr != pfnGetAttribute )
                pfnGetAttribute( hFunction, attr, pValue );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendLaunchFunction = context.xePrologueCbs.CommandList.pfnAppendLaunchFunction;
            if( nullptr != pfnAppendLaunchFunction )
                pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        }

        if( context.enableTracing )
        {
            auto pfnAppendLaunchFunction = context.xeEpilogueCbs.CommandList.pfnAppendLaunchFunction;
            if( nullptr != pfnAppendLaunchFunction )
                pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendLaunchFunctionIndirect = context.xePrologueCbs.CommandList.pfnAppendLaunchFunctionIndirect;
            if( nullptr != pfnAppendLaunchFunctionIndirect )
                pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }

        if( context.enableTracing )
        {
            auto pfnAppendLaunchFunctionIndirect = context.xeEpilogueCbs.CommandList.pfnAppendLaunchFunctionIndirect;
            if( nullptr != pfnAppendLaunchFunctionIndirect )
                pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendLaunchMultipleFunctionsIndirect = context.xePrologueCbs.CommandList.pfnAppendLaunchMultipleFunctionsIndirect;
            if( nullptr != pfnAppendLaunchMultipleFunctionsIndirect )
                pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }

        if( context.enableTracing )
        {
            auto pfnAppendLaunchMultipleFunctionsIndirect = context.xeEpilogueCbs.CommandList.pfnAppendLaunchMultipleFunctionsIndirect;
            if( nullptr != pfnAppendLaunchMultipleFunctionsIndirect )
                pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }

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

        if( context.enableTracing )
        {
            auto pfnAppendLaunchHostFunction = context.xePrologueCbs.CommandList.pfnAppendLaunchHostFunction;
            if( nullptr != pfnAppendLaunchHostFunction )
                pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
        }

        if( context.enableTracing )
        {
            auto pfnAppendLaunchHostFunction = context.xeEpilogueCbs.CommandList.pfnAppendLaunchHostFunction;
            if( nullptr != pfnAppendLaunchHostFunction )
                pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
        }

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

        if( context.enableTracing )
        {
            auto pfnMakeMemoryResident = context.xePrologueCbs.Device.pfnMakeMemoryResident;
            if( nullptr != pfnMakeMemoryResident )
                pfnMakeMemoryResident( hDevice, ptr, size );
        }

        if( context.enableTracing )
        {
            auto pfnMakeMemoryResident = context.xeEpilogueCbs.Device.pfnMakeMemoryResident;
            if( nullptr != pfnMakeMemoryResident )
                pfnMakeMemoryResident( hDevice, ptr, size );
        }

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

        if( context.enableTracing )
        {
            auto pfnEvictMemory = context.xePrologueCbs.Device.pfnEvictMemory;
            if( nullptr != pfnEvictMemory )
                pfnEvictMemory( hDevice, ptr, size );
        }

        if( context.enableTracing )
        {
            auto pfnEvictMemory = context.xeEpilogueCbs.Device.pfnEvictMemory;
            if( nullptr != pfnEvictMemory )
                pfnEvictMemory( hDevice, ptr, size );
        }

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

        if( context.enableTracing )
        {
            auto pfnMakeImageResident = context.xePrologueCbs.Device.pfnMakeImageResident;
            if( nullptr != pfnMakeImageResident )
                pfnMakeImageResident( hDevice, hImage );
        }

        if( context.enableTracing )
        {
            auto pfnMakeImageResident = context.xeEpilogueCbs.Device.pfnMakeImageResident;
            if( nullptr != pfnMakeImageResident )
                pfnMakeImageResident( hDevice, hImage );
        }

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

        if( context.enableTracing )
        {
            auto pfnEvictImage = context.xePrologueCbs.Device.pfnEvictImage;
            if( nullptr != pfnEvictImage )
                pfnEvictImage( hDevice, hImage );
        }

        if( context.enableTracing )
        {
            auto pfnEvictImage = context.xeEpilogueCbs.Device.pfnEvictImage;
            if( nullptr != pfnEvictImage )
                pfnEvictImage( hDevice, hImage );
        }

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

        if( context.enableTracing )
        {
            auto pfnCreate = context.xePrologueCbs.Sampler.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phSampler );
        }

        *phSampler = reinterpret_cast<xe_sampler_handle_t>( context.get() );

        if( context.enableTracing )
        {
            auto pfnCreate = context.xeEpilogueCbs.Sampler.pfnCreate;
            if( nullptr != pfnCreate )
                pfnCreate( hDevice, desc, phSampler );
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

        if( context.enableTracing )
        {
            auto pfnDestroy = context.xePrologueCbs.Sampler.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hSampler );
        }


        if( context.enableTracing )
        {
            auto pfnDestroy = context.xeEpilogueCbs.Sampler.pfnDestroy;
            if( nullptr != pfnDestroy )
                pfnDestroy( hSampler );
        }

        return result;
    }

} // namespace driver

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnInit                                   = driver::xeInit;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::xeDeviceGet;

    pDdiTable->pfnGetSubDevices                          = driver::xeDeviceGetSubDevices;

    pDdiTable->pfnGetP2PProperties                       = driver::xeDeviceGetP2PProperties;

    pDdiTable->pfnCanAccessPeer                          = driver::xeDeviceCanAccessPeer;

    pDdiTable->pfnSetIntermediateCacheConfig             = driver::xeDeviceSetIntermediateCacheConfig;

    pDdiTable->pfnSetLastLevelCacheConfig                = driver::xeDeviceSetLastLevelCacheConfig;

    pDdiTable->pfnSystemBarrier                          = driver::xeDeviceSystemBarrier;

#if XE_ENABLE_OCL_INTEROP
    pDdiTable->pfnRegisterCLMemory                       = driver::xeDeviceRegisterCLMemory;
#endif

#if XE_ENABLE_OCL_INTEROP
    pDdiTable->pfnRegisterCLProgram                      = driver::xeDeviceRegisterCLProgram;
#endif

#if XE_ENABLE_OCL_INTEROP
    pDdiTable->pfnRegisterCLCommandQueue                 = driver::xeDeviceRegisterCLCommandQueue;
#endif

    pDdiTable->pfnMakeMemoryResident                     = driver::xeDeviceMakeMemoryResident;

    pDdiTable->pfnEvictMemory                            = driver::xeDeviceEvictMemory;

    pDdiTable->pfnMakeImageResident                      = driver::xeDeviceMakeImageResident;

    pDdiTable->pfnEvictImage                             = driver::xeDeviceEvictImage;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::xeDeviceGroupGet;

    pDdiTable->pfnGetDriverVersion                       = driver::xeDeviceGroupGetDriverVersion;

    pDdiTable->pfnGetApiVersion                          = driver::xeDeviceGroupGetApiVersion;

    pDdiTable->pfnGetDeviceProperties                    = driver::xeDeviceGroupGetDeviceProperties;

    pDdiTable->pfnGetComputeProperties                   = driver::xeDeviceGroupGetComputeProperties;

    pDdiTable->pfnGetMemoryProperties                    = driver::xeDeviceGroupGetMemoryProperties;

    pDdiTable->pfnGetMemoryAccessProperties              = driver::xeDeviceGroupGetMemoryAccessProperties;

    pDdiTable->pfnGetCacheProperties                     = driver::xeDeviceGroupGetCacheProperties;

    pDdiTable->pfnGetImageProperties                     = driver::xeDeviceGroupGetImageProperties;

    pDdiTable->pfnAllocSharedMem                         = driver::xeDeviceGroupAllocSharedMem;

    pDdiTable->pfnAllocDeviceMem                         = driver::xeDeviceGroupAllocDeviceMem;

    pDdiTable->pfnAllocHostMem                           = driver::xeDeviceGroupAllocHostMem;

    pDdiTable->pfnFreeMem                                = driver::xeDeviceGroupFreeMem;

    pDdiTable->pfnGetMemProperties                       = driver::xeDeviceGroupGetMemProperties;

    pDdiTable->pfnGetMemAddressRange                     = driver::xeDeviceGroupGetMemAddressRange;

    pDdiTable->pfnGetMemIpcHandle                        = driver::xeDeviceGroupGetMemIpcHandle;

    pDdiTable->pfnOpenMemIpcHandle                       = driver::xeDeviceGroupOpenMemIpcHandle;

    pDdiTable->pfnCloseMemIpcHandle                      = driver::xeDeviceGroupCloseMemIpcHandle;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeCommandQueueCreate;

    pDdiTable->pfnDestroy                                = driver::xeCommandQueueDestroy;

    pDdiTable->pfnExecuteCommandLists                    = driver::xeCommandQueueExecuteCommandLists;

    pDdiTable->pfnSynchronize                            = driver::xeCommandQueueSynchronize;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeCommandListCreate;

    pDdiTable->pfnCreateImmediate                        = driver::xeCommandListCreateImmediate;

    pDdiTable->pfnDestroy                                = driver::xeCommandListDestroy;

    pDdiTable->pfnClose                                  = driver::xeCommandListClose;

    pDdiTable->pfnReset                                  = driver::xeCommandListReset;

    pDdiTable->pfnSetParameter                           = driver::xeCommandListSetParameter;

    pDdiTable->pfnGetParameter                           = driver::xeCommandListGetParameter;

    pDdiTable->pfnResetParameters                        = driver::xeCommandListResetParameters;

    pDdiTable->pfnReserveSpace                           = driver::xeCommandListReserveSpace;

    pDdiTable->pfnAppendBarrier                          = driver::xeCommandListAppendBarrier;

    pDdiTable->pfnAppendMemoryRangesBarrier              = driver::xeCommandListAppendMemoryRangesBarrier;

    pDdiTable->pfnAppendMemoryCopy                       = driver::xeCommandListAppendMemoryCopy;

    pDdiTable->pfnAppendMemorySet                        = driver::xeCommandListAppendMemorySet;

    pDdiTable->pfnAppendMemoryCopyRegion                 = driver::xeCommandListAppendMemoryCopyRegion;

    pDdiTable->pfnAppendImageCopy                        = driver::xeCommandListAppendImageCopy;

    pDdiTable->pfnAppendImageCopyRegion                  = driver::xeCommandListAppendImageCopyRegion;

    pDdiTable->pfnAppendImageCopyToMemory                = driver::xeCommandListAppendImageCopyToMemory;

    pDdiTable->pfnAppendImageCopyFromMemory              = driver::xeCommandListAppendImageCopyFromMemory;

    pDdiTable->pfnAppendMemoryPrefetch                   = driver::xeCommandListAppendMemoryPrefetch;

    pDdiTable->pfnAppendMemAdvise                        = driver::xeCommandListAppendMemAdvise;

    pDdiTable->pfnAppendSignalEvent                      = driver::xeCommandListAppendSignalEvent;

    pDdiTable->pfnAppendWaitOnEvents                     = driver::xeCommandListAppendWaitOnEvents;

    pDdiTable->pfnAppendEventReset                       = driver::xeCommandListAppendEventReset;

    pDdiTable->pfnAppendLaunchFunction                   = driver::xeCommandListAppendLaunchFunction;

    pDdiTable->pfnAppendLaunchFunctionIndirect           = driver::xeCommandListAppendLaunchFunctionIndirect;

    pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect  = driver::xeCommandListAppendLaunchMultipleFunctionsIndirect;

    pDdiTable->pfnAppendLaunchHostFunction               = driver::xeCommandListAppendLaunchHostFunction;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeFenceCreate;

    pDdiTable->pfnDestroy                                = driver::xeFenceDestroy;

    pDdiTable->pfnHostSynchronize                        = driver::xeFenceHostSynchronize;

    pDdiTable->pfnQueryStatus                            = driver::xeFenceQueryStatus;

    pDdiTable->pfnReset                                  = driver::xeFenceReset;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeEventPoolCreate;

    pDdiTable->pfnDestroy                                = driver::xeEventPoolDestroy;

    pDdiTable->pfnGetIpcHandle                           = driver::xeEventPoolGetIpcHandle;

    pDdiTable->pfnOpenIpcHandle                          = driver::xeEventPoolOpenIpcHandle;

    pDdiTable->pfnCloseIpcHandle                         = driver::xeEventPoolCloseIpcHandle;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeEventCreate;

    pDdiTable->pfnDestroy                                = driver::xeEventDestroy;

    pDdiTable->pfnHostSignal                             = driver::xeEventHostSignal;

    pDdiTable->pfnHostSynchronize                        = driver::xeEventHostSynchronize;

    pDdiTable->pfnQueryStatus                            = driver::xeEventQueryStatus;

    pDdiTable->pfnReset                                  = driver::xeEventReset;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::xeImageGetProperties;

    pDdiTable->pfnCreate                                 = driver::xeImageCreate;

    pDdiTable->pfnDestroy                                = driver::xeImageDestroy;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeModuleCreate;

    pDdiTable->pfnDestroy                                = driver::xeModuleDestroy;

    pDdiTable->pfnGetNativeBinary                        = driver::xeModuleGetNativeBinary;

    pDdiTable->pfnGetGlobalPointer                       = driver::xeModuleGetGlobalPointer;

    pDdiTable->pfnGetFunctionPointer                     = driver::xeModuleGetFunctionPointer;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnDestroy                                = driver::xeModuleBuildLogDestroy;

    pDdiTable->pfnGetString                              = driver::xeModuleBuildLogGetString;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeFunctionCreate;

    pDdiTable->pfnDestroy                                = driver::xeFunctionDestroy;

    pDdiTable->pfnSetGroupSize                           = driver::xeFunctionSetGroupSize;

    pDdiTable->pfnSuggestGroupSize                       = driver::xeFunctionSuggestGroupSize;

    pDdiTable->pfnSetArgumentValue                       = driver::xeFunctionSetArgumentValue;

    pDdiTable->pfnSetAttribute                           = driver::xeFunctionSetAttribute;

    pDdiTable->pfnGetAttribute                           = driver::xeFunctionGetAttribute;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::xeSamplerCreate;

    pDdiTable->pfnDestroy                                = driver::xeSamplerDestroy;

    return result;
}

#if defined(__cplusplus)
};
#endif
