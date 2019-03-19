<%!
import re
from templates import helper as th
%><%
    x=context['ns'][0]
    X=context['ns'][0].upper()
    Xx=context['ns'][0].title()
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
* @file icd_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/icd_loader.cpp.mako
* @endcond
*
******************************************************************************/
#include "icd_loader.h"

#include <mutex>

#if defined(__linux__)
#  include <dlfcn.h>
#  define ICD_LOAD_DRIVER_LIBRARY() dlopen("liblevel_zero.so", RTLD_LAZY|RTLD_LOCAL)
#  define ICD_LOAD_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#  include <Windows.h>
#  define ICD_LOAD_DRIVER_LIBRARY() LoadLibraryA("level_zero.dll")
#  define ICD_LOAD_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#  error "Unsupported OS"
#endif

xe_dispatch_table_t dispatchTable = {};
bool dispatchTableInitialized = false;

#if defined(__cplusplus)
extern "C" {
#endif

${x}_result_t __${x}call ${x}DriverInit(${x}_init_flag_t flags){
    static std::mutex crit;
    {
        std::lock_guard<std::mutex> lockGuard{crit};
        
        if(dispatchTableInitialized){
            return dispatchTable.${x}DriverInit(flags);
        }
        
        auto driverLibrary = ICD_LOAD_DRIVER_LIBRARY(); // persistent handle
        dispatchTableInitialized = 
                load_${x}(driverLibrary, 
                          [](void *library, const char *funcName)->void* { return ICD_LOAD_FUNCTION_PTR(library, funcName); }, 
                          &dispatchTable);
        if(false == dispatchTableInitialized){
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        }
    }
    return dispatchTable.${x}DriverInit(flags);
}

%for obj in objects:
%if re.match(r"function", obj['type']):
%if not "DriverInit" in th.make_func_name(ns, obj):
%if 'condition' in obj:
#if ${th.sub(ns,obj['condition'])}
%endif
${x}_result_t __${x}call ${th.make_func_name(ns, obj)}(
        %for line in th.make_param_lines(ns, obj):
        ${line}
        %endfor
    ){
    if(dispatchTableInitialized == false){
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.${th.make_func_name(ns, obj)}(${th.make_forwarding_param_call_str(ns, obj)});
}
%if 'condition' in obj:
#endif // ${th.sub(ns,obj['condition'])}
%endif
%endif
%endif
%endfor

#if defined(__cplusplus)
};
#endif
