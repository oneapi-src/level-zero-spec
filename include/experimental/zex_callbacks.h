/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_callbacks.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental
 * @endcond
 *
 */
#ifndef _ZEX_CALLBACKS_H
#define _ZEX_CALLBACKS_H
#if defined(__cplusplus)
#pragma once
#endif
#include "zex_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zexInit 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _zex_init_params_t
{
    ze_init_flag_t* pflags;
} zex_init_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zexInit 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__zecall *zex_pfnInitCb_t)(
    zex_init_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _zex_global_callbacks_t
{
    zex_pfnInitCb_t                                                 pfnInitCb;
} zex_global_callbacks_t;

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
    zex_global_callbacks_t              Global;
    zex_command_list_callbacks_t        CommandList;
    zex_command_graph_callbacks_t       CommandGraph;
} zex_callbacks_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZEX_CALLBACKS_H