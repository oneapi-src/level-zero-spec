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

#if defined(__cplusplus)
};
#endif
