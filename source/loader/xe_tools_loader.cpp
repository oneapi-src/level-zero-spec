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
* @file xe_tools_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_loader.h"

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetDeviceProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetDeviceProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetCommandListProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetCommandListProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetMetricGroupProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetMetricGroupProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetMetricProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetMetricProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetMetricTracerProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetMetricTracerProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetMetricQueryPoolProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetMetricQueryPoolProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetMetricQueryProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetMetricQueryProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetPowerProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetPowerProcAddrTable") );
        result = getTable( version, ptable );
    }

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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetFreqDomainProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetFreqDomainProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
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
xetGetSysmanProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xet_sysman_apitable_t* ptable                   ///< [in,out] pointer to table of API function pointers
    )
{
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xet_pfnGetSysmanProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xetGetSysmanProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xet_pfnGetSysmanProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xetGetSysmanProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetInit
xe_result_t __xecall
xetInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto pfnInit = xe_loader::loader.xetGlobal.pfnInit;
    
    
    //auto result = pfnInit( flags );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGroupGetCount
xe_result_t __xecall
xetMetricGroupGetCount(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount                                ///< [out] number of metric groups supported by the device
    )
{
    auto pfnGetCount = std::get<1>( *reinterpret_cast<xet_device_object_t*>( hDevice ) )->pMetricGroup->pfnGetCount;
    
    hDevice = std::get<0>( *reinterpret_cast<xet_device_object_t*>( hDevice ) );
    
    //auto result = pfnGetCount( hDevice, pCount );

    return XE_RESULT_SUCCESS;
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
    auto pfnGet = std::get<1>( *reinterpret_cast<xet_device_object_t*>( hDevice ) )->pMetricGroup->pfnGet;
    
    hDevice = std::get<0>( *reinterpret_cast<xet_device_object_t*>( hDevice ) );
    
    //auto result = pfnGet( hDevice, ordinal, phMetricGroup );

    *phMetricGroup = reinterpret_cast<xet_metric_group_handle_t>( new xet_metric_group_object_t( *phMetricGroup, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGroupGetProperties
xe_result_t __xecall
xetMetricGroupGetProperties(
    xet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    xet_metric_group_properties_t* pProperties      ///< [out] metric group properties
    )
{
    auto pfnGetProperties = std::get<1>( *reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup ) )->pfnGetProperties;
    
    hMetricGroup = std::get<0>( *reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup ) );
    
    //auto result = pfnGetProperties( hMetricGroup, pProperties );

    return XE_RESULT_SUCCESS;
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
    auto pfnGet = std::get<1>( *reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup ) )->pfnGet;
    
    hMetricGroup = std::get<0>( *reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup ) );
    
    //auto result = pfnGet( hMetricGroup, ordinal, phMetric );

    *phMetric = reinterpret_cast<xet_metric_handle_t>( new xet_metric_object_t( *phMetric, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricGetProperties
xe_result_t __xecall
xetMetricGetProperties(
    xet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    xet_metric_properties_t* pProperties            ///< [out] metric properties
    )
{
    auto pfnGetProperties = std::get<1>( *reinterpret_cast<xet_metric_object_t*>( hMetric ) )->pfnGetProperties;
    
    hMetric = std::get<0>( *reinterpret_cast<xet_metric_object_t*>( hMetric ) );
    
    //auto result = pfnGetProperties( hMetric, pProperties );

    return XE_RESULT_SUCCESS;
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
    auto pfnCalculateData = std::get<1>( *reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup ) )->pfnCalculateData;
    
    hMetricGroup = std::get<0>( *reinterpret_cast<xet_metric_group_object_t*>( hMetricGroup ) );
    
    //auto result = pfnCalculateData( hMetricGroup, pReportCount, rawDataSize, pRawData, calculatedDataSize, pCalculatedData );

    return XE_RESULT_SUCCESS;
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
    auto pfnActivateMetricGroups = std::get<1>( *reinterpret_cast<xet_device_object_t*>( hDevice ) )->pfnActivateMetricGroups;
    
    hDevice = std::get<0>( *reinterpret_cast<xet_device_object_t*>( hDevice ) );
    for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < count ); ++i )
        phMetricGroups[ i ] = std::get<0>( *reinterpret_cast<xet_metric_group_object_t*>( phMetricGroups[ i ] ) );
    
    //auto result = pfnActivateMetricGroups( hDevice, count, phMetricGroups );

    return XE_RESULT_SUCCESS;
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
    auto pfnOpen = std::get<1>( *reinterpret_cast<xet_device_object_t*>( hDevice ) )->pMetricTracer->pfnOpen;
    
    hDevice = std::get<0>( *reinterpret_cast<xet_device_object_t*>( hDevice ) );
    hNotificationEvent = std::get<0>( *reinterpret_cast<xet_event_object_t*>( hNotificationEvent ) );
    
    //auto result = pfnOpen( hDevice, pDesc, hNotificationEvent, phMetricTracer );

    *phMetricTracer = reinterpret_cast<xet_metric_tracer_handle_t>( new xet_metric_tracer_object_t( *phMetricTracer, nullptr ) );
    
    return XE_RESULT_SUCCESS;
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
    auto pfnAppendMetricTracerMarker = std::get<1>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) )->pfnAppendMetricTracerMarker;
    
    hCommandList = std::get<0>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) );
    hMetricTracer = std::get<0>( *reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer ) );
    
    //auto result = pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricTracerClose
