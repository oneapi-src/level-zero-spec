/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_tools_lib.cpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
 * @endcond
 *
 */
#include "xet_lib.h"

namespace xet_lib
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
            auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetGlobalProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Global );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetDeviceProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Device );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetCommandListProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.CommandList );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetModuleProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Module );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetFunctionProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetFunctionProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Function );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricGroupProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.MetricGroup );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Metric );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricTracerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.MetricTracer );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricQueryPoolProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.MetricQueryPool );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricQueryProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.MetricQuery );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetTracerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetTracerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Tracer );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Sysman );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanResContainerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanResContainerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanResContainer );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanResourceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanResourceProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanResource );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetPowerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Power );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetFreqDomainProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.FreqDomain );
        }

        return result;
    }
} // namespace xet_lib
