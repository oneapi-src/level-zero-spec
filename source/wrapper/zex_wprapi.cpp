/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_wprapi.cpp
 * @version v0.91-275
 *
 * @brief C++ wrapper of zex
 *
 */
#include "zex_api.hpp"
#include "ze_singleton.h"

#define _ZE_STRING(s) #s
#define ZE_STRING(s) _ZE_STRING(s)

namespace zex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reserve a section of contiguous command buffer space within the
    ///        command list.
    /// 
    /// @details
    ///     - The pointer returned is valid for both Host and device access.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to command buffer space reserved
    /// 
    /// @throws result_t
    void* __zecall
    CommandList::ReserveSpace(
        size_t size                                     ///< [in] size (in bytes) to reserve
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::zexCommandListReserveSpace(
            reinterpret_cast<zex_command_list_handle_t>( getHandle() ),
            size,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zex::CommandList::ReserveSpace" );

        return ptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    CommandGraph::CommandGraph( 
        ze::Device* pDevice,                            ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command graph object
        ) :
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command graph on the device for submitting commands to any
    ///        command queue.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - CommandGraph*: pointer to handle of command graph object created
    /// 
    /// @throws result_t
    CommandGraph* __zecall
    CommandGraph::Create(
        ze::Device* pDevice,                            ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command graph descriptor
        )
    {
        zex_command_graph_handle_t hCommandGraph;

        auto result = static_cast<result_t>( ::zexCommandGraphCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const zex_command_graph_desc_t*>( desc ),
            &hCommandGraph ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zex::CommandGraph::Create" );

        CommandGraph* pCommandGraph = nullptr;

        try
        {
            pCommandGraph = new CommandGraph( pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandGraph;
            pCommandGraph = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zex::CommandGraph::Create" );
        }

        return pCommandGraph;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command graph.
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host
    ///       allocations associated with this command graph.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command graph handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandGraph::Destroy(
        CommandGraph* pCommandGraph                     ///< [in][release] pointer to command graph object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zexCommandGraphDestroy(
            reinterpret_cast<zex_command_graph_handle_t>( pCommandGraph->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zex::CommandGraph::Destroy" );

        delete pCommandGraph;
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandGraph::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::zexCommandGraphClose(
            reinterpret_cast<zex_command_graph_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zex::CommandGraph::Close" );
    }

} // namespace zex

namespace zex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::desc_version_t to std::string
    std::string to_string( const CommandGraph::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandGraph::desc_version_t::CURRENT:
            str = "CommandGraph::desc_version_t::CURRENT";
            break;

        default:
            str = "CommandGraph::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::flag_t to std::string
    std::string to_string( const CommandGraph::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandGraph::flag_t::NONE:
            str = "CommandGraph::flag_t::NONE";
            break;

        default:
            str = "CommandGraph::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::desc_t to std::string
    std::string to_string( const CommandGraph::desc_t val )
    {
        std::string str;
        
        str += "CommandGraph::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "CommandGraph::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

} // namespace zex
