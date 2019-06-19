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
* @file xe_experimental_driver.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
* @endcond
*
******************************************************************************/
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xex_init_params_t params = {
                &flags
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexPrologueCbs.Global;
                    if( nullptr != table.pfnInitCb )
                        table.pfnInitCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xex_init_params_t params = {
                &flags
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexEpilogueCbs.Global;
                    if( nullptr != table.pfnInitCb )
                        table.pfnInitCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xex_command_list_reserve_space_params_t params = {
                &hCommandList,
                &size,
                &ptr
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexPrologueCbs.CommandList;
                    if( nullptr != table.pfnReserveSpaceCb )
                        table.pfnReserveSpaceCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xex_command_list_reserve_space_params_t params = {
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
                        table.pfnReserveSpaceCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xex_command_graph_create_params_t params = {
                &hDevice,
                &desc,
                &phCommandGraph
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexPrologueCbs.CommandGraph;
                    if( nullptr != table.pfnCreateCb )
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        *phCommandGraph = reinterpret_cast<xex_command_graph_handle_t>( context.get() );

        if( context.enableTracing )
        {
            // capture parameters
            xex_command_graph_create_params_t params = {
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
                        table.pfnCreateCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xex_command_graph_destroy_params_t params = {
                &hCommandGraph
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexPrologueCbs.CommandGraph;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }


        if( context.enableTracing )
        {
            // capture parameters
            xex_command_graph_destroy_params_t params = {
                &hCommandGraph
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexEpilogueCbs.CommandGraph;
                    if( nullptr != table.pfnDestroyCb )
                        table.pfnDestroyCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
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

        std::vector<void*> localUserData;
        if( context.enableTracing )
        {
            // capture parameters
            xex_command_graph_close_params_t params = {
                &hCommandGraph
            };

            // call each callback registered
            localUserData.resize( context.tracerData.size() );
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexPrologueCbs.CommandGraph;
                    if( nullptr != table.pfnCloseCb )
                        table.pfnCloseCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        if( context.enableTracing )
        {
            // capture parameters
            xex_command_graph_close_params_t params = {
                &hCommandGraph
            };

            // call each callback registered
            for( uint32_t i = 0; i < context.tracerData.size(); ++i )
                if( context.tracerData[ i ].enabled )
                {
                    auto& table = context.tracerData[ i ].xexEpilogueCbs.CommandGraph;
                    if( nullptr != table.pfnCloseCb )
                        table.pfnCloseCb( &params, result,
                            context.tracerData[ i ].globalUserData,
                            &localUserData[ i ] );
                }
        }

        return result;
    }

} // namespace driver

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

    pDdiTable->pfnCreate                                 = driver::xexCommandGraphCreate;

    pDdiTable->pfnDestroy                                = driver::xexCommandGraphDestroy;

    pDdiTable->pfnClose                                  = driver::xexCommandGraphClose;

    return result;
}

#if defined(__cplusplus)
};
#endif
