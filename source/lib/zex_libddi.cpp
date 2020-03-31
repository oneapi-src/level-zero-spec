/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_libddi.cpp
 * @version v1.0-r0.9.277
 *
 */
#include "ze_lib.h"

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::zexInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zex_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zexGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zexDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zex_pfnGetCommandGraphProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zexGetCommandGraphProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zexDdiTable.CommandGraph );
        }

        return result;
    }
} // namespace ze_lib
