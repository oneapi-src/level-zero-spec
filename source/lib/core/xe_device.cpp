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
/// @brief Retrieves properties of the device.
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
///         + nullptr == hDevice
///         + nullptr == pDeviceProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    auto pfnGetProperties = xe_lib::context.ddiTable.Device.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hDevice, pDeviceProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute properties of the device.
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
///         + nullptr == hDevice
///         + nullptr == pComputeProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGetComputeProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    auto pfnGetComputeProperties = xe_lib::context.ddiTable.Device.pfnGetComputeProperties;
    if( nullptr == pfnGetComputeProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetComputeProperties( hDevice, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves local memory properties of the device.
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
///         + nullptr == hDevice
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    auto pfnGetMemoryProperties = xe_lib::context.ddiTable.Device.pfnGetMemoryProperties;
    if( nullptr == pfnGetMemoryProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory access properties of the device.
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
///         + nullptr == hDevice
///         + nullptr == pMemAccessProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGetMemoryAccessProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_memory_access_properties_t* pMemAccessProperties  ///< [out] query result for memory access properties
    )
{
    auto pfnGetMemoryAccessProperties = xe_lib::context.ddiTable.Device.pfnGetMemoryAccessProperties;
    if( nullptr == pfnGetMemoryAccessProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves cache propreties of the device
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
///         + nullptr == hDevice
///         + nullptr == pCacheProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGetCacheProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_cache_properties_t* pCacheProperties  ///< [out] query result for cache properties
    )
{
    auto pfnGetCacheProperties = xe_lib::context.ddiTable.Device.pfnGetCacheProperties;
    if( nullptr == pfnGetCacheProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetCacheProperties( hDevice, pCacheProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves image X_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT of
///        the device
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
///         + nullptr == hDevice
///         + nullptr == pImageProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGetImageProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_image_properties_t* pImageProperties  ///< [out] query result for image properties
    )
{
    auto pfnGetImageProperties = xe_lib::context.ddiTable.Device.pfnGetImageProperties;
    if( nullptr == pfnGetImageProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetImageProperties( hDevice, pImageProperties );
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
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
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
    Driver::Driver( 
        driver_handle_t handle                          ///< [in] handle of the driver instance
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Device::Device( 
        device_handle_t handle,                         ///< [in] handle of device object
        Driver* pDriver                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver )
    {
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
                ppSubdevices[ i ] = xe_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hSubdevices[ i ] ), m_pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Device::GetSubDevices" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves properties of the device.
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
    ///     - properties_t: query result for device properties
    /// 
    /// @throws result_t
    Device::properties_t __xecall
    Device::GetProperties(
        void
        )
    {
        xe_device_properties_t deviceProperties;

        auto result = static_cast<result_t>( ::xeDeviceGetProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            &deviceProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetProperties" );

        return *reinterpret_cast<properties_t*>( &deviceProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves compute properties of the device.
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
    ///     - compute_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    Device::compute_properties_t __xecall
    Device::GetComputeProperties(
        void
        )
    {
        xe_device_compute_properties_t computeProperties;

        auto result = static_cast<result_t>( ::xeDeviceGetComputeProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            &computeProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetComputeProperties" );

        return *reinterpret_cast<compute_properties_t*>( &computeProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves local memory properties of the device.
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
    Device::GetMemoryProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties supported.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of memory properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< memory properties.
                                                        ///< if count is larger than the number of memory properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< memory properties available.
        memory_properties_t* pMemProperties             ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceGetMemoryProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<xe_device_memory_properties_t*>( pMemProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetMemoryProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves memory access properties of the device.
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
    ///     - memory_access_properties_t: query result for memory access properties
    /// 
    /// @throws result_t
    Device::memory_access_properties_t __xecall
    Device::GetMemoryAccessProperties(
        void
        )
    {
        xe_device_memory_access_properties_t memAccessProperties;

        auto result = static_cast<result_t>( ::xeDeviceGetMemoryAccessProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            &memAccessProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetMemoryAccessProperties" );

        return *reinterpret_cast<memory_access_properties_t*>( &memAccessProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves cache propreties of the device
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
    ///     - cache_properties_t: query result for cache properties
    /// 
    /// @throws result_t
    Device::cache_properties_t __xecall
    Device::GetCacheProperties(
        void
        )
    {
        xe_device_cache_properties_t cacheProperties;

        auto result = static_cast<result_t>( ::xeDeviceGetCacheProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            &cacheProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetCacheProperties" );

        return *reinterpret_cast<cache_properties_t*>( &cacheProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves image X_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT of
    ///        the device
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
    ///     - image_properties_t: query result for image properties
    /// 
    /// @throws result_t
    Device::image_properties_t __xecall
    Device::GetImageProperties(
        void
        )
    {
        xe_device_image_properties_t imageProperties;

        auto result = static_cast<result_t>( ::xeDeviceGetImageProperties(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            &imageProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetImageProperties" );

        return *reinterpret_cast<image_properties_t*>( &imageProperties );
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
            reinterpret_cast<xe_device_handle_t>( pPeerDevice->getHandle() ),
            &p2PProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::GetP2PProperties" );

        return *reinterpret_cast<p2p_properties_t*>( &p2PProperties );
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

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::api_version_t to std::string
    std::string to_string( const Driver::api_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::api_version_t::_1_0:
            str = "Driver::api_version_t::_1_0";
            break;

        default:
            str = "Driver::api_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_version_t to std::string
    std::string to_string( const Driver::ipc_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::ipc_properties_version_t::CURRENT:
            str = "Driver::ipc_properties_version_t::CURRENT";
            break;

        default:
            str = "Driver::ipc_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_type_t to std::string
    std::string to_string( const Driver::device_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::device_type_t::GPU:
            str = "Driver::device_type_t::GPU";
            break;

        case Driver::device_type_t::FPGA:
            str = "Driver::device_type_t::FPGA";
            break;

        default:
            str = "Driver::device_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::device_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(Driver::device_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Driver::device_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";

        return ( str.size() > 3 ) 
            ? "Driver::device_mem_alloc_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Driver::device_mem_alloc_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::host_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(Driver::host_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Driver::host_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";
        
        if( static_cast<uint32_t>(Driver::host_mem_alloc_flag_t::BIAS_WRITE_COMBINED) & bits )
            str += "BIAS_WRITE_COMBINED | ";

        return ( str.size() > 3 ) 
            ? "Driver::host_mem_alloc_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Driver::host_mem_alloc_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_allocation_properties_version_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::memory_allocation_properties_version_t::CURRENT:
            str = "Driver::memory_allocation_properties_version_t::CURRENT";
            break;

        default:
            str = "Driver::memory_allocation_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_type_t to std::string
    std::string to_string( const Driver::memory_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::memory_type_t::UNKNOWN:
            str = "Driver::memory_type_t::UNKNOWN";
            break;

        case Driver::memory_type_t::HOST:
            str = "Driver::memory_type_t::HOST";
            break;

        case Driver::memory_type_t::DEVICE:
            str = "Driver::memory_type_t::DEVICE";
            break;

        case Driver::memory_type_t::SHARED:
            str = "Driver::memory_type_t::SHARED";
            break;

        default:
            str = "Driver::memory_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_memory_flag_t to std::string
    std::string to_string( const Driver::ipc_memory_flag_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::ipc_memory_flag_t::NONE:
            str = "Driver::ipc_memory_flag_t::NONE";
            break;

        default:
            str = "Driver::ipc_memory_flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_t to std::string
    std::string to_string( const Driver::ipc_properties_t val )
    {
        std::string str;
        
        str += "Driver::ipc_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::ipc_properties_t::memsSupported : ";
        str += std::to_string(val.memsSupported);
        str += "\n";
        
        str += "Driver::ipc_properties_t::eventsSupported : ";
        str += std::to_string(val.eventsSupported);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_uuid_t to std::string
    std::string to_string( const Driver::device_uuid_t val )
    {
        std::string str;
        
        str += "Driver::device_uuid_t::id : ";
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
    /// @brief Converts Driver::memory_allocation_properties_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_t val )
    {
        std::string str;
        
        str += "Driver::memory_allocation_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::memory_allocation_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Driver::memory_allocation_properties_t::id : ";
        str += std::to_string(val.id);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_version_t to std::string
    std::string to_string( const Device::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::properties_version_t::CURRENT:
            str = "Device::properties_version_t::CURRENT";
            break;

        default:
            str = "Device::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_version_t to std::string
    std::string to_string( const Device::compute_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::compute_properties_version_t::CURRENT:
            str = "Device::compute_properties_version_t::CURRENT";
            break;

        default:
            str = "Device::compute_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_version_t to std::string
    std::string to_string( const Device::memory_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::memory_properties_version_t::CURRENT:
            str = "Device::memory_properties_version_t::CURRENT";
            break;

        default:
            str = "Device::memory_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_version_t to std::string
    std::string to_string( const Device::memory_access_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::memory_access_properties_version_t::CURRENT:
            str = "Device::memory_access_properties_version_t::CURRENT";
            break;

        default:
            str = "Device::memory_access_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_capabilities_t to std::string
    std::string to_string( const Device::memory_access_capabilities_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "MEMORY_ACCESS_NONE   ";
        
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_ACCESS) & bits )
            str += "MEMORY_ACCESS | ";
        
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_ATOMIC_ACCESS) & bits )
            str += "MEMORY_ATOMIC_ACCESS | ";
        
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_CONCURRENT_ACCESS) & bits )
            str += "MEMORY_CONCURRENT_ACCESS | ";
        
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_CONCURRENT_ATOMIC_ACCESS) & bits )
            str += "MEMORY_CONCURRENT_ATOMIC_ACCESS | ";

        return ( str.size() > 3 ) 
            ? "Device::memory_access_capabilities_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::memory_access_capabilities_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_version_t to std::string
    std::string to_string( const Device::cache_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::cache_properties_version_t::CURRENT:
            str = "Device::cache_properties_version_t::CURRENT";
            break;

        default:
            str = "Device::cache_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_version_t to std::string
    std::string to_string( const Device::image_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::image_properties_version_t::CURRENT:
            str = "Device::image_properties_version_t::CURRENT";
            break;

        default:
            str = "Device::image_properties_version_t::?";
            break;
        };

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
    /// @brief Converts Device::properties_t to std::string
    std::string to_string( const Device::properties_t val )
    {
        std::string str;
        
        str += "Device::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Device::properties_t::vendorId : ";
        str += std::to_string(val.vendorId);
        str += "\n";
        
        str += "Device::properties_t::deviceId : ";
        str += std::to_string(val.deviceId);
        str += "\n";
        
        str += "Device::properties_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "Device::properties_t::isSubdevice : ";
        str += std::to_string(val.isSubdevice);
        str += "\n";
        
        str += "Device::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Device::properties_t::coreClockRate : ";
        str += std::to_string(val.coreClockRate);
        str += "\n";
        
        str += "Device::properties_t::unifiedMemorySupported : ";
        str += std::to_string(val.unifiedMemorySupported);
        str += "\n";
        
        str += "Device::properties_t::onDemandPageFaultsSupported : ";
        str += std::to_string(val.onDemandPageFaultsSupported);
        str += "\n";
        
        str += "Device::properties_t::maxCommandQueues : ";
        str += std::to_string(val.maxCommandQueues);
        str += "\n";
        
        str += "Device::properties_t::numAsyncComputeEngines : ";
        str += std::to_string(val.numAsyncComputeEngines);
        str += "\n";
        
        str += "Device::properties_t::numAsyncCopyEngines : ";
        str += std::to_string(val.numAsyncCopyEngines);
        str += "\n";
        
        str += "Device::properties_t::maxCommandQueuePriority : ";
        str += std::to_string(val.maxCommandQueuePriority);
        str += "\n";
        
        str += "Device::properties_t::numThreadsPerEU : ";
        str += std::to_string(val.numThreadsPerEU);
        str += "\n";
        
        str += "Device::properties_t::physicalEUSimdWidth : ";
        str += std::to_string(val.physicalEUSimdWidth);
        str += "\n";
        
        str += "Device::properties_t::numEUsPerSubslice : ";
        str += std::to_string(val.numEUsPerSubslice);
        str += "\n";
        
        str += "Device::properties_t::numSubslicesPerSlice : ";
        str += std::to_string(val.numSubslicesPerSlice);
        str += "\n";
        
        str += "Device::properties_t::numSlicesPerTile : ";
        str += std::to_string(val.numSlicesPerTile);
        str += "\n";
        
        str += "Device::properties_t::numTiles : ";
        str += std::to_string(val.numTiles);
        str += "\n";
        
        str += "Device::properties_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_t to std::string
    std::string to_string( const Device::compute_properties_t val )
    {
        std::string str;
        
        str += "Device::compute_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::compute_properties_t::maxTotalGroupSize : ";
        str += std::to_string(val.maxTotalGroupSize);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupSizeX : ";
        str += std::to_string(val.maxGroupSizeX);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupSizeY : ";
        str += std::to_string(val.maxGroupSizeY);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupSizeZ : ";
        str += std::to_string(val.maxGroupSizeZ);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupCountX : ";
        str += std::to_string(val.maxGroupCountX);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupCountY : ";
        str += std::to_string(val.maxGroupCountY);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupCountZ : ";
        str += std::to_string(val.maxGroupCountZ);
        str += "\n";
        
        str += "Device::compute_properties_t::maxSharedLocalMemory : ";
        str += std::to_string(val.maxSharedLocalMemory);
        str += "\n";
        
        str += "Device::compute_properties_t::numSubGroupSizes : ";
        str += std::to_string(val.numSubGroupSizes);
        str += "\n";
        
        str += "Device::compute_properties_t::subGroupSizes : ";
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
    /// @brief Converts Device::memory_properties_t to std::string
    std::string to_string( const Device::memory_properties_t val )
    {
        std::string str;
        
        str += "Device::memory_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::memory_properties_t::maxClockRate : ";
        str += std::to_string(val.maxClockRate);
        str += "\n";
        
        str += "Device::memory_properties_t::maxBusWidth : ";
        str += std::to_string(val.maxBusWidth);
        str += "\n";
        
        str += "Device::memory_properties_t::totalSize : ";
        str += std::to_string(val.totalSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_t to std::string
    std::string to_string( const Device::memory_access_properties_t val )
    {
        std::string str;
        
        str += "Device::memory_access_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::memory_access_properties_t::hostAllocCapabilities : ";
        str += to_string(val.hostAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::deviceAllocCapabilities : ";
        str += to_string(val.deviceAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::sharedSingleDeviceAllocCapabilities : ";
        str += to_string(val.sharedSingleDeviceAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::sharedCrossDeviceAllocCapabilities : ";
        str += to_string(val.sharedCrossDeviceAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::sharedSystemAllocCapabilities : ";
        str += to_string(val.sharedSystemAllocCapabilities);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_t to std::string
    std::string to_string( const Device::cache_properties_t val )
    {
        std::string str;
        
        str += "Device::cache_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::cache_properties_t::intermediateCacheControlSupported : ";
        str += std::to_string(val.intermediateCacheControlSupported);
        str += "\n";
        
        str += "Device::cache_properties_t::intermediateCacheSize : ";
        str += std::to_string(val.intermediateCacheSize);
        str += "\n";
        
        str += "Device::cache_properties_t::lastLevelCacheSizeControlSupported : ";
        str += std::to_string(val.lastLevelCacheSizeControlSupported);
        str += "\n";
        
        str += "Device::cache_properties_t::lastLevelCacheSize : ";
        str += std::to_string(val.lastLevelCacheSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_t to std::string
    std::string to_string( const Device::image_properties_t val )
    {
        std::string str;
        
        str += "Device::image_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::image_properties_t::supported : ";
        str += std::to_string(val.supported);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageDims1D : ";
        str += std::to_string(val.maxImageDims1D);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageDims2D : ";
        str += std::to_string(val.maxImageDims2D);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageDims3D : ";
        str += std::to_string(val.maxImageDims3D);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageArraySlices : ";
        str += std::to_string(val.maxImageArraySlices);
        str += "\n";

        return str;
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
