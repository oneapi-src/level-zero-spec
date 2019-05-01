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
* @file tools_layer.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/layer.h.mako
* @endcond
*
******************************************************************************/
#ifndef _TOOLS_LAYER_H
#define _TOOLS_LAYER_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xet_all.h"
#include "layer.h"

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricGroupGetCount_t)(
    xe_device_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricGroupGet_t)(
    xe_device_handle_t,
    uint32_t,
    xet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricGroupGetProperties_t)(
    xet_metric_group_handle_t,
    xet_metric_group_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricGet_t)(
    xet_metric_group_handle_t,
    uint32_t,
    xet_metric_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricGetProperties_t)(
    xet_metric_handle_t,
    xet_metric_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricGroupCalculateData_t)(
    xet_metric_group_handle_t,
    uint32_t*,
    uint32_t,
    uint8_t*,
    uint32_t,
    xet_typed_value_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetDeviceActivateMetricGroups_t)(
    xe_device_handle_t,
    uint32_t,
    xet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricTracerOpen_t)(
    xe_device_handle_t,
    xet_metric_tracer_desc_t*,
    xe_event_handle_t,
    xet_metric_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetCommandListAppendMetricTracerMarker_t)(
    xe_command_list_handle_t,
    xet_metric_tracer_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricTracerClose_t)(
    xet_metric_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricTracerReadData_t)(
    xet_metric_tracer_handle_t,
    uint32_t*,
    uint32_t,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricQueryPoolCreate_t)(
    xe_device_handle_t,
    xet_metric_query_pool_desc_t*,
    xet_metric_query_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricQueryPoolDestroy_t)(
    xet_metric_query_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricQueryPoolGetMetricQuery_t)(
    xet_metric_query_pool_handle_t,
    uint32_t,
    xet_metric_query_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetCommandListAppendMetricQueryBegin_t)(
    xe_command_list_handle_t,
    xet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetCommandListAppendMetricQueryEnd_t)(
    xe_command_list_handle_t,
    xet_metric_query_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetCommandListAppendMetricMemoryBarrier_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xetMetricQueryGetData_t)(
    xet_metric_query_handle_t,
    uint32_t*,
    uint32_t,
    uint8_t*
    );


///////////////////////////////////////////////////////////////////////////////
typedef struct _xetapi_pfntable_t
{
    pfn_xetMetricGroupGetCount_t                                    xetMetricGroupGetCount;
    pfn_xetMetricGroupGet_t                                         xetMetricGroupGet;
    pfn_xetMetricGroupGetProperties_t                               xetMetricGroupGetProperties;
    pfn_xetMetricGet_t                                              xetMetricGet;
    pfn_xetMetricGetProperties_t                                    xetMetricGetProperties;
    pfn_xetMetricGroupCalculateData_t                               xetMetricGroupCalculateData;
    pfn_xetDeviceActivateMetricGroups_t                             xetDeviceActivateMetricGroups;
    pfn_xetMetricTracerOpen_t                                       xetMetricTracerOpen;
    pfn_xetCommandListAppendMetricTracerMarker_t                    xetCommandListAppendMetricTracerMarker;
    pfn_xetMetricTracerClose_t                                      xetMetricTracerClose;
    pfn_xetMetricTracerReadData_t                                   xetMetricTracerReadData;
    pfn_xetMetricQueryPoolCreate_t                                  xetMetricQueryPoolCreate;
    pfn_xetMetricQueryPoolDestroy_t                                 xetMetricQueryPoolDestroy;
    pfn_xetMetricQueryPoolGetMetricQuery_t                          xetMetricQueryPoolGetMetricQuery;
    pfn_xetCommandListAppendMetricQueryBegin_t                      xetCommandListAppendMetricQueryBegin;
    pfn_xetCommandListAppendMetricQueryEnd_t                        xetCommandListAppendMetricQueryEnd;
    pfn_xetCommandListAppendMetricMemoryBarrier_t                   xetCommandListAppendMetricMemoryBarrier;
    pfn_xetMetricQueryGetData_t                                     xetMetricQueryGetData;
} xetapi_pfntable_t;


namespace xe_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    bool xetIntercept(
        xetapi_pfntable_t* );  ///< [in] pointer to table of xet API function pointers

} // namespace xe_layer

#endif // _TOOLS_LAYER_H
