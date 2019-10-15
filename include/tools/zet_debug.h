/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_debug.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for Program Debug
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/debug.yml
 * @endcond
 *
 */
#ifndef _ZET_DEBUG_H
#define _ZET_DEBUG_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug session handle
typedef struct _zet_debug_session_handle_t *zet_debug_session_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug attach flags.
typedef enum _zet_debug_attach_flags_t
{
    ZET_DEBUG_ATTACH_NONE = 0,                      ///< No attach flags

} zet_debug_attach_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Attach to a device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hDebug
///         + an invalid device handle has been supplied
///         + an invalid process identifier has been supplied
///         + an invalid flag has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + attaching to this device is not supported
///     - ::ZE_RESULT_ERROR_INSUFFICENT_PERMISSIONS
///         + caller is not authorized to debug that process
///     - ::ZE_RESULT_ERROR_DEVICE_ACCESS
///         + a debugger is already attached
ze_result_t __zecall
zetDebugAttach(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    int pid,                                        ///< [in] host process identifier
    uint64_t flags,                                 ///< [in] a bit-vector of ::zet_debug_attach_flags_t
    zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Close a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + an invalid debug handle has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Query the number of device threads for a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + an invalid debug handle has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetDebugGetNumThreads(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t numThreads                             ///< [out] the maximal number of threads
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_DEBUG_H
