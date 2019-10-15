/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_debug.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Program Debug
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/debug.yml
 * @endcond
 *
 */
#ifndef _ZET_DEBUG_HPP
#define _ZET_DEBUG_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for Debug API
    class Debug
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug attach flags.
        enum class attach_flags_t
        {
            DEBUG_ATTACH_NONE = 0,                          ///< No attach flags

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        debug_session_handle_t* m_hDebug;               ///< [in] debug session handle

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Debug( void ) = delete;
        Debug( 
            debug_session_handle_t* hDebug                  ///< [in] debug session handle
            );

        ~Debug( void ) = default;

        Debug( Debug const& other ) = delete;
        void operator=( Debug const& other ) = delete;

        Debug( Debug&& other ) = delete;
        void operator=( Debug&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHdebug( void ) const { return m_hDebug; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Attach to a device.
        /// @returns
        ///     - debug_session_handle_t: debug session handle
        /// 
        /// @throws result_t
        static debug_session_handle_t __zecall
        Attach(
            Device* pDevice,                                ///< [in] device handle
            int pid,                                        ///< [in] host process identifier
            uint64_t flags                                  ///< [in] a bit-vector of ::zet_debug_attach_flags_t
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Close a debug session.
        /// @throws result_t
        void __zecall
        Detach(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query the number of device threads for a debug session.
        /// @returns
        ///     - uint64_t: the maximal number of threads
        /// 
        /// @throws result_t
        uint64_t __zecall
        GetNumThreads(
            void
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Debug session handle
    struct _debug_session_handle_t;
    using debug_session_handle_t = _debug_session_handle_t*;

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::attach_flags_t to std::string
    std::string to_string( const Debug::attach_flags_t val );

} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_DEBUG_HPP
