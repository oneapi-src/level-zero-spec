/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_driver.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/driver.yml
 * @endcond
 *
 */
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the 'One API' driver and must be called before any other
///        API function
/// 
/// @details
///     - If this function is not called then all other functions will return
///       ::XE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of a driver per process will be initialized.
///     - This function is thread-safe for scenarios where multiple libraries
///       may initialize the driver simultaneously.
/// 
/// @remarks
///   _Analogues_
///     - **cuInit**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
xe_result_t __xecall
xeInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto result = xe_lib::context.Init();
    if( XE_RESULT_SUCCESS != result )
        return result;

    auto pfnInit = xe_lib::context.ddiTable.Global.pfnInit;
    if( nullptr == pfnInit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnInit( flags );
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeGetDrivers(
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
    auto pfnGetDrivers = xe_lib::context.ddiTable.Global.pfnGetDrivers;
    if( nullptr == pfnGetDrivers )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDrivers( pCount, phDrivers );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the driver version for the specified driver
/// 
/// @details
///     - The driver version is a non-zero, monotonically increasing value where
///       higher values always indicate a more recent version.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDriverGetVersion**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetDriverVersion(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* version                               ///< [out] driver version
    )
{
    auto pfnGetDriverVersion = xe_lib::context.ddiTable.Driver.pfnGetDriverVersion;
    if( nullptr == pfnGetDriverVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDriverVersion( hDriver, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the specified driver
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
///         + nullptr == hDrivers
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetApiVersion(
    xe_driver_handle_t hDrivers,                    ///< [in] handle of the driver instance
    xe_api_version_t* version                       ///< [out] api version
    )
{
    auto pfnGetApiVersion = xe_lib::context.ddiTable.Driver.pfnGetApiVersion;
    if( nullptr == pfnGetApiVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetApiVersion( hDrivers, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves IPC attributes of the driver
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
///         + nullptr == hDriver
///         + nullptr == pIPCProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetIPCProperties(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    xe_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
    )
{
    auto pfnGetIPCProperties = xe_lib::context.ddiTable.Driver.pfnGetIPCProperties;
    if( nullptr == pfnGetIPCProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetIPCProperties( hDriver, pIPCProperties );
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDriverGetDevices(
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
    auto pfnGetDevices = xe_lib::context.ddiTable.Driver.pfnGetDevices;
    if( nullptr == pfnGetDevices )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDevices( hDriver, pCount, phDevices );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize the 'One API' driver and must be called before any other
    ///        API function
    /// 
    /// @details
    ///     - If this function is not called then all other functions will return
    ///       ::XE_RESULT_ERROR_UNINITIALIZED.
    ///     - Only one instance of a driver per process will be initialized.
    ///     - This function is thread-safe for scenarios where multiple libraries
    ///       may initialize the driver simultaneously.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuInit**
    /// 
    /// @throws result_t
    void __xecall
    Init(
        init_flag_t flags                               ///< [in] initialization flags
        )
    {
        auto result = static_cast<result_t>( ::xeInit(
            static_cast<xe_init_flag_t>( flags ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::::Init" );
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
    void __xecall
    GetDrivers(
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
        thread_local std::vector<xe_driver_handle_t> hDrivers;
        hDrivers.resize( ( ppDrivers ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xeGetDrivers(
            pCount,
            hDrivers.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::::GetDrivers" );

        for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
            ppDrivers[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
                ppDrivers[ i ] = xe_lib::context.driverFactory.getInstance( reinterpret_cast<driver_handle_t>( hDrivers[ i ] ) );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::::GetDrivers" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the driver version for the specified driver
    /// 
    /// @details
    ///     - The driver version is a non-zero, monotonically increasing value where
    ///       higher values always indicate a more recent version.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDriverGetVersion**
    /// 
    /// @returns
    ///     - uint32_t: driver version
    /// 
    /// @throws result_t
    uint32_t __xecall
    Driver::GetDriverVersion(
        void
        )
    {
        uint32_t version;

        auto result = static_cast<result_t>( ::xeDriverGetDriverVersion(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::GetDriverVersion" );

        return version;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the API version supported by the specified driver
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
    Driver::api_version_t __xecall
    Driver::GetApiVersion(
        void
        )
    {
        xe_api_version_t version;

        auto result = static_cast<result_t>( ::xeDriverGetApiVersion(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::GetApiVersion" );

        return *reinterpret_cast<api_version_t*>( &version );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves IPC attributes of the driver
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
    ///     - ipc_properties_t: query result for IPC properties
    /// 
    /// @throws result_t
    Driver::ipc_properties_t __xecall
    Driver::GetIPCProperties(
        void
        )
    {
        xe_driver_ipc_properties_t iPCProperties;

        auto result = static_cast<result_t>( ::xeDriverGetIPCProperties(
            reinterpret_cast<xe_driver_handle_t>( getHandle() ),
            &iPCProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::GetIPCProperties" );

        return *reinterpret_cast<ipc_properties_t*>( &iPCProperties );
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
    void __xecall
    Driver::GetDevices(
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
        thread_local std::vector<xe_device_handle_t> hDevices;
        hDevices.resize( ( ppDevices ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::xeDriverGetDevices(
            reinterpret_cast<xe_driver_handle_t>( pDriver->getHandle() ),
            pCount,
            hDevices.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Driver::GetDevices" );

        for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
            ppDevices[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
                ppDevices[ i ] = xe_lib::context.deviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevices[ i ] ), pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Driver::GetDevices" );
        }
    }

} // namespace xe

namespace xe
{
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

} // namespace xe
