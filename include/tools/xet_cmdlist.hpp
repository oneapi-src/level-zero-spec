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
* @file xet_cmdlist.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/cmdlist.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_CMDLIST_HPP
#define _XET_CMDLIST_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xet_common.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList : public xe::CommandList
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandList( void ) = delete;
        using xe::CommandList::CommandList;

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Append metric tracer marker to a given command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __xecall
        AppendMetricTracerMarker(
            MetricTracer* pMetricTracer,                    ///< [in] pointer to the metric tracer
            uint32_t value                                  ///< [in] tracer marker value
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query begin commands to command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __xecall
        AppendMetricQueryBegin(
            MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query end commands to command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __xecall
        AppendMetricQueryEnd(
            MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
            xe::Event* pCompletionEvent                     ///< [in] pointer to the completion event to signal
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query commands to flush all caches.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __xecall
        AppendMetricMemoryBarrier(
            void
            );

    };

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_CMDLIST_HPP
