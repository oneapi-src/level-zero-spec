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
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host
    ///       allocations associated with this command graph.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandGraph::Destroy(
        void
        )
    {
        // auto result = ::xeCommandGraphDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandGraphClose
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
    inline void 
    CommandGraph::Close(
        void
        )
    {
        // auto result = ::xeCommandGraphClose( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandGraph::Close");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDGRAPH_INL
