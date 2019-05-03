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
#include "xet_api.h"
#include "loader.h"

xet_apitable_t xet_apitable = {};

///////////////////////////////////////////////////////////////////////////////
/// @brief Loads function pointer table for loaded driver
bool xetLoadExports(
    void* handle )  ///< [in] driver handle
{
    xet_apitable.pfnMetricGroupGetCount                                  = (xet_pfnMetricGroupGetCount_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGetCount");
    xet_apitable.pfnMetricGroupGet                                       = (xet_pfnMetricGroupGet_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGet");
    xet_apitable.pfnMetricGroupGetProperties                             = (xet_pfnMetricGroupGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupGetProperties");
    xet_apitable.pfnMetricGet                                            = (xet_pfnMetricGet_t)LOAD_FUNCTION_PTR(handle, "xetMetricGet");
    xet_apitable.pfnMetricGetProperties                                  = (xet_pfnMetricGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetMetricGetProperties");
    xet_apitable.pfnMetricGroupCalculateData                             = (xet_pfnMetricGroupCalculateData_t)LOAD_FUNCTION_PTR(handle, "xetMetricGroupCalculateData");
    xet_apitable.pfnDeviceActivateMetricGroups                           = (xet_pfnDeviceActivateMetricGroups_t)LOAD_FUNCTION_PTR(handle, "xetDeviceActivateMetricGroups");
    xet_apitable.pfnMetricTracerOpen                                     = (xet_pfnMetricTracerOpen_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerOpen");
    xet_apitable.pfnCommandListAppendMetricTracerMarker                  = (xet_pfnCommandListAppendMetricTracerMarker_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricTracerMarker");
    xet_apitable.pfnMetricTracerClose                                    = (xet_pfnMetricTracerClose_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerClose");
    xet_apitable.pfnMetricTracerReadData                                 = (xet_pfnMetricTracerReadData_t)LOAD_FUNCTION_PTR(handle, "xetMetricTracerReadData");
    xet_apitable.pfnMetricQueryPoolCreate                                = (xet_pfnMetricQueryPoolCreate_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolCreate");
    xet_apitable.pfnMetricQueryPoolDestroy                               = (xet_pfnMetricQueryPoolDestroy_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolDestroy");
    xet_apitable.pfnMetricQueryPoolGetMetricQuery                        = (xet_pfnMetricQueryPoolGetMetricQuery_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryPoolGetMetricQuery");
    xet_apitable.pfnCommandListAppendMetricQueryBegin                    = (xet_pfnCommandListAppendMetricQueryBegin_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricQueryBegin");
    xet_apitable.pfnCommandListAppendMetricQueryEnd                      = (xet_pfnCommandListAppendMetricQueryEnd_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricQueryEnd");
    xet_apitable.pfnCommandListAppendMetricMemoryBarrier                 = (xet_pfnCommandListAppendMetricMemoryBarrier_t)LOAD_FUNCTION_PTR(handle, "xetCommandListAppendMetricMemoryBarrier");
    xet_apitable.pfnMetricQueryGetData                                   = (xet_pfnMetricQueryGetData_t)LOAD_FUNCTION_PTR(handle, "xetMetricQueryGetData");
    xet_apitable.pfnDevicePowerInit                                      = (xet_pfnDevicePowerInit_t)LOAD_FUNCTION_PTR(handle, "xetDevicePowerInit");
    xet_apitable.pfnPowerShutdown                                        = (xet_pfnPowerShutdown_t)LOAD_FUNCTION_PTR(handle, "xetPowerShutdown");
    xet_apitable.pfnPowerGetAveragePowerLimit                            = (xet_pfnPowerGetAveragePowerLimit_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetAveragePowerLimit");
    xet_apitable.pfnPowerGetBurstPowerLimit                              = (xet_pfnPowerGetBurstPowerLimit_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetBurstPowerLimit");
    xet_apitable.pfnPowerGetPeakPowerLimit                               = (xet_pfnPowerGetPeakPowerLimit_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetPeakPowerLimit");
    xet_apitable.pfnPowerGetAllPowerLimits                               = (xet_pfnPowerGetAllPowerLimits_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetAllPowerLimits");
    xet_apitable.pfnPowerGetDefaultPowerLimits                           = (xet_pfnPowerGetDefaultPowerLimits_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetDefaultPowerLimits");
    xet_apitable.pfnPowerSetAveragePowerLimit                            = (xet_pfnPowerSetAveragePowerLimit_t)LOAD_FUNCTION_PTR(handle, "xetPowerSetAveragePowerLimit");
    xet_apitable.pfnPowerSetBurstPowerLimit                              = (xet_pfnPowerSetBurstPowerLimit_t)LOAD_FUNCTION_PTR(handle, "xetPowerSetBurstPowerLimit");
    xet_apitable.pfnPowerSetPeakPowerLimit                               = (xet_pfnPowerSetPeakPowerLimit_t)LOAD_FUNCTION_PTR(handle, "xetPowerSetPeakPowerLimit");
    xet_apitable.pfnPowerSetPowerLimits                                  = (xet_pfnPowerSetPowerLimits_t)LOAD_FUNCTION_PTR(handle, "xetPowerSetPowerLimits");
    xet_apitable.pfnPowerGetEnergyCounter                                = (xet_pfnPowerGetEnergyCounter_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetEnergyCounter");
    xet_apitable.pfnPowerGetTurboMode                                    = (xet_pfnPowerGetTurboMode_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetTurboMode");
    xet_apitable.pfnPowerSetTurboMode                                    = (xet_pfnPowerSetTurboMode_t)LOAD_FUNCTION_PTR(handle, "xetPowerSetTurboMode");
    xet_apitable.pfnPowerFreqDomainCount                                 = (xet_pfnPowerFreqDomainCount_t)LOAD_FUNCTION_PTR(handle, "xetPowerFreqDomainCount");
    xet_apitable.pfnPowerFreqDomainGetHandle                             = (xet_pfnPowerFreqDomainGetHandle_t)LOAD_FUNCTION_PTR(handle, "xetPowerFreqDomainGetHandle");
    xet_apitable.pfnPowerFreqDomainGetProperties                         = (xet_pfnPowerFreqDomainGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetPowerFreqDomainGetProperties");
    xet_apitable.pfnPowerFreqDomainGetSupportedClocks                    = (xet_pfnPowerFreqDomainGetSupportedClocks_t)LOAD_FUNCTION_PTR(handle, "xetPowerFreqDomainGetSupportedClocks");
    xet_apitable.pfnPowerFreqDomainGetSupportedClockDividers             = (xet_pfnPowerFreqDomainGetSupportedClockDividers_t)LOAD_FUNCTION_PTR(handle, "xetPowerFreqDomainGetSupportedClockDividers");
    xet_apitable.pfnPowerpfnPowerFreqDomainGetClockRange                 = (xet_pfnPowerpfnPowerFreqDomainGetClockRange_t)LOAD_FUNCTION_PTR(handle, "xetPowerxetPowerFreqDomainGetClockRange");
    xet_apitable.pfnPowerpfnPowerFreqDomainSetClockRange                 = (xet_pfnPowerpfnPowerFreqDomainSetClockRange_t)LOAD_FUNCTION_PTR(handle, "xetPowerxetPowerFreqDomainSetClockRange");
    xet_apitable.pfnPowerFreqDomainSetClockDivider                       = (xet_pfnPowerFreqDomainSetClockDivider_t)LOAD_FUNCTION_PTR(handle, "xetPowerFreqDomainSetClockDivider");
    xet_apitable.pfnPowerGetCurrentFrequency                             = (xet_pfnPowerGetCurrentFrequency_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetCurrentFrequency");
    xet_apitable.pfnPowerFanCount                                        = (xet_pfnPowerFanCount_t)LOAD_FUNCTION_PTR(handle, "xetPowerFanCount");
    xet_apitable.pfnPowerFanGetProperties                                = (xet_pfnPowerFanGetProperties_t)LOAD_FUNCTION_PTR(handle, "xetPowerFanGetProperties");
    xet_apitable.pfnPowerFanGetSpeedTable                                = (xet_pfnPowerFanGetSpeedTable_t)LOAD_FUNCTION_PTR(handle, "xetPowerFanGetSpeedTable");
    xet_apitable.pfnPowerFanSetSpeedTable                                = (xet_pfnPowerFanSetSpeedTable_t)LOAD_FUNCTION_PTR(handle, "xetPowerFanSetSpeedTable");
    xet_apitable.pfnPowerFanGetSpeed                                     = (xet_pfnPowerFanGetSpeed_t)LOAD_FUNCTION_PTR(handle, "xetPowerFanGetSpeed");
    xet_apitable.pfnPowerFanSetSpeed                                     = (xet_pfnPowerFanSetSpeed_t)LOAD_FUNCTION_PTR(handle, "xetPowerFanSetSpeed");
    xet_apitable.pfnPowerTemperatureSensorCount                          = (xet_pfnPowerTemperatureSensorCount_t)LOAD_FUNCTION_PTR(handle, "xetPowerTemperatureSensorCount");
    xet_apitable.pfnPowerGetTemperatureProperties                        = (xet_pfnPowerGetTemperatureProperties_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetTemperatureProperties");
    xet_apitable.pfnPowerGetTemperature                                  = (xet_pfnPowerGetTemperature_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetTemperature");
    xet_apitable.pfnPowerSetTemperatureThreshold                         = (xet_pfnPowerSetTemperatureThreshold_t)LOAD_FUNCTION_PTR(handle, "xetPowerSetTemperatureThreshold");
    xet_apitable.pfnPowerActivityCount                                   = (xet_pfnPowerActivityCount_t)LOAD_FUNCTION_PTR(handle, "xetPowerActivityCount");
    xet_apitable.pfnPowerGetActivityProperties                           = (xet_pfnPowerGetActivityProperties_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetActivityProperties");
    xet_apitable.pfnPowerGetActivityCounters                             = (xet_pfnPowerGetActivityCounters_t)LOAD_FUNCTION_PTR(handle, "xetPowerGetActivityCounters");

    if( nullptr == xet_apitable.pfnMetricGroupGetCount )
        return false;
    if( nullptr == xet_apitable.pfnMetricGroupGet )
        return false;
    if( nullptr == xet_apitable.pfnMetricGroupGetProperties )
        return false;
    if( nullptr == xet_apitable.pfnMetricGet )
        return false;
    if( nullptr == xet_apitable.pfnMetricGetProperties )
        return false;
    if( nullptr == xet_apitable.pfnMetricGroupCalculateData )
        return false;
    if( nullptr == xet_apitable.pfnDeviceActivateMetricGroups )
        return false;
    if( nullptr == xet_apitable.pfnMetricTracerOpen )
        return false;
    if( nullptr == xet_apitable.pfnCommandListAppendMetricTracerMarker )
        return false;
    if( nullptr == xet_apitable.pfnMetricTracerClose )
        return false;
    if( nullptr == xet_apitable.pfnMetricTracerReadData )
        return false;
    if( nullptr == xet_apitable.pfnMetricQueryPoolCreate )
        return false;
    if( nullptr == xet_apitable.pfnMetricQueryPoolDestroy )
        return false;
    if( nullptr == xet_apitable.pfnMetricQueryPoolGetMetricQuery )
        return false;
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryBegin )
        return false;
    if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryEnd )
        return false;
    if( nullptr == xet_apitable.pfnCommandListAppendMetricMemoryBarrier )
        return false;
    if( nullptr == xet_apitable.pfnMetricQueryGetData )
        return false;
    if( nullptr == xet_apitable.pfnDevicePowerInit )
        return false;
    if( nullptr == xet_apitable.pfnPowerShutdown )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetAveragePowerLimit )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetBurstPowerLimit )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetPeakPowerLimit )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetAllPowerLimits )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetDefaultPowerLimits )
        return false;
    if( nullptr == xet_apitable.pfnPowerSetAveragePowerLimit )
        return false;
    if( nullptr == xet_apitable.pfnPowerSetBurstPowerLimit )
        return false;
    if( nullptr == xet_apitable.pfnPowerSetPeakPowerLimit )
        return false;
    if( nullptr == xet_apitable.pfnPowerSetPowerLimits )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetEnergyCounter )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetTurboMode )
        return false;
    if( nullptr == xet_apitable.pfnPowerSetTurboMode )
        return false;
    if( nullptr == xet_apitable.pfnPowerFreqDomainCount )
        return false;
    if( nullptr == xet_apitable.pfnPowerFreqDomainGetHandle )
        return false;
    if( nullptr == xet_apitable.pfnPowerFreqDomainGetProperties )
        return false;
    if( nullptr == xet_apitable.pfnPowerFreqDomainGetSupportedClocks )
        return false;
    if( nullptr == xet_apitable.pfnPowerFreqDomainGetSupportedClockDividers )
        return false;
    if( nullptr == xet_apitable.pfnPowerpfnPowerFreqDomainGetClockRange )
        return false;
    if( nullptr == xet_apitable.pfnPowerpfnPowerFreqDomainSetClockRange )
        return false;
    if( nullptr == xet_apitable.pfnPowerFreqDomainSetClockDivider )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetCurrentFrequency )
        return false;
    if( nullptr == xet_apitable.pfnPowerFanCount )
        return false;
    if( nullptr == xet_apitable.pfnPowerFanGetProperties )
        return false;
    if( nullptr == xet_apitable.pfnPowerFanGetSpeedTable )
        return false;
    if( nullptr == xet_apitable.pfnPowerFanSetSpeedTable )
        return false;
    if( nullptr == xet_apitable.pfnPowerFanGetSpeed )
        return false;
    if( nullptr == xet_apitable.pfnPowerFanSetSpeed )
        return false;
    if( nullptr == xet_apitable.pfnPowerTemperatureSensorCount )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetTemperatureProperties )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetTemperature )
        return false;
    if( nullptr == xet_apitable.pfnPowerSetTemperatureThreshold )
        return false;
    if( nullptr == xet_apitable.pfnPowerActivityCount )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetActivityProperties )
        return false;
    if( nullptr == xet_apitable.pfnPowerGetActivityCounters )
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
    return xet_apitable.pfnMetricGroupGet( hDevice, ordinal, phMetricGroup );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGroupGetProperties(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    )
{
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
    return xet_apitable.pfnMetricGet( hMetricGroup, ordinal, phMetric );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricGetProperties(
    xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    xet_metric_properties_t* pProperties            ///< [out] metric properties
    )
{
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
    return xet_apitable.pfnCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    )
{
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
    return xet_apitable.pfnMetricQueryPoolCreate( hDevice, pDesc, phMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    )
{
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
    return xet_apitable.pfnMetricQueryPoolGetMetricQuery( hMetricQueryPool, ordinal, phMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
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
    return xet_apitable.pfnCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
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
    return xet_apitable.pfnMetricQueryGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetDevicePowerInit(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
    xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
    )
{
    return xet_apitable.pfnDevicePowerInit( hDevice, flags, pPowerHandle );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerShutdown(
    xet_power_handle_t hPower                       ///< [in] handle of the power object
    )
{
    return xet_apitable.pfnPowerShutdown( hPower );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
    )
{
    return xet_apitable.pfnPowerGetAveragePowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
    )
{
    return xet_apitable.pfnPowerGetBurstPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
    )
{
    return xet_apitable.pfnPowerGetPeakPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetAllPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
    )
{
    return xet_apitable.pfnPowerGetAllPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetDefaultPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
    )
{
    return xet_apitable.pfnPowerGetDefaultPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerSetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
    )
{
    return xet_apitable.pfnPowerSetAveragePowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerSetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
    )
{
    return xet_apitable.pfnPowerSetBurstPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerSetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
    )
{
    return xet_apitable.pfnPowerSetPeakPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerSetPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
    )
{
    return xet_apitable.pfnPowerSetPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetEnergyCounter(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint64_t* pEnergyMillijoules                    ///< [out] the energy counter in millijoules
    )
{
    return xet_apitable.pfnPowerGetEnergyCounter( hPower, pEnergyMillijoules );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
    )
{
    return xet_apitable.pfnPowerGetTurboMode( hPower, pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerSetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
    )
{
    return xet_apitable.pfnPowerSetTurboMode( hPower, pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    )
{
    return xet_apitable.pfnPowerFreqDomainCount( hPower, pNumFreqDomains );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFreqDomainGetHandle(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t ordinal,                               ///< [in] frequency domain index [0 .. ::xetPowerFreqDomainCount - 1]
    xet_freq_domain_handle_t* phFreqDomain          ///< [out] pointer to handle of frequency domain object
    )
{
    return xet_apitable.pfnPowerFreqDomainGetHandle( hPower, ordinal, phFreqDomain );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFreqDomainGetProperties(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
    )
{
    return xet_apitable.pfnPowerFreqDomainGetProperties( hFreqDomain, pFreqDomainProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFreqDomainGetSupportedClocks(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockPoints,                        ///< [in] number of elements in pClocksMHz
    uint32_t* pClocksMHz                            ///< [out] pointer to array of frequencies
    )
{
    return xet_apitable.pfnPowerFreqDomainGetSupportedClocks( hFreqDomain, numClockPoints, pClocksMHz );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFreqDomainGetSupportedClockDividers(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockDividers,                      ///< [in] number of elements in pDividers
    xet_clock_divider_t* pDividers                  ///< [out] pointer to array of dividers
    )
{
    return xet_apitable.pfnPowerFreqDomainGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerxetPowerFreqDomainGetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pMinClockMHz,                         ///< [out] min clock frequency in units of MHz
    uint32_t* pMaxClockMHz                          ///< [out] max clock frequency in units of MHz
    )
{
    return xet_apitable.pfnPowerpfnPowerFreqDomainGetClockRange( hFreqDomain, pMinClockMHz, pMaxClockMHz );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerxetPowerFreqDomainSetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t minClockMHz,                           ///< [in] min clock frequency in units of MHz
    uint32_t maxClockMHz                            ///< [in] max clock frequency in units of MHz
    )
{
    return xet_apitable.pfnPowerpfnPowerFreqDomainSetClockRange( hFreqDomain, minClockMHz, maxClockMHz );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFreqDomainSetClockDivider(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
    )
{
    return xet_apitable.pfnPowerFreqDomainSetClockDivider( hFreqDomain, pClockDividerRequest );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetCurrentFrequency(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pFreqRequestMHz,                      ///< [out] current frequency in MHz requested by the driver
    uint32_t* pFreqResolvedMHz,                     ///< [out] the actual frequency in MHz
    xet_freq_throttle_reasons_t* pFreqThrottleReasons   ///< [out] the reason the resolved frequency is lower than the request
    )
{
    return xet_apitable.pfnPowerGetCurrentFrequency( hFreqDomain, pFreqRequestMHz, pFreqResolvedMHz, pFreqThrottleReasons );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFanCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pFanCount                             ///< [out] the number of fans on the device
    )
{
    return xet_apitable.pfnPowerFanCount( hPower, pFanCount );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFanGetProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xet_fan_properties_t* pFanProperties            ///< [out] pointer to storage for fan properties
    )
{
    return xet_apitable.pfnPowerFanGetProperties( hPower, fanIndex, pFanProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFanGetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    uint32_t* pNumFanPoints,                        ///< [in/out] input number of elements in pFanSpeedTable array; output
                                                    ///< number of elements returned
    xet_fan_point_t* pFanPoints                     ///< [out] pointer to an array of temperature/fan-speed points
    )
{
    return xet_apitable.pfnPowerFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFanSetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
    xet_fan_point_t* pFanPoints                     ///< [in] pointer to an array of temperature/fan-speed points
    )
{
    return xet_apitable.pfnPowerFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFanGetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    xet_fan_speed_info_t* pFanSpeed                 ///< [out] pointer to an array of current fan speeds
    )
{
    return xet_apitable.pfnPowerFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerFanSetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xet_fan_speed_info_t* pFanSpeed                 ///< [in] pointer to an array of current fan speeds
    )
{
    return xet_apitable.pfnPowerFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerTemperatureSensorCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
    )
{
    return xet_apitable.pfnPowerTemperatureSensorCount( hPower, pSensorCount );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetTemperatureProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    xet_temperature_properties_t* pProperties       ///< [out] pointer to properties for this sensor
    )
{
    return xet_apitable.pfnPowerGetTemperatureProperties( hPower, sensorIndex, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetTemperature(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint32_t numSensors,                            ///< [in] pTemperatures will contain results for sensors index
                                                    ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
    uint16_t* pTemperatures                         ///< [out] pointer to an array of temperatures in units of degrees celsius
    )
{
    return xet_apitable.pfnPowerGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerSetTemperatureThreshold(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                    ///< will be throttled
    )
{
    return xet_apitable.pfnPowerSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerActivityCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
    )
{
    return xet_apitable.pfnPowerActivityCount( hPower, pActivityCount );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetActivityProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t activityIndex,                         ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
    xet_activity_properties_t* pProperties          ///< [out] pointer to properties for this activity counter
    )
{
    return xet_apitable.pfnPowerGetActivityProperties( hPower, activityIndex, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xetPowerGetActivityCounters(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
    uint32_t numCounters,                           ///< [in] pCounters will contain results for activity counter index
                                                    ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
    xet_activity_counters_t* pCounters              ///< [out] pointer to an array of activity counter data
    )
{
    return xet_apitable.pfnPowerGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );
}

#if defined(__cplusplus)
};
#endif
