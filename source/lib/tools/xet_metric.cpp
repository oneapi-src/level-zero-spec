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
#include "xet_api.h"

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
    Metric::Metric( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricTracer::MetricTracer( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQueryPool::MetricQueryPool( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQuery::MetricQuery( 
        Device* pDevice                                 ///< [in] pointer to parent object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns metric group count for a given device.
    /// 
    /// @returns
    ///     - uint32_t: number of metric groups supported by the device
    /// 
    /// @throws result_t
    uint32_t __xecall
    MetricGroup::GetCount(
        xe::Device* pDevice                             ///< [in] pointer to the device object
        )
    {
        // auto result = ::xetMetricGroupGetCount( handle, pDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::GetCount");

        return uint32_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns metric group handle for a device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricGroup: metric group handle
    /// 
    /// @throws result_t
    MetricGroup* __xecall
    MetricGroup::Get(
        xe::Device* pDevice,                            ///< [in] pointer to the device
        uint32_t ordinal                                ///< [in] metric group index
        )
    {
        // auto result = ::xetMetricGroupGet( handle, pDevice, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::Get");

        return (MetricGroup*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns properties for a given metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - properties_t: metric group properties
    /// 
    /// @throws result_t
    MetricGroup::properties_t __xecall
    MetricGroup::GetProperties(
        void
        )
    {
        // auto result = ::xetMetricGroupGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricGroup::GetProperties");

        return properties_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns metric from a given metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - Metric: handle of metric
    /// 
    /// @throws result_t
    Metric* __xecall
    Metric::Get(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        uint32_t ordinal                                ///< [in] metric index
        )
    {
        // auto result = ::xetMetricGet( handle, pMetricGroup, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Metric::Get");

        return (Metric*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns metric properties.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - properties_t: metric properties
    /// 
    /// @throws result_t
    Metric::properties_t __xecall
    Metric::GetProperties(
        void
        )
    {
        // auto result = ::xetMetricGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Metric::GetProperties");

        return properties_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Calculates counter values from raw data.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads wth the same metric group handle.
    /// 
    /// @throws result_t
    void __xecall
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
    /// @brief Activates metric groups.
    /// 
    /// @details
    ///     - MetricGroup must be active until MetricQueryGetDeta and
    ///       ::MetricTracerClose.
    ///     - Conflicting metric groups cannot be activated, in such case tha call
    ///       would fail.
    /// 
    /// @throws result_t
    void __xecall
    Device::ActivateMetricGroups(
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        MetricGroup* phMetricGroups                     ///< [in] handles of the metric groups to activate. NULL to deactivate.
        )
    {
        // auto result = ::xetDeviceActivateMetricGroups( handle, count, phMetricGroups );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Device::ActivateMetricGroups");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens metric tracer for a given device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @returns
    ///     - MetricTracer: handle of metric tracer
    /// 
    /// @throws result_t
    MetricTracer* __xecall
    MetricTracer::Open(
        xe::Device* pDevice,                            ///< [in] pointer to the device
        desc_t* pDesc,                                  ///< [in,out] metric tracer descriptor
        xe::Event* pNotificationEvent                   ///< [in] event used for report availability notification. Must be device
                                                        ///< to host type.
        )
    {
        // auto result = ::xetMetricTracerOpen( handle, pDevice, pDesc, pNotificationEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricTracer::Open");

        return (MetricTracer*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Append metric tracer marker to a given command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricTracerMarker(
        MetricTracer* pMetricTracer,                    ///< [in] pointer to the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        // auto result = ::xetCommandListAppendMetricTracerMarker( handle, pMetricTracer, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricTracerMarker");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes metric tracer.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same metric tracer handle.
    /// 
    /// @throws result_t
    void __xecall
    MetricTracer::Close(
        void
        )
    {
        // auto result = ::xetMetricTracerClose( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricTracer::Close");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reads data from metric tracer.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
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
    /// @brief Creates metric query pool.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQueryPool: handle of metric query pool
    /// 
    /// @throws result_t
    MetricQueryPool* __xecall
    MetricQueryPool::Create(
        xe::Device* pDevice,                            ///< [in] pointer to the device
        desc_t* pDesc                                   ///< [in] metric query pool creation data
        )
    {
        // auto result = ::xetMetricQueryPoolCreate( handle, pDevice, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::Create");

        return (MetricQueryPool*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys query pool object.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query pool handle.
    /// 
    /// @throws result_t
    void __xecall
    MetricQueryPool::Destroy(
        MetricQueryPool* pMetricQueryPool               ///< [in] pointer to the metric query pool
        )
    {
        // auto result = ::xetMetricQueryPoolDestroy( handle, pMetricQueryPool );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns metric query handle from a given metric query pool.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQuery: handle of metric query
    /// 
    /// @throws result_t
    MetricQuery* __xecall
    MetricQueryPool::GetMetricQuery(
        uint32_t ordinal                                ///< [in] index of the query within the pool
        )
    {
        // auto result = ::xetMetricQueryPoolGetMetricQuery( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQueryPool::GetMetricQuery");

        return (MetricQuery*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query begin commands to command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricQueryBegin(
        MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
        )
    {
        // auto result = ::xetCommandListAppendMetricQueryBegin( handle, pMetricQuery );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricQueryBegin");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query end commands to command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricQueryEnd(
        MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
        xe::Event* pCompletionEvent                     ///< [in] pointer to the completion event to signal
        )
    {
        // auto result = ::xetCommandListAppendMetricQueryEnd( handle, pMetricQuery, pCompletionEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricQueryEnd");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query commands to flush all caches.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMetricMemoryBarrier(
        void
        )
    {
        // auto result = ::xetCommandListAppendMetricMemoryBarrier( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::CommandList::AppendMetricMemoryBarrier");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns raw data for a given metric query slot.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __xecall
    MetricQuery::GetData(
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
        uint8_t* pRawData                               ///< [in,out] query result data in raw format
        )
    {
        // auto result = ::xetMetricQueryGetData( handle, pReportCount, rawDataSize, pRawData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::MetricQuery::GetData");
    }

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( value_type_t val )
    {
        switch( val )
        {
        case value_type_t::UINT32:
            return std::string("value_type_t::UINT32");
        case value_type_t::UINT64:
            return std::string("value_type_t::UINT64");
        case value_type_t::FLOAT:
            return std::string("value_type_t::FLOAT");
        case value_type_t::BOOL:
            return std::string("value_type_t::BOOL");
        };
        return std::string("value_type_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_version_t to std::string
    std::string to_string( typed_value_version_t val )
    {
        switch( val )
        {
        case typed_value_version_t::CURRENT:
            return std::string("typed_value_version_t::CURRENT");
        };
        return std::string("typed_value_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type to std::string
    std::string to_string( MetricGroup::sampling_type val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(MetricGroup::sampling_type::METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED) & bits )
            str += "MetricGroup::sampling_type::METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED | ";
        if( static_cast<uint32_t>(MetricGroup::sampling_type::METRIC_GROUP_SAMPLING_TYPE_TIME_BASED) & bits )
            str += "MetricGroup::sampling_type::METRIC_GROUP_SAMPLING_TYPE_TIME_BASED | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_version_t to std::string
    std::string to_string( MetricGroup::properties_version_t val )
    {
        switch( val )
        {
        case MetricGroup::properties_version_t::CURRENT:
            return std::string("MetricGroup::properties_version_t::CURRENT");
        };
        return std::string("MetricGroup::properties_version_t::?");
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( Metric::type_t val )
    {
        switch( val )
        {
        case Metric::type_t::DURATION:
            return std::string("Metric::type_t::DURATION");
        case Metric::type_t::EVENT:
            return std::string("Metric::type_t::EVENT");
        case Metric::type_t::EVENT_WITH_RANGE:
            return std::string("Metric::type_t::EVENT_WITH_RANGE");
        case Metric::type_t::THROUGHPUT:
            return std::string("Metric::type_t::THROUGHPUT");
        case Metric::type_t::TIMESTAMP:
            return std::string("Metric::type_t::TIMESTAMP");
        case Metric::type_t::FLAG:
            return std::string("Metric::type_t::FLAG");
        case Metric::type_t::RATIO:
            return std::string("Metric::type_t::RATIO");
        case Metric::type_t::RAW:
            return std::string("Metric::type_t::RAW");
        };
        return std::string("Metric::type_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_version_t to std::string
    std::string to_string( Metric::properties_version_t val )
    {
        switch( val )
        {
        case Metric::properties_version_t::CURRENT:
            return std::string("Metric::properties_version_t::CURRENT");
        };
        return std::string("Metric::properties_version_t::?");
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_version_t to std::string
    std::string to_string( MetricTracer::desc_version_t val )
    {
        switch( val )
        {
        case MetricTracer::desc_version_t::CURRENT:
            return std::string("MetricTracer::desc_version_t::CURRENT");
        };
        return std::string("MetricTracer::desc_version_t::?");
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::flag_t to std::string
    std::string to_string( MetricQueryPool::flag_t val )
    {
        switch( val )
        {
        case MetricQueryPool::flag_t::PERFORMANCE:
            return std::string("MetricQueryPool::flag_t::PERFORMANCE");
        case MetricQueryPool::flag_t::SKIP_EXECUTION:
            return std::string("MetricQueryPool::flag_t::SKIP_EXECUTION");
        };
        return std::string("MetricQueryPool::flag_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_version_t to std::string
    std::string to_string( MetricQueryPool::desc_version_t val )
    {
        switch( val )
        {
        case MetricQueryPool::desc_version_t::CURRENT:
            return std::string("MetricQueryPool::desc_version_t::CURRENT");
        };
        return std::string("MetricQueryPool::desc_version_t::?");
    }



#endif // _DEBUG
} // namespace xet
