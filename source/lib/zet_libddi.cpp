/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_libddi.cpp
 *
 */
#include "ze_lib.h"

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::zetInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetModuleProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetKernelProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricTracerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricTracerProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.MetricTracer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryPoolProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetTracerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetTracerProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.Tracer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.Sysman );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanSchedulerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanSchedulerProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanScheduler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanPerformanceFactorProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanPerformanceFactorProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanPerformanceFactor );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanPowerProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanPower );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFrequencyProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanFrequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanEngineProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanEngineProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanEngine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanStandbyProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanStandby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFirmwareProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanFirmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanMemoryProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanMemory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFabricPortProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanFabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanTemperatureProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanTemperature );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanPsuProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanPsuProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanPsu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFanProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanFan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanLedProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanLedProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanLed );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanRasProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanRasProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanRas );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanDiagnosticsProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanDiagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanEventProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.SysmanEvent );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDebugProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zetDdiTable.Debug );
        }

        return result;
    }
} // namespace ze_lib
