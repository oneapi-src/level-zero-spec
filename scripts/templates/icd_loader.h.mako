<%!
import re
from templates import helper as th
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
* @file icd_loader.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/icd_loader.h.mako
* @endcond
*
******************************************************************************/
#ifndef _${X}_${name.upper()}_H
#define _${X}_${name.upper()}_H
#if defined(__cplusplus)
#pragma once
#endif
%if re.match(r"common", name):
#include <stdint.h>
#include <string.h>
%else:
#include "${x}_all.h"
%endif

typedef struct _cl_mem* cl_mem;
typedef struct _cl_command_queue* cl_command_queue;
typedef struct _cl_context* cl_context;
typedef struct _cl_program* cl_program;

%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if re.match(r"function", obj['type']):
%if 'condition' in obj:
#if ${th.subx(x,obj['condition'])}
%endif
typedef ${x}_result_t (__${x}call *pfn_${th.make_func_name(x, obj, cls)})(
    %for line in th.make_param_lines(x, obj, cls):
    ${line}
    %endfor
    );
%if 'condition' in obj:
#endif // ${th.subx(x,obj['condition'])}
%endif
%endif
%endfor
%endfor

typedef struct _${x}_dispatch_table_t
{
%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if re.match(r"function", obj['type']):
%if 'condition' in obj:
#if ${th.subx(x,obj['condition'])}
%endif
    pfn_${th.make_func_name(x, obj, cls)} ${th.make_func_name(x, obj, cls)};
%if 'condition' in obj:
#endif // ${th.subx(x,obj['condition'])}
%endif
%endif
%endfor
%endfor
} ${x}_dispatch_table_t;

inline bool load_${x}(void *handle, void *(*funcAddressGetter)(void *handle, const char *funcName), ${x}_dispatch_table_t *outTable){
    if((0 == funcAddressGetter) || (0 == outTable)){
        return false;
    }
%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if re.match(r"function", obj['type']):
%if 'condition' in obj:
#if ${th.subx(x,obj['condition'])}
%endif
    outTable->${th.make_func_name(x, obj, cls)} = (pfn_${th.make_func_name(x, obj, cls)})funcAddressGetter(handle, "${th.make_func_name(x, obj, cls)}");
%if 'condition' in obj:
#endif // ${th.subx(x,obj['condition'])}
%endif
%endif
%endfor
%endfor
%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if re.match(r"function", obj['type']):
%if 'condition' in obj:
#if ${th.subx(x,obj['condition'])}
%endif
    if(0 == outTable->${th.make_func_name(x, obj, cls)}){
        return false;
    }
%if 'condition' in obj:
#endif // ${th.subx(x,obj['condition'])}
%endif
%endif
%endfor
%endfor
    return true;
}
#endif // _${X}_${name.upper()}_H
