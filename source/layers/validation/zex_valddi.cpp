/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_valddi.cpp
 * @version v0.91-275
 *
 */
#include "ze_layer.h"

namespace layer
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
        auto pfnReserveSpace = context.zexDdiTable.CommandList.pfnReserveSpace;

        if( nullptr == pfnReserveSpace )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( 0 == size )
                return ZE_RESULT_ERROR_INVALID_SIZE;

        }

        return pfnReserveSpace( hCommandList, size, ptr );
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
        auto pfnCreate = context.zexDdiTable.CommandGraph.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phCommandGraph )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZEX_COMMAND_GRAPH_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 0 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDevice, desc, phCommandGraph );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zexCommandGraphDestroy
    __zedlllocal ze_result_t __zecall
    zexCommandGraphDestroy(
        zex_command_graph_handle_t hCommandGraph        ///< [in][release] handle of command graph object to destroy
        )
    {
        auto pfnDestroy = context.zexDdiTable.CommandGraph.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandGraph )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hCommandGraph );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zexCommandGraphClose
    __zedlllocal ze_result_t __zecall
    zexCommandGraphClose(
        zex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
        )
    {
        auto pfnClose = context.zexDdiTable.CommandGraph.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandGraph )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnClose( hCommandGraph );
    }

} // namespace layer

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
    auto& dditable = layer::context.zexDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnReserveSpace                             = pDdiTable->pfnReserveSpace;
    pDdiTable->pfnReserveSpace                           = layer::zexCommandListReserveSpace;

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
    auto& dditable = layer::context.zexDdiTable.CommandGraph;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zexCommandGraphCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zexCommandGraphDestroy;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = layer::zexCommandGraphClose;

    return result;
}

#if defined(__cplusplus)
};
#endif
