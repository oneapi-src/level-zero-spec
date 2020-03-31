/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_libapi.cpp
 * @version v1.0-r0.9.277
 *
 * @brief C++ static library for zex
 *
 */
#include "ze_lib.h"

extern "C" {

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `0 == size`
ze_result_t __zecall
zexCommandListReserveSpace(
    zex_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    auto pfnReserveSpace = ze_lib::context.zexDdiTable.CommandList.pfnReserveSpace;
    if( nullptr == pfnReserveSpace )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReserveSpace( hCommandList, size, ptr );
}

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
    )
{
    auto pfnCreate = ze_lib::context.zexDdiTable.CommandGraph.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCreate( hDevice, desc, phCommandGraph );
}

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
    )
{
    auto pfnDestroy = ze_lib::context.zexDdiTable.CommandGraph.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDestroy( hCommandGraph );
}

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
    )
{
    auto pfnClose = ze_lib::context.zexDdiTable.CommandGraph.pfnClose;
    if( nullptr == pfnClose )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnClose( hCommandGraph );
}

} // extern "C"
