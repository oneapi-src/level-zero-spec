/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
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
*
* @file xet_api.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools
* @endcond
*
******************************************************************************/
#ifndef _XET_API_H
#define _XET_API_H
#if defined(__cplusplus)
#pragma once
#endif

#include "xet_device.h"
#include "xet_cmdlist.h"
#include "xet_gtpin.h"
#include "xet_metric.h"
#include "xet_power.h"
#include "xet_sysman.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _xet_device_apitable_t
{
    xet_pfnDeviceActivateMetricGroups_t                         pfnActivateMetricGroups;
} xet_device_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetDeviceProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_device_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetDeviceProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetDeviceProcAddrTable_t)(
    xe_api_version_t,
    xet_device_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _xet_command_list_apitable_t
{
    xet_pfnCommandListAppendMetricTracerMarker_t                pfnAppendMetricTracerMarker;
    xet_pfnCommandListAppendMetricQueryBegin_t                  pfnAppendMetricQueryBegin;
    xet_pfnCommandListAppendMetricQueryEnd_t                    pfnAppendMetricQueryEnd;
    xet_pfnCommandListAppendMetricMemoryBarrier_t               pfnAppendMetricMemoryBarrier;
} xet_command_list_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetCommandListProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_command_list_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetCommandListProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetCommandListProcAddrTable_t)(
    xe_api_version_t,
    xet_command_list_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricGroup functions pointers
typedef struct _xet_metric_group_apitable_t
{
    xet_pfnMetricGroupGetCount_t                                pfnGetCount;
    xet_pfnMetricGroupGet_t                                     pfnGet;
    xet_pfnMetricGroupGetProperties_t                           pfnGetProperties;
    xet_pfnMetricGroupCalculateData_t                           pfnCalculateData;
} xet_metric_group_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricGroupProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_metric_group_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricGroupProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricGroupProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_group_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Metric functions pointers
typedef struct _xet_metric_apitable_t
{
    xet_pfnMetricGet_t                                          pfnGet;
    xet_pfnMetricGetProperties_t                                pfnGetProperties;
} xet_metric_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_metric_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricTracer functions pointers
typedef struct _xet_metric_tracer_apitable_t
{
    xet_pfnMetricTracerOpen_t                                   pfnOpen;
    xet_pfnMetricTracerClose_t                                  pfnClose;
    xet_pfnMetricTracerReadData_t                               pfnReadData;
} xet_metric_tracer_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricTracerProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_metric_tracer_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricTracerProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricTracerProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_tracer_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQueryPool functions pointers
typedef struct _xet_metric_query_pool_apitable_t
{
    xet_pfnMetricQueryPoolCreate_t                              pfnCreate;
    xet_pfnMetricQueryPoolDestroy_t                             pfnDestroy;
    xet_pfnMetricQueryPoolGetMetricQuery_t                      pfnGetMetricQuery;
} xet_metric_query_pool_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryPoolProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_metric_query_pool_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricQueryPoolProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricQueryPoolProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_query_pool_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQuery functions pointers
typedef struct _xet_metric_query_apitable_t
{
    xet_pfnMetricQueryGetData_t                                 pfnGetData;
} xet_metric_query_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetMetricQueryProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_metric_query_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetMetricQueryProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetMetricQueryProcAddrTable_t)(
    xe_api_version_t,
    xet_metric_query_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Power functions pointers
typedef struct _xet_power_apitable_t
{
    xet_pfnPowerCreate_t                                        pfnCreate;
    xet_pfnPowerDestroy_t                                       pfnDestroy;
    xet_pfnPowerGetAveragePowerLimit_t                          pfnGetAveragePowerLimit;
    xet_pfnPowerGetBurstPowerLimit_t                            pfnGetBurstPowerLimit;
    xet_pfnPowerGetPeakPowerLimit_t                             pfnGetPeakPowerLimit;
    xet_pfnPowerGetAllPowerLimits_t                             pfnGetAllPowerLimits;
    xet_pfnPowerGetDefaultPowerLimits_t                         pfnGetDefaultPowerLimits;
    xet_pfnPowerSetAveragePowerLimit_t                          pfnSetAveragePowerLimit;
    xet_pfnPowerSetBurstPowerLimit_t                            pfnSetBurstPowerLimit;
    xet_pfnPowerSetPeakPowerLimit_t                             pfnSetPeakPowerLimit;
    xet_pfnPowerSetPowerLimits_t                                pfnSetPowerLimits;
    xet_pfnPowerGetEnergyCounter_t                              pfnGetEnergyCounter;
    xet_pfnPowerGetTurboMode_t                                  pfnGetTurboMode;
    xet_pfnPowerSetTurboMode_t                                  pfnSetTurboMode;
    xet_pfnPowerGetFreqDomainCount_t                            pfnGetFreqDomainCount;
    xet_pfnPowerGetFreqDomain_t                                 pfnGetFreqDomain;
    xet_pfnPowerFanCount_t                                      pfnFanCount;
    xet_pfnPowerFanGetProperties_t                              pfnFanGetProperties;
    xet_pfnPowerFanGetSpeedTable_t                              pfnFanGetSpeedTable;
    xet_pfnPowerFanSetSpeedTable_t                              pfnFanSetSpeedTable;
    xet_pfnPowerFanGetSpeed_t                                   pfnFanGetSpeed;
    xet_pfnPowerFanSetSpeed_t                                   pfnFanSetSpeed;
    xet_pfnPowerTemperatureSensorCount_t                        pfnTemperatureSensorCount;
    xet_pfnPowerGetTemperatureProperties_t                      pfnGetTemperatureProperties;
    xet_pfnPowerGetTemperature_t                                pfnGetTemperature;
    xet_pfnPowerSetTemperatureThreshold_t                       pfnSetTemperatureThreshold;
    xet_pfnPowerActivityCount_t                                 pfnActivityCount;
    xet_pfnPowerGetActivityProperties_t                         pfnGetActivityProperties;
    xet_pfnPowerGetActivityCounters_t                           pfnGetActivityCounters;
} xet_power_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetPowerProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_power_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetPowerProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetPowerProcAddrTable_t)(
    xe_api_version_t,
    xet_power_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of FreqDomain functions pointers
typedef struct _xet_freq_domain_apitable_t
{
    xet_pfnFreqDomainGetProperties_t                            pfnGetProperties;
    xet_pfnFreqDomainGetSourceFreqDomain_t                      pfnGetSourceFreqDomain;
    xet_pfnFreqDomainGetSupportedClocks_t                       pfnGetSupportedClocks;
    xet_pfnFreqDomainGetSupportedClockDividers_t                pfnGetSupportedClockDividers;
    xet_pfnFreqDomainGetClockRange_t                            pfnGetClockRange;
    xet_pfnFreqDomainSetClockRange_t                            pfnSetClockRange;
    xet_pfnFreqDomainSetClockDivider_t                          pfnSetClockDivider;
    xet_pfnFreqDomainGetCurrentFrequency_t                      pfnGetCurrentFrequency;
} xet_freq_domain_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FreqDomain table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xetGetFreqDomainProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xet_freq_domain_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xetGetFreqDomainProcAddrTable
typedef xe_result_t (__xecall *xet_pfnGetFreqDomainProcAddrTable_t)(
    xe_api_version_t,
    xet_freq_domain_apitable_t*
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_API_H