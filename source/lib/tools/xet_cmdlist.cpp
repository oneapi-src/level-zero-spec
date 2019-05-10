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
* @file xet_cmdlist.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/cmdlist.yml
* @endcond
*
******************************************************************************/
#include "xet_api.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetCommandListAppendMetricTracerMarker
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendMetricTracerMarker(
        MetricTracer* pMetricTracer,                    ///< [in] pointer to the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        // auto result = ::xetCommandListAppendMetricTracerMarker( handle, pMetricTracer, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricTracerMarker");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetCommandListAppendMetricQueryBegin
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendMetricQueryBegin(
        MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
        )
    {
        // auto result = ::xetCommandListAppendMetricQueryBegin( handle, pMetricQuery );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricQueryBegin");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetCommandListAppendMetricQueryEnd
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendMetricQueryEnd(
        MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
        xe::Event* pCompletionEvent                     ///< [in] pointer to the completion event to signal
        )
    {
        // auto result = ::xetCommandListAppendMetricQueryEnd( handle, pMetricQuery, pCompletionEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricQueryEnd");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetCommandListAppendMetricMemoryBarrier
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendMetricMemoryBarrier(
        void
        )
    {
        // auto result = ::xetCommandListAppendMetricMemoryBarrier( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricMemoryBarrier");
    }

} // namespace xet
