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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetCommandListProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetCommandListProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetDeviceProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetDeviceProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetCommandQueueProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetCommandQueueProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetContextProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetContextProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetDeviceGroupProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetDeviceGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetDeviceGroupProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetFenceProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetFenceProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetEventPoolProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetEventPoolProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetEventProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetEventProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetImageProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetImageProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetModuleProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetModuleProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetModuleBuildLogProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetModuleBuildLogProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetFunctionProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetFunctionProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetSamplerProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetSamplerProcAddrTable") );
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
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xeGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xeGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeInit
xe_result_t __xecall
xeInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    // FOUND: Global
    // auto pfnInit = xe_loader::loader.xeGlobal.pfnInit;
    // return pfnInit( flags );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDriverVersion
xe_result_t __xecall
xeDeviceGroupGetDriverVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
    uint32_t* version                               ///< [out] driver version
    )
{
    hDeviceGroup = std::get<0>( *reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup ) );
    
    // FOUND: DeviceGroup

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextCreate
xe_result_t __xecall
xeContextCreate(
    uint32_t numDevices,                            ///< [in] number of devices in phDevice
    xe_device_handle_t* phDevice,                   ///< [in][range(0, numDevices)] pointer to array of handle of the device
                                                    ///< objects
    xe_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    )
{
    for( size_t i = 0; ( nullptr != phDevice ) && ( i < numDevices ); ++i )
        phDevice[ i ] = std::get<0>( *reinterpret_cast<xe_device_object_t*>( phDevice[ i ] ) );
    
    // FOUND: Context

    *phContext = reinterpret_cast<xe_context_handle_t>( new xe_context_object_t( *phContext, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextDestroy
xe_result_t __xecall
xeContextDestroy(
    xe_context_handle_t hContext                    ///< [in] handle of context object to destroy
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeGetDeviceGroups
xe_result_t __xecall
xeGetDeviceGroups(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_group_handle_t* pDeviceGroups         ///< [in,out][optional][range(0, *pCount)] array of handle of device groups
    )
{
    // FOUND: Global
    // auto pfnGetDeviceGroups = xe_loader::loader.xeGlobal.pfnGetDeviceGroups;
    // return pfnGetDeviceGroups( pCount, pDeviceGroups );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDevices
xe_result_t __xecall
xeDeviceGroupGetDevices(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_handle_t* pDevices                    ///< [in,out][optional][range(0, *pCount)] array of handle of devices
    )
{
    hDeviceGroup = std::get<0>( *reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup ) );
    
    // FOUND: DeviceGroup

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGetSubDevice
xe_result_t __xecall
xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    *phSubDevice = reinterpret_cast<xe_device_handle_t>( new xe_device_object_t( *phSubDevice, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetApiVersion
xe_result_t __xecall
xeDeviceGroupGetApiVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    hDeviceGroup = std::get<0>( *reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup ) );
    
    // FOUND: DeviceGroup

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetProperties
xe_result_t __xecall
xeDeviceGroupGetProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    hDeviceGroup = std::get<0>( *reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup ) );
    
    // FOUND: DeviceGroup

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetComputeProperties
xe_result_t __xecall
xeDeviceGroupGetComputeProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    hDeviceGroup = std::get<0>( *reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup ) );
    
    // FOUND: DeviceGroup

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemoryProperties
xe_result_t __xecall
xeDeviceGroupGetMemoryProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    hDeviceGroup = std::get<0>( *reinterpret_cast<xe_device_group_object_t*>( hDeviceGroup ) );
    
    // FOUND: DeviceGroup

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGetP2PProperties
xe_result_t __xecall
xeDeviceGetP2PProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    hPeerDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hPeerDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceCanAccessPeer
xe_result_t __xecall
xeDeviceCanAccessPeer(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_bool_t* value                                ///< [out] returned access capability
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    hPeerDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hPeerDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetIntermediateCacheConfig
xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetLastLevelCacheConfig
xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueCreate
xe_result_t __xecall
xeCommandQueueCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Create

    *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( new xe_command_queue_object_t( *phCommandQueue, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueDestroy
xe_result_t __xecall
xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    hCommandQueue = std::get<0>( *reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueExecuteCommandLists
xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    xe_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                    ///< to execute
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    hCommandQueue = std::get<0>( *reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue ) );
    for( size_t i = 0; ( nullptr != phCommandLists ) && ( i < numCommandLists ); ++i )
        phCommandLists[ i ] = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( phCommandLists[ i ] ) );
    hFence = ( hFence ) ? std::get<0>( *reinterpret_cast<xe_fence_object_t*>( hFence ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueSynchronize
xe_result_t __xecall
xeCommandQueueSynchronize(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    hCommandQueue = std::get<0>( *reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListCreate
xe_result_t __xecall
xeCommandListCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Create

    *phCommandList = reinterpret_cast<xe_command_list_handle_t>( new xe_command_list_object_t( *phCommandList, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListCreateImmediate
xe_result_t __xecall
xeCommandListCreateImmediate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Create

    *phCommandList = reinterpret_cast<xe_command_list_handle_t>( new xe_command_list_object_t( *phCommandList, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListDestroy
xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListClose
xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListReset
xe_result_t __xecall
xeCommandListReset(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListSetParameter
xe_result_t __xecall
xeCommandListSetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListGetParameter
xe_result_t __xecall
xeCommandListGetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListResetParameters
xe_result_t __xecall
xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListReserveSpace
xe_result_t __xecall
xeCommandListReserveSpace(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendBarrier
xe_result_t __xecall
xeCommandListAppendBarrier(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hSignalEvent = ( hSignalEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hSignalEvent ) ) : nullptr;
    for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
        phWaitEvents[ i ] = std::get<0>( *reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryRangesBarrier
xe_result_t __xecall
xeCommandListAppendMemoryRangesBarrier(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numRanges,                             ///< [in] number of memory ranges
    const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
    const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hSignalEvent = ( hSignalEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hSignalEvent ) ) : nullptr;
    for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
        phWaitEvents[ i ] = std::get<0>( *reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSystemBarrier
xe_result_t __xecall
xeDeviceSystemBarrier(
    xe_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLMemory
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
#endif // XE_ENABLE_OCL_INTEROP
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLProgram
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLProgram(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the program
    cl_program program,                             ///< [in] the OpenCL program to register
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    *phModule = reinterpret_cast<xe_module_handle_t>( new xe_module_object_t( *phModule, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
#endif // XE_ENABLE_OCL_INTEROP
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLCommandQueue
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLCommandQueue(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the command queue
    cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( new xe_command_queue_object_t( *phCommandQueue, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
#endif // XE_ENABLE_OCL_INTEROP
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryCopy
xe_result_t __xecall
xeCommandListAppendMemoryCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hEvent = ( hEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemorySet
xe_result_t __xecall
xeCommandListAppendMemorySet(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    int value,                                      ///< [in] value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initailize
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hEvent = ( hEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryCopyRegion
xe_result_t __xecall
xeCommandListAppendMemoryCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_copy_region_t* dstRegion,                    ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                              ///< [in] destination pitch in bytes
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    xe_copy_region_t* srcRegion,                    ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                              ///< [in] source pitch in bytes
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hEvent = ( hEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopy
xe_result_t __xecall
xeCommandListAppendImageCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hDstImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hDstImage ) );
    hSrcImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hSrcImage ) );
    hEvent = ( hEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyRegion
xe_result_t __xecall
xeCommandListAppendImageCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hDstImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hDstImage ) );
    hSrcImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hSrcImage ) );
    hEvent = ( hEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyToMemory
xe_result_t __xecall
xeCommandListAppendImageCopyToMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hSrcImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hSrcImage ) );
    hEvent = ( hEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyFromMemory
xe_result_t __xecall
xeCommandListAppendImageCopyFromMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hDstImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hDstImage ) );
    hEvent = ( hEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) ) : nullptr;
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryPrefetch
xe_result_t __xecall
xeCommandListAppendMemoryPrefetch(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemAdvise
xe_result_t __xecall
xeCommandListAppendMemAdvise(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolCreate
xe_result_t __xecall
xeEventPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Create

    *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( new xe_event_pool_object_t( *phEventPool, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolDestroy
xe_result_t __xecall
xeEventPoolDestroy(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    )
{
    hEventPool = std::get<0>( *reinterpret_cast<xe_event_pool_object_t*>( hEventPool ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventCreate
xe_result_t __xecall
xeEventCreate(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    hEventPool = std::get<0>( *reinterpret_cast<xe_event_pool_object_t*>( hEventPool ) );
    
    // FOUND: Create

    *phEvent = reinterpret_cast<xe_event_handle_t>( new xe_event_object_t( *phEvent, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventDestroy
xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    hEvent = std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolGetIpcHandle
xe_result_t __xecall
xeEventPoolGetIpcHandle(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    hEventPool = std::get<0>( *reinterpret_cast<xe_event_pool_object_t*>( hEventPool ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolOpenIpcHandle
xe_result_t __xecall
xeEventPoolOpenIpcHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
    xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( new xe_event_pool_object_t( *phEventPool, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolCloseIpcHandle
xe_result_t __xecall
xeEventPoolCloseIpcHandle(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    )
{
    hEventPool = std::get<0>( *reinterpret_cast<xe_event_pool_object_t*>( hEventPool ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendSignalEvent
xe_result_t __xecall
xeCommandListAppendSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hEvent = std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendWaitOnEvents
xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    xe_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                    ///< continuing
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    for( size_t i = 0; ( nullptr != phEvents ) && ( i < numEvents ); ++i )
        phEvents[ i ] = std::get<0>( *reinterpret_cast<xe_event_object_t*>( phEvents[ i ] ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventHostSignal
xe_result_t __xecall
xeEventHostSignal(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    hEvent = std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventHostSynchronize
xe_result_t __xecall
xeEventHostSynchronize(
    xe_event_handle_t hEvent,                       ///< [in] handle of the event
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    hEvent = std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventQueryStatus
xe_result_t __xecall
xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    hEvent = std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendEventReset
xe_result_t __xecall
xeCommandListAppendEventReset(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hEvent = std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventReset
xe_result_t __xecall
xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    hEvent = std::get<0>( *reinterpret_cast<xe_event_object_t*>( hEvent ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceCreate
xe_result_t __xecall
xeFenceCreate(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    hCommandQueue = std::get<0>( *reinterpret_cast<xe_command_queue_object_t*>( hCommandQueue ) );
    
    // FOUND: Create

    *phFence = reinterpret_cast<xe_fence_handle_t>( new xe_fence_object_t( *phFence, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceDestroy
xe_result_t __xecall
xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
    hFence = std::get<0>( *reinterpret_cast<xe_fence_object_t*>( hFence ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceHostSynchronize
xe_result_t __xecall
xeFenceHostSynchronize(
    xe_fence_handle_t hFence,                       ///< [in] handle of the fence
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    hFence = std::get<0>( *reinterpret_cast<xe_fence_object_t*>( hFence ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceQueryStatus
xe_result_t __xecall
xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    hFence = std::get<0>( *reinterpret_cast<xe_fence_object_t*>( hFence ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceReset
xe_result_t __xecall
xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    hFence = std::get<0>( *reinterpret_cast<xe_fence_object_t*>( hFence ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageGetProperties
xe_result_t __xecall
xeImageGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageCreate
xe_result_t __xecall
xeImageCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Create

    *phImage = reinterpret_cast<xe_image_handle_t>( new xe_image_object_t( *phImage, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageDestroy
xe_result_t __xecall
xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    hImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hImage ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextAllocSharedMem
xe_result_t __xecall
xeContextAllocSharedMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextAllocDeviceMem
xe_result_t __xecall
xeContextAllocDeviceMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextAllocHostMem
xe_result_t __xecall
xeContextAllocHostMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextFreeMem
xe_result_t __xecall
xeContextFreeMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextGetMemProperties
xe_result_t __xecall
xeContextGetMemProperties(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextGetMemAddressRange
xe_result_t __xecall
xeContextGetMemAddressRange(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextGetMemIpcHandle
xe_result_t __xecall
xeContextGetMemIpcHandle(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextOpenMemIpcHandle
xe_result_t __xecall
xeContextOpenMemIpcHandle(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextCloseMemIpcHandle
xe_result_t __xecall
xeContextCloseMemIpcHandle(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    hContext = std::get<0>( *reinterpret_cast<xe_context_object_t*>( hContext ) );
    
    // FOUND: Context

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleCreate
xe_result_t __xecall
xeModuleCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Create

    *phModule = reinterpret_cast<xe_module_handle_t>( new xe_module_object_t( *phModule, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleDestroy
xe_result_t __xecall
xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    hModule = std::get<0>( *reinterpret_cast<xe_module_object_t*>( hModule ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleBuildLogDestroy
xe_result_t __xecall
xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    )
{
    hModuleBuildLog = std::get<0>( *reinterpret_cast<xe_module_build_log_object_t*>( hModuleBuildLog ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleBuildLogGetString
xe_result_t __xecall
xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    hModuleBuildLog = std::get<0>( *reinterpret_cast<xe_module_build_log_object_t*>( hModuleBuildLog ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetNativeBinary
xe_result_t __xecall
xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    hModule = std::get<0>( *reinterpret_cast<xe_module_object_t*>( hModule ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetGlobalPointer
xe_result_t __xecall
xeModuleGetGlobalPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of function in global
    void** pPtr                                     ///< [out] device visible pointer
    )
{
    hModule = std::get<0>( *reinterpret_cast<xe_module_object_t*>( hModule ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionCreate
xe_result_t __xecall
xeFunctionCreate(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    )
{
    hModule = std::get<0>( *reinterpret_cast<xe_module_object_t*>( hModule ) );
    
    // FOUND: Create

    *phFunction = reinterpret_cast<xe_function_handle_t>( new xe_function_object_t( *phFunction, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionDestroy
xe_result_t __xecall
xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    hFunction = std::get<0>( *reinterpret_cast<xe_function_object_t*>( hFunction ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetFunctionPointer
xe_result_t __xecall
xeModuleGetFunctionPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    )
{
    hModule = std::get<0>( *reinterpret_cast<xe_module_object_t*>( hModule ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetGroupSize
xe_result_t __xecall
xeFunctionSetGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    )
{
    hFunction = std::get<0>( *reinterpret_cast<xe_function_object_t*>( hFunction ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSuggestGroupSize
xe_result_t __xecall
xeFunctionSuggestGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension.
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
    )
{
    hFunction = std::get<0>( *reinterpret_cast<xe_function_object_t*>( hFunction ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetArgumentValue
xe_result_t __xecall
xeFunctionSetArgumentValue(
    xe_function_handle_t hFunction,                 ///< [in,out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetAttribute
xe_result_t __xecall
xeFunctionSetAttribute(
    xe_function_handle_t hFunction,                 ///< [in,out] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionGetAttribute
xe_result_t __xecall
xeFunctionGetAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_get_attribute_t attr,               ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    hFunction = std::get<0>( *reinterpret_cast<xe_function_object_t*>( hFunction ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchFunction
xe_result_t __xecall
xeCommandListAppendLaunchFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] launch function arguments.
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hFunction = std::get<0>( *reinterpret_cast<xe_function_object_t*>( hFunction ) );
    hSignalEvent = ( hSignalEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hSignalEvent ) ) : nullptr;
    for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
        phWaitEvents[ i ] = std::get<0>( *reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchFunctionIndirect
xe_result_t __xecall
xeCommandListAppendLaunchFunctionIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hFunction = std::get<0>( *reinterpret_cast<xe_function_object_t*>( hFunction ) );
    hSignalEvent = ( hSignalEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hSignalEvent ) ) : nullptr;
    for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
        phWaitEvents[ i ] = std::get<0>( *reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchMultipleFunctionsIndirect
xe_result_t __xecall
xeCommandListAppendLaunchMultipleFunctionsIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
    xe_function_handle_t* phFunctions,              ///< [in][range(0, numFunctions)] handles of the function objects
    const uint32_t* pNumLaunchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of launch arguments; value must be less-than or equal-to
                                                    ///< numFunctions
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in][range(0, numFunctions)] pointer to device buffer that will
                                                    ///< contain a contiguous array of launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    for( size_t i = 0; ( nullptr != phFunctions ) && ( i < numFunctions ); ++i )
        phFunctions[ i ] = std::get<0>( *reinterpret_cast<xe_function_object_t*>( phFunctions[ i ] ) );
    hSignalEvent = ( hSignalEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hSignalEvent ) ) : nullptr;
    for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
        phWaitEvents[ i ] = std::get<0>( *reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchHostFunction
xe_result_t __xecall
xeCommandListAppendLaunchHostFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData,                                ///< [in] pointer to user data to pass to host function.
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    hCommandList = std::get<0>( *reinterpret_cast<xe_command_list_object_t*>( hCommandList ) );
    hSignalEvent = ( hSignalEvent ) ? std::get<0>( *reinterpret_cast<xe_event_object_t*>( hSignalEvent ) ) : nullptr;
    for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
        phWaitEvents[ i ] = std::get<0>( *reinterpret_cast<xe_event_object_t*>( phWaitEvents[ i ] ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceMakeMemoryResident
xe_result_t __xecall
xeDeviceMakeMemoryResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceEvictMemory
xe_result_t __xecall
xeDeviceEvictMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceMakeImageResident
xe_result_t __xecall
xeDeviceMakeImageResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    hImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hImage ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceEvictImage
xe_result_t __xecall
xeDeviceEvictImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    hImage = std::get<0>( *reinterpret_cast<xe_image_object_t*>( hImage ) );
    
    // FOUND: Other

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeSamplerCreate
xe_result_t __xecall
xeSamplerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
    xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    hDevice = std::get<0>( *reinterpret_cast<xe_device_object_t*>( hDevice ) );
    
    // FOUND: Create

    *phSampler = reinterpret_cast<xe_sampler_handle_t>( new xe_sampler_object_t( *phSampler, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeSamplerDestroy
xe_result_t __xecall
xeSamplerDestroy(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    )
{
    hSampler = std::get<0>( *reinterpret_cast<xe_sampler_object_t*>( hSampler ) );
    
    // FOUND: Destroy

    return XE_RESULT_SUCCESS;
}
#if defined(__cplusplus)
};
#endif
