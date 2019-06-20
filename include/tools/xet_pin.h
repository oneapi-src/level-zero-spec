/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_pin.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for Program Instrumentation (PIN)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/pin.yml
 * @endcond
 *
 */
#ifndef _XET_PIN_H
#define _XET_PIN_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve all function names in the module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetModuleGetFunctionNames(
    xet_module_handle_t hModule,                    ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of names available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of names.
                                                    ///< if count is larger than the number of names available, then the driver
                                                    ///< will update the value with the correct number of names available.
    const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_profile_info_t
typedef enum _xet_profile_info_version_t
{
    XET_PROFILE_INFO_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ), ///< version 1.0

} xet_profile_info_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supportted profile features
typedef enum _xet_profile_flag_t
{
    XET_PROFILE_FLAG_REGISTER_REALLOCATION = XE_BIT(0), ///< request the compiler attempt to minimize register usage as much as
                                                    ///< possible to allow for instrumentation
    XET_PROFILE_FLAG_FREE_REGISTER_INFO = XE_BIT(1),///< request the compiler generate free register info

} xet_profile_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profiling meta-data for instrumentation
typedef struct _xet_profile_info_t
{
    xet_profile_info_version_t version;             ///< [in] ::XET_PROFILE_INFO_VERSION_CURRENT
    xet_profile_flag_t flags;                       ///< [out] indicates which flags were enabled during compilation
    uint32_t numTokens;                             ///< [out] number of tokens immediately following this structure

} xet_profile_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported profile token types
typedef enum _xet_profile_token_type_t
{
    XET_PROFILE_TOKEN_TYPE_FREE_REGISTER,           ///< GRF info

} xet_profile_token_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profile free register token detailing unused registers in the current
///        function
typedef struct _xet_profile_free_register_token_t
{
    xet_profile_token_type_t type;                  ///< [out] type of token
    uint32_t size;                                  ///< [out] total size of the token, in bytes
    uint32_t count;                                 ///< [out] number of register sequences immediately following this
                                                    ///< structure

} xet_profile_free_register_token_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profile register sequence detailing consecutive bytes, all of which
///        are unused
typedef struct _xet_profile_register_sequence_t
{
    uint32_t start;                                 ///< [out] starting byte in the register table, representing the start of
                                                    ///< unused bytes in the current function
    uint32_t count;                                 ///< [out] number of consecutive bytes in the sequence, starting from start

} xet_profile_register_sequence_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve profiling information generated for the function.
/// 
/// @details
///     - Module must be created using the following build option:
///         + "-xet-profile-flags <n>" - enable generation of profile
///           information
///         + "<n>" must be a combination of ::xet_profile_flag_t, in hex
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFunction
///         + nullptr == pInfo
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetFunctionGetProfileInfo(
    xet_function_handle_t hFunction,                ///< [in] handle to function
    xet_profile_info_t* pInfo                       ///< [out] pointer to profile info
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_PIN_H
