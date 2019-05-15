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
#include "xe_ddi.h"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Module::Module( 
        Device* pDevice,                                ///< [in] pointer to parent object
        const desc_t& desc                              ///< [in] descriptor of the module object
        ) :
        m_pDevice( pDevice ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    ModuleBuildLog::ModuleBuildLog( 
        Module* pModule                                 ///< [in] pointer to parent object
        ) :
        m_pModule( pModule )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Function::Function( 
        Module* pModule,                                ///< [in] pointer to parent object
        const desc_t& desc                              ///< [in] descriptor of the function object
        ) :
        m_pModule( pModule ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates module object from an input IL or native binary.
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
    Module* __xecall
    Module::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* pDesc,                            ///< [in] pointer to module descriptor
        ModuleBuildLog* phBuildLog                      ///< [in,out][optional] pointer to pointer to module's build log.
        )
    {
        // auto result = ::xeModuleCreate( handle, pDevice, pDesc, phBuildLog );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::Create");

        return (Module*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
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
    void __xecall
    Module::Destroy(
        Module* pModule                                 ///< [in] pointer to the module
        )
    {
        // auto result = ::xeModuleDestroy( handle, pModule );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module build log object
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the build log before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this object
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same build log handle.
    ///     - The implementation of this function should be lock-free.
    ///     - This function can be called before or after ::ModuleDestroy for the
    ///       associated module.
    /// 
    /// @throws result_t
    void __xecall
    ModuleBuildLog::Destroy(
        ModuleBuildLog* pModuleBuildLog                 ///< [in] pointer to the module build log object.
        )
    {
        // auto result = ::xeModuleBuildLogDestroy( handle, pModuleBuildLog );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::ModuleBuildLog::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves text string for build log.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - The caller must provide memory for build log.
    ///     - The caller can pass nullptr for pBuildLog when querying only for size.
    /// 
    /// @throws result_t
    void __xecall
    ModuleBuildLog::GetString(
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        // auto result = ::xeModuleBuildLogGetString( handle, pSize, pBuildLog );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::ModuleBuildLog::GetString");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve native binary from Module.
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
    void __xecall
    Module::GetNativeBinary(
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        // auto result = ::xeModuleGetNativeBinary( handle, pSize, pModuleNativeBinary );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetNativeBinary");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve global variable pointer from Module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: device visible pointer
    /// 
    /// @throws result_t
    void* __xecall
    Module::GetGlobalPointer(
        const char* pGlobalName                         ///< [in] name of function in global
        )
    {
        // auto result = ::xeModuleGetGlobalPointer( handle, pGlobalName );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetGlobalPointer");

        return (void*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Create Function object from Module by name
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
    Function* __xecall
    Function::Create(
        Module* pModule,                                ///< [in] pointer to the module
        const desc_t* pDesc                             ///< [in] pointer to function descriptor
        )
    {
        // auto result = ::xeFunctionCreate( handle, pModule, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::Create");

        return (Function*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys Function object
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the function before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this function
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Function::Destroy(
        Function* pFunction                             ///< [in] pointer to the function object
        )
    {
        // auto result = ::xeFunctionDestroy( handle, pFunction );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve function pointer from Module by name
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
    void* __xecall
    Module::GetFunctionPointer(
        const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
        )
    {
        // auto result = ::xeModuleGetFunctionPointer( handle, pFunctionName );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Module::GetFunctionPointer");

        return (void*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set group size for Function.
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this function
    ///     - The implementation of this function should be lock-free.
    ///     - This can be called multiple times. The driver copies the group size
    ///       information when appending functions into a command list.
    /// 
    /// @throws result_t
    void __xecall
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
    /// @brief Query a suggested group size for function given a global size for each
    ///        dimension.
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
    std::tuple<uint32_t, uint32_t, uint32_t> __xecall
    Function::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension.
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
        uint32_t globalSizeZ                            ///< [in] global width for Z dimension.
        )
    {
        // auto result = ::xeFunctionSuggestGroupSize( handle, globalSizeX, globalSizeY, globalSizeZ );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SuggestGroupSize");

        return std::tuple<uint32_t, uint32_t, uint32_t>{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set function argument used on function launch.
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
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
    /// @brief Sets a function attribute
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
    void __xecall
    Function::SetAttribute(
        set_attribute_t attr,                           ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        // auto result = ::xeFunctionSetAttribute( handle, attr, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::SetAttribute");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a function attribute.
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
    uint32_t __xecall
    Function::GetAttribute(
        get_attribute_t attr                            ///< [in] attribute to query
        )
    {
        // auto result = ::xeFunctionGetAttribute( handle, attr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Function::GetAttribute");

        return uint32_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch function over one or more work groups.
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchFunction(
        Function* pFunction,                            ///< [in] pointer to the function object
        const thread_group_dimensions_t* pLaunchFuncArgs,   ///< [in] launch function arguments.
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before launching
        )
    {
        // auto result = ::xeCommandListAppendLaunchFunction( handle, pFunction, pLaunchFuncArgs, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchFunction");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch function over one or more work groups using indirect arguments.
    /// 
    /// @details
    ///     - The launch arguments need to be device visible.
    ///     - The launch arguments buffer may not be reusued until the function has
    ///       completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchFunctionIndirect(
        Function* pFunction,                            ///< [in] pointer to the function object
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before launching
        )
    {
        // auto result = ::xeCommandListAppendLaunchFunctionIndirect( handle, pFunction, pLaunchArgumentsBuffer, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchFunctionIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch multiple functions over one or more work groups using an array
    ///        of indirect arguments.
    /// 
    /// @details
    ///     - The array of launch arguments need to be device visible.
    ///     - The array of launch arguments buffer may not be reusued until the
    ///       function has completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchMultipleFunctionsIndirect(
        uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
        Function* phFunctions,                          ///< [in] handles of the function objects
        const size_t* pNumLaunchArguments,              ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of launch arguments; must be less-than or equal-to numFunctions
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain a contiguous array of
                                                        ///< launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before launching
        )
    {
        // auto result = ::xeCommandListAppendLaunchMultipleFunctionsIndirect( handle, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchMultipleFunctionsIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch host function. All work after this command in the command list
    ///        will block until host function completes.
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchHostFunc**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchHostFunction(
        host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
        void* pUserData,                                ///< [in] pointer to user data to pass to host function.
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before launching
        )
    {
        // auto result = ::xeCommandListAppendLaunchHostFunction( handle, pfnHostFunc, pUserData, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchHostFunction");
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_version_t to std::string
    std::string to_string( xe::Module::desc_version_t val )
    {
        switch( val )
        {
        case xe::Module::desc_version_t::CURRENT:
            return std::string("xe::Module::desc_version_t::CURRENT");
        };
        return std::string("xe::Module::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( xe::Module::format_t val )
    {
        switch( val )
        {
        case xe::Module::format_t::IL_SPIRV:
            return std::string("xe::Module::format_t::IL_SPIRV");
        case xe::Module::format_t::NATIVE:
            return std::string("xe::Module::format_t::NATIVE");
        };
        return std::string("xe::Module::format_t::?");
    }



    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::desc_version_t to std::string
    std::string to_string( xe::Function::desc_version_t val )
    {
        switch( val )
        {
        case xe::Function::desc_version_t::CURRENT:
            return std::string("xe::Function::desc_version_t::CURRENT");
        };
        return std::string("xe::Function::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::flag_t to std::string
    std::string to_string( xe::Function::flag_t val )
    {
        switch( val )
        {
        case xe::Function::flag_t::NONE:
            return std::string("xe::Function::flag_t::NONE");
        case xe::Function::flag_t::FORCE_RESIDENCY:
            return std::string("xe::Function::flag_t::FORCE_RESIDENCY");
        };
        return std::string("xe::Function::flag_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::set_attribute_t to std::string
    std::string to_string( xe::Function::set_attribute_t val )
    {
        switch( val )
        {
        case xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_HOST_ACCESS:
            return std::string("xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_HOST_ACCESS");
        case xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_DEVICE_ACCESS:
            return std::string("xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_DEVICE_ACCESS");
        case xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_SHARED_ACCESS:
            return std::string("xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_SHARED_ACCESS");
        };
        return std::string("xe::Function::set_attribute_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::get_attribute_t to std::string
    std::string to_string( xe::Function::get_attribute_t val )
    {
        switch( val )
        {
        case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_REGS_USED:
            return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_REGS_USED");
        case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_NUM_THREAD_DIMENSIONS:
            return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_NUM_THREAD_DIMENSIONS");
        case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_SHARED_MEM_SIZE:
            return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_SHARED_MEM_SIZE");
        case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_SPILL_FILL:
            return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_SPILL_FILL");
        case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_BARRIERS:
            return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_BARRIERS");
        case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_DPAS:
            return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_DPAS");
        };
        return std::string("xe::Function::get_attribute_t::?");
    }


#endif // _DEBUG
