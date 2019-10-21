/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_null.cpp
 *
 */
#include "ze_null.h"

namespace driver
{
    //////////////////////////////////////////////////////////////////////////
    context_t context;

    //////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnGet = [](
            uint32_t* pCount,
            ze_driver_handle_t* phDrivers )
        {
            *pCount = 1;
            if( nullptr != phDrivers ) *reinterpret_cast<void**>( phDrivers ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGet = [](
            ze_driver_handle_t,
            uint32_t* pCount,
            ze_device_handle_t* phDevices )
        {
            *pCount = 1;
            if( nullptr != phDevices ) *reinterpret_cast<void**>( phDevices ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //pfnCreateEventPool

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnGetDriverVersion = [](
            ze_driver_handle_t,
            uint32_t* version )
        {
            *version = 0;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnGetApiVersion = [](
            ze_driver_handle_t,
            ze_api_version_t* version )
        {
            *version = context.version;
            return ZE_RESULT_SUCCESS;
        };

        //pfnGetIPCProperties
        
        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnAllocSharedMem = [](
            ze_driver_handle_t,
            ze_device_handle_t,
            ze_device_mem_alloc_flag_t,
            uint32_t,
            ze_host_mem_alloc_flag_t,
            size_t size,
            size_t alignment,
            void** pptr)
        {
            *pptr = malloc(size);
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnAllocDeviceMem = [](
            ze_driver_handle_t,
            ze_device_handle_t,
            ze_device_mem_alloc_flag_t,
            uint32_t,
            size_t size,
            size_t alignment,
            void** pptr)
        {
            *pptr = malloc(size);
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnAllocHostMem = [](
            ze_driver_handle_t,
            ze_host_mem_alloc_flag_t,
            size_t size,
            size_t alignment,
            void** pptr)
        {
            *pptr = malloc(size);
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnFreeMem = [](
            ze_driver_handle_t,
            void* ptr)
        {
            free(ptr);
            return ZE_RESULT_SUCCESS;
        };

        //pfnGetMemProperties
        //pfnGetMemAddressRange
        //pfnGetMemIpcHandle
        //pfnOpenMemIpcHandle
        //pfnCloseMemIpcHandle

        //////////////////////////////////////////////////////////////////////////
        //pfnGetSubDevices

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetProperties = [](
            ze_device_handle_t,
            ze_device_properties_t* pDeviceProperties )
        {
            ze_device_properties_t deviceProperties = {};
            deviceProperties.version = ZE_DEVICE_PROPERTIES_VERSION_CURRENT;
            deviceProperties.type = ZE_DEVICE_TYPE_GPU;
            deviceProperties.maxCommandQueues = 1;
            deviceProperties.numAsyncComputeEngines = 1;
            deviceProperties.numAsyncCopyEngines = 1;
            strcpy( deviceProperties.name, "Null Device" );

            *pDeviceProperties = deviceProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetComputeProperties = [](
            ze_device_handle_t,
            ze_device_compute_properties_t* pComputeProperties )
        {
            ze_device_compute_properties_t computeProperties = {};
            computeProperties.version = ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT;

            *pComputeProperties = computeProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetMemoryProperties = [](
            ze_device_handle_t,
            uint32_t* pCount,
            ze_device_memory_properties_t* pMemProperties )
        {
            ze_device_memory_properties_t memoryProperties = {};
            memoryProperties.version = ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT;

            *pCount = 1;
            if( nullptr != pMemProperties ) *pMemProperties = memoryProperties;

            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetMemoryAccessProperties = [](
            ze_device_handle_t,
            ze_device_memory_access_properties_t* pMemAccessProperties )
        {
            ze_device_memory_access_properties_t memoryAccessProperties = {};
            memoryAccessProperties.version = ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT;

            *pMemAccessProperties = memoryAccessProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetCacheProperties = [](
            ze_device_handle_t,
            ze_device_cache_properties_t* pCacheProperties )
        {
            ze_device_cache_properties_t cacheProperties = {};
            cacheProperties.version = ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT;

            *pCacheProperties = cacheProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetImageProperties = [](
            ze_device_handle_t,
            ze_device_image_properties_t* pImageProperties )
        {
            ze_device_image_properties_t imageProperties = {};
            imageProperties.version = ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT;

            *pImageProperties = imageProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricGroup.pfnGet = [](
            zet_device_handle_t,
            uint32_t* pCount,
            zet_metric_group_handle_t* phMetricGroups )
        {
            *pCount = 1;
            if( nullptr != phMetricGroups ) *reinterpret_cast<void**>( phMetricGroups ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricGroup.pfnGetProperties = [](
            zet_metric_group_handle_t,
            zet_metric_group_properties_t* pProperties )
        {
            zet_metric_group_properties_t metricGroupProperties = {};
            metricGroupProperties.version = ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT;
            metricGroupProperties.metricCount = 1;
            metricGroupProperties.samplingType = static_cast<zet_metric_group_sampling_type_t>(
                ZET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED | ZET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED );
            strcpy( metricGroupProperties.name, "Null Metric Group" );

            *pProperties = metricGroupProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricGroup.pfnCalculateMetricValues = [](
            zet_metric_group_handle_t,
            size_t,
            const uint8_t*,
            uint32_t* pMetricValueCount,
            zet_typed_value_t* pMetricValues )
        {
            *pMetricValueCount = 1;
            if( pMetricValues ) *pMetricValues = {};
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.Metric.pfnGet = [](
            zet_metric_group_handle_t,
            uint32_t* pCount,
            zet_metric_handle_t* phMetrics )
        {
            *pCount = 1;
            if( nullptr != phMetrics ) *reinterpret_cast<void**>( phMetrics ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.Metric.pfnGetProperties = [](
            zet_metric_handle_t,
            zet_metric_properties_t* pProperties )
        {
            zet_metric_properties_t metricProperties = {};
            metricProperties.version = ZET_METRIC_PROPERTIES_VERSION_CURRENT;
            metricProperties.metricType = ZET_METRIC_TYPE_DURATION;
            metricProperties.resultType = ZET_VALUE_TYPE_UINT32;
            strcpy( metricProperties.name, "Null Metric" );
            strcpy( metricProperties.resultUnits, "ns" );

            *pProperties = metricProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricQuery.pfnGetData = [](
            zet_metric_query_handle_t,
            size_t* pRawDataSize,
            uint8_t* pRawData )
        {
            *pRawDataSize = 1;
            if( pRawData ) *pRawData = 0;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricTracer.pfnReadData = [](
            zet_metric_tracer_handle_t,
            uint32_t,
            size_t* pRawDataSize,
            uint8_t* pRawData )
        {
            *pRawDataSize = 1;
            if( pRawData ) *pRawData = 0;
            return ZE_RESULT_SUCCESS;
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
        enableTracing = getenv_tobool( "ZE_ENABLE_API_TRACING" );
        if( enableTracing )
        {
            tracerData.emplace_back(); // reserve index 0

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.Tracer.pfnCreate = [](
                zet_device_handle_t,
                const zet_tracer_desc_t* desc,
                zet_tracer_handle_t* phTracer )
            {
                context.tracerData.emplace_back();
                auto index = context.tracerData.size() - 1;
                context.tracerData[ index ].userData = desc->pUserData;

                *phTracer = reinterpret_cast<decltype( *phTracer )>( index );
                return ZE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.Tracer.pfnSetPrologues = [](
                zet_tracer_handle_t hTracer,
                zet_core_callbacks_t* pCoreCbs,
                zet_experimental_callbacks_t* pExperimentalCbs )
            {
                auto index = reinterpret_cast<size_t>( hTracer );

                context.tracerData[ index ].zePrologueCbs = *pCoreCbs;
                if( pExperimentalCbs ) context.tracerData[ index ].zexPrologueCbs = *pExperimentalCbs;
                return ZE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.Tracer.pfnSetEpilogues = [](
                zet_tracer_handle_t hTracer,
                zet_core_callbacks_t* pCoreCbs,
                zet_experimental_callbacks_t* pExperimentalCbs )
            {
                auto index = reinterpret_cast<size_t>( hTracer );

                context.tracerData[ index ].zeEpilogueCbs = *pCoreCbs;
                if( pExperimentalCbs ) context.tracerData[ index ].zexEpilogueCbs = *pExperimentalCbs;
                return ZE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.Tracer.pfnSetEnabled = [](
                zet_tracer_handle_t hTracer,
                ze_bool_t enable )
            {
                auto index = reinterpret_cast<size_t>( hTracer );
                context.tracerData[ index ].enabled = enable;

                return ZE_RESULT_SUCCESS;
            };
        }
    }
} // namespace instrumented
