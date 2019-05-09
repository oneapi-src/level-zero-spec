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
* DO NOT EDIT: generated from /scripts/templates/validation.cpp.mako
* @endcond
*
******************************************************************************/
#include "xet_api.h"
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
    if( nullptr == original->pfnMetricGroupGet )
        return false;
    if( nullptr == original->pfnMetricGroupGetProperties )
        return false;
    if( nullptr == original->pfnMetricGet )
        return false;
    if( nullptr == original->pfnMetricGetProperties )
        return false;
    if( nullptr == original->pfnMetricGroupCalculateData )
        return false;
    if( nullptr == original->pfnDeviceActivateMetricGroups )
        return false;
    if( nullptr == original->pfnMetricTracerOpen )
        return false;
    if( nullptr == original->pfnCommandListAppendMetricTracerMarker )
        return false;
    if( nullptr == original->pfnMetricTracerClose )
        return false;
    if( nullptr == original->pfnMetricTracerReadData )
        return false;
    if( nullptr == original->pfnMetricQueryPoolCreate )
        return false;
    if( nullptr == original->pfnMetricQueryPoolDestroy )
        return false;
    if( nullptr == original->pfnMetricQueryPoolGetMetricQuery )
        return false;
    if( nullptr == original->pfnCommandListAppendMetricQueryBegin )
        return false;
    if( nullptr == original->pfnCommandListAppendMetricQueryEnd )
        return false;
    if( nullptr == original->pfnCommandListAppendMetricMemoryBarrier )
        return false;
    if( nullptr == original->pfnMetricQueryGetData )
        return false;
    if( nullptr == original->pfnPowerCreate )
        return false;
    if( nullptr == original->pfnPowerDestroy )
        return false;
    if( nullptr == original->pfnPowerGetAveragePowerLimit )
        return false;
    if( nullptr == original->pfnPowerGetBurstPowerLimit )
        return false;
    if( nullptr == original->pfnPowerGetPeakPowerLimit )
        return false;
    if( nullptr == original->pfnPowerGetAllPowerLimits )
        return false;
    if( nullptr == original->pfnPowerGetDefaultPowerLimits )
        return false;
    if( nullptr == original->pfnPowerSetAveragePowerLimit )
        return false;
    if( nullptr == original->pfnPowerSetBurstPowerLimit )
        return false;
    if( nullptr == original->pfnPowerSetPeakPowerLimit )
        return false;
    if( nullptr == original->pfnPowerSetPowerLimits )
        return false;
    if( nullptr == original->pfnPowerGetEnergyCounter )
        return false;
    if( nullptr == original->pfnPowerGetTurboMode )
        return false;
    if( nullptr == original->pfnPowerSetTurboMode )
        return false;
    if( nullptr == original->pfnPowerGetFreqDomainCount )
        return false;
    if( nullptr == original->pfnPowerGetFreqDomainHandle )
        return false;
    if( nullptr == original->pfnFreqDomainGetProperties )
        return false;
    if( nullptr == original->pfnFreqDomainGetSourceFreqDomain )
        return false;
    if( nullptr == original->pfnFreqDomainGetSupportedClocks )
        return false;
    if( nullptr == original->pfnFreqDomainGetSupportedClockDividers )
        return false;
    if( nullptr == original->pfnFreqDomainGetClockRange )
        return false;
    if( nullptr == original->pfnFreqDomainSetClockRange )
        return false;
    if( nullptr == original->pfnFreqDomainSetClockDivider )
        return false;
    if( nullptr == original->pfnFreqDomainGetCurrentFrequency )
        return false;
    if( nullptr == original->pfnPowerFanCount )
        return false;
    if( nullptr == original->pfnPowerFanGetProperties )
        return false;
    if( nullptr == original->pfnPowerFanGetSpeedTable )
        return false;
    if( nullptr == original->pfnPowerFanSetSpeedTable )
        return false;
    if( nullptr == original->pfnPowerFanGetSpeed )
        return false;
    if( nullptr == original->pfnPowerFanSetSpeed )
        return false;
    if( nullptr == original->pfnPowerTemperatureSensorCount )
        return false;
    if( nullptr == original->pfnPowerGetTemperatureProperties )
        return false;
    if( nullptr == original->pfnPowerGetTemperature )
        return false;
    if( nullptr == original->pfnPowerSetTemperatureThreshold )
        return false;
    if( nullptr == original->pfnPowerActivityCount )
        return false;
    if( nullptr == original->pfnPowerGetActivityProperties )
        return false;
    if( nullptr == original->pfnPowerGetActivityCounters )
        return false;

    xet_apitable.pfnMetricGroupGetCount                                  = original->pfnMetricGroupGetCount;
    original->pfnMetricGroupGetCount                                     = xetMetricGroupGetCount;

    xet_apitable.pfnMetricGroupGet                                       = original->pfnMetricGroupGet;
    original->pfnMetricGroupGet                                          = xetMetricGroupGet;

    xet_apitable.pfnMetricGroupGetProperties                             = original->pfnMetricGroupGetProperties;
    original->pfnMetricGroupGetProperties                                = xetMetricGroupGetProperties;

    xet_apitable.pfnMetricGet                                            = original->pfnMetricGet;
    original->pfnMetricGet                                               = xetMetricGet;

    xet_apitable.pfnMetricGetProperties                                  = original->pfnMetricGetProperties;
    original->pfnMetricGetProperties                                     = xetMetricGetProperties;

    xet_apitable.pfnMetricGroupCalculateData                             = original->pfnMetricGroupCalculateData;
    original->pfnMetricGroupCalculateData                                = xetMetricGroupCalculateData;

    xet_apitable.pfnDeviceActivateMetricGroups                           = original->pfnDeviceActivateMetricGroups;
    original->pfnDeviceActivateMetricGroups                              = xetDeviceActivateMetricGroups;

    xet_apitable.pfnMetricTracerOpen                                     = original->pfnMetricTracerOpen;
    original->pfnMetricTracerOpen                                        = xetMetricTracerOpen;

    xet_apitable.pfnCommandListAppendMetricTracerMarker                  = original->pfnCommandListAppendMetricTracerMarker;
    original->pfnCommandListAppendMetricTracerMarker                     = xetCommandListAppendMetricTracerMarker;

    xet_apitable.pfnMetricTracerClose                                    = original->pfnMetricTracerClose;
    original->pfnMetricTracerClose                                       = xetMetricTracerClose;

    xet_apitable.pfnMetricTracerReadData                                 = original->pfnMetricTracerReadData;
    original->pfnMetricTracerReadData                                    = xetMetricTracerReadData;

    xet_apitable.pfnMetricQueryPoolCreate                                = original->pfnMetricQueryPoolCreate;
    original->pfnMetricQueryPoolCreate                                   = xetMetricQueryPoolCreate;

    xet_apitable.pfnMetricQueryPoolDestroy                               = original->pfnMetricQueryPoolDestroy;
    original->pfnMetricQueryPoolDestroy                                  = xetMetricQueryPoolDestroy;

    xet_apitable.pfnMetricQueryPoolGetMetricQuery                        = original->pfnMetricQueryPoolGetMetricQuery;
    original->pfnMetricQueryPoolGetMetricQuery                           = xetMetricQueryPoolGetMetricQuery;

    xet_apitable.pfnCommandListAppendMetricQueryBegin                    = original->pfnCommandListAppendMetricQueryBegin;
    original->pfnCommandListAppendMetricQueryBegin                       = xetCommandListAppendMetricQueryBegin;

    xet_apitable.pfnCommandListAppendMetricQueryEnd                      = original->pfnCommandListAppendMetricQueryEnd;
    original->pfnCommandListAppendMetricQueryEnd                         = xetCommandListAppendMetricQueryEnd;

    xet_apitable.pfnCommandListAppendMetricMemoryBarrier                 = original->pfnCommandListAppendMetricMemoryBarrier;
    original->pfnCommandListAppendMetricMemoryBarrier                    = xetCommandListAppendMetricMemoryBarrier;

    xet_apitable.pfnMetricQueryGetData                                   = original->pfnMetricQueryGetData;
    original->pfnMetricQueryGetData                                      = xetMetricQueryGetData;

    xet_apitable.pfnPowerCreate                                          = original->pfnPowerCreate;
    original->pfnPowerCreate                                             = xetPowerCreate;

    xet_apitable.pfnPowerDestroy                                         = original->pfnPowerDestroy;
    original->pfnPowerDestroy                                            = xetPowerDestroy;

    xet_apitable.pfnPowerGetAveragePowerLimit                            = original->pfnPowerGetAveragePowerLimit;
    original->pfnPowerGetAveragePowerLimit                               = xetPowerGetAveragePowerLimit;

    xet_apitable.pfnPowerGetBurstPowerLimit                              = original->pfnPowerGetBurstPowerLimit;
    original->pfnPowerGetBurstPowerLimit                                 = xetPowerGetBurstPowerLimit;

    xet_apitable.pfnPowerGetPeakPowerLimit                               = original->pfnPowerGetPeakPowerLimit;
    original->pfnPowerGetPeakPowerLimit                                  = xetPowerGetPeakPowerLimit;

    xet_apitable.pfnPowerGetAllPowerLimits                               = original->pfnPowerGetAllPowerLimits;
    original->pfnPowerGetAllPowerLimits                                  = xetPowerGetAllPowerLimits;

    xet_apitable.pfnPowerGetDefaultPowerLimits                           = original->pfnPowerGetDefaultPowerLimits;
    original->pfnPowerGetDefaultPowerLimits                              = xetPowerGetDefaultPowerLimits;

    xet_apitable.pfnPowerSetAveragePowerLimit                            = original->pfnPowerSetAveragePowerLimit;
    original->pfnPowerSetAveragePowerLimit                               = xetPowerSetAveragePowerLimit;

    xet_apitable.pfnPowerSetBurstPowerLimit                              = original->pfnPowerSetBurstPowerLimit;
    original->pfnPowerSetBurstPowerLimit                                 = xetPowerSetBurstPowerLimit;

    xet_apitable.pfnPowerSetPeakPowerLimit                               = original->pfnPowerSetPeakPowerLimit;
    original->pfnPowerSetPeakPowerLimit                                  = xetPowerSetPeakPowerLimit;

    xet_apitable.pfnPowerSetPowerLimits                                  = original->pfnPowerSetPowerLimits;
    original->pfnPowerSetPowerLimits                                     = xetPowerSetPowerLimits;

    xet_apitable.pfnPowerGetEnergyCounter                                = original->pfnPowerGetEnergyCounter;
    original->pfnPowerGetEnergyCounter                                   = xetPowerGetEnergyCounter;

    xet_apitable.pfnPowerGetTurboMode                                    = original->pfnPowerGetTurboMode;
    original->pfnPowerGetTurboMode                                       = xetPowerGetTurboMode;

    xet_apitable.pfnPowerSetTurboMode                                    = original->pfnPowerSetTurboMode;
    original->pfnPowerSetTurboMode                                       = xetPowerSetTurboMode;

    xet_apitable.pfnPowerGetFreqDomainCount                              = original->pfnPowerGetFreqDomainCount;
    original->pfnPowerGetFreqDomainCount                                 = xetPowerGetFreqDomainCount;

    xet_apitable.pfnPowerGetFreqDomainHandle                             = original->pfnPowerGetFreqDomainHandle;
    original->pfnPowerGetFreqDomainHandle                                = xetPowerGetFreqDomainHandle;

    xet_apitable.pfnFreqDomainGetProperties                              = original->pfnFreqDomainGetProperties;
    original->pfnFreqDomainGetProperties                                 = xetFreqDomainGetProperties;

    xet_apitable.pfnFreqDomainGetSourceFreqDomain                        = original->pfnFreqDomainGetSourceFreqDomain;
    original->pfnFreqDomainGetSourceFreqDomain                           = xetFreqDomainGetSourceFreqDomain;

    xet_apitable.pfnFreqDomainGetSupportedClocks                         = original->pfnFreqDomainGetSupportedClocks;
    original->pfnFreqDomainGetSupportedClocks                            = xetFreqDomainGetSupportedClocks;

    xet_apitable.pfnFreqDomainGetSupportedClockDividers                  = original->pfnFreqDomainGetSupportedClockDividers;
    original->pfnFreqDomainGetSupportedClockDividers                     = xetFreqDomainGetSupportedClockDividers;

    xet_apitable.pfnFreqDomainGetClockRange                              = original->pfnFreqDomainGetClockRange;
    original->pfnFreqDomainGetClockRange                                 = xetFreqDomainGetClockRange;

    xet_apitable.pfnFreqDomainSetClockRange                              = original->pfnFreqDomainSetClockRange;
    original->pfnFreqDomainSetClockRange                                 = xetFreqDomainSetClockRange;

    xet_apitable.pfnFreqDomainSetClockDivider                            = original->pfnFreqDomainSetClockDivider;
    original->pfnFreqDomainSetClockDivider                               = xetFreqDomainSetClockDivider;

    xet_apitable.pfnFreqDomainGetCurrentFrequency                        = original->pfnFreqDomainGetCurrentFrequency;
    original->pfnFreqDomainGetCurrentFrequency                           = xetFreqDomainGetCurrentFrequency;

    xet_apitable.pfnPowerFanCount                                        = original->pfnPowerFanCount;
    original->pfnPowerFanCount                                           = xetPowerFanCount;

    xet_apitable.pfnPowerFanGetProperties                                = original->pfnPowerFanGetProperties;
    original->pfnPowerFanGetProperties                                   = xetPowerFanGetProperties;

    xet_apitable.pfnPowerFanGetSpeedTable                                = original->pfnPowerFanGetSpeedTable;
    original->pfnPowerFanGetSpeedTable                                   = xetPowerFanGetSpeedTable;

    xet_apitable.pfnPowerFanSetSpeedTable                                = original->pfnPowerFanSetSpeedTable;
    original->pfnPowerFanSetSpeedTable                                   = xetPowerFanSetSpeedTable;

    xet_apitable.pfnPowerFanGetSpeed                                     = original->pfnPowerFanGetSpeed;
    original->pfnPowerFanGetSpeed                                        = xetPowerFanGetSpeed;

    xet_apitable.pfnPowerFanSetSpeed                                     = original->pfnPowerFanSetSpeed;
    original->pfnPowerFanSetSpeed                                        = xetPowerFanSetSpeed;

    xet_apitable.pfnPowerTemperatureSensorCount                          = original->pfnPowerTemperatureSensorCount;
    original->pfnPowerTemperatureSensorCount                             = xetPowerTemperatureSensorCount;

    xet_apitable.pfnPowerGetTemperatureProperties                        = original->pfnPowerGetTemperatureProperties;
    original->pfnPowerGetTemperatureProperties                           = xetPowerGetTemperatureProperties;

    xet_apitable.pfnPowerGetTemperature                                  = original->pfnPowerGetTemperature;
    original->pfnPowerGetTemperature                                     = xetPowerGetTemperature;

    xet_apitable.pfnPowerSetTemperatureThreshold                         = original->pfnPowerSetTemperatureThreshold;
    original->pfnPowerSetTemperatureThreshold                            = xetPowerSetTemperatureThreshold;

    xet_apitable.pfnPowerActivityCount                                   = original->pfnPowerActivityCount;
    original->pfnPowerActivityCount                                      = xetPowerActivityCount;

    xet_apitable.pfnPowerGetActivityProperties                           = original->pfnPowerGetActivityProperties;
    original->pfnPowerGetActivityProperties                              = xetPowerGetActivityProperties;

    xet_apitable.pfnPowerGetActivityCounters                             = original->pfnPowerGetActivityCounters;
    original->pfnPowerGetActivityCounters                                = xetPowerGetActivityCounters;

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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricGroupGetCount )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricGroupGet )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phMetricGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnMetricGroupGet( hDevice, ordinal, phMetricGroup );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGroupGetProperties(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricGroupGetProperties )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricGet )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phMetric )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnMetricGet( hMetricGroup, ordinal, phMetric );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricGetProperties(
    xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    xet_metric_properties_t* pProperties            ///< [out] metric properties
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricGetProperties )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetric )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricGroupCalculateData )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pReportCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pRawData )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pCalculatedData )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnDeviceActivateMetricGroups )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phMetricGroups )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricTracerOpen )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hNotificationEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phMetricTracer )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XET_METRIC_TRACER_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnCommandListAppendMetricTracerMarker )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hMetricTracer )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricTracerClose )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricTracer )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricTracerReadData )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricTracer )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pReportCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pRawData )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricQueryPoolCreate )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phMetricQueryPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }
    return xet_apitable.pfnMetricQueryPoolCreate( hDevice, pDesc, phMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricQueryPoolDestroy )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricQueryPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricQueryPoolGetMetricQuery )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricQueryPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phMetricQuery )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnMetricQueryPoolGetMetricQuery( hMetricQueryPool, ordinal, phMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryBegin )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hMetricQuery )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnCommandListAppendMetricQueryEnd )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hMetricQuery )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hCompletionEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnCommandListAppendMetricMemoryBarrier )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnMetricQueryGetData )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hMetricQuery )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pReportCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pRawData )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnMetricQueryGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
    xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerCreate )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pPowerHandle )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerCreate( hDevice, flags, pPowerHandle );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerDestroy(
    xet_power_handle_t hPower                       ///< [in] handle of the power object to destroy
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerDestroy )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerDestroy( hPower );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetAveragePowerLimit )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetAveragePowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetBurstPowerLimit )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetBurstPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetPeakPowerLimit )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetPeakPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetAllPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetAllPowerLimits )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimits )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetAllPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetDefaultPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetDefaultPowerLimits )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimits )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetDefaultPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerSetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerSetAveragePowerLimit )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerSetAveragePowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerSetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerSetBurstPowerLimit )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerSetBurstPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerSetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerSetPeakPowerLimit )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerSetPeakPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerSetPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerSetPowerLimits )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLimits )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerSetPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetEnergyCounter(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetEnergyCounter )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pEnergy )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetEnergyCounter( hPower, pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetTurboMode )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pTurboMode )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetTurboMode( hPower, pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerSetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerSetTurboMode )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerSetTurboMode( hPower, pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetFreqDomainCount )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pNumFreqDomains )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetFreqDomainCount( hPower, pNumFreqDomains );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetFreqDomainHandle(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t ordinal,                               ///< [in] frequency domain index [0 .. ::xetPowerGetFreqDomainCount - 1]
    xet_freq_domain_handle_t* phFreqDomain          ///< [out] pointer to handle of frequency domain object
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetFreqDomainHandle )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetFreqDomainHandle( hPower, ordinal, phFreqDomain );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainGetProperties(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainGetProperties )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFreqDomainProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainGetProperties( hFreqDomain, pFreqDomainProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainGetSourceFreqDomain(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_handle_t* phSrcFreqDomain       ///< [out] pointer to a handle where the source frequency domain handle
                                                    ///< will be returned
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainGetSourceFreqDomain )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phSrcFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainGetSourceFreqDomain( hFreqDomain, phSrcFreqDomain );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainGetSupportedClocks(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockPoints,                        ///< [in] number of elements in pClocks
    uint32_t* pClocks                               ///< [out] pointer to array of frequencies
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainGetSupportedClocks )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pClocks )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainGetSupportedClocks( hFreqDomain, numClockPoints, pClocks );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainGetSupportedClockDividers(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockDividers,                      ///< [in] number of elements in pDividers
    xet_clock_divider_t* pDividers                  ///< [out] pointer to array of dividers
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainGetSupportedClockDividers )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pDividers )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainGetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pMinClock,                            ///< [out] min clock frequency in units of MHz
    uint32_t* pMaxClock                             ///< [out] max clock frequency in units of MHz
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainGetClockRange )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pMinClock )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pMaxClock )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainGetClockRange( hFreqDomain, pMinClock, pMaxClock );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainSetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t minClock,                              ///< [in] min clock frequency in units of MHz
    uint32_t maxClock                               ///< [in] max clock frequency in units of MHz
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainSetClockRange )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainSetClockRange( hFreqDomain, minClock, maxClock );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainSetClockDivider(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainSetClockDivider )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pClockDividerRequest )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainSetClockDivider( hFreqDomain, pClockDividerRequest );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetFreqDomainGetCurrentFrequency(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pFreqRequest,                         ///< [out] current frequency in MHz requested by the driver
    uint32_t* pFreqResolved,                        ///< [out] the actual frequency in MHz
    xet_freq_throttle_reasons_t* pFreqThrottleReasons   ///< [out] the reason the resolved frequency is lower than the request
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnFreqDomainGetCurrentFrequency )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFreqRequest )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFreqResolved )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFreqThrottleReasons )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnFreqDomainGetCurrentFrequency( hFreqDomain, pFreqRequest, pFreqResolved, pFreqThrottleReasons );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerFanCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pFanCount                             ///< [out] the number of fans on the device
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerFanCount )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFanCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerFanCount( hPower, pFanCount );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerFanGetProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xet_fan_properties_t* pFanProperties            ///< [out] pointer to storage for fan properties
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerFanGetProperties )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFanProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerFanGetProperties( hPower, fanIndex, pFanProperties );
}

