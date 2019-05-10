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
* @file xe_event.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Event
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/event.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_EVENT_HPP
#define _XE_EVENT_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event pool
    class EventPool
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::event_pool_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported event pool creation flags
        enum class flag_t
        {
            DEFAULT = 0,                                    ///< signals and waits visible to the entire device and peer devices
            HOST_VISIBLE = XE_BIT(0),                       ///< signals and waits are also visible to host
            IPC = XE_BIT(1),                                ///< signals and waits may be shared across processes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event pool descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::EVENT_POOL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::DEFAULT;                 ///< [in] creation flags
            uint32_t count;                                 ///< [in] number of events within the pool

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        event_pool_handle_t m_handle = nullptr;         ///< handle of event pool object
        Device* m_pDevice;                              ///< [in] pointer to parent object
        desc_t m_desc;                                  ///< [in] descriptor of the event object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        EventPool( void ) = delete;
        EventPool( 
            Device* pDevice,                                ///< [in] pointer to parent object
            desc_t desc                                     ///< [in] descriptor of the event object
            );

        ~EventPool( void ) = default;

        EventPool( EventPool const& other ) = delete;
        void operator=( EventPool const& other ) = delete;

        EventPool( EventPool&& other ) = delete;
        void operator=( EventPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool for a set of event(s) on the device.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - EventPool: pointer handle of event pool object created
        /// 
        /// @throws result_t
        inline static EventPool*
        Create(
            Device* hDevice,                                ///< [in] handle of the device
            const desc_t* desc                              ///< [in] pointer to event pool descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes an event pool object.
        /// 
        /// @details
        ///     - The application is responsible for destroying all event handles
        ///       created from the pool before destroying the pool itself
        ///     - The application is responsible for making sure the GPU is not
        ///       currently referencing the any event within the pool before it is
        ///       deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this event pool
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same event pool handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        inline static void
        Destroy(
            EventPool* hEventPool                           ///< [in] handle of event pool object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Gets an IPC event pool handle for the specified event handle that can
        ///        be shared with another process.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuIpcGetEventHandle**
        /// @returns
        ///     - ipc_event_pool_handle_t: Returned IPC event handle
        /// 
        /// @throws result_t
        inline ipc_event_pool_handle_t
        GetIpcHandle(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens an IPC event pool handle to retrieve an event pool handle from
        ///        another process.
        /// 
        /// @details
        ///     - The event handle in this process should not be freed with
        ///       ::EventPoolDestroy, but rather with ::EventPoolCloseIpcHandle.
        ///     - The application may call this function from simultaneous threads.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuIpcOpenMemHandle**
        /// @returns
        ///     - EventPool: pointer handle of event pool object created
        /// 
        /// @throws result_t
        inline static EventPool*
        OpenIpcHandle(
            Device* hDevice,                                ///< [in] handle of the device to associate with the IPC event pool handle
            ipc_event_pool_handle_t hIpc                    ///< [in] IPC event handle
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes an IPC event handle in the current process.
        /// 
        /// @details
        ///     - Closes an IPC event handle by destroying events that were opened in
        ///       this process using ::EventPoolOpenIpcHandle.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same event pool handle.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuIpcCloseMemHandle**
        /// @throws result_t
        inline void
        CloseIpcHandle(
            void
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event
    class Event
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::event_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported event scope flags
        enum class scope_flag_t
        {
            NONE = 0,                                       ///< execution synchronization only; no cache hierarchies are flushed or
                                                            ///< invalidated
            SUBDEVICE = XE_BIT(0),                          ///< cache hierarchies are flushed or invalidated sufficient for local
                                                            ///< sub-device access
            DEVICE = XE_BIT(1),                             ///< cache hierarchies are flushed or invalidated sufficient for global
                                                            ///< device access and peer device access
            HOST = XE_BIT(2),                               ///< cache hierarchies are flushed or invalidated sufficient for device and
                                                            ///< host access

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::EVENT_DESC_VERSION_CURRENT
            uint32_t index;                                 ///< [in] index of the event within the pool; must be less-than the count
                                                            ///< specified during pool creation
            scope_flag_t signal = scope_flag_t::NONE;       ///< [in] defines the scope of relevant cache hierarchies to flush on a
                                                            ///< ‘signal’ action before the event is triggered
            scope_flag_t wait = scope_flag_t::NONE;         ///< [in] defines the scope of relevant cache hierarchies to invalidate on
                                                            ///< a ‘wait’ action after the event is complete

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        event_handle_t m_handle = nullptr;              ///< handle of event object
        EventPool* m_pEventPool;                        ///< [in] pointer to parent object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Event( void ) = delete;
        Event( 
            EventPool* pEventPool                           ///< [in] pointer to parent object
            );

        ~Event( void ) = default;

        Event( Event const& other ) = delete;
        void operator=( Event const& other ) = delete;

        Event( Event&& other ) = delete;
        void operator=( Event&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getEventpool( void ) const { return m_pEventPool; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates an event on the device.
        /// 
        /// @details
        ///     - Multiple events cannot be created using the same location within the
        ///       same pool.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clCreateUserEvent**
        ///     - vkCreateEvent
        ///     - cuEventCreate
        /// @returns
        ///     - Event: pointer to handle of event object created
        /// 
        /// @throws result_t
        inline static Event*
        Create(
            EventPool* hEventPool,                          ///< [in] handle of the event pool
            const desc_t* desc                              ///< [in] pointer to event descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes an event object.
        /// 
        /// @details
        ///     - The application is responsible for making sure the GPU is not
        ///       currently referencing the event before it is deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this event
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same event handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clReleaseEvent**
        ///     - vkDestroyEvent
        ///     - cuEventDestroy
        /// @throws result_t
        inline static void
        Destroy(
            Event* hEvent                                   ///< [in] handle of event object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Signals a event from host.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clSetUserEventStatus
        /// @throws result_t
        inline void
        HostSignal(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief The current host thread waits on an event to be signalled.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clWaitForEvents
        ///     - cuEventSynchronize
        /// @throws result_t
        inline void
        HostSynchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                            ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::EventQueryStatus;
                                                            ///< if MAX_UINT32, then function will not return until complete or device
                                                            ///< is lost.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Queries an event object's status.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clGetEventInfo**
        ///     - vkGetEventStatus
        ///     - cuEventQuery
        /// @throws result_t
        inline void
        QueryStatus(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset an event back to not signaled state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - vkResetEvent
        /// @throws result_t
        inline void
        Reset(
            void
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_EVENT_HPP
