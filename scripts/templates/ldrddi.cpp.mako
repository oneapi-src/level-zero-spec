<%!
import re
from templates import helper as th
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
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/ldrddi.cpp.mako
 * @endcond
 *
 */
#include "${x}_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    %for obj in th.extract_objs(specs, r"handle"):
    %if 'class' in obj:
    <%
        _handle_t = th.subt(n, tags, obj['name'])
        _factory_t = re.sub(r"(\w+)_handle_t", r"\1_factory_t", _handle_t)
        _factory = re.sub(r"(\w+)_handle_t", r"\1_factory", _handle_t)
    %>${th.append_ws(_factory_t, 35)} ${_factory};
    %endif
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
        xe_result_t result = ${X}_RESULT_SUCCESS;

        %if re.match(r"Init", obj['name']):
        for( auto& drv : context.drivers )
        {
            if( ${X}_RESULT_SUCCESS == result )
            {
                result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
            }
        }

        %elif re.match(r"\w+DeviceGroupGet$", th.make_func_name(n, tags, obj)):
        uint32_t total_count = 0;

        for( auto& drv : context.drivers )
        {
            uint32_t count = 0;

            result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &count, nullptr );
            if( ${X}_RESULT_SUCCESS != result ) break;

            if( ( 0 < *${obj['params'][0]['name']} ) && ( *${obj['params'][0]['name']} > total_count + count ) )
                break;

            if( nullptr != ${obj['params'][1]['name']} )
            {
                result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &count, &${obj['params'][1]['name']}[ total_count ] );
                if( ${X}_RESULT_SUCCESS != result ) break;

                try
                {
                    for( uint32_t i = total_count; i < count; ++i )
                        ${obj['params'][1]['name']}[ i ] = reinterpret_cast<${n}_device_group_handle_t>( 
                            ${n}_device_group_factory.getInstance( ${obj['params'][1]['name']}[ i ], &drv.dditable ) );
                }
                catch( std::bad_alloc& )
                {
                    result = ${X}_RESULT_ERROR_OUT_OF_HOST_MEMORY;
                }
            }

            total_count += count;
        }

        if( ${X}_RESULT_SUCCESS == result )
            *${obj['params'][0]['name']} = total_count;

        %else:
        %for i, item in enumerate(th.get_loader_prologue(n, tags, obj, meta)):
        %if 0 == i:
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<${item['obj']}*>( ${item['name']} )->dditable;
        auto ${th.make_pfn_name(n, tags, obj)} = dditable->${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
        if( nullptr == ${th.make_pfn_name(n, tags, obj)} )
            return ${X}_RESULT_ERROR_UNSUPPORTED;

        %endif
        %if 'range' in item:
        // convert loader handles to driver handles
        for( size_t i = ${item['range'][0]}; ( nullptr != ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
            ${item['name']}[ i ] = reinterpret_cast<${item['obj']}*>( ${item['name']}[ i ] )->handle;
        %else:
        // convert loader handle to driver handle
        %if item['optional']:
        ${item['name']} = ( ${item['name']} ) ? reinterpret_cast<${item['obj']}*>( ${item['name']} )->handle : nullptr;
        %else:
        ${item['name']} = reinterpret_cast<${item['obj']}*>( ${item['name']} )->handle;
        %endif
        %endif

        %endfor
        // forward to device-driver
        result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );

        %for item in th.get_loader_epilogue(n, tags, obj, meta):
        %if item['release']:
        // release loader handle
        ${item['factory']}.release( ${item['name']} );
        %else:
        try
        {
            %if 'range' in item:
            // convert driver handles to loader handles
            for( size_t i = ${item['range'][0]}; ( nullptr != ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
                ${item['name']}[ i ] = reinterpret_cast<${item['type']}>(
                    ${item['factory']}.getInstance( ${item['name']}[ i ], dditable ) );
            %else:
            // convert driver handle to loader handle
            %if item['optional']:
            if( nullptr != ${item['name']} )
                *${item['name']} = reinterpret_cast<${item['type']}>(
                    ${item['factory']}.getInstance( *${item['name']}, dditable ) );
            %else:
            *${item['name']} = reinterpret_cast<${item['type']}>(
                ${item['factory']}.getInstance( *${item['name']}, dditable ) );
            %endif
            %endif
        }
        catch( std::bad_alloc& )
        {
            result = ${X}_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        %endif

        %endfor
        %endif
        return result;
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endfor
} // namespace loader

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
///         + nullptr for pDdiTable
///     - ::${X}_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__${x}dllexport ${x}_result_t __${x}call
${tbl['export']['name']}(
    %for line in th.make_param_lines(n, tags, tbl['export']):
    ${line}
    %endfor
    )
{
    if( loader::context.drivers.size() < 1 )
        return ${X}_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ${X}_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ${X}_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR( drv.handle, "${tbl['export']['name']}") );
            result = getTable( version, &drv.dditable.${n}.${tbl['name']} );
        }
    }

    if( ${X}_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            %for obj in tbl['functions']:
            %if 'condition' in obj:
        #if ${th.subt(n, tags, obj['condition'])}
            %endif
            pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 43)} = loader::${th.make_func_name(n, tags, obj)};
            %if 'condition' in obj:
        #endif
            %endif
            %endfor
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.${n}.${tbl['name']};
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ${X}_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<${tbl['pfn']}>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "${tbl['export']['name']}") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

%endfor

#if defined(__cplusplus)
};
#endif
