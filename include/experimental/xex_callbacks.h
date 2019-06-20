/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_callbacks.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental
 * @endcond
 *
 */
#ifndef _XEX_CALLBACKS_H
#define _XEX_CALLBACKS_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xex_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexInit 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xex_init_params_t
{
    xe_init_flag_t* pflags;
} xex_init_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexInit 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
/// @param[in,out] ppStaticUserData Per-API user data
typedef void (__xecall *xex_pfnInitCb_t)(
    xex_init_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData,
    void** ppStaticUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _xex_global_callbacks_t
{
    xex_pfnInitCb_t                                                 pfnInitCb;
} xex_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexCommandListReserveSpace 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xex_command_list_reserve_space_params_t
{
    xex_command_list_handle_t* phCommandList;
    size_t* psize;
    void*** pptr;
} xex_command_list_reserve_space_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexCommandListReserveSpace 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
/// @param[in,out] ppStaticUserData Per-API user data
typedef void (__xecall *xex_pfnCommandListReserveSpaceCb_t)(
    xex_command_list_reserve_space_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData,
    void** ppStaticUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList callback functions pointers
typedef struct _xex_command_list_callbacks_t
{
    xex_pfnCommandListReserveSpaceCb_t                              pfnReserveSpaceCb;
} xex_command_list_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexCommandGraphCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xex_command_graph_create_params_t
{
    xe_device_handle_t* phDevice;
    const xex_command_graph_desc_t** pdesc;
    xex_command_graph_handle_t** pphCommandGraph;
} xex_command_graph_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexCommandGraphCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
/// @param[in,out] ppStaticUserData Per-API user data
typedef void (__xecall *xex_pfnCommandGraphCreateCb_t)(
    xex_command_graph_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData,
    void** ppStaticUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexCommandGraphDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xex_command_graph_destroy_params_t
{
    xex_command_graph_handle_t* phCommandGraph;
} xex_command_graph_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexCommandGraphDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
/// @param[in,out] ppStaticUserData Per-API user data
typedef void (__xecall *xex_pfnCommandGraphDestroyCb_t)(
    xex_command_graph_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData,
    void** ppStaticUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexCommandGraphClose 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xex_command_graph_close_params_t
{
    xex_command_graph_handle_t* phCommandGraph;
} xex_command_graph_close_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexCommandGraphClose 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
/// @param[in,out] ppStaticUserData Per-API user data
typedef void (__xecall *xex_pfnCommandGraphCloseCb_t)(
    xex_command_graph_close_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData,
    void** ppStaticUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandGraph callback functions pointers
typedef struct _xex_command_graph_callbacks_t
{
    xex_pfnCommandGraphCreateCb_t                                   pfnCreateCb;
    xex_pfnCommandGraphDestroyCb_t                                  pfnDestroyCb;
    xex_pfnCommandGraphCloseCb_t                                    pfnCloseCb;
} xex_command_graph_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _xex_callbacks_t
{
    xex_global_callbacks_t              Global;
    xex_command_list_callbacks_t        CommandList;
    xex_command_graph_callbacks_t       CommandGraph;
} xex_callbacks_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XEX_CALLBACKS_H