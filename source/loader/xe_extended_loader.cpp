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
* @file xe_extended_loader.cpp
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
xexGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xex_global_dditable_t* ptable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xex_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xexGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

    // If the validation layer is enabled, then intercept the device-driver DDI tables
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xex_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xexGetGlobalProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandGraph table
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
xexGetCommandGraphProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xex_command_graph_dditable_t* ptable            ///< [in,out] pointer to table of DDI function pointers
    )
{
#ifdef _DEBUG
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_loader::loader.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    if( nullptr != xe_loader::loader.commonDriver )
    {
        static auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.commonDriver, "xexGetCommandGraphProcAddrTable") );
        result = getTable( version, ptable );
    }

    // If the validation layer is enabled, then intercept the device-driver DDI tables
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != xe_loader::loader.validationLayer ))
    {
        static auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
            GET_FUNCTION_PTR(xe_loader::loader.validationLayer, "xexGetCommandGraphProcAddrTable") );
        result = getTable( version, ptable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xexInit
xe_result_t __xecall
xexInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto pfnInit = xe_loader::loader.xexGlobalDdiTable.pfnInit;
    
    
    auto result = pfnInit( flags );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xexCommandGraphCreate
xe_result_t __xecall
xexCommandGraphCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
    xex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
    )
{
    auto pfnCreate = std::get<1>( *reinterpret_cast<xex_device_object_t*>( hDevice ) )->CommandGraph.pfnCreate;
    
    hDevice = std::get<0>( *reinterpret_cast<xex_device_object_t*>( hDevice ) );
    
    auto result = pfnCreate( hDevice, desc, phCommandGraph );

    *phCommandGraph = reinterpret_cast<xex_command_graph_handle_t>( new xex_command_graph_object_t( *phCommandGraph, nullptr ) );
    
    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xexCommandGraphDestroy
xe_result_t __xecall
xexCommandGraphDestroy(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to destroy
    )
{
    auto pfnDestroy = std::get<1>( *reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph ) )->CommandGraph.pfnDestroy;
    
    hCommandGraph = std::get<0>( *reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph ) );
    
    auto result = pfnDestroy( hCommandGraph );

    return XE_RESULT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xexCommandGraphClose
xe_result_t __xecall
xexCommandGraphClose(
    xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    )
{
    auto pfnClose = std::get<1>( *reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph ) )->CommandGraph.pfnClose;
    
    hCommandGraph = std::get<0>( *reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph ) );
    
    auto result = pfnClose( hCommandGraph );

    return XE_RESULT_SUCCESS;
}
#if defined(__cplusplus)
};
#endif
