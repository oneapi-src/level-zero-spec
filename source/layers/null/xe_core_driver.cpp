/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_core_driver.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
 * @endcond
 *
 */
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInit = context.xeDdiTable.Global.pfnInit;
        if( nullptr != pfnInit )
        {
            result = pfnInit( flags );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGet
    xe_result_t __xecall
    xeDriverGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader will update the value with the total
                                                        ///< number of drivers available.
                                                        ///< if count is non-zero, then the loader will only retrieve that number
                                                        ///< of drivers.
                                                        ///< if count is larger than the number of drivers available, then the
                                                        ///< loader will update the value with the correct number of drivers available.
        xe_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.xeDdiTable.Driver.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( pCount, phDrivers );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDrivers ) && ( i < *pCount ); ++i )
                phDrivers[ i ] = reinterpret_cast<xe_driver_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetDriverVersion
    xe_result_t __xecall
    xeDriverGetDriverVersion(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* version                               ///< [out] driver version
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDriverVersion = context.xeDdiTable.Driver.pfnGetDriverVersion;
        if( nullptr != pfnGetDriverVersion )
        {
            result = pfnGetDriverVersion( hDriver, version );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetApiVersion
    xe_result_t __xecall
    xeDriverGetApiVersion(
        xe_driver_handle_t hDrivers,                    ///< [in] handle of the driver instance
        xe_api_version_t* version                       ///< [out] api version
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetApiVersion = context.xeDdiTable.Driver.pfnGetApiVersion;
        if( nullptr != pfnGetApiVersion )
        {
            result = pfnGetApiVersion( hDrivers, version );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetIPCProperties
    xe_result_t __xecall
    xeDriverGetIPCProperties(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIPCProperties = context.xeDdiTable.Driver.pfnGetIPCProperties;
        if( nullptr != pfnGetIPCProperties )
        {
            result = pfnGetIPCProperties( hDriver, pIPCProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGet
    xe_result_t __xecall
    xeDeviceGet(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.xeDdiTable.Device.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDriver, pCount, phDevices );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDevices ) && ( i < *pCount ); ++i )
                phDevices[ i ] = reinterpret_cast<xe_device_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetSubDevices = context.xeDdiTable.Device.pfnGetSubDevices;
        if( nullptr != pfnGetSubDevices )
        {
            result = pfnGetSubDevices( hDevice, pCount, phSubdevices );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phSubdevices ) && ( i < *pCount ); ++i )
                phSubdevices[ i ] = reinterpret_cast<xe_device_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetProperties
    xe_result_t __xecall
    xeDeviceGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.xeDdiTable.Device.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDevice, pDeviceProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetComputeProperties
    xe_result_t __xecall
    xeDeviceGetComputeProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetComputeProperties = context.xeDdiTable.Device.pfnGetComputeProperties;
        if( nullptr != pfnGetComputeProperties )
        {
            result = pfnGetComputeProperties( hDevice, pComputeProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetMemoryProperties
    xe_result_t __xecall
    xeDeviceGetMemoryProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemoryProperties = context.xeDdiTable.Device.pfnGetMemoryProperties;
        if( nullptr != pfnGetMemoryProperties )
        {
            result = pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetMemoryAccessProperties
    xe_result_t __xecall
    xeDeviceGetMemoryAccessProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_memory_access_properties_t* pMemAccessProperties  ///< [out] query result for memory access properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemoryAccessProperties = context.xeDdiTable.Device.pfnGetMemoryAccessProperties;
        if( nullptr != pfnGetMemoryAccessProperties )
        {
            result = pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetCacheProperties
    xe_result_t __xecall
    xeDeviceGetCacheProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_cache_properties_t* pCacheProperties  ///< [out] query result for cache properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetCacheProperties = context.xeDdiTable.Device.pfnGetCacheProperties;
        if( nullptr != pfnGetCacheProperties )
        {
            result = pfnGetCacheProperties( hDevice, pCacheProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetImageProperties
    xe_result_t __xecall
    xeDeviceGetImageProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_image_properties_t* pImageProperties  ///< [out] query result for image properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetImageProperties = context.xeDdiTable.Device.pfnGetImageProperties;
        if( nullptr != pfnGetImageProperties )
        {
            result = pfnGetImageProperties( hDevice, pImageProperties );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetP2PProperties = context.xeDdiTable.Device.pfnGetP2PProperties;
        if( nullptr != pfnGetP2PProperties )
        {
            result = pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCanAccessPeer = context.xeDdiTable.Device.pfnCanAccessPeer;
        if( nullptr != pfnCanAccessPeer )
        {
            result = pfnCanAccessPeer( hDevice, hPeerDevice, value );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetIntermediateCacheConfig = context.xeDdiTable.Device.pfnSetIntermediateCacheConfig;
        if( nullptr != pfnSetIntermediateCacheConfig )
        {
            result = pfnSetIntermediateCacheConfig( hDevice, CacheConfig );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLastLevelCacheConfig = context.xeDdiTable.Device.pfnSetLastLevelCacheConfig;
        if( nullptr != pfnSetLastLevelCacheConfig )
        {
            result = pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.CommandQueue.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phCommandQueue );
        }
        else
        {
            // generic implementation
            *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.CommandQueue.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hCommandQueue );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnExecuteCommandLists = context.xeDdiTable.CommandQueue.pfnExecuteCommandLists;
        if( nullptr != pfnExecuteCommandLists )
        {
            result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
        }
        else
        {
            // generic implementation
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
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSynchronize = context.xeDdiTable.CommandQueue.pfnSynchronize;
        if( nullptr != pfnSynchronize )
        {
            result = pfnSynchronize( hCommandQueue, timeout );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.CommandList.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phCommandList );
        }
        else
        {
            // generic implementation
            *phCommandList = reinterpret_cast<xe_command_list_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateImmediate = context.xeDdiTable.CommandList.pfnCreateImmediate;
        if( nullptr != pfnCreateImmediate )
        {
            result = pfnCreateImmediate( hDevice, altdesc, phCommandList );
        }
        else
        {
            // generic implementation
            *phCommandList = reinterpret_cast<xe_command_list_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.CommandList.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hCommandList );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.xeDdiTable.CommandList.pfnClose;
        if( nullptr != pfnClose )
        {
            result = pfnClose( hCommandList );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.xeDdiTable.CommandList.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hCommandList );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendBarrier = context.xeDdiTable.CommandList.pfnAppendBarrier;
        if( nullptr != pfnAppendBarrier )
        {
            result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryRangesBarrier = context.xeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;
        if( nullptr != pfnAppendMemoryRangesBarrier )
        {
            result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSystemBarrier = context.xeDdiTable.Device.pfnSystemBarrier;
        if( nullptr != pfnSystemBarrier )
        {
            result = pfnSystemBarrier( hDevice );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRegisterCLMemory = context.xeDdiTable.Device.pfnRegisterCLMemory;
        if( nullptr != pfnRegisterCLMemory )
        {
            result = pfnRegisterCLMemory( hDevice, context, mem, ptr );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRegisterCLProgram = context.xeDdiTable.Device.pfnRegisterCLProgram;
        if( nullptr != pfnRegisterCLProgram )
        {
            result = pfnRegisterCLProgram( hDevice, context, program, phModule );
        }
        else
        {
            // generic implementation
            *phModule = reinterpret_cast<xe_module_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRegisterCLCommandQueue = context.xeDdiTable.Device.pfnRegisterCLCommandQueue;
        if( nullptr != pfnRegisterCLCommandQueue )
        {
            result = pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
        }
        else
        {
            // generic implementation
            *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryCopy = context.xeDdiTable.CommandList.pfnAppendMemoryCopy;
        if( nullptr != pfnAppendMemoryCopy )
        {
            result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemorySet = context.xeDdiTable.CommandList.pfnAppendMemorySet;
        if( nullptr != pfnAppendMemorySet )
        {
            result = pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryCopyRegion = context.xeDdiTable.CommandList.pfnAppendMemoryCopyRegion;
        if( nullptr != pfnAppendMemoryCopyRegion )
        {
            result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopy = context.xeDdiTable.CommandList.pfnAppendImageCopy;
        if( nullptr != pfnAppendImageCopy )
        {
            result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
        }
        else
        {
            // generic implementation
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
        const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyRegion = context.xeDdiTable.CommandList.pfnAppendImageCopyRegion;
        if( nullptr != pfnAppendImageCopyRegion )
        {
            result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
        }
        else
        {
            // generic implementation
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
        const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyToMemory = context.xeDdiTable.CommandList.pfnAppendImageCopyToMemory;
        if( nullptr != pfnAppendImageCopyToMemory )
        {
            result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
        }
        else
        {
            // generic implementation
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
        const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyFromMemory = context.xeDdiTable.CommandList.pfnAppendImageCopyFromMemory;
        if( nullptr != pfnAppendImageCopyFromMemory )
        {
            result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryPrefetch = context.xeDdiTable.CommandList.pfnAppendMemoryPrefetch;
        if( nullptr != pfnAppendMemoryPrefetch )
        {
            result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemAdvise = context.xeDdiTable.CommandList.pfnAppendMemAdvise;
        if( nullptr != pfnAppendMemAdvise )
        {
            result = pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolCreate
    xe_result_t __xecall
    xeEventPoolCreate(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        xe_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.EventPool.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDriver, desc, numDevices, phDevices, phEventPool );
        }
        else
        {
            // generic implementation
            *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.EventPool.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hEventPool );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.Event.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hEventPool, desc, phEvent );
        }
        else
        {
            // generic implementation
            *phEvent = reinterpret_cast<xe_event_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.Event.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hEvent );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIpcHandle = context.xeDdiTable.EventPool.pfnGetIpcHandle;
        if( nullptr != pfnGetIpcHandle )
        {
            result = pfnGetIpcHandle( hEventPool, phIpc );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolOpenIpcHandle
    xe_result_t __xecall
    xeEventPoolOpenIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver to associate with the IPC event pool handle
        xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpenIpcHandle = context.xeDdiTable.EventPool.pfnOpenIpcHandle;
        if( nullptr != pfnOpenIpcHandle )
        {
            result = pfnOpenIpcHandle( hDriver, hIpc, phEventPool );
        }
        else
        {
            // generic implementation
            *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCloseIpcHandle = context.xeDdiTable.EventPool.pfnCloseIpcHandle;
        if( nullptr != pfnCloseIpcHandle )
        {
            result = pfnCloseIpcHandle( hEventPool );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendSignalEvent = context.xeDdiTable.CommandList.pfnAppendSignalEvent;
        if( nullptr != pfnAppendSignalEvent )
        {
            result = pfnAppendSignalEvent( hCommandList, hEvent );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendWaitOnEvents = context.xeDdiTable.CommandList.pfnAppendWaitOnEvents;
        if( nullptr != pfnAppendWaitOnEvents )
        {
            result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSignal = context.xeDdiTable.Event.pfnHostSignal;
        if( nullptr != pfnHostSignal )
        {
            result = pfnHostSignal( hEvent );
        }
        else
        {
            // generic implementation
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
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSynchronize = context.xeDdiTable.Event.pfnHostSynchronize;
        if( nullptr != pfnHostSynchronize )
        {
            result = pfnHostSynchronize( hEvent, timeout );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryStatus = context.xeDdiTable.Event.pfnQueryStatus;
        if( nullptr != pfnQueryStatus )
        {
            result = pfnQueryStatus( hEvent );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendEventReset = context.xeDdiTable.CommandList.pfnAppendEventReset;
        if( nullptr != pfnAppendEventReset )
        {
            result = pfnAppendEventReset( hCommandList, hEvent );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.xeDdiTable.Event.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hEvent );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.Fence.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hCommandQueue, desc, phFence );
        }
        else
        {
            // generic implementation
            *phFence = reinterpret_cast<xe_fence_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.Fence.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hFence );
        }
        else
        {
            // generic implementation

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
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSynchronize = context.xeDdiTable.Fence.pfnHostSynchronize;
        if( nullptr != pfnHostSynchronize )
        {
            result = pfnHostSynchronize( hFence, timeout );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryStatus = context.xeDdiTable.Fence.pfnQueryStatus;
        if( nullptr != pfnQueryStatus )
        {
            result = pfnQueryStatus( hFence );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.xeDdiTable.Fence.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hFence );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.xeDdiTable.Image.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDevice, desc, pImageProperties );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.Image.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phImage );
        }
        else
        {
            // generic implementation
            *phImage = reinterpret_cast<xe_image_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.Image.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hImage );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverAllocSharedMem
    xe_result_t __xecall
    xeDriverAllocSharedMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_device_handle_t hDevice,                     ///< [in] handle of a device
        xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
        xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocSharedMem = context.xeDdiTable.Driver.pfnAllocSharedMem;
        if( nullptr != pfnAllocSharedMem )
        {
            result = pfnAllocSharedMem( hDriver, hDevice, device_flags, ordinal, host_flags, size, alignment, pptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverAllocDeviceMem
    xe_result_t __xecall
    xeDriverAllocDeviceMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocDeviceMem = context.xeDdiTable.Driver.pfnAllocDeviceMem;
        if( nullptr != pfnAllocDeviceMem )
        {
            result = pfnAllocDeviceMem( hDriver, hDevice, flags, ordinal, size, alignment, pptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverAllocHostMem
    xe_result_t __xecall
    xeDriverAllocHostMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocHostMem = context.xeDdiTable.Driver.pfnAllocHostMem;
        if( nullptr != pfnAllocHostMem )
        {
            result = pfnAllocHostMem( hDriver, flags, size, alignment, pptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverFreeMem
    xe_result_t __xecall
    xeDriverFreeMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFreeMem = context.xeDdiTable.Driver.pfnFreeMem;
        if( nullptr != pfnFreeMem )
        {
            result = pfnFreeMem( hDriver, ptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetMemProperties
    xe_result_t __xecall
    xeDriverGetMemProperties(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        xe_memory_allocation_properties_t* pMemProperties,  ///< [out] query result for memory allocation properties
        xe_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemProperties = context.xeDdiTable.Driver.pfnGetMemProperties;
        if( nullptr != pfnGetMemProperties )
        {
            result = pfnGetMemProperties( hDriver, ptr, pMemProperties, phDevice );
        }
        else
        {
            // generic implementation
            if( nullptr != phDevice ) *phDevice = reinterpret_cast<xe_device_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetMemAddressRange
    xe_result_t __xecall
    xeDriverGetMemAddressRange(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemAddressRange = context.xeDdiTable.Driver.pfnGetMemAddressRange;
        if( nullptr != pfnGetMemAddressRange )
        {
            result = pfnGetMemAddressRange( hDriver, ptr, pBase, pSize );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetMemIpcHandle
    xe_result_t __xecall
    xeDriverGetMemIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemIpcHandle = context.xeDdiTable.Driver.pfnGetMemIpcHandle;
        if( nullptr != pfnGetMemIpcHandle )
        {
            result = pfnGetMemIpcHandle( hDriver, ptr, pIpcHandle );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverOpenMemIpcHandle
    xe_result_t __xecall
    xeDriverOpenMemIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpenMemIpcHandle = context.xeDdiTable.Driver.pfnOpenMemIpcHandle;
        if( nullptr != pfnOpenMemIpcHandle )
        {
            result = pfnOpenMemIpcHandle( hDriver, hDevice, handle, flags, pptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverCloseMemIpcHandle
    xe_result_t __xecall
    xeDriverCloseMemIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCloseMemIpcHandle = context.xeDdiTable.Driver.pfnCloseMemIpcHandle;
        if( nullptr != pfnCloseMemIpcHandle )
        {
            result = pfnCloseMemIpcHandle( hDriver, ptr );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.Module.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phModule, phBuildLog );
        }
        else
        {
            // generic implementation
            *phModule = reinterpret_cast<xe_module_handle_t>( context.get() );

            if( nullptr != phBuildLog ) *phBuildLog = reinterpret_cast<xe_module_build_log_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.Module.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hModule );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.ModuleBuildLog.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hModuleBuildLog );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetString = context.xeDdiTable.ModuleBuildLog.pfnGetString;
        if( nullptr != pfnGetString )
        {
            result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetNativeBinary = context.xeDdiTable.Module.pfnGetNativeBinary;
        if( nullptr != pfnGetNativeBinary )
        {
            result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetGlobalPointer = context.xeDdiTable.Module.pfnGetGlobalPointer;
        if( nullptr != pfnGetGlobalPointer )
        {
            result = pfnGetGlobalPointer( hModule, pGlobalName, pptr );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.Function.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hModule, desc, phFunction );
        }
        else
        {
            // generic implementation
            *phFunction = reinterpret_cast<xe_function_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.Function.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hFunction );
        }
        else
        {
            // generic implementation

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFunctionPointer = context.xeDdiTable.Module.pfnGetFunctionPointer;
        if( nullptr != pfnGetFunctionPointer )
        {
            result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetGroupSize = context.xeDdiTable.Function.pfnSetGroupSize;
        if( nullptr != pfnSetGroupSize )
        {
            result = pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSuggestGroupSize = context.xeDdiTable.Function.pfnSuggestGroupSize;
        if( nullptr != pfnSuggestGroupSize )
        {
            result = pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetArgumentValue = context.xeDdiTable.Function.pfnSetArgumentValue;
        if( nullptr != pfnSetArgumentValue )
        {
            result = pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetAttribute = context.xeDdiTable.Function.pfnSetAttribute;
        if( nullptr != pfnSetAttribute )
        {
            result = pfnSetAttribute( hFunction, attr, value );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAttribute = context.xeDdiTable.Function.pfnGetAttribute;
        if( nullptr != pfnGetAttribute )
        {
            result = pfnGetAttribute( hFunction, attr, pValue );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchFunction = context.xeDdiTable.CommandList.pfnAppendLaunchFunction;
        if( nullptr != pfnAppendLaunchFunction )
        {
            result = pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchFunctionIndirect = context.xeDdiTable.CommandList.pfnAppendLaunchFunctionIndirect;
        if( nullptr != pfnAppendLaunchFunctionIndirect )
        {
            result = pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchMultipleFunctionsIndirect = context.xeDdiTable.CommandList.pfnAppendLaunchMultipleFunctionsIndirect;
        if( nullptr != pfnAppendLaunchMultipleFunctionsIndirect )
        {
            result = pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchHostFunction = context.xeDdiTable.CommandList.pfnAppendLaunchHostFunction;
        if( nullptr != pfnAppendLaunchHostFunction )
        {
            result = pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMakeMemoryResident = context.xeDdiTable.Device.pfnMakeMemoryResident;
        if( nullptr != pfnMakeMemoryResident )
        {
            result = pfnMakeMemoryResident( hDevice, ptr, size );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEvictMemory = context.xeDdiTable.Device.pfnEvictMemory;
        if( nullptr != pfnEvictMemory )
        {
            result = pfnEvictMemory( hDevice, ptr, size );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMakeImageResident = context.xeDdiTable.Device.pfnMakeImageResident;
        if( nullptr != pfnMakeImageResident )
        {
            result = pfnMakeImageResident( hDevice, hImage );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEvictImage = context.xeDdiTable.Device.pfnEvictImage;
        if( nullptr != pfnEvictImage )
        {
            result = pfnEvictImage( hDevice, hImage );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xeDdiTable.Sampler.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phSampler );
        }
        else
        {
            // generic implementation
            *phSampler = reinterpret_cast<xe_sampler_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xeDdiTable.Sampler.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hSampler );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

} // namespace driver

namespace instrumented
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeInit
    xe_result_t __xecall
    xeInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_init_params_t in_params = {
            &flags
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeInit( flags );

        // capture parameters
        xe_init_params_t out_params = {
            &flags
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGet
    xe_result_t __xecall
    xeDriverGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader will update the value with the total
                                                        ///< number of drivers available.
                                                        ///< if count is non-zero, then the loader will only retrieve that number
                                                        ///< of drivers.
                                                        ///< if count is larger than the number of drivers available, then the
                                                        ///< loader will update the value with the correct number of drivers available.
        xe_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_get_params_t in_params = {
            &pCount,
            &phDrivers
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverGet( pCount, phDrivers );

        // capture parameters
        xe_driver_get_params_t out_params = {
            &pCount,
            &phDrivers
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetDriverVersion
    xe_result_t __xecall
    xeDriverGetDriverVersion(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* version                               ///< [out] driver version
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_get_driver_version_params_t in_params = {
            &hDriver,
            &version
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnGetDriverVersionCb )
                    table.pfnGetDriverVersionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverGetDriverVersion( hDriver, version );

        // capture parameters
        xe_driver_get_driver_version_params_t out_params = {
            &hDriver,
            &version
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetDriverVersionCb )
                    table.pfnGetDriverVersionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetApiVersion
    xe_result_t __xecall
    xeDriverGetApiVersion(
        xe_driver_handle_t hDrivers,                    ///< [in] handle of the driver instance
        xe_api_version_t* version                       ///< [out] api version
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_get_api_version_params_t in_params = {
            &hDrivers,
            &version
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnGetApiVersionCb )
                    table.pfnGetApiVersionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverGetApiVersion( hDrivers, version );

        // capture parameters
        xe_driver_get_api_version_params_t out_params = {
            &hDrivers,
            &version
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetApiVersionCb )
                    table.pfnGetApiVersionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetIPCProperties
    xe_result_t __xecall
    xeDriverGetIPCProperties(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_get_ipc_properties_params_t in_params = {
            &hDriver,
            &pIPCProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnGetIPCPropertiesCb )
                    table.pfnGetIPCPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverGetIPCProperties( hDriver, pIPCProperties );

        // capture parameters
        xe_driver_get_ipc_properties_params_t out_params = {
            &hDriver,
            &pIPCProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetIPCPropertiesCb )
                    table.pfnGetIPCPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGet
    xe_result_t __xecall
    xeDeviceGet(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
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

        // capture parameters
        xe_device_get_params_t in_params = {
            &hDriver,
            &pCount,
            &phDevices
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGet( hDriver, pCount, phDevices );

        // capture parameters
        xe_device_get_params_t out_params = {
            &hDriver,
            &pCount,
            &phDevices
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_get_sub_devices_params_t in_params = {
            &hDevice,
            &pCount,
            &phSubdevices
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetSubDevicesCb )
                    table.pfnGetSubDevicesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetSubDevices( hDevice, pCount, phSubdevices );

        // capture parameters
        xe_device_get_sub_devices_params_t out_params = {
            &hDevice,
            &pCount,
            &phSubdevices
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetSubDevicesCb )
                    table.pfnGetSubDevicesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetProperties
    xe_result_t __xecall
    xeDeviceGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_device_get_properties_params_t in_params = {
            &hDevice,
            &pDeviceProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetProperties( hDevice, pDeviceProperties );

        // capture parameters
        xe_device_get_properties_params_t out_params = {
            &hDevice,
            &pDeviceProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetComputeProperties
    xe_result_t __xecall
    xeDeviceGetComputeProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_device_get_compute_properties_params_t in_params = {
            &hDevice,
            &pComputeProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetComputePropertiesCb )
                    table.pfnGetComputePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetComputeProperties( hDevice, pComputeProperties );

        // capture parameters
        xe_device_get_compute_properties_params_t out_params = {
            &hDevice,
            &pComputeProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetComputePropertiesCb )
                    table.pfnGetComputePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetMemoryProperties
    xe_result_t __xecall
    xeDeviceGetMemoryProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
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

        // capture parameters
        xe_device_get_memory_properties_params_t in_params = {
            &hDevice,
            &pCount,
            &pMemProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetMemoryPropertiesCb )
                    table.pfnGetMemoryPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetMemoryProperties( hDevice, pCount, pMemProperties );

        // capture parameters
        xe_device_get_memory_properties_params_t out_params = {
            &hDevice,
            &pCount,
            &pMemProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetMemoryPropertiesCb )
                    table.pfnGetMemoryPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetMemoryAccessProperties
    xe_result_t __xecall
    xeDeviceGetMemoryAccessProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_memory_access_properties_t* pMemAccessProperties  ///< [out] query result for memory access properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_device_get_memory_access_properties_params_t in_params = {
            &hDevice,
            &pMemAccessProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                    table.pfnGetMemoryAccessPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetMemoryAccessProperties( hDevice, pMemAccessProperties );

        // capture parameters
        xe_device_get_memory_access_properties_params_t out_params = {
            &hDevice,
            &pMemAccessProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                    table.pfnGetMemoryAccessPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetCacheProperties
    xe_result_t __xecall
    xeDeviceGetCacheProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_cache_properties_t* pCacheProperties  ///< [out] query result for cache properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_device_get_cache_properties_params_t in_params = {
            &hDevice,
            &pCacheProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetCachePropertiesCb )
                    table.pfnGetCachePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetCacheProperties( hDevice, pCacheProperties );

        // capture parameters
        xe_device_get_cache_properties_params_t out_params = {
            &hDevice,
            &pCacheProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetCachePropertiesCb )
                    table.pfnGetCachePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGetImageProperties
    xe_result_t __xecall
    xeDeviceGetImageProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_image_properties_t* pImageProperties  ///< [out] query result for image properties
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_device_get_image_properties_params_t in_params = {
            &hDevice,
            &pImageProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetImagePropertiesCb )
                    table.pfnGetImagePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetImageProperties( hDevice, pImageProperties );

        // capture parameters
        xe_device_get_image_properties_params_t out_params = {
            &hDevice,
            &pImageProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetImagePropertiesCb )
                    table.pfnGetImagePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_get_p2_p_properties_params_t in_params = {
            &hDevice,
            &hPeerDevice,
            &pP2PProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnGetP2PPropertiesCb )
                    table.pfnGetP2PPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );

        // capture parameters
        xe_device_get_p2_p_properties_params_t out_params = {
            &hDevice,
            &hPeerDevice,
            &pP2PProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnGetP2PPropertiesCb )
                    table.pfnGetP2PPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_can_access_peer_params_t in_params = {
            &hDevice,
            &hPeerDevice,
            &value
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnCanAccessPeerCb )
                    table.pfnCanAccessPeerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceCanAccessPeer( hDevice, hPeerDevice, value );

        // capture parameters
        xe_device_can_access_peer_params_t out_params = {
            &hDevice,
            &hPeerDevice,
            &value
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnCanAccessPeerCb )
                    table.pfnCanAccessPeerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_set_intermediate_cache_config_params_t in_params = {
            &hDevice,
            &CacheConfig
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnSetIntermediateCacheConfigCb )
                    table.pfnSetIntermediateCacheConfigCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceSetIntermediateCacheConfig( hDevice, CacheConfig );

        // capture parameters
        xe_device_set_intermediate_cache_config_params_t out_params = {
            &hDevice,
            &CacheConfig
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnSetIntermediateCacheConfigCb )
                    table.pfnSetIntermediateCacheConfigCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_set_last_level_cache_config_params_t in_params = {
            &hDevice,
            &CacheConfig
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnSetLastLevelCacheConfigCb )
                    table.pfnSetLastLevelCacheConfigCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceSetLastLevelCacheConfig( hDevice, CacheConfig );

        // capture parameters
        xe_device_set_last_level_cache_config_params_t out_params = {
            &hDevice,
            &CacheConfig
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnSetLastLevelCacheConfigCb )
                    table.pfnSetLastLevelCacheConfigCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_queue_create_params_t in_params = {
            &hDevice,
            &desc,
            &phCommandQueue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandQueueCreate( hDevice, desc, phCommandQueue );

        // capture parameters
        xe_command_queue_create_params_t out_params = {
            &hDevice,
            &desc,
            &phCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_queue_destroy_params_t in_params = {
            &hCommandQueue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandQueueDestroy( hCommandQueue );

        // capture parameters
        xe_command_queue_destroy_params_t out_params = {
            &hCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_queue_execute_command_lists_params_t in_params = {
            &hCommandQueue,
            &numCommandLists,
            &phCommandLists,
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                if( nullptr != table.pfnExecuteCommandListsCb )
                    table.pfnExecuteCommandListsCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandQueueExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );

        // capture parameters
        xe_command_queue_execute_command_lists_params_t out_params = {
            &hCommandQueue,
            &numCommandLists,
            &phCommandLists,
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnExecuteCommandListsCb )
                    table.pfnExecuteCommandListsCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_command_queue_synchronize_params_t in_params = {
            &hCommandQueue,
            &timeout
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                if( nullptr != table.pfnSynchronizeCb )
                    table.pfnSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandQueueSynchronize( hCommandQueue, timeout );

        // capture parameters
        xe_command_queue_synchronize_params_t out_params = {
            &hCommandQueue,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnSynchronizeCb )
                    table.pfnSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_create_params_t in_params = {
            &hDevice,
            &desc,
            &phCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListCreate( hDevice, desc, phCommandList );

        // capture parameters
        xe_command_list_create_params_t out_params = {
            &hDevice,
            &desc,
            &phCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_create_immediate_params_t in_params = {
            &hDevice,
            &altdesc,
            &phCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnCreateImmediateCb )
                    table.pfnCreateImmediateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListCreateImmediate( hDevice, altdesc, phCommandList );

        // capture parameters
        xe_command_list_create_immediate_params_t out_params = {
            &hDevice,
            &altdesc,
            &phCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCreateImmediateCb )
                    table.pfnCreateImmediateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_destroy_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListDestroy( hCommandList );

        // capture parameters
        xe_command_list_destroy_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_close_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListClose( hCommandList );

        // capture parameters
        xe_command_list_close_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_reset_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListReset( hCommandList );

        // capture parameters
        xe_command_list_reset_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_barrier_params_t in_params = {
            &hCommandList,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendBarrierCb )
                    table.pfnAppendBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        xe_command_list_append_barrier_params_t out_params = {
            &hCommandList,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendBarrierCb )
                    table.pfnAppendBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_memory_ranges_barrier_params_t in_params = {
            &hCommandList,
            &numRanges,
            &pRangeSizes,
            &pRanges,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                    table.pfnAppendMemoryRangesBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        xe_command_list_append_memory_ranges_barrier_params_t out_params = {
            &hCommandList,
            &numRanges,
            &pRangeSizes,
            &pRanges,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                    table.pfnAppendMemoryRangesBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_system_barrier_params_t in_params = {
            &hDevice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnSystemBarrierCb )
                    table.pfnSystemBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceSystemBarrier( hDevice );

        // capture parameters
        xe_device_system_barrier_params_t out_params = {
            &hDevice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnSystemBarrierCb )
                    table.pfnSystemBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_register_cl_memory_params_t in_params = {
            &hDevice,
            &context,
            &mem,
            &ptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnRegisterCLMemoryCb )
                    table.pfnRegisterCLMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceRegisterCLMemory( hDevice, context, mem, ptr );

        // capture parameters
        xe_device_register_cl_memory_params_t out_params = {
            &hDevice,
            &context,
            &mem,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnRegisterCLMemoryCb )
                    table.pfnRegisterCLMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_register_cl_program_params_t in_params = {
            &hDevice,
            &context,
            &program,
            &phModule
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnRegisterCLProgramCb )
                    table.pfnRegisterCLProgramCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceRegisterCLProgram( hDevice, context, program, phModule );

        // capture parameters
        xe_device_register_cl_program_params_t out_params = {
            &hDevice,
            &context,
            &program,
            &phModule
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnRegisterCLProgramCb )
                    table.pfnRegisterCLProgramCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_register_cl_command_queue_params_t in_params = {
            &hDevice,
            &context,
            &command_queue,
            &phCommandQueue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnRegisterCLCommandQueueCb )
                    table.pfnRegisterCLCommandQueueCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );

        // capture parameters
        xe_device_register_cl_command_queue_params_t out_params = {
            &hDevice,
            &context,
            &command_queue,
            &phCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnRegisterCLCommandQueueCb )
                    table.pfnRegisterCLCommandQueueCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_memory_copy_params_t in_params = {
            &hCommandList,
            &dstptr,
            &srcptr,
            &size,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyCb )
                    table.pfnAppendMemoryCopyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );

        // capture parameters
        xe_command_list_append_memory_copy_params_t out_params = {
            &hCommandList,
            &dstptr,
            &srcptr,
            &size,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyCb )
                    table.pfnAppendMemoryCopyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_memory_set_params_t in_params = {
            &hCommandList,
            &ptr,
            &value,
            &size,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemorySetCb )
                    table.pfnAppendMemorySetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendMemorySet( hCommandList, ptr, value, size, hEvent );

        // capture parameters
        xe_command_list_append_memory_set_params_t out_params = {
            &hCommandList,
            &ptr,
            &value,
            &size,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemorySetCb )
                    table.pfnAppendMemorySetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        xe_command_list_append_memory_copy_region_params_t in_params = {
            &hCommandList,
            &dstptr,
            &dstRegion,
            &dstPitch,
            &srcptr,
            &srcRegion,
            &srcPitch,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                    table.pfnAppendMemoryCopyRegionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );

        // capture parameters
        xe_command_list_append_memory_copy_region_params_t out_params = {
            &hCommandList,
            &dstptr,
            &dstRegion,
            &dstPitch,
            &srcptr,
            &srcRegion,
            &srcPitch,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                    table.pfnAppendMemoryCopyRegionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_image_copy_params_t in_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyCb )
                    table.pfnAppendImageCopyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );

        // capture parameters
        xe_command_list_append_image_copy_params_t out_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyCb )
                    table.pfnAppendImageCopyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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
        const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_command_list_append_image_copy_region_params_t in_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &pDstRegion,
            &pSrcRegion,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyRegionCb )
                    table.pfnAppendImageCopyRegionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );

        // capture parameters
        xe_command_list_append_image_copy_region_params_t out_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &pDstRegion,
            &pSrcRegion,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyRegionCb )
                    table.pfnAppendImageCopyRegionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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
        const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_command_list_append_image_copy_to_memory_params_t in_params = {
            &hCommandList,
            &dstptr,
            &hSrcImage,
            &pSrcRegion,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                    table.pfnAppendImageCopyToMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );

        // capture parameters
        xe_command_list_append_image_copy_to_memory_params_t out_params = {
            &hCommandList,
            &dstptr,
            &hSrcImage,
            &pSrcRegion,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                    table.pfnAppendImageCopyToMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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
        const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_command_list_append_image_copy_from_memory_params_t in_params = {
            &hCommandList,
            &hDstImage,
            &srcptr,
            &pDstRegion,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                    table.pfnAppendImageCopyFromMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );

        // capture parameters
        xe_command_list_append_image_copy_from_memory_params_t out_params = {
            &hCommandList,
            &hDstImage,
            &srcptr,
            &pDstRegion,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                    table.pfnAppendImageCopyFromMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_memory_prefetch_params_t in_params = {
            &hCommandList,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryPrefetchCb )
                    table.pfnAppendMemoryPrefetchCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendMemoryPrefetch( hCommandList, ptr, size );

        // capture parameters
        xe_command_list_append_memory_prefetch_params_t out_params = {
            &hCommandList,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryPrefetchCb )
                    table.pfnAppendMemoryPrefetchCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_mem_advise_params_t in_params = {
            &hCommandList,
            &hDevice,
            &ptr,
            &size,
            &advice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemAdviseCb )
                    table.pfnAppendMemAdviseCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );

        // capture parameters
        xe_command_list_append_mem_advise_params_t out_params = {
            &hCommandList,
            &hDevice,
            &ptr,
            &size,
            &advice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemAdviseCb )
                    table.pfnAppendMemAdviseCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolCreate
    xe_result_t __xecall
    xeEventPoolCreate(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        xe_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_event_pool_create_params_t in_params = {
            &hDriver,
            &desc,
            &numDevices,
            &phDevices,
            &phEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventPoolCreate( hDriver, desc, numDevices, phDevices, phEventPool );

        // capture parameters
        xe_event_pool_create_params_t out_params = {
            &hDriver,
            &desc,
            &numDevices,
            &phDevices,
            &phEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_pool_destroy_params_t in_params = {
            &hEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventPoolDestroy( hEventPool );

        // capture parameters
        xe_event_pool_destroy_params_t out_params = {
            &hEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_create_params_t in_params = {
            &hEventPool,
            &desc,
            &phEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventCreate( hEventPool, desc, phEvent );

        // capture parameters
        xe_event_create_params_t out_params = {
            &hEventPool,
            &desc,
            &phEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_destroy_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventDestroy( hEvent );

        // capture parameters
        xe_event_destroy_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_pool_get_ipc_handle_params_t in_params = {
            &hEventPool,
            &phIpc
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventPoolGetIpcHandle( hEventPool, phIpc );

        // capture parameters
        xe_event_pool_get_ipc_handle_params_t out_params = {
            &hEventPool,
            &phIpc
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolOpenIpcHandle
    xe_result_t __xecall
    xeEventPoolOpenIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver to associate with the IPC event pool handle
        xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_event_pool_open_ipc_handle_params_t in_params = {
            &hDriver,
            &hIpc,
            &phEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventPoolOpenIpcHandle( hDriver, hIpc, phEventPool );

        // capture parameters
        xe_event_pool_open_ipc_handle_params_t out_params = {
            &hDriver,
            &hIpc,
            &phEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_pool_close_ipc_handle_params_t in_params = {
            &hEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventPoolCloseIpcHandle( hEventPool );

        // capture parameters
        xe_event_pool_close_ipc_handle_params_t out_params = {
            &hEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_signal_event_params_t in_params = {
            &hCommandList,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendSignalEventCb )
                    table.pfnAppendSignalEventCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendSignalEvent( hCommandList, hEvent );

        // capture parameters
        xe_command_list_append_signal_event_params_t out_params = {
            &hCommandList,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendSignalEventCb )
                    table.pfnAppendSignalEventCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_wait_on_events_params_t in_params = {
            &hCommandList,
            &numEvents,
            &phEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendWaitOnEventsCb )
                    table.pfnAppendWaitOnEventsCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendWaitOnEvents( hCommandList, numEvents, phEvents );

        // capture parameters
        xe_command_list_append_wait_on_events_params_t out_params = {
            &hCommandList,
            &numEvents,
            &phEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendWaitOnEventsCb )
                    table.pfnAppendWaitOnEventsCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_host_signal_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                if( nullptr != table.pfnHostSignalCb )
                    table.pfnHostSignalCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventHostSignal( hEvent );

        // capture parameters
        xe_event_host_signal_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                if( nullptr != table.pfnHostSignalCb )
                    table.pfnHostSignalCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_event_host_synchronize_params_t in_params = {
            &hEvent,
            &timeout
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventHostSynchronize( hEvent, timeout );

        // capture parameters
        xe_event_host_synchronize_params_t out_params = {
            &hEvent,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_query_status_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventQueryStatus( hEvent );

        // capture parameters
        xe_event_query_status_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_event_reset_params_t in_params = {
            &hCommandList,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendEventResetCb )
                    table.pfnAppendEventResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendEventReset( hCommandList, hEvent );

        // capture parameters
        xe_command_list_append_event_reset_params_t out_params = {
            &hCommandList,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendEventResetCb )
                    table.pfnAppendEventResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_event_reset_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeEventReset( hEvent );

        // capture parameters
        xe_event_reset_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_fence_create_params_t in_params = {
            &hCommandQueue,
            &desc,
            &phFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFenceCreate( hCommandQueue, desc, phFence );

        // capture parameters
        xe_fence_create_params_t out_params = {
            &hCommandQueue,
            &desc,
            &phFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_fence_destroy_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFenceDestroy( hFence );

        // capture parameters
        xe_fence_destroy_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_fence_host_synchronize_params_t in_params = {
            &hFence,
            &timeout
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFenceHostSynchronize( hFence, timeout );

        // capture parameters
        xe_fence_host_synchronize_params_t out_params = {
            &hFence,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_fence_query_status_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFenceQueryStatus( hFence );

        // capture parameters
        xe_fence_query_status_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_fence_reset_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFenceReset( hFence );

        // capture parameters
        xe_fence_reset_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_image_get_properties_params_t in_params = {
            &hDevice,
            &desc,
            &pImageProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Image;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeImageGetProperties( hDevice, desc, pImageProperties );

        // capture parameters
        xe_image_get_properties_params_t out_params = {
            &hDevice,
            &desc,
            &pImageProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Image;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_image_create_params_t in_params = {
            &hDevice,
            &desc,
            &phImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Image;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeImageCreate( hDevice, desc, phImage );

        // capture parameters
        xe_image_create_params_t out_params = {
            &hDevice,
            &desc,
            &phImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Image;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_image_destroy_params_t in_params = {
            &hImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Image;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeImageDestroy( hImage );

        // capture parameters
        xe_image_destroy_params_t out_params = {
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Image;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverAllocSharedMem
    xe_result_t __xecall
    xeDriverAllocSharedMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_device_handle_t hDevice,                     ///< [in] handle of a device
        xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
        xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_alloc_shared_mem_params_t in_params = {
            &hDriver,
            &hDevice,
            &device_flags,
            &ordinal,
            &host_flags,
            &size,
            &alignment,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnAllocSharedMemCb )
                    table.pfnAllocSharedMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverAllocSharedMem( hDriver, hDevice, device_flags, ordinal, host_flags, size, alignment, pptr );

        // capture parameters
        xe_driver_alloc_shared_mem_params_t out_params = {
            &hDriver,
            &hDevice,
            &device_flags,
            &ordinal,
            &host_flags,
            &size,
            &alignment,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnAllocSharedMemCb )
                    table.pfnAllocSharedMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverAllocDeviceMem
    xe_result_t __xecall
    xeDriverAllocDeviceMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::xeDeviceGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_alloc_device_mem_params_t in_params = {
            &hDriver,
            &hDevice,
            &flags,
            &ordinal,
            &size,
            &alignment,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnAllocDeviceMemCb )
                    table.pfnAllocDeviceMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverAllocDeviceMem( hDriver, hDevice, flags, ordinal, size, alignment, pptr );

        // capture parameters
        xe_driver_alloc_device_mem_params_t out_params = {
            &hDriver,
            &hDevice,
            &flags,
            &ordinal,
            &size,
            &alignment,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnAllocDeviceMemCb )
                    table.pfnAllocDeviceMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverAllocHostMem
    xe_result_t __xecall
    xeDriverAllocHostMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_alloc_host_mem_params_t in_params = {
            &hDriver,
            &flags,
            &size,
            &alignment,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnAllocHostMemCb )
                    table.pfnAllocHostMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverAllocHostMem( hDriver, flags, size, alignment, pptr );

        // capture parameters
        xe_driver_alloc_host_mem_params_t out_params = {
            &hDriver,
            &flags,
            &size,
            &alignment,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnAllocHostMemCb )
                    table.pfnAllocHostMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverFreeMem
    xe_result_t __xecall
    xeDriverFreeMem(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_free_mem_params_t in_params = {
            &hDriver,
            &ptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnFreeMemCb )
                    table.pfnFreeMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverFreeMem( hDriver, ptr );

        // capture parameters
        xe_driver_free_mem_params_t out_params = {
            &hDriver,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnFreeMemCb )
                    table.pfnFreeMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetMemProperties
    xe_result_t __xecall
    xeDriverGetMemProperties(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        xe_memory_allocation_properties_t* pMemProperties,  ///< [out] query result for memory allocation properties
        xe_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_get_mem_properties_params_t in_params = {
            &hDriver,
            &ptr,
            &pMemProperties,
            &phDevice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnGetMemPropertiesCb )
                    table.pfnGetMemPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverGetMemProperties( hDriver, ptr, pMemProperties, phDevice );

        // capture parameters
        xe_driver_get_mem_properties_params_t out_params = {
            &hDriver,
            &ptr,
            &pMemProperties,
            &phDevice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetMemPropertiesCb )
                    table.pfnGetMemPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetMemAddressRange
    xe_result_t __xecall
    xeDriverGetMemAddressRange(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_get_mem_address_range_params_t in_params = {
            &hDriver,
            &ptr,
            &pBase,
            &pSize
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnGetMemAddressRangeCb )
                    table.pfnGetMemAddressRangeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverGetMemAddressRange( hDriver, ptr, pBase, pSize );

        // capture parameters
        xe_driver_get_mem_address_range_params_t out_params = {
            &hDriver,
            &ptr,
            &pBase,
            &pSize
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetMemAddressRangeCb )
                    table.pfnGetMemAddressRangeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverGetMemIpcHandle
    xe_result_t __xecall
    xeDriverGetMemIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_get_mem_ipc_handle_params_t in_params = {
            &hDriver,
            &ptr,
            &pIpcHandle
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnGetMemIpcHandleCb )
                    table.pfnGetMemIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverGetMemIpcHandle( hDriver, ptr, pIpcHandle );

        // capture parameters
        xe_driver_get_mem_ipc_handle_params_t out_params = {
            &hDriver,
            &ptr,
            &pIpcHandle
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetMemIpcHandleCb )
                    table.pfnGetMemIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverOpenMemIpcHandle
    xe_result_t __xecall
    xeDriverOpenMemIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_open_mem_ipc_handle_params_t in_params = {
            &hDriver,
            &hDevice,
            &handle,
            &flags,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnOpenMemIpcHandleCb )
                    table.pfnOpenMemIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverOpenMemIpcHandle( hDriver, hDevice, handle, flags, pptr );

        // capture parameters
        xe_driver_open_mem_ipc_handle_params_t out_params = {
            &hDriver,
            &hDevice,
            &handle,
            &flags,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnOpenMemIpcHandleCb )
                    table.pfnOpenMemIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDriverCloseMemIpcHandle
    xe_result_t __xecall
    xeDriverCloseMemIpcHandle(
        xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xe_driver_close_mem_ipc_handle_params_t in_params = {
            &hDriver,
            &ptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Driver;
                if( nullptr != table.pfnCloseMemIpcHandleCb )
                    table.pfnCloseMemIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDriverCloseMemIpcHandle( hDriver, ptr );

        // capture parameters
        xe_driver_close_mem_ipc_handle_params_t out_params = {
            &hDriver,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Driver;
                if( nullptr != table.pfnCloseMemIpcHandleCb )
                    table.pfnCloseMemIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_module_create_params_t in_params = {
            &hDevice,
            &desc,
            &phModule,
            &phBuildLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeModuleCreate( hDevice, desc, phModule, phBuildLog );

        // capture parameters
        xe_module_create_params_t out_params = {
            &hDevice,
            &desc,
            &phModule,
            &phBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_module_destroy_params_t in_params = {
            &hModule
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeModuleDestroy( hModule );

        // capture parameters
        xe_module_destroy_params_t out_params = {
            &hModule
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_module_build_log_destroy_params_t in_params = {
            &hModuleBuildLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.ModuleBuildLog;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeModuleBuildLogDestroy( hModuleBuildLog );

        // capture parameters
        xe_module_build_log_destroy_params_t out_params = {
            &hModuleBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.ModuleBuildLog;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_module_build_log_get_string_params_t in_params = {
            &hModuleBuildLog,
            &pSize,
            &pBuildLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.ModuleBuildLog;
                if( nullptr != table.pfnGetStringCb )
                    table.pfnGetStringCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeModuleBuildLogGetString( hModuleBuildLog, pSize, pBuildLog );

        // capture parameters
        xe_module_build_log_get_string_params_t out_params = {
            &hModuleBuildLog,
            &pSize,
            &pBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.ModuleBuildLog;
                if( nullptr != table.pfnGetStringCb )
                    table.pfnGetStringCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_module_get_native_binary_params_t in_params = {
            &hModule,
            &pSize,
            &pModuleNativeBinary
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                if( nullptr != table.pfnGetNativeBinaryCb )
                    table.pfnGetNativeBinaryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeModuleGetNativeBinary( hModule, pSize, pModuleNativeBinary );

        // capture parameters
        xe_module_get_native_binary_params_t out_params = {
            &hModule,
            &pSize,
            &pModuleNativeBinary
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                if( nullptr != table.pfnGetNativeBinaryCb )
                    table.pfnGetNativeBinaryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        xe_module_get_global_pointer_params_t in_params = {
            &hModule,
            &pGlobalName,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                if( nullptr != table.pfnGetGlobalPointerCb )
                    table.pfnGetGlobalPointerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeModuleGetGlobalPointer( hModule, pGlobalName, pptr );

        // capture parameters
        xe_module_get_global_pointer_params_t out_params = {
            &hModule,
            &pGlobalName,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                if( nullptr != table.pfnGetGlobalPointerCb )
                    table.pfnGetGlobalPointerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_function_create_params_t in_params = {
            &hModule,
            &desc,
            &phFunction
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFunctionCreate( hModule, desc, phFunction );

        // capture parameters
        xe_function_create_params_t out_params = {
            &hModule,
            &desc,
            &phFunction
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_function_destroy_params_t in_params = {
            &hFunction
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFunctionDestroy( hFunction );

        // capture parameters
        xe_function_destroy_params_t out_params = {
            &hFunction
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_module_get_function_pointer_params_t in_params = {
            &hModule,
            &pFunctionName,
            &pfnFunction
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                if( nullptr != table.pfnGetFunctionPointerCb )
                    table.pfnGetFunctionPointerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeModuleGetFunctionPointer( hModule, pFunctionName, pfnFunction );

        // capture parameters
        xe_module_get_function_pointer_params_t out_params = {
            &hModule,
            &pFunctionName,
            &pfnFunction
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                if( nullptr != table.pfnGetFunctionPointerCb )
                    table.pfnGetFunctionPointerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_function_set_group_size_params_t in_params = {
            &hFunction,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                if( nullptr != table.pfnSetGroupSizeCb )
                    table.pfnSetGroupSizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFunctionSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );

        // capture parameters
        xe_function_set_group_size_params_t out_params = {
            &hFunction,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                if( nullptr != table.pfnSetGroupSizeCb )
                    table.pfnSetGroupSizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_function_suggest_group_size_params_t in_params = {
            &hFunction,
            &globalSizeX,
            &globalSizeY,
            &globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                if( nullptr != table.pfnSuggestGroupSizeCb )
                    table.pfnSuggestGroupSizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFunctionSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );

        // capture parameters
        xe_function_suggest_group_size_params_t out_params = {
            &hFunction,
            &globalSizeX,
            &globalSizeY,
            &globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                if( nullptr != table.pfnSuggestGroupSizeCb )
                    table.pfnSuggestGroupSizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_function_set_argument_value_params_t in_params = {
            &hFunction,
            &argIndex,
            &argSize,
            &pArgValue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                if( nullptr != table.pfnSetArgumentValueCb )
                    table.pfnSetArgumentValueCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFunctionSetArgumentValue( hFunction, argIndex, argSize, pArgValue );

        // capture parameters
        xe_function_set_argument_value_params_t out_params = {
            &hFunction,
            &argIndex,
            &argSize,
            &pArgValue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                if( nullptr != table.pfnSetArgumentValueCb )
                    table.pfnSetArgumentValueCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_function_set_attribute_params_t in_params = {
            &hFunction,
            &attr,
            &value
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                if( nullptr != table.pfnSetAttributeCb )
                    table.pfnSetAttributeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFunctionSetAttribute( hFunction, attr, value );

        // capture parameters
        xe_function_set_attribute_params_t out_params = {
            &hFunction,
            &attr,
            &value
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                if( nullptr != table.pfnSetAttributeCb )
                    table.pfnSetAttributeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_function_get_attribute_params_t in_params = {
            &hFunction,
            &attr,
            &pValue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                if( nullptr != table.pfnGetAttributeCb )
                    table.pfnGetAttributeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeFunctionGetAttribute( hFunction, attr, pValue );

        // capture parameters
        xe_function_get_attribute_params_t out_params = {
            &hFunction,
            &attr,
            &pValue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                if( nullptr != table.pfnGetAttributeCb )
                    table.pfnGetAttributeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_launch_function_params_t in_params = {
            &hCommandList,
            &hFunction,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchFunctionCb )
                    table.pfnAppendLaunchFunctionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        xe_command_list_append_launch_function_params_t out_params = {
            &hCommandList,
            &hFunction,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchFunctionCb )
                    table.pfnAppendLaunchFunctionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_launch_function_indirect_params_t in_params = {
            &hCommandList,
            &hFunction,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchFunctionIndirectCb )
                    table.pfnAppendLaunchFunctionIndirectCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        xe_command_list_append_launch_function_indirect_params_t out_params = {
            &hCommandList,
            &hFunction,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchFunctionIndirectCb )
                    table.pfnAppendLaunchFunctionIndirectCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_launch_multiple_functions_indirect_params_t in_params = {
            &hCommandList,
            &numFunctions,
            &phFunctions,
            &pNumLaunchArguments,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchMultipleFunctionsIndirectCb )
                    table.pfnAppendLaunchMultipleFunctionsIndirectCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        xe_command_list_append_launch_multiple_functions_indirect_params_t out_params = {
            &hCommandList,
            &numFunctions,
            &phFunctions,
            &pNumLaunchArguments,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchMultipleFunctionsIndirectCb )
                    table.pfnAppendLaunchMultipleFunctionsIndirectCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_command_list_append_launch_host_function_params_t in_params = {
            &hCommandList,
            &pfnHostFunc,
            &pUserData,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchHostFunctionCb )
                    table.pfnAppendLaunchHostFunctionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeCommandListAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        xe_command_list_append_launch_host_function_params_t out_params = {
            &hCommandList,
            &pfnHostFunc,
            &pUserData,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchHostFunctionCb )
                    table.pfnAppendLaunchHostFunctionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_make_memory_resident_params_t in_params = {
            &hDevice,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnMakeMemoryResidentCb )
                    table.pfnMakeMemoryResidentCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceMakeMemoryResident( hDevice, ptr, size );

        // capture parameters
        xe_device_make_memory_resident_params_t out_params = {
            &hDevice,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnMakeMemoryResidentCb )
                    table.pfnMakeMemoryResidentCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_evict_memory_params_t in_params = {
            &hDevice,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnEvictMemoryCb )
                    table.pfnEvictMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceEvictMemory( hDevice, ptr, size );

        // capture parameters
        xe_device_evict_memory_params_t out_params = {
            &hDevice,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnEvictMemoryCb )
                    table.pfnEvictMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_make_image_resident_params_t in_params = {
            &hDevice,
            &hImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnMakeImageResidentCb )
                    table.pfnMakeImageResidentCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceMakeImageResident( hDevice, hImage );

        // capture parameters
        xe_device_make_image_resident_params_t out_params = {
            &hDevice,
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnMakeImageResidentCb )
                    table.pfnMakeImageResidentCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_device_evict_image_params_t in_params = {
            &hDevice,
            &hImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                if( nullptr != table.pfnEvictImageCb )
                    table.pfnEvictImageCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeDeviceEvictImage( hDevice, hImage );

        // capture parameters
        xe_device_evict_image_params_t out_params = {
            &hDevice,
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                if( nullptr != table.pfnEvictImageCb )
                    table.pfnEvictImageCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_sampler_create_params_t in_params = {
            &hDevice,
            &desc,
            &phSampler
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Sampler;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeSamplerCreate( hDevice, desc, phSampler );

        // capture parameters
        xe_sampler_create_params_t out_params = {
            &hDevice,
            &desc,
            &phSampler
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Sampler;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        xe_sampler_destroy_params_t in_params = {
            &hSampler
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xePrologueCbs.Sampler;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::xeSamplerDestroy( hSampler );

        // capture parameters
        xe_sampler_destroy_params_t out_params = {
            &hSampler
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xeEpilogueCbs.Sampler;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

} // namespace instrumented

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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnInit                                   = instrumented::xeInit;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGet                                    = instrumented::xeDeviceGet;
    else
        pDdiTable->pfnGet                                    = driver::xeDeviceGet;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetSubDevices                          = instrumented::xeDeviceGetSubDevices;
    else
        pDdiTable->pfnGetSubDevices                          = driver::xeDeviceGetSubDevices;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::xeDeviceGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::xeDeviceGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetComputeProperties                   = instrumented::xeDeviceGetComputeProperties;
    else
        pDdiTable->pfnGetComputeProperties                   = driver::xeDeviceGetComputeProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemoryProperties                    = instrumented::xeDeviceGetMemoryProperties;
    else
        pDdiTable->pfnGetMemoryProperties                    = driver::xeDeviceGetMemoryProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemoryAccessProperties              = instrumented::xeDeviceGetMemoryAccessProperties;
    else
        pDdiTable->pfnGetMemoryAccessProperties              = driver::xeDeviceGetMemoryAccessProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetCacheProperties                     = instrumented::xeDeviceGetCacheProperties;
    else
        pDdiTable->pfnGetCacheProperties                     = driver::xeDeviceGetCacheProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetImageProperties                     = instrumented::xeDeviceGetImageProperties;
    else
        pDdiTable->pfnGetImageProperties                     = driver::xeDeviceGetImageProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetP2PProperties                       = instrumented::xeDeviceGetP2PProperties;
    else
        pDdiTable->pfnGetP2PProperties                       = driver::xeDeviceGetP2PProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCanAccessPeer                          = instrumented::xeDeviceCanAccessPeer;
    else
        pDdiTable->pfnCanAccessPeer                          = driver::xeDeviceCanAccessPeer;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetIntermediateCacheConfig             = instrumented::xeDeviceSetIntermediateCacheConfig;
    else
        pDdiTable->pfnSetIntermediateCacheConfig             = driver::xeDeviceSetIntermediateCacheConfig;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetLastLevelCacheConfig                = instrumented::xeDeviceSetLastLevelCacheConfig;
    else
        pDdiTable->pfnSetLastLevelCacheConfig                = driver::xeDeviceSetLastLevelCacheConfig;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSystemBarrier                          = instrumented::xeDeviceSystemBarrier;
    else
        pDdiTable->pfnSystemBarrier                          = driver::xeDeviceSystemBarrier;

#if XE_ENABLE_OCL_INTEROP
    if( instrumented::context.enableTracing )
        pDdiTable->pfnRegisterCLMemory                       = instrumented::xeDeviceRegisterCLMemory;
    else
        pDdiTable->pfnRegisterCLMemory                       = driver::xeDeviceRegisterCLMemory;
#endif

#if XE_ENABLE_OCL_INTEROP
    if( instrumented::context.enableTracing )
        pDdiTable->pfnRegisterCLProgram                      = instrumented::xeDeviceRegisterCLProgram;
    else
        pDdiTable->pfnRegisterCLProgram                      = driver::xeDeviceRegisterCLProgram;
#endif

#if XE_ENABLE_OCL_INTEROP
    if( instrumented::context.enableTracing )
        pDdiTable->pfnRegisterCLCommandQueue                 = instrumented::xeDeviceRegisterCLCommandQueue;
    else
        pDdiTable->pfnRegisterCLCommandQueue                 = driver::xeDeviceRegisterCLCommandQueue;
#endif

    if( instrumented::context.enableTracing )
        pDdiTable->pfnMakeMemoryResident                     = instrumented::xeDeviceMakeMemoryResident;
    else
        pDdiTable->pfnMakeMemoryResident                     = driver::xeDeviceMakeMemoryResident;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnEvictMemory                            = instrumented::xeDeviceEvictMemory;
    else
        pDdiTable->pfnEvictMemory                            = driver::xeDeviceEvictMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnMakeImageResident                      = instrumented::xeDeviceMakeImageResident;
    else
        pDdiTable->pfnMakeImageResident                      = driver::xeDeviceMakeImageResident;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnEvictImage                             = instrumented::xeDeviceEvictImage;
    else
        pDdiTable->pfnEvictImage                             = driver::xeDeviceEvictImage;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
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
xeGetDriverProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGet                                    = instrumented::xeDriverGet;
    else
        pDdiTable->pfnGet                                    = driver::xeDriverGet;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetDriverVersion                       = instrumented::xeDriverGetDriverVersion;
    else
        pDdiTable->pfnGetDriverVersion                       = driver::xeDriverGetDriverVersion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetApiVersion                          = instrumented::xeDriverGetApiVersion;
    else
        pDdiTable->pfnGetApiVersion                          = driver::xeDriverGetApiVersion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIPCProperties                       = instrumented::xeDriverGetIPCProperties;
    else
        pDdiTable->pfnGetIPCProperties                       = driver::xeDriverGetIPCProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocSharedMem                         = instrumented::xeDriverAllocSharedMem;
    else
        pDdiTable->pfnAllocSharedMem                         = driver::xeDriverAllocSharedMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocDeviceMem                         = instrumented::xeDriverAllocDeviceMem;
    else
        pDdiTable->pfnAllocDeviceMem                         = driver::xeDriverAllocDeviceMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocHostMem                           = instrumented::xeDriverAllocHostMem;
    else
        pDdiTable->pfnAllocHostMem                           = driver::xeDriverAllocHostMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnFreeMem                                = instrumented::xeDriverFreeMem;
    else
        pDdiTable->pfnFreeMem                                = driver::xeDriverFreeMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemProperties                       = instrumented::xeDriverGetMemProperties;
    else
        pDdiTable->pfnGetMemProperties                       = driver::xeDriverGetMemProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemAddressRange                     = instrumented::xeDriverGetMemAddressRange;
    else
        pDdiTable->pfnGetMemAddressRange                     = driver::xeDriverGetMemAddressRange;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemIpcHandle                        = instrumented::xeDriverGetMemIpcHandle;
    else
        pDdiTable->pfnGetMemIpcHandle                        = driver::xeDriverGetMemIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnOpenMemIpcHandle                       = instrumented::xeDriverOpenMemIpcHandle;
    else
        pDdiTable->pfnOpenMemIpcHandle                       = driver::xeDriverOpenMemIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCloseMemIpcHandle                      = instrumented::xeDriverCloseMemIpcHandle;
    else
        pDdiTable->pfnCloseMemIpcHandle                      = driver::xeDriverCloseMemIpcHandle;

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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeCommandQueueCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeCommandQueueCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeCommandQueueDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeCommandQueueDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnExecuteCommandLists                    = instrumented::xeCommandQueueExecuteCommandLists;
    else
        pDdiTable->pfnExecuteCommandLists                    = driver::xeCommandQueueExecuteCommandLists;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSynchronize                            = instrumented::xeCommandQueueSynchronize;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeCommandListCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeCommandListCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreateImmediate                        = instrumented::xeCommandListCreateImmediate;
    else
        pDdiTable->pfnCreateImmediate                        = driver::xeCommandListCreateImmediate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeCommandListDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeCommandListDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnClose                                  = instrumented::xeCommandListClose;
    else
        pDdiTable->pfnClose                                  = driver::xeCommandListClose;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::xeCommandListReset;
    else
        pDdiTable->pfnReset                                  = driver::xeCommandListReset;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendBarrier                          = instrumented::xeCommandListAppendBarrier;
    else
        pDdiTable->pfnAppendBarrier                          = driver::xeCommandListAppendBarrier;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryRangesBarrier              = instrumented::xeCommandListAppendMemoryRangesBarrier;
    else
        pDdiTable->pfnAppendMemoryRangesBarrier              = driver::xeCommandListAppendMemoryRangesBarrier;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryCopy                       = instrumented::xeCommandListAppendMemoryCopy;
    else
        pDdiTable->pfnAppendMemoryCopy                       = driver::xeCommandListAppendMemoryCopy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemorySet                        = instrumented::xeCommandListAppendMemorySet;
    else
        pDdiTable->pfnAppendMemorySet                        = driver::xeCommandListAppendMemorySet;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryCopyRegion                 = instrumented::xeCommandListAppendMemoryCopyRegion;
    else
        pDdiTable->pfnAppendMemoryCopyRegion                 = driver::xeCommandListAppendMemoryCopyRegion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopy                        = instrumented::xeCommandListAppendImageCopy;
    else
        pDdiTable->pfnAppendImageCopy                        = driver::xeCommandListAppendImageCopy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyRegion                  = instrumented::xeCommandListAppendImageCopyRegion;
    else
        pDdiTable->pfnAppendImageCopyRegion                  = driver::xeCommandListAppendImageCopyRegion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyToMemory                = instrumented::xeCommandListAppendImageCopyToMemory;
    else
        pDdiTable->pfnAppendImageCopyToMemory                = driver::xeCommandListAppendImageCopyToMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyFromMemory              = instrumented::xeCommandListAppendImageCopyFromMemory;
    else
        pDdiTable->pfnAppendImageCopyFromMemory              = driver::xeCommandListAppendImageCopyFromMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryPrefetch                   = instrumented::xeCommandListAppendMemoryPrefetch;
    else
        pDdiTable->pfnAppendMemoryPrefetch                   = driver::xeCommandListAppendMemoryPrefetch;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemAdvise                        = instrumented::xeCommandListAppendMemAdvise;
    else
        pDdiTable->pfnAppendMemAdvise                        = driver::xeCommandListAppendMemAdvise;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendSignalEvent                      = instrumented::xeCommandListAppendSignalEvent;
    else
        pDdiTable->pfnAppendSignalEvent                      = driver::xeCommandListAppendSignalEvent;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendWaitOnEvents                     = instrumented::xeCommandListAppendWaitOnEvents;
    else
        pDdiTable->pfnAppendWaitOnEvents                     = driver::xeCommandListAppendWaitOnEvents;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendEventReset                       = instrumented::xeCommandListAppendEventReset;
    else
        pDdiTable->pfnAppendEventReset                       = driver::xeCommandListAppendEventReset;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchFunction                   = instrumented::xeCommandListAppendLaunchFunction;
    else
        pDdiTable->pfnAppendLaunchFunction                   = driver::xeCommandListAppendLaunchFunction;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchFunctionIndirect           = instrumented::xeCommandListAppendLaunchFunctionIndirect;
    else
        pDdiTable->pfnAppendLaunchFunctionIndirect           = driver::xeCommandListAppendLaunchFunctionIndirect;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect  = instrumented::xeCommandListAppendLaunchMultipleFunctionsIndirect;
    else
        pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect  = driver::xeCommandListAppendLaunchMultipleFunctionsIndirect;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchHostFunction               = instrumented::xeCommandListAppendLaunchHostFunction;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeFenceCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeFenceCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeFenceDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeFenceDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSynchronize                        = instrumented::xeFenceHostSynchronize;
    else
        pDdiTable->pfnHostSynchronize                        = driver::xeFenceHostSynchronize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryStatus                            = instrumented::xeFenceQueryStatus;
    else
        pDdiTable->pfnQueryStatus                            = driver::xeFenceQueryStatus;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::xeFenceReset;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeEventPoolCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeEventPoolCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeEventPoolDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeEventPoolDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIpcHandle                           = instrumented::xeEventPoolGetIpcHandle;
    else
        pDdiTable->pfnGetIpcHandle                           = driver::xeEventPoolGetIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnOpenIpcHandle                          = instrumented::xeEventPoolOpenIpcHandle;
    else
        pDdiTable->pfnOpenIpcHandle                          = driver::xeEventPoolOpenIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCloseIpcHandle                         = instrumented::xeEventPoolCloseIpcHandle;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeEventCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeEventCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeEventDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeEventDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSignal                             = instrumented::xeEventHostSignal;
    else
        pDdiTable->pfnHostSignal                             = driver::xeEventHostSignal;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSynchronize                        = instrumented::xeEventHostSynchronize;
    else
        pDdiTable->pfnHostSynchronize                        = driver::xeEventHostSynchronize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryStatus                            = instrumented::xeEventQueryStatus;
    else
        pDdiTable->pfnQueryStatus                            = driver::xeEventQueryStatus;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::xeEventReset;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::xeImageGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::xeImageGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeImageCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeImageCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeImageDestroy;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeModuleCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeModuleCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeModuleDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeModuleDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetNativeBinary                        = instrumented::xeModuleGetNativeBinary;
    else
        pDdiTable->pfnGetNativeBinary                        = driver::xeModuleGetNativeBinary;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetGlobalPointer                       = instrumented::xeModuleGetGlobalPointer;
    else
        pDdiTable->pfnGetGlobalPointer                       = driver::xeModuleGetGlobalPointer;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetFunctionPointer                     = instrumented::xeModuleGetFunctionPointer;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeModuleBuildLogDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeModuleBuildLogDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetString                              = instrumented::xeModuleBuildLogGetString;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeFunctionCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeFunctionCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeFunctionDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeFunctionDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetGroupSize                           = instrumented::xeFunctionSetGroupSize;
    else
        pDdiTable->pfnSetGroupSize                           = driver::xeFunctionSetGroupSize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSuggestGroupSize                       = instrumented::xeFunctionSuggestGroupSize;
    else
        pDdiTable->pfnSuggestGroupSize                       = driver::xeFunctionSuggestGroupSize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetArgumentValue                       = instrumented::xeFunctionSetArgumentValue;
    else
        pDdiTable->pfnSetArgumentValue                       = driver::xeFunctionSetArgumentValue;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetAttribute                           = instrumented::xeFunctionSetAttribute;
    else
        pDdiTable->pfnSetAttribute                           = driver::xeFunctionSetAttribute;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetAttribute                           = instrumented::xeFunctionGetAttribute;
    else
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

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xeSamplerCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xeSamplerCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xeSamplerDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xeSamplerDestroy;

    return result;
}

#if defined(__cplusplus)
};
#endif
