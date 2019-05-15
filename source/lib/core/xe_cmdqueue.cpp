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
* @file xe_cmdqueue.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Command Queue
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdqueue.yml
* @endcond
*
******************************************************************************/
#include "xe_api.hpp"
#include "xe_ddi.h"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    CommandQueue::CommandQueue( 
        Device* pDevice,                                ///< [in] pointer to parent object
        const desc_t& desc                              ///< [in] descriptor of the command queue object
        ) :
        m_pDevice( pDevice ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command queue on the device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateCommandQueue**
    ///     - cuCtxCreate
    ///     - cuCtxGetCurrent
    /// 
    /// @returns
    ///     - CommandQueue: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __xecall
    CommandQueue::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command queue descriptor
        )
    {
        // auto result = ::xeCommandQueueCreate( handle, pDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandQueue::Create");

        return (CommandQueue*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command queue.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the command queue before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this command queue
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command queue handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseCommandQueue**
    ///     - cuCtxDestroy
    /// 
    /// @throws result_t
    void __xecall
    CommandQueue::Destroy(
        CommandQueue* pCommandQueue                     ///< [in] pointer to command queue object to destroy
        )
    {
        // auto result = ::xeCommandQueueDestroy( handle, pCommandQueue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandQueue::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Executes a command list in a command queue.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkQueueSubmit
    /// 
    /// @throws result_t
    void __xecall
    CommandQueue::ExecuteCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        CommandList* phCommandLists,                    ///< [in] list of handles of the command lists to execute
        Fence* pFence                                   ///< [in][optional] pointer to the fence to signal on completion
        )
    {
        // auto result = ::xeCommandQueueExecuteCommandLists( handle, numCommandLists, phCommandLists, pFence );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandQueue::ExecuteCommandLists");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Synchronizes a command queue by waiting on the host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    CommandQueue::Synchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::FenceQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        // auto result = ::xeCommandQueueSynchronize( handle, timeout );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandQueue::Synchronize");
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_version_t to std::string
    std::string to_string( xe::CommandQueue::desc_version_t val )
    {
        switch( val )
        {
        case xe::CommandQueue::desc_version_t::CURRENT:
            return std::string("xe::CommandQueue::desc_version_t::CURRENT");
        };
        return std::string("xe::CommandQueue::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flag_t to std::string
    std::string to_string( xe::CommandQueue::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::CommandQueue::flag_t::NONE) & bits )
            str += "xe::CommandQueue::flag_t::NONE | ";
        if( static_cast<uint32_t>(xe::CommandQueue::flag_t::COPY_ONLY) & bits )
            str += "xe::CommandQueue::flag_t::COPY_ONLY | ";
        if( static_cast<uint32_t>(xe::CommandQueue::flag_t::LOGICAL_ONLY) & bits )
            str += "xe::CommandQueue::flag_t::LOGICAL_ONLY | ";
        if( static_cast<uint32_t>(xe::CommandQueue::flag_t::SINGLE_SLICE_ONLY) & bits )
            str += "xe::CommandQueue::flag_t::SINGLE_SLICE_ONLY | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( xe::CommandQueue::mode_t val )
    {
        switch( val )
        {
        case xe::CommandQueue::mode_t::DEFAULT:
            return std::string("xe::CommandQueue::mode_t::DEFAULT");
        case xe::CommandQueue::mode_t::SYNCHRONOUS:
            return std::string("xe::CommandQueue::mode_t::SYNCHRONOUS");
        case xe::CommandQueue::mode_t::ASYNCHRONOUS:
            return std::string("xe::CommandQueue::mode_t::ASYNCHRONOUS");
        };
        return std::string("xe::CommandQueue::mode_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( xe::CommandQueue::priority_t val )
    {
        switch( val )
        {
        case xe::CommandQueue::priority_t::NORMAL:
            return std::string("xe::CommandQueue::priority_t::NORMAL");
        case xe::CommandQueue::priority_t::LOW:
            return std::string("xe::CommandQueue::priority_t::LOW");
        case xe::CommandQueue::priority_t::HIGH:
            return std::string("xe::CommandQueue::priority_t::HIGH");
        };
        return std::string("xe::CommandQueue::priority_t::?");
    }


#endif // _DEBUG
