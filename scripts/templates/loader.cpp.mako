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
#include "${name}.h"

namespace xe_loader
{
    extern context_t context;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Loads function pointer table for loaded driver
    bool ${n}LoadExports(
        void* handle )  ///< [in] driver handle
    {
        if(nullptr == context.${n}api)
            return false;

        %for obj in th.extract_objs(specs, r"function"):
        %if 'condition' in obj:
        #if ${th.subt(n, tags, obj['condition'])}
        %endif
        context.${n}api->${th.append_ws(th.make_func_name(n, tags, obj), 63)} = (pfn_${th.make_func_name(n, tags, obj)}_t)LOAD_FUNCTION_PTR(handle, "${th.make_func_name(n, tags, obj)}");
        %if 'condition' in obj:
        #endif // ${th.subt(n, tags, obj['condition'])}
        %endif
        %endfor

        %for obj in th.extract_objs(specs, r"function"):
        %if 'condition' in obj:
        #if ${th.subt(n, tags, obj['condition'])}
        %endif
        if(nullptr == context.${n}api->${th.make_func_name(n, tags, obj)})
            return false;
        %if 'condition' in obj:
        #endif // ${th.subt(n, tags, obj['condition'])}
        %endif
        %endfor

        return true;
    }
} // namespace xe_loader


#if defined(__cplusplus)
extern "C" {
#endif

%for obj in th.extract_objs(specs, r"function"):
%if "Init" != obj['name']:
///////////////////////////////////////////////////////////////////////////////
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
__${x}dllexport ${x}_result_t __${x}call
${th.make_func_name(n, tags, obj)}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
    ){
    if(false == xe_loader::context.initialized)
        return ${X}_RESULT_ERROR_UNINITIALIZED;

    return xe_loader::context.${n}api->${th.make_func_name(n, tags, obj)}(${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))});
}
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif
%endif

%endfor
#if defined(__cplusplus)
};
#endif
