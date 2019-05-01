<%!
import re
from templates import helper as th
%><%
    x=tags['$x']
    X=x.upper()
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

#include <cassert>
#include <mutex>

#if defined(__linux__)
#  include <dlfcn.h>
#  include <dirent.h>
#  include <sys/types.h>
#  include <string>
#  include <fstream>
// On Linux, use /etc/intel/level_zero/icd.d file entries (each file in this directory should 
//             have a single line of text. This line of text should point to the driver's main .so
void* ICD_LOAD_DRIVER_LIBRARY() {
    auto lib = dlopen("liblevel_zero.so", RTLD_LAZY|RTLD_LOCAL);
    if(lib != NULL){
        return lib;
    }

    std::string l0IcdsPath = "/etc/intel/level_zero/icd.d";
    DIR *l0DriversDir = opendir(l0IcdsPath.c_str());
    if (NULL == l0DriversDir){
        return NULL;
    }

    lib = NULL;
    struct dirent *driverEntry = readdir(l0DriversDir);
    for(;driverEntry != NULL; driverEntry = readdir(l0DriversDir)){
        if(DT_REG != driverEntry->d_type){
            continue;
        }
        std::string driverPath;
        std::ifstream(l0IcdsPath + "/" + driverEntry->d_name) >> driverPath;
        if(driverPath.empty()){
            continue;
        }

        if(*driverPath.rbegin() == '\n'){
            driverPath = driverPath.substr(driverPath.size() - 1);
        }

        lib = dlopen(driverPath.c_str(), RTLD_LAZY|RTLD_LOCAL);
        if(lib != NULL){
            // TODO : Add support for multiplexing
            //        Currently, return first that was loaded succesfully
            break;
        }
        closedir(l0DriversDir);
    }
    
    return lib;
}
#  define ICD_LOAD_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#  include <Windows.h>
// On Windows, use SOFTWARE\\Intel\\L0\\Drivers\\PATH_TO_LEVEL_ZERO_DLL (DWORD:0/1)
//             (where 0 = use this library, 1 = skip this library) or use level_zero.dll from 
//             process directory
// TODO : Add support for HKR keys
// TODO : Add support for 32-bit
HMODULE ICD_LOAD_DRIVER_LIBRARY() {
    auto lib = LoadLibraryA("level_zero.dll");
    if(lib != NULL){
        return lib;
    }

    HKEY driversKey = 0;
    const char* l0regPath = "SOFTWARE\\Intel\\IGFX\\L0\\Drivers";
    auto result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, l0regPath, 0, KEY_READ, &driversKey);
    if (ERROR_SUCCESS != result){
        return NULL;
    }

    DWORD it = 0;
    lib = NULL;
    for(;true; ++it){
        char driverPath[4096] = { 0 };
        DWORD driverPathMaxSize = sizeof(driverPath);
        DWORD driverPathRegType = 0;
        DWORD skipDriverValue = 0;
        DWORD skipDriverValueMaxSize = sizeof(skipDriverValueMaxSize);

        result = RegEnumValueA(driversKey, it,
                               driverPath, &driverPathMaxSize,
                               NULL, &driverPathRegType,
                               (LPBYTE)&skipDriverValue, &skipDriverValueMaxSize);
        if (ERROR_SUCCESS != result)
        {
            break; // no more keys
        }

        if (REG_DWORD != driverPathRegType)
        {
            assert(0);
            continue;
        }

        if (skipDriverValue)
        {
            // 0 indicates - use this driver, 1 indicates - skip
            continue;
        }

        lib = LoadLibraryA(driverPath);
        if(lib != NULL){
            // TODO : Add support for multiplexing
            //        Currently, return first that was loaded succesfully
            break;
        }
    }
    result = RegCloseKey(driversKey);
    assert(ERROR_SUCCESS == result);
    return lib;
}
#  define ICD_LOAD_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#  error "Unsupported OS"
#endif

xe_dispatch_table_t dispatchTable = {};
bool dispatchTableInitialized = false;

#if defined(__cplusplus)
extern "C" {
#endif

${x}_result_t __${x}call ${x}Init(${x}_init_flag_t flags){
    static std::mutex crit;
    {
        std::lock_guard<std::mutex> lockGuard{crit};
        
        if(dispatchTableInitialized){
            return dispatchTable.${x}Init(flags);
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
    return dispatchTable.${x}Init(flags);
}

%for obj in objects:
%if re.match(r"function", obj['type']):
%if not "Init" in th.make_func_name(n, tags, obj):
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
${x}_result_t __${x}call ${th.make_func_name(n, tags, obj)}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
    ){
    if(dispatchTableInitialized == false){
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.${th.make_func_name(n, tags, obj)}(${th.make_param_call_str("", obj)});
}
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif
%endif
%endif
%endfor

#if defined(__cplusplus)
};
#endif
