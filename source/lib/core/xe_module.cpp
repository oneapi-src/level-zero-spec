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
* @file xe_module.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Module
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/module.yml
* @endcond
*
******************************************************************************/
#include "xe_api.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Module::Module( 
        Device* pDevice,                                ///< pointer to parent object
        module_handle_t handle,                         ///< handle of module object
        desc_t desc                                     ///< descriptor of the module object
        ) :
        m_pDevice( pDevice ),
        m_handle( handle ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleCreate
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function will create and compile the module object.
    ///     - A build log can optionally be returned to the caller. Caller is
    ///       responsible for destroying build log using ::ModuleBuildLogDestroy
    ///     - Device memory will be allocated for module during creation.
    ///     - A module can be created directly from native binary format.
    ///     - A native binary object can be retrieved from a module using
    ///       ::ModuleGetNativeBinary. This can be cached to disk and to create new
    ///       modules.
    ///     - The following build options are supported:
    ///         + "--opt-disable" - Disable optimizations
    ///         + "--opt-greater-than-4GB-buffer-required" - Use 64-bit offset
    ///           calculations for buffers.
    ///         + "--opt-large-register-file" - Increase number of registers
    ///           available to threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleLoad**
    /// 
    /// @returns
    ///     - Module: pointer to handle of module object created
    /// 
    /// @throws result_t
    inline Module* 
    Module::Create(
        Device* hDevice,                                ///< [in] handle of the device
        const desc_t* pDesc,                            ///< [in] pointer to module descriptor
        ModuleBuildLog* phBuildLog                      ///< [in,out][optional] pointer to handle of module's build log.
        )
    {
        // auto result = ::xeModuleCreate( handle, hDevice, pDesc, phBuildLog );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the module before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this module
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same module handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleUnload**
    /// 
    /// @throws result_t
    inline void 
    Module::Destroy(
        Module* hModule                                 ///< [in] handle of the module
        )
    {
        // auto result = ::xeModuleDestroy( handle, hModule );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleGetNativeBinary
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - The caller can pass nullptr for pModuleNativeBinary when querying only
    ///       for size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The memory for the native binary output is associated with the module.
    ///     - The native binary output can be cached to disk and new modules can be
    ///       later constructed from the cached copy.
    ///     - The native binary will retain debugging information that is associated
    ///       with a module.
    /// 
    /// @throws result_t
    inline void 
    Module::GetNativeBinary(
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        // auto result = ::xeModuleGetNativeBinary( handle, pSize, pModuleNativeBinary );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetNativeBinary");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleGetGlobalPointer
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: device visible pointer
    /// 
    /// @throws result_t
    inline void* 
    Module::GetGlobalPointer(
        const char* pGlobalName                         ///< [in] name of function in global
        )
    {
        // auto result = ::xeModuleGetGlobalPointer( handle, pGlobalName );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetGlobalPointer");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeModuleGetFunctionPointer
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
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
    Function::Function( 
        Module* pModule,                                ///< pointer to parent object
        function_handle_t handle,                       ///< handle of function object
        desc_t desc                                     ///< descriptor of the function object
        ) :
        m_pModule( pModule ),
        m_handle( handle ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionCreate
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - Function objects should be destroyed before the Module is destroyed.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleGetFunction**
    /// 
    /// @returns
    ///     - Function: handle of the Function object
    /// 
    /// @throws result_t
    inline Function* 
    Function::Create(
        Module* hModule,                                ///< [in] handle of the module
        const desc_t* pDesc                             ///< [in] pointer to function descriptor
        )
    {
        // auto result = ::xeFunctionCreate( handle, hModule, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the function before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this function
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Function::Destroy(
        Function* hFunction                             ///< [in] handle of the function object
        )
    {
        // auto result = ::xeFunctionDestroy( handle, hFunction );
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
    ///       information when appending functions into a command list.
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
    ///     - The application may call this function from simultaneous threads.
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
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    Function::SetArgumentValue(
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        // auto result = ::xeFunctionSetArgumentValue( handle, argIndex, argSize, pArgValue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SetArgumentValue");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeFunctionSetAttribute
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetKernelExecInfo**
    /// 
    /// @throws result_t
    inline void 
    Function::SetAttribute(
        set_attribute_t attr,                           ///< [in] attribute to set
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
    ///     - The application may call this function from simultaneous threads.
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
        get_attribute_t attr                            ///< [in] attribute to query
        )
    {
        // auto result = ::xeFunctionGetAttribute( handle, attr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::GetAttribute");
    }

} // namespace xe
