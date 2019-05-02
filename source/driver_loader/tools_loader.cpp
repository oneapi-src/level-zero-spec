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
* @file tools_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.cpp.mako
* @endcond
*
******************************************************************************/
#include "xet_all.h"
#include "loader.h"

xet_apitable_t xet_apitable = {};

///////////////////////////////////////////////////////////////////////////////
/// @brief Loads function pointer table for loaded driver
bool xetLoadExports(
    void* handle )  ///< [in] driver handle
{
    xet_apitable.pfnMetricGroupGetCount                                  = (xet_pfnMetricGroupGetCount_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGetCount");
    if( nullptr == xet_apitable.pfnMetricGroupGetCount )
        return false;

    xet_apitable.pfnMetricGroupGet                                       = (xet_pfnMetricGroupGet_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGet");
    if( nullptr == xet_apitable.pfnMetricGroupGet )
        return false;

    xet_apitable.pfnMetricGroupGetProperties                             = (xet_pfnMetricGroupGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGetProperties");
    if( nullptr == xet_apitable.pfnMetricGroupGetProperties )
        return false;

    xet_apitable.pfnMetricGet                                            = (xet_pfnMetricGet_t)LOAD_FUNCTION_PTR(handle, "xetMetricGet");
    if( nullptr == xet_apitable.pfnMetricGet )
        return false;

    xet_apitable.pfnMetricGetProperties                                  = (xet_pfnMetricGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetMetricGetProperties");
    if( nullptr == xet_apitable.pfnMetricGetProperties )
        return false;

    xet_apitable.pfnMetricGroupCalculateData                             = (xet_pfnMetricGroupCalculateData_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupCalculateData");
    if( nullptr == xet_apitable.pfnMetricGroupCalculateData )
        return false;

    xet_apitable.pfnDeviceActivateMetricGroups                           = (xet_pfnDeviceActivateMetricGroups_t)LOAD_FUNCTION_PTR(handle, "xetDeviceActivateMetricGroups");
    if( nullptr == xet_apitable.pfnDeviceActivateMetricGroups )
        return false;

    xet_apitable.pfnMetricTracerOpen                                     = (xet_pfnMetricTracerOpen_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerOpen");
    if( nullptr == xet_apitable.pfnMetricTracerOpen )
        return false;

    xet_apitable.pfnCommandListAppendMetricTracerMarker                  = (xet_pfnCommandListAppendMetricTracerMarker_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricTracerMarker");
    if( nullptr == xet_apitable.pfnCommandListAppendMetricTracerMarker )
        return false;

    xet_apitable.pfnMetricTracerClose                                    = (xet_pfnMetricTracerClose_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerClose");
    if( nullptr == xet_apitable.pfnMetricTracerClose )
        return false;

    xet_apitable.pfnMetricTracerReadData                                 = (xet_pfnMetricTracerReadData_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerReadData");
    if( nullptr == xet_apitable.pfnMetricTracerReadData )
        return false;

    xet_apitable.pfnMetricQueryPoolCreate                                = (xet_pfnMetricQueryPoolCreate_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolCreate");
    if( nullptr == xet_apitable.pfnMetricQueryPoolCreate )
        return false;

    xet_apitable.pfnMetricQueryPoolDestroy                               = (xet_pfnMetricQueryPoolDestroy_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolDestroy");
    if( nullptr == xet_apitable.pfnMetricQueryPoolDestroy )
        return false;

    xet_apitable.pfnMetricQueryPoolGetMetricQuery                        = (xet_pfnMetricQueryPoolGetMetricQuery_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolGetMetricQuery");
    if( nullptr == xet_apitable.pfnMetricQueryPoolGetMetricQuery )
        return false;

    xet_apitable.pfnCommandListAppendMetricQueryBegin                    = (xet_pfnCommandListAppendMetricQueryBegin_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricQueryBegin");
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryBegin )
        return false;

    xet_apitable.pfnCommandListAppendMetricQueryEnd                      = (xet_pfnCommandListAppendMetricQueryEnd_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricQueryEnd");
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryEnd )
        return false;

    xet_apitable.pfnCommandListAppendMetricMemoryBarrier                 = (xet_pfnCommandListAppendMetricMemoryBarrier_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricMemoryBarrier");
    if( nullptr == xet_apitable.pfnCommandListAppendMetricMemoryBarrier )
        return false;

    xet_apitable.pfnMetricQueryGetData                                   = (xet_pfnMetricQueryGetData_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryGetData");
    if( nullptr == xet_apitable.pfnMetricQueryGetData )
        return false;

    return true;
}


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGroupGetCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    )
{
    if( nullptr == xet_apitable.pfnMetricGroupGetCount )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricGroupGetCount( hDevice, pCount );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGroupGet(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t ordinal,                               ///< [in] metric group index
    xet_metric_group_handle_t* phMetricGroup        ///< [out] metric group handle
    )
{
    if( nullptr == xet_apitable.pfnMetricGroupGet )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricGroupGet( hDevice, ordinal, phMetricGroup );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGroupGetProperties(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    )
{
    if( nullptr == xet_apitable.pfnMetricGroupGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricGroupGetProperties( hMetricGroup, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGet(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t ordinal,                               ///< [in] metric index
    xet_metric_handle_t* phMetric                   ///< [out] handle of metric
    )
{
    if( nullptr == xet_apitable.pfnMetricGet )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricGet( hMetricGroup, ordinal, phMetric );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGetProperties(
    xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    xet_metric_properties_t* pProperties            ///< [out] metric properties
    )
{
    if( nullptr == xet_apitable.pfnMetricGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricGetProperties( hMetric, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xet_apitable.pfnMetricGroupCalculateData( hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetDeviceActivateMetricGroups(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    xet_metric_group_handle_t* phMetricGroups       ///< [in] handles of the metric groups to activate. NULL to deactivate.
    )
{
    if( nullptr == xet_apitable.pfnDeviceActivateMetricGroups )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnDeviceActivateMetricGroups( hDevice, count, phMetricGroups );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xet_apitable.pfnMetricTracerOpen( hDevice, pDesc, hNotificationEvent, phMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricTracerMarker(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t value                                  ///< [in] tracer marker value
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricTracerMarker )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    )
{
    if( nullptr == xet_apitable.pfnMetricTracerClose )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricTracerClose( hMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricTracerReadData(
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
    uint32_t rawDataSize,                           ///< [in] raw data buffer size
    uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
    )
{
    if( nullptr == xet_apitable.pfnMetricTracerReadData )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricTracerReadData( hMetricTracer, pReportCount, rawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
    xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryPoolCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricQueryPoolCreate( hDevice, pDesc, phMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryPoolDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricQueryPoolDestroy( hMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryPoolGetMetricQuery(
    xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t ordinal,                               ///< [in] index of the query within the pool
    xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryPoolGetMetricQuery )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricQueryPoolGetMetricQuery( hMetricQueryPool, ordinal, phMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryBegin )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryEnd )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    if( nullptr == xet_apitable.pfnCommandListAppendMetricMemoryBarrier )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnCommandListAppendMetricMemoryBarrier( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryGetData(
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
    uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
    uint8_t* pRawData                               ///< [in,out] query result data in raw format
    )
{
    if( nullptr == xet_apitable.pfnMetricQueryGetData )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xet_apitable.pfnMetricQueryGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );
}

#if defined(__cplusplus)
};
#endif
