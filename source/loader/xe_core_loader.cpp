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
* @file xe_core_loader.cpp
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
xeGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_list_apitable_t* ptable              ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetCommandListProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetCommandListProcAddrTable") );
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
xeGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_apitable_t* ptable                    ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetDeviceProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetDeviceProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
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
xeGetCommandQueueProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_queue_apitable_t* ptable             ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetCommandQueueProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetCommandQueueProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
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
xeGetContextProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_context_apitable_t* ptable                   ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetContextProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetContextProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceGroup table
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
xeGetDeviceGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_group_apitable_t* ptable              ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetDeviceGroupProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetDeviceGroupProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
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
xeGetFenceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_fence_apitable_t* ptable                     ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetFenceProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetFenceProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
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
xeGetEventPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_pool_apitable_t* ptable                ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetEventPoolProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetEventPoolProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
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
xeGetEventProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_apitable_t* ptable                     ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetEventProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetEventProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
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
xeGetImageProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_image_apitable_t* ptable                     ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetImageProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetImageProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
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
xeGetModuleProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_apitable_t* ptable                    ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetModuleProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetModuleProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
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
xeGetModuleBuildLogProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_build_log_apitable_t* ptable          ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetModuleBuildLogProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetModuleBuildLogProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
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
xeGetFunctionProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_function_apitable_t* ptable                  ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetFunctionProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetFunctionProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
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
xeGetSamplerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_sampler_apitable_t* ptable                   ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetSamplerProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetSamplerProcAddrTable") );
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
xeGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_global_apitable_t* ptable                    ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != context.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(context.commonDriver, "xeGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != context.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(context.validationLayer, "xeGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

#if defined(__cplusplus)
};
#endif
