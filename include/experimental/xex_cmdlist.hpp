/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_cmdlist.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Experimental APIs for Command List
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/cmdlist.yml
 * @endcond
 *
 */
#ifndef _XEX_CMDLIST_HPP
#define _XEX_CMDLIST_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList : public xe::CommandList
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using xe::CommandList::CommandList;

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
        void* __xecall
        ReserveSpace(
            size_t size                                     ///< [in] size (in bytes) to reserve
            );

    };

} // namespace xex

namespace xex
{
} // namespace xex
#endif // defined(__cplusplus)
#endif // _XEX_CMDLIST_HPP
