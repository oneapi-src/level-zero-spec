/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_wprapi.cpp
 *
 * @brief C++ wrapper of zet
 *
 */
#include "zet_api.hpp"
#include "ze_singleton.h"

#define _ZE_STRING(s) #s
#define ZE_STRING(s) _ZE_STRING(s)

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    Debug::Debug( 
        debug_session_handle_t handle                   ///< [in] debug session handle
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Attach to a device.
    /// 
    /// @returns
    ///     - Debug*: debug session handle
    /// 
    /// @throws result_t
    Debug* __zecall
    Debug::Attach(
        Device* pDevice,                                ///< [in] device handle
        const config_t* config                          ///< [in] the debug configuration
        )
    {
        zet_debug_session_handle_t hDebug;

        auto result = static_cast<result_t>( ::zetDebugAttach(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const zet_debug_config_t*>( config ),
            &hDebug ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Attach" );

        Debug* pDebug = nullptr;

        try
        {
            pDebug = new Debug( reinterpret_cast<debug_session_handle_t>( hDebug ) );
        }
        catch( std::bad_alloc& )
        {
            delete pDebug;
            pDebug = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Attach" );
        }

        return pDebug;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Close a debug session.
    /// 
    /// @throws result_t
    void __zecall
    Debug::Detach(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetDebugDetach(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Detach" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query the number of device threads for a debug session.
    /// 
    /// @returns
    ///     - uint64_t: the maximal number of threads
    /// 
    /// @throws result_t
    uint64_t __zecall
    Debug::GetNumThreads(
        void
        )
    {
        uint64_t numThreads;

        auto result = static_cast<result_t>( ::zetDebugGetNumThreads(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            &numThreads ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::GetNumThreads" );

        return numThreads;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read the topmost debug event.
    /// 
    /// @returns
    ///     - ze::bool_t:'0' when ZE::RESULT_NOT_READY
    /// @throws result_t
    ze::bool_t __zecall
    Debug::ReadEvent(
        uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
        size_t size,                                    ///< [in] the size of the buffer in bytes
        void* buffer                                    ///< [in,out] a buffer to hold the event data
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadEvent(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            timeout,
            size,
            buffer ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::ReadEvent" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Interrupt device threads.
    /// 
    /// @throws result_t
    void __zecall
    Debug::Interrupt(
        uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto result = static_cast<result_t>( ::zetDebugInterrupt(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Interrupt" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Resume device threads.
    /// 
    /// @throws result_t
    void __zecall
    Debug::Resume(
        uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto result = static_cast<result_t>( ::zetDebugResume(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Resume" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read memory.
    /// 
    /// @throws result_t
    void __zecall
    Debug::ReadMemory(
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to read from
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadMemory(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            memSpace,
            address,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::ReadMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Write memory.
    /// 
    /// @throws result_t
    void __zecall
    Debug::WriteMemory(
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to write to
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto result = static_cast<result_t>( ::zetDebugWriteMemory(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            memSpace,
            address,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::WriteMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read register state.
    /// 
    /// @throws result_t
    void __zecall
    Debug::ReadState(
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadState(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            offset,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::ReadState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Write register state.
    /// 
    /// @throws result_t
    void __zecall
    Debug::WriteState(
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto result = static_cast<result_t>( ::zetDebugWriteState(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            offset,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::WriteState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricGroup::MetricGroup( 
        metric_group_handle_t handle,                   ///< [in] handle of metric group object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Metric::Metric( 
        metric_handle_t handle,                         ///< [in] handle of metric object
        MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pMetricGroup( pMetricGroup )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricTracer::MetricTracer( 
        metric_tracer_handle_t handle,                  ///< [in] handle of metric tracer object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the metric tracer
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQueryPool::MetricQueryPool( 
        metric_query_pool_handle_t handle,              ///< [in] handle of metric query pool object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the metric query pool
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQuery::MetricQuery( 
        metric_query_handle_t handle,                   ///< [in] handle of metric query object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves metric group for a device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    MetricGroup::Get(
        Device* pDevice,                                ///< [in] pointer to the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< metric groups.
                                                        ///< if count is larger than the number of metric groups available, then
                                                        ///< the driver will update the value with the correct number of metric
                                                        ///< groups available.
        MetricGroup** ppMetricGroups                    ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                        ///< groups
        )
    {
        thread_local std::vector<zet_metric_group_handle_t> hMetricGroups;
        hMetricGroups.resize( ( ppMetricGroups ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetMetricGroupGet(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            pCount,
            hMetricGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::Get" );

        for( uint32_t i = 0; ( ppMetricGroups ) && ( i < *pCount ); ++i )
            ppMetricGroups[ i ] = nullptr;

        try
        {
            static singleton_factory_t<MetricGroup, metric_group_handle_t> metricGroupFactory;

            for( uint32_t i = 0; ( ppMetricGroups ) && ( i < *pCount ); ++i )
                ppMetricGroups[ i ] = metricGroupFactory.getInstance( reinterpret_cast<metric_group_handle_t>( hMetricGroups[ i ] ), pDevice );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    MetricGroup::GetProperties(
        properties_t* pProperties                       ///< [in,out] metric group properties
        )
    {
        auto result = static_cast<result_t>( ::zetMetricGroupGetProperties(
            reinterpret_cast<zet_metric_group_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_group_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Calculates metric values from raw data.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    MetricGroup::CalculateMetricValues(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric values to be calculated.
                                                        ///< if count is non-zero, then driver will only calculate that number of
                                                        ///< metric values.
                                                        ///< if count is larger than the number available in the raw data buffer,
                                                        ///< then the driver will update the value with the actual number of metric
                                                        ///< values to be calculated.
        typed_value_t* pMetricValues                    ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                        ///< metrics
        )
    {
        auto result = static_cast<result_t>( ::zetMetricGroupCalculateMetricValues(
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            rawDataSize,
            pRawData,
            pMetricValueCount,
            reinterpret_cast<zet_typed_value_t*>( pMetricValues ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::CalculateMetricValues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves metric from a metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    Metric::Get(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metrics available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                        ///< if count is larger than the number of metrics available, then the
                                                        ///< driver will update the value with the correct number of metrics available.
        Metric** ppMetrics                              ///< [in,out][optional][range(0, *pCount)] array of pointer to metrics
        )
    {
        thread_local std::vector<zet_metric_handle_t> hMetrics;
        hMetrics.resize( ( ppMetrics ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetMetricGet(
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            pCount,
            hMetrics.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Metric::Get" );

        for( uint32_t i = 0; ( ppMetrics ) && ( i < *pCount ); ++i )
            ppMetrics[ i ] = nullptr;

        try
        {
            static singleton_factory_t<Metric, metric_handle_t> metricFactory;

            for( uint32_t i = 0; ( ppMetrics ) && ( i < *pCount ); ++i )
                ppMetrics[ i ] = metricFactory.getInstance( reinterpret_cast<metric_handle_t>( hMetrics[ i ] ), pMetricGroup );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Metric::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a metric.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    Metric::GetProperties(
        properties_t* pProperties                       ///< [in,out] metric properties
        )
    {
        auto result = static_cast<result_t>( ::zetMetricGetProperties(
            reinterpret_cast<zet_metric_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Metric::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Activates metric groups.
    /// 
    /// @details
    ///     - MetricGroup must be active until MetricQueryGetDeta and
    ///       ::zetMetricTracerClose.
    ///     - Conflicting metric groups cannot be activated, in such case tha call
    ///       would fail.
    /// 
    /// @throws result_t
    void __zecall
    Device::ActivateMetricGroups(
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        MetricGroup** ppMetricGroups                    ///< [in][optional][range(0, count)] handles of the metric groups to
                                                        ///< activate. NULL to deactivate.
        )
    {
        thread_local std::vector<zet_metric_group_handle_t> hMetricGroups;
        hMetricGroups.resize( 0 );
        hMetricGroups.reserve( count );
        for( uint32_t i = 0; i < count; ++i )
            hMetricGroups.emplace_back( ( ppMetricGroups ) ? reinterpret_cast<zet_metric_group_handle_t>( ppMetricGroups[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zetDeviceActivateMetricGroups(
            reinterpret_cast<zet_device_handle_t>( getHandle() ),
            count,
            hMetricGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Device::ActivateMetricGroups" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens metric tracer for a device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @returns
    ///     - MetricTracer*: handle of metric tracer
    /// 
    /// @throws result_t
    MetricTracer* __zecall
    MetricTracer::Open(
        Device* pDevice,                                ///< [in] pointer to the device
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        desc_t* desc,                                   ///< [in,out] metric tracer descriptor
        ze::Event* pNotificationEvent                   ///< [in][optional] event used for report availability notification. Must
                                                        ///< be device to host type.
        )
    {
        zet_metric_tracer_handle_t hMetricTracer;

        auto result = static_cast<result_t>( ::zetMetricTracerOpen(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<zet_metric_tracer_desc_t*>( desc ),
            ( pNotificationEvent ) ? reinterpret_cast<ze_event_handle_t>( pNotificationEvent->getHandle() ) : nullptr,
            &hMetricTracer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricTracer::Open" );

        MetricTracer* pMetricTracer = nullptr;

        try
        {
            pMetricTracer = new MetricTracer( reinterpret_cast<metric_tracer_handle_t>( hMetricTracer ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricTracer;
            pMetricTracer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricTracer::Open" );
        }

        return pMetricTracer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Append metric tracer marker into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMetricTracerMarker(
        MetricTracer* pMetricTracer,                    ///< [in] pointer to the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        auto result = static_cast<result_t>( ::zetCommandListAppendMetricTracerMarker(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_tracer_handle_t>( pMetricTracer->getHandle() ),
            value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricTracerMarker" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes metric tracer.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same metric tracer handle.
    /// 
    /// @throws result_t
    void __zecall
    MetricTracer::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetMetricTracerClose(
            reinterpret_cast<zet_metric_tracer_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricTracer::Close" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reads data from metric tracer.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    MetricTracer::ReadData(
        uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                        ///< if UINT32_MAX, then function will retrieve all reports available
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< reports in raw format
        )
    {
        auto result = static_cast<result_t>( ::zetMetricTracerReadData(
            reinterpret_cast<zet_metric_tracer_handle_t>( getHandle() ),
            maxReportCount,
            pRawDataSize,
            pRawData ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricTracer::ReadData" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a pool of metric queries.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQueryPool*: handle of metric query pool
    /// 
    /// @throws result_t
    MetricQueryPool* __zecall
    MetricQueryPool::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        MetricGroup* pMetricGroup,                      ///< [in] metric group associated with the query object.
        const desc_t* desc                              ///< [in] metric query pool descriptor
        )
    {
        zet_metric_query_pool_handle_t hMetricQueryPool;

        auto result = static_cast<result_t>( ::zetMetricQueryPoolCreate(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<const zet_metric_query_pool_desc_t*>( desc ),
            &hMetricQueryPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQueryPool::Create" );

        MetricQueryPool* pMetricQueryPool = nullptr;

        try
        {
            pMetricQueryPool = new MetricQueryPool( reinterpret_cast<metric_query_pool_handle_t>( hMetricQueryPool ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricQueryPool;
            pMetricQueryPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricQueryPool::Create" );
        }

        return pMetricQueryPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a query pool object.
    /// 
    /// @details
    ///     - The application is responsible for destroying all query handles
    ///       created from the pool before destroying the pool itself
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the any query within the pool before it is
    ///       deleted
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query pool handle.
    /// 
    /// @throws result_t
    void __zecall
    MetricQueryPool::Destroy(
        MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
        )
    {
        auto result = static_cast<result_t>( ::zetMetricQueryPoolDestroy(
            reinterpret_cast<zet_metric_query_pool_handle_t>( pMetricQueryPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQueryPool::Destroy" );

        delete pMetricQueryPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates metric query object.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - MetricQuery*: handle of metric query
    /// 
    /// @throws result_t
    MetricQuery* __zecall
    MetricQuery::Create(
        MetricQueryPool* pMetricQueryPool,              ///< [in] pointer to the metric query pool
        uint32_t index                                  ///< [in] index of the query within the pool
        )
    {
        zet_metric_query_handle_t hMetricQuery;

        auto result = static_cast<result_t>( ::zetMetricQueryCreate(
            reinterpret_cast<zet_metric_query_pool_handle_t>( pMetricQueryPool->getHandle() ),
            index,
            &hMetricQuery ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Create" );

        MetricQuery* pMetricQuery = nullptr;

        try
        {
            pMetricQuery = new MetricQuery( reinterpret_cast<metric_query_handle_t>( hMetricQuery ), nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricQuery;
            pMetricQuery = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Create" );
        }

        return pMetricQuery;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a metric query object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the query before it is deleted
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query handle.
    /// 
    /// @throws result_t
    void __zecall
    MetricQuery::Destroy(
        MetricQuery* pMetricQuery                       ///< [in][release] pointer to metric query
        )
    {
        auto result = static_cast<result_t>( ::zetMetricQueryDestroy(
            reinterpret_cast<zet_metric_query_handle_t>( pMetricQuery->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Destroy" );

        delete pMetricQuery;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Resets a metric query object back to inital state.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the query before it is reset
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same query handle.
    /// 
    /// @throws result_t
    void __zecall
    MetricQuery::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetMetricQueryReset(
            reinterpret_cast<zet_metric_query_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query begin into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMetricQueryBegin(
        MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
        )
    {
        auto result = static_cast<result_t>( ::zetCommandListAppendMetricQueryBegin(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_query_handle_t>( pMetricQuery->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricQueryBegin" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query end into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMetricQueryEnd(
        MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
        ze::Event* pCompletionEvent                     ///< [in][optional] pointer to the completion event to signal
        )
    {
        auto result = static_cast<result_t>( ::zetCommandListAppendMetricQueryEnd(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_query_handle_t>( pMetricQuery->getHandle() ),
            ( pCompletionEvent ) ? reinterpret_cast<ze_event_handle_t>( pCompletionEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricQueryEnd" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query commands to flush all caches.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMetricMemoryBarrier(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetCommandListAppendMetricMemoryBarrier(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricMemoryBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves raw data for a given metric query.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void __zecall
    MetricQuery::GetData(
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                        ///< reports in raw format
        )
    {
        auto result = static_cast<result_t>( ::zetMetricQueryGetData(
            reinterpret_cast<zet_metric_query_handle_t>( getHandle() ),
            pRawDataSize,
            pRawData ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::GetData" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve debug info from module.
    /// 
    /// @details
    ///     - The caller can pass nullptr for pDebugInfo when querying only for
    ///       size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Module::GetDebugInfo(
        debug_info_format_t format,                     ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        auto result = static_cast<result_t>( ::zetModuleGetDebugInfo(
            reinterpret_cast<zet_module_handle_t>( getHandle() ),
            static_cast<zet_module_debug_info_format_t>( format ),
            pSize,
            pDebugInfo ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Module::GetDebugInfo" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve profiling information generated for the kernel.
    /// 
    /// @details
    ///     - Module must be created using the following build option:
    ///         + "-zet-profile-flags <n>" - enable generation of profile
    ///           information
    ///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - profile_info_t: pointer to profile info
    /// 
    /// @throws result_t
    Kernel::profile_info_t __zecall
    Kernel::GetProfileInfo(
        void
        )
    {
        zet_profile_info_t info;

        auto result = static_cast<result_t>( ::zetKernelGetProfileInfo(
            reinterpret_cast<zet_kernel_handle_t>( getHandle() ),
            &info ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Kernel::GetProfileInfo" );

        return *reinterpret_cast<profile_info_t*>( &info );
    }

    ///////////////////////////////////////////////////////////////////////////////
    Sysman::Sysman( 
        sysman_handle_t handle,                         ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanScheduler::SysmanScheduler( 
        sysman_sched_handle_t handle,                   ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanPerformanceFactor::SysmanPerformanceFactor( 
        sysman_perf_handle_t handle,                    ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanPower::SysmanPower( 
        sysman_pwr_handle_t handle,                     ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFrequency::SysmanFrequency( 
        sysman_freq_handle_t handle,                    ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanEngine::SysmanEngine( 
        sysman_engine_handle_t handle,                  ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanStandby::SysmanStandby( 
        sysman_standby_handle_t handle,                 ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFirmware::SysmanFirmware( 
        sysman_firmware_handle_t handle,                ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanMemory::SysmanMemory( 
        sysman_mem_handle_t handle,                     ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFabricPort::SysmanFabricPort( 
        sysman_fabric_port_handle_t handle,             ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanTemperature::SysmanTemperature( 
        sysman_temp_handle_t handle,                    ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanPsu::SysmanPsu( 
        sysman_psu_handle_t handle,                     ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanFan::SysmanFan( 
        sysman_fan_handle_t handle,                     ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanLed::SysmanLed( 
        sysman_led_handle_t handle,                     ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanRas::SysmanRas( 
        sysman_ras_handle_t handle,                     ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanDiagnostics::SysmanDiagnostics( 
        sysman_diag_handle_t handle,                    ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    SysmanEvent::SysmanEvent( 
        sysman_event_handle_t handle,                   ///< [in] handle of Sysman object
        Sysman* pSysman                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pSysman( pSysman )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the handle to access Sysman features for a device
    /// 
    /// @details
    ///     - The returned handle is unique.
    ///     - ::zet_device_handle_t returned by ::zeDeviceGetSubDevices() are not
    ///       support. Only use handles returned by ::zeDeviceGet(). All resources
    ///       on sub-devices can be enumerated through the primary device.
    /// 
    /// @returns
    ///     - Sysman*: Handle for accessing Sysman features
    /// 
    /// @throws result_t
    Sysman* __zecall
    Sysman::Get(
        Device* pDevice,                                ///< [in] Handle of the device
        version_t version                               ///< [in] Sysman version that application was built with
        )
    {
        zet_sysman_handle_t hSysman;

        auto result = static_cast<result_t>( ::zetSysmanGet(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            static_cast<zet_sysman_version_t>( version ),
            &hSysman ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::Get" );

        Sysman* pSysman = nullptr;

        try
        {
            pSysman = new Sysman( reinterpret_cast<sysman_handle_t>( hSysman ), pDevice );
        }
        catch( std::bad_alloc& )
        {
            delete pSysman;
            pSysman = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::Get" );
        }

        return pSysman;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties about the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DeviceGetProperties(
        properties_t* pProperties                       ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDeviceGetProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_sysman_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::DeviceGetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get information about the state of the device - if a reset is
    ///        required, reasons for the reset and if the device has been repaired
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DeviceGetState(
        state_t* pState                                 ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDeviceGetState(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_sysman_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::DeviceGetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset device
    /// 
    /// @details
    ///     - Performs a PCI bus reset of the device. This will result in all
    ///       current device state being lost.
    ///     - All applications using the device should be stopped before calling
    ///       this function.
    ///     - If the force argument is specified, all applications using the device
    ///       will be forcibly killed.
    ///     - The function will block until the device has restarted or a timeout
    ///       occurred waiting for the reset to complete.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DeviceReset(
        ze::bool_t force                                ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDeviceReset(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( force ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::DeviceReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle to a scheduler component
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::SchedulerGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanScheduler** ppScheduler                   ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_sched_handle_t> hScheduler;
        hScheduler.resize( ( ppScheduler ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanSchedulerGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hScheduler.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::SchedulerGet" );

        for( uint32_t i = 0; ( ppScheduler ) && ( i < *pCount ); ++i )
            ppScheduler[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppScheduler ) && ( i < *pCount ); ++i )
                ppScheduler[ i ] = new SysmanScheduler( reinterpret_cast<sysman_sched_handle_t>( hScheduler[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppScheduler ) && ( i < *pCount ); ++i )
            {
                delete ppScheduler[ i ];
                ppScheduler[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::SchedulerGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties related to a scheduler component
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::GetProperties(
        sched_properties_t* pProperties                 ///< [in,out] Structure that will contain property data.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerGetProperties(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            reinterpret_cast<zet_sched_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current scheduling mode in effect on a scheduler component.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::GetCurrentMode(
        Sysman::sched_mode_t* pMode                     ///< [in,out] Will contain the current scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerGetCurrentMode(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            reinterpret_cast<zet_sched_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::GetCurrentMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMEOUT
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::GetTimeoutModeProperties(
        ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        Sysman::sched_timeout_properties_t* pConfig     ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerGetTimeoutModeProperties(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( getDefaults ),
            reinterpret_cast<zet_sched_timeout_properties_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::GetTimeoutModeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMESLICE
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::GetTimesliceModeProperties(
        ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        Sysman::sched_timeslice_properties_t* pConfig   ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerGetTimesliceModeProperties(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( getDefaults ),
            reinterpret_cast<zet_sched_timeslice_properties_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::GetTimesliceModeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZET_SCHED_MODE_TIMEOUT or update scheduler
    ///        mode parameters if already running in this mode.
    /// 
    /// @details
    ///     - This mode is optimized for multiple applications or contexts
    ///       submitting work to the hardware. When higher priority work arrives,
    ///       the scheduler attempts to pause the current executing work within some
    ///       timeout interval, then submits the other work.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::SetTimeoutMode(
        Sysman::sched_timeout_properties_t* pProperties,///< [in] The properties to use when configurating this mode.
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetTimeoutMode(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            reinterpret_cast<zet_sched_timeout_properties_t*>( pProperties ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::SetTimeoutMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZET_SCHED_MODE_TIMESLICE or update
    ///        scheduler mode parameters if already running in this mode.
    /// 
    /// @details
    ///     - This mode is optimized to provide fair sharing of hardware execution
    ///       time between multiple contexts submitting work to the hardware
    ///       concurrently.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::SetTimesliceMode(
        Sysman::sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetTimesliceMode(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            reinterpret_cast<zet_sched_timeslice_properties_t*>( pProperties ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::SetTimesliceMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZET_SCHED_MODE_EXCLUSIVE
    /// 
    /// @details
    ///     - This mode is optimized for single application/context use-cases. It
    ///       permits a context to run indefinitely on the hardware without being
    ///       preempted or terminated. All pending work for other contexts must wait
    ///       until the running context completes with no further submitted work.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::SetExclusiveMode(
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetExclusiveMode(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::SetExclusiveMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZET_SCHED_MODE_COMPUTE_UNIT_DEBUG
    /// 
    /// @details
    ///     - This mode is optimized for application debug. It ensures that only one
    ///       command queue can execute work on the hardware at a given time. Work
    ///       is permitted to run as long as needed without enforcing any scheduler
    ///       fairness policies.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanScheduler::SetComputeUnitDebugMode(
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanSchedulerSetComputeUnitDebugMode(
            reinterpret_cast<zet_sysman_sched_handle_t>( getHandle() ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanScheduler::SetComputeUnitDebugMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handles to accelerator domains whose performance can be optimized
    ///        via a Performance Factor
    /// 
    /// @details
    ///     - A Performance Factor should be tuned for each workload.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PerformanceFactorGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanPerformanceFactor** ppPerf                ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_perf_handle_t> hPerf;
        hPerf.resize( ( ppPerf ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanPerformanceFactorGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hPerf.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PerformanceFactorGet" );

        for( uint32_t i = 0; ( ppPerf ) && ( i < *pCount ); ++i )
            ppPerf[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPerf ) && ( i < *pCount ); ++i )
                ppPerf[ i ] = new SysmanPerformanceFactor( reinterpret_cast<sysman_perf_handle_t>( hPerf[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPerf ) && ( i < *pCount ); ++i )
            {
                delete ppPerf[ i ];
                ppPerf[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PerformanceFactorGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties about a Performance Factor domain
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPerformanceFactor::GetProperties(
        perf_properties_t* pProperties                  ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPerformanceFactorGetProperties(
            reinterpret_cast<zet_sysman_perf_handle_t>( getHandle() ),
            reinterpret_cast<zet_perf_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPerformanceFactor::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current Performance Factor for a given domain
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPerformanceFactor::GetConfig(
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPerformanceFactorGetConfig(
            reinterpret_cast<zet_sysman_perf_handle_t>( getHandle() ),
            pFactor ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPerformanceFactor::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change the performance factor for a domain
    /// 
    /// @details
    ///     - The Performance Factor is a number between 0 and 100.
    ///     - A Performance Factor is a hint to the hardware. Depending on the
    ///       hardware, the request may not be granted. Follow up this function with
    ///       a call to ::zetSysmanPerformanceFactorGetConfig() to determine the
    ///       actual factor being used by the hardware.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPerformanceFactor::SetConfig(
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPerformanceFactorSetConfig(
            reinterpret_cast<zet_sysman_perf_handle_t>( getHandle() ),
            factor ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPerformanceFactor::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get information about host processes using the device
    /// 
    /// @details
    ///     - The number of processes connected to the device is dynamic. This means
    ///       that between a call to determine the correct value of pCount and the
    ///       subsequent call, the number of processes may have increased. It is
    ///       recommended that a large array be passed in so as to avoid receiving
    ///       the error ::ZE_RESULT_ERROR_INVALID_SIZE.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::ProcessesGetState(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of processes currently using the device.
                                                        ///< if count is non-zero but less than the number of processes, the driver
                                                        ///< will set to the number of processes currently using the device and
                                                        ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                        ///< if count is larger than the number of processes, then the driver will
                                                        ///< update the value with the correct number of processes that are returned.
        process_state_t* pProcesses                     ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                        ///< one for each process currently using the device
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanProcessesGetState(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<zet_process_state_t*>( pProcesses ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::ProcessesGetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI properties - address, max speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetProperties(
        pci_properties_t* pProperties                   ///< [in,out] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetProperties(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_pci_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PciGetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current PCI state - current speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetState(
        pci_state_t* pState                             ///< [in,out] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetState(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_pci_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PciGetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get information about each configured bar
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetBars(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of bars.
                                                        ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                        ///< if count is larger than the number of bar, then the driver will update
                                                        ///< the value with the correct number of bars that are returned.
        pci_bar_properties_t* pProperties               ///< [in,out][optional][range(0, *pCount)] array of bar properties
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetBars(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<zet_pci_bar_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PciGetBars" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI stats - bandwidth, number of packets, number of replays
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PciGetStats(
        pci_stats_t* pStats                             ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPciGetStats(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<zet_pci_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PciGetStats" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PowerGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanPower** ppPower                           ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_pwr_handle_t> hPower;
        hPower.resize( ( ppPower ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanPowerGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hPower.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PowerGet" );

        for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
            ppPower[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
                ppPower[ i ] = new SysmanPower( reinterpret_cast<sysman_pwr_handle_t>( hPower[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
            {
                delete ppPower[ i ];
                ppPower[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PowerGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties related to a power domain
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetProperties(
        power_properties_t* pProperties                 ///< [in,out] Structure that will contain property data.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetProperties(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPower::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy counter
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetEnergyCounter(
        power_energy_counter_t* pEnergy                 ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetEnergyCounter(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_energy_counter_t*>( pEnergy ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPower::GetEnergyCounter" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetLimits(
        power_sustained_limit_t* pSustained,            ///< [in,out][optional] The sustained power limit.
        power_burst_limit_t* pBurst,                    ///< [in,out][optional] The burst power limit.
        power_peak_limit_t* pPeak                       ///< [in,out][optional] The peak power limit.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetLimits(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<zet_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<zet_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPower::GetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::SetLimits(
        const power_sustained_limit_t* pSustained,      ///< [in][optional] The sustained power limit.
        const power_burst_limit_t* pBurst,              ///< [in][optional] The burst power limit.
        const power_peak_limit_t* pPeak                 ///< [in][optional] The peak power limit.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerSetLimits(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<const zet_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<const zet_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<const zet_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPower::SetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy threshold
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::GetEnergyThreshold(
        energy_threshold_t* pThreshold                  ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerGetEnergyThreshold(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zet_energy_threshold_t*>( pThreshold ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPower::GetEnergyThreshold" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set energy threshold
    /// 
    /// @details
    ///     - An event ::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED will be
    ///       generated when the delta energy consumed starting from this call
    ///       exceeds the specified threshold. Use the function
    ///       ::zetSysmanEventSetConfig() to start receiving the event.
    ///     - Only one running process can control the energy threshold at a given
    ///       time. If another process attempts to change the energy threshold, the
    ///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
    ///       ::zetSysmanPowerGetEnergyThreshold() to determine the process ID
    ///       currently controlling this setting.
    ///     - Calling this function will remove any pending energy thresholds and
    ///       start counting from the time of this call.
    ///     - Once the energy threshold has been reached and the event generated,
    ///       the threshold is automatically removed. It is up to the application to
    ///       request a new threshold.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPower::SetEnergyThreshold(
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPowerSetEnergyThreshold(
            reinterpret_cast<zet_sysman_pwr_handle_t>( getHandle() ),
            threshold ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPower::SetEnergyThreshold" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of frequency domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FrequencyGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFrequency** ppFrequency                   ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_freq_handle_t> hFrequency;
        hFrequency.resize( ( ppFrequency ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFrequencyGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hFrequency.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FrequencyGet" );

        for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
            ppFrequency[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
                ppFrequency[ i ] = new SysmanFrequency( reinterpret_cast<sysman_freq_handle_t>( hFrequency[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
            {
                delete ppFrequency[ i ];
                ppFrequency[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FrequencyGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency properties - available frequencies
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetProperties(
        freq_properties_t* pProperties                  ///< [in,out] The frequency properties for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetProperties(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get available non-overclocked hardware clock frequencies for the
    ///        frequency domain
    /// 
    /// @details
    ///     - The list of available frequencies is returned in order of slowest to
    ///       fastest.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetAvailableClocks(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of frequencies available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                        ///< If count is larger than the number of frequencies available, then the
                                                        ///< driver will update the value with the correct number of frequencies available.
        double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                        ///< MHz and sorted from slowest to fastest
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetAvailableClocks(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            pCount,
            phFrequency ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::GetAvailableClocks" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetRange(
        freq_range_t* pLimits                           ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetRange(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::GetRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set frequency range between which the hardware can operate.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::SetRange(
        const freq_range_t* pLimits                     ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencySetRange(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<const zet_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::SetRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency state - frequency request, actual frequency, TDP
    ///        limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetState(
        freq_state_t* pState                            ///< [in,out] Frequency state for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetState(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency throttle time
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::GetThrottleTime(
        freq_throttle_time_t* pThrottleTime             ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyGetThrottleTime(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_freq_throttle_time_t*>( pThrottleTime ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::GetThrottleTime" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the overclocking capabilities.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::OcGetCapabilities(
        oc_capabilities_t* pOcCapabilities              ///< [in,out] Pointer to the capabilities structure
                                                        ///< ::zet_oc_capabilities_t.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyOcGetCapabilities(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_capabilities_t*>( pOcCapabilities ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::OcGetCapabilities" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current overclocking configuration.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::OcGetConfig(
        oc_config_t* pOcConfiguration                   ///< [in,out] Pointer to the configuration structure ::zet_oc_config_t.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyOcGetConfig(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_config_t*>( pOcConfiguration ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::OcGetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change the overclocking configuration.
    /// 
    /// @details
    ///     - If ::zet_oc_config_t.mode is set to ::ZET_OC_MODE_OFF, overclocking
    ///       will be turned off and the hardware returned to run with factory
    ///       voltages/frequencies. Call ::zetSysmanFrequencyOcSetIccMax() and
    ///       ::zetSysmanFrequencyOcSetTjMax() separately with 0.0 to return those
    ///       settings to factory defaults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::OcSetConfig(
        oc_config_t* pOcConfiguration,                  ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
        ze::bool_t* pDeviceRestart                      ///< [in,out] This will be set to true if the device needs to be restarted
                                                        ///< in order to enable the new overclock settings.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyOcSetConfig(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            reinterpret_cast<zet_oc_config_t*>( pOcConfiguration ),
            reinterpret_cast<ze_bool_t*>( pDeviceRestart ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::OcSetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the maximum current limit setting.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::OcGetIccMax(
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyOcGetIccMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            pOcIccMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::OcGetIccMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change the maximum current limit setting.
    /// 
    /// @details
    ///     - Setting ocIccMax to 0.0 will return the value to the factory default.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::OcSetIccMax(
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyOcSetIccMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            ocIccMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::OcSetIccMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the maximum temperature limit setting.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::OcGetTjMax(
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyOcGetTjMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            pOcTjMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::OcGetTjMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change the maximum temperature limit setting.
    /// 
    /// @details
    ///     - Setting ocTjMax to 0.0 will return the value to the factory default.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFrequency::OcSetTjMax(
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFrequencyOcSetTjMax(
            reinterpret_cast<zet_sysman_freq_handle_t>( getHandle() ),
            ocTjMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFrequency::OcSetTjMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of engine groups
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::EngineGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanEngine** ppEngine                         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_engine_handle_t> hEngine;
        hEngine.resize( ( ppEngine ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanEngineGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hEngine.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::EngineGet" );

        for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
            ppEngine[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
                ppEngine[ i ] = new SysmanEngine( reinterpret_cast<sysman_engine_handle_t>( hEngine[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
            {
                delete ppEngine[ i ];
                ppEngine[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::EngineGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get engine group properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEngine::GetProperties(
        engine_properties_t* pProperties                ///< [in,out] The properties for the specified engine group.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEngineGetProperties(
            reinterpret_cast<zet_sysman_engine_handle_t>( getHandle() ),
            reinterpret_cast<zet_engine_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanEngine::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the activity stats for an engine group
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEngine::GetActivity(
        engine_stats_t* pStats                          ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEngineGetActivity(
            reinterpret_cast<zet_sysman_engine_handle_t>( getHandle() ),
            reinterpret_cast<zet_engine_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanEngine::GetActivity" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of standby controls
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::StandbyGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanStandby** ppStandby                       ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_standby_handle_t> hStandby;
        hStandby.resize( ( ppStandby ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanStandbyGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hStandby.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::StandbyGet" );

        for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
            ppStandby[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
                ppStandby[ i ] = new SysmanStandby( reinterpret_cast<sysman_standby_handle_t>( hStandby[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
            {
                delete ppStandby[ i ];
                ppStandby[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::StandbyGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get standby hardware component properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanStandby::GetProperties(
        standby_properties_t* pProperties               ///< [in,out] Will contain the standby hardware properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanStandbyGetProperties(
            reinterpret_cast<zet_sysman_standby_handle_t>( getHandle() ),
            reinterpret_cast<zet_standby_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanStandby::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanStandby::GetMode(
        standby_promo_mode_t* pMode                     ///< [in,out] Will contain the current standby mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanStandbyGetMode(
            reinterpret_cast<zet_sysman_standby_handle_t>( getHandle() ),
            reinterpret_cast<zet_standby_promo_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanStandby::GetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanStandby::SetMode(
        standby_promo_mode_t mode                       ///< [in] New standby mode.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanStandbySetMode(
            reinterpret_cast<zet_sysman_standby_handle_t>( getHandle() ),
            static_cast<zet_standby_promo_mode_t>( mode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanStandby::SetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of firmwares
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FirmwareGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFirmware** ppFirmware                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_firmware_handle_t> hFirmware;
        hFirmware.resize( ( ppFirmware ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFirmwareGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hFirmware.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FirmwareGet" );

        for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
            ppFirmware[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
                ppFirmware[ i ] = new SysmanFirmware( reinterpret_cast<sysman_firmware_handle_t>( hFirmware[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
            {
                delete ppFirmware[ i ];
                ppFirmware[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FirmwareGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFirmware::GetProperties(
        firmware_properties_t* pProperties              ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFirmwareGetProperties(
            reinterpret_cast<zet_sysman_firmware_handle_t>( getHandle() ),
            reinterpret_cast<zet_firmware_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFirmware::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware checksum
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFirmware::GetChecksum(
        uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFirmwareGetChecksum(
            reinterpret_cast<zet_sysman_firmware_handle_t>( getHandle() ),
            pChecksum ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFirmware::GetChecksum" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Flash a new firmware image
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFirmware::Flash(
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFirmwareFlash(
            reinterpret_cast<zet_sysman_firmware_handle_t>( getHandle() ),
            pImage,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFirmware::Flash" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of memory modules
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::MemoryGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanMemory** ppMemory                         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_mem_handle_t> hMemory;
        hMemory.resize( ( ppMemory ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanMemoryGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hMemory.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::MemoryGet" );

        for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
            ppMemory[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
                ppMemory[ i ] = new SysmanMemory( reinterpret_cast<sysman_mem_handle_t>( hMemory[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
            {
                delete ppMemory[ i ];
                ppMemory[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::MemoryGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanMemory::GetProperties(
        mem_properties_t* pProperties                   ///< [in,out] Will contain memory properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanMemoryGetProperties(
            reinterpret_cast<zet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<zet_mem_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanMemory::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory state - health, allocated
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanMemory::GetState(
        mem_state_t* pState                             ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanMemoryGetState(
            reinterpret_cast<zet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<zet_mem_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanMemory::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory bandwidth
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanMemory::GetBandwidth(
        mem_bandwidth_t* pBandwidth                     ///< [in,out] Will contain the current health, free memory, total memory
                                                        ///< size.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanMemoryGetBandwidth(
            reinterpret_cast<zet_sysman_mem_handle_t>( getHandle() ),
            reinterpret_cast<zet_mem_bandwidth_t*>( pBandwidth ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanMemory::GetBandwidth" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of Fabric ports in a device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FabricPortGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFabricPort** ppPort                       ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_fabric_port_handle_t> hPort;
        hPort.resize( ( ppPort ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFabricPortGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hPort.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FabricPortGet" );

        for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            ppPort[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
                ppPort[ i ] = new SysmanFabricPort( reinterpret_cast<sysman_fabric_port_handle_t>( hPort[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            {
                delete ppPort[ i ];
                ppPort[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FabricPortGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetProperties(
        fabric_port_properties_t* pProperties           ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetProperties(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFabricPort::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port link type
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetLinkType(
        ze::bool_t verbose,                             ///< [in] Set to true to get a more detailed report.
        fabric_link_type_t* pLinkType                   ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetLinkType(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( verbose ),
            reinterpret_cast<zet_fabric_link_type_t*>( pLinkType ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFabricPort::GetLinkType" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetConfig(
        fabric_port_config_t* pConfig                   ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetConfig(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFabricPort::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set Fabric port configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::SetConfig(
        const fabric_port_config_t* pConfig             ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortSetConfig(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<const zet_fabric_port_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFabricPort::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port state - status (green/yellow/red/black), reasons for
    ///        link degradation or instability, current rx/tx speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetState(
        fabric_port_state_t* pState                     ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetState(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFabricPort::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port throughput
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFabricPort::GetThroughput(
        fabric_port_throughput_t* pThroughput           ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFabricPortGetThroughput(
            reinterpret_cast<zet_sysman_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zet_fabric_port_throughput_t*>( pThroughput ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFabricPort::GetThroughput" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of temperature sensors
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::TemperatureGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanTemperature** ppTemperature               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_temp_handle_t> hTemperature;
        hTemperature.resize( ( ppTemperature ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanTemperatureGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hTemperature.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::TemperatureGet" );

        for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
            ppTemperature[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
                ppTemperature[ i ] = new SysmanTemperature( reinterpret_cast<sysman_temp_handle_t>( hTemperature[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
            {
                delete ppTemperature[ i ];
                ppTemperature[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::TemperatureGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperature sensor properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanTemperature::GetProperties(
        temp_properties_t* pProperties                  ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanTemperatureGetProperties(
            reinterpret_cast<zet_sysman_temp_handle_t>( getHandle() ),
            reinterpret_cast<zet_temp_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanTemperature::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperature configuration for this sensor - which events are
    ///        triggered and the trigger conditions
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanTemperature::GetConfig(
        temp_config_t* pConfig                          ///< [in,out] Returns current configuration.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanTemperatureGetConfig(
            reinterpret_cast<zet_sysman_temp_handle_t>( getHandle() ),
            reinterpret_cast<zet_temp_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanTemperature::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set temperature configuration for this sensor - indicates which events
    ///        are triggered and the trigger conditions
    /// 
    /// @details
    ///     - Events ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL will be triggered when
    ///       temperature reaches the critical range. Use the function
    ///       ::zetSysmanEventSetConfig() to start receiving this event.
    ///     - Events ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 and
    ///       ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 will be generated when
    ///       temperature cross the thresholds set using this function. Use the
    ///       function ::zetSysmanEventSetConfig() to start receiving these events.
    ///     - Only one running process can set the temperature configuration at a
    ///       time. If another process attempts to change the configuration, the
    ///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
    ///       ::zetSysmanTemperatureGetConfig() will return the process ID currently
    ///       controlling these settings.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanTemperature::SetConfig(
        const temp_config_t* pConfig                    ///< [in] New configuration.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanTemperatureSetConfig(
            reinterpret_cast<zet_sysman_temp_handle_t>( getHandle() ),
            reinterpret_cast<const zet_temp_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanTemperature::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the temperature from a specified sensor
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanTemperature::GetState(
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanTemperatureGetState(
            reinterpret_cast<zet_sysman_temp_handle_t>( getHandle() ),
            pTemperature ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanTemperature::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power supplies
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::PsuGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanPsu** ppPsu                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_psu_handle_t> hPsu;
        hPsu.resize( ( ppPsu ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanPsuGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hPsu.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PsuGet" );

        for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
            ppPsu[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
                ppPsu[ i ] = new SysmanPsu( reinterpret_cast<sysman_psu_handle_t>( hPsu[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
            {
                delete ppPsu[ i ];
                ppPsu[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::PsuGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power supply properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPsu::GetProperties(
        psu_properties_t* pProperties                   ///< [in,out] Will contain the properties of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPsuGetProperties(
            reinterpret_cast<zet_sysman_psu_handle_t>( getHandle() ),
            reinterpret_cast<zet_psu_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPsu::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current power supply state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanPsu::GetState(
        psu_state_t* pState                             ///< [in,out] Will contain the current state of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanPsuGetState(
            reinterpret_cast<zet_sysman_psu_handle_t>( getHandle() ),
            reinterpret_cast<zet_psu_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanPsu::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of fans
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::FanGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanFan** ppFan                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_fan_handle_t> hFan;
        hFan.resize( ( ppFan ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanFanGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hFan.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FanGet" );

        for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
            ppFan[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
                ppFan[ i ] = new SysmanFan( reinterpret_cast<sysman_fan_handle_t>( hFan[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
            {
                delete ppFan[ i ];
                ppFan[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::FanGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::GetProperties(
        fan_properties_t* pProperties                   ///< [in,out] Will contain the properties of the fan.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanGetProperties(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<zet_fan_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFan::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current fan configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::GetConfig(
        fan_config_t* pConfig                           ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanGetConfig(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<zet_fan_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFan::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::SetConfig(
        const fan_config_t* pConfig                     ///< [in] New fan configuration.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanSetConfig(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            reinterpret_cast<const zet_fan_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFan::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a fan - current mode and speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanFan::GetState(
        fan_speed_units_t units,                        ///< [in] The units in which the fan speed should be returned.
        uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanFanGetState(
            reinterpret_cast<zet_sysman_fan_handle_t>( getHandle() ),
            static_cast<zet_fan_speed_units_t>( units ),
            pSpeed ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanFan::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of LEDs
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::LedGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanLed** ppLed                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_led_handle_t> hLed;
        hLed.resize( ( ppLed ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanLedGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hLed.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::LedGet" );

        for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
            ppLed[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
                ppLed[ i ] = new SysmanLed( reinterpret_cast<sysman_led_handle_t>( hLed[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
            {
                delete ppLed[ i ];
                ppLed[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::LedGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get LED properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanLed::GetProperties(
        led_properties_t* pProperties                   ///< [in,out] Will contain the properties of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanLedGetProperties(
            reinterpret_cast<zet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<zet_led_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanLed::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a LED - on/off, color
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanLed::GetState(
        led_state_t* pState                             ///< [in,out] Will contain the current state of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanLedGetState(
            reinterpret_cast<zet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<zet_led_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanLed::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set state of a LED - on/off, color
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanLed::SetState(
        const led_state_t* pState                       ///< [in] New state of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanLedSetState(
            reinterpret_cast<zet_sysman_led_handle_t>( getHandle() ),
            reinterpret_cast<const zet_led_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanLed::SetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of all RAS error sets on a device
    /// 
    /// @details
    ///     - A RAS error set is a collection of RAS error counters of a given type
    ///       (correctable/uncorrectable) from hardware blocks contained within a
    ///       sub-device or within the device.
    ///     - A device without sub-devices will typically return two handles, one
    ///       for correctable errors sets and one for uncorrectable error sets.
    ///     - A device with sub-devices will return RAS error sets for each
    ///       sub-device and possibly RAS error sets for hardware blocks outside the
    ///       sub-devices.
    ///     - If the function completes successfully but pCount is set to 0, RAS
    ///       features are not available/enabled on this device.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::RasGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanRas** ppRas                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_ras_handle_t> hRas;
        hRas.resize( ( ppRas ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanRasGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hRas.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::RasGet" );

        for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
            ppRas[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
                ppRas[ i ] = new SysmanRas( reinterpret_cast<sysman_ras_handle_t>( hRas[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
            {
                delete ppRas[ i ];
                ppRas[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::RasGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get RAS properties of a given RAS error set - this enables discovery
    ///        of the type of RAS error set (correctable/uncorrectable) and if
    ///        located on a sub-device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanRas::GetProperties(
        ras_properties_t* pProperties                   ///< [in,out] Structure describing RAS properties
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanRasGetProperties(
            reinterpret_cast<zet_sysman_ras_handle_t>( getHandle() ),
            reinterpret_cast<zet_ras_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanRas::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get RAS error thresholds that control when RAS events are generated
    /// 
    /// @details
    ///     - The driver maintains counters for all RAS error sets and error
    ///       categories. Events are generated when errors occur. The configuration
    ///       enables setting thresholds to limit when events are sent.
    ///     - When a particular RAS correctable error counter exceeds the configured
    ///       threshold, the event ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
    ///       will be triggered.
    ///     - When a particular RAS uncorrectable error counter exceeds the
    ///       configured threshold, the event
    ///       ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be triggered.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanRas::GetConfig(
        ras_config_t* pConfig                           ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanRasGetConfig(
            reinterpret_cast<zet_sysman_ras_handle_t>( getHandle() ),
            reinterpret_cast<zet_ras_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanRas::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set RAS error thresholds that control when RAS events are generated
    /// 
    /// @details
    ///     - The driver maintains counters for all RAS error sets and error
    ///       categories. Events are generated when errors occur. The configuration
    ///       enables setting thresholds to limit when events are sent.
    ///     - When a particular RAS correctable error counter exceeds the specified
    ///       threshold, the event ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
    ///       will be generated.
    ///     - When a particular RAS uncorrectable error counter exceeds the
    ///       specified threshold, the event
    ///       ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be generated.
    ///     - Call ::zetSysmanRasGetState() and set the clear flag to true to
    ///       restart event generation once counters have exceeded thresholds.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanRas::SetConfig(
        const ras_config_t* pConfig                     ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanRasSetConfig(
            reinterpret_cast<zet_sysman_ras_handle_t>( getHandle() ),
            reinterpret_cast<const zet_ras_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanRas::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current value of RAS error counters for a particular error set
    /// 
    /// @details
    ///     - Clearing errors will affect other threads/applications - the counter
    ///       values will start from zero.
    ///     - Clearing errors requires write permissions.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanRas::GetState(
        ze::bool_t clear,                               ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in,out] The number total number of errors that have occurred
        ras_details_t* pDetails                         ///< [in,out][optional] Breakdown of where errors have occurred
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanRasGetState(
            reinterpret_cast<zet_sysman_ras_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( clear ),
            pTotalErrors,
            reinterpret_cast<zet_ras_details_t*>( pDetails ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanRas::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the event handle for the specified device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - SysmanEvent*: The event handle for the specified device.
    /// 
    /// @throws result_t
    SysmanEvent* __zecall
    Sysman::EventGet(
        void
        )
    {
        zet_sysman_event_handle_t hEvent;

        auto result = static_cast<result_t>( ::zetSysmanEventGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            &hEvent ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::EventGet" );

        SysmanEvent* pEvent = nullptr;

        try
        {
            pEvent = new SysmanEvent( reinterpret_cast<sysman_event_handle_t>( hEvent ), this );
        }
        catch( std::bad_alloc& )
        {
            delete pEvent;
            pEvent = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::EventGet" );
        }

        return pEvent;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which events are currently registered on the specified device
    ///        event handler
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEvent::GetConfig(
        event_config_t* pConfig                         ///< [in,out] Will contain the current event configuration (list of
                                                        ///< registered events).
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEventGetConfig(
            reinterpret_cast<zet_sysman_event_handle_t>( getHandle() ),
            reinterpret_cast<zet_event_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanEvent::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set a new event configuration (list of registered events) on the
    ///        specified device event handler
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEvent::SetConfig(
        const event_config_t* pConfig                   ///< [in] New event configuration (list of registered events).
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEventSetConfig(
            reinterpret_cast<zet_sysman_event_handle_t>( getHandle() ),
            reinterpret_cast<const zet_event_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanEvent::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get events that have been triggered for a specific device
    /// 
    /// @details
    ///     - If events have occurred on the specified device event handle, they are
    ///       returned and the corresponding event status is cleared if the argument
    ///       clear = true.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEvent::GetState(
        ze::bool_t clear,                               ///< [in] Indicates if the event list for this device should be cleared.
        uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                        ///< triggered by this device.
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanEventGetState(
            reinterpret_cast<zet_sysman_event_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( clear ),
            pEvents ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanEvent::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Wait for the specified list of event handles to receive any registered
    ///        events
    /// 
    /// @details
    ///     - If previous events arrived and were not cleared using
    ///       ::zetSysmanEventGetState(), this call will return immediately.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanEvent::Listen(
        ze::Driver* pDriver,                            ///< [in] pointer to the driver instance
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                        ///< ::ZET_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                        ///< ::ZET_EVENT_WAIT_INFINITE to block until events arrive.
        uint32_t count,                                 ///< [in] Number of handles in phEvents
        SysmanEvent** ppEvents,                         ///< [in][range(0, count)] Handle of events that should be listened to
        uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                        ///< triggered by any of the supplied event handles. If timeout is not
                                                        ///< ::ZET_EVENT_WAIT_INFINITE and this value is
                                                        ///< ::ZET_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
        )
    {
        thread_local std::vector<zet_sysman_event_handle_t> hEvents;
        hEvents.resize( 0 );
        hEvents.reserve( count );
        for( uint32_t i = 0; i < count; ++i )
            hEvents.emplace_back( reinterpret_cast<zet_sysman_event_handle_t>( ppEvents[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zetSysmanEventListen(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            timeout,
            count,
            hEvents.data(),
            pEvents ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanEvent::Listen" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of diagnostics test suites
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Sysman::DiagnosticsGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        SysmanDiagnostics** ppDiagnostics               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zet_sysman_diag_handle_t> hDiagnostics;
        hDiagnostics.resize( ( ppDiagnostics ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetSysmanDiagnosticsGet(
            reinterpret_cast<zet_sysman_handle_t>( getHandle() ),
            pCount,
            hDiagnostics.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::DiagnosticsGet" );

        for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
            ppDiagnostics[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
                ppDiagnostics[ i ] = new SysmanDiagnostics( reinterpret_cast<sysman_diag_handle_t>( hDiagnostics[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
            {
                delete ppDiagnostics[ i ];
                ppDiagnostics[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Sysman::DiagnosticsGet" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties of a diagnostics test suite
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanDiagnostics::GetProperties(
        diag_properties_t* pProperties                  ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDiagnosticsGetProperties(
            reinterpret_cast<zet_sysman_diag_handle_t>( getHandle() ),
            reinterpret_cast<zet_diag_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanDiagnostics::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get individual tests that can be run separately. Not all test suites
    ///        permit running individual tests - check
    ///        ::zet_diag_properties_t.haveTests
    /// 
    /// @details
    ///     - The list of available tests is returned in order of increasing test
    ///       index ::zet_diag_test_t.index.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    SysmanDiagnostics::GetTests(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of tests available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                        ///< If count is larger than the number of tests available, then the driver
                                                        ///< will update the value with the correct number of tests available.
        diag_test_t* pTests                             ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                        ///< increasing value of ::zet_diag_test_t.index
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDiagnosticsGetTests(
            reinterpret_cast<zet_sysman_diag_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<zet_diag_test_t*>( pTests ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanDiagnostics::GetTests" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Run a diagnostics test suite, either all tests or a subset of tests.
    /// 
    /// @details
    ///     - WARNING: Performancing diagnostics may destroy current device state
    ///       information. Gracefully close any running workloads before initiating.
    ///     - To run all tests in a test suite, set start =
    ///       ::ZET_DIAG_FIRST_TEST_INDEX and end = ::ZET_DIAG_LAST_TEST_INDEX.
    ///     - If the test suite permits running individual tests,
    ///       ::zet_diag_properties_t.haveTests will be true. In this case, the
    ///       function ::zetSysmanDiagnosticsGetTests() can be called to get the
    ///       list of tests and corresponding indices that can be supplied to the
    ///       arguments start and end in this function.
    ///     - This function will block until the diagnostics have completed.
    /// 
    /// @throws result_t
    void __zecall
    SysmanDiagnostics::RunTests(
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        diag_result_t* pResult                          ///< [in,out] The result of the diagnostics
        )
    {
        auto result = static_cast<result_t>( ::zetSysmanDiagnosticsRunTests(
            reinterpret_cast<zet_sysman_diag_handle_t>( getHandle() ),
            start,
            end,
            reinterpret_cast<zet_diag_result_t*>( pResult ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::SysmanDiagnostics::RunTests" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    Tracer::Tracer( 
        tracer_handle_t handle,                         ///< [in] handle of tracer object
        Driver* pDriver,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the tracer object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a tracer for the specified driver.
    /// 
    /// @details
    ///     - The tracer can only be used on the driver on which it was created.
    ///     - The tracer is created in the disabled state.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Tracer*: pointer to handle of tracer object created
    /// 
    /// @throws result_t
    Tracer* __zecall
    Tracer::Create(
        Driver* pDriver,                                ///< [in] pointer to the driver
        const desc_t* desc                              ///< [in] pointer to tracer descriptor
        )
    {
        zet_tracer_handle_t hTracer;

        auto result = static_cast<result_t>( ::zetTracerCreate(
            reinterpret_cast<zet_driver_handle_t>( pDriver->getHandle() ),
            reinterpret_cast<const zet_tracer_desc_t*>( desc ),
            &hTracer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Tracer::Create" );

        Tracer* pTracer = nullptr;

        try
        {
            pTracer = new Tracer( reinterpret_cast<tracer_handle_t>( hTracer ), pDriver, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pTracer;
            pTracer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Tracer::Create" );
        }

        return pTracer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a tracer.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    ///     - The implementation of this function will stall and wait on any
    ///       outstanding threads executing callbacks before freeing any Host
    ///       allocations associated with this tracer.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::Destroy(
        Tracer* pTracer                                 ///< [in][release] pointer to tracer object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zetTracerDestroy(
            reinterpret_cast<zet_tracer_handle_t>( pTracer->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Tracer::Destroy" );

        delete pTracer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the collection of callbacks to be executed **before** driver
    ///        execution.
    /// 
    /// @details
    ///     - The application only needs to set the function pointers it is
    ///       interested in receiving; all others should be 'nullptr'
    ///     - The application must ensure that no other threads are executing
    ///       functions for which the tracing functions are changing.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::SetPrologues(
        core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto result = static_cast<result_t>( ::zetTracerSetPrologues(
            reinterpret_cast<zet_tracer_handle_t>( getHandle() ),
            reinterpret_cast<zet_core_callbacks_t*>( pCoreCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Tracer::SetPrologues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the collection of callbacks to be executed **after** driver
    ///        execution.
    /// 
    /// @details
    ///     - The application only needs to set the function pointers it is
    ///       interested in receiving; all others should be 'nullptr'
    ///     - The application must ensure that no other threads are executing
    ///       functions for which the tracing functions are changing.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::SetEpilogues(
        core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto result = static_cast<result_t>( ::zetTracerSetEpilogues(
            reinterpret_cast<zet_tracer_handle_t>( getHandle() ),
            reinterpret_cast<zet_core_callbacks_t*>( pCoreCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Tracer::SetEpilogues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Enables (or disables) the tracer
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::SetEnabled(
        ze::bool_t enable                               ///< [in] enable the tracer if true; disable if false
        )
    {
        auto result = static_cast<result_t>( ::zetTracerSetEnabled(
            reinterpret_cast<zet_tracer_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( enable ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Tracer::SetEnabled" );
    }

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_flags_t to std::string
    std::string to_string( const Debug::event_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEBUG_EVENT_FLAG_NONE   ";
        
        if( static_cast<uint32_t>(Debug::event_flags_t::DEBUG_EVENT_FLAG_STOPPED) & bits )
            str += "DEBUG_EVENT_FLAG_STOPPED | ";

        return ( str.size() > 3 ) 
            ? "Debug::event_flags_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Debug::event_flags_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_type_t to std::string
    std::string to_string( const Debug::event_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::event_type_t::DEBUG_EVENT_INVALID:
            str = "Debug::event_type_t::DEBUG_EVENT_INVALID";
            break;

        case Debug::event_type_t::DEBUG_EVENT_DETACHED:
            str = "Debug::event_type_t::DEBUG_EVENT_DETACHED";
            break;

        case Debug::event_type_t::DEBUG_EVENT_PROCESS_ENTRY:
            str = "Debug::event_type_t::DEBUG_EVENT_PROCESS_ENTRY";
            break;

        case Debug::event_type_t::DEBUG_EVENT_PROCESS_EXIT:
            str = "Debug::event_type_t::DEBUG_EVENT_PROCESS_EXIT";
            break;

        case Debug::event_type_t::DEBUG_EVENT_MODULE_LOAD:
            str = "Debug::event_type_t::DEBUG_EVENT_MODULE_LOAD";
            break;

        case Debug::event_type_t::DEBUG_EVENT_MODULE_UNLOAD:
            str = "Debug::event_type_t::DEBUG_EVENT_MODULE_UNLOAD";
            break;

        case Debug::event_type_t::DEBUG_EVENT_EXCEPTION:
            str = "Debug::event_type_t::DEBUG_EVENT_EXCEPTION";
            break;

        default:
            str = "Debug::event_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::detach_reason_t to std::string
    std::string to_string( const Debug::detach_reason_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::detach_reason_t::DEBUG_DETACH_INVALID:
            str = "Debug::detach_reason_t::DEBUG_DETACH_INVALID";
            break;

        case Debug::detach_reason_t::DEBUG_DETACH_HOST_EXIT:
            str = "Debug::detach_reason_t::DEBUG_DETACH_HOST_EXIT";
            break;

        default:
            str = "Debug::detach_reason_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_intel_graphics_t to std::string
    std::string to_string( const Debug::memory_space_intel_graphics_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_DEFAULT:
            str = "Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_DEFAULT";
            break;

        case Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_SLM:
            str = "Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_SLM";
            break;

        default:
            str = "Debug::memory_space_intel_graphics_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_intel_graphics_t to std::string
    std::string to_string( const Debug::state_intel_graphics_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_INVALID:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_INVALID";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_GRF:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_GRF";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ACC:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ACC";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ADDR:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ADDR";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_FLAG:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_FLAG";
            break;

        default:
            str = "Debug::state_intel_graphics_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_v1_t to std::string
    std::string to_string( const Debug::config_v1_t val )
    {
        std::string str;
        
        str += "Debug::config_v1_t::pid : ";
        str += std::to_string(val.pid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_variants_t to std::string
    std::string to_string( const Debug::config_variants_t val )
    {
        std::string str;
        
        str += "Debug::config_variants_t::v1 : ";
        str += to_string(val.v1);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_t to std::string
    std::string to_string( const Debug::config_t val )
    {
        std::string str;
        
        str += "Debug::config_t::version : ";
        str += std::to_string(val.version);
        str += "\n";
        
        str += "Debug::config_t::variant : ";
        str += to_string(val.variant);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_detached_t to std::string
    std::string to_string( const Debug::event_info_detached_t val )
    {
        std::string str;
        
        str += "Debug::event_info_detached_t::reason : ";
        str += std::to_string(val.reason);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_module_t to std::string
    std::string to_string( const Debug::event_info_module_t val )
    {
        std::string str;
        
        str += "Debug::event_info_module_t::moduleBegin : ";
        str += std::to_string(val.moduleBegin);
        str += "\n";
        
        str += "Debug::event_info_module_t::moduleEnd : ";
        str += std::to_string(val.moduleEnd);
        str += "\n";
        
        str += "Debug::event_info_module_t::load : ";
        str += std::to_string(val.load);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_t to std::string
    std::string to_string( const Debug::event_info_t val )
    {
        std::string str;
        
        str += "Debug::event_info_t::detached : ";
        str += to_string(val.detached);
        str += "\n";
        
        str += "Debug::event_info_t::module : ";
        str += to_string(val.module);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_t to std::string
    std::string to_string( const Debug::event_t val )
    {
        std::string str;
        
        str += "Debug::event_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Debug::event_t::thread : ";
        str += std::to_string(val.thread);
        str += "\n";
        
        str += "Debug::event_t::flags : ";
        str += std::to_string(val.flags);
        str += "\n";
        
        str += "Debug::event_t::info : ";
        str += to_string(val.info);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_section_t to std::string
    std::string to_string( const Debug::state_section_t val )
    {
        std::string str;
        
        str += "Debug::state_section_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Debug::state_section_t::version : ";
        str += std::to_string(val.version);
        str += "\n";
        
        str += "Debug::state_section_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Debug::state_section_t::offset : ";
        str += std::to_string(val.offset);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_t to std::string
    std::string to_string( const Debug::state_t val )
    {
        std::string str;
        
        str += "Debug::state_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Debug::state_t::headerSize : ";
        str += std::to_string(val.headerSize);
        str += "\n";
        
        str += "Debug::state_t::secSize : ";
        str += std::to_string(val.secSize);
        str += "\n";
        
        str += "Debug::state_t::numSec : ";
        str += std::to_string(val.numSec);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( const value_type_t val )
    {
        std::string str;

        switch( val )
        {
        case value_type_t::UINT32:
            str = "value_type_t::UINT32";
            break;

        case value_type_t::UINT64:
            str = "value_type_t::UINT64";
            break;

        case value_type_t::FLOAT32:
            str = "value_type_t::FLOAT32";
            break;

        case value_type_t::FLOAT64:
            str = "value_type_t::FLOAT64";
            break;

        case value_type_t::BOOL8:
            str = "value_type_t::BOOL8";
            break;

        default:
            str = "value_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_t to std::string
    std::string to_string( const value_t val )
    {
        std::string str;
        
        str += "value_t::ui32 : ";
        str += std::to_string(val.ui32);
        str += "\n";
        
        str += "value_t::ui64 : ";
        str += std::to_string(val.ui64);
        str += "\n";
        
        str += "value_t::fp32 : ";
        str += std::to_string(val.fp32);
        str += "\n";
        
        str += "value_t::fp64 : ";
        str += std::to_string(val.fp64);
        str += "\n";
        
        str += "value_t::b8 : ";
        str += std::to_string(val.b8);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_t to std::string
    std::string to_string( const typed_value_t val )
    {
        std::string str;
        
        str += "typed_value_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "typed_value_t::value : ";
        str += to_string(val.value);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type_t to std::string
    std::string to_string( const MetricGroup::sampling_type_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(MetricGroup::sampling_type_t::EVENT_BASED) & bits )
            str += "EVENT_BASED | ";
        
        if( static_cast<uint32_t>(MetricGroup::sampling_type_t::TIME_BASED) & bits )
            str += "TIME_BASED | ";

        return ( str.size() > 3 ) 
            ? "MetricGroup::sampling_type_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "MetricGroup::sampling_type_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_version_t to std::string
    std::string to_string( const MetricGroup::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricGroup::properties_version_t::CURRENT:
            str = "MetricGroup::properties_version_t::CURRENT";
            break;

        default:
            str = "MetricGroup::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_t to std::string
    std::string to_string( const MetricGroup::properties_t val )
    {
        std::string str;
        
        str += "MetricGroup::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "MetricGroup::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "MetricGroup::properties_t::description : ";
        str += val.description;
        str += "\n";
        
        str += "MetricGroup::properties_t::samplingType : ";
        str += to_string(val.samplingType);
        str += "\n";
        
        str += "MetricGroup::properties_t::domain : ";
        str += std::to_string(val.domain);
        str += "\n";
        
        str += "MetricGroup::properties_t::maxCommandQueueGroupOrdinal : ";
        str += std::to_string(val.maxCommandQueueGroupOrdinal);
        str += "\n";
        
        str += "MetricGroup::properties_t::metricCount : ";
        str += std::to_string(val.metricCount);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( const Metric::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Metric::type_t::DURATION:
            str = "Metric::type_t::DURATION";
            break;

        case Metric::type_t::EVENT:
            str = "Metric::type_t::EVENT";
            break;

        case Metric::type_t::EVENT_WITH_RANGE:
            str = "Metric::type_t::EVENT_WITH_RANGE";
            break;

        case Metric::type_t::THROUGHPUT:
            str = "Metric::type_t::THROUGHPUT";
            break;

        case Metric::type_t::TIMESTAMP:
            str = "Metric::type_t::TIMESTAMP";
            break;

        case Metric::type_t::FLAG:
            str = "Metric::type_t::FLAG";
            break;

        case Metric::type_t::RATIO:
            str = "Metric::type_t::RATIO";
            break;

        case Metric::type_t::RAW:
            str = "Metric::type_t::RAW";
            break;

        default:
            str = "Metric::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_version_t to std::string
    std::string to_string( const Metric::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Metric::properties_version_t::CURRENT:
            str = "Metric::properties_version_t::CURRENT";
            break;

        default:
            str = "Metric::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_t to std::string
    std::string to_string( const Metric::properties_t val )
    {
        std::string str;
        
        str += "Metric::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Metric::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Metric::properties_t::description : ";
        str += val.description;
        str += "\n";
        
        str += "Metric::properties_t::component : ";
        str += val.component;
        str += "\n";
        
        str += "Metric::properties_t::tierNumber : ";
        str += std::to_string(val.tierNumber);
        str += "\n";
        
        str += "Metric::properties_t::metricType : ";
        str += to_string(val.metricType);
        str += "\n";
        
        str += "Metric::properties_t::resultType : ";
        str += to_string(val.resultType);
        str += "\n";
        
        str += "Metric::properties_t::resultUnits : ";
        str += val.resultUnits;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_version_t to std::string
    std::string to_string( const MetricTracer::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricTracer::desc_version_t::CURRENT:
            str = "MetricTracer::desc_version_t::CURRENT";
            break;

        default:
            str = "MetricTracer::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_t to std::string
    std::string to_string( const MetricTracer::desc_t val )
    {
        std::string str;
        
        str += "MetricTracer::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "MetricTracer::desc_t::notifyEveryNReports : ";
        str += std::to_string(val.notifyEveryNReports);
        str += "\n";
        
        str += "MetricTracer::desc_t::samplingPeriod : ";
        str += std::to_string(val.samplingPeriod);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_version_t to std::string
    std::string to_string( const MetricQueryPool::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricQueryPool::desc_version_t::CURRENT:
            str = "MetricQueryPool::desc_version_t::CURRENT";
            break;

        default:
            str = "MetricQueryPool::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::flag_t to std::string
    std::string to_string( const MetricQueryPool::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricQueryPool::flag_t::PERFORMANCE:
            str = "MetricQueryPool::flag_t::PERFORMANCE";
            break;

        case MetricQueryPool::flag_t::SKIP_EXECUTION:
            str = "MetricQueryPool::flag_t::SKIP_EXECUTION";
            break;

        default:
            str = "MetricQueryPool::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_t to std::string
    std::string to_string( const MetricQueryPool::desc_t val )
    {
        std::string str;
        
        str += "MetricQueryPool::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "MetricQueryPool::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "MetricQueryPool::desc_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::debug_info_format_t to std::string
    std::string to_string( const Module::debug_info_format_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::debug_info_format_t::ELF_DWARF:
            str = "Module::debug_info_format_t::ELF_DWARF";
            break;

        default:
            str = "Module::debug_info_format_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_info_version_t to std::string
    std::string to_string( const Kernel::profile_info_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::profile_info_version_t::CURRENT:
            str = "Kernel::profile_info_version_t::CURRENT";
            break;

        default:
            str = "Kernel::profile_info_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_flag_t to std::string
    std::string to_string( const Kernel::profile_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( static_cast<uint32_t>(Kernel::profile_flag_t::REGISTER_REALLOCATION) & bits )
            str += "REGISTER_REALLOCATION | ";
        
        if( static_cast<uint32_t>(Kernel::profile_flag_t::FREE_REGISTER_INFO) & bits )
            str += "FREE_REGISTER_INFO | ";

        return ( str.size() > 3 ) 
            ? "Kernel::profile_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Kernel::profile_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_token_type_t to std::string
    std::string to_string( const Kernel::profile_token_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::profile_token_type_t::FREE_REGISTER:
            str = "Kernel::profile_token_type_t::FREE_REGISTER";
            break;

        default:
            str = "Kernel::profile_token_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_info_t to std::string
    std::string to_string( const Kernel::profile_info_t val )
    {
        std::string str;
        
        str += "Kernel::profile_info_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Kernel::profile_info_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Kernel::profile_info_t::numTokens : ";
        str += std::to_string(val.numTokens);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_free_register_token_t to std::string
    std::string to_string( const Kernel::profile_free_register_token_t val )
    {
        std::string str;
        
        str += "Kernel::profile_free_register_token_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Kernel::profile_free_register_token_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Kernel::profile_free_register_token_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_register_sequence_t to std::string
    std::string to_string( const Kernel::profile_register_sequence_t val )
    {
        std::string str;
        
        str += "Kernel::profile_register_sequence_t::start : ";
        str += std::to_string(val.start);
        str += "\n";
        
        str += "Kernel::profile_register_sequence_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::version_t::CURRENT:
            str = "Sysman::version_t::CURRENT";
            break;

        default:
            str = "Sysman::version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::engine_type_t to std::string
    std::string to_string( const Sysman::engine_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::engine_type_t::OTHER:
            str = "Sysman::engine_type_t::OTHER";
            break;

        case Sysman::engine_type_t::COMPUTE:
            str = "Sysman::engine_type_t::COMPUTE";
            break;

        case Sysman::engine_type_t::_3D:
            str = "Sysman::engine_type_t::_3D";
            break;

        case Sysman::engine_type_t::MEDIA:
            str = "Sysman::engine_type_t::MEDIA";
            break;

        case Sysman::engine_type_t::DMA:
            str = "Sysman::engine_type_t::DMA";
            break;

        default:
            str = "Sysman::engine_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::repair_status_t to std::string
    std::string to_string( const Sysman::repair_status_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::repair_status_t::UNSUPPORTED:
            str = "Sysman::repair_status_t::UNSUPPORTED";
            break;

        case Sysman::repair_status_t::NOT_PERFORMED:
            str = "Sysman::repair_status_t::NOT_PERFORMED";
            break;

        case Sysman::repair_status_t::PERFORMED:
            str = "Sysman::repair_status_t::PERFORMED";
            break;

        default:
            str = "Sysman::repair_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::reset_reasons_t to std::string
    std::string to_string( const Sysman::reset_reasons_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::reset_reasons_t::WEDGED) & bits )
            str += "WEDGED | ";
        
        if( static_cast<uint32_t>(Sysman::reset_reasons_t::REPAIR) & bits )
            str += "REPAIR | ";

        return ( str.size() > 3 ) 
            ? "Sysman::reset_reasons_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::reset_reasons_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_mode_t to std::string
    std::string to_string( const Sysman::sched_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::sched_mode_t::TIMEOUT:
            str = "Sysman::sched_mode_t::TIMEOUT";
            break;

        case Sysman::sched_mode_t::TIMESLICE:
            str = "Sysman::sched_mode_t::TIMESLICE";
            break;

        case Sysman::sched_mode_t::EXCLUSIVE:
            str = "Sysman::sched_mode_t::EXCLUSIVE";
            break;

        case Sysman::sched_mode_t::COMPUTE_UNIT_DEBUG:
            str = "Sysman::sched_mode_t::COMPUTE_UNIT_DEBUG";
            break;

        default:
            str = "Sysman::sched_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_link_status_t to std::string
    std::string to_string( const Sysman::pci_link_status_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::pci_link_status_t::GREEN:
            str = "Sysman::pci_link_status_t::GREEN";
            break;

        case Sysman::pci_link_status_t::YELLOW:
            str = "Sysman::pci_link_status_t::YELLOW";
            break;

        case Sysman::pci_link_status_t::RED:
            str = "Sysman::pci_link_status_t::RED";
            break;

        default:
            str = "Sysman::pci_link_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_link_qual_issues_t to std::string
    std::string to_string( const Sysman::pci_link_qual_issues_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::pci_link_qual_issues_t::REPLAYS) & bits )
            str += "REPLAYS | ";
        
        if( static_cast<uint32_t>(Sysman::pci_link_qual_issues_t::SPEED) & bits )
            str += "SPEED | ";

        return ( str.size() > 3 ) 
            ? "Sysman::pci_link_qual_issues_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::pci_link_qual_issues_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_link_stab_issues_t to std::string
    std::string to_string( const Sysman::pci_link_stab_issues_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::pci_link_stab_issues_t::RETRAINING) & bits )
            str += "RETRAINING | ";

        return ( str.size() > 3 ) 
            ? "Sysman::pci_link_stab_issues_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::pci_link_stab_issues_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_type_t to std::string
    std::string to_string( const Sysman::pci_bar_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::pci_bar_type_t::MMIO:
            str = "Sysman::pci_bar_type_t::MMIO";
            break;

        case Sysman::pci_bar_type_t::ROM:
            str = "Sysman::pci_bar_type_t::ROM";
            break;

        case Sysman::pci_bar_type_t::MEM:
            str = "Sysman::pci_bar_type_t::MEM";
            break;

        default:
            str = "Sysman::pci_bar_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_domain_t to std::string
    std::string to_string( const Sysman::freq_domain_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::freq_domain_t::GPU:
            str = "Sysman::freq_domain_t::GPU";
            break;

        case Sysman::freq_domain_t::MEMORY:
            str = "Sysman::freq_domain_t::MEMORY";
            break;

        default:
            str = "Sysman::freq_domain_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::DEVICE_RESET) & bits )
            str += "DEVICE_RESET | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::DEVICE_SLEEP_STATE_ENTER) & bits )
            str += "DEVICE_SLEEP_STATE_ENTER | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::DEVICE_SLEEP_STATE_EXIT) & bits )
            str += "DEVICE_SLEEP_STATE_EXIT | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::FREQ_THROTTLED) & bits )
            str += "FREQ_THROTTLED | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::ENERGY_THRESHOLD_CROSSED) & bits )
            str += "ENERGY_THRESHOLD_CROSSED | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::TEMP_CRITICAL) & bits )
            str += "TEMP_CRITICAL | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::TEMP_THRESHOLD1) & bits )
            str += "TEMP_THRESHOLD1 | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::TEMP_THRESHOLD2) & bits )
            str += "TEMP_THRESHOLD2 | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::MEM_HEALTH) & bits )
            str += "MEM_HEALTH | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::FABRIC_PORT_HEALTH) & bits )
            str += "FABRIC_PORT_HEALTH | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::PCI_LINK_HEALTH) & bits )
            str += "PCI_LINK_HEALTH | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::RAS_CORRECTABLE_ERRORS) & bits )
            str += "RAS_CORRECTABLE_ERRORS | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::RAS_UNCORRECTABLE_ERRORS) & bits )
            str += "RAS_UNCORRECTABLE_ERRORS | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::DEVICE_RESET_REQUIRED) & bits )
            str += "DEVICE_RESET_REQUIRED | ";
        
        if( static_cast<uint32_t>(Sysman::event_type_t::ALL) & bits )
            str += "ALL | ";

        return ( str.size() > 3 ) 
            ? "Sysman::event_type_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::event_type_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::state_t to std::string
    std::string to_string( const Sysman::state_t val )
    {
        std::string str;
        
        str += "Sysman::state_t::reset : ";
        str += std::to_string(val.reset);
        str += "\n";
        
        str += "Sysman::state_t::repaired : ";
        str += to_string(val.repaired);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::properties_t to std::string
    std::string to_string( const Sysman::properties_t val )
    {
        std::string str;
        
        str += "Sysman::properties_t::core : ";
        str += to_string(val.core);
        str += "\n";
        
        str += "Sysman::properties_t::numSubdevices : ";
        str += std::to_string(val.numSubdevices);
        str += "\n";
        
        str += "Sysman::properties_t::serialNumber : ";
        {
            std::string tmp;
            for( auto& entry : val.serialNumber )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::boardNumber : ";
        {
            std::string tmp;
            for( auto& entry : val.boardNumber )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::brandName : ";
        {
            std::string tmp;
            for( auto& entry : val.brandName )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::modelName : ";
        {
            std::string tmp;
            for( auto& entry : val.modelName )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::vendorName : ";
        {
            std::string tmp;
            for( auto& entry : val.vendorName )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::properties_t::driverVersion : ";
        {
            std::string tmp;
            for( auto& entry : val.driverVersion )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeout_properties_t to std::string
    std::string to_string( const Sysman::sched_timeout_properties_t val )
    {
        std::string str;
        
        str += "Sysman::sched_timeout_properties_t::watchdogTimeout : ";
        str += std::to_string(val.watchdogTimeout);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeslice_properties_t to std::string
    std::string to_string( const Sysman::sched_timeslice_properties_t val )
    {
        std::string str;
        
        str += "Sysman::sched_timeslice_properties_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";
        
        str += "Sysman::sched_timeslice_properties_t::yieldTimeout : ";
        str += std::to_string(val.yieldTimeout);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::process_state_t to std::string
    std::string to_string( const Sysman::process_state_t val )
    {
        std::string str;
        
        str += "Sysman::process_state_t::processId : ";
        str += std::to_string(val.processId);
        str += "\n";
        
        str += "Sysman::process_state_t::memSize : ";
        str += std::to_string(val.memSize);
        str += "\n";
        
        str += "Sysman::process_state_t::engines : ";
        str += std::to_string(val.engines);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_address_t to std::string
    std::string to_string( const Sysman::pci_address_t val )
    {
        std::string str;
        
        str += "Sysman::pci_address_t::domain : ";
        str += std::to_string(val.domain);
        str += "\n";
        
        str += "Sysman::pci_address_t::bus : ";
        str += std::to_string(val.bus);
        str += "\n";
        
        str += "Sysman::pci_address_t::device : ";
        str += std::to_string(val.device);
        str += "\n";
        
        str += "Sysman::pci_address_t::function : ";
        str += std::to_string(val.function);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_speed_t to std::string
    std::string to_string( const Sysman::pci_speed_t val )
    {
        std::string str;
        
        str += "Sysman::pci_speed_t::gen : ";
        str += std::to_string(val.gen);
        str += "\n";
        
        str += "Sysman::pci_speed_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "Sysman::pci_speed_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_properties_t to std::string
    std::string to_string( const Sysman::pci_properties_t val )
    {
        std::string str;
        
        str += "Sysman::pci_properties_t::address : ";
        str += to_string(val.address);
        str += "\n";
        
        str += "Sysman::pci_properties_t::maxSpeed : ";
        str += to_string(val.maxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_state_t to std::string
    std::string to_string( const Sysman::pci_state_t val )
    {
        std::string str;
        
        str += "Sysman::pci_state_t::status : ";
        str += to_string(val.status);
        str += "\n";
        
        str += "Sysman::pci_state_t::qualityIssues : ";
        str += to_string(val.qualityIssues);
        str += "\n";
        
        str += "Sysman::pci_state_t::stabilityIssues : ";
        str += to_string(val.stabilityIssues);
        str += "\n";
        
        str += "Sysman::pci_state_t::speed : ";
        str += to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_properties_t to std::string
    std::string to_string( const Sysman::pci_bar_properties_t val )
    {
        std::string str;
        
        str += "Sysman::pci_bar_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::pci_bar_properties_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::pci_bar_properties_t::base : ";
        str += std::to_string(val.base);
        str += "\n";
        
        str += "Sysman::pci_bar_properties_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_stats_t to std::string
    std::string to_string( const Sysman::pci_stats_t val )
    {
        std::string str;
        
        str += "Sysman::pci_stats_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "Sysman::pci_stats_t::replayCounter : ";
        str += std::to_string(val.replayCounter);
        str += "\n";
        
        str += "Sysman::pci_stats_t::packetCounter : ";
        str += std::to_string(val.packetCounter);
        str += "\n";
        
        str += "Sysman::pci_stats_t::rxCounter : ";
        str += std::to_string(val.rxCounter);
        str += "\n";
        
        str += "Sysman::pci_stats_t::txCounter : ";
        str += std::to_string(val.txCounter);
        str += "\n";
        
        str += "Sysman::pci_stats_t::speed : ";
        str += to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanScheduler::sched_properties_t to std::string
    std::string to_string( const SysmanScheduler::sched_properties_t val )
    {
        std::string str;
        
        str += "SysmanScheduler::sched_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanScheduler::sched_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanScheduler::sched_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanScheduler::sched_properties_t::engines : ";
        str += std::to_string(val.engines);
        str += "\n";
        
        str += "SysmanScheduler::sched_properties_t::supportedModes : ";
        str += std::to_string(val.supportedModes);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPerformanceFactor::perf_properties_t to std::string
    std::string to_string( const SysmanPerformanceFactor::perf_properties_t val )
    {
        std::string str;
        
        str += "SysmanPerformanceFactor::perf_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanPerformanceFactor::perf_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanPerformanceFactor::perf_properties_t::engines : ";
        str += std::to_string(val.engines);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_properties_t to std::string
    std::string to_string( const SysmanPower::power_properties_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::isEnergyThresholdSupported : ";
        str += std::to_string(val.isEnergyThresholdSupported);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::defaultLimit : ";
        str += std::to_string(val.defaultLimit);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::minLimit : ";
        str += std::to_string(val.minLimit);
        str += "\n";
        
        str += "SysmanPower::power_properties_t::maxLimit : ";
        str += std::to_string(val.maxLimit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_energy_counter_t to std::string
    std::string to_string( const SysmanPower::power_energy_counter_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_energy_counter_t::energy : ";
        str += std::to_string(val.energy);
        str += "\n";
        
        str += "SysmanPower::power_energy_counter_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_sustained_limit_t to std::string
    std::string to_string( const SysmanPower::power_sustained_limit_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_sustained_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanPower::power_sustained_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";
        
        str += "SysmanPower::power_sustained_limit_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_burst_limit_t to std::string
    std::string to_string( const SysmanPower::power_burst_limit_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_burst_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanPower::power_burst_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_peak_limit_t to std::string
    std::string to_string( const SysmanPower::power_peak_limit_t val )
    {
        std::string str;
        
        str += "SysmanPower::power_peak_limit_t::powerAC : ";
        str += std::to_string(val.powerAC);
        str += "\n";
        
        str += "SysmanPower::power_peak_limit_t::powerDC : ";
        str += std::to_string(val.powerDC);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::energy_threshold_t to std::string
    std::string to_string( const SysmanPower::energy_threshold_t val )
    {
        std::string str;
        
        str += "SysmanPower::energy_threshold_t::enable : ";
        str += std::to_string(val.enable);
        str += "\n";
        
        str += "SysmanPower::energy_threshold_t::threshold : ";
        str += std::to_string(val.threshold);
        str += "\n";
        
        str += "SysmanPower::energy_threshold_t::processId : ";
        str += std::to_string(val.processId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_reasons_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_reasons_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::AVE_PWR_CAP) & bits )
            str += "AVE_PWR_CAP | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::BURST_PWR_CAP) & bits )
            str += "BURST_PWR_CAP | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::CURRENT_LIMIT) & bits )
            str += "CURRENT_LIMIT | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::THERMAL_LIMIT) & bits )
            str += "THERMAL_LIMIT | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::PSU_ALERT) & bits )
            str += "PSU_ALERT | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::SW_RANGE) & bits )
            str += "SW_RANGE | ";
        
        if( static_cast<uint32_t>(SysmanFrequency::freq_throttle_reasons_t::HW_RANGE) & bits )
            str += "HW_RANGE | ";

        return ( str.size() > 3 ) 
            ? "SysmanFrequency::freq_throttle_reasons_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "SysmanFrequency::freq_throttle_reasons_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_mode_t to std::string
    std::string to_string( const SysmanFrequency::oc_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFrequency::oc_mode_t::OFF:
            str = "SysmanFrequency::oc_mode_t::OFF";
            break;

        case SysmanFrequency::oc_mode_t::OVERRIDE:
            str = "SysmanFrequency::oc_mode_t::OVERRIDE";
            break;

        case SysmanFrequency::oc_mode_t::INTERPOLATIVE:
            str = "SysmanFrequency::oc_mode_t::INTERPOLATIVE";
            break;

        default:
            str = "SysmanFrequency::oc_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_properties_t to std::string
    std::string to_string( const SysmanFrequency::freq_properties_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::isThrottleEventSupported : ";
        str += std::to_string(val.isThrottleEventSupported);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::max : ";
        str += std::to_string(val.max);
        str += "\n";
        
        str += "SysmanFrequency::freq_properties_t::step : ";
        str += std::to_string(val.step);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_range_t to std::string
    std::string to_string( const SysmanFrequency::freq_range_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_range_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "SysmanFrequency::freq_range_t::max : ";
        str += std::to_string(val.max);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_state_t to std::string
    std::string to_string( const SysmanFrequency::freq_state_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_state_t::request : ";
        str += std::to_string(val.request);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::tdp : ";
        str += std::to_string(val.tdp);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::efficient : ";
        str += std::to_string(val.efficient);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::actual : ";
        str += std::to_string(val.actual);
        str += "\n";
        
        str += "SysmanFrequency::freq_state_t::throttleReasons : ";
        str += std::to_string(val.throttleReasons);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_time_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_time_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::freq_throttle_time_t::throttleTime : ";
        str += std::to_string(val.throttleTime);
        str += "\n";
        
        str += "SysmanFrequency::freq_throttle_time_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_capabilities_t to std::string
    std::string to_string( const SysmanFrequency::oc_capabilities_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::oc_capabilities_t::isOcSupported : ";
        str += std::to_string(val.isOcSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::maxFactoryDefaultFrequency : ";
        str += std::to_string(val.maxFactoryDefaultFrequency);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::maxFactoryDefaultVoltage : ";
        str += std::to_string(val.maxFactoryDefaultVoltage);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::maxOcFrequency : ";
        str += std::to_string(val.maxOcFrequency);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::minOcVoltageOffset : ";
        str += std::to_string(val.minOcVoltageOffset);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::maxOcVoltageOffset : ";
        str += std::to_string(val.maxOcVoltageOffset);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::maxOcVoltage : ";
        str += std::to_string(val.maxOcVoltage);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::isTjMaxSupported : ";
        str += std::to_string(val.isTjMaxSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::isIccMaxSupported : ";
        str += std::to_string(val.isIccMaxSupported);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::isHighVoltModeCapable : ";
        str += std::to_string(val.isHighVoltModeCapable);
        str += "\n";
        
        str += "SysmanFrequency::oc_capabilities_t::isHighVoltModeEnabled : ";
        str += std::to_string(val.isHighVoltModeEnabled);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_config_t to std::string
    std::string to_string( const SysmanFrequency::oc_config_t val )
    {
        std::string str;
        
        str += "SysmanFrequency::oc_config_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "SysmanFrequency::oc_config_t::frequency : ";
        str += std::to_string(val.frequency);
        str += "\n";
        
        str += "SysmanFrequency::oc_config_t::voltageTarget : ";
        str += std::to_string(val.voltageTarget);
        str += "\n";
        
        str += "SysmanFrequency::oc_config_t::voltageOffset : ";
        str += std::to_string(val.voltageOffset);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_group_t to std::string
    std::string to_string( const SysmanEngine::engine_group_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanEngine::engine_group_t::ALL:
            str = "SysmanEngine::engine_group_t::ALL";
            break;

        case SysmanEngine::engine_group_t::COMPUTE_ALL:
            str = "SysmanEngine::engine_group_t::COMPUTE_ALL";
            break;

        case SysmanEngine::engine_group_t::MEDIA_ALL:
            str = "SysmanEngine::engine_group_t::MEDIA_ALL";
            break;

        case SysmanEngine::engine_group_t::COPY_ALL:
            str = "SysmanEngine::engine_group_t::COPY_ALL";
            break;

        default:
            str = "SysmanEngine::engine_group_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_properties_t to std::string
    std::string to_string( const SysmanEngine::engine_properties_t val )
    {
        std::string str;
        
        str += "SysmanEngine::engine_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanEngine::engine_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanEngine::engine_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_stats_t to std::string
    std::string to_string( const SysmanEngine::engine_stats_t val )
    {
        std::string str;
        
        str += "SysmanEngine::engine_stats_t::activeTime : ";
        str += std::to_string(val.activeTime);
        str += "\n";
        
        str += "SysmanEngine::engine_stats_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_type_t to std::string
    std::string to_string( const SysmanStandby::standby_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanStandby::standby_type_t::GLOBAL:
            str = "SysmanStandby::standby_type_t::GLOBAL";
            break;

        default:
            str = "SysmanStandby::standby_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_promo_mode_t to std::string
    std::string to_string( const SysmanStandby::standby_promo_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanStandby::standby_promo_mode_t::DEFAULT:
            str = "SysmanStandby::standby_promo_mode_t::DEFAULT";
            break;

        case SysmanStandby::standby_promo_mode_t::NEVER:
            str = "SysmanStandby::standby_promo_mode_t::NEVER";
            break;

        default:
            str = "SysmanStandby::standby_promo_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_properties_t to std::string
    std::string to_string( const SysmanStandby::standby_properties_t val )
    {
        std::string str;
        
        str += "SysmanStandby::standby_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanStandby::standby_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanStandby::standby_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFirmware::firmware_properties_t to std::string
    std::string to_string( const SysmanFirmware::firmware_properties_t val )
    {
        std::string str;
        
        str += "SysmanFirmware::firmware_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::name : ";
        {
            std::string tmp;
            for( auto& entry : val.name )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "SysmanFirmware::firmware_properties_t::version : ";
        {
            std::string tmp;
            for( auto& entry : val.version )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_type_t to std::string
    std::string to_string( const SysmanMemory::mem_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanMemory::mem_type_t::HBM:
            str = "SysmanMemory::mem_type_t::HBM";
            break;

        case SysmanMemory::mem_type_t::DDR:
            str = "SysmanMemory::mem_type_t::DDR";
            break;

        case SysmanMemory::mem_type_t::SRAM:
            str = "SysmanMemory::mem_type_t::SRAM";
            break;

        case SysmanMemory::mem_type_t::L1:
            str = "SysmanMemory::mem_type_t::L1";
            break;

        case SysmanMemory::mem_type_t::L3:
            str = "SysmanMemory::mem_type_t::L3";
            break;

        case SysmanMemory::mem_type_t::GRF:
            str = "SysmanMemory::mem_type_t::GRF";
            break;

        case SysmanMemory::mem_type_t::SLM:
            str = "SysmanMemory::mem_type_t::SLM";
            break;

        default:
            str = "SysmanMemory::mem_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_health_t to std::string
    std::string to_string( const SysmanMemory::mem_health_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanMemory::mem_health_t::OK:
            str = "SysmanMemory::mem_health_t::OK";
            break;

        case SysmanMemory::mem_health_t::DEGRADED:
            str = "SysmanMemory::mem_health_t::DEGRADED";
            break;

        case SysmanMemory::mem_health_t::CRITICAL:
            str = "SysmanMemory::mem_health_t::CRITICAL";
            break;

        case SysmanMemory::mem_health_t::REPLACE:
            str = "SysmanMemory::mem_health_t::REPLACE";
            break;

        default:
            str = "SysmanMemory::mem_health_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_properties_t to std::string
    std::string to_string( const SysmanMemory::mem_properties_t val )
    {
        std::string str;
        
        str += "SysmanMemory::mem_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanMemory::mem_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanMemory::mem_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanMemory::mem_properties_t::physicalSize : ";
        str += std::to_string(val.physicalSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_state_t to std::string
    std::string to_string( const SysmanMemory::mem_state_t val )
    {
        std::string str;
        
        str += "SysmanMemory::mem_state_t::health : ";
        str += to_string(val.health);
        str += "\n";
        
        str += "SysmanMemory::mem_state_t::free : ";
        str += std::to_string(val.free);
        str += "\n";
        
        str += "SysmanMemory::mem_state_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_bandwidth_t to std::string
    std::string to_string( const SysmanMemory::mem_bandwidth_t val )
    {
        std::string str;
        
        str += "SysmanMemory::mem_bandwidth_t::readCounter : ";
        str += std::to_string(val.readCounter);
        str += "\n";
        
        str += "SysmanMemory::mem_bandwidth_t::writeCounter : ";
        str += std::to_string(val.writeCounter);
        str += "\n";
        
        str += "SysmanMemory::mem_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";
        
        str += "SysmanMemory::mem_bandwidth_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_status_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_status_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFabricPort::fabric_port_status_t::GREEN:
            str = "SysmanFabricPort::fabric_port_status_t::GREEN";
            break;

        case SysmanFabricPort::fabric_port_status_t::YELLOW:
            str = "SysmanFabricPort::fabric_port_status_t::YELLOW";
            break;

        case SysmanFabricPort::fabric_port_status_t::RED:
            str = "SysmanFabricPort::fabric_port_status_t::RED";
            break;

        case SysmanFabricPort::fabric_port_status_t::BLACK:
            str = "SysmanFabricPort::fabric_port_status_t::BLACK";
            break;

        default:
            str = "SysmanFabricPort::fabric_port_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_qual_issues_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_qual_issues_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_qual_issues_t::FABRIC_PORT_QUAL_LINK_ERRORS) & bits )
            str += "FABRIC_PORT_QUAL_LINK_ERRORS | ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_qual_issues_t::SPEED) & bits )
            str += "SPEED | ";

        return ( str.size() > 3 ) 
            ? "SysmanFabricPort::fabric_port_qual_issues_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "SysmanFabricPort::fabric_port_qual_issues_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_stab_issues_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_stab_issues_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_stab_issues_t::FAILED) & bits )
            str += "FAILED | ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_stab_issues_t::TRAINING_TIMEOUT) & bits )
            str += "TRAINING_TIMEOUT | ";
        
        if( static_cast<uint32_t>(SysmanFabricPort::fabric_port_stab_issues_t::FLAPPING) & bits )
            str += "FLAPPING | ";

        return ( str.size() > 3 ) 
            ? "SysmanFabricPort::fabric_port_stab_issues_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "SysmanFabricPort::fabric_port_stab_issues_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_id_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_id_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_id_t::fabricId : ";
        str += std::to_string(val.fabricId);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_id_t::attachId : ";
        str += std::to_string(val.attachId);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_id_t::portNumber : ";
        str += std::to_string(val.portNumber);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_speed_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_speed_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_speed_t::bitRate : ";
        str += std::to_string(val.bitRate);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_speed_t::width : ";
        str += std::to_string(val.width);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_properties_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_properties_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_properties_t::model : ";
        {
            std::string tmp;
            for( auto& entry : val.model )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::portId : ";
        str += to_string(val.portId);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::maxRxSpeed : ";
        str += to_string(val.maxRxSpeed);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_properties_t::maxTxSpeed : ";
        str += to_string(val.maxTxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_link_type_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_link_type_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_link_type_t::desc : ";
        {
            std::string tmp;
            for( auto& entry : val.desc )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_config_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_config_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_config_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_config_t::beaconing : ";
        str += std::to_string(val.beaconing);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_state_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_state_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_state_t::status : ";
        str += to_string(val.status);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::qualityIssues : ";
        str += to_string(val.qualityIssues);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::stabilityIssues : ";
        str += to_string(val.stabilityIssues);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::remotePortId : ";
        str += to_string(val.remotePortId);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::rxSpeed : ";
        str += to_string(val.rxSpeed);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_state_t::txSpeed : ";
        str += to_string(val.txSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_throughput_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_throughput_t val )
    {
        std::string str;
        
        str += "SysmanFabricPort::fabric_port_throughput_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_throughput_t::rxCounter : ";
        str += std::to_string(val.rxCounter);
        str += "\n";
        
        str += "SysmanFabricPort::fabric_port_throughput_t::txCounter : ";
        str += std::to_string(val.txCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_sensors_t to std::string
    std::string to_string( const SysmanTemperature::temp_sensors_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanTemperature::temp_sensors_t::GLOBAL:
            str = "SysmanTemperature::temp_sensors_t::GLOBAL";
            break;

        case SysmanTemperature::temp_sensors_t::GPU:
            str = "SysmanTemperature::temp_sensors_t::GPU";
            break;

        case SysmanTemperature::temp_sensors_t::MEMORY:
            str = "SysmanTemperature::temp_sensors_t::MEMORY";
            break;

        default:
            str = "SysmanTemperature::temp_sensors_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_properties_t to std::string
    std::string to_string( const SysmanTemperature::temp_properties_t val )
    {
        std::string str;
        
        str += "SysmanTemperature::temp_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanTemperature::temp_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanTemperature::temp_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanTemperature::temp_properties_t::isCriticalTempSupported : ";
        str += std::to_string(val.isCriticalTempSupported);
        str += "\n";
        
        str += "SysmanTemperature::temp_properties_t::isThreshold1Supported : ";
        str += std::to_string(val.isThreshold1Supported);
        str += "\n";
        
        str += "SysmanTemperature::temp_properties_t::isThreshold2Supported : ";
        str += std::to_string(val.isThreshold2Supported);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_threshold_t to std::string
    std::string to_string( const SysmanTemperature::temp_threshold_t val )
    {
        std::string str;
        
        str += "SysmanTemperature::temp_threshold_t::enableLowToHigh : ";
        str += std::to_string(val.enableLowToHigh);
        str += "\n";
        
        str += "SysmanTemperature::temp_threshold_t::enableHighToLow : ";
        str += std::to_string(val.enableHighToLow);
        str += "\n";
        
        str += "SysmanTemperature::temp_threshold_t::threshold : ";
        str += std::to_string(val.threshold);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_config_t to std::string
    std::string to_string( const SysmanTemperature::temp_config_t val )
    {
        std::string str;
        
        str += "SysmanTemperature::temp_config_t::enableCritical : ";
        str += std::to_string(val.enableCritical);
        str += "\n";
        
        str += "SysmanTemperature::temp_config_t::threshold1 : ";
        str += to_string(val.threshold1);
        str += "\n";
        
        str += "SysmanTemperature::temp_config_t::threshold2 : ";
        str += to_string(val.threshold2);
        str += "\n";
        
        str += "SysmanTemperature::temp_config_t::processId : ";
        str += std::to_string(val.processId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_voltage_status_t to std::string
    std::string to_string( const SysmanPsu::psu_voltage_status_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanPsu::psu_voltage_status_t::NORMAL:
            str = "SysmanPsu::psu_voltage_status_t::NORMAL";
            break;

        case SysmanPsu::psu_voltage_status_t::OVER:
            str = "SysmanPsu::psu_voltage_status_t::OVER";
            break;

        case SysmanPsu::psu_voltage_status_t::UNDER:
            str = "SysmanPsu::psu_voltage_status_t::UNDER";
            break;

        default:
            str = "SysmanPsu::psu_voltage_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_properties_t to std::string
    std::string to_string( const SysmanPsu::psu_properties_t val )
    {
        std::string str;
        
        str += "SysmanPsu::psu_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanPsu::psu_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanPsu::psu_properties_t::haveFan : ";
        str += std::to_string(val.haveFan);
        str += "\n";
        
        str += "SysmanPsu::psu_properties_t::ampLimit : ";
        str += std::to_string(val.ampLimit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_state_t to std::string
    std::string to_string( const SysmanPsu::psu_state_t val )
    {
        std::string str;
        
        str += "SysmanPsu::psu_state_t::voltStatus : ";
        str += to_string(val.voltStatus);
        str += "\n";
        
        str += "SysmanPsu::psu_state_t::fanFailed : ";
        str += std::to_string(val.fanFailed);
        str += "\n";
        
        str += "SysmanPsu::psu_state_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "SysmanPsu::psu_state_t::current : ";
        str += std::to_string(val.current);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_mode_t to std::string
    std::string to_string( const SysmanFan::fan_speed_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFan::fan_speed_mode_t::DEFAULT:
            str = "SysmanFan::fan_speed_mode_t::DEFAULT";
            break;

        case SysmanFan::fan_speed_mode_t::FIXED:
            str = "SysmanFan::fan_speed_mode_t::FIXED";
            break;

        case SysmanFan::fan_speed_mode_t::TABLE:
            str = "SysmanFan::fan_speed_mode_t::TABLE";
            break;

        default:
            str = "SysmanFan::fan_speed_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_units_t to std::string
    std::string to_string( const SysmanFan::fan_speed_units_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanFan::fan_speed_units_t::RPM:
            str = "SysmanFan::fan_speed_units_t::RPM";
            break;

        case SysmanFan::fan_speed_units_t::PERCENT:
            str = "SysmanFan::fan_speed_units_t::PERCENT";
            break;

        default:
            str = "SysmanFan::fan_speed_units_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_temp_speed_t to std::string
    std::string to_string( const SysmanFan::fan_temp_speed_t val )
    {
        std::string str;
        
        str += "SysmanFan::fan_temp_speed_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "SysmanFan::fan_temp_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "SysmanFan::fan_temp_speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_properties_t to std::string
    std::string to_string( const SysmanFan::fan_properties_t val )
    {
        std::string str;
        
        str += "SysmanFan::fan_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::maxSpeed : ";
        str += std::to_string(val.maxSpeed);
        str += "\n";
        
        str += "SysmanFan::fan_properties_t::maxPoints : ";
        str += std::to_string(val.maxPoints);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_config_t to std::string
    std::string to_string( const SysmanFan::fan_config_t val )
    {
        std::string str;
        
        str += "SysmanFan::fan_config_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::speedUnits : ";
        str += to_string(val.speedUnits);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::numPoints : ";
        str += std::to_string(val.numPoints);
        str += "\n";
        
        str += "SysmanFan::fan_config_t::table : ";
        {
            std::string tmp;
            for( auto& entry : val.table )
            {
                tmp += to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_properties_t to std::string
    std::string to_string( const SysmanLed::led_properties_t val )
    {
        std::string str;
        
        str += "SysmanLed::led_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanLed::led_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanLed::led_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "SysmanLed::led_properties_t::haveRGB : ";
        str += std::to_string(val.haveRGB);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_state_t to std::string
    std::string to_string( const SysmanLed::led_state_t val )
    {
        std::string str;
        
        str += "SysmanLed::led_state_t::isOn : ";
        str += std::to_string(val.isOn);
        str += "\n";
        
        str += "SysmanLed::led_state_t::red : ";
        str += std::to_string(val.red);
        str += "\n";
        
        str += "SysmanLed::led_state_t::green : ";
        str += std::to_string(val.green);
        str += "\n";
        
        str += "SysmanLed::led_state_t::blue : ";
        str += std::to_string(val.blue);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_error_type_t to std::string
    std::string to_string( const SysmanRas::ras_error_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanRas::ras_error_type_t::CORRECTABLE:
            str = "SysmanRas::ras_error_type_t::CORRECTABLE";
            break;

        case SysmanRas::ras_error_type_t::UNCORRECTABLE:
            str = "SysmanRas::ras_error_type_t::UNCORRECTABLE";
            break;

        default:
            str = "SysmanRas::ras_error_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_properties_t to std::string
    std::string to_string( const SysmanRas::ras_properties_t val )
    {
        std::string str;
        
        str += "SysmanRas::ras_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanRas::ras_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanRas::ras_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_details_t to std::string
    std::string to_string( const SysmanRas::ras_details_t val )
    {
        std::string str;
        
        str += "SysmanRas::ras_details_t::numResets : ";
        str += std::to_string(val.numResets);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numProgrammingErrors : ";
        str += std::to_string(val.numProgrammingErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numDriverErrors : ";
        str += std::to_string(val.numDriverErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numComputeErrors : ";
        str += std::to_string(val.numComputeErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numNonComputeErrors : ";
        str += std::to_string(val.numNonComputeErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numCacheErrors : ";
        str += std::to_string(val.numCacheErrors);
        str += "\n";
        
        str += "SysmanRas::ras_details_t::numDisplayErrors : ";
        str += std::to_string(val.numDisplayErrors);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_config_t to std::string
    std::string to_string( const SysmanRas::ras_config_t val )
    {
        std::string str;
        
        str += "SysmanRas::ras_config_t::totalThreshold : ";
        str += std::to_string(val.totalThreshold);
        str += "\n";
        
        str += "SysmanRas::ras_config_t::detailedThresholds : ";
        str += to_string(val.detailedThresholds);
        str += "\n";
        
        str += "SysmanRas::ras_config_t::processId : ";
        str += std::to_string(val.processId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_type_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_type_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanDiagnostics::diag_type_t::SCAN:
            str = "SysmanDiagnostics::diag_type_t::SCAN";
            break;

        case SysmanDiagnostics::diag_type_t::ARRAY:
            str = "SysmanDiagnostics::diag_type_t::ARRAY";
            break;

        default:
            str = "SysmanDiagnostics::diag_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_result_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_result_t val )
    {
        std::string str;

        switch( val )
        {
        case SysmanDiagnostics::diag_result_t::NO_ERRORS:
            str = "SysmanDiagnostics::diag_result_t::NO_ERRORS";
            break;

        case SysmanDiagnostics::diag_result_t::ABORT:
            str = "SysmanDiagnostics::diag_result_t::ABORT";
            break;

        case SysmanDiagnostics::diag_result_t::FAIL_CANT_REPAIR:
            str = "SysmanDiagnostics::diag_result_t::FAIL_CANT_REPAIR";
            break;

        case SysmanDiagnostics::diag_result_t::REBOOT_FOR_REPAIR:
            str = "SysmanDiagnostics::diag_result_t::REBOOT_FOR_REPAIR";
            break;

        default:
            str = "SysmanDiagnostics::diag_result_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_test_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_test_t val )
    {
        std::string str;
        
        str += "SysmanDiagnostics::diag_test_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_test_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_properties_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_properties_t val )
    {
        std::string str;
        
        str += "SysmanDiagnostics::diag_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "SysmanDiagnostics::diag_properties_t::haveTests : ";
        str += std::to_string(val.haveTests);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEvent::event_config_t to std::string
    std::string to_string( const SysmanEvent::event_config_t val )
    {
        std::string str;
        
        str += "SysmanEvent::event_config_t::registered : ";
        str += std::to_string(val.registered);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_version_t to std::string
    std::string to_string( const Tracer::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Tracer::desc_version_t::CURRENT:
            str = "Tracer::desc_version_t::CURRENT";
            break;

        default:
            str = "Tracer::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_t to std::string
    std::string to_string( const Tracer::desc_t val )
    {
        std::string str;
        
        str += "Tracer::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Tracer::desc_t::pUserData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pUserData);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

} // namespace zet
