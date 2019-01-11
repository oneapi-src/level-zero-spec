<%!
import re

def sub(repl, string):
    string = re.sub(r"\$x", repl, string)
    string = re.sub(r"\$Xx", repl.title(), string)
    string = re.sub(r"\$X", repl.upper(), string)
    return string

def append(string, count):
    while len(string) > count:
        count = count + 4
    string = '{str: <{width}}'.format(str=string, width=count)
    return string

def make_line(lformat, rformat, repl, a, b, c):
    rhalf = lformat%(sub(repl,a), sub(repl,b))
    lhalf = rformat%(sub(repl,c))
    return "%s%s"%(append(rhalf, 48), lhalf)

def eline(repl, item):
    return make_line("%s = %s,", "///< %s", repl, item['name'], item['value'], item['desc'])

def mline(repl, item):
    return make_line("%s %s;", "///< %s", repl, item['type'], item['name'], item['desc'])

def pline(repl, item, more):
    lformat = "%s %s," if more else "%s %s"
    return make_line(lformat, "///< %s", repl, item['type'], item['name'], item['desc'])

%>/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
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
*
* @file ${x}_${name}.h
*
%for doc in docs:
%if re.match(r"header", doc['type']):
* @brief ${sub(x, doc['desc'])}
<% break %>
%endif
%endfor
*
******************************************************************************/
#ifndef _${x.upper()}_${name.upper()}_H
#define _${x.upper()}_${name.upper()}_H
#if defined(__cplusplus)
#pragma once
#endif
#include "${x}_common.h"

%for doc in docs:
///////////////////////////////////////////////////////////////////////////////
/// @brief ${sub(x, doc['desc'])}
%if re.match(r"macro", doc['type']):
#define ${sub(x, doc['name'])}  ${sub(x, doc['value'])}

%elif re.match(r"enum", doc['type']):
typedef enum _${sub(x, doc['name'])}
{
    %for etor in doc['etors']:
    ${eline(x, etor)}
    %endfor
} ${sub(x, doc['name'])};

%elif re.match(r"struct", doc['type']):
typedef struct _${sub(x, doc['name'])}
{
    %for member in doc['members']:
    ${mline(x, member)}
    %endfor
} ${sub(x, doc['name'])};

%elif re.match(r"function", doc['type']):
/// @returns
%for item in doc['returns']:
    %if isinstance(item, dict):
    %for key, values in item.items():
/// - ::${sub(x, key)}
        %for val in values:
///     + ${sub(x, val)}
        %endfor
    %endfor
    %else:
/// - ::${sub(x, item)}
    %endif
%endfor
${x}_result_t __${x}call
  ${sub(x, doc['name'])}(
    %for param in doc['params']:
    ${pline(x, param, loop.index < len(doc['params'])-1)}
    %endfor
    );

%endif
%endfor
#endif // _${x.upper()}_${name.upper()}_H
