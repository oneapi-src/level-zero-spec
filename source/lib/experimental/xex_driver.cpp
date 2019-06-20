/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_driver.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/driver.yml
 * @endcond
 *
 */
#include "xex_lib.h"

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
xexInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto result = xex_lib::context.Init();
    if( XE_RESULT_SUCCESS != result )
        return result;

    auto pfnInit = xex_lib::context.ddiTable.Global.pfnInit;
    if( nullptr == pfnInit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnInit( flags );
}

} // extern "C"

namespace xex
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
        xe::init_flag_t flags                           ///< [in] initialization flags
        )
    {
        auto result = static_cast<result_t>( ::xexInit(
            static_cast<xe_init_flag_t>( flags ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xex::::Init" );
    }

} // namespace xex

namespace xex
{
} // namespace xex
