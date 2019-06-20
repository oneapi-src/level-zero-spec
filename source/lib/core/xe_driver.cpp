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
///        API function.
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
/// @brief Returns the current version of the installed driver for the specified
///        device group.
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
///         + nullptr == hDeviceGroup
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetDriverVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
    uint32_t* version                               ///< [out] driver version
    )
{
    auto pfnGetDriverVersion = xe_lib::context.ddiTable.DeviceGroup.pfnGetDriverVersion;
    if( nullptr == pfnGetDriverVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDriverVersion( hDeviceGroup, version );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize the 'One API' driver and must be called before any other
    ///        API function.
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
    /// @brief Returns the current version of the installed driver for the specified
    ///        device group.
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
    DeviceGroup::GetDriverVersion(
        void
        )
    {
        uint32_t version;

        auto result = static_cast<result_t>( ::xeDeviceGroupGetDriverVersion(
            reinterpret_cast<xe_device_group_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::DeviceGroup::GetDriverVersion" );

        return version;
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
