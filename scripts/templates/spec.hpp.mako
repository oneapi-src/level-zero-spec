<%!
import re
from templates import helper as th

def declare_obj(obj, tags):
    if re.match(r"macro", obj['type']):
        return False
    if re.match(r"handle", obj['type']):
        return True
    if 'class' not in obj or obj['class'] in tags:
        return True
    return False

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
#if !defined(_${N}_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
%if re.match(r"common", name):
#include <stdint.h>
#include <string.h>
//#include "${n}_api.h"
#include <tuple>
%if x != n:
#include "${x}_api.hpp"
%endif
%else:
#include "${n}_common.hpp"
%endif
%for item in header['includes']:
#include "${re.sub(r"\$h", "hpp", th.subt(n, tags, item))}"
%endfor

%for obj in th.extract_objs([{'objects': objects}], r"macro"):
## MACRO ######################################################################
///////////////////////////////////////////////////////////////////////////////
## CONDITION-START ############################################################
#ifndef ${th.make_macro_name(n, tags, obj, params=False)}
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
%for line in th.make_desc_lines(n, tags, obj, cpp=True):
/// ${line}
%endfor
%for line in th.make_details_lines(n, tags, obj, cpp=True):
/// ${line}
%endfor
#define ${th.make_macro_name(n, tags, obj)}  ${th.subt(n, tags, obj['value'])}
%if 'altvalue' in obj:
#else
#define ${th.make_macro_name(n, tags, obj)}  ${th.subt(n, tags, obj['altvalue'])}
%endif
## CONDITION-END ##############################################################
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif
#endif // ${th.make_macro_name(n, tags, obj, params=False)}

%endfor # obj in th.extract_objs([objects], r"macro")
namespace ${n}
{
%for obj in objects:
%if declare_obj(obj, tags):
    ///////////////////////////////////////////////////////////////////////////////
    ## CONDITION-START ############################################################
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
    %if 'params' in obj:
    typedef ${obj['returns']}(__${x}call *${th.make_type_name(n, tags, obj, cpp=True)})(
        %for line in th.make_param_lines(n, tags, obj, cpp=True):
        ${line}
        %endfor
        );
    %else:
    using ${th.make_type_name(n, tags, obj, cpp=True)} = ${th.subt(n, tags, obj['value'], cpp=True)};
    %endif
    ## ENUM #######################################################################
    %elif re.match(r"enum", obj['type']):
    enum class ${th.make_type_name(n, tags, obj, cpp=True)}
    {
        %for line in th.make_etor_lines(n, tags, obj, cpp=True, meta=meta):
        ${line}
        %endfor

    };
    ## STRUCT/UNION ###############################################################
    %elif re.match(r"struct|union", obj['type']):
    ${obj['type']} ${th.make_type_name(n, tags, obj, cpp=True)}
    {
        %for line in th.make_member_lines(n, tags, obj, cpp=True, meta=meta):
        ${line}
        %endfor

    };
    ## FUNCTION ###################################################################
    %elif re.match(r"function", obj['type']):
    /// 
    %for line in th.make_returns_lines(n, tags, obj, cpp=True, meta=meta):
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
    class ${th.make_class_name(n, tags, obj)}${th.make_baseclass_decl(n, tags, obj)}
    {
    public:
        ## TYPEDEF ####################################################################
        %for t in th.filter_items(th.extract_objs(specs, r"typedef"), 'class', obj['name']):
%if 'condition' in t:
#if ${th.subt(n, tags, t['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        %for line in th.make_desc_lines(n, tags, t, cpp=True):
        /// ${line}
        %endfor
        %for line in th.make_details_lines(n, tags, t, cpp=True):
        /// ${line}
        %endfor
        %if 'params' in t:
        typedef ${t['returns']}(__${x}call *${th.make_type_name(n, tags, t, cpp=True)})(
            %for line in th.make_param_lines(n, tags, t):
            ${line}
            %endfor
            );
        %else:
        using ${th.make_type_name(n, tags, t, cpp=True)} = ${th.subt(n, tags, t['value'], cpp=True)};
        %endif
%if 'condition' in t:
#endif // ${th.subt(n, tags, t['condition'])}
%endif

