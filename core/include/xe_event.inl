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
* @brief C++ wrapper of Intel Xe Driver APIs for Event
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
#include "xe_event.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the event before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this event
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
        void
        )
    {
        // auto result = ::xeEventDestroy( handle );
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
                                                        ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY; if zero, then
                                                        ///< operates exactly like ::EventQueryStatus; if MAX_UINT32, then function
                                                        ///< will not return until complete or device is lost.
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
    /// @brief C++ wrapper for ::xeEventQueryElapsedTime
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuEventElapsedTime**
    /// 
    /// @returns
    ///     - double: time in milliseconds
    /// 
    /// @throws result_t
    inline double 
    Event::QueryElapsedTime(
        event_handle_t hEventBegin,                     ///< [in] handle of the begin event
        event_handle_t hEventEnd                        ///< [in] handle of the end event
        )
    {
        // auto result = ::xeEventQueryElapsedTime( handle, hEventBegin, hEventEnd );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::QueryElapsedTime");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventQueryMetricsData
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - uint32_t: report data buffer
    /// 
    /// @throws result_t
    inline uint32_t 
    Event::QueryMetricsData(
        event_handle_t hEventStart,                     ///< [in] handle of the start event
        event_handle_t hEventEnd,                       ///< [in] handle of the end event
        size_t reportSize                               ///< [in] size of the report data buffer in bytes
        )
    {
        // auto result = ::xeEventQueryMetricsData( handle, hEventStart, hEventEnd, reportSize );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::QueryMetricsData");
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
