<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/**************************************************************************//**
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
* @file ${name}.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.cpp.mako
* @endcond
*
******************************************************************************/
#include "${x}_loader.h"

#if defined(__cplusplus)
extern "C" {
#endif

%for tbl in th.get_pfntables(specs, meta, n, tags):
///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ${tbl['name']} table
///        with current process' addresses
///
/// @returns
///     - ::${X}_RESULT_SUCCESS
///     - ::${X}_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for ptable
///     - ::${X}_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__${x}dllexport ${x}_result_t __${x}call
${tbl['export']}(
    ${x}_api_version_t version, ///< [in] API version
    ${tbl['type']}* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return ${X}_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<${tbl['pfn']}>(
            GET_FUNCTION_PTR(context.commonDriver, "${tbl['export']}") );
        result = getTable( version, ptable );
    }

    if(( ${X}_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<${tbl['pfn']}>(
            GET_FUNCTION_PTR(context.validationLayer, "${tbl['export']}") );
        result = getTable( version, ptable );
    }

    return result;
}

%endfor
#if defined(__cplusplus)
};
#endif
