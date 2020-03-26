/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_api.h
 *
 */
#ifndef _ZEX_API_H
#define _ZEX_API_H
#if defined(__cplusplus)
#pragma once
#endif

// 'core' API headers
#include "ze_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

#pragma region common
///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of command list object
typedef ze_command_list_handle_t zex_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command graph object
typedef struct _zex_command_graph_handle_t *zex_command_graph_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare zex_command_graph_desc_t
typedef struct _zex_command_graph_desc_t zex_command_graph_desc_t;


#pragma endregion
#pragma region cmdlist
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
__ze_api_export ze_result_t __zecall
zexCommandListReserveSpace(
    zex_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    );

#pragma endregion
#pragma region cmdgraph
///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zex_command_graph_desc_t
typedef enum _zex_command_graph_desc_version_t
{
    ZEX_COMMAND_GRAPH_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

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
__ze_api_export ze_result_t __zecall
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
__ze_api_export ze_result_t __zecall
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
__ze_api_export ze_result_t __zecall
zexCommandGraphClose(
    zex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    );

#pragma endregion
#pragma region callbacks
///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zexCommandListReserveSpace 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zex_command_list_reserve_space_params_t
{
    zex_command_list_handle_t* phCommandList;
    size_t* psize;
    void*** pptr;
} zex_command_list_reserve_space_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zexCommandListReserveSpace 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zex_pfnCommandListReserveSpaceCb_t)(
    zex_command_list_reserve_space_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList callback functions pointers
typedef struct _zex_command_list_callbacks_t
{
    zex_pfnCommandListReserveSpaceCb_t                              pfnReserveSpaceCb;
} zex_command_list_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zexCommandGraphCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zex_command_graph_create_params_t
{
    ze_device_handle_t* phDevice;
    const zex_command_graph_desc_t** pdesc;
    zex_command_graph_handle_t** pphCommandGraph;
} zex_command_graph_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zexCommandGraphCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zex_pfnCommandGraphCreateCb_t)(
    zex_command_graph_create_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zexCommandGraphDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zex_command_graph_destroy_params_t
{
    zex_command_graph_handle_t* phCommandGraph;
} zex_command_graph_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zexCommandGraphDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zex_pfnCommandGraphDestroyCb_t)(
    zex_command_graph_destroy_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zexCommandGraphClose 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zex_command_graph_close_params_t
{
    zex_command_graph_handle_t* phCommandGraph;
} zex_command_graph_close_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zexCommandGraphClose 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zex_pfnCommandGraphCloseCb_t)(
    zex_command_graph_close_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandGraph callback functions pointers
typedef struct _zex_command_graph_callbacks_t
{
    zex_pfnCommandGraphCreateCb_t                                   pfnCreateCb;
    zex_pfnCommandGraphDestroyCb_t                                  pfnDestroyCb;
    zex_pfnCommandGraphCloseCb_t                                    pfnCloseCb;
} zex_command_graph_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _zex_callbacks_t
{
    zex_command_list_callbacks_t        CommandList;
    zex_command_graph_callbacks_t       CommandGraph;
} zex_callbacks_t;

#pragma endregion

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZEX_API_H