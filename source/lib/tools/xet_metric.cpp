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
* @file xet_metric.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Metric
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/metric.yml
* @endcond
*
******************************************************************************/
#include "xet_api.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    MetricGroup::MetricGroup( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGroupGetCount
    /// 
    /// @returns
    ///     - uint32_t: number of metric groups supported by the device
    /// 
    /// @throws result_t
    inline uint32_t 
    MetricGroup::GetCount(
        xe::Device* pDevice                             ///< [in] pointer to the device object
        )
    {
        // auto result = ::xetMetricGroupGetCount( handle, pDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::GetCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGroupGet
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricGroup: metric group handle
    /// 
    /// @throws result_t
    inline MetricGroup* 
    MetricGroup::Get(
        xe::Device* pDevice,                            ///< [in] pointer to the device
        uint32_t ordinal                                ///< [in] metric group index
        )
    {
        // auto result = ::xetMetricGroupGet( handle, pDevice, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::Get");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGroupGetProperties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - properties_t: metric group properties
    /// 
    /// @throws result_t
    inline MetricGroup::properties_t 
    MetricGroup::GetProperties(
        void
        )
    {
        // auto result = ::xetMetricGroupGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGroupCalculateData
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads wth the same metric group handle.
    /// 
    /// @throws result_t
    inline void 
    MetricGroup::CalculateData(
        uint32_t* pReportCount,                         ///< [in,out] report count to calculate
        uint32_t rawDataSize,                           ///< [in] raw data size
        uint8_t* pRawData,                              ///< [in] raw data to calculate
        uint32_t calculatedDataSize,                    ///< [in] calculated data size
        typed_value_t* pCalculatedData                  ///< [in,out] calculated metrics
        )
    {
        // auto result = ::xetMetricGroupCalculateData( handle, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::CalculateData");
    }

    ///////////////////////////////////////////////////////////////////////////////
    Metric::Metric( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGet
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - Metric: handle of metric
    /// 
    /// @throws result_t
    inline Metric* 
    Metric::Get(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        uint32_t ordinal                                ///< [in] metric index
        )
    {
        // auto result = ::xetMetricGet( handle, pMetricGroup, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Metric::Get");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricGetProperties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - properties_t: metric properties
    /// 
    /// @throws result_t
    inline Metric::properties_t 
    Metric::GetProperties(
        void
        )
    {
        // auto result = ::xetMetricGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Metric::GetProperties");
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricTracer::MetricTracer( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricTracerOpen
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @returns
    ///     - MetricTracer: handle of metric tracer
    /// 
    /// @throws result_t
    inline MetricTracer* 
    MetricTracer::Open(
        xe::Device* pDevice,                            ///< [in] pointer to the device
        desc_t* pDesc,                                  ///< [in,out] metric tracer descriptor
        xe::Event* pNotificationEvent                   ///< [in] event used for report availability notification. Must be device
                                                        ///< to host type.
        )
    {
        // auto result = ::xetMetricTracerOpen( handle, pDevice, pDesc, pNotificationEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricTracer::Open");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricTracerClose
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same metric tracer handle.
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
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    inline void 
    MetricTracer::ReadData(
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data buffer size
        uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
        )
    {
        // auto result = ::xetMetricTracerReadData( handle, pReportCount, rawDataSize, pRawData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricTracer::ReadData");
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQueryPool::MetricQueryPool( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricQueryPoolCreate
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQueryPool: handle of metric query pool
    /// 
    /// @throws result_t
    inline MetricQueryPool* 
    MetricQueryPool::Create(
        xe::Device* pDevice,                            ///< [in] pointer to the device
        desc_t* pDesc                                   ///< [in] metric query pool creation data
        )
    {
        // auto result = ::xetMetricQueryPoolCreate( handle, pDevice, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricQueryPoolDestroy
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query pool handle.
    /// 
    /// @throws result_t
    inline void 
    MetricQueryPool::Destroy(
        MetricQueryPool* pMetricQueryPool               ///< [in] pointer to the metric query pool
        )
    {
        // auto result = ::xetMetricQueryPoolDestroy( handle, pMetricQueryPool );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricQueryPoolGetMetricQuery
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQuery: handle of metric query
    /// 
    /// @throws result_t
    inline MetricQuery* 
    MetricQueryPool::GetMetricQuery(
        uint32_t ordinal                                ///< [in] index of the query within the pool
        )
    {
        // auto result = ::xetMetricQueryPoolGetMetricQuery( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::GetMetricQuery");
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQuery::MetricQuery( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xetMetricQueryGetData
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    inline void 
    MetricQuery::GetData(
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
        uint8_t* pRawData                               ///< [in,out] query result data in raw format
        )
    {
        // auto result = ::xetMetricQueryGetData( handle, pReportCount, rawDataSize, pRawData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQuery::GetData");
    }

} // namespace xet
