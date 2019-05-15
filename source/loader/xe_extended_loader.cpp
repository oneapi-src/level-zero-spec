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
* @file xe_extended_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_loader.h"

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
    xe_api_version_t version,                       ///< [in] API version requested
    xex_command_graph_apitable_t* ptable            ///< [in,out] pointer to table of API function pointers
    )
{
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xexGetCommandGraphProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xexGetCommandGraphProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

#if defined(__cplusplus)
};
#endif
