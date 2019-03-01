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
* @file xe_cmdqueue.hpp
*
* @brief C++ wrapper of Intel Xe Driver APIs for Command Queue
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdqueue.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDQUEUE_HPP
#define _XE_CMDQUEUE_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command queue
    class CommandQueue
    {
    protected:
        ::xe_command_queue_handle_t handle;               ///< handle of command queue object
        ::xe_command_queue_desc_t desc;                   ///< descriptor of the command queue object

    public:
        auto getHandle( void ) const { return handle; }
        auto getDesc( void ) const { return desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_fence_flag_t
        enum class fence_flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_fence_desc_t
        struct fence_desc_t
        {
            uint32_t version = XE_FENCE_DESC_VERSION;       ///< [in] descriptor version
            fence_flag_t flags = fence_flag_t::NONE;        ///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueDestroy
        inline void Destroy(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueEnqueueCommandLists
        inline void EnqueueCommandLists(
            uint32_t numCommandLists,                       ///< [in] number of command lists to enqueue
            command_list_handle_t* phCommandLists,          ///< [in] list of handles of the command lists to enqueue for execution
            fence_handle_t hFence                           ///< [in][optional] handle of the fence to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueSynchronize
        inline void Synchronize(
            synchronization_mode_t mode,                    ///< [in] synchronization mode
            uint32_t delay,                                 ///< [in] if ::SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                            ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                            ///< must be zero.
            uint32_t interval,                              ///< [in] if ::SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                            ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                            ///< must be zero.
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                            ///< before returning; if zero, then only a single status check is made
                                                            ///< before immediately returning; if MAX_UINT32, then function will not
                                                            ///< return until complete.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueCreateFence
        inline void CreateFence(
            const fence_desc_t* desc,                       ///< [in] pointer to fence descriptor
            fence_handle_t* phFence                         ///< [out] pointer to handle of fence object created
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDQUEUE_HPP
