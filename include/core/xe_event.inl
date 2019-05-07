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
* @file xe_event.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Event
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/event.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_EVENT_INL
#define _XE_EVENT_INL
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_event.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventPoolCreate
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ::event_pool_handle_t: pointer handle of event pool object created
    /// 
    /// @throws result_t
    inline event_pool_handle_t 
    EventPool::Create(
        device_handle_t hDevice,                        ///< [in] handle of the device
        const event_pool_desc_t* desc                   ///< [in] pointer to event pool descriptor
        )
    {
        // auto result = ::xeEventPoolCreate( handle, hDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventPoolDestroy
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
    /// 
    /// @throws result_t
    inline void 
    EventPool::Destroy(
        event_pool_handle_t hEventPool                  ///< [in] handle of event pool object to destroy
        )
    {
        // auto result = ::xeEventPoolDestroy( handle, hEventPool );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventPoolGetIpcHandle
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcGetEventHandle**
    /// 
    /// @returns
    ///     - ::ipc_event_pool_handle_t: Returned IPC event handle
    /// 
    /// @throws result_t
    inline ipc_event_pool_handle_t 
    EventPool::GetIpcHandle(
        void
        )
    {
        // auto result = ::xeEventPoolGetIpcHandle( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::GetIpcHandle");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventPoolOpenIpcHandle
    /// 
    /// @details
    ///     - The event handle in this process should not be freed with
    ///       ::EventPoolDestroy, but rather with ::EventPoolCloseIpcHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcOpenMemHandle**
    /// 
    /// @returns
    ///     - ::event_pool_handle_t: pointer handle of event pool object created
    /// 
    /// @throws result_t
    inline event_pool_handle_t 
    EventPool::OpenIpcHandle(
        device_handle_t hDevice,                        ///< [in] handle of the device to associate with the IPC event pool handle
        ipc_event_pool_handle_t hIpc                    ///< [in] IPC event handle
        )
    {
        // auto result = ::xeEventPoolOpenIpcHandle( handle, hDevice, hIpc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::OpenIpcHandle");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventPoolCloseIpcHandle
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
    /// 
    /// @throws result_t
    inline void 
    EventPool::CloseIpcHandle(
        void
        )
    {
        // auto result = ::xeEventPoolCloseIpcHandle( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::CloseIpcHandle");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventCreate
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
    /// 
    /// @returns
    ///     - ::event_handle_t: pointer to handle of event object created
    /// 
    /// @throws result_t
    inline event_handle_t 
    Event::Create(
        event_pool_handle_t hEventPool,                 ///< [in] handle of the event pool
        const event_desc_t* desc                        ///< [in] pointer to event descriptor
        )
    {
        // auto result = ::xeEventCreate( handle, hEventPool, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventDestroy
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
    /// 
    /// @throws result_t
    inline void 
    Event::Destroy(
        event_handle_t hEvent                           ///< [in] handle of event object to destroy
        )
    {
        // auto result = ::xeEventDestroy( handle, hEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventHostSignal
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clSetUserEventStatus
    /// 
    /// @throws result_t
    inline void 
    Event::HostSignal(
        void
        )
    {
        // auto result = ::xeEventHostSignal( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::HostSignal");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventHostSynchronize
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clWaitForEvents
    ///     - cuEventSynchronize
    /// 
    /// @throws result_t
    inline void 
    Event::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::EventQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        // auto result = ::xeEventHostSynchronize( handle, timeout );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::HostSynchronize");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventQueryStatus
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
    /// 
    /// @throws result_t
    inline void 
    Event::QueryStatus(
        void
        )
    {
        // auto result = ::xeEventQueryStatus( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::QueryStatus");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventReset
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkResetEvent
    /// 
    /// @throws result_t
    inline void 
    Event::Reset(
        void
        )
    {
        // auto result = ::xeEventReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Reset");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_EVENT_INL
