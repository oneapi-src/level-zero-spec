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
* @file xe_module.inl
*
* @brief C++ wrapper of Intel Xe Driver APIs for Module
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/module.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_MODULE_INL
#define _XE_MODULE_INL
#if defined(__cplusplus)
#pragma once
#include "xe_module.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the event before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this module
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleUnload**
    /// 
    /// @throws result_t
    inline void 
    Module::Destroy(
        void
        )
    {
        // auto result = ::xeModuleDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleBuildLogDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the event before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this object
    ///     - The implementation of this function should be lock-free.
    ///     - This function can be called before or after ::ModuleDestroy for the
    ///       associated module.
    /// 
    /// @throws result_t
    inline void 
    Module::BuildLogDestroy(
        module_build_log_handle_t hModuleBuildLog       ///< [in] handle of the module build log object.
        )
    {
        // auto result = ::xeModuleBuildLogDestroy( handle, hModuleBuildLog->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::BuildLogDestroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleBuildLogGetString
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - uint32_t: size of build log string.
    ///     - char*: pointer to null-terminated string of the log.
    /// 
    /// @throws result_t
    inline std::tuple<uint32_t, char*> 
    Module::BuildLogGetString(
        module_build_log_handle_t hModuleBuildLog       ///< [in] handle of the module build log object.
        )
    {
        // auto result = ::xeModuleBuildLogGetString( handle, hModuleBuildLog->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::BuildLogGetString");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleGetNativeBinary
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - The memory for the native binary output is associated with the module.
    ///       The output pointer should not be accessed after a module has been
    ///       destroyed.
    ///     - The native binary output can be cached to disk and new modules can be
    ///       later constructed from the cached copy.
    ///     - The native binary will retain debugging information that is associated
    ///       with a module.
    /// 
    /// @returns
    ///     - uint32_t: size of native binary.
    ///     - char*: pointer to native binary
    /// 
    /// @throws result_t
    inline std::tuple<uint32_t, char*> 
    Module::GetNativeBinary(
        void
        )
    {
        // auto result = ::xeModuleGetNativeBinary( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetNativeBinary");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleCreateFunction
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - Function objects should be destroyed before the Module is destroyed.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleGetFunction**
    /// 
    /// @returns
    ///     - function_handle_t: handle of the Function object
    /// 
    /// @throws result_t
    inline function_handle_t 
    Module::CreateFunction(
        const function_desc_t* pDesc                    ///< [in] pointer to function descriptor
        )
    {
        // auto result = ::xeModuleCreateFunction( handle, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::CreateFunction");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleGetFunctionPointer
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - Function pointer is no longer valid if Module is destroyed.
    /// 
    /// @returns
    ///     - void*: pointer to function.
    /// 
    /// @throws result_t
    inline void* 
    Module::GetFunctionPointer(
        const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
        )
    {
        // auto result = ::xeModuleGetFunctionPointer( handle, pFunctionName );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetFunctionPointer");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the event before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this function
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Function::Destroy(
        void
        )
    {
        // auto result = ::xeFunctionDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionSetGroupSize
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this function
    ///     - The implementation of this function should be lock-free.
    ///     - This can be called multiple times. The driver copies the group size
    ///       information when encoding dispatch functions into a command list.
    /// 
    /// @throws result_t
    inline void 
    Function::SetGroupSize(
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
        )
    {
        // auto result = ::xeFunctionSetGroupSize( handle, groupSizeX, groupSizeY, groupSizeZ );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SetGroupSize");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionSuggestGroupSize
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function ignores the group size that is set using
    ///       ::FunctionSetGroupSize.
    /// 
    /// @returns
    ///     - uint32_t: recommended size of group for X dimension.
    ///     - uint32_t: recommended size of group for Y dimension.
    ///     - uint32_t: recommended size of group for Z dimension.
    /// 
    /// @throws result_t
    inline std::tuple<uint32_t, uint32_t, uint32_t> 
    Function::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension.
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
        uint32_t globalSizeZ                            ///< [in] global width for Z dimension.
        )
    {
        // auto result = ::xeFunctionSuggestGroupSize( handle, globalSizeX, globalSizeY, globalSizeZ );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SuggestGroupSize");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionSetArgumentValue
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Function::SetArgumentValue(
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in] argument value represented as matching arg type
        )
    {
        // auto result = ::xeFunctionSetArgumentValue( handle, argIndex, argSize, pArgValue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SetArgumentValue");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionSetAttribute
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetKernelExecInfo**
    /// 
    /// @throws result_t
    inline void 
    Function::SetAttribute(
        function_set_attribute_t attr,                  ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        // auto result = ::xeFunctionSetAttribute( handle, attr, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SetAttribute");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionGetAttribute
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuFuncGetAttribute**
    /// 
    /// @returns
    ///     - uint32_t: returned attribute value
    /// 
    /// @throws result_t
    inline uint32_t 
    Function::GetAttribute(
        function_get_attribute_t attr                   ///< [in] attribute to query
        )
    {
        // auto result = ::xeFunctionGetAttribute( handle, attr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::GetAttribute");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_MODULE_INL
