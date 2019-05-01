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
#include "tools_layer.h"

namespace xe_layer
{
    extern context_t context;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Loads function pointer table for loaded driver
    bool xetIntercept(
        xetapi_pfntable_ptr_t pfntable )   ///< [in] pointer to table of xet API function pointers
    {
        if((nullptr == context.xetapi) || (nullptr == pfntable))
            return false;

        context.xetapi->xetMetricGroupGetCount                                      = pfntable->xetMetricGroupGetCount;
        pfntable->xetMetricGroupGetCount                                            = xetMetricGroupGetCount;

        context.xetapi->xetMetricGroupGet                                           = pfntable->xetMetricGroupGet;
        pfntable->xetMetricGroupGet                                                 = xetMetricGroupGet;

        context.xetapi->xetMetricGroupGetProperties                                 = pfntable->xetMetricGroupGetProperties;
        pfntable->xetMetricGroupGetProperties                                       = xetMetricGroupGetProperties;

        context.xetapi->xetMetricGet                                                = pfntable->xetMetricGet;
        pfntable->xetMetricGet                                                      = xetMetricGet;

        context.xetapi->xetMetricGetProperties                                      = pfntable->xetMetricGetProperties;
        pfntable->xetMetricGetProperties                                            = xetMetricGetProperties;

        context.xetapi->xetMetricGroupCalculateData                                 = pfntable->xetMetricGroupCalculateData;
        pfntable->xetMetricGroupCalculateData                                       = xetMetricGroupCalculateData;

        context.xetapi->xetDeviceActivateMetricGroups                               = pfntable->xetDeviceActivateMetricGroups;
        pfntable->xetDeviceActivateMetricGroups                                     = xetDeviceActivateMetricGroups;

        context.xetapi->xetMetricTracerOpen                                         = pfntable->xetMetricTracerOpen;
        pfntable->xetMetricTracerOpen                                               = xetMetricTracerOpen;

        context.xetapi->xetCommandListAppendMetricTracerMarker                      = pfntable->xetCommandListAppendMetricTracerMarker;
        pfntable->xetCommandListAppendMetricTracerMarker                            = xetCommandListAppendMetricTracerMarker;

        context.xetapi->xetMetricTracerClose                                        = pfntable->xetMetricTracerClose;
        pfntable->xetMetricTracerClose                                              = xetMetricTracerClose;

        context.xetapi->xetMetricTracerReadData                                     = pfntable->xetMetricTracerReadData;
        pfntable->xetMetricTracerReadData                                           = xetMetricTracerReadData;

        context.xetapi->xetMetricQueryPoolCreate                                    = pfntable->xetMetricQueryPoolCreate;
        pfntable->xetMetricQueryPoolCreate                                          = xetMetricQueryPoolCreate;

        context.xetapi->xetMetricQueryPoolDestroy                                   = pfntable->xetMetricQueryPoolDestroy;
        pfntable->xetMetricQueryPoolDestroy                                         = xetMetricQueryPoolDestroy;

        context.xetapi->xetMetricQueryPoolGetMetricQuery                            = pfntable->xetMetricQueryPoolGetMetricQuery;
        pfntable->xetMetricQueryPoolGetMetricQuery                                  = xetMetricQueryPoolGetMetricQuery;

        context.xetapi->xetCommandListAppendMetricQueryBegin                        = pfntable->xetCommandListAppendMetricQueryBegin;
        pfntable->xetCommandListAppendMetricQueryBegin                              = xetCommandListAppendMetricQueryBegin;

        context.xetapi->xetCommandListAppendMetricQueryEnd                          = pfntable->xetCommandListAppendMetricQueryEnd;
        pfntable->xetCommandListAppendMetricQueryEnd                                = xetCommandListAppendMetricQueryEnd;

        context.xetapi->xetCommandListAppendMetricMemoryBarrier                     = pfntable->xetCommandListAppendMetricMemoryBarrier;
        pfntable->xetCommandListAppendMetricMemoryBarrier                           = xetCommandListAppendMetricMemoryBarrier;

        context.xetapi->xetMetricQueryGetData                                       = pfntable->xetMetricQueryGetData;
        pfntable->xetMetricQueryGetData                                             = xetMetricQueryGetData;


        return true;
    }

} // namespace xe_layer


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGroupGetCount(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricGroupGetCount(hDevice, pCount);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGroupGet(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t ordinal,                               ///< [in] metric group index
        xet_metric_group_handle_t* phMetricGroup        ///< [out] metric group handle
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricGroupGet(hDevice, ordinal, phMetricGroup);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGroupGetProperties(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    ){
    // Check parameters
    if( nullptr == hMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricGroupGetProperties(hMetricGroup, pProperties);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGet(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t ordinal,                               ///< [in] metric index
        xet_metric_handle_t* phMetric                   ///< [out] handle of metric
    ){
    // Check parameters
    if( nullptr == hMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetric ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricGet(hMetricGroup, ordinal, phMetric);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGetProperties(
        xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        xet_metric_properties_t* pProperties            ///< [out] metric properties
    ){
    // Check parameters
    if( nullptr == hMetric ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricGetProperties(hMetric, pProperties);
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
    ){
    // Check parameters
    if( nullptr == hMetricGroup ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pReportCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRawData ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pCalculatedData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricGroupCalculateData(hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetDeviceActivateMetricGroups(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        xet_metric_group_handle_t* phMetricGroups       ///< [in] handles of the metric groups to activate. NULL to deactivate.
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricGroups ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetDeviceActivateMetricGroups(hDevice, count, phMetricGroups);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricTracerOpen(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xet_metric_tracer_desc_t* pDesc,                ///< [in,out] metric tracer descriptor
        xe_event_handle_t hNotificationEvent,           ///< [in] event used for report availability notification. Must be device
                                                        ///< to host type.
        xet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hNotificationEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XET_METRIC_TRACER_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xetapi->xetMetricTracerOpen(hDevice, pDesc, hNotificationEvent, phMetricTracer);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricTracerMarker(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetCommandListAppendMetricTracerMarker(hCommandList, hMetricTracer, value);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricTracerClose(
        xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    ){
    // Check parameters
    if( nullptr == hMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricTracerClose(hMetricTracer);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricTracerReadData(
        xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data buffer size
        uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
    ){
    // Check parameters
    if( nullptr == hMetricTracer ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pReportCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRawData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricTracerReadData(hMetricTracer, pReportCount, rawDataSize, pRawData);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryPoolCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
        xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricQueryPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xetapi->xetMetricQueryPoolCreate(hDevice, pDesc, phMetricQueryPool);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryPoolDestroy(
        xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    ){
    // Check parameters
    if( nullptr == hMetricQueryPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricQueryPoolDestroy(hMetricQueryPool);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryPoolGetMetricQuery(
        xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t ordinal,                               ///< [in] index of the query within the pool
        xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    ){
    // Check parameters
    if( nullptr == hMetricQueryPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricQueryPoolGetMetricQuery(hMetricQueryPool, ordinal, phMetricQuery);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetCommandListAppendMetricQueryBegin(hCommandList, hMetricQuery);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hCompletionEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetCommandListAppendMetricQueryEnd(hCommandList, hMetricQuery, hCompletionEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetCommandListAppendMetricMemoryBarrier(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryGetData(
        xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
        uint8_t* pRawData                               ///< [in,out] query result data in raw format
    ){
    // Check parameters
    if( nullptr == hMetricQuery ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pReportCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRawData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xetapi->xetMetricQueryGetData(hMetricQuery, pReportCount, rawDataSize, pRawData);
}

#if defined(__cplusplus)
};
#endif
