/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_valddi.cpp
 *
 */
#include "ze_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanGet
    __zedlllocal ze_result_t __zecall
    zesSysmanGet(
        zes_device_handle_t hDevice,                    ///< [in] Handle of the device
        zes_sysman_version_t version,                   ///< [in] Sysman version that application was built with
        zes_sysman_handle_t* phSysman                   ///< [out] Handle for accessing Sysman features
        )
    {
        auto pfnGet = context.zesDdiTable.Sysman.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 91 <= version )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == phSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hDevice, version, phSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDeviceGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanDeviceGetProperties(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_sysman_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto pfnDeviceGetProperties = context.zesDdiTable.Sysman.pfnDeviceGetProperties;

        if( nullptr == pfnDeviceGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnDeviceGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDeviceGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanDeviceGetState(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_sysman_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto pfnDeviceGetState = context.zesDdiTable.Sysman.pfnDeviceGetState;

        if( nullptr == pfnDeviceGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnDeviceGetState( hSysman, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDeviceReset
    __zedlllocal ze_result_t __zecall
    zesSysmanDeviceReset(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
        )
    {
        auto pfnDeviceReset = context.zesDdiTable.Sysman.pfnDeviceReset;

        if( nullptr == pfnDeviceReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDeviceReset( hSysman, force );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerGet
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_sched_handle_t* phScheduler          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnSchedulerGet = context.zesDdiTable.Sysman.pfnSchedulerGet;

        if( nullptr == pfnSchedulerGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerGet( hSysman, pCount, phScheduler );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerGetProperties(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanScheduler.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hScheduler, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerGetCurrentMode
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerGetCurrentMode(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        auto pfnGetCurrentMode = context.zesDdiTable.SysmanScheduler.pfnGetCurrentMode;

        if( nullptr == pfnGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetCurrentMode( hScheduler, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerGetTimeoutModeProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerGetTimeoutModeProperties(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto pfnGetTimeoutModeProperties = context.zesDdiTable.SysmanScheduler.pfnGetTimeoutModeProperties;

        if( nullptr == pfnGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerGetTimesliceModeProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerGetTimesliceModeProperties(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto pfnGetTimesliceModeProperties = context.zesDdiTable.SysmanScheduler.pfnGetTimesliceModeProperties;

        if( nullptr == pfnGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerSetTimeoutMode
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerSetTimeoutMode(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetTimeoutMode = context.zesDdiTable.SysmanScheduler.pfnSetTimeoutMode;

        if( nullptr == pfnSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerSetTimesliceMode
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerSetTimesliceMode(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetTimesliceMode = context.zesDdiTable.SysmanScheduler.pfnSetTimesliceMode;

        if( nullptr == pfnSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerSetExclusiveMode
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerSetExclusiveMode(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetExclusiveMode = context.zesDdiTable.SysmanScheduler.pfnSetExclusiveMode;

        if( nullptr == pfnSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetExclusiveMode( hScheduler, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerSetComputeUnitDebugMode
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerSetComputeUnitDebugMode(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetComputeUnitDebugMode = context.zesDdiTable.SysmanScheduler.pfnSetComputeUnitDebugMode;

        if( nullptr == pfnSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPerformanceFactorGet
    __zedlllocal ze_result_t __zecall
    zesSysmanPerformanceFactorGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_perf_handle_t* phPerf                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnPerformanceFactorGet = context.zesDdiTable.Sysman.pfnPerformanceFactorGet;

        if( nullptr == pfnPerformanceFactorGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPerformanceFactorGet( hSysman, pCount, phPerf );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPerformanceFactorGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanPerformanceFactorGetProperties(
        zes_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
        zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanPerformanceFactor.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPerf )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPerf, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPerformanceFactorGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanPerformanceFactorGetConfig(
        zes_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    {
        auto pfnGetConfig = context.zesDdiTable.SysmanPerformanceFactor.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPerf )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pFactor )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hPerf, pFactor );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPerformanceFactorSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanPerformanceFactorSetConfig(
        zes_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.SysmanPerformanceFactor.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPerf )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetConfig( hPerf, factor );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanProcessesGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanProcessesGetState(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of processes currently using the device.
                                                        ///< if count is non-zero but less than the number of processes, the driver
                                                        ///< will set to the number of processes currently using the device and
                                                        ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                        ///< if count is larger than the number of processes, then the driver will
                                                        ///< update the value with the correct number of processes that are returned.
        zes_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                        ///< one for each process currently using the device
        )
    {
        auto pfnProcessesGetState = context.zesDdiTable.Sysman.pfnProcessesGetState;

        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnProcessesGetState( hSysman, pCount, pProcesses );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPciGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanPciGetProperties(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        auto pfnPciGetProperties = context.zesDdiTable.Sysman.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPciGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanPciGetState(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        auto pfnPciGetState = context.zesDdiTable.Sysman.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetState( hSysman, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPciGetBars
    __zedlllocal ze_result_t __zecall
    zesSysmanPciGetBars(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of bars.
                                                        ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                        ///< if count is larger than the number of bar, then the driver will update
                                                        ///< the value with the correct number of bars that are returned.
        zes_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of bar properties
        )
    {
        auto pfnPciGetBars = context.zesDdiTable.Sysman.pfnPciGetBars;

        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetBars( hSysman, pCount, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPciGetStats
    __zedlllocal ze_result_t __zecall
    zesSysmanPciGetStats(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        auto pfnPciGetStats = context.zesDdiTable.Sysman.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetStats( hSysman, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerGet
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnPowerGet = context.zesDdiTable.Sysman.pfnPowerGet;

        if( nullptr == pfnPowerGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPowerGet( hSysman, pCount, phPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerGetProperties(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanPower.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPower, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerGetEnergyCounter
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerGetEnergyCounter(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto pfnGetEnergyCounter = context.zesDdiTable.SysmanPower.pfnGetEnergyCounter;

        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pEnergy )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetEnergyCounter( hPower, pEnergy );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerGetLimits
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerGetLimits(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit.
        zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit.
        zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit.
        )
    {
        auto pfnGetLimits = context.zesDdiTable.SysmanPower.pfnGetLimits;

        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerSetLimits
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerSetLimits(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        auto pfnSetLimits = context.zesDdiTable.SysmanPower.pfnSetLimits;

        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerGetEnergyThreshold
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerGetEnergyThreshold(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        auto pfnGetEnergyThreshold = context.zesDdiTable.SysmanPower.pfnGetEnergyThreshold;

        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThreshold )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetEnergyThreshold( hPower, pThreshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerSetEnergyThreshold
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerSetEnergyThreshold(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        auto pfnSetEnergyThreshold = context.zesDdiTable.SysmanPower.pfnSetEnergyThreshold;

        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetEnergyThreshold( hPower, threshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGet
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFrequencyGet = context.zesDdiTable.Sysman.pfnFrequencyGet;

        if( nullptr == pfnFrequencyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFrequencyGet( hSysman, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGetProperties(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanFrequency.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFrequency, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGetAvailableClocks
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGetAvailableClocks(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of frequencies available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                        ///< If count is larger than the number of frequencies available, then the
                                                        ///< driver will update the value with the correct number of frequencies available.
        double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                        ///< MHz and sorted from slowest to fastest
        )
    {
        auto pfnGetAvailableClocks = context.zesDdiTable.SysmanFrequency.pfnGetAvailableClocks;

        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGetRange
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGetRange(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetRange = context.zesDdiTable.SysmanFrequency.pfnGetRange;

        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencySetRange
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencySetRange(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnSetRange = context.zesDdiTable.SysmanFrequency.pfnSetRange;

        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGetState(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanFrequency.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hFrequency, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGetThrottleTime
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGetThrottleTime(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetThrottleTime = context.zesDdiTable.SysmanFrequency.pfnGetThrottleTime;

        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThrottleTime )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetThrottleTime( hFrequency, pThrottleTime );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcGetCapabilities
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcGetCapabilities(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        auto pfnOcGetCapabilities = context.zesDdiTable.SysmanFrequency.pfnOcGetCapabilities;

        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcCapabilities )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcGetConfig(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zes_oc_config_t.
        )
    {
        auto pfnOcGetConfig = context.zesDdiTable.SysmanFrequency.pfnOcGetConfig;

        if( nullptr == pfnOcGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcConfiguration )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetConfig( hFrequency, pOcConfiguration );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcSetConfig(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zes_oc_config_t.
        ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                        ///< in order to enable the new overclock settings.
        )
    {
        auto pfnOcSetConfig = context.zesDdiTable.SysmanFrequency.pfnOcSetConfig;

        if( nullptr == pfnOcSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcConfiguration )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pDeviceRestart )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcGetIccMax
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcGetIccMax(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    {
        auto pfnOcGetIccMax = context.zesDdiTable.SysmanFrequency.pfnOcGetIccMax;

        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcIccMax )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetIccMax( hFrequency, pOcIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcSetIccMax
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcSetIccMax(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        auto pfnOcSetIccMax = context.zesDdiTable.SysmanFrequency.pfnOcSetIccMax;

        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetIccMax( hFrequency, ocIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcGetTjMax
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcGetTjMax(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    {
        auto pfnOcGetTjMax = context.zesDdiTable.SysmanFrequency.pfnOcGetTjMax;

        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcTjMax )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetTjMax( hFrequency, pOcTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcSetTjMax
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcSetTjMax(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        auto pfnOcSetTjMax = context.zesDdiTable.SysmanFrequency.pfnOcSetTjMax;

        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetTjMax( hFrequency, ocTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEngineGet
    __zedlllocal ze_result_t __zecall
    zesSysmanEngineGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnEngineGet = context.zesDdiTable.Sysman.pfnEngineGet;

        if( nullptr == pfnEngineGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEngineGet( hSysman, pCount, phEngine );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEngineGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanEngineGetProperties(
        zes_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanEngine.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hEngine, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEngineGetActivity
    __zedlllocal ze_result_t __zecall
    zesSysmanEngineGetActivity(
        zes_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    {
        auto pfnGetActivity = context.zesDdiTable.SysmanEngine.pfnGetActivity;

        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetActivity( hEngine, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanStandbyGet
    __zedlllocal ze_result_t __zecall
    zesSysmanStandbyGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnStandbyGet = context.zesDdiTable.Sysman.pfnStandbyGet;

        if( nullptr == pfnStandbyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnStandbyGet( hSysman, pCount, phStandby );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanStandbyGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanStandbyGetProperties(
        zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanStandby.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hStandby, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanStandbyGetMode
    __zedlllocal ze_result_t __zecall
    zesSysmanStandbyGetMode(
        zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        auto pfnGetMode = context.zesDdiTable.SysmanStandby.pfnGetMode;

        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMode( hStandby, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanStandbySetMode
    __zedlllocal ze_result_t __zecall
    zesSysmanStandbySetMode(
        zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        auto pfnSetMode = context.zesDdiTable.SysmanStandby.pfnSetMode;

        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 1 <= mode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetMode( hStandby, mode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFirmwareGet
    __zedlllocal ze_result_t __zecall
    zesSysmanFirmwareGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFirmwareGet = context.zesDdiTable.Sysman.pfnFirmwareGet;

        if( nullptr == pfnFirmwareGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFirmwareGet( hSysman, pCount, phFirmware );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFirmwareGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanFirmwareGetProperties(
        zes_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanFirmware.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFirmware, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFirmwareGetChecksum
    __zedlllocal ze_result_t __zecall
    zesSysmanFirmwareGetChecksum(
        zes_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
        )
    {
        auto pfnGetChecksum = context.zesDdiTable.SysmanFirmware.pfnGetChecksum;

        if( nullptr == pfnGetChecksum )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pChecksum )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetChecksum( hFirmware, pChecksum );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFirmwareFlash
    __zedlllocal ze_result_t __zecall
    zesSysmanFirmwareFlash(
        zes_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto pfnFlash = context.zesDdiTable.SysmanFirmware.pfnFlash;

        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pImage )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFlash( hFirmware, pImage, size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanMemoryGet
    __zedlllocal ze_result_t __zecall
    zesSysmanMemoryGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnMemoryGet = context.zesDdiTable.Sysman.pfnMemoryGet;

        if( nullptr == pfnMemoryGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnMemoryGet( hSysman, pCount, phMemory );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanMemoryGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanMemoryGetProperties(
        zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanMemory.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hMemory, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanMemoryGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanMemoryGetState(
        zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanMemory.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hMemory, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanMemoryGetBandwidth
    __zedlllocal ze_result_t __zecall
    zesSysmanMemoryGetBandwidth(
        zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the current health, free memory, total memory
                                                        ///< size.
        )
    {
        auto pfnGetBandwidth = context.zesDdiTable.SysmanMemory.pfnGetBandwidth;

        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pBandwidth )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetBandwidth( hMemory, pBandwidth );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGet
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_fabric_port_handle_t* phPort         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFabricPortGet = context.zesDdiTable.Sysman.pfnFabricPortGet;

        if( nullptr == pfnFabricPortGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFabricPortGet( hSysman, pCount, phPort );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetProperties(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanFabricPort.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPort, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetLinkType
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetLinkType(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
        zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    {
        auto pfnGetLinkType = context.zesDdiTable.SysmanFabricPort.pfnGetLinkType;

        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLinkType )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetLinkType( hPort, verbose, pLinkType );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetConfig(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.SysmanFabricPort.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hPort, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortSetConfig(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.SysmanFabricPort.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hPort, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetState(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanFabricPort.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hPort, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetThroughput
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetThroughput(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        auto pfnGetThroughput = context.zesDdiTable.SysmanFabricPort.pfnGetThroughput;

        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThroughput )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetThroughput( hPort, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureGet
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnTemperatureGet = context.zesDdiTable.Sysman.pfnTemperatureGet;

        if( nullptr == pfnTemperatureGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnTemperatureGet( hSysman, pCount, phTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureGetProperties(
        zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanTemperature.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hTemperature, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureGetConfig(
        zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.SysmanTemperature.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hTemperature, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureSetConfig(
        zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.SysmanTemperature.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hTemperature, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureGetState(
        zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanTemperature.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hTemperature, pTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPsuGet
    __zedlllocal ze_result_t __zecall
    zesSysmanPsuGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnPsuGet = context.zesDdiTable.Sysman.pfnPsuGet;

        if( nullptr == pfnPsuGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPsuGet( hSysman, pCount, phPsu );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPsuGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanPsuGetProperties(
        zes_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanPsu.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPsu, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPsuGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanPsuGetState(
        zes_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanPsu.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hPsu, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanGet
    __zedlllocal ze_result_t __zecall
    zesSysmanFanGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFanGet = context.zesDdiTable.Sysman.pfnFanGet;

        if( nullptr == pfnFanGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFanGet( hSysman, pCount, phFan );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanFanGetProperties(
        zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanFan.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFan, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFanGetConfig(
        zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.SysmanFan.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFanSetConfig(
        zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const zes_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.SysmanFan.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanFanGetState(
        zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested.
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanFan.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 1 <= units )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pSpeed )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hFan, units, pSpeed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanLedGet
    __zedlllocal ze_result_t __zecall
    zesSysmanLedGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnLedGet = context.zesDdiTable.Sysman.pfnLedGet;

        if( nullptr == pfnLedGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnLedGet( hSysman, pCount, phLed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanLedGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanLedGetProperties(
        zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanLed.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hLed, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanLedGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanLedGetState(
        zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanLed.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanLedSetState
    __zedlllocal ze_result_t __zecall
    zesSysmanLedSetState(
        zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const zes_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        auto pfnSetState = context.zesDdiTable.SysmanLed.pfnSetState;

        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanRasGet
    __zedlllocal ze_result_t __zecall
    zesSysmanRasGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnRasGet = context.zesDdiTable.Sysman.pfnRasGet;

        if( nullptr == pfnRasGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRasGet( hSysman, pCount, phRas );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanRasGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanRasGetProperties(
        zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanRas.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hRas, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanRasGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanRasGetConfig(
        zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    {
        auto pfnGetConfig = context.zesDdiTable.SysmanRas.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hRas, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanRasSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanRasSetConfig(
        zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        auto pfnSetConfig = context.zesDdiTable.SysmanRas.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hRas, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanRasGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanRasGetState(
        zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in,out] The number total number of errors that have occurred
        zes_ras_details_t* pDetails                     ///< [in,out][optional] Breakdown of where errors have occurred
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanRas.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pTotalErrors )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hRas, clear, pTotalErrors, pDetails );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEventGet
    __zedlllocal ze_result_t __zecall
    zesSysmanEventGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zes_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
        )
    {
        auto pfnEventGet = context.zesDdiTable.Sysman.pfnEventGet;

        if( nullptr == pfnEventGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEventGet( hSysman, phEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEventGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanEventGetConfig(
        zes_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        zes_event_config_t* pConfig                     ///< [in,out] Will contain the current event configuration (list of
                                                        ///< registered events).
        )
    {
        auto pfnGetConfig = context.zesDdiTable.SysmanEvent.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hEvent, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEventSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanEventSetConfig(
        zes_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        const zes_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
        )
    {
        auto pfnSetConfig = context.zesDdiTable.SysmanEvent.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hEvent, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEventGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanEventGetState(
        zes_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device.
        ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
        uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_sysman_event_type_t that have been
                                                        ///< triggered by this device.
        )
    {
        auto pfnGetState = context.zesDdiTable.SysmanEvent.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hEvent, clear, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEventListen
    __zedlllocal ze_result_t __zecall
    zesSysmanEventListen(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                        ///< ::ZES_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                        ///< ::ZES_EVENT_WAIT_INFINITE to block until events arrive.
        uint32_t count,                                 ///< [in] Number of handles in phEvents
        zes_sysman_event_handle_t* phEvents,            ///< [in][range(0, count)] Handle of events that should be listened to
        uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_sysman_event_type_t that have been
                                                        ///< triggered by any of the supplied event handles. If timeout is not
                                                        ///< ::ZES_EVENT_WAIT_INFINITE and this value is
                                                        ///< ::ZES_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
        )
    {
        auto pfnListen = context.zesDdiTable.SysmanEvent.pfnListen;

        if( nullptr == pfnListen )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnListen( hDriver, timeout, count, phEvents, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDiagnosticsGet
    __zedlllocal ze_result_t __zecall
    zesSysmanDiagnosticsGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnDiagnosticsGet = context.zesDdiTable.Sysman.pfnDiagnosticsGet;

        if( nullptr == pfnDiagnosticsGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDiagnosticsGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanDiagnosticsGetProperties(
        zes_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
        )
    {
        auto pfnGetProperties = context.zesDdiTable.SysmanDiagnostics.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hDiagnostics, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDiagnosticsGetTests
    __zedlllocal ze_result_t __zecall
    zesSysmanDiagnosticsGetTests(
        zes_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of tests available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                        ///< If count is larger than the number of tests available, then the driver
                                                        ///< will update the value with the correct number of tests available.
        zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                        ///< increasing value of ::zes_diag_test_t.index
        )
    {
        auto pfnGetTests = context.zesDdiTable.SysmanDiagnostics.pfnGetTests;

        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTests( hDiagnostics, pCount, pTests );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDiagnosticsRunTests
    __zedlllocal ze_result_t __zecall
    zesSysmanDiagnosticsRunTests(
        zes_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
        )
    {
        auto pfnRunTests = context.zesDdiTable.SysmanDiagnostics.pfnRunTests;

        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pResult )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRunTests( hDiagnostics, start, end, pResult );
    }

} // namespace layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Sysman;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zesSysmanGet;

    dditable.pfnDeviceGetProperties                      = pDdiTable->pfnDeviceGetProperties;
    pDdiTable->pfnDeviceGetProperties                    = layer::zesSysmanDeviceGetProperties;

    dditable.pfnDeviceGetState                           = pDdiTable->pfnDeviceGetState;
    pDdiTable->pfnDeviceGetState                         = layer::zesSysmanDeviceGetState;

    dditable.pfnDeviceReset                              = pDdiTable->pfnDeviceReset;
    pDdiTable->pfnDeviceReset                            = layer::zesSysmanDeviceReset;

    dditable.pfnSchedulerGet                             = pDdiTable->pfnSchedulerGet;
    pDdiTable->pfnSchedulerGet                           = layer::zesSysmanSchedulerGet;

    dditable.pfnPerformanceFactorGet                     = pDdiTable->pfnPerformanceFactorGet;
    pDdiTable->pfnPerformanceFactorGet                   = layer::zesSysmanPerformanceFactorGet;

    dditable.pfnProcessesGetState                        = pDdiTable->pfnProcessesGetState;
    pDdiTable->pfnProcessesGetState                      = layer::zesSysmanProcessesGetState;

    dditable.pfnPciGetProperties                         = pDdiTable->pfnPciGetProperties;
    pDdiTable->pfnPciGetProperties                       = layer::zesSysmanPciGetProperties;

    dditable.pfnPciGetState                              = pDdiTable->pfnPciGetState;
    pDdiTable->pfnPciGetState                            = layer::zesSysmanPciGetState;

    dditable.pfnPciGetBars                               = pDdiTable->pfnPciGetBars;
    pDdiTable->pfnPciGetBars                             = layer::zesSysmanPciGetBars;

    dditable.pfnPciGetStats                              = pDdiTable->pfnPciGetStats;
    pDdiTable->pfnPciGetStats                            = layer::zesSysmanPciGetStats;

    dditable.pfnPowerGet                                 = pDdiTable->pfnPowerGet;
    pDdiTable->pfnPowerGet                               = layer::zesSysmanPowerGet;

    dditable.pfnFrequencyGet                             = pDdiTable->pfnFrequencyGet;
    pDdiTable->pfnFrequencyGet                           = layer::zesSysmanFrequencyGet;

    dditable.pfnEngineGet                                = pDdiTable->pfnEngineGet;
    pDdiTable->pfnEngineGet                              = layer::zesSysmanEngineGet;

    dditable.pfnStandbyGet                               = pDdiTable->pfnStandbyGet;
    pDdiTable->pfnStandbyGet                             = layer::zesSysmanStandbyGet;

    dditable.pfnFirmwareGet                              = pDdiTable->pfnFirmwareGet;
    pDdiTable->pfnFirmwareGet                            = layer::zesSysmanFirmwareGet;

    dditable.pfnMemoryGet                                = pDdiTable->pfnMemoryGet;
    pDdiTable->pfnMemoryGet                              = layer::zesSysmanMemoryGet;

    dditable.pfnFabricPortGet                            = pDdiTable->pfnFabricPortGet;
    pDdiTable->pfnFabricPortGet                          = layer::zesSysmanFabricPortGet;

    dditable.pfnTemperatureGet                           = pDdiTable->pfnTemperatureGet;
    pDdiTable->pfnTemperatureGet                         = layer::zesSysmanTemperatureGet;

    dditable.pfnPsuGet                                   = pDdiTable->pfnPsuGet;
    pDdiTable->pfnPsuGet                                 = layer::zesSysmanPsuGet;

    dditable.pfnFanGet                                   = pDdiTable->pfnFanGet;
    pDdiTable->pfnFanGet                                 = layer::zesSysmanFanGet;

    dditable.pfnLedGet                                   = pDdiTable->pfnLedGet;
    pDdiTable->pfnLedGet                                 = layer::zesSysmanLedGet;

    dditable.pfnRasGet                                   = pDdiTable->pfnRasGet;
    pDdiTable->pfnRasGet                                 = layer::zesSysmanRasGet;

    dditable.pfnEventGet                                 = pDdiTable->pfnEventGet;
    pDdiTable->pfnEventGet                               = layer::zesSysmanEventGet;

    dditable.pfnDiagnosticsGet                           = pDdiTable->pfnDiagnosticsGet;
    pDdiTable->pfnDiagnosticsGet                         = layer::zesSysmanDiagnosticsGet;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanScheduler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanSchedulerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_scheduler_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanScheduler;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanSchedulerGetProperties;

    dditable.pfnGetCurrentMode                           = pDdiTable->pfnGetCurrentMode;
    pDdiTable->pfnGetCurrentMode                         = layer::zesSysmanSchedulerGetCurrentMode;

    dditable.pfnGetTimeoutModeProperties                 = pDdiTable->pfnGetTimeoutModeProperties;
    pDdiTable->pfnGetTimeoutModeProperties               = layer::zesSysmanSchedulerGetTimeoutModeProperties;

    dditable.pfnGetTimesliceModeProperties               = pDdiTable->pfnGetTimesliceModeProperties;
    pDdiTable->pfnGetTimesliceModeProperties             = layer::zesSysmanSchedulerGetTimesliceModeProperties;

    dditable.pfnSetTimeoutMode                           = pDdiTable->pfnSetTimeoutMode;
    pDdiTable->pfnSetTimeoutMode                         = layer::zesSysmanSchedulerSetTimeoutMode;

    dditable.pfnSetTimesliceMode                         = pDdiTable->pfnSetTimesliceMode;
    pDdiTable->pfnSetTimesliceMode                       = layer::zesSysmanSchedulerSetTimesliceMode;

    dditable.pfnSetExclusiveMode                         = pDdiTable->pfnSetExclusiveMode;
    pDdiTable->pfnSetExclusiveMode                       = layer::zesSysmanSchedulerSetExclusiveMode;

    dditable.pfnSetComputeUnitDebugMode                  = pDdiTable->pfnSetComputeUnitDebugMode;
    pDdiTable->pfnSetComputeUnitDebugMode                = layer::zesSysmanSchedulerSetComputeUnitDebugMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPerformanceFactor table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPerformanceFactorProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_performance_factor_dditable_t* pDdiTable ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanPerformanceFactor;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanPerformanceFactorGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesSysmanPerformanceFactorGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesSysmanPerformanceFactorSetConfig;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanPower;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanPowerGetProperties;

    dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
    pDdiTable->pfnGetEnergyCounter                       = layer::zesSysmanPowerGetEnergyCounter;

    dditable.pfnGetLimits                                = pDdiTable->pfnGetLimits;
    pDdiTable->pfnGetLimits                              = layer::zesSysmanPowerGetLimits;

    dditable.pfnSetLimits                                = pDdiTable->pfnSetLimits;
    pDdiTable->pfnSetLimits                              = layer::zesSysmanPowerSetLimits;

    dditable.pfnGetEnergyThreshold                       = pDdiTable->pfnGetEnergyThreshold;
    pDdiTable->pfnGetEnergyThreshold                     = layer::zesSysmanPowerGetEnergyThreshold;

    dditable.pfnSetEnergyThreshold                       = pDdiTable->pfnSetEnergyThreshold;
    pDdiTable->pfnSetEnergyThreshold                     = layer::zesSysmanPowerSetEnergyThreshold;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanFrequency;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanFrequencyGetProperties;

    dditable.pfnGetAvailableClocks                       = pDdiTable->pfnGetAvailableClocks;
    pDdiTable->pfnGetAvailableClocks                     = layer::zesSysmanFrequencyGetAvailableClocks;

    dditable.pfnGetRange                                 = pDdiTable->pfnGetRange;
    pDdiTable->pfnGetRange                               = layer::zesSysmanFrequencyGetRange;

    dditable.pfnSetRange                                 = pDdiTable->pfnSetRange;
    pDdiTable->pfnSetRange                               = layer::zesSysmanFrequencySetRange;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanFrequencyGetState;

    dditable.pfnGetThrottleTime                          = pDdiTable->pfnGetThrottleTime;
    pDdiTable->pfnGetThrottleTime                        = layer::zesSysmanFrequencyGetThrottleTime;

    dditable.pfnOcGetCapabilities                        = pDdiTable->pfnOcGetCapabilities;
    pDdiTable->pfnOcGetCapabilities                      = layer::zesSysmanFrequencyOcGetCapabilities;

    dditable.pfnOcGetConfig                              = pDdiTable->pfnOcGetConfig;
    pDdiTable->pfnOcGetConfig                            = layer::zesSysmanFrequencyOcGetConfig;

    dditable.pfnOcSetConfig                              = pDdiTable->pfnOcSetConfig;
    pDdiTable->pfnOcSetConfig                            = layer::zesSysmanFrequencyOcSetConfig;

    dditable.pfnOcGetIccMax                              = pDdiTable->pfnOcGetIccMax;
    pDdiTable->pfnOcGetIccMax                            = layer::zesSysmanFrequencyOcGetIccMax;

    dditable.pfnOcSetIccMax                              = pDdiTable->pfnOcSetIccMax;
    pDdiTable->pfnOcSetIccMax                            = layer::zesSysmanFrequencyOcSetIccMax;

    dditable.pfnOcGetTjMax                               = pDdiTable->pfnOcGetTjMax;
    pDdiTable->pfnOcGetTjMax                             = layer::zesSysmanFrequencyOcGetTjMax;

    dditable.pfnOcSetTjMax                               = pDdiTable->pfnOcSetTjMax;
    pDdiTable->pfnOcSetTjMax                             = layer::zesSysmanFrequencyOcSetTjMax;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanEngine;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanEngineGetProperties;

    dditable.pfnGetActivity                              = pDdiTable->pfnGetActivity;
    pDdiTable->pfnGetActivity                            = layer::zesSysmanEngineGetActivity;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanStandby;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanStandbyGetProperties;

    dditable.pfnGetMode                                  = pDdiTable->pfnGetMode;
    pDdiTable->pfnGetMode                                = layer::zesSysmanStandbyGetMode;

    dditable.pfnSetMode                                  = pDdiTable->pfnSetMode;
    pDdiTable->pfnSetMode                                = layer::zesSysmanStandbySetMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanFirmware;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanFirmwareGetProperties;

    dditable.pfnGetChecksum                              = pDdiTable->pfnGetChecksum;
    pDdiTable->pfnGetChecksum                            = layer::zesSysmanFirmwareGetChecksum;

    dditable.pfnFlash                                    = pDdiTable->pfnFlash;
    pDdiTable->pfnFlash                                  = layer::zesSysmanFirmwareFlash;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanMemory;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanMemoryGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanMemoryGetState;

    dditable.pfnGetBandwidth                             = pDdiTable->pfnGetBandwidth;
    pDdiTable->pfnGetBandwidth                           = layer::zesSysmanMemoryGetBandwidth;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_fabric_port_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanFabricPort;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanFabricPortGetProperties;

    dditable.pfnGetLinkType                              = pDdiTable->pfnGetLinkType;
    pDdiTable->pfnGetLinkType                            = layer::zesSysmanFabricPortGetLinkType;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesSysmanFabricPortGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesSysmanFabricPortSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanFabricPortGetState;

    dditable.pfnGetThroughput                            = pDdiTable->pfnGetThroughput;
    pDdiTable->pfnGetThroughput                          = layer::zesSysmanFabricPortGetThroughput;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanTemperature;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanTemperatureGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesSysmanTemperatureGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesSysmanTemperatureSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanTemperatureGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanPsu;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanPsuGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanPsuGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanFan;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanFanGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesSysmanFanGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesSysmanFanSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanFanGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanLed;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanLedGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanLedGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = layer::zesSysmanLedSetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanRas;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanRasGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesSysmanRasGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesSysmanRasSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanRasGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanDiagnostics;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSysmanDiagnosticsGetProperties;

    dditable.pfnGetTests                                 = pDdiTable->pfnGetTests;
    pDdiTable->pfnGetTests                               = layer::zesSysmanDiagnosticsGetTests;

    dditable.pfnRunTests                                 = pDdiTable->pfnRunTests;
    pDdiTable->pfnRunTests                               = layer::zesSysmanDiagnosticsRunTests;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEvent table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_event_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.SysmanEvent;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesSysmanEventGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesSysmanEventSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesSysmanEventGetState;

    dditable.pfnListen                                   = pDdiTable->pfnListen;
    pDdiTable->pfnListen                                 = layer::zesSysmanEventListen;

    return result;
}

#if defined(__cplusplus)
};
#endif
