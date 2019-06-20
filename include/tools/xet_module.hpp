/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_module.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Module
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/module.yml
 * @endcond
 *
 */
#ifndef _XET_MODULE_HPP
#define _XET_MODULE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module : public xe::Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module debug info formats.
        enum class debug_info_format_t
        {
            ELF_DWARF,                                      ///< Format is ELF/DWARF

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using xe::Module::Module;

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

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
        /// @throws result_t
        void __xecall
        GetDebugInfo(
            debug_info_format_t format,                     ///< [in] debug info format requested
            size_t* pSize,                                  ///< [in,out] size of debug info in bytes
            uint8_t* pDebugInfo = nullptr                   ///< [in,out][optional] byte pointer to debug info
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve all function names in the module.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetFunctionNames(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of names available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of names.
                                                            ///< if count is larger than the number of names available, then the driver
                                                            ///< will update the value with the correct number of names available.
            const char** pNames = nullptr                   ///< [in,out][optional][range(0, *pCount)] array of names of functions
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for function
    class Function : public xe::Function
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::xet_profile_info_t
        enum class profile_info_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supportted profile features
        enum class profile_flag_t
        {
            REGISTER_REALLOCATION = XE_BIT(0),              ///< request the compiler attempt to minimize register usage as much as
                                                            ///< possible to allow for instrumentation
            FREE_REGISTER_INFO = XE_BIT(1),                 ///< request the compiler generate free register info

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported profile token types
        enum class profile_token_type_t
        {
            FREE_REGISTER,                                  ///< GRF info

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profiling meta-data for instrumentation
        struct profile_info_t
        {
            profile_info_version_t version = profile_info_version_t::CURRENT;   ///< [in] ::XET_PROFILE_INFO_VERSION_CURRENT
            profile_flag_t flags;                           ///< [out] indicates which flags were enabled during compilation
            uint32_t numTokens;                             ///< [out] number of tokens immediately following this structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile free register token detailing unused registers in the current
        ///        function
        struct profile_free_register_token_t
        {
            profile_token_type_t type;                      ///< [out] type of token
            uint32_t size;                                  ///< [out] total size of the token, in bytes
            uint32_t count;                                 ///< [out] number of register sequences immediately following this
                                                            ///< structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile register sequence detailing consecutive bytes, all of which
        ///        are unused
        struct profile_register_sequence_t
        {
            uint32_t start;                                 ///< [out] starting byte in the register table, representing the start of
                                                            ///< unused bytes in the current function
            uint32_t count;                                 ///< [out] number of consecutive bytes in the sequence, starting from start

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using xe::Function::Function;

        ~Function( void ) = default;

        Function( Function const& other ) = delete;
        void operator=( Function const& other ) = delete;

        Function( Function&& other ) = delete;
        void operator=( Function&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

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
        /// @returns
        ///     - profile_info_t: pointer to profile info
        /// 
        /// @throws result_t
        profile_info_t __xecall
        GetProfileInfo(
            void
            );

    };

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::debug_info_format_t to std::string
    std::string to_string( const Module::debug_info_format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_info_version_t to std::string
    std::string to_string( const Function::profile_info_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_flag_t to std::string
    std::string to_string( const Function::profile_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_info_t to std::string
    std::string to_string( const Function::profile_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_token_type_t to std::string
    std::string to_string( const Function::profile_token_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_free_register_token_t to std::string
    std::string to_string( const Function::profile_free_register_token_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Function::profile_register_sequence_t to std::string
    std::string to_string( const Function::profile_register_sequence_t val );

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_MODULE_HPP
