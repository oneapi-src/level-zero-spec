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
* @file ${name}.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/${name}.yml
* @endcond
*
******************************************************************************/
#pragma once

#include "${x}_${apiHeader}.h"
#include "${x}_all.h"

// for sharing
typedef struct _cl_mem* cl_mem;
typedef struct _cl_command_queue* cl_command_queue;
typedef struct _cl_context* cl_context;
typedef struct _cl_program* cl_program;

struct _${th.subx(x, handles[name]['name'])} {
};


namespace ${x} {

struct ${th.make_driver_frontend_class_name(name)} : public _${th.subx(x, handles[name]['name'])} {
    ${th.make_driver_frontend_class_name(name)}() = default;
    ${th.make_driver_frontend_class_name(name)}(const ${th.make_driver_frontend_class_name(name)} &) = delete;
    ${th.make_driver_frontend_class_name(name)}(${th.make_driver_frontend_class_name(name)} &&) = delete;
    ${th.make_driver_frontend_class_name(name)} &operator=(const ${th.make_driver_frontend_class_name(name)} &) = delete;
    ${th.make_driver_frontend_class_name(name)} &operator=(${th.make_driver_frontend_class_name(name)} &&) = delete;
    
    static ${th.make_driver_frontend_class_name(name)} *create();
    
%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if name == th.class_to_actor_name(cls):
%if re.match(r"function", obj['type']):
    virtual ${x}_result_t ${th.make_driver_frontend_class_member_func_declaration_name(x, obj, cls)}(
                                    %for line in th.make_param_lines_short_no_actor(x, obj, cls, handles):
                                    ${line}
                                    %endfor
                                    ) = 0;

%endif
%endif
%endfor
%endfor

    static ${th.make_driver_frontend_class_name(name)} *fromHandle(${th.subx(x, handles[name]['name'])} handle) {
        return static_cast<${th.make_driver_frontend_class_name(name)} *>(handle);
    }

    inline ${th.subx(x, handles[name]['name'])} toHandle() {
        return this;
    }
};

%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if name == th.class_to_actor_name(cls):
%if re.match(r"function", obj['type']):
${x}_result_t __${x}call ${th.make_func_name(x, obj, cls)}(
    %for line in th.make_param_lines_short(x, obj, cls):
    ${line}
    %endfor
    );

%endif
%endif
%endfor
%endfor
} // namespace ${x}

