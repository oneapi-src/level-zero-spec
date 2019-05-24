<%!
import re
from templates import helper as th

def declare_dbg(obj, tags):
    if re.match("class", obj['type']):
        return True
    if 'class' not in obj or obj['class'] in tags:
        return re.match("enum", obj['type'])
    return False

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
* @file ${n}_${name}.cpp
*
* @brief C++ wrapper of ${th.subt(n, tags, header['desc'])}
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/${section}/${name}.yml
* @endcond
*
******************************************************************************/
#include "${n}_lib.h"

extern "C" {

## FUNCTION ###################################################################
%for obj in th.filter_items(objects, 'type', 'function'):
///////////////////////////////////////////////////////////////////////////////
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
%for line in th.make_desc_lines(n, tags, obj):
/// ${line}
%endfor
%for line in th.make_details_lines(n, tags, obj):
/// ${line}
%endfor
/// 
%for line in th.make_returns_lines(n, tags, obj):
/// ${line}
%endfor
${x}_result_t __${x}call
${th.make_func_name(n, tags, obj)}(
    %for line in th.make_param_lines(n, tags, obj):
    ${line}
    %endfor
    )
{
%if re.match("Init", obj['name']):
    auto result = ${n}_lib::lib.Init();
    if( ${X}_RESULT_SUCCESS != result )
        return result;

%endif
    auto ${th.make_pfn_name(n, tags, obj)} = ${n}_lib::lib.ddiTable.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};

#if _DEBUG
    if( nullptr == ${th.make_pfn_name(n, tags, obj)} )
        return ${X}_RESULT_ERROR_UNSUPPORTED;
#endif

    return ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
}
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
} // extern "C"

namespace ${n}
{
## CLASS ################################################################
%for obj in th.filter_items(objects, 'type', 'class'):
    %if 'base' not in obj:
    ///////////////////////////////////////////////////////////////////////////////
    ${th.make_class_name(n, tags, obj)}::${th.make_class_name(n, tags, obj)}( 
    %for line in th.make_ctor_param_lines(n, tags, obj, meta=meta):
        ${line}
    %endfor
        )${" :" if th.has_ctor_params(obj) else ""}
    %for line in th.make_ctor_param_init_lines(n, tags, obj, "m_"):
        ${line}
    %endfor
    {
    }

    %endif
%endfor
## FUNCTION ###################################################################
%for obj in th.filter_items(objects, 'type', 'function'):
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
    /// 
    %for line in th.make_returns_lines(n, tags, obj, cpp=True, meta=meta):
    /// ${line}
    %endfor
    ## MEMBER FUNCTION ########################################################
    %if 'class' in obj and obj['class'] not in tags:
    %if 'tparams' in obj:
    template<${th.make_tparams_line(n, tags, obj)}>
    %endif
    ${th.make_return_value(n, tags, obj, cpp=True, meta=meta)} __${x}call
    ${th.subt(n, tags, obj['class'], cpp=True)}::${th.make_func_name(n, tags, obj, cpp=True)}(
        %for line in th.make_param_lines(n, tags, obj, cpp=True, meta=meta):
        ${line}
        %endfor
        )
    {
        <%
            return_value = th.make_return_value(n, tags, obj, cpp=True, decl=True, meta=meta)
        %>result_t result = result_t::SUCCESS;

        // auto result = ::${th.make_func_name(n, tags, obj)}( ${th.make_param_call_str(n, tags, "handle", obj, True)} );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "${n}::${th.subt(n, tags, obj['class'], cpp=True)}::${th.subt(n, tags, obj['name'], cpp=True)}" );
        %if not re.match("void$", return_value):

        %if re.match(r"(.*)\btuple\b(.*)", return_value) or re.match(r".*\w+_t$", return_value):
        return ${return_value}{};
        %else:
        return (${return_value})0;
        %endif
        %endif
    }
    ## GLOBAL FUNCTION ########################################################
    %else:
    ${th.make_return_value(n, tags, obj, cpp=True, meta=meta)} __${x}call
    ${th.make_func_name(n, tags, obj, cpp=True)}(
        %for line in th.make_param_lines(n, tags, obj, cpp=True, meta=meta):
        ${line}
        %endfor
        )
    {
        <%
            return_value = th.make_return_value(n, tags, obj, cpp=True, decl=True, meta=meta)
        %>result_t result = result_t::SUCCESS;

        // auto result = ::${th.make_func_name(n, tags, obj)}( ${th.make_param_call_str(n, tags, "handle", obj, True)} );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "${n}::${th.subt(n, tags, obj['class'], cpp=True)}::${th.subt(n, tags, obj['name'], cpp=True)}" );
        %if not re.match("void$", return_value):

        %if re.match(r"(.*)\btuple\b(.*)", return_value) or re.match(r".*\w+_t$", return_value):
        return ${return_value}{};
        %else:
        return (${return_value})0;
        %endif
        %endif
    }
    %endif
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
} // namespace ${n}

## DEBUG ######################################################################
#ifdef _DEBUG
%for obj in objects:
%if declare_dbg(obj, tags):
    ## ENUM #######################################################################
    %if re.match(r"enum", obj['type']):
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ${th.make_type_name(n, tags, obj, cpp=True)} to std::string
    ## CONDITION-START ############################################################
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
    std::string to_string( ${n}::${th.make_type_name(n, tags, obj, cpp=True)} val )
    {
        %for line in th.make_etor_debug_lines(n, tags, None, obj):
        ${line}
        %endfor
    }
    ## CONDITION-END ##############################################################
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif
    ## CLASS ######################################################################
    %elif re.match(r"class", obj['type']):
    %for e in th.filter_items(th.extract_objs(specs, r"enum"), 'class', obj['name']):
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ${th.make_class_name(n, tags, obj)}::${th.make_type_name(n, tags, e, cpp=True)} to std::string
%if 'condition' in e:
#if ${th.subt(n, tags, e['condition'])}
%endif
    std::string to_string( ${n}::${th.make_class_name(n, tags, obj)}::${th.make_type_name(n, tags, e, cpp=True)} val )
    {
        %for line in th.make_etor_debug_lines(n, tags, obj, e):
        ${line}
        %endfor
    }
%if 'condition' in e:
#endif // ${th.subt(n, tags, e['condition'])}
%endif

    %endfor
    %endif

%endif  ## declare_dbg
%endfor ## obj in objects
#endif // _DEBUG
