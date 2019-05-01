/**************************************************************************//**
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
* @file loader.h
*
******************************************************************************/
#ifndef _LOADER_H
#define _LOADER_H
#if defined(__cplusplus)
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
#if defined(__linux__)
#  include <dlfcn.h>
#  define LOAD_DRIVER_LIBRARY(NAME) dlopen("lib"NAME".so", RTLD_LAZY|RTLD_LOCAL)
#  define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#  include <Windows.h>
#  define LOAD_DRIVER_LIBRARY(NAME) LoadLibraryA(NAME".dll")
#  define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#  error "Unsupported OS"
#endif

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
typedef struct _cl_mem* cl_mem;
typedef struct _cl_command_queue* cl_command_queue;
typedef struct _cl_context* cl_context;
typedef struct _cl_program* cl_program;
#endif


///////////////////////////////////////////////////////////////////////////////
typedef struct _xeapi_pfntable_t*  xeapi_pfntable_ptr_t;
typedef struct _xexapi_pfntable_t* xexapi_pfntable_ptr_t;
typedef struct _xetapi_pfntable_t* xetapi_pfntable_ptr_t;


namespace xe_loader
{
    ///////////////////////////////////////////////////////////////////////////////
    typedef struct _context_t
    {
        xeapi_pfntable_ptr_t   xeapi;
        xexapi_pfntable_ptr_t  xexapi;
        xetapi_pfntable_ptr_t  xetapi;
    
        bool initialized;
    } context_t;

} // namespace xe_loader

#endif // _LOADER_H