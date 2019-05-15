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
* DO NOT EDIT: generated from /scripts/templates/validation.cpp.mako
* @endcond
*
******************************************************************************/
#include "layer.h"

extern ${x}_layer context;

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
///     - ::${X}_RESULT_ERROR_INVALID_PARAMETER
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
        return ${X}_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for obj in tbl['functions']:
    %if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
    %endif
    context.${n}${tbl['name']}.${th.append_ws(th.make_pfn_name(n, tags, obj), 55)} = ptable->${th.make_pfn_name(n, tags, obj)};
    ptable->${th.append_ws(th.make_pfn_name(n, tags, obj), 56+len(n)+len(tbl['name']))} = ${th.make_func_name(n, tags, obj)};
    %if 'condition' in obj:
#endif
    %endif

    %endfor
    return result;
}

%endfor
%for obj in th.extract_objs(specs, r"function"):
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for ${th.make_func_name(n, tags, obj)}
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
${x}_result_t __${x}call
${th.make_func_name(n, tags, obj)}(
    %for line in th.make_param_lines(n, tags, obj):
    ${line}
    %endfor
    )
{
    if( context.enableParameterValidation )
    {
        %for key, values in th.make_param_checks(n, tags, obj).items():
        %for val in values:
        if( ${val} )
            return ${key};

        %endfor
        %endfor
    }

    return context.${n}${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
}
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
#if defined(__cplusplus)
};
#endif