xe_result_t __xecall
xetMetricTracerClose(
    xet_metric_tracer_handle_t hMetricTracer        ///< [in] handle of the metric tracer
    )
{
    auto pfnClose = std::get<1>( *reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer ) )->pfnClose;
    
    hMetricTracer = std::get<0>( *reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer ) );
    
    //auto result = pfnClose( hMetricTracer );

    return XE_RESULT_SUCCESS;
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
    auto pfnReadData = std::get<1>( *reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer ) )->pfnReadData;
    
    hMetricTracer = std::get<0>( *reinterpret_cast<xet_metric_tracer_object_t*>( hMetricTracer ) );
    
    //auto result = pfnReadData( hMetricTracer, pReportCount, rawDataSize, pRawData );

    return XE_RESULT_SUCCESS;
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
    auto pfnCreate = std::get<1>( *reinterpret_cast<xet_device_object_t*>( hDevice ) )->pMetricQueryPool->pfnCreate;
    
    hDevice = std::get<0>( *reinterpret_cast<xet_device_object_t*>( hDevice ) );
    
    //auto result = pfnCreate( hDevice, pDesc, phMetricQueryPool );

    *phMetricQueryPool = reinterpret_cast<xet_metric_query_pool_handle_t>( new xet_metric_query_pool_object_t( *phMetricQueryPool, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetMetricQueryPoolDestroy
xe_result_t __xecall
xetMetricQueryPoolDestroy(
    xet_metric_query_pool_handle_t hMetricQueryPool ///< [in] handle of the metric query pool
    )
{
    auto pfnDestroy = std::get<1>( *reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool ) )->pfnDestroy;
    
    hMetricQueryPool = std::get<0>( *reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool ) );
    
    //auto result = pfnDestroy( hMetricQueryPool );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetMetricQuery = std::get<1>( *reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool ) )->pfnGetMetricQuery;
    
    hMetricQueryPool = std::get<0>( *reinterpret_cast<xet_metric_query_pool_object_t*>( hMetricQueryPool ) );
    
    //auto result = pfnGetMetricQuery( hMetricQueryPool, ordinal, phMetricQuery );

    *phMetricQuery = reinterpret_cast<xet_metric_query_handle_t>( new xet_metric_query_object_t( *phMetricQuery, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricQueryBegin
xe_result_t __xecall
xetCommandListAppendMetricQueryBegin(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    auto pfnAppendMetricQueryBegin = std::get<1>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) )->pfnAppendMetricQueryBegin;
    
    hCommandList = std::get<0>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) );
    hMetricQuery = std::get<0>( *reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery ) );
    
    //auto result = pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );

    return XE_RESULT_SUCCESS;
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
    auto pfnAppendMetricQueryEnd = std::get<1>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) )->pfnAppendMetricQueryEnd;
    
    hCommandList = std::get<0>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) );
    hMetricQuery = std::get<0>( *reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery ) );
    hCompletionEvent = std::get<0>( *reinterpret_cast<xet_event_object_t*>( hCompletionEvent ) );
    
    //auto result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetCommandListAppendMetricMemoryBarrier
