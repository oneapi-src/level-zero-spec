/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_device.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Device
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/device.yml
 * @endcond
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves devices within a driver
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnGet = ze_lib::context.ddiTable.Device.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGet( hDriver, pCount, phDevices );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnGetSubDevices = ze_lib::context.ddiTable.Device.pfnGetSubDevices;
    if( nullptr == pfnGetSubDevices )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDeviceProperties`
ze_result_t __zecall
zeDeviceGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
    )
{
    auto pfnGetProperties = ze_lib::context.ddiTable.Device.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pComputeProperties`
ze_result_t __zecall
zeDeviceGetComputeProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
    )
{
    auto pfnGetComputeProperties = ze_lib::context.ddiTable.Device.pfnGetComputeProperties;
    if( nullptr == pfnGetComputeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetComputeProperties( hDevice, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves kernel properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pKernelProperties`
ze_result_t __zecall
zeDeviceGetKernelProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_kernel_properties_t* pKernelProperties///< [in,out] query result for kernel properties
    )
{
    auto pfnGetKernelProperties = ze_lib::context.ddiTable.Device.pfnGetKernelProperties;
    if( nullptr == pfnGetKernelProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetKernelProperties( hDevice, pKernelProperties );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
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
    auto pfnGetMemoryProperties = ze_lib::context.ddiTable.Device.pfnGetMemoryProperties;
    if( nullptr == pfnGetMemoryProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemAccessProperties`
ze_result_t __zecall
zeDeviceGetMemoryAccessProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
    )
{
    auto pfnGetMemoryAccessProperties = ze_lib::context.ddiTable.Device.pfnGetMemoryAccessProperties;
    if( nullptr == pfnGetMemoryAccessProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves cache properties of the device
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCacheProperties`
ze_result_t __zecall
zeDeviceGetCacheProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
    )
{
    auto pfnGetCacheProperties = ze_lib::context.ddiTable.Device.pfnGetCacheProperties;
    if( nullptr == pfnGetCacheProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImageProperties`
ze_result_t __zecall
zeDeviceGetImageProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
    )
{
    auto pfnGetImageProperties = ze_lib::context.ddiTable.Device.pfnGetImageProperties;
    if( nullptr == pfnGetImageProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pP2PProperties`
ze_result_t __zecall
zeDeviceGetP2PProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
    )
{
    auto pfnGetP2PProperties = ze_lib::context.ddiTable.Device.pfnGetP2PProperties;
    if( nullptr == pfnGetP2PProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///         + If both device and remote device are connected by a direct or
///           indirect scale-up fabric or over PCIe (same root complex or shared
///           PCIe switch) then true.
///         + If both sub-device and remote parent device (and vice-versa) are
///           connected by a direct or indirect scale-up fabric or over PCIe
///           (same root complex or shared PCIe switch) then true.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaDeviceCanAccessPeer**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == value`
ze_result_t __zecall
zeDeviceCanAccessPeer(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_bool_t* value                                ///< [out] returned access capability
    )
{
    auto pfnCanAccessPeer = ze_lib::context.ddiTable.Device.pfnCanAccessPeer;
    if( nullptr == pfnCanAccessPeer )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCanAccessPeer( hDevice, hPeerDevice, value );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + CacheConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
ze_result_t __zecall
zeDeviceSetLastLevelCacheConfig(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device 
    ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    auto pfnSetLastLevelCacheConfig = ze_lib::context.ddiTable.Device.pfnSetLastLevelCacheConfig;
    if( nullptr == pfnSetLastLevelCacheConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
}

} // extern "C"

namespace ze
{
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
    /// @brief Retrieves devices within a driver
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
    void __zecall
    Device::Get(
        Driver* pDriver,                                ///< [in] pointer to the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                        ///< if count is larger than the number of devices available, then the
                                                        ///< driver will update the value with the correct number of devices available.
        Device** ppDevices                              ///< [in,out][optional][range(0, *pCount)] array of pointer to devices
        )
    {
        thread_local std::vector<ze_device_handle_t> hDevices;
        hDevices.resize( ( ppDevices ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zeDeviceGet(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            pCount,
            hDevices.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::Get" );

        for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
            ppDevices[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
                ppDevices[ i ] = ze_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevices[ i ] ), pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Device::Get" );
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
    void __zecall
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
        thread_local std::vector<ze_device_handle_t> hSubdevices;
        hSubdevices.resize( ( ppSubdevices ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zeDeviceGetSubDevices(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            pCount,
            hSubdevices.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetSubDevices" );

        for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
            ppSubdevices[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
                ppSubdevices[ i ] = ze_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hSubdevices[ i ] ), m_pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Device::GetSubDevices" );
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
    /// @throws result_t
    void __zecall
    Device::GetProperties(
        properties_t* pDeviceProperties                 ///< [in,out] query result for device properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_properties_t*>( pDeviceProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetProperties" );
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
    /// @throws result_t
    void __zecall
    Device::GetComputeProperties(
        compute_properties_t* pComputeProperties        ///< [in,out] query result for compute properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetComputeProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_compute_properties_t*>( pComputeProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetComputeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves kernel properties of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::GetKernelProperties(
        kernel_properties_t* pKernelProperties          ///< [in,out] query result for kernel properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetKernelProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_kernel_properties_t*>( pKernelProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetKernelProperties" );
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
    void __zecall
    Device::GetMemoryProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
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
        auto result = static_cast<result_t>( ::zeDeviceGetMemoryProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<ze_device_memory_properties_t*>( pMemProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetMemoryProperties" );
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
    /// @throws result_t
    void __zecall
    Device::GetMemoryAccessProperties(
        memory_access_properties_t* pMemAccessProperties///< [in,out] query result for memory access properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetMemoryAccessProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_memory_access_properties_t*>( pMemAccessProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetMemoryAccessProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves cache properties of the device
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
    void __zecall
    Device::GetCacheProperties(
        cache_properties_t* pCacheProperties            ///< [in,out] query result for cache properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetCacheProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_cache_properties_t*>( pCacheProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetCacheProperties" );
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
    /// @throws result_t
    void __zecall
    Device::GetImageProperties(
        image_properties_t* pImageProperties            ///< [in,out] query result for image properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetImageProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_image_properties_t*>( pImageProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetImageProperties" );
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
    void __zecall
    Device::GetP2PProperties(
        Device* pPeerDevice,                            ///< [in] pointer to the peer device with the allocation
        p2p_properties_t* pP2PProperties                ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetP2PProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pPeerDevice->getHandle() ),
            reinterpret_cast<ze_device_p2p_properties_t*>( pP2PProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::GetP2PProperties" );
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
    ///         + If both device and remote device are connected by a direct or
    ///           indirect scale-up fabric or over PCIe (same root complex or shared
    ///           PCIe switch) then true.
    ///         + If both sub-device and remote parent device (and vice-versa) are
    ///           connected by a direct or indirect scale-up fabric or over PCIe
    ///           (same root complex or shared PCIe switch) then true.
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
    bool_t __zecall
    Device::CanAccessPeer(
        Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
        )
    {
        ze_bool_t value;

        auto result = static_cast<result_t>( ::zeDeviceCanAccessPeer(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pPeerDevice->getHandle() ),
            &value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::CanAccessPeer" );

        return *reinterpret_cast<bool_t*>( &value );
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
    void __zecall
    Device::SetLastLevelCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceSetLastLevelCacheConfig(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            static_cast<ze_cache_config_t>( CacheConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::SetLastLevelCacheConfig" );
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts device_uuid_t to std::string
    std::string to_string( const device_uuid_t val )
    {
        std::string str;
        
        str += "device_uuid_t::id : ";
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
    /// @brief Converts Device::kernel_properties_version_t to std::string
    std::string to_string( const Device::kernel_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::kernel_properties_version_t::CURRENT:
            str = "Device::kernel_properties_version_t::CURRENT";
            break;

        default:
            str = "Device::kernel_properties_version_t::?";
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
        
        str += "Device::properties_t::eccMemorySupported : ";
        str += std::to_string(val.eccMemorySupported);
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
        
        str += "Device::properties_t::timerResolution : ";
        str += std::to_string(val.timerResolution);
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
    /// @brief Converts Device::kernel_properties_t to std::string
    std::string to_string( const Device::kernel_properties_t val )
    {
        std::string str;
        
        str += "Device::kernel_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::kernel_properties_t::spirvVersionSupported : ";
        str += std::to_string(val.spirvVersionSupported);
        str += "\n";
        
        str += "Device::kernel_properties_t::fp16Supported : ";
        str += std::to_string(val.fp16Supported);
        str += "\n";
        
        str += "Device::kernel_properties_t::fp64Supported : ";
        str += std::to_string(val.fp64Supported);
        str += "\n";
        
        str += "Device::kernel_properties_t::int64AtomicsSupported : ";
        str += std::to_string(val.int64AtomicsSupported);
        str += "\n";
        
        str += "Device::kernel_properties_t::dp4aSupported : ";
        str += std::to_string(val.dp4aSupported);
        str += "\n";
        
        str += "Device::kernel_properties_t::maxArgumentsSize : ";
        str += std::to_string(val.maxArgumentsSize);
        str += "\n";
        
        str += "Device::kernel_properties_t::printfBufferSize : ";
        str += std::to_string(val.printfBufferSize);
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
        
        str += "Device::cache_properties_t::intermediateCachelineSize : ";
        str += std::to_string(val.intermediateCachelineSize);
        str += "\n";
        
        str += "Device::cache_properties_t::lastLevelCacheSizeControlSupported : ";
        str += std::to_string(val.lastLevelCacheSizeControlSupported);
        str += "\n";
        
        str += "Device::cache_properties_t::lastLevelCacheSize : ";
        str += std::to_string(val.lastLevelCacheSize);
        str += "\n";
        
        str += "Device::cache_properties_t::lastLevelCachelineSize : ";
        str += std::to_string(val.lastLevelCachelineSize);
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
        
        str += "Device::image_properties_t::maxImageBufferSize : ";
        str += std::to_string(val.maxImageBufferSize);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageArraySlices : ";
        str += std::to_string(val.maxImageArraySlices);
        str += "\n";
        
        str += "Device::image_properties_t::maxSamplers : ";
        str += std::to_string(val.maxSamplers);
        str += "\n";
        
        str += "Device::image_properties_t::maxReadImageArgs : ";
        str += std::to_string(val.maxReadImageArgs);
        str += "\n";
        
        str += "Device::image_properties_t::maxWriteImageArgs : ";
        str += std::to_string(val.maxWriteImageArgs);
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

} // namespace ze
