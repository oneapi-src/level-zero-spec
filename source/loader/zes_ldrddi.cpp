/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_ldrddi.cpp
 *
 */
#include "ze_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    zes_driver_factory_t                zes_driver_factory;
    zes_device_factory_t                zes_device_factory;
    zes_sysman_factory_t                zes_sysman_factory;
    zes_sysman_sched_factory_t          zes_sysman_sched_factory;
    zes_sysman_perf_factory_t           zes_sysman_perf_factory;
    zes_sysman_pwr_factory_t            zes_sysman_pwr_factory;
    zes_sysman_freq_factory_t           zes_sysman_freq_factory;
    zes_sysman_engine_factory_t         zes_sysman_engine_factory;
    zes_sysman_standby_factory_t        zes_sysman_standby_factory;
    zes_sysman_firmware_factory_t       zes_sysman_firmware_factory;
    zes_sysman_mem_factory_t            zes_sysman_mem_factory;
    zes_sysman_fabric_port_factory_t    zes_sysman_fabric_port_factory;
    zes_sysman_temp_factory_t           zes_sysman_temp_factory;
    zes_sysman_psu_factory_t            zes_sysman_psu_factory;
    zes_sysman_fan_factory_t            zes_sysman_fan_factory;
    zes_sysman_led_factory_t            zes_sysman_led_factory;
    zes_sysman_ras_factory_t            zes_sysman_ras_factory;
    zes_sysman_diag_factory_t           zes_sysman_diag_factory;
    zes_sysman_event_factory_t          zes_sysman_event_factory;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGet = dditable->zes.Sysman.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGet( hDevice, version, phSysman );

        try
        {
            // convert driver handle to loader handle
            *phSysman = reinterpret_cast<zes_sysman_handle_t>(
                zes_sysman_factory.getInstance( *phSysman, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceGetProperties = dditable->zes.Sysman.pfnDeviceGetProperties;
        if( nullptr == pfnDeviceGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceGetProperties( hSysman, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceGetState = dditable->zes.Sysman.pfnDeviceGetState;
        if( nullptr == pfnDeviceGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceGetState( hSysman, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceReset = dditable->zes.Sysman.pfnDeviceReset;
        if( nullptr == pfnDeviceReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceReset( hSysman, force );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGet = dditable->zes.Sysman.pfnSchedulerGet;
        if( nullptr == pfnSchedulerGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGet( hSysman, pCount, phScheduler );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phScheduler ) && ( i < *pCount ); ++i )
                phScheduler[ i ] = reinterpret_cast<zes_sysman_sched_handle_t>(
                    zes_sysman_sched_factory.getInstance( phScheduler[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanScheduler.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetProperties( hScheduler, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetCurrentMode = dditable->zes.SysmanScheduler.pfnGetCurrentMode;
        if( nullptr == pfnGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetCurrentMode( hScheduler, pMode );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetTimeoutModeProperties = dditable->zes.SysmanScheduler.pfnGetTimeoutModeProperties;
        if( nullptr == pfnGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetTimesliceModeProperties = dditable->zes.SysmanScheduler.pfnGetTimesliceModeProperties;
        if( nullptr == pfnGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetTimeoutMode = dditable->zes.SysmanScheduler.pfnSetTimeoutMode;
        if( nullptr == pfnSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetTimesliceMode = dditable->zes.SysmanScheduler.pfnSetTimesliceMode;
        if( nullptr == pfnSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetExclusiveMode = dditable->zes.SysmanScheduler.pfnSetExclusiveMode;
        if( nullptr == pfnSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetExclusiveMode( hScheduler, pNeedReload );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetComputeUnitDebugMode = dditable->zes.SysmanScheduler.pfnSetComputeUnitDebugMode;
        if( nullptr == pfnSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sysman_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnPerformanceFactorGet = dditable->zes.Sysman.pfnPerformanceFactorGet;
        if( nullptr == pfnPerformanceFactorGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPerformanceFactorGet( hSysman, pCount, phPerf );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPerf ) && ( i < *pCount ); ++i )
                phPerf[ i ] = reinterpret_cast<zes_sysman_perf_handle_t>(
                    zes_sysman_perf_factory.getInstance( phPerf[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_perf_object_t*>( hPerf )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanPerformanceFactor.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_sysman_perf_object_t*>( hPerf )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPerf, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_perf_object_t*>( hPerf )->dditable;
        auto pfnGetConfig = dditable->zes.SysmanPerformanceFactor.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_sysman_perf_object_t*>( hPerf )->handle;

        // forward to device-driver
        result = pfnGetConfig( hPerf, pFactor );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_perf_object_t*>( hPerf )->dditable;
        auto pfnSetConfig = dditable->zes.SysmanPerformanceFactor.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_sysman_perf_object_t*>( hPerf )->handle;

        // forward to device-driver
        result = pfnSetConfig( hPerf, factor );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnProcessesGetState = dditable->zes.Sysman.pfnProcessesGetState;
        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnProcessesGetState( hSysman, pCount, pProcesses );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetProperties = dditable->zes.Sysman.pfnPciGetProperties;
        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetProperties( hSysman, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetState = dditable->zes.Sysman.pfnPciGetState;
        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetState( hSysman, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetBars = dditable->zes.Sysman.pfnPciGetBars;
        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetBars( hSysman, pCount, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetStats = dditable->zes.Sysman.pfnPciGetStats;
        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetStats( hSysman, pStats );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerGet = dditable->zes.Sysman.pfnPowerGet;
        if( nullptr == pfnPowerGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerGet( hSysman, pCount, phPower );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<zes_sysman_pwr_handle_t>(
                    zes_sysman_pwr_factory.getInstance( phPower[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanPower.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPower, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyCounter = dditable->zes.SysmanPower.pfnGetEnergyCounter;
        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyCounter( hPower, pEnergy );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetLimits = dditable->zes.SysmanPower.pfnGetLimits;
        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnSetLimits = dditable->zes.SysmanPower.pfnSetLimits;
        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyThreshold = dditable->zes.SysmanPower.pfnGetEnergyThreshold;
        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyThreshold( hPower, pThreshold );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnSetEnergyThreshold = dditable->zes.SysmanPower.pfnSetEnergyThreshold;
        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetEnergyThreshold( hPower, threshold );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencyGet = dditable->zes.Sysman.pfnFrequencyGet;
        if( nullptr == pfnFrequencyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencyGet( hSysman, pCount, phFrequency );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<zes_sysman_freq_handle_t>(
                    zes_sysman_freq_factory.getInstance( phFrequency[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanFrequency.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFrequency, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetAvailableClocks = dditable->zes.SysmanFrequency.pfnGetAvailableClocks;
        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetRange = dditable->zes.SysmanFrequency.pfnGetRange;
        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetRange( hFrequency, pLimits );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetRange = dditable->zes.SysmanFrequency.pfnSetRange;
        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetRange( hFrequency, pLimits );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetState = dditable->zes.SysmanFrequency.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetState( hFrequency, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetThrottleTime = dditable->zes.SysmanFrequency.pfnGetThrottleTime;
        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetThrottleTime( hFrequency, pThrottleTime );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetCapabilities = dditable->zes.SysmanFrequency.pfnOcGetCapabilities;
        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetConfig = dditable->zes.SysmanFrequency.pfnOcGetConfig;
        if( nullptr == pfnOcGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetConfig( hFrequency, pOcConfiguration );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetConfig = dditable->zes.SysmanFrequency.pfnOcSetConfig;
        if( nullptr == pfnOcSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetIccMax = dditable->zes.SysmanFrequency.pfnOcGetIccMax;
        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetIccMax( hFrequency, pOcIccMax );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetIccMax = dditable->zes.SysmanFrequency.pfnOcSetIccMax;
        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetIccMax( hFrequency, ocIccMax );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetTjMax = dditable->zes.SysmanFrequency.pfnOcGetTjMax;
        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetTjMax( hFrequency, pOcTjMax );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetTjMax = dditable->zes.SysmanFrequency.pfnOcSetTjMax;
        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetTjMax( hFrequency, ocTjMax );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnEngineGet = dditable->zes.Sysman.pfnEngineGet;
        if( nullptr == pfnEngineGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEngineGet( hSysman, pCount, phEngine );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<zes_sysman_engine_handle_t>(
                    zes_sysman_engine_factory.getInstance( phEngine[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_engine_object_t*>( hEngine )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanEngine.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zes_sysman_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetProperties( hEngine, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_engine_object_t*>( hEngine )->dditable;
        auto pfnGetActivity = dditable->zes.SysmanEngine.pfnGetActivity;
        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zes_sysman_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetActivity( hEngine, pStats );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnStandbyGet = dditable->zes.Sysman.pfnStandbyGet;
        if( nullptr == pfnStandbyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnStandbyGet( hSysman, pCount, phStandby );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<zes_sysman_standby_handle_t>(
                    zes_sysman_standby_factory.getInstance( phStandby[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanStandby.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetProperties( hStandby, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnGetMode = dditable->zes.SysmanStandby.pfnGetMode;
        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetMode( hStandby, pMode );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnSetMode = dditable->zes.SysmanStandby.pfnSetMode;
        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnSetMode( hStandby, mode );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnFirmwareGet = dditable->zes.Sysman.pfnFirmwareGet;
        if( nullptr == pfnFirmwareGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFirmwareGet( hSysman, pCount, phFirmware );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<zes_sysman_firmware_handle_t>(
                    zes_sysman_firmware_factory.getInstance( phFirmware[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanFirmware.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFirmware, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetChecksum = dditable->zes.SysmanFirmware.pfnGetChecksum;
        if( nullptr == pfnGetChecksum )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetChecksum( hFirmware, pChecksum );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnFlash = dditable->zes.SysmanFirmware.pfnFlash;
        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnFlash( hFirmware, pImage, size );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnMemoryGet = dditable->zes.Sysman.pfnMemoryGet;
        if( nullptr == pfnMemoryGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnMemoryGet( hSysman, pCount, phMemory );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<zes_sysman_mem_handle_t>(
                    zes_sysman_mem_factory.getInstance( phMemory[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanMemory.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMemory, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetState = dditable->zes.SysmanMemory.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetState( hMemory, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetBandwidth = dditable->zes.SysmanMemory.pfnGetBandwidth;
        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetBandwidth( hMemory, pBandwidth );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnFabricPortGet = dditable->zes.Sysman.pfnFabricPortGet;
        if( nullptr == pfnFabricPortGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFabricPortGet( hSysman, pCount, phPort );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<zes_sysman_fabric_port_handle_t>(
                    zes_sysman_fabric_port_factory.getInstance( phPort[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanFabricPort.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPort, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetLinkType = dditable->zes.SysmanFabricPort.pfnGetLinkType;
        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetLinkType( hPort, verbose, pLinkType );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetConfig = dditable->zes.SysmanFabricPort.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetConfig( hPort, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnSetConfig = dditable->zes.SysmanFabricPort.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnSetConfig( hPort, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetState = dditable->zes.SysmanFabricPort.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetState( hPort, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetThroughput = dditable->zes.SysmanFabricPort.pfnGetThroughput;
        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetThroughput( hPort, pThroughput );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnTemperatureGet = dditable->zes.Sysman.pfnTemperatureGet;
        if( nullptr == pfnTemperatureGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnTemperatureGet( hSysman, pCount, phTemperature );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<zes_sysman_temp_handle_t>(
                    zes_sysman_temp_factory.getInstance( phTemperature[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanTemperature.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetProperties( hTemperature, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetConfig = dditable->zes.SysmanTemperature.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetConfig( hTemperature, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnSetConfig = dditable->zes.SysmanTemperature.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnSetConfig( hTemperature, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetState = dditable->zes.SysmanTemperature.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetState( hTemperature, pTemperature );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnPsuGet = dditable->zes.Sysman.pfnPsuGet;
        if( nullptr == pfnPsuGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPsuGet( hSysman, pCount, phPsu );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<zes_sysman_psu_handle_t>(
                    zes_sysman_psu_factory.getInstance( phPsu[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_psu_object_t*>( hPsu )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanPsu.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zes_sysman_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPsu, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_psu_object_t*>( hPsu )->dditable;
        auto pfnGetState = dditable->zes.SysmanPsu.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zes_sysman_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetState( hPsu, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnFanGet = dditable->zes.Sysman.pfnFanGet;
        if( nullptr == pfnFanGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFanGet( hSysman, pCount, phFan );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<zes_sysman_fan_handle_t>(
                    zes_sysman_fan_factory.getInstance( phFan[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanFan.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFan, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetConfig = dditable->zes.SysmanFan.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetConfig( hFan, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnSetConfig = dditable->zes.SysmanFan.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnSetConfig( hFan, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetState = dditable->zes.SysmanFan.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetState( hFan, units, pSpeed );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnLedGet = dditable->zes.Sysman.pfnLedGet;
        if( nullptr == pfnLedGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnLedGet( hSysman, pCount, phLed );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<zes_sysman_led_handle_t>(
                    zes_sysman_led_factory.getInstance( phLed[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_led_object_t*>( hLed )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanLed.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetProperties( hLed, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_led_object_t*>( hLed )->dditable;
        auto pfnGetState = dditable->zes.SysmanLed.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetState( hLed, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_led_object_t*>( hLed )->dditable;
        auto pfnSetState = dditable->zes.SysmanLed.pfnSetState;
        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnSetState( hLed, pState );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnRasGet = dditable->zes.Sysman.pfnRasGet;
        if( nullptr == pfnRasGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRasGet( hSysman, pCount, phRas );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<zes_sysman_ras_handle_t>(
                    zes_sysman_ras_factory.getInstance( phRas[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanRas.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetProperties( hRas, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetConfig = dditable->zes.SysmanRas.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetConfig( hRas, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnSetConfig = dditable->zes.SysmanRas.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnSetConfig( hRas, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetState = dditable->zes.SysmanRas.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetState( hRas, clear, pTotalErrors, pDetails );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnEventGet = dditable->zes.Sysman.pfnEventGet;
        if( nullptr == pfnEventGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEventGet( hSysman, phEvent );

        try
        {
            // convert driver handle to loader handle
            *phEvent = reinterpret_cast<zes_sysman_event_handle_t>(
                zes_sysman_event_factory.getInstance( *phEvent, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_event_object_t*>( hEvent )->dditable;
        auto pfnGetConfig = dditable->zes.SysmanEvent.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zes_sysman_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnGetConfig( hEvent, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_event_object_t*>( hEvent )->dditable;
        auto pfnSetConfig = dditable->zes.SysmanEvent.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zes_sysman_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnSetConfig( hEvent, pConfig );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_event_object_t*>( hEvent )->dditable;
        auto pfnGetState = dditable->zes.SysmanEvent.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zes_sysman_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnGetState( hEvent, clear, pEvents );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnListen = dditable->zes.SysmanEvent.pfnListen;
        if( nullptr == pfnListen )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phEvents ) && ( i < count ); ++i )
            phEvents[ i ] = reinterpret_cast<zes_sysman_event_object_t*>( phEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnListen( hDriver, timeout, count, phEvents, pEvents );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_object_t*>( hSysman )->dditable;
        auto pfnDiagnosticsGet = dditable->zes.Sysman.pfnDiagnosticsGet;
        if( nullptr == pfnDiagnosticsGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zes_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<zes_sysman_diag_handle_t>(
                    zes_sysman_diag_factory.getInstance( phDiagnostics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetProperties = dditable->zes.SysmanDiagnostics.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDiagnostics, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetTests = dditable->zes.SysmanDiagnostics.pfnGetTests;
        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnGetTests( hDiagnostics, pCount, pTests );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnRunTests = dditable->zes.SysmanDiagnostics.pfnRunTests;
        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnRunTests( hDiagnostics, start, end, pResult );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Sysman );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zesSysmanGet;
            pDdiTable->pfnDeviceGetProperties                      = loader::zesSysmanDeviceGetProperties;
            pDdiTable->pfnDeviceGetState                           = loader::zesSysmanDeviceGetState;
            pDdiTable->pfnDeviceReset                              = loader::zesSysmanDeviceReset;
            pDdiTable->pfnSchedulerGet                             = loader::zesSysmanSchedulerGet;
            pDdiTable->pfnPerformanceFactorGet                     = loader::zesSysmanPerformanceFactorGet;
            pDdiTable->pfnProcessesGetState                        = loader::zesSysmanProcessesGetState;
            pDdiTable->pfnPciGetProperties                         = loader::zesSysmanPciGetProperties;
            pDdiTable->pfnPciGetState                              = loader::zesSysmanPciGetState;
            pDdiTable->pfnPciGetBars                               = loader::zesSysmanPciGetBars;
            pDdiTable->pfnPciGetStats                              = loader::zesSysmanPciGetStats;
            pDdiTable->pfnPowerGet                                 = loader::zesSysmanPowerGet;
            pDdiTable->pfnFrequencyGet                             = loader::zesSysmanFrequencyGet;
            pDdiTable->pfnEngineGet                                = loader::zesSysmanEngineGet;
            pDdiTable->pfnStandbyGet                               = loader::zesSysmanStandbyGet;
            pDdiTable->pfnFirmwareGet                              = loader::zesSysmanFirmwareGet;
            pDdiTable->pfnMemoryGet                                = loader::zesSysmanMemoryGet;
            pDdiTable->pfnFabricPortGet                            = loader::zesSysmanFabricPortGet;
            pDdiTable->pfnTemperatureGet                           = loader::zesSysmanTemperatureGet;
            pDdiTable->pfnPsuGet                                   = loader::zesSysmanPsuGet;
            pDdiTable->pfnFanGet                                   = loader::zesSysmanFanGet;
            pDdiTable->pfnLedGet                                   = loader::zesSysmanLedGet;
            pDdiTable->pfnRasGet                                   = loader::zesSysmanRasGet;
            pDdiTable->pfnEventGet                                 = loader::zesSysmanEventGet;
            pDdiTable->pfnDiagnosticsGet                           = loader::zesSysmanDiagnosticsGet;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Sysman;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanScheduler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanSchedulerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_scheduler_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanSchedulerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanSchedulerProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanScheduler );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanSchedulerGetProperties;
            pDdiTable->pfnGetCurrentMode                           = loader::zesSysmanSchedulerGetCurrentMode;
            pDdiTable->pfnGetTimeoutModeProperties                 = loader::zesSysmanSchedulerGetTimeoutModeProperties;
            pDdiTable->pfnGetTimesliceModeProperties               = loader::zesSysmanSchedulerGetTimesliceModeProperties;
            pDdiTable->pfnSetTimeoutMode                           = loader::zesSysmanSchedulerSetTimeoutMode;
            pDdiTable->pfnSetTimesliceMode                         = loader::zesSysmanSchedulerSetTimesliceMode;
            pDdiTable->pfnSetExclusiveMode                         = loader::zesSysmanSchedulerSetExclusiveMode;
            pDdiTable->pfnSetComputeUnitDebugMode                  = loader::zesSysmanSchedulerSetComputeUnitDebugMode;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanScheduler;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanSchedulerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanSchedulerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPerformanceFactor table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPerformanceFactorProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_performance_factor_dditable_t* pDdiTable ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanPerformanceFactorProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanPerformanceFactorProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanPerformanceFactor );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanPerformanceFactorGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesSysmanPerformanceFactorGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesSysmanPerformanceFactorSetConfig;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanPerformanceFactor;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanPerformanceFactorProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanPerformanceFactorProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanPowerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanPowerProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanPower );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanPowerGetProperties;
            pDdiTable->pfnGetEnergyCounter                         = loader::zesSysmanPowerGetEnergyCounter;
            pDdiTable->pfnGetLimits                                = loader::zesSysmanPowerGetLimits;
            pDdiTable->pfnSetLimits                                = loader::zesSysmanPowerSetLimits;
            pDdiTable->pfnGetEnergyThreshold                       = loader::zesSysmanPowerGetEnergyThreshold;
            pDdiTable->pfnSetEnergyThreshold                       = loader::zesSysmanPowerSetEnergyThreshold;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanPower;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanPowerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanFrequencyProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanFrequency );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanFrequencyGetProperties;
            pDdiTable->pfnGetAvailableClocks                       = loader::zesSysmanFrequencyGetAvailableClocks;
            pDdiTable->pfnGetRange                                 = loader::zesSysmanFrequencyGetRange;
            pDdiTable->pfnSetRange                                 = loader::zesSysmanFrequencySetRange;
            pDdiTable->pfnGetState                                 = loader::zesSysmanFrequencyGetState;
            pDdiTable->pfnGetThrottleTime                          = loader::zesSysmanFrequencyGetThrottleTime;
            pDdiTable->pfnOcGetCapabilities                        = loader::zesSysmanFrequencyOcGetCapabilities;
            pDdiTable->pfnOcGetConfig                              = loader::zesSysmanFrequencyOcGetConfig;
            pDdiTable->pfnOcSetConfig                              = loader::zesSysmanFrequencyOcSetConfig;
            pDdiTable->pfnOcGetIccMax                              = loader::zesSysmanFrequencyOcGetIccMax;
            pDdiTable->pfnOcSetIccMax                              = loader::zesSysmanFrequencyOcSetIccMax;
            pDdiTable->pfnOcGetTjMax                               = loader::zesSysmanFrequencyOcGetTjMax;
            pDdiTable->pfnOcSetTjMax                               = loader::zesSysmanFrequencyOcSetTjMax;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanFrequency;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanFrequencyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanFrequencyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanEngineProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanEngineProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanEngine );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanEngineGetProperties;
            pDdiTable->pfnGetActivity                              = loader::zesSysmanEngineGetActivity;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanEngine;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanEngineProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanEngineProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanStandbyProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanStandby );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanStandbyGetProperties;
            pDdiTable->pfnGetMode                                  = loader::zesSysmanStandbyGetMode;
            pDdiTable->pfnSetMode                                  = loader::zesSysmanStandbySetMode;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanStandby;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanStandbyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanStandbyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanFirmwareProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanFirmware );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanFirmwareGetProperties;
            pDdiTable->pfnGetChecksum                              = loader::zesSysmanFirmwareGetChecksum;
            pDdiTable->pfnFlash                                    = loader::zesSysmanFirmwareFlash;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanFirmware;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanFirmwareProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanFirmwareProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanMemoryProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanMemory );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanMemoryGetProperties;
            pDdiTable->pfnGetState                                 = loader::zesSysmanMemoryGetState;
            pDdiTable->pfnGetBandwidth                             = loader::zesSysmanMemoryGetBandwidth;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanMemory;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanMemoryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanMemoryProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_fabric_port_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanFabricPortProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanFabricPort );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanFabricPortGetProperties;
            pDdiTable->pfnGetLinkType                              = loader::zesSysmanFabricPortGetLinkType;
            pDdiTable->pfnGetConfig                                = loader::zesSysmanFabricPortGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesSysmanFabricPortSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesSysmanFabricPortGetState;
            pDdiTable->pfnGetThroughput                            = loader::zesSysmanFabricPortGetThroughput;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanFabricPort;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanFabricPortProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanFabricPortProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanTemperatureProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanTemperature );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanTemperatureGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesSysmanTemperatureGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesSysmanTemperatureSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesSysmanTemperatureGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanTemperature;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanTemperatureProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanTemperatureProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanPsuProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanPsuProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanPsu );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanPsuGetProperties;
            pDdiTable->pfnGetState                                 = loader::zesSysmanPsuGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanPsu;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanPsuProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanPsuProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanFanProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanFanProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanFan );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanFanGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesSysmanFanGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesSysmanFanSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesSysmanFanGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanFan;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanFanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanFanProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanLedProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanLedProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanLed );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanLedGetProperties;
            pDdiTable->pfnGetState                                 = loader::zesSysmanLedGetState;
            pDdiTable->pfnSetState                                 = loader::zesSysmanLedSetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanLed;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanLedProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanLedProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanRasProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanRasProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanRas );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanRasGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesSysmanRasGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesSysmanRasSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesSysmanRasGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanRas;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanRasProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanRasProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanDiagnosticsProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanDiagnostics );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSysmanDiagnosticsGetProperties;
            pDdiTable->pfnGetTests                                 = loader::zesSysmanDiagnosticsGetTests;
            pDdiTable->pfnRunTests                                 = loader::zesSysmanDiagnosticsRunTests;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanDiagnostics;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanDiagnosticsProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanDiagnosticsProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEvent table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSysmanEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_sysman_event_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSysmanEventProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSysmanEventProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.SysmanEvent );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetConfig                                = loader::zesSysmanEventGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesSysmanEventSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesSysmanEventGetState;
            pDdiTable->pfnListen                                   = loader::zesSysmanEventListen;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.SysmanEvent;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSysmanEventProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSysmanEventProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
