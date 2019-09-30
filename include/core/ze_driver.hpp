/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_driver.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/driver.yml
 * @endcond
 *
 */
#ifndef _ZE_DRIVER_HPP
#define _ZE_DRIVER_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported initialization flags
    enum class init_flag_t
    {
        NONE = 0,                                       ///< default behavior
        GPU_ONLY = ZE_BIT(0),                           ///< only initialize GPU drivers

    };

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
        );

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flag_t to std::string
    std::string to_string( const init_flag_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_DRIVER_HPP
