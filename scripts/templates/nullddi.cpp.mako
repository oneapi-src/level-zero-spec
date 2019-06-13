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
* DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "${x}_null.h"

namespace driver
{
    %for obj in th.extract_objs(specs, r"function"):
    ///////////////////////////////////////////////////////////////////////////////
    <%
        fname = th.make_func_name(n, tags, obj)
    %>/// @brief Intercept function for ${fname}
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    ${x}_result_t __${x}call
    ${fname}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
        )
    {
        ${x}_result_t result = ${X}_RESULT_SUCCESS;

        %if n != "xet":
        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            ${th.make_pfncb_param_type(n, tags, obj)} params = {
                ${",\n".join(th.make_param_lines(n, tags, obj, format=["name"]))}
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].${n}PrologueCbs.${th.get_table_name(n, tags, obj)};
                    if( nullptr != table.${th.make_pfncb_name(n, tags, obj)} )
                        table.${th.make_pfncb_name(n, tags, obj)}( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        %endif
        %if re.match(r"\w+DeviceGroupGet$", fname):
        *pCount = 1;
        if( nullptr != phDeviceGroups ) *reinterpret_cast<void**>(phDeviceGroups) = context.get();

        %elif re.match(r"\w+DeviceGet$", fname):
        *pCount = 1;
        if( nullptr != phDevices ) *reinterpret_cast<void**>(phDevices) = context.get() ;

        %elif re.match(r"\w+GetDriverVersion", fname):
        *version = 0;

        %elif re.match(r"\w+GetApiVersion", fname):
        *version = context.version;

        %elif re.match(r"\w+GetDeviceProperties$", fname):
        *pDeviceProperties = context.deviceProperties;

        %elif re.match(r"\w+GetComputeProperties", fname):
        *pComputeProperties = context.computeProperties;

        %elif re.match(r"\w+GetMemoryProperties", fname):
        *pCount = 1;
        if( nullptr != pMemProperties ) *pMemProperties = context.memoryProperties;

        %elif re.match(r"\w+GetMemoryAccessProperties", fname):
        *pMemAccessProperties = context.memoryAccessProperties;

        %elif re.match(r"\w+GetCacheProperties", fname):
        *pCacheProperties = context.cacheProperties;

        %elif re.match(r"\w+GetImageProperties", fname):
        *pImageProperties = context.imageProperties;

        %elif re.match(r"\w+GetP2PProperties", fname):
        *pP2PProperties = context.p2pProperties;

        %elif re.match(r"\w+CanAccessPeer", fname):
        *value = 0;

        %elif re.match(r"\w+Alloc\w+Mem", fname):
        *ptr = malloc( size );

        %elif re.match(r"\w+FreeMem", fname):
        free( ptr );

        %elif re.match(r"\w+GetMemProperties", fname):
        *pMemProperties = {};

        %elif re.match(r"\w+MetricGroupGet$", fname):
        *pCount = 1;
        if( nullptr != phMetricGroups ) *reinterpret_cast<void**>(phMetricGroups) = context.get();

        %elif re.match(r"\w+MetricGroupGetProperties", fname):
        *pProperties = context.metricGroupProperties;

        %elif re.match(r"\w+MetricGet$", fname):
        *pCount = 1;
        if( nullptr != phMetrics ) *reinterpret_cast<void**>(phMetrics) = context.get();

        %elif re.match(r"\w+MetricGetProperties", fname):
        *pProperties = context.metricProperties;

        %elif re.match(r"\w+CalculateMetricValues", fname):
        *pMetricValueCount = 1;
        if( pMetricValues ) *pMetricValues = {};

        %elif re.match(r"\w+ReadData", fname) or re.match(r"\w+GetData", fname):
        *pRawDataSize = 1;
        if( pRawData ) *pRawData = 0;

        %elif re.match(r"\w+TracerCreate", fname):
        context.tracerData.emplace_back();
        auto index = context.tracerData.size() - 1;
        context.tracerData[ index ].globalUserData = desc->pGlobalUserData;
        *phTracer = reinterpret_cast<decltype(*phTracer)>( index );

        %elif re.match(r"\w+TracerSetPrologues", fname):
        auto index = reinterpret_cast<size_t>( hTracer );
        context.tracerData[ index ].xePrologueCbs = *pCoreCbs;
        if( pExtendedCbs ) context.tracerData[ index ].xexPrologueCbs = *pExtendedCbs;

        %elif re.match(r"\w+TracerSetEpilogues", fname):
        auto index = reinterpret_cast<size_t>( hTracer );
        context.tracerData[ index ].xeEpilogueCbs = *pCoreCbs;
        if( pExtendedCbs ) context.tracerData[ index ].xexEpilogueCbs = *pExtendedCbs;

        %elif re.match(r"\w+TracerSetEnabled", fname):
        auto index = reinterpret_cast<size_t>( hTracer );
        context.tracerData[ index ].enabled = enable;

        %else:
        %for item in th.get_loader_epilogue(n, tags, obj, meta):
        %if 'range' in item:
        for( size_t i = ${item['range'][0]}; ( nullptr != ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
            ${item['name']}[ i ] = reinterpret_cast<${item['type']}>( context.get() );
        %elif not item['release']:
        %if item['optional']:
        if( nullptr != ${item['name']} ) *${item['name']} = reinterpret_cast<${item['type']}>( context.get() );
        %else:
        *${item['name']} = reinterpret_cast<${item['type']}>( context.get() );
        %endif
        %endif

        %endfor
        %endif
        %if n != "xet":
        if( context.enableTracing )
        {
            // capture parameters
            ${th.make_pfncb_param_type(n, tags, obj)} params = {
                ${",\n".join(th.make_param_lines(n, tags, obj, format=["name"]))}
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].${n}EpilogueCbs.${th.get_table_name(n, tags, obj)};
                    if( nullptr != table.${th.make_pfncb_name(n, tags, obj)} )
                        table.${th.make_pfncb_name(n, tags, obj)}( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        %endif
        return result;
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endfor
} // namespace driver

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
    if( nullptr == pDdiTable )
        return ${X}_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for obj in tbl['functions']:
    %if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
    %endif
    pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 41)} = driver::${th.make_func_name(n, tags, obj)};
    %if 'condition' in obj:
#endif
    %endif

    %endfor
    return result;
}

%endfor
#if defined(__cplusplus)
};
#endif
