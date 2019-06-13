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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_init_params_t params = {
                flags
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Global;
                    if( nullptr != table.pfnInitCb )
                        table.pfnInitCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_init_params_t params = {
                flags
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Global;
                    if( nullptr != table.pfnInitCb )
                        table.pfnInitCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_driver_version_params_t params = {
                hDeviceGroup,
version
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetDriverVersionCb )
                        table.pfnGetDriverVersionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *version = 0;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_driver_version_params_t params = {
                hDeviceGroup,
version
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetDriverVersionCb )
                        table.pfnGetDriverVersionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_params_t params = {
                pCount,
phDeviceGroups
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetCb )
                        table.pfnGetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pCount = 1;
        if( nullptr != phDeviceGroups ) *reinterpret_cast<void**>(phDeviceGroups) = context.get();

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_params_t params = {
                pCount,
phDeviceGroups
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetCb )
                        table.pfnGetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_get_params_t params = {
                hDeviceGroup,
pCount,
phDevices
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnGetCb )
                        table.pfnGetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pCount = 1;
        if( nullptr != phDevices ) *reinterpret_cast<void**>(phDevices) = context.get() ;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_get_params_t params = {
                hDeviceGroup,
pCount,
phDevices
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnGetCb )
                        table.pfnGetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_get_sub_devices_params_t params = {
                hDevice,
pCount,
phSubdevices
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnGetSubDevicesCb )
                        table.pfnGetSubDevicesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        for( size_t i = 0; ( nullptr != phSubdevices ) && ( i < *pCount ); ++i )
            phSubdevices[ i ] = reinterpret_cast<xe_device_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_get_sub_devices_params_t params = {
                hDevice,
pCount,
phSubdevices
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnGetSubDevicesCb )
                        table.pfnGetSubDevicesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_api_version_params_t params = {
                hDeviceGroup,
version
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetApiVersionCb )
                        table.pfnGetApiVersionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *version = context.version;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_api_version_params_t params = {
                hDeviceGroup,
version
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetApiVersionCb )
                        table.pfnGetApiVersionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_device_properties_params_t params = {
                hDeviceGroup,
pDeviceProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetDevicePropertiesCb )
                        table.pfnGetDevicePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pDeviceProperties = context.deviceProperties;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_device_properties_params_t params = {
                hDeviceGroup,
pDeviceProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetDevicePropertiesCb )
                        table.pfnGetDevicePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_compute_properties_params_t params = {
                hDeviceGroup,
pComputeProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetComputePropertiesCb )
                        table.pfnGetComputePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pComputeProperties = context.computeProperties;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_compute_properties_params_t params = {
                hDeviceGroup,
pComputeProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetComputePropertiesCb )
                        table.pfnGetComputePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_memory_properties_params_t params = {
                hDeviceGroup,
pCount,
pMemProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemoryPropertiesCb )
                        table.pfnGetMemoryPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pCount = 1;
        if( nullptr != pMemProperties ) *pMemProperties = context.memoryProperties;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_memory_properties_params_t params = {
                hDeviceGroup,
pCount,
pMemProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemoryPropertiesCb )
                        table.pfnGetMemoryPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_memory_access_properties_params_t params = {
                hDeviceGroup,
pMemAccessProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                        table.pfnGetMemoryAccessPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pMemAccessProperties = context.memoryAccessProperties;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_memory_access_properties_params_t params = {
                hDeviceGroup,
pMemAccessProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                        table.pfnGetMemoryAccessPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_cache_properties_params_t params = {
                hDeviceGroup,
pCacheProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetCachePropertiesCb )
                        table.pfnGetCachePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pCacheProperties = context.cacheProperties;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_cache_properties_params_t params = {
                hDeviceGroup,
pCacheProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetCachePropertiesCb )
                        table.pfnGetCachePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_image_properties_params_t params = {
                hDeviceGroup,
pImageProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetImagePropertiesCb )
                        table.pfnGetImagePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pImageProperties = context.imageProperties;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_image_properties_params_t params = {
                hDeviceGroup,
pImageProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetImagePropertiesCb )
                        table.pfnGetImagePropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_get_p2_p_properties_params_t params = {
                hDevice,
hPeerDevice,
pP2PProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnGetP2PPropertiesCb )
                        table.pfnGetP2PPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pP2PProperties = context.p2pProperties;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_get_p2_p_properties_params_t params = {
                hDevice,
hPeerDevice,
pP2PProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnGetP2PPropertiesCb )
                        table.pfnGetP2PPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_can_access_peer_params_t params = {
                hDevice,
hPeerDevice,
value
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnCanAccessPeerCb )
                        table.pfnCanAccessPeerCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *value = 0;

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_can_access_peer_params_t params = {
                hDevice,
hPeerDevice,
value
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnCanAccessPeerCb )
                        table.pfnCanAccessPeerCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_set_intermediate_cache_config_params_t params = {
                hDevice,
CacheConfig
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnSetIntermediateCacheConfigCb )
                        table.pfnSetIntermediateCacheConfigCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_set_intermediate_cache_config_params_t params = {
                hDevice,
CacheConfig
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnSetIntermediateCacheConfigCb )
                        table.pfnSetIntermediateCacheConfigCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_set_last_level_cache_config_params_t params = {
                hDevice,
CacheConfig
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnSetLastLevelCacheConfigCb )
                        table.pfnSetLastLevelCacheConfigCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_set_last_level_cache_config_params_t params = {
                hDevice,
CacheConfig
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnSetLastLevelCacheConfigCb )
                        table.pfnSetLastLevelCacheConfigCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_create_params_t params = {
                hDevice,
desc,
phCommandQueue
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_create_params_t params = {
                hDevice,
desc,
phCommandQueue
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_destroy_params_t params = {
                hCommandQueue
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_destroy_params_t params = {
                hCommandQueue
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_execute_command_lists_params_t params = {
                hCommandQueue,
numCommandLists,
phCommandLists,
hFence
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                    if( nullptr != table.pfnExecuteCommandListsCb )
                        table.pfnExecuteCommandListsCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_execute_command_lists_params_t params = {
                hCommandQueue,
numCommandLists,
phCommandLists,
hFence
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                    if( nullptr != table.pfnExecuteCommandListsCb )
                        table.pfnExecuteCommandListsCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_synchronize_params_t params = {
                hCommandQueue,
timeout
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandQueue;
                    if( nullptr != table.pfnSynchronizeCb )
                        table.pfnSynchronizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_queue_synchronize_params_t params = {
                hCommandQueue,
timeout
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandQueue;
                    if( nullptr != table.pfnSynchronizeCb )
                        table.pfnSynchronizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_create_params_t params = {
                hDevice,
desc,
phCommandList
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phCommandList = reinterpret_cast<xe_command_list_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_create_params_t params = {
                hDevice,
desc,
phCommandList
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_create_immediate_params_t params = {
                hDevice,
altdesc,
phCommandList
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnCreateImmediateCb )
                        table.pfnCreateImmediateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phCommandList = reinterpret_cast<xe_command_list_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_create_immediate_params_t params = {
                hDevice,
altdesc,
phCommandList
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnCreateImmediateCb )
                        table.pfnCreateImmediateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_destroy_params_t params = {
                hCommandList
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_destroy_params_t params = {
                hCommandList
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_close_params_t params = {
                hCommandList
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnCloseCb )
                        table.pfnCloseCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_close_params_t params = {
                hCommandList
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnCloseCb )
                        table.pfnCloseCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_reset_params_t params = {
                hCommandList
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnResetCb )
                        table.pfnResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_reset_params_t params = {
                hCommandList
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnResetCb )
                        table.pfnResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_set_parameter_params_t params = {
                hCommandList,
parameter,
value
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnSetParameterCb )
                        table.pfnSetParameterCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_set_parameter_params_t params = {
                hCommandList,
parameter,
value
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnSetParameterCb )
                        table.pfnSetParameterCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_get_parameter_params_t params = {
                hCommandList,
parameter,
value
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnGetParameterCb )
                        table.pfnGetParameterCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_get_parameter_params_t params = {
                hCommandList,
parameter,
value
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnGetParameterCb )
                        table.pfnGetParameterCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_reset_parameters_params_t params = {
                hCommandList
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnResetParametersCb )
                        table.pfnResetParametersCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_reset_parameters_params_t params = {
                hCommandList
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnResetParametersCb )
                        table.pfnResetParametersCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_reserve_space_params_t params = {
                hCommandList,
size,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnReserveSpaceCb )
                        table.pfnReserveSpaceCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_reserve_space_params_t params = {
                hCommandList,
size,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnReserveSpaceCb )
                        table.pfnReserveSpaceCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_barrier_params_t params = {
                hCommandList,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendBarrierCb )
                        table.pfnAppendBarrierCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_barrier_params_t params = {
                hCommandList,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendBarrierCb )
                        table.pfnAppendBarrierCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_ranges_barrier_params_t params = {
                hCommandList,
numRanges,
pRangeSizes,
pRanges,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                        table.pfnAppendMemoryRangesBarrierCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_ranges_barrier_params_t params = {
                hCommandList,
numRanges,
pRangeSizes,
pRanges,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                        table.pfnAppendMemoryRangesBarrierCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_system_barrier_params_t params = {
                hDevice
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnSystemBarrierCb )
                        table.pfnSystemBarrierCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_system_barrier_params_t params = {
                hDevice
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnSystemBarrierCb )
                        table.pfnSystemBarrierCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_register_cl_memory_params_t params = {
                hDevice,
context,
mem,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnRegisterCLMemoryCb )
                        table.pfnRegisterCLMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_register_cl_memory_params_t params = {
                hDevice,
context,
mem,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnRegisterCLMemoryCb )
                        table.pfnRegisterCLMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_register_cl_program_params_t params = {
                hDevice,
context,
program,
phModule
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnRegisterCLProgramCb )
                        table.pfnRegisterCLProgramCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phModule = reinterpret_cast<xe_module_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_register_cl_program_params_t params = {
                hDevice,
context,
program,
phModule
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnRegisterCLProgramCb )
                        table.pfnRegisterCLProgramCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_register_cl_command_queue_params_t params = {
                hDevice,
context,
command_queue,
phCommandQueue
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnRegisterCLCommandQueueCb )
                        table.pfnRegisterCLCommandQueueCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_register_cl_command_queue_params_t params = {
                hDevice,
context,
command_queue,
phCommandQueue
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnRegisterCLCommandQueueCb )
                        table.pfnRegisterCLCommandQueueCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_copy_params_t params = {
                hCommandList,
dstptr,
srcptr,
size,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryCopyCb )
                        table.pfnAppendMemoryCopyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_copy_params_t params = {
                hCommandList,
dstptr,
srcptr,
size,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryCopyCb )
                        table.pfnAppendMemoryCopyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_set_params_t params = {
                hCommandList,
ptr,
value,
size,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemorySetCb )
                        table.pfnAppendMemorySetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_set_params_t params = {
                hCommandList,
ptr,
value,
size,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemorySetCb )
                        table.pfnAppendMemorySetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_copy_region_params_t params = {
                hCommandList,
dstptr,
dstRegion,
dstPitch,
srcptr,
srcRegion,
srcPitch,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                        table.pfnAppendMemoryCopyRegionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_copy_region_params_t params = {
                hCommandList,
dstptr,
dstRegion,
dstPitch,
srcptr,
srcRegion,
srcPitch,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                        table.pfnAppendMemoryCopyRegionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_params_t params = {
                hCommandList,
hDstImage,
hSrcImage,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyCb )
                        table.pfnAppendImageCopyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_params_t params = {
                hCommandList,
hDstImage,
hSrcImage,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyCb )
                        table.pfnAppendImageCopyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_region_params_t params = {
                hCommandList,
hDstImage,
hSrcImage,
pDstRegion,
pSrcRegion,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyRegionCb )
                        table.pfnAppendImageCopyRegionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_region_params_t params = {
                hCommandList,
hDstImage,
hSrcImage,
pDstRegion,
pSrcRegion,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyRegionCb )
                        table.pfnAppendImageCopyRegionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_to_memory_params_t params = {
                hCommandList,
dstptr,
hSrcImage,
pSrcRegion,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                        table.pfnAppendImageCopyToMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_to_memory_params_t params = {
                hCommandList,
dstptr,
hSrcImage,
pSrcRegion,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                        table.pfnAppendImageCopyToMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_from_memory_params_t params = {
                hCommandList,
hDstImage,
srcptr,
pDstRegion,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                        table.pfnAppendImageCopyFromMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_image_copy_from_memory_params_t params = {
                hCommandList,
hDstImage,
srcptr,
pDstRegion,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                        table.pfnAppendImageCopyFromMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_prefetch_params_t params = {
                hCommandList,
ptr,
size
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryPrefetchCb )
                        table.pfnAppendMemoryPrefetchCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_memory_prefetch_params_t params = {
                hCommandList,
ptr,
size
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemoryPrefetchCb )
                        table.pfnAppendMemoryPrefetchCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_mem_advise_params_t params = {
                hCommandList,
hDevice,
ptr,
size,
advice
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemAdviseCb )
                        table.pfnAppendMemAdviseCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_mem_advise_params_t params = {
                hCommandList,
hDevice,
ptr,
size,
advice
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendMemAdviseCb )
                        table.pfnAppendMemAdviseCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_create_params_t params = {
                hDeviceGroup,
desc,
numDevices,
phDevices,
phEventPool
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_create_params_t params = {
                hDeviceGroup,
desc,
numDevices,
phDevices,
phEventPool
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_destroy_params_t params = {
                hEventPool
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_destroy_params_t params = {
                hEventPool
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_create_params_t params = {
                hEventPool,
desc,
phEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phEvent = reinterpret_cast<xe_event_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_create_params_t params = {
                hEventPool,
desc,
phEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_destroy_params_t params = {
                hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_event_destroy_params_t params = {
                hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_get_ipc_handle_params_t params = {
                hEventPool,
phIpc
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                    if( nullptr != table.pfnGetIpcHandleCb )
                        table.pfnGetIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_get_ipc_handle_params_t params = {
                hEventPool,
phIpc
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                    if( nullptr != table.pfnGetIpcHandleCb )
                        table.pfnGetIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_open_ipc_handle_params_t params = {
                hDevice,
hIpc,
phEventPool
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                    if( nullptr != table.pfnOpenIpcHandleCb )
                        table.pfnOpenIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_open_ipc_handle_params_t params = {
                hDevice,
hIpc,
phEventPool
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                    if( nullptr != table.pfnOpenIpcHandleCb )
                        table.pfnOpenIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_close_ipc_handle_params_t params = {
                hEventPool
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.EventPool;
                    if( nullptr != table.pfnCloseIpcHandleCb )
                        table.pfnCloseIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_event_pool_close_ipc_handle_params_t params = {
                hEventPool
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.EventPool;
                    if( nullptr != table.pfnCloseIpcHandleCb )
                        table.pfnCloseIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_signal_event_params_t params = {
                hCommandList,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendSignalEventCb )
                        table.pfnAppendSignalEventCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_signal_event_params_t params = {
                hCommandList,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendSignalEventCb )
                        table.pfnAppendSignalEventCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_wait_on_events_params_t params = {
                hCommandList,
numEvents,
phEvents
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendWaitOnEventsCb )
                        table.pfnAppendWaitOnEventsCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_wait_on_events_params_t params = {
                hCommandList,
numEvents,
phEvents
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendWaitOnEventsCb )
                        table.pfnAppendWaitOnEventsCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_host_signal_params_t params = {
                hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                    if( nullptr != table.pfnHostSignalCb )
                        table.pfnHostSignalCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_host_signal_params_t params = {
                hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                    if( nullptr != table.pfnHostSignalCb )
                        table.pfnHostSignalCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_host_synchronize_params_t params = {
                hEvent,
timeout
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                    if( nullptr != table.pfnHostSynchronizeCb )
                        table.pfnHostSynchronizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_host_synchronize_params_t params = {
                hEvent,
timeout
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                    if( nullptr != table.pfnHostSynchronizeCb )
                        table.pfnHostSynchronizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_query_status_params_t params = {
                hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                    if( nullptr != table.pfnQueryStatusCb )
                        table.pfnQueryStatusCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_query_status_params_t params = {
                hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                    if( nullptr != table.pfnQueryStatusCb )
                        table.pfnQueryStatusCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_event_reset_params_t params = {
                hCommandList,
hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendEventResetCb )
                        table.pfnAppendEventResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_event_reset_params_t params = {
                hCommandList,
hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendEventResetCb )
                        table.pfnAppendEventResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_event_reset_params_t params = {
                hEvent
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Event;
                    if( nullptr != table.pfnResetCb )
                        table.pfnResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_event_reset_params_t params = {
                hEvent
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Event;
                    if( nullptr != table.pfnResetCb )
                        table.pfnResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_create_params_t params = {
                hCommandQueue,
desc,
phFence
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phFence = reinterpret_cast<xe_fence_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_create_params_t params = {
                hCommandQueue,
desc,
phFence
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_destroy_params_t params = {
                hFence
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_destroy_params_t params = {
                hFence
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_host_synchronize_params_t params = {
                hFence,
timeout
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                    if( nullptr != table.pfnHostSynchronizeCb )
                        table.pfnHostSynchronizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_host_synchronize_params_t params = {
                hFence,
timeout
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                    if( nullptr != table.pfnHostSynchronizeCb )
                        table.pfnHostSynchronizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_query_status_params_t params = {
                hFence
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                    if( nullptr != table.pfnQueryStatusCb )
                        table.pfnQueryStatusCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_query_status_params_t params = {
                hFence
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                    if( nullptr != table.pfnQueryStatusCb )
                        table.pfnQueryStatusCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_reset_params_t params = {
                hFence
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Fence;
                    if( nullptr != table.pfnResetCb )
                        table.pfnResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_fence_reset_params_t params = {
                hFence
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Fence;
                    if( nullptr != table.pfnResetCb )
                        table.pfnResetCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_image_get_properties_params_t params = {
                hDevice,
desc,
pImageProperties
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Image;
                    if( nullptr != table.pfnGetPropertiesCb )
                        table.pfnGetPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_image_get_properties_params_t params = {
                hDevice,
desc,
pImageProperties
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Image;
                    if( nullptr != table.pfnGetPropertiesCb )
                        table.pfnGetPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_image_create_params_t params = {
                hDevice,
desc,
phImage
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Image;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phImage = reinterpret_cast<xe_image_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_image_create_params_t params = {
                hDevice,
desc,
phImage
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Image;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_image_destroy_params_t params = {
                hImage
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Image;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_image_destroy_params_t params = {
                hImage
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Image;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_alloc_shared_mem_params_t params = {
                hDeviceGroup,
hDevice,
device_flags,
ordinal,
host_flags,
size,
alignment,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnAllocSharedMemCb )
                        table.pfnAllocSharedMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *ptr = malloc( size );

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_alloc_shared_mem_params_t params = {
                hDeviceGroup,
hDevice,
device_flags,
ordinal,
host_flags,
size,
alignment,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnAllocSharedMemCb )
                        table.pfnAllocSharedMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_alloc_device_mem_params_t params = {
                hDeviceGroup,
hDevice,
flags,
ordinal,
size,
alignment,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnAllocDeviceMemCb )
                        table.pfnAllocDeviceMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *ptr = malloc( size );

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_alloc_device_mem_params_t params = {
                hDeviceGroup,
hDevice,
flags,
ordinal,
size,
alignment,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnAllocDeviceMemCb )
                        table.pfnAllocDeviceMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_alloc_host_mem_params_t params = {
                hDeviceGroup,
flags,
size,
alignment,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnAllocHostMemCb )
                        table.pfnAllocHostMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *ptr = malloc( size );

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_alloc_host_mem_params_t params = {
                hDeviceGroup,
flags,
size,
alignment,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnAllocHostMemCb )
                        table.pfnAllocHostMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_free_mem_params_t params = {
                hDeviceGroup,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnFreeMemCb )
                        table.pfnFreeMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        free( ptr );

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_free_mem_params_t params = {
                hDeviceGroup,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnFreeMemCb )
                        table.pfnFreeMemCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_mem_properties_params_t params = {
                hDeviceGroup,
ptr,
pMemProperties,
phDevice
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemPropertiesCb )
                        table.pfnGetMemPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *pMemProperties = {};

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_mem_properties_params_t params = {
                hDeviceGroup,
ptr,
pMemProperties,
phDevice
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemPropertiesCb )
                        table.pfnGetMemPropertiesCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_mem_address_range_params_t params = {
                hDeviceGroup,
ptr,
pBase,
pSize
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemAddressRangeCb )
                        table.pfnGetMemAddressRangeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_mem_address_range_params_t params = {
                hDeviceGroup,
ptr,
pBase,
pSize
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemAddressRangeCb )
                        table.pfnGetMemAddressRangeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_mem_ipc_handle_params_t params = {
                hDeviceGroup,
ptr,
pIpcHandle
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemIpcHandleCb )
                        table.pfnGetMemIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_get_mem_ipc_handle_params_t params = {
                hDeviceGroup,
ptr,
pIpcHandle
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnGetMemIpcHandleCb )
                        table.pfnGetMemIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_open_mem_ipc_handle_params_t params = {
                hDeviceGroup,
hDevice,
handle,
flags,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnOpenMemIpcHandleCb )
                        table.pfnOpenMemIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_open_mem_ipc_handle_params_t params = {
                hDeviceGroup,
hDevice,
handle,
flags,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnOpenMemIpcHandleCb )
                        table.pfnOpenMemIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_close_mem_ipc_handle_params_t params = {
                hDeviceGroup,
ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.DeviceGroup;
                    if( nullptr != table.pfnCloseMemIpcHandleCb )
                        table.pfnCloseMemIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_group_close_mem_ipc_handle_params_t params = {
                hDeviceGroup,
ptr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.DeviceGroup;
                    if( nullptr != table.pfnCloseMemIpcHandleCb )
                        table.pfnCloseMemIpcHandleCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_module_create_params_t params = {
                hDevice,
desc,
phModule,
phBuildLog
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phModule = reinterpret_cast<xe_module_handle_t>( context.get() );

        if( nullptr != phBuildLog ) *phBuildLog = reinterpret_cast<xe_module_build_log_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_module_create_params_t params = {
                hDevice,
desc,
phModule,
phBuildLog
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_module_destroy_params_t params = {
                hModule
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_module_destroy_params_t params = {
                hModule
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_module_build_log_destroy_params_t params = {
                hModuleBuildLog
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.ModuleBuildLog;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_module_build_log_destroy_params_t params = {
                hModuleBuildLog
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.ModuleBuildLog;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_module_build_log_get_string_params_t params = {
                hModuleBuildLog,
pSize,
pBuildLog
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.ModuleBuildLog;
                    if( nullptr != table.pfnGetStringCb )
                        table.pfnGetStringCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_module_build_log_get_string_params_t params = {
                hModuleBuildLog,
pSize,
pBuildLog
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.ModuleBuildLog;
                    if( nullptr != table.pfnGetStringCb )
                        table.pfnGetStringCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_module_get_native_binary_params_t params = {
                hModule,
pSize,
pModuleNativeBinary
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                    if( nullptr != table.pfnGetNativeBinaryCb )
                        table.pfnGetNativeBinaryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_module_get_native_binary_params_t params = {
                hModule,
pSize,
pModuleNativeBinary
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                    if( nullptr != table.pfnGetNativeBinaryCb )
                        table.pfnGetNativeBinaryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_module_get_global_pointer_params_t params = {
                hModule,
pGlobalName,
pPtr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                    if( nullptr != table.pfnGetGlobalPointerCb )
                        table.pfnGetGlobalPointerCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_module_get_global_pointer_params_t params = {
                hModule,
pGlobalName,
pPtr
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                    if( nullptr != table.pfnGetGlobalPointerCb )
                        table.pfnGetGlobalPointerCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_function_create_params_t params = {
                hModule,
desc,
phFunction
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phFunction = reinterpret_cast<xe_function_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_function_create_params_t params = {
                hModule,
desc,
phFunction
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_function_destroy_params_t params = {
                hFunction
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_function_destroy_params_t params = {
                hFunction
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_module_get_function_pointer_params_t params = {
                hModule,
pFunctionName,
pfnFunction
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Module;
                    if( nullptr != table.pfnGetFunctionPointerCb )
                        table.pfnGetFunctionPointerCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_module_get_function_pointer_params_t params = {
                hModule,
pFunctionName,
pfnFunction
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Module;
                    if( nullptr != table.pfnGetFunctionPointerCb )
                        table.pfnGetFunctionPointerCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_function_set_group_size_params_t params = {
                hFunction,
groupSizeX,
groupSizeY,
groupSizeZ
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                    if( nullptr != table.pfnSetGroupSizeCb )
                        table.pfnSetGroupSizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_function_set_group_size_params_t params = {
                hFunction,
groupSizeX,
groupSizeY,
groupSizeZ
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                    if( nullptr != table.pfnSetGroupSizeCb )
                        table.pfnSetGroupSizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_function_suggest_group_size_params_t params = {
                hFunction,
globalSizeX,
globalSizeY,
globalSizeZ,
groupSizeX,
groupSizeY,
groupSizeZ
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                    if( nullptr != table.pfnSuggestGroupSizeCb )
                        table.pfnSuggestGroupSizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_function_suggest_group_size_params_t params = {
                hFunction,
globalSizeX,
globalSizeY,
globalSizeZ,
groupSizeX,
groupSizeY,
groupSizeZ
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                    if( nullptr != table.pfnSuggestGroupSizeCb )
                        table.pfnSuggestGroupSizeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_function_set_argument_value_params_t params = {
                hFunction,
argIndex,
argSize,
pArgValue
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                    if( nullptr != table.pfnSetArgumentValueCb )
                        table.pfnSetArgumentValueCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_function_set_argument_value_params_t params = {
                hFunction,
argIndex,
argSize,
pArgValue
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                    if( nullptr != table.pfnSetArgumentValueCb )
                        table.pfnSetArgumentValueCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_function_set_attribute_params_t params = {
                hFunction,
attr,
value
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                    if( nullptr != table.pfnSetAttributeCb )
                        table.pfnSetAttributeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_function_set_attribute_params_t params = {
                hFunction,
attr,
value
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                    if( nullptr != table.pfnSetAttributeCb )
                        table.pfnSetAttributeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_function_get_attribute_params_t params = {
                hFunction,
attr,
pValue
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Function;
                    if( nullptr != table.pfnGetAttributeCb )
                        table.pfnGetAttributeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_function_get_attribute_params_t params = {
                hFunction,
attr,
pValue
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Function;
                    if( nullptr != table.pfnGetAttributeCb )
                        table.pfnGetAttributeCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_function_params_t params = {
                hCommandList,
hFunction,
pLaunchFuncArgs,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchFunctionCb )
                        table.pfnAppendLaunchFunctionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_function_params_t params = {
                hCommandList,
hFunction,
pLaunchFuncArgs,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchFunctionCb )
                        table.pfnAppendLaunchFunctionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_function_indirect_params_t params = {
                hCommandList,
hFunction,
pLaunchArgumentsBuffer,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchFunctionIndirectCb )
                        table.pfnAppendLaunchFunctionIndirectCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_function_indirect_params_t params = {
                hCommandList,
hFunction,
pLaunchArgumentsBuffer,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchFunctionIndirectCb )
                        table.pfnAppendLaunchFunctionIndirectCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_multiple_functions_indirect_params_t params = {
                hCommandList,
numFunctions,
phFunctions,
pNumLaunchArguments,
pLaunchArgumentsBuffer,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchMultipleFunctionsIndirectCb )
                        table.pfnAppendLaunchMultipleFunctionsIndirectCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_multiple_functions_indirect_params_t params = {
                hCommandList,
numFunctions,
phFunctions,
pNumLaunchArguments,
pLaunchArgumentsBuffer,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchMultipleFunctionsIndirectCb )
                        table.pfnAppendLaunchMultipleFunctionsIndirectCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_host_function_params_t params = {
                hCommandList,
pfnHostFunc,
pUserData,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchHostFunctionCb )
                        table.pfnAppendLaunchHostFunctionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_command_list_append_launch_host_function_params_t params = {
                hCommandList,
pfnHostFunc,
pUserData,
hSignalEvent,
numWaitEvents,
phWaitEvents
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.CommandList;
                    if( nullptr != table.pfnAppendLaunchHostFunctionCb )
                        table.pfnAppendLaunchHostFunctionCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_make_memory_resident_params_t params = {
                hDevice,
ptr,
size
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnMakeMemoryResidentCb )
                        table.pfnMakeMemoryResidentCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_make_memory_resident_params_t params = {
                hDevice,
ptr,
size
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnMakeMemoryResidentCb )
                        table.pfnMakeMemoryResidentCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_evict_memory_params_t params = {
                hDevice,
ptr,
size
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnEvictMemoryCb )
                        table.pfnEvictMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_evict_memory_params_t params = {
                hDevice,
ptr,
size
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnEvictMemoryCb )
                        table.pfnEvictMemoryCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_make_image_resident_params_t params = {
                hDevice,
hImage
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnMakeImageResidentCb )
                        table.pfnMakeImageResidentCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_make_image_resident_params_t params = {
                hDevice,
hImage
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnMakeImageResidentCb )
                        table.pfnMakeImageResidentCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_device_evict_image_params_t params = {
                hDevice,
hImage
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Device;
                    if( nullptr != table.pfnEvictImageCb )
                        table.pfnEvictImageCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xe_device_evict_image_params_t params = {
                hDevice,
hImage
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Device;
                    if( nullptr != table.pfnEvictImageCb )
                        table.pfnEvictImageCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_sampler_create_params_t params = {
                hDevice,
desc,
phSampler
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Sampler;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phSampler = reinterpret_cast<xe_sampler_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xe_sampler_create_params_t params = {
                hDevice,
desc,
phSampler
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Sampler;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xe_sampler_destroy_params_t params = {
                hSampler
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xePrologueCbs.Sampler;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xe_sampler_destroy_params_t params = {
                hSampler
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xeEpilogueCbs.Sampler;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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
