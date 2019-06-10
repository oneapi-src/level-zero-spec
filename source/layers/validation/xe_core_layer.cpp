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
* @file xe_core_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/valddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeInit
    xe_result_t __xecall
    xeInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        auto pfnInit = context.xeDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
        }

        return pfnInit( flags );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetDriverVersion
    xe_result_t __xecall
    xeDeviceGroupGetDriverVersion(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
        uint32_t* version                               ///< [out] driver version
        )
    {
        auto pfnGetDriverVersion = context.xeDdiTable.DeviceGroup.pfnGetDriverVersion;

        if( nullptr == pfnGetDriverVersion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == version )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDriverVersion( hDeviceGroup, version );
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
        xe_device_group_handle_t* phDeviceGroups        ///< [in,out][optional][range(0, *pCount)] array of handle of device groups
        )
    {
        auto pfnGet = context.xeDdiTable.DeviceGroup.pfnGet;

        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( pCount, phDeviceGroups );
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
        xe_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
        )
    {
        auto pfnGet = context.xeDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGet( hDeviceGroup, pCount, phDevices );
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
        xe_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices
        )
    {
        auto pfnGetSubDevices = context.xeDdiTable.Device.pfnGetSubDevices;

        if( nullptr == pfnGetSubDevices )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetSubDevices( hDevice, pCount, phSubdevices );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetApiVersion
    xe_result_t __xecall
    xeDeviceGroupGetApiVersion(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_api_version_t* version                       ///< [out] api version
        )
    {
        auto pfnGetApiVersion = context.xeDdiTable.DeviceGroup.pfnGetApiVersion;

        if( nullptr == pfnGetApiVersion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == version )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetApiVersion( hDeviceGroup, version );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetDeviceProperties
    xe_result_t __xecall
    xeDeviceGroupGetDeviceProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
        )
    {
        auto pfnGetDeviceProperties = context.xeDdiTable.DeviceGroup.pfnGetDeviceProperties;

        if( nullptr == pfnGetDeviceProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pDeviceProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetDeviceProperties( hDeviceGroup, pDeviceProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetComputeProperties
    xe_result_t __xecall
    xeDeviceGroupGetComputeProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
        )
    {
        auto pfnGetComputeProperties = context.xeDdiTable.DeviceGroup.pfnGetComputeProperties;

        if( nullptr == pfnGetComputeProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pComputeProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetComputeProperties( hDeviceGroup, pComputeProperties );
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
        xe_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        auto pfnGetMemoryProperties = context.xeDdiTable.DeviceGroup.pfnGetMemoryProperties;

        if( nullptr == pfnGetMemoryProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCount )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMemoryProperties( hDeviceGroup, pCount, pMemProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetMemoryAccessProperties
    xe_result_t __xecall
    xeDeviceGroupGetMemoryAccessProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_memory_access_properties_t* pMemAccessProperties  ///< [out] query result for memory access properties
        )
    {
        auto pfnGetMemoryAccessProperties = context.xeDdiTable.DeviceGroup.pfnGetMemoryAccessProperties;

        if( nullptr == pfnGetMemoryAccessProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMemAccessProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMemoryAccessProperties( hDeviceGroup, pMemAccessProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetCacheProperties
    xe_result_t __xecall
    xeDeviceGroupGetCacheProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_cache_properties_t* pCacheProperties  ///< [out] query result for cache properties
        )
    {
        auto pfnGetCacheProperties = context.xeDdiTable.DeviceGroup.pfnGetCacheProperties;

        if( nullptr == pfnGetCacheProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pCacheProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetCacheProperties( hDeviceGroup, pCacheProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupGetImageProperties
    xe_result_t __xecall
    xeDeviceGroupGetImageProperties(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        xe_device_image_properties_t* pImageProperties  ///< [out] query result for image properties
        )
    {
        auto pfnGetImageProperties = context.xeDdiTable.DeviceGroup.pfnGetImageProperties;

        if( nullptr == pfnGetImageProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pImageProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetImageProperties( hDeviceGroup, pImageProperties );
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
        auto pfnGetP2PProperties = context.xeDdiTable.Device.pfnGetP2PProperties;

        if( nullptr == pfnGetP2PProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hPeerDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pP2PProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
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
        auto pfnCanAccessPeer = context.xeDdiTable.Device.pfnCanAccessPeer;

        if( nullptr == pfnCanAccessPeer )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hPeerDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == value )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCanAccessPeer( hDevice, hPeerDevice, value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceSetIntermediateCacheConfig
    xe_result_t __xecall
    xeDeviceSetIntermediateCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        auto pfnSetIntermediateCacheConfig = context.xeDdiTable.Device.pfnSetIntermediateCacheConfig;

        if( nullptr == pfnSetIntermediateCacheConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetIntermediateCacheConfig( hDevice, CacheConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceSetLastLevelCacheConfig
    xe_result_t __xecall
    xeDeviceSetLastLevelCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        auto pfnSetLastLevelCacheConfig = context.xeDdiTable.Device.pfnSetLastLevelCacheConfig;

        if( nullptr == pfnSetLastLevelCacheConfig )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
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
        auto pfnCreate = context.xeDdiTable.CommandQueue.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phCommandQueue )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, desc, phCommandQueue );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandQueueDestroy
    xe_result_t __xecall
    xeCommandQueueDestroy(
        xe_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        auto pfnDestroy = context.xeDdiTable.CommandQueue.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hCommandQueue );
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
        auto pfnExecuteCommandLists = context.xeDdiTable.CommandQueue.pfnExecuteCommandLists;

        if( nullptr == pfnExecuteCommandLists )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phCommandLists )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
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
        auto pfnSynchronize = context.xeDdiTable.CommandQueue.pfnSynchronize;

        if( nullptr == pfnSynchronize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSynchronize( hCommandQueue, timeout );
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
        auto pfnCreate = context.xeDdiTable.CommandList.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, desc, phCommandList );
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
        auto pfnCreateImmediate = context.xeDdiTable.CommandList.pfnCreateImmediate;

        if( nullptr == pfnCreateImmediate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == altdesc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < altdesc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreateImmediate( hDevice, altdesc, phCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListDestroy
    xe_result_t __xecall
    xeCommandListDestroy(
        xe_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        auto pfnDestroy = context.xeDdiTable.CommandList.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListClose
    xe_result_t __xecall
    xeCommandListClose(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        auto pfnClose = context.xeDdiTable.CommandList.pfnClose;

        if( nullptr == pfnClose )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnClose( hCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListReset
    xe_result_t __xecall
    xeCommandListReset(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        auto pfnReset = context.xeDdiTable.CommandList.pfnReset;

        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReset( hCommandList );
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
        auto pfnSetParameter = context.xeDdiTable.CommandList.pfnSetParameter;

        if( nullptr == pfnSetParameter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetParameter( hCommandList, parameter, value );
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
        auto pfnGetParameter = context.xeDdiTable.CommandList.pfnGetParameter;

        if( nullptr == pfnGetParameter )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == value )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetParameter( hCommandList, parameter, value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListResetParameters
    xe_result_t __xecall
    xeCommandListResetParameters(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
        )
    {
        auto pfnResetParameters = context.xeDdiTable.CommandList.pfnResetParameters;

        if( nullptr == pfnResetParameters )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnResetParameters( hCommandList );
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
        auto pfnReserveSpace = context.xeDdiTable.CommandList.pfnReserveSpace;

        if( nullptr == pfnReserveSpace )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReserveSpace( hCommandList, size, ptr );
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
        auto pfnAppendBarrier = context.xeDdiTable.CommandList.pfnAppendBarrier;

        if( nullptr == pfnAppendBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendMemoryRangesBarrier = context.xeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;

        if( nullptr == pfnAppendMemoryRangesBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRangeSizes )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pRanges )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceSystemBarrier
    xe_result_t __xecall
    xeDeviceSystemBarrier(
        xe_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        auto pfnSystemBarrier = context.xeDdiTable.Device.pfnSystemBarrier;

        if( nullptr == pfnSystemBarrier )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSystemBarrier( hDevice );
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
        auto pfnRegisterCLMemory = context.xeDdiTable.Device.pfnRegisterCLMemory;

        if( nullptr == pfnRegisterCLMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRegisterCLMemory( hDevice, context, mem, ptr );
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
        auto pfnRegisterCLProgram = context.xeDdiTable.Device.pfnRegisterCLProgram;

        if( nullptr == pfnRegisterCLProgram )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRegisterCLProgram( hDevice, context, program, phModule );
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
        auto pfnRegisterCLCommandQueue = context.xeDdiTable.Device.pfnRegisterCLCommandQueue;

        if( nullptr == pfnRegisterCLCommandQueue )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phCommandQueue )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
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
        auto pfnAppendMemoryCopy = context.xeDdiTable.CommandList.pfnAppendMemoryCopy;

        if( nullptr == pfnAppendMemoryCopy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == dstptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == srcptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
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
        auto pfnAppendMemorySet = context.xeDdiTable.CommandList.pfnAppendMemorySet;

        if( nullptr == pfnAppendMemorySet )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );
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
        auto pfnAppendMemoryCopyRegion = context.xeDdiTable.CommandList.pfnAppendMemoryCopyRegion;

        if( nullptr == pfnAppendMemoryCopyRegion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == dstptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == dstRegion )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == srcptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == srcRegion )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );
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
        auto pfnAppendImageCopy = context.xeDdiTable.CommandList.pfnAppendImageCopy;

        if( nullptr == pfnAppendImageCopy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDstImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hSrcImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
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
        auto pfnAppendImageCopyRegion = context.xeDdiTable.CommandList.pfnAppendImageCopyRegion;

        if( nullptr == pfnAppendImageCopyRegion )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDstImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hSrcImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
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
        auto pfnAppendImageCopyToMemory = context.xeDdiTable.CommandList.pfnAppendImageCopyToMemory;

        if( nullptr == pfnAppendImageCopyToMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == dstptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hSrcImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
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
        auto pfnAppendImageCopyFromMemory = context.xeDdiTable.CommandList.pfnAppendImageCopyFromMemory;

        if( nullptr == pfnAppendImageCopyFromMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDstImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == srcptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
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
        auto pfnAppendMemoryPrefetch = context.xeDdiTable.CommandList.pfnAppendMemoryPrefetch;

        if( nullptr == pfnAppendMemoryPrefetch )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMemoryPrefetch( hCommandList, ptr, size );
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
        auto pfnAppendMemAdvise = context.xeDdiTable.CommandList.pfnAppendMemAdvise;

        if( nullptr == pfnAppendMemAdvise )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
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
        auto pfnCreate = context.xeDdiTable.EventPool.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phEventPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDeviceGroup, desc, numDevices, phDevices, phEventPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolDestroy
    xe_result_t __xecall
    xeEventPoolDestroy(
        xe_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        auto pfnDestroy = context.xeDdiTable.EventPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hEventPool );
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
        auto pfnCreate = context.xeDdiTable.Event.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_EVENT_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hEventPool, desc, phEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventDestroy
    xe_result_t __xecall
    xeEventDestroy(
        xe_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        auto pfnDestroy = context.xeDdiTable.Event.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolGetIpcHandle
    xe_result_t __xecall
    xeEventPoolGetIpcHandle(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        auto pfnGetIpcHandle = context.xeDdiTable.EventPool.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phIpc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetIpcHandle( hEventPool, phIpc );
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
        auto pfnOpenIpcHandle = context.xeDdiTable.EventPool.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hIpc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phEventPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnOpenIpcHandle( hDevice, hIpc, phEventPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventPoolCloseIpcHandle
    xe_result_t __xecall
    xeEventPoolCloseIpcHandle(
        xe_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        auto pfnCloseIpcHandle = context.xeDdiTable.EventPool.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCloseIpcHandle( hEventPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendSignalEvent
    xe_result_t __xecall
    xeCommandListAppendSignalEvent(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendSignalEvent = context.xeDdiTable.CommandList.pfnAppendSignalEvent;

        if( nullptr == pfnAppendSignalEvent )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendSignalEvent( hCommandList, hEvent );
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
        auto pfnAppendWaitOnEvents = context.xeDdiTable.CommandList.pfnAppendWaitOnEvents;

        if( nullptr == pfnAppendWaitOnEvents )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phEvents )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventHostSignal
    xe_result_t __xecall
    xeEventHostSignal(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnHostSignal = context.xeDdiTable.Event.pfnHostSignal;

        if( nullptr == pfnHostSignal )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnHostSignal( hEvent );
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
        auto pfnHostSynchronize = context.xeDdiTable.Event.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnHostSynchronize( hEvent, timeout );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventQueryStatus
    xe_result_t __xecall
    xeEventQueryStatus(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnQueryStatus = context.xeDdiTable.Event.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnQueryStatus( hEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeCommandListAppendEventReset
    xe_result_t __xecall
    xeCommandListAppendEventReset(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendEventReset = context.xeDdiTable.CommandList.pfnAppendEventReset;

        if( nullptr == pfnAppendEventReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendEventReset( hCommandList, hEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeEventReset
    xe_result_t __xecall
    xeEventReset(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnReset = context.xeDdiTable.Event.pfnReset;

        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReset( hEvent );
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
        auto pfnCreate = context.xeDdiTable.Fence.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phFence )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_FENCE_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hCommandQueue, desc, phFence );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceDestroy
    xe_result_t __xecall
    xeFenceDestroy(
        xe_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        auto pfnDestroy = context.xeDdiTable.Fence.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hFence );
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
        auto pfnHostSynchronize = context.xeDdiTable.Fence.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnHostSynchronize( hFence, timeout );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceQueryStatus
    xe_result_t __xecall
    xeFenceQueryStatus(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnQueryStatus = context.xeDdiTable.Fence.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnQueryStatus( hFence );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFenceReset
    xe_result_t __xecall
    xeFenceReset(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnReset = context.xeDdiTable.Fence.pfnReset;

        if( nullptr == pfnReset )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnReset( hFence );
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
        auto pfnGetProperties = context.xeDdiTable.Image.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pImageProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnGetProperties( hDevice, desc, pImageProperties );
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
        auto pfnCreate = context.xeDdiTable.Image.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, desc, phImage );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeImageDestroy
    xe_result_t __xecall
    xeImageDestroy(
        xe_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        auto pfnDestroy = context.xeDdiTable.Image.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hImage );
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
        auto pfnAllocSharedMem = context.xeDdiTable.DeviceGroup.pfnAllocSharedMem;

        if( nullptr == pfnAllocSharedMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAllocSharedMem( hDeviceGroup, hDevice, device_flags, ordinal, host_flags, size, alignment, ptr );
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
        auto pfnAllocDeviceMem = context.xeDdiTable.DeviceGroup.pfnAllocDeviceMem;

        if( nullptr == pfnAllocDeviceMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAllocDeviceMem( hDeviceGroup, hDevice, flags, ordinal, size, alignment, ptr );
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
        auto pfnAllocHostMem = context.xeDdiTable.DeviceGroup.pfnAllocHostMem;

        if( nullptr == pfnAllocHostMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAllocHostMem( hDeviceGroup, flags, size, alignment, ptr );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupFreeMem
    xe_result_t __xecall
    xeDeviceGroupFreeMem(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto pfnFreeMem = context.xeDdiTable.DeviceGroup.pfnFreeMem;

        if( nullptr == pfnFreeMem )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnFreeMem( hDeviceGroup, ptr );
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
        auto pfnGetMemProperties = context.xeDdiTable.DeviceGroup.pfnGetMemProperties;

        if( nullptr == pfnGetMemProperties )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pMemProperties )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMemProperties( hDeviceGroup, ptr, pMemProperties, phDevice );
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
        auto pfnGetMemAddressRange = context.xeDdiTable.DeviceGroup.pfnGetMemAddressRange;

        if( nullptr == pfnGetMemAddressRange )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMemAddressRange( hDeviceGroup, ptr, pBase, pSize );
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
        auto pfnGetMemIpcHandle = context.xeDdiTable.DeviceGroup.pfnGetMemIpcHandle;

        if( nullptr == pfnGetMemIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pIpcHandle )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetMemIpcHandle( hDeviceGroup, ptr, pIpcHandle );
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
        auto pfnOpenMemIpcHandle = context.xeDdiTable.DeviceGroup.pfnOpenMemIpcHandle;

        if( nullptr == pfnOpenMemIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == handle )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnOpenMemIpcHandle( hDeviceGroup, hDevice, handle, flags, ptr );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceGroupCloseMemIpcHandle
    xe_result_t __xecall
    xeDeviceGroupCloseMemIpcHandle(
        xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto pfnCloseMemIpcHandle = context.xeDdiTable.DeviceGroup.pfnCloseMemIpcHandle;

        if( nullptr == pfnCloseMemIpcHandle )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDeviceGroup )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnCloseMemIpcHandle( hDeviceGroup, ptr );
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
        auto pfnCreate = context.xeDdiTable.Module.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_MODULE_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, desc, phModule, phBuildLog );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleDestroy
    xe_result_t __xecall
    xeModuleDestroy(
        xe_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        auto pfnDestroy = context.xeDdiTable.Module.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hModule );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleBuildLogDestroy
    xe_result_t __xecall
    xeModuleBuildLogDestroy(
        xe_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        auto pfnDestroy = context.xeDdiTable.ModuleBuildLog.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModuleBuildLog )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hModuleBuildLog );
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
        auto pfnGetString = context.xeDdiTable.ModuleBuildLog.pfnGetString;

        if( nullptr == pfnGetString )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModuleBuildLog )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pSize )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeModuleGetNativeBinary
    xe_result_t __xecall
    xeModuleGetNativeBinary(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        auto pfnGetNativeBinary = context.xeDdiTable.Module.pfnGetNativeBinary;

        if( nullptr == pfnGetNativeBinary )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pSize )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
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
        auto pfnGetGlobalPointer = context.xeDdiTable.Module.pfnGetGlobalPointer;

        if( nullptr == pfnGetGlobalPointer )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pGlobalName )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pPtr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetGlobalPointer( hModule, pGlobalName, pPtr );
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
        auto pfnCreate = context.xeDdiTable.Function.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_FUNCTION_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hModule, desc, phFunction );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeFunctionDestroy
    xe_result_t __xecall
    xeFunctionDestroy(
        xe_function_handle_t hFunction                  ///< [in][release] handle of the function object
        )
    {
        auto pfnDestroy = context.xeDdiTable.Function.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hFunction );
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
        auto pfnGetFunctionPointer = context.xeDdiTable.Module.pfnGetFunctionPointer;

        if( nullptr == pfnGetFunctionPointer )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pFunctionName )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pfnFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
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
        auto pfnSetGroupSize = context.xeDdiTable.Function.pfnSetGroupSize;

        if( nullptr == pfnSetGroupSize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
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
        auto pfnSuggestGroupSize = context.xeDdiTable.Function.pfnSuggestGroupSize;

        if( nullptr == pfnSuggestGroupSize )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == groupSizeX )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == groupSizeY )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == groupSizeZ )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
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
        auto pfnSetArgumentValue = context.xeDdiTable.Function.pfnSetArgumentValue;

        if( nullptr == pfnSetArgumentValue )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
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
        auto pfnSetAttribute = context.xeDdiTable.Function.pfnSetAttribute;

        if( nullptr == pfnSetAttribute )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnSetAttribute( hFunction, attr, value );
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
        auto pfnGetAttribute = context.xeDdiTable.Function.pfnGetAttribute;

        if( nullptr == pfnGetAttribute )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pValue )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnGetAttribute( hFunction, attr, pValue );
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
        auto pfnAppendLaunchFunction = context.xeDdiTable.CommandList.pfnAppendLaunchFunction;

        if( nullptr == pfnAppendLaunchFunction )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLaunchFuncArgs )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendLaunchFunctionIndirect = context.xeDdiTable.CommandList.pfnAppendLaunchFunctionIndirect;

        if( nullptr == pfnAppendLaunchFunctionIndirect )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hFunction )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLaunchArgumentsBuffer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendLaunchMultipleFunctionsIndirect = context.xeDdiTable.CommandList.pfnAppendLaunchMultipleFunctionsIndirect;

        if( nullptr == pfnAppendLaunchMultipleFunctionsIndirect )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phFunctions )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pNumLaunchArguments )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pLaunchArgumentsBuffer )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendLaunchHostFunction = context.xeDdiTable.CommandList.pfnAppendLaunchHostFunction;

        if( nullptr == pfnAppendLaunchHostFunction )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == pUserData )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnMakeMemoryResident = context.xeDdiTable.Device.pfnMakeMemoryResident;

        if( nullptr == pfnMakeMemoryResident )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnMakeMemoryResident( hDevice, ptr, size );
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
        auto pfnEvictMemory = context.xeDdiTable.Device.pfnEvictMemory;

        if( nullptr == pfnEvictMemory )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == ptr )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEvictMemory( hDevice, ptr, size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceMakeImageResident
    xe_result_t __xecall
    xeDeviceMakeImageResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        auto pfnMakeImageResident = context.xeDdiTable.Device.pfnMakeImageResident;

        if( nullptr == pfnMakeImageResident )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnMakeImageResident( hDevice, hImage );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeDeviceEvictImage
    xe_result_t __xecall
    xeDeviceEvictImage(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        auto pfnEvictImage = context.xeDdiTable.Device.pfnEvictImage;

        if( nullptr == pfnEvictImage )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == hImage )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnEvictImage( hDevice, hImage );
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
        auto pfnCreate = context.xeDdiTable.Sampler.pfnCreate;

        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == desc )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( nullptr == phSampler )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

            if( XE_SAMPLER_DESC_VERSION_CURRENT < desc->version )
                return XE_RESULT_ERROR_UNSUPPORTED;

        }

        return pfnCreate( hDevice, desc, phSampler );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xeSamplerDestroy
    xe_result_t __xecall
    xeSamplerDestroy(
        xe_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        auto pfnDestroy = context.xeDdiTable.Sampler.pfnDestroy;

        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSampler )
                return XE_RESULT_ERROR_INVALID_ARGUMENT;

        }

        return pfnDestroy( hSampler );
    }

} // namespace layer

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
    auto& dditable = layer::context.xeDdiTable.Global;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = layer::xeInit;

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
    auto& dditable = layer::context.xeDdiTable.Device;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::xeDeviceGet;

    dditable.pfnGetSubDevices                            = pDdiTable->pfnGetSubDevices;
    pDdiTable->pfnGetSubDevices                          = layer::xeDeviceGetSubDevices;

    dditable.pfnGetP2PProperties                         = pDdiTable->pfnGetP2PProperties;
    pDdiTable->pfnGetP2PProperties                       = layer::xeDeviceGetP2PProperties;

    dditable.pfnCanAccessPeer                            = pDdiTable->pfnCanAccessPeer;
    pDdiTable->pfnCanAccessPeer                          = layer::xeDeviceCanAccessPeer;

    dditable.pfnSetIntermediateCacheConfig               = pDdiTable->pfnSetIntermediateCacheConfig;
    pDdiTable->pfnSetIntermediateCacheConfig             = layer::xeDeviceSetIntermediateCacheConfig;

    dditable.pfnSetLastLevelCacheConfig                  = pDdiTable->pfnSetLastLevelCacheConfig;
    pDdiTable->pfnSetLastLevelCacheConfig                = layer::xeDeviceSetLastLevelCacheConfig;

    dditable.pfnSystemBarrier                            = pDdiTable->pfnSystemBarrier;
    pDdiTable->pfnSystemBarrier                          = layer::xeDeviceSystemBarrier;

#if XE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLMemory                         = pDdiTable->pfnRegisterCLMemory;
    pDdiTable->pfnRegisterCLMemory                       = layer::xeDeviceRegisterCLMemory;
#endif

#if XE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLProgram                        = pDdiTable->pfnRegisterCLProgram;
    pDdiTable->pfnRegisterCLProgram                      = layer::xeDeviceRegisterCLProgram;
#endif

#if XE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLCommandQueue                   = pDdiTable->pfnRegisterCLCommandQueue;
    pDdiTable->pfnRegisterCLCommandQueue                 = layer::xeDeviceRegisterCLCommandQueue;
#endif

    dditable.pfnMakeMemoryResident                       = pDdiTable->pfnMakeMemoryResident;
    pDdiTable->pfnMakeMemoryResident                     = layer::xeDeviceMakeMemoryResident;

    dditable.pfnEvictMemory                              = pDdiTable->pfnEvictMemory;
    pDdiTable->pfnEvictMemory                            = layer::xeDeviceEvictMemory;

    dditable.pfnMakeImageResident                        = pDdiTable->pfnMakeImageResident;
    pDdiTable->pfnMakeImageResident                      = layer::xeDeviceMakeImageResident;

    dditable.pfnEvictImage                               = pDdiTable->pfnEvictImage;
    pDdiTable->pfnEvictImage                             = layer::xeDeviceEvictImage;

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
    auto& dditable = layer::context.xeDdiTable.DeviceGroup;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::xeDeviceGroupGet;

    dditable.pfnGetDriverVersion                         = pDdiTable->pfnGetDriverVersion;
    pDdiTable->pfnGetDriverVersion                       = layer::xeDeviceGroupGetDriverVersion;

    dditable.pfnGetApiVersion                            = pDdiTable->pfnGetApiVersion;
    pDdiTable->pfnGetApiVersion                          = layer::xeDeviceGroupGetApiVersion;

    dditable.pfnGetDeviceProperties                      = pDdiTable->pfnGetDeviceProperties;
    pDdiTable->pfnGetDeviceProperties                    = layer::xeDeviceGroupGetDeviceProperties;

    dditable.pfnGetComputeProperties                     = pDdiTable->pfnGetComputeProperties;
    pDdiTable->pfnGetComputeProperties                   = layer::xeDeviceGroupGetComputeProperties;

    dditable.pfnGetMemoryProperties                      = pDdiTable->pfnGetMemoryProperties;
    pDdiTable->pfnGetMemoryProperties                    = layer::xeDeviceGroupGetMemoryProperties;

    dditable.pfnGetMemoryAccessProperties                = pDdiTable->pfnGetMemoryAccessProperties;
    pDdiTable->pfnGetMemoryAccessProperties              = layer::xeDeviceGroupGetMemoryAccessProperties;

    dditable.pfnGetCacheProperties                       = pDdiTable->pfnGetCacheProperties;
    pDdiTable->pfnGetCacheProperties                     = layer::xeDeviceGroupGetCacheProperties;

    dditable.pfnGetImageProperties                       = pDdiTable->pfnGetImageProperties;
    pDdiTable->pfnGetImageProperties                     = layer::xeDeviceGroupGetImageProperties;

    dditable.pfnAllocSharedMem                           = pDdiTable->pfnAllocSharedMem;
    pDdiTable->pfnAllocSharedMem                         = layer::xeDeviceGroupAllocSharedMem;

    dditable.pfnAllocDeviceMem                           = pDdiTable->pfnAllocDeviceMem;
    pDdiTable->pfnAllocDeviceMem                         = layer::xeDeviceGroupAllocDeviceMem;

    dditable.pfnAllocHostMem                             = pDdiTable->pfnAllocHostMem;
    pDdiTable->pfnAllocHostMem                           = layer::xeDeviceGroupAllocHostMem;

    dditable.pfnFreeMem                                  = pDdiTable->pfnFreeMem;
    pDdiTable->pfnFreeMem                                = layer::xeDeviceGroupFreeMem;

    dditable.pfnGetMemProperties                         = pDdiTable->pfnGetMemProperties;
    pDdiTable->pfnGetMemProperties                       = layer::xeDeviceGroupGetMemProperties;

    dditable.pfnGetMemAddressRange                       = pDdiTable->pfnGetMemAddressRange;
    pDdiTable->pfnGetMemAddressRange                     = layer::xeDeviceGroupGetMemAddressRange;

    dditable.pfnGetMemIpcHandle                          = pDdiTable->pfnGetMemIpcHandle;
    pDdiTable->pfnGetMemIpcHandle                        = layer::xeDeviceGroupGetMemIpcHandle;

    dditable.pfnOpenMemIpcHandle                         = pDdiTable->pfnOpenMemIpcHandle;
    pDdiTable->pfnOpenMemIpcHandle                       = layer::xeDeviceGroupOpenMemIpcHandle;

    dditable.pfnCloseMemIpcHandle                        = pDdiTable->pfnCloseMemIpcHandle;
    pDdiTable->pfnCloseMemIpcHandle                      = layer::xeDeviceGroupCloseMemIpcHandle;

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
    auto& dditable = layer::context.xeDdiTable.CommandQueue;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeCommandQueueCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeCommandQueueDestroy;

    dditable.pfnExecuteCommandLists                      = pDdiTable->pfnExecuteCommandLists;
    pDdiTable->pfnExecuteCommandLists                    = layer::xeCommandQueueExecuteCommandLists;

    dditable.pfnSynchronize                              = pDdiTable->pfnSynchronize;
    pDdiTable->pfnSynchronize                            = layer::xeCommandQueueSynchronize;

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
    auto& dditable = layer::context.xeDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeCommandListCreate;

    dditable.pfnCreateImmediate                          = pDdiTable->pfnCreateImmediate;
    pDdiTable->pfnCreateImmediate                        = layer::xeCommandListCreateImmediate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeCommandListDestroy;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = layer::xeCommandListClose;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::xeCommandListReset;

    dditable.pfnSetParameter                             = pDdiTable->pfnSetParameter;
    pDdiTable->pfnSetParameter                           = layer::xeCommandListSetParameter;

    dditable.pfnGetParameter                             = pDdiTable->pfnGetParameter;
    pDdiTable->pfnGetParameter                           = layer::xeCommandListGetParameter;

    dditable.pfnResetParameters                          = pDdiTable->pfnResetParameters;
    pDdiTable->pfnResetParameters                        = layer::xeCommandListResetParameters;

    dditable.pfnReserveSpace                             = pDdiTable->pfnReserveSpace;
    pDdiTable->pfnReserveSpace                           = layer::xeCommandListReserveSpace;

    dditable.pfnAppendBarrier                            = pDdiTable->pfnAppendBarrier;
    pDdiTable->pfnAppendBarrier                          = layer::xeCommandListAppendBarrier;

    dditable.pfnAppendMemoryRangesBarrier                = pDdiTable->pfnAppendMemoryRangesBarrier;
    pDdiTable->pfnAppendMemoryRangesBarrier              = layer::xeCommandListAppendMemoryRangesBarrier;

    dditable.pfnAppendMemoryCopy                         = pDdiTable->pfnAppendMemoryCopy;
    pDdiTable->pfnAppendMemoryCopy                       = layer::xeCommandListAppendMemoryCopy;

    dditable.pfnAppendMemorySet                          = pDdiTable->pfnAppendMemorySet;
    pDdiTable->pfnAppendMemorySet                        = layer::xeCommandListAppendMemorySet;

    dditable.pfnAppendMemoryCopyRegion                   = pDdiTable->pfnAppendMemoryCopyRegion;
    pDdiTable->pfnAppendMemoryCopyRegion                 = layer::xeCommandListAppendMemoryCopyRegion;

    dditable.pfnAppendImageCopy                          = pDdiTable->pfnAppendImageCopy;
    pDdiTable->pfnAppendImageCopy                        = layer::xeCommandListAppendImageCopy;

    dditable.pfnAppendImageCopyRegion                    = pDdiTable->pfnAppendImageCopyRegion;
    pDdiTable->pfnAppendImageCopyRegion                  = layer::xeCommandListAppendImageCopyRegion;

    dditable.pfnAppendImageCopyToMemory                  = pDdiTable->pfnAppendImageCopyToMemory;
    pDdiTable->pfnAppendImageCopyToMemory                = layer::xeCommandListAppendImageCopyToMemory;

    dditable.pfnAppendImageCopyFromMemory                = pDdiTable->pfnAppendImageCopyFromMemory;
    pDdiTable->pfnAppendImageCopyFromMemory              = layer::xeCommandListAppendImageCopyFromMemory;

    dditable.pfnAppendMemoryPrefetch                     = pDdiTable->pfnAppendMemoryPrefetch;
    pDdiTable->pfnAppendMemoryPrefetch                   = layer::xeCommandListAppendMemoryPrefetch;

    dditable.pfnAppendMemAdvise                          = pDdiTable->pfnAppendMemAdvise;
    pDdiTable->pfnAppendMemAdvise                        = layer::xeCommandListAppendMemAdvise;

    dditable.pfnAppendSignalEvent                        = pDdiTable->pfnAppendSignalEvent;
    pDdiTable->pfnAppendSignalEvent                      = layer::xeCommandListAppendSignalEvent;

    dditable.pfnAppendWaitOnEvents                       = pDdiTable->pfnAppendWaitOnEvents;
    pDdiTable->pfnAppendWaitOnEvents                     = layer::xeCommandListAppendWaitOnEvents;

    dditable.pfnAppendEventReset                         = pDdiTable->pfnAppendEventReset;
    pDdiTable->pfnAppendEventReset                       = layer::xeCommandListAppendEventReset;

    dditable.pfnAppendLaunchFunction                     = pDdiTable->pfnAppendLaunchFunction;
    pDdiTable->pfnAppendLaunchFunction                   = layer::xeCommandListAppendLaunchFunction;

    dditable.pfnAppendLaunchFunctionIndirect             = pDdiTable->pfnAppendLaunchFunctionIndirect;
    pDdiTable->pfnAppendLaunchFunctionIndirect           = layer::xeCommandListAppendLaunchFunctionIndirect;

    dditable.pfnAppendLaunchMultipleFunctionsIndirect    = pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect;
    pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect  = layer::xeCommandListAppendLaunchMultipleFunctionsIndirect;

    dditable.pfnAppendLaunchHostFunction                 = pDdiTable->pfnAppendLaunchHostFunction;
    pDdiTable->pfnAppendLaunchHostFunction               = layer::xeCommandListAppendLaunchHostFunction;

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
    auto& dditable = layer::context.xeDdiTable.Fence;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeFenceCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeFenceDestroy;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = layer::xeFenceHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = layer::xeFenceQueryStatus;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::xeFenceReset;

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
    auto& dditable = layer::context.xeDdiTable.EventPool;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeEventPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeEventPoolDestroy;

    dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
    pDdiTable->pfnGetIpcHandle                           = layer::xeEventPoolGetIpcHandle;

    dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
    pDdiTable->pfnOpenIpcHandle                          = layer::xeEventPoolOpenIpcHandle;

    dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
    pDdiTable->pfnCloseIpcHandle                         = layer::xeEventPoolCloseIpcHandle;

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
    auto& dditable = layer::context.xeDdiTable.Event;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeEventCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeEventDestroy;

    dditable.pfnHostSignal                               = pDdiTable->pfnHostSignal;
    pDdiTable->pfnHostSignal                             = layer::xeEventHostSignal;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = layer::xeEventHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = layer::xeEventQueryStatus;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::xeEventReset;

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
    auto& dditable = layer::context.xeDdiTable.Image;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::xeImageGetProperties;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeImageCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeImageDestroy;

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
    auto& dditable = layer::context.xeDdiTable.Module;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeModuleCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeModuleDestroy;

    dditable.pfnGetNativeBinary                          = pDdiTable->pfnGetNativeBinary;
    pDdiTable->pfnGetNativeBinary                        = layer::xeModuleGetNativeBinary;

    dditable.pfnGetGlobalPointer                         = pDdiTable->pfnGetGlobalPointer;
    pDdiTable->pfnGetGlobalPointer                       = layer::xeModuleGetGlobalPointer;

    dditable.pfnGetFunctionPointer                       = pDdiTable->pfnGetFunctionPointer;
    pDdiTable->pfnGetFunctionPointer                     = layer::xeModuleGetFunctionPointer;

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
    auto& dditable = layer::context.xeDdiTable.ModuleBuildLog;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeModuleBuildLogDestroy;

    dditable.pfnGetString                                = pDdiTable->pfnGetString;
    pDdiTable->pfnGetString                              = layer::xeModuleBuildLogGetString;

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
    auto& dditable = layer::context.xeDdiTable.Function;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeFunctionCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeFunctionDestroy;

    dditable.pfnSetGroupSize                             = pDdiTable->pfnSetGroupSize;
    pDdiTable->pfnSetGroupSize                           = layer::xeFunctionSetGroupSize;

    dditable.pfnSuggestGroupSize                         = pDdiTable->pfnSuggestGroupSize;
    pDdiTable->pfnSuggestGroupSize                       = layer::xeFunctionSuggestGroupSize;

    dditable.pfnSetArgumentValue                         = pDdiTable->pfnSetArgumentValue;
    pDdiTable->pfnSetArgumentValue                       = layer::xeFunctionSetArgumentValue;

    dditable.pfnSetAttribute                             = pDdiTable->pfnSetAttribute;
    pDdiTable->pfnSetAttribute                           = layer::xeFunctionSetAttribute;

    dditable.pfnGetAttribute                             = pDdiTable->pfnGetAttribute;
    pDdiTable->pfnGetAttribute                           = layer::xeFunctionGetAttribute;

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
    auto& dditable = layer::context.xeDdiTable.Sampler;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( layer::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::xeSamplerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::xeSamplerDestroy;

    return result;
}

#if defined(__cplusplus)
};
#endif
