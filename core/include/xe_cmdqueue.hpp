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
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Command Queue
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
        /// @brief C++ version for ::xe_command_queue_desc_version_t
        enum class command_queue_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_flag_t
        enum class command_queue_flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = XE_BIT(0),                          ///< command queue only supports enqueing copy-only command lists
            LOGICAL_ONLY = XE_BIT(1),                       ///< command queue is not tied to a physical command queue; driver may
                                                            ///< dynamically assign based on usage
            SINGLE_SLICE_ONLY = XE_BIT(2),                  ///< command queue reserves and cannot comsume more than a single slice.
                                                            ///< 'slice' size is device-specific.  cannot be combined with COPY_ONLY.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_mode_t
        enum class command_queue_mode_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            SYNCHRONOUS,                                    ///< GPU execution always completes immediately on execute;
                                                            ///< CPU thread is blocked using wait on implicit synchronization object
            ASYNCHRONOUS,                                   ///< GPU execution is scheduled and will complete in future;
                                                            ///< explicit synchronization object must be used to determine completeness

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_priority_t
        enum class command_queue_priority_t
        {
            NORMAL = 0,                                     ///< [default] normal priority
            LOW,                                            ///< lower priority than normal
            HIGH,                                           ///< higher priority than normal

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_queue_desc_t
        struct command_queue_desc_t
        {
            command_queue_desc_version_t version = command_queue_desc_version_t::CURRENT;   ///< [in] ::COMMAND_QUEUE_DESC_VERSION_CURRENT
            command_queue_flag_t flags = command_queue_flag_t::NONE;///< [in] creation flags
            command_queue_mode_t mode = command_queue_mode_t::DEFAULT;  ///< [in] operation mode
            command_queue_priority_t priority = command_queue_priority_t::NORMAL;   ///< [in] priority
            uint32_t ordinal = 0;                           ///< [in] if logical-only flag is set, then will be ignored;
                                                            ///< else-if copy-only flag is set, then must be less than ::device_properties_t.numAsyncCopyEngines;
                                                            ///< otherwise must be less than
                                                            ///< ::device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                            ///< the ::device_properties_t.numAsyncComputeEngines must be queried from
                                                            ///< the sub-device being used.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueCreate
        /// @returns
        ///     - ::command_queue_handle_t: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        inline static command_queue_handle_t
        Create(
            device_handle_t hDevice,                        ///< [in] handle of the device object
            const command_queue_desc_t* desc                ///< [in] pointer to command queue descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueDestroy
        /// @throws result_t
        inline static void
        Destroy(
            command_queue_handle_t hCommandQueue            ///< [in] handle of command queue object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueExecuteCommandLists
        /// @throws result_t
        inline void
        ExecuteCommandLists(
            uint32_t numCommandLists,                       ///< [in] number of command lists to execute
            command_list_handle_t* phCommandLists,          ///< [in] list of handles of the command lists to execute
            fence_handle_t hFence = nullptr                 ///< [in][optional] handle of the fence to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandQueueSynchronize
        /// @throws result_t
        inline void
        Synchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                            ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::FenceQueryStatus;
                                                            ///< if MAX_UINT32, then function will not return until complete or device
                                                            ///< is lost.
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDQUEUE_HPP
