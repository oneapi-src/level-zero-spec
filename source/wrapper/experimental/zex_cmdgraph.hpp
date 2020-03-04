/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_cmdgraph.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Experimental APIs for CommandGraph
 *
 */
#ifndef _ZEX_CMDGRAPH_HPP
#define _ZEX_CMDGRAPH_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

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
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

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
#endif // defined(__cplusplus)
#endif // _ZEX_CMDGRAPH_HPP
