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
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command queue
    class CommandQueue
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::command_queue_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = XE_BIT(0),                          ///< command queue only supports enqueing copy-only command lists
            LOGICAL_ONLY = XE_BIT(1),                       ///< command queue is not tied to a physical command queue; driver may
                                                            ///< dynamically assign based on usage
            SINGLE_SLICE_ONLY = XE_BIT(2),                  ///< command queue reserves and cannot comsume more than a single slice.
                                                            ///< 'slice' size is device-specific.  cannot be combined with COPY_ONLY.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue modes
        enum class mode_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            SYNCHRONOUS,                                    ///< Device execution always completes immediately on execute;
                                                            ///< Host thread is blocked using wait on implicit synchronization object
            ASYNCHRONOUS,                                   ///< Device execution is scheduled and will complete in future;
                                                            ///< explicit synchronization object must be used to determine completeness

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue priorities
        enum class priority_t
        {
            NORMAL = 0,                                     ///< [default] normal priority
            LOW,                                            ///< lower priority than normal
            HIGH,                                           ///< higher priority than normal

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command Queue descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::COMMAND_QUEUE_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags
            mode_t mode = mode_t::DEFAULT;                  ///< [in] operation mode
            priority_t priority = priority_t::NORMAL;       ///< [in] priority
            uint32_t ordinal = 0;                           ///< [in] if logical-only flag is set, then will be ignored;
                                                            ///< else-if copy-only flag is set, then must be less than ::device_properties_t.numAsyncCopyEngines;
                                                            ///< otherwise must be less than
                                                            ///< ::device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                            ///< the ::device_properties_t.numAsyncComputeEngines must be queried from
                                                            ///< the sub-device being used.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_queue_handle_t m_handle = nullptr;      ///< handle of command queue object
        Device* m_pDevice;                              ///< [in] pointer to parent object
        desc_t m_desc;                                  ///< [in] descriptor of the command queue object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandQueue( void ) = delete;
        CommandQueue( 
            Device* pDevice,                                ///< [in] pointer to parent object
            const desc_t& desc                              ///< [in] descriptor of the command queue object
            );

        ~CommandQueue( void ) = default;

        CommandQueue( CommandQueue const& other ) = delete;
        void operator=( CommandQueue const& other ) = delete;

        CommandQueue( CommandQueue&& other ) = delete;
        void operator=( CommandQueue&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - CommandQueue: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        static CommandQueue* __xecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command queue descriptor
            );

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
        /// @throws result_t
        static void __xecall
        Destroy(
            CommandQueue* pCommandQueue                     ///< [in] pointer to command queue object to destroy
            );

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
        /// @throws result_t
        void __xecall
        ExecuteCommandLists(
            uint32_t numCommandLists,                       ///< [in] number of command lists to execute
            CommandList* phCommandLists,                    ///< [in] list of handles of the command lists to execute
            Fence* pFence = nullptr                         ///< [in][optional] pointer to the fence to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Synchronizes a command queue by waiting on the host.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        Synchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                            ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::FenceQueryStatus;
                                                            ///< if MAX_UINT32, then function will not return until complete or device
                                                            ///< is lost.
            );

    };

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_version_t to std::string
    std::string to_string( CommandQueue::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flag_t to std::string
    std::string to_string( CommandQueue::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( CommandQueue::mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( CommandQueue::priority_t val );


#endif // _DEBUG
} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDQUEUE_HPP
