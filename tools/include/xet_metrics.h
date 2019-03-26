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
* @file xet_metrics.h
*
* @brief Intel Xe Level-Zero Tool APIs for Metrics
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/metrics.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_METRICS_H
#define _XET_METRICS_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xet_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
typedef enum _xet_metric_group_sampling_type
{

} xet_metric_group_sampling_type;

///////////////////////////////////////////////////////////////////////////////
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetDeviceGetMetricGroupCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xet_metric_group_sampling_type type,            ///< [in] metric group sampling type
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric group universal unique id (UUID)
typedef struct _xe_metric_group_uuid_t
{
    uint8_t id[XE_MAX_UUID_SIZE];                   ///< [out] metric group universal unique id

} xe_metric_group_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pUniqueIds
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetDeviceGetMetricGroupUniqueIds(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xet_metric_group_sampling_type type,            ///< [in] metric group sampling type
    uint32_t count,                                 ///< [in] number of metric groups to retrieve uuids
    xe_metric_group_uuid_t* pUniqueIds              ///< [in,out] pointer to an array of uuids for metric groups.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_metric_group_properties
typedef enum _xet_metric_group_properties_version_t
{
    XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xet_metric_group_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Maximum metric group name string size
#define XET_MAX_METRIC_GROUP_NAME  256

///////////////////////////////////////////////////////////////////////////////
/// @brief Maximum metric group description name string size
#define XET_MAX_METRIC_GROUP_DESCRIPTION  256

///////////////////////////////////////////////////////////////////////////////
/// @brief Device metric group properties queried using
///        ::xetDeviceGetMetricGroupProperties
typedef struct _xet_metric_group_properties
{
    xet_metric_group_properties_version_t version;  ///< [in] ::XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
    xet_metric_group_sampling_type samplingType;    ///< [out]
    uint32_t domain;                                ///< [out] cannot use simultaneous metric groups from different domains
    uint32_t numMetrics;                            ///< [out] number of metrics in the group
    size_t sizeMetrics;                             ///< [out] size in bytes of the metrics in the group
    char name[XET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
    char description[XET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description

} xet_metric_group_properties;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the metric group
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pMetricGroupProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetDeviceGetMetricGroupProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_metric_group_uuid_t uuid,                    ///< [in] metric group uuid
    xet_metric_group_properties* pMetricGroupProperties ///< [out] device properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_metric_properties
typedef enum _xet_metric_properties_version_t
{
    XET_METRIC_PROPERTIES_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),///< version 1.0

} xet_metric_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device metric group properties queried using
///        ::xetDeviceGetMetricGroupProperties
typedef struct _xet_metric_properties
{
    xet_metric_properties_version_t version;        ///< [in] ::XET_METRIC_PROPERTIES_VERSION_CURRENT

} xet_metric_properties;

///////////////////////////////////////////////////////////////////////////////
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pMetricProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
__xedllport xe_result_t __xecall
xetDeviceGetMetricGroupMetricProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_metric_group_uuid_t uuid,                    ///< [in] metric group uuid
    uint32_t ordinal,                               ///< [in] ordinal of the metric
    xet_metric_properties* pMetricProperties        ///< [out] device properties
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_METRICS_H
