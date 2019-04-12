<%!
import re
from templates import helper as th

def declare_obj(obj, tags):
    if re.match(r"macro", obj['type']):
        return False
    if 'class' not in obj or obj['class'] in tags:
        return True
    return re.match(r"handle", obj['type'])

%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
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
* @file ${n}_${name}.hpp
*
* @brief C++ wrapper of ${th.subt(n, tags, header['desc'])}
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/${section}/${name}.yml
* @endcond
*
******************************************************************************/
#ifndef _${N}_${name.upper()}_HPP
#define _${N}_${name.upper()}_HPP
#if defined(__cplusplus)
#pragma once
%if re.match(r"common", name):
#include "${n}_all.h"
#include <tuple>
%if x != n:
#include "${x}_all.hpp"
%endif
%else:
#include "${n}_common.hpp"
%endif
%for item in header['includes']:
#include "${re.sub(r"\$h", "hpp", th.subt(n, tags, item))}"
%endfor

namespace ${n}
{
%for obj in objects:
%if declare_obj(obj, tags):
    ///////////////////////////////////////////////////////////////////////////////
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    %for line in th.make_desc_lines(n, tags, obj, cpp=True):
    /// ${line}
    %endfor
    %for line in th.make_details_lines(n, tags, obj, cpp=True):
    /// ${line}
    %endfor
    ## TYPEDEF ####################################################################
    %if re.match(r"typedef", obj['type']):
    using ${th.subt(n, tags, obj['name'], cpp=True)} = ::${th.subt(n, tags, obj['name'])};
    ## ENUM #######################################################################
    %elif re.match(r"enum", obj['type']):
    enum class ${th.subt(n, tags, obj['name'], cpp=True)}
    {
        %for line in th.make_etor_lines(n, tags, obj, cpp=True, meta=meta):
        ${line}
        %endfor

    };
    ## STRUCT/UNION ###############################################################
    %elif re.match(r"struct", obj['type']) or re.match(r"union", obj['type']):
    ${obj['type']} ${th.subt(n, tags, obj['name'], cpp=True)}
    {
        %for line in th.make_member_lines(n, tags, obj, cpp=True, meta=meta):
        ${line}
        %endfor

    };
    ## FUNCTION ###################################################################
    %elif re.match(r"function", obj['type']):
    /// 
    %for line in th.make_returns_lines(n, tags, obj, cpp=True):
    /// ${line}
    %endfor
    inline ${th.make_return_value(n, tags, obj, cpp=True, decl=True, meta=meta)}
    ${th.make_func_name(n, tags, obj, cpp=True)}(
        %for line in th.make_param_lines(n, tags, obj, cpp=True, decl=True, meta=meta):
        ${line}
        %endfor
        );
    ## CLASS ######################################################################
    %elif re.match(r"class", obj['type']):
    class ${th.make_class_name(n, tags, obj)}
    {
    protected:
        %for line in th.make_member_lines(n, tags, obj):
        ::${line}
        %endfor

    public:
        %for line in th.make_member_function_lines(n, tags, obj):
        ${line}
        %endfor

        %for t in th.filter_items(th.extract_objs(specs, r"typedef"), 'class', obj['name']):
%if 'condition' in t:
#if ${th.subt(n, tags, t['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::${th.subt(n, tags, t['name'])}
        using ${th.subt(n, tags, t['name'], cpp=True)} = ::${th.subt(n, tags, t['name'])};
%if 'condition' in t:
#endif // ${th.subt(n, tags, t['condition'])}
%endif

        %endfor
        %for e in th.filter_items(th.extract_objs(specs, r"enum"), 'class', obj['name']):
%if 'condition' in e:
#if ${th.subt(n, tags, e['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::${th.subt(n, tags, e['name'])}
        enum class ${th.subt(n, tags, e['name'], cpp=True)}
        {
            %for line in th.make_etor_lines(n, tags, e, cpp=True, meta=meta):
            ${line}
            %endfor

        };
%if 'condition' in e:
#endif // ${th.subt(n, tags, e['condition'])}
%endif

        %endfor
        %for s in th.filter_items(th.extract_objs(specs, r"struct|union"), 'class', obj['name']):
%if 'condition' in s:
#if ${th.subt(n, tags, s['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::${th.subt(n, tags, s['name'])}
        ${s['type']} ${th.subt(n, tags, s['name'], cpp=True)}
        {
            %for line in th.make_member_lines(n, tags, s, cpp=True, meta=meta):
            ${line}
            %endfor

        };
%if 'condition' in s:
#endif // ${th.subt(n, tags, s['condition'])}
%endif

        %endfor
        %for f in th.filter_items(th.extract_objs(specs, r"function"), 'class', obj['name']):
%if 'condition' in f:
#if ${th.subt(n, tags, f['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::${th.make_func_name(n, tags, f)}
        %for line in th.make_returns_lines(n, tags, f, cpp=True):
        /// ${line}
        %endfor
        inline ${th.make_return_value(n, tags, f, cpp=True, decl=True, meta=meta)}
        ${th.make_func_name(n, tags, f, cpp=True)}(
            %for line in th.make_param_lines(n, tags, f, cpp=True, decl=True, meta=meta):
            ${line}
            %endfor
            );
%if 'condition' in f:
#endif // ${th.subt(n, tags, f['condition'])}
%endif

        %endfor
    };
    ## HANDLE #####################################################################
    %elif re.match(r"handle", obj['type']):
    %if 'class' in obj:
    class ${th.subt(n, tags, obj['class'], cpp=True)};
    using ${th.subt(n, tags, obj['name'], cpp=True)} = ${th.subt(n, tags, obj['class'], cpp=True)}*;
    %else:
    using ${th.subt(n, tags, obj['name'], cpp=True)} = ::${th.subt(n, tags, obj['name'])};
    %endif
    %endif
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

%endif
%endfor
} // namespace ${n}
#endif // defined(__cplusplus)
#endif // _${N}_${name.upper()}_HPP
