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
* @file xe_tools_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/validation.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_layer.h"

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_global_apitable_t* ptable                   ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetGlobal;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnInit                                                 = ptable->pfnInit;
    ptable->pfnInit                                                 = xetInit;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_device_apitable_t* ptable                   ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetDevice;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnActivateMetricGroups                                 = ptable->pfnActivateMetricGroups;
    ptable->pfnActivateMetricGroups                                 = xetDeviceActivateMetricGroups;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_command_list_apitable_t* ptable             ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetCommandList;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnAppendMetricTracerMarker                             = ptable->pfnAppendMetricTracerMarker;
    ptable->pfnAppendMetricTracerMarker                             = xetCommandListAppendMetricTracerMarker;

    mytable.pfnAppendMetricQueryBegin                               = ptable->pfnAppendMetricQueryBegin;
    ptable->pfnAppendMetricQueryBegin                               = xetCommandListAppendMetricQueryBegin;

    mytable.pfnAppendMetricQueryEnd                                 = ptable->pfnAppendMetricQueryEnd;
    ptable->pfnAppendMetricQueryEnd                                 = xetCommandListAppendMetricQueryEnd;

    mytable.pfnAppendMetricMemoryBarrier                            = ptable->pfnAppendMetricMemoryBarrier;
    ptable->pfnAppendMetricMemoryBarrier                            = xetCommandListAppendMetricMemoryBarrier;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_group_apitable_t* ptable             ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetMetricGroup;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnGetCount                                             = ptable->pfnGetCount;
    ptable->pfnGetCount                                             = xetMetricGroupGetCount;

    mytable.pfnGet                                                  = ptable->pfnGet;
    ptable->pfnGet                                                  = xetMetricGroupGet;

    mytable.pfnGetProperties                                        = ptable->pfnGetProperties;
    ptable->pfnGetProperties                                        = xetMetricGroupGetProperties;

    mytable.pfnCalculateData                                        = ptable->pfnCalculateData;
    ptable->pfnCalculateData                                        = xetMetricGroupCalculateData;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_apitable_t* ptable                   ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetMetric;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnGet                                                  = ptable->pfnGet;
    ptable->pfnGet                                                  = xetMetricGet;

    mytable.pfnGetProperties                                        = ptable->pfnGetProperties;
    ptable->pfnGetProperties                                        = xetMetricGetProperties;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricTracerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_tracer_apitable_t* ptable            ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetMetricTracer;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnOpen                                                 = ptable->pfnOpen;
    ptable->pfnOpen                                                 = xetMetricTracerOpen;

    mytable.pfnClose                                                = ptable->pfnClose;
    ptable->pfnClose                                                = xetMetricTracerClose;

    mytable.pfnReadData                                             = ptable->pfnReadData;
    ptable->pfnReadData                                             = xetMetricTracerReadData;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_pool_apitable_t* ptable        ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetMetricQueryPool;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                               = xetMetricQueryPoolCreate;

    mytable.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                              = xetMetricQueryPoolDestroy;

    mytable.pfnGetMetricQuery                                       = ptable->pfnGetMetricQuery;
    ptable->pfnGetMetricQuery                                       = xetMetricQueryPoolGetMetricQuery;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_metric_query_apitable_t* ptable             ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetMetricQuery;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnGetData                                              = ptable->pfnGetData;
    ptable->pfnGetData                                              = xetMetricQueryGetData;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetPowerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_power_apitable_t* ptable                    ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetPower;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                               = xetPowerCreate;

    mytable.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                              = xetPowerDestroy;

    mytable.pfnGetAveragePowerLimit                                 = ptable->pfnGetAveragePowerLimit;
    ptable->pfnGetAveragePowerLimit                                 = xetPowerGetAveragePowerLimit;

    mytable.pfnGetBurstPowerLimit                                   = ptable->pfnGetBurstPowerLimit;
    ptable->pfnGetBurstPowerLimit                                   = xetPowerGetBurstPowerLimit;

    mytable.pfnGetPeakPowerLimit                                    = ptable->pfnGetPeakPowerLimit;
    ptable->pfnGetPeakPowerLimit                                    = xetPowerGetPeakPowerLimit;

    mytable.pfnGetAllPowerLimits                                    = ptable->pfnGetAllPowerLimits;
    ptable->pfnGetAllPowerLimits                                    = xetPowerGetAllPowerLimits;

    mytable.pfnGetDefaultPowerLimits                                = ptable->pfnGetDefaultPowerLimits;
    ptable->pfnGetDefaultPowerLimits                                = xetPowerGetDefaultPowerLimits;

    mytable.pfnSetAveragePowerLimit                                 = ptable->pfnSetAveragePowerLimit;
    ptable->pfnSetAveragePowerLimit                                 = xetPowerSetAveragePowerLimit;

    mytable.pfnSetBurstPowerLimit                                   = ptable->pfnSetBurstPowerLimit;
    ptable->pfnSetBurstPowerLimit                                   = xetPowerSetBurstPowerLimit;

    mytable.pfnSetPeakPowerLimit                                    = ptable->pfnSetPeakPowerLimit;
    ptable->pfnSetPeakPowerLimit                                    = xetPowerSetPeakPowerLimit;

    mytable.pfnSetPowerLimits                                       = ptable->pfnSetPowerLimits;
    ptable->pfnSetPowerLimits                                       = xetPowerSetPowerLimits;

    mytable.pfnGetEnergyCounter                                     = ptable->pfnGetEnergyCounter;
    ptable->pfnGetEnergyCounter                                     = xetPowerGetEnergyCounter;

    mytable.pfnGetTurboMode                                         = ptable->pfnGetTurboMode;
    ptable->pfnGetTurboMode                                         = xetPowerGetTurboMode;

    mytable.pfnSetTurboMode                                         = ptable->pfnSetTurboMode;
    ptable->pfnSetTurboMode                                         = xetPowerSetTurboMode;

    mytable.pfnGetFreqDomainCount                                   = ptable->pfnGetFreqDomainCount;
    ptable->pfnGetFreqDomainCount                                   = xetPowerGetFreqDomainCount;

    mytable.pfnGetFreqDomain                                        = ptable->pfnGetFreqDomain;
    ptable->pfnGetFreqDomain                                        = xetPowerGetFreqDomain;

    mytable.pfnFanCount                                             = ptable->pfnFanCount;
    ptable->pfnFanCount                                             = xetPowerFanCount;

    mytable.pfnFanGetProperties                                     = ptable->pfnFanGetProperties;
    ptable->pfnFanGetProperties                                     = xetPowerFanGetProperties;

    mytable.pfnFanGetSpeedTable                                     = ptable->pfnFanGetSpeedTable;
    ptable->pfnFanGetSpeedTable                                     = xetPowerFanGetSpeedTable;

    mytable.pfnFanSetSpeedTable                                     = ptable->pfnFanSetSpeedTable;
    ptable->pfnFanSetSpeedTable                                     = xetPowerFanSetSpeedTable;

    mytable.pfnFanGetSpeed                                          = ptable->pfnFanGetSpeed;
    ptable->pfnFanGetSpeed                                          = xetPowerFanGetSpeed;

    mytable.pfnFanSetSpeed                                          = ptable->pfnFanSetSpeed;
    ptable->pfnFanSetSpeed                                          = xetPowerFanSetSpeed;

    mytable.pfnTemperatureSensorCount                               = ptable->pfnTemperatureSensorCount;
    ptable->pfnTemperatureSensorCount                               = xetPowerTemperatureSensorCount;

    mytable.pfnGetTemperatureProperties                             = ptable->pfnGetTemperatureProperties;
    ptable->pfnGetTemperatureProperties                             = xetPowerGetTemperatureProperties;

    mytable.pfnGetTemperature                                       = ptable->pfnGetTemperature;
    ptable->pfnGetTemperature                                       = xetPowerGetTemperature;

    mytable.pfnSetTemperatureThreshold                              = ptable->pfnSetTemperatureThreshold;
    ptable->pfnSetTemperatureThreshold                              = xetPowerSetTemperatureThreshold;

    mytable.pfnActivityCount                                        = ptable->pfnActivityCount;
    ptable->pfnActivityCount                                        = xetPowerActivityCount;

    mytable.pfnGetActivityProperties                                = ptable->pfnGetActivityProperties;
    ptable->pfnGetActivityProperties                                = xetPowerGetActivityProperties;

    mytable.pfnGetActivityCounters                                  = ptable->pfnGetActivityCounters;
    ptable->pfnGetActivityCounters                                  = xetPowerGetActivityCounters;

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
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetFreqDomainProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_freq_domain_apitable_t* ptable              ///< [in,out] pointer to table of API function pointers
    )
{
    auto& mytable = xe_layer::val.xetFreqDomain;

#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    mytable.pfnGetProperties                                        = ptable->pfnGetProperties;
    ptable->pfnGetProperties                                        = xetFreqDomainGetProperties;

    mytable.pfnGetSourceFreqDomain                                  = ptable->pfnGetSourceFreqDomain;
    ptable->pfnGetSourceFreqDomain                                  = xetFreqDomainGetSourceFreqDomain;

    mytable.pfnGetSupportedClocks                                   = ptable->pfnGetSupportedClocks;
    ptable->pfnGetSupportedClocks                                   = xetFreqDomainGetSupportedClocks;

    mytable.pfnGetSupportedClockDividers                            = ptable->pfnGetSupportedClockDividers;
    ptable->pfnGetSupportedClockDividers                            = xetFreqDomainGetSupportedClockDividers;

    mytable.pfnGetClockRange                                        = ptable->pfnGetClockRange;
    ptable->pfnGetClockRange                                        = xetFreqDomainGetClockRange;

    mytable.pfnSetClockRange                                        = ptable->pfnSetClockRange;
    ptable->pfnSetClockRange                                        = xetFreqDomainSetClockRange;

    mytable.pfnSetClockDivider                                      = ptable->pfnSetClockDivider;
    ptable->pfnSetClockDivider                                      = xetFreqDomainSetClockDivider;

    mytable.pfnGetCurrentFrequency                                  = ptable->pfnGetCurrentFrequency;
    ptable->pfnGetCurrentFrequency                                  = xetFreqDomainGetCurrentFrequency;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetInit
xe_result_t __xecall
xetInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto pfnInit = xe_layer::val.xetGlobal.pfnInit;

    if( nullptr == pfnInit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
    }

    return pfnInit( flags );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGroupGetCount
xe_result_t __xecall
xetMetricGroupGetCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    )
{
    auto pfnGetCount = xe_layer::val.xetMetricGroup.pfnGetCount;

    if( nullptr == pfnGetCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetCount( hDevice, pCount );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGroupGet
xe_result_t __xecall
xetMetricGroupGet(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t ordinal,                               ///< [in] metric group index
    xet_metric_group_handle_t* phMetricGroup        ///< [out] metric group handle
    )
{
    auto pfnGet = xe_layer::val.xetMetricGroup.pfnGet;

    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phMetricGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGet( hDevice, ordinal, phMetricGroup );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGroupGetProperties
xe_result_t __xecall
xetMetricGroupGetProperties(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    )
{
    auto pfnGetProperties = xe_layer::val.xetMetricGroup.pfnGetProperties;

    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetProperties( hMetricGroup, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGet
xe_result_t __xecall
xetMetricGet(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t ordinal,                               ///< [in] metric index
    xet_metric_handle_t* phMetric                   ///< [out] handle of metric
    )
{
    auto pfnGet = xe_layer::val.xetMetric.pfnGet;

    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phMetric )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGet( hMetricGroup, ordinal, phMetric );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGetProperties
xe_result_t __xecall
xetMetricGetProperties(
    xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    xet_metric_properties_t* pProperties            ///< [out] metric properties
    )
{
    auto pfnGetProperties = xe_layer::val.xetMetric.pfnGetProperties;

    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetric )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetProperties( hMetric, pProperties );
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
    auto pfnCalculateData = xe_layer::val.xetMetricGroup.pfnCalculateData;

    if( nullptr == pfnCalculateData )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pReportCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pRawData )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pCalculatedData )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnCalculateData( hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetDeviceActivateMetricGroups
xe_result_t __xecall
xetDeviceActivateMetricGroups(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    xet_metric_group_handle_t* phMetricGroups       ///< [in][range(0, count)] handles of the metric groups to activate. NULL
                                                    ///< to deactivate.
    )
{
    auto pfnActivateMetricGroups = xe_layer::val.xetDevice.pfnActivateMetricGroups;

    if( nullptr == pfnActivateMetricGroups )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phMetricGroups )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnActivateMetricGroups( hDevice, count, phMetricGroups );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricTracerOpen
xe_result_t __xecall
xetMetricTracerOpen(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xet_metric_tracer_desc_t* pDesc,                ///< [in,out] metric tracer descriptor
    xe_event_handle_t hNotificationEvent,           ///< [in] event used for report availability notification. Must be device
                                                    ///< to host type.
    xet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    )
{
    auto pfnOpen = xe_layer::val.xetMetricTracer.pfnOpen;

    if( nullptr == pfnOpen )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hNotificationEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phMetricTracer )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XET_METRIC_TRACER_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnOpen( hDevice, pDesc, hNotificationEvent, phMetricTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricTracerMarker
xe_result_t __xecall
xetCommandListAppendMetricTracerMarker(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t value                                  ///< [in] tracer marker value
    )
{
    auto pfnAppendMetricTracerMarker = xe_layer::val.xetCommandList.pfnAppendMetricTracerMarker;

    if( nullptr == pfnAppendMetricTracerMarker )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hMetricTracer )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricTracerClose
xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    )
{
    auto pfnClose = xe_layer::val.xetMetricTracer.pfnClose;

    if( nullptr == pfnClose )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricTracer )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnClose( hMetricTracer );
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
    auto pfnReadData = xe_layer::val.xetMetricTracer.pfnReadData;

    if( nullptr == pfnReadData )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricTracer )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pReportCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pRawData )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnReadData( hMetricTracer, pReportCount, rawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricQueryPoolCreate
xe_result_t __xecall
xetMetricQueryPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xet_metric_query_pool_desc_t* pDesc,            ///< [in] metric query pool creation data
    xet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    )
{
    auto pfnCreate = xe_layer::val.xetMetricQueryPool.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phMetricQueryPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hDevice, pDesc, phMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricQueryPoolDestroy
xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    )
{
    auto pfnDestroy = xe_layer::val.xetMetricQueryPool.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricQueryPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hMetricQueryPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricQueryPoolGetMetricQuery
xe_result_t __xecall
xetMetricQueryPoolGetMetricQuery(
    xet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t ordinal,                               ///< [in] index of the query within the pool
    xet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    )
{
    auto pfnGetMetricQuery = xe_layer::val.xetMetricQueryPool.pfnGetMetricQuery;

    if( nullptr == pfnGetMetricQuery )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricQueryPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phMetricQuery )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetMetricQuery( hMetricQueryPool, ordinal, phMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricQueryBegin
xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    auto pfnAppendMetricQueryBegin = xe_layer::val.xetCommandList.pfnAppendMetricQueryBegin;

    if( nullptr == pfnAppendMetricQueryBegin )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hMetricQuery )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricQueryEnd
xe_result_t __xecall
xetCommandListAppendMetricQueryEnd(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    xe_event_handle_t hCompletionEvent              ///< [in] handle of the completion event to signal
    )
{
    auto pfnAppendMetricQueryEnd = xe_layer::val.xetCommandList.pfnAppendMetricQueryEnd;

    if( nullptr == pfnAppendMetricQueryEnd )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hMetricQuery )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hCompletionEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricMemoryBarrier
xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    auto pfnAppendMetricMemoryBarrier = xe_layer::val.xetCommandList.pfnAppendMetricMemoryBarrier;

    if( nullptr == pfnAppendMetricMemoryBarrier )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMetricMemoryBarrier( hCommandList );
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
    auto pfnGetData = xe_layer::val.xetMetricQuery.pfnGetData;

    if( nullptr == pfnGetData )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hMetricQuery )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pReportCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pRawData )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerCreate
xe_result_t __xecall
xetPowerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
    xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
    )
{
    auto pfnCreate = xe_layer::val.xetPower.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pPowerHandle )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnCreate( hDevice, flags, pPowerHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerDestroy
xe_result_t __xecall
xetPowerDestroy(
    xet_power_handle_t hPower                       ///< [in] handle of the power object to destroy
    )
{
    auto pfnDestroy = xe_layer::val.xetPower.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hPower );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetAveragePowerLimit
xe_result_t __xecall
xetPowerGetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
    )
{
    auto pfnGetAveragePowerLimit = xe_layer::val.xetPower.pfnGetAveragePowerLimit;

    if( nullptr == pfnGetAveragePowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetAveragePowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetBurstPowerLimit
xe_result_t __xecall
xetPowerGetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
    )
{
    auto pfnGetBurstPowerLimit = xe_layer::val.xetPower.pfnGetBurstPowerLimit;

    if( nullptr == pfnGetBurstPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetBurstPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetPeakPowerLimit
xe_result_t __xecall
xetPowerGetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
    )
{
    auto pfnGetPeakPowerLimit = xe_layer::val.xetPower.pfnGetPeakPowerLimit;

    if( nullptr == pfnGetPeakPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetPeakPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetAllPowerLimits
xe_result_t __xecall
xetPowerGetAllPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
    )
{
    auto pfnGetAllPowerLimits = xe_layer::val.xetPower.pfnGetAllPowerLimits;

    if( nullptr == pfnGetAllPowerLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimits )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetAllPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetDefaultPowerLimits
xe_result_t __xecall
xetPowerGetDefaultPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
    )
{
    auto pfnGetDefaultPowerLimits = xe_layer::val.xetPower.pfnGetDefaultPowerLimits;

    if( nullptr == pfnGetDefaultPowerLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimits )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetDefaultPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetAveragePowerLimit
xe_result_t __xecall
xetPowerSetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
    )
{
    auto pfnSetAveragePowerLimit = xe_layer::val.xetPower.pfnSetAveragePowerLimit;

    if( nullptr == pfnSetAveragePowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetAveragePowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetBurstPowerLimit
xe_result_t __xecall
xetPowerSetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
    )
{
    auto pfnSetBurstPowerLimit = xe_layer::val.xetPower.pfnSetBurstPowerLimit;

    if( nullptr == pfnSetBurstPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetBurstPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetPeakPowerLimit
xe_result_t __xecall
xetPowerSetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
    )
{
    auto pfnSetPeakPowerLimit = xe_layer::val.xetPower.pfnSetPeakPowerLimit;

    if( nullptr == pfnSetPeakPowerLimit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimit )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetPeakPowerLimit( hPower, pLimit );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetPowerLimits
xe_result_t __xecall
xetPowerSetPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
    )
{
    auto pfnSetPowerLimits = xe_layer::val.xetPower.pfnSetPowerLimits;

    if( nullptr == pfnSetPowerLimits )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLimits )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetPowerLimits( hPower, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetEnergyCounter
xe_result_t __xecall
xetPowerGetEnergyCounter(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
    )
{
    auto pfnGetEnergyCounter = xe_layer::val.xetPower.pfnGetEnergyCounter;

    if( nullptr == pfnGetEnergyCounter )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pEnergy )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetEnergyCounter( hPower, pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetTurboMode
xe_result_t __xecall
xetPowerGetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
    )
{
    auto pfnGetTurboMode = xe_layer::val.xetPower.pfnGetTurboMode;

    if( nullptr == pfnGetTurboMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pTurboMode )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetTurboMode( hPower, pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetTurboMode
xe_result_t __xecall
xetPowerSetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
    )
{
    auto pfnSetTurboMode = xe_layer::val.xetPower.pfnSetTurboMode;

    if( nullptr == pfnSetTurboMode )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetTurboMode( hPower, pTurboMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetFreqDomainCount
xe_result_t __xecall
xetPowerGetFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    )
{
    auto pfnGetFreqDomainCount = xe_layer::val.xetPower.pfnGetFreqDomainCount;

    if( nullptr == pfnGetFreqDomainCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pNumFreqDomains )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetFreqDomainCount( hPower, pNumFreqDomains );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetFreqDomain
xe_result_t __xecall
xetPowerGetFreqDomain(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t ordinal,                               ///< [in] frequency domain index [0 .. ::xetPowerGetFreqDomainCount - 1]
    xet_freq_domain_handle_t* phFreqDomain          ///< [out] pointer to handle of frequency domain object
    )
{
    auto pfnGetFreqDomain = xe_layer::val.xetPower.pfnGetFreqDomain;

    if( nullptr == pfnGetFreqDomain )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetFreqDomain( hPower, ordinal, phFreqDomain );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetFreqDomainGetProperties
xe_result_t __xecall
xetFreqDomainGetProperties(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
    )
{
    auto pfnGetProperties = xe_layer::val.xetFreqDomain.pfnGetProperties;

    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFreqDomainProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetProperties( hFreqDomain, pFreqDomainProperties );
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
    auto pfnGetSourceFreqDomain = xe_layer::val.xetFreqDomain.pfnGetSourceFreqDomain;

    if( nullptr == pfnGetSourceFreqDomain )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phSrcFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetSourceFreqDomain( hFreqDomain, phSrcFreqDomain );
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
    auto pfnGetSupportedClocks = xe_layer::val.xetFreqDomain.pfnGetSupportedClocks;

    if( nullptr == pfnGetSupportedClocks )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pClocks )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetSupportedClocks( hFreqDomain, numClockPoints, pClocks );
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
    auto pfnGetSupportedClockDividers = xe_layer::val.xetFreqDomain.pfnGetSupportedClockDividers;

    if( nullptr == pfnGetSupportedClockDividers )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pDividers )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );
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
    auto pfnGetClockRange = xe_layer::val.xetFreqDomain.pfnGetClockRange;

    if( nullptr == pfnGetClockRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pMinClock )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pMaxClock )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetClockRange( hFreqDomain, pMinClock, pMaxClock );
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
    auto pfnSetClockRange = xe_layer::val.xetFreqDomain.pfnSetClockRange;

    if( nullptr == pfnSetClockRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetClockRange( hFreqDomain, minClock, maxClock );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetFreqDomainSetClockDivider
xe_result_t __xecall
xetFreqDomainSetClockDivider(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
    )
{
    auto pfnSetClockDivider = xe_layer::val.xetFreqDomain.pfnSetClockDivider;

    if( nullptr == pfnSetClockDivider )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pClockDividerRequest )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetClockDivider( hFreqDomain, pClockDividerRequest );
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
    auto pfnGetCurrentFrequency = xe_layer::val.xetFreqDomain.pfnGetCurrentFrequency;

    if( nullptr == pfnGetCurrentFrequency )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFreqDomain )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFreqRequest )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFreqResolved )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFreqThrottleReasons )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetCurrentFrequency( hFreqDomain, pFreqRequest, pFreqResolved, pFreqThrottleReasons );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerFanCount
xe_result_t __xecall
xetPowerFanCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pFanCount                             ///< [out] the number of fans on the device
    )
{
    auto pfnFanCount = xe_layer::val.xetPower.pfnFanCount;

    if( nullptr == pfnFanCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFanCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnFanCount( hPower, pFanCount );
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
    auto pfnFanGetProperties = xe_layer::val.xetPower.pfnFanGetProperties;

    if( nullptr == pfnFanGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFanProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnFanGetProperties( hPower, fanIndex, pFanProperties );
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
    auto pfnFanGetSpeedTable = xe_layer::val.xetPower.pfnFanGetSpeedTable;

    if( nullptr == pfnFanGetSpeedTable )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pNumFanPoints )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFanPoints )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );
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
    auto pfnFanSetSpeedTable = xe_layer::val.xetPower.pfnFanSetSpeedTable;

    if( nullptr == pfnFanSetSpeedTable )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFanPoints )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );
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
    auto pfnFanGetSpeed = xe_layer::val.xetPower.pfnFanGetSpeed;

    if( nullptr == pfnFanGetSpeed )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFanSpeed )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );
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
    auto pfnFanSetSpeed = xe_layer::val.xetPower.pfnFanSetSpeed;

    if( nullptr == pfnFanSetSpeed )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFanSpeed )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerTemperatureSensorCount
