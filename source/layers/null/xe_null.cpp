/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_null.cpp
 *
 */
#include "xe_null.h"

namespace driver
{
    //////////////////////////////////////////////////////////////////////////
    context_t context;

    //////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Driver.pfnGetDevices = [](
            xe_driver_handle_t,
            uint32_t* pCount,
            xe_device_handle_t* phDevices )
        {
            *pCount = 1;
            if( nullptr != phDevices) *reinterpret_cast<void**>( phDevices ) = context.get();
            return XE_RESULT_SUCCESS;
        };

        //pfnCreateEventPool

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Driver.pfnGetDriverVersion = [](
            xe_driver_handle_t,
            uint32_t* version )
        {
            *version = 0;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Driver.pfnGetApiVersion = [](
            xe_driver_handle_t,
            xe_api_version_t* version )
        {
            *version = context.version;
            return XE_RESULT_SUCCESS;
        };

        //pfnGetIPCProperties
        
        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Driver.pfnAllocSharedMem = [](
            xe_driver_handle_t,
            xe_device_handle_t,
            xe_device_mem_alloc_flag_t,
            uint32_t,
            xe_host_mem_alloc_flag_t,
            size_t size,
            size_t alignment,
            void** pptr)
        {
            *pptr = malloc(size);
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Driver.pfnAllocDeviceMem = [](
            xe_driver_handle_t,
            xe_device_handle_t,
            xe_device_mem_alloc_flag_t,
            uint32_t,
            size_t size,
            size_t alignment,
            void** pptr)
        {
            *pptr = malloc(size);
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Driver.pfnAllocHostMem = [](
            xe_driver_handle_t,
            xe_host_mem_alloc_flag_t,
            size_t size,
            size_t alignment,
            void** pptr)
        {
            *pptr = malloc(size);
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Driver.pfnFreeMem = [](
            xe_driver_handle_t,
            void* ptr)
        {
            free(ptr);
            return XE_RESULT_SUCCESS;
        };

        //pfnGetMemProperties
        //pfnGetMemAddressRange
        //pfnGetMemIpcHandle
        //pfnOpenMemIpcHandle
        //pfnCloseMemIpcHandle

        //////////////////////////////////////////////////////////////////////////
        //pfnGetSubDevices

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Device.pfnGetProperties = [](
            xe_device_handle_t,
            xe_device_properties_t* pDeviceProperties )
        {
            xe_device_properties_t deviceProperties = {};
            deviceProperties.version = XE_DEVICE_PROPERTIES_VERSION_CURRENT;
            deviceProperties.type = XE_DEVICE_TYPE_GPU;
            deviceProperties.maxCommandQueues = 1;
            deviceProperties.numAsyncComputeEngines = 1;
            deviceProperties.numAsyncCopyEngines = 1;
            strcpy( deviceProperties.name, "Null Device" );

            *pDeviceProperties = deviceProperties;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Device.pfnGetComputeProperties = [](
            xe_device_handle_t,
            xe_device_compute_properties_t* pComputeProperties )
        {
            xe_device_compute_properties_t computeProperties = {};
            computeProperties.version = XE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT;

            *pComputeProperties = computeProperties;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Device.pfnGetMemoryProperties = [](
            xe_device_handle_t,
            uint32_t* pCount,
            xe_device_memory_properties_t* pMemProperties )
        {
            xe_device_memory_properties_t memoryProperties = {};
            memoryProperties.version = XE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT;

            *pCount = 1;
            if( nullptr != pMemProperties ) *pMemProperties = memoryProperties;

            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Device.pfnGetMemoryAccessProperties = [](
            xe_device_handle_t,
            xe_device_memory_access_properties_t* pMemAccessProperties )
        {
            xe_device_memory_access_properties_t memoryAccessProperties = {};
            memoryAccessProperties.version = XE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT;

            *pMemAccessProperties = memoryAccessProperties;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Device.pfnGetCacheProperties = [](
            xe_device_handle_t,
            xe_device_cache_properties_t* pCacheProperties )
        {
            xe_device_cache_properties_t cacheProperties = {};
            cacheProperties.version = XE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT;

            *pCacheProperties = cacheProperties;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xeDdiTable.Device.pfnGetImageProperties = [](
            xe_device_handle_t,
            xe_device_image_properties_t* pImageProperties )
        {
            xe_device_image_properties_t imageProperties = {};
            imageProperties.version = XE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT;

            *pImageProperties = imageProperties;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xetDdiTable.MetricGroup.pfnGet = [](
            xet_device_handle_t,
            uint32_t* pCount,
            xet_metric_group_handle_t* phMetricGroups )
        {
            *pCount = 1;
            if( nullptr != phMetricGroups ) *reinterpret_cast<void**>( phMetricGroups ) = context.get();
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xetDdiTable.MetricGroup.pfnGetProperties = [](
            xet_metric_group_handle_t,
            xet_metric_group_properties_t* pProperties )
        {
            xet_metric_group_properties_t metricGroupProperties = {};
            metricGroupProperties.version = XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT;
            metricGroupProperties.metricCount = 1;
            metricGroupProperties.samplingType = static_cast<xet_metric_group_sampling_type_t>(
                XET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED | XET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED );
            strcpy( metricGroupProperties.name, "Null Metric Group" );

            *pProperties = metricGroupProperties;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xetDdiTable.MetricGroup.pfnCalculateMetricValues = [](
            xet_metric_group_handle_t,
            size_t,
            uint8_t*,
            uint32_t* pMetricValueCount,
            xet_typed_value_t* pMetricValues )
        {
            *pMetricValueCount = 1;
            if( pMetricValues ) *pMetricValues = {};
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xetDdiTable.Metric.pfnGet = [](
            xet_metric_group_handle_t,
            uint32_t* pCount,
            xet_metric_handle_t* phMetrics )
        {
            *pCount = 1;
            if( nullptr != phMetrics ) *reinterpret_cast<void**>( phMetrics ) = context.get();
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xetDdiTable.Metric.pfnGetProperties = [](
            xet_metric_handle_t,
            xet_metric_properties_t* pProperties )
        {
            xet_metric_properties_t metricProperties = {};
            metricProperties.version = XET_METRIC_PROPERTIES_VERSION_CURRENT;
            metricProperties.metricType = XET_METRIC_TYPE_DURATION;
            metricProperties.resultType = XET_VALUE_TYPE_UINT32;
            strcpy( metricProperties.name, "Null Metric" );
            strcpy( metricProperties.resultUnits, "ns" );

            *pProperties = metricProperties;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xetDdiTable.MetricQuery.pfnGetData = [](
            xet_metric_query_handle_t,
            size_t* pRawDataSize,
            uint8_t* pRawData )
        {
            *pRawDataSize = 1;
            if( pRawData ) *pRawData = 0;
            return XE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        xetDdiTable.MetricTracer.pfnReadData = [](
            xet_metric_tracer_handle_t,
            uint32_t,
            size_t* pRawDataSize,
            uint8_t* pRawData )
        {
            *pRawDataSize = 1;
            if( pRawData ) *pRawData = 0;
            return XE_RESULT_SUCCESS;
        };
    }
} // namespace driver

namespace instrumented
{
    //////////////////////////////////////////////////////////////////////////
    context_t context;

    //////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        //////////////////////////////////////////////////////////////////////////
        enableTracing = getenv_tobool( "XE_ENABLE_API_TRACING" );
        if( enableTracing )
        {
            tracerData.emplace_back(); // reserve index 0

            //////////////////////////////////////////////////////////////////////////
            driver::context.xetDdiTable.Tracer.pfnCreate = [](
                xet_device_handle_t,
                const xet_tracer_desc_t* desc,
                xet_tracer_handle_t* phTracer )
            {
                context.tracerData.emplace_back();
                auto index = context.tracerData.size() - 1;
                context.tracerData[ index ].userData = desc->pUserData;

                *phTracer = reinterpret_cast<decltype( *phTracer )>( index );
                return XE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.xetDdiTable.Tracer.pfnSetPrologues = [](
                xet_tracer_handle_t hTracer,
                xet_core_callbacks_t* pCoreCbs,
                xet_experimental_callbacks_t* pExperimentalCbs )
            {
                auto index = reinterpret_cast<size_t>( hTracer );

                context.tracerData[ index ].xePrologueCbs = *pCoreCbs;
                if( pExperimentalCbs ) context.tracerData[ index ].xexPrologueCbs = *pExperimentalCbs;
                return XE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.xetDdiTable.Tracer.pfnSetEpilogues = [](
                xet_tracer_handle_t hTracer,
                xet_core_callbacks_t* pCoreCbs,
                xet_experimental_callbacks_t* pExperimentalCbs )
            {
                auto index = reinterpret_cast<size_t>( hTracer );

                context.tracerData[ index ].xeEpilogueCbs = *pCoreCbs;
                if( pExperimentalCbs ) context.tracerData[ index ].xexEpilogueCbs = *pExperimentalCbs;
                return XE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.xetDdiTable.Tracer.pfnSetEnabled = [](
                xet_tracer_handle_t hTracer,
                xe_bool_t enable )
            {
                auto index = reinterpret_cast<size_t>( hTracer );
                context.tracerData[ index ].enabled = enable;

                return XE_RESULT_SUCCESS;
            };
        }
    }
} // namespace instrumented
