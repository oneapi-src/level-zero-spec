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
* @file xet_ddi.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools
* @endcond
*
******************************************************************************/
#ifndef _XET_DDI_H
#define _XET_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xet_api.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricGroupGetCount function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricGroupGetCount_t)(
    xe_device_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricGroupGet function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricGroupGet_t)(
    xe_device_handle_t,
    uint32_t,
    xet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricGroupGetProperties function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricGroupGetProperties_t)(
    xet_metric_group_handle_t,
    xet_metric_group_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricGet function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricGet_t)(
    xet_metric_group_handle_t,
    uint32_t,
    xet_metric_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricGetProperties function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricGetProperties_t)(
    xet_metric_handle_t,
    xet_metric_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricGroupCalculateData function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricGroupCalculateData_t)(
    xet_metric_group_handle_t,
    uint32_t*,
    uint32_t,
    uint8_t*,
    uint32_t,
    xet_typed_value_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetDeviceActivateMetricGroups function-pointer
typedef xe_result_t (__xecall *xet_pfnDeviceActivateMetricGroups_t)(
    xe_device_handle_t,
    uint32_t,
    xet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricTracerOpen function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricTracerOpen_t)(
    xe_device_handle_t,
    xet_metric_tracer_desc_t*,
    xe_event_handle_t,
    xet_metric_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetCommandListAppendMetricTracerMarker function-pointer
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricTracerMarker_t)(
    xe_command_list_handle_t,
    xet_metric_tracer_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricTracerClose function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricTracerClose_t)(
    xet_metric_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricTracerReadData function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricTracerReadData_t)(
    xet_metric_tracer_handle_t,
    uint32_t*,
    uint32_t,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricQueryPoolCreate function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricQueryPoolCreate_t)(
    xe_device_handle_t,
    xet_metric_query_pool_desc_t*,
    xet_metric_query_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricQueryPoolDestroy function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricQueryPoolDestroy_t)(
    xet_metric_query_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricQueryPoolGetMetricQuery function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricQueryPoolGetMetricQuery_t)(
    xet_metric_query_pool_handle_t,
    uint32_t,
    xet_metric_query_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetCommandListAppendMetricQueryBegin function-pointer
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricQueryBegin_t)(
    xe_command_list_handle_t,
    xet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetCommandListAppendMetricQueryEnd function-pointer
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricQueryEnd_t)(
    xe_command_list_handle_t,
    xet_metric_query_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetCommandListAppendMetricMemoryBarrier function-pointer
typedef xe_result_t (__xecall *xet_pfnCommandListAppendMetricMemoryBarrier_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xetMetricQueryGetData function-pointer
typedef xe_result_t (__xecall *xet_pfnMetricQueryGetData_t)(
    xet_metric_query_handle_t,
    uint32_t*,
    uint32_t,
    uint8_t*
    );


///////////////////////////////////////////////////////////////////////////////
typedef struct _xet_apitable_t
{
    xet_pfnMetricGroupGetCount_t                    pfnMetricGroupGetCount;
    xet_pfnMetricGroupGet_t                         pfnMetricGroupGet;
    xet_pfnMetricGroupGetProperties_t               pfnMetricGroupGetProperties;
    xet_pfnMetricGet_t                              pfnMetricGet;
    xet_pfnMetricGetProperties_t                    pfnMetricGetProperties;
    xet_pfnMetricGroupCalculateData_t               pfnMetricGroupCalculateData;
    xet_pfnDeviceActivateMetricGroups_t             pfnDeviceActivateMetricGroups;
    xet_pfnMetricTracerOpen_t                       pfnMetricTracerOpen;
    xet_pfnCommandListAppendMetricTracerMarker_t    pfnCommandListAppendMetricTracerMarker;
    xet_pfnMetricTracerClose_t                      pfnMetricTracerClose;
    xet_pfnMetricTracerReadData_t                   pfnMetricTracerReadData;
    xet_pfnMetricQueryPoolCreate_t                  pfnMetricQueryPoolCreate;
    xet_pfnMetricQueryPoolDestroy_t                 pfnMetricQueryPoolDestroy;
    xet_pfnMetricQueryPoolGetMetricQuery_t          pfnMetricQueryPoolGetMetricQuery;
    xet_pfnCommandListAppendMetricQueryBegin_t      pfnCommandListAppendMetricQueryBegin;
    xet_pfnCommandListAppendMetricQueryEnd_t        pfnCommandListAppendMetricQueryEnd;
    xet_pfnCommandListAppendMetricMemoryBarrier_t   pfnCommandListAppendMetricMemoryBarrier;
    xet_pfnMetricQueryGetData_t                     pfnMetricQueryGetData;
} xet_apitable_t;

#endif // _XET_DDI_H