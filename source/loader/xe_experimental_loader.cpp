/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_experimental_loader.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/ldrddi.cpp.mako
 * @endcond
 *
 */
#include "xe_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    xex_command_list_factory_t          xex_command_list_factory;
    xex_command_graph_factory_t         xex_command_graph_factory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xexInit
    xe_result_t __xecall
    xexInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        for( auto& drv : context.drivers )
        {
            if( XE_RESULT_SUCCESS == result )
            {
                result = drv.dditable.xex.Global.pfnInit( flags );
            }
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xexCommandListReserveSpace
    xe_result_t __xecall
    xexCommandListReserveSpace(
        xex_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xex_command_list_object_t*>( hCommandList )->dditable;
        auto pfnReserveSpace = dditable->xex.CommandList.pfnReserveSpace;
        if( nullptr == pfnReserveSpace )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<xex_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnReserveSpace( hCommandList, size, ptr );

        return result;
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
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xe_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->xex.CommandGraph.pfnCreate;
        if( nullptr == pfnCreate )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<xe_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phCommandGraph );

        try
        {
            // convert driver handle to loader handle
            *phCommandGraph = reinterpret_cast<xex_command_graph_handle_t>(
                xex_command_graph_factory.getInstance( *phCommandGraph, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xexCommandGraphDestroy
    xe_result_t __xecall
    xexCommandGraphDestroy(
        xex_command_graph_handle_t hCommandGraph        ///< [in][release] handle of command graph object to destroy
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph )->dditable;
        auto pfnDestroy = dditable->xex.CommandGraph.pfnDestroy;
        if( nullptr == pfnDestroy )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandGraph = reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandGraph );

        // release loader handle
        xex_command_graph_factory.release( hCommandGraph );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xexCommandGraphClose
    xe_result_t __xecall
    xexCommandGraphClose(
        xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph )->dditable;
        auto pfnClose = dditable->xex.CommandGraph.pfnClose;
        if( nullptr == pfnClose )
            return XE_RESULT_ERROR_UNSUPPORTED;

        // convert loader handle to driver handle
        hCommandGraph = reinterpret_cast<xex_command_graph_object_t*>( hCommandGraph )->handle;

        // forward to device-driver
        result = pfnClose( hCommandGraph );

        return result;
    }

} // namespace loader

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
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xexGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xex_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xex_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xexGetGlobalProcAddrTable") );
            result = getTable( version, &drv.dditable.xex.Global );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnInit                                     = loader::xexInit;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xex.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xex_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xexGetGlobalProcAddrTable") );
        result = getTable( version, pDdiTable );
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
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xexGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xex_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xex_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xexGetCommandListProcAddrTable") );
            result = getTable( version, &drv.dditable.xex.CommandList );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnReserveSpace                             = loader::xexCommandListReserveSpace;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xex.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xex_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xexGetCommandListProcAddrTable") );
        result = getTable( version, pDdiTable );
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
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xexGetCommandGraphProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xex_command_graph_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return XE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( loader::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "xexGetCommandGraphProcAddrTable") );
            result = getTable( version, &drv.dditable.xex.CommandGraph );
        }
    }

    if( XE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::xexCommandGraphCreate;
            pDdiTable->pfnDestroy                                  = loader::xexCommandGraphDestroy;
            pDdiTable->pfnClose                                    = loader::xexCommandGraphClose;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.xex.CommandGraph;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( XE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "xexGetCommandGraphProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
