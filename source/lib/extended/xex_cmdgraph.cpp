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
* @file xex_cmdgraph.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Extended APIs for CommandGraph
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/extended/cmdgraph.yml
* @endcond
*
******************************************************************************/
#include "xex_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command graph on the device for submitting commands to any
///        command queue.
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
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xexCommandGraphCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
    xex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
    )
{
    auto pfnCreate = xex_lib::context.ddiTable.CommandGraph.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hDevice, desc, phCommandGraph );
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xexCommandGraphDestroy(
    xex_command_graph_handle_t hCommandGraph        ///< [in][release] handle of command graph object to destroy
    )
{
    auto pfnDestroy = xex_lib::context.ddiTable.CommandGraph.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hCommandGraph );
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xexCommandGraphClose(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    )
{
    auto pfnClose = xex_lib::context.ddiTable.CommandGraph.pfnClose;

#if _DEBUG
    if( nullptr == pfnClose )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnClose( hCommandGraph );
}

} // extern "C"

namespace xex
{
    ///////////////////////////////////////////////////////////////////////////////
    CommandGraph::CommandGraph( 
        xe::Device* pDevice,                            ///< [in] pointer to owner object
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
    CommandGraph* __xecall
    CommandGraph::Create(
        xe::Device* pDevice,                            ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command graph descriptor
        )
    {
        xex_command_graph_handle_t hCommandGraph;

        auto result = static_cast<result_t>( ::xexCommandGraphCreate(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const xex_command_graph_desc_t*>( desc ),
            &hCommandGraph ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xex::CommandGraph::Create" );

        CommandGraph* pCommandGraph = nullptr;

        try
        {
            pCommandGraph = new CommandGraph( pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandGraph;
            pCommandGraph = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xex::CommandGraph::Create" );
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
    void __xecall
    CommandGraph::Destroy(
        CommandGraph* pCommandGraph                     ///< [in][release] pointer to command graph object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xexCommandGraphDestroy(
            reinterpret_cast<xex_command_graph_handle_t>( pCommandGraph->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xex::CommandGraph::Destroy" );

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
    void __xecall
    CommandGraph::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::xexCommandGraphClose(
            reinterpret_cast<xex_command_graph_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xex::CommandGraph::Close" );
    }

} // namespace xex

namespace xex
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

} // namespace xex
