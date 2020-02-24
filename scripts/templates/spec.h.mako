<%!
import re
from templates import helper as th
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
 * @file ${n}_${name}.h
 *
 * @brief ${th.subt(n, tags, header['desc'])}
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/${section}/${name}.yml
 * @endcond
 *
 */
 
#ifndef _${N}_${name.upper()}_H
#define _${N}_${name.upper()}_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_${N}_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
%for item in header['includes']:
#include "${re.sub(r"\$h", "h", th.subt(n, tags, item))}"
%endfor

#if defined(__cplusplus)
extern "C" {
#endif

%for obj in objects:
%if not re.match(r"class", obj['type']):
///////////////////////////////////////////////////////////////////////////////
## MACRO ######################################################################
%if re.match(r"macro", obj['type']):
#ifndef ${th.make_macro_name(n, tags, obj, params=False)}
%endif
## CONDITION-START ############################################################
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
## DESCRIPTION ################################################################
%for line in th.make_desc_lines(n, tags, obj):
/// ${line}
%endfor
%for line in th.make_details_lines(n, tags, obj):
/// ${line}
%endfor
## MACRO ######################################################################
%if re.match(r"macro", obj['type']):
#define ${th.make_macro_name(n, tags, obj)}  ${th.subt(n, tags, obj['value'])}
%if 'altvalue' in obj:
#else
#define ${th.make_macro_name(n, tags, obj)}  ${th.subt(n, tags, obj['altvalue'])}
%endif
## TYPEDEF ####################################################################
%elif re.match(r"typedef", obj['type']):
%if 'params' in obj:
typedef ${obj['returns']}(__${x}call *${th.make_type_name(n, tags, obj)})(
    %for line in th.make_param_lines(n, tags, obj):
    ${line}
    %endfor
    );
%else:
typedef ${th.subt(n, tags, obj['value'])} ${th.make_type_name(n, tags, obj)};
%endif
## ENUM #######################################################################
%elif re.match(r"enum", obj['type']):
typedef enum _${th.make_type_name(n, tags, obj)}
{
    %for line in th.make_etor_lines(n, tags, obj):
    ${line}
    %endfor

} ${th.make_type_name(n, tags, obj)};
## STRUCT/UNION ###############################################################
%elif re.match(r"struct|union", obj['type']):
typedef ${obj['type']} _${th.make_type_name(n, tags, obj)}
{
    %for line in th.make_member_lines(n, tags, obj):
    ${line}
    %endfor

} ${th.make_type_name(n, tags, obj)};
## FUNCTION ###################################################################
%elif re.match(r"function", obj['type']):
/// 
%for line in th.make_returns_lines(n, tags, obj, meta=meta):
/// ${line}
%endfor
${x}_result_t __${x}call
${th.make_func_name(n, tags, obj)}(
    %for line in th.make_param_lines(n, tags, obj):
    ${line}
    %endfor
    );
## HANDLE #####################################################################
%elif re.match(r"handle", obj['type']):
%if 'alias' in obj:
typedef ${th.subt(n, tags, obj['alias'])} ${th.subt(n, tags, obj['name'])};
%else:
typedef struct _${th.subt(n, tags, obj['name'])} *${th.subt(n, tags, obj['name'])};
%endif
%endif
## CONDITION-END ##############################################################
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif
## MACRO ######################################################################
%if re.match(r"macro", obj['type']):
#endif // ${th.make_macro_name(n, tags, obj, params=False)}
%endif

%endif  # not re.match(r"class", obj['type'])
%endfor # obj in objects
## FORWARD-DECLARE STRUCTS ####################################################
%if re.match(r"common", name):
%for obj in th.extract_objs(specs, 'struct'):
///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ${th.make_type_name(n, tags, obj)}
typedef struct _${th.make_type_name(n, tags, obj)} ${th.make_type_name(n, tags, obj)};

%endfor

%endif
#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _${N}_${name.upper()}_H
