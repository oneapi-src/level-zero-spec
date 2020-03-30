/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_ldrddi.cpp
 * @version v0.91-275
 *
 */
#include "ze_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    zex_command_list_factory_t          zex_command_list_factory;
    zex_command_graph_factory_t         zex_command_graph_factory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zexCommandListReserveSpace
    __zedlllocal ze_result_t __zecall
    zexCommandListReserveSpace(
        zex_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zex_command_list_object_t*>( hCommandList )->dditable;
        auto pfnReserveSpace = dditable->zex.CommandList.pfnReserveSpace;
        if( nullptr == pfnReserveSpace )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zex_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnReserveSpace( hCommandList, size, ptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zexCommandGraphCreate
    __zedlllocal ze_result_t __zecall
    zexCommandGraphCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const zex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
        zex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->zex.CommandGraph.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phCommandGraph );

        try
        {
            // convert driver handle to loader handle
            *phCommandGraph = reinterpret_cast<zex_command_graph_handle_t>(
                zex_command_graph_factory.getInstance( *phCommandGraph, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zexCommandGraphDestroy
    __zedlllocal ze_result_t __zecall
    zexCommandGraphDestroy(
        zex_command_graph_handle_t hCommandGraph        ///< [in][release] handle of command graph object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zex_command_graph_object_t*>( hCommandGraph )->dditable;
        auto pfnDestroy = dditable->zex.CommandGraph.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandGraph = reinterpret_cast<zex_command_graph_object_t*>( hCommandGraph )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandGraph );

        // release loader handle
        zex_command_graph_factory.release( hCommandGraph );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zexCommandGraphClose
    __zedlllocal ze_result_t __zecall
    zexCommandGraphClose(
        zex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zex_command_graph_object_t*>( hCommandGraph )->dditable;
        auto pfnClose = dditable->zex.CommandGraph.pfnClose;
        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandGraph = reinterpret_cast<zex_command_graph_object_t*>( hCommandGraph )->handle;

        // forward to device-driver
        result = pfnClose( hCommandGraph );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zexGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zex_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zex_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zexGetCommandListProcAddrTable") );
            result = getTable( version, &drv.dditable.zex.CommandList );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnReserveSpace                             = loader::zexCommandListReserveSpace;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zex.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zex_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zexGetCommandListProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandGraph table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zexGetCommandGraphProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zex_command_graph_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zex_pfnGetCommandGraphProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zexGetCommandGraphProcAddrTable") );
            result = getTable( version, &drv.dditable.zex.CommandGraph );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zexCommandGraphCreate;
            pDdiTable->pfnDestroy                                  = loader::zexCommandGraphDestroy;
            pDdiTable->pfnClose                                    = loader::zexCommandGraphClose;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zex.CommandGraph;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zex_pfnGetCommandGraphProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zexGetCommandGraphProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
