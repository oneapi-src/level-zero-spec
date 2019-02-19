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
#include "${x}_common.h"
%else:
#include "${x}_common.hpp"
%endif

namespace ${x}
{
%for obj in objects:
    %for cls in obj['class']:
    ///////////////////////////////////////////////////////////////////////////////
    %if 'condition' in obj:
    #if ${th.subx(x,obj['condition'])}
    %endif
    %for line in th.make_desc_lines(None, obj):
    /// ${line}
    %endfor
    %for line in th.make_details_lines(None, obj):
    /// ${line}
    %endfor
    ## TYPEDEF ####################################################################
    %if re.match(r"typedef", obj['type']):
    using ${th.subx(None, obj['name'])} = ${th.subx(x, obj['name'])};
    ## ENUM #######################################################################
    %elif re.match(r"enum", obj['type']):
    enum class ${th.subx(None, obj['name'])}
    {
        %for line in th.make_etor_lines(None, obj, True):
        ${line}
        %endfor

    };
    ## STRUCT #####################################################################
    %elif re.match(r"struct", obj['type']):
    struct ${th.subx(None, obj['name'])}
    {
        %for line in th.make_member_lines(None, obj, True):
        ${line}
        %endfor

    };
    ## FUNCTION ###################################################################
    %elif re.match(r"function", obj['type']):
    /// 
    %for line in th.make_return_lines(None, obj, cls):
    /// ${line}
    %endfor
    inline void
      ${th.make_func_name(None, obj, cls)}(
        %for line in th.make_param_lines(None, obj, cls):
        ${line}
        %endfor
        )
    {
        auto result = ::${th.make_func_name(x, obj, cls)}(
            %for line in th.make_param_lines(None, obj, cls):
            ${line}
            %endfor
            );
    }
    ## HANDLE #####################################################################
    %elif re.match(r"handle", obj['type']):
    using ${th.subx(None, obj['name'])} = ${th.subx(x, obj['name'])};
    %endif
    %if 'condition' in obj:
    #endif // ${th.subx(x,obj['condition'])}
    %endif

    %endfor
%endfor
} // namespace ${x}
#endif // _${X}_${name.upper()}_HPP
