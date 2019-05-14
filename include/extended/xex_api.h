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
* @file xex_api.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/extended
* @endcond
*
******************************************************************************/
#ifndef _XEX_API_H
#define _XEX_API_H
#if defined(__cplusplus)
#pragma once
#endif

#include "xex_device.h"
#include "xex_cmdgraph.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandGraph functions pointers
typedef struct _xex_command_graph_apitable_t
{
    xex_pfnCommandGraphCreate_t                                 pfnCreate;
    xex_pfnCommandGraphDestroy_t                                pfnDestroy;
    xex_pfnCommandGraphClose_t                                  pfnClose;
} xex_command_graph_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandGraph table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xexGetCommandGraphProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xex_command_graph_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xexGetCommandGraphProcAddrTable
typedef xe_result_t (__xecall *xex_pfnGetCommandGraphProcAddrTable_t)(
    uint32_t,
    xex_command_graph_apitable_t*
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XEX_API_H