/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_nullddi.cpp
 *
 */
#include "ze_null.h"

namespace driver
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zesDdiTable.Sysman.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDevice, version, phSysman );
        }
        else
        {
            // generic implementation
            *phSysman = reinterpret_cast<zes_sysman_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDeviceGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanDeviceGetProperties(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_sysman_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceGetProperties = context.zesDdiTable.Sysman.pfnDeviceGetProperties;
        if( nullptr != pfnDeviceGetProperties )
        {
            result = pfnDeviceGetProperties( hSysman, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanDeviceGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanDeviceGetState(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_sysman_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceGetState = context.zesDdiTable.Sysman.pfnDeviceGetState;
        if( nullptr != pfnDeviceGetState )
        {
            result = pfnDeviceGetState( hSysman, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDeviceReset = context.zesDdiTable.Sysman.pfnDeviceReset;
        if( nullptr != pfnDeviceReset )
        {
            result = pfnDeviceReset( hSysman, force );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSchedulerGet = context.zesDdiTable.Sysman.pfnSchedulerGet;
        if( nullptr != pfnSchedulerGet )
        {
            result = pfnSchedulerGet( hSysman, pCount, phScheduler );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phScheduler ) && ( i < *pCount ); ++i )
                phScheduler[ i ] = reinterpret_cast<zes_sysman_sched_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerGetProperties(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanScheduler.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hScheduler, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanSchedulerGetCurrentMode
    __zedlllocal ze_result_t __zecall
    zesSysmanSchedulerGetCurrentMode(
        zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetCurrentMode = context.zesDdiTable.SysmanScheduler.pfnGetCurrentMode;
        if( nullptr != pfnGetCurrentMode )
        {
            result = pfnGetCurrentMode( hScheduler, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTimeoutModeProperties = context.zesDdiTable.SysmanScheduler.pfnGetTimeoutModeProperties;
        if( nullptr != pfnGetTimeoutModeProperties )
        {
            result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTimesliceModeProperties = context.zesDdiTable.SysmanScheduler.pfnGetTimesliceModeProperties;
        if( nullptr != pfnGetTimesliceModeProperties )
        {
            result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetTimeoutMode = context.zesDdiTable.SysmanScheduler.pfnSetTimeoutMode;
        if( nullptr != pfnSetTimeoutMode )
        {
            result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetTimesliceMode = context.zesDdiTable.SysmanScheduler.pfnSetTimesliceMode;
        if( nullptr != pfnSetTimesliceMode )
        {
            result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetExclusiveMode = context.zesDdiTable.SysmanScheduler.pfnSetExclusiveMode;
        if( nullptr != pfnSetExclusiveMode )
        {
            result = pfnSetExclusiveMode( hScheduler, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetComputeUnitDebugMode = context.zesDdiTable.SysmanScheduler.pfnSetComputeUnitDebugMode;
        if( nullptr != pfnSetComputeUnitDebugMode )
        {
            result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPerformanceFactorGet = context.zesDdiTable.Sysman.pfnPerformanceFactorGet;
        if( nullptr != pfnPerformanceFactorGet )
        {
            result = pfnPerformanceFactorGet( hSysman, pCount, phPerf );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPerf ) && ( i < *pCount ); ++i )
                phPerf[ i ] = reinterpret_cast<zes_sysman_perf_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanPerformanceFactor.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPerf, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.SysmanPerformanceFactor.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hPerf, pFactor );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPerformanceFactorSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanPerformanceFactorSetConfig(
        zes_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.SysmanPerformanceFactor.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hPerf, factor );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnProcessesGetState = context.zesDdiTable.Sysman.pfnProcessesGetState;
        if( nullptr != pfnProcessesGetState )
        {
            result = pfnProcessesGetState( hSysman, pCount, pProcesses );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPciGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanPciGetProperties(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetProperties = context.zesDdiTable.Sysman.pfnPciGetProperties;
        if( nullptr != pfnPciGetProperties )
        {
            result = pfnPciGetProperties( hSysman, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPciGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanPciGetState(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetState = context.zesDdiTable.Sysman.pfnPciGetState;
        if( nullptr != pfnPciGetState )
        {
            result = pfnPciGetState( hSysman, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetBars = context.zesDdiTable.Sysman.pfnPciGetBars;
        if( nullptr != pfnPciGetBars )
        {
            result = pfnPciGetBars( hSysman, pCount, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPciGetStats
    __zedlllocal ze_result_t __zecall
    zesSysmanPciGetStats(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetStats = context.zesDdiTable.Sysman.pfnPciGetStats;
        if( nullptr != pfnPciGetStats )
        {
            result = pfnPciGetStats( hSysman, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPowerGet = context.zesDdiTable.Sysman.pfnPowerGet;
        if( nullptr != pfnPowerGet )
        {
            result = pfnPowerGet( hSysman, pCount, phPower );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<zes_sysman_pwr_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerGetProperties(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanPower.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPower, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetEnergyCounter = context.zesDdiTable.SysmanPower.pfnGetEnergyCounter;
        if( nullptr != pfnGetEnergyCounter )
        {
            result = pfnGetEnergyCounter( hPower, pEnergy );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLimits = context.zesDdiTable.SysmanPower.pfnGetLimits;
        if( nullptr != pfnGetLimits )
        {
            result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLimits = context.zesDdiTable.SysmanPower.pfnSetLimits;
        if( nullptr != pfnSetLimits )
        {
            result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetEnergyThreshold = context.zesDdiTable.SysmanPower.pfnGetEnergyThreshold;
        if( nullptr != pfnGetEnergyThreshold )
        {
            result = pfnGetEnergyThreshold( hPower, pThreshold );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPowerSetEnergyThreshold
    __zedlllocal ze_result_t __zecall
    zesSysmanPowerSetEnergyThreshold(
        zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEnergyThreshold = context.zesDdiTable.SysmanPower.pfnSetEnergyThreshold;
        if( nullptr != pfnSetEnergyThreshold )
        {
            result = pfnSetEnergyThreshold( hPower, threshold );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFrequencyGet = context.zesDdiTable.Sysman.pfnFrequencyGet;
        if( nullptr != pfnFrequencyGet )
        {
            result = pfnFrequencyGet( hSysman, pCount, phFrequency );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<zes_sysman_freq_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGetProperties(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanFrequency.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFrequency, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAvailableClocks = context.zesDdiTable.SysmanFrequency.pfnGetAvailableClocks;
        if( nullptr != pfnGetAvailableClocks )
        {
            result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetRange = context.zesDdiTable.SysmanFrequency.pfnGetRange;
        if( nullptr != pfnGetRange )
        {
            result = pfnGetRange( hFrequency, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetRange = context.zesDdiTable.SysmanFrequency.pfnSetRange;
        if( nullptr != pfnSetRange )
        {
            result = pfnSetRange( hFrequency, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyGetState(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanFrequency.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hFrequency, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetThrottleTime = context.zesDdiTable.SysmanFrequency.pfnGetThrottleTime;
        if( nullptr != pfnGetThrottleTime )
        {
            result = pfnGetThrottleTime( hFrequency, pThrottleTime );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetCapabilities = context.zesDdiTable.SysmanFrequency.pfnOcGetCapabilities;
        if( nullptr != pfnOcGetCapabilities )
        {
            result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcGetConfig(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zes_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zes_oc_config_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetConfig = context.zesDdiTable.SysmanFrequency.pfnOcGetConfig;
        if( nullptr != pfnOcGetConfig )
        {
            result = pfnOcGetConfig( hFrequency, pOcConfiguration );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetConfig = context.zesDdiTable.SysmanFrequency.pfnOcSetConfig;
        if( nullptr != pfnOcSetConfig )
        {
            result = pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetIccMax = context.zesDdiTable.SysmanFrequency.pfnOcGetIccMax;
        if( nullptr != pfnOcGetIccMax )
        {
            result = pfnOcGetIccMax( hFrequency, pOcIccMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcSetIccMax
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcSetIccMax(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetIccMax = context.zesDdiTable.SysmanFrequency.pfnOcSetIccMax;
        if( nullptr != pfnOcSetIccMax )
        {
            result = pfnOcSetIccMax( hFrequency, ocIccMax );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetTjMax = context.zesDdiTable.SysmanFrequency.pfnOcGetTjMax;
        if( nullptr != pfnOcGetTjMax )
        {
            result = pfnOcGetTjMax( hFrequency, pOcTjMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFrequencyOcSetTjMax
    __zedlllocal ze_result_t __zecall
    zesSysmanFrequencyOcSetTjMax(
        zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetTjMax = context.zesDdiTable.SysmanFrequency.pfnOcSetTjMax;
        if( nullptr != pfnOcSetTjMax )
        {
            result = pfnOcSetTjMax( hFrequency, ocTjMax );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEngineGet = context.zesDdiTable.Sysman.pfnEngineGet;
        if( nullptr != pfnEngineGet )
        {
            result = pfnEngineGet( hSysman, pCount, phEngine );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<zes_sysman_engine_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEngineGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanEngineGetProperties(
        zes_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanEngine.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hEngine, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetActivity = context.zesDdiTable.SysmanEngine.pfnGetActivity;
        if( nullptr != pfnGetActivity )
        {
            result = pfnGetActivity( hEngine, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnStandbyGet = context.zesDdiTable.Sysman.pfnStandbyGet;
        if( nullptr != pfnStandbyGet )
        {
            result = pfnStandbyGet( hSysman, pCount, phStandby );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<zes_sysman_standby_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanStandbyGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanStandbyGetProperties(
        zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanStandby.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hStandby, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanStandbyGetMode
    __zedlllocal ze_result_t __zecall
    zesSysmanStandbyGetMode(
        zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMode = context.zesDdiTable.SysmanStandby.pfnGetMode;
        if( nullptr != pfnGetMode )
        {
            result = pfnGetMode( hStandby, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanStandbySetMode
    __zedlllocal ze_result_t __zecall
    zesSysmanStandbySetMode(
        zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetMode = context.zesDdiTable.SysmanStandby.pfnSetMode;
        if( nullptr != pfnSetMode )
        {
            result = pfnSetMode( hStandby, mode );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFirmwareGet = context.zesDdiTable.Sysman.pfnFirmwareGet;
        if( nullptr != pfnFirmwareGet )
        {
            result = pfnFirmwareGet( hSysman, pCount, phFirmware );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<zes_sysman_firmware_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanFirmware.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFirmware, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFirmwareGetChecksum
    __zedlllocal ze_result_t __zecall
    zesSysmanFirmwareGetChecksum(
        zes_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetChecksum = context.zesDdiTable.SysmanFirmware.pfnGetChecksum;
        if( nullptr != pfnGetChecksum )
        {
            result = pfnGetChecksum( hFirmware, pChecksum );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFlash = context.zesDdiTable.SysmanFirmware.pfnFlash;
        if( nullptr != pfnFlash )
        {
            result = pfnFlash( hFirmware, pImage, size );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMemoryGet = context.zesDdiTable.Sysman.pfnMemoryGet;
        if( nullptr != pfnMemoryGet )
        {
            result = pfnMemoryGet( hSysman, pCount, phMemory );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<zes_sysman_mem_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanMemoryGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanMemoryGetProperties(
        zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanMemory.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hMemory, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanMemoryGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanMemoryGetState(
        zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanMemory.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hMemory, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetBandwidth = context.zesDdiTable.SysmanMemory.pfnGetBandwidth;
        if( nullptr != pfnGetBandwidth )
        {
            result = pfnGetBandwidth( hMemory, pBandwidth );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFabricPortGet = context.zesDdiTable.Sysman.pfnFabricPortGet;
        if( nullptr != pfnFabricPortGet )
        {
            result = pfnFabricPortGet( hSysman, pCount, phPort );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<zes_sysman_fabric_port_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetProperties(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanFabricPort.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPort, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLinkType = context.zesDdiTable.SysmanFabricPort.pfnGetLinkType;
        if( nullptr != pfnGetLinkType )
        {
            result = pfnGetLinkType( hPort, verbose, pLinkType );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetConfig(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.SysmanFabricPort.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hPort, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortSetConfig(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.SysmanFabricPort.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hPort, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetState(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanFabricPort.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hPort, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFabricPortGetThroughput
    __zedlllocal ze_result_t __zecall
    zesSysmanFabricPortGetThroughput(
        zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetThroughput = context.zesDdiTable.SysmanFabricPort.pfnGetThroughput;
        if( nullptr != pfnGetThroughput )
        {
            result = pfnGetThroughput( hPort, pThroughput );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnTemperatureGet = context.zesDdiTable.Sysman.pfnTemperatureGet;
        if( nullptr != pfnTemperatureGet )
        {
            result = pfnTemperatureGet( hSysman, pCount, phTemperature );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<zes_sysman_temp_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureGetProperties(
        zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanTemperature.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hTemperature, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureGetConfig(
        zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.SysmanTemperature.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hTemperature, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanTemperatureSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanTemperatureSetConfig(
        zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.SysmanTemperature.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hTemperature, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanTemperature.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hTemperature, pTemperature );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPsuGet = context.zesDdiTable.Sysman.pfnPsuGet;
        if( nullptr != pfnPsuGet )
        {
            result = pfnPsuGet( hSysman, pCount, phPsu );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<zes_sysman_psu_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPsuGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanPsuGetProperties(
        zes_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanPsu.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPsu, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanPsuGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanPsuGetState(
        zes_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanPsu.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hPsu, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFanGet = context.zesDdiTable.Sysman.pfnFanGet;
        if( nullptr != pfnFanGet )
        {
            result = pfnFanGet( hSysman, pCount, phFan );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<zes_sysman_fan_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanFanGetProperties(
        zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanFan.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFan, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanGetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFanGetConfig(
        zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.SysmanFan.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hFan, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanFanSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanFanSetConfig(
        zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const zes_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.SysmanFan.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hFan, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanFan.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hFan, units, pSpeed );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnLedGet = context.zesDdiTable.Sysman.pfnLedGet;
        if( nullptr != pfnLedGet )
        {
            result = pfnLedGet( hSysman, pCount, phLed );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<zes_sysman_led_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanLedGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanLedGetProperties(
        zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanLed.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hLed, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanLedGetState
    __zedlllocal ze_result_t __zecall
    zesSysmanLedGetState(
        zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanLed.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hLed, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanLedSetState
    __zedlllocal ze_result_t __zecall
    zesSysmanLedSetState(
        zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const zes_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetState = context.zesDdiTable.SysmanLed.pfnSetState;
        if( nullptr != pfnSetState )
        {
            result = pfnSetState( hLed, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRasGet = context.zesDdiTable.Sysman.pfnRasGet;
        if( nullptr != pfnRasGet )
        {
            result = pfnRasGet( hSysman, pCount, phRas );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<zes_sysman_ras_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanRasGetProperties
    __zedlllocal ze_result_t __zecall
    zesSysmanRasGetProperties(
        zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanRas.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hRas, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.SysmanRas.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hRas, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanRasSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanRasSetConfig(
        zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.SysmanRas.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hRas, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanRas.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hRas, clear, pTotalErrors, pDetails );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEventGet
    __zedlllocal ze_result_t __zecall
    zesSysmanEventGet(
        zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zes_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventGet = context.zesDdiTable.Sysman.pfnEventGet;
        if( nullptr != pfnEventGet )
        {
            result = pfnEventGet( hSysman, phEvent );
        }
        else
        {
            // generic implementation
            *phEvent = reinterpret_cast<zes_sysman_event_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.SysmanEvent.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hEvent, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSysmanEventSetConfig
    __zedlllocal ze_result_t __zecall
    zesSysmanEventSetConfig(
        zes_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        const zes_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.SysmanEvent.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hEvent, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.SysmanEvent.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hEvent, clear, pEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnListen = context.zesDdiTable.SysmanEvent.pfnListen;
        if( nullptr != pfnListen )
        {
            result = pfnListen( hDriver, timeout, count, phEvents, pEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDiagnosticsGet = context.zesDdiTable.Sysman.pfnDiagnosticsGet;
        if( nullptr != pfnDiagnosticsGet )
        {
            result = pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<zes_sysman_diag_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.SysmanDiagnostics.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDiagnostics, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTests = context.zesDdiTable.SysmanDiagnostics.pfnGetTests;
        if( nullptr != pfnGetTests )
        {
            result = pfnGetTests( hDiagnostics, pCount, pTests );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRunTests = context.zesDdiTable.SysmanDiagnostics.pfnRunTests;
        if( nullptr != pfnRunTests )
        {
            result = pfnRunTests( hDiagnostics, start, end, pResult );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

} // namespace driver

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::zesSysmanGet;

    pDdiTable->pfnDeviceGetProperties                    = driver::zesSysmanDeviceGetProperties;

    pDdiTable->pfnDeviceGetState                         = driver::zesSysmanDeviceGetState;

    pDdiTable->pfnDeviceReset                            = driver::zesSysmanDeviceReset;

    pDdiTable->pfnSchedulerGet                           = driver::zesSysmanSchedulerGet;

    pDdiTable->pfnPerformanceFactorGet                   = driver::zesSysmanPerformanceFactorGet;

    pDdiTable->pfnProcessesGetState                      = driver::zesSysmanProcessesGetState;

    pDdiTable->pfnPciGetProperties                       = driver::zesSysmanPciGetProperties;

    pDdiTable->pfnPciGetState                            = driver::zesSysmanPciGetState;

    pDdiTable->pfnPciGetBars                             = driver::zesSysmanPciGetBars;

    pDdiTable->pfnPciGetStats                            = driver::zesSysmanPciGetStats;

    pDdiTable->pfnPowerGet                               = driver::zesSysmanPowerGet;

    pDdiTable->pfnFrequencyGet                           = driver::zesSysmanFrequencyGet;

    pDdiTable->pfnEngineGet                              = driver::zesSysmanEngineGet;

    pDdiTable->pfnStandbyGet                             = driver::zesSysmanStandbyGet;

    pDdiTable->pfnFirmwareGet                            = driver::zesSysmanFirmwareGet;

    pDdiTable->pfnMemoryGet                              = driver::zesSysmanMemoryGet;

    pDdiTable->pfnFabricPortGet                          = driver::zesSysmanFabricPortGet;

    pDdiTable->pfnTemperatureGet                         = driver::zesSysmanTemperatureGet;

    pDdiTable->pfnPsuGet                                 = driver::zesSysmanPsuGet;

    pDdiTable->pfnFanGet                                 = driver::zesSysmanFanGet;

    pDdiTable->pfnLedGet                                 = driver::zesSysmanLedGet;

    pDdiTable->pfnRasGet                                 = driver::zesSysmanRasGet;

    pDdiTable->pfnEventGet                               = driver::zesSysmanEventGet;

    pDdiTable->pfnDiagnosticsGet                         = driver::zesSysmanDiagnosticsGet;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanSchedulerGetProperties;

    pDdiTable->pfnGetCurrentMode                         = driver::zesSysmanSchedulerGetCurrentMode;

    pDdiTable->pfnGetTimeoutModeProperties               = driver::zesSysmanSchedulerGetTimeoutModeProperties;

    pDdiTable->pfnGetTimesliceModeProperties             = driver::zesSysmanSchedulerGetTimesliceModeProperties;

    pDdiTable->pfnSetTimeoutMode                         = driver::zesSysmanSchedulerSetTimeoutMode;

    pDdiTable->pfnSetTimesliceMode                       = driver::zesSysmanSchedulerSetTimesliceMode;

    pDdiTable->pfnSetExclusiveMode                       = driver::zesSysmanSchedulerSetExclusiveMode;

    pDdiTable->pfnSetComputeUnitDebugMode                = driver::zesSysmanSchedulerSetComputeUnitDebugMode;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanPerformanceFactorGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesSysmanPerformanceFactorGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesSysmanPerformanceFactorSetConfig;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanPowerGetProperties;

    pDdiTable->pfnGetEnergyCounter                       = driver::zesSysmanPowerGetEnergyCounter;

    pDdiTable->pfnGetLimits                              = driver::zesSysmanPowerGetLimits;

    pDdiTable->pfnSetLimits                              = driver::zesSysmanPowerSetLimits;

    pDdiTable->pfnGetEnergyThreshold                     = driver::zesSysmanPowerGetEnergyThreshold;

    pDdiTable->pfnSetEnergyThreshold                     = driver::zesSysmanPowerSetEnergyThreshold;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanFrequencyGetProperties;

    pDdiTable->pfnGetAvailableClocks                     = driver::zesSysmanFrequencyGetAvailableClocks;

    pDdiTable->pfnGetRange                               = driver::zesSysmanFrequencyGetRange;

    pDdiTable->pfnSetRange                               = driver::zesSysmanFrequencySetRange;

    pDdiTable->pfnGetState                               = driver::zesSysmanFrequencyGetState;

    pDdiTable->pfnGetThrottleTime                        = driver::zesSysmanFrequencyGetThrottleTime;

    pDdiTable->pfnOcGetCapabilities                      = driver::zesSysmanFrequencyOcGetCapabilities;

    pDdiTable->pfnOcGetConfig                            = driver::zesSysmanFrequencyOcGetConfig;

    pDdiTable->pfnOcSetConfig                            = driver::zesSysmanFrequencyOcSetConfig;

    pDdiTable->pfnOcGetIccMax                            = driver::zesSysmanFrequencyOcGetIccMax;

    pDdiTable->pfnOcSetIccMax                            = driver::zesSysmanFrequencyOcSetIccMax;

    pDdiTable->pfnOcGetTjMax                             = driver::zesSysmanFrequencyOcGetTjMax;

    pDdiTable->pfnOcSetTjMax                             = driver::zesSysmanFrequencyOcSetTjMax;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanEngineGetProperties;

    pDdiTable->pfnGetActivity                            = driver::zesSysmanEngineGetActivity;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanStandbyGetProperties;

    pDdiTable->pfnGetMode                                = driver::zesSysmanStandbyGetMode;

    pDdiTable->pfnSetMode                                = driver::zesSysmanStandbySetMode;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanFirmwareGetProperties;

    pDdiTable->pfnGetChecksum                            = driver::zesSysmanFirmwareGetChecksum;

    pDdiTable->pfnFlash                                  = driver::zesSysmanFirmwareFlash;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanMemoryGetProperties;

    pDdiTable->pfnGetState                               = driver::zesSysmanMemoryGetState;

    pDdiTable->pfnGetBandwidth                           = driver::zesSysmanMemoryGetBandwidth;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanFabricPortGetProperties;

    pDdiTable->pfnGetLinkType                            = driver::zesSysmanFabricPortGetLinkType;

    pDdiTable->pfnGetConfig                              = driver::zesSysmanFabricPortGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesSysmanFabricPortSetConfig;

    pDdiTable->pfnGetState                               = driver::zesSysmanFabricPortGetState;

    pDdiTable->pfnGetThroughput                          = driver::zesSysmanFabricPortGetThroughput;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanTemperatureGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesSysmanTemperatureGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesSysmanTemperatureSetConfig;

    pDdiTable->pfnGetState                               = driver::zesSysmanTemperatureGetState;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanPsuGetProperties;

    pDdiTable->pfnGetState                               = driver::zesSysmanPsuGetState;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanFanGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesSysmanFanGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesSysmanFanSetConfig;

    pDdiTable->pfnGetState                               = driver::zesSysmanFanGetState;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanLedGetProperties;

    pDdiTable->pfnGetState                               = driver::zesSysmanLedGetState;

    pDdiTable->pfnSetState                               = driver::zesSysmanLedSetState;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanRasGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesSysmanRasGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesSysmanRasSetConfig;

    pDdiTable->pfnGetState                               = driver::zesSysmanRasGetState;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSysmanDiagnosticsGetProperties;

    pDdiTable->pfnGetTests                               = driver::zesSysmanDiagnosticsGetTests;

    pDdiTable->pfnRunTests                               = driver::zesSysmanDiagnosticsRunTests;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetConfig                              = driver::zesSysmanEventGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesSysmanEventSetConfig;

    pDdiTable->pfnGetState                               = driver::zesSysmanEventGetState;

    pDdiTable->pfnListen                                 = driver::zesSysmanEventListen;

    return result;
}

#if defined(__cplusplus)
};
#endif
