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

#include "xet_cmdlist.h"
#include "xet_device.h"
#include "xet_gtpin.h"
#include "xet_metric.h"
#include "xet_power.h"
#include "xet_sysman.h"

///////////////////////////////////////////////////////////////////////////////
typedef struct _xet_apitable_t
{
    xet_pfnMetricGroupGetCount_t                                pfnMetricGroupGetCount;
    xet_pfnMetricGroupGet_t                                     pfnMetricGroupGet;
    xet_pfnMetricGroupGetProperties_t                           pfnMetricGroupGetProperties;
    xet_pfnMetricGet_t                                          pfnMetricGet;
    xet_pfnMetricGetProperties_t                                pfnMetricGetProperties;
    xet_pfnMetricGroupCalculateData_t                           pfnMetricGroupCalculateData;
    xet_pfnDeviceActivateMetricGroups_t                         pfnDeviceActivateMetricGroups;
    xet_pfnMetricTracerOpen_t                                   pfnMetricTracerOpen;
    xet_pfnCommandListAppendMetricTracerMarker_t                pfnCommandListAppendMetricTracerMarker;
    xet_pfnMetricTracerClose_t                                  pfnMetricTracerClose;
    xet_pfnMetricTracerReadData_t                               pfnMetricTracerReadData;
    xet_pfnMetricQueryPoolCreate_t                              pfnMetricQueryPoolCreate;
    xet_pfnMetricQueryPoolDestroy_t                             pfnMetricQueryPoolDestroy;
    xet_pfnMetricQueryPoolGetMetricQuery_t                      pfnMetricQueryPoolGetMetricQuery;
    xet_pfnCommandListAppendMetricQueryBegin_t                  pfnCommandListAppendMetricQueryBegin;
    xet_pfnCommandListAppendMetricQueryEnd_t                    pfnCommandListAppendMetricQueryEnd;
    xet_pfnCommandListAppendMetricMemoryBarrier_t               pfnCommandListAppendMetricMemoryBarrier;
    xet_pfnMetricQueryGetData_t                                 pfnMetricQueryGetData;
    xet_pfnPowerCreate_t                                        pfnPowerCreate;
    xet_pfnPowerDestroy_t                                       pfnPowerDestroy;
    xet_pfnPowerGetAveragePowerLimit_t                          pfnPowerGetAveragePowerLimit;
    xet_pfnPowerGetBurstPowerLimit_t                            pfnPowerGetBurstPowerLimit;
    xet_pfnPowerGetPeakPowerLimit_t                             pfnPowerGetPeakPowerLimit;
    xet_pfnPowerGetAllPowerLimits_t                             pfnPowerGetAllPowerLimits;
    xet_pfnPowerGetDefaultPowerLimits_t                         pfnPowerGetDefaultPowerLimits;
    xet_pfnPowerSetAveragePowerLimit_t                          pfnPowerSetAveragePowerLimit;
    xet_pfnPowerSetBurstPowerLimit_t                            pfnPowerSetBurstPowerLimit;
    xet_pfnPowerSetPeakPowerLimit_t                             pfnPowerSetPeakPowerLimit;
    xet_pfnPowerSetPowerLimits_t                                pfnPowerSetPowerLimits;
    xet_pfnPowerGetEnergyCounter_t                              pfnPowerGetEnergyCounter;
    xet_pfnPowerGetTurboMode_t                                  pfnPowerGetTurboMode;
    xet_pfnPowerSetTurboMode_t                                  pfnPowerSetTurboMode;
    xet_pfnPowerGetFreqDomainCount_t                            pfnPowerGetFreqDomainCount;
    xet_pfnPowerGetFreqDomainHandle_t                           pfnPowerGetFreqDomainHandle;
    xet_pfnFreqDomainGetProperties_t                            pfnFreqDomainGetProperties;
    xet_pfnFreqDomainGetSourceFreqDomain_t                      pfnFreqDomainGetSourceFreqDomain;
    xet_pfnFreqDomainGetSupportedClocks_t                       pfnFreqDomainGetSupportedClocks;
    xet_pfnFreqDomainGetSupportedClockDividers_t                pfnFreqDomainGetSupportedClockDividers;
    xet_pfnFreqDomainGetClockRange_t                            pfnFreqDomainGetClockRange;
    xet_pfnFreqDomainSetClockRange_t                            pfnFreqDomainSetClockRange;
    xet_pfnFreqDomainSetClockDivider_t                          pfnFreqDomainSetClockDivider;
    xet_pfnFreqDomainGetCurrentFrequency_t                      pfnFreqDomainGetCurrentFrequency;
    xet_pfnPowerFanCount_t                                      pfnPowerFanCount;
    xet_pfnPowerFanGetProperties_t                              pfnPowerFanGetProperties;
    xet_pfnPowerFanGetSpeedTable_t                              pfnPowerFanGetSpeedTable;
    xet_pfnPowerFanSetSpeedTable_t                              pfnPowerFanSetSpeedTable;
    xet_pfnPowerFanGetSpeed_t                                   pfnPowerFanGetSpeed;
    xet_pfnPowerFanSetSpeed_t                                   pfnPowerFanSetSpeed;
    xet_pfnPowerTemperatureSensorCount_t                        pfnPowerTemperatureSensorCount;
    xet_pfnPowerGetTemperatureProperties_t                      pfnPowerGetTemperatureProperties;
    xet_pfnPowerGetTemperature_t                                pfnPowerGetTemperature;
    xet_pfnPowerSetTemperatureThreshold_t                       pfnPowerSetTemperatureThreshold;
    xet_pfnPowerActivityCount_t                                 pfnPowerActivityCount;
    xet_pfnPowerGetActivityProperties_t                         pfnPowerGetActivityProperties;
    xet_pfnPowerGetActivityCounters_t                           pfnPowerGetActivityCounters;
} xet_apitable_t;

#endif // _XET_API_H