///////////////////////////////////////////////////////////////////////////////
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerFanGetSpeedTable )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pNumFanPoints )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFanPoints )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerFanSetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
    xet_fan_point_t* pFanPoints                     ///< [in] pointer to an array of temperature/fan-speed points
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerFanSetSpeedTable )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFanPoints )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );
}

///////////////////////////////////////////////////////////////////////////////
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
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerFanGetSpeed )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFanSpeed )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerFanSetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xet_fan_speed_info_t* pFanSpeed                 ///< [in] pointer to an array of current fan speeds
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerFanSetSpeed )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFanSpeed )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerTemperatureSensorCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerTemperatureSensorCount )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pSensorCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerTemperatureSensorCount( hPower, pSensorCount );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetTemperatureProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    xet_temperature_properties_t* pProperties       ///< [out] pointer to properties for this sensor
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetTemperatureProperties )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetTemperatureProperties( hPower, sensorIndex, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetTemperature(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint32_t numSensors,                            ///< [in] pTemperatures will contain results for sensors index
                                                    ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
    uint16_t* pTemperatures                         ///< [out] pointer to an array of temperatures in units of degrees celsius
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetTemperature )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pTemperatures )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerSetTemperatureThreshold(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                    ///< will be throttled
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerSetTemperatureThreshold )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerActivityCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerActivityCount )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pActivityCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerActivityCount( hPower, pActivityCount );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetActivityProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t activityIndex,                         ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
    xet_activity_properties_t* pProperties          ///< [out] pointer to properties for this activity counter
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetActivityProperties )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetActivityProperties( hPower, activityIndex, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xetPowerGetActivityCounters(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
    uint32_t numCounters,                           ///< [in] pCounters will contain results for activity counter index
                                                    ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
    xet_activity_counters_t* pCounters              ///< [out] pointer to an array of activity counter data
    )
{
    if( xe_validation_enables.ParameterValidation )
    {
        if( nullptr == xet_apitable.pfnPowerGetActivityCounters )
            return XE_RESULT_ERROR_UNINITIALIZED;

        // Check parameters
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pCounters )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }
    return xet_apitable.pfnPowerGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );
}

#if defined(__cplusplus)
};
#endif
