/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_driver.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/driver.yml
 * @endcond
 *
 */
#include "ze_lib.h"

extern "C" {

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
/// @remarks
///   _Analogues_
///     - **cuInit**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zeInit(
    ze_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto result = ze_lib::context.Init();
    if( ZE_RESULT_SUCCESS != result )
        return result;

    auto pfnInit = ze_lib::context.ddiTable.Global.pfnInit;
    if( nullptr == pfnInit )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == pCount
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
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
    auto pfnGet = ze_lib::context.ddiTable.Driver.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGet( pCount, phDrivers );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == version
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverGetDriverVersion(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* version                               ///< [out] driver version
    )
{
    auto pfnGetDriverVersion = ze_lib::context.ddiTable.Driver.pfnGetDriverVersion;
    if( nullptr == pfnGetDriverVersion )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDrivers
///         + nullptr == version
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverGetApiVersion(
    ze_driver_handle_t hDrivers,                    ///< [in] handle of the driver instance
    ze_api_version_t* version                       ///< [out] api version
    )
{
    auto pfnGetApiVersion = ze_lib::context.ddiTable.Driver.pfnGetApiVersion;
    if( nullptr == pfnGetApiVersion )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pIPCProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverGetIPCProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
    )
{
    auto pfnGetIPCProperties = ze_lib::context.ddiTable.Driver.pfnGetIPCProperties;
    if( nullptr == pfnGetIPCProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetIPCProperties( hDriver, pIPCProperties );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == pFuncName
///         + nullptr == pfunc
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeDriverGetExtensionFunctionAddress(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const char* pFuncName,                          ///< [in] name of the extension function
    void** pfunc                                    ///< [out] pointer to extension function
    )
{
    auto pfnGetExtensionFunctionAddress = ze_lib::context.ddiTable.Driver.pfnGetExtensionFunctionAddress;
    if( nullptr == pfnGetExtensionFunctionAddress )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetExtensionFunctionAddress( hDriver, pFuncName, pfunc );
}

} // extern "C"

namespace ze
{
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
    /// @remarks
    ///   _Analogues_
    ///     - **cuInit**
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
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::::Init" );
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
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::Get" );

        for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
            ppDrivers[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
                ppDrivers[ i ] = ze_lib::context.driverFactory.getInstance( reinterpret_cast<driver_handle_t>( hDrivers[ i ] ) );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Driver::Get" );
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
    uint32_t __zecall
    Driver::GetDriverVersion(
        void
        )
    {
        uint32_t version;

        auto result = static_cast<result_t>( ::zeDriverGetDriverVersion(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetDriverVersion" );

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
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetApiVersion" );

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
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetIPCProperties" );

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
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetExtensionFunctionAddress" );

        return pfunc;
    }

} // namespace ze

namespace ze
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

} // namespace ze
