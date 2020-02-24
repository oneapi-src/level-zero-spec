/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_driver.h
 *
 * @brief Intel 'One API' Level-Zero APIs
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/driver.yml
 * @endcond
 *
 */
 
#ifndef _ZEX_DRIVER_H
#define _ZEX_DRIVER_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZEX_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

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
/// @remarks
///   _Analogues_
///     - **cuInit**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zexInit(
    ze_init_flag_t flags                            ///< [in] initialization flags
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZEX_DRIVER_H
