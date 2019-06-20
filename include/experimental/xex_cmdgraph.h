/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_cmdgraph.h
 *
 * @brief Intel 'One API' Level-Zero Experimental APIs for CommandGraph
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/cmdgraph.yml
 * @endcond
 *
 */
#ifndef _XEX_CMDGRAPH_H
#define _XEX_CMDGRAPH_H
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
/// @brief API version of ::xex_command_graph_desc_t
typedef enum _xex_command_graph_desc_version_t
{
    XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} xex_command_graph_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command graph creation flags
typedef enum _xex_command_graph_flag_t
{
    XEX_COMMAND_GRAPH_FLAG_NONE = 0,                ///< default behavior

} xex_command_graph_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief CommandGraph descriptor
typedef struct _xex_command_graph_desc_t
{
    xex_command_graph_desc_version_t version;       ///< [in] ::XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT
    xex_command_graph_flag_t flags;                 ///< [in] creation flags

} xex_command_graph_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command graph on the device for submitting commands to any
///        command queue.
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
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xexCommandGraphCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
    xex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xexCommandGraphDestroy(
    xex_command_graph_handle_t hCommandGraph        ///< [in][release] handle of command graph object to destroy
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xexCommandGraphClose(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XEX_CMDGRAPH_H
