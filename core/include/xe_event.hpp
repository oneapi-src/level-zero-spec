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
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event
    class Event
    {
    protected:
        ::xe_event_handle_t handle;                       ///< handle of event object
        ::xe_event_desc_t desc;                           ///< descriptor of the event object

    public:
        auto getHandle( void ) const { return handle; }
        auto getDesc( void ) const { return desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeEventDestroy
        /// @throws result_t
        inline void
        Destroy(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeEventHostSignal
        /// @throws result_t
        inline void
        HostSignal(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeEventHostSynchronize
        /// @throws result_t
        inline void
        HostSynchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                            ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY; if zero, then
                                                            ///< operates exactly like ::EventQueryStatus; if MAX_UINT32, then function
                                                            ///< will not return until complete or device is lost.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeEventQueryStatus
        /// @throws result_t
        inline void
        QueryStatus(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeEventQueryElapsedTime
        /// @returns
        ///     - double: time in milliseconds
        /// 
        /// @throws result_t
        inline static double
        QueryElapsedTime(
            event_handle_t hEventBegin,                     ///< [in] handle of the begin event
            event_handle_t hEventEnd                        ///< [in] handle of the end event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeEventQueryMetricsData
        /// @returns
        ///     - uint32_t: report data buffer
        /// 
        /// @throws result_t
        inline static uint32_t
        QueryMetricsData(
            event_handle_t hEventStart,                     ///< [in] handle of the start event
            event_handle_t hEventEnd,                       ///< [in] handle of the end event
            size_t reportSize                               ///< [in] size of the report data buffer in bytes
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeEventReset
        /// @throws result_t
        inline void
        Reset(
            void
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_EVENT_HPP
