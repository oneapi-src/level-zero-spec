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
#include "tools_loader.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Loads function pointer table for loaded driver
bool xetLoad(
    void* handle,                   ///< [in] driver handle
    xetapi_pfntable_t* pfntable )  ///< [in] pointer to table of xet API function pointers
{
    if(nullptr == pfntable){
        return false;
    }

    pfntable->xetMetricGroupGetCount                                          = (pfn_xetMetricGroupGetCount_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGetCount");
    pfntable->xetMetricGroupGet                                               = (pfn_xetMetricGroupGet_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGet");
    pfntable->xetMetricGroupGetProperties                                     = (pfn_xetMetricGroupGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGetProperties");
    pfntable->xetMetricGet                                                    = (pfn_xetMetricGet_t)LOAD_FUNCTION_PTR(handle, "xetMetricGet");
    pfntable->xetMetricGetProperties                                          = (pfn_xetMetricGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetMetricGetProperties");
    pfntable->xetMetricGroupCalculateData                                     = (pfn_xetMetricGroupCalculateData_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupCalculateData");
    pfntable->xetDeviceActivateMetricGroups                                   = (pfn_xetDeviceActivateMetricGroups_t)LOAD_FUNCTION_PTR(handle, "xetDeviceActivateMetricGroups");
    pfntable->xetMetricTracerOpen                                             = (pfn_xetMetricTracerOpen_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerOpen");
    pfntable->xetCommandListAppendMetricTracerMarker                          = (pfn_xetCommandListAppendMetricTracerMarker_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricTracerMarker");
    pfntable->xetMetricTracerClose                                            = (pfn_xetMetricTracerClose_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerClose");
    pfntable->xetMetricTracerReadData                                         = (pfn_xetMetricTracerReadData_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerReadData");
    pfntable->xetMetricQueryPoolCreate                                        = (pfn_xetMetricQueryPoolCreate_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolCreate");
    pfntable->xetMetricQueryPoolDestroy                                       = (pfn_xetMetricQueryPoolDestroy_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolDestroy");
    pfntable->xetMetricQueryPoolGetMetricQuery                                = (pfn_xetMetricQueryPoolGetMetricQuery_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolGetMetricQuery");
    pfntable->xetCommandListAppendMetricQueryBegin                            = (pfn_xetCommandListAppendMetricQueryBegin_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricQueryBegin");
    pfntable->xetCommandListAppendMetricQueryEnd                              = (pfn_xetCommandListAppendMetricQueryEnd_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricQueryEnd");
    pfntable->xetCommandListAppendMetricMemoryBarrier                         = (pfn_xetCommandListAppendMetricMemoryBarrier_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricMemoryBarrier");
    pfntable->xetMetricQueryGetData                                           = (pfn_xetMetricQueryGetData_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryGetData");

    if(nullptr == pfntable->xetMetricGroupGetCount)
        return false;
    if(nullptr == pfntable->xetMetricGroupGet)
        return false;
    if(nullptr == pfntable->xetMetricGroupGetProperties)
        return false;
    if(nullptr == pfntable->xetMetricGet)
        return false;
    if(nullptr == pfntable->xetMetricGetProperties)
        return false;
    if(nullptr == pfntable->xetMetricGroupCalculateData)
        return false;
    if(nullptr == pfntable->xetDeviceActivateMetricGroups)
        return false;
    if(nullptr == pfntable->xetMetricTracerOpen)
        return false;
    if(nullptr == pfntable->xetCommandListAppendMetricTracerMarker)
        return false;
    if(nullptr == pfntable->xetMetricTracerClose)
        return false;
    if(nullptr == pfntable->xetMetricTracerReadData)
        return false;
    if(nullptr == pfntable->xetMetricQueryPoolCreate)
        return false;
    if(nullptr == pfntable->xetMetricQueryPoolDestroy)
        return false;
    if(nullptr == pfntable->xetMetricQueryPoolGetMetricQuery)
        return false;
    if(nullptr == pfntable->xetCommandListAppendMetricQueryBegin)
        return false;
    if(nullptr == pfntable->xetCommandListAppendMetricQueryEnd)
        return false;
    if(nullptr == pfntable->xetCommandListAppendMetricMemoryBarrier)
        return false;
    if(nullptr == pfntable->xetMetricQueryGetData)
        return false;

    return true;
}

///////////////////////////////////////////////////////////////////////////////
extern context_t context;

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGroupGetCount(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricGroupGetCount(hDevice, pCount);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGroupGet(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t ordinal,                               ///< [in] metric group index
        xet_metric_group_handle_t* phMetricGroup        ///< [out] metric group handle
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricGroupGet(hDevice, ordinal, phMetricGroup);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGroupGetProperties(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricGroupGetProperties(hMetricGroup, pProperties);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGet(
        xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t ordinal,                               ///< [in] metric index
        xet_metric_handle_t* phMetric                   ///< [out] handle of metric
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricGet(hMetricGroup, ordinal, phMetric);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGetProperties(
        xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        xet_metric_properties_t* pProperties            ///< [out] metric properties
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricGetProperties(hMetric, pProperties);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricGroupCalculateData(hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetDeviceActivateMetricGroups(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        xet_metric_group_handle_t* phMetricGroups       ///< [in] handles of the metric groups to activate. NULL to deactivate.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetDeviceActivateMetricGroups(hDevice, count, phMetricGroups);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricTracerOpen(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xet_metric_tracer_desc_t* pDesc,                ///< [in,out] metric tracer descriptor
        xe_event_handle_t hNotificationEvent,           ///< [in] event used for report availability notification. Must be device
                                                        ///< to host type.
        xet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricTracerOpen(hDevice, pDesc, hNotificationEvent, phMetricTracer);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricTracerMarker(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetCommandListAppendMetricTracerMarker(hCommandList, hMetricTracer, value);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricTracerClose(
        xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricTracerClose(hMetricTracer);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricTracerReadData(
        xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data buffer size
        uint8_t* pRawData                               ///< [in,out] raw data buffer for reports
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricTracerReadData(hMetricTracer, pReportCount, rawDataSize, pRawData);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryPoolCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
        xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricQueryPoolCreate(hDevice, pDesc, phMetricQueryPool);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryPoolDestroy(
        xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricQueryPoolDestroy(hMetricQueryPool);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryPoolGetMetricQuery(
        xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t ordinal,                               ///< [in] index of the query within the pool
        xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricQueryPoolGetMetricQuery(hMetricQueryPool, ordinal, phMetricQuery);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetCommandListAppendMetricQueryBegin(hCommandList, hMetricQuery);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetCommandListAppendMetricQueryEnd(hCommandList, hMetricQuery, hCompletionEvent);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetCommandListAppendMetricMemoryBarrier(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryGetData(
        xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        uint32_t* pReportCount,                         ///< [in,out] report count to read/returned
        uint32_t rawDataSize,                           ///< [in] raw data size passed by the user
        uint8_t* pRawData                               ///< [in,out] query result data in raw format
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xetapi->xetMetricQueryGetData(hMetricQuery, pReportCount, rawDataSize, pRawData);
}

#if defined(__cplusplus)
};
#endif
