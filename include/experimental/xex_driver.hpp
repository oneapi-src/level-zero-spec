/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_driver.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/driver.yml
 * @endcond
 *
 */
#ifndef _XEX_DRIVER_HPP
#define _XEX_DRIVER_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

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
        );

} // namespace xex

namespace xex
{
} // namespace xex
#endif // defined(__cplusplus)
#endif // _XEX_DRIVER_HPP
