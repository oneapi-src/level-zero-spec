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
* @file xe_tools_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/ldrddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    xet_device_factory_t                xet_device_factory;
    xet_command_list_factory_t          xet_command_list_factory;
    xet_metric_group_factory_t          xet_metric_group_factory;
    xet_metric_factory_t                xet_metric_factory;
    xet_metric_tracer_factory_t         xet_metric_tracer_factory;
    xet_metric_query_pool_factory_t     xet_metric_query_pool_factory;
    xet_metric_query_factory_t          xet_metric_query_factory;
    xet_power_factory_t                 xet_power_factory;
    xet_freq_domain_factory_t           xet_freq_domain_factory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetInit
    xe_result_t __xecall
    xetInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        for( auto& drv : context.drivers )
        {
            if( XE_RESULT_SUCCESS == result )
            {
                result = drv.dditable.xet.Global.pfnInit( flags );
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGroupGet
    xe_result_t __xecall
    xetMetricGroupGet(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< metric groups.
        xet_metric_group_handle_t* phMetricGroup        ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricGroup.pfnGet( hDevice, pCount, phMetricGroup );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetricGroup ) && ( i < *pCount ); ++i )
                phMetricGroup[ i ] = reinterpret_cast<xet_metric_group_handle_t>(
                    xet_metric_group_factory.get( phMetricGroup[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGroupGetProperties
    xe_result_t __xecall
    xetMetricGroupGetProperties(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->dditable;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricGroup.pfnGetProperties( hMetricGroup, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGet
    xe_result_t __xecall
    xetMetricGet(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t ordinal,                               ///< [in] ordinal of metric to retrieve; must be less than
                                                        ///< ::xet_metric_group_properties_t::metricCount
        xet_metric_handle_t* phMetric                   ///< [out] handle of metric
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->dditable;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        auto result = dditable->xet.Metric.pfnGet( hMetricGroup, ordinal, phMetric );

        try
        {
            // convert driver handle to loader handle
            *phMetric = reinterpret_cast<xet_metric_handle_t>(
                xet_metric_factory.get( *phMetric, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGetProperties
    xe_result_t __xecall
    xetMetricGetProperties(
        xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        xet_metric_properties_t* pProperties            ///< [out] metric properties
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_object_t*>( hMetric )->dditable;

        // convert loader handle to driver handle
        hMetric = reinterpret_cast<xet_metric_object_t*>( hMetric )->handle;

        // forward to device-driver
        auto result = dditable->xet.Metric.pfnGetProperties( hMetric, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricGroupCalculateData
    xe_result_t __xecall
    xetMetricGroupCalculateData(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t* pReportCount,                         ///< [in,out] report count to calculate
        uint32_t rawDataSize,                           ///< [in] raw data size
        uint8_t* pRawData,                              ///< [in] raw data to calculate
        uint32_t calculatedDataSize,                    ///< [in] calculated data size
        xet_typed_value_t* pCalculatedData              ///< [in,out] calculated metrics
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->dditable;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricGroup.pfnCalculateData( hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetDeviceActivateMetricGroups
    xe_result_t __xecall
    xetDeviceActivateMetricGroups(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        xet_metric_group_handle_t* phMetricGroups       ///< [in][range(0, count)] handles of the metric groups to activate. NULL
                                                        ///< to deactivate.
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < count ); ++i )
            phMetricGroups[ i ] = reinterpret_cast<xet_metric_group_object_t*>( phMetricGroups[ i ] )->handle;

        // forward to device-driver
        auto result = dditable->xet.Device.pfnActivateMetricGroups( hDevice, count, phMetricGroups );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricTracerOpen
    xe_result_t __xecall
    xetMetricTracerOpen(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        xet_metric_tracer_desc_t* pDesc,                ///< [in,out] metric tracer descriptor
        xe_event_handle_t hNotificationEvent,           ///< [in] event used for report availability notification. Must be device
                                                        ///< to host type.
        xet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // convert loader handle to driver handle
        hNotificationEvent = reinterpret_cast<xe_event_object_t*>( hNotificationEvent )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricTracer.pfnOpen( hDevice, hMetricGroup, pDesc, hNotificationEvent, phMetricTracer );

        try
        {
            // convert driver handle to loader handle
            *phMetricTracer = reinterpret_cast<xet_metric_tracer_handle_t>(
                xet_metric_tracer_factory.get( *phMetricTracer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricTracerMarker
    xe_result_t __xecall
    xetCommandListAppendMetricTracerMarker(
        xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        auto result = dditable->xet.CommandList.pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricTracerClose
    xe_result_t __xecall
    xetMetricTracerClose(
        xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->dditable;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricTracer.pfnClose( hMetricTracer );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricTracerReadData
    xe_result_t __xecall
    xetMetricTracerReadData(
        xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data buffer size
        uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->dditable;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricTracer.pfnReadData( hMetricTracer, pReportCount, rawDataSize, pRawData );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryPoolCreate
    xe_result_t __xecall
    xetMetricQueryPoolCreate(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device
        xet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
        xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricQueryPool.pfnCreate( hDevice, hMetricGroup, pDesc, phMetricQueryPool );

        try
        {
            // convert driver handle to loader handle
            *phMetricQueryPool = reinterpret_cast<xet_metric_query_pool_handle_t>(
                xet_metric_query_pool_factory.get( *phMetricQueryPool, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryPoolDestroy
    xe_result_t __xecall
    xetMetricQueryPoolDestroy(
        xet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricQueryPool.pfnDestroy( hMetricQueryPool );

        // release loader handle
        xet_metric_query_pool_factory.release( hMetricQueryPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryPoolGetMetricQuery
    xe_result_t __xecall
    xetMetricQueryPoolGetMetricQuery(
        xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricQueryPool.pfnGetMetricQuery( hMetricQueryPool, index, phMetricQuery );

        try
        {
            // convert driver handle to loader handle
            *phMetricQuery = reinterpret_cast<xet_metric_query_handle_t>(
                xet_metric_query_factory.get( *phMetricQuery, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricQueryBegin
    xe_result_t __xecall
    xetCommandListAppendMetricQueryBegin(
        xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        auto result = dditable->xet.CommandList.pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricQueryEnd
    xe_result_t __xecall
    xetCommandListAppendMetricQueryEnd(
        xet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // convert loader handle to driver handle
        hCompletionEvent = reinterpret_cast<xe_event_object_t*>( hCompletionEvent )->handle;

        // forward to device-driver
        auto result = dditable->xet.CommandList.pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetCommandListAppendMetricMemoryBarrier
    xe_result_t __xecall
    xetCommandListAppendMetricMemoryBarrier(
        xet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->dditable;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xet_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        auto result = dditable->xet.CommandList.pfnAppendMetricMemoryBarrier( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetMetricQueryGetData
    xe_result_t __xecall
    xetMetricQueryGetData(
        xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
        uint8_t* pRawData                               ///< [in,out] query result data in raw format
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->dditable;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        auto result = dditable->xet.MetricQuery.pfnGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerCreate
    xe_result_t __xecall
    xetPowerCreate(
        xet_device_handle_t hDevice,                    ///< [in] handle of the device object
        uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
        xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_device_object_t*>( hDevice )->dditable;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnCreate( hDevice, flags, pPowerHandle );

        try
        {
            // convert driver handle to loader handle
            *pPowerHandle = reinterpret_cast<xet_power_handle_t>(
                xet_power_factory.get( *pPowerHandle, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerDestroy
    xe_result_t __xecall
    xetPowerDestroy(
        xet_power_handle_t hPower                       ///< [in][release] handle of the power object to destroy
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnDestroy( hPower );

        // release loader handle
        xet_power_factory.release( hPower );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetAveragePowerLimit
    xe_result_t __xecall
    xetPowerGetAveragePowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetAveragePowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetBurstPowerLimit
    xe_result_t __xecall
    xetPowerGetBurstPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetBurstPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetPeakPowerLimit
    xe_result_t __xecall
    xetPowerGetPeakPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetPeakPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetAllPowerLimits
    xe_result_t __xecall
    xetPowerGetAllPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetAllPowerLimits( hPower, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetDefaultPowerLimits
    xe_result_t __xecall
    xetPowerGetDefaultPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetDefaultPowerLimits( hPower, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetAveragePowerLimit
    xe_result_t __xecall
    xetPowerSetAveragePowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnSetAveragePowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetBurstPowerLimit
    xe_result_t __xecall
    xetPowerSetBurstPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnSetBurstPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetPeakPowerLimit
    xe_result_t __xecall
    xetPowerSetPeakPowerLimit(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnSetPeakPowerLimit( hPower, pLimit );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetPowerLimits
    xe_result_t __xecall
    xetPowerSetPowerLimits(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnSetPowerLimits( hPower, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetEnergyCounter
    xe_result_t __xecall
    xetPowerGetEnergyCounter(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetEnergyCounter( hPower, pEnergy );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetTurboMode
    xe_result_t __xecall
    xetPowerGetTurboMode(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetTurboMode( hPower, pTurboMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetTurboMode
    xe_result_t __xecall
    xetPowerSetTurboMode(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnSetTurboMode( hPower, pTurboMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGet
    xe_result_t __xecall
    xetFreqDomainGet(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequency domains.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of frequency domains available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< frequency domains.
        xet_freq_domain_handle_t* phFreqDomain          ///< [in,out][optional][range(0, *pCount)] array of handle of frequency
                                                        ///< domains
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnGet( hPower, pCount, phFreqDomain );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFreqDomain ) && ( i < *pCount ); ++i )
                phFreqDomain[ i ] = reinterpret_cast<xet_freq_domain_handle_t>(
                    xet_freq_domain_factory.get( phFreqDomain[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetProperties
    xe_result_t __xecall
    xetFreqDomainGetProperties(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnGetProperties( hFreqDomain, pFreqDomainProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetSourceFreqDomain
    xe_result_t __xecall
    xetFreqDomainGetSourceFreqDomain(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_freq_domain_handle_t* phSrcFreqDomain       ///< [out] pointer to a handle where the source frequency domain handle
                                                        ///< will be returned
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnGetSourceFreqDomain( hFreqDomain, phSrcFreqDomain );

        try
        {
            // convert driver handle to loader handle
            *phSrcFreqDomain = reinterpret_cast<xet_freq_domain_handle_t>(
                xet_freq_domain_factory.get( *phSrcFreqDomain, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetSupportedClocks
    xe_result_t __xecall
    xetFreqDomainGetSupportedClocks(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t numClockPoints,                        ///< [in] number of elements in pClocks
        uint32_t* pClocks                               ///< [out] pointer to array of frequencies
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnGetSupportedClocks( hFreqDomain, numClockPoints, pClocks );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetSupportedClockDividers
    xe_result_t __xecall
    xetFreqDomainGetSupportedClockDividers(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t numClockDividers,                      ///< [in] number of elements in pDividers
        xet_clock_divider_t* pDividers                  ///< [out] pointer to array of dividers
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetClockRange
    xe_result_t __xecall
    xetFreqDomainGetClockRange(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t* pMinClock,                            ///< [out] min clock frequency in units of MHz
        uint32_t* pMaxClock                             ///< [out] max clock frequency in units of MHz
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnGetClockRange( hFreqDomain, pMinClock, pMaxClock );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainSetClockRange
    xe_result_t __xecall
    xetFreqDomainSetClockRange(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
        uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnSetClockRange( hFreqDomain, minClock, maxClock );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainSetClockDivider
    xe_result_t __xecall
    xetFreqDomainSetClockDivider(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnSetClockDivider( hFreqDomain, pClockDividerRequest );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetFreqDomainGetCurrentFrequency
    xe_result_t __xecall
    xetFreqDomainGetCurrentFrequency(
        xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
        uint32_t* pFreqRequest,                         ///< [out] current frequency in MHz requested by the driver
        uint32_t* pFreqResolved,                        ///< [out] the actual frequency in MHz
        xet_freq_throttle_reasons_t* pFreqThrottleReasons   ///< [out] the reason the resolved frequency is lower than the request
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->dditable;

        // convert loader handle to driver handle
        hFreqDomain = reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain )->handle;

        // forward to device-driver
        auto result = dditable->xet.FreqDomain.pfnGetCurrentFrequency( hFreqDomain, pFreqRequest, pFreqResolved, pFreqThrottleReasons );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanCount
    xe_result_t __xecall
    xetPowerFanCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pFanCount                             ///< [out] the number of fans on the device
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnFanCount( hPower, pFanCount );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanGetProperties
    xe_result_t __xecall
    xetPowerFanGetProperties(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        xet_fan_properties_t* pFanProperties            ///< [out] pointer to storage for fan properties
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnFanGetProperties( hPower, fanIndex, pFanProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanGetSpeedTable
    xe_result_t __xecall
    xetPowerFanGetSpeedTable(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
        uint32_t* pNumFanPoints,                        ///< [in,out] input number of elements in pFanSpeedTable array; output
                                                        ///< number of elements returned
        xet_fan_point_t* pFanPoints                     ///< [out] pointer to an array of temperature/fan-speed points
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanSetSpeedTable
    xe_result_t __xecall
    xetPowerFanSetSpeedTable(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
        xet_fan_point_t* pFanPoints                     ///< [in] pointer to an array of temperature/fan-speed points
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanGetSpeed
    xe_result_t __xecall
    xetPowerFanGetSpeed(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
        xet_fan_speed_info_t* pFanSpeed                 ///< [out] pointer to an array of current fan speeds
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerFanSetSpeed
    xe_result_t __xecall
    xetPowerFanSetSpeed(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
        uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                        ///< (startFanIndex)..(startFanIndex + numFans - 1)
        xet_fan_speed_info_t* pFanSpeed                 ///< [in] pointer to an array of current fan speeds
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerTemperatureSensorCount
    xe_result_t __xecall
    xetPowerTemperatureSensorCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnTemperatureSensorCount( hPower, pSensorCount );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetTemperatureProperties
    xe_result_t __xecall
    xetPowerGetTemperatureProperties(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        xet_temperature_properties_t* pProperties       ///< [out] pointer to properties for this sensor
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetTemperatureProperties( hPower, sensorIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetTemperature
    xe_result_t __xecall
    xetPowerGetTemperature(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        uint32_t numSensors,                            ///< [in] pTemperatures will contain results for sensors index
                                                        ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
        uint16_t* pTemperatures                         ///< [out] pointer to an array of temperatures in units of degrees celsius
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerSetTemperatureThreshold
    xe_result_t __xecall
    xetPowerSetTemperatureThreshold(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
        uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                        ///< will be throttled
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerActivityCount
    xe_result_t __xecall
    xetPowerActivityCount(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnActivityCount( hPower, pActivityCount );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetActivityProperties
    xe_result_t __xecall
    xetPowerGetActivityProperties(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t activityIndex,                         ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
        xet_activity_properties_t* pProperties          ///< [out] pointer to properties for this activity counter
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetActivityProperties( hPower, activityIndex, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xetPowerGetActivityCounters
    xe_result_t __xecall
    xetPowerGetActivityCounters(
        xet_power_handle_t hPower,                      ///< [in] handle of the power object
        uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
        uint32_t numCounters,                           ///< [in] pCounters will contain results for activity counter index
                                                        ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
        xet_activity_counters_t* pCounters              ///< [out] pointer to an array of activity counter data
        )
    {
        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xet_power_object_t*>( hPower )->dditable;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<xet_power_object_t*>( hPower )->handle;

        // forward to device-driver
        auto result = dditable->xet.Power.pfnGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetGlobalProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Global );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnInit                                     = loader::xetInit;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetGlobalProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetDeviceProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Device );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnActivateMetricGroups                     = loader::xetDeviceActivateMetricGroups;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetDeviceProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetCommandListProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.CommandList );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnAppendMetricTracerMarker                 = loader::xetCommandListAppendMetricTracerMarker;
            pDdiTable->pfnAppendMetricQueryBegin                   = loader::xetCommandListAppendMetricQueryBegin;
            pDdiTable->pfnAppendMetricQueryEnd                     = loader::xetCommandListAppendMetricQueryEnd;
            pDdiTable->pfnAppendMetricMemoryBarrier                = loader::xetCommandListAppendMetricMemoryBarrier;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetCommandListProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricGroupProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricGroup );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xetMetricGroupGet;
            pDdiTable->pfnGetProperties                            = loader::xetMetricGroupGetProperties;
            pDdiTable->pfnCalculateData                            = loader::xetMetricGroupCalculateData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricGroup;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricGroupProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Metric );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xetMetricGet;
            pDdiTable->pfnGetProperties                            = loader::xetMetricGetProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Metric;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricTracerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricTracerProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricTracer );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnOpen                                     = loader::xetMetricTracerOpen;
            pDdiTable->pfnClose                                    = loader::xetMetricTracerClose;
            pDdiTable->pfnReadData                                 = loader::xetMetricTracerReadData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricTracer;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricTracerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricQueryPoolProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricQueryPool );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xetMetricQueryPoolCreate;
            pDdiTable->pfnDestroy                                  = loader::xetMetricQueryPoolDestroy;
            pDdiTable->pfnGetMetricQuery                           = loader::xetMetricQueryPoolGetMetricQuery;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricQueryPool;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricQueryPoolProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetMetricQueryProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.MetricQuery );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetData                                  = loader::xetMetricQueryGetData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.MetricQuery;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetMetricQueryProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetPowerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_power_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetPowerProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.Power );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xetPowerCreate;
            pDdiTable->pfnDestroy                                  = loader::xetPowerDestroy;
            pDdiTable->pfnGetAveragePowerLimit                     = loader::xetPowerGetAveragePowerLimit;
            pDdiTable->pfnGetBurstPowerLimit                       = loader::xetPowerGetBurstPowerLimit;
            pDdiTable->pfnGetPeakPowerLimit                        = loader::xetPowerGetPeakPowerLimit;
            pDdiTable->pfnGetAllPowerLimits                        = loader::xetPowerGetAllPowerLimits;
            pDdiTable->pfnGetDefaultPowerLimits                    = loader::xetPowerGetDefaultPowerLimits;
            pDdiTable->pfnSetAveragePowerLimit                     = loader::xetPowerSetAveragePowerLimit;
            pDdiTable->pfnSetBurstPowerLimit                       = loader::xetPowerSetBurstPowerLimit;
            pDdiTable->pfnSetPeakPowerLimit                        = loader::xetPowerSetPeakPowerLimit;
            pDdiTable->pfnSetPowerLimits                           = loader::xetPowerSetPowerLimits;
            pDdiTable->pfnGetEnergyCounter                         = loader::xetPowerGetEnergyCounter;
            pDdiTable->pfnGetTurboMode                             = loader::xetPowerGetTurboMode;
            pDdiTable->pfnSetTurboMode                             = loader::xetPowerSetTurboMode;
            pDdiTable->pfnFanCount                                 = loader::xetPowerFanCount;
            pDdiTable->pfnFanGetProperties                         = loader::xetPowerFanGetProperties;
            pDdiTable->pfnFanGetSpeedTable                         = loader::xetPowerFanGetSpeedTable;
            pDdiTable->pfnFanSetSpeedTable                         = loader::xetPowerFanSetSpeedTable;
            pDdiTable->pfnFanGetSpeed                              = loader::xetPowerFanGetSpeed;
            pDdiTable->pfnFanSetSpeed                              = loader::xetPowerFanSetSpeed;
            pDdiTable->pfnTemperatureSensorCount                   = loader::xetPowerTemperatureSensorCount;
            pDdiTable->pfnGetTemperatureProperties                 = loader::xetPowerGetTemperatureProperties;
            pDdiTable->pfnGetTemperature                           = loader::xetPowerGetTemperature;
            pDdiTable->pfnSetTemperatureThreshold                  = loader::xetPowerSetTemperatureThreshold;
            pDdiTable->pfnActivityCount                            = loader::xetPowerActivityCount;
            pDdiTable->pfnGetActivityProperties                    = loader::xetPowerGetActivityProperties;
            pDdiTable->pfnGetActivityCounters                      = loader::xetPowerGetActivityCounters;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.Power;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetPowerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FreqDomain table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetFreqDomainProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_freq_domain_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            static auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xetGetFreqDomainProcAddrTable") );
            result = getTable( version, &drv.dditable.xet.FreqDomain );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::xetFreqDomainGet;
            pDdiTable->pfnGetProperties                            = loader::xetFreqDomainGetProperties;
            pDdiTable->pfnGetSourceFreqDomain                      = loader::xetFreqDomainGetSourceFreqDomain;
            pDdiTable->pfnGetSupportedClocks                       = loader::xetFreqDomainGetSupportedClocks;
            pDdiTable->pfnGetSupportedClockDividers                = loader::xetFreqDomainGetSupportedClockDividers;
            pDdiTable->pfnGetClockRange                            = loader::xetFreqDomainGetClockRange;
            pDdiTable->pfnSetClockRange                            = loader::xetFreqDomainSetClockRange;
            pDdiTable->pfnSetClockDivider                          = loader::xetFreqDomainSetClockDivider;
            pDdiTable->pfnGetCurrentFrequency                      = loader::xetFreqDomainGetCurrentFrequency;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xet.FreqDomain;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xetGetFreqDomainProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
