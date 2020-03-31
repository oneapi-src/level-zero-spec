/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_api.hpp
 * @version v1.0-r0.9.277
 *
 */
#ifndef _ZEX_API_HPP
#define _ZEX_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "zex_api.h"

// 'core' C++ API headers
#include "ze_api.hpp"

#pragma region common
namespace zex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command graph object
    class CommandGraph;
    struct _command_graph_handle_t;
    using command_graph_handle_t = _command_graph_handle_t*;

} // namespace zex

namespace zex
{
} // namespace zex

namespace zex
{
    using result_t = ze::result_t;
    using exception_t = ze::exception_t;

} // namespace zex
#pragma endregion
#pragma region cmdlist
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
#pragma endregion
#pragma region cmdgraph
namespace zex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command graph
    class CommandGraph
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zex_command_graph_desc_t
        enum class desc_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command graph creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief CommandGraph descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZEX_COMMAND_GRAPH_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_graph_handle_t m_handle = nullptr;      ///< handle of command graph object
        ze::Device* m_pDevice;                          ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command graph object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandGraph( void ) = delete;
        CommandGraph( 
            ze::Device* pDevice,                            ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command graph object
            );

        ~CommandGraph( void ) = default;

        CommandGraph( CommandGraph const& other ) = delete;
        void operator=( CommandGraph const& other ) = delete;

        CommandGraph( CommandGraph&& other ) = delete;
        void operator=( CommandGraph&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a command graph on the device for submitting commands to any
        ///        command queue.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - CommandGraph*: pointer to handle of command graph object created
        /// 
        /// @throws result_t
        static CommandGraph* __zecall
        Create(
            ze::Device* pDevice,                            ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command graph descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a command graph.
        /// 
        /// @details
        ///     - The implementation of this function will immediately free all Host
        ///       allocations associated with this command graph.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command graph handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __zecall
        Destroy(
            CommandGraph* pCommandGraph                     ///< [in][release] pointer to command graph object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes a command graph; ready to be executed by a command queue.
        /// 
        /// @details
        ///     - The command graph will optimize the execution order of the command
        ///       lists.
        ///     - A command list may **not** be reset after the command graph is closed.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command graph handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        Close(
            void
            );

    };

} // namespace zex

namespace zex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::desc_version_t to std::string
    std::string to_string( const CommandGraph::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::flag_t to std::string
    std::string to_string( const CommandGraph::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::desc_t to std::string
    std::string to_string( const CommandGraph::desc_t val );

} // namespace zex
#pragma endregion
#endif // defined(__cplusplus)
#endif // _ZEX_API_HPP