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
* @file tools_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/layer.cpp.mako
* @endcond
*
******************************************************************************/
#include "xet_all.h"
#include "layer.h"

xet_apitable_t xet_apitable = {};

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercepts function pointer table for loaded driver
bool xetIntercept(
    xet_apitable_t* original ) ///< [in] pointer to table of xet API function pointers
{
    if(nullptr == original)
        return false;

    if( nullptr == original->pfnMetricGroupGetCount )
        return false;
    xet_apitable.pfnMetricGroupGetCount                                  = original->pfnMetricGroupGetCount;
    original->pfnMetricGroupGetCount                                     = xetMetricGroupGetCount;

    if( nullptr == original->pfnMetricGroupGet )
        return false;
    xet_apitable.pfnMetricGroupGet                                       = original->pfnMetricGroupGet;
    original->pfnMetricGroupGet                                          = xetMetricGroupGet;

    if( nullptr == original->pfnMetricGroupGetProperties )
        return false;
    xet_apitable.pfnMetricGroupGetProperties                             = original->pfnMetricGroupGetProperties;
    original->pfnMetricGroupGetProperties                                = xetMetricGroupGetProperties;

    if( nullptr == original->pfnMetricGet )
        return false;
    xet_apitable.pfnMetricGet                                            = original->pfnMetricGet;
    original->pfnMetricGet                                               = xetMetricGet;

    if( nullptr == original->pfnMetricGetProperties )
        return false;
    xet_apitable.pfnMetricGetProperties                                  = original->pfnMetricGetProperties;
    original->pfnMetricGetProperties                                     = xetMetricGetProperties;

    if( nullptr == original->pfnMetricGroupCalculateData )
        return false;
    xet_apitable.pfnMetricGroupCalculateData                             = original->pfnMetricGroupCalculateData;
    original->pfnMetricGroupCalculateData                                = xetMetricGroupCalculateData;

    if( nullptr == original->pfnDeviceActivateMetricGroups )
        return false;
    xet_apitable.pfnDeviceActivateMetricGroups                           = original->pfnDeviceActivateMetricGroups;
    original->pfnDeviceActivateMetricGroups                              = xetDeviceActivateMetricGroups;

    if( nullptr == original->pfnMetricTracerOpen )
        return false;
    xet_apitable.pfnMetricTracerOpen                                     = original->pfnMetricTracerOpen;
    original->pfnMetricTracerOpen                                        = xetMetricTracerOpen;

    if( nullptr == original->pfnCommandListAppendMetricTracerMarker )
        return false;
    xet_apitable.pfnCommandListAppendMetricTracerMarker                  = original->pfnCommandListAppendMetricTracerMarker;
    original->pfnCommandListAppendMetricTracerMarker                     = xetCommandListAppendMetricTracerMarker;

    if( nullptr == original->pfnMetricTracerClose )
        return false;
    xet_apitable.pfnMetricTracerClose                                    = original->pfnMetricTracerClose;
    original->pfnMetricTracerClose                                       = xetMetricTracerClose;

    if( nullptr == original->pfnMetricTracerReadData )
        return false;
    xet_apitable.pfnMetricTracerReadData                                 = original->pfnMetricTracerReadData;
    original->pfnMetricTracerReadData                                    = xetMetricTracerReadData;

    if( nullptr == original->pfnMetricQueryPoolCreate )
        return false;
    xet_apitable.pfnMetricQueryPoolCreate                                = original->pfnMetricQueryPoolCreate;
    original->pfnMetricQueryPoolCreate                                   = xetMetricQueryPoolCreate;

    if( nullptr == original->pfnMetricQueryPoolDestroy )
        return false;
    xet_apitable.pfnMetricQueryPoolDestroy                               = original->pfnMetricQueryPoolDestroy;
    original->pfnMetricQueryPoolDestroy                                  = xetMetricQueryPoolDestroy;

    if( nullptr == original->pfnMetricQueryPoolGetMetricQuery )
        return false;
    xet_apitable.pfnMetricQueryPoolGetMetricQuery                        = original->pfnMetricQueryPoolGetMetricQuery;
    original->pfnMetricQueryPoolGetMetricQuery                           = xetMetricQueryPoolGetMetricQuery;

    if( nullptr == original->pfnCommandListAppendMetricQueryBegin )
        return false;
    xet_apitable.pfnCommandListAppendMetricQueryBegin                    = original->pfnCommandListAppendMetricQueryBegin;
    original->pfnCommandListAppendMetricQueryBegin                       = xetCommandListAppendMetricQueryBegin;

    if( nullptr == original->pfnCommandListAppendMetricQueryEnd )
        return false;
    xet_apitable.pfnCommandListAppendMetricQueryEnd                      = original->pfnCommandListAppendMetricQueryEnd;
    original->pfnCommandListAppendMetricQueryEnd                         = xetCommandListAppendMetricQueryEnd;

    if( nullptr == original->pfnCommandListAppendMetricMemoryBarrier )
        return false;
    xet_apitable.pfnCommandListAppendMetricMemoryBarrier                 = original->pfnCommandListAppendMetricMemoryBarrier;
    original->pfnCommandListAppendMetricMemoryBarrier                    = xetCommandListAppendMetricMemoryBarrier;

    if( nullptr == original->pfnMetricQueryGetData )
        return false;
    xet_apitable.pfnMetricQueryGetData                                   = original->pfnMetricQueryGetData;
    original->pfnMetricQueryGetData                                      = xetMetricQueryGetData;

    return true;
}


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGroupGetCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    )
{
    if( nullptr == xet_apitable.pfnMetricGroupGetCount )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricGroupGetCount( hDevice, pCount );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGroupGet(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t ordinal,                               ///< [in] metric group index
    xet_metric_group_handle_t* phMetricGroup        ///< [out] metric group handle
    )
{
    if( nullptr == xet_apitable.pfnMetricGroupGet )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricGroupGet( hDevice, ordinal, phMetricGroup );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGroupGetProperties(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    )
{
    if( nullptr == xet_apitable.pfnMetricGroupGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricGroupGetProperties( hMetricGroup, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGet(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t ordinal,                               ///< [in] metric index
    xet_metric_handle_t* phMetric                   ///< [out] handle of metric
    )
{
    if( nullptr == xet_apitable.pfnMetricGet )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetric ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricGet( hMetricGroup, ordinal, phMetric );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGetProperties(
    xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    xet_metric_properties_t* pProperties            ///< [out] metric properties
    )
{
    if( nullptr == xet_apitable.pfnMetricGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetric ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricGetProperties( hMetric, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
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
    if( nullptr == xet_apitable.pfnMetricGroupCalculateData )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pReportCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRawData ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pCalculatedData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricGroupCalculateData( hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetDeviceActivateMetricGroups(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    xet_metric_group_handle_t* phMetricGroups       ///< [in] handles of the metric groups to activate. NULL to deactivate.
    )
{
    if( nullptr == xet_apitable.pfnDeviceActivateMetricGroups )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricGroups ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnDeviceActivateMetricGroups( hDevice, count, phMetricGroups );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricTracerOpen(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xet_metric_tracer_desc_t* pDesc,                ///< [in,out] metric tracer descriptor
    xe_event_handle_t hNotificationEvent,           ///< [in] event used for report availability notification. Must be device
                                                    ///< to host type.
    xet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    )
{
    if( nullptr == xet_apitable.pfnMetricTracerOpen )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hNotificationEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XET_METRIC_TRACER_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xet_apitable.pfnMetricTracerOpen( hDevice, pDesc, hNotificationEvent, phMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricTracerMarker(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t value                                  ///< [in] tracer marker value
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricTracerMarker )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    )
{
    if( nullptr == xet_apitable.pfnMetricTracerClose )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricTracerClose( hMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricTracerReadData(
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
    uint32_t rawDataSize,                           ///< [in] raw data buffer size
    uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
    )
{
    if( nullptr == xet_apitable.pfnMetricTracerReadData )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pReportCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRawData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricTracerReadData( hMetricTracer, pReportCount, rawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
    xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryPoolCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricQueryPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xet_apitable.pfnMetricQueryPoolCreate( hDevice, pDesc, phMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryPoolDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricQueryPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricQueryPoolDestroy( hMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryPoolGetMetricQuery(
    xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t ordinal,                               ///< [in] index of the query within the pool
    xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryPoolGetMetricQuery )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricQueryPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricQueryPoolGetMetricQuery( hMetricQueryPool, ordinal, phMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryBegin )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryEnd )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hCompletionEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricMemoryBarrier )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnCommandListAppendMetricMemoryBarrier( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryGetData(
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
    uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
    uint8_t* pRawData                               ///< [in,out] query result data in raw format
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryGetData )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pReportCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRawData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xet_apitable.pfnMetricQueryGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );
}

#if defined(__cplusplus)
};
#endif