xe_result_t __xecall
xetPowerTemperatureSensorCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
    )
{
    auto pfnTemperatureSensorCount = xe_layer::val.xetPower.pfnTemperatureSensorCount;

    if( nullptr == pfnTemperatureSensorCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pSensorCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnTemperatureSensorCount( hPower, pSensorCount );
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
    auto pfnGetTemperatureProperties = xe_layer::val.xetPower.pfnGetTemperatureProperties;

    if( nullptr == pfnGetTemperatureProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetTemperatureProperties( hPower, sensorIndex, pProperties );
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
    auto pfnGetTemperature = xe_layer::val.xetPower.pfnGetTemperature;

    if( nullptr == pfnGetTemperature )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pTemperatures )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );
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
    auto pfnSetTemperatureThreshold = xe_layer::val.xetPower.pfnSetTemperatureThreshold;

    if( nullptr == pfnSetTemperatureThreshold )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerActivityCount
xe_result_t __xecall
xetPowerActivityCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
    )
{
    auto pfnActivityCount = xe_layer::val.xetPower.pfnActivityCount;

    if( nullptr == pfnActivityCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pActivityCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnActivityCount( hPower, pActivityCount );
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
    auto pfnGetActivityProperties = xe_layer::val.xetPower.pfnGetActivityProperties;

    if( nullptr == pfnGetActivityProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetActivityProperties( hPower, activityIndex, pProperties );
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
    auto pfnGetActivityCounters = xe_layer::val.xetPower.pfnGetActivityCounters;

    if( nullptr == pfnGetActivityCounters )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hPower )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pCounters )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );
}

#if defined(__cplusplus)
};
#endif
