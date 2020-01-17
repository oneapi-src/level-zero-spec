/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_pin.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Program Instrumentation (PIN)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/pin.yml
 * @endcond
 *
 */
#include "zet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve profiling information generated for the kernel.
/// 
/// @details
///     - Module must be created using the following build option:
///         + "-zet-profile-flags <n>" - enable generation of profile
///           information
///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pInfo`
ze_result_t __zecall
zetKernelGetProfileInfo(
    zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
    zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
    )
{
    auto pfnGetProfileInfo = zet_lib::context.ddiTable.Kernel.pfnGetProfileInfo;
    if( nullptr == pfnGetProfileInfo )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProfileInfo( hKernel, pInfo );
}

} // extern "C"

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve profiling information generated for the kernel.
    /// 
    /// @details
    ///     - Module must be created using the following build option:
    ///         + "-zet-profile-flags <n>" - enable generation of profile
    ///           information
    ///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - profile_info_t: pointer to profile info
    /// 
    /// @throws result_t
    Kernel::profile_info_t __zecall
    Kernel::GetProfileInfo(
        void
        )
    {
        zet_profile_info_t info;

        auto result = static_cast<result_t>( ::zetKernelGetProfileInfo(
            reinterpret_cast<zet_kernel_handle_t>( getHandle() ),
            &info ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Kernel::GetProfileInfo" );

        return *reinterpret_cast<profile_info_t*>( &info );
    }

} // namespace zet

namespace zet
{
} // namespace zet
