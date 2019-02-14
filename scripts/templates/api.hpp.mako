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
* @file ${x}_${name}.hpp
*
* @brief C++ wrapper of ${th.subx(x, header['desc'])}
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/${name}.yml
* @endcond
*
******************************************************************************/
#ifndef _${X}_${name.upper()}_HPP
#define _${X}_${name.upper()}_HPP
#if defined(__cplusplus)
#pragma once
#endif
%if re.match(r"common", name):
#include "${x}_common.hpp"
%else:
#include "${x}_common.h"
%endif

%for obj in objects:
%for class in th.get_class_list(obj):
///////////////////////////////////////////////////////////////////////////////
%if 'condition' in obj:
#if ${th.subx(x,obj['condition'])}
%endif
%for line in th.make_desc_lines(x, obj):
/// ${line}
%endfor
%for line in th.make_details_lines(x, obj):
/// ${line}
%endfor
## MACRO ######################################################################
%if re.match(r"macro", obj['type']):
#define ${th.subx(x, obj['name'])}  ${th.subx(x, obj['value'])}
%if 'altvalue' in obj:
#else
#define ${th.subx(x, obj['name'])}  ${th.subx(x, obj['altvalue'])}
%endif
## TYPEDEF ####################################################################
%elif re.match(r"typedef", obj['type']):
%if 'params' in obj:
typedef ${obj['returns']}(__${x}call *${th.subx(x, obj['name'])})(
  %for line in th.make_param_lines(x, obj):
  ${line}
  %endfor
  );
%else:
typedef ${th.subx(x, obj['value'])} ${th.subx(x, obj['name'])};
%endif
## ENUM #######################################################################
%elif re.match(r"enum", obj['type']):
typedef enum _${th.subx(x, obj['name'])}
{
    %for line in th.make_etor_lines(x, obj):
    ${line}
    %endfor

} ${th.subx(x, obj['name'])};
## STRUCT #####################################################################
%elif re.match(r"struct", obj['type']):
typedef struct _${th.subx(x, obj['name'])}
{
    %for line in th.make_member_lines(x, obj):
    ${line}
    %endfor

} ${th.subx(x, obj['name'])};
## FUNCTION ###################################################################
%elif re.match(r"function", obj['type']):
/// 
%for line in th.make_return_lines(x, obj, cls):
/// ${line}
%endfor
${x}_result_t __${x}call
  ${th.make_func_name(x, obj)}(
    %for line in th.make_param_lines(x, obj):
    ${line}
    %endfor
    );
## HANDLE #####################################################################
%elif re.match(r"handle", obj['type']):
typedef struct _${th.subx(x, obj['name'])} *${th.subx(x, obj['name'])};
%endif
%if 'condition' in obj:
#endif // ${th.subx(x,obj['condition'])}
%endif

%endfor
%endfor
#endif // _${X}_${name.upper()}_HPP
