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
* @file xe_module.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Module
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/module.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_MODULE_HPP
#define _XE_MODULE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::module_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module creation input formats
        enum class format_t
        {
            IL_SPIRV = 0,                                   ///< Format is SPIRV IL format
            NATIVE,                                         ///< Format is device native format

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Module descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::MODULE_DESC_VERSION_CURRENT
            format_t format;                                ///< [in] Module format passed in with pInputModule
            size_t inputSize = 0;                           ///< [in] size of input IL or ISA from pInputModule.
            const uint8_t* pInputModule = nullptr;          ///< [in] pointer to IL or ISA
            const char* pBuildFlags = nullptr;              ///< [in] string containing compiler flags. See programming guide for build
                                                            ///< flags.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_handle_t m_handle;                       ///< handle of module object
        desc_t m_desc;                                  ///< descriptor of the module object

        ///////////////////////////////////////////////////////////////////////////////
        Module( void ) = delete;
        Module( 
                module_handle_t handle,                         ///< handle of module object
                desc_t desc                                     ///< descriptor of the module object
                ) :
                m_handle( handle ),
                m_desc( desc )
            {}

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

    public:
        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Module: pointer to handle of module object created
        /// 
        /// @throws result_t
        inline static Module*
        Create(
            Device* hDevice,                                ///< [in] handle of the device
            const desc_t* pDesc,                            ///< [in] pointer to module descriptor
            ModuleBuildLog* phBuildLog = nullptr            ///< [in,out][optional] pointer to handle of module's build log.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys module
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
        /// @throws result_t
        inline static void
        Destroy(
            Module* hModule                                 ///< [in] handle of the module
            );

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
        /// @throws result_t
        inline void
        GetNativeBinary(
            size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
            uint8_t* pModuleNativeBinary = nullptr          ///< [in,out][optional] byte pointer to native binary
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve global variable pointer from Module.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: device visible pointer
        /// 
        /// @throws result_t
        inline void*
        GetGlobalPointer(
            const char* pGlobalName                         ///< [in] name of function in global
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve function pointer from Module by name
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        ///     - Function pointer is no longer valid if Module is destroyed.
        /// @returns
        ///     - void*: pointer to function.
        /// 
        /// @throws result_t
        inline void*
        GetFunctionPointer(
            const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for function
    class Function
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::function_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported function creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default driver behavior
            FORCE_RESIDENCY,                                ///< force all device allocations to be resident during execution

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Function attributes
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cl_kernel_exec_info**
        enum class set_attribute_t
        {
            FUNCTION_SET_ATTR_INDIRECT_HOST_ACCESS = 0,     ///< Indicates that the function accesses host allocations indirectly
                                                            ///< (default: false)
            FUNCTION_SET_ATTR_INDIRECT_DEVICE_ACCESS,       ///< Indicates that the function accesses device allocations indirectly
                                                            ///< (default: false)
            FUNCTION_SET_ATTR_INDIRECT_SHARED_ACCESS,       ///< Indicates that the function accesses shared allocations indirectly
                                                            ///< (default: false)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Function attributes
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **CUfunction_attribute**
        enum class get_attribute_t
        {
            FUNCTION_GET_ATTR_MAX_REGS_USED = 0,            ///< Maximum device registers used for this function
            FUNCTION_GET_ATTR_NUM_THREAD_DIMENSIONS,        ///< Maximum dimensions for group for this function
            FUNCTION_GET_ATTR_MAX_SHARED_MEM_SIZE,          ///< Maximum shared memory required for this function
            FUNCTION_GET_ATTR_HAS_SPILL_FILL,               ///< Function required spill/fills.
            FUNCTION_GET_ATTR_HAS_BARRIERS,                 ///< Function contains barriers.
            FUNCTION_GET_ATTR_HAS_DPAS,                     ///< Function contains DPAs.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Function descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::FUNCTION_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags
            const char* pFunctionName = nullptr;            ///< [in] null-terminated name of function in Module

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        function_handle_t m_handle;                     ///< handle of function object
        desc_t m_desc;                                  ///< descriptor of the function object

        ///////////////////////////////////////////////////////////////////////////////
        Function( void ) = delete;
        Function( 
                function_handle_t handle,                       ///< handle of function object
                desc_t desc                                     ///< descriptor of the function object
                ) :
                m_handle( handle ),
                m_desc( desc )
            {}

        ~Function( void ) = default;

        Function( Function const& other ) = delete;
        void operator=( Function const& other ) = delete;

        Function( Function&& other ) = delete;
        void operator=( Function&& other ) = delete;

    public:
        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Function: handle of the Function object
        /// 
        /// @throws result_t
        inline static Function*
        Create(
            Module* hModule,                                ///< [in] handle of the module
            const desc_t* pDesc                             ///< [in] pointer to function descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys Function object
        /// 
        /// @details
        ///     - The application is responsible for making sure the GPU is not
        ///       currently referencing the function before it is deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this function
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same function handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        inline static void
        Destroy(
            Function* hFunction                             ///< [in] handle of the function object
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set group size for Function.
        /// 
        /// @details
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this function
        ///     - The implementation of this function should be lock-free.
        ///     - This can be called multiple times. The driver copies the group size
        ///       information when appending functions into a command list.
        /// @throws result_t
        inline void
        SetGroupSize(
            uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
            uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
            uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested group size for function given a global size for each
        ///        dimension.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        ///     - This function ignores the group size that is set using
        ///       ::FunctionSetGroupSize.
        /// @returns
        ///     - uint32_t: recommended size of group for X dimension.
        ///     - uint32_t: recommended size of group for Y dimension.
        ///     - uint32_t: recommended size of group for Z dimension.
        /// 
        /// @throws result_t
        inline std::tuple<uint32_t, uint32_t, uint32_t>
        SuggestGroupSize(
            uint32_t globalSizeX,                           ///< [in] global width for X dimension.
            uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
            uint32_t globalSizeZ                            ///< [in] global width for Z dimension.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set function argument used on function launch.
        /// 
        /// @details
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same function handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        inline void
        SetArgumentValue(
            uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
            size_t argSize,                                 ///< [in] size of argument type
            const void* pArgValue = nullptr                 ///< [in][optional] argument value represented as matching arg type. If
                                                            ///< null then argument value is considered null.
            );

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
        /// @throws result_t
        inline void
        SetAttribute(
            set_attribute_t attr,                           ///< [in] attribute to set
            uint32_t value                                  ///< [in] attribute value to set
            );

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
        /// @returns
        ///     - uint32_t: returned attribute value
        /// 
        /// @throws result_t
        inline uint32_t
        GetAttribute(
            get_attribute_t attr                            ///< [in] attribute to query
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_MODULE_HPP
