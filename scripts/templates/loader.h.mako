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
* @file ${name}.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.h.mako
* @endcond
*
******************************************************************************/
#ifndef _${name.upper()}_H
#define _${name.upper()}_H
#if defined(__cplusplus)
#pragma once
#endif
#include "${n}_all.h"
#include "loader.h"

%for obj in th.extract_objs(specs, r"function"):
///////////////////////////////////////////////////////////////////////////////
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
typedef ${x}_result_t (__${x}call *pfn_${th.make_func_name(n, tags, obj)}_t)(
    %for line in th.make_param_lines(n, tags, obj, format=["type", "delim"]):
    ${line}
    %endfor
    );
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor

///////////////////////////////////////////////////////////////////////////////
typedef struct _${n}api_pfntable_t
{
    %for obj in th.extract_objs(specs, r"function"):
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    ${th.append_ws("pfn_"+th.make_func_name(n, tags, obj)+"_t", 63)} ${th.make_func_name(n, tags, obj)};
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif
    %endfor
} ${n}api_pfntable_t;

///////////////////////////////////////////////////////////////////////////////
bool ${n}Load(
    void* handle,           ///< [in] driver handle
    ${n}api_pfntable_t* );  ///< [in] pointer to table of ${n} API function pointers

#endif // _${name.upper()}_H