        %endfor
        ## ENUM #######################################################################
        %for e in th.filter_items(th.extract_objs(specs, r"enum"), 'class', obj['name']):
%if 'condition' in e:
#if ${th.subt(n, tags, e['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        %for line in th.make_desc_lines(n, tags, e, cpp=True):
        /// ${line}
        %endfor
        %for line in th.make_details_lines(n, tags, e, cpp=True):
        /// ${line}
        %endfor
        enum class ${th.make_type_name(n, tags, e, cpp=True)}
        {
            %for line in th.make_etor_lines(n, tags, e, cpp=True, meta=meta):
            ${line}
            %endfor

        };
%if 'condition' in e:
#endif // ${th.subt(n, tags, e['condition'])}
%endif

        %endfor
        ## STRUCT/UNION ###############################################################
        %for s in th.filter_items(th.extract_objs(specs, r"struct|union"), 'class', obj['name']):
%if 'condition' in s:
#if ${th.subt(n, tags, s['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        %for line in th.make_desc_lines(n, tags, s, cpp=True):
        /// ${line}
        %endfor
        %for line in th.make_details_lines(n, tags, s, cpp=True):
        /// ${line}
        %endfor
        ${s['type']} ${th.make_type_name(n, tags, s, cpp=True)}
        {
            %for line in th.make_member_lines(n, tags, s, cpp=True, meta=meta):
            ${line}
            %endfor

        };
%if 'condition' in s:
#endif // ${th.subt(n, tags, s['condition'])}
%endif

        %endfor

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        %for line in th.make_member_lines(n, tags, obj, "m_", cpp=True, meta=meta):
        ${line}
        %endfor

    public:
        ## CTORS/DTORS ################################################################
        ///////////////////////////////////////////////////////////////////////////////
        ${th.make_class_name(n, tags, obj)}( void ) = delete;
        %if 'base' in obj:
        using ${th.make_baseclass_ctor(n, tags, obj)};
        %else:
        ${th.make_class_name(n, tags, obj)}( 
        %for line in th.make_ctor_param_lines(n, tags, obj, meta=meta):
            ${line}
        %endfor
            );
        %endif

        ~${th.make_class_name(n, tags, obj)}( void ) = default;

        ${th.make_class_name(n, tags, obj)}( ${th.make_class_name(n, tags, obj)} const& other ) = delete;
        void operator=( ${th.make_class_name(n, tags, obj)} const& other ) = delete;

        ${th.make_class_name(n, tags, obj)}( ${th.make_class_name(n, tags, obj)}&& other ) = delete;
        void operator=( ${th.make_class_name(n, tags, obj)}&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        %for line in th.make_member_function_lines(n, tags, obj, "m_"):
        ${line}
        %endfor

        ## FUNCTION ###################################################################
        %for f in th.get_class_function_objs(specs, obj['name']):
%if 'condition' in f:
#if ${th.subt(n, tags, f['condition'])}
%endif
        ///////////////////////////////////////////////////////////////////////////////
        %for line in th.make_desc_lines(n, tags, f, cpp=True):
        /// ${line}
        %endfor
        %for line in th.make_details_lines(n, tags, f, cpp=True):
        /// ${line}
        %endfor
        %for line in th.make_returns_lines(n, tags, f, cpp=True, meta=meta):
        /// ${line}
        %endfor
        %if 'tparams' in f:
        template<${th.make_tparams_line(n, tags, f)}>
        %endif
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
    %endif
    struct _${th.subt(n, tags, obj['name'], cpp=True)};
    using ${th.subt(n, tags, obj['name'], cpp=True)} = _${th.subt(n, tags, obj['name'], cpp=True)}*;
    %endif
    ## CONDITION-END ##############################################################
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

%endif  ## declare_obj
%endfor ## obj in objects
} // namespace ${n}
#endif // defined(__cplusplus)
#endif // _${N}_${name.upper()}_HPP
