/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_cmdgraph.h
 *
 * @brief Intel 'One API' Level-Zero Experimental APIs for CommandGraph
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/cmdgraph.yml
 * @endcond
 *
 */
#ifndef _ZEX_CMDGRAPH_H
#define _ZEX_CMDGRAPH_H
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
/// @brief API version of ::zex_command_graph_desc_t
typedef enum _zex_command_graph_desc_version_t
{
    ZEX_COMMAND_GRAPH_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} zex_command_graph_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command graph creation flags
typedef enum _zex_command_graph_flag_t
{
    ZEX_COMMAND_GRAPH_FLAG_NONE = 0,                ///< default behavior

} zex_command_graph_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief CommandGraph descriptor
typedef struct _zex_command_graph_desc_t
{
    zex_command_graph_desc_version_t version;       ///< [in] ::ZEX_COMMAND_GRAPH_DESC_VERSION_CURRENT
    zex_command_graph_flag_t flags;                 ///< [in] creation flags

} zex_command_graph_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command graph on the device for submitting commands to any
///        command queue.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandGraph`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZEX_COMMAND_GRAPH_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
ze_result_t __zecall
zexCommandGraphCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const zex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
    zex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command graph.
/// 
/// @details
///     - The implementation of this function will immediately free all Host
///       allocations associated with this command graph.
///     - The application may **not** call this function from simultaneous
///       threads with the same command graph handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandGraph`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t __zecall
zexCommandGraphDestroy(
    zex_command_graph_handle_t hCommandGraph        ///< [in][release] handle of command graph object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command graph; ready to be executed by a command queue.
/// 
/// @details
///     - The command graph will optimize the execution order of the command
///       lists.
///     - A command list may **not** be reset after the command graph is closed.
///     - The application may **not** call this function from simultaneous
///       threads with the same command graph handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandGraph`
ze_result_t __zecall
zexCommandGraphClose(
    zex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZEX_CMDGRAPH_H
