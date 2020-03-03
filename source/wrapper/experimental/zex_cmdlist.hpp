/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_cmdlist.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Experimental APIs for Command List
 *
 */
#ifndef _ZEX_CMDLIST_HPP
#define _ZEX_CMDLIST_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList : public ze::CommandList
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::CommandList::CommandList;

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reserve a section of contiguous command buffer space within the
        ///        command list.
        /// 
        /// @details
        ///     - The pointer returned is valid for both Host and device access.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: pointer to command buffer space reserved
        /// 
        /// @throws result_t
        void* __zecall
        ReserveSpace(
            size_t size                                     ///< [in] size (in bytes) to reserve
            );

    };

} // namespace zex

namespace zex
{
} // namespace zex
#endif // defined(__cplusplus)
#endif // _ZEX_CMDLIST_HPP
