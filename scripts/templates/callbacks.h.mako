<%
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
 * @file ${n}_callbacks.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/${section}
 * @endcond
 *
 */
#ifndef _${N}_CALLBACKS_H
#define _${N}_CALLBACKS_H
#if defined(__cplusplus)
#pragma once
#endif
#include "${n}_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

%for tbl in th.get_pfncbtables(specs, meta, n, tags):
%for obj in tbl['functions']:
///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for ${th.make_func_name(n, tags, obj)} 
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
typedef struct _${th.make_pfncb_param_type(n, tags, obj)}
{
    %for line in th.make_param_lines(n, tags, obj, format=["type*", "name"]):
    ${line};
    %endfor
} ${th.make_pfncb_param_type(n, tags, obj)};
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for ${th.make_func_name(n, tags, obj)} 
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
typedef void (__${x}call *${th.make_pfncb_type(n, tags, obj)})(
    ${th.make_pfncb_param_type(n, tags, obj)}* params,
    ${x}_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ${tbl['name']} callback functions pointers
typedef struct _${tbl['type']}
{
    %for obj in tbl['functions']:
    %if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
    %endif
    ${th.append_ws(th.make_pfncb_type(n, tags, obj), 63)} ${th.make_pfncb_name(n, tags, obj)};
    %if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
    %endif
    %endfor
} ${tbl['type']};

%endfor
///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _${n}_callbacks_t
{
%for tbl in th.get_pfncbtables(specs, meta, n, tags):
    ${th.append_ws(tbl['type'], 35)} ${tbl['name']};
%endfor
} ${n}_callbacks_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _${N}_CALLBACKS_H