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
* @file ${x}_${name}.hpp
*
* @brief C++ wrapper of ${th.sub(ns, header['desc'])}
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/${section}/${name}.yml
* @endcond
*
******************************************************************************/
#ifndef _${X}_${name.upper()}_HPP
#define _${X}_${name.upper()}_HPP
#if defined(__cplusplus)
#pragma once
%if re.match(r"common", name):
#include "${x}_all.h"
#include <tuple>
%else:
#include "${x}_common.hpp"
%endif

namespace ${x}
{
%for obj in objects:
%if not re.match(r"macro", obj['type']) and ('class' not in obj or re.match(r"\$x$", obj['class']) or re.match(r"handle", obj['type'])):
    ///////////////////////////////////////////////////////////////////////////////
    %if 'condition' in obj:
    #if ${th.sub(ns,obj['condition'])}
    %endif
    %for line in th.make_desc_lines(None, obj):
    /// ${line}
    %endfor
    %for line in th.make_details_lines(None, obj):
    /// ${line}
    %endfor
    ## TYPEDEF ####################################################################
    %if re.match(r"typedef", obj['type']):
    using ${th.sub(None, obj['name'])} = ::${th.sub(ns, obj['name'])};
    ## ENUM #######################################################################
    %elif re.match(r"enum", obj['type']):
    enum class ${th.sub(None, obj['name'])}
    {
        %for line in th.make_etor_lines(None, obj, True, ns, meta):
        ${line}
        %endfor

    };
    ## STRUCT #####################################################################
    %elif re.match(r"struct", obj['type']):
    struct ${th.sub(None, obj['name'])}
    {
        %for line in th.make_member_lines(None, obj, True, ns, meta):
        ${line}
        %endfor

    };
    ## FUNCTION ###################################################################
    %elif re.match(r"function", obj['type']):
    /// 
    %for line in th.make_returns_lines(None, obj, True):
    /// ${line}
    %endfor
    inline ${th.make_return_value(None, obj)}
    ${th.make_func_name(None, obj, True)}(
        %for line in th.make_param_lines(None, obj, True):
        ${line}
        %endfor
        );
    ## CLASS ######################################################################
    %elif re.match(r"class", obj['type']):
    class ${th.sub(None, obj['name'])}
    {
    protected:
        %for line in th.make_member_lines(ns, obj):
        ::${line}
        %endfor

    public:
        %for line in th.make_member_function_lines(ns, obj):
        ${line}
        %endfor

        %for t in th.filter_items(th.extract_objs(specs, "typedef"), 'class', obj['name']):
%if 'condition' in t:
#if ${th.sub(ns,t['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::${th.sub(ns, t['name'])}
        using ${th.sub(None, t['name'])} = ::${th.sub(ns, t['name'])};
%if 'condition' in t:
#endif // ${th.sub(ns,t['condition'])}
%endif

        %endfor
        %for e in th.filter_items(th.extract_objs(specs, "enum"), 'class', obj['name']):
%if 'condition' in e:
#if ${th.sub(ns,e['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::${th.sub(ns, e['name'])}
        enum class ${th.sub(None, e['name'])}
        {
            %for line in th.make_etor_lines(None, e, True, ns, meta):
            ${line}
            %endfor

        };
%if 'condition' in e:
#endif // ${th.sub(ns,e['condition'])}
%endif

        %endfor
        %for s in th.filter_items(th.extract_objs(specs, "struct"), 'class', obj['name']):
%if 'condition' in s:
#if ${th.sub(ns,s['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::${th.sub(ns, s['name'])}
        struct ${th.sub(None, s['name'])}
        {
            %for line in th.make_member_lines(None, s, True, ns, meta):
            ${line}
            %endfor

        };
%if 'condition' in s:
#endif // ${th.sub(ns,s['condition'])}
%endif

        %endfor
        %for f in th.filter_items(th.extract_objs(specs, "function"), 'class', obj['name']):
%if 'condition' in f:
#if ${th.sub(ns,f['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::${th.make_func_name(ns, f)}
        %for line in th.make_returns_lines(None, f, True):
        /// ${line}
        %endfor
        inline ${th.make_return_value(None, f, True)}
        ${th.make_func_name(None, f, True)}(
            %for line in th.make_param_lines(None, f, True):
            ${line}
            %endfor
            );
%if 'condition' in f:
#endif // ${th.sub(ns,f['condition'])}
%endif

        %endfor
    };
    ## HANDLE #####################################################################
    %elif re.match(r"handle", obj['type']):
    %if 'class' in obj:
    class ${th.sub(None, obj['class'])};
    using ${th.sub(None, obj['name'])} = ${th.sub(None, obj['class'])}*;
    %else:
    using ${th.sub(None, obj['name'])} = ::${th.sub(ns, obj['name'])};
    %endif
    %endif
    %if 'condition' in obj:
    #endif // ${th.sub(ns,obj['condition'])}
    %endif

%endif
%endfor
} // namespace ${x}
#endif // defined(__cplusplus)
#endif // _${X}_${name.upper()}_HPP
