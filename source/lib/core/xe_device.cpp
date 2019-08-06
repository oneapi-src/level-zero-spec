/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_device.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Device
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/device.yml
 * @endcond
 *
 */
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
                                                    ///< if count is larger than the number of device groups available, then
                                                    ///< the driver will update the value with the correct number of device
                                                    ///< groups available.
    xe_device_group_handle_t* phDeviceGroups        ///< [in,out][optional][range(0, *pCount)] array of handle of device groups
    )
{
    auto pfnGet = xe_lib::context.ddiTable.DeviceGroup.pfnGet;
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    auto pfnGet = xe_lib::context.ddiTable.Device.pfnGet;
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    auto pfnGetSubDevices = xe_lib::context.ddiTable.Device.pfnGetSubDevices;
    if( nullptr == pfnGetSubDevices )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetSubDevices( hDevice, pCount, phSubdevices );
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
    auto pfnGetApiVersion = xe_lib::context.ddiTable.DeviceGroup.pfnGetApiVersion;
    if( nullptr == pfnGetApiVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetApiVersion( hDeviceGroup, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of all devices in the device group.
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
xeDeviceGroupGetDeviceProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
    )
{
    auto pfnGetDeviceProperties = xe_lib::context.ddiTable.DeviceGroup.pfnGetDeviceProperties;
    if( nullptr == pfnGetDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDeviceProperties( hDeviceGroup, pDeviceProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute attributes of all devices in the device group.
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
    xe_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
    )
{
    auto pfnGetComputeProperties = xe_lib::context.ddiTable.DeviceGroup.pfnGetComputeProperties;
    if( nullptr == pfnGetComputeProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetComputeProperties( hDeviceGroup, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves local memory attributes of all devices in the device group.
/// 
/// @details
///     - Properties are reported for each physical memory type supported by the
///       device.
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
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    auto pfnGetMemoryProperties = xe_lib::context.ddiTable.DeviceGroup.pfnGetMemoryProperties;
    if( nullptr == pfnGetMemoryProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemoryProperties( hDeviceGroup, pCount, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory access attributes of all devices in the device group.
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
///         + nullptr == pMemAccessProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetMemoryAccessProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
    )
{
    auto pfnGetMemoryAccessProperties = xe_lib::context.ddiTable.DeviceGroup.pfnGetMemoryAccessProperties;
    if( nullptr == pfnGetMemoryAccessProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemoryAccessProperties( hDeviceGroup, pMemAccessProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves cache attributes of the device
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
///         + nullptr == pCacheProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetCacheProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
    )
{
    auto pfnGetCacheProperties = xe_lib::context.ddiTable.DeviceGroup.pfnGetCacheProperties;
    if( nullptr == pfnGetCacheProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetCacheProperties( hDeviceGroup, pCacheProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves image attributes of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pImageProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetImageProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
    )
{
    auto pfnGetImageProperties = xe_lib::context.ddiTable.DeviceGroup.pfnGetImageProperties;
    if( nullptr == pfnGetImageProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetImageProperties( hDeviceGroup, pImageProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves IPC attributes of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDeviceGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == pIPCProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetIPCProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_ipc_properties_t* pIPCProperties      ///< [in,out] query result for IPC properties
    )
{
    auto pfnGetIPCProperties = xe_lib::context.ddiTable.DeviceGroup.pfnGetIPCProperties;
    if( nullptr == pfnGetIPCProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetIPCProperties( hDeviceGroup, pIPCProperties );
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
    xe_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
    )
{
    auto pfnGetP2PProperties = xe_lib::context.ddiTable.Device.pfnGetP2PProperties;
    if( nullptr == pfnGetP2PProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries if one device can directly access peer device allocations
/// 
/// @details
///     - Any device can access any other device within a node through a
///       scale-up fabric.
///     - The following are conditions for CanAccessPeer query.
///         + If both device and peer device are the same then return true.
///         + If both sub-device and peer sub-device are the same then return
///           true.
///         + If both are sub-devices and share the same parent device then
///           return true.
///         + If both device and remote device are connected by a scale-up
///           fabric then true, if pci-e then false.
///         + If both sub-device and remote parent device (and vice-versa) are
///           connected by a scale-up fabric then true, if pci-e then false.
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
    auto pfnCanAccessPeer = xe_lib::context.ddiTable.Device.pfnCanAccessPeer;
    if( nullptr == pfnCanAccessPeer )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    xe_cache_config_t CacheConfig                   ///< [in,out] CacheConfig
    )
{
    auto pfnSetIntermediateCacheConfig = xe_lib::context.ddiTable.Device.pfnSetIntermediateCacheConfig;
    if( nullptr == pfnSetIntermediateCacheConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnSetLastLevelCacheConfig = xe_lib::context.ddiTable.Device.pfnSetLastLevelCacheConfig;
    if( nullptr == pfnSetLastLevelCacheConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
                                                        ///< if count is larger than the number of device groups available, then
                                                        ///< the driver will update the value with the correct number of device
                                                        ///< groups available.
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
            ppDeviceGroups[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDeviceGroups ) && ( i < *pCount ); ++i )
                ppDeviceGroups[ i ] = xe_lib::context.deviceGroupFactory.getInstance( reinterpret_cast<device_group_handle_t>( hDeviceGroups[ i ] ) );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::DeviceGroup::Get" );
        }
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
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                        ///< if count is larger than the number of devices available, then the
                                                        ///< driver will update the value with the correct number of devices available.
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
            ppDevices[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
                ppDevices[ i ] = xe_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevices[ i ] ), pDeviceGroup );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Device::Get" );
        }
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
    /// @throws result_t
    void __xecall
    Device::GetSubDevices(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of sub-devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                        ///< if count is larger than the number of sub-devices available, then the
                                                        ///< driver will update the value with the correct number of sub-devices available.
        Device** ppSubdevices                           ///< [in,out][optional][range(0, *pCount)] array of pointer to sub-devices
        )
    {
        thread_local std::vector<xe_device_handle_t> hSubdevices;
        hSubdevices.resize( ( ppSubdevices ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xeDeviceGetSubDevices(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            pCount,
            hSubdevices.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetSubDevices" );

        for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
            ppSubdevices[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
                ppSubdevices[ i ] = xe_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hSubdevices[ i ] ), m_pDeviceGroup );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Device::GetSubDevices" );
        }
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
    /// @brief Retrieves attributes of all devices in the device group.
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
    /// @throws result_t
    void __xecall
    DeviceGroup::GetDeviceProperties(
        device_properties_t* pDeviceProperties          ///< [in,out] query result for device properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetDeviceProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_properties_t*>( pDeviceProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetDeviceProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves compute attributes of all devices in the device group.
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
    /// @throws result_t
    void __xecall
    DeviceGroup::GetComputeProperties(
        device_compute_properties_t* pComputeProperties ///< [in,out] query result for compute properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetComputeProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_compute_properties_t*>( pComputeProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetComputeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves local memory attributes of all devices in the device group.
    /// 
    /// @details
    ///     - Properties are reported for each physical memory type supported by the
    ///       device.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    ///     - cuDeviceTotalMem
    ///     - clGetDeviceInfo
    /// 
    /// @throws result_t
    void __xecall
    DeviceGroup::GetMemoryProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties supported.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of memory properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< memory properties.
                                                        ///< if count is larger than the number of memory properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< memory properties available.
        device_memory_properties_t* pMemProperties      ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetMemoryProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<xe_device_memory_properties_t*>( pMemProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetMemoryProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves memory access attributes of all devices in the device group.
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
    /// @throws result_t
    void __xecall
    DeviceGroup::GetMemoryAccessProperties(
        device_memory_access_properties_t* pMemAccessProperties ///< [in,out] query result for memory access properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetMemoryAccessProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_memory_access_properties_t*>( pMemAccessProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetMemoryAccessProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves cache attributes of the device
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
    /// @throws result_t
    void __xecall
    DeviceGroup::GetCacheProperties(
        device_cache_properties_t* pCacheProperties     ///< [in,out] query result for cache properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetCacheProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_cache_properties_t*>( pCacheProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetCacheProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves image attributes of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    /// 
    /// @throws result_t
    void __xecall
    DeviceGroup::GetImageProperties(
        device_image_properties_t* pImageProperties     ///< [in,out] query result for image properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetImageProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_image_properties_t*>( pImageProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetImageProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves IPC attributes of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    /// 
    /// @throws result_t
    void __xecall
    DeviceGroup::GetIPCProperties(
        device_ipc_properties_t* pIPCProperties         ///< [in,out] query result for IPC properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGroupGetIPCProperties(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_ipc_properties_t*>( pIPCProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetIPCProperties" );
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
    /// @throws result_t
    void __xecall
    Device::GetP2PProperties(
        Device* pPeerDevice,                            ///< [in] pointer to the peer device with the allocation
        p2p_properties_t* pP2PProperties                ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGetP2PProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pPeerDevice->getHandle() ),
            reinterpret_cast<xe_device_p2p_properties_t*>( pP2PProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetP2PProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries if one device can directly access peer device allocations
    /// 
    /// @details
    ///     - Any device can access any other device within a node through a
    ///       scale-up fabric.
    ///     - The following are conditions for CanAccessPeer query.
    ///         + If both device and peer device are the same then return true.
    ///         + If both sub-device and peer sub-device are the same then return
    ///           true.
    ///         + If both are sub-devices and share the same parent device then
    ///           return true.
    ///         + If both device and remote device are connected by a scale-up
    ///           fabric then true, if pci-e then false.
    ///         + If both sub-device and remote parent device (and vice-versa) are
    ///           connected by a scale-up fabric then true, if pci-e then false.
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
            reinterpret_cast<xe_device_handle_t>( pPeerDevice->getHandle() ),
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
        cache_config_t CacheConfig                      ///< [in,out] CacheConfig
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

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::api_version_t to std::string
    std::string to_string( const DeviceGroup::api_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::api_version_t::_1_0:
            str = "DeviceGroup::api_version_t::_1_0";
            break;

        default:
            str = "DeviceGroup::api_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_properties_version_t to std::string
    std::string to_string( const DeviceGroup::device_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_properties_version_t::CURRENT:
            str = "DeviceGroup::device_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::device_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_type_t to std::string
    std::string to_string( const DeviceGroup::device_type_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_type_t::GPU:
            str = "DeviceGroup::device_type_t::GPU";
            break;

        case DeviceGroup::device_type_t::FPGA:
            str = "DeviceGroup::device_type_t::FPGA";
            break;

        default:
            str = "DeviceGroup::device_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_compute_properties_version_t to std::string
    std::string to_string( const DeviceGroup::device_compute_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_compute_properties_version_t::CURRENT:
            str = "DeviceGroup::device_compute_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::device_compute_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_memory_properties_version_t to std::string
    std::string to_string( const DeviceGroup::device_memory_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_memory_properties_version_t::CURRENT:
            str = "DeviceGroup::device_memory_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::device_memory_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_memory_access_properties_version_t to std::string
    std::string to_string( const DeviceGroup::device_memory_access_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_memory_access_properties_version_t::CURRENT:
            str = "DeviceGroup::device_memory_access_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::device_memory_access_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::memory_access_capabilities_t to std::string
    std::string to_string( const DeviceGroup::memory_access_capabilities_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "MEMORY_ACCESS_NONE   ";
        
        if( static_cast<uint32_t>(DeviceGroup::memory_access_capabilities_t::MEMORY_ACCESS) & bits )
            str += "MEMORY_ACCESS | ";
        
        if( static_cast<uint32_t>(DeviceGroup::memory_access_capabilities_t::MEMORY_ATOMIC_ACCESS) & bits )
            str += "MEMORY_ATOMIC_ACCESS | ";
        
        if( static_cast<uint32_t>(DeviceGroup::memory_access_capabilities_t::MEMORY_CONCURRENT_ACCESS) & bits )
            str += "MEMORY_CONCURRENT_ACCESS | ";
        
        if( static_cast<uint32_t>(DeviceGroup::memory_access_capabilities_t::MEMORY_CONCURRENT_ATOMIC_ACCESS) & bits )
            str += "MEMORY_CONCURRENT_ATOMIC_ACCESS | ";

        return ( str.size() > 3 ) 
            ? "DeviceGroup::memory_access_capabilities_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "DeviceGroup::memory_access_capabilities_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_cache_properties_version_t to std::string
    std::string to_string( const DeviceGroup::device_cache_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_cache_properties_version_t::CURRENT:
            str = "DeviceGroup::device_cache_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::device_cache_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_image_properties_version_t to std::string
    std::string to_string( const DeviceGroup::device_image_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_image_properties_version_t::CURRENT:
            str = "DeviceGroup::device_image_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::device_image_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_ipc_properties_version_t to std::string
    std::string to_string( const DeviceGroup::device_ipc_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::device_ipc_properties_version_t::CURRENT:
            str = "DeviceGroup::device_ipc_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::device_ipc_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_mem_alloc_flag_t to std::string
    std::string to_string( const DeviceGroup::device_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(DeviceGroup::device_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(DeviceGroup::device_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";

        return ( str.size() > 3 ) 
            ? "DeviceGroup::device_mem_alloc_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "DeviceGroup::device_mem_alloc_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::host_mem_alloc_flag_t to std::string
    std::string to_string( const DeviceGroup::host_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(DeviceGroup::host_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(DeviceGroup::host_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";
        
        if( static_cast<uint32_t>(DeviceGroup::host_mem_alloc_flag_t::BIAS_WRITE_COMBINED) & bits )
            str += "BIAS_WRITE_COMBINED | ";

        return ( str.size() > 3 ) 
            ? "DeviceGroup::host_mem_alloc_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "DeviceGroup::host_mem_alloc_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::memory_allocation_properties_version_t to std::string
    std::string to_string( const DeviceGroup::memory_allocation_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::memory_allocation_properties_version_t::CURRENT:
            str = "DeviceGroup::memory_allocation_properties_version_t::CURRENT";
            break;

        default:
            str = "DeviceGroup::memory_allocation_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::memory_type_t to std::string
    std::string to_string( const DeviceGroup::memory_type_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::memory_type_t::UNKNOWN:
            str = "DeviceGroup::memory_type_t::UNKNOWN";
            break;

        case DeviceGroup::memory_type_t::HOST:
            str = "DeviceGroup::memory_type_t::HOST";
            break;

        case DeviceGroup::memory_type_t::DEVICE:
            str = "DeviceGroup::memory_type_t::DEVICE";
            break;

        case DeviceGroup::memory_type_t::SHARED:
            str = "DeviceGroup::memory_type_t::SHARED";
            break;

        default:
            str = "DeviceGroup::memory_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::ipc_memory_flag_t to std::string
    std::string to_string( const DeviceGroup::ipc_memory_flag_t val )
    {
        std::string str;

        switch( val )
        {
        case DeviceGroup::ipc_memory_flag_t::NONE:
            str = "DeviceGroup::ipc_memory_flag_t::NONE";
            break;

        default:
            str = "DeviceGroup::ipc_memory_flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_uuid_t to std::string
    std::string to_string( const DeviceGroup::device_uuid_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_uuid_t::id : ";
        {
            std::string tmp;
            for( auto& entry : val.id )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_properties_t to std::string
    std::string to_string( const DeviceGroup::device_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::vendorId : ";
        str += std::to_string(val.vendorId);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::deviceId : ";
        str += std::to_string(val.deviceId);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::isSubdevice : ";
        str += std::to_string(val.isSubdevice);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::coreClockRate : ";
        str += std::to_string(val.coreClockRate);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::unifiedMemorySupported : ";
        str += std::to_string(val.unifiedMemorySupported);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::onDemandPageFaultsSupported : ";
        str += std::to_string(val.onDemandPageFaultsSupported);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::maxCommandQueues : ";
        str += std::to_string(val.maxCommandQueues);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::numAsyncComputeEngines : ";
        str += std::to_string(val.numAsyncComputeEngines);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::numAsyncCopyEngines : ";
        str += std::to_string(val.numAsyncCopyEngines);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::maxCommandQueuePriority : ";
        str += std::to_string(val.maxCommandQueuePriority);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::numThreadsPerEU : ";
        str += std::to_string(val.numThreadsPerEU);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::physicalEUSimdWidth : ";
        str += std::to_string(val.physicalEUSimdWidth);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::numEUsPerSubslice : ";
        str += std::to_string(val.numEUsPerSubslice);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::numSubslicesPerSlice : ";
        str += std::to_string(val.numSubslicesPerSlice);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::numSlicesPerTile : ";
        str += std::to_string(val.numSlicesPerTile);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::numTiles : ";
        str += std::to_string(val.numTiles);
        str += "\n";
        
        str += "DeviceGroup::device_properties_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_compute_properties_t to std::string
    std::string to_string( const DeviceGroup::device_compute_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_compute_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxTotalGroupSize : ";
        str += std::to_string(val.maxTotalGroupSize);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxGroupSizeX : ";
        str += std::to_string(val.maxGroupSizeX);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxGroupSizeY : ";
        str += std::to_string(val.maxGroupSizeY);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxGroupSizeZ : ";
        str += std::to_string(val.maxGroupSizeZ);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxGroupCountX : ";
        str += std::to_string(val.maxGroupCountX);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxGroupCountY : ";
        str += std::to_string(val.maxGroupCountY);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxGroupCountZ : ";
        str += std::to_string(val.maxGroupCountZ);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::maxSharedLocalMemory : ";
        str += std::to_string(val.maxSharedLocalMemory);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::numSubGroupSizes : ";
        str += std::to_string(val.numSubGroupSizes);
        str += "\n";
        
        str += "DeviceGroup::device_compute_properties_t::subGroupSizes : ";
        {
            std::string tmp;
            for( auto& entry : val.subGroupSizes )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_memory_properties_t to std::string
    std::string to_string( const DeviceGroup::device_memory_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_memory_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::device_memory_properties_t::maxClockRate : ";
        str += std::to_string(val.maxClockRate);
        str += "\n";
        
        str += "DeviceGroup::device_memory_properties_t::maxBusWidth : ";
        str += std::to_string(val.maxBusWidth);
        str += "\n";
        
        str += "DeviceGroup::device_memory_properties_t::totalSize : ";
        str += std::to_string(val.totalSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_memory_access_properties_t to std::string
    std::string to_string( const DeviceGroup::device_memory_access_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_memory_access_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::device_memory_access_properties_t::hostAllocCapabilities : ";
        str += to_string(val.hostAllocCapabilities);
        str += "\n";
        
        str += "DeviceGroup::device_memory_access_properties_t::deviceAllocCapabilities : ";
        str += to_string(val.deviceAllocCapabilities);
        str += "\n";
        
        str += "DeviceGroup::device_memory_access_properties_t::sharedSingleDeviceAllocCapabilities : ";
        str += to_string(val.sharedSingleDeviceAllocCapabilities);
        str += "\n";
        
        str += "DeviceGroup::device_memory_access_properties_t::sharedCrossDeviceAllocCapabilities : ";
        str += to_string(val.sharedCrossDeviceAllocCapabilities);
        str += "\n";
        
        str += "DeviceGroup::device_memory_access_properties_t::sharedSystemAllocCapabilities : ";
        str += to_string(val.sharedSystemAllocCapabilities);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_cache_properties_t to std::string
    std::string to_string( const DeviceGroup::device_cache_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_cache_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::device_cache_properties_t::intermediateCacheControlSupported : ";
        str += std::to_string(val.intermediateCacheControlSupported);
        str += "\n";
        
        str += "DeviceGroup::device_cache_properties_t::intermediateCacheSize : ";
        str += std::to_string(val.intermediateCacheSize);
        str += "\n";
        
        str += "DeviceGroup::device_cache_properties_t::lastLevelCacheSizeControlSupported : ";
        str += std::to_string(val.lastLevelCacheSizeControlSupported);
        str += "\n";
        
        str += "DeviceGroup::device_cache_properties_t::lastLevelCacheSize : ";
        str += std::to_string(val.lastLevelCacheSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_image_properties_t to std::string
    std::string to_string( const DeviceGroup::device_image_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_image_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::device_image_properties_t::supported : ";
        str += std::to_string(val.supported);
        str += "\n";
        
        str += "DeviceGroup::device_image_properties_t::maxImageDims1D : ";
        str += std::to_string(val.maxImageDims1D);
        str += "\n";
        
        str += "DeviceGroup::device_image_properties_t::maxImageDims2D : ";
        str += std::to_string(val.maxImageDims2D);
        str += "\n";
        
        str += "DeviceGroup::device_image_properties_t::maxImageDims3D : ";
        str += std::to_string(val.maxImageDims3D);
        str += "\n";
        
        str += "DeviceGroup::device_image_properties_t::maxImageArraySlices : ";
        str += std::to_string(val.maxImageArraySlices);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::device_ipc_properties_t to std::string
    std::string to_string( const DeviceGroup::device_ipc_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::device_ipc_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::device_ipc_properties_t::memsSupported : ";
        str += std::to_string(val.memsSupported);
        str += "\n";
        
        str += "DeviceGroup::device_ipc_properties_t::eventsSupported : ";
        str += std::to_string(val.eventsSupported);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts DeviceGroup::memory_allocation_properties_t to std::string
    std::string to_string( const DeviceGroup::memory_allocation_properties_t val )
    {
        std::string str;
        
        str += "DeviceGroup::memory_allocation_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "DeviceGroup::memory_allocation_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "DeviceGroup::memory_allocation_properties_t::id : ";
        str += std::to_string(val.id);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_version_t to std::string
    std::string to_string( const Device::p2p_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::p2p_properties_version_t::CURRENT:
            str = "Device::p2p_properties_version_t::CURRENT";
            break;

        default:
            str = "Device::p2p_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_config_t to std::string
    std::string to_string( const Device::cache_config_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(Device::cache_config_t::DEFAULT) & bits )
            str += "DEFAULT | ";
        
        if( static_cast<uint32_t>(Device::cache_config_t::LARGE_SLM) & bits )
            str += "LARGE_SLM | ";
        
        if( static_cast<uint32_t>(Device::cache_config_t::LARGE_DATA) & bits )
            str += "LARGE_DATA | ";

        return ( str.size() > 3 ) 
            ? "Device::cache_config_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::cache_config_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_t to std::string
    std::string to_string( const Device::p2p_properties_t val )
    {
        std::string str;
        
        str += "Device::p2p_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::p2p_properties_t::accessSupported : ";
        str += std::to_string(val.accessSupported);
        str += "\n";
        
        str += "Device::p2p_properties_t::atomicsSupported : ";
        str += std::to_string(val.atomicsSupported);
        str += "\n";

        return str;
    }

} // namespace xe
