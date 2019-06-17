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
* @file xet_module.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Module
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/module.yml
* @endcond
*
******************************************************************************/
#include "xet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve debug info from module.
/// 
/// @details
///     - The caller can pass nullptr for pDebugInfo when querying only for
///       size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetModuleGetDebugInfo(
    xet_module_handle_t hModule,                    ///< [in] handle of the module
    xet_module_debug_info_format_t format,          ///< [in] debug info format requested
    size_t* pSize,                                  ///< [in,out] size of debug info in bytes
    uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
    )
{
    auto pfnGetDebugInfo = xet_lib::context.ddiTable.Module.pfnGetDebugInfo;

#if _DEBUG
    if( nullptr == pfnGetDebugInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve debug info from module.
    /// 
    /// @details
    ///     - The caller can pass nullptr for pDebugInfo when querying only for
    ///       size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Module::GetDebugInfo(
        debug_info_format_t format,                     ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        auto result = static_cast<result_t>( ::xetModuleGetDebugInfo(
            reinterpret_cast<xet_module_handle_t>( getHandle() ),
            static_cast<xet_module_debug_info_format_t>( format ),
            pSize,
            pDebugInfo ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Module::GetDebugInfo" );
    }

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::debug_info_format_t to std::string
    std::string to_string( const Module::debug_info_format_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::debug_info_format_t::ELF_DWARF:
            str = "Module::debug_info_format_t::ELF_DWARF";
            break;

        default:
            str = "Module::debug_info_format_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_info_version_t to std::string
    std::string to_string( const Function::profile_info_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Function::profile_info_version_t::CURRENT:
            str = "Function::profile_info_version_t::CURRENT";
            break;

        default:
            str = "Function::profile_info_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_flag_t to std::string
    std::string to_string( const Function::profile_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(Function::profile_flag_t::REGISTER_REALLOCATION) & bits )
            str += "REGISTER_REALLOCATION | ";
        
        if( static_cast<uint32_t>(Function::profile_flag_t::FREE_REGISTER_INFO) & bits )
            str += "FREE_REGISTER_INFO | ";

        return ( str.size() > 3 ) 
            ? "Function::profile_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Function::profile_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_token_type_t to std::string
    std::string to_string( const Function::profile_token_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Function::profile_token_type_t::FREE_REGISTER:
            str = "Function::profile_token_type_t::FREE_REGISTER";
            break;

        default:
            str = "Function::profile_token_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_info_t to std::string
    std::string to_string( const Function::profile_info_t val )
    {
        std::string str;
        
        str += "Function::profile_info_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Function::profile_info_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Function::profile_info_t::numTokens : ";
        str += std::to_string(val.numTokens);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_free_register_token_t to std::string
    std::string to_string( const Function::profile_free_register_token_t val )
    {
        std::string str;
        
        str += "Function::profile_free_register_token_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Function::profile_free_register_token_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Function::profile_free_register_token_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_register_sequence_t to std::string
    std::string to_string( const Function::profile_register_sequence_t val )
    {
        std::string str;
        
        str += "Function::profile_register_sequence_t::start : ";
        str += std::to_string(val.start);
        str += "\n";
        
        str += "Function::profile_register_sequence_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

} // namespace xet
