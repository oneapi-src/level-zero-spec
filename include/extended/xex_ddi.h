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
* @file xex_ddi.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/extended
* @endcond
*
******************************************************************************/
#ifndef _XEX_DDI_H
#define _XEX_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xex_api.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief xexCommandGraphCreate function-pointer
typedef xe_result_t (__xecall *xex_pfnCommandGraphCreate_t)(
    xe_device_handle_t,
    const xex_command_graph_desc_t*,
    xex_command_graph_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xexCommandGraphDestroy function-pointer
typedef xe_result_t (__xecall *xex_pfnCommandGraphDestroy_t)(
    xex_command_graph_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xexCommandGraphClose function-pointer
typedef xe_result_t (__xecall *xex_pfnCommandGraphClose_t)(
    xex_command_graph_handle_t
    );


///////////////////////////////////////////////////////////////////////////////
typedef struct _xex_apitable_t
{
    xex_pfnCommandGraphCreate_t                     pfnCommandGraphCreate;
    xex_pfnCommandGraphDestroy_t                    pfnCommandGraphDestroy;
    xex_pfnCommandGraphClose_t                      pfnCommandGraphClose;
} xex_apitable_t;

#endif // _XEX_DDI_H