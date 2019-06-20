/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_experimental_lib.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
 * @endcond
 *
 */
#include "xex_lib.h"

namespace xex_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    xe_result_t context_t::Init()
    {
        loader = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "xe_loader" ) );

        if( NULL == loader )
            return XE_RESULT_ERROR_UNINITIALIZED;

        xe_result_t result = XE_RESULT_SUCCESS;

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xex_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xexGetGlobalProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Global );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xex_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xexGetCommandListProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.CommandList );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xexGetCommandGraphProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.CommandGraph );
        }

        return result;
    }
} // namespace xex_lib
