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
* @file xet_pin.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Program Instrumentation (PIN)
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/pin.yml
* @endcond
*
******************************************************************************/
#include "xet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates executable memory from a module.
/// 
/// @details
///     - The pointer returned is accessible by both the Host and the device
///       from which the module was created.
///     - The pointer is only valid to be used from within the module.
///     - The application may **not** call this function from simultaneous
///       threads with the same module handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == ptr
///         + 0 for size
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xetModuleAllocateExecutableMemory(
    xet_module_handle_t hModule,                    ///< [in] handle of the module
    size_t size,                                    ///< [in] size (in bytes) to allocate
    void** ptr                                      ///< [out] pointer to allocation
    )
{
    auto pfnAllocateExecutableMemory = xet_lib::context.ddiTable.Module.pfnAllocateExecutableMemory;

#if _DEBUG
    if( nullptr == pfnAllocateExecutableMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAllocateExecutableMemory( hModule, size, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees executable memory from a module.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same module handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetModuleFreeExecutableMemory(
    xet_module_handle_t hModule,                    ///< [in] handle of the module
    void* ptr                                       ///< [in] pointer to allocation to free
    )
{
    auto pfnFreeExecutableMemory = xet_lib::context.ddiTable.Module.pfnFreeExecutableMemory;

#if _DEBUG
    if( nullptr == pfnFreeExecutableMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnFreeExecutableMemory( hModule, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve all function names in the module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetModuleGetFunctionNames(
    xet_module_handle_t hModule,                    ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of names available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of names.
    const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
    )
{
    auto pfnGetFunctionNames = xet_lib::context.ddiTable.Module.pfnGetFunctionNames;

#if _DEBUG
    if( nullptr == pfnGetFunctionNames )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetFunctionNames( hModule, pCount, pNames );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve profiling information generated for the function.
/// 
/// @details
///     - Module must be created using the following build option:
///         + "-xet-profile-flags <n>" - enable generation of profile
///           information
///         + "<n>" must be a combination of ::xet_profile_flag_t, in hex
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFunction
///         + nullptr == pInfo
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetFunctionGetProfileInfo(
    xet_function_handle_t hFunction,                ///< [in] handle to function
    xet_profile_info_t* pInfo                       ///< [out] pointer to profile info
    )
{
    auto pfnGetProfileInfo = xet_lib::context.ddiTable.Function.pfnGetProfileInfo;

#if _DEBUG
    if( nullptr == pfnGetProfileInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetProfileInfo( hFunction, pInfo );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Changes the address of a function for the next
///        ::xeCommandListAppendLaunchFunction
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFunction
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetFunctionSetAddress(
    xet_function_handle_t hFunction,                ///< [in] handle to function
    void* ptr                                       ///< [in] address to use for function; must be allocated using ::xetModuleAllocateExecutableMemory.
                                                    ///< if address is nullptr, then resets function address to default value."
    )
{
    auto pfnSetAddress = xet_lib::context.ddiTable.Function.pfnSetAddress;

#if _DEBUG
    if( nullptr == pfnSetAddress )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetAddress( hFunction, ptr );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates executable memory from a module.
    /// 
    /// @details
    ///     - The pointer returned is accessible by both the Host and the device
    ///       from which the module was created.
    ///     - The pointer is only valid to be used from within the module.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same module handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to allocation
    /// 
    /// @throws result_t
    void* __xecall
    Module::AllocateExecutableMemory(
        size_t size                                     ///< [in] size (in bytes) to allocate
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xetModuleAllocateExecutableMemory(
            reinterpret_cast<xet_module_handle_t>( getHandle() ),
            size,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Module::AllocateExecutableMemory" );

        return ptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Frees executable memory from a module.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same module handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Module::FreeExecutableMemory(
        void* ptr                                       ///< [in] pointer to allocation to free
        )
    {
        auto result = static_cast<result_t>( ::xetModuleFreeExecutableMemory(
            reinterpret_cast<xet_module_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Module::FreeExecutableMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve all function names in the module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Module::GetFunctionNames(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of names available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of names.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
        )
    {
        auto result = static_cast<result_t>( ::xetModuleGetFunctionNames(
            reinterpret_cast<xet_module_handle_t>( getHandle() ),
            pCount,
            pNames ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Module::GetFunctionNames" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve profiling information generated for the function.
    /// 
    /// @details
    ///     - Module must be created using the following build option:
    ///         + "--profile-flags <n>" - enable generation of profile information
    ///         + "<n>" must be a combination of ::profile_flag_t, in hex
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - profile_info_t: pointer to profile info
    /// 
    /// @throws result_t
    Function::profile_info_t __xecall
    Function::GetProfileInfo(
        void
        )
    {
        xet_profile_info_t info;

        auto result = static_cast<result_t>( ::xetFunctionGetProfileInfo(
            reinterpret_cast<xet_function_handle_t>( getHandle() ),
            &info ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Function::GetProfileInfo" );

        return *reinterpret_cast<profile_info_t*>( &info );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Changes the address of a function for the next
    ///        ::xeCommandListAppendLaunchFunction
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Function::SetAddress(
        void* ptr                                       ///< [in] address to use for function; must be allocated using ::ModuleAllocateExecutableMemory.
                                                        ///< if address is nullptr, then resets function address to default value."
        )
    {
        auto result = static_cast<result_t>( ::xetFunctionSetAddress(
            reinterpret_cast<xet_function_handle_t>( getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Function::SetAddress" );
    }

} // namespace xet

namespace xet
{
} // namespace xet
