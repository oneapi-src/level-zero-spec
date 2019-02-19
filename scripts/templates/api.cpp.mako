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
* @file ${x}_${name}.cpp
*
* @brief ${th.subx(x, header['desc'])}
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/${name}.yml
* @endcond
*
******************************************************************************/
#include "../include/${x}_${name}.h"

%for obj in objects:
%if re.match(r"function", obj['type']):
%for cli, cls in enumerate(obj['class']):
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
/// 
%for line in th.make_return_lines(x, obj, cls):
/// ${line}
%endfor
/*@todo: __declspec(dllexport)*/
${x}_result_t __${x}call
  ${th.make_func_name(x, obj, cls)}(
    %for line in th.make_param_lines(x, obj, cls):
    ${line}
    %endfor
    )
{
    %if not re.match(r".*DriverInit", obj['name']):
    // @todo: check_return(nullptr == get_driver(), ${X}_RESULT_ERROR_UNINITIALIZED);

    %endif
    // Check parameters
    %for key, values in th.make_param_checks(x, obj, cls).items():
    %for val in values:
    // @todo: check_return(${val}, ${key});
    %endfor
    %endfor
    /// @begin {${obj['hash'][cli]}}

    // @todo: insert <code> here

    /// @end   {${obj['hash'][cli]}}
    return ${X}_RESULT_SUCCESS;
}
%if 'condition' in obj:
#endif // ${th.subx(x,obj['condition'])}
%endif

%endfor
%endif
%endfor
