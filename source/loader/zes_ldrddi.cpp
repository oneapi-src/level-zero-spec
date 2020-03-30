/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_ldrddi.cpp
 * @version v0.91-271
 *
 */
#include "ze_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    zes_driver_factory_t                zes_driver_factory;
    zes_device_factory_t                zes_device_factory;
    zes_sched_factory_t                 zes_sched_factory;
    zes_perf_factory_t                  zes_perf_factory;
    zes_pwr_factory_t                   zes_pwr_factory;
    zes_freq_factory_t                  zes_freq_factory;
    zes_engine_factory_t                zes_engine_factory;
    zes_standby_factory_t               zes_standby_factory;
    zes_firmware_factory_t              zes_firmware_factory;
    zes_mem_factory_t                   zes_mem_factory;
    zes_fabric_port_factory_t           zes_fabric_port_factory;
    zes_temp_factory_t                  zes_temp_factory;
    zes_psu_factory_t                   zes_psu_factory;
    zes_fan_factory_t                   zes_fan_factory;
    zes_led_factory_t                   zes_led_factory;
    zes_ras_factory_t                   zes_ras_factory;
    zes_diag_factory_t                  zes_diag_factory;
    zes_event_factory_t                 zes_event_factory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetProperties
    __zedlllocal ze_result_t __zecall
    zesDeviceGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetProperties = dditable->zes.Device.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDevice, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetState
    __zedlllocal ze_result_t __zecall
    zesDeviceGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetState = dditable->zes.Device.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetState( hDevice, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceReset
    __zedlllocal ze_result_t __zecall
    zesDeviceReset(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnReset = dditable->zes.Device.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnReset( hDevice, force );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceProcessesGetState
    __zedlllocal ze_result_t __zecall
    zesDeviceProcessesGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
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
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnProcessesGetState = dditable->zes.Device.pfnProcessesGetState;
        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnProcessesGetState( hDevice, pCount, pProcesses );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetProperties
    __zedlllocal ze_result_t __zecall
    zesDevicePciGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetProperties = dditable->zes.Device.pfnPciGetProperties;
        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnPciGetProperties( hDevice, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetState
    __zedlllocal ze_result_t __zecall
    zesDevicePciGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetState = dditable->zes.Device.pfnPciGetState;
        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnPciGetState( hDevice, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetBars
    __zedlllocal ze_result_t __zecall
    zesDevicePciGetBars(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
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
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetBars = dditable->zes.Device.pfnPciGetBars;
        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnPciGetBars( hDevice, pCount, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetStats
    __zedlllocal ze_result_t __zecall
    zesDevicePciGetStats(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetStats = dditable->zes.Device.pfnPciGetStats;
        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnPciGetStats( hDevice, pStats );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumDiagnosticTestSuites
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumDiagnosticTestSuites(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_diag_handle_t* phDiagnostics                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumDiagnosticTestSuites = dditable->zes.Device.pfnEnumDiagnosticTestSuites;
        if( nullptr == pfnEnumDiagnosticTestSuites )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<zes_diag_handle_t>(
                    zes_diag_factory.getInstance( phDiagnostics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDiagnosticsGetProperties
    __zedlllocal ze_result_t __zecall
    zesDiagnosticsGetProperties(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetProperties = dditable->zes.Diagnostics.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDiagnostics, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDiagnosticsGetTests
    __zedlllocal ze_result_t __zecall
    zesDiagnosticsGetTests(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
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
        auto dditable = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetTests = dditable->zes.Diagnostics.pfnGetTests;
        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnGetTests( hDiagnostics, pCount, pTests );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDiagnosticsRunTests
    __zedlllocal ze_result_t __zecall
    zesDiagnosticsRunTests(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnRunTests = dditable->zes.Diagnostics.pfnRunTests;
        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnRunTests( hDiagnostics, start, end, pResult );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumEngineGroups
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumEngineGroups(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_engine_handle_t* phEngine                   ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumEngineGroups = dditable->zes.Device.pfnEnumEngineGroups;
        if( nullptr == pfnEnumEngineGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumEngineGroups( hDevice, pCount, phEngine );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<zes_engine_handle_t>(
                    zes_engine_factory.getInstance( phEngine[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetProperties
    __zedlllocal ze_result_t __zecall
    zesEngineGetProperties(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_engine_object_t*>( hEngine )->dditable;
        auto pfnGetProperties = dditable->zes.Engine.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zes_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetProperties( hEngine, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetActivity
    __zedlllocal ze_result_t __zecall
    zesEngineGetActivity(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_engine_object_t*>( hEngine )->dditable;
        auto pfnGetActivity = dditable->zes.Engine.pfnGetActivity;
        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zes_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetActivity( hEngine, pStats );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceCreateEvents
    __zedlllocal ze_result_t __zecall
    zesDeviceCreateEvents(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        zes_event_handle_t* phEvent                     ///< [out] The event handle for the specified device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnCreateEvents = dditable->zes.Device.pfnCreateEvents;
        if( nullptr == pfnCreateEvents )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreateEvents( hDevice, phEvent );

        try
        {
            // convert driver handle to loader handle
            *phEvent = reinterpret_cast<zes_event_handle_t>(
                zes_event_factory.getInstance( *phEvent, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEventGetConfig
    __zedlllocal ze_result_t __zecall
    zesEventGetConfig(
        zes_event_handle_t hEvent,                      ///< [in] The event handle for the device
        zes_event_config_t* pConfig                     ///< [in,out] Will contain the current event configuration (list of
                                                        ///< registered events).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_event_object_t*>( hEvent )->dditable;
        auto pfnGetConfig = dditable->zes.Event.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zes_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnGetConfig( hEvent, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEventSetConfig
    __zedlllocal ze_result_t __zecall
    zesEventSetConfig(
        zes_event_handle_t hEvent,                      ///< [in] The event handle for the device
        const zes_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_event_object_t*>( hEvent )->dditable;
        auto pfnSetConfig = dditable->zes.Event.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zes_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnSetConfig( hEvent, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEventGetState
    __zedlllocal ze_result_t __zecall
    zesEventGetState(
        zes_event_handle_t hEvent,                      ///< [in] The event handle for the device.
        ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
        uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_event_type_t that have been
                                                        ///< triggered by this device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_event_object_t*>( hEvent )->dditable;
        auto pfnGetState = dditable->zes.Event.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zes_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnGetState( hEvent, clear, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEventListen
    __zedlllocal ze_result_t __zecall
    zesEventListen(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                        ///< ::ZES_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                        ///< ::ZES_EVENT_WAIT_INFINITE to block until events arrive.
        uint32_t count,                                 ///< [in] Number of handles in phEvents
        zes_event_handle_t* phEvents,                   ///< [in][range(0, count)] Handle of events that should be listened to
        uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_event_type_t that have been
                                                        ///< triggered by any of the supplied event handles. If timeout is not
                                                        ///< ::ZES_EVENT_WAIT_INFINITE and this value is ::ZES_EVENT_TYPE_NONE,
                                                        ///< then a timeout has occurred.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnListen = dditable->zes.Event.pfnListen;
        if( nullptr == pfnListen )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phEvents ) && ( i < count ); ++i )
            phEvents[ i ] = reinterpret_cast<zes_event_object_t*>( phEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnListen( hDriver, timeout, count, phEvents, pEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFabricPorts
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumFabricPorts(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_fabric_port_handle_t* phPort                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFabricPorts = dditable->zes.Device.pfnEnumFabricPorts;
        if( nullptr == pfnEnumFabricPorts )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFabricPorts( hDevice, pCount, phPort );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<zes_fabric_port_handle_t>(
                    zes_fabric_port_factory.getInstance( phPort[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetProperties
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetProperties(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetProperties = dditable->zes.FabricPort.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPort, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetLinkType
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetLinkType(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
        zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetLinkType = dditable->zes.FabricPort.pfnGetLinkType;
        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetLinkType( hPort, verbose, pLinkType );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetConfig
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetConfig = dditable->zes.FabricPort.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetConfig( hPort, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortSetConfig
    __zedlllocal ze_result_t __zecall
    zesFabricPortSetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnSetConfig = dditable->zes.FabricPort.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnSetConfig( hPort, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetState
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetState(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetState = dditable->zes.FabricPort.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetState( hPort, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetThroughput
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetThroughput(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetThroughput = dditable->zes.FabricPort.pfnGetThroughput;
        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetThroughput( hPort, pThroughput );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFans
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumFans(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_fan_handle_t* phFan                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFans = dditable->zes.Device.pfnEnumFans;
        if( nullptr == pfnEnumFans )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFans( hDevice, pCount, phFan );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<zes_fan_handle_t>(
                    zes_fan_factory.getInstance( phFan[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetProperties
    __zedlllocal ze_result_t __zecall
    zesFanGetProperties(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnGetProperties = dditable->zes.Fan.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFan, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetConfig
    __zedlllocal ze_result_t __zecall
    zesFanGetConfig(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnGetConfig = dditable->zes.Fan.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetConfig( hFan, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetConfig
    __zedlllocal ze_result_t __zecall
    zesFanSetConfig(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnSetConfig = dditable->zes.Fan.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnSetConfig( hFan, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetState
    __zedlllocal ze_result_t __zecall
    zesFanGetState(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnGetState = dditable->zes.Fan.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetState( hFan, units, pSpeed );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFirmwares
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumFirmwares(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_firmware_handle_t* phFirmware               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFirmwares = dditable->zes.Device.pfnEnumFirmwares;
        if( nullptr == pfnEnumFirmwares )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFirmwares( hDevice, pCount, phFirmware );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<zes_firmware_handle_t>(
                    zes_firmware_factory.getInstance( phFirmware[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareGetProperties
    __zedlllocal ze_result_t __zecall
    zesFirmwareGetProperties(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetProperties = dditable->zes.Firmware.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFirmware, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareGetChecksum
    __zedlllocal ze_result_t __zecall
    zesFirmwareGetChecksum(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetChecksum = dditable->zes.Firmware.pfnGetChecksum;
        if( nullptr == pfnGetChecksum )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetChecksum( hFirmware, pChecksum );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareFlash
    __zedlllocal ze_result_t __zecall
    zesFirmwareFlash(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnFlash = dditable->zes.Firmware.pfnFlash;
        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnFlash( hFirmware, pImage, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFrequencyDomains
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumFrequencyDomains(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_freq_handle_t* phFrequency                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFrequencyDomains = dditable->zes.Device.pfnEnumFrequencyDomains;
        if( nullptr == pfnEnumFrequencyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<zes_freq_handle_t>(
                    zes_freq_factory.getInstance( phFrequency[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetProperties
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetProperties(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetProperties = dditable->zes.Frequency.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFrequency, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetAvailableClocks
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetAvailableClocks(
        zes_freq_handle_t hFrequency,                   ///< [in] Sysman handle of the device.
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
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetAvailableClocks = dditable->zes.Frequency.pfnGetAvailableClocks;
        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetRange
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetRange(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetRange = dditable->zes.Frequency.pfnGetRange;
        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetRange( hFrequency, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencySetRange
    __zedlllocal ze_result_t __zecall
    zesFrequencySetRange(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetRange = dditable->zes.Frequency.pfnSetRange;
        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetRange( hFrequency, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetState
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetState(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetState = dditable->zes.Frequency.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetState( hFrequency, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetThrottleTime
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetThrottleTime(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetThrottleTime = dditable->zes.Frequency.pfnGetThrottleTime;
        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetThrottleTime( hFrequency, pThrottleTime );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetCapabilities
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetCapabilities(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetCapabilities = dditable->zes.Frequency.pfnOcGetCapabilities;
        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetConfig
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetConfig(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zes_oc_config_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetConfig = dditable->zes.Frequency.pfnOcGetConfig;
        if( nullptr == pfnOcGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetConfig( hFrequency, pOcConfiguration );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetConfig
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcSetConfig(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zes_oc_config_t.
        ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                        ///< in order to enable the new overclock settings.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetConfig = dditable->zes.Frequency.pfnOcSetConfig;
        if( nullptr == pfnOcSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetIccMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetIccMax = dditable->zes.Frequency.pfnOcGetIccMax;
        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetIccMax( hFrequency, pOcIccMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetIccMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcSetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetIccMax = dditable->zes.Frequency.pfnOcSetIccMax;
        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetIccMax( hFrequency, ocIccMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetTjMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetTjMax = dditable->zes.Frequency.pfnOcGetTjMax;
        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetTjMax( hFrequency, pOcTjMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetTjMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcSetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetTjMax = dditable->zes.Frequency.pfnOcSetTjMax;
        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetTjMax( hFrequency, ocTjMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumLeds
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumLeds(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_led_handle_t* phLed                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumLeds = dditable->zes.Device.pfnEnumLeds;
        if( nullptr == pfnEnumLeds )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumLeds( hDevice, pCount, phLed );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<zes_led_handle_t>(
                    zes_led_factory.getInstance( phLed[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetProperties
    __zedlllocal ze_result_t __zecall
    zesLedGetProperties(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_led_object_t*>( hLed )->dditable;
        auto pfnGetProperties = dditable->zes.Led.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetProperties( hLed, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetState
    __zedlllocal ze_result_t __zecall
    zesLedGetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_led_object_t*>( hLed )->dditable;
        auto pfnGetState = dditable->zes.Led.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetState( hLed, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedSetState
    __zedlllocal ze_result_t __zecall
    zesLedSetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_led_object_t*>( hLed )->dditable;
        auto pfnSetState = dditable->zes.Led.pfnSetState;
        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnSetState( hLed, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumMemoryModules
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumMemoryModules(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_mem_handle_t* phMemory                      ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumMemoryModules = dditable->zes.Device.pfnEnumMemoryModules;
        if( nullptr == pfnEnumMemoryModules )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumMemoryModules( hDevice, pCount, phMemory );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<zes_mem_handle_t>(
                    zes_mem_factory.getInstance( phMemory[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetProperties
    __zedlllocal ze_result_t __zecall
    zesMemoryGetProperties(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_mem_object_t*>( hMemory )->dditable;
        auto pfnGetProperties = dditable->zes.Memory.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMemory, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetState
    __zedlllocal ze_result_t __zecall
    zesMemoryGetState(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_mem_object_t*>( hMemory )->dditable;
        auto pfnGetState = dditable->zes.Memory.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetState( hMemory, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetBandwidth
    __zedlllocal ze_result_t __zecall
    zesMemoryGetBandwidth(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the current health, free memory, total memory
                                                        ///< size.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_mem_object_t*>( hMemory )->dditable;
        auto pfnGetBandwidth = dditable->zes.Memory.pfnGetBandwidth;
        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetBandwidth( hMemory, pBandwidth );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumPerformanceFactorDomains
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumPerformanceFactorDomains(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_perf_handle_t* phPerf                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumPerformanceFactorDomains = dditable->zes.Device.pfnEnumPerformanceFactorDomains;
        if( nullptr == pfnEnumPerformanceFactorDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPerf ) && ( i < *pCount ); ++i )
                phPerf[ i ] = reinterpret_cast<zes_perf_handle_t>(
                    zes_perf_factory.getInstance( phPerf[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorGetProperties
    __zedlllocal ze_result_t __zecall
    zesPerformanceFactorGetProperties(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_perf_object_t*>( hPerf )->dditable;
        auto pfnGetProperties = dditable->zes.PerformanceFactor.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_perf_object_t*>( hPerf )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPerf, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorGetConfig
    __zedlllocal ze_result_t __zecall
    zesPerformanceFactorGetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_perf_object_t*>( hPerf )->dditable;
        auto pfnGetConfig = dditable->zes.PerformanceFactor.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_perf_object_t*>( hPerf )->handle;

        // forward to device-driver
        result = pfnGetConfig( hPerf, pFactor );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorSetConfig
    __zedlllocal ze_result_t __zecall
    zesPerformanceFactorSetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_perf_object_t*>( hPerf )->dditable;
        auto pfnSetConfig = dditable->zes.PerformanceFactor.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_perf_object_t*>( hPerf )->handle;

        // forward to device-driver
        result = pfnSetConfig( hPerf, factor );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumPowerDomains
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumPowerDomains(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_pwr_handle_t* phPower                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumPowerDomains = dditable->zes.Device.pfnEnumPowerDomains;
        if( nullptr == pfnEnumPowerDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumPowerDomains( hDevice, pCount, phPower );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<zes_pwr_handle_t>(
                    zes_pwr_factory.getInstance( phPower[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetProperties
    __zedlllocal ze_result_t __zecall
    zesPowerGetProperties(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetProperties = dditable->zes.Power.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPower, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetEnergyCounter
    __zedlllocal ze_result_t __zecall
    zesPowerGetEnergyCounter(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyCounter = dditable->zes.Power.pfnGetEnergyCounter;
        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyCounter( hPower, pEnergy );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetLimits
    __zedlllocal ze_result_t __zecall
    zesPowerGetLimits(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit.
        zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit.
        zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetLimits = dditable->zes.Power.pfnGetLimits;
        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerSetLimits
    __zedlllocal ze_result_t __zecall
    zesPowerSetLimits(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnSetLimits = dditable->zes.Power.pfnSetLimits;
        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetEnergyThreshold
    __zedlllocal ze_result_t __zecall
    zesPowerGetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyThreshold = dditable->zes.Power.pfnGetEnergyThreshold;
        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyThreshold( hPower, pThreshold );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerSetEnergyThreshold
    __zedlllocal ze_result_t __zecall
    zesPowerSetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnSetEnergyThreshold = dditable->zes.Power.pfnSetEnergyThreshold;
        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetEnergyThreshold( hPower, threshold );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumPsus
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumPsus(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_psu_handle_t* phPsu                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumPsus = dditable->zes.Device.pfnEnumPsus;
        if( nullptr == pfnEnumPsus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumPsus( hDevice, pCount, phPsu );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<zes_psu_handle_t>(
                    zes_psu_factory.getInstance( phPsu[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetProperties
    __zedlllocal ze_result_t __zecall
    zesPsuGetProperties(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_psu_object_t*>( hPsu )->dditable;
        auto pfnGetProperties = dditable->zes.Psu.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zes_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPsu, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetState
    __zedlllocal ze_result_t __zecall
    zesPsuGetState(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_psu_object_t*>( hPsu )->dditable;
        auto pfnGetState = dditable->zes.Psu.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zes_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetState( hPsu, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumRasErrorSets
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumRasErrorSets(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_ras_handle_t* phRas                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumRasErrorSets = dditable->zes.Device.pfnEnumRasErrorSets;
        if( nullptr == pfnEnumRasErrorSets )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumRasErrorSets( hDevice, pCount, phRas );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<zes_ras_handle_t>(
                    zes_ras_factory.getInstance( phRas[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetProperties
    __zedlllocal ze_result_t __zecall
    zesRasGetProperties(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnGetProperties = dditable->zes.Ras.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetProperties( hRas, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetConfig
    __zedlllocal ze_result_t __zecall
    zesRasGetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnGetConfig = dditable->zes.Ras.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetConfig( hRas, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasSetConfig
    __zedlllocal ze_result_t __zecall
    zesRasSetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnSetConfig = dditable->zes.Ras.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnSetConfig( hRas, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetState
    __zedlllocal ze_result_t __zecall
    zesRasGetState(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnGetState = dditable->zes.Ras.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetState( hRas, clear, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumSchedulers
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumSchedulers(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_sched_handle_t* phScheduler                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumSchedulers = dditable->zes.Device.pfnEnumSchedulers;
        if( nullptr == pfnEnumSchedulers )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumSchedulers( hDevice, pCount, phScheduler );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phScheduler ) && ( i < *pCount ); ++i )
                phScheduler[ i ] = reinterpret_cast<zes_sched_handle_t>(
                    zes_sched_factory.getInstance( phScheduler[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetProperties
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetProperties = dditable->zes.Scheduler.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetProperties( hScheduler, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetCurrentMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetCurrentMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetCurrentMode = dditable->zes.Scheduler.pfnGetCurrentMode;
        if( nullptr == pfnGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetCurrentMode( hScheduler, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetTimeoutModeProperties
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetTimeoutModeProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetTimeoutModeProperties = dditable->zes.Scheduler.pfnGetTimeoutModeProperties;
        if( nullptr == pfnGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetTimesliceModeProperties
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetTimesliceModeProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetTimesliceModeProperties = dditable->zes.Scheduler.pfnGetTimesliceModeProperties;
        if( nullptr == pfnGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetTimeoutMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetTimeoutMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetTimeoutMode = dditable->zes.Scheduler.pfnSetTimeoutMode;
        if( nullptr == pfnSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetTimesliceMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetTimesliceMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetTimesliceMode = dditable->zes.Scheduler.pfnSetTimesliceMode;
        if( nullptr == pfnSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetExclusiveMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetExclusiveMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetExclusiveMode = dditable->zes.Scheduler.pfnSetExclusiveMode;
        if( nullptr == pfnSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetExclusiveMode( hScheduler, pNeedReload );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetComputeUnitDebugMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetComputeUnitDebugMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetComputeUnitDebugMode = dditable->zes.Scheduler.pfnSetComputeUnitDebugMode;
        if( nullptr == pfnSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

        // forward to device-driver
        result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumStandbyDomains
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumStandbyDomains(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_standby_handle_t* phStandby                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumStandbyDomains = dditable->zes.Device.pfnEnumStandbyDomains;
        if( nullptr == pfnEnumStandbyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumStandbyDomains( hDevice, pCount, phStandby );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<zes_standby_handle_t>(
                    zes_standby_factory.getInstance( phStandby[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetProperties
    __zedlllocal ze_result_t __zecall
    zesStandbyGetProperties(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_standby_object_t*>( hStandby )->dditable;
        auto pfnGetProperties = dditable->zes.Standby.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetProperties( hStandby, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetMode
    __zedlllocal ze_result_t __zecall
    zesStandbyGetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_standby_object_t*>( hStandby )->dditable;
        auto pfnGetMode = dditable->zes.Standby.pfnGetMode;
        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetMode( hStandby, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbySetMode
    __zedlllocal ze_result_t __zecall
    zesStandbySetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_standby_object_t*>( hStandby )->dditable;
        auto pfnSetMode = dditable->zes.Standby.pfnSetMode;
        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnSetMode( hStandby, mode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumTemperatureSensors
    __zedlllocal ze_result_t __zecall
    zesDeviceEnumTemperatureSensors(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zes_temp_handle_t* phTemperature                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumTemperatureSensors = dditable->zes.Device.pfnEnumTemperatureSensors;
        if( nullptr == pfnEnumTemperatureSensors )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<zes_temp_handle_t>(
                    zes_temp_factory.getInstance( phTemperature[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetProperties
    __zedlllocal ze_result_t __zecall
    zesTemperatureGetProperties(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetProperties = dditable->zes.Temperature.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetProperties( hTemperature, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetConfig
    __zedlllocal ze_result_t __zecall
    zesTemperatureGetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetConfig = dditable->zes.Temperature.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetConfig( hTemperature, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureSetConfig
    __zedlllocal ze_result_t __zecall
    zesTemperatureSetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnSetConfig = dditable->zes.Temperature.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnSetConfig( hTemperature, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetState
    __zedlllocal ze_result_t __zecall
    zesTemperatureGetState(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetState = dditable->zes.Temperature.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetState( hTemperature, pTemperature );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetDeviceProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Device );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesDeviceGetProperties;
            pDdiTable->pfnGetState                                 = loader::zesDeviceGetState;
            pDdiTable->pfnReset                                    = loader::zesDeviceReset;
            pDdiTable->pfnProcessesGetState                        = loader::zesDeviceProcessesGetState;
            pDdiTable->pfnPciGetProperties                         = loader::zesDevicePciGetProperties;
            pDdiTable->pfnPciGetState                              = loader::zesDevicePciGetState;
            pDdiTable->pfnPciGetBars                               = loader::zesDevicePciGetBars;
            pDdiTable->pfnPciGetStats                              = loader::zesDevicePciGetStats;
            pDdiTable->pfnEnumDiagnosticTestSuites                 = loader::zesDeviceEnumDiagnosticTestSuites;
            pDdiTable->pfnEnumEngineGroups                         = loader::zesDeviceEnumEngineGroups;
            pDdiTable->pfnCreateEvents                             = loader::zesDeviceCreateEvents;
            pDdiTable->pfnEnumFabricPorts                          = loader::zesDeviceEnumFabricPorts;
            pDdiTable->pfnEnumFans                                 = loader::zesDeviceEnumFans;
            pDdiTable->pfnEnumFirmwares                            = loader::zesDeviceEnumFirmwares;
            pDdiTable->pfnEnumFrequencyDomains                     = loader::zesDeviceEnumFrequencyDomains;
            pDdiTable->pfnEnumLeds                                 = loader::zesDeviceEnumLeds;
            pDdiTable->pfnEnumMemoryModules                        = loader::zesDeviceEnumMemoryModules;
            pDdiTable->pfnEnumPerformanceFactorDomains             = loader::zesDeviceEnumPerformanceFactorDomains;
            pDdiTable->pfnEnumPowerDomains                         = loader::zesDeviceEnumPowerDomains;
            pDdiTable->pfnEnumPsus                                 = loader::zesDeviceEnumPsus;
            pDdiTable->pfnEnumRasErrorSets                         = loader::zesDeviceEnumRasErrorSets;
            pDdiTable->pfnEnumSchedulers                           = loader::zesDeviceEnumSchedulers;
            pDdiTable->pfnEnumStandbyDomains                       = loader::zesDeviceEnumStandbyDomains;
            pDdiTable->pfnEnumTemperatureSensors                   = loader::zesDeviceEnumTemperatureSensors;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetDeviceProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Scheduler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSchedulerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_scheduler_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetSchedulerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetSchedulerProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Scheduler );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesSchedulerGetProperties;
            pDdiTable->pfnGetCurrentMode                           = loader::zesSchedulerGetCurrentMode;
            pDdiTable->pfnGetTimeoutModeProperties                 = loader::zesSchedulerGetTimeoutModeProperties;
            pDdiTable->pfnGetTimesliceModeProperties               = loader::zesSchedulerGetTimesliceModeProperties;
            pDdiTable->pfnSetTimeoutMode                           = loader::zesSchedulerSetTimeoutMode;
            pDdiTable->pfnSetTimesliceMode                         = loader::zesSchedulerSetTimesliceMode;
            pDdiTable->pfnSetExclusiveMode                         = loader::zesSchedulerSetExclusiveMode;
            pDdiTable->pfnSetComputeUnitDebugMode                  = loader::zesSchedulerSetComputeUnitDebugMode;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Scheduler;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSchedulerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetSchedulerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PerformanceFactor table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetPerformanceFactorProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_performance_factor_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetPerformanceFactorProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetPerformanceFactorProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.PerformanceFactor );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesPerformanceFactorGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesPerformanceFactorGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesPerformanceFactorSetConfig;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.PerformanceFactor;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetPerformanceFactorProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetPerformanceFactorProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_power_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetPowerProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Power );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesPowerGetProperties;
            pDdiTable->pfnGetEnergyCounter                         = loader::zesPowerGetEnergyCounter;
            pDdiTable->pfnGetLimits                                = loader::zesPowerGetLimits;
            pDdiTable->pfnSetLimits                                = loader::zesPowerSetLimits;
            pDdiTable->pfnGetEnergyThreshold                       = loader::zesPowerGetEnergyThreshold;
            pDdiTable->pfnSetEnergyThreshold                       = loader::zesPowerSetEnergyThreshold;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Power;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetPowerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Frequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_frequency_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetFrequencyProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Frequency );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesFrequencyGetProperties;
            pDdiTable->pfnGetAvailableClocks                       = loader::zesFrequencyGetAvailableClocks;
            pDdiTable->pfnGetRange                                 = loader::zesFrequencyGetRange;
            pDdiTable->pfnSetRange                                 = loader::zesFrequencySetRange;
            pDdiTable->pfnGetState                                 = loader::zesFrequencyGetState;
            pDdiTable->pfnGetThrottleTime                          = loader::zesFrequencyGetThrottleTime;
            pDdiTable->pfnOcGetCapabilities                        = loader::zesFrequencyOcGetCapabilities;
            pDdiTable->pfnOcGetConfig                              = loader::zesFrequencyOcGetConfig;
            pDdiTable->pfnOcSetConfig                              = loader::zesFrequencyOcSetConfig;
            pDdiTable->pfnOcGetIccMax                              = loader::zesFrequencyOcGetIccMax;
            pDdiTable->pfnOcSetIccMax                              = loader::zesFrequencyOcSetIccMax;
            pDdiTable->pfnOcGetTjMax                               = loader::zesFrequencyOcGetTjMax;
            pDdiTable->pfnOcSetTjMax                               = loader::zesFrequencyOcSetTjMax;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Frequency;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFrequencyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetFrequencyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Engine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_engine_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetEngineProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetEngineProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Engine );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesEngineGetProperties;
            pDdiTable->pfnGetActivity                              = loader::zesEngineGetActivity;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Engine;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetEngineProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetEngineProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Standby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_standby_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetStandbyProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Standby );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesStandbyGetProperties;
            pDdiTable->pfnGetMode                                  = loader::zesStandbyGetMode;
            pDdiTable->pfnSetMode                                  = loader::zesStandbySetMode;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Standby;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetStandbyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetStandbyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Firmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_firmware_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetFirmwareProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Firmware );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesFirmwareGetProperties;
            pDdiTable->pfnGetChecksum                              = loader::zesFirmwareGetChecksum;
            pDdiTable->pfnFlash                                    = loader::zesFirmwareFlash;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Firmware;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFirmwareProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetFirmwareProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Memory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_memory_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetMemoryProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Memory );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesMemoryGetProperties;
            pDdiTable->pfnGetState                                 = loader::zesMemoryGetState;
            pDdiTable->pfnGetBandwidth                             = loader::zesMemoryGetBandwidth;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Memory;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetMemoryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetMemoryProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fabric_port_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetFabricPortProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.FabricPort );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesFabricPortGetProperties;
            pDdiTable->pfnGetLinkType                              = loader::zesFabricPortGetLinkType;
            pDdiTable->pfnGetConfig                                = loader::zesFabricPortGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesFabricPortSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesFabricPortGetState;
            pDdiTable->pfnGetThroughput                            = loader::zesFabricPortGetThroughput;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.FabricPort;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFabricPortProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetFabricPortProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Temperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_temperature_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetTemperatureProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Temperature );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesTemperatureGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesTemperatureGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesTemperatureSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesTemperatureGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Temperature;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetTemperatureProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetTemperatureProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Psu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_psu_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetPsuProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetPsuProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Psu );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesPsuGetProperties;
            pDdiTable->pfnGetState                                 = loader::zesPsuGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Psu;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetPsuProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetPsuProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fan_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetFanProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetFanProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Fan );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesFanGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesFanGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesFanSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesFanGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Fan;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetFanProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Led table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_led_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetLedProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetLedProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Led );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesLedGetProperties;
            pDdiTable->pfnGetState                                 = loader::zesLedGetState;
            pDdiTable->pfnSetState                                 = loader::zesLedSetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Led;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetLedProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetLedProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Ras table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_ras_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetRasProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetRasProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Ras );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesRasGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zesRasGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesRasSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesRasGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Ras;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetRasProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetRasProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Diagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_diagnostics_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetDiagnosticsProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Diagnostics );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zesDiagnosticsGetProperties;
            pDdiTable->pfnGetTests                                 = loader::zesDiagnosticsGetTests;
            pDdiTable->pfnRunTests                                 = loader::zesDiagnosticsRunTests;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Diagnostics;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetDiagnosticsProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetDiagnosticsProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_event_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
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
            auto getTable = reinterpret_cast<zes_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zesGetEventProcAddrTable") );
            result = getTable( version, &drv.dditable.zes.Event );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetConfig                                = loader::zesEventGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zesEventSetConfig;
            pDdiTable->pfnGetState                                 = loader::zesEventGetState;
            pDdiTable->pfnListen                                   = loader::zesEventListen;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zes.Event;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zesGetEventProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
