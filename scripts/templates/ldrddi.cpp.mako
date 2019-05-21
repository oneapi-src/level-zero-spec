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
${tbl['export']['name']}(
    %for line in th.make_param_lines(n, tags, tbl['export']):
    ${line}
    %endfor
    )
{
#ifdef _DEBUG
    if( nullptr == ptable )
        return ${X}_RESULT_ERROR_INVALID_ARGUMENT;

    if( ${x}_loader::loader.version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED;
#endif

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : ${x}_loader::loader.drivers )
    {
        if( ${X}_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR( drv.handle, "${tbl['export']['name']}") );
            result = getTable( version, &drv.${n}DdiTable.${tbl['name']} );
        }

        // If the validation layer is enabled, then intercept the device-driver DDI tables
        if(( ${X}_RESULT_SUCCESS == result ) && ( nullptr != ${x}_loader::loader.validationLayer ))
        {
            static auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(${x}_loader::loader.validationLayer, "${tbl['export']['name']}") );
            result = getTable( version, &drv.${n}DdiTable.${tbl['name']} );
        }
    }

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
    %if re.match(r"Global.*", th.get_table_name(n, tags, obj)):
    // global functions need to be handled manually by the loader
    auto result = ${x}_loader::loader.${th.make_func_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );

    %else:
    %for line in th.make_loader_prologue_lines(n, tags, obj, meta):
    ${line}
    %endfor
    // forward to device-driver
    auto result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );

    %for line in th.make_loader_epilogue_lines(n, tags, obj, meta):
    ${line}
    %endfor
    %endif
    return result;
}
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif
%endfor
#if defined(__cplusplus)
};
#endif
