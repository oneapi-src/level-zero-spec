/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_libddi.cpp
 *
 */
#include "ze_lib.h"

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::zesInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.Sysman );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanSchedulerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanSchedulerProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanScheduler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanPerformanceFactorProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanPerformanceFactorProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanPerformanceFactor );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanPowerProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanPower );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanFrequencyProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanFrequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanEngineProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanEngineProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanEngine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanStandbyProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanStandby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanFirmwareProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanFirmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanMemoryProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanMemory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanFabricPortProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanFabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanTemperatureProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanTemperature );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanPsuProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanPsuProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanPsu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanFanProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanFan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanLedProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanLedProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanLed );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanRasProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanRasProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanRas );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanDiagnosticsProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanDiagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSysmanEventProcAddrTable") );
            result = getTable( ZE_API_VERSION_0_91, &zesDdiTable.SysmanEvent );
        }

        return result;
    }
} // namespace ze_lib
