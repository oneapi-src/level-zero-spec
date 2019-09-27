/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_module.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Module
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/module.yml
 * @endcond
 *
 */
#ifndef _XE_MODULE_HPP
#define _XE_MODULE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::xe_module_desc_t
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
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::XE_MODULE_DESC_VERSION_CURRENT
            format_t format;                                ///< [in] Module format passed in with pInputModule
            size_t inputSize = 0;                           ///< [in] size of input IL or ISA from pInputModule.
            const uint8_t* pInputModule = nullptr;          ///< [in] pointer to IL or ISA
            const char* pBuildFlags = nullptr;              ///< [in] string containing compiler flags. See programming guide for build
                                                            ///< flags.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_handle_t m_handle;                       ///< [in] handle of module object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the module object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Module( void ) = delete;
        Module( 
            module_handle_t handle,                         ///< [in] handle of module object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the module object
            );

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates module object from an input IL or native binary.
        /// 
        /// @details
        ///     - Compiles the module for execution on the device.
        ///     - The module can only be used on the device on which it was created.
        ///     - The module can be copied to other devices within the same driver
        ///       instance by using ::xeModuleGetNativeBinary.
        ///     - The following build options are supported:
        ///         + "-xe-opt-disable" - Disable optimizations
        ///         + "-xe-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
        ///           calculations for buffers.
        ///         + "-xe-opt-large-register-file" - Increase number of registers
        ///           available to threads.
        ///     - A build log can optionally be returned to the caller. The caller is
        ///       responsible for destroying build log using ::xeModuleBuildLogDestroy.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuModuleLoad**
        /// @returns
        ///     - Module*: pointer to handle of module object created
        ///     - ModuleBuildLog*: pointer to handle of module's build log.
        /// 
        /// @throws result_t
        static Module* __xecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc,                             ///< [in] pointer to module descriptor
            ModuleBuildLog** ppBuildLog = nullptr           ///< [out][optional] pointer to pointer to module's build log.
            );

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
        /// @throws result_t
        static void __xecall
        Destroy(
            Module* pModule                                 ///< [in][release] pointer to the module
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve native binary from Module.
        /// 
        /// @details
        ///     - The native binary output can be cached to disk and new modules can be
        ///       later constructed from the cached copy.
        ///     - The native binary will retain debugging information that is associated
        ///       with a module.
        ///     - The caller can pass nullptr for pModuleNativeBinary when querying only
        ///       for size.
        ///     - The implementation will copy the native binary into a buffer supplied
        ///       by the caller.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
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
        void* __xecall
        GetGlobalPointer(
            const char* pGlobalName                         ///< [in] name of global variable in module
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve a function pointer from a module by name
        /// 
        /// @details
        ///     - The function pointer is unique for the device on which the module was
        ///       created.
        ///     - The function pointer is no longer valid if module is destroyed.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: pointer to function.
        /// 
        /// @throws result_t
        void* __xecall
        GetFunctionPointer(
            const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for buildlog
    class ModuleBuildLog
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_build_log_handle_t m_handle;             ///< [in] handle of the buildlog object
        Module* m_pModule;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        ModuleBuildLog( void ) = delete;
        ModuleBuildLog( 
            module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
            Module* pModule                                 ///< [in] pointer to owner object
            );

        ~ModuleBuildLog( void ) = default;

        ModuleBuildLog( ModuleBuildLog const& other ) = delete;
        void operator=( ModuleBuildLog const& other ) = delete;

        ModuleBuildLog( ModuleBuildLog&& other ) = delete;
        void operator=( ModuleBuildLog&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys module build log object
        /// 
        /// @details
        ///     - The implementation of this function will immediately free all Host
        ///       allocations associated with this object
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same build log handle.
        ///     - The implementation of this function should be lock-free.
        ///     - This function can be called before or after ::xeModuleDestroy for the
        ///       associated module.
        /// @throws result_t
        static void __xecall
        Destroy(
            ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves text string for build log.
        /// 
        /// @details
        ///     - The caller can pass nullptr for pBuildLog when querying only for size.
        ///     - The caller must provide memory for build log.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetString(
            size_t* pSize,                                  ///< [in,out] size of build log string.
            char* pBuildLog = nullptr                       ///< [in,out][optional] pointer to null-terminated string of the log.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for kernel
    class Kernel
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::xe_kernel_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported kernel creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default driver behavior
            FORCE_RESIDENCY,                                ///< force all device allocations to be resident during execution

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel attributes
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cl_kernel_exec_info**
        enum class set_attribute_t
        {
            KERNEL_SET_ATTR_INDIRECT_HOST_ACCESS = 0,       ///< Indicates that the function accesses host allocations indirectly
                                                            ///< (default: false)
            KERNEL_SET_ATTR_INDIRECT_DEVICE_ACCESS,         ///< Indicates that the function accesses device allocations indirectly
                                                            ///< (default: false)
            KERNEL_SET_ATTR_INDIRECT_SHARED_ACCESS,         ///< Indicates that the function accesses shared allocations indirectly
                                                            ///< (default: false)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel attributes
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **CUfunction_attribute**
        enum class get_attribute_t
        {
            KERNEL_GET_ATTR_MAX_REGS_USED = 0,              ///< Maximum device registers used for this kernel
            KERNEL_GET_ATTR_NUM_THREAD_DIMENSIONS,          ///< Maximum dimensions for group for this kernel
            KERNEL_GET_ATTR_MAX_SHARED_MEM_SIZE,            ///< Maximum shared memory required for this kernel
            KERNEL_GET_ATTR_HAS_SPILL_FILL,                 ///< Kernel required spill/fills
            KERNEL_GET_ATTR_HAS_BARRIERS,                   ///< Kernel contains barriers
            KERNEL_GET_ATTR_HAS_DPAS,                       ///< Kernel contains DPAS

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::XE_KERNEL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags
            const char* pKernelName = nullptr;              ///< [in] null-terminated name of kernel in module

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        kernel_handle_t m_handle;                       ///< [in] handle of kernel object
        Module* m_pModule;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the kernel object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Kernel( void ) = delete;
        Kernel( 
            kernel_handle_t handle,                         ///< [in] handle of kernel object
            Module* pModule,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the kernel object
            );

        ~Kernel( void ) = default;

        Kernel( Kernel const& other ) = delete;
        void operator=( Kernel const& other ) = delete;

        Kernel( Kernel&& other ) = delete;
        void operator=( Kernel&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Create a kernel object from a module by name
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuModuleGetFunction**
        /// @returns
        ///     - Kernel*: handle of the Function object
        /// 
        /// @throws result_t
        static Kernel* __xecall
        Create(
            Module* pModule,                                ///< [in] pointer to the module
            const desc_t* desc                              ///< [in] pointer to kernel descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a kernel object
        /// 
        /// @details
        ///     - All kernels must be destroyed before the module is destroyed.
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the kernel before it is deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this kernel
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same kernel handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __xecall
        Destroy(
            Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set group size for a kernel
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same function handle.
        ///     - The implementation of this function should be lock-free.
        ///     - The implementation will copy the group size information into a command
        ///       list when the function is appended.
        /// @throws result_t
        void __xecall
        SetGroupSize(
            uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
            uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
            uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested group size for a kernel given a global size for each
        ///        dimension.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        ///     - This function ignores the group size that is set using
        ///       ::xeKernelSetGroupSize.
        /// @returns
        ///     - uint32_t: recommended size of group for X dimension
        ///     - uint32_t: recommended size of group for Y dimension
        ///     - uint32_t: recommended size of group for Z dimension
        /// 
        /// @throws result_t
        std::tuple<uint32_t, uint32_t, uint32_t> __xecall
        SuggestGroupSize(
            uint32_t globalSizeX,                           ///< [in] global width for X dimension
            uint32_t globalSizeY,                           ///< [in] global width for Y dimension
            uint32_t globalSizeZ                            ///< [in] global width for Z dimension
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested max group count a cooperative kernel.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - uint32_t: recommend group count X dimension.
        ///     - uint32_t: recommend group count Y dimension.
        ///     - uint32_t: recommend group count Z dimension.
        /// 
        /// @throws result_t
        std::tuple<uint32_t, uint32_t, uint32_t> __xecall
        SuggestMaxCooperativeGroupCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set kernel argument used on kernel launch.
        /// 
        /// @details
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same function handle.
        ///     - The implementation of this function should be lock-free.
        ///     - The implementation will copy the arguments into a command list when
        ///       the function is appended.
        /// @throws result_t
        void __xecall
        SetArgumentValue(
            uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
            size_t argSize,                                 ///< [in] size of argument type
            const void* pArgValue = nullptr                 ///< [in][optional] argument value represented as matching arg type. If
                                                            ///< null then argument value is considered null.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a kernel attribute
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
        void __xecall
        SetAttribute(
            set_attribute_t attr,                           ///< [in] attribute to set
            uint32_t value                                  ///< [in] attribute value to set
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a kernel attribute.
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
        uint32_t __xecall
        GetAttribute(
            get_attribute_t attr                            ///< [in] attribute to query
            );

    };

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_version_t to std::string
    std::string to_string( const Module::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_version_t to std::string
    std::string to_string( const Kernel::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flag_t to std::string
    std::string to_string( const Kernel::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::set_attribute_t to std::string
    std::string to_string( const Kernel::set_attribute_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::get_attribute_t to std::string
    std::string to_string( const Kernel::get_attribute_t val );

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_MODULE_HPP
