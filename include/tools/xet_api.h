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
} xet_apitable_t;

#endif // _XET_API_H