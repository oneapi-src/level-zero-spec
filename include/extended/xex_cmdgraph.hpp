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
* @file xex_cmdgraph.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Extended APIs for CommandGraph
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/extended/cmdgraph.yml
* @endcond
*
******************************************************************************/
#ifndef _XEX_CMDGRAPH_HPP
#define _XEX_CMDGRAPH_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command graph
    class CommandGraph
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::command_graph_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

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
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::COMMAND_GRAPH_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_graph_handle_t m_handle = nullptr;      ///< handle of command graph object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command graph object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandGraph( void ) = delete;
        CommandGraph( 
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t& desc                              ///< [in] descriptor of the command graph object
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
        ///     - CommandGraph: pointer to handle of command graph object created
        /// 
        /// @throws result_t
        static CommandGraph* __xecall
        Create(
            xe::Device* pDevice,                            ///< [in] pointer to the device object
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
        static void __xecall
        Destroy(
            CommandGraph* pCommandGraph                     ///< [in] pointer to command graph object to destroy
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
        void __xecall
        Close(
            void
            );

    };

} // namespace xex

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::desc_version_t to std::string
    std::string to_string( xex::CommandGraph::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandGraph::flag_t to std::string
    std::string to_string( xex::CommandGraph::flag_t val );


#endif // _DEBUG
#endif // defined(__cplusplus)
#endif // _XEX_CMDGRAPH_HPP
