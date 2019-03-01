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
* @file xe_cmdgraph.inl
*
* @brief C++ wrapper of Intel Xe Driver APIs for CommandGraph
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdgraph.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDGRAPH_INL
#define _XE_CMDGRAPH_INL
#if defined(__cplusplus)
#pragma once
#include "xe_cmdgraph.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandGraphDestroy
    inline void CommandGraph::Destroy(
        )
    {
        // auto result = ::xeCommandGraphDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandGraphClose
    inline void CommandGraph::Close(
        )
    {
        // auto result = ::xeCommandGraphClose( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::Close");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandGraphReset
    inline void CommandGraph::Reset(
        )
    {
        // auto result = ::xeCommandGraphReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::Reset");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandGraphEncodeDispatchFunction
    inline void CommandGraph::EncodeDispatchFunction(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const dispatch_function_arguments_t* pDispatchFuncArgs, ///< [in] dispatch function arguments.
        event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
        )
    {
        // auto result = ::xeCommandGraphEncodeDispatchFunction( handle, hFunction->getHandle(), pDispatchFuncArgs, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::EncodeDispatchFunction");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandGraphEncodeDispatchFunctionIndirect
    inline void CommandGraph::EncodeDispatchFunctionIndirect(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer, ///< [in] Pointer to buffer that will contain dispatch arguments.
        event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
        )
    {
        // auto result = ::xeCommandGraphEncodeDispatchFunctionIndirect( handle, hFunction->getHandle(), pDispatchArgumentsBuffer, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::EncodeDispatchFunctionIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandGraphEncodeDispatchHostFunction
    inline void CommandGraph::EncodeDispatchHostFunction(
        host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
        )
    {
        // auto result = ::xeCommandGraphEncodeDispatchHostFunction( handle, pfnHostFunc, pUserData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::EncodeDispatchHostFunction");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDGRAPH_INL
