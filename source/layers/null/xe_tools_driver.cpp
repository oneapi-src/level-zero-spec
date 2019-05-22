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
* @file xe_tools_driver.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_null.h"

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnInit                                   = xetInit;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnActivateMetricGroups                   = xetDeviceActivateMetricGroups;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnAppendMetricTracerMarker               = xetCommandListAppendMetricTracerMarker;

    pDdiTable->pfnAppendMetricQueryBegin                 = xetCommandListAppendMetricQueryBegin;

    pDdiTable->pfnAppendMetricQueryEnd                   = xetCommandListAppendMetricQueryEnd;

    pDdiTable->pfnAppendMetricMemoryBarrier              = xetCommandListAppendMetricMemoryBarrier;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetCount                               = xetMetricGroupGetCount;

    pDdiTable->pfnGet                                    = xetMetricGroupGet;

    pDdiTable->pfnGetProperties                          = xetMetricGroupGetProperties;

    pDdiTable->pfnCalculateData                          = xetMetricGroupCalculateData;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = xetMetricGet;

    pDdiTable->pfnGetProperties                          = xetMetricGetProperties;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnOpen                                   = xetMetricTracerOpen;

    pDdiTable->pfnClose                                  = xetMetricTracerClose;

    pDdiTable->pfnReadData                               = xetMetricTracerReadData;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xetMetricQueryPoolCreate;

    pDdiTable->pfnDestroy                                = xetMetricQueryPoolDestroy;

    pDdiTable->pfnGetMetricQuery                         = xetMetricQueryPoolGetMetricQuery;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetData                                = xetMetricQueryGetData;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xetPowerCreate;

    pDdiTable->pfnDestroy                                = xetPowerDestroy;

    pDdiTable->pfnGetAveragePowerLimit                   = xetPowerGetAveragePowerLimit;

    pDdiTable->pfnGetBurstPowerLimit                     = xetPowerGetBurstPowerLimit;

    pDdiTable->pfnGetPeakPowerLimit                      = xetPowerGetPeakPowerLimit;

    pDdiTable->pfnGetAllPowerLimits                      = xetPowerGetAllPowerLimits;

    pDdiTable->pfnGetDefaultPowerLimits                  = xetPowerGetDefaultPowerLimits;

    pDdiTable->pfnSetAveragePowerLimit                   = xetPowerSetAveragePowerLimit;

    pDdiTable->pfnSetBurstPowerLimit                     = xetPowerSetBurstPowerLimit;

    pDdiTable->pfnSetPeakPowerLimit                      = xetPowerSetPeakPowerLimit;

    pDdiTable->pfnSetPowerLimits                         = xetPowerSetPowerLimits;

    pDdiTable->pfnGetEnergyCounter                       = xetPowerGetEnergyCounter;

    pDdiTable->pfnGetTurboMode                           = xetPowerGetTurboMode;

    pDdiTable->pfnSetTurboMode                           = xetPowerSetTurboMode;

    pDdiTable->pfnGetFreqDomainCount                     = xetPowerGetFreqDomainCount;

    pDdiTable->pfnGetFreqDomain                          = xetPowerGetFreqDomain;

    pDdiTable->pfnFanCount                               = xetPowerFanCount;

    pDdiTable->pfnFanGetProperties                       = xetPowerFanGetProperties;

    pDdiTable->pfnFanGetSpeedTable                       = xetPowerFanGetSpeedTable;

    pDdiTable->pfnFanSetSpeedTable                       = xetPowerFanSetSpeedTable;

    pDdiTable->pfnFanGetSpeed                            = xetPowerFanGetSpeed;

    pDdiTable->pfnFanSetSpeed                            = xetPowerFanSetSpeed;

    pDdiTable->pfnTemperatureSensorCount                 = xetPowerTemperatureSensorCount;

    pDdiTable->pfnGetTemperatureProperties               = xetPowerGetTemperatureProperties;

    pDdiTable->pfnGetTemperature                         = xetPowerGetTemperature;

    pDdiTable->pfnSetTemperatureThreshold                = xetPowerSetTemperatureThreshold;

    pDdiTable->pfnActivityCount                          = xetPowerActivityCount;

    pDdiTable->pfnGetActivityProperties                  = xetPowerGetActivityProperties;

    pDdiTable->pfnGetActivityCounters                    = xetPowerGetActivityCounters;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = xetFreqDomainGetProperties;

    pDdiTable->pfnGetSourceFreqDomain                    = xetFreqDomainGetSourceFreqDomain;

    pDdiTable->pfnGetSupportedClocks                     = xetFreqDomainGetSupportedClocks;

    pDdiTable->pfnGetSupportedClockDividers              = xetFreqDomainGetSupportedClockDividers;

    pDdiTable->pfnGetClockRange                          = xetFreqDomainGetClockRange;

    pDdiTable->pfnSetClockRange                          = xetFreqDomainSetClockRange;

    pDdiTable->pfnSetClockDivider                        = xetFreqDomainSetClockDivider;

    pDdiTable->pfnGetCurrentFrequency                    = xetFreqDomainGetCurrentFrequency;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetInit
xe_result_t __xecall
xetInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    // global functions need to be handled manually by the driver
    result = driver.xetInit( flags );

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGroupGetCount
xe_result_t __xecall
xetMetricGroupGetCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    *phMetricGroup = reinterpret_cast<xet_metric_group_handle_t>( driver.get() );
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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    *phMetric = reinterpret_cast<xet_metric_handle_t>( driver.get() );
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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    *phMetricTracer = reinterpret_cast<xet_metric_tracer_handle_t>( driver.get() );
    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricTracerClose
xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    *phMetricQueryPool = reinterpret_cast<xet_metric_query_pool_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricQueryPoolDestroy
xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    *phMetricQuery = reinterpret_cast<xet_metric_query_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricQueryBegin
xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricMemoryBarrier
xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    *pPowerHandle = reinterpret_cast<xet_power_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerDestroy
xe_result_t __xecall
xetPowerDestroy(
    xet_power_handle_t hPower                       ///< [in] handle of the power object to destroy
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetFreqDomainCount
xe_result_t __xecall
xetPowerGetFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
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
    xe_result_t result = XE_RESULT_SUCCESS;

    *phFreqDomain = reinterpret_cast<xet_freq_domain_handle_t>( driver.get() );
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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

    *phSrcFreqDomain = reinterpret_cast<xet_freq_domain_handle_t>( driver.get() );
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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

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
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

#if defined(__cplusplus)
};
#endif
