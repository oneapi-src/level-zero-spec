/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_core_lib.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
 * @endcond
 *
 */
#include "xe_lib.h"

namespace xe_lib
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
            auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetGlobalProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Global );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetDeviceProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Device );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetDriverProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Driver );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetCommandQueueProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.CommandQueue );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetCommandListProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.CommandList );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetFenceProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Fence );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetEventPoolProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.EventPool );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetEventProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Event );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetImageProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Image );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetModuleProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Module );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetModuleBuildLogProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.ModuleBuildLog );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetFunctionProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Function );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetSamplerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Sampler );
        }

        return result;
    }
} // namespace xe_lib
