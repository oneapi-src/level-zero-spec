/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_nullddi.cpp
 * @version v1.0-r0.9.277
 *
 */
#include "ze_null.h"

namespace driver
{
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReserveSpace = context.zexDdiTable.CommandList.pfnReserveSpace;
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
    /// @brief Intercept function for zexCommandGraphCreate
    __zedlllocal ze_result_t __zecall
    zexCommandGraphCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const zex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
        zex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zexDdiTable.CommandGraph.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDevice, desc, phCommandGraph );
        }
        else
        {
            // generic implementation
            *phCommandGraph = reinterpret_cast<zex_command_graph_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zexDdiTable.CommandGraph.pfnDestroy;
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
    /// @brief Intercept function for zexCommandGraphClose
    __zedlllocal ze_result_t __zecall
    zexCommandGraphClose(
        zex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.zexDdiTable.CommandGraph.pfnClose;
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
    /// @brief Intercept function for zexCommandListReserveSpace
    __zedlllocal ze_result_t __zecall
    zexCommandListReserveSpace(
        zex_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        zex_command_list_reserve_space_params_t in_params = {
            &hCommandList,
            &size,
            &ptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexPrologueCbs.CommandList;
                if( nullptr != table.pfnReserveSpaceCb )
                    table.pfnReserveSpaceCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zexCommandListReserveSpace( hCommandList, size, ptr );

        // capture parameters
        zex_command_list_reserve_space_params_t out_params = {
            &hCommandList,
            &size,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexEpilogueCbs.CommandList;
                if( nullptr != table.pfnReserveSpaceCb )
                    table.pfnReserveSpaceCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        zex_command_graph_create_params_t in_params = {
            &hDevice,
            &desc,
            &phCommandGraph
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexPrologueCbs.CommandGraph;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zexCommandGraphCreate( hDevice, desc, phCommandGraph );

        // capture parameters
        zex_command_graph_create_params_t out_params = {
            &hDevice,
            &desc,
            &phCommandGraph
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexEpilogueCbs.CommandGraph;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        zex_command_graph_destroy_params_t in_params = {
            &hCommandGraph
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexPrologueCbs.CommandGraph;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zexCommandGraphDestroy( hCommandGraph );

        // capture parameters
        zex_command_graph_destroy_params_t out_params = {
            &hCommandGraph
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexEpilogueCbs.CommandGraph;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        zex_command_graph_close_params_t in_params = {
            &hCommandGraph
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexPrologueCbs.CommandGraph;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zexCommandGraphClose( hCommandGraph );

        // capture parameters
        zex_command_graph_close_params_t out_params = {
            &hCommandGraph
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zexEpilogueCbs.CommandGraph;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

} // namespace instrumented

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zexGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zex_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReserveSpace                           = instrumented::zexCommandListReserveSpace;
    else
        pDdiTable->pfnReserveSpace                           = driver::zexCommandListReserveSpace;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandGraph table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zexGetCommandGraphProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zex_command_graph_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zexCommandGraphCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zexCommandGraphCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zexCommandGraphDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zexCommandGraphDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnClose                                  = instrumented::zexCommandGraphClose;
    else
        pDdiTable->pfnClose                                  = driver::zexCommandGraphClose;

    return result;
}

#if defined(__cplusplus)
};
#endif
