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
* DO NOT EDIT: generated from /scripts/templates/layer.cpp.mako
* @endcond
*
******************************************************************************/
#include "extended_layer.h"

namespace xe_layer
{
    extern context_t context;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Loads function pointer table for loaded driver
    bool xexIntercept(
        xexapi_pfntable_ptr_t pfntable )   ///< [in] pointer to table of xex API function pointers
    {
        if((nullptr == context.xexapi) || (nullptr == pfntable))
            return false;

        context.xexapi->xexCommandGraphCreate                                       = pfntable->xexCommandGraphCreate;
        pfntable->xexCommandGraphCreate                                             = xexCommandGraphCreate;

        context.xexapi->xexCommandGraphDestroy                                      = pfntable->xexCommandGraphDestroy;
        pfntable->xexCommandGraphDestroy                                            = xexCommandGraphDestroy;

        context.xexapi->xexCommandGraphClose                                        = pfntable->xexCommandGraphClose;
        pfntable->xexCommandGraphClose                                              = xexCommandGraphClose;


        return true;
    }

} // namespace xe_layer


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xexCommandGraphCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
        xex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandGraph ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xexapi->xexCommandGraphCreate(hDevice, desc, phCommandGraph);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xexCommandGraphDestroy(
        xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to destroy
    ){
    // Check parameters
    if( nullptr == hCommandGraph ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xexapi->xexCommandGraphDestroy(hCommandGraph);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xexCommandGraphClose(
        xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    ){
    // Check parameters
    if( nullptr == hCommandGraph ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xexapi->xexCommandGraphClose(hCommandGraph);
}

#if defined(__cplusplus)
};
#endif
