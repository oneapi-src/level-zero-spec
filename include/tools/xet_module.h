/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_module.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for Module
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/module.yml
 * @endcond
 *
 */
#ifndef _XET_MODULE_H
#define _XET_MODULE_H
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
/// @brief Supported module debug info formats.
typedef enum _xet_module_debug_info_format_t
{
    XET_MODULE_DEBUG_INFO_FORMAT_ELF_DWARF,         ///< Format is ELF/DWARF

} xet_module_debug_info_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve debug info from module.
/// 
/// @details
///     - The caller can pass nullptr for pDebugInfo when querying only for
///       size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetModuleGetDebugInfo(
    xet_module_handle_t hModule,                    ///< [in] handle of the module
    xet_module_debug_info_format_t format,          ///< [in] debug info format requested
    size_t* pSize,                                  ///< [in,out] size of debug info in bytes
    uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_MODULE_H
