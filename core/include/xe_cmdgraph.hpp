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
* @file xe_cmdgraph.hpp
*
* @brief C++ wrapper of Intel Xe Driver APIs for CommandGraph
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdgraph.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDGRAPH_HPP
#define _XE_CMDGRAPH_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command graph
    class CommandGraph
    {
    protected:
        ::xe_command_graph_handle_t handle;               ///< handle of command graph object
        ::xe_command_graph_desc_t desc;                   ///< descriptor of the command graph object

    public:
        auto getHandle( void ) const { return handle; }
        auto getDesc( void ) const { return desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_host_pfn_t
        using host_pfn_t = ::xe_host_pfn_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_dispatch_function_arguments_version_t
        enum class dispatch_function_arguments_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_dispatch_function_arguments_t
        struct dispatch_function_arguments_t
        {
            dispatch_function_arguments_version_t version = dispatch_function_arguments_version_t::CURRENT; ///< [in] ::DISPATCH_FUNCTION_ARGUMENTS_VERSION_CURRENT
            uint32_t groupCountX = 0;                       ///< [in] width of dispatches in X dimension
            uint32_t groupCountY = 0;                       ///< [in] width of dispatches in Y dimension
            uint32_t groupCountZ = 0;                       ///< [in] width of dispatches in Z dimension

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_dispatch_function_indirect_arguments_t
        struct dispatch_function_indirect_arguments_t
        {
            uint32_t groupCountX;                           ///< [in] width of dispatches in X dimension
            uint32_t groupCountY;                           ///< [in] width of dispatches in Y dimension
            uint32_t groupCountZ;                           ///< [in] width of dispatches in Z dimension

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandGraphDestroy
        inline void Destroy(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandGraphClose
        inline void Close(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandGraphReset
        inline void Reset(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandGraphEncodeDispatchFunction
        inline void EncodeDispatchFunction(
            function_handle_t hFunction,                    ///< [in] handle of the function object
            const dispatch_function_arguments_t* pDispatchFuncArgs, ///< [in] dispatch function arguments.
            event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandGraphEncodeDispatchFunctionIndirect
        inline void EncodeDispatchFunctionIndirect(
            function_handle_t hFunction,                    ///< [in] handle of the function object
            const dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer, ///< [in] Pointer to buffer that will contain dispatch arguments.
            event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandGraphEncodeDispatchHostFunction
        inline void EncodeDispatchHostFunction(
            host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
            void* pUserData                                 ///< [in] pointer to user data to pass to host function.
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDGRAPH_HPP
