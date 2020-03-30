/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_valddi.cpp
 * @version v0.91-271
 *
 */
#include "ze_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetProperties
    __zedlllocal ze_result_t __zecall
    zesDeviceGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hDevice, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetState
    __zedlllocal ze_result_t __zecall
    zesDeviceGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto pfnGetState = context.zesDdiTable.Device.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hDevice, pState );
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
        auto pfnReset = context.zesDdiTable.Device.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnReset( hDevice, force );
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
        auto pfnProcessesGetState = context.zesDdiTable.Device.pfnProcessesGetState;

        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnProcessesGetState( hDevice, pCount, pProcesses );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetProperties
    __zedlllocal ze_result_t __zecall
    zesDevicePciGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        auto pfnPciGetProperties = context.zesDdiTable.Device.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetProperties( hDevice, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetState
    __zedlllocal ze_result_t __zecall
    zesDevicePciGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        auto pfnPciGetState = context.zesDdiTable.Device.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetState( hDevice, pState );
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
        auto pfnPciGetBars = context.zesDdiTable.Device.pfnPciGetBars;

        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetBars( hDevice, pCount, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetStats
    __zedlllocal ze_result_t __zecall
    zesDevicePciGetStats(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        auto pfnPciGetStats = context.zesDdiTable.Device.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetStats( hDevice, pStats );
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
        auto pfnEnumDiagnosticTestSuites = context.zesDdiTable.Device.pfnEnumDiagnosticTestSuites;

        if( nullptr == pfnEnumDiagnosticTestSuites )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
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
        auto pfnGetProperties = context.zesDdiTable.Diagnostics.pfnGetProperties;

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
        auto pfnGetTests = context.zesDdiTable.Diagnostics.pfnGetTests;

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
        auto pfnRunTests = context.zesDdiTable.Diagnostics.pfnRunTests;

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
        auto pfnEnumEngineGroups = context.zesDdiTable.Device.pfnEnumEngineGroups;

        if( nullptr == pfnEnumEngineGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumEngineGroups( hDevice, pCount, phEngine );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetProperties
    __zedlllocal ze_result_t __zecall
    zesEngineGetProperties(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Engine.pfnGetProperties;

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
    /// @brief Intercept function for zesEngineGetActivity
    __zedlllocal ze_result_t __zecall
    zesEngineGetActivity(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    {
        auto pfnGetActivity = context.zesDdiTable.Engine.pfnGetActivity;

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
    /// @brief Intercept function for zesDeviceCreateEvents
    __zedlllocal ze_result_t __zecall
    zesDeviceCreateEvents(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        zes_event_handle_t* phEvent                     ///< [out] The event handle for the specified device.
        )
    {
        auto pfnCreateEvents = context.zesDdiTable.Device.pfnCreateEvents;

        if( nullptr == pfnCreateEvents )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnCreateEvents( hDevice, phEvent );
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
        auto pfnGetConfig = context.zesDdiTable.Event.pfnGetConfig;

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
    /// @brief Intercept function for zesEventSetConfig
    __zedlllocal ze_result_t __zecall
    zesEventSetConfig(
        zes_event_handle_t hEvent,                      ///< [in] The event handle for the device
        const zes_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
        )
    {
        auto pfnSetConfig = context.zesDdiTable.Event.pfnSetConfig;

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
    /// @brief Intercept function for zesEventGetState
    __zedlllocal ze_result_t __zecall
    zesEventGetState(
        zes_event_handle_t hEvent,                      ///< [in] The event handle for the device.
        ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
        uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_event_type_t that have been
                                                        ///< triggered by this device.
        )
    {
        auto pfnGetState = context.zesDdiTable.Event.pfnGetState;

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
        auto pfnListen = context.zesDdiTable.Event.pfnListen;

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
        auto pfnEnumFabricPorts = context.zesDdiTable.Device.pfnEnumFabricPorts;

        if( nullptr == pfnEnumFabricPorts )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFabricPorts( hDevice, pCount, phPort );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetProperties
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetProperties(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.FabricPort.pfnGetProperties;

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
    /// @brief Intercept function for zesFabricPortGetLinkType
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetLinkType(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
        zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    {
        auto pfnGetLinkType = context.zesDdiTable.FabricPort.pfnGetLinkType;

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
    /// @brief Intercept function for zesFabricPortGetConfig
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.FabricPort.pfnGetConfig;

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
    /// @brief Intercept function for zesFabricPortSetConfig
    __zedlllocal ze_result_t __zecall
    zesFabricPortSetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.FabricPort.pfnSetConfig;

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
    /// @brief Intercept function for zesFabricPortGetState
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetState(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        auto pfnGetState = context.zesDdiTable.FabricPort.pfnGetState;

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
    /// @brief Intercept function for zesFabricPortGetThroughput
    __zedlllocal ze_result_t __zecall
    zesFabricPortGetThroughput(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        auto pfnGetThroughput = context.zesDdiTable.FabricPort.pfnGetThroughput;

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
        auto pfnEnumFans = context.zesDdiTable.Device.pfnEnumFans;

        if( nullptr == pfnEnumFans )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFans( hDevice, pCount, phFan );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetProperties
    __zedlllocal ze_result_t __zecall
    zesFanGetProperties(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Fan.pfnGetProperties;

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
    /// @brief Intercept function for zesFanGetConfig
    __zedlllocal ze_result_t __zecall
    zesFanGetConfig(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.Fan.pfnGetConfig;

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
    /// @brief Intercept function for zesFanSetConfig
    __zedlllocal ze_result_t __zecall
    zesFanSetConfig(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.Fan.pfnSetConfig;

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
    /// @brief Intercept function for zesFanGetState
    __zedlllocal ze_result_t __zecall
    zesFanGetState(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested.
        )
    {
        auto pfnGetState = context.zesDdiTable.Fan.pfnGetState;

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
        auto pfnEnumFirmwares = context.zesDdiTable.Device.pfnEnumFirmwares;

        if( nullptr == pfnEnumFirmwares )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFirmwares( hDevice, pCount, phFirmware );
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
        auto pfnGetProperties = context.zesDdiTable.Firmware.pfnGetProperties;

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
    /// @brief Intercept function for zesFirmwareGetChecksum
    __zedlllocal ze_result_t __zecall
    zesFirmwareGetChecksum(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
        )
    {
        auto pfnGetChecksum = context.zesDdiTable.Firmware.pfnGetChecksum;

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
    /// @brief Intercept function for zesFirmwareFlash
    __zedlllocal ze_result_t __zecall
    zesFirmwareFlash(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto pfnFlash = context.zesDdiTable.Firmware.pfnFlash;

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
        auto pfnEnumFrequencyDomains = context.zesDdiTable.Device.pfnEnumFrequencyDomains;

        if( nullptr == pfnEnumFrequencyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetProperties
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetProperties(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Frequency.pfnGetProperties;

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
        auto pfnGetAvailableClocks = context.zesDdiTable.Frequency.pfnGetAvailableClocks;

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
    /// @brief Intercept function for zesFrequencyGetRange
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetRange(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetRange = context.zesDdiTable.Frequency.pfnGetRange;

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
    /// @brief Intercept function for zesFrequencySetRange
    __zedlllocal ze_result_t __zecall
    zesFrequencySetRange(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnSetRange = context.zesDdiTable.Frequency.pfnSetRange;

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
    /// @brief Intercept function for zesFrequencyGetState
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetState(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        auto pfnGetState = context.zesDdiTable.Frequency.pfnGetState;

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
    /// @brief Intercept function for zesFrequencyGetThrottleTime
    __zedlllocal ze_result_t __zecall
    zesFrequencyGetThrottleTime(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetThrottleTime = context.zesDdiTable.Frequency.pfnGetThrottleTime;

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
    /// @brief Intercept function for zesFrequencyOcGetCapabilities
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetCapabilities(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        auto pfnOcGetCapabilities = context.zesDdiTable.Frequency.pfnOcGetCapabilities;

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
    /// @brief Intercept function for zesFrequencyOcGetConfig
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetConfig(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zes_oc_config_t.
        )
    {
        auto pfnOcGetConfig = context.zesDdiTable.Frequency.pfnOcGetConfig;

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
    /// @brief Intercept function for zesFrequencyOcSetConfig
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcSetConfig(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zes_oc_config_t.
        ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                        ///< in order to enable the new overclock settings.
        )
    {
        auto pfnOcSetConfig = context.zesDdiTable.Frequency.pfnOcSetConfig;

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
    /// @brief Intercept function for zesFrequencyOcGetIccMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    {
        auto pfnOcGetIccMax = context.zesDdiTable.Frequency.pfnOcGetIccMax;

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
    /// @brief Intercept function for zesFrequencyOcSetIccMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcSetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        auto pfnOcSetIccMax = context.zesDdiTable.Frequency.pfnOcSetIccMax;

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
    /// @brief Intercept function for zesFrequencyOcGetTjMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcGetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    {
        auto pfnOcGetTjMax = context.zesDdiTable.Frequency.pfnOcGetTjMax;

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
    /// @brief Intercept function for zesFrequencyOcSetTjMax
    __zedlllocal ze_result_t __zecall
    zesFrequencyOcSetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        auto pfnOcSetTjMax = context.zesDdiTable.Frequency.pfnOcSetTjMax;

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
        auto pfnEnumLeds = context.zesDdiTable.Device.pfnEnumLeds;

        if( nullptr == pfnEnumLeds )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumLeds( hDevice, pCount, phLed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetProperties
    __zedlllocal ze_result_t __zecall
    zesLedGetProperties(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Led.pfnGetProperties;

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
    /// @brief Intercept function for zesLedGetState
    __zedlllocal ze_result_t __zecall
    zesLedGetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        auto pfnGetState = context.zesDdiTable.Led.pfnGetState;

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
    /// @brief Intercept function for zesLedSetState
    __zedlllocal ze_result_t __zecall
    zesLedSetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        auto pfnSetState = context.zesDdiTable.Led.pfnSetState;

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
        auto pfnEnumMemoryModules = context.zesDdiTable.Device.pfnEnumMemoryModules;

        if( nullptr == pfnEnumMemoryModules )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumMemoryModules( hDevice, pCount, phMemory );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetProperties
    __zedlllocal ze_result_t __zecall
    zesMemoryGetProperties(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Memory.pfnGetProperties;

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
    /// @brief Intercept function for zesMemoryGetState
    __zedlllocal ze_result_t __zecall
    zesMemoryGetState(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        auto pfnGetState = context.zesDdiTable.Memory.pfnGetState;

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
    /// @brief Intercept function for zesMemoryGetBandwidth
    __zedlllocal ze_result_t __zecall
    zesMemoryGetBandwidth(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the current health, free memory, total memory
                                                        ///< size.
        )
    {
        auto pfnGetBandwidth = context.zesDdiTable.Memory.pfnGetBandwidth;

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
        auto pfnEnumPerformanceFactorDomains = context.zesDdiTable.Device.pfnEnumPerformanceFactorDomains;

        if( nullptr == pfnEnumPerformanceFactorDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
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
        auto pfnGetProperties = context.zesDdiTable.PerformanceFactor.pfnGetProperties;

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
    /// @brief Intercept function for zesPerformanceFactorGetConfig
    __zedlllocal ze_result_t __zecall
    zesPerformanceFactorGetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    {
        auto pfnGetConfig = context.zesDdiTable.PerformanceFactor.pfnGetConfig;

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
    /// @brief Intercept function for zesPerformanceFactorSetConfig
    __zedlllocal ze_result_t __zecall
    zesPerformanceFactorSetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.PerformanceFactor.pfnSetConfig;

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
        auto pfnEnumPowerDomains = context.zesDdiTable.Device.pfnEnumPowerDomains;

        if( nullptr == pfnEnumPowerDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumPowerDomains( hDevice, pCount, phPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetProperties
    __zedlllocal ze_result_t __zecall
    zesPowerGetProperties(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Power.pfnGetProperties;

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
    /// @brief Intercept function for zesPowerGetEnergyCounter
    __zedlllocal ze_result_t __zecall
    zesPowerGetEnergyCounter(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto pfnGetEnergyCounter = context.zesDdiTable.Power.pfnGetEnergyCounter;

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
    /// @brief Intercept function for zesPowerGetLimits
    __zedlllocal ze_result_t __zecall
    zesPowerGetLimits(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit.
        zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit.
        zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit.
        )
    {
        auto pfnGetLimits = context.zesDdiTable.Power.pfnGetLimits;

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
    /// @brief Intercept function for zesPowerSetLimits
    __zedlllocal ze_result_t __zecall
    zesPowerSetLimits(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        auto pfnSetLimits = context.zesDdiTable.Power.pfnSetLimits;

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
    /// @brief Intercept function for zesPowerGetEnergyThreshold
    __zedlllocal ze_result_t __zecall
    zesPowerGetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        auto pfnGetEnergyThreshold = context.zesDdiTable.Power.pfnGetEnergyThreshold;

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
    /// @brief Intercept function for zesPowerSetEnergyThreshold
    __zedlllocal ze_result_t __zecall
    zesPowerSetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        auto pfnSetEnergyThreshold = context.zesDdiTable.Power.pfnSetEnergyThreshold;

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
        auto pfnEnumPsus = context.zesDdiTable.Device.pfnEnumPsus;

        if( nullptr == pfnEnumPsus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumPsus( hDevice, pCount, phPsu );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetProperties
    __zedlllocal ze_result_t __zecall
    zesPsuGetProperties(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Psu.pfnGetProperties;

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
    /// @brief Intercept function for zesPsuGetState
    __zedlllocal ze_result_t __zecall
    zesPsuGetState(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        auto pfnGetState = context.zesDdiTable.Psu.pfnGetState;

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
        auto pfnEnumRasErrorSets = context.zesDdiTable.Device.pfnEnumRasErrorSets;

        if( nullptr == pfnEnumRasErrorSets )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumRasErrorSets( hDevice, pCount, phRas );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetProperties
    __zedlllocal ze_result_t __zecall
    zesRasGetProperties(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Ras.pfnGetProperties;

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
    /// @brief Intercept function for zesRasGetConfig
    __zedlllocal ze_result_t __zecall
    zesRasGetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    {
        auto pfnGetConfig = context.zesDdiTable.Ras.pfnGetConfig;

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
    /// @brief Intercept function for zesRasSetConfig
    __zedlllocal ze_result_t __zecall
    zesRasSetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        auto pfnSetConfig = context.zesDdiTable.Ras.pfnSetConfig;

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
    /// @brief Intercept function for zesRasGetState
    __zedlllocal ze_result_t __zecall
    zesRasGetState(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
        )
    {
        auto pfnGetState = context.zesDdiTable.Ras.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hRas, clear, pState );
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
        auto pfnEnumSchedulers = context.zesDdiTable.Device.pfnEnumSchedulers;

        if( nullptr == pfnEnumSchedulers )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumSchedulers( hDevice, pCount, phScheduler );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetProperties
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Scheduler.pfnGetProperties;

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
    /// @brief Intercept function for zesSchedulerGetCurrentMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetCurrentMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        auto pfnGetCurrentMode = context.zesDdiTable.Scheduler.pfnGetCurrentMode;

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
    /// @brief Intercept function for zesSchedulerGetTimeoutModeProperties
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetTimeoutModeProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto pfnGetTimeoutModeProperties = context.zesDdiTable.Scheduler.pfnGetTimeoutModeProperties;

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
    /// @brief Intercept function for zesSchedulerGetTimesliceModeProperties
    __zedlllocal ze_result_t __zecall
    zesSchedulerGetTimesliceModeProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto pfnGetTimesliceModeProperties = context.zesDdiTable.Scheduler.pfnGetTimesliceModeProperties;

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
    /// @brief Intercept function for zesSchedulerSetTimeoutMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetTimeoutMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetTimeoutMode = context.zesDdiTable.Scheduler.pfnSetTimeoutMode;

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
    /// @brief Intercept function for zesSchedulerSetTimesliceMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetTimesliceMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetTimesliceMode = context.zesDdiTable.Scheduler.pfnSetTimesliceMode;

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
    /// @brief Intercept function for zesSchedulerSetExclusiveMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetExclusiveMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetExclusiveMode = context.zesDdiTable.Scheduler.pfnSetExclusiveMode;

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
    /// @brief Intercept function for zesSchedulerSetComputeUnitDebugMode
    __zedlllocal ze_result_t __zecall
    zesSchedulerSetComputeUnitDebugMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetComputeUnitDebugMode = context.zesDdiTable.Scheduler.pfnSetComputeUnitDebugMode;

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
        auto pfnEnumStandbyDomains = context.zesDdiTable.Device.pfnEnumStandbyDomains;

        if( nullptr == pfnEnumStandbyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumStandbyDomains( hDevice, pCount, phStandby );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetProperties
    __zedlllocal ze_result_t __zecall
    zesStandbyGetProperties(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Standby.pfnGetProperties;

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
    /// @brief Intercept function for zesStandbyGetMode
    __zedlllocal ze_result_t __zecall
    zesStandbyGetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        auto pfnGetMode = context.zesDdiTable.Standby.pfnGetMode;

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
    /// @brief Intercept function for zesStandbySetMode
    __zedlllocal ze_result_t __zecall
    zesStandbySetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        auto pfnSetMode = context.zesDdiTable.Standby.pfnSetMode;

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
        auto pfnEnumTemperatureSensors = context.zesDdiTable.Device.pfnEnumTemperatureSensors;

        if( nullptr == pfnEnumTemperatureSensors )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetProperties
    __zedlllocal ze_result_t __zecall
    zesTemperatureGetProperties(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Temperature.pfnGetProperties;

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
    /// @brief Intercept function for zesTemperatureGetConfig
    __zedlllocal ze_result_t __zecall
    zesTemperatureGetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.Temperature.pfnGetConfig;

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
    /// @brief Intercept function for zesTemperatureSetConfig
    __zedlllocal ze_result_t __zecall
    zesTemperatureSetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.Temperature.pfnSetConfig;

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
    /// @brief Intercept function for zesTemperatureGetState
    __zedlllocal ze_result_t __zecall
    zesTemperatureGetState(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    {
        auto pfnGetState = context.zesDdiTable.Temperature.pfnGetState;

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

} // namespace layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesDeviceGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesDeviceGetState;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::zesDeviceReset;

    dditable.pfnProcessesGetState                        = pDdiTable->pfnProcessesGetState;
    pDdiTable->pfnProcessesGetState                      = layer::zesDeviceProcessesGetState;

    dditable.pfnPciGetProperties                         = pDdiTable->pfnPciGetProperties;
    pDdiTable->pfnPciGetProperties                       = layer::zesDevicePciGetProperties;

    dditable.pfnPciGetState                              = pDdiTable->pfnPciGetState;
    pDdiTable->pfnPciGetState                            = layer::zesDevicePciGetState;

    dditable.pfnPciGetBars                               = pDdiTable->pfnPciGetBars;
    pDdiTable->pfnPciGetBars                             = layer::zesDevicePciGetBars;

    dditable.pfnPciGetStats                              = pDdiTable->pfnPciGetStats;
    pDdiTable->pfnPciGetStats                            = layer::zesDevicePciGetStats;

    dditable.pfnEnumDiagnosticTestSuites                 = pDdiTable->pfnEnumDiagnosticTestSuites;
    pDdiTable->pfnEnumDiagnosticTestSuites               = layer::zesDeviceEnumDiagnosticTestSuites;

    dditable.pfnEnumEngineGroups                         = pDdiTable->pfnEnumEngineGroups;
    pDdiTable->pfnEnumEngineGroups                       = layer::zesDeviceEnumEngineGroups;

    dditable.pfnCreateEvents                             = pDdiTable->pfnCreateEvents;
    pDdiTable->pfnCreateEvents                           = layer::zesDeviceCreateEvents;

    dditable.pfnEnumFabricPorts                          = pDdiTable->pfnEnumFabricPorts;
    pDdiTable->pfnEnumFabricPorts                        = layer::zesDeviceEnumFabricPorts;

    dditable.pfnEnumFans                                 = pDdiTable->pfnEnumFans;
    pDdiTable->pfnEnumFans                               = layer::zesDeviceEnumFans;

    dditable.pfnEnumFirmwares                            = pDdiTable->pfnEnumFirmwares;
    pDdiTable->pfnEnumFirmwares                          = layer::zesDeviceEnumFirmwares;

    dditable.pfnEnumFrequencyDomains                     = pDdiTable->pfnEnumFrequencyDomains;
    pDdiTable->pfnEnumFrequencyDomains                   = layer::zesDeviceEnumFrequencyDomains;

    dditable.pfnEnumLeds                                 = pDdiTable->pfnEnumLeds;
    pDdiTable->pfnEnumLeds                               = layer::zesDeviceEnumLeds;

    dditable.pfnEnumMemoryModules                        = pDdiTable->pfnEnumMemoryModules;
    pDdiTable->pfnEnumMemoryModules                      = layer::zesDeviceEnumMemoryModules;

    dditable.pfnEnumPerformanceFactorDomains             = pDdiTable->pfnEnumPerformanceFactorDomains;
    pDdiTable->pfnEnumPerformanceFactorDomains           = layer::zesDeviceEnumPerformanceFactorDomains;

    dditable.pfnEnumPowerDomains                         = pDdiTable->pfnEnumPowerDomains;
    pDdiTable->pfnEnumPowerDomains                       = layer::zesDeviceEnumPowerDomains;

    dditable.pfnEnumPsus                                 = pDdiTable->pfnEnumPsus;
    pDdiTable->pfnEnumPsus                               = layer::zesDeviceEnumPsus;

    dditable.pfnEnumRasErrorSets                         = pDdiTable->pfnEnumRasErrorSets;
    pDdiTable->pfnEnumRasErrorSets                       = layer::zesDeviceEnumRasErrorSets;

    dditable.pfnEnumSchedulers                           = pDdiTable->pfnEnumSchedulers;
    pDdiTable->pfnEnumSchedulers                         = layer::zesDeviceEnumSchedulers;

    dditable.pfnEnumStandbyDomains                       = pDdiTable->pfnEnumStandbyDomains;
    pDdiTable->pfnEnumStandbyDomains                     = layer::zesDeviceEnumStandbyDomains;

    dditable.pfnEnumTemperatureSensors                   = pDdiTable->pfnEnumTemperatureSensors;
    pDdiTable->pfnEnumTemperatureSensors                 = layer::zesDeviceEnumTemperatureSensors;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Scheduler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetSchedulerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_scheduler_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Scheduler;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesSchedulerGetProperties;

    dditable.pfnGetCurrentMode                           = pDdiTable->pfnGetCurrentMode;
    pDdiTable->pfnGetCurrentMode                         = layer::zesSchedulerGetCurrentMode;

    dditable.pfnGetTimeoutModeProperties                 = pDdiTable->pfnGetTimeoutModeProperties;
    pDdiTable->pfnGetTimeoutModeProperties               = layer::zesSchedulerGetTimeoutModeProperties;

    dditable.pfnGetTimesliceModeProperties               = pDdiTable->pfnGetTimesliceModeProperties;
    pDdiTable->pfnGetTimesliceModeProperties             = layer::zesSchedulerGetTimesliceModeProperties;

    dditable.pfnSetTimeoutMode                           = pDdiTable->pfnSetTimeoutMode;
    pDdiTable->pfnSetTimeoutMode                         = layer::zesSchedulerSetTimeoutMode;

    dditable.pfnSetTimesliceMode                         = pDdiTable->pfnSetTimesliceMode;
    pDdiTable->pfnSetTimesliceMode                       = layer::zesSchedulerSetTimesliceMode;

    dditable.pfnSetExclusiveMode                         = pDdiTable->pfnSetExclusiveMode;
    pDdiTable->pfnSetExclusiveMode                       = layer::zesSchedulerSetExclusiveMode;

    dditable.pfnSetComputeUnitDebugMode                  = pDdiTable->pfnSetComputeUnitDebugMode;
    pDdiTable->pfnSetComputeUnitDebugMode                = layer::zesSchedulerSetComputeUnitDebugMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PerformanceFactor table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetPerformanceFactorProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_performance_factor_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.PerformanceFactor;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesPerformanceFactorGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesPerformanceFactorGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesPerformanceFactorSetConfig;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_power_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Power;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesPowerGetProperties;

    dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
    pDdiTable->pfnGetEnergyCounter                       = layer::zesPowerGetEnergyCounter;

    dditable.pfnGetLimits                                = pDdiTable->pfnGetLimits;
    pDdiTable->pfnGetLimits                              = layer::zesPowerGetLimits;

    dditable.pfnSetLimits                                = pDdiTable->pfnSetLimits;
    pDdiTable->pfnSetLimits                              = layer::zesPowerSetLimits;

    dditable.pfnGetEnergyThreshold                       = pDdiTable->pfnGetEnergyThreshold;
    pDdiTable->pfnGetEnergyThreshold                     = layer::zesPowerGetEnergyThreshold;

    dditable.pfnSetEnergyThreshold                       = pDdiTable->pfnSetEnergyThreshold;
    pDdiTable->pfnSetEnergyThreshold                     = layer::zesPowerSetEnergyThreshold;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Frequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_frequency_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Frequency;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesFrequencyGetProperties;

    dditable.pfnGetAvailableClocks                       = pDdiTable->pfnGetAvailableClocks;
    pDdiTable->pfnGetAvailableClocks                     = layer::zesFrequencyGetAvailableClocks;

    dditable.pfnGetRange                                 = pDdiTable->pfnGetRange;
    pDdiTable->pfnGetRange                               = layer::zesFrequencyGetRange;

    dditable.pfnSetRange                                 = pDdiTable->pfnSetRange;
    pDdiTable->pfnSetRange                               = layer::zesFrequencySetRange;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesFrequencyGetState;

    dditable.pfnGetThrottleTime                          = pDdiTable->pfnGetThrottleTime;
    pDdiTable->pfnGetThrottleTime                        = layer::zesFrequencyGetThrottleTime;

    dditable.pfnOcGetCapabilities                        = pDdiTable->pfnOcGetCapabilities;
    pDdiTable->pfnOcGetCapabilities                      = layer::zesFrequencyOcGetCapabilities;

    dditable.pfnOcGetConfig                              = pDdiTable->pfnOcGetConfig;
    pDdiTable->pfnOcGetConfig                            = layer::zesFrequencyOcGetConfig;

    dditable.pfnOcSetConfig                              = pDdiTable->pfnOcSetConfig;
    pDdiTable->pfnOcSetConfig                            = layer::zesFrequencyOcSetConfig;

    dditable.pfnOcGetIccMax                              = pDdiTable->pfnOcGetIccMax;
    pDdiTable->pfnOcGetIccMax                            = layer::zesFrequencyOcGetIccMax;

    dditable.pfnOcSetIccMax                              = pDdiTable->pfnOcSetIccMax;
    pDdiTable->pfnOcSetIccMax                            = layer::zesFrequencyOcSetIccMax;

    dditable.pfnOcGetTjMax                               = pDdiTable->pfnOcGetTjMax;
    pDdiTable->pfnOcGetTjMax                             = layer::zesFrequencyOcGetTjMax;

    dditable.pfnOcSetTjMax                               = pDdiTable->pfnOcSetTjMax;
    pDdiTable->pfnOcSetTjMax                             = layer::zesFrequencyOcSetTjMax;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Engine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_engine_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Engine;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesEngineGetProperties;

    dditable.pfnGetActivity                              = pDdiTable->pfnGetActivity;
    pDdiTable->pfnGetActivity                            = layer::zesEngineGetActivity;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Standby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_standby_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Standby;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesStandbyGetProperties;

    dditable.pfnGetMode                                  = pDdiTable->pfnGetMode;
    pDdiTable->pfnGetMode                                = layer::zesStandbyGetMode;

    dditable.pfnSetMode                                  = pDdiTable->pfnSetMode;
    pDdiTable->pfnSetMode                                = layer::zesStandbySetMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Firmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_firmware_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Firmware;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesFirmwareGetProperties;

    dditable.pfnGetChecksum                              = pDdiTable->pfnGetChecksum;
    pDdiTable->pfnGetChecksum                            = layer::zesFirmwareGetChecksum;

    dditable.pfnFlash                                    = pDdiTable->pfnFlash;
    pDdiTable->pfnFlash                                  = layer::zesFirmwareFlash;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Memory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_memory_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Memory;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesMemoryGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesMemoryGetState;

    dditable.pfnGetBandwidth                             = pDdiTable->pfnGetBandwidth;
    pDdiTable->pfnGetBandwidth                           = layer::zesMemoryGetBandwidth;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fabric_port_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.FabricPort;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesFabricPortGetProperties;

    dditable.pfnGetLinkType                              = pDdiTable->pfnGetLinkType;
    pDdiTable->pfnGetLinkType                            = layer::zesFabricPortGetLinkType;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesFabricPortGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesFabricPortSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesFabricPortGetState;

    dditable.pfnGetThroughput                            = pDdiTable->pfnGetThroughput;
    pDdiTable->pfnGetThroughput                          = layer::zesFabricPortGetThroughput;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Temperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_temperature_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Temperature;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesTemperatureGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesTemperatureGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesTemperatureSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesTemperatureGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Psu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_psu_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Psu;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesPsuGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesPsuGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fan_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Fan;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesFanGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesFanGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesFanSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesFanGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Led table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_led_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Led;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesLedGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesLedGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = layer::zesLedSetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Ras table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_ras_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Ras;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesRasGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesRasGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesRasSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesRasGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Diagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_diagnostics_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Diagnostics;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zesDiagnosticsGetProperties;

    dditable.pfnGetTests                                 = pDdiTable->pfnGetTests;
    pDdiTable->pfnGetTests                               = layer::zesDiagnosticsGetTests;

    dditable.pfnRunTests                                 = pDdiTable->pfnRunTests;
    pDdiTable->pfnRunTests                               = layer::zesDiagnosticsRunTests;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zesGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_event_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zesDdiTable.Event;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zesEventGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zesEventSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zesEventGetState;

    dditable.pfnListen                                   = pDdiTable->pfnListen;
    pDdiTable->pfnListen                                 = layer::zesEventListen;

    return result;
}

#if defined(__cplusplus)
};
#endif
