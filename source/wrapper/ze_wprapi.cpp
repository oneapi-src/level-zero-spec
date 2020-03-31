/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_wprapi.cpp
 * @version v1.0-r0.9.277
 *
 * @brief C++ wrapper of ze
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _ZE_STRING(s) #s
#define ZE_STRING(s) _ZE_STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    std::string exception_t::formatted(
        const result_t result,
        const char* file,
        const char* line,
        const char* func )
    {
    #ifdef _DEBUG
        std::stringstream msg;
        msg << file << "(" << line << ") : exception : " << func << "(" << ze::to_string(result) << ")";
        return msg.str();
    #else
        return ze::to_string(result);
    #endif
    }

    ///////////////////////////////////////////////////////////////////////////////
    Driver::Driver( 
        driver_handle_t handle                          ///< [in] handle of the driver instance
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize the 'One API' driver and must be called before any other
    ///        API function
    /// 
    /// @details
    ///     - If this function is not called then all other functions will return
    ///       ::ZE_RESULT_ERROR_UNINITIALIZED.
    ///     - Only one instance of a driver per process will be initialized.
    ///     - This function is thread-safe for scenarios where multiple libraries
    ///       may initialize the driver simultaneously.
    /// 
    /// @throws result_t
    void __zecall
    Init(
        init_flag_t flags                               ///< [in] initialization flags
        )
    {
        auto result = static_cast<result_t>( ::zeInit(
            static_cast<ze_init_flag_t>( flags ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::::Init" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves driver instances
    /// 
    /// @details
    ///     - A driver represents a collection of physical devices.
    ///     - The application may pass nullptr for pDrivers when only querying the
    ///       number of drivers.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetPlatformIDs
    /// 
    /// @throws result_t
    void __zecall
    Driver::Get(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader will update the value with the total
                                                        ///< number of drivers available.
                                                        ///< if count is non-zero, then the loader will only retrieve that number
                                                        ///< of drivers.
                                                        ///< if count is larger than the number of drivers available, then the
                                                        ///< loader will update the value with the correct number of drivers available.
        Driver** ppDrivers                              ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
        )
    {
        thread_local std::vector<ze_driver_handle_t> hDrivers;
        hDrivers.resize( ( ppDrivers ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zeDriverGet(
            pCount,
            hDrivers.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::Get" );

        for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
            ppDrivers[ i ] = nullptr;

        try
        {
            static singleton_factory_t<Driver, driver_handle_t> driverFactory;

            for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
                ppDrivers[ i ] = driverFactory.getInstance( reinterpret_cast<driver_handle_t>( hDrivers[ i ] ) );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Driver::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the API version supported by the specified driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - api_version_t: api version
    /// 
    /// @throws result_t
    Driver::api_version_t __zecall
    Driver::GetApiVersion(
        void
        )
    {
        ze_api_version_t version;

        auto result = static_cast<result_t>( ::zeDriverGetApiVersion(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetApiVersion" );

        return *reinterpret_cast<api_version_t*>( &version );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves properties of the driver.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clGetPlatformInfo**
    /// 
    /// @throws result_t
    void __zecall
    Driver::GetProperties(
        properties_t* pDriverProperties                 ///< [in,out] query result for driver properties
        )
    {
        auto result = static_cast<result_t>( ::zeDriverGetProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<ze_driver_properties_t*>( pDriverProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves IPC attributes of the driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ipc_properties_t: query result for IPC properties
    /// 
    /// @throws result_t
    Driver::ipc_properties_t __zecall
    Driver::GetIPCProperties(
        void
        )
    {
        ze_driver_ipc_properties_t iPCProperties;

        auto result = static_cast<result_t>( ::zeDriverGetIPCProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            &iPCProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetIPCProperties" );

        return *reinterpret_cast<ipc_properties_t*>( &iPCProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves an extension function for the specified driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clGetExtensionFunctionAddressForPlatform**
    /// 
    /// @returns
    ///     - void*: pointer to extension function
    /// 
    /// @throws result_t
    void* __zecall
    Driver::GetExtensionFunctionAddress(
        const char* pFuncName                           ///< [in] name of the extension function
        )
    {
        void* pfunc;

        auto result = static_cast<result_t>( ::zeDriverGetExtensionFunctionAddress(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            pFuncName,
            &pfunc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetExtensionFunctionAddress" );

        return pfunc;
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
    /// @brief Retrieves devices within a driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::Get" );

        for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
            ppDevices[ i ] = nullptr;

        try
        {
            static singleton_factory_t<Device, device_handle_t> deviceFactory;

            for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
                ppDevices[ i ] = deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevices[ i ] ), pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Device::Get" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetSubDevices" );

        for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
            ppSubdevices[ i ] = nullptr;

        try
        {
            static singleton_factory_t<Device, device_handle_t> deviceFactory;

            for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
                ppSubdevices[ i ] = deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hSubdevices[ i ] ), m_pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetSubDevices" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetProperties" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetComputeProperties" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetKernelProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves command queue group properties of the device.
    /// 
    /// @details
    ///     - Properties are reported for each physical command queue type supported
    ///       by the device.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkGetPhysicalDeviceQueueFamilyProperties**
    /// 
    /// @throws result_t
    void __zecall
    Device::GetCommandQueueGroupProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of command queue group properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< command queue group properties.
                                                        ///< if count is larger than the number of command queue group properties
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of command queue group properties available.
        command_queue_group_properties_t* pCommandQueueGroupProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< command queue group properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetCommandQueueGroupProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<ze_command_queue_group_properties_t*>( pCommandQueueGroupProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetCommandQueueGroupProperties" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetMemoryProperties" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetMemoryAccessProperties" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetCacheProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves image properties of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetImageProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves Peer-to-Peer properties between one device and a peer
    ///        devices
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetP2PProperties" );
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::CanAccessPeer" );

        return *reinterpret_cast<bool_t*>( &value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred Last Level cache configuration for a device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::SetLastLevelCacheConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    CommandQueue::CommandQueue( 
        command_queue_handle_t handle,                  ///< [in] handle of command queue object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command queue object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command queue on the device.
    /// 
    /// @details
    ///     - The command queue can only be used on the device on which it was
    ///       created.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateCommandQueue**
    /// 
    /// @returns
    ///     - CommandQueue*: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __zecall
    CommandQueue::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command queue descriptor
        )
    {
        ze_command_queue_handle_t hCommandQueue;

        auto result = static_cast<result_t>( ::zeCommandQueueCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_queue_desc_t*>( desc ),
            &hCommandQueue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Create" );

        CommandQueue* pCommandQueue = nullptr;

        try
        {
            pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandQueue;
            pCommandQueue = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Create" );
        }

        return pCommandQueue;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command queue.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the command queue before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this command queue
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command queue handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseCommandQueue**
    /// 
    /// @throws result_t
    void __zecall
    CommandQueue::Destroy(
        CommandQueue* pCommandQueue                     ///< [in][release] pointer to command queue object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeCommandQueueDestroy(
            reinterpret_cast<ze_command_queue_handle_t>( pCommandQueue->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Destroy" );

        delete pCommandQueue;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Executes a command list in a command queue.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkQueueSubmit
    /// 
    /// @throws result_t
    void __zecall
    CommandQueue::ExecuteCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        CommandList** ppCommandLists,                   ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        Fence* pFence                                   ///< [in][optional] pointer to the fence to signal on completion
        )
    {
        thread_local std::vector<ze_command_list_handle_t> hCommandLists;
        hCommandLists.resize( 0 );
        hCommandLists.reserve( numCommandLists );
        for( uint32_t i = 0; i < numCommandLists; ++i )
            hCommandLists.emplace_back( reinterpret_cast<ze_command_list_handle_t>( ppCommandLists[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zeCommandQueueExecuteCommandLists(
            reinterpret_cast<ze_command_queue_handle_t>( getHandle() ),
            numCommandLists,
            hCommandLists.data(),
            ( pFence ) ? reinterpret_cast<ze_fence_handle_t>( pFence->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::ExecuteCommandLists" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Synchronizes a command queue by waiting on the host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    CommandQueue::Synchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::zeCommandQueueSynchronize(
            reinterpret_cast<ze_command_queue_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Synchronize" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    CommandList::CommandList( 
        command_list_handle_t handle,                   ///< [in] handle of command list object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command list object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command list on the device for submitting commands to any
    ///        command queue.
    /// 
    /// @details
    ///     - The command list can only be used on the device on which it was
    ///       created.
    ///     - The command list is created in the 'open' state.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - CommandList*: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* __zecall
    CommandList::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command list descriptor
        )
    {
        ze_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::zeCommandListCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_list_desc_t*>( desc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Create" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Create" );
        }

        return pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command list on the device with an implicit command queue
    ///        for immediate submission of commands.
    /// 
    /// @details
    ///     - The command list can only be used on the device on which it was
    ///       created.
    ///     - The command list is created in the 'open' state and never needs to be
    ///       closed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - CommandList*: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* __zecall
    CommandList::CreateImmediate(
        Device* pDevice,                                ///< [in] pointer to the device object
        const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
        )
    {
        ze_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::zeCommandListCreateImmediate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_queue_desc_t*>( altdesc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::CreateImmediate" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::CreateImmediate" );
        }

        return pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command list.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the command list before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this command list.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::Destroy(
        CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListDestroy(
            reinterpret_cast<ze_command_list_handle_t>( pCommandList->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Destroy" );

        delete pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes a command list; ready to be executed by a command queue.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListClose(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Close" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset a command list to initial (empty) state; ready for appending
    ///        commands.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the command list before it is reset
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListReset(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends an execution and global memory barrier into a command list.
    /// 
    /// @details
    ///     - If numWaitEvents is zero, then all previous commands are completed
    ///       prior to the execution of the barrier.
    ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
    ///       signaled prior to the execution of the barrier.
    ///     - This command blocks all following commands from beginning until the
    ///       execution of the barrier completes.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkCmdPipelineBarrier**
    ///     - clEnqueueBarrierWithWaitList
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendBarrier(
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before executing barrier
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendBarrier(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a global memory ranges barrier into a command list.
    /// 
    /// @details
    ///     - If numWaitEvents is zero, then all previous commands are completed
    ///       prior to the execution of the barrier.
    ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
    ///       signaled prior to the execution of the barrier.
    ///     - This command blocks all following commands from beginning until the
    ///       execution of the barrier completes.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryRangesBarrier(
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before executing barrier
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryRangesBarrier(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numRanges,
            pRangeSizes,
            pRanges,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryRangesBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Ensures in-bound writes to the device are globally observable.
    /// 
    /// @details
    ///     - This is a special-case system level barrier that can be used to ensure
    ///       global observability of writes; typically needed after a producer
    ///       (e.g., NIC) performs direct writes to the device's memory (e.g.,
    ///       Direct RDMA writes).  This is typically required when the memory
    ///       corresponding to the writes is subsequently accessed from a remote
    ///       device.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::SystemBarrier(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceSystemBarrier(
            reinterpret_cast<ze_device_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::SystemBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL memory with 'One API'
    /// 
    /// @returns
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    void* __zecall
    Device::RegisterCLMemory(
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem                                      ///< [in] the OpenCL memory to register
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::zeDeviceRegisterCLMemory(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            context,
            mem,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::RegisterCLMemory" );

        return ptr;
    }
#endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL program with 'One API'
    /// 
    /// @returns
    ///     - Module*: pointer to handle of module object created
    /// 
    /// @throws result_t
    Module* __zecall
    Device::RegisterCLProgram(
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program                              ///< [in] the OpenCL program to register
        )
    {
        ze_module_handle_t hModule;

        auto result = static_cast<result_t>( ::zeDeviceRegisterCLProgram(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            context,
            program,
            &hModule ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::RegisterCLProgram" );

        Module* pModule = nullptr;

        try
        {
            pModule = new Module( reinterpret_cast<module_handle_t>( hModule ), this, m_desc );
        }
        catch( std::bad_alloc& )
        {
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Device::RegisterCLProgram" );
        }

        return pModule;
    }
#endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if ZE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL command queue with 'One API'
    /// 
    /// @returns
    ///     - CommandQueue*: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __zecall
    Device::RegisterCLCommandQueue(
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
        )
    {
        ze_command_queue_handle_t hCommandQueue;

        auto result = static_cast<result_t>( ::zeDeviceRegisterCLCommandQueue(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            context,
            command_queue,
            &hCommandQueue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::RegisterCLCommandQueue" );

        CommandQueue* pCommandQueue = nullptr;

        try
        {
            pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), this, m_desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandQueue;
            pCommandQueue = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Device::RegisterCLCommandQueue" );
        }

        return pCommandQueue;
    }
#endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies host, device, or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by both srcptr and dstptr must be accessible by
    ///       the device on which the command list is created.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueCopyBuffer**
    ///     - **clEnqueueReadBuffer**
    ///     - **clEnqueueWriteBuffer**
    ///     - **clEnqueueSVMMemcpy**
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            srcptr,
            size,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryCopy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes host, device, or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by dstptr must be accessible by the device on
    ///       which the command list is created.
    ///     - The value to initialize memory to is described by the pattern and the
    ///       pattern size.
    ///     - The pattern size must be a power of two.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueFillBuffer**
    ///     - **clEnqueueSVMMemFill**
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryFill(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryFill(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            pattern,
            pattern_size,
            size,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryFill" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a region from a 2D or 3D array of host, device, or shared
    ///        memory.
    /// 
    /// @details
    ///     - The memory pointed to by both srcptr and dstptr must be accessible by
    ///       the device on which the command list is created.
    ///     - The region width, height, and depth for both src and dst must be same.
    ///       The origins can be different.
    ///     - The src and dst regions cannot be overlapping.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryCopyRegion(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const copy_region_t* dstRegion,                 ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                        ///< ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const copy_region_t* srcRegion,                 ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                        ///< ignored.
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<const ze_copy_region_t*>( dstRegion ),
            dstPitch,
            dstSlicePitch,
            srcptr,
            reinterpret_cast<const ze_copy_region_t*>( srcRegion ),
            srcPitch,
            srcSlicePitch,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryCopyRegion" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a image.
    /// 
    /// @details
    ///     - Images format descriptors for both source and destination images must
    ///       be the same.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueCopyImage**
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopy(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a region of a image to another image.
    /// 
    /// @details
    ///     - The region width and height for both src and dst must be same. The
    ///       origins can be different.
    ///     - The src and dst regions cannot be overlapping.
    ///     - Images format descriptors for both source and destination images must
    ///       be the same.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopyRegion(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopyRegion" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies from a image to device or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by dstptr must be accessible by the device on
    ///       which the command list is created.
    ///     - Media formats are not supported for this function.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueReadImage
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyToMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopyToMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies to a image from device or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by srcptr must be accessible by the device on
    ///       which the command list is created.
    ///     - Media formats are not supported for this function.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueWriteImage
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopyFromMemory(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyFromMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            srcptr,
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopyFromMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Asynchronously prefetches shared memory to the device associated with
    ///        the specified command list
    /// 
    /// @details
    ///     - This is a hint to improve performance only and is not required for
    ///       correctness.
    ///     - Only prefetching to the device associated with the specified command
    ///       list is supported.
    ///       Prefetching to the host or to a peer device is not supported.
    ///     - Prefetching may not be supported for all allocation types for all devices.
    ///       If memory prefetching is not supported for the specified memory range
    ///       the prefetch hint may be ignored.
    ///     - Prefetching may only be supported at a device-specific granularity,
    ///       such as at a page boundary.
    ///       In this case, the memory range may be expanded such that the start and
    ///       end of the range satisfy granularity requirements.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueSVMMigrateMem
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryPrefetch(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryPrefetch" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Provides advice about the use of a shared memory range
    /// 
    /// @details
    ///     - Memory advice is a performance hint only and is not required for
    ///       functional correctness.
    ///     - Memory advice can be used to override driver heuristics to explicitly
    ///       control shared memory behavior.
    ///     - Not all memory advice hints may be supported for all allocation types
    ///       for all devices.
    ///       If a memory advice hint is not supported by the device it will be ignored.
    ///     - Memory advice may only be supported at a device-specific granularity,
    ///       such as at a page boundary.
    ///       In this case, the memory range may be expanded such that the start and
    ///       end of the range satisfy granularity requirements.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemAdvise(
        Device* pDevice,                                ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemAdvise(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            ptr,
            size,
            static_cast<ze_memory_advice_t>( advice ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemAdvise" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    EventPool::EventPool( 
        event_pool_handle_t handle,                     ///< [in] handle of event pool object
        Driver* pDriver,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the event pool object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Event::Event( 
        event_handle_t handle,                          ///< [in] handle of event object
        EventPool* pEventPool,                          ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the event object
        ) :
        m_handle( handle ),
        m_pEventPool( pEventPool ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a pool for a set of event(s) for the driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __zecall
    EventPool::Create(
        Driver* pDriver,                                ///< [in] pointer to the driver instance
        const desc_t* desc,                             ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        Device** ppDevices                              ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        )
    {
        thread_local std::vector<ze_device_handle_t> hDevices;
        hDevices.resize( 0 );
        hDevices.reserve( numDevices );
        for( uint32_t i = 0; i < numDevices; ++i )
            hDevices.emplace_back( ( ppDevices ) ? reinterpret_cast<ze_device_handle_t>( ppDevices[ i ]->getHandle() ) : nullptr );

        ze_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::zeEventPoolCreate(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            reinterpret_cast<const ze_event_pool_desc_t*>( desc ),
            numDevices,
            hDevices.data(),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::Create" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pDriver, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::Create" );
        }

        return pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes an event pool object.
    /// 
    /// @details
    ///     - The application is responsible for destroying all event handles
    ///       created from the pool before destroying the pool itself
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the any event within the pool before it is
    ///       deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this event pool
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    EventPool::Destroy(
        EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolDestroy(
            reinterpret_cast<ze_event_pool_handle_t>( pEventPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::Destroy" );

        delete pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an event on the device.
    /// 
    /// @details
    ///     - Multiple events cannot be created using the same location within the
    ///       same pool.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateUserEvent**
    ///     - vkCreateEvent
    /// 
    /// @returns
    ///     - Event*: pointer to handle of event object created
    /// 
    /// @throws result_t
    Event* __zecall
    Event::Create(
        EventPool* pEventPool,                          ///< [in] pointer to the event pool
        const desc_t* desc                              ///< [in] pointer to event descriptor
        )
    {
        ze_event_handle_t hEvent;

        auto result = static_cast<result_t>( ::zeEventCreate(
            reinterpret_cast<ze_event_pool_handle_t>( pEventPool->getHandle() ),
            reinterpret_cast<const ze_event_desc_t*>( desc ),
            &hEvent ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::Create" );

        Event* pEvent = nullptr;

        try
        {
            pEvent = new Event( reinterpret_cast<event_handle_t>( hEvent ), pEventPool, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEvent;
            pEvent = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Event::Create" );
        }

        return pEvent;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes an event object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the event before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this event
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseEvent**
    ///     - vkDestroyEvent
    /// 
    /// @throws result_t
    void __zecall
    Event::Destroy(
        Event* pEvent                                   ///< [in][release] pointer to event object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventDestroy(
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::Destroy" );

        delete pEvent;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Gets an IPC event pool handle for the specified event handle that can
    ///        be shared with another process.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - ipc_event_pool_handle_t: Returned IPC event handle
    /// 
    /// @throws result_t
    ipc_event_pool_handle_t __zecall
    EventPool::GetIpcHandle(
        void
        )
    {
        ze_ipc_event_pool_handle_t hIpc;

        auto result = static_cast<result_t>( ::zeEventPoolGetIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ),
            &hIpc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::GetIpcHandle" );

        return *reinterpret_cast<ipc_event_pool_handle_t*>( &hIpc );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC event pool handle to retrieve an event pool handle from
    ///        another process.
    /// 
    /// @details
    ///     - The event handle in this process should not be freed with
    ///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __zecall
    EventPool::OpenIpcHandle(
        Driver* pDriver,                                ///< [in] pointer to the driver to associate with the IPC event pool handle
        ipc_event_pool_handle_t pIpc                    ///< [in] IPC event handle
        )
    {
        ze_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::zeEventPoolOpenIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            *reinterpret_cast<ze_ipc_event_pool_handle_t*>( &pIpc ),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pDriver, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );
        }

        return pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC event handle in the current process.
    /// 
    /// @details
    ///     - Closes an IPC event handle by destroying events that were opened in
    ///       this process using ::zeEventPoolOpenIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    /// 
    /// @throws result_t
    void __zecall
    EventPool::CloseIpcHandle(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolCloseIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::CloseIpcHandle" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a signal of the event from the device into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetUserEventStatus**
    ///     - vkCmdSetEvent
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendSignalEvent(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendSignalEvent(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendSignalEvent" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends wait on event(s) on the device into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendWaitOnEvents(
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        Event** ppEvents                                ///< [in][range(0, numEvents)] pointer to the events to wait on before
                                                        ///< continuing
        )
    {
        thread_local std::vector<ze_event_handle_t> hEvents;
        hEvents.resize( 0 );
        hEvents.reserve( numEvents );
        for( uint32_t i = 0; i < numEvents; ++i )
            hEvents.emplace_back( reinterpret_cast<ze_event_handle_t>( ppEvents[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zeCommandListAppendWaitOnEvents(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numEvents,
            hEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendWaitOnEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Signals a event from host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clSetUserEventStatus
    /// 
    /// @throws result_t
    void __zecall
    Event::HostSignal(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSignal(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::HostSignal" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The current host thread waits on an event to be signaled.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clWaitForEvents
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    Event::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSynchronize(
            reinterpret_cast<ze_event_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::HostSynchronize" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries an event object's status.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clGetEventInfo**
    ///     - vkGetEventStatus
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    Event::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventQueryStatus(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::QueryStatus" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset an event back to not signaled state
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkResetEvent
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendEventReset(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendEventReset(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendEventReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset an event back to not signaled state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkResetEvent
    /// 
    /// @throws result_t
    void __zecall
    Event::HostReset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostReset(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::HostReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query timestamp information associated with an event. Event must come
    ///        from an event pool that was created using
    ///        ::ZE_EVENT_POOL_FLAG_TIMESTAMP flag.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Event::GetTimestamp(
        EventPool::event_timestamp_type_t timestampType,///< [in] specifies timestamp type to query for that is associated with
                                                        ///< hEvent.
        void* dstptr                                    ///< [in,out] pointer to memory for where timestamp will be written to. The
                                                        ///< size of timestamp is specified in the ::ze_event_timestamp_type_t
                                                        ///< definition.
        )
    {
        auto result = static_cast<result_t>( ::zeEventGetTimestamp(
            reinterpret_cast<ze_event_handle_t>( getHandle() ),
            static_cast<ze_event_timestamp_type_t>( timestampType ),
            dstptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::GetTimestamp" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    Fence::Fence( 
        fence_handle_t handle,                          ///< [in] handle of fence object
        CommandQueue* pCommandQueue,                    ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the fence object
        ) :
        m_handle( handle ),
        m_pCommandQueue( pCommandQueue ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a fence object on the device's command queue.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkCreateFence**
    /// 
    /// @returns
    ///     - Fence*: pointer to handle of fence object created
    /// 
    /// @throws result_t
    Fence* __zecall
    Fence::Create(
        CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
        const desc_t* desc                              ///< [in] pointer to fence descriptor
        )
    {
        ze_fence_handle_t hFence;

        auto result = static_cast<result_t>( ::zeFenceCreate(
            reinterpret_cast<ze_command_queue_handle_t>( pCommandQueue->getHandle() ),
            reinterpret_cast<const ze_fence_desc_t*>( desc ),
            &hFence ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Create" );

        Fence* pFence = nullptr;

        try
        {
            pFence = new Fence( reinterpret_cast<fence_handle_t>( hFence ), pCommandQueue, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pFence;
            pFence = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Create" );
        }

        return pFence;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a fence object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the fence before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this fence
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same fence handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkDestroyFence**
    /// 
    /// @throws result_t
    void __zecall
    Fence::Destroy(
        Fence* pFence                                   ///< [in][release] pointer to fence object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeFenceDestroy(
            reinterpret_cast<ze_fence_handle_t>( pFence->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Destroy" );

        delete pFence;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The current host thread waits on a fence to be signaled.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkWaitForFences**
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    Fence::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::zeFenceHostSynchronize(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::HostSynchronize" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries a fence object's status.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkGetFenceStatus**
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    Fence::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeFenceQueryStatus(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::QueryStatus" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset a fence back to the not signaled state.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkResetFences**
    /// 
    /// @throws result_t
    void __zecall
    Fence::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeFenceReset(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    Image::Image( 
        image_handle_t handle,                          ///< [in] handle of image object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the image object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves supported properties of an image.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - properties_t: pointer to image properties
    /// 
    /// @throws result_t
    Image::properties_t __zecall
    Image::GetProperties(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        ze_image_properties_t imageProperties;

        auto result = static_cast<result_t>( ::zeImageGetProperties(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_image_desc_t*>( desc ),
            &imageProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Image::GetProperties" );

        return *reinterpret_cast<properties_t*>( &imageProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a image object on the device.
    /// 
    /// @details
    ///     - The image is only visible to the device on which it was created.
    ///     - The image can be copied to another device using the
    ///       ::::zeCommandListAppendImageCopy functions.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clCreateImage
    /// 
    /// @returns
    ///     - Image*: pointer to handle of image object created
    /// 
    /// @throws result_t
    Image* __zecall
    Image::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        ze_image_handle_t hImage;

        auto result = static_cast<result_t>( ::zeImageCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_image_desc_t*>( desc ),
            &hImage ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Image::Create" );

        Image* pImage = nullptr;

        try
        {
            pImage = new Image( reinterpret_cast<image_handle_t>( hImage ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pImage;
            pImage = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Image::Create" );
        }

        return pImage;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a image object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the image before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this image
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same image handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Image::Destroy(
        Image* pImage                                   ///< [in][release] pointer to image object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeImageDestroy(
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Image::Destroy" );

        delete pImage;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates memory that is shared between the host and one or more
    ///        devices
    /// 
    /// @details
    ///     - Shared allocations share ownership between the host and one or more
    ///       devices.
    ///     - Shared allocations may optionally be associated with a device by
    ///       passing a handle to the device.
    ///     - Devices supporting only single-device shared access capabilities may
    ///       access shared memory associated with the device.
    ///       For these devices, ownership of the allocation is shared between the
    ///       host and the associated device only.
    ///     - Passing nullptr as the device handle does not associate the shared
    ///       allocation with any device.
    ///       For allocations with no associated device, ownership of the allocation
    ///       is shared between the host and all devices supporting cross-device
    ///       shared access capabilities.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - void*: pointer to shared allocation
    /// 
    /// @throws result_t
    void* __zecall
    Driver::AllocSharedMem(
        const device_mem_alloc_desc_t* device_desc,     ///< [in] pointer to device mem alloc descriptor
        const host_mem_alloc_desc_t* host_desc,         ///< [in] pointer to host mem alloc descriptor
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        Device* pDevice                                 ///< [in][optional] device handle to associate with
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverAllocSharedMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<const ze_device_mem_alloc_desc_t*>( device_desc ),
            reinterpret_cast<const ze_host_mem_alloc_desc_t*>( host_desc ),
            size,
            alignment,
            ( pDevice ) ? reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ) : nullptr,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::AllocSharedMem" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates memory specific to a device
    /// 
    /// @details
    ///     - A device allocation is owned by a specific device.
    ///     - In general, a device allocation may only be accessed by the device
    ///       that owns it.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    void* __zecall
    Driver::AllocDeviceMem(
        const device_mem_alloc_desc_t* device_desc,     ///< [in] pointer to device mem alloc descriptor
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        Device* pDevice                                 ///< [in] pointer to the device
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverAllocDeviceMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<const ze_device_mem_alloc_desc_t*>( device_desc ),
            size,
            alignment,
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::AllocDeviceMem" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates host memory
    /// 
    /// @details
    ///     - A host allocation is owned by the host process.
    ///     - Host allocations are accessible by the host and all devices within the
    ///       driver driver.
    ///     - Host allocations are frequently used as staging areas to transfer data
    ///       to or from devices.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - void*: pointer to host allocation
    /// 
    /// @throws result_t
    void* __zecall
    Driver::AllocHostMem(
        const host_mem_alloc_desc_t* host_desc,         ///< [in] pointer to host mem alloc descriptor
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverAllocHostMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<const ze_host_mem_alloc_desc_t*>( host_desc ),
            size,
            alignment,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::AllocHostMem" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Frees allocated host memory, device memory, or shared memory
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the memory before it is freed
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this memory
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @throws result_t
    void __zecall
    Driver::FreeMem(
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto result = static_cast<result_t>( ::zeDriverFreeMem(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::FreeMem" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a memory allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - Device*: device associated with this allocation
    /// 
    /// @throws result_t
    void __zecall
    Driver::GetMemAllocProperties(
        const void* ptr,                                ///< [in] memory pointer to query
        memory_allocation_properties_t* pMemAllocProperties,///< [in,out] query result for memory allocation properties
        Device** ppDevice                               ///< [out][optional] device associated with this allocation
        )
    {
        ze_device_handle_t hDevice;

        auto result = static_cast<result_t>( ::zeDriverGetMemAllocProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr,
            reinterpret_cast<ze_memory_allocation_properties_t*>( pMemAllocProperties ),
            ( ppDevice ) ? &hDevice : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetMemAllocProperties" );

        if( ppDevice )
            *ppDevice =  nullptr;

        try
        {
            static singleton_factory_t<Device, device_handle_t> deviceFactory;

            if( ppDevice )
                *ppDevice =  deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevice ), this );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetMemAllocProperties" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves the base address and/or size of an allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    Driver::GetMemAddressRange(
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        auto result = static_cast<result_t>( ::zeDriverGetMemAddressRange(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr,
            pBase,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetMemAddressRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an IPC memory handle for the specified allocation in the
    ///        sending process
    /// 
    /// @details
    ///     - Takes a pointer to the base of a device memory allocation and exports
    ///       it for use in another process.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - ipc_mem_handle_t: Returned IPC memory handle
    /// 
    /// @throws result_t
    ipc_mem_handle_t __zecall
    Driver::GetMemIpcHandle(
        const void* ptr                                 ///< [in] pointer to the device memory allocation
        )
    {
        ze_ipc_mem_handle_t ipcHandle;

        auto result = static_cast<result_t>( ::zeDriverGetMemIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr,
            &ipcHandle ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetMemIpcHandle" );

        return *reinterpret_cast<ipc_mem_handle_t*>( &ipcHandle );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
    ///        process
    /// 
    /// @details
    ///     - Takes an IPC memory handle from a sending process and associates it
    ///       with a device pointer usable in this process.
    ///     - The device pointer in this process should not be freed with
    ///       ::zeDriverFreeMem, but rather with ::zeDriverCloseMemIpcHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - void*: pointer to device allocation in this process
    /// 
    /// @throws result_t
    void* __zecall
    Driver::OpenMemIpcHandle(
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
        ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
        ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeDriverOpenMemIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            *reinterpret_cast<ze_ipc_mem_handle_t*>( &handle ),
            static_cast<ze_ipc_memory_flag_t>( flags ),
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::OpenMemIpcHandle" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC memory handle in a receiving process
    /// 
    /// @details
    ///     - Closes an IPC memory handle by unmapping memory that was opened in
    ///       this process using ::zeDriverOpenMemIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same pointer.
    /// 
    /// @throws result_t
    void __zecall
    Driver::CloseMemIpcHandle(
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto result = static_cast<result_t>( ::zeDriverCloseMemIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::CloseMemIpcHandle" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    Module::Module( 
        module_handle_t handle,                         ///< [in] handle of module object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the module object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    ModuleBuildLog::ModuleBuildLog( 
        module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
        Module* pModule                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pModule( pModule )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Kernel::Kernel( 
        kernel_handle_t handle,                         ///< [in] handle of kernel object
        Module* pModule,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the kernel object
        ) :
        m_handle( handle ),
        m_pModule( pModule ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates module object from an input IL or native binary.
    /// 
    /// @details
    ///     - Compiles the module for execution on the device.
    ///     - The module can only be used on the device on which it was created.
    ///     - The module can be copied to other devices within the same driver
    ///       instance by using ::zeModuleGetNativeBinary.
    ///     - The following build options are supported:
    ///         + "-ze-opt-disable" - Disable optimizations
    ///         + "-ze-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
    ///           calculations for buffers.
    ///         + "-ze-opt-large-register-file" - Increase number of registers
    ///           available to threads.
    ///     - A build log can optionally be returned to the caller. The caller is
    ///       responsible for destroying build log using ::zeModuleBuildLogDestroy.
    ///     - The module descriptor constants are only supported for SPIR-V
    ///       specialization constants.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Module*: pointer to handle of module object created
    ///     - ModuleBuildLog*: pointer to handle of module's build log.
    /// 
    /// @throws result_t
    Module* __zecall
    Module::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc,                             ///< [in] pointer to module descriptor
        ModuleBuildLog** ppBuildLog                     ///< [out][optional] pointer to pointer to module's build log.
        )
    {
        ze_module_handle_t hModule;

        ze_module_build_log_handle_t hBuildLog;

        auto result = static_cast<result_t>( ::zeModuleCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_module_desc_t*>( desc ),
            &hModule,
            ( ppBuildLog ) ? &hBuildLog : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::Create" );

        Module* pModule = nullptr;

        try
        {
            pModule = new Module( reinterpret_cast<module_handle_t>( hModule ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Module::Create" );
        }

        if( ppBuildLog )
            *ppBuildLog =  nullptr;

        try
        {
            if( ppBuildLog )
                *ppBuildLog =  new ModuleBuildLog( reinterpret_cast<module_build_log_handle_t>( hBuildLog ), pModule );
        }
        catch( std::bad_alloc& )
        {
            if( ppBuildLog )
            {
                delete *ppBuildLog;
                *ppBuildLog =  nullptr;
            }
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Module::Create" );
        }

        return pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the module before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this module
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same module handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Module::Destroy(
        Module* pModule                                 ///< [in][release] pointer to the module
        )
    {
        auto result = static_cast<result_t>( ::zeModuleDestroy(
            reinterpret_cast<ze_module_handle_t>( pModule->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::Destroy" );

        delete pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module build log object
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host
    ///       allocations associated with this object
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same build log handle.
    ///     - The implementation of this function should be lock-free.
    ///     - This function can be called before or after ::zeModuleDestroy for the
    ///       associated module.
    /// 
    /// @throws result_t
    void __zecall
    ModuleBuildLog::Destroy(
        ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
        )
    {
        auto result = static_cast<result_t>( ::zeModuleBuildLogDestroy(
            reinterpret_cast<ze_module_build_log_handle_t>( pModuleBuildLog->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::ModuleBuildLog::Destroy" );

        delete pModuleBuildLog;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves text string for build log.
    /// 
    /// @details
    ///     - The caller can pass nullptr for pBuildLog when querying only for size.
    ///     - The caller must provide memory for build log.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    ModuleBuildLog::GetString(
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        auto result = static_cast<result_t>( ::zeModuleBuildLogGetString(
            reinterpret_cast<ze_module_build_log_handle_t>( getHandle() ),
            pSize,
            pBuildLog ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::ModuleBuildLog::GetString" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve native binary from Module.
    /// 
    /// @details
    ///     - The native binary output can be cached to disk and new modules can be
    ///       later constructed from the cached copy.
    ///     - The native binary will retain debugging information that is associated
    ///       with a module.
    ///     - The caller can pass nullptr for pModuleNativeBinary when querying only
    ///       for size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Module::GetNativeBinary(
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetNativeBinary(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pSize,
            pModuleNativeBinary ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetNativeBinary" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve global variable pointer from Module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: device visible pointer
    /// 
    /// @throws result_t
    void* __zecall
    Module::GetGlobalPointer(
        const char* pGlobalName                         ///< [in] name of global variable in module
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeModuleGetGlobalPointer(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pGlobalName,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetGlobalPointer" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve all kernel names in the module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Module::GetKernelNames(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of names available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of names.
                                                        ///< if count is larger than the number of names available, then the driver
                                                        ///< will update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetKernelNames(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pCount,
            pNames ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetKernelNames" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Create a kernel object from a module by name
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Kernel*: handle of the Function object
    /// 
    /// @throws result_t
    Kernel* __zecall
    Kernel::Create(
        Module* pModule,                                ///< [in] pointer to the module
        const desc_t* desc                              ///< [in] pointer to kernel descriptor
        )
    {
        ze_kernel_handle_t hKernel;

        auto result = static_cast<result_t>( ::zeKernelCreate(
            reinterpret_cast<ze_module_handle_t>( pModule->getHandle() ),
            reinterpret_cast<const ze_kernel_desc_t*>( desc ),
            &hKernel ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::Create" );

        Kernel* pKernel = nullptr;

        try
        {
            pKernel = new Kernel( reinterpret_cast<kernel_handle_t>( hKernel ), pModule, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pKernel;
            pKernel = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::Create" );
        }

        return pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a kernel object
    /// 
    /// @details
    ///     - All kernels must be destroyed before the module is destroyed.
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the kernel before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this kernel
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::Destroy(
        Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
        )
    {
        auto result = static_cast<result_t>( ::zeKernelDestroy(
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::Destroy" );

        delete pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve a function pointer from a module by name
    /// 
    /// @details
    ///     - The function pointer is unique for the device on which the module was
    ///       created.
    ///     - The function pointer is no longer valid if module is destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to function.
    /// 
    /// @throws result_t
    void* __zecall
    Module::GetFunctionPointer(
        const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
        )
    {
        void* pfnFunction;

        auto result = static_cast<result_t>( ::zeModuleGetFunctionPointer(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pFunctionName,
            &pfnFunction ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetFunctionPointer" );

        return pfnFunction;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set group size for a kernel
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The implementation will copy the group size information into a command
    ///       list when the function is appended.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetGroupSize(
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetGroupSize(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            groupSizeX,
            groupSizeY,
            groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetGroupSize" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested group size for a kernel given a global size for each
    ///        dimension.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function ignores the group size that is set using
    ///       ::zeKernelSetGroupSize.
    /// 
    /// @returns
    ///     - uint32_t: recommended size of group for X dimension
    ///     - uint32_t: recommended size of group for Y dimension
    ///     - uint32_t: recommended size of group for Z dimension
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t, uint32_t> __zecall
    Kernel::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ                            ///< [in] global width for Z dimension
        )
    {
        uint32_t groupSizeX;

        uint32_t groupSizeY;

        uint32_t groupSizeZ;

        auto result = static_cast<result_t>( ::zeKernelSuggestGroupSize(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            globalSizeX,
            globalSizeY,
            globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SuggestGroupSize" );

        return std::make_tuple( groupSizeX, groupSizeY, groupSizeZ );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested max group count a cooperative kernel.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - uint32_t: recommended total group count.
    /// 
    /// @throws result_t
    uint32_t __zecall
    Kernel::SuggestMaxCooperativeGroupCount(
        void
        )
    {
        uint32_t totalGroupCount;

        auto result = static_cast<result_t>( ::zeKernelSuggestMaxCooperativeGroupCount(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            &totalGroupCount ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SuggestMaxCooperativeGroupCount" );

        return totalGroupCount;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set kernel argument used on kernel launch.
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The implementation will copy the arguments into a command list when
    ///       the function is appended.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetArgumentValue(
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetArgumentValue(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            argIndex,
            argSize,
            pArgValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetArgumentValue" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets a kernel attribute
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetKernelExecInfo**
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetAttribute(
        attribute_t attr,                               ///< [in] attribute to set
        uint32_t size,                                  ///< [in] size in bytes of kernel attribute value.
        const void* pValue                              ///< [in][optional] pointer to attribute value.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetAttribute(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_kernel_attribute_t>( attr ),
            size,
            pValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetAttribute" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Gets a kernel attribute
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The caller sets pValue to nullptr when querying only for size.
    ///     - The caller must provide memory for pValue querying when querying size.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::GetAttribute(
        attribute_t attr,                               ///< [in] attribute to get. Documentation for ::ze_kernel_attribute_t for
                                                        ///< return type information for pValue.
        uint32_t* pSize,                                ///< [in,out] size in bytes needed for kernel attribute value. If pValue is
                                                        ///< nullptr then the size needed for pValue memory will be written to
                                                        ///< pSize. Only need to query size for arbitrary sized attributes.
        void* pValue                                    ///< [in,out][optional] pointer to attribute value result.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelGetAttribute(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_kernel_attribute_t>( attr ),
            pSize,
            pValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::GetAttribute" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred Intermediate cache configuration for a kernel.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::SetIntermediateCacheConfig(
        Device::cache_config_t CacheConfig              ///< [in] CacheConfig
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetIntermediateCacheConfig(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_cache_config_t>( CacheConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetIntermediateCacheConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve kernel properties.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Kernel::GetProperties(
        properties_t* pKernelProperties                 ///< [in,out] query result for kernel properties.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelGetProperties(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_properties_t*>( pKernelProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups.
    /// 
    /// @details
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchKernel(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel cooperatively over one or more work groups.
    /// 
    /// @details
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This may only be used for a command list that are submitted to command
    ///       queue with cooperative flag set.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    ///     - Use ::zeKernelSuggestMaxCooperativeGroupCount to recommend max group
    ///       count for device for cooperative functions that device supports.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchCooperativeKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchCooperativeKernel(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchCooperativeKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups using indirect arguments.
    /// 
    /// @details
    ///     - The launch arguments need to be device visible.
    ///     - The launch arguments buffer may not be reused until the function has
    ///       completed on the device.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchKernelIndirect(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchArgumentsBuffer,    ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchKernelIndirect(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchKernelIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch multiple kernels over one or more work groups using an array of
    ///        indirect arguments.
    /// 
    /// @details
    ///     - The array of launch arguments need to be device visible.
    ///     - The array of launch arguments buffer may not be reused until the
    ///       kernel has completed on the device.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendLaunchMultipleKernelsIndirect(
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        Kernel** ppKernels,                             ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less-than or equal-to
                                                        ///< numKernels
        const group_count_t* pLaunchArgumentsBuffer,    ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_kernel_handle_t> hKernels;
        hKernels.resize( 0 );
        hKernels.reserve( numKernels );
        for( uint32_t i = 0; i < numKernels; ++i )
            hKernels.emplace_back( reinterpret_cast<ze_kernel_handle_t>( ppKernels[ i ]->getHandle() ) );

        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchMultipleKernelsIndirect(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numKernels,
            hKernels.data(),
            pCountBuffer,
            reinterpret_cast<const ze_group_count_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchMultipleKernelsIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes memory resident for the device.
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::MakeMemoryResident(
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceMakeMemoryResident(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::MakeMemoryResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows memory to be evicted from the device.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the memory before it is evicted
    ///     - Memory is always implicitly evicted if it is resident when freed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::EvictMemory(
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceEvictMemory(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::EvictMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes image resident for the device.
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::MakeImageResident(
        Image* pImage                                   ///< [in] pointer to image to make resident
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceMakeImageResident(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::MakeImageResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows image to be evicted from the device.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the memory before it is evicted
    ///     - An image is always implicitly evicted if it is resident when
    ///       destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::EvictImage(
        Image* pImage                                   ///< [in] pointer to image to make evict
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceEvictImage(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::EvictImage" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    Sampler::Sampler( 
        sampler_handle_t handle,                        ///< [in] handle of the sample object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] sampler descriptor
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates sampler object.
    /// 
    /// @details
    ///     - The sampler can only be used on the device on which it was created.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Sampler*: handle of the sampler
    /// 
    /// @throws result_t
    Sampler* __zecall
    Sampler::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to sampler descriptor
        )
    {
        ze_sampler_handle_t hSampler;

        auto result = static_cast<result_t>( ::zeSamplerCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_sampler_desc_t*>( desc ),
            &hSampler ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Sampler::Create" );

        Sampler* pSampler = nullptr;

        try
        {
            pSampler = new Sampler( reinterpret_cast<sampler_handle_t>( hSampler ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pSampler;
            pSampler = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Sampler::Create" );
        }

        return pSampler;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys sampler object
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the sampler before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this module
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same sampler handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sampler::Destroy(
        Sampler* pSampler                               ///< [in][release] pointer to the sampler
        )
    {
        auto result = static_cast<result_t>( ::zeSamplerDestroy(
            reinterpret_cast<ze_sampler_handle_t>( pSampler->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Sampler::Destroy" );

        delete pSampler;
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_mem_handle_t to std::string
    std::string to_string( const ipc_mem_handle_t val )
    {
        std::string str;
        
        str += "ipc_mem_handle_t::data : ";
        str += val.data;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_event_pool_handle_t to std::string
    std::string to_string( const ipc_event_pool_handle_t val )
    {
        std::string str;
        
        str += "ipc_event_pool_handle_t::data : ";
        str += val.data;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts result_t to std::string
    std::string to_string( const result_t val )
    {
        std::string str;

        switch( val )
        {
        case result_t::SUCCESS:
            str = "result_t::SUCCESS";
            break;

        case result_t::NOT_READY:
            str = "result_t::NOT_READY";
            break;

        case result_t::ERROR_DEVICE_LOST:
            str = "result_t::ERROR_DEVICE_LOST";
            break;

        case result_t::ERROR_OUT_OF_HOST_MEMORY:
            str = "result_t::ERROR_OUT_OF_HOST_MEMORY";
            break;

        case result_t::ERROR_OUT_OF_DEVICE_MEMORY:
            str = "result_t::ERROR_OUT_OF_DEVICE_MEMORY";
            break;

        case result_t::ERROR_MODULE_BUILD_FAILURE:
            str = "result_t::ERROR_MODULE_BUILD_FAILURE";
            break;

        case result_t::ERROR_INSUFFICIENT_PERMISSIONS:
            str = "result_t::ERROR_INSUFFICIENT_PERMISSIONS";
            break;

        case result_t::ERROR_NOT_AVAILABLE:
            str = "result_t::ERROR_NOT_AVAILABLE";
            break;

        case result_t::ERROR_UNINITIALIZED:
            str = "result_t::ERROR_UNINITIALIZED";
            break;

        case result_t::ERROR_UNSUPPORTED_VERSION:
            str = "result_t::ERROR_UNSUPPORTED_VERSION";
            break;

        case result_t::ERROR_UNSUPPORTED_FEATURE:
            str = "result_t::ERROR_UNSUPPORTED_FEATURE";
            break;

        case result_t::ERROR_INVALID_ARGUMENT:
            str = "result_t::ERROR_INVALID_ARGUMENT";
            break;

        case result_t::ERROR_INVALID_NULL_HANDLE:
            str = "result_t::ERROR_INVALID_NULL_HANDLE";
            break;

        case result_t::ERROR_HANDLE_OBJECT_IN_USE:
            str = "result_t::ERROR_HANDLE_OBJECT_IN_USE";
            break;

        case result_t::ERROR_INVALID_NULL_POINTER:
            str = "result_t::ERROR_INVALID_NULL_POINTER";
            break;

        case result_t::ERROR_INVALID_SIZE:
            str = "result_t::ERROR_INVALID_SIZE";
            break;

        case result_t::ERROR_UNSUPPORTED_SIZE:
            str = "result_t::ERROR_UNSUPPORTED_SIZE";
            break;

        case result_t::ERROR_UNSUPPORTED_ALIGNMENT:
            str = "result_t::ERROR_UNSUPPORTED_ALIGNMENT";
            break;

        case result_t::ERROR_INVALID_SYNCHRONIZATION_OBJECT:
            str = "result_t::ERROR_INVALID_SYNCHRONIZATION_OBJECT";
            break;

        case result_t::ERROR_INVALID_ENUMERATION:
            str = "result_t::ERROR_INVALID_ENUMERATION";
            break;

        case result_t::ERROR_UNSUPPORTED_ENUMERATION:
            str = "result_t::ERROR_UNSUPPORTED_ENUMERATION";
            break;

        case result_t::ERROR_UNSUPPORTED_IMAGE_FORMAT:
            str = "result_t::ERROR_UNSUPPORTED_IMAGE_FORMAT";
            break;

        case result_t::ERROR_INVALID_NATIVE_BINARY:
            str = "result_t::ERROR_INVALID_NATIVE_BINARY";
            break;

        case result_t::ERROR_INVALID_GLOBAL_NAME:
            str = "result_t::ERROR_INVALID_GLOBAL_NAME";
            break;

        case result_t::ERROR_INVALID_KERNEL_NAME:
            str = "result_t::ERROR_INVALID_KERNEL_NAME";
            break;

        case result_t::ERROR_INVALID_FUNCTION_NAME:
            str = "result_t::ERROR_INVALID_FUNCTION_NAME";
            break;

        case result_t::ERROR_INVALID_GROUP_SIZE_DIMENSION:
            str = "result_t::ERROR_INVALID_GROUP_SIZE_DIMENSION";
            break;

        case result_t::ERROR_INVALID_GLOBAL_WIDTH_DIMENSION:
            str = "result_t::ERROR_INVALID_GLOBAL_WIDTH_DIMENSION";
            break;

        case result_t::ERROR_INVALID_KERNEL_ARGUMENT_INDEX:
            str = "result_t::ERROR_INVALID_KERNEL_ARGUMENT_INDEX";
            break;

        case result_t::ERROR_INVALID_KERNEL_ARGUMENT_SIZE:
            str = "result_t::ERROR_INVALID_KERNEL_ARGUMENT_SIZE";
            break;

        case result_t::ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE:
            str = "result_t::ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE";
            break;

        case result_t::ERROR_INVALID_COMMAND_LIST_TYPE:
            str = "result_t::ERROR_INVALID_COMMAND_LIST_TYPE";
            break;

        case result_t::ERROR_OVERLAPPING_REGIONS:
            str = "result_t::ERROR_OVERLAPPING_REGIONS";
            break;

        case result_t::ERROR_UNKNOWN:
            str = "result_t::ERROR_UNKNOWN";
            break;

        default:
            str = "result_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flag_t to std::string
    std::string to_string( const init_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(init_flag_t::GPU_ONLY) & bits )
            str += "GPU_ONLY | ";

        return ( str.size() > 3 ) 
            ? "init_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "init_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts driver_uuid_t to std::string
    std::string to_string( const driver_uuid_t val )
    {
        std::string str;
        
        str += "driver_uuid_t::id : ";
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
    /// @brief Converts Driver::properties_version_t to std::string
    std::string to_string( const Driver::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::properties_version_t::_1_0:
            str = "Driver::properties_version_t::_1_0";
            break;

        default:
            str = "Driver::properties_version_t::?";
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
        case Driver::ipc_properties_version_t::_1_0:
            str = "Driver::ipc_properties_version_t::_1_0";
            break;

        default:
            str = "Driver::ipc_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::device_mem_alloc_desc_version_t::_1_0:
            str = "Driver::device_mem_alloc_desc_version_t::_1_0";
            break;

        default:
            str = "Driver::device_mem_alloc_desc_version_t::?";
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
    /// @brief Converts Driver::host_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::host_mem_alloc_desc_version_t::_1_0:
            str = "Driver::host_mem_alloc_desc_version_t::_1_0";
            break;

        default:
            str = "Driver::host_mem_alloc_desc_version_t::?";
            break;
        };

        return str;
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
        case Driver::memory_allocation_properties_version_t::_1_0:
            str = "Driver::memory_allocation_properties_version_t::_1_0";
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
    /// @brief Converts Driver::properties_t to std::string
    std::string to_string( const Driver::properties_t val )
    {
        std::string str;
        
        str += "Driver::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::properties_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "Driver::properties_t::driverVersion : ";
        str += std::to_string(val.driverVersion);
        str += "\n";

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
    /// @brief Converts Driver::device_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_t val )
    {
        std::string str;
        
        str += "Driver::device_mem_alloc_desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::device_mem_alloc_desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Driver::device_mem_alloc_desc_t::ordinal : ";
        str += std::to_string(val.ordinal);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_t val )
    {
        std::string str;
        
        str += "Driver::host_mem_alloc_desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::host_mem_alloc_desc_t::flags : ";
        str += to_string(val.flags);
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
        case Device::properties_version_t::_1_0:
            str = "Device::properties_version_t::_1_0";
            break;

        default:
            str = "Device::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::type_t to std::string
    std::string to_string( const Device::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::type_t::GPU:
            str = "Device::type_t::GPU";
            break;

        case Device::type_t::FPGA:
            str = "Device::type_t::FPGA";
            break;

        default:
            str = "Device::type_t::?";
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
        case Device::compute_properties_version_t::_1_0:
            str = "Device::compute_properties_version_t::_1_0";
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
        case Device::kernel_properties_version_t::_1_0:
            str = "Device::kernel_properties_version_t::_1_0";
            break;

        default:
            str = "Device::kernel_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::fp_capabilities_t to std::string
    std::string to_string( const Device::fp_capabilities_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "FP_CAPS_NONE   ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_DENORM) & bits )
            str += "FP_CAPS_DENORM | ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_INF_NAN) & bits )
            str += "FP_CAPS_INF_NAN | ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_ROUND_TO_NEAREST) & bits )
            str += "FP_CAPS_ROUND_TO_NEAREST | ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_ROUND_TO_ZERO) & bits )
            str += "FP_CAPS_ROUND_TO_ZERO | ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_ROUND_TO_INF) & bits )
            str += "FP_CAPS_ROUND_TO_INF | ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_FMA) & bits )
            str += "FP_CAPS_FMA | ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_ROUNDED_DIVIDE_SQRT) & bits )
            str += "FP_CAPS_ROUNDED_DIVIDE_SQRT | ";
        
        if( static_cast<uint32_t>(Device::fp_capabilities_t::FP_CAPS_SOFT_FLOAT) & bits )
            str += "FP_CAPS_SOFT_FLOAT | ";

        return ( str.size() > 3 ) 
            ? "Device::fp_capabilities_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::fp_capabilities_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::command_queue_group_properties_version_t to std::string
    std::string to_string( const Device::command_queue_group_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::command_queue_group_properties_version_t::_1_0:
            str = "Device::command_queue_group_properties_version_t::_1_0";
            break;

        default:
            str = "Device::command_queue_group_properties_version_t::?";
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
        case Device::memory_properties_version_t::_1_0:
            str = "Device::memory_properties_version_t::_1_0";
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
        case Device::memory_access_properties_version_t::_1_0:
            str = "Device::memory_access_properties_version_t::_1_0";
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
        case Device::cache_properties_version_t::_1_0:
            str = "Device::cache_properties_version_t::_1_0";
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
        case Device::image_properties_version_t::_1_0:
            str = "Device::image_properties_version_t::_1_0";
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
        case Device::p2p_properties_version_t::_1_0:
            str = "Device::p2p_properties_version_t::_1_0";
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
        
        str += "Device::properties_t::maxHardwareContexts : ";
        str += std::to_string(val.maxHardwareContexts);
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
        
        str += "Device::properties_t::numSlices : ";
        str += std::to_string(val.numSlices);
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
    /// @brief Converts Device::native_kernel_uuid_t to std::string
    std::string to_string( const Device::native_kernel_uuid_t val )
    {
        std::string str;
        
        str += "Device::native_kernel_uuid_t::id : ";
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
        
        str += "Device::kernel_properties_t::nativeKernelSupported : ";
        str += to_string(val.nativeKernelSupported);
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
        
        str += "Device::kernel_properties_t::halfFpCapabilities : ";
        str += to_string(val.halfFpCapabilities);
        str += "\n";
        
        str += "Device::kernel_properties_t::singleFpCapabilities : ";
        str += to_string(val.singleFpCapabilities);
        str += "\n";
        
        str += "Device::kernel_properties_t::doubleFpCapabilities : ";
        str += to_string(val.doubleFpCapabilities);
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
    /// @brief Converts Device::command_queue_group_properties_t to std::string
    std::string to_string( const Device::command_queue_group_properties_t val )
    {
        std::string str;
        
        str += "Device::command_queue_group_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::computeSupported : ";
        str += std::to_string(val.computeSupported);
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::copySupported : ";
        str += std::to_string(val.copySupported);
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::singleSliceSupported : ";
        str += std::to_string(val.singleSliceSupported);
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::cooperativeKernelsSupported : ";
        str += std::to_string(val.cooperativeKernelsSupported);
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

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_version_t to std::string
    std::string to_string( const CommandQueue::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::desc_version_t::_1_0:
            str = "CommandQueue::desc_version_t::_1_0";
            break;

        default:
            str = "CommandQueue::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flag_t to std::string
    std::string to_string( const CommandQueue::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::SINGLE_SLICE_ONLY) & bits )
            str += "SINGLE_SLICE_ONLY | ";

        return ( str.size() > 3 ) 
            ? "CommandQueue::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "CommandQueue::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( const CommandQueue::mode_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::mode_t::DEFAULT:
            str = "CommandQueue::mode_t::DEFAULT";
            break;

        case CommandQueue::mode_t::SYNCHRONOUS:
            str = "CommandQueue::mode_t::SYNCHRONOUS";
            break;

        case CommandQueue::mode_t::ASYNCHRONOUS:
            str = "CommandQueue::mode_t::ASYNCHRONOUS";
            break;

        default:
            str = "CommandQueue::mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( const CommandQueue::priority_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::priority_t::NORMAL:
            str = "CommandQueue::priority_t::NORMAL";
            break;

        case CommandQueue::priority_t::LOW:
            str = "CommandQueue::priority_t::LOW";
            break;

        case CommandQueue::priority_t::HIGH:
            str = "CommandQueue::priority_t::HIGH";
            break;

        default:
            str = "CommandQueue::priority_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_t to std::string
    std::string to_string( const CommandQueue::desc_t val )
    {
        std::string str;
        
        str += "CommandQueue::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "CommandQueue::desc_t::ordinal : ";
        str += std::to_string(val.ordinal);
        str += "\n";
        
        str += "CommandQueue::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "CommandQueue::desc_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "CommandQueue::desc_t::priority : ";
        str += to_string(val.priority);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_version_t to std::string
    std::string to_string( const CommandList::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandList::desc_version_t::_1_0:
            str = "CommandList::desc_version_t::_1_0";
            break;

        default:
            str = "CommandList::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::flag_t to std::string
    std::string to_string( const CommandList::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(CommandList::flag_t::RELAXED_ORDERING) & bits )
            str += "RELAXED_ORDERING | ";
        
        if( static_cast<uint32_t>(CommandList::flag_t::MAXIMIZE_THROUGHPUT) & bits )
            str += "MAXIMIZE_THROUGHPUT | ";
        
        if( static_cast<uint32_t>(CommandList::flag_t::EXPLICIT_ONLY) & bits )
            str += "EXPLICIT_ONLY | ";

        return ( str.size() > 3 ) 
            ? "CommandList::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "CommandList::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::memory_advice_t to std::string
    std::string to_string( const CommandList::memory_advice_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandList::memory_advice_t::SET_READ_MOSTLY:
            str = "CommandList::memory_advice_t::SET_READ_MOSTLY";
            break;

        case CommandList::memory_advice_t::CLEAR_READ_MOSTLY:
            str = "CommandList::memory_advice_t::CLEAR_READ_MOSTLY";
            break;

        case CommandList::memory_advice_t::SET_PREFERRED_LOCATION:
            str = "CommandList::memory_advice_t::SET_PREFERRED_LOCATION";
            break;

        case CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION:
            str = "CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION";
            break;

        case CommandList::memory_advice_t::SET_ACCESSED_BY:
            str = "CommandList::memory_advice_t::SET_ACCESSED_BY";
            break;

        case CommandList::memory_advice_t::CLEAR_ACCESSED_BY:
            str = "CommandList::memory_advice_t::CLEAR_ACCESSED_BY";
            break;

        case CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY:
            str = "CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY";
            break;

        case CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY:
            str = "CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY";
            break;

        case CommandList::memory_advice_t::BIAS_CACHED:
            str = "CommandList::memory_advice_t::BIAS_CACHED";
            break;

        case CommandList::memory_advice_t::BIAS_UNCACHED:
            str = "CommandList::memory_advice_t::BIAS_UNCACHED";
            break;

        default:
            str = "CommandList::memory_advice_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_t to std::string
    std::string to_string( const CommandList::desc_t val )
    {
        std::string str;
        
        str += "CommandList::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "CommandList::desc_t::commandQueueGroupOrdinal : ";
        str += std::to_string(val.commandQueueGroupOrdinal);
        str += "\n";
        
        str += "CommandList::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::copy_region_t to std::string
    std::string to_string( const CommandList::copy_region_t val )
    {
        std::string str;
        
        str += "CommandList::copy_region_t::originX : ";
        str += std::to_string(val.originX);
        str += "\n";
        
        str += "CommandList::copy_region_t::originY : ";
        str += std::to_string(val.originY);
        str += "\n";
        
        str += "CommandList::copy_region_t::originZ : ";
        str += std::to_string(val.originZ);
        str += "\n";
        
        str += "CommandList::copy_region_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "CommandList::copy_region_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "CommandList::copy_region_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::image_region_t to std::string
    std::string to_string( const CommandList::image_region_t val )
    {
        std::string str;
        
        str += "CommandList::image_region_t::originX : ";
        str += std::to_string(val.originX);
        str += "\n";
        
        str += "CommandList::image_region_t::originY : ";
        str += std::to_string(val.originY);
        str += "\n";
        
        str += "CommandList::image_region_t::originZ : ";
        str += std::to_string(val.originZ);
        str += "\n";
        
        str += "CommandList::image_region_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "CommandList::image_region_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "CommandList::image_region_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::group_count_t to std::string
    std::string to_string( const CommandList::group_count_t val )
    {
        std::string str;
        
        str += "CommandList::group_count_t::groupCountX : ";
        str += std::to_string(val.groupCountX);
        str += "\n";
        
        str += "CommandList::group_count_t::groupCountY : ";
        str += std::to_string(val.groupCountY);
        str += "\n";
        
        str += "CommandList::group_count_t::groupCountZ : ";
        str += std::to_string(val.groupCountZ);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_version_t to std::string
    std::string to_string( const EventPool::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case EventPool::desc_version_t::_1_0:
            str = "EventPool::desc_version_t::_1_0";
            break;

        default:
            str = "EventPool::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flag_t to std::string
    std::string to_string( const EventPool::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::HOST_VISIBLE) & bits )
            str += "HOST_VISIBLE | ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::IPC) & bits )
            str += "IPC | ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::TIMESTAMP) & bits )
            str += "TIMESTAMP | ";

        return ( str.size() > 3 ) 
            ? "EventPool::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "EventPool::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::event_timestamp_type_t to std::string
    std::string to_string( const EventPool::event_timestamp_type_t val )
    {
        std::string str;

        switch( val )
        {
        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_START:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_START";
            break;

        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_END:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_END";
            break;

        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_START:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_START";
            break;

        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_END:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_END";
            break;

        default:
            str = "EventPool::event_timestamp_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_t to std::string
    std::string to_string( const EventPool::desc_t val )
    {
        std::string str;
        
        str += "EventPool::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "EventPool::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "EventPool::desc_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_version_t to std::string
    std::string to_string( const Event::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Event::desc_version_t::_1_0:
            str = "Event::desc_version_t::_1_0";
            break;

        default:
            str = "Event::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flag_t to std::string
    std::string to_string( const Event::scope_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::SUBDEVICE) & bits )
            str += "SUBDEVICE | ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::DEVICE) & bits )
            str += "DEVICE | ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::HOST) & bits )
            str += "HOST | ";

        return ( str.size() > 3 ) 
            ? "Event::scope_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Event::scope_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_t to std::string
    std::string to_string( const Event::desc_t val )
    {
        std::string str;
        
        str += "Event::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Event::desc_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Event::desc_t::signal : ";
        str += to_string(val.signal);
        str += "\n";
        
        str += "Event::desc_t::wait : ";
        str += to_string(val.wait);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_version_t to std::string
    std::string to_string( const Fence::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Fence::desc_version_t::_1_0:
            str = "Fence::desc_version_t::_1_0";
            break;

        default:
            str = "Fence::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::flag_t to std::string
    std::string to_string( const Fence::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case Fence::flag_t::NONE:
            str = "Fence::flag_t::NONE";
            break;

        default:
            str = "Fence::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_t to std::string
    std::string to_string( const Fence::desc_t val )
    {
        std::string str;
        
        str += "Fence::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Fence::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_version_t to std::string
    std::string to_string( const Image::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::desc_version_t::_1_0:
            str = "Image::desc_version_t::_1_0";
            break;

        default:
            str = "Image::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::flag_t to std::string
    std::string to_string( const Image::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(Image::flag_t::PROGRAM_READ) & bits )
            str += "PROGRAM_READ | ";
        
        if( static_cast<uint32_t>(Image::flag_t::PROGRAM_WRITE) & bits )
            str += "PROGRAM_WRITE | ";
        
        if( static_cast<uint32_t>(Image::flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Image::flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";

        return ( str.size() > 3 ) 
            ? "Image::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Image::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::type_t to std::string
    std::string to_string( const Image::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::type_t::_1D:
            str = "Image::type_t::_1D";
            break;

        case Image::type_t::_1DARRAY:
            str = "Image::type_t::_1DARRAY";
            break;

        case Image::type_t::_2D:
            str = "Image::type_t::_2D";
            break;

        case Image::type_t::_2DARRAY:
            str = "Image::type_t::_2DARRAY";
            break;

        case Image::type_t::_3D:
            str = "Image::type_t::_3D";
            break;

        case Image::type_t::BUFFER:
            str = "Image::type_t::BUFFER";
            break;

        default:
            str = "Image::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_layout_t to std::string
    std::string to_string( const Image::format_layout_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_layout_t::_8:
            str = "Image::format_layout_t::_8";
            break;

        case Image::format_layout_t::_16:
            str = "Image::format_layout_t::_16";
            break;

        case Image::format_layout_t::_32:
            str = "Image::format_layout_t::_32";
            break;

        case Image::format_layout_t::_8_8:
            str = "Image::format_layout_t::_8_8";
            break;

        case Image::format_layout_t::_8_8_8_8:
            str = "Image::format_layout_t::_8_8_8_8";
            break;

        case Image::format_layout_t::_16_16:
            str = "Image::format_layout_t::_16_16";
            break;

        case Image::format_layout_t::_16_16_16_16:
            str = "Image::format_layout_t::_16_16_16_16";
            break;

        case Image::format_layout_t::_32_32:
            str = "Image::format_layout_t::_32_32";
            break;

        case Image::format_layout_t::_32_32_32_32:
            str = "Image::format_layout_t::_32_32_32_32";
            break;

        case Image::format_layout_t::_10_10_10_2:
            str = "Image::format_layout_t::_10_10_10_2";
            break;

        case Image::format_layout_t::_11_11_10:
            str = "Image::format_layout_t::_11_11_10";
            break;

        case Image::format_layout_t::_5_6_5:
            str = "Image::format_layout_t::_5_6_5";
            break;

        case Image::format_layout_t::_5_5_5_1:
            str = "Image::format_layout_t::_5_5_5_1";
            break;

        case Image::format_layout_t::_4_4_4_4:
            str = "Image::format_layout_t::_4_4_4_4";
            break;

        case Image::format_layout_t::Y8:
            str = "Image::format_layout_t::Y8";
            break;

        case Image::format_layout_t::NV12:
            str = "Image::format_layout_t::NV12";
            break;

        case Image::format_layout_t::YUYV:
            str = "Image::format_layout_t::YUYV";
            break;

        case Image::format_layout_t::VYUY:
            str = "Image::format_layout_t::VYUY";
            break;

        case Image::format_layout_t::YVYU:
            str = "Image::format_layout_t::YVYU";
            break;

        case Image::format_layout_t::UYVY:
            str = "Image::format_layout_t::UYVY";
            break;

        case Image::format_layout_t::AYUV:
            str = "Image::format_layout_t::AYUV";
            break;

        case Image::format_layout_t::YUAV:
            str = "Image::format_layout_t::YUAV";
            break;

        case Image::format_layout_t::P010:
            str = "Image::format_layout_t::P010";
            break;

        case Image::format_layout_t::Y410:
            str = "Image::format_layout_t::Y410";
            break;

        case Image::format_layout_t::P012:
            str = "Image::format_layout_t::P012";
            break;

        case Image::format_layout_t::Y16:
            str = "Image::format_layout_t::Y16";
            break;

        case Image::format_layout_t::P016:
            str = "Image::format_layout_t::P016";
            break;

        case Image::format_layout_t::Y216:
            str = "Image::format_layout_t::Y216";
            break;

        case Image::format_layout_t::P216:
            str = "Image::format_layout_t::P216";
            break;

        case Image::format_layout_t::P416:
            str = "Image::format_layout_t::P416";
            break;

        default:
            str = "Image::format_layout_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_type_t to std::string
    std::string to_string( const Image::format_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_type_t::UINT:
            str = "Image::format_type_t::UINT";
            break;

        case Image::format_type_t::SINT:
            str = "Image::format_type_t::SINT";
            break;

        case Image::format_type_t::UNORM:
            str = "Image::format_type_t::UNORM";
            break;

        case Image::format_type_t::SNORM:
            str = "Image::format_type_t::SNORM";
            break;

        case Image::format_type_t::FLOAT:
            str = "Image::format_type_t::FLOAT";
            break;

        default:
            str = "Image::format_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_swizzle_t to std::string
    std::string to_string( const Image::format_swizzle_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_swizzle_t::R:
            str = "Image::format_swizzle_t::R";
            break;

        case Image::format_swizzle_t::G:
            str = "Image::format_swizzle_t::G";
            break;

        case Image::format_swizzle_t::B:
            str = "Image::format_swizzle_t::B";
            break;

        case Image::format_swizzle_t::A:
            str = "Image::format_swizzle_t::A";
            break;

        case Image::format_swizzle_t::_0:
            str = "Image::format_swizzle_t::_0";
            break;

        case Image::format_swizzle_t::_1:
            str = "Image::format_swizzle_t::_1";
            break;

        case Image::format_swizzle_t::X:
            str = "Image::format_swizzle_t::X";
            break;

        default:
            str = "Image::format_swizzle_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_version_t to std::string
    std::string to_string( const Image::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::properties_version_t::_1_0:
            str = "Image::properties_version_t::_1_0";
            break;

        default:
            str = "Image::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::sampler_filter_flags_t to std::string
    std::string to_string( const Image::sampler_filter_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Image::sampler_filter_flags_t::POINT) & bits )
            str += "POINT | ";
        
        if( static_cast<uint32_t>(Image::sampler_filter_flags_t::LINEAR) & bits )
            str += "LINEAR | ";

        return ( str.size() > 3 ) 
            ? "Image::sampler_filter_flags_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Image::sampler_filter_flags_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_desc_t to std::string
    std::string to_string( const Image::format_desc_t val )
    {
        std::string str;
        
        str += "Image::format_desc_t::layout : ";
        str += to_string(val.layout);
        str += "\n";
        
        str += "Image::format_desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Image::format_desc_t::x : ";
        str += to_string(val.x);
        str += "\n";
        
        str += "Image::format_desc_t::y : ";
        str += to_string(val.y);
        str += "\n";
        
        str += "Image::format_desc_t::z : ";
        str += to_string(val.z);
        str += "\n";
        
        str += "Image::format_desc_t::w : ";
        str += to_string(val.w);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_t to std::string
    std::string to_string( const Image::desc_t val )
    {
        std::string str;
        
        str += "Image::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Image::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Image::desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Image::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Image::desc_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "Image::desc_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "Image::desc_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";
        
        str += "Image::desc_t::arraylevels : ";
        str += std::to_string(val.arraylevels);
        str += "\n";
        
        str += "Image::desc_t::miplevels : ";
        str += std::to_string(val.miplevels);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_t to std::string
    std::string to_string( const Image::properties_t val )
    {
        std::string str;
        
        str += "Image::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Image::properties_t::samplerFilterFlags : ";
        str += to_string(val.samplerFilterFlags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_version_t to std::string
    std::string to_string( const Module::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::desc_version_t::_1_0:
            str = "Module::desc_version_t::_1_0";
            break;

        default:
            str = "Module::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::format_t::IL_SPIRV:
            str = "Module::format_t::IL_SPIRV";
            break;

        case Module::format_t::NATIVE:
            str = "Module::format_t::NATIVE";
            break;

        default:
            str = "Module::format_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::constants_t to std::string
    std::string to_string( const Module::constants_t val )
    {
        std::string str;
        
        str += "Module::constants_t::numConstants : ";
        str += std::to_string(val.numConstants);
        str += "\n";
        
        str += "Module::constants_t::pConstantIds : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstantIds);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::constants_t::pConstantValues : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstantValues);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val )
    {
        std::string str;
        
        str += "Module::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Module::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Module::desc_t::inputSize : ";
        str += std::to_string(val.inputSize);
        str += "\n";
        
        str += "Module::desc_t::pInputModule : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pInputModule);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::desc_t::pBuildFlags : ";
        str += val.pBuildFlags;
        str += "\n";
        
        str += "Module::desc_t::pConstants : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstants);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_version_t to std::string
    std::string to_string( const Kernel::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::desc_version_t::_1_0:
            str = "Kernel::desc_version_t::_1_0";
            break;

        default:
            str = "Kernel::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flag_t to std::string
    std::string to_string( const Kernel::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::flag_t::NONE:
            str = "Kernel::flag_t::NONE";
            break;

        case Kernel::flag_t::FORCE_RESIDENCY:
            str = "Kernel::flag_t::FORCE_RESIDENCY";
            break;

        default:
            str = "Kernel::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::attribute_t to std::string
    std::string to_string( const Kernel::attribute_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::attribute_t::KERNEL_ATTR_INDIRECT_HOST_ACCESS:
            str = "Kernel::attribute_t::KERNEL_ATTR_INDIRECT_HOST_ACCESS";
            break;

        case Kernel::attribute_t::KERNEL_ATTR_INDIRECT_DEVICE_ACCESS:
            str = "Kernel::attribute_t::KERNEL_ATTR_INDIRECT_DEVICE_ACCESS";
            break;

        case Kernel::attribute_t::KERNEL_ATTR_INDIRECT_SHARED_ACCESS:
            str = "Kernel::attribute_t::KERNEL_ATTR_INDIRECT_SHARED_ACCESS";
            break;

        case Kernel::attribute_t::KERNEL_ATTR_SOURCE_ATTRIBUTE:
            str = "Kernel::attribute_t::KERNEL_ATTR_SOURCE_ATTRIBUTE";
            break;

        default:
            str = "Kernel::attribute_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_version_t to std::string
    std::string to_string( const Kernel::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::properties_version_t::_1_0:
            str = "Kernel::properties_version_t::_1_0";
            break;

        default:
            str = "Kernel::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val )
    {
        std::string str;
        
        str += "Kernel::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Kernel::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Kernel::desc_t::pKernelName : ";
        str += val.pKernelName;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_t to std::string
    std::string to_string( const Kernel::properties_t val )
    {
        std::string str;
        
        str += "Kernel::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Kernel::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Kernel::properties_t::numKernelArgs : ";
        str += std::to_string(val.numKernelArgs);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeX : ";
        str += std::to_string(val.requiredGroupSizeX);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeY : ";
        str += std::to_string(val.requiredGroupSizeY);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeZ : ";
        str += std::to_string(val.requiredGroupSizeZ);
        str += "\n";
        
        str += "Kernel::properties_t::requiredNumSubGroups : ";
        str += std::to_string(val.requiredNumSubGroups);
        str += "\n";
        
        str += "Kernel::properties_t::requiredSubgroupSize : ";
        str += std::to_string(val.requiredSubgroupSize);
        str += "\n";
        
        str += "Kernel::properties_t::maxSubgroupSize : ";
        str += std::to_string(val.maxSubgroupSize);
        str += "\n";
        
        str += "Kernel::properties_t::maxNumSubgroups : ";
        str += std::to_string(val.maxNumSubgroups);
        str += "\n";
        
        str += "Kernel::properties_t::localMemSize : ";
        str += std::to_string(val.localMemSize);
        str += "\n";
        
        str += "Kernel::properties_t::privateMemSize : ";
        str += std::to_string(val.privateMemSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_version_t to std::string
    std::string to_string( const Sampler::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::desc_version_t::_1_0:
            str = "Sampler::desc_version_t::_1_0";
            break;

        default:
            str = "Sampler::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::address_mode_t to std::string
    std::string to_string( const Sampler::address_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::address_mode_t::NONE:
            str = "Sampler::address_mode_t::NONE";
            break;

        case Sampler::address_mode_t::REPEAT:
            str = "Sampler::address_mode_t::REPEAT";
            break;

        case Sampler::address_mode_t::CLAMP:
            str = "Sampler::address_mode_t::CLAMP";
            break;

        case Sampler::address_mode_t::CLAMP_TO_BORDER:
            str = "Sampler::address_mode_t::CLAMP_TO_BORDER";
            break;

        case Sampler::address_mode_t::MIRROR:
            str = "Sampler::address_mode_t::MIRROR";
            break;

        default:
            str = "Sampler::address_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::filter_mode_t to std::string
    std::string to_string( const Sampler::filter_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::filter_mode_t::NEAREST:
            str = "Sampler::filter_mode_t::NEAREST";
            break;

        case Sampler::filter_mode_t::LINEAR:
            str = "Sampler::filter_mode_t::LINEAR";
            break;

        default:
            str = "Sampler::filter_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_t to std::string
    std::string to_string( const Sampler::desc_t val )
    {
        std::string str;
        
        str += "Sampler::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Sampler::desc_t::addressMode : ";
        str += to_string(val.addressMode);
        str += "\n";
        
        str += "Sampler::desc_t::filterMode : ";
        str += to_string(val.filterMode);
        str += "\n";
        
        str += "Sampler::desc_t::isNormalized : ";
        str += std::to_string(val.isNormalized);
        str += "\n";

        return str;
    }

} // namespace ze
