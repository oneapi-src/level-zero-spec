/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_driver.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 */
#ifndef _ZEX_DRIVER_HPP
#define _ZEX_DRIVER_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize the 'One API' driver and must be called before any other
    ///        API function.
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
        ze::init_flag_t flags                           ///< [in] initialization flags
        );

} // namespace zex

namespace zex
{
} // namespace zex
#endif // defined(__cplusplus)
#endif // _ZEX_DRIVER_HPP
