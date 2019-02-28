<%!
import re
import extended_helper as th
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
* @file ${x}_${name}.h
*
* @brief ${th.subx(x, header['desc'])}
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/${name}.yml
* @endcond
*
******************************************************************************/

#include "${name}.h"

namespace L0 {

%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if re.match(r"function", obj['type']):
%if name == th.class_to_actor_name(cls):
${x}_result_t __${x}call ${th.make_func_name(x, obj, cls)}(
                                %for line in th.make_param_lines_short(x, obj, cls):
                                ${line}
                                %endfor
    ){
    auto obj = ${th.make_driver_frontend_class_name(name)}::fromHandle(${th.get_param(obj, cls, 0)['name']});
    return obj->${th.make_driver_frontend_class_member_func_declaration_name(x, obj, cls)}(${th.make_params_list_single_line(obj, cls, 1, False)});
}

%endif
%endif
%endfor
%endfor
} // namespace L0

