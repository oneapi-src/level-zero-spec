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
    inline void Module::Destroy(
        )
    {
        // auto result = ::xeModuleDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleGetNativeBinary
    inline void Module::GetNativeBinary(
        uint32_t* pSize,                                ///< [out] size of native binary.
        char** pModuleNativeBinary                      ///< [out] pointer to native binary
        )
    {
        // auto result = ::xeModuleGetNativeBinary( handle, pSize, pModuleNativeBinary );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetNativeBinary");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleCreateFunction
    inline void Module::CreateFunction(
        const function_desc_t* pDesc,                   ///< [in] pointer to function descriptor
        function_handle_t* phFunction                   ///< [out] handle of the Function object
        )
    {
        // auto result = ::xeModuleCreateFunction( handle, pDesc, phFunction );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::CreateFunction");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleGetFunctionPointer
    inline void Module::GetFunctionPointer(
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        // auto result = ::xeModuleGetFunctionPointer( handle, pFunctionName, pfnFunction );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetFunctionPointer");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionDestroy
    inline void Function::Destroy(
        )
    {
        // auto result = ::xeFunctionDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionSetGroupSize
    inline void Function::SetGroupSize(
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
    inline void Function::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension.
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
        )
    {
        // auto result = ::xeFunctionSuggestGroupSize( handle, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SuggestGroupSize");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionSetArgumentValue
    inline void Function::SetArgumentValue(
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
    inline void Function::SetAttribute(
        function_set_attribute_t attr,                  ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        // auto result = ::xeFunctionSetAttribute( handle, attr, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SetAttribute");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionGetAttribute
    inline void Function::GetAttribute(
        function_get_attribute_t attr,                  ///< [in] attribute to query
        uint32_t* pValue                                ///< [out] returned attribute value
        )
    {
        // auto result = ::xeFunctionGetAttribute( handle, attr, pValue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::GetAttribute");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_MODULE_INL
