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
* @file xet_metric.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Metric
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/metric.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_METRIC_INL
#define _XET_METRIC_INL
#if defined(__cplusplus)
#pragma once
#include "xet_metric.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGroupGetProperties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same metric group handle.
    /// 
    /// @returns
    ///     - ::metric_group_properties_t: metric group properties
    /// 
    /// @throws result_t
    inline MetricGroup::metric_group_properties_t 
    MetricGroup::GetProperties(
        void
        )
    {
        // auto result = ::xetMetricGroupGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGroupGetMetric
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same metric group handle.
    /// 
    /// @returns
    ///     - ::metric_handle_t: handle of metric
    /// 
    /// @throws result_t
    inline metric_handle_t 
    MetricGroup::GetMetric(
        uint32_t ordinal                                ///< [in] metric index
        )
    {
        // auto result = ::xetMetricGroupGetMetric( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::GetMetric");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGroupCalculateData
    /// 
    /// @details
    ///     - The application may not call this function from simultaneous threads
    ///       with the same metric group handle.
    /// 
    /// @returns
    ///     - ::typed_value_t: calculated metrics
    /// 
    /// @throws result_t
    inline Metric::typed_value_t 
    MetricGroup::CalculateData(
        uint32_t* pReportCount,                         ///< [in/out] report count to calculate
        uint32_t rawDataSize,                           ///< [in] raw data size
        uint8_t* pRawData,                              ///< [in] raw data to calculate
        uint32_t calculatedDataSize                     ///< [in] calculated data size
        )
    {
        // auto result = ::xetMetricGroupCalculateData( handle, pReportCount, rawDataSize, pRawData, calculatedDataSize );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::CalculateData");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGetProperties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same metric group handle.
    /// 
    /// @returns
    ///     - ::metric_properties_t: metric properties
    /// 
    /// @throws result_t
    inline Metric::metric_properties_t 
    Metric::GetProperties(
        void
        )
    {
        // auto result = ::xetMetricGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Metric::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricTracerClose
    /// 
    /// @details
    ///     - The application may not call this function from simultaneous threads
    ///       with the same device handle.
    /// 
    /// @throws result_t
    inline void 
    MetricTracer::Close(
        void
        )
    {
        // auto result = ::xetMetricTracerClose( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricTracer::Close");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricTracerReadData
    /// 
    /// @details
    ///     - The application may not call this function from simultaneous threads
    ///       with the same device handle.
    /// 
    /// @throws result_t
    inline void 
    MetricTracer::ReadData(
        uint32_t* pReportCount,                         ///< [in/out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data buffer size
        uint8_t* pRawData                               ///< [in/out] raw data buffer for reports
        )
    {
        // auto result = ::xetMetricTracerReadData( handle, pReportCount, rawDataSize, pRawData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricTracer::ReadData");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricQueryPoolGetMetricQuery
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same device handle.
    /// 
    /// @returns
    ///     - ::metric_query_handle_t: handle of metric query
    /// 
    /// @throws result_t
    inline metric_query_handle_t 
    MetricQueryPool::GetMetricQuery(
        uint32_t ordinal                                ///< [in] index of the query within the pool
        )
    {
        // auto result = ::xetMetricQueryPoolGetMetricQuery( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::GetMetricQuery");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricQueryPoolDestroy
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same device handle.
    /// 
    /// @throws result_t
    inline void 
    MetricQueryPool::Destroy(
        void
        )
    {
        // auto result = ::xetMetricQueryPoolDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricQueryGetData
    /// 
    /// @details
    ///     - The application may not call this function from simultaneous threads
    ///       with the same device handle.
    /// 
    /// @throws result_t
    inline void 
    MetricQuery::GetData(
        uint32_t* pReportCount,                         ///< [in/out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
        uint8_t* pRawData                               ///< [in/out] query result data in raw format
        )
    {
        // auto result = ::xetMetricQueryGetData( handle, pReportCount, rawDataSize, pRawData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQuery::GetData");
    }

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_METRIC_INL
