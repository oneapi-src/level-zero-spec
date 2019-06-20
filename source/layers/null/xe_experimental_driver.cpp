/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_experimental_driver.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
 * @endcond
 *
 */
#include "xe_null.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xexInit
    xe_result_t __xecall
    xexInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInit = context.xexDdiTable.Global.pfnInit;
        if( nullptr != pfnInit )
        {
            result = pfnInit( flags );
        }
        else
        {
            // generic implementation
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReserveSpace = context.xexDdiTable.CommandList.pfnReserveSpace;
        if( nullptr != pfnReserveSpace )
        {
            result = pfnReserveSpace( hCommandList, size, ptr );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.xexDdiTable.CommandGraph.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phCommandGraph );
        }
        else
        {
            // generic implementation
            *phCommandGraph = reinterpret_cast<xex_command_graph_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.xexDdiTable.CommandGraph.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hCommandGraph );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.xexDdiTable.CommandGraph.pfnClose;
        if( nullptr != pfnClose )
        {
            result = pfnClose( hCommandGraph );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

} // namespace driver

namespace instrumented
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for xexInit
    xe_result_t __xecall
    xexInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        xe_result_t result = XE_RESULT_SUCCESS;

        // capture parameters
        xex_init_params_t in_params = {
            &flags
        };

        // call each callback registered
        std::vector<void*> localUserData;
        localUserData.resize( context.tracerData.size() );
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexPrologueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &in_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

        result = driver::xexInit( flags );

        // capture parameters
        xex_init_params_t out_params = {
            &flags
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexEpilogueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &out_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
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

        // capture parameters
        xex_command_list_reserve_space_params_t in_params = {
            &hCommandList,
            &size,
            &ptr
        };

        // call each callback registered
        std::vector<void*> localUserData;
        localUserData.resize( context.tracerData.size() );
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexPrologueCbs.CommandList;
                if( nullptr != table.pfnReserveSpaceCb )
                    table.pfnReserveSpaceCb( &in_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

        result = driver::xexCommandListReserveSpace( hCommandList, size, ptr );

        // capture parameters
        xex_command_list_reserve_space_params_t out_params = {
            &hCommandList,
            &size,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexEpilogueCbs.CommandList;
                if( nullptr != table.pfnReserveSpaceCb )
                    table.pfnReserveSpaceCb( &out_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

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

        // capture parameters
        xex_command_graph_create_params_t in_params = {
            &hDevice,
            &desc,
            &phCommandGraph
        };

        // call each callback registered
        std::vector<void*> localUserData;
        localUserData.resize( context.tracerData.size() );
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexPrologueCbs.CommandGraph;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

        result = driver::xexCommandGraphCreate( hDevice, desc, phCommandGraph );

        // capture parameters
        xex_command_graph_create_params_t out_params = {
            &hDevice,
            &desc,
            &phCommandGraph
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexEpilogueCbs.CommandGraph;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
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

        // capture parameters
        xex_command_graph_destroy_params_t in_params = {
            &hCommandGraph
        };

        // call each callback registered
        std::vector<void*> localUserData;
        localUserData.resize( context.tracerData.size() );
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexPrologueCbs.CommandGraph;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

        result = driver::xexCommandGraphDestroy( hCommandGraph );

        // capture parameters
        xex_command_graph_destroy_params_t out_params = {
            &hCommandGraph
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexEpilogueCbs.CommandGraph;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

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

        // capture parameters
        xex_command_graph_close_params_t in_params = {
            &hCommandGraph
        };

        // call each callback registered
        std::vector<void*> localUserData;
        localUserData.resize( context.tracerData.size() );
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexPrologueCbs.CommandGraph;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &in_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

        result = driver::xexCommandGraphClose( hCommandGraph );

        // capture parameters
        xex_command_graph_close_params_t out_params = {
            &hCommandGraph
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].xexEpilogueCbs.CommandGraph;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &out_params, result,
                        context.tracerData[ i ].globalUserData,
                        &localUserData[ i ] );
            }

        return result;
    }

} // namespace instrumented

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnInit                                   = instrumented::xexInit;
    else
        pDdiTable->pfnInit                                   = driver::xexInit;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReserveSpace                           = instrumented::xexCommandListReserveSpace;
    else
        pDdiTable->pfnReserveSpace                           = driver::xexCommandListReserveSpace;

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
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver::context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::xexCommandGraphCreate;
    else
        pDdiTable->pfnCreate                                 = driver::xexCommandGraphCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::xexCommandGraphDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::xexCommandGraphDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnClose                                  = instrumented::xexCommandGraphClose;
    else
        pDdiTable->pfnClose                                  = driver::xexCommandGraphClose;

    return result;
}

#if defined(__cplusplus)
};
#endif
