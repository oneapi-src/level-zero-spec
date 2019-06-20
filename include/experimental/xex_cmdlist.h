/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_cmdlist.h
 *
 * @brief Intel 'One API' Level-Zero Experimental APIs for Command List
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/cmdlist.yml
 * @endcond
 *
 */
#ifndef _XEX_CMDLIST_H
#define _XEX_CMDLIST_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XEX_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Reserve a section of contiguous command buffer space within the
///        command list.
/// 
/// @details
///     - The pointer returned is valid for both Host and device access.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == ptr
///         + 0 for size
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xexCommandListReserveSpace(
    xex_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XEX_CMDLIST_H
