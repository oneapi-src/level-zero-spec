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
    protected:

        CommandList( void ) = delete;
        using xe::CommandList::CommandList;

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

    public:

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetCommandListAppendMetricTracerMarker
        /// @throws result_t
        inline void
        AppendMetricTracerMarker(
            metric_tracer_handle_t hMetricTracer,           ///< [in] handle of the metric tracer
            uint32_t value                                  ///< [in] tracer marker value
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetCommandListAppendMetricQueryBegin
        /// @throws result_t
        inline void
        AppendMetricQueryBegin(
            metric_query_handle_t hMetricQuery              ///< [in] handle of the metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetCommandListAppendMetricQueryEnd
        /// @throws result_t
        inline void
        AppendMetricQueryEnd(
            metric_query_handle_t hMetricQuery,             ///< [in] handle of the metric query
            xe::event_handle_t hCompletionEvent             ///< [in] handle of the completion event to signal
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xetCommandListAppendMetricMemoryBarrier
        /// @throws result_t
        inline void
        AppendMetricMemoryBarrier(
            void
            );

    };

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_CMDLIST_HPP
