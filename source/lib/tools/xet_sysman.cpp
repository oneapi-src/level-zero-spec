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
/// @brief Creates a handle to access SMI features for a device
/// 
/// @details
///     - Initializes internal structures to support SMI features.
///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is specified, no
///       access right checks are made during initialization. The check is done
///       in functions that attempt to control a device.
///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is not specified, any
///       function attempting to control a device will return
///       ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS.
///     - Multiple SMI handles can be created for the same device and concurrent
///       access through each handle to access underlying hardware resources is
///       supported.
/// 
/// @remarks
///   _Analogues_
///     - **nvmlInit**
///     - **rsmi_init**
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
xetSysmanCreate(
    xet_device_handle_t hDevice,                    ///< [in] Handle of the device
    xet_sysman_version_t version,                   ///< [in] SMI version that application was built with
    uint32_t flags,                                 ///< [in] Bitfield of ::xet_sysman_init_flags_t
    xet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing SMI features
    )
{
    auto pfnCreate = xet_lib::context.ddiTable.Sysman.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDevice, version, flags, phSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a SMI handle
/// 
/// @details
///     - Only once all SMI handles to a device have been destroyed will
///       internal data structures be freed from the application memory.
/// 
/// @remarks
///   _Analogues_
///     - **nvmlShutdown**
///     - **rsmi_shut_down**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanDestroy(
    xet_sysman_handle_t hSysman                     ///< [in][release] SMI handle to destroy
    )
{
    auto pfnDestroy = xet_lib::context.ddiTable.Sysman.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get human-readable name for an accelerator asset
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hSysman
///         + nullptr == ppName
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetAccelAssetName(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle
    xet_accel_asset_t type,                         ///< [in] The type of accelerator asset
    const char** ppName                             ///< [in] Pointer to the asset name
    )
{
    auto pfnGetAccelAssetName = xet_lib::context.ddiTable.Sysman.pfnGetAccelAssetName;
    if( nullptr == pfnGetAccelAssetName )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAccelAssetName( hSysman, type, ppName );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get SMI information for a device
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
///         + nullptr == pInfo
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanGetInfo(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of a device
    xet_sysman_info_t* pInfo                        ///< [in] Returned information
    )
{
    auto pfnGetInfo = xet_lib::context.ddiTable.Sysman.pfnGetInfo;
    if( nullptr == pfnGetInfo )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetInfo( hSysman, pInfo );
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
/// @brief Find out which device properties are available on a given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableDeviceProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_device_prop_capability_t* pCap              ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableDeviceProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableDeviceProperties;
    if( nullptr == pfnAvailableDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableDeviceProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get device property data
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
///         + One or more requested properties is not supported on this device
xe_result_t __xecall
xetSysmanGetDeviceProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetDeviceProperties = xet_lib::context.ddiTable.Sysman.pfnGetDeviceProperties;
    if( nullptr == pfnGetDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetDeviceProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set device property data
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
///         + One or more requested properties is not supported on this device
xe_result_t __xecall
xetSysmanSetDeviceProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle for the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_device_property_request_t* pRequest         ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetDeviceProperties = xet_lib::context.ddiTable.Sysman.pfnSetDeviceProperties;
    if( nullptr == pfnSetDeviceProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetDeviceProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which PSU resource properties are available on a given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailablePsuProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_psu_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailablePsuProperties = xet_lib::context.ddiTable.Sysman.pfnAvailablePsuProperties;
    if( nullptr == pfnAvailablePsuProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailablePsuProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PSU resource property data
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
xetSysmanGetPsuProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetPsuProperties = xet_lib::context.ddiTable.Sysman.pfnGetPsuProperties;
    if( nullptr == pfnGetPsuProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPsuProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set PSU resource property data
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
xetSysmanSetPsuProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_psu_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetPsuProperties = xet_lib::context.ddiTable.Sysman.pfnSetPsuProperties;
    if( nullptr == pfnSetPsuProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPsuProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which temperature sensor properties are available on a given
///        device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableTempProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_temp_prop_capability_t* pCap                ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableTempProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableTempProperties;
    if( nullptr == pfnAvailableTempProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableTempProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor resource property data
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
xetSysmanGetTempProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_temp_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetTempProperties = xet_lib::context.ddiTable.Sysman.pfnGetTempProperties;
    if( nullptr == pfnGetTempProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetTempProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which fan resource properties are available on a given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableFanProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_fan_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableFanProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableFanProperties;
    if( nullptr == pfnAvailableFanProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableFanProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan resource property data
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
xetSysmanGetFanProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetFanProperties = xet_lib::context.ddiTable.Sysman.pfnGetFanProperties;
    if( nullptr == pfnGetFanProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFanProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan resource property data
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
xetSysmanSetFanProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_fan_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetFanProperties = xet_lib::context.ddiTable.Sysman.pfnSetFanProperties;
    if( nullptr == pfnSetFanProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFanProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which LED resource properties are available on a given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableLedProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_led_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableLedProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableLedProperties;
    if( nullptr == pfnAvailableLedProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableLedProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED resource property data
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
xetSysmanGetLedProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetLedProperties = xet_lib::context.ddiTable.Sysman.pfnGetLedProperties;
    if( nullptr == pfnGetLedProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLedProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set LED resource property data
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
xetSysmanSetLedProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_led_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetLedProperties = xet_lib::context.ddiTable.Sysman.pfnSetLedProperties;
    if( nullptr == pfnSetLedProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLedProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which firmware resource properties are available on a given
///        device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableFirmwareProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_firmware_prop_capability_t* pCap            ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableFirmwareProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableFirmwareProperties;
    if( nullptr == pfnAvailableFirmwareProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableFirmwareProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware resource property data
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
xetSysmanGetFirmwareProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetFirmwareProperties = xet_lib::context.ddiTable.Sysman.pfnGetFirmwareProperties;
    if( nullptr == pfnGetFirmwareProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFirmwareProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set firmware resource property data
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
xetSysmanSetFirmwareProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_firmware_property_request_t* pRequest       ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetFirmwareProperties = xet_lib::context.ddiTable.Sysman.pfnSetFirmwareProperties;
    if( nullptr == pfnSetFirmwareProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFirmwareProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which power domain resource properties are available on a
///        given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailablePwrProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_pwr_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailablePwrProperties = xet_lib::context.ddiTable.Sysman.pfnAvailablePwrProperties;
    if( nullptr == pfnAvailablePwrProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailablePwrProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power domain resource property data
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
xetSysmanGetPwrProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetPwrProperties = xet_lib::context.ddiTable.Sysman.pfnGetPwrProperties;
    if( nullptr == pfnGetPwrProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPwrProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power power resource property data
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
xetSysmanSetPwrProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwr_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetPwrProperties = xet_lib::context.ddiTable.Sysman.pfnSetPwrProperties;
    if( nullptr == pfnSetPwrProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPwrProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which frequency domain resource properties are available on a
///        given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableFreqProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_freq_prop_capability_t* pCap                ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableFreqProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableFreqProperties;
    if( nullptr == pfnAvailableFreqProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableFreqProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency domain resource property data
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
xetSysmanGetFreqProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetFreqProperties = xet_lib::context.ddiTable.Sysman.pfnGetFreqProperties;
    if( nullptr == pfnGetFreqProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFreqProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency domain resource property data
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
xetSysmanSetFreqProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_freq_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetFreqProperties = xet_lib::context.ddiTable.Sysman.pfnSetFreqProperties;
    if( nullptr == pfnSetFreqProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetFreqProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which power-well domain resource properties are available on
///        a given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailablePwrwellProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_pwrwell_prop_capability_t* pCap             ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailablePwrwellProperties = xet_lib::context.ddiTable.Sysman.pfnAvailablePwrwellProperties;
    if( nullptr == pfnAvailablePwrwellProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailablePwrwellProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power-well domain resource property data
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
xetSysmanGetPwrwellProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetPwrwellProperties = xet_lib::context.ddiTable.Sysman.pfnGetPwrwellProperties;
    if( nullptr == pfnGetPwrwellProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetPwrwellProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power-well domain resource property data
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
xetSysmanSetPwrwellProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_pwrwell_property_request_t* pRequest        ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetPwrwellProperties = xet_lib::context.ddiTable.Sysman.pfnSetPwrwellProperties;
    if( nullptr == pfnSetPwrwellProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetPwrwellProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which accelerator resource properties are available on a
///        given device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableAccelProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_accel_prop_capability_t* pCap               ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableAccelProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableAccelProperties;
    if( nullptr == pfnAvailableAccelProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableAccelProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get accelerator resource property data
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
xetSysmanGetAccelProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_accel_property_request_t* pRequest          ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetAccelProperties = xet_lib::context.ddiTable.Sysman.pfnGetAccelProperties;
    if( nullptr == pfnGetAccelProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAccelProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which memory resource properties are available on a given
///        device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableMemProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_mem_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableMemProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableMemProperties;
    if( nullptr == pfnAvailableMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableMemProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory resource property data
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
xetSysmanGetMemProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetMemProperties = xet_lib::context.ddiTable.Sysman.pfnGetMemProperties;
    if( nullptr == pfnGetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetMemProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set memory resource property data
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
xetSysmanSetMemProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_mem_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetMemProperties = xet_lib::context.ddiTable.Sysman.pfnSetMemProperties;
    if( nullptr == pfnSetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetMemProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which link resource properties are available on a given
///        device
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
///         + nullptr == pCap
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanAvailableLinkProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device.
    uint32_t count,                                 ///< [in] The number of entries in the array pCap
    xet_link_prop_capability_t* pCap                ///< [in] Pointer to an array of avilable property requests
    )
{
    auto pfnAvailableLinkProperties = xet_lib::context.ddiTable.Sysman.pfnAvailableLinkProperties;
    if( nullptr == pfnAvailableLinkProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAvailableLinkProperties( hSysman, count, pCap );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get link resource property data
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
xetSysmanGetLinkProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnGetLinkProperties = xet_lib::context.ddiTable.Sysman.pfnGetLinkProperties;
    if( nullptr == pfnGetLinkProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetLinkProperties( hSysman, count, pRequest );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set link resource property data
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
xetSysmanSetLinkProperties(
    xet_sysman_handle_t hSysman,                    ///< [in] SMI handle of the device
    uint32_t count,                                 ///< [in] The number of properties in the array pRequest
    xet_link_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
    )
{
    auto pfnSetLinkProperties = xet_lib::context.ddiTable.Sysman.pfnSetLinkProperties;
    if( nullptr == pfnSetLinkProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetLinkProperties( hSysman, count, pRequest );
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
    /// @brief Creates a handle to access SMI features for a device
    /// 
    /// @details
    ///     - Initializes internal structures to support SMI features.
    ///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is specified, no
    ///       access right checks are made during initialization. The check is done
    ///       in functions that attempt to control a device.
    ///     - If the write flag ::XET_SYSMAN_INIT_FLAGS_WRITE is not specified, any
    ///       function attempting to control a device will return
    ///       ::XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS.
    ///     - Multiple SMI handles can be created for the same device and concurrent
    ///       access through each handle to access underlying hardware resources is
    ///       supported.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **nvmlInit**
    ///     - **rsmi_init**
    /// 
    /// @returns
    ///     - Sysman*: Handle for accessing SMI features
    /// 
    /// @throws result_t
    Sysman* __xecall
    Sysman::Create(
        Device* pDevice,                                ///< [in] Handle of the device
        version_t version,                              ///< [in] SMI version that application was built with
        uint32_t flags                                  ///< [in] Bitfield of ::xet_sysman_init_flags_t
        )
    {
        xet_sysman_handle_t hSysman;

        auto result = static_cast<result_t>( ::xetSysmanCreate(
            reinterpret_cast<xet_device_handle_t>( pDevice->getHandle() ),
            static_cast<xet_sysman_version_t>( version ),
            flags,
            &hSysman ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::Create" );

        Sysman* pSysman = nullptr;

        try
        {
            pSysman = new Sysman( reinterpret_cast<sysman_handle_t>( hSysman ), nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pSysman;
            pSysman = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Sysman::Create" );
        }

        return pSysman;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a SMI handle
    /// 
    /// @details
    ///     - Only once all SMI handles to a device have been destroyed will
    ///       internal data structures be freed from the application memory.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **nvmlShutdown**
    ///     - **rsmi_shut_down**
    /// 
    /// @throws result_t
    void __xecall
    Sysman::Destroy(
        Sysman* pSysman                                 ///< [in][release] SMI handle to destroy
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanDestroy(
            reinterpret_cast<xet_sysman_handle_t>( pSysman->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::Destroy" );

        delete pSysman;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get human-readable name for an accelerator asset
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetAccelAssetName(
        accel_asset_t type,                             ///< [in] The type of accelerator asset
        const char** ppName                             ///< [in] Pointer to the asset name
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetAccelAssetName(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            static_cast<xet_accel_asset_t>( type ),
            ppName ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetAccelAssetName" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get SMI information for a device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetInfo(
        info_t* pInfo                                   ///< [in] Returned information
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetInfo(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            reinterpret_cast<xet_sysman_info_t*>( pInfo ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetInfo" );
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
    /// @brief Find out which device properties are available on a given device
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
    Sysman::AvailableDeviceProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        device_prop_capability_t* pCap                  ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableDeviceProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_device_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableDeviceProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get device property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetDeviceProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        device_property_request_t* pRequest             ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetDeviceProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_device_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetDeviceProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set device property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetDeviceProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        device_property_request_t* pRequest             ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetDeviceProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_device_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetDeviceProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which PSU resource properties are available on a given device
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
    Sysman::AvailablePsuProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        psu_prop_capability_t* pCap                     ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailablePsuProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_psu_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailablePsuProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PSU resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetPsuProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        psu_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetPsuProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_psu_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetPsuProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set PSU resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetPsuProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        psu_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetPsuProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_psu_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetPsuProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which temperature sensor properties are available on a given
    ///        device
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
    Sysman::AvailableTempProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        temp_prop_capability_t* pCap                    ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableTempProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_temp_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableTempProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperature sensor resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetTempProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        temp_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetTempProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_temp_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetTempProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which fan resource properties are available on a given device
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
    Sysman::AvailableFanProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        fan_prop_capability_t* pCap                     ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableFanProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_fan_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableFanProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetFanProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        fan_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetFanProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_fan_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetFanProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set fan resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetFanProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        fan_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetFanProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_fan_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetFanProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which LED resource properties are available on a given device
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
    Sysman::AvailableLedProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        led_prop_capability_t* pCap                     ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableLedProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_led_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableLedProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get LED resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetLedProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        led_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetLedProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_led_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetLedProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set LED resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetLedProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        led_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetLedProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_led_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetLedProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which firmware resource properties are available on a given
    ///        device
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
    Sysman::AvailableFirmwareProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        firmware_prop_capability_t* pCap                ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableFirmwareProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_firmware_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableFirmwareProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetFirmwareProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        firmware_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetFirmwareProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_firmware_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetFirmwareProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set firmware resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetFirmwareProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        firmware_property_request_t* pRequest           ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetFirmwareProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_firmware_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetFirmwareProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which power domain resource properties are available on a
    ///        given device
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
    Sysman::AvailablePwrProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        pwr_prop_capability_t* pCap                     ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailablePwrProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwr_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailablePwrProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power domain resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetPwrProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwr_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetPwrProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwr_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetPwrProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power power resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetPwrProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwr_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetPwrProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwr_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetPwrProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which frequency domain resource properties are available on a
    ///        given device
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
    Sysman::AvailableFreqProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        freq_prop_capability_t* pCap                    ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableFreqProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_freq_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableFreqProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency domain resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetFreqProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        freq_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetFreqProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_freq_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetFreqProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set frequency domain resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetFreqProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        freq_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetFreqProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_freq_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetFreqProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which power-well domain resource properties are available on
    ///        a given device
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
    Sysman::AvailablePwrwellProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        pwrwell_prop_capability_t* pCap                 ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailablePwrwellProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwrwell_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailablePwrwellProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power-well domain resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetPwrwellProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwrwell_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetPwrwellProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwrwell_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetPwrwellProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power-well domain resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetPwrwellProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        pwrwell_property_request_t* pRequest            ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetPwrwellProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_pwrwell_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetPwrwellProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which accelerator resource properties are available on a
    ///        given device
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
    Sysman::AvailableAccelProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        accel_prop_capability_t* pCap                   ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableAccelProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_accel_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableAccelProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get accelerator resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetAccelProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        accel_property_request_t* pRequest              ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetAccelProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_accel_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetAccelProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which memory resource properties are available on a given
    ///        device
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
    Sysman::AvailableMemProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        mem_prop_capability_t* pCap                     ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableMemProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_mem_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableMemProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetMemProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        mem_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetMemProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_mem_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetMemProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set memory resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetMemProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        mem_property_request_t* pRequest                ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetMemProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_mem_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetMemProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Find out which link resource properties are available on a given
    ///        device
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
    Sysman::AvailableLinkProperties(
        uint32_t count,                                 ///< [in] The number of entries in the array pCap
        link_prop_capability_t* pCap                    ///< [in] Pointer to an array of avilable property requests
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanAvailableLinkProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_link_prop_capability_t*>( pCap ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::AvailableLinkProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get link resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::GetLinkProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        link_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanGetLinkProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_link_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::GetLinkProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set link resource property data
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Sysman::SetLinkProperties(
        uint32_t count,                                 ///< [in] The number of properties in the array pRequest
        link_property_request_t* pRequest               ///< [in] Pointer to list of properties and corresponding data storage
        )
    {
        auto result = static_cast<result_t>( ::xetSysmanSetLinkProperties(
            reinterpret_cast<xet_sysman_handle_t>( getHandle() ),
            count,
            reinterpret_cast<xet_link_property_request_t*>( pRequest ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Sysman::SetLinkProperties" );
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
    /// @brief Converts Sysman::init_flags_t to std::string
    std::string to_string( const Sysman::init_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Sysman::init_flags_t::WRITE) & bits )
            str += "WRITE | ";

        return ( str.size() > 3 ) 
            ? "Sysman::init_flags_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Sysman::init_flags_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_type_t to std::string
    std::string to_string( const Sysman::resource_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::resource_type_t::PSU:
            str = "Sysman::resource_type_t::PSU";
            break;

        case Sysman::resource_type_t::TEMP:
            str = "Sysman::resource_type_t::TEMP";
            break;

        case Sysman::resource_type_t::FAN:
            str = "Sysman::resource_type_t::FAN";
            break;

        case Sysman::resource_type_t::LED:
            str = "Sysman::resource_type_t::LED";
            break;

        case Sysman::resource_type_t::FIRMWARE:
            str = "Sysman::resource_type_t::FIRMWARE";
            break;

        case Sysman::resource_type_t::PWR:
            str = "Sysman::resource_type_t::PWR";
            break;

        case Sysman::resource_type_t::FREQ:
            str = "Sysman::resource_type_t::FREQ";
            break;

        case Sysman::resource_type_t::PWRWELL:
            str = "Sysman::resource_type_t::PWRWELL";
            break;

        case Sysman::resource_type_t::ACCEL:
            str = "Sysman::resource_type_t::ACCEL";
            break;

        case Sysman::resource_type_t::MEM:
            str = "Sysman::resource_type_t::MEM";
            break;

        case Sysman::resource_type_t::LINK:
            str = "Sysman::resource_type_t::LINK";
            break;

        case Sysman::resource_type_t::MAX_TYPES:
            str = "Sysman::resource_type_t::MAX_TYPES";
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
    /// @brief Converts Sysman::accel_asset_t to std::string
    std::string to_string( const Sysman::accel_asset_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::accel_asset_t::PCIE_CONTROLLER:
            str = "Sysman::accel_asset_t::PCIE_CONTROLLER";
            break;

        case Sysman::accel_asset_t::IDI_MEM_CONTROLLER:
            str = "Sysman::accel_asset_t::IDI_MEM_CONTROLLER";
            break;

        case Sysman::accel_asset_t::HBM_MEM_CONTROLLER:
            str = "Sysman::accel_asset_t::HBM_MEM_CONTROLLER";
            break;

        case Sysman::accel_asset_t::L3_CACHE:
            str = "Sysman::accel_asset_t::L3_CACHE";
            break;

        case Sysman::accel_asset_t::BLITTER:
            str = "Sysman::accel_asset_t::BLITTER";
            break;

        case Sysman::accel_asset_t::VIDEO_DECODER:
            str = "Sysman::accel_asset_t::VIDEO_DECODER";
            break;

        case Sysman::accel_asset_t::VIDEO_ENCODER:
            str = "Sysman::accel_asset_t::VIDEO_ENCODER";
            break;

        case Sysman::accel_asset_t::VIDEO_PROCESSING:
            str = "Sysman::accel_asset_t::VIDEO_PROCESSING";
            break;

        case Sysman::accel_asset_t::_3D_FF:
            str = "Sysman::accel_asset_t::_3D_FF";
            break;

        case Sysman::accel_asset_t::_3D_RENDER:
            str = "Sysman::accel_asset_t::_3D_RENDER";
            break;

        case Sysman::accel_asset_t::COMPUTE:
            str = "Sysman::accel_asset_t::COMPUTE";
            break;

        case Sysman::accel_asset_t::SYSTOLIC:
            str = "Sysman::accel_asset_t::SYSTOLIC";
            break;

        case Sysman::accel_asset_t::RAYTRACING:
            str = "Sysman::accel_asset_t::RAYTRACING";
            break;

        case Sysman::accel_asset_t::LOCAL_MEM:
            str = "Sysman::accel_asset_t::LOCAL_MEM";
            break;

        case Sysman::accel_asset_t::LINK:
            str = "Sysman::accel_asset_t::LINK";
            break;

        case Sysman::accel_asset_t::MAX_TYPES:
            str = "Sysman::accel_asset_t::MAX_TYPES";
            break;

        default:
            str = "Sysman::accel_asset_t::?";
            break;
        };

        return str;
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
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::PCI) & bits )
            str += "PCI | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::PCI_ROUTING) & bits )
            str += "PCI_ROUTING | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::SGUNIT) & bits )
            str += "SGUNIT | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::GSC) & bits )
            str += "GSC | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::DISPLAY) & bits )
            str += "DISPLAY | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::SOC) & bits )
            str += "SOC | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::GPU_HANG) & bits )
            str += "GPU_HANG | ";
        
        if( static_cast<uint32_t>(Sysman::ras_error_loc_t::GPU_WARM_RESET) & bits )
            str += "GPU_WARM_RESET | ";
        
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
    /// @brief Converts Sysman::device_properties_t to std::string
    std::string to_string( const Sysman::device_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::device_properties_t::DEVICE_PROP_SERIAL_NUMBER:
            str = "Sysman::device_properties_t::DEVICE_PROP_SERIAL_NUMBER";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_BOARD_NUMBER:
            str = "Sysman::device_properties_t::DEVICE_PROP_BOARD_NUMBER";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_BRAND:
            str = "Sysman::device_properties_t::DEVICE_PROP_BRAND";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_MODEL:
            str = "Sysman::device_properties_t::DEVICE_PROP_MODEL";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_DEVICEID:
            str = "Sysman::device_properties_t::DEVICE_PROP_DEVICEID";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_VENDOR_NAME:
            str = "Sysman::device_properties_t::DEVICE_PROP_VENDOR_NAME";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_DRIVER_VERSION:
            str = "Sysman::device_properties_t::DEVICE_PROP_DRIVER_VERSION";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_BARS:
            str = "Sysman::device_properties_t::DEVICE_PROP_BARS";
            break;

        case Sysman::device_properties_t::DEVICE_PROP_RESET:
            str = "Sysman::device_properties_t::DEVICE_PROP_RESET";
            break;

        default:
            str = "Sysman::device_properties_t::?";
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
    /// @brief Converts Sysman::psu_properties_t to std::string
    std::string to_string( const Sysman::psu_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::psu_properties_t::PSU_PROP_AMP_LIMIT:
            str = "Sysman::psu_properties_t::PSU_PROP_AMP_LIMIT";
            break;

        case Sysman::psu_properties_t::PSU_PROP_VOLTAGE_STATUS:
            str = "Sysman::psu_properties_t::PSU_PROP_VOLTAGE_STATUS";
            break;

        case Sysman::psu_properties_t::PSU_PROP_FAN_FAILURE:
            str = "Sysman::psu_properties_t::PSU_PROP_FAN_FAILURE";
            break;

        case Sysman::psu_properties_t::PSU_PROP_TEMPERATURE:
            str = "Sysman::psu_properties_t::PSU_PROP_TEMPERATURE";
            break;

        case Sysman::psu_properties_t::PSU_PROP_AMPS:
            str = "Sysman::psu_properties_t::PSU_PROP_AMPS";
            break;

        default:
            str = "Sysman::psu_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_properties_t to std::string
    std::string to_string( const Sysman::temp_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::temp_properties_t::TEMP_PROP_TEMPERATURE:
            str = "Sysman::temp_properties_t::TEMP_PROP_TEMPERATURE";
            break;

        default:
            str = "Sysman::temp_properties_t::?";
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
    /// @brief Converts Sysman::fan_properties_t to std::string
    std::string to_string( const Sysman::fan_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::fan_properties_t::FAN_PROP_MAX_RPM:
            str = "Sysman::fan_properties_t::FAN_PROP_MAX_RPM";
            break;

        case Sysman::fan_properties_t::FAN_PROP_MAX_TABLE_SIZE:
            str = "Sysman::fan_properties_t::FAN_PROP_MAX_TABLE_SIZE";
            break;

        case Sysman::fan_properties_t::FAN_PROP_SPEED_RPM:
            str = "Sysman::fan_properties_t::FAN_PROP_SPEED_RPM";
            break;

        case Sysman::fan_properties_t::FAN_PROP_SPEED_PERCENT:
            str = "Sysman::fan_properties_t::FAN_PROP_SPEED_PERCENT";
            break;

        case Sysman::fan_properties_t::FAN_PROP_MODE:
            str = "Sysman::fan_properties_t::FAN_PROP_MODE";
            break;

        case Sysman::fan_properties_t::FAN_PROP_FIXED_SPEED:
            str = "Sysman::fan_properties_t::FAN_PROP_FIXED_SPEED";
            break;

        case Sysman::fan_properties_t::FAN_PROP_SPEED_TABLE:
            str = "Sysman::fan_properties_t::FAN_PROP_SPEED_TABLE";
            break;

        default:
            str = "Sysman::fan_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_properties_t to std::string
    std::string to_string( const Sysman::led_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::led_properties_t::LED_PROP_RGB_CAP:
            str = "Sysman::led_properties_t::LED_PROP_RGB_CAP";
            break;

        case Sysman::led_properties_t::LED_PROP_STATE:
            str = "Sysman::led_properties_t::LED_PROP_STATE";
            break;

        default:
            str = "Sysman::led_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_properties_t to std::string
    std::string to_string( const Sysman::firmware_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::firmware_properties_t::FIRMWARE_PROP_NAME:
            str = "Sysman::firmware_properties_t::FIRMWARE_PROP_NAME";
            break;

        case Sysman::firmware_properties_t::FIRMWARE_PROP_VERSION:
            str = "Sysman::firmware_properties_t::FIRMWARE_PROP_VERSION";
            break;

        case Sysman::firmware_properties_t::FIRMWARE_PROP_CHECK:
            str = "Sysman::firmware_properties_t::FIRMWARE_PROP_CHECK";
            break;

        case Sysman::firmware_properties_t::FIRMWARE_PROP_FLASH:
            str = "Sysman::firmware_properties_t::FIRMWARE_PROP_FLASH";
            break;

        default:
            str = "Sysman::firmware_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_properties_t to std::string
    std::string to_string( const Sysman::pwr_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::pwr_properties_t::PWR_PROP_ACCEL_ASSETS:
            str = "Sysman::pwr_properties_t::PWR_PROP_ACCEL_ASSETS";
            break;

        case Sysman::pwr_properties_t::PWR_PROP_MAX_LIMIT:
            str = "Sysman::pwr_properties_t::PWR_PROP_MAX_LIMIT";
            break;

        case Sysman::pwr_properties_t::PWR_PROP_ENERGY_COUNTER:
            str = "Sysman::pwr_properties_t::PWR_PROP_ENERGY_COUNTER";
            break;

        case Sysman::pwr_properties_t::PWR_PROP_SUSTAINED_LIMIT:
            str = "Sysman::pwr_properties_t::PWR_PROP_SUSTAINED_LIMIT";
            break;

        case Sysman::pwr_properties_t::PWR_PROP_BURST_LIMIT:
            str = "Sysman::pwr_properties_t::PWR_PROP_BURST_LIMIT";
            break;

        case Sysman::pwr_properties_t::PWR_PROP_PEAK_LIMIT:
            str = "Sysman::pwr_properties_t::PWR_PROP_PEAK_LIMIT";
            break;

        default:
            str = "Sysman::pwr_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_domain_type_t to std::string
    std::string to_string( const Sysman::freq_domain_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::freq_domain_type_t::PLL:
            str = "Sysman::freq_domain_type_t::PLL";
            break;

        case Sysman::freq_domain_type_t::DIVIDER:
            str = "Sysman::freq_domain_type_t::DIVIDER";
            break;

        case Sysman::freq_domain_type_t::MULTIPLIER:
            str = "Sysman::freq_domain_type_t::MULTIPLIER";
            break;

        default:
            str = "Sysman::freq_domain_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_mode_t to std::string
    std::string to_string( const Sysman::freq_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::freq_mode_t::DEFAULT:
            str = "Sysman::freq_mode_t::DEFAULT";
            break;

        case Sysman::freq_mode_t::FIXED:
            str = "Sysman::freq_mode_t::FIXED";
            break;

        default:
            str = "Sysman::freq_mode_t::?";
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
    /// @brief Converts Sysman::freq_properties_t to std::string
    std::string to_string( const Sysman::freq_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::freq_properties_t::FREQ_PROP_ACCEL_ASSETS:
            str = "Sysman::freq_properties_t::FREQ_PROP_ACCEL_ASSETS";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_POWER_DOMAIN:
            str = "Sysman::freq_properties_t::FREQ_PROP_POWER_DOMAIN";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_DOMAIN_TYPE:
            str = "Sysman::freq_properties_t::FREQ_PROP_DOMAIN_TYPE";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_AVAIL_CLOCKS:
            str = "Sysman::freq_properties_t::FREQ_PROP_AVAIL_CLOCKS";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_AVAIL_DIVIDERS:
            str = "Sysman::freq_properties_t::FREQ_PROP_AVAIL_DIVIDERS";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_AVAIL_MULTIPLIERS:
            str = "Sysman::freq_properties_t::FREQ_PROP_AVAIL_MULTIPLIERS";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_SRC_FREQ:
            str = "Sysman::freq_properties_t::FREQ_PROP_SRC_FREQ";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_FREQ_REQUEST:
            str = "Sysman::freq_properties_t::FREQ_PROP_FREQ_REQUEST";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_FREQ_DIVIDER:
            str = "Sysman::freq_properties_t::FREQ_PROP_FREQ_DIVIDER";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_FREQ_MULTIPLIER:
            str = "Sysman::freq_properties_t::FREQ_PROP_FREQ_MULTIPLIER";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_FREQ_TDP:
            str = "Sysman::freq_properties_t::FREQ_PROP_FREQ_TDP";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_FREQ_EFFICIENT:
            str = "Sysman::freq_properties_t::FREQ_PROP_FREQ_EFFICIENT";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_FREQ_RESOLVED:
            str = "Sysman::freq_properties_t::FREQ_PROP_FREQ_RESOLVED";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_THROTTLE_REASONS:
            str = "Sysman::freq_properties_t::FREQ_PROP_THROTTLE_REASONS";
            break;

        case Sysman::freq_properties_t::FREQ_PROP_THROTTLE_TIME:
            str = "Sysman::freq_properties_t::FREQ_PROP_THROTTLE_TIME";
            break;

        default:
            str = "Sysman::freq_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_promo_mode_t to std::string
    std::string to_string( const Sysman::pwrwell_promo_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::pwrwell_promo_mode_t::IMMEDIATE:
            str = "Sysman::pwrwell_promo_mode_t::IMMEDIATE";
            break;

        case Sysman::pwrwell_promo_mode_t::EFFICIENT:
            str = "Sysman::pwrwell_promo_mode_t::EFFICIENT";
            break;

        case Sysman::pwrwell_promo_mode_t::DEFAULT:
            str = "Sysman::pwrwell_promo_mode_t::DEFAULT";
            break;

        case Sysman::pwrwell_promo_mode_t::PERFORMANCE:
            str = "Sysman::pwrwell_promo_mode_t::PERFORMANCE";
            break;

        case Sysman::pwrwell_promo_mode_t::NEVER:
            str = "Sysman::pwrwell_promo_mode_t::NEVER";
            break;

        default:
            str = "Sysman::pwrwell_promo_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_properties_t to std::string
    std::string to_string( const Sysman::pwrwell_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::pwrwell_properties_t::PWRWELL_PROP_ACCEL_ASSETS:
            str = "Sysman::pwrwell_properties_t::PWRWELL_PROP_ACCEL_ASSETS";
            break;

        case Sysman::pwrwell_properties_t::PWRWELL_PROP_PROMO_CAP:
            str = "Sysman::pwrwell_properties_t::PWRWELL_PROP_PROMO_CAP";
            break;

        case Sysman::pwrwell_properties_t::PWRWELL_PROP_PROMO_MODE:
            str = "Sysman::pwrwell_properties_t::PWRWELL_PROP_PROMO_MODE";
            break;

        case Sysman::pwrwell_properties_t::PWRWELL_PROP_UTILIZATION:
            str = "Sysman::pwrwell_properties_t::PWRWELL_PROP_UTILIZATION";
            break;

        case Sysman::pwrwell_properties_t::PWRWELL_PROP_TRANSITIONS:
            str = "Sysman::pwrwell_properties_t::PWRWELL_PROP_TRANSITIONS";
            break;

        default:
            str = "Sysman::pwrwell_properties_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_properties_t to std::string
    std::string to_string( const Sysman::accel_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::accel_properties_t::ACCEL_PROP_ACCEL_ASSETS:
            str = "Sysman::accel_properties_t::ACCEL_PROP_ACCEL_ASSETS";
            break;

        case Sysman::accel_properties_t::ACCEL_PROP_UTILIZATION:
            str = "Sysman::accel_properties_t::ACCEL_PROP_UTILIZATION";
            break;

        default:
            str = "Sysman::accel_properties_t::?";
            break;
        };

        return str;
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
    /// @brief Converts Sysman::mem_retire_reason_t to std::string
    std::string to_string( const Sysman::mem_retire_reason_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::mem_retire_reason_t::MULTIPLE_SINGLE_BIT_ERRORS:
            str = "Sysman::mem_retire_reason_t::MULTIPLE_SINGLE_BIT_ERRORS";
            break;

        case Sysman::mem_retire_reason_t::DOUBLE_BIT_ERRORS:
            str = "Sysman::mem_retire_reason_t::DOUBLE_BIT_ERRORS";
            break;

        default:
            str = "Sysman::mem_retire_reason_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_properties_t to std::string
    std::string to_string( const Sysman::mem_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::mem_properties_t::MEM_PROP_TYPE:
            str = "Sysman::mem_properties_t::MEM_PROP_TYPE";
            break;

        case Sysman::mem_properties_t::MEM_PROP_UTILIZATION:
            str = "Sysman::mem_properties_t::MEM_PROP_UTILIZATION";
            break;

        case Sysman::mem_properties_t::MEM_PROP_BANDWIDTH:
            str = "Sysman::mem_properties_t::MEM_PROP_BANDWIDTH";
            break;

        default:
            str = "Sysman::mem_properties_t::?";
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

        case Sysman::link_type_t::PEER_TO_PEER:
            str = "Sysman::link_type_t::PEER_TO_PEER";
            break;

        default:
            str = "Sysman::link_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_properties_t to std::string
    std::string to_string( const Sysman::link_properties_t val )
    {
        std::string str;

        switch( val )
        {
        case Sysman::link_properties_t::LINK_PROP_TYPE:
            str = "Sysman::link_properties_t::LINK_PROP_TYPE";
            break;

        case Sysman::link_properties_t::LINK_PROP_BUS_ADDRESS:
            str = "Sysman::link_properties_t::LINK_PROP_BUS_ADDRESS";
            break;

        case Sysman::link_properties_t::LINK_PROP_PEER_DEVICE:
            str = "Sysman::link_properties_t::LINK_PROP_PEER_DEVICE";
            break;

        case Sysman::link_properties_t::LINK_PROP_AVAIL_SPEEDS:
            str = "Sysman::link_properties_t::LINK_PROP_AVAIL_SPEEDS";
            break;

        case Sysman::link_properties_t::LINK_PROP_MAX_PACKET_SIZE:
            str = "Sysman::link_properties_t::LINK_PROP_MAX_PACKET_SIZE";
            break;

        case Sysman::link_properties_t::LINK_PROP_BANDWIDTH:
            str = "Sysman::link_properties_t::LINK_PROP_BANDWIDTH";
            break;

        case Sysman::link_properties_t::LINK_PROP_SPEED:
            str = "Sysman::link_properties_t::LINK_PROP_SPEED";
            break;

        case Sysman::link_properties_t::LINK_PROP_SPEED_RANGE:
            str = "Sysman::link_properties_t::LINK_PROP_SPEED_RANGE";
            break;

        default:
            str = "Sysman::link_properties_t::?";
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
    /// @brief Converts Sysman::resource_id_t to std::string
    std::string to_string( const Sysman::resource_id_t val )
    {
        std::string str;
        
        str += "Sysman::resource_id_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Sysman::resource_id_t::index : ";
        str += std::to_string(val.index);
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
        
        str += "Sysman::ras_error_t::resourceId : ";
        str += to_string(val.resourceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::info_t to std::string
    std::string to_string( const Sysman::info_t val )
    {
        std::string str;
        
        str += "Sysman::info_t::numAssets : ";
        {
            std::string tmp;
            for( auto& entry : val.numAssets )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "Sysman::info_t::numRas : ";
        str += std::to_string(val.numRas);
        str += "\n";
        
        str += "Sysman::info_t::rasTypes : ";
        str += std::to_string(val.rasTypes);
        str += "\n";
        
        str += "Sysman::info_t::rasLocations : ";
        str += std::to_string(val.rasLocations);
        str += "\n";
        
        str += "Sysman::info_t::numResourcesByType : ";
        {
            std::string tmp;
            for( auto& entry : val.numResourcesByType )
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
    /// @brief Converts Sysman::device_prop_serial_number_t to std::string
    std::string to_string( const Sysman::device_prop_serial_number_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_serial_number_t::str : ";
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
    /// @brief Converts Sysman::device_prop_board_number_t to std::string
    std::string to_string( const Sysman::device_prop_board_number_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_board_number_t::str : ";
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
    /// @brief Converts Sysman::device_prop_brand_t to std::string
    std::string to_string( const Sysman::device_prop_brand_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_brand_t::str : ";
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
    /// @brief Converts Sysman::device_prop_model_t to std::string
    std::string to_string( const Sysman::device_prop_model_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_model_t::str : ";
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
    /// @brief Converts Sysman::device_prop_deviceid_t to std::string
    std::string to_string( const Sysman::device_prop_deviceid_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_deviceid_t::str : ";
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
    /// @brief Converts Sysman::device_prop_vendor_name_t to std::string
    std::string to_string( const Sysman::device_prop_vendor_name_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_vendor_name_t::str : ";
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
    /// @brief Converts Sysman::device_prop_driver_version_t to std::string
    std::string to_string( const Sysman::device_prop_driver_version_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_driver_version_t::str : ";
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
    /// @brief Converts Sysman::device_prop_bars_t to std::string
    std::string to_string( const Sysman::device_prop_bars_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_bars_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "Sysman::device_prop_bars_t::pBars : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pBars);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_reset_t to std::string
    std::string to_string( const Sysman::device_prop_reset_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_reset_t::doReset : ";
        str += std::to_string(val.doReset);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_prop_capability_t to std::string
    std::string to_string( const Sysman::device_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::device_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::device_prop_capability_t::support : ";
        str += std::to_string(val.support);
        str += "\n";
        
        str += "Sysman::device_prop_capability_t::access : ";
        str += std::to_string(val.access);
        str += "\n";
        
        str += "Sysman::device_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::device_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::device_property_request_t to std::string
    std::string to_string( const Sysman::device_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::device_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::device_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::device_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_amp_limit_t to std::string
    std::string to_string( const Sysman::psu_prop_amp_limit_t val )
    {
        std::string str;
        
        str += "Sysman::psu_prop_amp_limit_t::limit : ";
        str += std::to_string(val.limit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_voltage_status_t to std::string
    std::string to_string( const Sysman::psu_prop_voltage_status_t val )
    {
        std::string str;
        
        str += "Sysman::psu_prop_voltage_status_t::status : ";
        str += to_string(val.status);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_fan_failure_t to std::string
    std::string to_string( const Sysman::psu_prop_fan_failure_t val )
    {
        std::string str;
        
        str += "Sysman::psu_prop_fan_failure_t::status : ";
        str += std::to_string(val.status);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_temperature_t to std::string
    std::string to_string( const Sysman::psu_prop_temperature_t val )
    {
        std::string str;
        
        str += "Sysman::psu_prop_temperature_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_amps_t to std::string
    std::string to_string( const Sysman::psu_prop_amps_t val )
    {
        std::string str;
        
        str += "Sysman::psu_prop_amps_t::current : ";
        str += std::to_string(val.current);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_prop_capability_t to std::string
    std::string to_string( const Sysman::psu_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::psu_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::psu_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::psu_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::psu_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::psu_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::psu_property_request_t to std::string
    std::string to_string( const Sysman::psu_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::psu_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::psu_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::psu_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::psu_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_prop_temperature_t to std::string
    std::string to_string( const Sysman::temp_prop_temperature_t val )
    {
        std::string str;
        
        str += "Sysman::temp_prop_temperature_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_prop_capability_t to std::string
    std::string to_string( const Sysman::temp_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::temp_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::temp_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::temp_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::temp_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::temp_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::temp_property_request_t to std::string
    std::string to_string( const Sysman::temp_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::temp_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::temp_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::temp_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::temp_property_request_t::size : ";
        str += std::to_string(val.size);
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
    /// @brief Converts Sysman::fan_prop_max_rpm_t to std::string
    std::string to_string( const Sysman::fan_prop_max_rpm_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_max_rpm_t::maxSpeed : ";
        str += std::to_string(val.maxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_max_table_size_t to std::string
    std::string to_string( const Sysman::fan_prop_max_table_size_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_max_table_size_t::maxPoints : ";
        str += std::to_string(val.maxPoints);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_speed_rpm_t to std::string
    std::string to_string( const Sysman::fan_prop_speed_rpm_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_speed_rpm_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_speed_percent_t to std::string
    std::string to_string( const Sysman::fan_prop_speed_percent_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_speed_percent_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_mode_t to std::string
    std::string to_string( const Sysman::fan_prop_mode_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_mode_t::mode : ";
        str += to_string(val.mode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_fixed_speed_t to std::string
    std::string to_string( const Sysman::fan_prop_fixed_speed_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_fixed_speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "Sysman::fan_prop_fixed_speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_prop_speed_table_t to std::string
    std::string to_string( const Sysman::fan_prop_speed_table_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_speed_table_t::pCount : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pCount);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::fan_prop_speed_table_t::points : ";
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
    /// @brief Converts Sysman::fan_prop_capability_t to std::string
    std::string to_string( const Sysman::fan_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::fan_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::fan_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::fan_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::fan_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::fan_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::fan_property_request_t to std::string
    std::string to_string( const Sysman::fan_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::fan_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::fan_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::fan_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::fan_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_prop_rgb_cap_t to std::string
    std::string to_string( const Sysman::led_prop_rgb_cap_t val )
    {
        std::string str;
        
        str += "Sysman::led_prop_rgb_cap_t::haveRGB : ";
        str += std::to_string(val.haveRGB);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_prop_state_t to std::string
    std::string to_string( const Sysman::led_prop_state_t val )
    {
        std::string str;
        
        str += "Sysman::led_prop_state_t::isOn : ";
        str += std::to_string(val.isOn);
        str += "\n";
        
        str += "Sysman::led_prop_state_t::red : ";
        str += std::to_string(val.red);
        str += "\n";
        
        str += "Sysman::led_prop_state_t::green : ";
        str += std::to_string(val.green);
        str += "\n";
        
        str += "Sysman::led_prop_state_t::blue : ";
        str += std::to_string(val.blue);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_prop_capability_t to std::string
    std::string to_string( const Sysman::led_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::led_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::led_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::led_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::led_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::led_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::led_property_request_t to std::string
    std::string to_string( const Sysman::led_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::led_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::led_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::led_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::led_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_prop_name_t to std::string
    std::string to_string( const Sysman::firmware_prop_name_t val )
    {
        std::string str;
        
        str += "Sysman::firmware_prop_name_t::str : ";
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
    /// @brief Converts Sysman::firmware_prop_version_t to std::string
    std::string to_string( const Sysman::firmware_prop_version_t val )
    {
        std::string str;
        
        str += "Sysman::firmware_prop_version_t::str : ";
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
    /// @brief Converts Sysman::firmware_prop_check_t to std::string
    std::string to_string( const Sysman::firmware_prop_check_t val )
    {
        std::string str;
        
        str += "Sysman::firmware_prop_check_t::checksum : ";
        str += std::to_string(val.checksum);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_prop_flash_t to std::string
    std::string to_string( const Sysman::firmware_prop_flash_t val )
    {
        std::string str;
        
        str += "Sysman::firmware_prop_flash_t::pImage : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pImage);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::firmware_prop_flash_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_prop_capability_t to std::string
    std::string to_string( const Sysman::firmware_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::firmware_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::firmware_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::firmware_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::firmware_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::firmware_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::firmware_property_request_t to std::string
    std::string to_string( const Sysman::firmware_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::firmware_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::firmware_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::firmware_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::firmware_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::pwr_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_max_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_max_limit_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_prop_max_limit_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_energy_counter_t to std::string
    std::string to_string( const Sysman::pwr_prop_energy_counter_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_prop_energy_counter_t::energy : ";
        str += std::to_string(val.energy);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_sustained_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_sustained_limit_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_prop_sustained_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Sysman::pwr_prop_sustained_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";
        
        str += "Sysman::pwr_prop_sustained_limit_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_burst_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_burst_limit_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_prop_burst_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Sysman::pwr_prop_burst_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_peak_limit_t to std::string
    std::string to_string( const Sysman::pwr_prop_peak_limit_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_prop_peak_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_prop_capability_t to std::string
    std::string to_string( const Sysman::pwr_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::pwr_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::pwr_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::pwr_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::pwr_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwr_property_request_t to std::string
    std::string to_string( const Sysman::pwr_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::pwr_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::pwr_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::pwr_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::pwr_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_divider_t to std::string
    std::string to_string( const Sysman::freq_divider_t val )
    {
        std::string str;
        
        str += "Sysman::freq_divider_t::numerator : ";
        str += std::to_string(val.numerator);
        str += "\n";
        
        str += "Sysman::freq_divider_t::denominator : ";
        str += std::to_string(val.denominator);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_multiplier_t to std::string
    std::string to_string( const Sysman::freq_multiplier_t val )
    {
        std::string str;
        
        str += "Sysman::freq_multiplier_t::multiplierFP8_8 : ";
        str += std::to_string(val.multiplierFP8_8);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::freq_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_power_domain_t to std::string
    std::string to_string( const Sysman::freq_prop_power_domain_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_power_domain_t::resource : ";
        str += to_string(val.resource);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_domain_type_t to std::string
    std::string to_string( const Sysman::freq_prop_domain_type_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_domain_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_avail_clocks_t to std::string
    std::string to_string( const Sysman::freq_prop_avail_clocks_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_avail_clocks_t::minFP16_16 : ";
        str += std::to_string(val.minFP16_16);
        str += "\n";
        
        str += "Sysman::freq_prop_avail_clocks_t::maxFP16_16 : ";
        str += std::to_string(val.maxFP16_16);
        str += "\n";
        
        str += "Sysman::freq_prop_avail_clocks_t::stepFP16_16 : ";
        str += std::to_string(val.stepFP16_16);
        str += "\n";
        
        str += "Sysman::freq_prop_avail_clocks_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "Sysman::freq_prop_avail_clocks_t::pClocksFP16_16 : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pClocksFP16_16);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_avail_dividers_t to std::string
    std::string to_string( const Sysman::freq_prop_avail_dividers_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_avail_dividers_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "Sysman::freq_prop_avail_dividers_t::pDividers : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pDividers);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_avail_multipliers_t to std::string
    std::string to_string( const Sysman::freq_prop_avail_multipliers_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_avail_multipliers_t::minFP8_8 : ";
        str += std::to_string(val.minFP8_8);
        str += "\n";
        
        str += "Sysman::freq_prop_avail_multipliers_t::maxFP8_8 : ";
        str += std::to_string(val.maxFP8_8);
        str += "\n";
        
        str += "Sysman::freq_prop_avail_multipliers_t::minStepFP8_8 : ";
        str += std::to_string(val.minStepFP8_8);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_src_freq_t to std::string
    std::string to_string( const Sysman::freq_prop_src_freq_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_src_freq_t::resourceId : ";
        str += to_string(val.resourceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_request_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_request_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_freq_request_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "Sysman::freq_prop_freq_request_t::freqRequest : ";
        str += std::to_string(val.freqRequest);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_divider_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_divider_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_freq_divider_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "Sysman::freq_prop_freq_divider_t::divider : ";
        str += to_string(val.divider);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_multiplier_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_multiplier_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_freq_multiplier_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "Sysman::freq_prop_freq_multiplier_t::multiplier : ";
        str += to_string(val.multiplier);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_tdp_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_tdp_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_freq_tdp_t::freqTdp : ";
        str += std::to_string(val.freqTdp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_efficient_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_efficient_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_freq_efficient_t::freqEfficient : ";
        str += std::to_string(val.freqEfficient);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_freq_resolved_t to std::string
    std::string to_string( const Sysman::freq_prop_freq_resolved_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_freq_resolved_t::freqResolved : ";
        str += std::to_string(val.freqResolved);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_throttle_reasons_t to std::string
    std::string to_string( const Sysman::freq_prop_throttle_reasons_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_throttle_reasons_t::throttleReasons : ";
        str += std::to_string(val.throttleReasons);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_throttle_time_t to std::string
    std::string to_string( const Sysman::freq_prop_throttle_time_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_throttle_time_t::throttleTime : ";
        str += std::to_string(val.throttleTime);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_prop_capability_t to std::string
    std::string to_string( const Sysman::freq_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::freq_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::freq_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::freq_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::freq_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::freq_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_property_request_t to std::string
    std::string to_string( const Sysman::freq_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::freq_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::freq_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::freq_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::freq_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "Sysman::pwrwell_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_promo_cap_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_promo_cap_t val )
    {
        std::string str;
        
        str += "Sysman::pwrwell_prop_promo_cap_t::canChangePromoMode : ";
        str += std::to_string(val.canChangePromoMode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_promo_mode_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_promo_mode_t val )
    {
        std::string str;
        
        str += "Sysman::pwrwell_prop_promo_mode_t::mode : ";
        str += to_string(val.mode);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_utilization_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_utilization_t val )
    {
        std::string str;
        
        str += "Sysman::pwrwell_prop_utilization_t::sleepCounter : ";
        str += std::to_string(val.sleepCounter);
        str += "\n";
        
        str += "Sysman::pwrwell_prop_utilization_t::idleCounter : ";
        str += std::to_string(val.idleCounter);
        str += "\n";
        
        str += "Sysman::pwrwell_prop_utilization_t::activeCounter : ";
        str += std::to_string(val.activeCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_transitions_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_transitions_t val )
    {
        std::string str;
        
        str += "Sysman::pwrwell_prop_transitions_t::wakeCounter : ";
        str += std::to_string(val.wakeCounter);
        str += "\n";
        
        str += "Sysman::pwrwell_prop_transitions_t::execCounter : ";
        str += std::to_string(val.execCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_prop_capability_t to std::string
    std::string to_string( const Sysman::pwrwell_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::pwrwell_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::pwrwell_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::pwrwell_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::pwrwell_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::pwrwell_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pwrwell_property_request_t to std::string
    std::string to_string( const Sysman::pwrwell_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::pwrwell_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::pwrwell_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::pwrwell_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::pwrwell_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_prop_accel_assets_t to std::string
    std::string to_string( const Sysman::accel_prop_accel_assets_t val )
    {
        std::string str;
        
        str += "Sysman::accel_prop_accel_assets_t::assets : ";
        str += std::to_string(val.assets);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_prop_utilization_t to std::string
    std::string to_string( const Sysman::accel_prop_utilization_t val )
    {
        std::string str;
        
        str += "Sysman::accel_prop_utilization_t::activeCounter : ";
        str += std::to_string(val.activeCounter);
        str += "\n";
        
        str += "Sysman::accel_prop_utilization_t::idleCounter : ";
        str += std::to_string(val.idleCounter);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_prop_capability_t to std::string
    std::string to_string( const Sysman::accel_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::accel_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::accel_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::accel_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::accel_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::accel_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::accel_property_request_t to std::string
    std::string to_string( const Sysman::accel_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::accel_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::accel_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::accel_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::accel_property_request_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_retire_info_t to std::string
    std::string to_string( const Sysman::mem_retire_info_t val )
    {
        std::string str;
        
        str += "Sysman::mem_retire_info_t::address : ";
        str += std::to_string(val.address);
        str += "\n";
        
        str += "Sysman::mem_retire_info_t::reason : ";
        str += to_string(val.reason);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_type_t to std::string
    std::string to_string( const Sysman::mem_prop_type_t val )
    {
        std::string str;
        
        str += "Sysman::mem_prop_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_utilization_t to std::string
    std::string to_string( const Sysman::mem_prop_utilization_t val )
    {
        std::string str;
        
        str += "Sysman::mem_prop_utilization_t::total : ";
        str += std::to_string(val.total);
        str += "\n";
        
        str += "Sysman::mem_prop_utilization_t::stolen : ";
        str += std::to_string(val.stolen);
        str += "\n";
        
        str += "Sysman::mem_prop_utilization_t::bad : ";
        str += std::to_string(val.bad);
        str += "\n";
        
        str += "Sysman::mem_prop_utilization_t::allocated : ";
        str += std::to_string(val.allocated);
        str += "\n";
        
        str += "Sysman::mem_prop_utilization_t::unallocated : ";
        str += std::to_string(val.unallocated);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_bandwidth_t to std::string
    std::string to_string( const Sysman::mem_prop_bandwidth_t val )
    {
        std::string str;
        
        str += "Sysman::mem_prop_bandwidth_t::readCounter : ";
        str += std::to_string(val.readCounter);
        str += "\n";
        
        str += "Sysman::mem_prop_bandwidth_t::writeCounter : ";
        str += std::to_string(val.writeCounter);
        str += "\n";
        
        str += "Sysman::mem_prop_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_prop_capability_t to std::string
    std::string to_string( const Sysman::mem_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::mem_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::mem_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::mem_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::mem_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::mem_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::mem_property_request_t to std::string
    std::string to_string( const Sysman::mem_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::mem_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::mem_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::mem_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::mem_property_request_t::size : ";
        str += std::to_string(val.size);
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
    /// @brief Converts Sysman::link_prop_type_t to std::string
    std::string to_string( const Sysman::link_prop_type_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_type_t::type : ";
        str += to_string(val.type);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_bus_address_t to std::string
    std::string to_string( const Sysman::link_prop_bus_address_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_bus_address_t::str : ";
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
    /// @brief Converts Sysman::link_prop_peer_device_t to std::string
    std::string to_string( const Sysman::link_prop_peer_device_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_peer_device_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_avail_speeds_t to std::string
    std::string to_string( const Sysman::link_prop_avail_speeds_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_avail_speeds_t::num : ";
        str += std::to_string(val.num);
        str += "\n";
        
        str += "Sysman::link_prop_avail_speeds_t::pList : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pList);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_max_packet_size_t to std::string
    std::string to_string( const Sysman::link_prop_max_packet_size_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_max_packet_size_t::maxPacketSize : ";
        str += std::to_string(val.maxPacketSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_bandwidth_t to std::string
    std::string to_string( const Sysman::link_prop_bandwidth_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_bandwidth_t::recvCounter : ";
        str += std::to_string(val.recvCounter);
        str += "\n";
        
        str += "Sysman::link_prop_bandwidth_t::sendCounter : ";
        str += std::to_string(val.sendCounter);
        str += "\n";
        
        str += "Sysman::link_prop_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_speed_t to std::string
    std::string to_string( const Sysman::link_prop_speed_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_speed_t::pSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pSpeed);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_speed_range_t to std::string
    std::string to_string( const Sysman::link_prop_speed_range_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_speed_range_t::pMinSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pMinSpeed);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::link_prop_speed_range_t::pMaxSpeed : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pMaxSpeed);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_prop_capability_t to std::string
    std::string to_string( const Sysman::link_prop_capability_t val )
    {
        std::string str;
        
        str += "Sysman::link_prop_capability_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::link_prop_capability_t::support : ";
        str += to_string(val.support);
        str += "\n";
        
        str += "Sysman::link_prop_capability_t::access : ";
        str += to_string(val.access);
        str += "\n";
        
        str += "Sysman::link_prop_capability_t::minGetInterval : ";
        str += std::to_string(val.minGetInterval);
        str += "\n";
        
        str += "Sysman::link_prop_capability_t::minSetInterval : ";
        str += std::to_string(val.minSetInterval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::link_property_request_t to std::string
    std::string to_string( const Sysman::link_property_request_t val )
    {
        std::string str;
        
        str += "Sysman::link_property_request_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Sysman::link_property_request_t::property : ";
        str += to_string(val.property);
        str += "\n";
        
        str += "Sysman::link_property_request_t::pData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pData);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sysman::link_property_request_t::size : ";
        str += std::to_string(val.size);
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
