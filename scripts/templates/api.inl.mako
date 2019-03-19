<%!
import re
from templates import helper as th
%><%
    x=context['ns'][0]
    X=context['ns'][0].upper()
    Xx=context['ns'][0].title()
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
* @file ${x}_${name}.inl
*
* @brief C++ wrapper of ${th.sub(ns, header['desc'])}
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/${section}/${name}.yml
* @endcond
*
******************************************************************************/
#ifndef _${X}_${name.upper()}_INL
#define _${X}_${name.upper()}_INL
#if defined(__cplusplus)
#pragma once
%if re.match(r"common", name):
#include "${x}_all.h"
%else:
#include "${x}_${name}.hpp"
%endif

namespace ${x}
{
%for obj in objects:
%if re.match(r"class", obj['type']) or (re.match(r"function", obj['type']) and ('class' not in obj or re.match(r"\$x$", obj['class']))):
%if re.match(r"function", obj['type']):
    ## FUNCTION ###################################################################
    ///////////////////////////////////////////////////////////////////////////////
%if 'condition' in obj:
#if ${th.sub(ns, obj['condition'])}
%endif
    /// @brief C++ wrapper for ::${th.make_func_name(ns, obj)}
    %for line in th.make_details_lines(None, obj):
    /// ${line}
    %endfor
    /// 
    %for line in th.make_returns_lines(None, obj, True):
    /// ${line}
    %endfor
    inline ${th.make_return_value(None, obj)} 
    ${th.make_func_name(None, obj, True)}(
        %for line in th.make_param_lines(None, obj, True):
        ${line}
        %endfor
        )
    {
        // auto result = ::${th.make_func_name(ns, obj)}( ${th.make_param_call_str("handle", None, obj, True)} );
        // if( ::${X}_RESULT_SUCCESS != result ) throw exception(result, "${x}::${th.sub(None, obj['name'])}::${th.sub(None, obj['name'])}");
    }
%if 'condition' in obj:
#endif // ${th.sub(ns, obj['condition'])}
%endif

%elif re.match(r"class", obj['type']):
    ## CLASS FUNCTION #############################################################
    %for f in th.filter_items(th.extract_objs(specs, "function"), 'class', obj['name']):
    ///////////////////////////////////////////////////////////////////////////////
%if 'condition' in f:
#if ${th.sub(ns, f['condition'])}
%endif
    /// @brief C++ wrapper for ::${th.make_func_name(ns, f)}
    %for line in th.make_details_lines(None, f):
    /// ${line}
    %endfor
    /// 
    %for line in th.make_returns_lines(None, f, True):
    /// ${line}
    %endfor
    inline ${th.make_return_value(None, f)} 
    ${th.sub(None, obj['name'])}::${th.make_func_name(None, f, True)}(
        %for line in th.make_param_lines(None, f, True):
        ${line}
        %endfor
        )
    {
        // auto result = ::${th.make_func_name(ns, f)}( ${th.make_param_call_str("handle", None, f, True)} );
        // if( ::${X}_RESULT_SUCCESS != result ) throw exception(result, "${x}::${th.sub(None, obj['name'])}::${th.sub(None, f['name'])}");
    }
%if 'condition' in f:
#endif // ${th.sub(ns, f['condition'])}
%endif

    %endfor
%endif
%endif
%endfor
} // namespace ${x}
#endif // defined(__cplusplus)
#endif // _${X}_${name.upper()}_INL
