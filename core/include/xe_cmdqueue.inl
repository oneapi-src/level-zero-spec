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
* @file xe_cmdqueue.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Command Queue
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdqueue.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDQUEUE_INL
#define _XE_CMDQUEUE_INL
#if defined(__cplusplus)
#pragma once
#include "xe_cmdqueue.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandQueueCreate
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateCommandQueue**
    ///     - cuCtxCreate
    ///     - cuCtxGetCurrent
    /// 
    /// @returns
    ///     - ::command_queue_handle_t: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    inline command_queue_handle_t 
    CommandQueue::Create(
        device_handle_t hDevice,                        ///< [in] handle of the device object
        const command_queue_desc_t* desc                ///< [in] pointer to command queue descriptor
        )
    {
        // auto result = ::xeCommandQueueCreate( handle, hDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandQueue::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandQueueDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the command queue before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this command queue
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseCommandQueue**
    ///     - cuCtxDestroy
    /// 
    /// @throws result_t
    inline void 
    CommandQueue::Destroy(
        command_queue_handle_t hCommandQueue            ///< [in] handle of command queue object to destroy
        )
    {
        // auto result = ::xeCommandQueueDestroy( handle, hCommandQueue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandQueue::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandQueueExecuteCommandLists
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
    inline void 
    CommandQueue::ExecuteCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        command_list_handle_t* phCommandLists,          ///< [in] list of handles of the command lists to execute
        fence_handle_t hFence                           ///< [in][optional] handle of the fence to signal on completion
        )
    {
        // auto result = ::xeCommandQueueExecuteCommandLists( handle, numCommandLists, phCommandLists, hFence );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandQueue::ExecuteCommandLists");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandQueueSynchronize
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
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
#endif // defined(__cplusplus)
#endif // _XE_CMDQUEUE_INL
