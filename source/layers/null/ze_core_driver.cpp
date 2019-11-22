/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_core_driver.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
 * @endcond
 *
 */
#include "ze_null.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    ze_result_t __zecall
    zeInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInit = context.zeDdiTable.Global.pfnInit;
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
    /// @brief Intercept function for zeDriverGet
    ze_result_t __zecall
    zeDriverGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader will update the value with the total
                                                        ///< number of drivers available.
                                                        ///< if count is non-zero, then the loader will only retrieve that number
                                                        ///< of drivers.
                                                        ///< if count is larger than the number of drivers available, then the
                                                        ///< loader will update the value with the correct number of drivers available.
        ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zeDdiTable.Driver.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( pCount, phDrivers );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDrivers ) && ( i < *pCount ); ++i )
                phDrivers[ i ] = reinterpret_cast<ze_driver_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetDriverVersion
    ze_result_t __zecall
    zeDriverGetDriverVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* version                               ///< [out] driver version
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDriverVersion = context.zeDdiTable.Driver.pfnGetDriverVersion;
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
    /// @brief Intercept function for zeDriverGetApiVersion
    ze_result_t __zecall
    zeDriverGetApiVersion(
        ze_driver_handle_t hDrivers,                    ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetApiVersion = context.zeDdiTable.Driver.pfnGetApiVersion;
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
    /// @brief Intercept function for zeDriverGetIPCProperties
    ze_result_t __zecall
    zeDriverGetIPCProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIPCProperties = context.zeDdiTable.Driver.pfnGetIPCProperties;
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
    /// @brief Intercept function for zeDriverGetExtensionFunctionAddress
    ze_result_t __zecall
    zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* pFuncName,                          ///< [in] name of the extension function
        void** pfunc                                    ///< [out] pointer to extension function
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetExtensionFunctionAddress = context.zeDdiTable.Driver.pfnGetExtensionFunctionAddress;
        if( nullptr != pfnGetExtensionFunctionAddress )
        {
            result = pfnGetExtensionFunctionAddress( hDriver, pFuncName, pfunc );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    ze_result_t __zecall
    zeDeviceGet(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                        ///< if count is larger than the number of devices available, then the
                                                        ///< driver will update the value with the correct number of devices available.
        ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zeDdiTable.Device.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDriver, pCount, phDevices );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDevices ) && ( i < *pCount ); ++i )
                phDevices[ i ] = reinterpret_cast<ze_device_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetSubDevices
    ze_result_t __zecall
    zeDeviceGetSubDevices(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of sub-devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                        ///< if count is larger than the number of sub-devices available, then the
                                                        ///< driver will update the value with the correct number of sub-devices available.
        ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetSubDevices = context.zeDdiTable.Device.pfnGetSubDevices;
        if( nullptr != pfnGetSubDevices )
        {
            result = pfnGetSubDevices( hDevice, pCount, phSubdevices );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phSubdevices ) && ( i < *pCount ); ++i )
                phSubdevices[ i ] = reinterpret_cast<ze_device_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetProperties
    ze_result_t __zecall
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Device.pfnGetProperties;
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
    /// @brief Intercept function for zeDeviceGetComputeProperties
    ze_result_t __zecall
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetComputeProperties = context.zeDdiTable.Device.pfnGetComputeProperties;
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
    /// @brief Intercept function for zeDeviceGetKernelProperties
    ze_result_t __zecall
    zeDeviceGetKernelProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_kernel_properties_t* pKernelProperties///< [in,out] query result for kernel properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetKernelProperties = context.zeDdiTable.Device.pfnGetKernelProperties;
        if( nullptr != pfnGetKernelProperties )
        {
            result = pfnGetKernelProperties( hDevice, pKernelProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    ze_result_t __zecall
    zeDeviceGetMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of memory properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< memory properties.
                                                        ///< if count is larger than the number of memory properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< memory properties available.
        ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemoryProperties = context.zeDdiTable.Device.pfnGetMemoryProperties;
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
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    ze_result_t __zecall
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemoryAccessProperties = context.zeDdiTable.Device.pfnGetMemoryAccessProperties;
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
    /// @brief Intercept function for zeDeviceGetCacheProperties
    ze_result_t __zecall
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetCacheProperties = context.zeDdiTable.Device.pfnGetCacheProperties;
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
    /// @brief Intercept function for zeDeviceGetImageProperties
    ze_result_t __zecall
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetImageProperties = context.zeDdiTable.Device.pfnGetImageProperties;
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
    /// @brief Intercept function for zeDeviceGetP2PProperties
    ze_result_t __zecall
    zeDeviceGetP2PProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetP2PProperties = context.zeDdiTable.Device.pfnGetP2PProperties;
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
    /// @brief Intercept function for zeDeviceCanAccessPeer
    ze_result_t __zecall
    zeDeviceCanAccessPeer(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCanAccessPeer = context.zeDdiTable.Device.pfnCanAccessPeer;
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
    /// @brief Intercept function for zeDeviceSetLastLevelCacheConfig
    ze_result_t __zecall
    zeDeviceSetLastLevelCacheConfig(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device 
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLastLevelCacheConfig = context.zeDdiTable.Device.pfnSetLastLevelCacheConfig;
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
    /// @brief Intercept function for zeCommandQueueCreate
    ze_result_t __zecall
    zeCommandQueueCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.CommandQueue.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phCommandQueue );
        }
        else
        {
            // generic implementation
            *phCommandQueue = reinterpret_cast<ze_command_queue_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueDestroy
    ze_result_t __zecall
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.CommandQueue.pfnDestroy;
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
    /// @brief Intercept function for zeCommandQueueExecuteCommandLists
    ze_result_t __zecall
    zeCommandQueueExecuteCommandLists(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnExecuteCommandLists = context.zeDdiTable.CommandQueue.pfnExecuteCommandLists;
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
    /// @brief Intercept function for zeCommandQueueSynchronize
    ze_result_t __zecall
    zeCommandQueueSynchronize(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSynchronize = context.zeDdiTable.CommandQueue.pfnSynchronize;
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
    /// @brief Intercept function for zeCommandListCreate
    ze_result_t __zecall
    zeCommandListCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.CommandList.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phCommandList );
        }
        else
        {
            // generic implementation
            *phCommandList = reinterpret_cast<ze_command_list_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateImmediate
    ze_result_t __zecall
    zeCommandListCreateImmediate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateImmediate = context.zeDdiTable.CommandList.pfnCreateImmediate;
        if( nullptr != pfnCreateImmediate )
        {
            result = pfnCreateImmediate( hDevice, altdesc, phCommandList );
        }
        else
        {
            // generic implementation
            *phCommandList = reinterpret_cast<ze_command_list_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListDestroy
    ze_result_t __zecall
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.CommandList.pfnDestroy;
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
    /// @brief Intercept function for zeCommandListClose
    ze_result_t __zecall
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.zeDdiTable.CommandList.pfnClose;
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
    /// @brief Intercept function for zeCommandListReset
    ze_result_t __zecall
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zeDdiTable.CommandList.pfnReset;
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
    /// @brief Intercept function for zeCommandListAppendBarrier
    ze_result_t __zecall
    zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendBarrier = context.zeDdiTable.CommandList.pfnAppendBarrier;
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
    /// @brief Intercept function for zeCommandListAppendMemoryRangesBarrier
    ze_result_t __zecall
    zeCommandListAppendMemoryRangesBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryRangesBarrier = context.zeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;
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
    /// @brief Intercept function for zeDeviceSystemBarrier
    ze_result_t __zecall
    zeDeviceSystemBarrier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSystemBarrier = context.zeDdiTable.Device.pfnSystemBarrier;
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
    /// @brief Intercept function for zeDeviceRegisterCLMemory
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLMemory(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRegisterCLMemory = context.zeDdiTable.Device.pfnRegisterCLMemory;
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
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLProgram
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLProgram(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        ze_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRegisterCLProgram = context.zeDdiTable.Device.pfnRegisterCLProgram;
        if( nullptr != pfnRegisterCLProgram )
        {
            result = pfnRegisterCLProgram( hDevice, context, program, phModule );
        }
        else
        {
            // generic implementation
            *phModule = reinterpret_cast<ze_module_handle_t>( context.get() );

        }

        return result;
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLCommandQueue
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLCommandQueue(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRegisterCLCommandQueue = context.zeDdiTable.Device.pfnRegisterCLCommandQueue;
        if( nullptr != pfnRegisterCLCommandQueue )
        {
            result = pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
        }
        else
        {
            // generic implementation
            *phCommandQueue = reinterpret_cast<ze_command_queue_handle_t>( context.get() );

        }

        return result;
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopy
    ze_result_t __zecall
    zeCommandListAppendMemoryCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryCopy = context.zeDdiTable.CommandList.pfnAppendMemoryCopy;
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
    /// @brief Intercept function for zeCommandListAppendMemoryFill
    ze_result_t __zecall
    zeCommandListAppendMemoryFill(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryFill = context.zeDdiTable.CommandList.pfnAppendMemoryFill;
        if( nullptr != pfnAppendMemoryFill )
        {
            result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hEvent );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyRegion
    ze_result_t __zecall
    zeCommandListAppendMemoryCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryCopyRegion = context.zeDdiTable.CommandList.pfnAppendMemoryCopyRegion;
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
    /// @brief Intercept function for zeCommandListAppendImageCopy
    ze_result_t __zecall
    zeCommandListAppendImageCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopy = context.zeDdiTable.CommandList.pfnAppendImageCopy;
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
    /// @brief Intercept function for zeCommandListAppendImageCopyRegion
    ze_result_t __zecall
    zeCommandListAppendImageCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyRegion = context.zeDdiTable.CommandList.pfnAppendImageCopyRegion;
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
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemory
    ze_result_t __zecall
    zeCommandListAppendImageCopyToMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyToMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemory;
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
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemory
    ze_result_t __zecall
    zeCommandListAppendImageCopyFromMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyFromMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemory;
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
    /// @brief Intercept function for zeCommandListAppendMemoryPrefetch
    ze_result_t __zecall
    zeCommandListAppendMemoryPrefetch(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryPrefetch = context.zeDdiTable.CommandList.pfnAppendMemoryPrefetch;
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
    /// @brief Intercept function for zeCommandListAppendMemAdvise
    ze_result_t __zecall
    zeCommandListAppendMemAdvise(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemAdvise = context.zeDdiTable.CommandList.pfnAppendMemAdvise;
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
    /// @brief Intercept function for zeEventPoolCreate
    ze_result_t __zecall
    zeEventPoolCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.EventPool.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDriver, desc, numDevices, phDevices, phEventPool );
        }
        else
        {
            // generic implementation
            *phEventPool = reinterpret_cast<ze_event_pool_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolDestroy
    ze_result_t __zecall
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.EventPool.pfnDestroy;
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
    /// @brief Intercept function for zeEventCreate
    ze_result_t __zecall
    zeEventCreate(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Event.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hEventPool, desc, phEvent );
        }
        else
        {
            // generic implementation
            *phEvent = reinterpret_cast<ze_event_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventDestroy
    ze_result_t __zecall
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Event.pfnDestroy;
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
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    ze_result_t __zecall
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIpcHandle = context.zeDdiTable.EventPool.pfnGetIpcHandle;
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
    /// @brief Intercept function for zeEventPoolOpenIpcHandle
    ze_result_t __zecall
    zeEventPoolOpenIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver to associate with the IPC event pool handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpenIpcHandle = context.zeDdiTable.EventPool.pfnOpenIpcHandle;
        if( nullptr != pfnOpenIpcHandle )
        {
            result = pfnOpenIpcHandle( hDriver, hIpc, phEventPool );
        }
        else
        {
            // generic implementation
            *phEventPool = reinterpret_cast<ze_event_pool_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCloseIpcHandle
    ze_result_t __zecall
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCloseIpcHandle = context.zeDdiTable.EventPool.pfnCloseIpcHandle;
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
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    ze_result_t __zecall
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendSignalEvent = context.zeDdiTable.CommandList.pfnAppendSignalEvent;
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
    /// @brief Intercept function for zeCommandListAppendWaitOnEvents
    ze_result_t __zecall
    zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                        ///< continuing
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendWaitOnEvents = context.zeDdiTable.CommandList.pfnAppendWaitOnEvents;
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
    /// @brief Intercept function for zeEventHostSignal
    ze_result_t __zecall
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSignal = context.zeDdiTable.Event.pfnHostSignal;
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
    /// @brief Intercept function for zeEventHostSynchronize
    ze_result_t __zecall
    zeEventHostSynchronize(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSynchronize = context.zeDdiTable.Event.pfnHostSynchronize;
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
    /// @brief Intercept function for zeEventQueryStatus
    ze_result_t __zecall
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryStatus = context.zeDdiTable.Event.pfnQueryStatus;
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
    /// @brief Intercept function for zeCommandListAppendEventReset
    ze_result_t __zecall
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendEventReset = context.zeDdiTable.CommandList.pfnAppendEventReset;
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
    /// @brief Intercept function for zeEventReset
    ze_result_t __zecall
    zeEventReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zeDdiTable.Event.pfnReset;
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
    /// @brief Intercept function for zeFenceCreate
    ze_result_t __zecall
    zeFenceCreate(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Fence.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hCommandQueue, desc, phFence );
        }
        else
        {
            // generic implementation
            *phFence = reinterpret_cast<ze_fence_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceDestroy
    ze_result_t __zecall
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Fence.pfnDestroy;
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
    /// @brief Intercept function for zeFenceHostSynchronize
    ze_result_t __zecall
    zeFenceHostSynchronize(
        ze_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSynchronize = context.zeDdiTable.Fence.pfnHostSynchronize;
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
    /// @brief Intercept function for zeFenceQueryStatus
    ze_result_t __zecall
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryStatus = context.zeDdiTable.Fence.pfnQueryStatus;
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
    /// @brief Intercept function for zeFenceReset
    ze_result_t __zecall
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zeDdiTable.Fence.pfnReset;
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
    /// @brief Intercept function for zeImageGetProperties
    ze_result_t __zecall
    zeImageGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Image.pfnGetProperties;
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
    /// @brief Intercept function for zeImageCreate
    ze_result_t __zecall
    zeImageCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Image.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phImage );
        }
        else
        {
            // generic implementation
            *phImage = reinterpret_cast<ze_image_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    ze_result_t __zecall
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Image.pfnDestroy;
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
    /// @brief Intercept function for zeDriverAllocSharedMem
    ze_result_t __zecall
    zeDriverAllocSharedMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_device_handle_t hDevice,                     ///< [in] handle of a device
        ze_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
        ze_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocSharedMem = context.zeDdiTable.Driver.pfnAllocSharedMem;
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
    /// @brief Intercept function for zeDriverAllocDeviceMem
    ze_result_t __zecall
    zeDriverAllocDeviceMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocDeviceMem = context.zeDdiTable.Driver.pfnAllocDeviceMem;
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
    /// @brief Intercept function for zeDriverAllocHostMem
    ze_result_t __zecall
    zeDriverAllocHostMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocHostMem = context.zeDdiTable.Driver.pfnAllocHostMem;
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
    /// @brief Intercept function for zeDriverFreeMem
    ze_result_t __zecall
    zeDriverFreeMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFreeMem = context.zeDdiTable.Driver.pfnFreeMem;
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
    /// @brief Intercept function for zeDriverGetMemAllocProperties
    ze_result_t __zecall
    zeDriverGetMemAllocProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemAllocProperties = context.zeDdiTable.Driver.pfnGetMemAllocProperties;
        if( nullptr != pfnGetMemAllocProperties )
        {
            result = pfnGetMemAllocProperties( hDriver, ptr, pMemAllocProperties, phDevice );
        }
        else
        {
            // generic implementation
            if( nullptr != phDevice ) *phDevice = reinterpret_cast<ze_device_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetMemAddressRange
    ze_result_t __zecall
    zeDriverGetMemAddressRange(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemAddressRange = context.zeDdiTable.Driver.pfnGetMemAddressRange;
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
    /// @brief Intercept function for zeDriverGetMemIpcHandle
    ze_result_t __zecall
    zeDriverGetMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemIpcHandle = context.zeDdiTable.Driver.pfnGetMemIpcHandle;
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
    /// @brief Intercept function for zeDriverOpenMemIpcHandle
    ze_result_t __zecall
    zeDriverOpenMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpenMemIpcHandle = context.zeDdiTable.Driver.pfnOpenMemIpcHandle;
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
    /// @brief Intercept function for zeDriverCloseMemIpcHandle
    ze_result_t __zecall
    zeDriverCloseMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCloseMemIpcHandle = context.zeDdiTable.Driver.pfnCloseMemIpcHandle;
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
    /// @brief Intercept function for zeModuleCreate
    ze_result_t __zecall
    zeModuleCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Module.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phModule, phBuildLog );
        }
        else
        {
            // generic implementation
            *phModule = reinterpret_cast<ze_module_handle_t>( context.get() );

            if( nullptr != phBuildLog ) *phBuildLog = reinterpret_cast<ze_module_build_log_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDestroy
    ze_result_t __zecall
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Module.pfnDestroy;
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
    /// @brief Intercept function for zeModuleBuildLogDestroy
    ze_result_t __zecall
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.ModuleBuildLog.pfnDestroy;
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
    /// @brief Intercept function for zeModuleBuildLogGetString
    ze_result_t __zecall
    zeModuleBuildLogGetString(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetString = context.zeDdiTable.ModuleBuildLog.pfnGetString;
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
    /// @brief Intercept function for zeModuleGetNativeBinary
    ze_result_t __zecall
    zeModuleGetNativeBinary(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetNativeBinary = context.zeDdiTable.Module.pfnGetNativeBinary;
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
    /// @brief Intercept function for zeModuleGetGlobalPointer
    ze_result_t __zecall
    zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the device
        const char* pGlobalName,                        ///< [in] name of global variable in module
        void** pptr                                     ///< [out] device visible pointer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetGlobalPointer = context.zeDdiTable.Module.pfnGetGlobalPointer;
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
    /// @brief Intercept function for zeKernelCreate
    ze_result_t __zecall
    zeKernelCreate(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Kernel.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hModule, desc, phKernel );
        }
        else
        {
            // generic implementation
            *phKernel = reinterpret_cast<ze_kernel_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelDestroy
    ze_result_t __zecall
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Kernel.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hKernel );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetFunctionPointer
    ze_result_t __zecall
    zeModuleGetFunctionPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFunctionPointer = context.zeDdiTable.Module.pfnGetFunctionPointer;
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
    /// @brief Intercept function for zeKernelSetGroupSize
    ze_result_t __zecall
    zeKernelSetGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetGroupSize = context.zeDdiTable.Kernel.pfnSetGroupSize;
        if( nullptr != pfnSetGroupSize )
        {
            result = pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestGroupSize
    ze_result_t __zecall
    zeKernelSuggestGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSuggestGroupSize = context.zeDdiTable.Kernel.pfnSuggestGroupSize;
        if( nullptr != pfnSuggestGroupSize )
        {
            result = pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    ze_result_t __zecall
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSuggestMaxCooperativeGroupCount = context.zeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;
        if( nullptr != pfnSuggestMaxCooperativeGroupCount )
        {
            result = pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetArgumentValue
    ze_result_t __zecall
    zeKernelSetArgumentValue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetArgumentValue = context.zeDdiTable.Kernel.pfnSetArgumentValue;
        if( nullptr != pfnSetArgumentValue )
        {
            result = pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetAttribute
    ze_result_t __zecall
    zeKernelSetAttribute(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_set_attribute_t attr,                 ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetAttribute = context.zeDdiTable.Kernel.pfnSetAttribute;
        if( nullptr != pfnSetAttribute )
        {
            result = pfnSetAttribute( hKernel, attr, value );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIntermediateCacheConfig
    ze_result_t __zecall
    zeKernelSetIntermediateCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetIntermediateCacheConfig = context.zeDdiTable.Kernel.pfnSetIntermediateCacheConfig;
        if( nullptr != pfnSetIntermediateCacheConfig )
        {
            result = pfnSetIntermediateCacheConfig( hKernel, CacheConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    ze_result_t __zecall
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Kernel.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hKernel, pKernelProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernel
    ze_result_t __zecall
    zeCommandListAppendLaunchKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchKernel = context.zeDdiTable.CommandList.pfnAppendLaunchKernel;
        if( nullptr != pfnAppendLaunchKernel )
        {
            result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchCooperativeKernel
    ze_result_t __zecall
    zeCommandListAppendLaunchCooperativeKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchCooperativeKernel = context.zeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel;
        if( nullptr != pfnAppendLaunchCooperativeKernel )
        {
            result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelIndirect
    ze_result_t __zecall
    zeCommandListAppendLaunchKernelIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchKernelIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchKernelIndirect;
        if( nullptr != pfnAppendLaunchKernelIndirect )
        {
            result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchMultipleKernelsIndirect
    ze_result_t __zecall
    zeCommandListAppendLaunchMultipleKernelsIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less-than or equal-to
                                                        ///< numKernels
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchMultipleKernelsIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;
        if( nullptr != pfnAppendLaunchMultipleKernelsIndirect )
        {
            result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchHostFunction
    ze_result_t __zecall
    zeCommandListAppendLaunchHostFunction(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData,                                ///< [in] pointer to user data to pass to host function.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchHostFunction = context.zeDdiTable.CommandList.pfnAppendLaunchHostFunction;
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
    /// @brief Intercept function for zeDeviceMakeMemoryResident
    ze_result_t __zecall
    zeDeviceMakeMemoryResident(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMakeMemoryResident = context.zeDdiTable.Device.pfnMakeMemoryResident;
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
    /// @brief Intercept function for zeDeviceEvictMemory
    ze_result_t __zecall
    zeDeviceEvictMemory(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEvictMemory = context.zeDdiTable.Device.pfnEvictMemory;
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
    /// @brief Intercept function for zeDeviceMakeImageResident
    ze_result_t __zecall
    zeDeviceMakeImageResident(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMakeImageResident = context.zeDdiTable.Device.pfnMakeImageResident;
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
    /// @brief Intercept function for zeDeviceEvictImage
    ze_result_t __zecall
    zeDeviceEvictImage(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEvictImage = context.zeDdiTable.Device.pfnEvictImage;
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
    /// @brief Intercept function for zeSamplerCreate
    ze_result_t __zecall
    zeSamplerCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Sampler.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phSampler );
        }
        else
        {
            // generic implementation
            *phSampler = reinterpret_cast<ze_sampler_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    ze_result_t __zecall
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Sampler.pfnDestroy;
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
    /// @brief Intercept function for zeInit
    ze_result_t __zecall
    zeInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_init_params_t in_params = {
            &flags
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeInit( flags );

        // capture parameters
        ze_init_params_t out_params = {
            &flags
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGet
    ze_result_t __zecall
    zeDriverGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader will update the value with the total
                                                        ///< number of drivers available.
                                                        ///< if count is non-zero, then the loader will only retrieve that number
                                                        ///< of drivers.
                                                        ///< if count is larger than the number of drivers available, then the
                                                        ///< loader will update the value with the correct number of drivers available.
        ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGet( pCount, phDrivers );

        // capture parameters
        ze_driver_get_params_t out_params = {
            &pCount,
            &phDrivers
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetDriverVersion
    ze_result_t __zecall
    zeDriverGetDriverVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* version                               ///< [out] driver version
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_driver_version_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetDriverVersionCb )
                    table.pfnGetDriverVersionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetDriverVersion( hDriver, version );

        // capture parameters
        ze_driver_get_driver_version_params_t out_params = {
            &hDriver,
            &version
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetDriverVersionCb )
                    table.pfnGetDriverVersionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetApiVersion
    ze_result_t __zecall
    zeDriverGetApiVersion(
        ze_driver_handle_t hDrivers,                    ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_api_version_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetApiVersionCb )
                    table.pfnGetApiVersionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetApiVersion( hDrivers, version );

        // capture parameters
        ze_driver_get_api_version_params_t out_params = {
            &hDrivers,
            &version
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetApiVersionCb )
                    table.pfnGetApiVersionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIPCProperties
    ze_result_t __zecall
    zeDriverGetIPCProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_ipc_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetIPCPropertiesCb )
                    table.pfnGetIPCPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetIPCProperties( hDriver, pIPCProperties );

        // capture parameters
        ze_driver_get_ipc_properties_params_t out_params = {
            &hDriver,
            &pIPCProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetIPCPropertiesCb )
                    table.pfnGetIPCPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionFunctionAddress
    ze_result_t __zecall
    zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* pFuncName,                          ///< [in] name of the extension function
        void** pfunc                                    ///< [out] pointer to extension function
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_extension_function_address_params_t in_params = {
            &hDriver,
            &pFuncName,
            &pfunc
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetExtensionFunctionAddressCb )
                    table.pfnGetExtensionFunctionAddressCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetExtensionFunctionAddress( hDriver, pFuncName, pfunc );

        // capture parameters
        ze_driver_get_extension_function_address_params_t out_params = {
            &hDriver,
            &pFuncName,
            &pfunc
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetExtensionFunctionAddressCb )
                    table.pfnGetExtensionFunctionAddressCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    ze_result_t __zecall
    zeDeviceGet(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                        ///< if count is larger than the number of devices available, then the
                                                        ///< driver will update the value with the correct number of devices available.
        ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGet( hDriver, pCount, phDevices );

        // capture parameters
        ze_device_get_params_t out_params = {
            &hDriver,
            &pCount,
            &phDevices
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetSubDevices
    ze_result_t __zecall
    zeDeviceGetSubDevices(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of sub-devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                        ///< if count is larger than the number of sub-devices available, then the
                                                        ///< driver will update the value with the correct number of sub-devices available.
        ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_sub_devices_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetSubDevicesCb )
                    table.pfnGetSubDevicesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetSubDevices( hDevice, pCount, phSubdevices );

        // capture parameters
        ze_device_get_sub_devices_params_t out_params = {
            &hDevice,
            &pCount,
            &phSubdevices
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetSubDevicesCb )
                    table.pfnGetSubDevicesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetProperties
    ze_result_t __zecall
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetProperties( hDevice, pDeviceProperties );

        // capture parameters
        ze_device_get_properties_params_t out_params = {
            &hDevice,
            &pDeviceProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetComputeProperties
    ze_result_t __zecall
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_compute_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetComputePropertiesCb )
                    table.pfnGetComputePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetComputeProperties( hDevice, pComputeProperties );

        // capture parameters
        ze_device_get_compute_properties_params_t out_params = {
            &hDevice,
            &pComputeProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetComputePropertiesCb )
                    table.pfnGetComputePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetKernelProperties
    ze_result_t __zecall
    zeDeviceGetKernelProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_kernel_properties_t* pKernelProperties///< [in,out] query result for kernel properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_kernel_properties_params_t in_params = {
            &hDevice,
            &pKernelProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetKernelPropertiesCb )
                    table.pfnGetKernelPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetKernelProperties( hDevice, pKernelProperties );

        // capture parameters
        ze_device_get_kernel_properties_params_t out_params = {
            &hDevice,
            &pKernelProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetKernelPropertiesCb )
                    table.pfnGetKernelPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    ze_result_t __zecall
    zeDeviceGetMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of memory properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< memory properties.
                                                        ///< if count is larger than the number of memory properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< memory properties available.
        ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_memory_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetMemoryPropertiesCb )
                    table.pfnGetMemoryPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetMemoryProperties( hDevice, pCount, pMemProperties );

        // capture parameters
        ze_device_get_memory_properties_params_t out_params = {
            &hDevice,
            &pCount,
            &pMemProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetMemoryPropertiesCb )
                    table.pfnGetMemoryPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    ze_result_t __zecall
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_memory_access_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                    table.pfnGetMemoryAccessPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetMemoryAccessProperties( hDevice, pMemAccessProperties );

        // capture parameters
        ze_device_get_memory_access_properties_params_t out_params = {
            &hDevice,
            &pMemAccessProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                    table.pfnGetMemoryAccessPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    ze_result_t __zecall
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_cache_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetCachePropertiesCb )
                    table.pfnGetCachePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetCacheProperties( hDevice, pCacheProperties );

        // capture parameters
        ze_device_get_cache_properties_params_t out_params = {
            &hDevice,
            &pCacheProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetCachePropertiesCb )
                    table.pfnGetCachePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetImageProperties
    ze_result_t __zecall
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_image_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetImagePropertiesCb )
                    table.pfnGetImagePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetImageProperties( hDevice, pImageProperties );

        // capture parameters
        ze_device_get_image_properties_params_t out_params = {
            &hDevice,
            &pImageProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetImagePropertiesCb )
                    table.pfnGetImagePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetP2PProperties
    ze_result_t __zecall
    zeDeviceGetP2PProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_p2_p_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetP2PPropertiesCb )
                    table.pfnGetP2PPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );

        // capture parameters
        ze_device_get_p2_p_properties_params_t out_params = {
            &hDevice,
            &hPeerDevice,
            &pP2PProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetP2PPropertiesCb )
                    table.pfnGetP2PPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceCanAccessPeer
    ze_result_t __zecall
    zeDeviceCanAccessPeer(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_can_access_peer_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnCanAccessPeerCb )
                    table.pfnCanAccessPeerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceCanAccessPeer( hDevice, hPeerDevice, value );

        // capture parameters
        ze_device_can_access_peer_params_t out_params = {
            &hDevice,
            &hPeerDevice,
            &value
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnCanAccessPeerCb )
                    table.pfnCanAccessPeerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSetLastLevelCacheConfig
    ze_result_t __zecall
    zeDeviceSetLastLevelCacheConfig(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device 
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_set_last_level_cache_config_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnSetLastLevelCacheConfigCb )
                    table.pfnSetLastLevelCacheConfigCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceSetLastLevelCacheConfig( hDevice, CacheConfig );

        // capture parameters
        ze_device_set_last_level_cache_config_params_t out_params = {
            &hDevice,
            &CacheConfig
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnSetLastLevelCacheConfigCb )
                    table.pfnSetLastLevelCacheConfigCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueCreate
    ze_result_t __zecall
    zeCommandQueueCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_queue_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueCreate( hDevice, desc, phCommandQueue );

        // capture parameters
        ze_command_queue_create_params_t out_params = {
            &hDevice,
            &desc,
            &phCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueDestroy
    ze_result_t __zecall
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_queue_destroy_params_t in_params = {
            &hCommandQueue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueDestroy( hCommandQueue );

        // capture parameters
        ze_command_queue_destroy_params_t out_params = {
            &hCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueExecuteCommandLists
    ze_result_t __zecall
    zeCommandQueueExecuteCommandLists(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_queue_execute_command_lists_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnExecuteCommandListsCb )
                    table.pfnExecuteCommandListsCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );

        // capture parameters
        ze_command_queue_execute_command_lists_params_t out_params = {
            &hCommandQueue,
            &numCommandLists,
            &phCommandLists,
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnExecuteCommandListsCb )
                    table.pfnExecuteCommandListsCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueSynchronize
    ze_result_t __zecall
    zeCommandQueueSynchronize(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_queue_synchronize_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnSynchronizeCb )
                    table.pfnSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueSynchronize( hCommandQueue, timeout );

        // capture parameters
        ze_command_queue_synchronize_params_t out_params = {
            &hCommandQueue,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnSynchronizeCb )
                    table.pfnSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreate
    ze_result_t __zecall
    zeCommandListCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListCreate( hDevice, desc, phCommandList );

        // capture parameters
        ze_command_list_create_params_t out_params = {
            &hDevice,
            &desc,
            &phCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateImmediate
    ze_result_t __zecall
    zeCommandListCreateImmediate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_create_immediate_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnCreateImmediateCb )
                    table.pfnCreateImmediateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListCreateImmediate( hDevice, altdesc, phCommandList );

        // capture parameters
        ze_command_list_create_immediate_params_t out_params = {
            &hDevice,
            &altdesc,
            &phCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCreateImmediateCb )
                    table.pfnCreateImmediateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListDestroy
    ze_result_t __zecall
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_destroy_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListDestroy( hCommandList );

        // capture parameters
        ze_command_list_destroy_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListClose
    ze_result_t __zecall
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_close_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListClose( hCommandList );

        // capture parameters
        ze_command_list_close_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListReset
    ze_result_t __zecall
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_reset_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListReset( hCommandList );

        // capture parameters
        ze_command_list_reset_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendBarrier
    ze_result_t __zecall
    zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_barrier_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendBarrierCb )
                    table.pfnAppendBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_barrier_params_t out_params = {
            &hCommandList,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendBarrierCb )
                    table.pfnAppendBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryRangesBarrier
    ze_result_t __zecall
    zeCommandListAppendMemoryRangesBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_memory_ranges_barrier_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                    table.pfnAppendMemoryRangesBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_memory_ranges_barrier_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                    table.pfnAppendMemoryRangesBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSystemBarrier
    ze_result_t __zecall
    zeDeviceSystemBarrier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_system_barrier_params_t in_params = {
            &hDevice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnSystemBarrierCb )
                    table.pfnSystemBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceSystemBarrier( hDevice );

        // capture parameters
        ze_device_system_barrier_params_t out_params = {
            &hDevice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnSystemBarrierCb )
                    table.pfnSystemBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLMemory
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLMemory(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_register_cl_memory_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnRegisterCLMemoryCb )
                    table.pfnRegisterCLMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceRegisterCLMemory( hDevice, context, mem, ptr );

        // capture parameters
        ze_device_register_cl_memory_params_t out_params = {
            &hDevice,
            &context,
            &mem,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnRegisterCLMemoryCb )
                    table.pfnRegisterCLMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLProgram
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLProgram(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        ze_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_register_cl_program_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnRegisterCLProgramCb )
                    table.pfnRegisterCLProgramCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceRegisterCLProgram( hDevice, context, program, phModule );

        // capture parameters
        ze_device_register_cl_program_params_t out_params = {
            &hDevice,
            &context,
            &program,
            &phModule
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnRegisterCLProgramCb )
                    table.pfnRegisterCLProgramCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLCommandQueue
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLCommandQueue(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_register_cl_command_queue_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnRegisterCLCommandQueueCb )
                    table.pfnRegisterCLCommandQueueCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );

        // capture parameters
        ze_device_register_cl_command_queue_params_t out_params = {
            &hDevice,
            &context,
            &command_queue,
            &phCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnRegisterCLCommandQueueCb )
                    table.pfnRegisterCLCommandQueueCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopy
    ze_result_t __zecall
    zeCommandListAppendMemoryCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_memory_copy_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyCb )
                    table.pfnAppendMemoryCopyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );

        // capture parameters
        ze_command_list_append_memory_copy_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyCb )
                    table.pfnAppendMemoryCopyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryFill
    ze_result_t __zecall
    zeCommandListAppendMemoryFill(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_memory_fill_params_t in_params = {
            &hCommandList,
            &ptr,
            &pattern,
            &pattern_size,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryFillCb )
                    table.pfnAppendMemoryFillCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hEvent );

        // capture parameters
        ze_command_list_append_memory_fill_params_t out_params = {
            &hCommandList,
            &ptr,
            &pattern,
            &pattern_size,
            &size,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryFillCb )
                    table.pfnAppendMemoryFillCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyRegion
    ze_result_t __zecall
    zeCommandListAppendMemoryCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_memory_copy_region_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                    table.pfnAppendMemoryCopyRegionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );

        // capture parameters
        ze_command_list_append_memory_copy_region_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                    table.pfnAppendMemoryCopyRegionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopy
    ze_result_t __zecall
    zeCommandListAppendImageCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_image_copy_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyCb )
                    table.pfnAppendImageCopyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );

        // capture parameters
        ze_command_list_append_image_copy_params_t out_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyCb )
                    table.pfnAppendImageCopyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyRegion
    ze_result_t __zecall
    zeCommandListAppendImageCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_image_copy_region_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyRegionCb )
                    table.pfnAppendImageCopyRegionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );

        // capture parameters
        ze_command_list_append_image_copy_region_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyRegionCb )
                    table.pfnAppendImageCopyRegionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemory
    ze_result_t __zecall
    zeCommandListAppendImageCopyToMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_image_copy_to_memory_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                    table.pfnAppendImageCopyToMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );

        // capture parameters
        ze_command_list_append_image_copy_to_memory_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                    table.pfnAppendImageCopyToMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemory
    ze_result_t __zecall
    zeCommandListAppendImageCopyFromMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_image_copy_from_memory_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                    table.pfnAppendImageCopyFromMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );

        // capture parameters
        ze_command_list_append_image_copy_from_memory_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                    table.pfnAppendImageCopyFromMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryPrefetch
    ze_result_t __zecall
    zeCommandListAppendMemoryPrefetch(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_memory_prefetch_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryPrefetchCb )
                    table.pfnAppendMemoryPrefetchCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryPrefetch( hCommandList, ptr, size );

        // capture parameters
        ze_command_list_append_memory_prefetch_params_t out_params = {
            &hCommandList,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryPrefetchCb )
                    table.pfnAppendMemoryPrefetchCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemAdvise
    ze_result_t __zecall
    zeCommandListAppendMemAdvise(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_mem_advise_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemAdviseCb )
                    table.pfnAppendMemAdviseCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );

        // capture parameters
        ze_command_list_append_mem_advise_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemAdviseCb )
                    table.pfnAppendMemAdviseCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCreate
    ze_result_t __zecall
    zeEventPoolCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_pool_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolCreate( hDriver, desc, numDevices, phDevices, phEventPool );

        // capture parameters
        ze_event_pool_create_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolDestroy
    ze_result_t __zecall
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_pool_destroy_params_t in_params = {
            &hEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolDestroy( hEventPool );

        // capture parameters
        ze_event_pool_destroy_params_t out_params = {
            &hEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventCreate
    ze_result_t __zecall
    zeEventCreate(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventCreate( hEventPool, desc, phEvent );

        // capture parameters
        ze_event_create_params_t out_params = {
            &hEventPool,
            &desc,
            &phEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventDestroy
    ze_result_t __zecall
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_destroy_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventDestroy( hEvent );

        // capture parameters
        ze_event_destroy_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    ze_result_t __zecall
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_pool_get_ipc_handle_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolGetIpcHandle( hEventPool, phIpc );

        // capture parameters
        ze_event_pool_get_ipc_handle_params_t out_params = {
            &hEventPool,
            &phIpc
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolOpenIpcHandle
    ze_result_t __zecall
    zeEventPoolOpenIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver to associate with the IPC event pool handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_pool_open_ipc_handle_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolOpenIpcHandle( hDriver, hIpc, phEventPool );

        // capture parameters
        ze_event_pool_open_ipc_handle_params_t out_params = {
            &hDriver,
            &hIpc,
            &phEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCloseIpcHandle
    ze_result_t __zecall
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_pool_close_ipc_handle_params_t in_params = {
            &hEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolCloseIpcHandle( hEventPool );

        // capture parameters
        ze_event_pool_close_ipc_handle_params_t out_params = {
            &hEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    ze_result_t __zecall
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_signal_event_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendSignalEventCb )
                    table.pfnAppendSignalEventCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendSignalEvent( hCommandList, hEvent );

        // capture parameters
        ze_command_list_append_signal_event_params_t out_params = {
            &hCommandList,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendSignalEventCb )
                    table.pfnAppendSignalEventCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWaitOnEvents
    ze_result_t __zecall
    zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                        ///< continuing
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_wait_on_events_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendWaitOnEventsCb )
                    table.pfnAppendWaitOnEventsCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendWaitOnEvents( hCommandList, numEvents, phEvents );

        // capture parameters
        ze_command_list_append_wait_on_events_params_t out_params = {
            &hCommandList,
            &numEvents,
            &phEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendWaitOnEventsCb )
                    table.pfnAppendWaitOnEventsCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSignal
    ze_result_t __zecall
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_host_signal_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnHostSignalCb )
                    table.pfnHostSignalCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventHostSignal( hEvent );

        // capture parameters
        ze_event_host_signal_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnHostSignalCb )
                    table.pfnHostSignalCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSynchronize
    ze_result_t __zecall
    zeEventHostSynchronize(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_host_synchronize_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventHostSynchronize( hEvent, timeout );

        // capture parameters
        ze_event_host_synchronize_params_t out_params = {
            &hEvent,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryStatus
    ze_result_t __zecall
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_query_status_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventQueryStatus( hEvent );

        // capture parameters
        ze_event_query_status_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendEventReset
    ze_result_t __zecall
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_event_reset_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendEventResetCb )
                    table.pfnAppendEventResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendEventReset( hCommandList, hEvent );

        // capture parameters
        ze_command_list_append_event_reset_params_t out_params = {
            &hCommandList,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendEventResetCb )
                    table.pfnAppendEventResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventReset
    ze_result_t __zecall
    zeEventReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_reset_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventReset( hEvent );

        // capture parameters
        ze_event_reset_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceCreate
    ze_result_t __zecall
    zeFenceCreate(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_fence_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceCreate( hCommandQueue, desc, phFence );

        // capture parameters
        ze_fence_create_params_t out_params = {
            &hCommandQueue,
            &desc,
            &phFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceDestroy
    ze_result_t __zecall
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_fence_destroy_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceDestroy( hFence );

        // capture parameters
        ze_fence_destroy_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceHostSynchronize
    ze_result_t __zecall
    zeFenceHostSynchronize(
        ze_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_fence_host_synchronize_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceHostSynchronize( hFence, timeout );

        // capture parameters
        ze_fence_host_synchronize_params_t out_params = {
            &hFence,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceQueryStatus
    ze_result_t __zecall
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_fence_query_status_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceQueryStatus( hFence );

        // capture parameters
        ze_fence_query_status_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceReset
    ze_result_t __zecall
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_fence_reset_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceReset( hFence );

        // capture parameters
        ze_fence_reset_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetProperties
    ze_result_t __zecall
    zeImageGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_image_get_properties_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Image;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeImageGetProperties( hDevice, desc, pImageProperties );

        // capture parameters
        ze_image_get_properties_params_t out_params = {
            &hDevice,
            &desc,
            &pImageProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Image;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageCreate
    ze_result_t __zecall
    zeImageCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_image_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Image;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeImageCreate( hDevice, desc, phImage );

        // capture parameters
        ze_image_create_params_t out_params = {
            &hDevice,
            &desc,
            &phImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Image;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    ze_result_t __zecall
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_image_destroy_params_t in_params = {
            &hImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Image;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeImageDestroy( hImage );

        // capture parameters
        ze_image_destroy_params_t out_params = {
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Image;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverAllocSharedMem
    ze_result_t __zecall
    zeDriverAllocSharedMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_device_handle_t hDevice,                     ///< [in] handle of a device
        ze_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
        ze_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_alloc_shared_mem_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnAllocSharedMemCb )
                    table.pfnAllocSharedMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverAllocSharedMem( hDriver, hDevice, device_flags, ordinal, host_flags, size, alignment, pptr );

        // capture parameters
        ze_driver_alloc_shared_mem_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnAllocSharedMemCb )
                    table.pfnAllocSharedMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverAllocDeviceMem
    ze_result_t __zecall
    zeDriverAllocDeviceMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        uint32_t ordinal,                               ///< [in] ordinal of the device's local memory to allocate from;
                                                        ///< must be less than the count returned from ::zeDeviceGetMemoryProperties
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_alloc_device_mem_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnAllocDeviceMemCb )
                    table.pfnAllocDeviceMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverAllocDeviceMem( hDriver, hDevice, flags, ordinal, size, alignment, pptr );

        // capture parameters
        ze_driver_alloc_device_mem_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnAllocDeviceMemCb )
                    table.pfnAllocDeviceMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverAllocHostMem
    ze_result_t __zecall
    zeDriverAllocHostMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_alloc_host_mem_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnAllocHostMemCb )
                    table.pfnAllocHostMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverAllocHostMem( hDriver, flags, size, alignment, pptr );

        // capture parameters
        ze_driver_alloc_host_mem_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnAllocHostMemCb )
                    table.pfnAllocHostMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverFreeMem
    ze_result_t __zecall
    zeDriverFreeMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_free_mem_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnFreeMemCb )
                    table.pfnFreeMemCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverFreeMem( hDriver, ptr );

        // capture parameters
        ze_driver_free_mem_params_t out_params = {
            &hDriver,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnFreeMemCb )
                    table.pfnFreeMemCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetMemAllocProperties
    ze_result_t __zecall
    zeDriverGetMemAllocProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_mem_alloc_properties_params_t in_params = {
            &hDriver,
            &ptr,
            &pMemAllocProperties,
            &phDevice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetMemAllocPropertiesCb )
                    table.pfnGetMemAllocPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetMemAllocProperties( hDriver, ptr, pMemAllocProperties, phDevice );

        // capture parameters
        ze_driver_get_mem_alloc_properties_params_t out_params = {
            &hDriver,
            &ptr,
            &pMemAllocProperties,
            &phDevice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetMemAllocPropertiesCb )
                    table.pfnGetMemAllocPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetMemAddressRange
    ze_result_t __zecall
    zeDriverGetMemAddressRange(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_mem_address_range_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetMemAddressRangeCb )
                    table.pfnGetMemAddressRangeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetMemAddressRange( hDriver, ptr, pBase, pSize );

        // capture parameters
        ze_driver_get_mem_address_range_params_t out_params = {
            &hDriver,
            &ptr,
            &pBase,
            &pSize
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetMemAddressRangeCb )
                    table.pfnGetMemAddressRangeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetMemIpcHandle
    ze_result_t __zecall
    zeDriverGetMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_mem_ipc_handle_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetMemIpcHandleCb )
                    table.pfnGetMemIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetMemIpcHandle( hDriver, ptr, pIpcHandle );

        // capture parameters
        ze_driver_get_mem_ipc_handle_params_t out_params = {
            &hDriver,
            &ptr,
            &pIpcHandle
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetMemIpcHandleCb )
                    table.pfnGetMemIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverOpenMemIpcHandle
    ze_result_t __zecall
    zeDriverOpenMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_open_mem_ipc_handle_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnOpenMemIpcHandleCb )
                    table.pfnOpenMemIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverOpenMemIpcHandle( hDriver, hDevice, handle, flags, pptr );

        // capture parameters
        ze_driver_open_mem_ipc_handle_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnOpenMemIpcHandleCb )
                    table.pfnOpenMemIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverCloseMemIpcHandle
    ze_result_t __zecall
    zeDriverCloseMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_close_mem_ipc_handle_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnCloseMemIpcHandleCb )
                    table.pfnCloseMemIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverCloseMemIpcHandle( hDriver, ptr );

        // capture parameters
        ze_driver_close_mem_ipc_handle_params_t out_params = {
            &hDriver,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnCloseMemIpcHandleCb )
                    table.pfnCloseMemIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleCreate
    ze_result_t __zecall
    zeModuleCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_module_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleCreate( hDevice, desc, phModule, phBuildLog );

        // capture parameters
        ze_module_create_params_t out_params = {
            &hDevice,
            &desc,
            &phModule,
            &phBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDestroy
    ze_result_t __zecall
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_module_destroy_params_t in_params = {
            &hModule
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleDestroy( hModule );

        // capture parameters
        ze_module_destroy_params_t out_params = {
            &hModule
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogDestroy
    ze_result_t __zecall
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_module_build_log_destroy_params_t in_params = {
            &hModuleBuildLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.ModuleBuildLog;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleBuildLogDestroy( hModuleBuildLog );

        // capture parameters
        ze_module_build_log_destroy_params_t out_params = {
            &hModuleBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.ModuleBuildLog;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogGetString
    ze_result_t __zecall
    zeModuleBuildLogGetString(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_module_build_log_get_string_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.ModuleBuildLog;
                if( nullptr != table.pfnGetStringCb )
                    table.pfnGetStringCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleBuildLogGetString( hModuleBuildLog, pSize, pBuildLog );

        // capture parameters
        ze_module_build_log_get_string_params_t out_params = {
            &hModuleBuildLog,
            &pSize,
            &pBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.ModuleBuildLog;
                if( nullptr != table.pfnGetStringCb )
                    table.pfnGetStringCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetNativeBinary
    ze_result_t __zecall
    zeModuleGetNativeBinary(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_module_get_native_binary_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetNativeBinaryCb )
                    table.pfnGetNativeBinaryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetNativeBinary( hModule, pSize, pModuleNativeBinary );

        // capture parameters
        ze_module_get_native_binary_params_t out_params = {
            &hModule,
            &pSize,
            &pModuleNativeBinary
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetNativeBinaryCb )
                    table.pfnGetNativeBinaryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetGlobalPointer
    ze_result_t __zecall
    zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the device
        const char* pGlobalName,                        ///< [in] name of global variable in module
        void** pptr                                     ///< [out] device visible pointer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_module_get_global_pointer_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetGlobalPointerCb )
                    table.pfnGetGlobalPointerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetGlobalPointer( hModule, pGlobalName, pptr );

        // capture parameters
        ze_module_get_global_pointer_params_t out_params = {
            &hModule,
            &pGlobalName,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetGlobalPointerCb )
                    table.pfnGetGlobalPointerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelCreate
    ze_result_t __zecall
    zeKernelCreate(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_create_params_t in_params = {
            &hModule,
            &desc,
            &phKernel
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelCreate( hModule, desc, phKernel );

        // capture parameters
        ze_kernel_create_params_t out_params = {
            &hModule,
            &desc,
            &phKernel
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelDestroy
    ze_result_t __zecall
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_destroy_params_t in_params = {
            &hKernel
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelDestroy( hKernel );

        // capture parameters
        ze_kernel_destroy_params_t out_params = {
            &hKernel
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetFunctionPointer
    ze_result_t __zecall
    zeModuleGetFunctionPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_module_get_function_pointer_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetFunctionPointerCb )
                    table.pfnGetFunctionPointerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetFunctionPointer( hModule, pFunctionName, pfnFunction );

        // capture parameters
        ze_module_get_function_pointer_params_t out_params = {
            &hModule,
            &pFunctionName,
            &pfnFunction
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetFunctionPointerCb )
                    table.pfnGetFunctionPointerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGroupSize
    ze_result_t __zecall
    zeKernelSetGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_set_group_size_params_t in_params = {
            &hKernel,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetGroupSizeCb )
                    table.pfnSetGroupSizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );

        // capture parameters
        ze_kernel_set_group_size_params_t out_params = {
            &hKernel,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetGroupSizeCb )
                    table.pfnSetGroupSizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestGroupSize
    ze_result_t __zecall
    zeKernelSuggestGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_suggest_group_size_params_t in_params = {
            &hKernel,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSuggestGroupSizeCb )
                    table.pfnSuggestGroupSizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );

        // capture parameters
        ze_kernel_suggest_group_size_params_t out_params = {
            &hKernel,
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSuggestGroupSizeCb )
                    table.pfnSuggestGroupSizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    ze_result_t __zecall
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_suggest_max_cooperative_group_count_params_t in_params = {
            &hKernel,
            &totalGroupCount
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSuggestMaxCooperativeGroupCountCb )
                    table.pfnSuggestMaxCooperativeGroupCountCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );

        // capture parameters
        ze_kernel_suggest_max_cooperative_group_count_params_t out_params = {
            &hKernel,
            &totalGroupCount
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSuggestMaxCooperativeGroupCountCb )
                    table.pfnSuggestMaxCooperativeGroupCountCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetArgumentValue
    ze_result_t __zecall
    zeKernelSetArgumentValue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_set_argument_value_params_t in_params = {
            &hKernel,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetArgumentValueCb )
                    table.pfnSetArgumentValueCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetArgumentValue( hKernel, argIndex, argSize, pArgValue );

        // capture parameters
        ze_kernel_set_argument_value_params_t out_params = {
            &hKernel,
            &argIndex,
            &argSize,
            &pArgValue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetArgumentValueCb )
                    table.pfnSetArgumentValueCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetAttribute
    ze_result_t __zecall
    zeKernelSetAttribute(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_set_attribute_t attr,                 ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_set_attribute_params_t in_params = {
            &hKernel,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetAttributeCb )
                    table.pfnSetAttributeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetAttribute( hKernel, attr, value );

        // capture parameters
        ze_kernel_set_attribute_params_t out_params = {
            &hKernel,
            &attr,
            &value
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetAttributeCb )
                    table.pfnSetAttributeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIntermediateCacheConfig
    ze_result_t __zecall
    zeKernelSetIntermediateCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_set_intermediate_cache_config_params_t in_params = {
            &hKernel,
            &CacheConfig
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetIntermediateCacheConfigCb )
                    table.pfnSetIntermediateCacheConfigCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetIntermediateCacheConfig( hKernel, CacheConfig );

        // capture parameters
        ze_kernel_set_intermediate_cache_config_params_t out_params = {
            &hKernel,
            &CacheConfig
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetIntermediateCacheConfigCb )
                    table.pfnSetIntermediateCacheConfigCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    ze_result_t __zecall
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_get_properties_params_t in_params = {
            &hKernel,
            &pKernelProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelGetProperties( hKernel, pKernelProperties );

        // capture parameters
        ze_kernel_get_properties_params_t out_params = {
            &hKernel,
            &pKernelProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernel
    ze_result_t __zecall
    zeCommandListAppendLaunchKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_launch_kernel_params_t in_params = {
            &hCommandList,
            &hKernel,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelCb )
                    table.pfnAppendLaunchKernelCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_kernel_params_t out_params = {
            &hCommandList,
            &hKernel,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelCb )
                    table.pfnAppendLaunchKernelCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchCooperativeKernel
    ze_result_t __zecall
    zeCommandListAppendLaunchCooperativeKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_launch_cooperative_kernel_params_t in_params = {
            &hCommandList,
            &hKernel,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchCooperativeKernelCb )
                    table.pfnAppendLaunchCooperativeKernelCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_cooperative_kernel_params_t out_params = {
            &hCommandList,
            &hKernel,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchCooperativeKernelCb )
                    table.pfnAppendLaunchCooperativeKernelCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelIndirect
    ze_result_t __zecall
    zeCommandListAppendLaunchKernelIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_launch_kernel_indirect_params_t in_params = {
            &hCommandList,
            &hKernel,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelIndirectCb )
                    table.pfnAppendLaunchKernelIndirectCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_kernel_indirect_params_t out_params = {
            &hCommandList,
            &hKernel,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelIndirectCb )
                    table.pfnAppendLaunchKernelIndirectCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchMultipleKernelsIndirect
    ze_result_t __zecall
    zeCommandListAppendLaunchMultipleKernelsIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less-than or equal-to
                                                        ///< numKernels
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_launch_multiple_kernels_indirect_params_t in_params = {
            &hCommandList,
            &numKernels,
            &phKernels,
            &pCountBuffer,
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchMultipleKernelsIndirectCb )
                    table.pfnAppendLaunchMultipleKernelsIndirectCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_multiple_kernels_indirect_params_t out_params = {
            &hCommandList,
            &numKernels,
            &phKernels,
            &pCountBuffer,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchMultipleKernelsIndirectCb )
                    table.pfnAppendLaunchMultipleKernelsIndirectCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchHostFunction
    ze_result_t __zecall
    zeCommandListAppendLaunchHostFunction(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData,                                ///< [in] pointer to user data to pass to host function.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_launch_host_function_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchHostFunctionCb )
                    table.pfnAppendLaunchHostFunctionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_host_function_params_t out_params = {
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
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchHostFunctionCb )
                    table.pfnAppendLaunchHostFunctionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceMakeMemoryResident
    ze_result_t __zecall
    zeDeviceMakeMemoryResident(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_make_memory_resident_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnMakeMemoryResidentCb )
                    table.pfnMakeMemoryResidentCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceMakeMemoryResident( hDevice, ptr, size );

        // capture parameters
        ze_device_make_memory_resident_params_t out_params = {
            &hDevice,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnMakeMemoryResidentCb )
                    table.pfnMakeMemoryResidentCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceEvictMemory
    ze_result_t __zecall
    zeDeviceEvictMemory(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_evict_memory_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnEvictMemoryCb )
                    table.pfnEvictMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceEvictMemory( hDevice, ptr, size );

        // capture parameters
        ze_device_evict_memory_params_t out_params = {
            &hDevice,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnEvictMemoryCb )
                    table.pfnEvictMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceMakeImageResident
    ze_result_t __zecall
    zeDeviceMakeImageResident(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_make_image_resident_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnMakeImageResidentCb )
                    table.pfnMakeImageResidentCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceMakeImageResident( hDevice, hImage );

        // capture parameters
        ze_device_make_image_resident_params_t out_params = {
            &hDevice,
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnMakeImageResidentCb )
                    table.pfnMakeImageResidentCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceEvictImage
    ze_result_t __zecall
    zeDeviceEvictImage(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_evict_image_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnEvictImageCb )
                    table.pfnEvictImageCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceEvictImage( hDevice, hImage );

        // capture parameters
        ze_device_evict_image_params_t out_params = {
            &hDevice,
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnEvictImageCb )
                    table.pfnEvictImageCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerCreate
    ze_result_t __zecall
    zeSamplerCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_sampler_create_params_t in_params = {
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
                auto& table = context.tracerData[ i ].zePrologueCbs.Sampler;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeSamplerCreate( hDevice, desc, phSampler );

        // capture parameters
        ze_sampler_create_params_t out_params = {
            &hDevice,
            &desc,
            &phSampler
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Sampler;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    ze_result_t __zecall
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_sampler_destroy_params_t in_params = {
            &hSampler
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Sampler;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeSamplerDestroy( hSampler );

        // capture parameters
        ze_sampler_destroy_params_t out_params = {
            &hSampler
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Sampler;
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnInit                                   = instrumented::zeInit;
    else
        pDdiTable->pfnInit                                   = driver::zeInit;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGet                                    = instrumented::zeDeviceGet;
    else
        pDdiTable->pfnGet                                    = driver::zeDeviceGet;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetSubDevices                          = instrumented::zeDeviceGetSubDevices;
    else
        pDdiTable->pfnGetSubDevices                          = driver::zeDeviceGetSubDevices;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeDeviceGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeDeviceGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetComputeProperties                   = instrumented::zeDeviceGetComputeProperties;
    else
        pDdiTable->pfnGetComputeProperties                   = driver::zeDeviceGetComputeProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetKernelProperties                    = instrumented::zeDeviceGetKernelProperties;
    else
        pDdiTable->pfnGetKernelProperties                    = driver::zeDeviceGetKernelProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemoryProperties                    = instrumented::zeDeviceGetMemoryProperties;
    else
        pDdiTable->pfnGetMemoryProperties                    = driver::zeDeviceGetMemoryProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemoryAccessProperties              = instrumented::zeDeviceGetMemoryAccessProperties;
    else
        pDdiTable->pfnGetMemoryAccessProperties              = driver::zeDeviceGetMemoryAccessProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetCacheProperties                     = instrumented::zeDeviceGetCacheProperties;
    else
        pDdiTable->pfnGetCacheProperties                     = driver::zeDeviceGetCacheProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetImageProperties                     = instrumented::zeDeviceGetImageProperties;
    else
        pDdiTable->pfnGetImageProperties                     = driver::zeDeviceGetImageProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetP2PProperties                       = instrumented::zeDeviceGetP2PProperties;
    else
        pDdiTable->pfnGetP2PProperties                       = driver::zeDeviceGetP2PProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCanAccessPeer                          = instrumented::zeDeviceCanAccessPeer;
    else
        pDdiTable->pfnCanAccessPeer                          = driver::zeDeviceCanAccessPeer;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetLastLevelCacheConfig                = instrumented::zeDeviceSetLastLevelCacheConfig;
    else
        pDdiTable->pfnSetLastLevelCacheConfig                = driver::zeDeviceSetLastLevelCacheConfig;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSystemBarrier                          = instrumented::zeDeviceSystemBarrier;
    else
        pDdiTable->pfnSystemBarrier                          = driver::zeDeviceSystemBarrier;

#if ZE_ENABLE_OCL_INTEROP
    if( instrumented::context.enableTracing )
        pDdiTable->pfnRegisterCLMemory                       = instrumented::zeDeviceRegisterCLMemory;
    else
        pDdiTable->pfnRegisterCLMemory                       = driver::zeDeviceRegisterCLMemory;
#else
    pDdiTable->pfnRegisterCLMemory                       = nullptr;
#endif

#if ZE_ENABLE_OCL_INTEROP
    if( instrumented::context.enableTracing )
        pDdiTable->pfnRegisterCLProgram                      = instrumented::zeDeviceRegisterCLProgram;
    else
        pDdiTable->pfnRegisterCLProgram                      = driver::zeDeviceRegisterCLProgram;
#else
    pDdiTable->pfnRegisterCLProgram                      = nullptr;
#endif

#if ZE_ENABLE_OCL_INTEROP
    if( instrumented::context.enableTracing )
        pDdiTable->pfnRegisterCLCommandQueue                 = instrumented::zeDeviceRegisterCLCommandQueue;
    else
        pDdiTable->pfnRegisterCLCommandQueue                 = driver::zeDeviceRegisterCLCommandQueue;
#else
    pDdiTable->pfnRegisterCLCommandQueue                 = nullptr;
#endif

    if( instrumented::context.enableTracing )
        pDdiTable->pfnMakeMemoryResident                     = instrumented::zeDeviceMakeMemoryResident;
    else
        pDdiTable->pfnMakeMemoryResident                     = driver::zeDeviceMakeMemoryResident;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnEvictMemory                            = instrumented::zeDeviceEvictMemory;
    else
        pDdiTable->pfnEvictMemory                            = driver::zeDeviceEvictMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnMakeImageResident                      = instrumented::zeDeviceMakeImageResident;
    else
        pDdiTable->pfnMakeImageResident                      = driver::zeDeviceMakeImageResident;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnEvictImage                             = instrumented::zeDeviceEvictImage;
    else
        pDdiTable->pfnEvictImage                             = driver::zeDeviceEvictImage;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGet                                    = instrumented::zeDriverGet;
    else
        pDdiTable->pfnGet                                    = driver::zeDriverGet;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetDriverVersion                       = instrumented::zeDriverGetDriverVersion;
    else
        pDdiTable->pfnGetDriverVersion                       = driver::zeDriverGetDriverVersion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetApiVersion                          = instrumented::zeDriverGetApiVersion;
    else
        pDdiTable->pfnGetApiVersion                          = driver::zeDriverGetApiVersion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIPCProperties                       = instrumented::zeDriverGetIPCProperties;
    else
        pDdiTable->pfnGetIPCProperties                       = driver::zeDriverGetIPCProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetExtensionFunctionAddress            = instrumented::zeDriverGetExtensionFunctionAddress;
    else
        pDdiTable->pfnGetExtensionFunctionAddress            = driver::zeDriverGetExtensionFunctionAddress;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocSharedMem                         = instrumented::zeDriverAllocSharedMem;
    else
        pDdiTable->pfnAllocSharedMem                         = driver::zeDriverAllocSharedMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocDeviceMem                         = instrumented::zeDriverAllocDeviceMem;
    else
        pDdiTable->pfnAllocDeviceMem                         = driver::zeDriverAllocDeviceMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocHostMem                           = instrumented::zeDriverAllocHostMem;
    else
        pDdiTable->pfnAllocHostMem                           = driver::zeDriverAllocHostMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnFreeMem                                = instrumented::zeDriverFreeMem;
    else
        pDdiTable->pfnFreeMem                                = driver::zeDriverFreeMem;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemAllocProperties                  = instrumented::zeDriverGetMemAllocProperties;
    else
        pDdiTable->pfnGetMemAllocProperties                  = driver::zeDriverGetMemAllocProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemAddressRange                     = instrumented::zeDriverGetMemAddressRange;
    else
        pDdiTable->pfnGetMemAddressRange                     = driver::zeDriverGetMemAddressRange;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemIpcHandle                        = instrumented::zeDriverGetMemIpcHandle;
    else
        pDdiTable->pfnGetMemIpcHandle                        = driver::zeDriverGetMemIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnOpenMemIpcHandle                       = instrumented::zeDriverOpenMemIpcHandle;
    else
        pDdiTable->pfnOpenMemIpcHandle                       = driver::zeDriverOpenMemIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCloseMemIpcHandle                      = instrumented::zeDriverCloseMemIpcHandle;
    else
        pDdiTable->pfnCloseMemIpcHandle                      = driver::zeDriverCloseMemIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeCommandQueueCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeCommandQueueCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeCommandQueueDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeCommandQueueDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnExecuteCommandLists                    = instrumented::zeCommandQueueExecuteCommandLists;
    else
        pDdiTable->pfnExecuteCommandLists                    = driver::zeCommandQueueExecuteCommandLists;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSynchronize                            = instrumented::zeCommandQueueSynchronize;
    else
        pDdiTable->pfnSynchronize                            = driver::zeCommandQueueSynchronize;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeCommandListCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeCommandListCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreateImmediate                        = instrumented::zeCommandListCreateImmediate;
    else
        pDdiTable->pfnCreateImmediate                        = driver::zeCommandListCreateImmediate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeCommandListDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeCommandListDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnClose                                  = instrumented::zeCommandListClose;
    else
        pDdiTable->pfnClose                                  = driver::zeCommandListClose;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::zeCommandListReset;
    else
        pDdiTable->pfnReset                                  = driver::zeCommandListReset;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendBarrier                          = instrumented::zeCommandListAppendBarrier;
    else
        pDdiTable->pfnAppendBarrier                          = driver::zeCommandListAppendBarrier;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryRangesBarrier              = instrumented::zeCommandListAppendMemoryRangesBarrier;
    else
        pDdiTable->pfnAppendMemoryRangesBarrier              = driver::zeCommandListAppendMemoryRangesBarrier;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryCopy                       = instrumented::zeCommandListAppendMemoryCopy;
    else
        pDdiTable->pfnAppendMemoryCopy                       = driver::zeCommandListAppendMemoryCopy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryFill                       = instrumented::zeCommandListAppendMemoryFill;
    else
        pDdiTable->pfnAppendMemoryFill                       = driver::zeCommandListAppendMemoryFill;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryCopyRegion                 = instrumented::zeCommandListAppendMemoryCopyRegion;
    else
        pDdiTable->pfnAppendMemoryCopyRegion                 = driver::zeCommandListAppendMemoryCopyRegion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopy                        = instrumented::zeCommandListAppendImageCopy;
    else
        pDdiTable->pfnAppendImageCopy                        = driver::zeCommandListAppendImageCopy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyRegion                  = instrumented::zeCommandListAppendImageCopyRegion;
    else
        pDdiTable->pfnAppendImageCopyRegion                  = driver::zeCommandListAppendImageCopyRegion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyToMemory                = instrumented::zeCommandListAppendImageCopyToMemory;
    else
        pDdiTable->pfnAppendImageCopyToMemory                = driver::zeCommandListAppendImageCopyToMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyFromMemory              = instrumented::zeCommandListAppendImageCopyFromMemory;
    else
        pDdiTable->pfnAppendImageCopyFromMemory              = driver::zeCommandListAppendImageCopyFromMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryPrefetch                   = instrumented::zeCommandListAppendMemoryPrefetch;
    else
        pDdiTable->pfnAppendMemoryPrefetch                   = driver::zeCommandListAppendMemoryPrefetch;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemAdvise                        = instrumented::zeCommandListAppendMemAdvise;
    else
        pDdiTable->pfnAppendMemAdvise                        = driver::zeCommandListAppendMemAdvise;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendSignalEvent                      = instrumented::zeCommandListAppendSignalEvent;
    else
        pDdiTable->pfnAppendSignalEvent                      = driver::zeCommandListAppendSignalEvent;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendWaitOnEvents                     = instrumented::zeCommandListAppendWaitOnEvents;
    else
        pDdiTable->pfnAppendWaitOnEvents                     = driver::zeCommandListAppendWaitOnEvents;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendEventReset                       = instrumented::zeCommandListAppendEventReset;
    else
        pDdiTable->pfnAppendEventReset                       = driver::zeCommandListAppendEventReset;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchKernel                     = instrumented::zeCommandListAppendLaunchKernel;
    else
        pDdiTable->pfnAppendLaunchKernel                     = driver::zeCommandListAppendLaunchKernel;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchCooperativeKernel          = instrumented::zeCommandListAppendLaunchCooperativeKernel;
    else
        pDdiTable->pfnAppendLaunchCooperativeKernel          = driver::zeCommandListAppendLaunchCooperativeKernel;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchKernelIndirect             = instrumented::zeCommandListAppendLaunchKernelIndirect;
    else
        pDdiTable->pfnAppendLaunchKernelIndirect             = driver::zeCommandListAppendLaunchKernelIndirect;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = instrumented::zeCommandListAppendLaunchMultipleKernelsIndirect;
    else
        pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = driver::zeCommandListAppendLaunchMultipleKernelsIndirect;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchHostFunction               = instrumented::zeCommandListAppendLaunchHostFunction;
    else
        pDdiTable->pfnAppendLaunchHostFunction               = driver::zeCommandListAppendLaunchHostFunction;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeFenceCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeFenceCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeFenceDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeFenceDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSynchronize                        = instrumented::zeFenceHostSynchronize;
    else
        pDdiTable->pfnHostSynchronize                        = driver::zeFenceHostSynchronize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryStatus                            = instrumented::zeFenceQueryStatus;
    else
        pDdiTable->pfnQueryStatus                            = driver::zeFenceQueryStatus;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::zeFenceReset;
    else
        pDdiTable->pfnReset                                  = driver::zeFenceReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeEventPoolCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeEventPoolCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeEventPoolDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeEventPoolDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIpcHandle                           = instrumented::zeEventPoolGetIpcHandle;
    else
        pDdiTable->pfnGetIpcHandle                           = driver::zeEventPoolGetIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnOpenIpcHandle                          = instrumented::zeEventPoolOpenIpcHandle;
    else
        pDdiTable->pfnOpenIpcHandle                          = driver::zeEventPoolOpenIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCloseIpcHandle                         = instrumented::zeEventPoolCloseIpcHandle;
    else
        pDdiTable->pfnCloseIpcHandle                         = driver::zeEventPoolCloseIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeEventCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeEventCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeEventDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeEventDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSignal                             = instrumented::zeEventHostSignal;
    else
        pDdiTable->pfnHostSignal                             = driver::zeEventHostSignal;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSynchronize                        = instrumented::zeEventHostSynchronize;
    else
        pDdiTable->pfnHostSynchronize                        = driver::zeEventHostSynchronize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryStatus                            = instrumented::zeEventQueryStatus;
    else
        pDdiTable->pfnQueryStatus                            = driver::zeEventQueryStatus;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::zeEventReset;
    else
        pDdiTable->pfnReset                                  = driver::zeEventReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeImageGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeImageGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeImageCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeImageCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeImageDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeImageDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeModuleCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeModuleCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeModuleDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeModuleDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetNativeBinary                        = instrumented::zeModuleGetNativeBinary;
    else
        pDdiTable->pfnGetNativeBinary                        = driver::zeModuleGetNativeBinary;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetGlobalPointer                       = instrumented::zeModuleGetGlobalPointer;
    else
        pDdiTable->pfnGetGlobalPointer                       = driver::zeModuleGetGlobalPointer;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetFunctionPointer                     = instrumented::zeModuleGetFunctionPointer;
    else
        pDdiTable->pfnGetFunctionPointer                     = driver::zeModuleGetFunctionPointer;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeModuleBuildLogDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeModuleBuildLogDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetString                              = instrumented::zeModuleBuildLogGetString;
    else
        pDdiTable->pfnGetString                              = driver::zeModuleBuildLogGetString;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeKernelCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeKernelCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeKernelDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeKernelDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetIntermediateCacheConfig             = instrumented::zeKernelSetIntermediateCacheConfig;
    else
        pDdiTable->pfnSetIntermediateCacheConfig             = driver::zeKernelSetIntermediateCacheConfig;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetGroupSize                           = instrumented::zeKernelSetGroupSize;
    else
        pDdiTable->pfnSetGroupSize                           = driver::zeKernelSetGroupSize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSuggestGroupSize                       = instrumented::zeKernelSuggestGroupSize;
    else
        pDdiTable->pfnSuggestGroupSize                       = driver::zeKernelSuggestGroupSize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSuggestMaxCooperativeGroupCount        = instrumented::zeKernelSuggestMaxCooperativeGroupCount;
    else
        pDdiTable->pfnSuggestMaxCooperativeGroupCount        = driver::zeKernelSuggestMaxCooperativeGroupCount;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetArgumentValue                       = instrumented::zeKernelSetArgumentValue;
    else
        pDdiTable->pfnSetArgumentValue                       = driver::zeKernelSetArgumentValue;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetAttribute                           = instrumented::zeKernelSetAttribute;
    else
        pDdiTable->pfnSetAttribute                           = driver::zeKernelSetAttribute;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeKernelGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeKernelGetProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__zedllexport ze_result_t __zecall
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeSamplerCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeSamplerCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeSamplerDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeSamplerDestroy;

    return result;
}

#if defined(__cplusplus)
};
#endif