xe_result_t __xecall
xetCommandListAppendMetricMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    auto pfnAppendMetricMemoryBarrier = std::get<1>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) )->pfnAppendMetricMemoryBarrier;
    
    hCommandList = std::get<0>( *reinterpret_cast<xet_command_list_object_t*>( hCommandList ) );
    
    //auto result = pfnAppendMetricMemoryBarrier( hCommandList );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetData = std::get<1>( *reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery ) )->pfnGetData;
    
    hMetricQuery = std::get<0>( *reinterpret_cast<xet_metric_query_object_t*>( hMetricQuery ) );
    
    //auto result = pfnGetData( hMetricQuery, pReportCount, rawDataSize, pRawData );

    return XE_RESULT_SUCCESS;
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
    auto pfnCreate = std::get<1>( *reinterpret_cast<xet_device_object_t*>( hDevice ) )->pPower->pfnCreate;
    
    hDevice = std::get<0>( *reinterpret_cast<xet_device_object_t*>( hDevice ) );
    
    //auto result = pfnCreate( hDevice, flags, pPowerHandle );

    *pPowerHandle = reinterpret_cast<xet_power_handle_t>( new xet_power_object_t( *pPowerHandle, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerDestroy
xe_result_t __xecall
xetPowerDestroy(
    xet_power_handle_t hPower                       ///< [in] handle of the power object to destroy
    )
{
    auto pfnDestroy = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnDestroy;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnDestroy( hPower );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetAveragePowerLimit
xe_result_t __xecall
xetPowerGetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
    )
{
    auto pfnGetAveragePowerLimit = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetAveragePowerLimit;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetAveragePowerLimit( hPower, pLimit );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetBurstPowerLimit
xe_result_t __xecall
xetPowerGetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
    )
{
    auto pfnGetBurstPowerLimit = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetBurstPowerLimit;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetBurstPowerLimit( hPower, pLimit );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetPeakPowerLimit
xe_result_t __xecall
xetPowerGetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
    )
{
    auto pfnGetPeakPowerLimit = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetPeakPowerLimit;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetPeakPowerLimit( hPower, pLimit );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetAllPowerLimits
xe_result_t __xecall
xetPowerGetAllPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
    )
{
    auto pfnGetAllPowerLimits = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetAllPowerLimits;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetAllPowerLimits( hPower, pLimits );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetDefaultPowerLimits
xe_result_t __xecall
xetPowerGetDefaultPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
    )
{
    auto pfnGetDefaultPowerLimits = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetDefaultPowerLimits;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetDefaultPowerLimits( hPower, pLimits );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetAveragePowerLimit
xe_result_t __xecall
xetPowerSetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
    )
{
    auto pfnSetAveragePowerLimit = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnSetAveragePowerLimit;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnSetAveragePowerLimit( hPower, pLimit );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetBurstPowerLimit
xe_result_t __xecall
xetPowerSetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
    )
{
    auto pfnSetBurstPowerLimit = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnSetBurstPowerLimit;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnSetBurstPowerLimit( hPower, pLimit );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetPeakPowerLimit
xe_result_t __xecall
xetPowerSetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
    )
{
    auto pfnSetPeakPowerLimit = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnSetPeakPowerLimit;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnSetPeakPowerLimit( hPower, pLimit );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetPowerLimits
xe_result_t __xecall
xetPowerSetPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
    )
{
    auto pfnSetPowerLimits = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnSetPowerLimits;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnSetPowerLimits( hPower, pLimits );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetEnergyCounter
xe_result_t __xecall
xetPowerGetEnergyCounter(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint64_t* pEnergy                               ///< [out] the energy counter in millijoules
    )
{
    auto pfnGetEnergyCounter = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetEnergyCounter;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetEnergyCounter( hPower, pEnergy );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetTurboMode
xe_result_t __xecall
xetPowerGetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
    )
{
    auto pfnGetTurboMode = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetTurboMode;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetTurboMode( hPower, pTurboMode );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerSetTurboMode
xe_result_t __xecall
xetPowerSetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
    )
{
    auto pfnSetTurboMode = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnSetTurboMode;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnSetTurboMode( hPower, pTurboMode );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerGetFreqDomainCount
xe_result_t __xecall
xetPowerGetFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    )
{
    auto pfnGetFreqDomainCount = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetFreqDomainCount;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetFreqDomainCount( hPower, pNumFreqDomains );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetFreqDomain = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetFreqDomain;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetFreqDomain( hPower, ordinal, phFreqDomain );

    *phFreqDomain = reinterpret_cast<xet_freq_domain_handle_t>( new xet_freq_domain_object_t( *phFreqDomain, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetFreqDomainGetProperties
xe_result_t __xecall
xetFreqDomainGetProperties(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
    )
{
    auto pfnGetProperties = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnGetProperties;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnGetProperties( hFreqDomain, pFreqDomainProperties );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetSourceFreqDomain = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnGetSourceFreqDomain;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnGetSourceFreqDomain( hFreqDomain, phSrcFreqDomain );

    *phSrcFreqDomain = reinterpret_cast<xet_freq_domain_handle_t>( new xet_freq_domain_object_t( *phSrcFreqDomain, nullptr ) );
    
    return XE_RESULT_SUCCESS;
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
    auto pfnGetSupportedClocks = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnGetSupportedClocks;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnGetSupportedClocks( hFreqDomain, numClockPoints, pClocks );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetSupportedClockDividers = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnGetSupportedClockDividers;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnGetSupportedClockDividers( hFreqDomain, numClockDividers, pDividers );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetClockRange = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnGetClockRange;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnGetClockRange( hFreqDomain, pMinClock, pMaxClock );

    return XE_RESULT_SUCCESS;
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
    auto pfnSetClockRange = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnSetClockRange;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnSetClockRange( hFreqDomain, minClock, maxClock );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetFreqDomainSetClockDivider
xe_result_t __xecall
xetFreqDomainSetClockDivider(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
    )
{
    auto pfnSetClockDivider = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnSetClockDivider;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnSetClockDivider( hFreqDomain, pClockDividerRequest );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetCurrentFrequency = std::get<1>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) )->pfnGetCurrentFrequency;
    
    hFreqDomain = std::get<0>( *reinterpret_cast<xet_freq_domain_object_t*>( hFreqDomain ) );
    
    //auto result = pfnGetCurrentFrequency( hFreqDomain, pFreqRequest, pFreqResolved, pFreqThrottleReasons );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerFanCount
xe_result_t __xecall
xetPowerFanCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pFanCount                             ///< [out] the number of fans on the device
    )
{
    auto pfnFanCount = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnFanCount;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnFanCount( hPower, pFanCount );

    return XE_RESULT_SUCCESS;
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
    auto pfnFanGetProperties = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnFanGetProperties;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnFanGetProperties( hPower, fanIndex, pFanProperties );

    return XE_RESULT_SUCCESS;
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
    auto pfnFanGetSpeedTable = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnFanGetSpeedTable;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnFanGetSpeedTable( hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints );

    return XE_RESULT_SUCCESS;
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
    auto pfnFanSetSpeedTable = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnFanSetSpeedTable;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnFanSetSpeedTable( hPower, fanIndex, numFanPoints, pFanPoints );

    return XE_RESULT_SUCCESS;
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
    auto pfnFanGetSpeed = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnFanGetSpeed;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnFanGetSpeed( hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed );

    return XE_RESULT_SUCCESS;
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
    auto pfnFanSetSpeed = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnFanSetSpeed;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnFanSetSpeed( hPower, startFanIndex, numFans, pFanSpeed );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerTemperatureSensorCount
xe_result_t __xecall
xetPowerTemperatureSensorCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
    )
{
    auto pfnTemperatureSensorCount = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnTemperatureSensorCount;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnTemperatureSensorCount( hPower, pSensorCount );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetTemperatureProperties = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetTemperatureProperties;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetTemperatureProperties( hPower, sensorIndex, pProperties );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetTemperature = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetTemperature;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetTemperature( hPower, startSensorIndex, numSensors, pTemperatures );

    return XE_RESULT_SUCCESS;
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
    auto pfnSetTemperatureThreshold = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnSetTemperatureThreshold;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnSetTemperatureThreshold( hPower, sensorIndex, maxTemperature );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetPowerActivityCount
xe_result_t __xecall
xetPowerActivityCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
    )
{
    auto pfnActivityCount = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnActivityCount;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnActivityCount( hPower, pActivityCount );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetActivityProperties = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetActivityProperties;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetActivityProperties( hPower, activityIndex, pProperties );

    return XE_RESULT_SUCCESS;
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
    auto pfnGetActivityCounters = std::get<1>( *reinterpret_cast<xet_power_object_t*>( hPower ) )->pfnGetActivityCounters;
    
    hPower = std::get<0>( *reinterpret_cast<xet_power_object_t*>( hPower ) );
    
    //auto result = pfnGetActivityCounters( hPower, startCounterIndex, numCounters, pCounters );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xetSysmanfoo
xe_result_t __xecall
xetSysmanfoo(
    void* blob                                      ///< [in]
    )
{
    //auto result = pfnfoo( blob );

    return XE_RESULT_SUCCESS;
}
#if defined(__cplusplus)
};
#endif
