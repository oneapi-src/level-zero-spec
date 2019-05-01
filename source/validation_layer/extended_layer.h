/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
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
* @endcond
*
* @file extended_layer.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/layer.h.mako
* @endcond
*
******************************************************************************/
#ifndef _EXTENDED_LAYER_H
#define _EXTENDED_LAYER_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xex_all.h"
#include "layer.h"

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xexCommandGraphCreate_t)(
    xe_device_handle_t,
    const xex_command_graph_desc_t*,
    xex_command_graph_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xexCommandGraphDestroy_t)(
    xex_command_graph_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xexCommandGraphClose_t)(
    xex_command_graph_handle_t
    );


///////////////////////////////////////////////////////////////////////////////
typedef struct _xexapi_pfntable_t
{
    pfn_xexCommandGraphCreate_t                                     xexCommandGraphCreate;
    pfn_xexCommandGraphDestroy_t                                    xexCommandGraphDestroy;
    pfn_xexCommandGraphClose_t                                      xexCommandGraphClose;
} xexapi_pfntable_t;


namespace xe_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    bool xexIntercept(
        xexapi_pfntable_t* );  ///< [in] pointer to table of xex API function pointers

} // namespace xe_layer

#endif // _EXTENDED_LAYER_H
