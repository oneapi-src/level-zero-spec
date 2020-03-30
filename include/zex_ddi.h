/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_ddi.h
 * @version v0.91-271
 *
 */
#ifndef _ZEX_DDI_H
#define _ZEX_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "zex_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zexCommandListReserveSpace 
typedef ze_result_t (__zecall *zex_pfnCommandListReserveSpace_t)(
    zex_command_list_handle_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _zex_command_list_dditable_t
{
    zex_pfnCommandListReserveSpace_t                            pfnReserveSpace;
} zex_command_list_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zexGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zex_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zexGetCommandListProcAddrTable
typedef ze_result_t (__zecall *zex_pfnGetCommandListProcAddrTable_t)(
    ze_api_version_t,
    zex_command_list_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zexCommandGraphCreate 
typedef ze_result_t (__zecall *zex_pfnCommandGraphCreate_t)(
    ze_device_handle_t,
    const zex_command_graph_desc_t*,
    zex_command_graph_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zexCommandGraphDestroy 
typedef ze_result_t (__zecall *zex_pfnCommandGraphDestroy_t)(
    zex_command_graph_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zexCommandGraphClose 
typedef ze_result_t (__zecall *zex_pfnCommandGraphClose_t)(
    zex_command_graph_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandGraph functions pointers
typedef struct _zex_command_graph_dditable_t
{
    zex_pfnCommandGraphCreate_t                                 pfnCreate;
    zex_pfnCommandGraphDestroy_t                                pfnDestroy;
    zex_pfnCommandGraphClose_t                                  pfnClose;
} zex_command_graph_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandGraph table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zexGetCommandGraphProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zex_command_graph_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zexGetCommandGraphProcAddrTable
typedef ze_result_t (__zecall *zex_pfnGetCommandGraphProcAddrTable_t)(
    ze_api_version_t,
    zex_command_graph_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _zex_dditable_t
{
    zex_command_list_dditable_t         CommandList;
    zex_command_graph_dditable_t        CommandGraph;
} zex_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZEX_DDI_H