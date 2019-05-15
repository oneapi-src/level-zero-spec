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
* @file xe_extended_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/validation.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_layer.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandGraph table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xexGetCommandGraphProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xex_command_graph_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xexCommandGraph.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                               = xexCommandGraphCreate;

    context.xexCommandGraph.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                              = xexCommandGraphDestroy;

    context.xexCommandGraph.pfnClose                                                = ptable->pfnClose;
    ptable->pfnClose                                                                = xexCommandGraphClose;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xexCommandGraphCreate
xe_result_t __xecall
xexCommandGraphCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
    xex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phCommandGraph )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xexCommandGraph.pfnCreate( hDevice, desc, phCommandGraph );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xexCommandGraphDestroy
xe_result_t __xecall
xexCommandGraphDestroy(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandGraph )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return context.xexCommandGraph.pfnDestroy( hCommandGraph );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xexCommandGraphClose
xe_result_t __xecall
xexCommandGraphClose(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandGraph )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return context.xexCommandGraph.pfnClose( hCommandGraph );
}

#if defined(__cplusplus)
};
#endif
