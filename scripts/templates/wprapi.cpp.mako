<%!
import re
from templates import helper as th

def define_dbg(obj, tags):
    if re.match("class", obj['type']):
        return True
    if 'class' not in obj or obj['class'] in tags:
        return re.match("enum", obj['type']) or re.match("struct|union", obj['type'])
    return False

%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 * @version v${ver}-r${rev}
 *
 * @brief C++ wrapper of ${n}
 *
 */
#include "${n}_api.hpp"
#include "${x}_singleton.h"

#define _${X}_STRING(s) #s
#define ${X}_STRING(s) _${X}_STRING(s)

namespace ${n}
{
%for s in specs:
#pragma region ${s['name']}
## EXCEPTION ##############################################################
%if re.match(r"common", s['name']) and (n == x):
    ///////////////////////////////////////////////////////////////////////////////
    std::string exception_t::formatted(
        const result_t result,
        const char* file,
        const char* line,
        const char* func )
    {
    #ifdef _DEBUG
        std::stringstream msg;
        msg << file << "(" << line << ") : exception : " << func << "(" << ${x}::to_string(result) << ")";
        return msg.str();
    #else
        return ${x}::to_string(result);
    #endif
    }

%endif
## CLASS ################################################################
%for obj in th.filter_items(s['objects'], 'type', 'class'):
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
    %if th.class_traits.is_singleton(obj):
    static singleton_factory_t<${th.make_class_name(n, tags, obj)}, ${th.subt(n, tags, th.class_traits.get_handle(obj, meta), cpp=True)}> g_${th.make_class_name(n, tags, obj)}Factory;

