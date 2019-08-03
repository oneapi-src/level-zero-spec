/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_sysman.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#include "xet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the handle to access SMI features for a device
/// 
/// @details
///     - The returned handle is unique
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == phSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGet(
    xet_device_handle_t hDevice,                    ///< [in] Handle of the device
    xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
    xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
    )
{
    auto pfnGet = xet_lib::context.ddiTable.Sysman.pfnGet;
    if( nullptr == pfnGet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGet( hDevice, version, phSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out if specific resources are available on this device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pResources
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetResourceInfo(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the the array pResources
    xet_resid_info_t* pResources                    ///< [in] Pointer to an array that hold the ID of resources on input and
                                                    ///< will contain the availability on output
    )
{
    auto pfnGetResourceInfo = xet_lib::context.ddiTable.Sysman.pfnGetResourceInfo;
    if( nullptr == pfnGetResourceInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetResourceInfo( hSysman, count, pResources );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get list of resources available on this device of a given type
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pCount
///         + nullptr == pResources
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetResources(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    xet_resource_type_t type,                       ///< [in] Get a list of resources of given type. If this is
                                                    ///< ::XET_RESOURCE_TYPE_ANY, then all resources will be returned.
    uint32_t* pCount,                               ///< [in] Pointer to the number of elements in the array pResources.
                                                    ///< If count is 0 or pResources is nullptr, driver will update with the
                                                    ///< number of supported resources on this device.
                                                    ///< If count is non-zero and less than the number of supported resources,
                                                    ///< driver will update with the number of resources. No data is returned
                                                    ///< and an error is generated.
                                                    ///< If count is greater than or equal to the number of supported
                                                    ///< resources, all data is returned and count will be set to the number of
                                                    ///< returned resources.
    xet_resid_info_t* pResources                    ///< [in] Pointer to an array that will hold the ID of information about
                                                    ///< supported resources
    )
{
    auto pfnGetResources = xet_lib::context.ddiTable.Sysman.pfnGetResources;
    if( nullptr == pfnGetResources )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetResources( hSysman, type, pCount, pResources );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which resources properties are available on a given device
/// 
/// @details
///     - Access rights are specific to the device. Need to check separately on
///       each device.
///     - API support is based on the device class and doesn't need to be
///       checked for each device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetPropertyInfo(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pProperties
    xet_resprop_info_t* pProperties                 ///< [in] Pointer to an array of property info. Contains the property ID on
                                                    ///< input and the property info completed on output
    )
{
    auto pfnGetPropertyInfo = xet_lib::context.ddiTable.Sysman.pfnGetPropertyInfo;
    if( nullptr == pfnGetPropertyInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPropertyInfo( hSysman, count, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get resource property data
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pRequest
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_UNKNOWN
///         + One or more of the specified resource/properties had access errors. Check ::xet_resprop_request_t.status for each request.
xe_result_t __xecall
xetSysmanGetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_resprop_request_t* pRequest                 ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetProperties = xet_lib::context.ddiTable.Sysman.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set resource property data
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pRequest
///         + An invalid resource index was specified in one or more of the requests
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + One or more requested properties is not supported on this device
xe_result_t __xecall
xetSysmanSetProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_resprop_request_t* pRequest                 ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetProperties = xet_lib::context.ddiTable.Sysman.pfnSetProperties;
    if( nullptr == pfnSetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pConfig
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetRasConfig(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_ras_config_t* pConfig                       ///< [in] Pointer to storage for current RAS configuration
    )
{
    auto pfnGetRasConfig = xet_lib::context.ddiTable.Sysman.pfnGetRasConfig;
    if( nullptr == pfnGetRasConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetRasConfig( hSysman, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Setup (enable/disable) RAS
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEnabledLoc
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRasSetup(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    uint32_t enableLoc,                             ///< [in] Structural locations where RAS should be enabled (bitfield of
                                                    ///< ::xet_ras_error_loc_t)
    uint32_t disableLoc,                            ///< [in] Structural locations where RAS should be disabled (bitfield of
                                                    ///< ::xet_ras_error_loc_t)
    uint32_t* pEnabledLoc                           ///< [in] Structural locations where RAS is currently enabled after
                                                    ///< applying enableLoc and disableLoc (bitfield of ::xet_ras_error_loc_t)
    )
{
    auto pfnRasSetup = xet_lib::context.ddiTable.Sysman.pfnRasSetup;
    if( nullptr == pfnRasSetup )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRasSetup( hSysman, enableLoc, disableLoc, pEnabledLoc );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS errors that have occurred
/// 
/// @details
///     - Returned errors can be filtered by resource, type, location and
///       threshold.
///     - Clearing error counters will affect any subsequent calls to this
///       function from any application. Accumulated counter values are not
///       affected by this.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pFilter
///         + nullptr == pCount
///         + nullptr == pErrors
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_ARRAY_SIZE_TOO_SMALL
///         + The array doesn't have enough elements to store all the errors
xe_result_t __xecall
xetSysmanGetRasErrors(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    xet_ras_filter_t* pFilter,                      ///< [in] Filter for RAS errors to return
    xe_bool_t clear,                                ///< [in] Set to true to clear the underlying counters after they are
                                                    ///< returned
    uint32_t* pCount,                               ///< [in] Pointer to the number of elements in the array pErrors.
                                                    ///< If count is 0 or pErrors is nullptr, driver will update with the
                                                    ///< number of errors matching the specified filters. Counters are not cleared.
                                                    ///< If count is non-zero and less than the number of matching errors,
                                                    ///< driver will update with the number of errors matching the specified
                                                    ///< filters. No data is returned and counters are not cleared.
                                                    ///< If count is greater than or equal to the number of matching errors,
                                                    ///< all data is returned, counters are cleared if requested and count will
                                                    ///< be set to actual number of errors returned.
    xet_ras_error_t* pErrors                        ///< [in] Array of error data
    )
{
    auto pfnGetRasErrors = xet_lib::context.ddiTable.Sysman.pfnGetRasErrors;
    if( nullptr == pfnGetRasErrors )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetRasErrors( hSysman, pFilter, clear, pCount, pErrors );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which events are supported on a given device
/// 
/// @details
///     - Event support is the same for all devices with the same device ID.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pAccess
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanSupportedEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pAccess
    xet_event_support_t* pAccess                    ///< [in] Pointer to an array of event support requests
    )
{
    auto pfnSupportedEvents = xet_lib::context.ddiTable.Sysman.pfnSupportedEvents;
    if( nullptr == pfnSupportedEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSupportedEvents( hSysman, count, pAccess );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Register to receive events
/// 
/// @details
///     - This will only register the specified list of events. If other events
///       have been registered, notifications for them will continue.
///     - Set count to zero to receive notifications for all events.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRegisterEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be registered.
    xet_event_request_t* pEvents                    ///< [in] Events to register.
    )
{
    auto pfnRegisterEvents = xet_lib::context.ddiTable.Sysman.pfnRegisterEvents;
    if( nullptr == pfnRegisterEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRegisterEvents( hSysman, count, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Unregister events
/// 
/// @details
///     - This will only unregister the specified list of events. If other
///       events have been registered, notifications for them will continue.
///     - Set count to zero to no longer receive any notifications.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanUnregisterEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] Handle of the SMI object
    uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                    ///< be unregistered.
    xet_event_request_t* pEvents                    ///< [in] Events to unregister.
    )
{
    auto pfnUnregisterEvents = xet_lib::context.ddiTable.Sysman.pfnUnregisterEvents;
    if( nullptr == pfnUnregisterEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnUnregisterEvents( hSysman, count, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get events that have been triggered for a specific device or from all
///        registered devices
/// 
/// @details
///     - If events have occurred, they are returned and the corresponding event
///       status is cleared if the argument clear = true.
///     - If listening to events from multiple devices, it is recommended to
///       call this function with hSysman = nullptr, clear = false and timeout =
///       ::XET_EVENT_WAIT_INFINITE. Then call this function for each device
///       with clear = true and timeout = 0.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetEvents(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                    ///< device for which the application has registered to receive
                                                    ///< notifications.
    xe_bool_t clear,                                ///< [in] Clear the event status.
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                    ///< check status and return immediately. Set to ::XET_EVENT_WAIT_INFINITE
                                                    ///< to block until events arrive.
    uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                    ///< triggered.
    )
{
    auto pfnGetEvents = xet_lib::context.ddiTable.Sysman.pfnGetEvents;
    if( nullptr == pfnGetEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetEvents( hSysman, clear, timeout, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get diagnostic tests
/// 
/// @details
///     - Tests are returned in order of increasing index.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == ppTests
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetDiagnosticTests(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
    const xet_diag_test_list_t** ppTests            ///< [in] Returns a constant pointer to the list of diagnostic tests
    )
{
    auto pfnGetDiagnosticTests = xet_lib::context.ddiTable.Sysman.pfnGetDiagnosticTests;
    if( nullptr == pfnGetDiagnosticTests )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDiagnosticTests( hSysman, type, ppTests );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Run diagnostics
/// 
/// @details
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == pResult
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanRunDiagnosticTests(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    xet_diag_type_t type,                           ///< [in] Type of diagnostic to run
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    xet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
    )
{
    auto pfnRunDiagnosticTests = xet_lib::context.ddiTable.Sysman.pfnRunDiagnosticTests;
    if( nullptr == pfnRunDiagnosticTests )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRunDiagnosticTests( hSysman, type, start, end, pResult );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDeviceReset(
    xet_sysman_handle_t hSysman                     ///< [in] SMI handle for the device
    )
{
    auto pfnDeviceReset = xet_lib::context.ddiTable.Sysman.pfnDeviceReset;
    if( nullptr == pfnDeviceReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDeviceReset( hSysman );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    Sysman::Sysman( 
        sysman_handle_t handle,                         ///< [in] handle of SMI object
        DeviceGroup* pDeviceGroup                       ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDeviceGroup( pDeviceGroup )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the handle to access SMI features for a device
    /// 
    /// @details
    ///     - The returned handle is unique
    /// 
    /// @returns
    ///     - Sysman*: Handle for accessing SMI features
    /// 
    /// @throws result_t
    Sysman* __xecall
    Sysman::Get(
        Device* pDevice,                                ///< [in] Handle of the device
        version_t version                               ///< [in] SMI version that application was built with
        )
    {
        xet_sysman_handle_t hSysman;

        auto result = static_cast<result_t>( ::xetSysmanGet(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            static_cast<xet_sysman_version_t>( version ),
            &hSysman ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::Get" );

        Sysman* pSysman = nullptr;

        try
        {
            pSysman = new Sysman( reinterpret_cast<sysman_handle_t>( hSysman ), nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pSysman;
            pSysman = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::Get" );
        }

        return pSysman;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out if specific resources are available on this device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetResourceInfo(
        uint32_t count,                                 ///< [in] The number of entries in the the array pResources
        resid_info_t* pResources                        ///< [in] Pointer to an array that hold the ID of resources on input and
                                                        ///< will contain the availability on output
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetResourceInfo(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_resid_info_t*>( pResources ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetResourceInfo" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get list of resources available on this device of a given type
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetResources(
        resource_type_t type,                           ///< [in] Get a list of resources of given type. If this is
                                                        ///< ::XET_RESOURCE_TYPE_ANY, then all resources will be returned.
        uint32_t* pCount,                               ///< [in] Pointer to the number of elements in the array pResources.
                                                        ///< If count is 0 or pResources is nullptr, driver will update with the
                                                        ///< number of supported resources on this device.
                                                        ///< If count is non-zero and less than the number of supported resources,
                                                        ///< driver will update with the number of resources. No data is returned
                                                        ///< and an error is generated.
                                                        ///< If count is greater than or equal to the number of supported
                                                        ///< resources, all data is returned and count will be set to the number of
                                                        ///< returned resources.
        resid_info_t* pResources                        ///< [in] Pointer to an array that will hold the ID of information about
                                                        ///< supported resources
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetResources(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            static_cast<xet_resource_type_t>( type ),
            pCount,
            reinterpret_cast<xet_resid_info_t*>( pResources ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetResources" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which resources properties are available on a given device
    /// 
    /// @details
    ///     - Access rights are specific to the device. Need to check separately on
    ///       each device.
    ///     - API support is based on the device class and doesn't need to be
    ///       checked for each device.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetPropertyInfo(
        uint32_t count,                                 ///< [in] The number of entries in the array pProperties
        resprop_info_t* pProperties                     ///< [in] Pointer to an array of property info. Contains the property ID on
                                                        ///< input and the property info completed on output
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetPropertyInfo(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_resprop_info_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetPropertyInfo" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        resprop_request_t* pRequest                     ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_resprop_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        resprop_request_t* pRequest                     ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_resprop_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get RAS configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetRasConfig(
        ras_config_t* pConfig                           ///< [in] Pointer to storage for current RAS configuration
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetRasConfig(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_ras_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetRasConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Setup (enable/disable) RAS
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::RasSetup(
        uint32_t enableLoc,                             ///< [in] Structural locations where RAS should be enabled (bitfield of
                                                        ///< ::xet_ras_error_loc_t)
        uint32_t disableLoc,                            ///< [in] Structural locations where RAS should be disabled (bitfield of
                                                        ///< ::xet_ras_error_loc_t)
        uint32_t* pEnabledLoc                           ///< [in] Structural locations where RAS is currently enabled after
                                                        ///< applying enableLoc and disableLoc (bitfield of ::xet_ras_error_loc_t)
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanRasSetup(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            enableLoc,
            disableLoc,
            pEnabledLoc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::RasSetup" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get RAS errors that have occurred
    /// 
    /// @details
    ///     - Returned errors can be filtered by resource, type, location and
    ///       threshold.
    ///     - Clearing error counters will affect any subsequent calls to this
    ///       function from any application. Accumulated counter values are not
    ///       affected by this.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetRasErrors(
        ras_filter_t* pFilter,                          ///< [in] Filter for RAS errors to return
        xe::bool_t clear,                               ///< [in] Set to true to clear the underlying counters after they are
                                                        ///< returned
        uint32_t* pCount,                               ///< [in] Pointer to the number of elements in the array pErrors.
                                                        ///< If count is 0 or pErrors is nullptr, driver will update with the
                                                        ///< number of errors matching the specified filters. Counters are not cleared.
                                                        ///< If count is non-zero and less than the number of matching errors,
                                                        ///< driver will update with the number of errors matching the specified
                                                        ///< filters. No data is returned and counters are not cleared.
                                                        ///< If count is greater than or equal to the number of matching errors,
                                                        ///< all data is returned, counters are cleared if requested and count will
                                                        ///< be set to actual number of errors returned.
        ras_error_t* pErrors                            ///< [in] Array of error data
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetRasErrors(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_ras_filter_t*>( pFilter ),
            static_cast<xe_bool_t>( clear ),
            pCount,
            reinterpret_cast<xet_ras_error_t*>( pErrors ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetRasErrors" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which events are supported on a given device
    /// 
    /// @details
    ///     - Event support is the same for all devices with the same device ID.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SupportedEvents(
        uint32_t count,                                 ///< [in] The number of entries in the array pAccess
        event_support_t* pAccess                        ///< [in] Pointer to an array of event support requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSupportedEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_event_support_t*>( pAccess ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SupportedEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Register to receive events
    /// 
    /// @details
    ///     - This will only register the specified list of events. If other events
    ///       have been registered, notifications for them will continue.
    ///     - Set count to zero to receive notifications for all events.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::RegisterEvents(
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be registered.
        event_request_t* pEvents                        ///< [in] Events to register.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanRegisterEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_event_request_t*>( pEvents ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::RegisterEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Unregister events
    /// 
    /// @details
    ///     - This will only unregister the specified list of events. If other
    ///       events have been registered, notifications for them will continue.
    ///     - Set count to zero to no longer receive any notifications.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::UnregisterEvents(
        uint32_t count,                                 ///< [in] Number of entries in the array pEvents. If zero, all events will
                                                        ///< be unregistered.
        event_request_t* pEvents                        ///< [in] Events to unregister.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanUnregisterEvents(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_event_request_t*>( pEvents ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::UnregisterEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get events that have been triggered for a specific device or from all
    ///        registered devices
    /// 
    /// @details
    ///     - If events have occurred, they are returned and the corresponding event
    ///       status is cleared if the argument clear = true.
    ///     - If listening to events from multiple devices, it is recommended to
    ///       call this function with hSysman = nullptr, clear = false and timeout =
    ///       ::XET_EVENT_WAIT_INFINITE. Then call this function for each device
    ///       with clear = true and timeout = 0.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetEvents(
        Sysman* pSysman,                                ///< [in] SMI handle for a device. Set to nullptr to get events from any
                                                        ///< device for which the application has registered to receive
                                                        ///< notifications.
        xe::bool_t clear,                               ///< [in] Clear the event status.
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Zero will
                                                        ///< check status and return immediately. Set to ::XET_EVENT_WAIT_INFINITE
                                                        ///< to block until events arrive.
        uint32_t* pEvents                               ///< [in] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                        ///< triggered.
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetEvents(
            reinterpret_cast<xet_sysman_handle_t>( pSysman->getHandle() ),
            static_cast<xe_bool_t>( clear ),
            timeout,
            pEvents ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get diagnostic tests
    /// 
    /// @details
    ///     - Tests are returned in order of increasing index.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetDiagnosticTests(
        diag_type_t type,                               ///< [in] Type of diagnostic to run
        const diag_test_list_t** ppTests                ///< [in] Returns a constant pointer to the list of diagnostic tests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetDiagnosticTests(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            static_cast<xet_diag_type_t>( type ),
            reinterpret_cast<const xet_diag_test_list_t**>( ppTests ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetDiagnosticTests" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Run diagnostics
    /// 
    /// @details
    ///     - This function will block until the diagnostics have completed.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::RunDiagnosticTests(
        diag_type_t type,                               ///< [in] Type of diagnostic to run
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::XET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::XET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        diag_result_t* pResult                          ///< [in] The result of the diagnostics
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanRunDiagnosticTests(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            static_cast<xet_diag_type_t>( type ),
            start,
            end,
            reinterpret_cast<xet_diag_result_t*>( pResult ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::RunDiagnosticTests" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset device
    /// 
    /// @throws result_t
    void __xecall
    Sysman::DeviceReset(
        void
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDeviceReset(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::DeviceReset" );
    }

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::version_t::CURRENT:
            str = "Sysman::version_t::CURRENT";
            break;

        default:
            str = "Sysman::version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_type_t to std::string
    std::string to_string( const Sysman::resource_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::resource_type_t::DEV:
            str = "Sysman::resource_type_t::DEV";
            break;

        case Sysman::resource_type_t::PWR:
            str = "Sysman::resource_type_t::PWR";
            break;

        case Sysman::resource_type_t::FREQ:
            str = "Sysman::resource_type_t::FREQ";
            break;

        case Sysman::resource_type_t::UTIL:
            str = "Sysman::resource_type_t::UTIL";
            break;

        case Sysman::resource_type_t::MEM:
            str = "Sysman::resource_type_t::MEM";
            break;

        case Sysman::resource_type_t::LINK:
            str = "Sysman::resource_type_t::LINK";
            break;

        case Sysman::resource_type_t::TEMP:
            str = "Sysman::resource_type_t::TEMP";
            break;

        case Sysman::resource_type_t::STBY:
            str = "Sysman::resource_type_t::STBY";
            break;

        case Sysman::resource_type_t::FW:
            str = "Sysman::resource_type_t::FW";
            break;

        case Sysman::resource_type_t::PSU:
            str = "Sysman::resource_type_t::PSU";
            break;

        case Sysman::resource_type_t::FAN:
            str = "Sysman::resource_type_t::FAN";
            break;

        case Sysman::resource_type_t::LED:
            str = "Sysman::resource_type_t::LED";
            break;

        case Sysman::resource_type_t::ANY:
            str = "Sysman::resource_type_t::ANY";
            break;

        default:
            str = "Sysman::resource_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resid_t to std::string
    std::string to_string( const Sysman::resid_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::resid_t::DEV_INVENTORY:
            str = "Sysman::resid_t::DEV_INVENTORY";
            break;

        case Sysman::resid_t::PWR_TOTAL:
            str = "Sysman::resid_t::PWR_TOTAL";
            break;

        case Sysman::resid_t::FREQ_GPU:
            str = "Sysman::resid_t::FREQ_GPU";
            break;

        case Sysman::resid_t::FREQ_LOCAL_MEM:
            str = "Sysman::resid_t::FREQ_LOCAL_MEM";
            break;

        case Sysman::resid_t::UTIL_GPU:
            str = "Sysman::resid_t::UTIL_GPU";
            break;

        case Sysman::resid_t::UTIL_COMPUTE:
            str = "Sysman::resid_t::UTIL_COMPUTE";
            break;

        case Sysman::resid_t::UTIL_MEDIA:
            str = "Sysman::resid_t::UTIL_MEDIA";
            break;

        case Sysman::resid_t::UTIL_VIDEO_DECODE:
            str = "Sysman::resid_t::UTIL_VIDEO_DECODE";
            break;

        case Sysman::resid_t::UTIL_VIDEO_ENCODE:
            str = "Sysman::resid_t::UTIL_VIDEO_ENCODE";
            break;

        case Sysman::resid_t::MEM_LOCAL:
            str = "Sysman::resid_t::MEM_LOCAL";
            break;

        case Sysman::resid_t::LINK_PCIE:
            str = "Sysman::resid_t::LINK_PCIE";
            break;

        case Sysman::resid_t::LINK_CD_PORT1:
            str = "Sysman::resid_t::LINK_CD_PORT1";
            break;

        case Sysman::resid_t::LINK_CD_PORT2:
            str = "Sysman::resid_t::LINK_CD_PORT2";
            break;

        case Sysman::resid_t::LINK_CD_PORT3:
            str = "Sysman::resid_t::LINK_CD_PORT3";
            break;

        case Sysman::resid_t::LINK_CD_PORT4:
            str = "Sysman::resid_t::LINK_CD_PORT4";
            break;

        case Sysman::resid_t::LINK_CD_PORT5:
            str = "Sysman::resid_t::LINK_CD_PORT5";
            break;

        case Sysman::resid_t::LINK_CD_PORT6:
            str = "Sysman::resid_t::LINK_CD_PORT6";
            break;

        case Sysman::resid_t::LINK_CD_PORT7:
            str = "Sysman::resid_t::LINK_CD_PORT7";
            break;

        case Sysman::resid_t::LINK_CD_PORT8:
            str = "Sysman::resid_t::LINK_CD_PORT8";
            break;

        case Sysman::resid_t::LINK_CD_PORT9:
            str = "Sysman::resid_t::LINK_CD_PORT9";
            break;

        case Sysman::resid_t::LINK_CD_PORT10:
            str = "Sysman::resid_t::LINK_CD_PORT10";
            break;

        case Sysman::resid_t::LINK_CD_PORT11:
            str = "Sysman::resid_t::LINK_CD_PORT11";
            break;

        case Sysman::resid_t::LINK_CD_PORT12:
            str = "Sysman::resid_t::LINK_CD_PORT12";
            break;

        case Sysman::resid_t::LINK_CD_PORT13:
            str = "Sysman::resid_t::LINK_CD_PORT13";
            break;

        case Sysman::resid_t::LINK_CD_PORT14:
            str = "Sysman::resid_t::LINK_CD_PORT14";
            break;

        case Sysman::resid_t::LINK_CD_PORT15:
            str = "Sysman::resid_t::LINK_CD_PORT15";
            break;

        case Sysman::resid_t::LINK_CD_PORT16:
            str = "Sysman::resid_t::LINK_CD_PORT16";
            break;

        case Sysman::resid_t::TEMP_MAX:
            str = "Sysman::resid_t::TEMP_MAX";
            break;

        case Sysman::resid_t::TEMP_GPU:
            str = "Sysman::resid_t::TEMP_GPU";
            break;

        case Sysman::resid_t::TEMP_LOCAL_MEM:
            str = "Sysman::resid_t::TEMP_LOCAL_MEM";
            break;

        case Sysman::resid_t::STBY_GLOBAL:
            str = "Sysman::resid_t::STBY_GLOBAL";
            break;

        case Sysman::resid_t::STBY_COMPUTE:
            str = "Sysman::resid_t::STBY_COMPUTE";
            break;

        case Sysman::resid_t::STBY_MEDIA:
            str = "Sysman::resid_t::STBY_MEDIA";
            break;

        case Sysman::resid_t::FW_1:
            str = "Sysman::resid_t::FW_1";
            break;

        case Sysman::resid_t::FW_2:
            str = "Sysman::resid_t::FW_2";
            break;

        case Sysman::resid_t::FW_3:
            str = "Sysman::resid_t::FW_3";
            break;

        case Sysman::resid_t::FW_4:
            str = "Sysman::resid_t::FW_4";
            break;

        case Sysman::resid_t::FW_5:
            str = "Sysman::resid_t::FW_5";
            break;

        case Sysman::resid_t::FW_6:
            str = "Sysman::resid_t::FW_6";
            break;

        case Sysman::resid_t::FW_7:
            str = "Sysman::resid_t::FW_7";
            break;

        case Sysman::resid_t::FW_8:
            str = "Sysman::resid_t::FW_8";
            break;

        case Sysman::resid_t::FW_9:
            str = "Sysman::resid_t::FW_9";
            break;

        case Sysman::resid_t::FW_10:
            str = "Sysman::resid_t::FW_10";
            break;

        case Sysman::resid_t::FW_11:
            str = "Sysman::resid_t::FW_11";
            break;

        case Sysman::resid_t::FW_12:
            str = "Sysman::resid_t::FW_12";
            break;

        case Sysman::resid_t::FW_13:
            str = "Sysman::resid_t::FW_13";
            break;

        case Sysman::resid_t::FW_14:
            str = "Sysman::resid_t::FW_14";
            break;

        case Sysman::resid_t::FW_15:
            str = "Sysman::resid_t::FW_15";
            break;

        case Sysman::resid_t::FW_16:
            str = "Sysman::resid_t::FW_16";
            break;

        case Sysman::resid_t::FW_17:
            str = "Sysman::resid_t::FW_17";
            break;

        case Sysman::resid_t::FW_18:
            str = "Sysman::resid_t::FW_18";
            break;

        case Sysman::resid_t::FW_19:
            str = "Sysman::resid_t::FW_19";
            break;

        case Sysman::resid_t::FW_20:
            str = "Sysman::resid_t::FW_20";
            break;

        case Sysman::resid_t::PSU_MAIN:
            str = "Sysman::resid_t::PSU_MAIN";
            break;

        case Sysman::resid_t::PSU_AUX:
            str = "Sysman::resid_t::PSU_AUX";
            break;

        case Sysman::resid_t::PSU_1:
            str = "Sysman::resid_t::PSU_1";
            break;

        case Sysman::resid_t::PSU_2:
            str = "Sysman::resid_t::PSU_2";
            break;

        case Sysman::resid_t::FAN_MAIN:
            str = "Sysman::resid_t::FAN_MAIN";
            break;

        case Sysman::resid_t::FAN_1:
            str = "Sysman::resid_t::FAN_1";
            break;

        case Sysman::resid_t::FAN_2:
            str = "Sysman::resid_t::FAN_2";
            break;

        case Sysman::resid_t::FAN_3:
            str = "Sysman::resid_t::FAN_3";
            break;

        case Sysman::resid_t::LED_MAIN:
            str = "Sysman::resid_t::LED_MAIN";
            break;

        case Sysman::resid_t::LED_1:
            str = "Sysman::resid_t::LED_1";
            break;

        case Sysman::resid_t::LED_2:
            str = "Sysman::resid_t::LED_2";
            break;

        case Sysman::resid_t::LED_3:
            str = "Sysman::resid_t::LED_3";
            break;

        case Sysman::resid_t::ANY:
            str = "Sysman::resid_t::ANY";
            break;

        default:
            str = "Sysman::resid_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_t to std::string
    std::string to_string( const Sysman::resprop_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::resprop_t::DEV_SERIAL_NUMBER:
            str = "Sysman::resprop_t::DEV_SERIAL_NUMBER";
            break;

        case Sysman::resprop_t::DEV_BOARD_NUMBER:
            str = "Sysman::resprop_t::DEV_BOARD_NUMBER";
            break;

        case Sysman::resprop_t::DEV_BRAND:
            str = "Sysman::resprop_t::DEV_BRAND";
            break;

        case Sysman::resprop_t::DEV_MODEL:
            str = "Sysman::resprop_t::DEV_MODEL";
            break;

        case Sysman::resprop_t::DEV_DEVICEID:
            str = "Sysman::resprop_t::DEV_DEVICEID";
            break;

        case Sysman::resprop_t::DEV_VENDOR_NAME:
            str = "Sysman::resprop_t::DEV_VENDOR_NAME";
            break;

        case Sysman::resprop_t::DEV_DRIVER_VERSION:
            str = "Sysman::resprop_t::DEV_DRIVER_VERSION";
            break;

        case Sysman::resprop_t::DEV_BARS:
            str = "Sysman::resprop_t::DEV_BARS";
            break;

        case Sysman::resprop_t::DEV_UUID:
            str = "Sysman::resprop_t::DEV_UUID";
            break;

        case Sysman::resprop_t::PWR_MAX_LIMIT:
            str = "Sysman::resprop_t::PWR_MAX_LIMIT";
            break;

        case Sysman::resprop_t::PWR_ENERGY_COUNTER:
            str = "Sysman::resprop_t::PWR_ENERGY_COUNTER";
            break;

        case Sysman::resprop_t::PWR_SUSTAINED_LIMIT:
            str = "Sysman::resprop_t::PWR_SUSTAINED_LIMIT";
            break;

        case Sysman::resprop_t::PWR_BURST_LIMIT:
            str = "Sysman::resprop_t::PWR_BURST_LIMIT";
            break;

        case Sysman::resprop_t::PWR_PEAK_LIMIT:
            str = "Sysman::resprop_t::PWR_PEAK_LIMIT";
            break;

        case Sysman::resprop_t::FREQ_AVAIL_CLOCKS:
            str = "Sysman::resprop_t::FREQ_AVAIL_CLOCKS";
            break;

        case Sysman::resprop_t::FREQ_RANGE:
            str = "Sysman::resprop_t::FREQ_RANGE";
            break;

        case Sysman::resprop_t::FREQ_REQUESTED_FREQ:
            str = "Sysman::resprop_t::FREQ_REQUESTED_FREQ";
            break;

        case Sysman::resprop_t::FREQ_TDP_FREQ:
            str = "Sysman::resprop_t::FREQ_TDP_FREQ";
            break;

        case Sysman::resprop_t::FREQ_EFFICIENT_FREQ:
            str = "Sysman::resprop_t::FREQ_EFFICIENT_FREQ";
            break;

        case Sysman::resprop_t::FREQ_RESOLVED_FREQ:
            str = "Sysman::resprop_t::FREQ_RESOLVED_FREQ";
            break;

        case Sysman::resprop_t::FREQ_THROTTLE_REASONS:
            str = "Sysman::resprop_t::FREQ_THROTTLE_REASONS";
            break;

        case Sysman::resprop_t::FREQ_THROTTLE_TIME:
            str = "Sysman::resprop_t::FREQ_THROTTLE_TIME";
            break;

        case Sysman::resprop_t::UTIL_COUNTERS:
            str = "Sysman::resprop_t::UTIL_COUNTERS";
            break;

        case Sysman::resprop_t::MEM_TYPE:
            str = "Sysman::resprop_t::MEM_TYPE";
            break;

        case Sysman::resprop_t::MEM_UTILIZATION:
            str = "Sysman::resprop_t::MEM_UTILIZATION";
            break;

        case Sysman::resprop_t::MEM_BANDWIDTH:
            str = "Sysman::resprop_t::MEM_BANDWIDTH";
            break;

        case Sysman::resprop_t::LINK_TYPE:
            str = "Sysman::resprop_t::LINK_TYPE";
            break;

        case Sysman::resprop_t::LINK_BUS_ADDRESS:
            str = "Sysman::resprop_t::LINK_BUS_ADDRESS";
            break;

        case Sysman::resprop_t::LINK_PEER_DEVICE:
            str = "Sysman::resprop_t::LINK_PEER_DEVICE";
            break;

        case Sysman::resprop_t::LINK_AVAIL_SPEEDS:
            str = "Sysman::resprop_t::LINK_AVAIL_SPEEDS";
            break;

        case Sysman::resprop_t::LINK_MAX_PACKET_SIZE:
            str = "Sysman::resprop_t::LINK_MAX_PACKET_SIZE";
            break;

        case Sysman::resprop_t::LINK_STATE:
            str = "Sysman::resprop_t::LINK_STATE";
            break;

        case Sysman::resprop_t::LINK_BANDWIDTH:
            str = "Sysman::resprop_t::LINK_BANDWIDTH";
            break;

        case Sysman::resprop_t::LINK_SPEED:
            str = "Sysman::resprop_t::LINK_SPEED";
            break;

        case Sysman::resprop_t::LINK_SPEED_RANGE:
            str = "Sysman::resprop_t::LINK_SPEED_RANGE";
            break;

        case Sysman::resprop_t::TEMP_TEMPERATURE:
            str = "Sysman::resprop_t::TEMP_TEMPERATURE";
            break;

        case Sysman::resprop_t::STBY_PROMO_MODE:
            str = "Sysman::resprop_t::STBY_PROMO_MODE";
            break;

        case Sysman::resprop_t::FW_NAME:
            str = "Sysman::resprop_t::FW_NAME";
            break;

        case Sysman::resprop_t::FW_VERSION:
            str = "Sysman::resprop_t::FW_VERSION";
            break;

        case Sysman::resprop_t::FW_CHECK:
            str = "Sysman::resprop_t::FW_CHECK";
            break;

        case Sysman::resprop_t::FW_FLASH:
            str = "Sysman::resprop_t::FW_FLASH";
            break;

        case Sysman::resprop_t::PSU_AMP_LIMIT:
            str = "Sysman::resprop_t::PSU_AMP_LIMIT";
            break;

        case Sysman::resprop_t::PSU_VOLTAGE_STATUS:
            str = "Sysman::resprop_t::PSU_VOLTAGE_STATUS";
            break;

        case Sysman::resprop_t::PSU_FAN_FAILURE:
            str = "Sysman::resprop_t::PSU_FAN_FAILURE";
            break;

        case Sysman::resprop_t::PSU_TEMPERATURE:
            str = "Sysman::resprop_t::PSU_TEMPERATURE";
            break;

        case Sysman::resprop_t::PSU_AMPS:
            str = "Sysman::resprop_t::PSU_AMPS";
            break;

        case Sysman::resprop_t::FAN_MAX_RPM:
            str = "Sysman::resprop_t::FAN_MAX_RPM";
            break;

        case Sysman::resprop_t::FAN_MAX_TABLE_SIZE:
            str = "Sysman::resprop_t::FAN_MAX_TABLE_SIZE";
            break;

        case Sysman::resprop_t::FAN_SPEED_RPM:
            str = "Sysman::resprop_t::FAN_SPEED_RPM";
            break;

        case Sysman::resprop_t::FAN_SPEED_PERCENT:
            str = "Sysman::resprop_t::FAN_SPEED_PERCENT";
            break;

        case Sysman::resprop_t::FAN_MODE:
            str = "Sysman::resprop_t::FAN_MODE";
            break;

        case Sysman::resprop_t::FAN_FIXED_SPEED:
            str = "Sysman::resprop_t::FAN_FIXED_SPEED";
            break;

        case Sysman::resprop_t::FAN_SPEED_TABLE:
            str = "Sysman::resprop_t::FAN_SPEED_TABLE";
            break;

        case Sysman::resprop_t::LED_RGB_CAP:
            str = "Sysman::resprop_t::LED_RGB_CAP";
            break;

        case Sysman::resprop_t::LED_STATE:
            str = "Sysman::resprop_t::LED_STATE";
            break;

        default:
            str = "Sysman::resprop_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_type_t to std::string
    std::string to_string( const Sysman::pci_bar_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::pci_bar_type_t::CONFIG:
            str = "Sysman::pci_bar_type_t::CONFIG";
            break;

        case Sysman::pci_bar_type_t::MMIO:
            str = "Sysman::pci_bar_type_t::MMIO";
            break;

        case Sysman::pci_bar_type_t::VRAM:
            str = "Sysman::pci_bar_type_t::VRAM";
            break;

        case Sysman::pci_bar_type_t::ROM:
            str = "Sysman::pci_bar_type_t::ROM";
            break;

        case Sysman::pci_bar_type_t::VGA_IO:
            str = "Sysman::pci_bar_type_t::VGA_IO";
            break;

        case Sysman::pci_bar_type_t::VGA_MEM:
            str = "Sysman::pci_bar_type_t::VGA_MEM";
            break;

        case Sysman::pci_bar_type_t::INDIRECT_IO:
            str = "Sysman::pci_bar_type_t::INDIRECT_IO";
            break;

        case Sysman::pci_bar_type_t::INDIRECT_MEM:
            str = "Sysman::pci_bar_type_t::INDIRECT_MEM";
            break;

        case Sysman::pci_bar_type_t::OTHER:
            str = "Sysman::pci_bar_type_t::OTHER";
            break;

        default:
            str = "Sysman::pci_bar_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_throttle_reasons_t to std::string
    std::string to_string( const Sysman::freq_throttle_reasons_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::freq_throttle_reasons_t::AVE_PWR_CAP) & bits )
            str += "AVE_PWR_CAP | ";
        
        if( static_cast<uint32_t>(Sysman::freq_throttle_reasons_t::BURST_PWR_CAP) & bits )
            str += "BURST_PWR_CAP | ";
        
        if( static_cast<uint32_t>(Sysman::freq_throttle_reasons_t::CURRENT_LIMIT) & bits )
            str += "CURRENT_LIMIT | ";
        
        if( static_cast<uint32_t>(Sysman::freq_throttle_reasons_t::THERMAL_LIMIT) & bits )
            str += "THERMAL_LIMIT | ";
        
        if( static_cast<uint32_t>(Sysman::freq_throttle_reasons_t::PSU_ALERT) & bits )
            str += "PSU_ALERT | ";
        
        if( static_cast<uint32_t>(Sysman::freq_throttle_reasons_t::SW_RANGE) & bits )
            str += "SW_RANGE | ";
        
        if( static_cast<uint32_t>(Sysman::freq_throttle_reasons_t::HW_RANGE) & bits )
            str += "HW_RANGE | ";

        return ( str.size() > 3 ) 
            ? "Sysman::freq_throttle_reasons_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::freq_throttle_reasons_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_type_t to std::string
    std::string to_string( const Sysman::mem_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::mem_type_t::HBM:
            str = "Sysman::mem_type_t::HBM";
            break;

        case Sysman::mem_type_t::DDR:
            str = "Sysman::mem_type_t::DDR";
            break;

        case Sysman::mem_type_t::SRAM:
            str = "Sysman::mem_type_t::SRAM";
            break;

        case Sysman::mem_type_t::L1:
            str = "Sysman::mem_type_t::L1";
            break;

        case Sysman::mem_type_t::L3:
            str = "Sysman::mem_type_t::L3";
            break;

        case Sysman::mem_type_t::GRF:
            str = "Sysman::mem_type_t::GRF";
            break;

        case Sysman::mem_type_t::SLM:
            str = "Sysman::mem_type_t::SLM";
            break;

        default:
            str = "Sysman::mem_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_type_t to std::string
    std::string to_string( const Sysman::link_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::link_type_t::PCI:
            str = "Sysman::link_type_t::PCI";
            break;

        case Sysman::link_type_t::CD_PORT:
            str = "Sysman::link_type_t::CD_PORT";
            break;

        default:
            str = "Sysman::link_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::stby_promo_mode_t to std::string
    std::string to_string( const Sysman::stby_promo_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::stby_promo_mode_t::IMMEDIATE:
            str = "Sysman::stby_promo_mode_t::IMMEDIATE";
            break;

        case Sysman::stby_promo_mode_t::DEFAULT:
            str = "Sysman::stby_promo_mode_t::DEFAULT";
            break;

        case Sysman::stby_promo_mode_t::NEVER:
            str = "Sysman::stby_promo_mode_t::NEVER";
            break;

        default:
            str = "Sysman::stby_promo_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_voltage_status_t to std::string
    std::string to_string( const Sysman::psu_voltage_status_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::psu_voltage_status_t::NORMAL:
            str = "Sysman::psu_voltage_status_t::NORMAL";
            break;

        case Sysman::psu_voltage_status_t::OVER:
            str = "Sysman::psu_voltage_status_t::OVER";
            break;

        case Sysman::psu_voltage_status_t::UNDER:
            str = "Sysman::psu_voltage_status_t::UNDER";
            break;

        default:
            str = "Sysman::psu_voltage_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_speed_mode_t to std::string
    std::string to_string( const Sysman::fan_speed_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::fan_speed_mode_t::FIXED:
            str = "Sysman::fan_speed_mode_t::FIXED";
            break;

        case Sysman::fan_speed_mode_t::TABLE:
            str = "Sysman::fan_speed_mode_t::TABLE";
            break;

        default:
            str = "Sysman::fan_speed_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_speed_units_t to std::string
    std::string to_string( const Sysman::fan_speed_units_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::fan_speed_units_t::RPM:
            str = "Sysman::fan_speed_units_t::RPM";
            break;

        case Sysman::fan_speed_units_t::PERCENT:
            str = "Sysman::fan_speed_units_t::PERCENT";
            break;

        default:
            str = "Sysman::fan_speed_units_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::prop_support_t to std::string
    std::string to_string( const Sysman::prop_support_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::prop_support_t::API) & bits )
            str += "API | ";
        
        if( static_cast<uint32_t>(Sysman::prop_support_t::DEVICE_CLASS) & bits )
            str += "DEVICE_CLASS | ";
        
        if( static_cast<uint32_t>(Sysman::prop_support_t::DEVICE) & bits )
            str += "DEVICE | ";

        return ( str.size() > 3 ) 
            ? "Sysman::prop_support_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::prop_support_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::prop_access_t to std::string
    std::string to_string( const Sysman::prop_access_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NO_PERMISSIONS   ";
        
        if( static_cast<uint32_t>(Sysman::prop_access_t::READ_PERMISSIONS) & bits )
            str += "READ_PERMISSIONS | ";
        
        if( static_cast<uint32_t>(Sysman::prop_access_t::WRITE_PERMISSIONS) & bits )
            str += "WRITE_PERMISSIONS | ";

        return ( str.size() > 3 ) 
            ? "Sysman::prop_access_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::prop_access_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_type_t to std::string
    std::string to_string( const Sysman::ras_error_type_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::FATAL) & bits )
            str += "FATAL | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::NON_FATAL) & bits )
            str += "NON_FATAL | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::CORRECTABLE) & bits )
            str += "CORRECTABLE | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::UNCORRECTABLE) & bits )
            str += "UNCORRECTABLE | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::PARITY) & bits )
            str += "PARITY | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::SINGLE_BIT) & bits )
            str += "SINGLE_BIT | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::DOUBLE_BIT) & bits )
            str += "DOUBLE_BIT | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::REPLAY) & bits )
            str += "REPLAY | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::RESET) & bits )
            str += "RESET | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_type_t::ALL) & bits )
            str += "ALL | ";

        return ( str.size() > 3 ) 
            ? "Sysman::ras_error_type_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::ras_error_type_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_loc_t to std::string
    std::string to_string( const Sysman::ras_error_loc_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::MAIN_MEM) & bits )
            str += "MAIN_MEM | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::L3_CACHE) & bits )
            str += "L3_CACHE | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::SAMPLER_SRAM) & bits )
            str += "SAMPLER_SRAM | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::GUC_SRAM) & bits )
            str += "GUC_SRAM | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::INST_CACHE) & bits )
            str += "INST_CACHE | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::GRF) & bits )
            str += "GRF | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::SLM) & bits )
            str += "SLM | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::MESSAGING) & bits )
            str += "MESSAGING | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::SECURITY) & bits )
            str += "SECURITY | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::DISPLAY) & bits )
            str += "DISPLAY | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::SOC) & bits )
            str += "SOC | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::GPU_HANG) & bits )
            str += "GPU_HANG | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::PCI) & bits )
            str += "PCI | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::PCI_ROUTING) & bits )
            str += "PCI_ROUTING | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::P2P_LINK) & bits )
            str += "P2P_LINK | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::ALL) & bits )
            str += "ALL | ";

        return ( str.size() > 3 ) 
            ? "Sysman::ras_error_loc_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::ras_error_loc_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_data_type_t to std::string
    std::string to_string( const Sysman::ras_data_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::ras_data_type_t::NONE:
            str = "Sysman::ras_data_type_t::NONE";
            break;

        case Sysman::ras_data_type_t::OCCURRED:
            str = "Sysman::ras_data_type_t::OCCURRED";
            break;

        case Sysman::ras_data_type_t::COUNTER:
            str = "Sysman::ras_data_type_t::COUNTER";
            break;

        default:
            str = "Sysman::ras_data_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::event_type_t::FREQ_THROTTLED:
            str = "Sysman::event_type_t::FREQ_THROTTLED";
            break;

        case Sysman::event_type_t::RAS_ERRORS:
            str = "Sysman::event_type_t::RAS_ERRORS";
            break;

        case Sysman::event_type_t::COUNT:
            str = "Sysman::event_type_t::COUNT";
            break;

        default:
            str = "Sysman::event_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_type_t to std::string
    std::string to_string( const Sysman::diag_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::diag_type_t::SCAN:
            str = "Sysman::diag_type_t::SCAN";
            break;

        case Sysman::diag_type_t::ARRAY:
            str = "Sysman::diag_type_t::ARRAY";
            break;

        default:
            str = "Sysman::diag_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_result_t to std::string
    std::string to_string( const Sysman::diag_result_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::diag_result_t::NO_ERRORS:
            str = "Sysman::diag_result_t::NO_ERRORS";
            break;

        case Sysman::diag_result_t::ABORT:
            str = "Sysman::diag_result_t::ABORT";
            break;

        case Sysman::diag_result_t::FAIL_CANT_REPAIR:
            str = "Sysman::diag_result_t::FAIL_CANT_REPAIR";
            break;

        case Sysman::diag_result_t::REBOOT_FOR_REPAIR:
            str = "Sysman::diag_result_t::REBOOT_FOR_REPAIR";
            break;

        default:
            str = "Sysman::diag_result_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_info_t to std::string
    std::string to_string( const Sysman::pci_bar_info_t val )
    {
        std::string str;
        
        str += "Sysman::pci_bar_info_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::pci_bar_info_t::base : ";
        str += std::to_string(val.base);
        str += "\n";
        
        str += "Sysman::pci_bar_info_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_serial_number_t to std::string
    std::string to_string( const Sysman::resprop_dev_serial_number_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_serial_number_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_board_number_t to std::string
    std::string to_string( const Sysman::resprop_dev_board_number_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_board_number_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_brand_t to std::string
    std::string to_string( const Sysman::resprop_dev_brand_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_brand_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_model_t to std::string
    std::string to_string( const Sysman::resprop_dev_model_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_model_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_deviceid_t to std::string
    std::string to_string( const Sysman::resprop_dev_deviceid_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_deviceid_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_vendor_name_t to std::string
    std::string to_string( const Sysman::resprop_dev_vendor_name_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_vendor_name_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_driver_version_t to std::string
    std::string to_string( const Sysman::resprop_dev_driver_version_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_driver_version_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_bars_t to std::string
    std::string to_string( const Sysman::resprop_dev_bars_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_bars_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "Sysman::resprop_dev_bars_t::pBars : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pBars);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_dev_uuid_t to std::string
    std::string to_string( const Sysman::resprop_dev_uuid_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_dev_uuid_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_max_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_max_limit_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_pwr_max_limit_t::limit : ";
        str += std::to_string(val.limit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_energy_counter_t to std::string
    std::string to_string( const Sysman::resprop_pwr_energy_counter_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_pwr_energy_counter_t::energy : ";
        str += std::to_string(val.energy);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_sustained_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_sustained_limit_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_pwr_sustained_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Sysman::resprop_pwr_sustained_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";
        
        str += "Sysman::resprop_pwr_sustained_limit_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_burst_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_burst_limit_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_pwr_burst_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Sysman::resprop_pwr_burst_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_pwr_peak_limit_t to std::string
    std::string to_string( const Sysman::resprop_pwr_peak_limit_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_pwr_peak_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_avail_clocks_t to std::string
    std::string to_string( const Sysman::resprop_freq_avail_clocks_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_avail_clocks_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "Sysman::resprop_freq_avail_clocks_t::max : ";
        str += std::to_string(val.max);
        str += "\n";
        
        str += "Sysman::resprop_freq_avail_clocks_t::step : ";
        str += std::to_string(val.step);
        str += "\n";
        
        str += "Sysman::resprop_freq_avail_clocks_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "Sysman::resprop_freq_avail_clocks_t::pClocks : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pClocks);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_range_t to std::string
    std::string to_string( const Sysman::resprop_freq_range_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_range_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "Sysman::resprop_freq_range_t::max : ";
        str += std::to_string(val.max);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_requested_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_requested_freq_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_requested_freq_t::freqRequest : ";
        str += std::to_string(val.freqRequest);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_tdp_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_tdp_freq_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_tdp_freq_t::freqTdp : ";
        str += std::to_string(val.freqTdp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_efficient_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_efficient_freq_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_efficient_freq_t::freqEfficient : ";
        str += std::to_string(val.freqEfficient);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_resolved_freq_t to std::string
    std::string to_string( const Sysman::resprop_freq_resolved_freq_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_resolved_freq_t::freqResolved : ";
        str += std::to_string(val.freqResolved);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_throttle_reasons_t to std::string
    std::string to_string( const Sysman::resprop_freq_throttle_reasons_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_throttle_reasons_t::throttleReasons : ";
        str += std::to_string(val.throttleReasons);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_freq_throttle_time_t to std::string
    std::string to_string( const Sysman::resprop_freq_throttle_time_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_freq_throttle_time_t::throttleTime : ";
        str += std::to_string(val.throttleTime);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_util_counters_t to std::string
    std::string to_string( const Sysman::resprop_util_counters_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_util_counters_t::activeCounter : ";
        str += std::to_string(val.activeCounter);
        str += "\n";
        
        str += "Sysman::resprop_util_counters_t::idleCounter : ";
        str += std::to_string(val.idleCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_mem_type_t to std::string
    std::string to_string( const Sysman::resprop_mem_type_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_mem_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_mem_utilization_t to std::string
    std::string to_string( const Sysman::resprop_mem_utilization_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_mem_utilization_t::total : ";
        str += std::to_string(val.total);
        str += "\n";
        
        str += "Sysman::resprop_mem_utilization_t::stolen : ";
        str += std::to_string(val.stolen);
        str += "\n";
        
        str += "Sysman::resprop_mem_utilization_t::bad : ";
        str += std::to_string(val.bad);
        str += "\n";
        
        str += "Sysman::resprop_mem_utilization_t::allocated : ";
        str += std::to_string(val.allocated);
        str += "\n";
        
        str += "Sysman::resprop_mem_utilization_t::unallocated : ";
        str += std::to_string(val.unallocated);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_mem_bandwidth_t to std::string
    std::string to_string( const Sysman::resprop_mem_bandwidth_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_mem_bandwidth_t::readCounter : ";
        str += std::to_string(val.readCounter);
        str += "\n";
        
        str += "Sysman::resprop_mem_bandwidth_t::writeCounter : ";
        str += std::to_string(val.writeCounter);
        str += "\n";
        
        str += "Sysman::resprop_mem_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_speed_t to std::string
    std::string to_string( const Sysman::link_speed_t val )
    {
        std::string str;
        
        str += "Sysman::link_speed_t::numLanes : ";
        str += std::to_string(val.numLanes);
        str += "\n";
        
        str += "Sysman::link_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "Sysman::link_speed_t::bandwidth : ";
        str += std::to_string(val.bandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_type_t to std::string
    std::string to_string( const Sysman::resprop_link_type_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_bus_address_t to std::string
    std::string to_string( const Sysman::resprop_link_bus_address_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_bus_address_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_peer_device_t to std::string
    std::string to_string( const Sysman::resprop_link_peer_device_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_peer_device_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_avail_speeds_t to std::string
    std::string to_string( const Sysman::resprop_link_avail_speeds_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_avail_speeds_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "Sysman::resprop_link_avail_speeds_t::pList : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pList);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_state_t to std::string
    std::string to_string( const Sysman::resprop_link_state_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_state_t::enable : ";
        str += std::to_string(val.enable);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_max_packet_size_t to std::string
    std::string to_string( const Sysman::resprop_link_max_packet_size_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_max_packet_size_t::maxPacketSize : ";
        str += std::to_string(val.maxPacketSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_bandwidth_t to std::string
    std::string to_string( const Sysman::resprop_link_bandwidth_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_bandwidth_t::recvCounter : ";
        str += std::to_string(val.recvCounter);
        str += "\n";
        
        str += "Sysman::resprop_link_bandwidth_t::sendCounter : ";
        str += std::to_string(val.sendCounter);
        str += "\n";
        
        str += "Sysman::resprop_link_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_speed_t to std::string
    std::string to_string( const Sysman::resprop_link_speed_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_speed_t::pSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pSpeed);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_link_speed_range_t to std::string
    std::string to_string( const Sysman::resprop_link_speed_range_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_link_speed_range_t::pMinSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pMinSpeed);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::resprop_link_speed_range_t::pMaxSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pMaxSpeed);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_temp_temperature_t to std::string
    std::string to_string( const Sysman::resprop_temp_temperature_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_temp_temperature_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_stby_promo_mode_t to std::string
    std::string to_string( const Sysman::resprop_stby_promo_mode_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_stby_promo_mode_t::mode : ";
        str += to_string(val.mode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_name_t to std::string
    std::string to_string( const Sysman::resprop_fw_name_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fw_name_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_version_t to std::string
    std::string to_string( const Sysman::resprop_fw_version_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fw_version_t::str : ";
        {
            std::string tmp;
            for( auto& entry : val.str )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_check_t to std::string
    std::string to_string( const Sysman::resprop_fw_check_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fw_check_t::checksum : ";
        str += std::to_string(val.checksum);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fw_flash_t to std::string
    std::string to_string( const Sysman::resprop_fw_flash_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fw_flash_t::pImage : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pImage);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::resprop_fw_flash_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_amp_limit_t to std::string
    std::string to_string( const Sysman::resprop_psu_amp_limit_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_psu_amp_limit_t::limit : ";
        str += std::to_string(val.limit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_voltage_status_t to std::string
    std::string to_string( const Sysman::resprop_psu_voltage_status_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_psu_voltage_status_t::status : ";
        str += to_string(val.status);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_fan_failure_t to std::string
    std::string to_string( const Sysman::resprop_psu_fan_failure_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_psu_fan_failure_t::status : ";
        str += std::to_string(val.status);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_temperature_t to std::string
    std::string to_string( const Sysman::resprop_psu_temperature_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_psu_temperature_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_psu_amps_t to std::string
    std::string to_string( const Sysman::resprop_psu_amps_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_psu_amps_t::current : ";
        str += std::to_string(val.current);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_temp_speed_t to std::string
    std::string to_string( const Sysman::fan_temp_speed_t val )
    {
        std::string str;
        
        str += "Sysman::fan_temp_speed_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "Sysman::fan_temp_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "Sysman::fan_temp_speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_max_rpm_t to std::string
    std::string to_string( const Sysman::resprop_fan_max_rpm_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fan_max_rpm_t::maxSpeed : ";
        str += std::to_string(val.maxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_max_table_size_t to std::string
    std::string to_string( const Sysman::resprop_fan_max_table_size_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fan_max_table_size_t::maxPoints : ";
        str += std::to_string(val.maxPoints);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_speed_rpm_t to std::string
    std::string to_string( const Sysman::resprop_fan_speed_rpm_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fan_speed_rpm_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_speed_percent_t to std::string
    std::string to_string( const Sysman::resprop_fan_speed_percent_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fan_speed_percent_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_mode_t to std::string
    std::string to_string( const Sysman::resprop_fan_mode_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fan_mode_t::mode : ";
        str += to_string(val.mode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_fixed_speed_t to std::string
    std::string to_string( const Sysman::resprop_fan_fixed_speed_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fan_fixed_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "Sysman::resprop_fan_fixed_speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_fan_speed_table_t to std::string
    std::string to_string( const Sysman::resprop_fan_speed_table_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_fan_speed_table_t::pCount : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pCount);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::resprop_fan_speed_table_t::points : ";
        {
            std::string tmp;
            for( auto& entry : val.points )
            {
                tmp += to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_led_rgb_cap_t to std::string
    std::string to_string( const Sysman::resprop_led_rgb_cap_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_led_rgb_cap_t::haveRGB : ";
        str += std::to_string(val.haveRGB);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_led_state_t to std::string
    std::string to_string( const Sysman::resprop_led_state_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_led_state_t::isOn : ";
        str += std::to_string(val.isOn);
        str += "\n";
        
        str += "Sysman::resprop_led_state_t::red : ";
        str += std::to_string(val.red);
        str += "\n";
        
        str += "Sysman::resprop_led_state_t::green : ";
        str += std::to_string(val.green);
        str += "\n";
        
        str += "Sysman::resprop_led_state_t::blue : ";
        str += std::to_string(val.blue);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resid_info_t to std::string
    std::string to_string( const Sysman::resid_info_t val )
    {
        std::string str;
        
        str += "Sysman::resid_info_t::id : ";
        str += to_string(val.id);
        str += "\n";
        
        str += "Sysman::resid_info_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::resid_info_t::pName : ";
        str += val.pName;
        str += "\n";
        
        str += "Sysman::resid_info_t::pDesc : ";
        str += val.pDesc;
        str += "\n";
        
        str += "Sysman::resid_info_t::available : ";
        str += std::to_string(val.available);
        str += "\n";
        
        str += "Sysman::resid_info_t::propsOnSubdevices : ";
        str += std::to_string(val.propsOnSubdevices);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_info_t to std::string
    std::string to_string( const Sysman::resprop_info_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_info_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::resprop_info_t::resourceType : ";
        str += to_string(val.resourceType);
        str += "\n";
        
        str += "Sysman::resprop_info_t::pName : ";
        str += val.pName;
        str += "\n";
        
        str += "Sysman::resprop_info_t::pDesc : ";
        str += val.pDesc;
        str += "\n";
        
        str += "Sysman::resprop_info_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::resprop_info_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::resprop_info_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::resprop_info_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resprop_request_t to std::string
    std::string to_string( const Sysman::resprop_request_t val )
    {
        std::string str;
        
        str += "Sysman::resprop_request_t::resource : ";
        str += to_string(val.resource);
        str += "\n";
        
        str += "Sysman::resprop_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::resprop_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::resprop_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Sysman::resprop_request_t::status : ";
        str += to_string(val.status);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_config_t to std::string
    std::string to_string( const Sysman::ras_config_t val )
    {
        std::string str;
        
        str += "Sysman::ras_config_t::numRas : ";
        str += std::to_string(val.numRas);
        str += "\n";
        
        str += "Sysman::ras_config_t::rasTypes : ";
        str += std::to_string(val.rasTypes);
        str += "\n";
        
        str += "Sysman::ras_config_t::rasLocations : ";
        str += std::to_string(val.rasLocations);
        str += "\n";
        
        str += "Sysman::ras_config_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_filter_t to std::string
    std::string to_string( const Sysman::ras_filter_t val )
    {
        std::string str;
        
        str += "Sysman::ras_filter_t::resourceId : ";
        str += to_string(val.resourceId);
        str += "\n";
        
        str += "Sysman::ras_filter_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Sysman::ras_filter_t::location : ";
        str += std::to_string(val.location);
        str += "\n";
        
        str += "Sysman::ras_filter_t::threshold : ";
        str += std::to_string(val.threshold);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::ras_error_t to std::string
    std::string to_string( const Sysman::ras_error_t val )
    {
        std::string str;
        
        str += "Sysman::ras_error_t::pName : ";
        str += val.pName;
        str += "\n";
        
        str += "Sysman::ras_error_t::pDesc : ";
        str += val.pDesc;
        str += "\n";
        
        str += "Sysman::ras_error_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Sysman::ras_error_t::loc : ";
        str += std::to_string(val.loc);
        str += "\n";
        
        str += "Sysman::ras_error_t::dataType : ";
        str += to_string(val.dataType);
        str += "\n";
        
        str += "Sysman::ras_error_t::data : ";
        str += std::to_string(val.data);
        str += "\n";
        
        str += "Sysman::ras_error_t::accumulated : ";
        str += std::to_string(val.accumulated);
        str += "\n";
        
        str += "Sysman::ras_error_t::resourceId : ";
        str += to_string(val.resourceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_support_t to std::string
    std::string to_string( const Sysman::event_support_t val )
    {
        std::string str;
        
        str += "Sysman::event_support_t::event : ";
        str += to_string(val.event);
        str += "\n";
        
        str += "Sysman::event_support_t::supported : ";
        str += std::to_string(val.supported);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_request_t to std::string
    std::string to_string( const Sysman::event_request_t val )
    {
        std::string str;
        
        str += "Sysman::event_request_t::event : ";
        str += to_string(val.event);
        str += "\n";
        
        str += "Sysman::event_request_t::resourceId : ";
        str += to_string(val.resourceId);
        str += "\n";
        
        str += "Sysman::event_request_t::threshold : ";
        str += std::to_string(val.threshold);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_test_t to std::string
    std::string to_string( const Sysman::diag_test_t val )
    {
        std::string str;
        
        str += "Sysman::diag_test_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::diag_test_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::diag_test_list_t to std::string
    std::string to_string( const Sysman::diag_test_list_t val )
    {
        std::string str;
        
        str += "Sysman::diag_test_list_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::diag_test_list_t::count : ";
        str += std::to_string(val.count);
        str += "\n";
        
        str += "Sysman::diag_test_list_t::pTests : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pTests);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

} // namespace xet
