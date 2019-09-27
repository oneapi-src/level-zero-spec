/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_module.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Module
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/module.yml
 * @endcond
 *
 */
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
    if( nullptr == pfnGetDebugInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    /// @brief Converts Kernel::profile_info_version_t to std::string
    std::string to_string( const Kernel::profile_info_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::profile_info_version_t::CURRENT:
            str = "Kernel::profile_info_version_t::CURRENT";
            break;

        default:
            str = "Kernel::profile_info_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_flag_t to std::string
    std::string to_string( const Kernel::profile_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(Kernel::profile_flag_t::REGISTER_REALLOCATION) & bits )
            str += "REGISTER_REALLOCATION | ";
        
        if( static_cast<uint32_t>(Kernel::profile_flag_t::FREE_REGISTER_INFO) & bits )
            str += "FREE_REGISTER_INFO | ";

        return ( str.size() > 3 ) 
            ? "Kernel::profile_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Kernel::profile_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_token_type_t to std::string
    std::string to_string( const Kernel::profile_token_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::profile_token_type_t::FREE_REGISTER:
            str = "Kernel::profile_token_type_t::FREE_REGISTER";
            break;

        default:
            str = "Kernel::profile_token_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_info_t to std::string
    std::string to_string( const Kernel::profile_info_t val )
    {
        std::string str;
        
        str += "Kernel::profile_info_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Kernel::profile_info_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Kernel::profile_info_t::numTokens : ";
        str += std::to_string(val.numTokens);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_free_register_token_t to std::string
    std::string to_string( const Kernel::profile_free_register_token_t val )
    {
        std::string str;
        
        str += "Kernel::profile_free_register_token_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Kernel::profile_free_register_token_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Kernel::profile_free_register_token_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_register_sequence_t to std::string
    std::string to_string( const Kernel::profile_register_sequence_t val )
    {
        std::string str;
        
        str += "Kernel::profile_register_sequence_t::start : ";
        str += std::to_string(val.start);
        str += "\n";
        
        str += "Kernel::profile_register_sequence_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

} // namespace xet
