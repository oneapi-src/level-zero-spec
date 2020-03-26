<%
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

def declare_dbg(obj, tags):
    if re.match("class", obj['type']):
        return True
    if 'class' not in obj or obj['class'] in tags:
        return re.match("enum", obj['type']) or re.match("struct|union", obj['type'])
    return False

%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
%>/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${n}_api.hpp
 *
 */
#ifndef _${N}_API_HPP
#define _${N}_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "${n}_api.h"

%if n != x:
// 'core' C++ API headers
#include "${x}_api.hpp"
%else:
// standard headers
#include <stdint.h>
#include <string.h>
#include <exception>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
%endif

%for spec in specs:
#pragma region ${spec['name']}
## MACROS #####################################################################
%for obj in th.filter_items(spec['objects'], 'type', "macro"):
///////////////////////////////////////////////////////////////////////////////
#ifndef ${th.make_macro_name(n, tags, obj, params=False)}
## CONDITION-START ############################################################
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
## DESCRIPTION ################################################################
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

%endfor # obj
namespace ${n}
{
%for obj in spec['objects']:
%if declare_obj(obj, tags):
    ///////////////////////////////////////////////////////////////////////////////
## CONDITION-START ############################################################
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
    ## DESCRIPTION ################################################################
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
    using ${th.make_type_name(n, tags, obj, cpp=True)} = ${th.get_type_name(n, tags, obj, obj['value'], cpp=True, meta=meta, handle_to_class=True)};
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
    ${th.make_return_type(n, tags, obj, cpp=True, decl=True, meta=meta)} __${x}call
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
        ## DESCRIPTION ################################################################
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
        using ${th.make_type_name(n, tags, t, cpp=True)} = ${th.subt(n, tags, t['value'], cpp=False)};
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
        ## DESCRIPTION ################################################################
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
        ## DESCRIPTION ################################################################
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
        %if 'base' in obj:
        using ${th.make_baseclass_ctor(n, tags, obj)};
        %else:
        %if th.has_ctor_params(obj):
        ${th.make_class_name(n, tags, obj)}( void ) = delete;
        %endif
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
        ## DESCRIPTION ################################################################
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
        %if 'decl' in f:
        ${f['decl']} ${th.make_return_type(n, tags, f, cpp=True, decl=True, meta=meta)} __${x}call
        %else:
        ${th.make_return_type(n, tags, f, cpp=True, decl=True, meta=meta)} __${x}call
        %endif
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
%endfor ## obj in spec['objects']
} // namespace ${n}

## DEBUG ######################################################################
namespace ${n}
{
    %for obj in spec['objects']:
    %if declare_dbg(obj, tags):
    %if re.match(r"enum", obj['type']) or re.match(r"struct|union", obj['type']):
    <%
        tname = th.make_type_name(n, tags, obj, cpp=True)
    %>///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ${tname} to std::string
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    std::string to_string( const ${tname} val );
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    ## CLASS ######################################################################
    %elif re.match(r"class", obj['type']):
    %for t in th.filter_items(th.extract_objs(specs, r"enum|struct|union"), 'class', obj['name']):
    <%
        tname = "%s::%s"%(th.make_class_name(n, tags, obj), th.make_type_name(n, tags, t, cpp=True))
    %>///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ${tname} to std::string
    %if 'condition' in t:
    #if ${th.subt(n, tags, t['condition'])}
    %endif
    std::string to_string( const ${tname} val );
    %if 'condition' in t:
    #endif // ${th.subt(n, tags, t['condition'])}
    %endif

    %endfor
    %endif  ## class
    %endif  ## declare_dbg
    %endfor ## obj in spec['objects']
} // namespace ${n}
## EXCEPTION ##############################################################
%if re.match(r"common", spec['name']):

namespace ${n}
{
    %if n == x:
    ///////////////////////////////////////////////////////////////////////////////
    class exception_t : public std::exception
    {
    protected:
        static std::string formatted( const result_t, const char*, const char*, const char* );

        const std::string _msg;
        const result_t _result;

    public:
        exception_t() = delete;

        exception_t( const result_t result, const char* file, const char* line, const char* func )
            : std::exception(),
            _msg( formatted(result, file, line, func) ),
            _result(result)
        {
        }

        const char* what() const noexcept { return _msg.c_str(); }
        result_t value() const noexcept { return _result; }
    };
    %else:
    using result_t = ${x}::result_t;
    using exception_t = ${x}::exception_t;
    %endif

} // namespace ${n}
%endif
#pragma endregion
%endfor # spec in specs
#endif // defined(__cplusplus)
#endif // _${N}_API_HPP