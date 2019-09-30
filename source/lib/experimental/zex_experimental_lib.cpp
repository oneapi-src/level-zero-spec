/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_experimental_lib.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
 * @endcond
 *
 */
#include "zex_lib.h"

namespace zex_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    ze_result_t context_t::Init()
    {
        loader = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "ze_loader" ) );

        if( NULL == loader )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zex_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zexGetGlobalProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zex_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zexGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zex_pfnGetCommandGraphProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zexGetCommandGraphProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.CommandGraph );
        }

        return result;
    }
} // namespace zex_lib
