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
            auto getTable = reinterpret_cast<xet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetKernelProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Kernel );
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
            auto getTable = reinterpret_cast<xet_pfnGetSysmanPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanPowerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanPower );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanFrequencyProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanFrequency );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanEngineProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanEngineProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanEngine );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanStandbyProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanStandby );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanFirmwareProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanFirmware );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanMemoryProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanMemory );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanLinkSwitchProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanLinkSwitchProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanLinkSwitch );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanLinkPortProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanLinkPortProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanLinkPort );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanTemperatureProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanTemperature );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanPsuProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanPsuProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanPsu );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanFanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanFanProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanFan );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanLedProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanLedProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanLed );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanRasProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanRasProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanRas );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetSysmanDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetSysmanDiagnosticsProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.SysmanDiagnostics );
        }

        return result;
    }
} // namespace xet_lib
