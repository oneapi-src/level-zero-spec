/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
* The source code contained or described herein and all documents related to the
* source code ("Material") are owned by Intel Corporation or its suppliers or
* licensors. Title to the Material remains with Intel Corporation or its suppliers
* and licensors. The Material contains trade secrets and proprietary and confidential
* information of Intel or its suppliers and licensors. The Material is protected by
* worldwide copyright and trade secret laws and treaty provisions. No part of the
* Material may be used, copied, reproduced, modified, published, uploaded, posted
* transmitted, distributed, or disclosed in any way without Intel's prior express
* written permission.
*
* No license under any patent, copyright, trade secret or other intellectual
* property right is granted to or conferred upon you by disclosure or delivery
* of the Materials, either expressly, by implication, inducement, estoppel
* or otherwise. Any license under such intellectual property rights must be
* express and approved by Intel in writing.
*
* @file xex_callbacks.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/extended
* @endcond
*
******************************************************************************/
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
typedef struct _xex_init_params_t
{
    xe_init_flag_t* pflags;
} xex_init_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexInit 
typedef void (__xecall *xex_pfnInitCb_t)(
    xex_init_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _xex_global_callbacks_t
{
    xex_pfnInitCb_t                                                 pfnInitCb;
} xex_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexCommandGraphCreate 
typedef struct _xex_command_graph_create_params_t
{
    xe_device_handle_t* phDevice;
    const xex_command_graph_desc_t** pdesc;
    xex_command_graph_handle_t** pphCommandGraph;
} xex_command_graph_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexCommandGraphCreate 
typedef void (__xecall *xex_pfnCommandGraphCreateCb_t)(
    xex_command_graph_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexCommandGraphDestroy 
typedef struct _xex_command_graph_destroy_params_t
{
    xex_command_graph_handle_t* phCommandGraph;
} xex_command_graph_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexCommandGraphDestroy 
typedef void (__xecall *xex_pfnCommandGraphDestroyCb_t)(
    xex_command_graph_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xexCommandGraphClose 
typedef struct _xex_command_graph_close_params_t
{
    xex_command_graph_handle_t* phCommandGraph;
} xex_command_graph_close_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xexCommandGraphClose 
typedef void (__xecall *xex_pfnCommandGraphCloseCb_t)(
    xex_command_graph_close_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
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
    xex_command_graph_callbacks_t       CommandGraph;
} xex_callbacks_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XEX_CALLBACKS_H