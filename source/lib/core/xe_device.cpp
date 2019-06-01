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
* @file xe_device.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/device.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves device groups
/// 
/// @details
///     - A device group represents a collection of physical, homogeneous
///       devices.
///     - The application may pass nullptr for pDeviceGroups when only querying
///       the number of device groups.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceIDs
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    auto pfnGet = xe_lib::lib.ddiTable.DeviceGroup.pfnGet;

#if _DEBUG
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGet( pCount, phDeviceGroups );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves devices within a device group
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGet**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pCount
///         + count is out of range reported by ::xeDeviceGroupGetDevices
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGet(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
    )
{
    auto pfnGet = xe_lib::lib.ddiTable.Device.pfnGet;

#if _DEBUG
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGet( hDeviceGroup, pCount, phDevices );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a sub-device from a device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clCreateSubDevices
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == phSubDevice
///         + ordinal is out of range reported by device properties.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    )
{
    auto pfnGetSubDevice = xe_lib::lib.ddiTable.Device.pfnGetSubDevice;

#if _DEBUG
    if( nullptr == pfnGetSubDevice )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetSubDevice( hDevice, ordinal, phSubDevice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the device group
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuCtxGetApiVersion**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetApiVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    auto pfnGetApiVersion = xe_lib::lib.ddiTable.DeviceGroup.pfnGetApiVersion;

#if _DEBUG
    if( nullptr == pfnGetApiVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetApiVersion( hDeviceGroup, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - cuDeviceGetName
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pDeviceProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    auto pfnGetProperties = xe_lib::lib.ddiTable.DeviceGroup.pfnGetProperties;

#if _DEBUG
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetProperties( hDeviceGroup, pDeviceProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute attributes of the device group
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pComputeProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetComputeProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    auto pfnGetComputeProperties = xe_lib::lib.ddiTable.DeviceGroup.pfnGetComputeProperties;

#if _DEBUG
    if( nullptr == pfnGetComputeProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetComputeProperties( hDeviceGroup, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory attributes of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
///     - cuDeviceTotalMem
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pMemProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemoryProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    auto pfnGetMemoryProperties = xe_lib::lib.ddiTable.DeviceGroup.pfnGetMemoryProperties;

#if _DEBUG
    if( nullptr == pfnGetMemoryProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetMemoryProperties( hDeviceGroup, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves Peer-to-Peer properties between one device and a peer
///        devices
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaDeviceGetP2PAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hPeerDevice
///         + nullptr == pP2PProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGetP2PProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    )
{
    auto pfnGetP2PProperties = xe_lib::lib.ddiTable.Device.pfnGetP2PProperties;

#if _DEBUG
    if( nullptr == pfnGetP2PProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries if one device can directly access peer device allocations
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaDeviceCanAccessPeer**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hPeerDevice
///         + nullptr == value
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceCanAccessPeer(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_bool_t* value                                ///< [out] returned access capability
    )
{
    auto pfnCanAccessPeer = xe_lib::lib.ddiTable.Device.pfnCanAccessPeer;

#if _DEBUG
    if( nullptr == pfnCanAccessPeer )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCanAccessPeer( hDevice, hPeerDevice, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Intermediate cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFuncSetCacheConfig **
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + devices do not support CacheConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    auto pfnSetIntermediateCacheConfig = xe_lib::lib.ddiTable.Device.pfnSetIntermediateCacheConfig;

#if _DEBUG
    if( nullptr == pfnSetIntermediateCacheConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetIntermediateCacheConfig( hDevice, CacheConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Last Level cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFuncSetCacheConfig **
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + devices do not support CacheConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    auto pfnSetLastLevelCacheConfig = xe_lib::lib.ddiTable.Device.pfnSetLastLevelCacheConfig;

#if _DEBUG
    if( nullptr == pfnSetLastLevelCacheConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    DeviceGroup::DeviceGroup( 
        device_group_handle_t handle                    ///< [in] handle of device group object
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Device::Device( 
        device_handle_t handle,                         ///< [in] handle of device object
        DeviceGroup* pDeviceGroup                       ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDeviceGroup( pDeviceGroup )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves device groups
    /// 
    /// @details
    ///     - A device group represents a collection of physical, homogeneous
    ///       devices.
    ///     - The application may pass nullptr for pDeviceGroups when only querying
    ///       the number of device groups.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetDeviceIDs
    /// 
    /// @throws result_t
    void __xecall
    DeviceGroup::Get(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of device groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< device groups.
        DeviceGroup** ppDeviceGroups                    ///< [in,out][optional][range(0, *pCount)] array of pointer to device
                                                        ///< groups
        )
    {
        thread_local std::vector<xe_device_group_handle_t> hDeviceGroups;
        hDeviceGroups.resize( ( ppDeviceGroups ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xeDeviceGroupGet(
            pCount,
            hDeviceGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::Get" );

        for( uint32_t i = 0; ( ppDeviceGroups ) && ( i < *pCount ); ++i )
            ppDeviceGroups[ i ] = new DeviceGroup( reinterpret_cast<device_group_handle_t>( hDeviceGroups[ i ] ) );

    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves devices within a device group
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGet**
    /// 
    /// @throws result_t
    void __xecall
    Device::Get(
        DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of device groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< device groups.
        Device** ppDevices                              ///< [in,out][optional][range(0, *pCount)] array of pointer to devices
        )
    {
        thread_local std::vector<xe_device_handle_t> hDevices;
        hDevices.resize( ( ppDevices ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xeDeviceGet(
            reinterpret_cast<xe_device_group_handle_t>( pDeviceGroup->getHandle() ),
            pCount,
            hDevices.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::Get" );

        for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
            ppDevices[ i ] = new Device( reinterpret_cast<device_handle_t>( hDevices[ i ] ), pDeviceGroup );

    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves a sub-device from a device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clCreateSubDevices
    /// 
    /// @returns
    ///     - Device*: pointer to handle of sub-device object.
    /// 
    /// @throws result_t
    Device* __xecall
    Device::GetSubDevice(
        uint32_t ordinal                                ///< [in] ordinal of sub-device to retrieve
        )
    {
        xe_device_handle_t hSubDevice;

        auto result = static_cast<result_t>( ::xeDeviceGetSubDevice(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            ordinal,
            &hSubDevice ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetSubDevice" );

        auto pSubDevice = new Device( reinterpret_cast<device_handle_t>( hSubDevice ), nullptr );

        return pSubDevice;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the API version supported by the device group
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuCtxGetApiVersion**
    /// 
    /// @returns
    ///     - api_version_t: api version
    /// 
    /// @throws result_t
    DeviceGroup::api_version_t __xecall
    DeviceGroup::GetApiVersion(
        void
        )
    {
        xe_api_version_t version;

        auto result = static_cast<result_t>( ::xeDeviceGroupGetApiVersion(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetApiVersion" );

        return *reinterpret_cast<api_version_t*>( &version );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    ///     - cuDeviceGetName
    ///     - clGetDeviceInfo
    /// 
    /// @returns
    ///     - device_properties_t: query result for device properties
    /// 
    /// @throws result_t
    DeviceGroup::device_properties_t __xecall
    DeviceGroup::GetProperties(
        void
        )
    {
        xe_device_properties_t deviceProperties;

        auto result = static_cast<result_t>( ::xeDeviceGroupGetProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            &deviceProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetProperties" );

        return *reinterpret_cast<device_properties_t*>( &deviceProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves compute attributes of the device group
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    ///     - clGetDeviceInfo
    /// 
    /// @returns
    ///     - device_compute_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    DeviceGroup::device_compute_properties_t __xecall
    DeviceGroup::GetComputeProperties(
        void
        )
    {
        xe_device_compute_properties_t computeProperties;

        auto result = static_cast<result_t>( ::xeDeviceGroupGetComputeProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            &computeProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetComputeProperties" );

        return *reinterpret_cast<device_compute_properties_t*>( &computeProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves memory attributes of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    ///     - cuDeviceTotalMem
    ///     - clGetDeviceInfo
    /// 
    /// @returns
    ///     - device_memory_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    DeviceGroup::device_memory_properties_t __xecall
    DeviceGroup::GetMemoryProperties(
        void
        )
    {
        xe_device_memory_properties_t memProperties;

        auto result = static_cast<result_t>( ::xeDeviceGroupGetMemoryProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            &memProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetMemoryProperties" );

        return *reinterpret_cast<device_memory_properties_t*>( &memProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves Peer-to-Peer properties between one device and a peer
    ///        devices
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaDeviceGetP2PAttribute**
    /// 
    /// @returns
    ///     - p2p_properties_t: Peer-to-Peer properties between source and peer device
    /// 
    /// @throws result_t
    Device::p2p_properties_t __xecall
    Device::GetP2PProperties(
        Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
        )
    {
        xe_device_p2p_properties_t p2PProperties;

        auto result = static_cast<result_t>( ::xeDeviceGetP2PProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            &p2PProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetP2PProperties" );

        return *reinterpret_cast<p2p_properties_t*>( &p2PProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries if one device can directly access peer device allocations
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaDeviceCanAccessPeer**
    /// 
    /// @returns
    ///     - bool_t: returned access capability
    /// 
    /// @throws result_t
    bool_t __xecall
    Device::CanAccessPeer(
        Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
        )
    {
        xe_bool_t value;

        auto result = static_cast<result_t>( ::xeDeviceCanAccessPeer(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            &value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::CanAccessPeer" );

        return *reinterpret_cast<bool_t*>( &value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred Intermediate cache configuration for a device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFuncSetCacheConfig **
    /// 
    /// @throws result_t
    void __xecall
    Device::SetIntermediateCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceSetIntermediateCacheConfig(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            static_cast<xe_cache_config_t>( CacheConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::SetIntermediateCacheConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred Last Level cache configuration for a device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFuncSetCacheConfig **
    /// 
    /// @throws result_t
    void __xecall
    Device::SetLastLevelCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceSetLastLevelCacheConfig(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            static_cast<xe_cache_config_t>( CacheConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::SetLastLevelCacheConfig" );
    }

} // namespace xe

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::api_version_t to std::string
std::string to_string( xe::DeviceGroup::api_version_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::api_version_t::_1_0:
        return std::string("xe::DeviceGroup::api_version_t::_1_0");
    };
    return std::string("xe::DeviceGroup::api_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::device_properties_version_t to std::string
std::string to_string( xe::DeviceGroup::device_properties_version_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::device_properties_version_t::CURRENT:
        return std::string("xe::DeviceGroup::device_properties_version_t::CURRENT");
    };
    return std::string("xe::DeviceGroup::device_properties_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::device_type_t to std::string
std::string to_string( xe::DeviceGroup::device_type_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::device_type_t::GPU:
        return std::string("xe::DeviceGroup::device_type_t::GPU");
    case xe::DeviceGroup::device_type_t::FPGA:
        return std::string("xe::DeviceGroup::device_type_t::FPGA");
    };
    return std::string("xe::DeviceGroup::device_type_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::device_compute_properties_version_t to std::string
std::string to_string( xe::DeviceGroup::device_compute_properties_version_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::device_compute_properties_version_t::CURRENT:
        return std::string("xe::DeviceGroup::device_compute_properties_version_t::CURRENT");
    };
    return std::string("xe::DeviceGroup::device_compute_properties_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::device_memory_properties_version_t to std::string
std::string to_string( xe::DeviceGroup::device_memory_properties_version_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::device_memory_properties_version_t::CURRENT:
        return std::string("xe::DeviceGroup::device_memory_properties_version_t::CURRENT");
    };
    return std::string("xe::DeviceGroup::device_memory_properties_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::memory_access_capabilities_t to std::string
std::string to_string( xe::DeviceGroup::memory_access_capabilities_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xe::DeviceGroup::memory_access_capabilities_t::MEMORY_ACCESS) & bits )
        str += "xe::DeviceGroup::memory_access_capabilities_t::MEMORY_ACCESS | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::memory_access_capabilities_t::MEMORY_ATOMIC_ACCESS) & bits )
        str += "xe::DeviceGroup::memory_access_capabilities_t::MEMORY_ATOMIC_ACCESS | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::memory_access_capabilities_t::MEMORY_CONCURRENT_ACCESS) & bits )
        str += "xe::DeviceGroup::memory_access_capabilities_t::MEMORY_CONCURRENT_ACCESS | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::memory_access_capabilities_t::MEMORY_CONCURRENT_ATOMIC_ACCESS) & bits )
        str += "xe::DeviceGroup::memory_access_capabilities_t::MEMORY_CONCURRENT_ATOMIC_ACCESS | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::device_mem_alloc_flag_t to std::string
std::string to_string( xe::DeviceGroup::device_mem_alloc_flag_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xe::DeviceGroup::device_mem_alloc_flag_t::DEFAULT) & bits )
        str += "xe::DeviceGroup::device_mem_alloc_flag_t::DEFAULT | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::device_mem_alloc_flag_t::BIAS_CACHED) & bits )
        str += "xe::DeviceGroup::device_mem_alloc_flag_t::BIAS_CACHED | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::device_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
        str += "xe::DeviceGroup::device_mem_alloc_flag_t::BIAS_UNCACHED | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::host_mem_alloc_flag_t to std::string
std::string to_string( xe::DeviceGroup::host_mem_alloc_flag_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xe::DeviceGroup::host_mem_alloc_flag_t::DEFAULT) & bits )
        str += "xe::DeviceGroup::host_mem_alloc_flag_t::DEFAULT | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::host_mem_alloc_flag_t::BIAS_CACHED) & bits )
        str += "xe::DeviceGroup::host_mem_alloc_flag_t::BIAS_CACHED | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::host_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
        str += "xe::DeviceGroup::host_mem_alloc_flag_t::BIAS_UNCACHED | ";
    if( static_cast<uint32_t>(xe::DeviceGroup::host_mem_alloc_flag_t::BIAS_WRITE_COMBINED) & bits )
        str += "xe::DeviceGroup::host_mem_alloc_flag_t::BIAS_WRITE_COMBINED | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::memory_allocation_properties_version_t to std::string
std::string to_string( xe::DeviceGroup::memory_allocation_properties_version_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::memory_allocation_properties_version_t::CURRENT:
        return std::string("xe::DeviceGroup::memory_allocation_properties_version_t::CURRENT");
    };
    return std::string("xe::DeviceGroup::memory_allocation_properties_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::memory_type_t to std::string
std::string to_string( xe::DeviceGroup::memory_type_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::memory_type_t::UNKNOWN:
        return std::string("xe::DeviceGroup::memory_type_t::UNKNOWN");
    case xe::DeviceGroup::memory_type_t::HOST:
        return std::string("xe::DeviceGroup::memory_type_t::HOST");
    case xe::DeviceGroup::memory_type_t::DEVICE:
        return std::string("xe::DeviceGroup::memory_type_t::DEVICE");
    case xe::DeviceGroup::memory_type_t::SHARED:
        return std::string("xe::DeviceGroup::memory_type_t::SHARED");
    };
    return std::string("xe::DeviceGroup::memory_type_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts DeviceGroup::ipc_memory_flag_t to std::string
std::string to_string( xe::DeviceGroup::ipc_memory_flag_t val )
{
    switch( val )
    {
    case xe::DeviceGroup::ipc_memory_flag_t::NONE:
        return std::string("xe::DeviceGroup::ipc_memory_flag_t::NONE");
    };
    return std::string("xe::DeviceGroup::ipc_memory_flag_t::?");
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Device::p2p_properties_version_t to std::string
std::string to_string( xe::Device::p2p_properties_version_t val )
{
    switch( val )
    {
    case xe::Device::p2p_properties_version_t::CURRENT:
        return std::string("xe::Device::p2p_properties_version_t::CURRENT");
    };
    return std::string("xe::Device::p2p_properties_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Device::cache_config_t to std::string
std::string to_string( xe::Device::cache_config_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xe::Device::cache_config_t::DEFAULT) & bits )
        str += "xe::Device::cache_config_t::DEFAULT | ";
    if( static_cast<uint32_t>(xe::Device::cache_config_t::LARGE_SLM) & bits )
        str += "xe::Device::cache_config_t::LARGE_SLM | ";
    if( static_cast<uint32_t>(xe::Device::cache_config_t::LARGE_DATA) & bits )
        str += "xe::Device::cache_config_t::LARGE_DATA | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}


#endif // _DEBUG
