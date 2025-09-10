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
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${n}_api.cpp
 * @version v${ver}-r${rev}
 *
 */
#include "${n}_api.h"

%for obj in th.extract_objs(specs, r"function"):
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
%for line in th.make_returns_lines(n, tags, obj, meta=meta):
/// ${line}
%endfor
${obj['return_type']} ${X}_APICALL
${th.make_func_name(n, tags, obj)}(
    %for line in th.make_param_lines(n, tags, obj):
    ${line}
    %endfor
    )
{
    %if 'return_fail_value' in obj:
    ${obj['return_type']} result = ${obj['return_fail_value']};
    %else:
    ${x}_result_t result = ${X}_RESULT_SUCCESS;
    %endif
    return result;
}
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
