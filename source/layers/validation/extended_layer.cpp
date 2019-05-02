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
* @file extended_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/layer_val.cpp.mako
* @endcond
*
******************************************************************************/
#include "xex_api.h"
#include "layer.h"

xex_apitable_t xex_apitable = {};

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercepts function pointer table for loaded driver
bool xexIntercept(
    xex_apitable_t* original ) ///< [in] pointer to table of xex API function pointers
{
    if(nullptr == original)
        return false;

    if( nullptr == original->pfnCommandGraphCreate )
        return false;
    xex_apitable.pfnCommandGraphCreate                                   = original->pfnCommandGraphCreate;
    original->pfnCommandGraphCreate                                      = xexCommandGraphCreate;

    if( nullptr == original->pfnCommandGraphDestroy )
        return false;
    xex_apitable.pfnCommandGraphDestroy                                  = original->pfnCommandGraphDestroy;
    original->pfnCommandGraphDestroy                                     = xexCommandGraphDestroy;

    if( nullptr == original->pfnCommandGraphClose )
        return false;
    xex_apitable.pfnCommandGraphClose                                    = original->pfnCommandGraphClose;
    original->pfnCommandGraphClose                                       = xexCommandGraphClose;

    return true;
}


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xexCommandGraphCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
    xex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
    )
{
    if( nullptr == xex_apitable.pfnCommandGraphCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandGraph ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xex_apitable.pfnCommandGraphCreate( hDevice, desc, phCommandGraph );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xexCommandGraphDestroy(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to destroy
    )
{
    if( nullptr == xex_apitable.pfnCommandGraphDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandGraph ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xex_apitable.pfnCommandGraphDestroy( hCommandGraph );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xexCommandGraphClose(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    )
{
    if( nullptr == xex_apitable.pfnCommandGraphClose )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandGraph ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xex_apitable.pfnCommandGraphClose( hCommandGraph );
}

#if defined(__cplusplus)
};
#endif