    %endif
%endfor
## FUNCTION ###################################################################
%for obj in th.filter_items(s['objects'], 'type', 'function'):
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
    %if 'tparams' in obj:
    template<${th.make_tparams_line(n, tags, obj)}>
    %endif
    ${th.make_return_type(n, tags, obj, cpp=True, meta=meta)} ${X}_APICALL
    %if 'class' in obj and obj['class'] not in tags:
    ${th.subt(n, tags, obj['class'], cpp=True)}::${th.make_func_name(n, tags, obj, cpp=True)}(
    %else:
    ${th.make_func_name(n, tags, obj, cpp=True)}(
    %endif
        %for line in th.make_param_lines(n, tags, obj, cpp=True, meta=meta):
        ${line}
        %endfor
        )<%
        wparams, rvalue = th.make_wrapper_params(n, tags, obj, meta, specs)
        release_items = []  # free all memory on bad_alloc exception
%>
    {
        %for item in wparams:
        %if 'local' in item:
        %if 'range' in item:
        thread_local std::vector<${item['ctype']}> ${item['local']};
        %if 'init' in item:
        ${item['local']}.resize( 0 );
        ${item['local']}.reserve( ${item['range'][1]} );
        for( uint32_t i = ${item['range'][0]}; i < ${item['range'][1]}; ++i )
            %if item['optional']:
            ${item['local']}.emplace_back( ( ${item['init']} ) ? reinterpret_cast<${item['ctype']}>( ${item['init']}[ i ]->getHandle() ) : nullptr );
            %else:
            ${item['local']}.emplace_back( reinterpret_cast<${item['ctype']}>( ${item['init']}[ i ]->getHandle() ) );
            %endif
        %else:
        ${item['local']}.resize( ( ${item['name']} ) ? ${item['range'][1]} : 0 );
        %endif
        %else:
        ${item['ctype']} ${item['local']};
        %endif

        %endif
        %endfor
        auto result = static_cast<result_t>( ::${th.make_func_name(n, tags, obj)}(
            ${",\n            ".join(th.extract_items(wparams, 'arg'))} ) );

        %if len(rvalue) == 0 and re.match(r"[\w,:]*bool_t", th.make_return_type(n, tags, obj, cpp=True, meta=meta)):
        if( result_t::NOT_READY == result )
            return 0; // false
        %endif
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ${X}_STRING(__LINE__), "${n}::${th.subt(n, tags, obj['class'], cpp=True)}::${th.subt(n, tags, obj['name'], cpp=True)}" );
        %for item in wparams:
        %if 'class' in item:

        %if 'release' in item and item['release']:
        delete ${item['name']};
        %else:
        %if 'range' in item:
        %if item['optional']:
        for( uint32_t i = ${item['range'][0]}; ( ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
            ${item['name']}[ i ] = nullptr;
        %else:
        for( uint32_t i = ${item['range'][0]}; i < ${item['range'][1]}; ++i )
            ${item['name']}[ i ] = nullptr;
        %endif
        %elif item['optional']:
        if( ${item['name']} )
            *${item['name']} =  nullptr;
        %else:
        ${item['class']}* ${item['name']} = nullptr;
        %endif

        try
        {
            %if 'range' in item:
            %if item['optional']:
            for( uint32_t i = ${item['range'][0]}; ( ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
                %if item['ctor']['factory']:
                ${item['name']}[ i ] = ${item['ctor']['factory']}.getInstance( ${", ".join(item['ctor']['params'])} );
                %else:
                ${item['name']}[ i ] = new ${item['class']}( ${", ".join(item['ctor']['params'])} );<%release_items.append(item['name'])%>
                %endif
            %else:
            for( uint32_t i = ${item['range'][0]}; i < ${item['range'][1]}; ++i )
                %if item['ctor']['factory']:
                ${item['name']}[ i ] = ${item['ctor']['factory']}.getInstance( ${", ".join(item['ctor']['params'])} );
                %else:
                ${item['name']}[ i ] = new ${item['class']}( ${", ".join(item['ctor']['params'])} );<%release_items.append(item['name'])%>
                %endif
            %endif
            %elif item['optional']:
            if( ${item['name']} )
                %if item['ctor']['factory']:
                *${item['name']} =  ${item['ctor']['factory']}.getInstance( ${", ".join(item['ctor']['params'])} );
                %else:
                *${item['name']} =  new ${item['class']}( ${", ".join(item['ctor']['params'])} );<%release_items.append(item['name'])%>
                %endif
            %else:
            %if item['ctor']['factory']:
            ${item['name']} = ${item['ctor']['factory']}.getInstance( ${", ".join(item['ctor']['params'])} );
            %else:
            ${item['name']} = new ${item['class']}( ${", ".join(item['ctor']['params'])} );<%release_items.append(item['name'])%>
            %endif
            %endif
        }
        catch( std::bad_alloc& )
        {
            %if not item['ctor']['factory']:
            %if 'range' in item:
            %if item['optional']:
            for( uint32_t i = ${item['range'][0]}; ( ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
            {
                delete ${item['name']}[ i ];
                ${item['name']}[ i ] = nullptr;
            }
            %else:
            for( uint32_t i = ${item['range'][0]}; i < ${item['range'][1]}; ++i )
            {
                delete ${item['name']}[ i ];
                ${item['name']}[ i ] = nullptr;
            }
            %endif
            %elif item['optional']:
            if( ${item['name']} )
            {
                delete *${item['name']};
                *${item['name']} =  nullptr;
            }
            %else:
            delete ${item['name']};
            ${item['name']} = nullptr;
            %endif
            %for release_item in release_items:
            %if release_item != item['name']:
            delete ${release_item};
            ${release_item} = nullptr;
            %endif
            %endfor

            %endif
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ${X}_STRING(__LINE__), "${n}::${th.subt(n, tags, obj['class'], cpp=True)}::${th.subt(n, tags, obj['name'], cpp=True)}" );
        }
        %endif
        %endif
        %endfor
        %if len(rvalue) > 0:

        return ${rvalue};
        %elif re.match(r"[\w,:]*bool_t", th.make_return_type(n, tags, obj, cpp=True, meta=meta)):
        return 1; // true
        %endif
    }
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
#pragma endregion
%endfor
} // namespace ${n}

## DEBUG ######################################################################
namespace ${n}
{
    %for s in specs:
#pragma region ${s['name']}
    %for obj in s['objects']:
    %if define_dbg(obj, tags):
    %if re.match(r"enum", obj['type']) or re.match(r"struct|union", obj['type']):
    <%
        tname = th.make_type_name(n, tags, obj, cpp=True)
    %>///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ${tname} to std::string
    ## CONDITION-START ############################################################
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    std::string to_string( const ${tname} val )
    {
        ## ENUM #######################################################################
        %if re.match(r"enum", obj['type']):
        %if th.is_enum_bitfield(obj):
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        %for i, item in enumerate(obj['etors']):
        <%
            ename = th.make_etor_name(n, tags, obj['name'], item['name'], cpp=True, meta=meta)
        %>
        %if th.type_traits.is_flags(tname):
        if( static_cast<uint32_t>(${ename}) & bits )
            str += "${ename} | ";
        %else:
        if( static_cast<uint32_t>(${tname}::${ename}) & bits )
            str += "${ename} | ";
        %endif
        %endfor

        return ( str.size() > 3 ) 
        %if th.type_traits.is_flags(tname):
            ? "{ " + str.substr(0, str.size() - 3) + " }"
            : "{ ? }";
        %else:
            ? "${tname}::{ " + str.substr(0, str.size() - 3) + " }"
            : "${tname}::{ ? }";
        %endif
        %else:
        std::string str;

        switch( val )
        {
        %for item in obj['etors']:
        %if not item['name'].endswith("CURRENT"):
        <%
            ename = th.make_etor_name(n, tags, obj['name'], item['name'], cpp=True, meta=meta)
        %>case ${tname}::${ename}:
            str = "${tname}::${ename}";
            break;

        %endif
        %endfor
        default:
            str = "${tname}::?";
            break;
        };

        return str;
        %endif
        ## STRUCT/UNION ############################################################
        %else:
        std::string str;
        %for item in obj['members']:
        <%
            mname = th.make_member_name(n, tags, item, cpp=True, meta=meta, remove_array=True)
        %>
        str += "${tname}::${mname} : ";
        %if "char" in item['type']:
        str += val.${mname};
        %elif th.type_traits.is_pointer(item['type']):
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.${mname});
            str += ss.str();
        }
        %elif th.type_traits.is_known(item['type'], meta) and (item['type'] != "$x_bool_t"):
        str += to_string(val.${mname});
        %elif th.value_traits.is_array(item['name']):
        {
            std::string tmp;
            for( auto& entry : val.${mname} )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        %else:
        str += std::to_string(val.${mname});
        %endif
        str += "\n";
        %endfor

        return str;
        %endif
    }
    ## CONDITION-END ##############################################################
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    ## CLASS ######################################################################
    %elif re.match(r"class", obj['type']):
    ## ENUM #######################################################################
    %for e in th.filter_items(th.extract_objs(specs, r"enum"), 'class', obj['name']):
    <%
        cname = th.make_class_name(n, tags, obj)
        tname = "%s::%s"%(cname, th.make_type_name(n, tags, e, cpp=True))
    %>///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ${tname} to std::string
    %if 'condition' in e:
    #if ${th.subt(n, tags, e['condition'])}
    %endif
    std::string to_string( const ${tname} val )
    {
        %if th.is_enum_bitfield(e):
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        %for i, item in enumerate(e['etors']):
        <%
            ename = th.make_etor_name(n, tags, e['name'], item['name'], cpp=True, meta=meta)
        %>
        %if th.type_traits.is_flags(tname):
        if( static_cast<uint32_t>(${cname}::${ename}) & bits )
            str += "${ename} | ";
        %else:
        if( static_cast<uint32_t>(${tname}::${ename}) & bits )
            str += "${ename} | ";
        %endif
        %endfor

        return ( str.size() > 3 ) 
        %if th.type_traits.is_flags(tname):
            ? "${cname}::{ " + str.substr(0, str.size() - 3) + " }"
            : "${cname}::{ ? }";
        %else:
            ? "${tname}::{ " + str.substr(0, str.size() - 3) + " }"
            : "${tname}::{ ? }";
        %endif
        %else:
        std::string str;

        switch( val )
        {
        %for item in e['etors']:
        %if not item['name'].endswith("CURRENT"):
        <%
            ename = th.make_etor_name(n, tags, e['name'], item['name'], cpp=True, meta=meta)
        %>case ${tname}::${ename}:
            str = "${tname}::${ename}";
            break;

        %endif
        %endfor
        default:
            str = "${tname}::?";
            break;
        };

        return str;
        %endif
    }
    %if 'condition' in e:
    #endif // ${th.subt(n, tags, e['condition'])}
    %endif

    %endfor ## enum
    ## STRUCT/UNION ############################################################
    %for s in th.filter_items(th.extract_objs(specs, r"struct|union"), 'class', obj['name']):
    <%
        tname = "%s::%s"%(th.make_class_name(n, tags, obj), th.make_type_name(n, tags, s, cpp=True))
    %>///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ${tname} to std::string
    %if 'condition' in s:
    #if ${th.subt(n, tags, s['condition'])}
    %endif
    std::string to_string( const ${tname} val )
    {
        std::string str;
        %for item in s['members']:
        <%
            mname = th.make_member_name(n, tags, item, cpp=True, meta=meta, remove_array=True)
        %>
        str += "${tname}::${mname} : ";
        %if "char" in item['type']:
        str += val.${mname};
        %elif th.type_traits.is_pointer(item['type']):
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.${mname});
            str += ss.str();
        }
        %elif th.value_traits.is_array(item['name']):
        {
            std::string tmp;
            for( auto& entry : val.${mname} )
            {
                %if th.type_traits.is_known(item['type'], meta) and (item['type'] != "$x_bool_t"):
                tmp += to_string( entry );
                %else:
                tmp += std::to_string( entry );
                %endif
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        %elif th.type_traits.is_known(item['type'], meta) and (item['type'] != "$x_bool_t"):
        str += to_string(val.${mname});
        %else:
        str += std::to_string(val.${mname});
        %endif
        str += "\n";
        %endfor

        return str;
    }
    %if 'condition' in s:
    #endif // ${th.subt(n, tags, s['condition'])}
    %endif

    %endfor ## struct
    %endif  ## class
    %endif  ## define_dbg
    %endfor ## obj in s['objects']
#pragma endregion
    %endfor ## s in specs
} // namespace ${n}
