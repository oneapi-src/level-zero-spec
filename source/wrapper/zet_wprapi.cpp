/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_wprapi.cpp
 * @version v0.91-271
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
