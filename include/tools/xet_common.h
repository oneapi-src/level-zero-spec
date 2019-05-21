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
* @file xet_common.h
*
* @brief Intel Xe Level-Zero Tool API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/common.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_COMMON_H
#define _XET_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include <stdint.h>
#include <string.h>
#include "xe_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of device object
typedef struct _xet_device_handle_t *xet_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of command list object
typedef struct _xet_command_list_handle_t *xet_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric group's object
typedef struct _xet_metric_group_handle_t *xet_metric_group_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric's object
typedef struct _xet_metric_handle_t *xet_metric_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric tracer's object
typedef struct _xet_metric_tracer_handle_t *xet_metric_tracer_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query pool's object
typedef struct _xet_metric_query_pool_handle_t *xet_metric_query_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of metric query's object
typedef struct _xet_metric_query_handle_t *xet_metric_query_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of power object
typedef struct _xet_power_handle_t *xet_power_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of a frequency domain on a device
typedef struct _xet_freq_domain_handle_t *xet_freq_domain_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_group_properties_t
typedef struct _xet_metric_group_properties_t xet_metric_group_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_typed_value_t
typedef struct _xet_typed_value_t xet_typed_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_properties_t
typedef struct _xet_metric_properties_t xet_metric_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_tracer_desc_t
typedef struct _xet_metric_tracer_desc_t xet_metric_tracer_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_metric_query_pool_desc_t
typedef struct _xet_metric_query_pool_desc_t xet_metric_query_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_average_limit_t
typedef struct _xet_power_average_limit_t xet_power_average_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_burst_limit_t
typedef struct _xet_power_burst_limit_t xet_power_burst_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_peak_limit_t
typedef struct _xet_power_peak_limit_t xet_power_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_power_limits_t
typedef struct _xet_power_limits_t xet_power_limits_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_freq_domain_properties_t
typedef struct _xet_freq_domain_properties_t xet_freq_domain_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_clock_divider_t
typedef struct _xet_clock_divider_t xet_clock_divider_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_properties_t
typedef struct _xet_fan_properties_t xet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_point_t
typedef struct _xet_fan_point_t xet_fan_point_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_fan_speed_info_t
typedef struct _xet_fan_speed_info_t xet_fan_speed_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_temperature_properties_t
typedef struct _xet_temperature_properties_t xet_temperature_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_activity_properties_t
typedef struct _xet_activity_properties_t xet_activity_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xet_activity_counters_t
typedef struct _xet_activity_counters_t xet_activity_counters_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_COMMON_H
