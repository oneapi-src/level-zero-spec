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

} // extern "C"

namespace xet
{
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

} // namespace xet

namespace xet
{
} // namespace xet
