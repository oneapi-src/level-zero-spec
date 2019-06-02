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
* @file xe_fence.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Fence
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/fence.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_FENCE_HPP
#define _XE_FENCE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for fence
    class Fence
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::fence_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported fence creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fence descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::FENCE_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        fence_handle_t m_handle;                        ///< [in] handle of fence object
        CommandQueue* m_pCommandQueue;                  ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the fence object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Fence( void ) = delete;
        Fence( 
            fence_handle_t handle,                          ///< [in] handle of fence object
            CommandQueue* pCommandQueue,                    ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the fence object
            );

        ~Fence( void ) = default;

        Fence( Fence const& other ) = delete;
        void operator=( Fence const& other ) = delete;

        Fence( Fence&& other ) = delete;
        void operator=( Fence&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getCommandqueue( void ) const { return m_pCommandQueue; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a fence object on the device's command queue.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **vkCreateFence**
        /// @returns
        ///     - Fence*: pointer to handle of fence object created
        /// 
        /// @throws result_t
        static Fence* __xecall
        Create(
            CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
            const desc_t* desc                              ///< [in] pointer to fence descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a fence object.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the fence before it is deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this fence
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same fence handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **vkDestroyFence**
        /// @throws result_t
        static void __xecall
        Destroy(
            Fence* pFence                                   ///< [in][release] pointer to fence object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief The current host thread waits on a fence to be signaled.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **vkWaitForFences**
        /// @throws result_t
        void __xecall
        HostSynchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                            ///< yield before returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::FenceQueryStatus;
                                                            ///< if MAX_UINT32, then function will not return until complete or device
                                                            ///< is lost.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Queries a fence object's status.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **vkGetFenceStatus**
        /// @throws result_t
        void __xecall
        QueryStatus(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset a fence back to the not signaled state.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **vkResetFences**
        /// @throws result_t
        void __xecall
        Reset(
            void
            );

    };

} // namespace xe

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Fence::desc_version_t to std::string
std::string to_string( xe::Fence::desc_version_t val );

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Fence::flag_t to std::string
std::string to_string( xe::Fence::flag_t val );


#endif // _DEBUG
#endif // defined(__cplusplus)
#endif // _XE_FENCE_HPP
